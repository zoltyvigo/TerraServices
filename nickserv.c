/* NickServ functions.
 *
 * Services is copyright (c) 1996-1999 Andrew Church.
 *     E-mail: <achurch@dragonfire.net>
 * Services is copyright (c) 1999-2000 Andrew Kempe.
 *     E-mail: <theshadow@shadowfire.org>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

/*
 * Note that with the addition of nick links, most functions in Services
 * access the "effective nick" (u->ni) to determine privileges and such.
 * The only functions which access the "real nick" (u->real_ni) are:
 *	various functions which set/check validation flags
 *	    (validate_user, cancel_user, nick_{identified,recognized},
 *	     do_identify)
 *	validate_user (adding a collide timeout on the real nick)
 *	cancel_user (deleting a timeout on the real nick)
 *	do_register (checking whether the real nick is registered)
 *	do_drop (dropping the real nick)
 *	do_link (linking the real nick to another)
 *	do_unlink (unlinking the real nick)
 *	chanserv.c/do_register (setting the founder to the real nick)
 * plus a few functions in users.c relating to nick creation/changing.
 */

#include "services.h"
#include "pseudo.h"

/*************************************************************************/

static NickInfo *nicklists[256];	/* One for each initial character */

#define TO_COLLIDE   0			/* Collide the user with this nick */
#define TO_RELEASE   1			/* Release a collided nick */

/*************************************************************************/

Mail *domainlist;

static int is_on_access(User *u, NickInfo *ni);
static void alpha_insert_nick(NickInfo *ni);
static NickInfo *makenick(const char *nick);
static int delnick(NickInfo *ni);
static void remove_links(NickInfo *ni);
static void delink(NickInfo *ni);

static void collide(NickInfo *ni, int from_timeout);
static void release(NickInfo *ni, int from_timeout);
static void add_ns_timeout(NickInfo *ni, int type, time_t delay);
static void del_ns_timeout(NickInfo *ni, int type);

#ifdef DEBUG_COMMANDS
static void do_commands(User *u);
#endif
static void do_help(User *u);
static void do_credits(User *u);
static void do_register(User *u);
static void do_mail(User *u);
static void do_identify(User *u);
static void do_drop(User *u);
static void do_set(User *u);
static void do_set_password(User *u, NickInfo *ni, char *param);
static void do_set_language(User *u, NickInfo *ni, char *param);
static void do_set_url(User *u, NickInfo *ni, char *param);
static void do_set_email(User *u, NickInfo *ni, char *param);
static void do_set_kill(User *u, NickInfo *ni, char *param);
static void do_set_secure(User *u, NickInfo *ni, char *param);
static void do_set_private(User *u, NickInfo *ni, char *param);
static void do_set_hide(User *u, NickInfo *ni, char *param);
static void do_set_noexpire(User *u, NickInfo *ni, char *param);
static void do_access(User *u);
static void do_link(User *u);
static void do_unlink(User *u);
static void do_listlinks(User *u);
static void do_info(User *u);
static void do_list(User *u);
static void do_recover(User *u);
static void do_release(User *u);
static void do_ghost(User *u);
static void do_status(User *u);
static void do_opers(User *u);
static void do_listemails(User *u);
#ifdef REG_NICK_MAIL
static void do_sendpass(User *u);
#endif
static void do_getpass(User *u);
static void do_suspend(User *u);
static void do_unsuspend(User *u);
static void do_forbid(User *u);
static void do_unforbid(User *u);
static void do_reguser(User *u);

/*************************************************************************/

static Command cmds[] = {
#ifdef DEBUG_COMMANDS
    { "COMMANDS", do_commands, NULL,  -1,                     -1,-1,-1,-1 },
#endif
    { "AYUDA",    do_help,     NULL,  -1,                     -1,-1,-1,-1 },
    { "HELP",     do_help,     NULL,  -1,                     -1,-1,-1,-1 },
    { "?",        do_help,     NULL,  -1,                     -1,-1,-1,-1 },
    { ":?",       do_help,     NULL,  -1,                     -1,-1,-1,-1 },
    { "CREDITS",  do_credits,  NULL,  SERVICES_CREDITS_TERRA, -1,-1,-1,-1 },
    { "CREDITOS", do_credits,  NULL,  SERVICES_CREDITS_TERRA, -1,-1,-1,-1 },
    { "REGISTRA", do_register, NULL,  NICK_HELP_REGISTER,     -1,-1,-1,-1 },    
    { "REGISTER", do_register, NULL,  NICK_HELP_REGISTER,     -1,-1,-1,-1 },
    { "MAIL",     do_mail,     NULL,  NICK_HELP_MAIL,         -1,-1,-1,-1 },
    { "IDENTIFICA", do_identify, NULL,  NICK_HELP_IDENTIFY,   -1,-1,-1,-1 },
    { "IDENTIFY", do_identify, NULL,  NICK_HELP_IDENTIFY,     -1,-1,-1,-1 },
    { "AUTH",     do_identify, NULL,  NICK_HELP_IDENTIFY,     -1,-1,-1,-1 },
    { "PASS",     do_identify, NULL,  NICK_HELP_IDENTIFY,     -1,-1,-1,-1 },
    { "BORRA",    do_drop,     NULL,  -1,
                NICK_HELP_DROP, NICK_SERVADMIN_HELP_DROP,
                NICK_SERVADMIN_HELP_DROP, NICK_SERVADMIN_HELP_DROP },    
    { "DROP",     do_drop,     is_services_oper,
		NICK_HELP_DROP, NICK_SERVADMIN_HELP_DROP,
		NICK_SERVADMIN_HELP_DROP, NICK_SERVADMIN_HELP_DROP },
    { "ACCESS",   do_access,   NULL,  NICK_HELP_ACCESS,       -1,-1,-1,-1 },
    { "LINKA",    do_link,     NULL,  NICK_HELP_LINK,         -1,-1,-1,-1 },
    { "LINK",     do_link,     NULL,  NICK_HELP_LINK,         -1,-1,-1,-1 },
    { "DESLINKA", do_unlink,   NULL,  NICK_HELP_UNLINK,       -1,-1,-1,-1 },
    { "UNLINK",   do_unlink,   NULL,  NICK_HELP_UNLINK,
               -1, NICK_SERVADMIN_HELP_UNLINK, NICK_SERVADMIN_HELP_UNLINK,
               NICK_SERVADMIN_HELP_UNLINK },
    { "DESLINK",  do_unlink,   NULL,  NICK_HELP_UNLINK,
                -1, NICK_SERVADMIN_HELP_UNLINK, NICK_SERVADMIN_HELP_UNLINK,
                NICK_SERVADMIN_HELP_UNLINK },
    { "SET",      do_set,      NULL,  NICK_HELP_SET,
		-1, NICK_SERVADMIN_HELP_SET,
		NICK_SERVADMIN_HELP_SET, NICK_SERVADMIN_HELP_SET },
    { "SET PASSWORD", NULL,    NULL,  NICK_HELP_SET_PASSWORD, -1,-1,-1,-1 },
    { "SET URL",      NULL,    NULL,  NICK_HELP_SET_URL,      -1,-1,-1,-1 },
    { "SET EMAIL",    NULL,    NULL,  NICK_HELP_SET_EMAIL,    -1,-1,-1,-1 },
    { "SET KILL",     NULL,    NULL,  NICK_HELP_SET_KILL,     -1,-1,-1,-1 },
    { "SET CHANGE",   NULL,    NULL,  NICK_HELP_SET_CHANGE,   -1,-1,-1,-1 },
    { "SET SECURE",   NULL,    NULL,  NICK_HELP_SET_SECURE,   -1,-1,-1,-1 },
    { "SET PRIVATE",  NULL,    NULL,  NICK_HELP_SET_PRIVATE,  -1,-1,-1,-1 },
    { "SET HIDE",     NULL,    NULL,  NICK_HELP_SET_HIDE,     -1,-1,-1,-1 },
    { "SET NOEXPIRE", NULL,    NULL,  -1, -1,
		NICK_SERVADMIN_HELP_SET_NOEXPIRE,
		NICK_SERVADMIN_HELP_SET_NOEXPIRE,
		NICK_SERVADMIN_HELP_SET_NOEXPIRE },
    { "RECOVER",  do_recover,  NULL,  NICK_HELP_RECOVER,      -1,-1,-1,-1 },
    { "RELEASE",  do_release,  NULL,  NICK_HELP_RELEASE,      -1,-1,-1,-1 },
    { "GHOST",    do_ghost,    NULL,  NICK_HELP_GHOST,        -1,-1,-1,-1 },
    { "INFO",     do_info,     NULL,  NICK_HELP_INFO,
		-1, NICK_HELP_INFO, NICK_SERVADMIN_HELP_INFO,
		NICK_SERVADMIN_HELP_INFO },
    { "LISTA",    do_list,     NULL,  -1,
                NICK_HELP_LIST, NICK_SERVADMIN_HELP_LIST,
                NICK_SERVADMIN_HELP_LIST, NICK_SERVADMIN_HELP_LIST },		
    { "LIST",     do_list,     NULL,  -1,
		NICK_HELP_LIST, NICK_SERVADMIN_HELP_LIST,
		NICK_SERVADMIN_HELP_LIST, NICK_SERVADMIN_HELP_LIST },
    { "ESTADO",   do_status,   NULL,  NICK_HELP_STATUS,       -1,-1,-1,-1 },
    { "STATUS",   do_status,   NULL,  NICK_HELP_STATUS,       -1,-1,-1,-1 },
    { "OPERS",    do_opers,    NULL,  NICK_HELP_OPERS,        -1,-1,-1,-1 },
    { "IRCOPS",   do_opers,    NULL,  NICK_HELP_OPERS,        -1,-1,-1,-1 },
    { "ADMINS",   do_opers,    NULL,  NICK_HELP_OPERS,        -1,-1,-1,-1 },   
    { "LISTEMAILS", do_listemails, is_services_oper, -1,
                -1, NICK_SERVADMIN_HELP_LISTEMAILS,
                NICK_SERVADMIN_HELP_LISTEMAILS, NICK_SERVADMIN_HELP_LISTEMAILS },
    { "LISTLINKS",do_listlinks,is_services_oper, -1,
		-1, NICK_SERVADMIN_HELP_LISTLINKS,
		NICK_SERVADMIN_HELP_LISTLINKS, NICK_SERVADMIN_HELP_LISTLINKS },
#ifdef REG_NICK_MAIL
    { "SENDPASS", do_sendpass,  is_services_oper,  -1,
                -1, NICK_SERVADMIN_HELP_SENDPASS,
                NICK_SERVADMIN_HELP_SENDPASS, NICK_SERVADMIN_HELP_SENDPASS },
#endif
    { "GETPASS",  do_getpass,  is_services_admin,  -1,
		-1, NICK_SERVADMIN_HELP_GETPASS,
		NICK_SERVADMIN_HELP_GETPASS, NICK_SERVADMIN_HELP_GETPASS },
    { "SUSPEND",  do_suspend,  is_services_oper,  -1,
                -1, NICK_SERVADMIN_HELP_SUSPEND,
                NICK_SERVADMIN_HELP_SUSPEND, NICK_SERVADMIN_HELP_SUSPEND },
    { "UNSUSPEND", do_unsuspend, is_services_oper,  -1,
                -1, NICK_SERVADMIN_HELP_UNSUSPEND,
                NICK_SERVADMIN_HELP_UNSUSPEND, NICK_SERVADMIN_HELP_UNSUSPEND },		
    { "FORBID",   do_forbid,   is_services_admin,  -1,
		-1, NICK_SERVADMIN_HELP_FORBID,
		NICK_SERVADMIN_HELP_FORBID, NICK_SERVADMIN_HELP_FORBID },
    { "UNFORBID", do_unforbid, is_services_admin,  -1,
                -1, NICK_SERVADMIN_HELP_UNFORBID,
                NICK_SERVADMIN_HELP_UNFORBID, NICK_SERVADMIN_HELP_UNFORBID },		
    { "REGUSER", do_reguser, is_services_admin,  -1,
                -1, NICK_SERVADMIN_HELP_REGUSER,
                NICK_SERVADMIN_HELP_REGUSER, NICK_SERVADMIN_HELP_REGUSER },		
    { NULL }
};

/*************************************************************************/
/*************************************************************************/

/* Display total number of registered nicks and info about each; or, if
 * a specific nick is given, display information about that nick (like
 * /msg NickServ INFO <nick>).  If count_only != 0, then only display the
 * number of registered nicks (the nick parameter is ignored).
 */

void listnicks(int count_only, const char *nick)
{
    int count = 0;
    NickInfo *ni;
    int i;
    char *end;

    if (count_only) {

	for (i = 0; i < 256; i++) {
	    for (ni = nicklists[i]; ni; ni = ni->next)
		count++;
	}
	printf("%d nicknames registered.\n", count);

    } else if (nick) {

	struct tm *tm;
	char buf[512];
	static const char commastr[] = ", ";
	int need_comma = 0;

	if (!(ni = findnick(nick))) {
	    printf("%s not registered.\n", nick);
	    return;
	} else if (ni->status & NS_VERBOTEN) {
	    printf("%s is FORBIDden.\n", nick);
	    return;
	}
	printf("%s is %s\n", nick, ni->last_realname);
	printf("Last seen address: %s\n", ni->last_usermask);
	tm = localtime(&ni->time_registered);
	strftime(buf, sizeof(buf), getstring((NickInfo *)NULL,STRFTIME_DATE_TIME_FORMAT), tm);
	printf("  Time registered: %s\n", buf);
	tm = localtime(&ni->last_seen);
	strftime(buf, sizeof(buf), getstring((NickInfo *)NULL,STRFTIME_DATE_TIME_FORMAT), tm);
	printf("   Last seen time: %s\n", buf);
	if (ni->url)
	    printf("              URL: %s\n", ni->url);
	if (ni->email)
	    printf("   E-mail address: %s\n", ni->email);
	*buf = 0;
	end = buf;
	if (ni->flags & NI_KILLPROTECT) {
	    end += snprintf(end, sizeof(buf)-(end-buf), "Kill protection");
	    need_comma = 1;
	}
	if (ni->flags & NI_SECURE) {
	    end += snprintf(buf, sizeof(buf)-(end-buf), "%sSecurity",
			need_comma ? commastr : "");
	    need_comma = 1;
	}
	if (ni->flags & NI_PRIVATE) {
	    end += snprintf(buf, sizeof(buf)-(end-buf), "%sPrivate",
			need_comma ? commastr : "");
	    need_comma = 1;
	}
	if (ni->status & NS_NO_EXPIRE) {
	    end += snprintf(buf, sizeof(buf)-(end-buf), "%sNo Expire",
			need_comma ? commastr : "");
	    need_comma = 1;
	}
	printf("          Options: %s\n", *buf ? buf : "None");

    } else {

	for (i = 0; i < 256; i++) {
	    for (ni = nicklists[i]; ni; ni = ni->next) {
		printf("    %s %-20s  %s\n", 
			    ni->status & NS_NO_EXPIRE ? "!" : " ", 
			    ni->nick, ni->status & NS_VERBOTEN ? 
				     "Disallowed (FORBID)" : ni->last_usermask);
		count++;
	    }
	}
	printf("%d nicknames registered.\n", count);

    }
}

/*************************************************************************/

/* Return information on memory use.  Assumes pointers are valid. */

void get_nickserv_stats(long *nrec, long *memuse, long *nforbid,
 long *nsuspend, long *naccess, long *nignore, long *nmemos, long *nmemosnr)
{
    long count = 0, mem = 0, cforbid = 0, csuspend = 0, caccess = 0;
    long cignore = 0, cmemos = 0, cmemosnr = 0;
    int i, j;
    NickInfo *ni;
    char **accptr;

    for (i = 0; i < 256; i++) {
	for (ni = nicklists[i]; ni; ni = ni->next) {
	    count++;
	    mem += sizeof(*ni);
            if (ni->status & NS_VERBOTEN)
                cforbid++;
            else if (ni->status & NS_SUSPENDED)
                csuspend++;
	    if (ni->url)
		mem += strlen(ni->url)+1;
	    if (ni->email)
		mem += strlen(ni->email)+1;
            if (ni->emailreg)
                mem += strlen(ni->emailreg)+1;		
            if (ni->msg_fullmemo)
                mem += strlen(ni->msg_fullmemo) +1;
	    if (ni->last_usermask)
		mem += strlen(ni->last_usermask)+1;
	    if (ni->last_realname)
		mem += strlen(ni->last_realname)+1;
	    if (ni->last_quit)
		mem += strlen(ni->last_quit)+1;
            caccess+= ni->accesscount;
	    mem += sizeof(char *) * ni->accesscount;
	    for (accptr=ni->access, j=0; j < ni->accesscount; accptr++, j++) {
		if (*accptr)
		    mem += strlen(*accptr)+1;
	    }
         /* AQUI IGNORE MEMO */

            cmemos += ni->memos.memocount;
	    mem += ni->memos.memocount * sizeof(Memo);
	    for (j = 0; j < ni->memos.memocount; j++) {
		if (ni->memos.memos[j].text)
		    mem += strlen(ni->memos.memos[j].text)+1;
                /* Memos no leidos */
                if (ni->memos.memos[j].flags & MF_UNREAD)
                    cmemosnr++;
	    }
	}
    }
    *nrec = count;
    *memuse = mem;
    *nforbid = cforbid;
    *nsuspend = csuspend;
    *naccess = caccess;
    *nignore = cignore;
    *nmemos = cmemos;
    *nmemosnr = cmemosnr;
}

/*************************************************************************/
/*************************************************************************/

/* NickServ initialization. */

void ns_init(void)
{
}

/*************************************************************************/

/* Main NickServ routine. */

void nickserv(const char *source, char *buf)
{
    char *cmd, *s;
    User *u = finduser(source);

    if (!u) {
	log("%s: user record for %s not found", s_NickServ, source);
	privmsg(s_NickServ, source,
		getstring((NickInfo *)NULL, USER_RECORD_NOT_FOUND));
	return;
    }

    cmd = strtok(buf, " ");

    if (!cmd) {
	return;
    } else if (stricmp(cmd, "\1PING") == 0) {
	if (!(s = strtok(NULL, "")))
	    s = "\1";
	notice(s_NickServ, source, "\1PING %s", s);
    } else if (stricmp(cmd, "\1VERSION\1") == 0) {
        notice(s_NickServ, source, "\1VERSION ircservices-%s+Terra-%s %s -- %s\1",
                   version_number, version_terra, s_NickServ, version_build);
    } else if (skeleton) {
	notice_lang(s_NickServ, u, SERVICE_OFFLINE, s_NickServ);
    } else {
	run_cmd(s_NickServ, u, cmds, cmd);
    }

}

/*************************************************************************/

/* Load/save data files. */


#define SAFE(x) do {					\
    if ((x) < 0) {					\
	if (!forceload)					\
	    fatal("Read error on %s", NickDBName);	\
	failed = 1;					\
	break;						\
    }							\
} while (0)


static void load_old_ns_dbase(dbFILE *f, int ver)
{
    struct nickinfo_ {
	NickInfo *next, *prev;
	char nick[NICKMAX];
	char pass[PASSMAX];
	char *last_usermask;
	char *last_realname;
	time_t time_registered;
	time_t last_seen;
	long accesscount;
	char **access;
	long flags;
	time_t id_timestamp;
	unsigned short memomax;
	unsigned short channelcount;
	char *url;
	char *email;
    } old_nickinfo;

    int i, j, c;
    NickInfo *ni, **last, *prev;
    int failed = 0;

    for (i = 33; i < 256 && !failed; i++) {
	last = &nicklists[i];
	prev = NULL;
	while ((c = getc_db(f)) != 0) {
	    if (c != 1)
		fatal("Invalid format in %s", NickDBName);
	    SAFE(read_variable(old_nickinfo, f));
	    if (debug >= 3)
		log("debug: load_old_ns_dbase read nick %s", old_nickinfo.nick);
	    ni = scalloc(1, sizeof(NickInfo));
	    *last = ni;
	    last = &ni->next;
	    ni->prev = prev;
	    prev = ni;
	    strscpy(ni->nick, old_nickinfo.nick, NICKMAX);
	    strscpy(ni->pass, old_nickinfo.pass, PASSMAX);
	    ni->time_registered = old_nickinfo.time_registered;
	    ni->last_seen = old_nickinfo.last_seen;
	    ni->accesscount = old_nickinfo.accesscount;
	    ni->flags = old_nickinfo.flags;
	    if (ver < 3)	/* Memo max field created in ver 3 */
		ni->memos.memomax = MSMaxMemos;
	    else if (old_nickinfo.memomax)
		ni->memos.memomax = old_nickinfo.memomax;
	    else
		ni->memos.memomax = -1;  /* Unlimited is now -1 */
	    /* Reset channel count because counting was broken in old
	     * versions; load_old_cs_dbase() will calculate the count */
	    ni->channelcount = 0;
	    ni->channelmax = CSMaxReg;
	    ni->language = DEF_LANGUAGE;
	    /* ENCRYPTEDPW and VERBOTEN moved from ni->flags to ni->status */
	    if (ni->flags & 4)
		ni->status |= NS_VERBOTEN;
	    if (ni->flags & 8)
		ni->status |= NS_ENCRYPTEDPW;
	    ni->flags &= ~0xE000000C;
#ifdef USE_ENCRYPTION
	    if (!(ni->status & (NS_ENCRYPTEDPW | NS_VERBOTEN))) {
		if (debug)
		    log("debug: %s: encrypting password for `%s' on load",
				s_NickServ, ni->nick);
		if (encrypt_in_place(ni->pass, PASSMAX) < 0)
		    fatal("%s: Can't encrypt `%s' nickname password!",
				s_NickServ, ni->nick);
		ni->status |= NS_ENCRYPTEDPW;
	    }
#else
	    if (ni->status & NS_ENCRYPTEDPW) {
		/* Bail: it makes no sense to continue with encrypted
		 * passwords, since we won't be able to verify them */
		fatal("%s: load database: password for %s encrypted "
		          "but encryption disabled, aborting",
		          s_NickServ, ni->nick);
	    }
#endif
	    if (old_nickinfo.url)
		SAFE(read_string(&ni->url, f));
	    if (old_nickinfo.email)
		SAFE(read_string(&ni->email, f));
	    SAFE(read_string(&ni->last_usermask, f));
	    if (!ni->last_usermask)
		ni->last_usermask = sstrdup("@");
	    SAFE(read_string(&ni->last_realname, f));
	    if (!ni->last_realname)
		ni->last_realname = sstrdup("");
	    if (ni->accesscount) {
		char **access, *s;
		if (ni->accesscount > NSAccessMax)
		    ni->accesscount = NSAccessMax;
		access = smalloc(sizeof(char *) * ni->accesscount);
		ni->access = access;
		for (j = 0; j < ni->accesscount; j++, access++)
		    SAFE(read_string(access, f));
		while (j < old_nickinfo.accesscount) {
		    SAFE(read_string(&s, f));
		    if (s)
			free(s);
		    j++;
		}
	    }
	    ni->id_timestamp = 0;
	    if (ver < 3) {
		ni->flags |= NI_MEMO_SIGNON | NI_MEMO_RECEIVE;
	    } else if (ver == 3) {
		if (!(ni->flags & (NI_MEMO_SIGNON | NI_MEMO_RECEIVE)))
		    ni->flags |= NI_MEMO_SIGNON | NI_MEMO_RECEIVE;
	    }
	} /* while (getc_db(f) != 0) */
	*last = NULL;
    } /* for (i) */
    if (debug >= 2)
	log("debug: load_old_ns_dbase(): loading memos");
    load_old_ms_dbase();
}

static void load_domainmail_db(void)
{
    FILE *file;
    char buff[65535];
    char *email;
    Mail *mail, *last= NULL;
    
    domainlist = NULL;
    
    file = fopen("listamails.txt", "r");
    
    if (!file)
        return;
        
    if (!fread(buff, 1, sizeof(buff), file))
        return;
        
    email = strtok(buff,"\n\n\t ");
    
    for(;email; email = strtok(NULL, "\r\n\t ")) {
        mail = smalloc(sizeof(Mail *));
        mail->domain = sstrdup(email);
        mail->next = NULL;
        
        if (last)
            last->next = mail;
        if (!domainlist)
            domainlist = mail;   

        last = mail;
    }
    
    fclose(file);    
}

void load_ns_dbase(void)
{
    dbFILE *f;
    int ver, i, j, c;
    NickInfo *ni, **last, *prev;
    int failed = 0;

    load_domainmail_db();

    if (!(f = open_db(s_NickServ, NickDBName, "r", NICK_VERSION)))
	return;

    switch (ver = get_file_version(f)) {
      case 10:
      case 9:
      case 8:
      case 7:
      case 6:
      case 5:
	for (i = 0; i < 256 && !failed; i++) {
	    int32 tmp32;
	    last = &nicklists[i];
	    prev = NULL;
	    while ((c = getc_db(f)) == 1) {
		if (c != 1)
		    fatal("Invalid format in %s", NickDBName);
		ni = scalloc(sizeof(NickInfo), 1);
		*last = ni;
		last = &ni->next;
		ni->prev = prev;
		prev = ni;
		SAFE(read_buffer(ni->nick, f));
		SAFE(read_buffer(ni->pass, f));
		SAFE(read_string(&ni->url, f));
		SAFE(read_string(&ni->email, f));
                if (ver >= 9) {
                    SAFE(read_string(&ni->emailreg, f));                
                } else {		
                    ni->emailreg = NULL;  
                }
                if (ver >= 10) {
                    SAFE(read_string(&ni->msg_fullmemo, f));
                } else {
                    ni->msg_fullmemo = NULL;
                }
		SAFE(read_string(&ni->last_usermask, f));
		if (!ni->last_usermask)
		    ni->last_usermask = sstrdup("@");
		SAFE(read_string(&ni->last_realname, f));
		if (!ni->last_realname)
		    ni->last_realname = sstrdup("");
		SAFE(read_string(&ni->last_quit, f));
		SAFE(read_int32(&tmp32, f));
		ni->time_registered = tmp32;
		SAFE(read_int32(&tmp32, f));
		ni->last_seen = tmp32;
                if (ver >= 10) {
                    SAFE(read_int32(&tmp32, f));
                    ni->last_changed_pass = tmp32;
                } else {
                    ni->last_changed_pass = time(NULL);
                }
		SAFE(read_int16(&ni->status, f));
		ni->status &= ~NS_TEMPORARY;
#ifdef USE_ENCRYPTION
		if (!(ni->status & (NS_ENCRYPTEDPW | NS_VERBOTEN))) {
		    if (debug)
			log("debug: %s: encrypting password for `%s' on load",
				s_NickServ, ni->nick);
		    if (encrypt_in_place(ni->pass, PASSMAX) < 0)
			fatal("%s: Can't encrypt `%s' nickname password!",
				s_NickServ, ni->nick);
		    ni->status |= NS_ENCRYPTEDPW;
		}
#else
		if (ni->status & NS_ENCRYPTEDPW) {
		    /* Bail: it makes no sense to continue with encrypted
		     * passwords, since we won't be able to verify them */
		    fatal("%s: load database: password for %s encrypted "
		          "but encryption disabled, aborting",
		          s_NickServ, ni->nick);
		}
#endif
                /* Suspensi�n y forbid de nicks
                 * zoltan 8/11/2000
                 */
                if (ver >= 8) {
                    SAFE(read_string(&ni->suspendby, f));
                    SAFE(read_string(&ni->suspendreason, f));
                    SAFE(read_int32(&tmp32, f));
                    ni->time_suspend = tmp32;
                    SAFE(read_int32(&tmp32, f));
                    ni->time_expiresuspend = tmp32;
                    SAFE(read_string(&ni->forbidby, f));
                    SAFE(read_string(&ni->forbidreason, f));
                } else {
                    ni->suspendby = NULL;
                    ni->suspendreason = NULL;
                    ni->time_suspend = 0;
                    ni->time_expiresuspend = 0;
                    ni->forbidby = NULL;
                    ni->forbidreason = NULL;
                }                
		/* Store the _name_ of the link target in ni->link for now;
		 * we'll resolve it after we've loaded all the nicks */
		SAFE(read_string((char **)&ni->link, f));
		SAFE(read_int16(&ni->linkcount, f));
		if (ni->link) {
		    SAFE(read_int16(&ni->channelcount, f));
		    /* No other information saved for linked nicks, since
		     * they get it all from their link target */
		    ni->flags = 0;
		    ni->accesscount = 0;
		    ni->access = NULL;
		    ni->memos.memocount = 0;
		    ni->memos.memomax = MSMaxMemos;
		    ni->memos.memos = NULL;
		    ni->channelmax = CSMaxReg;
		    ni->language = DEF_LANGUAGE;
		} else {
		    SAFE(read_int32(&ni->flags, f));
		    if (!NSAllowKillImmed)
			ni->flags &= ~NI_KILL_IMMED;
		    SAFE(read_int16(&ni->accesscount, f));
		    if (ni->accesscount) {
			char **access;
			access = smalloc(sizeof(char *) * ni->accesscount);
			ni->access = access;
			for (j = 0; j < ni->accesscount; j++, access++)
			    SAFE(read_string(access, f));
		    }
		    SAFE(read_int16(&ni->memos.memocount, f));
		    SAFE(read_int16(&ni->memos.memomax, f));
		    if (ni->memos.memocount) {
			Memo *memos;
			memos = smalloc(sizeof(Memo) * ni->memos.memocount);
			ni->memos.memos = memos;
			for (j = 0; j < ni->memos.memocount; j++, memos++) {
			    SAFE(read_int32(&memos->number, f));
			    SAFE(read_int16(&memos->flags, f));
			    SAFE(read_int32(&tmp32, f));
			    memos->time = tmp32;
			    SAFE(read_buffer(memos->sender, f));
			    SAFE(read_string(&memos->text, f));
			}
		    }
		    SAFE(read_int16(&ni->channelcount, f));
		    SAFE(read_int16(&ni->channelmax, f));
		    if (ver == 5) {
			/* Fields not initialized properly for new nicks */
			/* These will be updated by load_cs_dbase() */
			ni->channelcount = 0;
			ni->channelmax = CSMaxReg;
		    }
		    SAFE(read_int16(&ni->language, f));
		}
		ni->id_timestamp = 0;
	    } /* while (getc_db(f) != 0) */
	    *last = NULL;
	} /* for (i) */

	/* Now resolve links */
	for (i = 0; i < 256; i++) {
	    for (ni = nicklists[i]; ni; ni = ni->next) {
		if (ni->link)
		    ni->link = findnick((char *)ni->link);
	    }
	}

	break;

      case 4:
      case 3:
      case 2:
      case 1:
	load_old_ns_dbase(f, ver);
	break;

      default:
	fatal("Unsupported version number (%d) on %s", ver, NickDBName);

    } /* switch (version) */

    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do {						\
    if ((x) < 0) {						\
	restore_db(f);						\
	log_perror("Write error on %s", NickDBName);		\
	if (time(NULL) - lastwarn > WarningTimeout) {		\
	    canalopers(NULL, "Write error on %s: %s", NickDBName,	\
			strerror(errno));			\
	    lastwarn = time(NULL);				\
	}							\
	return;							\
    }								\
} while (0)

void save_ns_dbase(void)
{
    dbFILE *f;
    int i, j;
    NickInfo *ni;
    char **access;
    Memo *memos;
    static time_t lastwarn = 0;

    if (!(f = open_db(s_NickServ, NickDBName, "w", NICK_VERSION)))
	return;
    for (i = 0; i < 256; i++) {
	for (ni = nicklists[i]; ni; ni = ni->next) {
	    SAFE(write_int8(1, f));
	    SAFE(write_buffer(ni->nick, f));
	    SAFE(write_buffer(ni->pass, f));
	    SAFE(write_string(ni->url, f));
	    SAFE(write_string(ni->email, f));
	    SAFE(write_string(ni->emailreg, f));
            SAFE(write_string(ni->msg_fullmemo, f));
	    SAFE(write_string(ni->last_usermask, f));
	    SAFE(write_string(ni->last_realname, f));
	    SAFE(write_string(ni->last_quit, f));
	    SAFE(write_int32(ni->time_registered, f));
	    SAFE(write_int32(ni->last_seen, f));
            SAFE(write_int32(ni->last_changed_pass, f));
	    SAFE(write_int16(ni->status, f));
            SAFE(write_string(ni->suspendby, f));
            SAFE(write_string(ni->suspendreason, f));
            SAFE(write_int32(ni->time_suspend, f));
            SAFE(write_int32(ni->time_expiresuspend, f));
            SAFE(write_string(ni->forbidby, f));
            SAFE(write_string(ni->forbidreason, f));
	    if (ni->link) {
		SAFE(write_string(ni->link->nick, f));
		SAFE(write_int16(ni->linkcount, f));
		SAFE(write_int16(ni->channelcount, f));
	    } else {
		SAFE(write_string(NULL, f));
		SAFE(write_int16(ni->linkcount, f));
		SAFE(write_int32(ni->flags, f));
		SAFE(write_int16(ni->accesscount, f));
		for (j=0, access=ni->access; j<ni->accesscount; j++, access++)
		    SAFE(write_string(*access, f));
		SAFE(write_int16(ni->memos.memocount, f));
		SAFE(write_int16(ni->memos.memomax, f));
		memos = ni->memos.memos;
		for (j = 0; j < ni->memos.memocount; j++, memos++) {
		    SAFE(write_int32(memos->number, f));
		    SAFE(write_int16(memos->flags, f));
		    SAFE(write_int32(memos->time, f));
		    SAFE(write_buffer(memos->sender, f));
		    SAFE(write_string(memos->text, f));
		}
		SAFE(write_int16(ni->channelcount, f));
		SAFE(write_int16(ni->channelmax, f));
		SAFE(write_int16(ni->language, f));
	    }
	} /* for (ni) */
	SAFE(write_int8(0, f));
    } /* for (i) */
    close_db(f);
}

#undef SAFE

/*************************************************************************/

/* Check whether a user is on the access list of the nick they're using, or
 * if they're the same user who last identified for the nick.  If not, send
 * warnings as appropriate.  If so (and not NI_SECURE), update last seen
 * info.  Return 1 if the user is valid and recognized, 0 otherwise (note
 * that this means an NI_SECURE nick will return 0 from here unless the
 * user's timestamp matches the last identify timestamp).  If the user's
 * nick is not registered, 0 is returned.
 */

int validate_user(User *u)
{
    NickInfo *ni;
    int on_access;

    if (!(ni = u->real_ni))
	return 0;

    if (ni->status & NS_VERBOTEN) {
	notice_lang(s_NickServ, u, NICK_MAY_NOT_BE_USED);
	if (NSForceNickChange)
	    notice_lang(s_NickServ, u, FORCENICKCHANGE_IN_1_MINUTE);
	else
	    notice_lang(s_NickServ, u, DISCONNECT_IN_1_MINUTE);
	add_ns_timeout(ni, TO_COLLIDE, 60);
	return 0;
    }
    
    if (ni->status & NS_SUSPENDED) {
        notice_lang(s_NickServ, u, NICK_SUSPENDED, ni->nick, ni->suspendreason);
        return 0;
    }    

#ifdef OBSOLETO
/* Con el control de servers, esto no sirve de nada :P */
    if (!NoSplitRecovery) {
	/* XXX: This code should be checked to ensure it can't be fooled */
	if (ni->id_timestamp != 0 && u->signon == ni->id_timestamp) {
	    char buf[256];
	    snprintf(buf, sizeof(buf), "%s@%s", u->username, u->host);
	    if (strcmp(buf, ni->last_usermask) == 0) {
		ni->status |= NS_IDENTIFIED;
		return 1;
	    }
	}
    }
#endif

    on_access = is_on_access(u, u->ni);
    if (on_access)
	ni->status |= NS_ON_ACCESS;

    if (!(u->ni->flags & NI_SECURE) && on_access) {
	ni->status |= NS_RECOGNIZED;
	ni->last_seen = time(NULL);
	if (ni->last_usermask)
	    free(ni->last_usermask);
	ni->last_usermask = smalloc(strlen(u->username)+strlen(u->host)+2);
	sprintf(ni->last_usermask, "%s@%s", u->username, u->host);
	if (ni->last_realname)
	    free(ni->last_realname);
	ni->last_realname = sstrdup(u->realname);
	return 1;
    }

    if (on_access || !(u->ni->flags & NI_KILL_IMMED)) {
	if (u->ni->flags & NI_SECURE)
	    notice_lang(s_NickServ, u, NICK_IS_SECURE, s_NickServ);
	else
	    notice_lang(s_NickServ, u, NICK_IS_REGISTERED, s_NickServ);
    }

    if ((u->ni->flags & NI_KILLPROTECT) && !on_access) {
	if (u->ni->flags & NI_KILL_IMMED) {
//	    collide(ni, 0);
            add_ns_timeout(ni, TO_COLLIDE, 1);
	} else if (u->ni->flags & NI_KILL_QUICK) {
	    if (NSForceNickChange)
	    	notice_lang(s_NickServ, u, FORCENICKCHANGE_IN_20_SECONDS);
	    else
              	notice_lang(s_NickServ, u, DISCONNECT_IN_20_SECONDS);
	    add_ns_timeout(ni, TO_COLLIDE, 20);
	} else {
	    if (NSForceNickChange)
	    	notice_lang(s_NickServ, u, FORCENICKCHANGE_IN_1_MINUTE);
	    else
	    	notice_lang(s_NickServ, u, DISCONNECT_IN_1_MINUTE);
	    add_ns_timeout(ni, TO_COLLIDE, 60);
	}
    }

    return 0;
}

/*************************************************************************/

/* Cancel validation flags for a nick (i.e. when the user with that nick
 * signs off or changes nicks).  Also cancels any impending collide. */

void cancel_user(User *u)
{
    NickInfo *ni = u->real_ni;
    char realname[NICKMAX+16]; /*Long enough for s_NickServ and " Enforcement" */
    if (ni) {
       snprintf(realname, sizeof(realname), "Protecci�n de %s", s_NickServ);
        if (ni->status & NS_GUESTED) {
            send_nick(u->nick, NSEnforcerUser, NSEnforcerHost, ServerName,
                       realname);
	    add_ns_timeout(ni, TO_RELEASE, NSReleaseTimeout);
	    ni->status &= ~NS_TEMPORARY;
	    ni->status |= NS_KILL_HELD;
	} else {
	    ni->status &= ~NS_TEMPORARY;
	}
	del_ns_timeout(ni, TO_COLLIDE);
    }
}

/*************************************************************************/

/* Return whether a user has identified for their nickname. */

int nick_identified(User *u)
{
    return u->real_ni && (u->real_ni->status & NS_IDENTIFIED);
}

/*************************************************************************/

/* Return whether a user is recognized for their nickname. */

int nick_recognized(User *u)
{
    return u->real_ni && (u->real_ni->status & (NS_IDENTIFIED | NS_RECOGNIZED));
}

/*************************************************************************/

/* Nick suspendido. */

int nick_suspendied(User *u)
{
    return u->real_ni && (u->real_ni->status & NS_SUSPENDED);
}
    
/*************************************************************************/

/* Remove all nicks which have expired.  Also update last-seen time for all
 * nicks.
 */

void expire_nicks()
{
    User *u;
    NickInfo *ni, *next;
    int i;
    time_t now = time(NULL);

    /* Assumption: this routine takes less than NSExpire seconds to run.
     * If it doesn't, some users may end up with invalid user->ni pointers. */
    for (u = firstuser(); u; u = nextuser()) {
	if (u->real_ni) {
	    if (debug >= 2)
		log("debug: NickServ: updating last seen time for %s", u->nick);
	    u->real_ni->last_seen = time(NULL);
	}
    }
    if (!NSExpire || opt_noexpire)
	return;
    for (i = 0; i < 256; i++) {
	for (ni = nicklists[i]; ni; ni = next) {
	    next = ni->next;
 
      /* Expiracion suspension nicks suspendidos */     
            if (ni->status & NS_SUSPENDED)
                if (ni->time_expiresuspend != 0 && ni->time_expiresuspend <= now) {
                    if (NSExpire && NSSuspendGrace &&
                           (now - ni->last_seen >= NSExpire - NSSuspendGrace))
                        ni->last_seen = now - NSExpire + NSSuspendGrace;	    
                    log("Expiring nick-suspend for %s", ni->nick);
                    canalopers(s_NickServ, "Expirando suspension del nick %s", ni->nick);
                    free(ni->suspendby);
                    free(ni->suspendreason);
                    ni->time_suspend = 0;
                    ni->time_expiresuspend = 0;
                    ni->status &= ~NS_SUSPENDED;                        
                }     
                        
      /* Expiracion nicks */
	    if (now - ni->last_seen >= NSExpire
			&& !(ni->status & (NS_VERBOTEN | NS_NO_EXPIRE | NS_SUSPENDED))) {
		log("Expiring nickname %s", ni->nick);
		canalopers(s_NickServ, "Expirando el nick %s", ni->nick);
		delnick(ni);
	    }
	    
	}
    }
}

/*************************************************************************/
/*************************************************************************/

/* Return the NickInfo structure for the given nick, or NULL if the nick
 * isn't registered. */

NickInfo *findnick(const char *nick)
{
    NickInfo *ni;

/* A�adido soporte toLower y toUpper para evitar conflictos con nicks,
 * debido a la arquitectura de undernet, que considera como equivalentes
 * los nicks [zoltan] y {zoltan} entre otros signos.
 * As� los Services, lo considerar� como el mismo nick, impidiendo que
 * se pueda registrar {zoltan} existiendo [zoltan]
 *
 * Signos equivalentes
 * Min�sculas == May�sculas (esto ya estaba antes con tolower)
 * [ == {
 * ] == }
 * ^ == ~
 * \ == |
 *
 * Copiado codigo common.c y common.h del ircu de Undernet
 *
 * zoltan 1/11/2000
 */       
 /* Codigo Antiguo */
 /*
    for (ni = nicklists[tolower(*nick)]; ni; ni = ni->next) {
	if (stricmp(ni->nick, nick) == 0)
	    return ni;
    }
 */

    if(!nick)
        return NULL;

 /* Codigo Nuevo */
    for (ni = nicklists[toLower(*nick)]; ni; ni = ni->next) {
        if (strCasecmp(ni->nick, nick) == 0)
            return ni;
    }    
 
    for (ni = nicklists[toUpper(*nick)]; ni; ni = ni->next) {
        if (strCasecmp(ni->nick, nick) == 0)
            return ni;
    }
    return NULL;  
}

/*************************************************************************/

/* Return the "master" nick for the given nick; i.e., trace the linked list
 * through the `link' field until we find a nickname with a NULL `link'
 * field.  Assumes `ni' is not NULL.
 *
 * Note that we impose an arbitrary limit of 512 nested links.  This is to
 * prevent infinite loops in case someone manages to create a circular
 * link.  If we pass this limit, we arbitrarily cut off the link at the
 * initial nick.
 */

NickInfo *getlink(NickInfo *ni)
{
    NickInfo *orig = ni;
    int i = 0;
    
    if(ni) 
        while (ni->link && ++i < 512)
	    ni = ni->link;
    if (i >= 512) {
	log("%s: Infinite loop(?) found at nick %s for nick %s, cutting link",
		s_NickServ, ni->nick, orig->nick);
	orig->link = NULL;
	ni = orig;
	/* FIXME: we should sanitize the data fields */
    }
    return ni;
}

/*************************************************************************/
/*********************** NickServ private routines ***********************/
/*************************************************************************/

/* Is the given user's address on the given nick's access list?  Return 1
 * if so, 0 if not. */

static int is_on_access(User *u, NickInfo *ni)
{
    int i;
    char *buf;

    if (ni->accesscount == 0)
	return 0;
    i = strlen(u->username);
    buf = smalloc(i + strlen(u->host) + 2);
    sprintf(buf, "%s@%s", u->username, u->host);
    strlower(buf+i+1);
    for (i = 0; i < ni->accesscount; i++) {
	if (match_wild_nocase(ni->access[i], buf)) {
	    free(buf);
	    return 1;
	}
    }
    free(buf);
    return 0;
}

/*************************************************************************/

/* Insert a nick alphabetically into the database. */

static void alpha_insert_nick(NickInfo *ni)
{
    NickInfo *ptr, *prev;
    char *nick = ni->nick;

    for (prev = NULL, ptr = nicklists[tolower(*nick)];
			ptr && stricmp(ptr->nick, nick) < 0;
			prev = ptr, ptr = ptr->next)
	;
    ni->prev = prev;
    ni->next = ptr;
    if (!prev)
	nicklists[tolower(*nick)] = ni;
    else
	prev->next = ni;
    if (ptr)
	ptr->prev = ni;
}

/*************************************************************************/

/* Add a nick to the database.  Returns a pointer to the new NickInfo
 * structure if the nick was successfully registered, NULL otherwise.
 * Assumes nick does not already exist.
 */

static NickInfo *makenick(const char *nick)
{
    NickInfo *ni;

    ni = scalloc(sizeof(NickInfo), 1);
    strscpy(ni->nick, nick, NICKMAX);
    alpha_insert_nick(ni);
    return ni;
}

/*************************************************************************/

/* Remove a nick from the NickServ database.  Return 1 on success, 0
 * otherwise.  Also deletes the nick from any ChanServ/OperServ lists it is
 * on.
 */

static int delnick(NickInfo *ni)
{
    int i;

    cs_remove_nick(ni);
    os_remove_nick(ni);
#ifdef CYBER
    cyber_remove_nick(ni);
#endif
    if (ni->linkcount)
	remove_links(ni);
    if (ni->link)
	ni->link->linkcount--;
    if (ni->next)
	ni->next->prev = ni->prev;
    if (ni->prev)
	ni->prev->next = ni->next;
    else
	nicklists[tolower(*ni->nick)] = ni->next;
    if (ni->emailreg)
    	free(ni->emailreg);
    if (ni->msg_fullmemo)
        free(ni->msg_fullmemo);
    if (ni->last_usermask)
	free(ni->last_usermask);
    if (ni->last_realname)
	free(ni->last_realname);
    if (ni->suspendby)
        free(ni->suspendby);
    if (ni->suspendreason)
        free(ni->suspendreason);
    if (ni->forbidby)
        free(ni->forbidby);
    if (ni->forbidreason)
        free(ni->forbidreason);	
    if (ni->access) {
	for (i = 0; i < ni->accesscount; i++) {
	    if (ni->access[i])
		free(ni->access[i]);
	}
	free(ni->access);
    }
    if (ni->memos.memos) {
	for (i = 0; i < ni->memos.memocount; i++) {
	    if (ni->memos.memos[i].text)
		free(ni->memos.memos[i].text);
	}
	free(ni->memos.memos);
    }
    free(ni);
    return 1;
}

/*************************************************************************/

/* Remove any links to the given nick (i.e. prior to deleting the nick).
 * Note this is currently linear in the number of nicks in the database--
 * that's the tradeoff for the nice clean method of keeping a single parent
 * link in the data structure.
 */

static void remove_links(NickInfo *ni)
{
    int i;
    NickInfo *ptr;

    for (i = 0; i < 256; i++) {
	for (ptr = nicklists[i]; ptr; ptr = ptr->next) {
	    if (ptr->link == ni) {
		if (ni->link) {
		    ptr->link = ni->link;
		    ni->link->linkcount++;
		} else
		    delink(ptr);
	    }
	}
    }
}

/*************************************************************************/

/* Break a link from the given nick to its parent. */

static void delink(NickInfo *ni)
{
    NickInfo *link;

    link = ni->link;
    ni->link = NULL;
    do {
	link->channelcount -= ni->channelcount;
	if (link->link)
	    link = link->link;
    } while (link->link);
    ni->status = link->status;
    link->status &= ~NS_TEMPORARY;
    ni->flags = link->flags;
    ni->channelmax = link->channelmax;
    ni->memos.memomax = link->memos.memomax;
    ni->language = link->language;
    if (link->accesscount > 0) {
	char **access;
	int i;

	ni->accesscount = link->accesscount;
	access = smalloc(sizeof(char *) * ni->accesscount);
	ni->access = access;
	for (i = 0; i < ni->accesscount; i++, access++)
	    *access = sstrdup(link->access[i]);
    }
    link->linkcount--;
}

/*************************************************************************/
/*************************************************************************/

/* Collide a nick. 
 *
 * When connected to a network using DALnet servers, version 4.4.15 and above, 
 * Services is able to force a nick change instead of killing the user.
 * The new nick takes the form "Guest######". If a nick change is forced, we
 * do not introduce the enforcer nick until the user's nick actually changes. 
 * This is watched for and done in cancel_user().
 *
 *     - Atomic
 *     - Unique within a 24 hour period - basically this means that if someone
 *       has a "Guest" nick for more than 24 hours, there is a slight chance
 *       that a new "Guest" could be collided. I really don't see this as a
 *       problem.
 *     - Reasonably unpredictable
 *
 * -TheShadow
 */

static void collide(NickInfo *ni, int from_timeout)
{
    User *u;

    u = finduser(ni->nick);

    if (!from_timeout)
	del_ns_timeout(ni, TO_COLLIDE);

    if (NSForceNickChange) {
#ifdef GUARDADO /* Guardo codigo */
	struct timeval tv;
	char guestnick[NICKMAX];
        static long sec = -1;
        static long usec = -1;
        long tmp_sec, tmp_usec;
        uint16 counter = 0;

	gettimeofday(&tv, NULL);
        tmp_usec = tv.tv_usec / 10000;
        if (usec == tmp_usec && sec == tmp_sec) {
            counter++;
        } else {
            sec = tmp_sec;
            usec = tmp_usec;
            counter = 0;
        }
        snprintf(guestnick, sizeof(guestnick), "%s%ld%d%ld",
                        NSGuestNickPrefix, usec, counter, sec);
 
        notice_lang(s_NickServ, u, FORCENICKCHANGE_NOW, guestnick);

#endif
//        notice_lang(s_NickServ, u, FORCENICKCHANGE_NOW, guestnick);
        notice_lang(s_NickServ, u, FORCENICKCHANGE_NOW, "ircXXXXXX");

//	send_cmd(NULL, "SVSNICK %s %s :%ld", ni->nick, guestnick, time(NULL));
        /* Comando SVSNICK de TERRA */
        send_cmd(ServerName, "SVSNICK %s", ni->nick);        
	ni->status |= NS_GUESTED;
    } else {  
	notice_lang(s_NickServ, u, DISCONNECT_NOW);
    	kill_user(s_NickServ, ni->nick, "Nick kill enforced");
    	send_cmd(NULL, "NICK %s %ld 1 %s %s %s :Protegiendo a %s",
		ni->nick, time(NULL), NSEnforcerUser, NSEnforcerHost,
		ServerName, ni->nick);
	ni->status |= NS_KILL_HELD;
	add_ns_timeout(ni, TO_RELEASE, NSReleaseTimeout);
    }
}

/*************************************************************************/

/* Release hold on a nick. */

static void release(NickInfo *ni, int from_timeout)
{
    if (!from_timeout)
	del_ns_timeout(ni, TO_RELEASE);
    send_cmd(ni->nick, "QUIT");
    ni->status &= ~NS_KILL_HELD;
}

/*************************************************************************/
/*************************************************************************/

static struct my_timeout {
    struct my_timeout *next, *prev;
    NickInfo *ni;
    Timeout *to;
    int type;
} *my_timeouts;

/*************************************************************************/

/* Remove a collide/release timeout from our private list. */

static void rem_ns_timeout(NickInfo *ni, int type)
{
    struct my_timeout *t, *t2;

    t = my_timeouts;
    while (t) {
	if (t->ni == ni && t->type == type) {
	    t2 = t->next;
	    if (t->next)
		t->next->prev = t->prev;
	    if (t->prev)
		t->prev->next = t->next;
	    else
		my_timeouts = t->next;
	    free(t);
	    t = t2;
	} else {
	    t = t->next;
	}
    }
}

/*************************************************************************/

/* Collide a nick on timeout. */

static void timeout_collide(Timeout *t)
{
    NickInfo *ni = t->data;
    User *u;

    rem_ns_timeout(ni, TO_COLLIDE);
    /* If they identified or don't exist anymore, don't kill them. */
    if ((ni->status & NS_IDENTIFIED)
		|| !(u = finduser(ni->nick))
		|| u->my_signon > t->settime)
	return;
    /* The RELEASE timeout will always add to the beginning of the
     * list, so we won't see it.  Which is fine because it can't be
     * triggered yet anyway. */
    collide(ni, 1);
}

/*************************************************************************/

/* Release a nick on timeout. */

static void timeout_release(Timeout *t)
{
    NickInfo *ni = t->data;

    rem_ns_timeout(ni, TO_RELEASE);
    release(ni, 1);
}

/*************************************************************************/

/* Add a collide/release timeout. */

void add_ns_timeout(NickInfo *ni, int type, time_t delay)
{
    Timeout *to;
    struct my_timeout *t;
    void (*timeout_routine)(Timeout *);

    if (type == TO_COLLIDE)
	timeout_routine = timeout_collide;
    else if (type == TO_RELEASE)
	timeout_routine = timeout_release;
    else {
	log("NickServ: unknown timeout type %d!  ni=%p (%s), delay=%ld",
		type, ni, ni->nick, delay);
	return;
    }
    to = add_timeout(delay, timeout_routine, 0);
    to->data = ni;
    t = smalloc(sizeof(*t));
    t->next = my_timeouts;
    my_timeouts = t;
    t->prev = NULL;
    t->ni = ni;
    t->to = to;
    t->type = type;
}

/*************************************************************************/

/* Delete a collide/release timeout. */

static void del_ns_timeout(NickInfo *ni, int type)
{
    struct my_timeout *t, *t2;

    t = my_timeouts;
    while (t) {
	if (t->ni == ni && t->type == type) {
	    t2 = t->next;
	    if (t->next)
		t->next->prev = t->prev;
	    if (t->prev)
		t->prev->next = t->next;
	    else
		my_timeouts = t->next;
	    del_timeout(t->to);
	    free(t);
	    t = t2;
	} else {
	    t = t->next;
	}
    }
}

/*************************************************************************/
/*********************** NickServ command routines ***********************/
/*************************************************************************/

#ifdef DEBUG_COMMANDS

/* List NickServ commands */

static void do_commands(User *u)
{
    Command *c;
    char buf[50], *end;

    end = buf;
    *end = 0;
    for (c = cmds; c->name; c++) {
       if ((c->has_priv == NULL) || c->has_priv(u)) {
           if ((end-buf)+strlen(c->name)+2 >= sizeof(buf)) {
               privmsg(s_NickServ, u->nick, "%s,", buf);
               end = buf;
               *end = 0;
           }
           end += snprintf(end, sizeof(buf)-(end-buf), "%s%s",
           (end == buf) ? "" : ", ", c->name);
       }
    }
    if (buf[0])
       privmsg(s_NickServ, u->nick, "%s", buf);
}

#endif /* DEBUG_COMMANDS */

/*************************************************************************/

/* Return a help message. */

static void do_help(User *u)
{
    char *cmd = strtok(NULL, "");

    if (!cmd) {
	if (NSExpire >= 86400)
	    notice_help(s_NickServ, u, NICK_HELP, NSExpire/86400);
	else
	    notice_help(s_NickServ, u, NICK_HELP_EXPIRE_ZERO);
	if (is_services_oper(u))
	    notice_help(s_NickServ, u, NICK_SERVADMIN_HELP);
    } else if (stricmp(cmd, "SET LANGUAGE") == 0) {
	int i;
	notice_help(s_NickServ, u, NICK_HELP_SET_LANGUAGE);
	for (i = 0; i < NUM_LANGS && langlist[i] >= 0; i++) {
	    privmsg(s_NickServ, u->nick, "    %2d) %s",
			i+1, langnames[langlist[i]]);
	}
    } else {
	help_cmd(s_NickServ, u, cmds, cmd);
    }
}

/*************************************************************************/

static void do_credits(User *u)
{

    notice_lang(s_NickServ, u, SERVICES_CREDITS_TERRA);

}

/*************************************************************************/

static int is_domain_allowed(char *email)
{
    Mail *mail;
    char *p;
    
    p = strchr(email, '@');
    if (!p)
        return 0;
    
    for (mail = domainlist; mail != NULL; mail = mail->next) {
        if (mail->domain && strstr(p, mail->domain))
            return 1;
    }        
         
    return 0;
}                

static int is_domain_teleline(char *email)
{
   char *p;
   
   p = strchr(email, '@');
   if (!p)
       return 0;
       
   if (strstr(p, "teleline.es"))
       return 1;
   
   return 0;
}           
       
/*************************************************************************/

static void do_mail(User *u)
{
   notice_lang(s_NickServ, u, NICK_HELP_MAIL);
}
/*************************************************************************/

/* Register a nick. */

static void do_register(User *u)
{
    NickInfo *ni;
#ifdef REG_NICK_MAIL
    char *email = strtok(NULL, " ");
    int i, nicksmail = 0;
    char pass[16];
#else    
    char *pass = strtok(NULL, " ");
#endif

    if (readonly) {
	notice_lang(s_NickServ, u, NICK_REGISTRATION_DISABLED);
	return;
    }

/* SOLO IRCOPS REGISTO DE NICK */
/*
    if (!is_oper(u->nick)) {
        privmsg(s_NickServ, u->nick, "El servicio de Registro de Nicks "
         "est� en fase de pruebas.");
        privmsg(s_NickServ, u->nick, "Proximamente estar� disponible, "
         "ya se avisar� de ello.");
        return;
    }
*/

    /* Previene que los nicks "ircXXXXXX" que genera el ircu
     * no puedan ser registrados
     */
    if (NSForceNickChange) {
	int prefixlen = strlen(NSGuestNickPrefix);
	int nicklen = strlen(u->nick);

	/* A guest nick is defined as a nick...
	 * 	- starting with NSGuestNickPrefix
	 * 	- with a series of between, and including, 2 and 7 digits
	 * -TheShadow
	 */
	if (nicklen <= prefixlen+7 && nicklen >= prefixlen+2 &&
			stristr(u->nick, NSGuestNickPrefix) == u->nick &&
			strspn(u->nick+prefixlen, "1234567890") ==
							nicklen-prefixlen) {
	    notice_lang(s_NickServ, u, NICK_CANNOT_BE_REGISTERED, u->nick);
	    return;
	}
    }

#ifdef REG_NICK_MAIL
    if (!email || (stricmp(email, u->nick) == 0 && strtok(NULL, " "))) {
        syntax_error(s_NickServ, u, "REGISTER", NICK_REGISTER_MAIL_SYNTAX);
#else
    if (!pass || (stricmp(pass, u->nick) == 0 && strtok(NULL, " "))) {
	syntax_error(s_NickServ, u, "REGISTER", NICK_REGISTER_SYNTAX);
#endif
    } else if ((time(NULL) < u->lastnickreg + NSRegDelay) && !is_oper(u->nick)) {
	notice_lang(s_NickServ, u, NICK_REG_PLEASE_WAIT, NSRegDelay);

    } else if (u->real_ni) {	/* i.e. there's already such a nick regged */
	if (u->real_ni->status & NS_VERBOTEN) {
	    log("%s: %s@%s tried to register FORBIDden nick %s", s_NickServ,
			u->username, u->host, u->nick);
	    notice_lang(s_NickServ, u, NICK_CANNOT_BE_REGISTERED, u->nick);
	} else {
	    notice_lang(s_NickServ, u, NICK_ALREADY_REGISTERED, u->nick);
	}
#ifdef REG_NICK_MAIL
    } else if (!strchr(email,'@') ||
                strchr(email,'@') != strrchr(email,'@') ||
               !strchr(email,'.') || strchr(email,'|') ) {
        notice_lang(s_NickServ, u, NICK_MAIL_INVALID);
        syntax_error(s_NickServ, u, "REGISTER", NICK_REGISTER_MAIL_SYNTAX);

    } else if (is_domain_teleline(email)) { 
        notice_lang(s_NickServ, u, NICK_MAIL_TELELINE);

    } else if (!is_domain_allowed(email)) {
        notice_lang(s_NickServ, u, NICK_MAIL_TERRA, s_NickServ);

    } else {    
        if (!is_oper(u->nick)) {
           strlower(email);
           for (i=0; i < 256; i++)
               for (ni = nicklists[i]; ni; ni = ni->next)
                   if (ni->emailreg && !strcmp(email, ni->emailreg))
                       nicksmail++;
           if (nicksmail > NSNicksMail) {
               notice_lang(s_NickServ, u, NICK_MAIL_ABUSE, NSNicksMail);
               return;
           }
        } 
                    
/* Registro de nicks por mail
 * - zoltan
 */
        srand(time(NULL));
        sprintf(pass,"Terra%04u",1+(int)(rand()%9999));
#else
    } else if (stricmp(u->nick, pass) == 0
		|| (StrictPasswords && strlen(pass) < 5)) {
	notice_lang(s_NickServ, u, MORE_OBSCURE_PASSWORD);
    } else {
#endif    
	ni = makenick(u->nick);
	if (ni) {
#ifdef USE_ENCRYPTION
	    int len = strlen(pass);
	    if (len > PASSMAX) {
		len = PASSMAX;
		pass[len] = 0;
		notice_lang(s_NickServ, u, PASSWORD_TRUNCATED, PASSMAX);
	    }
	    if (encrypt(pass, len, ni->pass, PASSMAX) < 0) {
		memset(pass, 0, strlen(pass));
		log("%s: Failed to encrypt password for %s (register)",
			s_NickServ, u->nick);
		notice_lang(s_NickServ, u, NICK_REGISTRATION_FAILED);
		return;
	    }
	    memset(pass, 0, strlen(pass));
	    ni->status = NS_ENCRYPTEDPW | NS_IDENTIFIED | NS_RECOGNIZED;
	    
#elif defined (REG_NICK_MAIL)
            strscpy(ni->pass, pass, PASSMAX);
            ni->emailreg = sstrdup(email);
                          	    
#else
	    if (strlen(pass) > PASSMAX-1) /* -1 for null byte */
		notice_lang(s_NickServ, u, PASSWORD_TRUNCATED, PASSMAX-1);
	    strscpy(ni->pass, pass, PASSMAX);
	    ni->status = NS_IDENTIFIED | NS_RECOGNIZED;
#endif
	    ni->flags = 0;
	    if (NSDefKill)
		ni->flags |= NI_KILLPROTECT;
	    if (NSDefKillQuick)
		ni->flags |= NI_KILL_QUICK;
	    if (NSDefSecure)
		ni->flags |= NI_SECURE;
	    if (NSDefPrivate)
		ni->flags |= NI_PRIVATE;
	    if (NSDefHideEmail)
		ni->flags |= NI_HIDE_EMAIL;
	    if (NSDefHideUsermask)
		ni->flags |= NI_HIDE_MASK;
	    if (NSDefHideQuit)
		ni->flags |= NI_HIDE_QUIT;
	    if (NSDefMemoSignon)
		ni->flags |= NI_MEMO_SIGNON;
	    if (NSDefMemoReceive)
		ni->flags |= NI_MEMO_RECEIVE;
	    ni->memos.memomax = MSMaxMemos;
            ni->msg_fullmemo = NULL;
	    ni->channelcount = 0;
	    ni->channelmax = CSMaxReg;
	    ni->last_usermask = smalloc(strlen(u->username)+strlen(u->host)+2);
	    sprintf(ni->last_usermask, "%s@%s", u->username, u->host);
	    ni->last_realname = sstrdup(u->realname);
	    ni->time_registered = ni->last_seen = time(NULL);
/* A peticion de GSi, que se registraba con masks muy genericas
 * de tipo Ircap6.999@*.uc.nombres.ttd.es
 * Se borra del codigo
 *	    ni->accesscount = 1;
 *	    ni->access = smalloc(sizeof(char *));
 *	    ni->access[0] = create_mask(u);
 */
            ni->accesscount = 0;
            ni->access = NULL;
            ni->last_changed_pass = 0;
	    ni->language = DEF_LANGUAGE;
	    ni->link = NULL;
	    u->ni = u->real_ni = ni;
#ifdef REG_NICK_MAIL
            log("%s: %s registered by %s@%s Email: %s Pass: %s", s_NickServ,
                  u->nick, u->username, u->host, ni->emailreg, ni->pass);
            notice_lang(s_NickServ, u, NICK_REGISTERED_MAIL, u->nick, ni->emailreg);
                           
            {	    
            /* envio de mails */
            char *buf;
            char subject[BUFSIZE];
            if (fork()==0) {
               buf = smalloc(sizeof(char *) * 1024);
               sprintf(buf,"\n  Nick registrado: %s\n"
                           "Password del nick: %s\n\n"
                           "Para identificarte   -> /IDENTIFY %s\n"
                           "Para cambio de clave -> /msg %s SET PASSWORD nueva_contrase�a\n\n"
                           "P�gina de Informaci�n %s\n",
                  ni->nick, ni->pass, ni->pass, s_NickServ, WebNetwork);

               snprintf(subject, sizeof(subject), "Registro del Nick '%s' en Terra", ni->nick);
               
               send_mail(ni->emailreg, subject, buf);
               exit(0);
            }
            notice_lang(s_NickServ, u, NICK_IN_MAIL, ni->emailreg);                                                                                                                                                                       
     
            }
#else            
	    log("%s: `%s' registered by %s@%s", s_NickServ,
			u->nick, u->username, u->host);
	    notice_lang(s_NickServ, u, NICK_REGISTERED, u->nick, "<no definida>");
#endif  /* REG_NICK_MAIL */
	    
#if defined (USE_ENCRYPTION) && !defined (REG_NICK_MAIL)
	    notice_lang(s_NickServ, u, NICK_PASSWORD_IS, ni->pass);
#endif
	    u->lastnickreg = time(NULL);

#ifndef REG_NICK_MAIL
	    send_cmd(ServerName, "SVSMODE %s +r", u->nick);
#endif

	} else {
	    log("%s: makenick(%s) failed", s_NickServ, u->nick);
	    notice_lang(s_NickServ, u, NICK_REGISTRATION_FAILED);
	}

    }

}

/*************************************************************************/

static void do_identify(User *u)
{
    char *pass = strtok(NULL, " ");
    NickInfo *ni;
    int res;

    if (!pass) {
	syntax_error(s_NickServ, u, "IDENTIFY", NICK_IDENTIFY_SYNTAX);

    } else if (!(ni = u->real_ni)) {
	privmsg(s_NickServ, u->nick, "Tu nick no est� registrado.");
    } else if (ni->status & NS_SUSPENDED) {
        notice_lang(s_NickServ, u, NICK_SUSPENDED, ni->nick, ni->suspendreason);
    } else if (!(res = check_password(pass, ni->pass))) {
	log("%s: Failed IDENTIFY for %s!%s@%s",
		s_NickServ, u->nick, u->username, u->host);
	notice_lang(s_NickServ, u, PASSWORD_INCORRECT);
	bad_password(u);
	/* SVSNICK Terra */
//	send_cmd(NULL, "SVSNICK %s", u->nick);

    } else if (res == -1) {
	notice_lang(s_NickServ, u, NICK_IDENTIFY_FAILED);

    } else {
        char *last_mask;
        time_t last_login;
        char buf[BUFSIZE];
        struct tm *tm;
        time_t now = time(NULL);
        char **av_umode;        
                
        last_mask = sstrdup(ni->last_usermask);
        last_login = ni->last_seen;
        if (ni->status & NS_IDENTIFIED)
            notice_lang(s_NickServ, u, NICK_IS_IDENTIFIED, ni->nick);
	ni->id_timestamp = u->signon;
	if (!(ni->status & NS_RECOGNIZED)) {
	    ni->last_seen = time(NULL);
	    if (ni->last_usermask)
		free(ni->last_usermask);
	    ni->last_usermask = smalloc(strlen(u->username)+strlen(u->host)+2);
	    sprintf(ni->last_usermask, "%s@%s", u->username, u->host);
	    if (ni->last_realname)
		free(ni->last_realname);
	    ni->last_realname = sstrdup(u->realname);
	}
        if (!(ni->status & NS_IDENTIFIED)) {
//            log("%s: %s!%s@%s identified for nick %s", s_NickServ,
//                        u->nick, u->username, u->host, u->nick);
            tm = localtime(&last_login);
            strftime_lang(buf, sizeof(buf), u, STRFTIME_DATE_TIME_FORMAT, tm);                                               
            notice_lang(s_NickServ, u, NICK_IDENTIFY_LAST_LOGIN,
                     buf, last_mask);            
            notice_lang(s_NickServ, u, NICK_IDENTIFY_SUCCEEDED);
        }	
        ni->status |= NS_IDENTIFIED;
/* Doy modos de oper y admin
 * zoltan 30/11/2000
 */
        av_umode = smalloc(sizeof(char *) * 2);
        av_umode[0] = u->nick;
        if (is_services_oper(u)) {
            if (is_services_admin(u)) {
                send_cmd(ServerName, "SVSMODE %s +rha", u->nick);
                av_umode[1] = sstrdup("+rha");
            } else {
                send_cmd(ServerName, "SVSMODE %s +rh", u->nick);
                av_umode[1] = sstrdup("+rh");
            }
        } else {
            send_cmd(ServerName, "SVSMODE %s +r", u->nick);
            av_umode[1] = sstrdup("+r");
        }   
        do_umode(av_umode[0], 2, av_umode);
        free(av_umode[1]);
        free(av_umode);     

        if (!ni->last_changed_pass)
            notice_lang(s_NickServ, u, NICK_IDENTIFY_FIRST);

        if (now - ni->last_changed_pass >= NSPassChanged)
            ni->flags |= NI_CHANGE_PASS;

        if (ni->last_changed_pass && NSPassChanged && (ni->flags & NI_CHANGE_PASS))
            notice_lang(s_NickServ, u, NICK_IDENTIFY_PASSWORD_NO_CHANGED,
                                NSPassChanged/86400);
/*
        if (u->ni && !u->ni->emailreg)
            notice_help(s_NickServ, u, NICK_IDENTIFY_EMAIL_REQUIRED);
*/            
	if (!(ni->status & NS_RECOGNIZED)) {
	    check_memos(u);
            check_all_cs_memos(u);
        }
	    
#ifdef CYBER
        if (ni->flags & NI_ADMIN_CYBER)
            check_ip_iline(u);    
#endif	

    }
}

/*************************************************************************/

static void do_drop(User *u)
{
    char *nick = strtok(NULL, " ");
    char *reason = strtok(NULL, "");
    NickInfo *ni;
    User *u2;

    if (readonly && !is_services_oper(u)) {
	notice_lang(s_NickServ, u, NICK_DROP_DISABLED);
	return;
    }
    
    if (!reason) {
        syntax_error(s_NickServ, u, "DROP", NICK_DROP_SYNTAX);
        return;
    }

    if (!is_services_oper(u) && nick) {
	syntax_error(s_NickServ, u, "DROP", NICK_DROP_SYNTAX);

    } else if (!(ni = (nick ? findnick(nick) : u->real_ni))) {
	if (nick)
	    notice_lang(s_NickServ, u, NICK_X_NOT_REGISTERED, nick);
	else
	    notice_lang(s_NickServ, u, NICK_NOT_REGISTERED);

    } else if (nick && nick_is_services_admin(ni) && 
    					!is_services_root(u)) {
	notice_lang(s_NickServ, u, PERMISSION_DENIED);	
    } else if (nick && nick_is_services_oper(ni) &&
                                        !is_services_admin(u)) {
        notice_lang(s_NickServ, u, PERMISSION_DENIED);	        
    } else if (!nick && !nick_identified(u)) {
	notice_lang(s_NickServ, u, NICK_IDENTIFY_REQUIRED, s_NickServ);

    } else {
        char **av_umode;

	if (readonly)
	    notice_lang(s_NickServ, u, READ_ONLY_MODE);

        if (finduser(nick)) {
            send_cmd(ServerName, "SVSMODE %s -rah", ni->nick);
            av_umode = smalloc(sizeof(char *) * 2);
            av_umode[0] = ni->nick;
            av_umode[1] = sstrdup("-rah");
            do_umode(av_umode[0], 2, av_umode);
            free(av_umode[1]);
            free(av_umode);
        } 

	delnick(ni);
	log("%s: %s!%s@%s dropped nickname %s", s_NickServ,
		u->nick, u->username, u->host, nick ? nick : u->nick);
	canalopers(s_OperServ, "%s DROPA el nick %s", u->nick, nick ? nick : u->nick);	
	if (nick)
	    notice_lang(s_NickServ, u, NICK_X_DROPPED, nick);
	else
	    notice_lang(s_NickServ, u, NICK_DROPPED);
	if (nick && (u2 = finduser(nick)))
	    u2->ni = u2->real_ni = NULL;
	else if (!nick)
	    u->ni = u->real_ni = NULL;
        {
           /* envio de mails */
#ifdef REG_NICK_MAIL
        char *buf;
        char subject[BUFSIZE];
        if (fork()==0) {
            buf = smalloc(sizeof(char *) * 1024);
            sprintf(buf,"\n Drop del Nick %s\n"
                        "Operador:  %s\n\n"
                        "Motivo  :  %s\n",
                        nick ? nick : u->nick, u->nick, reason);
            snprintf(subject, sizeof(subject), "Drop del Nick '%s' en Terra",
                                 nick);
            send_mail(SendFrom, subject, buf);
            exit(0);

        }
#endif
       }
    }
}

/*************************************************************************/

static void do_set(User *u)
{
    char *cmd    = strtok(NULL, " ");
    char *param  = strtok(NULL, " ");
    NickInfo *ni;
    int is_servadmin = is_services_admin(u);
    int set_nick = 0;

    if (readonly) {
	notice_lang(s_NickServ, u, NICK_SET_DISABLED);
	return;
    }

    if (is_servadmin && cmd && (ni = findnick(cmd))) {
	cmd = param;
	param = strtok(NULL, " ");
	set_nick = 1;
    } else {
	ni = u->ni;
    }
    if (!param && (!cmd || (stricmp(cmd,"URL")!=0 && stricmp(cmd,"EMAIL")!=0))){
	if (is_servadmin) {
	    syntax_error(s_NickServ, u, "SET", NICK_SET_SERVADMIN_SYNTAX);
	} else {
	    syntax_error(s_NickServ, u, "SET", NICK_SET_SYNTAX);
	}
/* Jundiox, ke co�o hace aqui, xDDDDDDD */
/* Church, esto ta duplicao :P */
//	notice_lang(s_NickServ, u, MORE_INFO, s_NickServ, "SET");
    } else if (!ni) {
	notice_lang(s_NickServ, u, NICK_NOT_REGISTERED);
    } else if (ni->status & NS_VERBOTEN) {
        notice_lang(s_NickServ, u, NICK_X_FORBIDDEN, ni->nick);
    } else if (!is_servadmin && !nick_identified(u)) {
	notice_lang(s_NickServ, u, NICK_IDENTIFY_REQUIRED, s_NickServ);
    } else if (stricmp(cmd, "PASSWORD") == 0) {
	do_set_password(u, set_nick ? ni : u->real_ni, param);
    } else if (stricmp(cmd, "LANGUAGE") == 0) {
	do_set_language(u, ni, param);
    } else if (stricmp(cmd, "URL") == 0) {
	do_set_url(u, set_nick ? ni : u->real_ni, param);
    } else if (stricmp(cmd, "EMAIL") == 0) {
	do_set_email(u, set_nick ? ni : u->real_ni, param);
    } else if (stricmp(cmd, "KILL") == 0) {
	do_set_kill(u, ni, param);
    } else if (stricmp(cmd, "CHANGE") == 0) {
        do_set_kill(u, ni, param);
    } else if (stricmp(cmd, "SECURE") == 0) {
	do_set_secure(u, ni, param);
    } else if (stricmp(cmd, "PRIVATE") == 0) {
	do_set_private(u, ni, param);
    } else if (stricmp(cmd, "HIDE") == 0) {
	do_set_hide(u, ni, param);
    } else if (stricmp(cmd, "NOEXPIRE") == 0) {
	do_set_noexpire(u, ni, param);
    } else {
	if (is_servadmin)
	    notice_lang(s_NickServ, u, NICK_SET_UNKNOWN_OPTION_OR_BAD_NICK,
			strupper(cmd));
	else
	    notice_lang(s_NickServ, u, NICK_SET_UNKNOWN_OPTION, strupper(cmd));
    }
}

/*************************************************************************/

static void do_set_password(User *u, NickInfo *ni, char *param)
{
    int len = strlen(param);

    if (u->real_ni != ni && nick_is_services_admin(ni) && 
    							!is_services_root(u)) {
	notice_lang(s_NickServ, u, PERMISSION_DENIED);
	return;
    } else if (stricmp(ni->nick, param) == 0 || (StrictPasswords && len < 5)) {
	notice_lang(s_NickServ, u, MORE_OBSCURE_PASSWORD);
	return;
    }

#ifdef USE_ENCRYPTION
    if (len > PASSMAX) {
	len = PASSMAX;
	param[len] = 0;
	notice_lang(s_NickServ, u, PASSWORD_TRUNCATED, PASSMAX);
    }
    if (encrypt(param, len, ni->pass, PASSMAX) < 0) {
	memset(param, 0, strlen(param));
	log("%s: Failed to encrypt password for %s (set)",
		s_NickServ, ni->nick);
	notice_lang(s_NickServ, u, NICK_SET_PASSWORD_FAILED);
	return;
    }
    memset(param, 0, strlen(param));
    notice_lang(s_NickServ, u, NICK_SET_PASSWORD_CHANGED);
#else
    if (strlen(param) > PASSMAX-1) /* -1 for null byte */
	notice_lang(s_NickServ, u, PASSWORD_TRUNCATED, PASSMAX-1);
    strscpy(ni->pass, param, PASSMAX);
    ni->flags &= ~NI_CHANGE_PASS;
    ni->last_changed_pass = time(NULL);
    notice_lang(s_NickServ, u, NICK_SET_PASSWORD_CHANGED_TO, ni->pass);
#endif
    if (u->real_ni != ni) {
	log("%s: %s!%s@%s used SET PASSWORD as Services admin on %s",
		s_NickServ, u->nick, u->username, u->host, ni->nick);
	canalopers(s_NickServ, "%s usa SET PASSWORD como Services admin "
			"en %s", u->nick, ni->nick);
    }
}

/*************************************************************************/

static void do_set_language(User *u, NickInfo *ni, char *param)
{
    int langnum;

    if (param[strspn(param, "0123456789")] != 0) {  /* i.e. not a number */
	syntax_error(s_NickServ, u, "SET LANGUAGE", NICK_SET_LANGUAGE_SYNTAX);
	return;
    }
    langnum = atoi(param)-1;
    if (langnum < 0 || langnum >= NUM_LANGS || langlist[langnum] < 0) {
	notice_lang(s_NickServ, u, NICK_SET_LANGUAGE_UNKNOWN,
		langnum+1, s_NickServ);
	return;
    }
    ni->language = langlist[langnum];
    notice_lang(s_NickServ, u, NICK_SET_LANGUAGE_CHANGED);
}

/*************************************************************************/

static void do_set_url(User *u, NickInfo *ni, char *param)
{
    if (ni->url)
	free(ni->url);
    if (param) {
	ni->url = sstrdup(param);
	notice_lang(s_NickServ, u, NICK_SET_URL_CHANGED, param);
    } else {
	ni->url = NULL;
	notice_lang(s_NickServ, u, NICK_SET_URL_UNSET);
    }
}

/*************************************************************************/

static void do_set_email(User *u, NickInfo *ni, char *param)
{
    if (ni->email)
	free(ni->email);
    if (param) {
	ni->email = sstrdup(param);
	notice_lang(s_NickServ, u, NICK_SET_EMAIL_CHANGED, param);
    } else {
	ni->email = NULL;
	notice_lang(s_NickServ, u, NICK_SET_EMAIL_UNSET);
    }
}

/*************************************************************************/

static void do_set_kill(User *u, NickInfo *ni, char *param)
{
    if (stricmp(param, "ON") == 0) {
	ni->flags |= NI_KILLPROTECT;
	ni->flags &= ~(NI_KILL_QUICK | NI_KILL_IMMED);
        if (NSForceNickChange)
            notice_lang(s_NickServ, u, NICK_SET_CHANGE_ON);
        else
	    notice_lang(s_NickServ, u, NICK_SET_KILL_ON);
    } else if (stricmp(param, "QUICK") == 0) {
	ni->flags |= NI_KILLPROTECT | NI_KILL_QUICK;
	ni->flags &= ~NI_KILL_IMMED;
        if (NSForceNickChange)
            notice_lang(s_NickServ, u, NICK_SET_CHANGE_QUICK);
        else	
            notice_lang(s_NickServ, u, NICK_SET_KILL_QUICK);
    } else if (stricmp(param, "IMMED") == 0) {
	if (NSAllowKillImmed) {
	    ni->flags |= NI_KILLPROTECT | NI_KILL_IMMED;
	    ni->flags &= ~NI_KILL_QUICK;
            if (NSForceNickChange)
                notice_lang(s_NickServ, u, NICK_SET_CHANGE_IMMED);
            else	    
     	        notice_lang(s_NickServ, u, NICK_SET_KILL_IMMED);
	} else {
	    notice_lang(s_NickServ, u, NICK_SET_KILL_IMMED_DISABLED);
	}
    } else if (stricmp(param, "OFF") == 0) {
	ni->flags &= ~(NI_KILLPROTECT | NI_KILL_QUICK | NI_KILL_IMMED);
        if (NSForceNickChange)
            notice_lang(s_NickServ, u, NICK_SET_CHANGE_OFF);
        else
            notice_lang(s_NickServ, u, NICK_SET_KILL_OFF);
    } else {
        if (NSForceNickChange)            
	    syntax_error(s_NickServ, u, "SET CHANGE",
                NSAllowKillImmed ? NICK_SET_CHANGE_IMMED_SYNTAX
                                 : NICK_SET_CHANGE_SYNTAX);
                                                 	    
        else
            syntax_error(s_NickServ, u, "SET KILL",
		NSAllowKillImmed ? NICK_SET_KILL_IMMED_SYNTAX
		                 : NICK_SET_KILL_SYNTAX);
    }
}

/*************************************************************************/

static void do_set_secure(User *u, NickInfo *ni, char *param)
{
    if (stricmp(param, "ON") == 0) {
	ni->flags |= NI_SECURE;
	notice_lang(s_NickServ, u, NICK_SET_SECURE_ON);
    } else if (stricmp(param, "OFF") == 0) {
	ni->flags &= ~NI_SECURE;
	notice_lang(s_NickServ, u, NICK_SET_SECURE_OFF);
    } else {
	syntax_error(s_NickServ, u, "SET SECURE", NICK_SET_SECURE_SYNTAX);
    }
}

/*************************************************************************/

static void do_set_private(User *u, NickInfo *ni, char *param)
{
    if (stricmp(param, "ON") == 0) {
	ni->flags |= NI_PRIVATE;
	notice_lang(s_NickServ, u, NICK_SET_PRIVATE_ON);
    } else if (stricmp(param, "OFF") == 0) {
	ni->flags &= ~NI_PRIVATE;
	notice_lang(s_NickServ, u, NICK_SET_PRIVATE_OFF);
    } else {
	syntax_error(s_NickServ, u, "SET PRIVATE", NICK_SET_PRIVATE_SYNTAX);
    }
}

/*************************************************************************/

static void do_set_hide(User *u, NickInfo *ni, char *param)
{
    int flag, onmsg, offmsg;

    if (stricmp(param, "EMAIL") == 0) {
	flag = NI_HIDE_EMAIL;
	onmsg = NICK_SET_HIDE_EMAIL_ON;
	offmsg = NICK_SET_HIDE_EMAIL_OFF;
/* Desactivado en Terra */
/* 	
    } else if (stricmp(param, "USERMASK") == 0) {
	flag = NI_HIDE_MASK;
	onmsg = NICK_SET_HIDE_MASK_ON;
	offmsg = NICK_SET_HIDE_MASK_OFF;
*/	
    } else if (stricmp(param, "QUIT") == 0) {
	flag = NI_HIDE_QUIT;
	onmsg = NICK_SET_HIDE_QUIT_ON;
	offmsg = NICK_SET_HIDE_QUIT_OFF;
    } else {
	syntax_error(s_NickServ, u, "SET HIDE", NICK_SET_HIDE_SYNTAX);
	return;
    }
    param = strtok(NULL, " ");
    if (!param) {
	syntax_error(s_NickServ, u, "SET HIDE", NICK_SET_HIDE_SYNTAX);
    } else if (stricmp(param, "ON") == 0) {
	ni->flags |= flag;
	notice_lang(s_NickServ, u, onmsg, s_NickServ);
    } else if (stricmp(param, "OFF") == 0) {
	ni->flags &= ~flag;
	notice_lang(s_NickServ, u, offmsg, s_NickServ);
    } else {
	syntax_error(s_NickServ, u, "SET HIDE", NICK_SET_HIDE_SYNTAX);
    }
}

/*************************************************************************/

static void do_set_noexpire(User *u, NickInfo *ni, char *param)
{
    if (!is_services_admin(u)) {
	notice_lang(s_NickServ, u, PERMISSION_DENIED);
	return;
    }
    if (!param) {
	syntax_error(s_NickServ, u, "SET NOEXPIRE", NICK_SET_NOEXPIRE_SYNTAX);
	return;
    }
    if (stricmp(param, "ON") == 0) {
	ni->status |= NS_NO_EXPIRE;
	notice_lang(s_NickServ, u, NICK_SET_NOEXPIRE_ON, ni->nick);
    } else if (stricmp(param, "OFF") == 0) {
	ni->status &= ~NS_NO_EXPIRE;
	notice_lang(s_NickServ, u, NICK_SET_NOEXPIRE_OFF, ni->nick);
    } else {
	syntax_error(s_NickServ, u, "SET NOEXPIRE", NICK_SET_NOEXPIRE_SYNTAX);
    }
}

/*************************************************************************/

static void do_access(User *u)
{
    char *cmd = strtok(NULL, " ");
    char *mask = strtok(NULL, " ");
    NickInfo *ni;
    int i;
    char **access;

    if (cmd && stricmp(cmd, "LIST") == 0 && mask && is_services_admin(u)
			&& (ni = findnick(mask))) {
	ni = getlink(ni);
	notice_lang(s_NickServ, u, NICK_ACCESS_LIST_X, mask);
	mask = strtok(NULL, " ");
	for (access = ni->access, i = 0; i < ni->accesscount; access++, i++) {
	    if (mask && !match_wild(mask, *access))
		continue;
	    privmsg(s_NickServ, u->nick, "    %s", *access);
	}

    } else if (!cmd || ((stricmp(cmd,"LIST")==0) ? !!mask : !mask)) {
	syntax_error(s_NickServ, u, "ACCESS", NICK_ACCESS_SYNTAX);

    } else if (mask && !strchr(mask, '@')) {
	notice_lang(s_NickServ, u, BAD_USERHOST_MASK);
	notice_lang(s_NickServ, u, MORE_INFO, s_NickServ, "ACCESS");

    } else if (!(ni = u->ni)) {
	notice_lang(s_NickServ, u, NICK_NOT_REGISTERED);

    } else if (!nick_identified(u)) {
	notice_lang(s_NickServ, u, NICK_IDENTIFY_REQUIRED, s_NickServ);

    } else if (stricmp(cmd, "ADD") == 0) {
	if (ni->accesscount >= NSAccessMax) {
	    notice_lang(s_NickServ, u, NICK_ACCESS_REACHED_LIMIT, NSAccessMax);
	    return;
	}
	for (access = ni->access, i = 0; i < ni->accesscount; access++, i++) {
	    if (strcmp(*access, mask) == 0) {
		notice_lang(s_NickServ, u,
			NICK_ACCESS_ALREADY_PRESENT, *access);
		return;
	    }
	}
	ni->accesscount++;
	ni->access = srealloc(ni->access, sizeof(char *) * ni->accesscount);
	ni->access[ni->accesscount-1] = sstrdup(mask);
	notice_lang(s_NickServ, u, NICK_ACCESS_ADDED, mask);

    } else if (stricmp(cmd, "DEL") == 0) {
	/* First try for an exact match; then, a case-insensitive one. */
	for (access = ni->access, i = 0; i < ni->accesscount; access++, i++) {
	    if (strcmp(*access, mask) == 0)
		break;
	}
	if (i == ni->accesscount) {
	    for (access = ni->access, i = 0; i < ni->accesscount;
							access++, i++) {
		if (stricmp(*access, mask) == 0)
		    break;
	    }
	}
	if (i == ni->accesscount) {
	    notice_lang(s_NickServ, u, NICK_ACCESS_NOT_FOUND, mask);
	    return;
	}
	notice_lang(s_NickServ, u, NICK_ACCESS_DELETED, *access);
	free(*access);
	ni->accesscount--;
	if (i < ni->accesscount)	/* if it wasn't the last entry... */
	    memmove(access, access+1, (ni->accesscount-i) * sizeof(char *));
	if (ni->accesscount)		/* if there are any entries left... */
	    ni->access = srealloc(ni->access, ni->accesscount * sizeof(char *));
	else {
	    free(ni->access);
	    ni->access = NULL;
	}

    } else if (stricmp(cmd, "LIST") == 0) {
	notice_lang(s_NickServ, u, NICK_ACCESS_LIST);
	for (access = ni->access, i = 0; i < ni->accesscount; access++, i++) {
	    if (mask && !match_wild(mask, *access))
		continue;
	    privmsg(s_NickServ, u->nick, "    %s", *access);
	}

    } else {
	syntax_error(s_NickServ, u, "ACCESS", NICK_ACCESS_SYNTAX);

    }
}

/*************************************************************************/

static void do_link(User *u)
{
    char *nick = strtok(NULL, " ");
    char *pass = strtok(NULL, " ");
    NickInfo *ni = u->real_ni, *target;
    int res;

    if (NSDisableLinkCommand) {
	notice_lang(s_NickServ, u, NICK_LINK_DISABLED);
	return;
    }

    if (!pass) {
	syntax_error(s_NickServ, u, "LINK", NICK_LINK_SYNTAX);

    } else if (!ni) {
	notice_lang(s_NickServ, u, NICK_NOT_REGISTERED);

    } else if (!nick_identified(u)) {
	notice_lang(s_NickServ, u, NICK_IDENTIFY_REQUIRED, s_NickServ);

    } else if (!(target = findnick(nick))) {
	notice_lang(s_NickServ, u, NICK_X_NOT_REGISTERED, nick);

    } else if (target == ni) {
	notice_lang(s_NickServ, u, NICK_NO_LINK_SAME, nick);

    } else if (target->status & NS_VERBOTEN) {
	notice_lang(s_NickServ, u, NICK_X_FORBIDDEN, nick);

    } else if (target->status & NS_SUSPENDED) {
        notice_lang(s_NickServ, u, NICK_X_SUSPENDED, nick);
        
    } else if (!(res = check_password(pass, target->pass))) {
	log("%s: LINK: bad password for %s by %s!%s@%s",
		s_NickServ, nick, u->nick, u->username, u->host);
	notice_lang(s_NickServ, u, PASSWORD_INCORRECT);
	bad_password(u);

    } else if (res == -1) {
	notice_lang(s_NickServ, u, NICK_LINK_FAILED);

    } else {
	NickInfo *tmp;

	/* Make sure they're not trying to make a circular link */
	for (tmp = target; tmp; tmp = tmp->link) {
	    if (tmp == ni) {
		notice_lang(s_NickServ, u, NICK_LINK_CIRCULAR, nick);
		return;
	    }
	}

	/* If this nick already has a link, break it */
	if (ni->link)
	    delink(ni);

	ni->link = target;
	target->linkcount++;
	do {
	    target->channelcount += ni->channelcount;
	    if (target->link)
		target = target->link;
	} while (target->link);
	if (ni->access) {
	    int i;
	    for (i = 0; i < ni->accesscount; i++) {
		if (ni->access[i])
		    free(ni->access[i]);
	    }
	    free(ni->access);
	    ni->access = NULL;
	    ni->accesscount = 0;
	}
	if (ni->memos.memos) {
	    int i, num;
	    Memo *memo;
	    if (target->memos.memos) {
		num = 0;
		for (i = 0; i < target->memos.memocount; i++) {
		    if (target->memos.memos[i].number > num)
			num = target->memos.memos[i].number;
		}
		num++;
		target->memos.memos = srealloc(target->memos.memos,
			sizeof(Memo) * (ni->memos.memocount +
			                target->memos.memocount));
	    } else {
		num = 1;
		target->memos.memos = smalloc(sizeof(Memo)*ni->memos.memocount);
		target->memos.memocount = 0;
	    }
	    memo = target->memos.memos + target->memos.memocount;
	    for (i = 0; i < ni->memos.memocount; i++, memo++) {
		*memo = ni->memos.memos[i];
		memo->number = num++;
	    }
	    target->memos.memocount += ni->memos.memocount;
	    ni->memos.memocount = 0;
	    free(ni->memos.memos);
	    ni->memos.memos = NULL;
	    ni->memos.memocount = 0;
	}
	u->ni = target;
       log("%s: %s!%s@%s linked nick %s to %s", s_NickServ, u->nick,
                       u->username, u->host, u->nick, nick);
	notice_lang(s_NickServ, u, NICK_LINKED, nick);
	/* They gave the password, so they might as well have IDENTIFY'd */
	target->status |= NS_IDENTIFIED;
    }
}

/*************************************************************************/

static void do_unlink(User *u)
{
    NickInfo *ni;
    char *linkname;
    char *nick = strtok(NULL, " ");
    char *pass = strtok(NULL, " ");
    int res = 0;

    if (nick) {
	int is_servadmin = is_services_admin(u);
	ni = findnick(nick);
	if (!ni) {
	    notice_lang(s_NickServ, u, NICK_X_NOT_REGISTERED, nick);
	} else if (!ni->link) {
	    notice_lang(s_NickServ, u, NICK_X_NOT_LINKED, nick);
	} else if (!is_servadmin && !pass) {
	    syntax_error(s_NickServ, u, "UNLINK", NICK_UNLINK_SYNTAX);
	} else if (!is_servadmin &&
				!(res = check_password(pass, ni->pass))) {
	    log("%s: UNLINK: bad password for %s by %s!%s@%s",
		s_NickServ, nick, u->nick, u->username, u->host);
	    notice_lang(s_NickServ, u, PASSWORD_INCORRECT);
	    bad_password(u);
	} else if (res == -1) {
	    notice_lang(s_NickServ, u, NICK_UNLINK_FAILED);
	} else {
	    linkname = ni->link->nick;
	    delink(ni);
	    notice_lang(s_NickServ, u, NICK_X_UNLINKED, ni->nick, linkname);
	    /* Adjust user record if user is online */
	    /* FIXME: probably other cases we need to consider here */
	    for (u = firstuser(); u; u = nextuser()) {
		if (u->real_ni == ni) {
		    u->ni = ni;
		    break;
		}
	    }
	}
    } else {
	ni = u->real_ni;
	if (!ni)
	    notice_lang(s_NickServ, u, NICK_NOT_REGISTERED);
	else if (!nick_identified(u))
	    notice_lang(s_NickServ, u, NICK_IDENTIFY_REQUIRED, s_NickServ);
	else if (!ni->link)
	    notice_lang(s_NickServ, u, NICK_NOT_LINKED);
	else {
	    linkname = ni->link->nick;
	    u->ni = ni;  /* Effective nick now the same as real nick */
	    delink(ni);
            log("%s: %s!%s@%s unlinked nick %s from %s", s_NickServ, u->nick,
                       u->username, u->host, u->nick, linkname);
	    notice_lang(s_NickServ, u, NICK_UNLINKED, linkname);
	}
    }
}

/*************************************************************************/

static void do_listlinks(User *u)
{
    char *nick = strtok(NULL, " ");
    char *param = strtok(NULL, " ");
    NickInfo *ni, *ni2;
    int count = 0, i;

    if (!nick || (param && stricmp(param, "ALL") != 0)) {
	syntax_error(s_NickServ, u, "LISTLINKS", NICK_LISTLINKS_SYNTAX);

    } else if (!(ni = findnick(nick))) {
	notice_lang(s_NickServ, u, NICK_X_NOT_REGISTERED, nick);

    } else if (ni->status & NS_VERBOTEN) {
	notice_lang(s_NickServ, u, NICK_X_FORBIDDEN, ni->nick);

    } else {
	notice_lang(s_NickServ, u, NICK_LISTLINKS_HEADER, ni->nick);
	if (param)
	    ni = getlink(ni);
	for (i = 0; i < 256; i++) {
	    for (ni2 = nicklists[i]; ni2; ni2 = ni2->next) {
		if (ni2 == ni)
		    continue;
		if (param ? getlink(ni2) == ni : ni2->link == ni) {
                    if (ni2->link == ni)
                        notice_lang(s_NickServ, u, NICK_X_IS_LINKED, ni2->nick);
                    else
                        notice_lang(s_NickServ, u, NICK_X_IS_LINKED_VIA_X,
                                          ni2->nick, ni2->link->nick);                        
		    count++;
		}
	    }
	}
	notice_lang(s_NickServ, u, NICK_LISTLINKS_FOOTER, count);
    }
}

/*************************************************************************/

/* Show hidden info to nick owners and sadmins when the "ALL" parameter is
 * supplied. If a nick is online, the "Last seen address" changes to "Is 
 * online from".
 * Syntax: INFO <nick> {ALL}
 * -TheShadow (13 Mar 1999)
 */

static void do_info(User *u)
{
    char *nick = strtok(NULL, " ");
    char *param = strtok(NULL, " ");
    NickInfo *ni, *real;

    if (!nick) {
    	syntax_error(s_NickServ, u, "INFO", NICK_INFO_SYNTAX);

    } else if (!(ni = findnick(nick))) {
	notice_lang(s_NickServ, u, NICK_X_NOT_REGISTERED, nick);

    } else if (ni->status & NS_VERBOTEN) {
	notice_lang(s_NickServ, u, NICK_X_FORBIDDEN, nick);
        if (is_services_oper(u)) {
            notice_lang(s_NickServ, u, NICK_X_FORBIDDEN_OPER, ni->nick,
                              ni->forbidby, ni->forbidreason);
        }
    } else {
	struct tm *tm;
	char buf[BUFSIZE], *end;
	const char *commastr = getstring(u->ni, COMMA_SPACE);
	int i;
	NickInfo *ni2;
	int need_comma = 0;
	int nick_online = 0;
        int show_all = 0;

	/* Is the real owner of the nick we're looking up online? -TheShadow */
	if (ni->status & NS_IDENTIFIED)
	    nick_online = 1;

        /* Only show hidden fields to owner and sadmins and only when the ALL
	 * parameter is used. -TheShadow */
        if (param && stricmp(param, "ALL") == 0 && 
			((nick_online && (stricmp(u->nick, nick) == 0)) ||
                        	is_services_oper(u)))
            show_all = 1;

	real = getlink(ni);

	notice_lang(s_NickServ, u, NICK_INFO_REALNAME,
		nick, ni->last_realname);
        /* Info Nick suspendido
         * - zoltan
         */

        if (ni->status & NS_SUSPENDED) {
            notice_lang(s_NickServ, u, NICK_INFO_SUSPENDED, ni->suspendreason);
            if (is_services_oper(u)) {
                char timebuf[32], expirebuf[256];
                time_t now = time(NULL);
                tm = localtime(&ni->time_suspend);            
                strftime_lang(timebuf, sizeof(timebuf), u, STRFTIME_DATE_TIME_FORMAT, tm);
                if (ni->time_expiresuspend == 0) {
                    snprintf(expirebuf, sizeof(expirebuf),
                        getstring(u->ni, OPER_AKILL_NO_EXPIRE));
                } else if (ni->time_expiresuspend <= now) {
                    snprintf(expirebuf, sizeof(expirebuf),
                        getstring(u->ni, OPER_AKILL_EXPIRES_SOON));
                } else {
                    expires_in_lang(expirebuf, sizeof(expirebuf), u,
                                  ni->time_expiresuspend - now + 59);
                }                
                notice_lang(s_NickServ, u, NICK_INFO_SUSPENDED_DETAILS,
                                 ni->suspendby, timebuf, expirebuf);
            }
        }                

        if (nick_is_services_admin(ni))
            notice_lang(s_NickServ, u, NICK_INFO_SERVICES_ADMIN, ni->nick);
        else if (nick_is_services_oper(ni))
            notice_lang(s_NickServ, u, NICK_INFO_SERVICES_OPER, ni->nick);
                                                        
	if (nick_online) {
//	    if (show_all || !(real->flags & NI_HIDE_MASK))
             /* SI tiene el modo +x, no deberia salir esta info */
            if (show_all)   /* por el momento, mas adelante cambiare...
                             *  en funcion del +x de el y +X de nosotros
                             */
		notice_lang(s_NickServ, u, NICK_INFO_ADDRESS_ONLINE,		
			ni->last_usermask);
	    else
		notice_lang(s_NickServ, u, NICK_INFO_ADDRESS_ONLINE_NOHOST,
			ni->nick);

	} else {
//	    if (show_all || !(real->flags & NI_HIDE_MASK))
            if (show_all)
		notice_lang(s_NickServ, u, NICK_INFO_ADDRESS,
			ni->last_usermask);

            tm = localtime(&ni->last_seen);
            strftime_lang(buf, sizeof(buf), u, STRFTIME_DATE_TIME_FORMAT, tm);
            notice_lang(s_NickServ, u, NICK_INFO_LAST_SEEN, buf);
	}	    
	    
	tm = localtime(&ni->time_registered);
	strftime_lang(buf, sizeof(buf), u, STRFTIME_DATE_TIME_FORMAT, tm);
	notice_lang(s_NickServ, u, NICK_INFO_TIME_REGGED, buf);
        if (show_all) {
            tm = localtime(&ni->last_changed_pass);
            strftime_lang(buf, sizeof(buf), u, STRFTIME_DATE_TIME_FORMAT, tm);
            notice_lang(s_NickServ, u, NICK_INFO_LAST_PASS_CHANGED, buf);
        }
/*	if (is_services_oper(u))
	    notice_lang(s_NickServ, u, NICK_INFO_EMAIL_REGISTER, ni->emailreg);*/
	if (ni->last_quit && (show_all || !(real->flags & NI_HIDE_QUIT)))
	    notice_lang(s_NickServ, u, NICK_INFO_LAST_QUIT, ni->last_quit);
	if (ni->url)
	    notice_lang(s_NickServ, u, NICK_INFO_URL, ni->url);
	if (ni->email && (show_all || !(real->flags & NI_HIDE_EMAIL)))
	    notice_lang(s_NickServ, u, NICK_INFO_EMAIL, ni->email);
	*buf = 0;
	end = buf;
	if (real->flags & NI_KILLPROTECT) {
	    end += snprintf(end, sizeof(buf)-(end-buf), "%s",
			getstring(u->ni, NICK_INFO_OPT_KILL));
	    need_comma = 1;
	}
	if (real->flags & NI_SECURE) {
	    end += snprintf(end, sizeof(buf)-(end-buf), "%s%s",
			need_comma ? commastr : "",
			getstring(u->ni, NICK_INFO_OPT_SECURE));
	    need_comma = 1;
	}
	if (real->flags & NI_PRIVATE) {
	    end += snprintf(end, sizeof(buf)-(end-buf), "%s%s",
			need_comma ? commastr : "",
			getstring(u->ni, NICK_INFO_OPT_PRIVATE));
	    need_comma = 1;
	}
	notice_lang(s_NickServ, u, NICK_INFO_OPTIONS,
		*buf ? buf : getstring(u->ni, NICK_INFO_OPT_NONE));
 
        if (stricmp(ni->nick, real->nick) != 0)
            notice_lang(s_NickServ, u, NICK_INFO_LINKED_TO, real->nick);		

        if (ni->link && show_all)
            notice_lang(s_NickServ, u, NICK_INFO_LINKED_TO, ni->link->nick);

            
//	if ((ni->status & NS_NO_EXPIRE) && (real == u->ni || is_servoper))
        if ((ni->status & NS_NO_EXPIRE) && show_all)
	    notice_lang(s_NickServ, u, NICK_INFO_NO_EXPIRE);
       
        if (!show_all && (is_services_oper(u) || (ni == u->ni) || (ni == u->real_ni)))
            notice_lang(s_NickServ, u, NICK_INFO_FOR_MORE, s_NickServ, ni->nick);
         
//        if (param && (stricmp(param, "ALL") == 0) && ((is_services_oper(u) || (ni == u->ni)
//                    || (ni == u->real_ni))) {
        if (show_all) {
#ifdef CYBER        
            check_cyber_iline(u, ni);
#endif            
            check_cs_access(u, ni);
           /* Si hay links, mostrar la info */
            if (ni->linkcount) {
                for (i = 0; i < 256; i++)
                    for (ni2 = nicklists[i]; ni2; ni2 = ni2->next)
                        if (ni2->link == ni) {
                            notice_lang(s_NickServ, u, NICK_INFO_LINKS, ni2->nick, 
                                      ni2->email ? ni2->email : "Sin email");
                            check_cs_access(u, ni2);
                        }                    
            }                    
        }           
    }
}

/*************************************************************************/

static void do_list(User *u)
{
    char *pattern = strtok(NULL, " ");
    char *keyword;
    NickInfo *ni;
    int nnicks, i;
    char buf[BUFSIZE];
    int is_servoper = is_services_oper(u);
    int16 matchflags = 0; /* NS_ flags a nick must match one of to qualify */

    if (NSListOpersOnly && !(u->mode & UMODE_O)) {
	notice_lang(s_NickServ, u, PERMISSION_DENIED);
	return;
    }

    if (!pattern) {
	syntax_error(s_NickServ, u, "LIST",
		is_servoper ? NICK_LIST_SERVADMIN_SYNTAX : NICK_LIST_SYNTAX);
    } else {
	nnicks = 0;

	while (is_servoper && (keyword = strtok(NULL, " "))) {
	    if (stricmp(keyword, "FORBID") == 0)
		matchflags |= NS_VERBOTEN;
            if (stricmp(keyword, "SUSPEND") == 0)
                matchflags |= NS_SUSPENDED;		
	    if (stricmp(keyword, "NOEXPIRE") == 0)
		matchflags |= NS_NO_EXPIRE;
	}

	notice_lang(s_NickServ, u, NICK_LIST_HEADER, pattern);
	for (i = 0; i < 256; i++) {
	    for (ni = nicklists[i]; ni; ni = ni->next) {
		if (!is_servoper && ((ni->flags & NI_PRIVATE)
						|| (ni->status & NS_VERBOTEN)))
		    continue;
		if ((matchflags != 0) && !(ni->status & matchflags))
		    continue;

		/* We no longer compare the pattern against the output buffer.
		 * Instead we build a nice nick!user@host buffer to compare.
		 * The output is then generated separately. -TheShadow */
		snprintf(buf, sizeof(buf), "%s!%s", ni->nick,
				ni->last_usermask ? ni->last_usermask : "*@*");
		if (stricmp(pattern, ni->nick) == 0 ||
					match_wild_nocase(pattern, buf)) {
		    if (++nnicks <= NSListMax) {
			char noexpire_char = ' ';
                        char suspend_char = ' ';
                        if (is_servoper) {
                           if (ni->status & NS_NO_EXPIRE)
                               noexpire_char = '!';
                            if (ni->status & NS_SUSPENDED)
                                suspend_char = '*';
                        }
//                     if (!is_servoper && (ni->flags & NI_HIDE_MASK)) {
                        if (!is_servoper) {
                            snprintf(buf, sizeof(buf), "%-20s  [Oculto]",
						ni->nick);
			} else if (ni->status & NS_VERBOTEN) {
			    snprintf(buf, sizeof(buf), "%-20s  [Prohibido]",
						ni->nick);
                        } else if (ni->status & NS_SUSPENDED) {
                            snprintf(buf, sizeof(buf), "%-20s  [Suspendido]",
                                                ni->nick);						
			} else {
			    snprintf(buf, sizeof(buf), "%-20s  %s",
						ni->nick, ni->last_usermask);
			}
			privmsg(s_NickServ, u->nick, "   %c%c%s",
                                       suspend_char, noexpire_char, buf);
		    }
		}
	    }
	}
	notice_lang(s_NickServ, u, NICK_LIST_RESULTS,
			nnicks>NSListMax ? NSListMax : nnicks, nnicks);
    }
}

/*************************************************************************/

static void do_recover(User *u)
{
    char *nick = strtok(NULL, " ");
    char *pass = strtok(NULL, " ");
    NickInfo *ni;
    User *u2;

    if (!nick) {
	syntax_error(s_NickServ, u, "RECOVER", NICK_RECOVER_SYNTAX);
    } else if (!(u2 = finduser(nick))) {
	notice_lang(s_NickServ, u, NICK_X_NOT_IN_USE, nick);
    } else if (!(ni = u2->real_ni)) {
	notice_lang(s_NickServ, u, NICK_X_NOT_REGISTERED, nick);
    } else if (ni->status & NS_VERBOTEN) {
        notice_lang(s_NickServ, u, NICK_X_FORBIDDEN, ni->nick);
    } else if (ni->status & NS_SUSPENDED) {
        notice_lang(s_NickServ, u, NICK_X_SUSPENDED, ni->nick);	
    } else if (stricmp(nick, u->nick) == 0) {
	notice_lang(s_NickServ, u, NICK_NO_RECOVER_SELF);
    } else if (pass) {
	int res = check_password(pass, ni->pass);
	if (res == 1) {
	    collide(ni, 0);
	    if (NSForceNickChange)
           	notice_lang(s_NickServ, u, NICK_REVOVERED_CHANGE, s_NickServ, nick);
            else
                notice_lang(s_NickServ, u, NICK_RECOVERED, s_NickServ, nick);                	
	} else {
	    notice_lang(s_NickServ, u, ACCESS_DENIED);
	    if (res == 0) {
		log("%s: RECOVER: invalid password for %s by %s!%s@%s",
			s_NickServ, nick, u->nick, u->username, u->host);
		bad_password(u);
	    }
	}
    } else {
	if (!(ni->flags & NI_SECURE) && is_on_access(u, ni)) {
	    collide(ni, 0);
	    if (NSForceNickChange)
                notice_lang(s_NickServ, u, NICK_REVOVERED_CHANGE, s_NickServ, nick);
            else    
                notice_lang(s_NickServ, u, NICK_RECOVERED, s_NickServ, nick);
	} else {
	    notice_lang(s_NickServ, u, ACCESS_DENIED);
	}
    }
}

/*************************************************************************/

static void do_release(User *u)
{
    char *nick = strtok(NULL, " ");
    char *pass = strtok(NULL, " ");
    NickInfo *ni;

    if (!nick) {
	syntax_error(s_NickServ, u, "RELEASE", NICK_RELEASE_SYNTAX);
    } else if (!(ni = findnick(nick))) {
	notice_lang(s_NickServ, u, NICK_X_NOT_REGISTERED, nick);
    } else if (ni->status & NS_VERBOTEN) {
        notice_lang(s_NickServ, u, NICK_X_FORBIDDEN, ni->nick);
    } else if (ni->status & NS_SUSPENDED) {
        notice_lang(s_NickServ, u, NICK_X_SUSPENDED, ni->nick);	
    } else if (!(ni->status & NS_KILL_HELD)) {
	notice_lang(s_NickServ, u, NICK_RELEASE_NOT_HELD, nick);
    } else if (pass) {
	int res = check_password(pass, ni->pass);
	if (res == 1) {
	    release(ni, 0);
	    notice_lang(s_NickServ, u, NICK_RELEASED);
	} else {
	    notice_lang(s_NickServ, u, ACCESS_DENIED);
	    if (res == 0) {
		log("%s: RELEASE: invalid password for %s by %s!%s@%s",
			s_NickServ, nick, u->nick, u->username, u->host);
		bad_password(u);
	    }
	}
    } else {
	if (!(ni->flags & NI_SECURE) && is_on_access(u, ni)) {
	    release(ni, 0);
	    notice_lang(s_NickServ, u, NICK_RELEASED);
	} else {
	    notice_lang(s_NickServ, u, ACCESS_DENIED);
	}
    }
}

/*************************************************************************/

static void do_ghost(User *u)
{
    char *nick = strtok(NULL, " ");
    char *pass = strtok(NULL, " ");
    NickInfo *ni;
    User *u2;

    if (!nick) {
	syntax_error(s_NickServ, u, "GHOST", NICK_GHOST_SYNTAX);
    } else if (!(u2 = finduser(nick))) {
	notice_lang(s_NickServ, u, NICK_X_NOT_IN_USE, nick);
    } else if (!(ni = u2->real_ni)) {
	notice_lang(s_NickServ, u, NICK_X_NOT_REGISTERED, nick);
    } else if (ni->status & NS_VERBOTEN) {
        notice_lang(s_NickServ, u, NICK_X_FORBIDDEN, ni->nick);
    } else if (ni->status & NS_SUSPENDED) {
        notice_lang(s_NickServ, u, NICK_X_SUSPENDED, ni->nick);
    } else if (stricmp(nick, u->nick) == 0) {
	notice_lang(s_NickServ, u, NICK_NO_GHOST_SELF);
    } else if (pass) {
	int res = check_password(pass, ni->pass);
	if (res == 1) {
	    char buf[NICKMAX+32];
	    snprintf(buf, sizeof(buf), "Comando GHOST usado por %s", u->nick);
	    kill_user(s_NickServ, nick, buf);
	    notice_lang(s_NickServ, u, NICK_GHOST_KILLED, nick);
	} else {
	    notice_lang(s_NickServ, u, ACCESS_DENIED);
	    if (res == 0) {
		log("%s: RELEASE: invalid password for %s by %s!%s@%s",
			s_NickServ, nick, u->nick, u->username, u->host);
		bad_password(u);
	    }
	}
    } else {
	if (!(ni->flags & NI_SECURE) && is_on_access(u, ni)) {
	    char buf[NICKMAX+32];
	    snprintf(buf, sizeof(buf), "Comando GHOST usado por %s", u->nick);
	    kill_user(s_NickServ, nick, buf);
	    notice_lang(s_NickServ, u, NICK_GHOST_KILLED, nick);
	} else {
	    notice_lang(s_NickServ, u, ACCESS_DENIED);
	}
    }
}

/*************************************************************************/

static void do_status(User *u)
{
    char *nick;
    User *u2;
    int i = 0;

    while ((nick = strtok(NULL, " ")) && (i++ < 16)) {
	if (!(u2 = finduser(nick)))
            notice_lang(s_NickServ, u, NICK_STATUS_OFFLINE, nick);
        else if (!(findnick(nick)))
            notice_lang(s_NickServ, u, NICK_STATUS_NOT_REGISTRED, nick);
        else if (nick_suspendied(u2))
            notice_lang(s_NickServ, u, NICK_STATUS_SUSPENDED, nick);
        else if (nick_identified(u2))
            notice_lang(s_NickServ, u, NICK_STATUS_IDENTIFIED, nick);
        else if (nick_recognized(u2))
            notice_lang(s_NickServ, u, NICK_STATUS_RECOGNIZED, nick);
        else
            notice_lang(s_NickServ, u, NICK_STATUS_NOT_IDENTIFIED, nick);
    }
}

/*************************************************************************/
/* Lista los opers/ircops/admins on-line */

static void do_opers(User *u)
{
    int i;
    int online = 0;
    User *u2;
    
    for (i = 0; i < 1024; i++) {
        for (u2 = userlist[i]; u2; u2 = u2->next) {
            if (u2->ni && (u2->ni->status & NS_IDENTIFIED) && !(u2->mode & AWAY)) {     
                if (is_services_admin(u2)) {
                    privmsg(s_NickServ, u->nick, "%-10s es un 12Administrador de la red", u2->nick);
                    online++;
                    break;
                }
                if (is_services_oper(u2)) {
                    privmsg(s_NickServ, u->nick, "%-10s es un 12Operador de la red", u2->nick);
                    online++;
                    break;
                }                
                if (u2->mode & UMODE_O) {
                    privmsg(s_NickServ, u->nick, "%-10s es un 12IRCop de la red", u2->nick);
                    online++;
                }   
            }                    
        }
    }        
    privmsg(s_NickServ, u->nick, "12%d IRCops, OPERS y ADMINS on-line", online);                

}

/*************************************************************************/

/* Lista los nicks asociados a un nick */

static void do_listemails(User *u)
{

    char *email = strtok(NULL, " ");
    NickInfo *ni;
    int nicksmail = 0, total = 0, i;

    if (!email){
        syntax_error(s_NickServ, u, "LISTEMAILS", NICK_LISTEMAILS_SYNTAX);
    } else if (!strchr(email,'@') ||
                strchr(email,'@') != strrchr(email,'@') ||
               !strchr(email,'.') || strchr(email,'|') ) {
        notice_lang(s_NickServ, u, NICK_LISTEMAILS_INVALID);
    } else if (is_domain_teleline(email)) {
        notice_lang(s_NickServ, u, NICK_LISTEMAILS_TELELINE);

    } else if (!is_domain_allowed(email)) {
        notice_lang(s_NickServ, u, NICK_LISTEMAILS_TERRA);
    } else {
        notice_lang(s_NickServ, u, NICK_LISTEMAILS_HEADER, email);
        strlower(email);
        for (i=0; i < 256; i++) {
            for (ni = nicklists[i]; ni; ni = ni->next) {
                total++;
                if (ni->emailreg && !strcmp(email, ni->emailreg)) {
                    privmsg(s_NickServ, u->nick, "  %s", ni->nick);
                    nicksmail++;
                }
            }
        }
        notice_lang(s_NickServ, u, NICK_LISTEMAILS_RESULTS, nicksmail, total);
    }
}

/*************************************************************************/

#ifdef REG_NICK_MAIL
static void do_sendpass(User *u)
{
    char *nick = strtok(NULL, " ");
    NickInfo *ni;
        
    if (!nick){
        syntax_error(s_NickServ, u, "SENDPASS", NICK_SENDPASS_SYNTAX);
    } else if (!(ni = findnick(nick))) {
        notice_lang(s_NickServ, u, NICK_X_NOT_REGISTERED, nick);
    } else if (ni->status & NS_VERBOTEN) {
        notice_lang(s_NickServ, u, NICK_X_FORBIDDEN, ni->nick);
    } else {
        notice_lang(s_NickServ, u, NICK_SENDPASS_MAIL, nick, ni->emailreg);
        {        
        /* Funcion envio de mails */                                                                                         
#endif
#ifdef REG_NICK_MAIL
         char *buf;
         char subject[BUFSIZE];
                 
         if (fork()==0) {
         
             buf = smalloc(sizeof(char *) * 1024);
             sprintf(buf,"\nNick registrado: %s\n"
                         "Password del nick: %s\n\n"
                         "Para identificarte   -> /IDENTIFY %s\n"
                         "Para cambio de clave -> /msg %s SET PASSWORD nueva_contrase�a\n\n"
                         "P�gina de Informaci�n %s\n",
                               ni->nick, ni->pass, ni->pass, s_NickServ, WebNetwork);
                                                                        
             snprintf(subject, sizeof(subject), "Contrase�a solicitada del Nick '%s' en Terra", ni->nick);

             send_mail(ni->emailreg, subject, buf);
             exit(0);
         }                                                                                                                                                                      
#endif
#ifdef REG_NICK_MAIL
         notice_lang(s_NickServ, u, NICK_SENDPASS_SUCCEEDED, nick, ni->emailreg);                                                
        }            
        canalopers(s_NickServ, "%s ha usado SENDPASS sobre %s", u->nick, nick);        
    }
}            
#endif

/*************************************************************************/
static void do_getpass(User *u)
{
#ifndef USE_ENCRYPTION
    char *nick = strtok(NULL, " ");
    NickInfo *ni;
#endif

    /* Assumes that permission checking has already been done. */
#ifdef USE_ENCRYPTION
    notice_lang(s_NickServ, u, NICK_GETPASS_UNAVAILABLE);
#else
    if (!nick) {
	syntax_error(s_NickServ, u, "GETPASS", NICK_GETPASS_SYNTAX);
    } else if (!(ni = findnick(nick))) {
	notice_lang(s_NickServ, u, NICK_X_NOT_REGISTERED, nick);
    } else if (ni->status & NS_VERBOTEN) {
        notice_lang(s_NickServ, u, NICK_X_FORBIDDEN, ni->nick);	
    } else if (nick_is_services_admin(ni) && 
					!is_services_root(u)) {
	notice_lang(s_NickServ, u, PERMISSION_DENIED);
    } else if (nick && nick_is_services_oper(ni) &&
                                        !is_services_admin(u)) {
       notice_lang(s_NickServ, u, PERMISSION_DENIED);                                                   	
    } else {
	log("%s: %s!%s@%s used GETPASS on %s",
		s_NickServ, u->nick, u->username, u->host, nick);
        canalopers(s_NickServ, "%s ha usado GETPASS sobre %s", u->nick, nick);
	notice_lang(s_NickServ, u, NICK_GETPASS_PASSWORD_IS, nick, ni->pass);
    }
#endif
}

/*************************************************************************/

static void do_suspend(User *u)
{
    NickInfo *ni;
    char *nick, *expiry, *reason;
    time_t expires;
    User *u2;

    nick = strtok(NULL, " ");
    if (nick && *nick == '+') {
        expiry = nick;
        nick = strtok(NULL, " ");
    } else {
        expiry = NULL;
    }    

    reason = strtok(NULL, "");
    
    if (!reason) {
        syntax_error(s_NickServ, u, "SUSPEND", NICK_SUSPEND_SYNTAX);
        return;
    }    

    if (readonly)
        notice_lang(s_NickServ, u, READ_ONLY_MODE);
            
    if (!(ni = findnick(nick))) {
        notice_lang(s_NickServ, u, NICK_X_NOT_REGISTERED, nick);
    } else if (ni->status & NS_VERBOTEN) {
        notice_lang(s_NickServ, u, NICK_SUSPEND_FORBIDDEN, nick);
    } else if (ni->status & NS_SUSPENDED) {
        notice_lang(s_NickServ, u, NICK_SUSPEND_SUSPENDED, nick);    
    } else if (nick && nick_is_services_admin(ni) &&
                                       !is_services_root(u)) {
        notice_lang(s_NickServ, u, PERMISSION_DENIED);
    } else if (nick && nick_is_services_oper(ni) &&
                                       !is_services_admin(u)) {
        notice_lang(s_NickServ, u, PERMISSION_DENIED);
    } else {        
        char **av_umode;

        if (expiry) {
            expires = dotime(expiry);
            if (expires < 0) {
                notice_lang(s_NickServ, u, BAD_EXPIRY_TIME);
                return;
            } else if (expires > 0) {
                expires += time(NULL);
            }    
        } else {
            expires = time(NULL) + NSSuspendExpire;
        }            
        u2 = finduser(nick);
        log("%s: %s!%s@%s SUSPENDi� el nick %s, Motivo: %s",
                  s_NickServ, u->nick, u->username, u->host, nick, reason);
        ni->suspendby = sstrdup(u->nick);
        ni->suspendreason = sstrdup(reason);
        ni->time_suspend = time(NULL);        
        ni->time_expiresuspend = expires;
        ni->status |= NS_SUSPENDED;
        ni->status &= ~NS_IDENTIFIED;
        notice_lang(s_NickServ, u, NICK_SUSPEND_SUCCEEDED, nick);
        canalopers(s_NickServ, "%s ha SUSPENDido el nick %s, motivo: %s",
                                              u->nick, nick, reason);        
        if (u2) {
            notice_lang(s_NickServ, u2, NICK_SUSPENDED, nick, reason);
            send_cmd(ServerName, "SVSMODE %s -rah", u2->nick);
            av_umode = smalloc(sizeof(char *) * 2);
            av_umode[0] = u2->nick;
            av_umode[1] = sstrdup("-rah");
            do_umode(av_umode[0], 2, av_umode);
            free(av_umode[1]);
            free(av_umode);
        }
    }
}   

/*************************************************************************/

static void do_unsuspend(User *u)
{
     NickInfo *ni;
     char *nick = strtok(NULL, " ");
          
     if (!nick) {
         syntax_error(s_NickServ, u, "UNSUSPEND", NICK_UNSUSPEND_SYNTAX);
         return;
     }
                                  
     if (readonly)
         notice_lang(s_NickServ, u, READ_ONLY_MODE);
     if (!(ni = findnick(nick))) {
         notice_lang(s_NickServ, u, NICK_X_NOT_REGISTERED, nick);                                           
     } else if (!(ni->status & NS_SUSPENDED)) {
         notice_lang(s_NickServ, u, NICK_SUSPEND_NOT_SUSPEND, nick);
     } else if ((nick_is_services_admin(findnick(ni->suspendby)))
                        && !is_services_admin(u)) {
         notice_lang(s_NickServ, u, NICK_UNSUSPEND_SUSPEND_ADMIN, nick);
         log("%s: %s!%s@%s intenta UNSUSPENDER el nick %s, suspendido por un admin",
                     s_NickServ, u->nick, u->username, u->host, nick);
         canaladmins(s_NickServ, "%s intenta UNSUSPENDER el nick %s, suspendidido"
                " por un admin", u->nick, nick);
     } else {
         User *u2 = finduser(nick);         
         log("%s: %s!%s@%s ha usado UNSUSPEND on %s",
                     s_NickServ, u->nick, u->username, u->host, nick);
         free(ni->suspendby);
         free(ni->suspendreason);
         ni->time_suspend = 0;
         ni->time_expiresuspend = 0;         
         ni->status &= ~NS_SUSPENDED;
         notice_lang(s_NickServ, u, NICK_UNSUSPEND_SUCCEEDED, nick);
         canalopers(s_NickServ, "%s ha reactivado el nick %s", u->nick, nick);

        if (u2)
            notice_lang(s_NickServ, u2, NICK_REACTIVED, nick);
     }
}    
                       
/*************************************************************************/

static void do_forbid(User *u)
{
    NickInfo *ni;
    char *nick = strtok(NULL, " ");
    char *reason = strtok(NULL, "");

    /* Assumes that permission checking has already been done. */
    if (!reason) {
	syntax_error(s_NickServ, u, "FORBID", NICK_FORBID_SYNTAX);
	return;
    }
    
    if (nick_is_services_oper(findnick(nick))) {
        notice_lang(s_NickServ, u, PERMISSION_DENIED);
        canalopers(s_NickServ, "%s ha intentado FORBIDear el nick %s", u->nick, nick);
        return;
    }    
    if (readonly)
	notice_lang(s_NickServ, u, READ_ONLY_MODE);
    if ((ni = findnick(nick)) != NULL)
	delnick(ni);
    ni = makenick(nick);
    if (ni) {
	ni->status |= NS_VERBOTEN;
        ni->forbidby = sstrdup(u->nick);
        ni->forbidreason = sstrdup(reason);	
	log("%s: %s set FORBID for nick %s (%s)", s_NickServ, u->nick, nick, reason);
	notice_lang(s_NickServ, u, NICK_FORBID_SUCCEEDED, nick);
	canalopers(s_NickServ, "%s ha FORBIDeado el nick %s (%s)", u->nick, nick, reason);
    } else {
	log("%s: Valid FORBID for %s by %s failed", s_NickServ,
		nick, u->nick);
	notice_lang(s_NickServ, u, NICK_FORBID_FAILED, nick);
    }
}

/*************************************************************************/

static void do_unforbid(User *u)
{
    NickInfo *ni;
    char *nick = strtok(NULL, " ");
    
    /* Assumes that permission checking has already been done. */
    if (!nick) {
        syntax_error(s_NickServ, u, "UNFORBID", NICK_FORBID_SYNTAX);
        return;
    }    
    if (readonly)
        notice_lang(s_NickServ, u, READ_ONLY_MODE);
    if ((ni = findnick(nick)) != NULL && (ni->status & NS_VERBOTEN)) {
        delnick(ni);    
        log("%s: %s!%s@%s used UNFORBID on %s",
                     s_NickServ, u->nick, u->username, u->host, nick);
        notice_lang(s_NickServ, u, NICK_UNFORBID_SUCCEEDED, nick);
        canalopers(s_NickServ, "%s ha UNFORBIDeado el nick %s", u->nick, nick);
    } else {
        log("%s: Valid UNFORBID for %s by %s failed", s_NickServ, nick,
                                 u->nick);
        notice_lang(s_NickServ, u, NICK_UNFORBID_NOT_FORBID, nick);
    }        
}                                            
        
/*************************************************************************/

/* Register a nick. */

static void do_reguser(User *u)
{
    char *nick = strtok(NULL, " ");
    char *pass = strtok(NULL, " ");
    char *email = strtok(NULL, " ");
    NickInfo *ni;

    if (readonly) {
	notice_lang(s_NickServ, u, NICK_REGISTRATION_DISABLED);
	return;
    }

   if (!pass || !email || !nick) {
        syntax_error(s_NickServ, u, "REGUSER", NICK_REGUSER_SYNTAX);
	return;
   }
   if (!is_oper(u->nick)) {
       privmsg(s_NickServ, u->nick, "El servicio de Registro de Nicks "
        "est� en fase de pruebas.");
       privmsg(s_NickServ, u->nick, "Proximamente estar� disponible, "
        "ya se avisar� de ello.");
       return;
   }

    /* Previene que los nicks "ircXXXXXX" que genera el ircu
     * no puedan ser registrados
     */
    if (NSForceNickChange) {
	int prefixlen = strlen(NSGuestNickPrefix);
	int nicklen = strlen(nick);

	/* A guest nick is defined as a nick...
	 * 	- starting with NSGuestNickPrefix
	 * 	- with a series of between, and including, 2 and 7 digits
	 * -TheShadow
	 */
	if (nicklen <= prefixlen+7 && nicklen >= prefixlen+2 &&
			stristr(nick, NSGuestNickPrefix) == nick &&
			strspn(nick+prefixlen, "1234567890") ==
							nicklen-prefixlen) {
	    notice_lang(s_NickServ, u, NICK_CANNOT_BE_REGISTERED, nick);
	    return;
	}
    }

    if (!pass || !email || (stricmp(pass, nick) == 0 && strtok(NULL, " "))) {
	syntax_error(s_NickServ, u, "REGUSER", NICK_REGUSER_SYNTAX);
    } else if ((ni = findnick(nick))) {	/* i.e. there's already such a nick regged */
	if (ni->status & NS_VERBOTEN) {
	    log("%s: %s@%s tried to register FORBIDden nick %s", s_NickServ,
			u->username, u->host, nick);
	    notice_lang(s_NickServ, u, NICK_CANNOT_BE_REGISTERED, nick);
	} else {
	    notice_lang(s_NickServ, u, NICK_ALREADY_REGISTERED, nick);
	}
    } else if (stricmp(nick, pass) == 0
		|| (StrictPasswords && strlen(pass) < 5)) {
	notice_lang(s_NickServ, u, MORE_OBSCURE_PASSWORD);
    } else {
	ni = makenick(nick);
	if (ni) {
#ifdef USE_ENCRYPTION
	    int len = strlen(pass);
	    if (len > PASSMAX) {
		len = PASSMAX;
		pass[len] = 0;
		notice_lang(s_NickServ, u, PASSWORD_TRUNCATED, PASSMAX);
	    }
	    if (encrypt(pass, len, ni->pass, PASSMAX) < 0) {
		memset(pass, 0, strlen(pass));
		log("%s: Failed to encrypt password for %s (register)",
			s_NickServ, nick);
		notice_lang(s_NickServ, u, NICK_REGISTRATION_FAILED);
		return;
	    }
	    memset(pass, 0, strlen(pass));
	    ni->status = NS_ENCRYPTEDPW | NS_IDENTIFIED | NS_RECOGNIZED;
#else	    
	    if (strlen(pass) > PASSMAX-1) /* -1 for null byte */
		notice_lang(s_NickServ, u, PASSWORD_TRUNCATED, PASSMAX-1);
	    strscpy(ni->pass, pass, PASSMAX);
#endif
	    ni->status = NS_IDENTIFIED | NS_RECOGNIZED;
	    ni->flags = 0;
	    if (NSDefKill)
		ni->flags |= NI_KILLPROTECT;
	    if (NSDefKillQuick)
		ni->flags |= NI_KILL_QUICK;
	    if (NSDefSecure)
		ni->flags |= NI_SECURE;
	    if (NSDefPrivate)
		ni->flags |= NI_PRIVATE;
	    if (NSDefHideEmail)
		ni->flags |= NI_HIDE_EMAIL;
	    if (NSDefHideUsermask)
		ni->flags |= NI_HIDE_MASK;
	    if (NSDefHideQuit)
		ni->flags |= NI_HIDE_QUIT;
	    if (NSDefMemoSignon)
		ni->flags |= NI_MEMO_SIGNON;
	    if (NSDefMemoReceive)
		ni->flags |= NI_MEMO_RECEIVE;
	    ni->memos.memomax = MSMaxMemos;
            ni->msg_fullmemo = NULL;
	    ni->channelcount = 0;
	    ni->channelmax = CSMaxReg;
	    ni->last_usermask = smalloc(strlen(u->username)+strlen(u->host)+2);
	    sprintf(ni->last_usermask, "%s@%s", u->username, u->host);
	    ni->last_realname = sstrdup(u->realname);
	    ni->time_registered = ni->last_seen = time(NULL);
/* A peticion de GSi, que se registraba con masks muy genericas
 * de tipo Ircap6.999@*.uc.nombres.ttd.es
 * Se borra del codigo
 *	    ni->accesscount = 1;
 *	    ni->access = smalloc(sizeof(char *));
 *	    ni->access[0] = create_mask(u);
 */
            ni->accesscount = 0;
            ni->access = NULL;
            ni->last_changed_pass = 0;
	    ni->language = DEF_LANGUAGE;
	    ni->link = NULL;
            ni->email = email;
	    u->ni = u->real_ni = ni;
	    log("%s: `%s' registered by %s!%s@%s", s_NickServ,
			nick, u->nick, u->username, u->host);
	    notice_lang(s_NickServ, u, NICK_REGISTERED, nick, "<no definida>");
	    
#if defined (USE_ENCRYPTION) && !defined (REG_NICK_MAIL)
	    notice_lang(s_NickServ, u, NICK_PASSWORD_IS, ni->pass);
#endif
	    u->lastnickreg = time(NULL);

	} else {
	    log("%s: makenick(%s) failed", s_NickServ, u->nick);
	    notice_lang(s_NickServ, u, NICK_REGISTRATION_FAILED);
	}

    }

}

/**************************************************************/

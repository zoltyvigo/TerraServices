/* NickServ functions.
 *
 * Services is copyright (c) 1996-1999 Andy Church.
 *     E-mail: <achurch@dragonfire.net>
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

static void do_help(User *u);
static void do_register(User *u);
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
static void do_getpass(User *u);
static void do_forbid(User *u);

/*************************************************************************/

static Command cmds[] = {
    { "HELP",     do_help,     NULL,  -1,                     -1,-1,-1,-1 },
    { "REGISTER", do_register, NULL,  NICK_HELP_REGISTER,     -1,-1,-1,-1 },
    { "IDENTIFY", do_identify, NULL,  NICK_HELP_IDENTIFY,     -1,-1,-1,-1 },
    { "DROP",     do_drop,     NULL,  -1,
		NICK_HELP_DROP, NICK_SERVADMIN_HELP_DROP,
		NICK_SERVADMIN_HELP_DROP, NICK_SERVADMIN_HELP_DROP },
    { "ACCESS",   do_access,   NULL,  NICK_HELP_ACCESS,       -1,-1,-1,-1 },
    { "LINK",     do_link,     NULL,  NICK_HELP_LINK,         -1,-1,-1,-1 },
    { "UNLINK",   do_unlink,   NULL,  NICK_HELP_UNLINK,       -1,-1,-1,-1 },
    { "SET",      do_set,      NULL,  NICK_HELP_SET,
		-1, NICK_SERVADMIN_HELP_SET,
		NICK_SERVADMIN_HELP_SET, NICK_SERVADMIN_HELP_SET },
    { "SET PASSWORD", NULL,    NULL,  NICK_HELP_SET_PASSWORD, -1,-1,-1,-1 },
    { "SET URL",      NULL,    NULL,  NICK_HELP_SET_URL,      -1,-1,-1,-1 },
    { "SET EMAIL",    NULL,    NULL,  NICK_HELP_SET_EMAIL,    -1,-1,-1,-1 },
    { "SET KILL",     NULL,    NULL,  NICK_HELP_SET_KILL,     -1,-1,-1,-1 },
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
    { "LIST",     do_list,     NULL,  -1,
		NICK_HELP_LIST, NICK_SERVADMIN_HELP_LIST,
		NICK_SERVADMIN_HELP_LIST, NICK_SERVADMIN_HELP_LIST },
    { "STATUS",   do_status,   NULL,  NICK_HELP_STATUS,       -1,-1,-1,-1 },
    { "LISTLINKS",do_listlinks,is_services_admin, -1,
		-1, NICK_SERVADMIN_HELP_LISTLINKS,
		NICK_SERVADMIN_HELP_LISTLINKS, NICK_SERVADMIN_HELP_LISTLINKS },
    { "GETPASS",  do_getpass,  is_services_admin,  -1,
		-1, NICK_SERVADMIN_HELP_GETPASS,
		NICK_SERVADMIN_HELP_GETPASS, NICK_SERVADMIN_HELP_GETPASS },
    { "FORBID",   do_forbid,   is_services_admin,  -1,
		-1, NICK_SERVADMIN_HELP_FORBID,
		NICK_SERVADMIN_HELP_FORBID, NICK_SERVADMIN_HELP_FORBID },
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

void get_nickserv_stats(long *nrec, long *memuse)
{
    long count = 0, mem = 0;
    int i, j;
    NickInfo *ni;
    char **accptr;

    for (i = 0; i < 256; i++) {
	for (ni = nicklists[i]; ni; ni = ni->next) {
	    count++;
	    mem += sizeof(*ni);
	    if (ni->url)
		mem += strlen(ni->url)+1;
	    if (ni->email)
		mem += strlen(ni->email)+1;
	    if (ni->last_usermask)
		mem += strlen(ni->last_usermask)+1;
	    if (ni->last_realname)
		mem += strlen(ni->last_realname)+1;
	    if (ni->last_quit)
		mem += strlen(ni->last_quit)+1;
	    mem += sizeof(char *) * ni->accesscount;
	    for (accptr=ni->access, j=0; j < ni->accesscount; accptr++, j++) {
		if (*accptr)
		    mem += strlen(*accptr)+1;
	    }
	    mem += ni->memos.memocount * sizeof(Memo);
	    for (j = 0; j < ni->memos.memocount; j++) {
		if (ni->memos.memos[j].text)
		    mem += strlen(ni->memos.memos[j].text)+1;
	    }
	}
    }
    *nrec = count;
    *memuse = mem;
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
	notice(s_NickServ, source,
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


void load_ns_dbase(void)
{
    dbFILE *f;
    int ver, i, j, c;
    NickInfo *ni, **last, *prev;
    int failed = 0;

    if (!(f = open_db(s_NickServ, NickDBName, "r")))
	return;

    switch (ver = get_file_version(f)) {

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
	    wallops(NULL, "Write error on %s: %s", NickDBName,	\
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

    if (!(f = open_db(s_NickServ, NickDBName, "w")))
	return;
    for (i = 0; i < 256; i++) {
	for (ni = nicklists[i]; ni; ni = ni->next) {
	    SAFE(write_int8(1, f));
	    SAFE(write_buffer(ni->nick, f));
	    SAFE(write_buffer(ni->pass, f));
	    SAFE(write_string(ni->url, f));
	    SAFE(write_string(ni->email, f));
	    SAFE(write_string(ni->last_usermask, f));
	    SAFE(write_string(ni->last_realname, f));
	    SAFE(write_string(ni->last_quit, f));
	    SAFE(write_int32(ni->time_registered, f));
	    SAFE(write_int32(ni->last_seen, f));
	    SAFE(write_int16(ni->status, f));
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
#ifdef IRC_DAL4_4_15
	if (NSForceNickChange)
	    notice_lang(s_NickServ, u, FORCENICKCHANGE_IN_1_MINUTE);
	else
#endif
	    notice_lang(s_NickServ, u, DISCONNECT_IN_1_MINUTE);
	add_ns_timeout(ni, TO_COLLIDE, 60);
	return 0;
    }

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
	    collide(ni, 0);
	} else if (u->ni->flags & NI_KILL_QUICK) {
#ifdef IRC_DAL4_4_15
	    if (NSForceNickChange)
	    	notice_lang(s_NickServ, u, FORCENICKCHANGE_IN_20_SECONDS);
	    else
#endif
	    	notice_lang(s_NickServ, u, DISCONNECT_IN_20_SECONDS);
	    add_ns_timeout(ni, TO_COLLIDE, 20);
	} else {
#ifdef IRC_DAL4_4_15
	    if (NSForceNickChange)
	    	notice_lang(s_NickServ, u, FORCENICKCHANGE_IN_1_MINUTE);
	    else
#endif
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
    if (ni) {

#ifdef IRC_DAL4_4_15
	if (ni->status & NS_GUESTED) {
	    send_cmd(NULL, "NICK %s %ld 1 %s %s %s :%s Enforcement",
			u->nick, time(NULL), NSEnforcerUser, NSEnforcerHost, 
			ServerName, s_NickServ);
	    add_ns_timeout(ni, TO_RELEASE, NSReleaseTimeout);
	    ni->status &= ~NS_TEMPORARY;
	    ni->status |= NS_KILL_HELD;
	} else {
#endif
	    ni->status &= ~NS_TEMPORARY;
#ifdef IRC_DAL4_4_15
	}
#endif
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
    if (!NSExpire)
	return;
    for (i = 0; i < 256; i++) {
	for (ni = nicklists[i]; ni; ni = next) {
	    next = ni->next;
	    if (now - ni->last_seen >= NSExpire
			&& !(ni->status & (NS_VERBOTEN | NS_NO_EXPIRE))) {
		log("Expiring nickname %s", ni->nick);
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

    for (ni = nicklists[tolower(*nick)]; ni; ni = ni->next) {
	if (stricmp(ni->nick, nick) == 0)
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
    if (ni->last_usermask)
	free(ni->last_usermask);
    if (ni->last_realname)
	free(ni->last_realname);
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
 * Services is now able to force a nick change instead of killing the user. 
 * The new nick takes the form "Guest######". If a nick change is forced, we
 * do not introduce the enforcer nick until the user's nick actually changes. 
 * This is watched for and done in cancel_user(). -TheShadow 
 */

static void collide(NickInfo *ni, int from_timeout)
{
    User *u;

    u = finduser(ni->nick);

    if (!from_timeout)
	del_ns_timeout(ni, TO_COLLIDE);

#ifdef IRC_DAL4_4_15
    if (NSForceNickChange) {
	struct timeval tv;
	char guestnick[NICKMAX];

	gettimeofday(&tv, NULL);
	snprintf(guestnick, sizeof(guestnick), "%s%ld%ld", NSGuestNickPrefix,
			tv.tv_usec / 10000, tv.tv_sec % (60*60*24));

        notice_lang(s_NickServ, u, FORCENICKCHANGE_NOW, guestnick);

	send_cmd(NULL, "SVSNICK %s %s :%ld", ni->nick, guestnick, time(NULL));
	ni->status |= NS_GUESTED;
    } else {
#endif
	notice_lang(s_NickServ, u, DISCONNECT_NOW);
    	kill_user(s_NickServ, ni->nick, "Nick kill enforced");
    	send_cmd(NULL, "NICK %s %ld 1 %s %s %s :%s Enforcement",
		ni->nick, time(NULL), NSEnforcerUser, NSEnforcerHost,
		ServerName, s_NickServ);
	ni->status |= NS_KILL_HELD;
	add_ns_timeout(ni, TO_RELEASE, NSReleaseTimeout);
#ifdef IRC_DAL4_4_15
    }
#endif
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
	    notice(s_NickServ, u->nick, "    %2d) %s",
			i+1, langnames[langlist[i]]);
	}
    } else {
	help_cmd(s_NickServ, u, cmds, cmd);
    }
}

/*************************************************************************/

/* Register a nick. */

static void do_register(User *u)
{
    NickInfo *ni;
    char *pass = strtok(NULL, " ");

    if (readonly) {
	notice_lang(s_NickServ, u, NICK_REGISTRATION_DISABLED);
	return;
    }

#ifdef IRC_DAL4_4_15
    /* Prevent "Guest" nicks from being registered. -TheShadow */
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
#endif

    if (!pass || (stricmp(pass, u->nick) == 0 && strtok(NULL, " "))) {
	syntax_error(s_NickServ, u, "REGISTER", NICK_REGISTER_SYNTAX);

    } else if (time(NULL) < u->lastnickreg + NSRegDelay) {
	notice_lang(s_NickServ, u, NICK_REG_PLEASE_WAIT, NSRegDelay);

    } else if (u->real_ni) {	/* i.e. there's already such a nick regged */
	if (u->real_ni->status & NS_VERBOTEN) {
	    log("%s: %s@%s tried to register FORBIDden nick %s", s_NickServ,
			u->username, u->host, u->nick);
	    notice_lang(s_NickServ, u, NICK_CANNOT_BE_REGISTERED, u->nick);
	} else {
	    notice_lang(s_NickServ, u, NICK_ALREADY_REGISTERED, u->nick);
	}

    } else if (stricmp(u->nick, pass) == 0
		|| (StrictPasswords && strlen(pass) < 5)
    ) {
	notice_lang(s_NickServ, u, MORE_OBSCURE_PASSWORD);

    } else {
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
	    ni->channelcount = 0;
	    ni->channelmax = CSMaxReg;
	    ni->last_usermask = smalloc(strlen(u->username)+strlen(u->host)+2);
	    sprintf(ni->last_usermask, "%s@%s", u->username, u->host);
	    ni->last_realname = sstrdup(u->realname);
	    ni->time_registered = ni->last_seen = time(NULL);
	    ni->accesscount = 1;
	    ni->access = smalloc(sizeof(char *));
	    ni->access[0] = create_mask(u);
	    ni->language = DEF_LANGUAGE;
	    ni->link = NULL;
	    u->ni = u->real_ni = ni;
	    log("%s: `%s' registered by %s@%s", s_NickServ,
			u->nick, u->username, u->host);
	    notice_lang(s_NickServ, u, NICK_REGISTERED, u->nick, ni->access[0]);
#ifndef USE_ENCRYPTION
	    notice_lang(s_NickServ, u, NICK_PASSWORD_IS, ni->pass);
#endif
	    u->lastnickreg = time(NULL);
#ifdef IRC_DAL4_4_15
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
	notice(s_NickServ, u->nick, "Your nick isn't registered.");

    } else if (!(res = check_password(pass, ni->pass))) {
	log("%s: Failed IDENTIFY for %s!%s@%s",
		s_NickServ, u->nick, u->username, u->host);
	notice_lang(s_NickServ, u, PASSWORD_INCORRECT);
	bad_password(u);

    } else if (res == -1) {
	notice_lang(s_NickServ, u, NICK_IDENTIFY_FAILED);

    } else {
	ni->status |= NS_IDENTIFIED;
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
#ifdef IRC_DAL4_4_15
	send_cmd(ServerName, "SVSMODE %s +r", u->nick);
#endif
	log("%s: %s!%s@%s identified for nick %s", s_NickServ,
			u->nick, u->username, u->host, u->nick);
	notice_lang(s_NickServ, u, NICK_IDENTIFY_SUCCEEDED);
	if (!(ni->status & NS_RECOGNIZED))
	    check_memos(u);

    }
}

/*************************************************************************/

static void do_drop(User *u)
{
    char *nick = strtok(NULL, " ");
    NickInfo *ni;
    User *u2;

    if (readonly && !is_services_admin(u)) {
	notice_lang(s_NickServ, u, NICK_DROP_DISABLED);
	return;
    }

    if (!is_services_admin(u) && nick) {
	syntax_error(s_NickServ, u, "DROP", NICK_DROP_SYNTAX);

    } else if (!(ni = (nick ? findnick(nick) : u->real_ni))) {
	if (nick)
	    notice_lang(s_NickServ, u, NICK_X_NOT_REGISTERED, nick);
	else
	    notice_lang(s_NickServ, u, NICK_NOT_REGISTERED);

    } else if (NSSecureAdmins && nick && nick_is_services_admin(ni) && 
    							!is_services_root(u)) {
	notice_lang(s_NickServ, u, PERMISSION_DENIED);
	
    } else if (!nick && !nick_identified(u)) {
	notice_lang(s_NickServ, u, NICK_IDENTIFY_REQUIRED, s_NickServ);

    } else {
	if (readonly)
	    notice_lang(s_NickServ, u, READ_ONLY_MODE);
#ifdef IRC_DAL4_4_15
	send_cmd(ServerName, "SVSMODE %s -r", ni->nick);
#endif
	delnick(ni);
	log("%s: %s!%s@%s dropped nickname %s", s_NickServ,
		u->nick, u->username, u->host, nick ? nick : u->nick);
	if (nick)
	    notice_lang(s_NickServ, u, NICK_X_DROPPED, nick);
	else
	    notice_lang(s_NickServ, u, NICK_DROPPED);
	if (nick && (u2 = finduser(nick)))
	    u2->ni = u2->real_ni = NULL;
	else if (!nick)
	    u->ni = u->real_ni = NULL;
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
	notice_lang(s_NickServ, u, MORE_INFO, s_NickServ, "SET");
    } else if (!ni) {
	notice_lang(s_NickServ, u, NICK_NOT_REGISTERED);
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

    if (NSSecureAdmins && u->real_ni != ni && nick_is_services_admin(ni) && 
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
    notice_lang(s_NickServ, u, NICK_SET_PASSWORD_CHANGED_TO, ni->pass);
#endif
    if (u->real_ni != ni) {
	log("%s: %s!%s@%s used SET PASSWORD as Services admin on %s",
		s_NickServ, u->nick, u->username, u->host, ni->nick);
	if (WallSetpass) {
	    wallops(s_NickServ, "\2%s\2 used SET PASSWORD as Services admin "
			"on \2%s\2", u->nick, ni->nick);
	}
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
	notice_lang(s_NickServ, u, NICK_SET_KILL_ON);
    } else if (stricmp(param, "QUICK") == 0) {
	ni->flags |= NI_KILLPROTECT | NI_KILL_QUICK;
	ni->flags &= ~NI_KILL_IMMED;
	notice_lang(s_NickServ, u, NICK_SET_KILL_QUICK);
    } else if (stricmp(param, "IMMED") == 0) {
	if (NSAllowKillImmed) {
	    ni->flags |= NI_KILLPROTECT | NI_KILL_IMMED;
	    ni->flags &= ~NI_KILL_QUICK;
	    notice_lang(s_NickServ, u, NICK_SET_KILL_IMMED);
	} else {
	    notice_lang(s_NickServ, u, NICK_SET_KILL_IMMED_DISABLED);
	}
    } else if (stricmp(param, "OFF") == 0) {
	ni->flags &= ~(NI_KILLPROTECT | NI_KILL_QUICK | NI_KILL_IMMED);
	notice_lang(s_NickServ, u, NICK_SET_KILL_OFF);
    } else {
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
    } else if (stricmp(param, "USERMASK") == 0) {
	flag = NI_HIDE_MASK;
	onmsg = NICK_SET_HIDE_MASK_ON;
	offmsg = NICK_SET_HIDE_MASK_OFF;
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
	    notice(s_NickServ, u->nick, "    %s", *access);
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
	    notice(s_NickServ, u->nick, "    %s", *access);
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
	    log("%s: LINK: bad password for %s by %s!%s@%s",
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
		    notice(s_NickServ, u->nick, "    %s", ni2->nick);
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
    int is_servadmin = is_services_admin(u);

    if (!nick) {
    	syntax_error(s_NickServ, u, "INFO", NICK_INFO_SYNTAX);

    } else if (!(ni = findnick(nick))) {
	notice_lang(s_NickServ, u, NICK_X_NOT_REGISTERED, nick);

    } else if (ni->status & NS_VERBOTEN) {
	notice_lang(s_NickServ, u, NICK_X_FORBIDDEN, nick);

    } else {
	struct tm *tm;
	char buf[BUFSIZE], *end;
	const char *commastr = getstring(u->ni, COMMA_SPACE);
	int need_comma = 0;
	int nick_online = 0;
	int show_hidden = 0;

	/* Is the real owner of the nick we're looking up online? -TheShadow */
	if (ni->status & NS_IDENTIFIED)
	    nick_online = 1;

        /* Only show hidden fields to owner and sadmins and only when the ALL
	 * parameter is used. -TheShadow */
        if (param && stricmp(param, "ALL") == 0 && 
			((nick_online && (stricmp(u->nick, nick) == 0)) ||
                        	is_services_admin(u)))
            show_hidden = 1;

	real = getlink(ni);

	notice_lang(s_NickServ, u, NICK_INFO_REALNAME,
		nick, ni->last_realname);

	if (nick_online) {
	    if (show_hidden || !(real->flags & NI_HIDE_MASK))
		notice_lang(s_NickServ, u, NICK_INFO_ADDRESS_ONLINE,
			ni->last_usermask);
	    else
		notice_lang(s_NickServ, u, NICK_INFO_ADDRESS_ONLINE_NOHOST,
			ni->nick);

	} else {
	    if (show_hidden || !(real->flags & NI_HIDE_MASK))
		notice_lang(s_NickServ, u, NICK_INFO_ADDRESS,
			ni->last_usermask);

            tm = localtime(&ni->last_seen);
            strftime_lang(buf, sizeof(buf), u, STRFTIME_DATE_TIME_FORMAT, tm);
            notice_lang(s_NickServ, u, NICK_INFO_LAST_SEEN, buf);
	}	    
	    
	tm = localtime(&ni->time_registered);
	strftime_lang(buf, sizeof(buf), u, STRFTIME_DATE_TIME_FORMAT, tm);
	notice_lang(s_NickServ, u, NICK_INFO_TIME_REGGED, buf);
	if (ni->last_quit && (show_hidden || !(real->flags & NI_HIDE_QUIT)))
	    notice_lang(s_NickServ, u, NICK_INFO_LAST_QUIT, ni->last_quit);
	if (ni->url)
	    notice_lang(s_NickServ, u, NICK_INFO_URL, ni->url);
	if (ni->email && (show_hidden || !(real->flags & NI_HIDE_EMAIL)))
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
	if ((ni->status & NS_NO_EXPIRE) && (real == u->ni || is_servadmin))
	    notice_lang(s_NickServ, u, NICK_INFO_NO_EXPIRE);

    }
}

/*************************************************************************/

/* SADMINS can search for nicks based on their NS_VERBOTEN and NS_NO_EXPIRE
 * status. The keywords FORBIDDEN and NOEXPIRE represent these two states
 * respectively. These keywords should be included after the search pattern.
 * Multiple keywords are accepted and should be separated by spaces. Only one
 * of the keywords needs to match a nick's state for the nick to be displayed.
 * Forbidden nicks can be identified by "[Forbidden]" appearing in the last
 * seen address field. Nicks with NOEXPIRE set are preceeded by a "!". Only
 * SADMINS will be shown forbidden nicks and the "!" indicator.
 * Syntax for sadmins: LIST pattern [FORBIDDEN] [NOEXPIRE]
 * -TheShadow
 */

static void do_list(User *u)
{
    char *pattern = strtok(NULL, " ");
    char *keyword;
    NickInfo *ni;
    int nnicks, i;
    char buf[BUFSIZE];
    int is_servadmin = is_services_admin(u);
    int16 matchflags = 0; /* NS_ flags a nick must match one of to qualify */

    if (NSListOpersOnly && !(u->mode & UMODE_O)) {
	notice_lang(s_NickServ, u, PERMISSION_DENIED);
	return;
    }

    if (!pattern) {
	syntax_error(s_NickServ, u, "LIST",
		is_servadmin ? NICK_LIST_SERVADMIN_SYNTAX : NICK_LIST_SYNTAX);
    } else {
	nnicks = 0;

	while (is_servadmin && (keyword = strtok(NULL, " "))) {
	    if (stricmp(keyword, "FORBIDDEN") == 0)
		matchflags |= NS_VERBOTEN;
	    if (stricmp(keyword, "NOEXPIRE") == 0)
		matchflags |= NS_NO_EXPIRE;
	}

	notice_lang(s_NickServ, u, NICK_LIST_HEADER, pattern);
	for (i = 0; i < 256; i++) {
	    for (ni = nicklists[i]; ni; ni = ni->next) {
		if (!is_servadmin && ((ni->flags & NI_PRIVATE)
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
			if (is_servadmin && (ni->status & NS_NO_EXPIRE))
			    noexpire_char = '!';
			if (!is_servadmin && (ni->flags & NI_HIDE_MASK)) {
			    snprintf(buf, sizeof(buf), "%-20s  [Hidden]",
						ni->nick);
			} else if (ni->status & NS_VERBOTEN) {
			    snprintf(buf, sizeof(buf), "%-20s  [Forbidden]",
						ni->nick);
			} else {
			    snprintf(buf, sizeof(buf), "%-20s  %s",
						ni->nick, ni->last_usermask);
			}
			notice(s_NickServ, u->nick, "   %c%s",
						noexpire_char, buf);
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
    } else if (stricmp(nick, u->nick) == 0) {
	notice_lang(s_NickServ, u, NICK_NO_RECOVER_SELF);
    } else if (pass) {
	int res = check_password(pass, ni->pass);
	if (res == 1) {
	    collide(ni, 0);
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
    } else if (stricmp(nick, u->nick) == 0) {
	notice_lang(s_NickServ, u, NICK_NO_GHOST_SELF);
    } else if (pass) {
	int res = check_password(pass, ni->pass);
	if (res == 1) {
	    char buf[NICKMAX+32];
	    snprintf(buf, sizeof(buf), "GHOST command used by %s", u->nick);
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
	    snprintf(buf, sizeof(buf), "GHOST command used by %s", u->nick);
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
	    notice(s_NickServ, u->nick, "STATUS %s 0", nick);
	else if (nick_identified(u2))
	    notice(s_NickServ, u->nick, "STATUS %s 3", nick);
	else if (nick_recognized(u2))
	    notice(s_NickServ, u->nick, "STATUS %s 2", nick);
	else
	    notice(s_NickServ, u->nick, "STATUS %s 1", nick);
    }
}

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
    } else if (NSSecureAdmins && nick_is_services_admin(ni) && 
    							!is_services_root(u)) {
	notice_lang(s_NickServ, u, PERMISSION_DENIED);
    } else {
	log("%s: %s!%s@%s used GETPASS on %s",
		s_NickServ, u->nick, u->username, u->host, nick);
	if (WallGetpass)
	    wallops(s_NickServ, "\2%s\2 used GETPASS on \2%s\2", u->nick, nick);
	notice_lang(s_NickServ, u, NICK_GETPASS_PASSWORD_IS, nick, ni->pass);
    }
#endif
}

/*************************************************************************/

static void do_forbid(User *u)
{
    NickInfo *ni;
    char *nick = strtok(NULL, " ");

    /* Assumes that permission checking has already been done. */
    if (!nick) {
	syntax_error(s_NickServ, u, "FORBID", NICK_FORBID_SYNTAX);
	return;
    }
    if (readonly)
	notice_lang(s_NickServ, u, READ_ONLY_MODE);
    if ((ni = findnick(nick)) != NULL)
	delnick(ni);
    ni = makenick(nick);
    if (ni) {
	ni->status |= NS_VERBOTEN;
	log("%s: %s set FORBID for nick %s", s_NickServ, u->nick, nick);
	notice_lang(s_NickServ, u, NICK_FORBID_SUCCEEDED, nick);
    } else {
	log("%s: Valid FORBID for %s by %s failed", s_NickServ,
		nick, u->nick);
	notice_lang(s_NickServ, u, NICK_FORBID_FAILED, nick);
    }
}

/*************************************************************************/

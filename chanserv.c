/* ChanServ functions.
 *
 * Services is copyright (c) 1996-1999 Andy Church.
 *     E-mail: <achurch@dragonfire.net>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

/*************************************************************************/

#include "services.h"
#include "pseudo.h"

/*************************************************************************/

static ChannelInfo *chanlists[256];

static int def_levels[][2] = {
    { CA_AUTOOP,             5 },
    { CA_AUTOVOICE,          3 },
    { CA_AUTODEOP,          -1 },
    { CA_NOJOIN,            -2 },
    { CA_INVITE,             5 },
    { CA_AKICK,             10 },
    { CA_SET,   ACCESS_INVALID },
    { CA_CLEAR, ACCESS_INVALID },
    { CA_UNBAN,              5 },
    { CA_OPDEOP,             5 },
    { CA_ACCESS_LIST,        0 },
    { CA_ACCESS_CHANGE,      1 },
    { CA_MEMO,              10 },
    { -1 }
};

typedef struct {
    int what;
    char *name;
    int desc;
} LevelInfo;
static LevelInfo levelinfo[] = {
    { CA_AUTOOP,        "AUTOOP",     CHAN_LEVEL_AUTOOP },
    { CA_AUTOVOICE,     "AUTOVOICE",  CHAN_LEVEL_AUTOVOICE },
    { CA_AUTODEOP,      "AUTODEOP",   CHAN_LEVEL_AUTODEOP },
    { CA_NOJOIN,        "NOJOIN",     CHAN_LEVEL_NOJOIN },
    { CA_INVITE,        "INVITE",     CHAN_LEVEL_INVITE },
    { CA_AKICK,         "AKICK",      CHAN_LEVEL_AKICK },
    { CA_SET,           "SET",        CHAN_LEVEL_SET },
    { CA_CLEAR,         "CLEAR",      CHAN_LEVEL_CLEAR },
    { CA_UNBAN,         "UNBAN",      CHAN_LEVEL_UNBAN },
    { CA_OPDEOP,        "OPDEOP",     CHAN_LEVEL_OPDEOP },
    { CA_ACCESS_LIST,   "ACC-LIST",   CHAN_LEVEL_ACCESS_LIST },
    { CA_ACCESS_CHANGE, "ACC-CHANGE", CHAN_LEVEL_ACCESS_CHANGE },
    { CA_MEMO,          "MEMO",       CHAN_LEVEL_MEMO },
    { -1 }
};
static int levelinfo_maxwidth = 0;

/*************************************************************************/

static void alpha_insert_chan(ChannelInfo *ci);
static ChannelInfo *makechan(const char *chan);
static int delchan(ChannelInfo *ci);
static void reset_levels(ChannelInfo *ci);
static int is_founder(User *user, ChannelInfo *ci);
static int is_identified(User *user, ChannelInfo *ci);
static int get_access(User *user, ChannelInfo *ci);

static void do_help(User *u);
static void do_register(User *u);
static void do_identify(User *u);
static void do_drop(User *u);
static void do_set(User *u);
static void do_set_founder(User *u, ChannelInfo *ci, char *param);
static void do_set_successor(User *u, ChannelInfo *ci, char *param);
static void do_set_password(User *u, ChannelInfo *ci, char *param);
static void do_set_desc(User *u, ChannelInfo *ci, char *param);
static void do_set_url(User *u, ChannelInfo *ci, char *param);
static void do_set_email(User *u, ChannelInfo *ci, char *param);
static void do_set_entrymsg(User *u, ChannelInfo *ci, char *param);
static void do_set_topic(User *u, ChannelInfo *ci, char *param);
static void do_set_mlock(User *u, ChannelInfo *ci, char *param);
static void do_set_keeptopic(User *u, ChannelInfo *ci, char *param);
static void do_set_topiclock(User *u, ChannelInfo *ci, char *param);
static void do_set_private(User *u, ChannelInfo *ci, char *param);
static void do_set_secureops(User *u, ChannelInfo *ci, char *param);
static void do_set_leaveops(User *u, ChannelInfo *ci, char *param);
static void do_set_restricted(User *u, ChannelInfo *ci, char *param);
static void do_set_secure(User *u, ChannelInfo *ci, char *param);
static void do_set_opnotice(User *u, ChannelInfo *ci, char *param);
static void do_set_noexpire(User *u, ChannelInfo *ci, char *param);
static void do_access(User *u);
static void do_akick(User *u);
static void do_info(User *u);
static void do_list(User *u);
static void do_invite(User *u);
static void do_levels(User *u);
static void do_op(User *u);
static void do_deop(User *u);
static void do_unban(User *u);
static void do_clear(User *u);
static void do_getpass(User *u);
static void do_forbid(User *u);
static void do_status(User *u);

/*************************************************************************/

static Command cmds[] = {
    { "HELP",     do_help,     NULL,  -1,                       -1,-1,-1,-1 },
    { "REGISTER", do_register, NULL,  CHAN_HELP_REGISTER,       -1,-1,-1,-1 },
    { "IDENTIFY", do_identify, NULL,  CHAN_HELP_IDENTIFY,       -1,-1,-1,-1 },
    { "DROP",     do_drop,     NULL,  -1,
		CHAN_HELP_DROP, CHAN_SERVADMIN_HELP_DROP,
		CHAN_SERVADMIN_HELP_DROP, CHAN_SERVADMIN_HELP_DROP },
    { "SET",      do_set,      NULL,  CHAN_HELP_SET,
		-1, CHAN_SERVADMIN_HELP_SET,
		CHAN_SERVADMIN_HELP_SET, CHAN_SERVADMIN_HELP_SET },
    { "SET FOUNDER",    NULL,  NULL,  CHAN_HELP_SET_FOUNDER,    -1,-1,-1,-1 },
    { "SET SUCCESSOR",  NULL,  NULL,  CHAN_HELP_SET_SUCCESSOR,  -1,-1,-1,-1 },
    { "SET PASSWORD",   NULL,  NULL,  CHAN_HELP_SET_PASSWORD,   -1,-1,-1,-1 },
    { "SET DESC",       NULL,  NULL,  CHAN_HELP_SET_DESC,       -1,-1,-1,-1 },
    { "SET URL",        NULL,  NULL,  CHAN_HELP_SET_URL,        -1,-1,-1,-1 },
    { "SET EMAIL",      NULL,  NULL,  CHAN_HELP_SET_EMAIL,      -1,-1,-1,-1 },
    { "SET ENTRYMSG",   NULL,  NULL,  CHAN_HELP_SET_ENTRYMSG,   -1,-1,-1,-1 },
    { "SET TOPIC",      NULL,  NULL,  CHAN_HELP_SET_TOPIC,      -1,-1,-1,-1 },
    { "SET KEEPTOPIC",  NULL,  NULL,  CHAN_HELP_SET_KEEPTOPIC,  -1,-1,-1,-1 },
    { "SET TOPICLOCK",  NULL,  NULL,  CHAN_HELP_SET_TOPICLOCK,  -1,-1,-1,-1 },
    { "SET MLOCK",      NULL,  NULL,  CHAN_HELP_SET_MLOCK,      -1,-1,-1,-1 },
    { "SET RESTRICTED", NULL,  NULL,  CHAN_HELP_SET_RESTRICTED, -1,-1,-1,-1 },
    { "SET SECURE",     NULL,  NULL,  CHAN_HELP_SET_SECURE,     -1,-1,-1,-1 },
    { "SET SECUREOPS",  NULL,  NULL,  CHAN_HELP_SET_SECUREOPS,  -1,-1,-1,-1 },
    { "SET LEAVEOPS",   NULL,  NULL,  CHAN_HELP_SET_LEAVEOPS,   -1,-1,-1,-1 },
    { "SET OPNOTICE",   NULL,  NULL,  CHAN_HELP_SET_OPNOTICE,   -1,-1,-1,-1 },
    { "SET NOEXPIRE",   NULL,  NULL,  -1, -1,
		CHAN_SERVADMIN_HELP_SET_NOEXPIRE,
		CHAN_SERVADMIN_HELP_SET_NOEXPIRE,
		CHAN_SERVADMIN_HELP_SET_NOEXPIRE },
    { "ACCESS",   do_access,   NULL,  CHAN_HELP_ACCESS,         -1,-1,-1,-1 },
    { "ACCESS LEVELS",  NULL,  NULL,  CHAN_HELP_ACCESS_LEVELS,  -1,-1,-1,-1 },
    { "AKICK",    do_akick,    NULL,  CHAN_HELP_AKICK,          -1,-1,-1,-1 },
    { "LEVELS",   do_levels,   NULL,  CHAN_HELP_LEVELS,         -1,-1,-1,-1 },
    { "INFO",     do_info,     NULL,  CHAN_HELP_INFO,           
		-1, CHAN_SERVADMIN_HELP_INFO, CHAN_SERVADMIN_HELP_INFO, 
		CHAN_SERVADMIN_HELP_INFO },
    { "LIST",     do_list,     NULL,  -1,
		CHAN_HELP_LIST, CHAN_SERVADMIN_HELP_LIST,
		CHAN_SERVADMIN_HELP_LIST, CHAN_SERVADMIN_HELP_LIST },
    { "OP",       do_op,       NULL,  CHAN_HELP_OP,             -1,-1,-1,-1 },
    { "DEOP",     do_deop,     NULL,  CHAN_HELP_DEOP,           -1,-1,-1,-1 },
    { "INVITE",   do_invite,   NULL,  CHAN_HELP_INVITE,         -1,-1,-1,-1 },
    { "UNBAN",    do_unban,    NULL,  CHAN_HELP_UNBAN,          -1,-1,-1,-1 },
    { "CLEAR",    do_clear,    NULL,  CHAN_HELP_CLEAR,          -1,-1,-1,-1 },
    { "GETPASS",  do_getpass,  is_services_admin,  -1,
		-1, CHAN_SERVADMIN_HELP_GETPASS,
		CHAN_SERVADMIN_HELP_GETPASS, CHAN_SERVADMIN_HELP_GETPASS },
    { "FORBID",   do_forbid,   is_services_admin,  -1,
		-1, CHAN_SERVADMIN_HELP_FORBID,
		CHAN_SERVADMIN_HELP_FORBID, CHAN_SERVADMIN_HELP_FORBID },
    { "STATUS",   do_status,   is_services_admin,  -1,
		-1, CHAN_SERVADMIN_HELP_STATUS,
		CHAN_SERVADMIN_HELP_STATUS, CHAN_SERVADMIN_HELP_STATUS },
    { NULL }
};

/*************************************************************************/
/*************************************************************************/

/* Display total number of registered channels and info about each; or, if
 * a specific channel is given, display information about that channel
 * (like /msg ChanServ INFO <channel>).  If count_only != 0, then only
 * display the number of registered channels (the channel parameter is
 * ignored).
 */

void listchans(int count_only, const char *chan)
{
    int count = 0;
    ChannelInfo *ci;
    int i;

    if (count_only) {

	for (i = 0; i < 256; i++) {
	    for (ci = chanlists[i]; ci; ci = ci->next)
		count++;
	}
	printf("%d channels registered.\n", count);

    } else if (chan) {

	struct tm *tm;
	char *s, buf[BUFSIZE];

	if (!(ci = cs_findchan(chan))) {
	    printf("Channel %s not registered.\n", chan);
	    return;
	}
	if (ci->flags & CI_VERBOTEN) {
	    printf("Channel %s is FORBIDden.\n", ci->name);
	} else {
	    printf("Information about channel %s:\n", ci->name);
	    s = ci->founder->last_usermask;
	    printf("        Founder: %s%s%s%s\n",
			ci->founder->nick,
			s ? " (" : "", s ? s : "", s ? ")" : "");
	    printf("    Description: %s\n", ci->desc);
	    tm = localtime(&ci->time_registered);
	    strftime(buf, sizeof(buf), getstring(NULL,STRFTIME_DATE_TIME_FORMAT), tm);
	    printf("     Registered: %s\n", buf);
	    tm = localtime(&ci->last_used);
	    strftime(buf, sizeof(buf), getstring(NULL,STRFTIME_DATE_TIME_FORMAT), tm);
	    printf("      Last used: %s\n", buf);
	    if (ci->last_topic) {
		printf("     Last topic: %s\n", ci->last_topic);
		printf("   Topic set by: %s\n", ci->last_topic_setter);
	    }
	    if (ci->url)
		printf("            URL: %s\n", ci->url);
	    if (ci->email)
		printf(" E-mail address: %s\n", ci->email);
	    printf("        Options: ");
	    if (!ci->flags) {
		printf("None\n");
	    } else {
		int need_comma = 0;
		static const char commastr[] = ", ";
		if (ci->flags & CI_PRIVATE) {
		    printf("Private");
		    need_comma = 1;
		}
		if (ci->flags & CI_KEEPTOPIC) {
		    printf("%sTopic Retention", need_comma ? commastr : "");
		    need_comma = 1;
		}
		if (ci->flags & CI_TOPICLOCK) {
		    printf("%sTopic Lock", need_comma ? commastr : "");
		    need_comma = 1;
		}
		if (ci->flags & CI_SECUREOPS) {
		    printf("%sSecure Ops", need_comma ? commastr : "");
		    need_comma = 1;
		}
		if (ci->flags & CI_LEAVEOPS) {
		    printf("%sLeave Ops", need_comma ? commastr : "");
		    need_comma = 1;
		}
		if (ci->flags & CI_RESTRICTED) {
		    printf("%sRestricted Access", need_comma ? commastr : "");
		    need_comma = 1;
		}
		if (ci->flags & CI_SECURE) {
		    printf("%sSecure", need_comma ? commastr : "");
		    need_comma = 1;
		}
		if (ci->flags & CI_NO_EXPIRE) {
		    printf("%sNo Expire", need_comma ? commastr : "");
		    need_comma = 1;
		}
		printf("\n");
	    }
	    printf("      Mode lock: ");
	    if (ci->mlock_on || ci->mlock_key || ci->mlock_limit) {
		printf("+%s%s%s%s%s%s%s%s%s",
			(ci->mlock_on & CMODE_I) ? "i" : "",
			(ci->mlock_key         ) ? "k" : "",
			(ci->mlock_limit       ) ? "l" : "",
			(ci->mlock_on & CMODE_M) ? "m" : "",
			(ci->mlock_on & CMODE_N) ? "n" : "",
			(ci->mlock_on & CMODE_P) ? "p" : "",
			(ci->mlock_on & CMODE_S) ? "s" : "",
			(ci->mlock_on & CMODE_T) ? "t" : "",
#ifdef IRC_DAL4_4_15
			(ci->mlock_on & CMODE_R) ? "R" : "");
#else
			"");
#endif
	    }
	    if (ci->mlock_off)
		printf("-%s%s%s%s%s%s%s%s%s",
			(ci->mlock_off & CMODE_I) ? "i" : "",
			(ci->mlock_off & CMODE_K) ? "k" : "",
			(ci->mlock_off & CMODE_L) ? "l" : "",
			(ci->mlock_off & CMODE_M) ? "m" : "",
			(ci->mlock_off & CMODE_N) ? "n" : "",
			(ci->mlock_off & CMODE_P) ? "p" : "",
			(ci->mlock_off & CMODE_S) ? "s" : "",
			(ci->mlock_off & CMODE_T) ? "t" : "",
#ifdef IRC_DAL4_4_15
			(ci->mlock_off & CMODE_R) ? "R" : "");
#else
			"");
#endif

	    if (ci->mlock_key)
		printf(" %s", ci->mlock_key);
	    if (ci->mlock_limit)
		printf(" %d", ci->mlock_limit);
	    printf("\n");
	}

    } else {

	for (i = 0; i < 256; i++) {
	    for (ci = chanlists[i]; ci; ci = ci->next) {
		printf("  %s %-20s  %s\n", ci->flags & CI_NO_EXPIRE ? "!" : " ",
			    ci->name,
			    ci->flags & CI_VERBOTEN ? 
				    "Disallowed (FORBID)" : ci->desc);
		count++;
	    }
	}
	printf("%d channels registered.\n", count);

    }
}

/*************************************************************************/

/* Return information on memory use.  Assumes pointers are valid. */

void get_chanserv_stats(long *nrec, long *memuse)
{
    long count = 0, mem = 0;
    int i, j;
    ChannelInfo *ci;

    for (i = 0; i < 256; i++) {
	for (ci = chanlists[i]; ci; ci = ci->next) {
	    count++;
	    mem += sizeof(*ci);
	    if (ci->desc)
		mem += strlen(ci->desc)+1;
	    if (ci->url)
		mem += strlen(ci->url)+1;
	    if (ci->email)
		mem += strlen(ci->email)+1;
	    mem += ci->accesscount * sizeof(ChanAccess);
	    mem += ci->akickcount * sizeof(AutoKick);
	    for (j = 0; j < ci->akickcount; j++) {
		if (!ci->akick[j].is_nick && ci->akick[j].u.mask)
		    mem += strlen(ci->akick[j].u.mask)+1;
		if (ci->akick[j].reason)
		    mem += strlen(ci->akick[j].reason)+1;
	    }
	    if (ci->mlock_key)
		mem += strlen(ci->mlock_key)+1;
	    if (ci->last_topic)
		mem += strlen(ci->last_topic)+1;
	    if (ci->entry_message)
		mem += strlen(ci->entry_message)+1;
	    if (ci->levels)
		mem += sizeof(*ci->levels) * CA_SIZE;
	    mem += ci->memos.memocount * sizeof(Memo);
	    for (j = 0; j < ci->memos.memocount; j++) {
		if (ci->memos.memos[j].text)
		    mem += strlen(ci->memos.memos[j].text)+1;
	    }
	}
    }
    *nrec = count;
    *memuse = mem;
}

/*************************************************************************/
/*************************************************************************/

/* ChanServ initialization. */

void cs_init(void)
{
    Command *cmd;

    cmd = lookup_cmd(cmds, "REGISTER");
    if (cmd)
	cmd->help_param1 = s_NickServ;
    cmd = lookup_cmd(cmds, "SET SECURE");
    if (cmd)
	cmd->help_param1 = s_NickServ;
    cmd = lookup_cmd(cmds, "SET SUCCESSOR");
    if (cmd)
	cmd->help_param1 = (char *)(long)CSMaxReg;
}

/*************************************************************************/

/* Main ChanServ routine. */

void chanserv(const char *source, char *buf)
{
    char *cmd, *s;
    User *u = finduser(source);

    if (!u) {
	log("%s: user record for %s not found", s_ChanServ, source);
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
	notice(s_ChanServ, source, "\1PING %s", s);
    } else if (skeleton) {
	notice_lang(s_ChanServ, u, SERVICE_OFFLINE, s_ChanServ);
    } else if (stricmp(cmd, "AOP") == 0 || stricmp(cmd, "SOP") == 0) {
	notice_lang(s_ChanServ, u, CHAN_NO_AOP_SOP, s_ChanServ);
    } else {
	run_cmd(s_ChanServ, u, cmds, cmd);
    }
}

/*************************************************************************/

/* Load/save data files. */


#define SAFE(x) do {					\
    if ((x) < 0) {					\
	if (!forceload)					\
	    fatal("Read error on %s", ChanDBName);	\
	failed = 1;					\
	break;						\
    }							\
} while (0)


/* Load v1-v4 files. */
static void load_old_cs_dbase(dbFILE *f, int ver)
{
    int i, j, c;
    ChannelInfo *ci, **last, *prev;
    NickInfo *ni;
    int failed = 0;

    struct {
	short level;
#ifdef COMPATIBILITY_V2
	short is_nick;
#else
	short in_use;
#endif
	char *name;
    } old_chanaccess;

    struct {
	short is_nick;
	short pad;
	char *name;
	char *reason;
    } old_autokick;

    struct {
	ChannelInfo *next, *prev;
	char name[CHANMAX];
	char founder[NICKMAX];
	char founderpass[PASSMAX];
	char *desc;
	time_t time_registered;
	time_t last_used;
	long accesscount;
	ChanAccess *access;
	long akickcount;
	AutoKick *akick;
	short mlock_on, mlock_off;
	long mlock_limit;
	char *mlock_key;
	char *last_topic;
	char last_topic_setter[NICKMAX];
	time_t last_topic_time;
	long flags;
	short *levels;
	char *url;
	char *email;
	struct channel_ *c;
    } old_channelinfo;


    for (i = 33; i < 256 && !failed; i++) {

	last = &chanlists[i];
	prev = NULL;
	while ((c = getc_db(f)) != 0) {
	    if (c != 1)
		fatal("Invalid format in %s", ChanDBName);
	    SAFE(read_variable(old_channelinfo, f));
	    if (debug >= 3)
		log("debug: load_old_cs_dbase: read channel %s",
			old_channelinfo.name);
	    ci = scalloc(1, sizeof(ChannelInfo));
	    strscpy(ci->name, old_channelinfo.name, CHANMAX);
	    ci->founder = findnick(old_channelinfo.founder);
	    strscpy(ci->founderpass, old_channelinfo.founderpass, PASSMAX);
	    ci->time_registered = old_channelinfo.time_registered;
	    ci->last_used = old_channelinfo.last_used;
	    ci->accesscount = old_channelinfo.accesscount;
	    ci->akickcount = old_channelinfo.akickcount;
	    ci->mlock_on = old_channelinfo.mlock_on;
	    ci->mlock_off = old_channelinfo.mlock_off;
	    ci->mlock_limit = old_channelinfo.mlock_limit;
	    strscpy(ci->last_topic_setter,
			old_channelinfo.last_topic_setter, NICKMAX);
	    ci->last_topic_time = old_channelinfo.last_topic_time;
	    ci->flags = old_channelinfo.flags;
#ifdef USE_ENCRYPTION
	    if (!(ci->flags & (CI_ENCRYPTEDPW | CI_VERBOTEN))) {
		if (debug)
		    log("debug: %s: encrypting password for %s on load",
				s_ChanServ, ci->name);
		if (encrypt_in_place(ci->founderpass, PASSMAX) < 0)
		    fatal("%s: load database: Can't encrypt %s password!",
				s_ChanServ, ci->name);
		ci->flags |= CI_ENCRYPTEDPW;
	    }
#else
	    if (ci->flags & CI_ENCRYPTEDPW) {
		/* Bail: it makes no sense to continue with encrypted
		 * passwords, since we won't be able to verify them */
		fatal("%s: load database: password for %s encrypted "
		          "but encryption disabled, aborting",
		          s_ChanServ, ci->name);
	    }
#endif
	    ni = ci->founder;
	    if (ni) {
		if (ni->channelcount+1 > ni->channelcount)
		    ni->channelcount++;
		ni = getlink(ni);
		if (ni != ci->founder && ni->channelcount+1 > ni->channelcount)
		    ni->channelcount++;
	    }
	    SAFE(read_string(&ci->desc, f));
	    if (!ci->desc)
		ci->desc = sstrdup("");
	    if (old_channelinfo.url)
		SAFE(read_string(&ci->url, f));
	    if (old_channelinfo.email)
		SAFE(read_string(&ci->email, f));
	    if (old_channelinfo.mlock_key)
		SAFE(read_string(&ci->mlock_key, f));
	    if (old_channelinfo.last_topic)
		SAFE(read_string(&ci->last_topic, f));

	    if (ci->accesscount) {
		ChanAccess *access;
		char *s;

		access = smalloc(sizeof(ChanAccess) * ci->accesscount);
		ci->access = access;
		for (j = 0; j < ci->accesscount; j++, access++) {
		    SAFE(read_variable(old_chanaccess, f));
#ifdef COMPATIBILITY_V2
		    if (old_chanaccess.is_nick < 0)
			access->in_use = 0;
		    else
			access->in_use = old_chanaccess.is_nick;
#else
		    access->in_use = old_chanaccess.in_use;
#endif
		    access->level = old_chanaccess.level;
		}
		access = ci->access;
		for (j = 0; j < ci->accesscount; j++, access++) {
		    SAFE(read_string(&s, f));
		    if (s && access->in_use)
			access->ni = findnick(s);
		    else
			access->ni = NULL;
		    if (s)
			free(s);
		    if (access->ni == NULL)
			access->in_use = 0;
		}
	    } else {
		ci->access = NULL;
	    } /* if (ci->accesscount) */

	    if (ci->akickcount) {
		AutoKick *akick;
		char *s;

		akick = smalloc(sizeof(AutoKick) * ci->akickcount);
		ci->akick = akick;
		for (j = 0; j < ci->akickcount; j++, akick++) {
		    SAFE(read_variable(old_autokick, f));
		    if (old_autokick.is_nick < 0) {
			akick->in_use = 0;
			akick->is_nick = 0;
		    } else {
			akick->in_use = 1;
			akick->is_nick = old_autokick.is_nick;
		    }
		    akick->reason = old_autokick.reason;
		}
		akick = ci->akick;
		for (j = 0; j < ci->akickcount; j++, akick++) {
		    SAFE(read_string(&s, f));
		    if (akick->is_nick) {
			if (!(akick->u.ni = findnick(s)))
			    akick->in_use = akick->is_nick = 0;
			free(s);
		    } else {
			if (!(akick->u.mask = s))
			    akick->in_use = 0;
		    }
		    if (akick->reason)
			SAFE(read_string(&akick->reason, f));
		    if (!akick->in_use) {
			if (akick->is_nick) {
			    akick->u.ni = NULL;
			} else {
			    free(akick->u.mask);
			    akick->u.mask = NULL;
			}
			if (akick->reason) {
			    free(akick->reason);
			    akick->reason = NULL;
			}
		    }
		}
	    } else {
		ci->akick = NULL;
	    } /* if (ci->akickcount) */

	    if (old_channelinfo.levels) {
		int16 n_entries;
		ci->levels = NULL;
		reset_levels(ci);
		SAFE(read_int16(&n_entries, f));
#ifdef COMPATIBILITY_V2
		/* Ignore earlier, incompatible levels list */
		if (n_entries == 6) {
		    fseek(f, sizeof(short) * n_entries, SEEK_CUR);
		} else
#endif
		for (j = 0; j < n_entries; j++) {
		    short lev;
		    SAFE(read_variable(lev, f));
		    if (j < CA_SIZE)
			ci->levels[j] = lev;
		}
	    } else {
		reset_levels(ci);
	    }

	    ci->memos.memomax = MSMaxMemos;

	    *last = ci;
	    last = &ci->next;
	    ci->prev = prev;
	    prev = ci;

	} /* while (getc_db(f) != 0) */

	*last = NULL;

    } /* for (i) */
}


void load_cs_dbase(void)
{
    dbFILE *f;
    int ver, i, j, c;
    ChannelInfo *ci, **last, *prev;
    int failed = 0;

    if (!(f = open_db(s_ChanServ, ChanDBName, "r")))
	return;

    switch (ver = get_file_version(f)) {

      case 7:
      case 6:
      case 5:

	for (i = 0; i < 256 && !failed; i++) {
	    int16 tmp16;
	    int32 tmp32;
	    int n_levels;
	    char *s;

	    last = &chanlists[i];
	    prev = NULL;
	    while ((c = getc_db(f)) != 0) {
		if (c != 1)
		    fatal("Invalid format in %s", ChanDBName);
		ci = smalloc(sizeof(ChannelInfo));
		*last = ci;
		last = &ci->next;
		ci->prev = prev;
		prev = ci;
		SAFE(read_buffer(ci->name, f));
		SAFE(read_string(&s, f));
		if (s)
		    ci->founder = findnick(s);
		else
		    ci->founder = NULL;
		if (ver >= 7) {
		    SAFE(read_string(&s, f));
		    if (s)
			ci->successor = findnick(s);
		    else
			ci->successor = NULL;
		} else {
		    ci->successor = NULL;
		}
		if (ver == 5 && ci->founder != NULL) {
		    /* Channel count incorrect in version 5 files */
		    ci->founder->channelcount++;
		}
		SAFE(read_buffer(ci->founderpass, f));
		SAFE(read_string(&ci->desc, f));
		if (!ci->desc)
		    ci->desc = sstrdup("");
		SAFE(read_string(&ci->url, f));
		SAFE(read_string(&ci->email, f));
		SAFE(read_int32(&tmp32, f));
		ci->time_registered = tmp32;
		SAFE(read_int32(&tmp32, f));
		ci->last_used = tmp32;
		SAFE(read_string(&ci->last_topic, f));
		SAFE(read_buffer(ci->last_topic_setter, f));
		SAFE(read_int32(&tmp32, f));
		ci->last_topic_time = tmp32;
		SAFE(read_int32(&ci->flags, f));
#ifdef USE_ENCRYPTION
		if (!(ci->flags & (CI_ENCRYPTEDPW | CI_VERBOTEN))) {
		    if (debug)
			log("debug: %s: encrypting password for %s on load",
				s_ChanServ, ci->name);
		    if (encrypt_in_place(ci->founderpass, PASSMAX) < 0)
			fatal("%s: load database: Can't encrypt %s password!",
				s_ChanServ, ci->name);
		    ci->flags |= CI_ENCRYPTEDPW;
		}
#else
		if (ci->flags & CI_ENCRYPTEDPW) {
		    /* Bail: it makes no sense to continue with encrypted
		     * passwords, since we won't be able to verify them */
		    fatal("%s: load database: password for %s encrypted "
		          "but encryption disabled, aborting",
		          s_ChanServ, ci->name);
		}
#endif
		SAFE(read_int16(&tmp16, f));
		n_levels = tmp16;
		ci->levels = smalloc(2*CA_SIZE);
		reset_levels(ci);
		for (j = 0; j < n_levels; j++) {
		    if (j < CA_SIZE)
			SAFE(read_int16(&ci->levels[j], f));
		    else
			SAFE(read_int16(&tmp16, f));
		}

		SAFE(read_int16(&ci->accesscount, f));
		if (ci->accesscount) {
		    ci->access = scalloc(ci->accesscount, sizeof(ChanAccess));
		    for (j = 0; j < ci->accesscount; j++) {
			SAFE(read_int16(&ci->access[j].in_use, f));
			if (ci->access[j].in_use) {
			    SAFE(read_int16(&ci->access[j].level, f));
			    SAFE(read_string(&s, f));
			    if (s) {
				ci->access[j].ni = findnick(s);
				free(s);
			    }
			    if (ci->access[j].ni == NULL)
				ci->access[j].in_use = 0;
			}
		    }
		} else {
		    ci->access = NULL;
		}

		SAFE(read_int16(&ci->akickcount, f));
		if (ci->akickcount) {
		    ci->akick = scalloc(ci->akickcount, sizeof(AutoKick));
		    for (j = 0; j < ci->akickcount; j++) {
			SAFE(read_int16(&ci->akick[j].in_use, f));
			if (ci->akick[j].in_use) {
			    SAFE(read_int16(&ci->akick[j].is_nick, f));
			    SAFE(read_string(&s, f));
			    if (ci->akick[j].is_nick) {
				ci->akick[j].u.ni = findnick(s);
				if (!ci->akick[j].u.ni)
				    ci->akick[j].in_use = 0;
				free(s);
			    } else {
				ci->akick[j].u.mask = s;
			    }
			    SAFE(read_string(&s, f));
			    if (ci->akick[j].in_use)
				ci->akick[j].reason = s;
			    else if (s)
				free(s);
			}
		    }
		} else {
		    ci->akick = NULL;
		}

		SAFE(read_int16(&ci->mlock_on, f));
		SAFE(read_int16(&ci->mlock_off, f));
		SAFE(read_int32(&ci->mlock_limit, f));
		SAFE(read_string(&ci->mlock_key, f));

		SAFE(read_int16(&ci->memos.memocount, f));
		SAFE(read_int16(&ci->memos.memomax, f));
		if (ci->memos.memocount) {
		    Memo *memos;
		    memos = smalloc(sizeof(Memo) * ci->memos.memocount);
		    ci->memos.memos = memos;
		    for (j = 0; j < ci->memos.memocount; j++, memos++) {
			SAFE(read_int32(&memos->number, f));
			SAFE(read_int16(&memos->flags, f));
			SAFE(read_int32(&tmp32, f));
			memos->time = tmp32;
			SAFE(read_buffer(memos->sender, f));
			SAFE(read_string(&memos->text, f));
		    }
		}

		SAFE(read_string(&ci->entry_message, f));

		ci->c = NULL;
		
	    } /* while (getc_db(f) != 0) */

	    *last = NULL;

	} /* for (i) */

	break; /* case 5 and up */

      case 4:
      case 3:
      case 2:
      case 1:
	load_old_cs_dbase(f, ver);
	break;

      default:
	fatal("Unsupported version number (%d) on %s", ver, ChanDBName);

    } /* switch (version) */

    close_db(f);

    /* Check for non-forbidden channels with no founder */
    for (i = 0; i < 256; i++) {
	ChannelInfo *next;
	for (ci = chanlists[i]; ci; ci = next) {
	    next = ci->next;
	    if (!(ci->flags & CI_VERBOTEN) && !ci->founder) {
		log("%s: database load: Deleting founderless channel %s",
			s_ChanServ, ci->name);
		delchan(ci);
	    }
	}
    }

}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do {						\
    if ((x) < 0) {						\
	restore_db(f);						\
	log_perror("Write error on %s", ChanDBName);		\
	if (time(NULL) - lastwarn > WarningTimeout) {		\
	    wallops(NULL, "Write error on %s: %s", ChanDBName,	\
			strerror(errno));			\
	    lastwarn = time(NULL);				\
	}							\
	return;							\
    }								\
} while (0)

void save_cs_dbase(void)
{
    dbFILE *f;
    int i, j;
    ChannelInfo *ci;
    Memo *memos;
    static time_t lastwarn = 0;

    if (!(f = open_db(s_ChanServ, ChanDBName, "w")))
	return;

    for (i = 0; i < 256; i++) {
	int16 tmp16;

	for (ci = chanlists[i]; ci; ci = ci->next) {
	    SAFE(write_int8(1, f));
	    SAFE(write_buffer(ci->name, f));
	    if (ci->founder)
		SAFE(write_string(ci->founder->nick, f));
	    else
		SAFE(write_string(NULL, f));
	    if (ci->successor)
		SAFE(write_string(ci->successor->nick, f));
	    else
		SAFE(write_string(NULL, f));
	    SAFE(write_buffer(ci->founderpass, f));
	    SAFE(write_string(ci->desc, f));
	    SAFE(write_string(ci->url, f));
	    SAFE(write_string(ci->email, f));
	    SAFE(write_int32(ci->time_registered, f));
	    SAFE(write_int32(ci->last_used, f));
	    SAFE(write_string(ci->last_topic, f));
	    SAFE(write_buffer(ci->last_topic_setter, f));
	    SAFE(write_int32(ci->last_topic_time, f));
	    SAFE(write_int32(ci->flags, f));

	    tmp16 = CA_SIZE;
	    SAFE(write_int16(tmp16, f));
	    for (j = 0; j < CA_SIZE; j++)
		SAFE(write_int16(ci->levels[j], f));

	    SAFE(write_int16(ci->accesscount, f));
	    for (j = 0; j < ci->accesscount; j++) {
		SAFE(write_int16(ci->access[j].in_use, f));
		if (ci->access[j].in_use) {
		    SAFE(write_int16(ci->access[j].level, f));
		    SAFE(write_string(ci->access[j].ni->nick, f));
		}
	    }

	    SAFE(write_int16(ci->akickcount, f));
	    for (j = 0; j < ci->akickcount; j++) {
		SAFE(write_int16(ci->akick[j].in_use, f));
		if (ci->akick[j].in_use) {
		    SAFE(write_int16(ci->akick[j].is_nick, f));
		    if (ci->akick[j].is_nick)
			SAFE(write_string(ci->akick[j].u.ni->nick, f));
		    else
			SAFE(write_string(ci->akick[j].u.mask, f));
		    SAFE(write_string(ci->akick[j].reason, f));
		}
	    }

	    SAFE(write_int16(ci->mlock_on, f));
	    SAFE(write_int16(ci->mlock_off, f));
	    SAFE(write_int32(ci->mlock_limit, f));
	    SAFE(write_string(ci->mlock_key, f));

	    SAFE(write_int16(ci->memos.memocount, f));
	    SAFE(write_int16(ci->memos.memomax, f));
	    memos = ci->memos.memos;
	    for (j = 0; j < ci->memos.memocount; j++, memos++) {
		SAFE(write_int32(memos->number, f));
		SAFE(write_int16(memos->flags, f));
		SAFE(write_int32(memos->time, f));
		SAFE(write_buffer(memos->sender, f));
		SAFE(write_string(memos->text, f));
	    }

	    SAFE(write_string(ci->entry_message, f));

	} /* for (chanlists[i]) */

	SAFE(write_int8(0, f));

    } /* for (i) */

    close_db(f);
}

#undef SAFE

/*************************************************************************/

/* Check the current modes on a channel; if they conflict with a mode lock,
 * fix them. */

void check_modes(const char *chan)
{
    Channel *c = findchan(chan);
    ChannelInfo *ci;
    char newmodes[32], *newkey = NULL;
    int32 newlimit = 0;
    char *end = newmodes;
    int modes;
    int set_limit = 0, set_key = 0;

    if (!c || c->bouncy_modes)
	return;

/* FIXME: old code... delete me when the -r code below is working. -TheShadow
    if (!c || !(ci = c->ci) || c->bouncy_modes)
	return;
*/

    /* Check for mode bouncing */
    if (c->server_modecount >= 3 && c->chanserv_modecount >= 3) {
#if defined(IRC_DALNET) || defined(IRC_UNDERNET)
	wallops(NULL, "Warning: unable to set modes on channel %s.  "
		"Are your servers' U:lines configured correctly?", chan);
#else
	wallops(NULL, "Warning: unable to set modes on channel %s.  "
		"Are your servers configured correctly?", chan);
#endif
	log("%s: Bouncy modes on channel %s", s_ChanServ, c->name);
	c->bouncy_modes = 1;
	return;
    }

    if (c->chanserv_modetime != time(NULL)) {
	c->chanserv_modecount = 0;
	c->chanserv_modetime = time(NULL);
    }
    c->chanserv_modecount++;

    if (!(ci = c->ci)) {
#ifdef IRC_DAL4_4_15
	/* Services _always_ knows who should be +r. If a channel tries to be
	 * +r and is not registered, send mode -r. This will compensate for
	 * servers that are split when mode -r is initially sent and then try
	 * to set +r when they rejoin. -TheShadow 
	 */
	if (c->mode & CMODE_r) {
	    c->mode &= ~CMODE_r;
	    send_cmd(MODE_SENDER(s_ChanServ), "MODE %s -r", c->name);
	}
#endif
	return;
    }

    *end++ = '+';
    modes = ~c->mode & ci->mlock_on;
    if (modes & CMODE_I) {
	*end++ = 'i';
	c->mode |= CMODE_I;
    }
    if (modes & CMODE_M) {
	*end++ = 'm';
	c->mode |= CMODE_M;
    }
    if (modes & CMODE_N) {
	*end++ = 'n';
	c->mode |= CMODE_N;
    }
    if (modes & CMODE_P) {
	*end++ = 'p';
	c->mode |= CMODE_P;
    }
    if (modes & CMODE_S) {
	*end++ = 's';
	c->mode |= CMODE_S;
    }
    if (modes & CMODE_T) {
	*end++ = 't';
	c->mode |= CMODE_T;
    }
#ifdef IRC_DAL4_4_15
    if (modes & CMODE_R) {
	*end++ = 'R';
	c->mode |= CMODE_R;
    }
    if (modes & CMODE_r) {
	*end++ = 'r';
	c->mode |= CMODE_r;
    }
#endif

    if (ci->mlock_limit && ci->mlock_limit != c->limit) {
	*end++ = 'l';
	newlimit = ci->mlock_limit;
	c->limit = newlimit;
	set_limit = 1;
    }
    if (!c->key && ci->mlock_key) {
	*end++ = 'k';
	newkey = ci->mlock_key;
	c->key = sstrdup(newkey);
	set_key = 1;
    } else if (c->key && ci->mlock_key && strcmp(c->key, ci->mlock_key) != 0) {
	char *av[3];
	send_cmd(MODE_SENDER(s_ChanServ), "MODE %s -k %s", c->name, c->key);
	av[0] = sstrdup(c->name);
	av[1] = sstrdup("-k");
	av[2] = sstrdup(c->key);
	do_cmode(s_ChanServ, 3, av);
	free(av[0]);
	free(av[1]);
	free(av[2]);
	free(c->key);
	*end++ = 'k';
	newkey = ci->mlock_key;
	c->key = sstrdup(newkey);
	set_key = 1;
    }

    if (end[-1] == '+')
	end--;

    *end++ = '-';
    modes = c->mode & ci->mlock_off;
    if (modes & CMODE_I) {
	*end++ = 'i';
	c->mode &= ~CMODE_I;
    }
    if (modes & CMODE_M) {
	*end++ = 'm';
	c->mode &= ~CMODE_M;
    }
    if (modes & CMODE_N) {
	*end++ = 'n';
	c->mode &= ~CMODE_N;
    }
    if (modes & CMODE_P) {
	*end++ = 'p';
	c->mode &= ~CMODE_P;
    }
    if (modes & CMODE_S) {
	*end++ = 's';
	c->mode &= ~CMODE_S;
    }
    if (modes & CMODE_T) {
	*end++ = 't';
	c->mode &= ~CMODE_T;
    }
#ifdef IRC_DAL4_4_15
    if (modes & CMODE_R) {
    	*end++ = 'R';
    	c->mode &= ~CMODE_R;
    }
#endif

    if (c->key && (ci->mlock_off & CMODE_K)) {
	*end++ = 'k';
	newkey = sstrdup(c->key);
	free(c->key);
	c->key = NULL;
	set_key = 1;
    }
    if (c->limit && (ci->mlock_off & CMODE_L)) {
	*end++ = 'l';
	c->limit = 0;
    }

    if (end[-1] == '-')
	end--;

    if (end == newmodes)
	return;
    *end = 0;
    if (set_limit) {
	if (set_key)
	    send_cmd(MODE_SENDER(s_ChanServ), "MODE %s %s %d :%s", c->name,
				newmodes, newlimit, newkey ? newkey : "");
	else
	    send_cmd(MODE_SENDER(s_ChanServ), "MODE %s %s %d", c->name,
				newmodes, newlimit);
    } else if (set_key) {
	send_cmd(MODE_SENDER(s_ChanServ), "MODE %s %s :%s", c->name,
				newmodes, newkey ? newkey : "");
    } else {
	send_cmd(MODE_SENDER(s_ChanServ), "MODE %s %s", c->name, newmodes);
    }

    if (newkey && !c->key)
	free(newkey);
}

/*************************************************************************/

/* Check whether a user is allowed to be opped on a channel; if they
 * aren't, deop them.  If serverop is 1, the +o was done by a server.
 * Return 1 if the user is allowed to be opped, 0 otherwise. */

int check_valid_op(User *user, const char *chan, int serverop)
{
    ChannelInfo *ci = cs_findchan(chan);

    if (!ci || (ci->flags & CI_LEAVEOPS))
	return 1;

    if (is_oper(user->nick) || is_services_admin(user))
	return 1;

    if (ci->flags & CI_VERBOTEN) {
	/* check_kick() will get them out; we needn't explain. */
	send_cmd(MODE_SENDER(s_ChanServ), "MODE %s -o %s", chan, user->nick);
	return 0;
    }

    if (serverop && time(NULL)-start_time >= CSRestrictDelay
				&& !check_access(user, ci, CA_AUTOOP)) {
	notice_lang(s_ChanServ, user, CHAN_IS_REGISTERED, s_ChanServ);
	send_cmd(MODE_SENDER(s_ChanServ), "MODE %s -o %s", chan, user->nick);
	return 0;
    }

    if (check_access(user, ci, CA_AUTODEOP)) {
#if 0	/* This is probably a bad idea.  People could flood other people,
	 * and stuff. */
	notice(s_ChanServ, user->nick, CHAN_NOT_ALLOWED_OP, chan);
#endif
	send_cmd(MODE_SENDER(s_ChanServ), "MODE %s -o %s", chan, user->nick);
	return 0;
    }

    return 1;
}

/*************************************************************************/

/* Check whether a user should be opped on a channel, and if so, do it.
 * Return 1 if the user was opped, 0 otherwise.  (Updates the channel's
 * last used time if the user was opped.) */

int check_should_op(User *user, const char *chan)
{
    ChannelInfo *ci = cs_findchan(chan);

    if (!ci || (ci->flags & CI_VERBOTEN) || *chan == '+')
	return 0;

    if ((ci->flags & CI_SECURE) && !nick_identified(user))
	return 0;

    if (check_access(user, ci, CA_AUTOOP)) {
	send_cmd(MODE_SENDER(s_ChanServ), "MODE %s +o %s", chan, user->nick);
	ci->last_used = time(NULL);
	return 1;
    }

    return 0;
}

/*************************************************************************/

/* Check whether a user should be voiced on a channel, and if so, do it.
 * Return 1 if the user was voiced, 0 otherwise. */

int check_should_voice(User *user, const char *chan)
{
    ChannelInfo *ci = cs_findchan(chan);

    if (!ci || (ci->flags & CI_VERBOTEN) || *chan == '+')
	return 0;

    if ((ci->flags & CI_SECURE) && !nick_identified(user))
	return 0;

    if (check_access(user, ci, CA_AUTOVOICE)) {
	send_cmd(MODE_SENDER(s_ChanServ), "MODE %s +v %s", chan, user->nick);
	return 1;
    }

    return 0;
}

/*************************************************************************/

/* Tiny helper routine to get ChanServ out of a channel after it went in. */

static void timeout_leave(Timeout *to)
{
    char *chan = to->data;
    send_cmd(s_ChanServ, "PART %s", chan);
    free(to->data);
}


/* Check whether a user is permitted to be on a channel.  If so, return 0;
 * else, kickban the user with an appropriate message (could be either
 * AKICK or restricted access) and return 1.  Note that this is called
 * _before_ the user is added to internal channel lists (so do_kick() is
 * not called).
 */

int check_kick(User *user, const char *chan)
{
    ChannelInfo *ci = cs_findchan(chan);
    AutoKick *akick;
    int i;
    NickInfo *ni;
    char *av[3], *mask;
    const char *reason;
    Timeout *t;
    int stay;

    if (!ci)
	return 0;

    if (is_oper(user->nick) || is_services_admin(user))
	return 0;

    if (ci->flags & CI_VERBOTEN) {
	mask = create_mask(user);
	reason = getstring(user->ni, CHAN_MAY_NOT_BE_USED);
	goto kick;
    }

    if (nick_recognized(user))
	ni = user->ni;
    else
	ni = NULL;

    for (akick = ci->akick, i = 0; i < ci->akickcount; akick++, i++) {
	if (!akick->in_use)
	    continue;
	if ((akick->is_nick && getlink(akick->u.ni) == ni)
		|| (!akick->is_nick && match_usermask(akick->u.mask, user))
	) {
	    if (debug >= 2) {
		log("debug: %s matched akick %s", user->nick,
			akick->is_nick ? akick->u.ni->nick : akick->u.mask);
	    }
	    mask = akick->is_nick ? create_mask(user) : sstrdup(akick->u.mask);
	    reason = akick->reason ? akick->reason : CSAutokickReason;
	    goto kick;
	}
    }

    if (time(NULL)-start_time >= CSRestrictDelay
				&& check_access(user, ci, CA_NOJOIN)) {
	mask = create_mask(user);
	reason = getstring(user->ni, CHAN_NOT_ALLOWED_TO_JOIN);
	goto kick;
    }

    return 0;

kick:
    if (debug) {
	log("debug: channel: AutoKicking %s!%s@%s",
		user->nick, user->username, user->host);
    }
    /* Remember that the user has not been added to our channel user list
     * yet, so we check whether the channel does not exist */
    stay = !findchan(chan);
    av[0] = sstrdup(chan);
#if defined(IRC_DALNET) || defined(IRC_UNDERNET)
    if (stay) {
#endif
	send_cmd(s_ChanServ, "JOIN %s", chan);
#if !defined(IRC_DALNET) && !defined(IRC_UNDERNET)
	send_cmd(ServerName, "MODE %s +o %s  0", chan, s_ChanServ);
	strcpy(av[0], chan);
	av[1] = sstrdup("+o");
	av[2] = sstrdup(s_ChanServ);
	do_cmode(ServerName, 3, av);
	free(av[1]);
	free(av[2]);
#endif
	strcpy(av[0], chan);
#if defined(IRC_DALNET) || defined(IRC_UNDERNET)
    }
#endif
    strcpy(av[0], chan);
    av[1] = sstrdup("+b");
    av[2] = mask;
    send_cmd(s_ChanServ, "MODE %s +b %s  %lu", chan, av[2], time(NULL));
    do_cmode(s_ChanServ, 3, av);
    free(av[0]);
    free(av[1]);
    free(av[2]);
    send_cmd(s_ChanServ, "KICK %s %s :%s", chan, user->nick, reason);
    if (stay) {
	t = add_timeout(CSInhabit, timeout_leave, 0);
	t->data = sstrdup(chan);
#if !defined(IRC_DALNET) && !defined(IRC_UNDERNET)
    } else {
	send_cmd(s_ChanServ, "PART %s", chan);
#endif
    }
    return 1;
}

/*************************************************************************/

/* Record the current channel topic in the ChannelInfo structure. */

void record_topic(const char *chan)
{
    Channel *c;
    ChannelInfo *ci;

    if (readonly)
	return;
    c = findchan(chan);
    if (!c || !(ci = c->ci))
	return;
    if (ci->last_topic)
	free(ci->last_topic);
    if (c->topic)
	ci->last_topic = sstrdup(c->topic);
    else
	ci->last_topic = NULL;
    strscpy(ci->last_topic_setter, c->topic_setter, NICKMAX);
    ci->last_topic_time = c->topic_time;
}

/*************************************************************************/

/* Restore the topic in a channel when it's created, if we should. */

void restore_topic(const char *chan)
{
    Channel *c = findchan(chan);
    ChannelInfo *ci;

    if (!c || !(ci = c->ci) || !(ci->flags & CI_KEEPTOPIC))
	return;
    if (c->topic)
	free(c->topic);
    if (ci->last_topic) {
	c->topic = sstrdup(ci->last_topic);
	strscpy(c->topic_setter, ci->last_topic_setter, NICKMAX);
	c->topic_time = ci->last_topic_time;
    } else {
	c->topic = NULL;
	strscpy(c->topic_setter, s_ChanServ, NICKMAX);
    }
#ifdef IRC_CLASSIC
    send_cmd(MODE_SENDER(s_ChanServ), "TOPIC %s %s :%s", chan,
		c->topic_setter, c->topic ? c->topic : "");
#else
    send_cmd(MODE_SENDER(s_ChanServ), "TOPIC %s %s %lu :%s", chan,
		c->topic_setter, c->topic_time, c->topic ? c->topic : "");
#endif
}

/*************************************************************************/

/* See if the topic is locked on the given channel, and return 1 (and fix
 * the topic) if so. */

int check_topiclock(const char *chan)
{
    Channel *c = findchan(chan);
    ChannelInfo *ci;

    if (!c || !(ci = c->ci) || !(ci->flags & CI_TOPICLOCK))
	return 0;
    if (c->topic)
	free(c->topic);
    if (ci->last_topic)
	c->topic = sstrdup(ci->last_topic);
    else
	c->topic = NULL;
    strscpy(c->topic_setter, ci->last_topic_setter, NICKMAX);
    c->topic_time = ci->last_topic_time;
#ifdef IRC_CLASSIC
    send_cmd(MODE_SENDER(s_ChanServ), "TOPIC %s %s :%s", chan,
		c->topic_setter, c->topic ? c->topic : "");
#else
    send_cmd(MODE_SENDER(s_ChanServ), "TOPIC %s %s %lu :%s", chan,
		c->topic_setter, c->topic_time, c->topic ? c->topic : "");
#endif
    return 1;
}

/*************************************************************************/

/* Remove all channels which have expired. */

void expire_chans()
{
    ChannelInfo *ci, *next;
    Channel *c;
    int i;
    time_t now = time(NULL);

    if (!CSExpire)
	return;

    for (i = 0; i < 256; i++) {
	for (ci = chanlists[i]; ci; ci = next) {
	    next = ci->next;
	    if (now - ci->last_used >= CSExpire
			&& !(ci->flags & (CI_VERBOTEN | CI_NO_EXPIRE))) {
		log("Expiring channel %s", ci->name);
#ifdef IRC_DAL4_4_15
		if ((c = findchan(ci->name))) {
		    c->mode &= ~CMODE_r;
		    send_cmd(s_ChanServ, "MODE %s -r", ci->name);
		}
#endif
		delchan(ci);
	    }
	}
    }
}

/*************************************************************************/

/* Remove a (deleted or expired) nickname from all channel lists. */

void cs_remove_nick(const NickInfo *ni)
{
    int i, j;
    ChannelInfo *ci, *next;
    ChanAccess *ca;
    AutoKick *akick;

    for (i = 0; i < 256; i++) {
	for (ci = chanlists[i]; ci; ci = next) {
	    next = ci->next;
	    if (ci->founder == ni) {
		if (ci->successor) {
		    NickInfo *ni2 = ci->successor;
		    if (ni2->channelcount >= ni2->channelmax) {
			log("%s: Successor (%s) of %s owns too many channels, "
			    "deleting channel",
			    s_ChanServ, ni2->nick, ci->name);
			delchan(ci);
		    } else {
			log("%s: Transferring foundership of %s from deleted "
			    "nick %s to successor %s",
			    s_ChanServ, ci->name, ni->nick, ni2->nick);
			ci->founder = ni2;
			ci->successor = NULL;
			if (ni2->channelcount+1 > ni2->channelcount)
			    ni2->channelcount++;
		    }
		} else {
		    log("%s: Deleting channel %s owned by deleted nick %s",
				s_ChanServ, ci->name, ni->nick);
		    delchan(ci);
		}
		continue;
	    }
	    for (ca = ci->access, j = ci->accesscount; j > 0; ca++, j--) {
		if (ca->in_use && ca->ni == ni) {
		    ca->in_use = 0;
		    ca->ni = NULL;
		}
	    }
	    for (akick = ci->akick, j = ci->akickcount; j > 0; akick++, j--) {
		if (akick->is_nick && akick->u.ni == ni) {
		    akick->in_use = akick->is_nick = 0;
		    akick->u.ni = NULL;
		    if (akick->reason) {
			free(akick->reason);
			akick->reason = NULL;
		    }
		}
	    }
	}
    }
}

/*************************************************************************/

/* Return the ChannelInfo structure for the given channel, or NULL if the
 * channel isn't registered. */

ChannelInfo *cs_findchan(const char *chan)
{
    ChannelInfo *ci;

    for (ci = chanlists[tolower(chan[1])]; ci; ci = ci->next) {
	if (stricmp(ci->name, chan) == 0)
	    return ci;
    }
    return NULL;
}

/*************************************************************************/

/* Return 1 if the user's access level on the given channel falls into the
 * given category, 0 otherwise.  Note that this may seem slightly confusing
 * in some cases: for example, check_access(..., CA_NOJOIN) returns true if
 * the user does _not_ have access to the channel (i.e. matches the NOJOIN
 * criterion). */

int check_access(User *user, ChannelInfo *ci, int what)
{
    int level = get_access(user, ci);
    int limit = ci->levels[what];

    if (level == ACCESS_FOUNDER)
	return (what==CA_AUTODEOP || what==CA_NOJOIN) ? 0 : 1;
    /* Hacks to make flags work */
    if (what == CA_AUTODEOP && (ci->flags & CI_SECUREOPS) && level == 0)
	return 1;
    if (limit == ACCESS_INVALID)
	return 0;
    if (what == CA_AUTODEOP || what == CA_NOJOIN)
	return level <= ci->levels[what];
    else
	return level >= ci->levels[what];
}

/*************************************************************************/
/*********************** ChanServ private routines ***********************/
/*************************************************************************/

/* Insert a channel alphabetically into the database. */

static void alpha_insert_chan(ChannelInfo *ci)
{
    ChannelInfo *ptr, *prev;
    char *chan = ci->name;

    for (prev = NULL, ptr = chanlists[tolower(chan[1])];
			ptr != NULL && stricmp(ptr->name, chan) < 0;
			prev = ptr, ptr = ptr->next)
	;
    ci->prev = prev;
    ci->next = ptr;
    if (!prev)
	chanlists[tolower(chan[1])] = ci;
    else
	prev->next = ci;
    if (ptr)
	ptr->prev = ci;
}

/*************************************************************************/

/* Add a channel to the database.  Returns a pointer to the new ChannelInfo
 * structure if the channel was successfully registered, NULL otherwise.
 * Assumes channel does not already exist. */

static ChannelInfo *makechan(const char *chan)
{
    ChannelInfo *ci;

    ci = scalloc(sizeof(ChannelInfo), 1);
    strscpy(ci->name, chan, CHANMAX);
    ci->time_registered = time(NULL);
    reset_levels(ci);
    alpha_insert_chan(ci);
    return ci;
}

/*************************************************************************/

/* Remove a channel from the ChanServ database.  Return 1 on success, 0
 * otherwise. */

static int delchan(ChannelInfo *ci)
{
    int i;
    NickInfo *ni = ci->founder;

    if (ci->c)
	ci->c->ci = NULL;
    if (ci->next)
	ci->next->prev = ci->prev;
    if (ci->prev)
	ci->prev->next = ci->next;
    else
	chanlists[tolower(ci->name[1])] = ci->next;
    if (ci->desc)
	free(ci->desc);
    if (ci->mlock_key)
	free(ci->mlock_key);
    if (ci->last_topic)
	free(ci->last_topic);
    if (ci->access)
	free(ci->access);
    for (i = 0; i < ci->akickcount; i++) {
	if (!ci->akick[i].is_nick && ci->akick[i].u.mask)
	    free(ci->akick[i].u.mask);
	if (ci->akick[i].reason)
	    free(ci->akick[i].reason);
    }
    if (ci->akick)
	free(ci->akick);
    if (ci->levels)
	free(ci->levels);
    if (ci->memos.memos) {
	for (i = 0; i < ci->memos.memocount; i++) {
	    if (ci->memos.memos[i].text)
		free(ci->memos.memos[i].text);
	}
	free(ci->memos.memos);
    }
    free(ci);
    while (ni) {
	if (ni->channelcount > 0)
	    ni->channelcount--;
	ni = ni->link;
    }
    return 1;
}

/*************************************************************************/

/* Reset channel access level values to their default state. */

static void reset_levels(ChannelInfo *ci)
{
    int i;

    if (ci->levels)
	free(ci->levels);
    ci->levels = smalloc(CA_SIZE * sizeof(*ci->levels));
    for (i = 0; def_levels[i][0] >= 0; i++)
	ci->levels[def_levels[i][0]] = def_levels[i][1];
}

/*************************************************************************/

/* Does the given user have founder access to the channel? */

static int is_founder(User *user, ChannelInfo *ci)
{
    if (user->ni == getlink(ci->founder)) {
	if ((nick_identified(user) ||
		 (nick_recognized(user) && !(ci->flags & CI_SECURE))))
	    return 1;
    }
    if (is_identified(user, ci))
	return 1;
    return 0;
}

/*************************************************************************/

/* Has the given user password-identified as founder for the channel? */

static int is_identified(User *user, ChannelInfo *ci)
{
    struct u_chaninfolist *c;

    for (c = user->founder_chans; c; c = c->next) {
	if (c->chan == ci)
	    return 1;
    }
    return 0;
}

/*************************************************************************/

/* Return the access level the given user has on the channel.  If the
 * channel doesn't exist, the user isn't on the access list, or the channel
 * is CS_SECURE and the user hasn't IDENTIFY'd with NickServ, return 0. */

static int get_access(User *user, ChannelInfo *ci)
{
    NickInfo *ni = user->ni;
    ChanAccess *access;
    int i;

    if (!ci || !ni)
	return 0;
    if (is_founder(user, ci))
	return ACCESS_FOUNDER;
    if (nick_identified(user)
	|| (nick_recognized(user) && !(ci->flags & CI_SECURE))
    ) {
	for (access = ci->access, i = 0; i < ci->accesscount; access++, i++) {
	    if (access->in_use && getlink(access->ni) == ni)
		return access->level;
	}
    }
    return 0;
}

/*************************************************************************/
/*********************** ChanServ command routines ***********************/
/*************************************************************************/

static void do_help(User *u)
{
    char *cmd = strtok(NULL, "");

    if (!cmd) {
	notice_help(s_ChanServ, u, CHAN_HELP);
	if (CSExpire >= 86400)
	    notice_help(s_ChanServ, u, CHAN_HELP_EXPIRES, CSExpire/86400);
	if (is_services_oper(u))
	    notice_help(s_ChanServ, u, CHAN_SERVADMIN_HELP);
    } else if (stricmp(cmd, "LEVELS DESC") == 0) {
	int i;
	notice_help(s_ChanServ, u, CHAN_HELP_LEVELS_DESC);
	if (!levelinfo_maxwidth) {
	    for (i = 0; levelinfo[i].what >= 0; i++) {
		int len = strlen(levelinfo[i].name);
		if (len > levelinfo_maxwidth)
		    levelinfo_maxwidth = len;
	    }
	}
	for (i = 0; levelinfo[i].what >= 0; i++) {
	    notice_help(s_ChanServ, u, CHAN_HELP_LEVELS_DESC_FORMAT,
			levelinfo_maxwidth, levelinfo[i].name,
			getstring(u->ni, levelinfo[i].desc));
	}
    } else {
	help_cmd(s_ChanServ, u, cmds, cmd);
    }
}

/*************************************************************************/

static void do_register(User *u)
{
    char *chan = strtok(NULL, " ");
    char *pass = strtok(NULL, " ");
    char *desc = strtok(NULL, "");
    NickInfo *ni = u->ni;
    Channel *c;
    ChannelInfo *ci;
    struct u_chaninfolist *uc;
#ifdef USE_ENCRYPTION
    char founderpass[PASSMAX+1];
#endif

    if (readonly) {
	notice_lang(s_ChanServ, u, CHAN_REGISTER_DISABLED);
	return;
    }

    if (!desc) {
	syntax_error(s_ChanServ, u, "REGISTER", CHAN_REGISTER_SYNTAX);
    } else if (*chan == '&') {
	notice_lang(s_ChanServ, u, CHAN_REGISTER_NOT_LOCAL);
    } else if (!ni) {
	notice_lang(s_ChanServ, u, CHAN_MUST_REGISTER_NICK, s_NickServ);
    } else if (!nick_recognized(u)) {
	notice_lang(s_ChanServ, u, CHAN_MUST_IDENTIFY_NICK,
		s_NickServ, s_NickServ);

    } else if ((ci = cs_findchan(chan)) != NULL) {
	if (ci->flags & CI_VERBOTEN) {
	    log("%s: Attempt to register FORBIDden channel %s by %s!%s@%s",
			s_ChanServ, ci->name, u->nick, u->username, u->host);
	    notice_lang(s_ChanServ, u, CHAN_MAY_NOT_BE_REGISTERED, chan);
	} else {
	    notice_lang(s_ChanServ, u, CHAN_ALREADY_REGISTERED, chan);
	}

    } else if (!is_chanop(u->nick, chan)) {
	notice_lang(s_ChanServ, u, CHAN_MUST_BE_CHANOP);

    } else if (ni->channelmax > 0 && ni->channelcount >= ni->channelmax) {
	notice_lang(s_ChanServ, u,
		ni->channelcount > ni->channelmax
					? CHAN_EXCEEDED_CHANNEL_LIMIT
					: CHAN_REACHED_CHANNEL_LIMIT,
		ni->channelmax);

    } else if (!(c = findchan(chan))) {
	log("%s: Channel %s not found for REGISTER", s_ChanServ, chan);
	notice_lang(s_ChanServ, u, CHAN_REGISTRATION_FAILED);

    } else if (!(ci = makechan(chan))) {
	log("%s: makechan() failed for REGISTER %s", s_ChanServ, chan);
	notice_lang(s_ChanServ, u, CHAN_REGISTRATION_FAILED);

#ifdef USE_ENCRYPTION
    } else if (strscpy(founderpass, pass, PASSMAX+1),
               encrypt_in_place(founderpass, PASSMAX) < 0) {
	log("%s: Couldn't encrypt password for %s (REGISTER)",
		s_ChanServ, chan);
	notice_lang(s_ChanServ, u, CHAN_REGISTRATION_FAILED);
	delchan(ci);
#endif

    } else {
	c->ci = ci;
	ci->c = c;
	ci->flags = CI_KEEPTOPIC | CI_SECURE;
#ifdef IRC_DAL4_4_15
	ci->mlock_on = CMODE_N | CMODE_T | CMODE_r;
#else
	ci->mlock_on = CMODE_N | CMODE_T;
#endif
	ci->memos.memomax = MSMaxMemos;
	ci->last_used = ci->time_registered;
	ci->founder = u->real_ni;
#ifdef USE_ENCRYPTION
	if (strlen(pass) > PASSMAX)
	    notice_lang(s_ChanServ, u, PASSWORD_TRUNCATED, PASSMAX);
	memset(pass, 0, strlen(pass));
	memcpy(ci->founderpass, founderpass, PASSMAX);
	ci->flags |= CI_ENCRYPTEDPW;
#else
	if (strlen(pass) > PASSMAX-1) /* -1 for null byte */
	    notice_lang(s_ChanServ, u, PASSWORD_TRUNCATED, PASSMAX-1);
	strscpy(ci->founderpass, pass, PASSMAX);
#endif
	ci->desc = sstrdup(desc);
	if (c->topic) {
	    ci->last_topic = sstrdup(c->topic);
	    strscpy(ci->last_topic_setter, c->topic_setter, NICKMAX);
	    ci->last_topic_time = c->topic_time;
	}
	ni = ci->founder;
	while (ni) {
	    if (ni->channelcount+1 > ni->channelcount)  /* Avoid wraparound */
		ni->channelcount++;
	    ni = ni->link;
	}
	log("%s: Channel %s registered by %s!%s@%s", s_ChanServ, chan,
		u->nick, u->username, u->host);
	notice_lang(s_ChanServ, u, CHAN_REGISTERED, chan, u->nick);
#ifndef USE_ENCRYPTION
	notice_lang(s_ChanServ, u, CHAN_PASSWORD_IS, ci->founderpass);
#endif
	uc = smalloc(sizeof(*uc));
	uc->next = u->founder_chans;
	uc->prev = NULL;
	if (u->founder_chans)
	    u->founder_chans->prev = uc;
	u->founder_chans = uc;
	uc->chan = ci;
	/* Implement new mode lock */
	check_modes(ci->name);

    }
}

/*************************************************************************/

static void do_identify(User *u)
{
    char *chan = strtok(NULL, " ");
    char *pass = strtok(NULL, " ");
    ChannelInfo *ci;
    struct u_chaninfolist *uc;

    if (!pass) {
	syntax_error(s_ChanServ, u, "IDENTIFY", CHAN_IDENTIFY_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else {
	int res;

	if ((res = check_password(pass, ci->founderpass)) == 1) {
	    if (!is_identified(u, ci)) {
		uc = smalloc(sizeof(*uc));
		uc->next = u->founder_chans;
		uc->prev = NULL;
		if (u->founder_chans)
		    u->founder_chans->prev = uc;
		u->founder_chans = uc;
		uc->chan = ci;
		log("%s: %s!%s@%s identified for %s", s_ChanServ,
			u->nick, u->username, u->host, ci->name);
	    }
	    notice_lang(s_ChanServ, u, CHAN_IDENTIFY_SUCCEEDED, chan);
	} else if (res < 0) {
	    log("%s: check_password failed for %s", s_ChanServ, ci->name);
	    notice_lang(s_ChanServ, u, CHAN_IDENTIFY_FAILED);
	} else {
	    log("%s: Failed IDENTIFY for %s by %s!%s@%s",
			s_ChanServ, ci->name, u->nick, u->username, u->host);
	    notice_lang(s_ChanServ, u, PASSWORD_INCORRECT);
	    bad_password(u);
	}

    }
}

/*************************************************************************/

static void do_drop(User *u)
{
    char *chan = strtok(NULL, " ");
    ChannelInfo *ci;
    NickInfo *ni;
    Channel *c;
    int is_servadmin = is_services_admin(u);

    if (readonly && !is_servadmin) {
	notice_lang(s_ChanServ, u, CHAN_DROP_DISABLED);
	return;
    }

    if (!chan) {
	syntax_error(s_ChanServ, u, "DROP", CHAN_DROP_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (!is_servadmin & (ci->flags & CI_VERBOTEN)) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!is_servadmin && !is_identified(u, ci)) {
	notice_lang(s_ChanServ, u, CHAN_IDENTIFY_REQUIRED, s_ChanServ, chan);
    } else {
	if (readonly)  /* in this case we know they're a Services admin */
	    notice_lang(s_ChanServ, u, READ_ONLY_MODE);
	ni = ci->founder;
	if (ni) {   /* This might be NULL (i.e. after FORBID) */
	    if (ni->channelcount > 0)
		ni->channelcount--;
	    ni = getlink(ni);
	    if (ni != ci->founder && ni->channelcount > 0)
		ni->channelcount--;
	}
	log("%s: Channel %s dropped by %s!%s@%s", s_ChanServ, ci->name,
			u->nick, u->username, u->host);
	delchan(ci);
#ifdef IRC_DAL4_4_15
	if ((c = findchan(chan))) {
	    c->mode &= ~CMODE_r;
	    send_cmd(s_ChanServ, "MODE %s -r", chan);
	}
#endif
	notice_lang(s_ChanServ, u, CHAN_DROPPED, chan);
    }
}

/*************************************************************************/

/* Main SET routine.  Calls other routines as follows:
 *	do_set_command(User *command_sender, ChannelInfo *ci, char *param);
 * The parameter passed is the first space-delimited parameter after the
 * option name, except in the case of DESC, TOPIC, and ENTRYMSG, in which
 * it is the entire remainder of the line.  Additional parameters beyond
 * the first passed in the function call can be retrieved using
 * strtok(NULL, toks).
 */
static void do_set(User *u)
{
    char *chan = strtok(NULL, " ");
    char *cmd  = strtok(NULL, " ");
    char *param;
    ChannelInfo *ci;
    int is_servadmin = is_services_admin(u);

    if (readonly) {
	notice_lang(s_ChanServ, u, CHAN_SET_DISABLED);
	return;
    }

    if (cmd) {
	if (stricmp(cmd, "DESC") == 0 || stricmp(cmd, "TOPIC") == 0
	 || stricmp(cmd, "ENTRYMSG") == 0)
	    param = strtok(NULL, "");
	else
	    param = strtok(NULL, " ");
    } else {
	param = NULL;
    }

    if (!param && (!cmd || (stricmp(cmd, "SUCCESSOR") != 0 &&
                            stricmp(cmd, "URL") != 0 &&
                            stricmp(cmd, "EMAIL") != 0 &&
                            stricmp(cmd, "ENTRYMSG") != 0))) {
	syntax_error(s_ChanServ, u, "SET", CHAN_SET_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!is_servadmin && !check_access(u, ci, CA_SET)) {
	notice_lang(s_ChanServ, u, ACCESS_DENIED);
    } else if (stricmp(cmd, "FOUNDER") == 0) {
	if (!is_servadmin && get_access(u, ci) < ACCESS_FOUNDER) {
	    notice_lang(s_ChanServ, u, CHAN_IDENTIFY_REQUIRED, s_ChanServ,chan);
	} else {
	    do_set_founder(u, ci, param);
	}
    } else if (stricmp(cmd, "SUCCESSOR") == 0) {
	if (!is_servadmin && get_access(u, ci) < ACCESS_FOUNDER) {
	    notice_lang(s_ChanServ, u, CHAN_IDENTIFY_REQUIRED, s_ChanServ,chan);
	} else {
	    do_set_successor(u, ci, param);
	}
    } else if (stricmp(cmd, "PASSWORD") == 0) {
	if (!is_servadmin && get_access(u, ci) < ACCESS_FOUNDER) {
	    notice_lang(s_ChanServ, u, CHAN_IDENTIFY_REQUIRED, s_ChanServ,chan);
	} else {
	    do_set_password(u, ci, param);
	}
    } else if (stricmp(cmd, "DESC") == 0) {
	do_set_desc(u, ci, param);
    } else if (stricmp(cmd, "URL") == 0) {
	do_set_url(u, ci, param);
    } else if (stricmp(cmd, "EMAIL") == 0) {
	do_set_email(u, ci, param);
    } else if (stricmp(cmd, "ENTRYMSG") == 0) {
	do_set_entrymsg(u, ci, param);
    } else if (stricmp(cmd, "TOPIC") == 0) {
	do_set_topic(u, ci, param);
    } else if (stricmp(cmd, "MLOCK") == 0) {
	do_set_mlock(u, ci, param);
    } else if (stricmp(cmd, "KEEPTOPIC") == 0) {
	do_set_keeptopic(u, ci, param);
    } else if (stricmp(cmd, "TOPICLOCK") == 0) {
	do_set_topiclock(u, ci, param);
    } else if (stricmp(cmd, "PRIVATE") == 0) {
	do_set_private(u, ci, param);
    } else if (stricmp(cmd, "SECUREOPS") == 0) {
	do_set_secureops(u, ci, param);
    } else if (stricmp(cmd, "LEAVEOPS") == 0) {
	do_set_leaveops(u, ci, param);
    } else if (stricmp(cmd, "RESTRICTED") == 0) {
	do_set_restricted(u, ci, param);
    } else if (stricmp(cmd, "SECURE") == 0) {
	do_set_secure(u, ci, param);
    } else if (stricmp(cmd, "OPNOTICE") == 0) {
	do_set_opnotice(u, ci, param);
    } else if (stricmp(cmd, "NOEXPIRE") == 0) {
	do_set_noexpire(u, ci, param);
    } else {
	notice_lang(s_ChanServ, u, CHAN_SET_UNKNOWN_OPTION, strupper(cmd));
	notice_lang(s_ChanServ, u, MORE_INFO, s_ChanServ, "SET");
    }
}

/*************************************************************************/

static void do_set_founder(User *u, ChannelInfo *ci, char *param)
{
    NickInfo *ni = findnick(param), *ni0 = ci->founder;

    if (!ni) {
	notice_lang(s_ChanServ, u, NICK_X_NOT_REGISTERED, param);
	return;
    }
    if (ni->channelcount >= ni->channelmax && !is_services_admin(u)) {
	notice_lang(s_ChanServ, u, CHAN_SET_FOUNDER_TOO_MANY_CHANS, param);
	return;
    }
    if (ni0->channelcount > 0)  /* Let's be paranoid... */
	ni0->channelcount--;
    ni0 = getlink(ni0);
    if (ni0 != ci->founder && ni0->channelcount > 0)
	ni0->channelcount--;
    ci->founder = ni;
    if (ni->channelcount+1 > ni->channelcount)
	ni->channelcount++;
    ni = getlink(ni);
    if (ni != ci->founder && ni->channelcount+1 > ni->channelcount)
	ni->channelcount++;
    log("%s: Changing founder of %s to %s by %s!%s@%s", s_ChanServ,
		ci->name, param, u->nick, u->username, u->host);
    notice_lang(s_ChanServ, u, CHAN_FOUNDER_CHANGED, ci->name, param);
}

/*************************************************************************/

static void do_set_successor(User *u, ChannelInfo *ci, char *param)
{
    NickInfo *ni;

    if (param) {
	ni = findnick(param);
	if (!ni) {
	    notice_lang(s_ChanServ, u, NICK_X_NOT_REGISTERED, param);
	    return;
	}
    } else {
	ni = NULL;
    }
    ci->successor = ni;
    if (ni)
	notice_lang(s_ChanServ, u, CHAN_SUCCESSOR_CHANGED, ci->name, param);
    else
	notice_lang(s_ChanServ, u, CHAN_SUCCESSOR_UNSET, ci->name);
}

/*************************************************************************/

static void do_set_password(User *u, ChannelInfo *ci, char *param)
{
#ifdef USE_ENCRYPTION
    int len = strlen(param);
    if (len > PASSMAX) {
	len = PASSMAX;
	param[len] = 0;
	notice_lang(s_ChanServ, u, PASSWORD_TRUNCATED, PASSMAX);
    }
    if (encrypt(param, len, ci->founderpass, PASSMAX) < 0) {
	memset(param, 0, strlen(param));
	log("%s: Failed to encrypt password for %s (set)",
		s_ChanServ, ci->name);
	notice_lang(s_ChanServ, u, CHAN_SET_PASSWORD_FAILED);
	return;
    }
    memset(param, 0, strlen(param));
    notice_lang(s_ChanServ, u, CHAN_PASSWORD_CHANGED, ci->name);
#else /* !USE_ENCRYPTION */
    if (strlen(param) > PASSMAX-1) /* -1 for null byte */
	notice_lang(s_ChanServ, u, PASSWORD_TRUNCATED, PASSMAX-1);
    strscpy(ci->founderpass, param, PASSMAX);
    notice_lang(s_ChanServ, u, CHAN_PASSWORD_CHANGED_TO,
		ci->name, ci->founderpass);
#endif /* USE_ENCRYPTION */
    if (get_access(u, ci) < ACCESS_FOUNDER) {
	log("%s: %s!%s@%s set password as Services admin for %s",
		s_ChanServ, u->nick, u->username, u->host, ci->name);
	if (WallSetpass)
	    wallops(s_ChanServ, "\2%s\2 set password as Services admin for "
				"channel \2%s\2", u->nick, ci->name);
    }
}

/*************************************************************************/

static void do_set_desc(User *u, ChannelInfo *ci, char *param)
{
    if (ci->desc)
	free(ci->desc);
    ci->desc = sstrdup(param);
    notice_lang(s_ChanServ, u, CHAN_DESC_CHANGED, ci->name, param);
}

/*************************************************************************/

static void do_set_url(User *u, ChannelInfo *ci, char *param)
{
    if (ci->url)
	free(ci->url);
    if (param) {
	ci->url = sstrdup(param);
	notice_lang(s_ChanServ, u, CHAN_URL_CHANGED, ci->name, param);
    } else {
	ci->url = NULL;
	notice_lang(s_ChanServ, u, CHAN_URL_UNSET, ci->name);
    }
}

/*************************************************************************/

static void do_set_email(User *u, ChannelInfo *ci, char *param)
{
    if (ci->email)
	free(ci->email);
    if (param) {
	ci->email = sstrdup(param);
	notice_lang(s_ChanServ, u, CHAN_EMAIL_CHANGED, ci->name, param);
    } else {
	ci->email = NULL;
	notice_lang(s_ChanServ, u, CHAN_EMAIL_UNSET, ci->name);
    }
}

/*************************************************************************/

static void do_set_entrymsg(User *u, ChannelInfo *ci, char *param)
{
    if (ci->entry_message)
	free(ci->entry_message);
    if (param) {
	ci->entry_message = sstrdup(param);
	notice_lang(s_ChanServ, u, CHAN_ENTRY_MSG_CHANGED, ci->name, param);
    } else {
	ci->entry_message = NULL;
	notice_lang(s_ChanServ, u, CHAN_ENTRY_MSG_UNSET, ci->name);
    }
}

/*************************************************************************/

static void do_set_topic(User *u, ChannelInfo *ci, char *param)
{
    Channel *c = ci->c;

    if (!c) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_IN_USE, ci->name);
	return;
    }
    if (ci->last_topic)
	free(ci->last_topic);
    if (*param)
	ci->last_topic = sstrdup(param);
    else
	ci->last_topic = NULL;
    if (c->topic) {
	free(c->topic);
	c->topic_time--;	/* to get around TS8 */
    } else
	c->topic_time = time(NULL);
    if (*param)
	c->topic = sstrdup(param);
    else
	c->topic = NULL;
    strscpy(ci->last_topic_setter, u->nick, NICKMAX);
    strscpy(c->topic_setter, u->nick, NICKMAX);
    ci->last_topic_time = c->topic_time;
#ifdef IRC_CLASSIC
    send_cmd(MODE_SENDER(s_ChanServ), "TOPIC %s %s :%s",
		ci->name, u->nick, param);
#else
    send_cmd(MODE_SENDER(s_ChanServ), "TOPIC %s %s %lu :%s",
		ci->name, u->nick, c->topic_time, param);
#endif
}

/*************************************************************************/

static void do_set_mlock(User *u, ChannelInfo *ci, char *param)
{
    char *s, modebuf[32], *end, c;
    int add = -1;	/* 1 if adding, 0 if deleting, -1 if neither */
    int newlock_on = 0, newlock_off = 0, newlock_limit = 0;
    char *newlock_key = NULL;

    while (*param) {
	if (*param != '+' && *param != '-' && add < 0) {
	    param++;
	    continue;
	}
	switch ((c = *param++)) {
	  case '+':
	    add = 1;
	    break;
	  case '-':
	    add = 0;
	    break;
	  case 'i':
	    if (add) {
		newlock_on |= CMODE_I;
		newlock_off &= ~CMODE_I;
	    } else {
		newlock_off |= CMODE_I;
		newlock_on &= ~CMODE_I;
	    }
	    break;
	  case 'k':
	    if (add) {
		if (!(s = strtok(NULL, " "))) {
		    notice_lang(s_ChanServ, u, CHAN_SET_MLOCK_KEY_REQUIRED);
		    return;
		}
		if (newlock_key)
		    free(newlock_key);
		newlock_key = sstrdup(s);
		newlock_off &= ~CMODE_K;
	    } else {
		if (newlock_key) {
		    free(newlock_key);
		    newlock_key = NULL;
		}
		newlock_off |= CMODE_K;
	    }
	    break;
	  case 'l':
	    if (add) {
		if (!(s = strtok(NULL, " "))) {
		    notice_lang(s_ChanServ, u, CHAN_SET_MLOCK_LIMIT_REQUIRED);
		    return;
		}
		if (atol(s) <= 0) {
		    notice_lang(s_ChanServ, u, CHAN_SET_MLOCK_LIMIT_POSITIVE);
		    return;
		}
		newlock_limit = atol(s);
		newlock_off &= ~CMODE_L;
	    } else {
		newlock_limit = 0;
		newlock_off |= CMODE_L;
	    }
	    break;
	  case 'm':
	    if (add) {
		newlock_on |= CMODE_M;
		newlock_off &= ~CMODE_M;
	    } else {
		newlock_off |= CMODE_M;
		newlock_on &= ~CMODE_M;
	    }
	    break;
	  case 'n':
	    if (add) {
		newlock_on |= CMODE_N;
		newlock_off &= ~CMODE_N;
	    } else {
		newlock_off |= CMODE_N;
		newlock_on &= ~CMODE_N;
	    }
	    break;
	  case 'p':
	    if (add) {
		newlock_on |= CMODE_P;
		newlock_off &= ~CMODE_P;
	    } else {
		newlock_off |= CMODE_P;
		newlock_on &= ~CMODE_P;
	    }
	    break;
	  case 's':
	    if (add) {
		newlock_on |= CMODE_S;
		newlock_off &= ~CMODE_S;
	    } else {
		newlock_off |= CMODE_S;
		newlock_on &= ~CMODE_S;
	    }
	    break;
	  case 't':
	    if (add) {
		newlock_on |= CMODE_T;
		newlock_off &= ~CMODE_T;
	    } else {
		newlock_off |= CMODE_T;
		newlock_on &= ~CMODE_T;
	    }
	    break;
#ifdef IRC_DAL4_4_15
	  case 'R':
	    if (add) {
		newlock_on |= CMODE_R;
		newlock_off &= ~CMODE_R;
	    } else {
		newlock_off |= CMODE_R;
	    	newlock_on &= ~CMODE_R;
	    }
	    break;
#endif
	  default:
	    notice_lang(s_ChanServ, u, CHAN_SET_MLOCK_UNKNOWN_CHAR, c);
	    break;
	} /* switch */
    } /* while (*param) */

    /* Now that everything's okay, actually set the new mode lock. */
    ci->mlock_on = newlock_on;
    ci->mlock_off = newlock_off;
    ci->mlock_limit = newlock_limit;
    if (ci->mlock_key)
	free(ci->mlock_key);
    ci->mlock_key = newlock_key;

    /* Tell the user about it. */
    end = modebuf;
    *end = 0;
    if (ci->mlock_on)
	end += snprintf(end, sizeof(modebuf)-(end-modebuf), 
			"+%s%s%s%s%s%s%s%s%s",
				(ci->mlock_on & CMODE_I) ? "i" : "",
				(ci->mlock_key         ) ? "k" : "",
				(ci->mlock_limit       ) ? "l" : "",
				(ci->mlock_on & CMODE_M) ? "m" : "",
				(ci->mlock_on & CMODE_N) ? "n" : "",
				(ci->mlock_on & CMODE_P) ? "p" : "",
				(ci->mlock_on & CMODE_S) ? "s" : "",
				(ci->mlock_on & CMODE_T) ? "t" : "",
#ifdef IRC_DAL4_4_15
				(ci->mlock_on & CMODE_R) ? "R" : "");
#else
				"");
#endif
    if (ci->mlock_off)
	end += snprintf(end, sizeof(modebuf)-(end-modebuf), 
			"-%s%s%s%s%s%s%s%s%s",
				(ci->mlock_off & CMODE_I) ? "i" : "",
				(ci->mlock_off & CMODE_K) ? "k" : "",
				(ci->mlock_off & CMODE_L) ? "l" : "",
				(ci->mlock_off & CMODE_M) ? "m" : "",
				(ci->mlock_off & CMODE_N) ? "n" : "",
				(ci->mlock_off & CMODE_P) ? "p" : "",
				(ci->mlock_off & CMODE_S) ? "s" : "",
				(ci->mlock_off & CMODE_T) ? "t" : "",
#ifdef IRC_DAL4_4_15
				(ci->mlock_off & CMODE_R) ? "R" : "");
#else
				"");
#endif

    if (*modebuf) {
	notice_lang(s_ChanServ, u, CHAN_MLOCK_CHANGED, ci->name, modebuf);
    } else {
	notice_lang(s_ChanServ, u, CHAN_MLOCK_REMOVED, ci->name);
    }

    /* Implement the new lock. */
    check_modes(ci->name);
}

/*************************************************************************/

static void do_set_keeptopic(User *u, ChannelInfo *ci, char *param)
{
    if (stricmp(param, "ON") == 0) {
	ci->flags |= CI_KEEPTOPIC;
	notice_lang(s_ChanServ, u, CHAN_SET_KEEPTOPIC_ON);
    } else if (stricmp(param, "OFF") == 0) {
	ci->flags &= ~CI_KEEPTOPIC;
	notice_lang(s_ChanServ, u, CHAN_SET_KEEPTOPIC_OFF);
    } else {
	syntax_error(s_ChanServ, u, "SET KEEPTOPIC", CHAN_SET_KEEPTOPIC_SYNTAX);
    }
}

/*************************************************************************/

static void do_set_topiclock(User *u, ChannelInfo *ci, char *param)
{
    if (stricmp(param, "ON") == 0) {
	ci->flags |= CI_TOPICLOCK;
	notice_lang(s_ChanServ, u, CHAN_SET_TOPICLOCK_ON);
    } else if (stricmp(param, "OFF") == 0) {
	ci->flags &= ~CI_TOPICLOCK;
	notice_lang(s_ChanServ, u, CHAN_SET_TOPICLOCK_OFF);
    } else {
	syntax_error(s_ChanServ, u, "SET TOPICLOCK", CHAN_SET_TOPICLOCK_SYNTAX);
    }
}

/*************************************************************************/

static void do_set_private(User *u, ChannelInfo *ci, char *param)
{
    if (stricmp(param, "ON") == 0) {
	ci->flags |= CI_PRIVATE;
	notice_lang(s_ChanServ, u, CHAN_SET_PRIVATE_ON);
    } else if (stricmp(param, "OFF") == 0) {
	ci->flags &= ~CI_PRIVATE;
	notice_lang(s_ChanServ, u, CHAN_SET_PRIVATE_OFF);
    } else {
	syntax_error(s_ChanServ, u, "SET PRIVATE", CHAN_SET_PRIVATE_SYNTAX);
    }
}

/*************************************************************************/

static void do_set_secureops(User *u, ChannelInfo *ci, char *param)
{
    if (stricmp(param, "ON") == 0) {
	ci->flags |= CI_SECUREOPS;
	notice_lang(s_ChanServ, u, CHAN_SET_SECUREOPS_ON);
    } else if (stricmp(param, "OFF") == 0) {
	ci->flags &= ~CI_SECUREOPS;
	notice_lang(s_ChanServ, u, CHAN_SET_SECUREOPS_OFF);
    } else {
	syntax_error(s_ChanServ, u, "SET SECUREOPS", CHAN_SET_SECUREOPS_SYNTAX);
    }
}

/*************************************************************************/

static void do_set_leaveops(User *u, ChannelInfo *ci, char *param)
{
    if (stricmp(param, "ON") == 0) {
	ci->flags |= CI_LEAVEOPS;
	notice_lang(s_ChanServ, u, CHAN_SET_LEAVEOPS_ON);
    } else if (stricmp(param, "OFF") == 0) {
	ci->flags &= ~CI_LEAVEOPS;
	notice_lang(s_ChanServ, u, CHAN_SET_LEAVEOPS_OFF);
    } else {
	syntax_error(s_ChanServ, u, "SET LEAVEOPS", CHAN_SET_LEAVEOPS_SYNTAX);
    }
}

/*************************************************************************/

static void do_set_restricted(User *u, ChannelInfo *ci, char *param)
{
    if (stricmp(param, "ON") == 0) {
	ci->flags |= CI_RESTRICTED;
	if (ci->levels[CA_NOJOIN] < 0)
	    ci->levels[CA_NOJOIN] = 0;
	notice_lang(s_ChanServ, u, CHAN_SET_RESTRICTED_ON);
    } else if (stricmp(param, "OFF") == 0) {
	ci->flags &= ~CI_RESTRICTED;
	if (ci->levels[CA_NOJOIN] >= 0)
	    ci->levels[CA_NOJOIN] = -1;
	notice_lang(s_ChanServ, u, CHAN_SET_RESTRICTED_OFF);
    } else {
	syntax_error(s_ChanServ,u,"SET RESTRICTED",CHAN_SET_RESTRICTED_SYNTAX);
    }
}

/*************************************************************************/

static void do_set_secure(User *u, ChannelInfo *ci, char *param)
{
    if (stricmp(param, "ON") == 0) {
	ci->flags |= CI_SECURE;
	notice_lang(s_ChanServ, u, CHAN_SET_SECURE_ON);
    } else if (stricmp(param, "OFF") == 0) {
	ci->flags &= ~CI_SECURE;
	notice_lang(s_ChanServ, u, CHAN_SET_SECURE_OFF);
    } else {
	syntax_error(s_ChanServ, u, "SET SECURE", CHAN_SET_SECURE_SYNTAX);
    }
}

/*************************************************************************/

static void do_set_opnotice(User *u, ChannelInfo *ci, char *param)
{
    if (stricmp(param, "ON") == 0) {
	ci->flags |= CI_OPNOTICE;
	notice_lang(s_ChanServ, u, CHAN_SET_OPNOTICE_ON);
    } else if (stricmp(param, "OFF") == 0) {
	ci->flags &= ~CI_OPNOTICE;
	notice_lang(s_ChanServ, u, CHAN_SET_OPNOTICE_OFF);
    } else {
	syntax_error(s_ChanServ, u, "SET OPNOTICE", CHAN_SET_OPNOTICE_SYNTAX);
    }
}

/*************************************************************************/

static void do_set_noexpire(User *u, ChannelInfo *ci, char *param)
{
    if (!is_services_admin(u)) {
	notice_lang(s_ChanServ, u, PERMISSION_DENIED);
	return;
    }
    if (stricmp(param, "ON") == 0) {
	ci->flags |= CI_NO_EXPIRE;
	notice_lang(s_ChanServ, u, CHAN_SET_NOEXPIRE_ON, ci->name);
    } else if (stricmp(param, "OFF") == 0) {
	ci->flags &= ~CI_NO_EXPIRE;
	notice_lang(s_ChanServ, u, CHAN_SET_NOEXPIRE_OFF, ci->name);
    } else {
	syntax_error(s_ChanServ, u, "SET NOEXPIRE", CHAN_SET_NOEXPIRE_SYNTAX);
    }
}

/*************************************************************************/

/* `last' is set to the last index this routine was called with
 * `perm' is incremented whenever a permission-denied error occurs
 */
static int access_del(User *u, ChanAccess *access, int *perm, int uacc)
{
    if (!access->in_use)
	return 0;
    if (uacc <= access->level) {
	(*perm)++;
	return 0;
    }
    access->ni = NULL;
    access->in_use = 0;
    return 1;
}

static int access_del_callback(User *u, int num, va_list args)
{
    ChannelInfo *ci = va_arg(args, ChannelInfo *);
    int *last = va_arg(args, int *);
    int *perm = va_arg(args, int *);
    int uacc = va_arg(args, int);
    if (num < 1 || num > ci->accesscount)
	return 0;
    *last = num;
    return access_del(u, &ci->access[num-1], perm, uacc);
}


static int access_list(User *u, int index, ChannelInfo *ci, int *sent_header)
{
    ChanAccess *access = &ci->access[index];
    NickInfo *ni;
    char *s;

    if (!access->in_use)
	return 0;
    if (!*sent_header) {
	notice_lang(s_ChanServ, u, CHAN_ACCESS_LIST_HEADER, ci->name);
	*sent_header = 1;
    }
    if ((ni = findnick(access->ni->nick))
			&& !(getlink(ni)->flags & NI_HIDE_MASK))
	s = ni->last_usermask;
    else
	s = NULL;
    notice_lang(s_ChanServ, u, CHAN_ACCESS_LIST_FORMAT,
		index+1, access->level, access->ni->nick,
		s ? " (" : "", s ? s : "", s ? ")" : "");
    return 1;
}

static int access_list_callback(User *u, int num, va_list args)
{
    ChannelInfo *ci = va_arg(args, ChannelInfo *);
    int *sent_header = va_arg(args, int *);
    if (num < 1 || num > ci->accesscount)
	return 0;
    return access_list(u, num-1, ci, sent_header);
}


static void do_access(User *u)
{
    char *chan = strtok(NULL, " ");
    char *cmd  = strtok(NULL, " ");
    char *nick = strtok(NULL, " ");
    char *s    = strtok(NULL, " ");
    ChannelInfo *ci;
    NickInfo *ni;
    short level = 0, ulev;
    int i;
    int is_list = (cmd && stricmp(cmd, "LIST") == 0);
    ChanAccess *access;

    /* If LIST, we don't *require* any parameters, but we can take any.
     * If DEL, we require a nick and no level.
     * Else (ADD), we require a level (which implies a nick). */
    if (!cmd || (is_list ? 0 :
			(stricmp(cmd,"DEL")==0) ? (!nick || s) : !s)) {
	syntax_error(s_ChanServ, u, "ACCESS", CHAN_ACCESS_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (((is_list && !check_access(u, ci, CA_ACCESS_LIST))
                || (!is_list && !check_access(u, ci, CA_ACCESS_CHANGE)))
               && !is_services_admin(u))
    {
	notice_lang(s_ChanServ, u, ACCESS_DENIED);

    } else if (stricmp(cmd, "ADD") == 0) {

	if (readonly) {
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_DISABLED);
	    return;
	}

	level = atoi(s);
	ulev = get_access(u, ci);
	if (level >= ulev) {
	    notice_lang(s_ChanServ, u, PERMISSION_DENIED);
	    return;
	}
	if (level == 0) {
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_LEVEL_NONZERO);
	    return;
	} else if (level <= ACCESS_INVALID || level >= ACCESS_FOUNDER) {
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_LEVEL_RANGE,
			ACCESS_INVALID+1, ACCESS_FOUNDER-1);
	    return;
	}
	ni = findnick(nick);
	if (!ni) {
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_NICKS_ONLY);
	    return;
	}
	for (access = ci->access, i = 0; i < ci->accesscount; access++, i++) {
	    if (access->ni == ni) {
		/* Don't allow lowering from a level >= ulev */
		if (access->level >= ulev) {
		    notice_lang(s_ChanServ, u, PERMISSION_DENIED);
		    return;
		}
		if (access->level == level) {
		    notice_lang(s_ChanServ, u, CHAN_ACCESS_LEVEL_UNCHANGED,
			access->ni->nick, chan, level);
		    return;
		}
		access->level = level;
		notice_lang(s_ChanServ, u, CHAN_ACCESS_LEVEL_CHANGED,
			access->ni->nick, chan, level);
		return;
	    }
	}
	for (i = 0; i < ci->accesscount; i++) {
	    if (!ci->access[i].in_use)
		break;
	}
	if (i == ci->accesscount) {
	    if (i < CSAccessMax) {
		ci->accesscount++;
		ci->access =
		    srealloc(ci->access, sizeof(ChanAccess) * ci->accesscount);
	    } else {
		notice_lang(s_ChanServ, u, CHAN_ACCESS_REACHED_LIMIT,
			CSAccessMax);
		return;
	    }
	}
	access = &ci->access[i];
	access->ni = ni;
	access->in_use = 1;
	access->level = level;
	notice_lang(s_ChanServ, u, CHAN_ACCESS_ADDED,
		access->ni->nick, chan, level);

    } else if (stricmp(cmd, "DEL") == 0) {

	if (readonly) {
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_DISABLED);
	    return;
	}

	/* Special case: is it a number/list?  Only do search if it isn't. */
	if (isdigit(*nick) && strspn(nick, "1234567890,-") == strlen(nick)) {
	    int count, deleted, last = -1, perm = 0;
	    deleted = process_numlist(nick, &count, access_del_callback, u,
					ci, &last, &perm, get_access(u, ci));
	    if (!deleted) {
		if (perm) {
		    notice_lang(s_ChanServ, u, PERMISSION_DENIED);
		} else if (count == 1) {
		    notice_lang(s_ChanServ, u, CHAN_ACCESS_NO_SUCH_ENTRY,
				last, ci->name);
		} else {
		    notice_lang(s_ChanServ, u, CHAN_ACCESS_NO_MATCH, ci->name);
		}
	    } else if (deleted == 1) {
		notice_lang(s_ChanServ, u, CHAN_ACCESS_DELETED_ONE, ci->name);
	    } else {
		notice_lang(s_ChanServ, u, CHAN_ACCESS_DELETED_SEVERAL,
				deleted, ci->name);
	    }
	} else {
	    ni = findnick(nick);
	    if (!ni) {
		notice_lang(s_ChanServ, u, NICK_X_NOT_REGISTERED, nick);
		return;
	    }
	    for (i = 0; i < ci->accesscount; i++) {
		if (ci->access[i].ni == ni)
		    break;
	    }
	    if (i == ci->accesscount) {
		notice_lang(s_ChanServ, u, CHAN_ACCESS_NOT_FOUND, nick, chan);
		return;
	    }
	    access = &ci->access[i];
	    if (get_access(u, ci) <= access->level) {
		notice_lang(s_ChanServ, u, PERMISSION_DENIED);
	    } else {
		notice_lang(s_ChanServ, u, CHAN_ACCESS_DELETED,
				access->ni->nick, ci->name);
		access->ni = NULL;
		access->in_use = 0;
	    }
	}

    } else if (stricmp(cmd, "LIST") == 0) {
	int sent_header = 0;

	if (ci->accesscount == 0) {
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_LIST_EMPTY, chan);
	    return;
	}
	if (nick && strspn(nick, "1234567890,-") == strlen(nick)) {
	    process_numlist(nick, NULL, access_list_callback, u, ci,
								&sent_header);
	} else {
	    for (i = 0; i < ci->accesscount; i++) {
		if (nick && ci->access[i].ni
			 && !match_wild(nick, ci->access[i].ni->nick))
		    continue;
		access_list(u, i, ci, &sent_header);
	    }
	}
	if (!sent_header)
	    notice_lang(s_ChanServ, u, CHAN_ACCESS_NO_MATCH, chan);

    } else {
	syntax_error(s_ChanServ, u, "ACCESS", CHAN_ACCESS_SYNTAX);
    }
}

/*************************************************************************/

/* `last' is set to the last index this routine was called with */
static int akick_del(User *u, AutoKick *akick)
{
    if (!akick->in_use)
	return 0;
    if (akick->is_nick) {
	akick->u.ni = NULL;
    } else {
	free(akick->u.mask);
	akick->u.mask = NULL;
    }
    if (akick->reason) {
	free(akick->reason);
	akick->reason = NULL;
    }
    akick->in_use = akick->is_nick = 0;
    return 1;
}

static int akick_del_callback(User *u, int num, va_list args)
{
    ChannelInfo *ci = va_arg(args, ChannelInfo *);
    int *last = va_arg(args, int *);
    if (num < 1 || num > ci->akickcount)
	return 0;
    *last = num;
    return akick_del(u, &ci->akick[num-1]);
}


static int akick_list(User *u, int index, ChannelInfo *ci, int *sent_header)
{
    AutoKick *akick = &ci->akick[index];
    char buf[BUFSIZE], buf2[BUFSIZE];

    if (!akick->in_use)
	return 0;
    if (!*sent_header) {
	notice_lang(s_ChanServ, u, CHAN_AKICK_LIST_HEADER, ci->name);
	*sent_header = 1;
    }
    if (akick->is_nick) {
	if (akick->u.ni->flags & NI_HIDE_MASK)
	    strscpy(buf, akick->u.ni->nick, sizeof(buf));
	else
	    snprintf(buf, sizeof(buf), "%s (%s)",
			akick->u.ni->nick, akick->u.ni->last_usermask);
    } else {
	strscpy(buf, akick->u.mask, sizeof(buf));
    }
    if (akick->reason)
	snprintf(buf2, sizeof(buf2), " (%s)", akick->reason);
    else
	*buf2 = 0;
    notice_lang(s_ChanServ, u, CHAN_AKICK_LIST_FORMAT, index+1, buf, buf2);
    return 1;
}

static int akick_list_callback(User *u, int num, va_list args)
{
    ChannelInfo *ci = va_arg(args, ChannelInfo *);
    int *sent_header = va_arg(args, int *);
    if (num < 1 || num > ci->akickcount)
	return 0;
    return akick_list(u, num-1, ci, sent_header);
}


static void do_akick(User *u)
{
    char *chan   = strtok(NULL, " ");
    char *cmd    = strtok(NULL, " ");
    char *mask   = strtok(NULL, " ");
    char *reason = strtok(NULL, "");
    ChannelInfo *ci;
    int i;
    AutoKick *akick;

    if (!cmd || (!mask && 
		(stricmp(cmd, "ADD") == 0 || stricmp(cmd, "DEL") == 0))) {
	syntax_error(s_ChanServ, u, "AKICK", CHAN_AKICK_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!check_access(u, ci, CA_AKICK) && !is_services_admin(u)) {
	if (ci->founder && getlink(ci->founder) == u->ni)
	    notice_lang(s_ChanServ, u, CHAN_IDENTIFY_REQUIRED, s_ChanServ,chan);
	else
	    notice_lang(s_ChanServ, u, ACCESS_DENIED);

    } else if (stricmp(cmd, "ADD") == 0) {

	NickInfo *ni = findnick(mask);
	char *nick, *user, *host;

	if (readonly) {
	    notice_lang(s_ChanServ, u, CHAN_AKICK_DISABLED);
	    return;
	}

	if (!ni) {
	    split_usermask(mask, &nick, &user, &host);
	    mask = smalloc(strlen(nick)+strlen(user)+strlen(host)+3);
	    sprintf(mask, "%s!%s@%s", nick, user, host);
	    free(nick);
	    free(user);
	    free(host);
	}

	for (akick = ci->akick, i = 0; i < ci->akickcount; akick++, i++) {
	    if (!akick->in_use)
		continue;
	    if (akick->is_nick ? akick->u.ni == ni
	                       : stricmp(akick->u.mask,mask) == 0) {
		notice_lang(s_ChanServ, u, CHAN_AKICK_ALREADY_EXISTS,
			akick->is_nick ? akick->u.ni->nick : akick->u.mask,
			chan);
		return;
	    }
	}

	for (i = 0; i < ci->akickcount; i++) {
	    if (!ci->akick[i].in_use)
		break;
	}
	if (i == ci->akickcount) {
	    if (ci->akickcount >= CSAutokickMax) {
		notice_lang(s_ChanServ, u, CHAN_AKICK_REACHED_LIMIT,
			CSAutokickMax);
		return;
	    }
	    ci->akickcount++;
	    ci->akick = srealloc(ci->akick, sizeof(AutoKick) * ci->akickcount);
	}
	akick = &ci->akick[i];
	akick->in_use = 1;
	if (ni) {
	    akick->is_nick = 1;
	    akick->u.ni = ni;
	} else {
	    akick->is_nick = 0;
	    akick->u.mask = mask;
	}
	if (reason)
	    akick->reason = sstrdup(reason);
	else
	    akick->reason = NULL;
	notice_lang(s_ChanServ, u, CHAN_AKICK_ADDED, mask, chan);

    } else if (stricmp(cmd, "DEL") == 0) {

	if (readonly) {
	    notice_lang(s_ChanServ, u, CHAN_AKICK_DISABLED);
	    return;
	}

	/* Special case: is it a number/list?  Only do search if it isn't. */
	if (isdigit(*mask) && strspn(mask, "1234567890,-") == strlen(mask)) {
	    int count, deleted, last = -1;
	    deleted = process_numlist(mask, &count, akick_del_callback, u,
					ci, &last);
	    if (!deleted) {
		if (count == 1) {
		    notice_lang(s_ChanServ, u, CHAN_AKICK_NO_SUCH_ENTRY,
				last, ci->name);
		} else {
		    notice_lang(s_ChanServ, u, CHAN_AKICK_NO_MATCH, ci->name);
		}
	    } else if (deleted == 1) {
		notice_lang(s_ChanServ, u, CHAN_AKICK_DELETED_ONE, ci->name);
	    } else {
		notice_lang(s_ChanServ, u, CHAN_AKICK_DELETED_SEVERAL,
				deleted, ci->name);
	    }
	} else {
	    NickInfo *ni = findnick(mask);

	    for (akick = ci->akick, i = 0; i < ci->akickcount; akick++, i++) {
		if (!akick->in_use)
		    continue;
		if ((akick->is_nick && akick->u.ni == ni)
		 || (!akick->is_nick && stricmp(akick->u.mask, mask) == 0))
		    break;
	    }
	    if (i == ci->akickcount) {
		notice_lang(s_ChanServ, u, CHAN_AKICK_NOT_FOUND, mask, chan);
		return;
	    }
	    notice_lang(s_ChanServ, u, CHAN_AKICK_DELETED, mask, chan);
	    akick_del(u, akick);
	}

    } else if (stricmp(cmd, "LIST") == 0) {
	int sent_header = 0;

	if (ci->akickcount == 0) {
	    notice_lang(s_ChanServ, u, CHAN_AKICK_LIST_EMPTY, chan);
	    return;
	}
	if (mask && isdigit(*mask) &&
			strspn(mask, "1234567890,-") == strlen(mask)) {
	    process_numlist(mask, NULL, akick_list_callback, u, ci,
								&sent_header);
	} else {
	    for (akick = ci->akick, i = 0; i < ci->akickcount; akick++, i++) {
		if (!akick->in_use)
		    continue;
		if (mask) {
		    if (!akick->is_nick && !match_wild(mask, akick->u.mask))
			continue;
		    if (akick->is_nick && !match_wild(mask, akick->u.ni->nick))
			continue;
		}
		akick_list(u, i, ci, &sent_header);
	    }
	}
	if (!sent_header)
	    notice_lang(s_ChanServ, u, CHAN_AKICK_NO_MATCH, chan);

    } else if (stricmp(cmd, "ENFORCE") == 0) {
	Channel *c = findchan(ci->name);
	struct c_userlist *cu = NULL;
	struct c_userlist *next;
	char *argv[3];
	int i;
	int count = 0;

	if (!c) {
	    notice_lang(s_ChanServ, u, CHAN_X_NOT_IN_USE, ci->name);
	    return;
	}

	for (i = 0; i < 3; i++) {
	    switch (i) {
		case 0: cu = c->chanops; break;
		case 1: cu = c->voices; break;
		case 2: cu = c->users; break;
	    }
		    
	    while (cu) {
		next = cu->next;
		if (check_kick(cu->user, c->name)) {
		    argv[0] = sstrdup(c->name);
		    argv[1] = sstrdup(cu->user->nick);
		    argv[2] = sstrdup(CSAutokickReason);

		    do_kick(s_ChanServ, 3, argv);

		    free(argv[2]);
		    free(argv[1]);
		    free(argv[0]);

		    count++;
		}
		cu = next;
	    }
	}

	notice_lang(s_ChanServ, u, CHAN_AKICK_ENFORCE_DONE, chan, count);

    } else {
	syntax_error(s_ChanServ, u, "AKICK", CHAN_AKICK_SYNTAX);
    }
}

/*************************************************************************/

static void do_levels(User *u)
{
    char *chan = strtok(NULL, " ");
    char *cmd  = strtok(NULL, " ");
    char *what = strtok(NULL, " ");
    char *s    = strtok(NULL, " ");
    ChannelInfo *ci;
    short level;
    int i;

    /* If SET, we want two extra parameters; if DIS[ABLE], we want only
     * one; else, we want none.
     */
    if (!cmd || ((stricmp(cmd,"SET")==0) ? !s :
			(strnicmp(cmd,"DIS",3)==0) ? (!what || s) : !!what)) {
	syntax_error(s_ChanServ, u, "LEVELS", CHAN_LEVELS_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!is_founder(u, ci) && !is_services_admin(u)) {
	notice_lang(s_ChanServ, u, ACCESS_DENIED);

    } else if (stricmp(cmd, "SET") == 0) {
	level = atoi(s);
	if (level <= ACCESS_INVALID || level >= ACCESS_FOUNDER) {
	    notice_lang(s_ChanServ, u, CHAN_LEVELS_RANGE,
			ACCESS_INVALID+1, ACCESS_FOUNDER-1);
	    return;
	}
	for (i = 0; levelinfo[i].what >= 0; i++) {
	    if (stricmp(levelinfo[i].name, what) == 0) {
		ci->levels[levelinfo[i].what] = level;
		notice_lang(s_ChanServ, u, CHAN_LEVELS_CHANGED,
			levelinfo[i].name, chan, level);
		return;
	    }
	}
	notice_lang(s_ChanServ, u, CHAN_LEVELS_UNKNOWN, what, s_ChanServ);

    } else if (stricmp(cmd, "DIS") == 0 || stricmp(cmd, "DISABLE") == 0) {
	for (i = 0; levelinfo[i].what >= 0; i++) {
	    if (stricmp(levelinfo[i].name, what) == 0) {
		ci->levels[levelinfo[i].what] = ACCESS_INVALID;
		notice_lang(s_ChanServ, u, CHAN_LEVELS_DISABLED,
			levelinfo[i].name, chan);
		return;
	    }
	}
	notice_lang(s_ChanServ, u, CHAN_LEVELS_UNKNOWN, what, s_ChanServ);

    } else if (stricmp(cmd, "LIST") == 0) {
	int i;
	notice_lang(s_ChanServ, u, CHAN_LEVELS_LIST_HEADER, chan);
	if (!levelinfo_maxwidth) {
	    for (i = 0; levelinfo[i].what >= 0; i++) {
		int len = strlen(levelinfo[i].name);
		if (len > levelinfo_maxwidth)
		    levelinfo_maxwidth = len;
	    }
	}
	for (i = 0; levelinfo[i].what >= 0; i++) {
	    int j = ci->levels[levelinfo[i].what];
	    if (j == ACCESS_INVALID) {
		j = levelinfo[i].what;
		if (j == CA_AUTOOP || j == CA_AUTODEOP
				|| j == CA_AUTOVOICE || j == CA_NOJOIN)
		{
		    notice_lang(s_ChanServ, u, CHAN_LEVELS_LIST_DISABLED,
				levelinfo_maxwidth, levelinfo[i].name);
		} else {
		    notice_lang(s_ChanServ, u, CHAN_LEVELS_LIST_DISABLED,
				levelinfo_maxwidth, levelinfo[i].name);
		}
	    } else {
		notice_lang(s_ChanServ, u, CHAN_LEVELS_LIST_NORMAL,
				levelinfo_maxwidth, levelinfo[i].name, j);
	    }
	}

    } else if (stricmp(cmd, "RESET") == 0) {
	reset_levels(ci);
	notice_lang(s_ChanServ, u, CHAN_LEVELS_RESET, chan);

    } else {
	syntax_error(s_ChanServ, u, "LEVELS", CHAN_LEVELS_SYNTAX);
    }
}

/*************************************************************************/

/* SADMINS and users, who have identified for a channel, can now cause it's
 * Enstry Message and Successor to be displayed by supplying the ALL parameter.
 * Syntax: INFO channel [ALL]
 * -TheShadow (29 Mar 1999)
 */

static void do_info(User *u)
{
    char *chan = strtok(NULL, " ");
    char *param = strtok(NULL, " ");
    ChannelInfo *ci;
    NickInfo *ni;
    char buf[BUFSIZE], *end;
    struct tm *tm;
    int need_comma = 0;
    const char *commastr = getstring(u->ni, COMMA_SPACE);
    int is_servadmin = is_services_admin(u);
    int show_all = 0;

    if (!chan) {
        syntax_error(s_ChanServ, u, "INFO", CHAN_INFO_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
        notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
        notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!ci->founder) {
        /* Paranoia... this shouldn't be able to happen */
        delchan(ci);
        notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else {

        /* Should we show all fields? Only for sadmins and identified users */
        if (param && stricmp(param, "ALL") == 0 && 
	    				(is_identified(u, ci) || is_servadmin))
            show_all = 1;

        notice_lang(s_ChanServ, u, CHAN_INFO_HEADER, chan);
        ni = ci->founder;
        if (ni->last_usermask && (is_servadmin || !(ni->flags & NI_HIDE_MASK)))
        {
            notice_lang(s_ChanServ, u, CHAN_INFO_FOUNDER, ni->nick,
                        ni->last_usermask);
        } else {
            notice_lang(s_ChanServ, u, CHAN_INFO_NO_FOUNDER, ni->nick);
        }

	if (show_all) {
	    ni = ci->successor;
	    if (ni) {
		if (ni->last_usermask && (is_servadmin ||
				!(ni->flags & NI_HIDE_MASK))) {
		    notice_lang(s_ChanServ, u, CHAN_INFO_SUCCESSOR, ni->nick, 
				ni->last_usermask);
		} else {
		    notice_lang(s_ChanServ, u, CHAN_INFO_NO_SUCCESSOR,
				ni->nick);
		}
	    }
	}

	notice_lang(s_ChanServ, u, CHAN_INFO_DESCRIPTION, ci->desc);
	tm = localtime(&ci->time_registered);
	strftime_lang(buf, sizeof(buf), u, STRFTIME_DATE_TIME_FORMAT, tm);
	notice_lang(s_ChanServ, u, CHAN_INFO_TIME_REGGED, buf);
	tm = localtime(&ci->last_used);
	strftime_lang(buf, sizeof(buf), u, STRFTIME_DATE_TIME_FORMAT, tm);
	notice_lang(s_ChanServ, u, CHAN_INFO_LAST_USED, buf);
	if (ci->last_topic) {
	    notice_lang(s_ChanServ, u, CHAN_INFO_LAST_TOPIC, ci->last_topic);
	    notice_lang(s_ChanServ, u, CHAN_INFO_TOPIC_SET_BY,
			ci->last_topic_setter);
	}

	if (ci->entry_message && show_all)
	    notice_lang(s_ChanServ, u, CHAN_INFO_ENTRYMSG, ci->entry_message);
	if (ci->url)
	    notice_lang(s_ChanServ, u, CHAN_INFO_URL, ci->url);
	if (ci->email)
	    notice_lang(s_ChanServ, u, CHAN_INFO_EMAIL, ci->email);
	end = buf;
	*end = 0;
	if (ci->flags & CI_PRIVATE) {
	    end += snprintf(end, sizeof(buf)-(end-buf), "%s",
			getstring(u->ni, CHAN_INFO_OPT_PRIVATE));
	    need_comma = 1;
	}
	if (ci->flags & CI_KEEPTOPIC) {
	    end += snprintf(end, sizeof(buf)-(end-buf), "%s%s",
			need_comma ? commastr : "",
			getstring(u->ni, CHAN_INFO_OPT_KEEPTOPIC));
	    need_comma = 1;
	}
	if (ci->flags & CI_TOPICLOCK) {
	    end += snprintf(end, sizeof(buf)-(end-buf), "%s%s",
			need_comma ? commastr : "",
			getstring(u->ni, CHAN_INFO_OPT_TOPICLOCK));
	    need_comma = 1;
	}
	if (ci->flags & CI_SECUREOPS) {
	    end += snprintf(end, sizeof(buf)-(end-buf), "%s%s",
			need_comma ? commastr : "",
			getstring(u->ni, CHAN_INFO_OPT_SECUREOPS));
	    need_comma = 1;
	}
	if (ci->flags & CI_LEAVEOPS) {
	    end += snprintf(end, sizeof(buf)-(end-buf), "%s%s",
			need_comma ? commastr : "",
			getstring(u->ni, CHAN_INFO_OPT_LEAVEOPS));
	    need_comma = 1;
	}
	if (ci->flags & CI_RESTRICTED) {
	    end += snprintf(end, sizeof(buf)-(end-buf), "%s%s",
			need_comma ? commastr : "",
			getstring(u->ni, CHAN_INFO_OPT_RESTRICTED));
	    need_comma = 1;
	}
	if (ci->flags & CI_SECURE) {
	    end += snprintf(end, sizeof(buf)-(end-buf), "%s%s",
			need_comma ? commastr : "",
			getstring(u->ni, CHAN_INFO_OPT_SECURE));
	    need_comma = 1;
	}
	notice_lang(s_ChanServ, u, CHAN_INFO_OPTIONS,
		*buf ? buf : getstring(u->ni, CHAN_INFO_OPT_NONE));
	end = buf;
	*end = 0;
	if (ci->mlock_on || ci->mlock_key || ci->mlock_limit)
	    end += snprintf(end, sizeof(buf)-(end-buf), "+%s%s%s%s%s%s%s%s%s",
				(ci->mlock_on & CMODE_I) ? "i" : "",
				(ci->mlock_key         ) ? "k" : "",
				(ci->mlock_limit       ) ? "l" : "",
				(ci->mlock_on & CMODE_M) ? "m" : "",
				(ci->mlock_on & CMODE_N) ? "n" : "",
				(ci->mlock_on & CMODE_P) ? "p" : "",
				(ci->mlock_on & CMODE_S) ? "s" : "",
				(ci->mlock_on & CMODE_T) ? "t" : "",
#ifdef IRC_DAL4_4_15
	    			(ci->mlock_on & CMODE_R) ? "R" : "");
#else
	    			"");
#endif
	if (ci->mlock_off)
	    end += snprintf(end, sizeof(buf)-(end-buf), "-%s%s%s%s%s%s%s%s%s",
				(ci->mlock_off & CMODE_I) ? "i" : "",
				(ci->mlock_off & CMODE_K) ? "k" : "",
				(ci->mlock_off & CMODE_L) ? "l" : "",
				(ci->mlock_off & CMODE_M) ? "m" : "",
				(ci->mlock_off & CMODE_N) ? "n" : "",
				(ci->mlock_off & CMODE_P) ? "p" : "",
				(ci->mlock_off & CMODE_S) ? "s" : "",
				(ci->mlock_off & CMODE_T) ? "t" : "",
#ifdef IRC_DAL4_4_15
	    			(ci->mlock_off & CMODE_R) ? "R" : "");
#else
	    			"");
#endif
	if (*buf)
	    notice_lang(s_ChanServ, u, CHAN_INFO_MODE_LOCK, buf);

        if ((ci->flags & CI_NO_EXPIRE) && show_all)
	                notice_lang(s_ChanServ, u, CHAN_INFO_NO_EXPIRE);
    }
}

/*************************************************************************/

static void do_list(User *u)
{
    char *pattern = strtok(NULL, " ");
    ChannelInfo *ci;
    int nchans, i;
    char buf[BUFSIZE];
    int is_servadmin = is_services_admin(u);

    if (CSListOpersOnly && (!u || !(u->mode & UMODE_O))) {
	notice_lang(s_ChanServ, u, PERMISSION_DENIED);
	return;
    }

    if (!pattern) {
	syntax_error(s_ChanServ, u, "LIST", CHAN_LIST_SYNTAX);
    } else {
	nchans = 0;
	notice_lang(s_ChanServ, u, CHAN_LIST_HEADER, pattern);
	for (i = 0; i < 256; i++) {
	    for (ci = chanlists[i]; ci; ci = ci->next) {
		if (!is_servadmin & (ci->flags & CI_VERBOTEN))
		    continue;
		snprintf(buf, sizeof(buf), "%-20s  %s", ci->name,
						ci->desc ? ci->desc : "");
		if (stricmp(pattern, ci->name) == 0 ||
					match_wild_nocase(pattern, buf)) {
		    if (++nchans <= CSListMax) {
			char noexpire_char = ' ';
			if (is_servadmin && (ci->flags & CI_NO_EXPIRE))
			    noexpire_char = '!';
			notice(s_ChanServ, u->nick, "  %c%s",
						noexpire_char, buf);
		    }
		}
	    }
	}
	notice_lang(s_ChanServ, u, CHAN_LIST_END,
			nchans>CSListMax ? CSListMax : nchans, nchans);
    }

}

/*************************************************************************/

static void do_invite(User *u)
{
    char *chan = strtok(NULL, " ");
    Channel *c;
    ChannelInfo *ci;

    if (!chan) {
	syntax_error(s_ChanServ, u, "INVITE", CHAN_INVITE_SYNTAX);
    } else if (!(c = findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (!(ci = c->ci)) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!u || !check_access(u, ci, CA_INVITE)) {
	notice_lang(s_ChanServ, u, PERMISSION_DENIED);
    } else {
	send_cmd(s_ChanServ, "INVITE %s %s", u->nick, chan);
    }
}

/*************************************************************************/

static void do_op(User *u)
{
    char *chan = strtok(NULL, " ");
    char *op_params = strtok(NULL, " ");  
    Channel *c;
    ChannelInfo *ci;

    if (!chan || !op_params) {
	syntax_error(s_ChanServ, u, "OP", CHAN_OP_SYNTAX);
    } else if (!(c = findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (!(ci = c->ci)) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!u || !check_access(u, ci, CA_OPDEOP)) {
	notice_lang(s_ChanServ, u, PERMISSION_DENIED);
    } else {
	char *av[3];
	send_cmd(MODE_SENDER(s_ChanServ), "MODE %s +o %s", chan, op_params);
	av[0] = chan;
	av[1] = sstrdup("+o");
	av[2] = op_params;
	do_cmode(s_ChanServ, 3, av);
	free(av[1]);
	if (ci->flags & CI_OPNOTICE) {
	    char buf[NICKMAX*2+32];
	    snprintf(buf, sizeof(buf), "OP command used for %s by %s",
			op_params, u->nick);
	    notice(s_ChanServ, chan, buf);
	}
    }
}

/*************************************************************************/

static void do_deop(User *u)
{
    char *chan = strtok(NULL, " ");
    char *deop_params = strtok(NULL, " ");
    Channel *c;
    ChannelInfo *ci;

    if (!chan || !deop_params) {
	syntax_error(s_ChanServ, u, "DEOP", CHAN_DEOP_SYNTAX);
    } else if (!(c = findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (!(ci = c->ci)) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!u || !check_access(u, ci, CA_OPDEOP)) {
	notice_lang(s_ChanServ, u, PERMISSION_DENIED);
    } else {
	char *av[3];
	send_cmd(MODE_SENDER(s_ChanServ), "MODE %s -o %s", chan, deop_params);
	av[0] = chan;
	av[1] = sstrdup("-o");
	av[2] = deop_params;
	do_cmode(s_ChanServ, 3, av);
	free(av[1]);
	if (ci->flags & CI_OPNOTICE) {
	    char buf[NICKMAX*2+32];
	    snprintf(buf, sizeof(buf), "DEOP command used for %s by %s",
			deop_params, u->nick);
	    notice(s_ChanServ, chan, buf);
	}
    }
}

/*************************************************************************/

static void do_unban(User *u)
{
    char *chan = strtok(NULL, " ");
    Channel *c;
    ChannelInfo *ci;
    int i;
    char *av[3];

    if (!chan) {
	syntax_error(s_ChanServ, u, "UNBAN", CHAN_UNBAN_SYNTAX);
    } else if (!(c = findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (!(ci = c->ci)) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!u || !check_access(u, ci, CA_UNBAN)) {
	notice_lang(s_ChanServ, u, PERMISSION_DENIED);
    } else {
	/* Save original ban info */
	int count = c->bancount;
	char **bans = smalloc(sizeof(char *) * count);
	memcpy(bans, c->bans, sizeof(char *) * count);

	av[0] = chan;
	av[1] = sstrdup("-b");
	for (i = 0; i < count; i++) {
	    if (match_usermask(bans[i], u)) {
		send_cmd(MODE_SENDER(s_ChanServ), "MODE %s -b %s",
			chan, bans[i]);
		av[2] = sstrdup(bans[i]);
		do_cmode(s_ChanServ, 3, av);
		free(av[2]);
	    }
	}
	free(av[1]);
	notice_lang(s_ChanServ, u, CHAN_UNBANNED, chan);
	free(bans);
    }
}

/*************************************************************************/

static void do_clear(User *u)
{
    char *chan = strtok(NULL, " ");
    char *what = strtok(NULL, " ");
    Channel *c;
    ChannelInfo *ci;

    if (!what) {
	syntax_error(s_ChanServ, u, "CLEAR", CHAN_CLEAR_SYNTAX);
    } else if (!(c = findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (!(ci = c->ci)) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else if (!u || !check_access(u, ci, CA_CLEAR)) {
	notice_lang(s_ChanServ, u, PERMISSION_DENIED);
    } else if (stricmp(what, "bans") == 0) {
	char *av[3];
	int i;

	/* Save original ban info */
	int count = c->bancount;
	char **bans = smalloc(sizeof(char *) * count);
	for (i = 0; i < count; i++)
	    bans[i] = sstrdup(c->bans[i]);

	for (i = 0; i < count; i++) {
	    av[0] = sstrdup(chan);
	    av[1] = sstrdup("-b");
	    av[2] = bans[i];
	    send_cmd(MODE_SENDER(s_ChanServ), "MODE %s %s :%s",
			av[0], av[1], av[2]);
	    do_cmode(s_ChanServ, 3, av);
	    free(av[2]);
	    free(av[1]);
	    free(av[0]);
	}
	notice_lang(s_ChanServ, u, CHAN_CLEARED_BANS, chan);
	free(bans);
    } else if (stricmp(what, "modes") == 0) {
	char *av[3];

	av[0] = chan;
	av[1] = sstrdup("-mintpslk");
	if (c->key)
	    av[2] = sstrdup(c->key);
	else
	    av[2] = sstrdup("");
	send_cmd(MODE_SENDER(s_ChanServ), "MODE %s %s :%s",
			av[0], av[1], av[2]);
	do_cmode(s_ChanServ, 3, av);
	free(av[2]);
	free(av[1]);
	check_modes(chan);
	notice_lang(s_ChanServ, u, CHAN_CLEARED_MODES, chan);
    } else if (stricmp(what, "ops") == 0) {
	char *av[3];
	struct c_userlist *cu, *next;

	for (cu = c->chanops; cu; cu = next) {
	    next = cu->next;
	    av[0] = sstrdup(chan);
	    av[1] = sstrdup("-o");
	    av[2] = sstrdup(cu->user->nick);
	    send_cmd(MODE_SENDER(s_ChanServ), "MODE %s %s :%s",
			av[0], av[1], av[2]);
	    do_cmode(s_ChanServ, 3, av);
	    free(av[2]);
	    free(av[1]);
	    free(av[0]);
	}
	notice_lang(s_ChanServ, u, CHAN_CLEARED_OPS, chan);
    } else if (stricmp(what, "voices") == 0) {
	char *av[3];
	struct c_userlist *cu, *next;

	for (cu = c->voices; cu; cu = next) {
	    next = cu->next;
	    av[0] = sstrdup(chan);
	    av[1] = sstrdup("-v");
	    av[2] = sstrdup(cu->user->nick);
	    send_cmd(MODE_SENDER(s_ChanServ), "MODE %s %s :%s",
			av[0], av[1], av[2]);
	    do_cmode(s_ChanServ, 3, av);
	    free(av[2]);
	    free(av[1]);
	    free(av[0]);
	}
	notice_lang(s_ChanServ, u, CHAN_CLEARED_VOICES, chan);
    } else if (stricmp(what, "users") == 0) {
	char *av[3];
	struct c_userlist *cu, *next;
	char buf[256];

	snprintf(buf, sizeof(buf), "CLEAR USERS command from %s", u->nick);

	for (cu = c->users; cu; cu = next) {
	    next = cu->next;
	    av[0] = sstrdup(chan);
	    av[1] = sstrdup(cu->user->nick);
	    av[2] = sstrdup(buf);
	    send_cmd(MODE_SENDER(s_ChanServ), "KICK %s %s :%s",
			av[0], av[1], av[2]);
	    do_kick(s_ChanServ, 3, av);
	    free(av[2]);
	    free(av[1]);
	    free(av[0]);
	}
	notice_lang(s_ChanServ, u, CHAN_CLEARED_USERS, chan);
    } else {
	syntax_error(s_ChanServ, u, "CLEAR", CHAN_CLEAR_SYNTAX);
    }
}

/*************************************************************************/

static void do_getpass(User *u)
{
#ifndef USE_ENCRYPTION
    char *chan = strtok(NULL, " ");
    ChannelInfo *ci;
#endif

    /* Assumes that permission checking has already been done. */
#ifdef USE_ENCRYPTION
    notice_lang(s_ChanServ, u, CHAN_GETPASS_UNAVAILABLE);
#else
    if (!chan) {
	syntax_error(s_ChanServ, u, "GETPASS", CHAN_GETPASS_SYNTAX);
    } else if (!(ci = cs_findchan(chan))) {
	notice_lang(s_ChanServ, u, CHAN_X_NOT_REGISTERED, chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice_lang(s_ChanServ, u, CHAN_X_FORBIDDEN, chan);
    } else {
	log("%s: %s!%s@%s used GETPASS on %s",
		s_ChanServ, u->nick, u->username, u->host, ci->name);
	if (WallGetpass) {
	    wallops(s_ChanServ, "\2%s\2 used GETPASS on channel \2%s\2",
		u->nick, chan);
	}
	notice_lang(s_ChanServ, u, CHAN_GETPASS_PASSWORD_IS,
		chan, ci->founderpass);
    }
#endif
}

/*************************************************************************/

static void do_forbid(User *u)
{
    ChannelInfo *ci;
    char *chan = strtok(NULL, " ");

    /* Assumes that permission checking has already been done. */
    if (!chan) {
	syntax_error(s_ChanServ, u, "FORBID", CHAN_FORBID_SYNTAX);
	return;
    }
    if (readonly)
	notice_lang(s_ChanServ, u, READ_ONLY_MODE);
    if ((ci = cs_findchan(chan)) != NULL)
	delchan(ci);
    ci = makechan(chan);
    if (ci) {
	log("%s: %s set FORBID for channel %s", s_ChanServ, u->nick,
		ci->name);
	ci->flags |= CI_VERBOTEN;
	notice_lang(s_ChanServ, u, CHAN_FORBID_SUCCEEDED, chan);
    } else {
	log("%s: Valid FORBID for %s by %s failed", s_ChanServ, ci->name,
		u->nick);
	notice_lang(s_ChanServ, u, CHAN_FORBID_FAILED, chan);
    }
}

/*************************************************************************/

static void do_status(User *u)
{
    ChannelInfo *ci;
    User *u2;
    char *nick, *chan;

    chan = strtok(NULL, " ");
    nick = strtok(NULL, " ");
    if (!nick || strtok(NULL, " ")) {
	notice(s_ChanServ, u->nick, "STATUS ERROR Syntax error");
	return;
    }
    if (!(ci = cs_findchan(chan))) {
	char *temp = chan;
	chan = nick;
	nick = temp;
	ci = cs_findchan(chan);
    }
    if (!ci) {
	notice(s_ChanServ, u->nick, "STATUS ERROR Channel %s not registered",
		chan);
    } else if (ci->flags & CI_VERBOTEN) {
	notice(s_ChanServ, u->nick, "STATUS ERROR Channel %s forbidden", chan);
	return;
    } else if ((u2 = finduser(nick)) != NULL) {
	notice(s_ChanServ, u->nick, "STATUS %s %s %d",
		chan, nick, get_access(u2, ci));
    } else { /* !u2 */
	notice(s_ChanServ, u->nick, "STATUS ERROR Nick %s not online", nick);
    }
}

/*************************************************************************/

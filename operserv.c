/* OperServ functions.
 *
 * Services is copyright (c) 1996-1999 Andrew Church.
 *     E-mail: <achurch@dragonfire.net>
 * Services is copyright (c) 1999-2000 Andrew Kempe.
 *     E-mail: <theshadow@shadowfire.org>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#include "services.h"
#include "pseudo.h"

/*************************************************************************/

/* Services admin list */
static NickInfo *services_admins[MAX_SERVADMINS];

/* Services operator list */
static NickInfo *services_opers[MAX_SERVOPERS];


/************************************************************************/

static void do_help(User *u);
static void do_credits(User *u);
static void do_global(User *u);
static void do_globaln(User *u);
static void do_stats(User *u);
static void do_admin(User *u);
static void do_oper(User *u);
static void do_getkey(User *u);
static void do_os_op(User *u);
static void do_os_deop(User *u);
static void do_os_mode(User *u);
static void do_clearmodes(User *u);
static void do_os_kick(User *u);
static void do_apodera(User *u);
static void do_limpia(User *u);
static void do_os_kill(User *u);
static void do_block(User *u);
static void do_unblock(User *u);
static void do_set(User *u);
static void do_settime(User *u);
static void do_jupe(User *u);
static void do_raw(User *u);
static void do_update(User *u);
static void do_os_quit(User *u);
static void do_shutdown(User *u);
static void do_restart(User *u);
static void do_listignore(User *u);
static void do_killclones(User *u);

#ifdef DEBUG_COMMANDS
static void do_matchwild(User *u);
#endif

/*************************************************************************/

static Command cmds[] = {
    { "AYUDA",      do_help,       NULL,  -1,                   -1,-1,-1,-1 },
    { "HELP",       do_help,       NULL,  -1,                   -1,-1,-1,-1 },
    { "?",          do_help,       NULL,  -1,                   -1,-1,-1,-1 },
    { ":?",         do_help,       NULL,  -1,                   -1,-1,-1,-1 },    
    { "CREDITOS",   do_credits,    NULL,  SERVICES_CREDITS_TERRA, -1,-1,-1,-1 },
    { "CREDITS",    do_credits,    NULL,  SERVICES_CREDITS_TERRA, -1,-1,-1,-1 },
    { "SERVIDORES", do_servers,    NULL,  -1,                   -1,-1,-1,-1 },
    { "SERVERS",    do_servers,    NULL,  -1,                   -1,-1,-1,-1 },
    { "STATS",      do_stats,      NULL,  OPER_HELP_STATS,      -1,-1,-1,-1 },
    { "UPTIME",     do_stats,      NULL,  OPER_HELP_STATS,      -1,-1,-1,-1 },

    /* Anyone can use the LIST option to the ADMIN and OPER commands; those
     * routines check privileges to ensure that only authorized users
     * modify the list. */
    { "ADMIN",      do_admin,      NULL,  OPER_HELP_ADMIN,      -1,-1,-1,-1 },
    { "OPER",       do_oper,       NULL,  OPER_HELP_OPER,       -1,-1,-1,-1 },
    /* Similarly, anyone can use *NEWS LIST, but *NEWS {ADD,DEL} are
     * reserved for Services admins. */
    { "LOGONNEWS",  do_logonnews,  NULL,  NEWS_HELP_LOGON,      -1,-1,-1,-1 },
    { "OPERNEWS",   do_opernews,   NULL,  NEWS_HELP_OPER,       -1,-1,-1,-1 },

    /* Commands for Services opers: */
    { "GETKEY",     do_getkey,     is_services_oper,
        OPER_HELP_GETKEY, -1,-1,-1,-1},
    { "OP",         do_os_op,      is_services_oper,
        OPER_HELP_OP, -1,-1,-1,-1},
    { "DEOP",       do_os_deop,    is_services_oper,
        OPER_HELP_DEOP, -1,-1,-1,-1},
    { "MODE",       do_os_mode,    is_services_oper,
	OPER_HELP_MODE, -1,-1,-1,-1 },
    { "CLEARMODES", do_clearmodes, is_services_oper,
	OPER_HELP_CLEARMODES, -1,-1,-1,-1 },
    { "KICK",       do_os_kick,    is_services_oper,
	OPER_HELP_KICK, -1,-1,-1,-1 },
    { "KILL",      do_os_kill,     is_services_oper,
        OPER_HELP_KILL, -1,-1,-1,-1},
    { "BLOCK",      do_block,      is_services_oper,
        OPER_HELP_BLOCK, -1,-1,-1,-1},
    { "UNBLOCK",    do_unblock,    is_services_oper,
        OPER_HELP_UNBLOCK, -1,-1,-1,-1},
    { "UNGLINE",    do_unblock,    is_services_oper,
        OPER_HELP_UNBLOCK, -1,-1,-1,-1},
    { "LIMPIA",     do_limpia,     is_services_oper,
        OPER_HELP_LIMPIA, -1,-1,-1,-1},
    { "APODERA",    do_apodera,    is_services_oper,
        OPER_HELP_APODERA, -1,-1,-1,-1},
    { "GLINE",      do_akill,      is_services_admin,
        OPER_HELP_AKILL,-1,-1,-1,-1},
    { "AKILL",      do_akill,      is_services_admin,
	OPER_HELP_AKILL, -1,-1,-1,-1 },

    /* Commands for Services admins: */
    { "GLOBAL",     do_global,     is_services_admin,
        OPER_HELP_GLOBAL,     -1,-1,-1,-1 },
    { "GLOBALN",    do_globaln,    is_services_admin,
        OPER_HELP_GLOBALN,     -1,-1,-1,-1 },
    { "SET",        do_set,        is_services_admin,
	OPER_HELP_SET, -1,-1,-1,-1 },
    { "SET READONLY",0,0,  OPER_HELP_SET_READONLY, -1,-1,-1,-1 },
    { "SET DEBUG",0,0,     OPER_HELP_SET_DEBUG, -1,-1,-1,-1 },
     { "SETTIME",    do_settime,    is_services_oper,
       -1,-1,-1,-1,-1},
    { "JUPE",       do_jupe,       is_services_admin,
	OPER_HELP_JUPE, -1,-1,-1,-1 },
    { "RAW",        do_raw,        is_services_admin,
	OPER_HELP_RAW, -1,-1,-1,-1 },
/*
    { "GENERATEKEY", do_generatekey, is_services_admin,
        OPER_HELP_GENERATEKEY, -1,-1,-1,-1 },
*/
    { "UPDATE",     do_update,     is_services_admin,
	OPER_HELP_UPDATE, -1,-1,-1,-1 },
    { "QUIT",       do_os_quit,    is_services_admin,
	OPER_HELP_QUIT, -1,-1,-1,-1 },
    { "SHUTDOWN",   do_shutdown,   is_services_admin,
	OPER_HELP_SHUTDOWN, -1,-1,-1,-1 },
    { "RESTART",    do_restart,    is_services_admin,
	OPER_HELP_RESTART, -1,-1,-1,-1 },
    { "LISTIGNORE", do_listignore, is_services_admin,
	-1,-1,-1,-1, -1 },
    { "KILLCLONES", do_killclones, is_services_admin,
	OPER_HELP_KILLCLONES, -1,-1,-1, -1 },

    /* Commands for Services root: */

    { "ROTATELOG",  rotate_log,  is_services_root, -1,-1,-1,-1,
	OPER_HELP_ROTATELOG },
/*
    { "ROTATEDB",   NULL,   is_services_root, -1,-1,-1,-1,
        OPER_HELP_ROTATEDB },	
*/

#ifdef DEBUG_COMMANDS
    { "LISTCHANS",  send_channel_list,  is_services_admin, -1,-1,-1,-1,-1 },
    { "LISTCHAN",   send_channel_users, is_services_admin, -1,-1,-1,-1,-1 },
    { "LISTUSERS",  send_user_list,     is_services_admin, -1,-1,-1,-1,-1 },
    { "LISTUSER",   send_user_info,     is_services_admin, -1,-1,-1,-1,-1 },
    { "LISTTIMERS", send_timeout_list,  is_services_admin, -1,-1,-1,-1,-1 },
    { "MATCHWILD",  do_matchwild,       is_services_admin, -1,-1,-1,-1,-1 },
#endif

    /* Fencepost: */
    { NULL }
};

/*************************************************************************/
/*************************************************************************/

/* OperServ initialization. */

void os_init(void)
{
    Command *cmd;

    cmd = lookup_cmd(cmds, "GLOBAL");
    if (cmd)
	cmd->help_param1 = s_GlobalNoticer;
    cmd = lookup_cmd(cmds, "GLOBALN");
    if (cmd)
        cmd->help_param1 = s_GlobalNoticer;                	
    cmd = lookup_cmd(cmds, "ADMIN");
    if (cmd)
	cmd->help_param1 = s_NickServ;
    cmd = lookup_cmd(cmds, "OPER");
    if (cmd)
	cmd->help_param1 = s_NickServ;
}

/*************************************************************************/

/* Main OperServ routine. */

void operserv(const char *source, char *buf)
{
    char *cmd;
    char *s;
    User *u = finduser(source);

    if (!u) {
	log("%s: user record for %s not found", s_OperServ, source);
	privmsg(s_OperServ, source,
		getstring((NickInfo *)NULL, USER_RECORD_NOT_FOUND));
	return;
    }

    log("%s: %s: %s", s_OperServ, source, buf);

    cmd = strtok(buf, " ");
    if (!cmd) {
	return;
    } else if (stricmp(cmd, "\1PING") == 0) {
	if (!(s = strtok(NULL, "")))
	    s = "\1";
	notice(s_OperServ, source, "\1PING %s", s);
    } else if (stricmp(cmd, "\1VERSION") == 0) {
     	notice(s_OperServ, source, "\1VERSION ircservices-%s+Terra-%s %s -- %s\1",
                  version_number, version_terra,  s_OperServ, version_build);
    } else {
	run_cmd(s_OperServ, u, cmds, cmd);
    }
}

/*************************************************************************/
/**************************** Privilege checks ***************************/
/*************************************************************************/

/* Load OperServ data. */

#define SAFE(x) do {					\
    if ((x) < 0) {					\
	if (!forceload)					\
	    fatal("Read error on %s", OperDBName);	\
	failed = 1;					\
	break;						\
    }							\
} while (0)

void load_os_dbase(void)
{
    dbFILE *f;
    int16 i, n, ver;
    char *s;
    int failed = 0;

    if (!(f = open_db(s_OperServ, OperDBName, "r", OPER_VERSION)))
	return;
    switch (ver = get_file_version(f)) {
      case 8:
      case 7:
      case 6:
      case 5:
	SAFE(read_int16(&n, f));
	for (i = 0; i < n && !failed; i++) {
	    SAFE(read_string(&s, f));
	    if (s && i < MAX_SERVADMINS)
		services_admins[i] = findnick(s);
	    if (s)
		free(s);
	}
	if (!failed)
	    SAFE(read_int16(&n, f));
	for (i = 0; i < n && !failed; i++) {
	    SAFE(read_string(&s, f));
	    if (s && i < MAX_SERVOPERS)
		services_opers[i] = findnick(s);
	    if (s)
		free(s);
	}
	if (ver >= 7) {
	    int32 tmp32;
	    SAFE(read_int32(&maxusercnt, f));
	    SAFE(read_int32(&tmp32, f));
	    maxusertime = tmp32;
	}
	if (ver >= 8) {
	    int32 tmp32;
	    SAFE(read_int32(&maxchancnt, f));
	    SAFE(read_int32(&tmp32, f));
	    maxchantime = tmp32;	    
	}
	break;

      case 4:
      case 3:
	SAFE(read_int16(&n, f));
	for (i = 0; i < n && !failed; i++) {
	    SAFE(read_string(&s, f));
	    if (s && i < MAX_SERVADMINS)
		services_admins[i] = findnick(s);
	    if (s)
		free(s);
	}
	break;

      default:
	fatal("Unsupported version (%d) on %s", ver, OperDBName);
    } /* switch (version) */
    close_db(f);
}

#undef SAFE

/*************************************************************************/

/* Save OperServ data. */

#define SAFE(x) do {						\
    if ((x) < 0) {						\
	restore_db(f);						\
	log_perror("Write error on %s", OperDBName);		\
	if (time(NULL) - lastwarn > WarningTimeout) {		\
	    canalopers(NULL, "Write error on %s: %s", OperDBName,	\
			strerror(errno));			\
	    lastwarn = time(NULL);				\
	}							\
	return;							\
    }								\
} while (0)

void save_os_dbase(void)
{
    dbFILE *f;
    int16 i, count = 0;
    static time_t lastwarn = 0;

    if (!(f = open_db(s_OperServ, OperDBName, "w", OPER_VERSION)))
	return;
    for (i = 0; i < MAX_SERVADMINS; i++) {
	if (services_admins[i])
	    count++;
    }
    SAFE(write_int16(count, f));
    for (i = 0; i < MAX_SERVADMINS; i++) {
	if (services_admins[i])
	    SAFE(write_string(services_admins[i]->nick, f));
    }
    count = 0;
    for (i = 0; i < MAX_SERVOPERS; i++) {
	if (services_opers[i])
	    count++;
    }
    SAFE(write_int16(count, f));
    for (i = 0; i < MAX_SERVOPERS; i++) {
	if (services_opers[i])
	    SAFE(write_string(services_opers[i]->nick, f));
    }
    SAFE(write_int32(maxusercnt, f));
    SAFE(write_int32(maxusertime, f));
    SAFE(write_int32(maxchancnt, f));
    SAFE(write_int32(maxchantime, f));            
    close_db(f);
}

#undef SAFE

/*************************************************************************/

/* Does the given user have Services root privileges? */

int is_services_root(User *u)
{
    if (!(u->mode & UMODE_O) || stricmp(u->nick, ServicesRoot) != 0)
	return 0;
    if (skeleton || nick_identified(u))
	return 1;
    return 0;
}

/*************************************************************************/

/* Does the given user have Services admin privileges? */

int is_services_admin(User *u)
{
    int i;
/*
    if (!(u->mode & UMODE_O))
	return 0;
*/
    if (is_services_root(u))
	return 1;
    if (skeleton)
	return 1;

    if (u->ni && ((u->ni->flags & NI_ADMIN_SERV) && nick_identified(u)))
        return 1;
   
    for (i = 0; i < MAX_SERVADMINS; i++) {
	if (services_admins[i] && u->ni == getlink(services_admins[i])) {
	    if (nick_identified(u))
		return 1;
	    return 0;
	}
    }
    return 0;
}

/*************************************************************************/

/* Does the given user have Services oper privileges? */

int is_services_oper(User *u)
{
    int i;

//    if (!(u->mode & UMODE_O))
//	return 0;
    if (is_services_admin(u))
	return 1;
    if (skeleton)
	return 1;

    if (u->ni && ((u->ni->flags & NI_OPER_SERV) && nick_identified(u)))
        return 1;

    for (i = 0; i < MAX_SERVOPERS; i++) {
	if (services_opers[i] && u->ni == getlink(services_opers[i])) {
	    if (nick_identified(u))
		return 1;
	    return 0;
	}
    }
    return 0;
}

/*************************************************************************/

/* Is the given nick a Services admin/root nick? */

/* NOTE: Do not use this to check if a user who is online is a services admin
 * or root. This function only checks if a user has the ABILITY to be a 
 * services admin. Rather use is_services_admin(User *u). -TheShadow */

int nick_is_services_admin(NickInfo *ni)
{
    int i;

    if (!ni)
	return 0;
    if (stricmp(ni->nick, ServicesRoot) == 0)
	return 1;
    if (ni->flags & NI_ADMIN_SERV)
        return 1;
        	
    for (i = 0; i < MAX_SERVADMINS; i++) {
	if (services_admins[i] && getlink(ni) == getlink(services_admins[i]))
	    return 1;
    }
    return 0;
}

/*************************************************************************/
/* El nick es de un oper?
 * - zoltan
 */
 
int nick_is_services_oper(NickInfo *ni)
{
    int i;
    
    if (!ni)
        return 0; 
   if (stricmp(ni->nick, ServicesRoot) == 0)
        return 1;        
    if (nick_is_services_admin(ni))
        return 1;
    if (ni->flags & NI_OPER_SERV)
        return 1;        
    for (i = 0; i < MAX_SERVOPERS; i++) {
        if (services_opers[i] && getlink(ni) == getlink(services_opers[i]))
            return 1;
    }        
    return 0;
}    

/*************************************************************************/


/* Expunge a deleted nick from the Services admin/oper lists. */

void os_remove_nick(const NickInfo *ni)
{
    int i;

    for (i = 0; i < MAX_SERVADMINS; i++) {
	if (services_admins[i] == ni)
	    services_admins[i] = NULL;
    }
    for (i = 0; i < MAX_SERVOPERS; i++) {
	if (services_opers[i] == ni)
	    services_opers[i] = NULL;
    }
}

/*************************************************************************/
/*********************** OperServ command functions **********************/
/*************************************************************************/

/* HELP command. */

static void do_help(User *u)
{
    const char *cmd = strtok(NULL, "");

    if (!cmd) {
	notice_help(s_OperServ, u, OPER_HELP);
    } else {
	help_cmd(s_OperServ, u, cmds, cmd);
    }
}

/*************************************************************************/

static void do_credits(User *u)
{

    notice_lang(s_OperServ, u, SERVICES_CREDITS_TERRA);

}

/*************************************************************************/

/* Global notice sending via GlobalNoticer. */

/* Por Privmsg */

static void do_global(User *u)
{
    char *msg = strtok(NULL, "");

    if (!msg) {
	syntax_error(s_OperServ, u, "GLOBAL", OPER_GLOBAL_SYNTAX);
	return;
    }
#if HAVE_ALLWILD_NOTICE
    privmsg(s_GlobalNoticer, "$*", "Mensaje Global: %s", msg);
#else
# ifdef NETWORK_DOMAIN
    privmsg(s_GlobalNoticer, "$*." NETWORK_DOMAIN, "Mensaje Global: %s", msg);
# else
    /* Go through all common top-level domains.  If you have others,
     * add them here.
     */
    privmsg(s_GlobalNoticer, "$*.es", "Mensaje Global: %s", msg);  /* España */     
    privmsg(s_GlobalNoticer, "$*.com", "Mensaje Global: %s", msg); /* Comercial */
    privmsg(s_GlobalNoticer, "$*.net", "Mensaje Global: %s", msg); /* Networks */
    privmsg(s_GlobalNoticer, "$*.org", "Mensaje Global: %s", msg); /* Organizaciones */
    privmsg(s_GlobalNoticer, "$*.edu", "Mensaje Global: %s", msg); /* Educativo */
# endif
#endif
    canalopers(s_GlobalNoticer, "%s ha enviado el GLOBAL (%s)", u->nick, msg);
}

/*************************************************************************/

/* Global notice sending via GlobalNoticer. */

/* Por Notice */

static void do_globaln(User *u)
{
    char *msg = strtok(NULL, "");
    
    if (!msg) {
        syntax_error(s_OperServ, u, "GLOBALN", OPER_GLOBALN_SYNTAX);
        return;
    }
#if HAVE_ALLWILD_NOTICE
    notice(s_GlobalNoticer, "$*", "Mensaje Global: %s", msg);
#else
# ifdef NETWORK_DOMAIN
    notice(s_GlobalNoticer, "$*." NETWORK_DOMAIN, "Mensaje Global: %s", msg);
# else
    /* Go through all common top-level domains.  If you have others,
     * add them here.
     */
    notice(s_GlobalNoticer, "$*.es", "Mensaje Global: %s", msg);  /* España */
    notice(s_GlobalNoticer, "$*.com", "Mensaje Global: %s", msg); /* Comercial */
    notice(s_GlobalNoticer, "$*.net", "Mensaje Global: %s", msg); /* Networks */
    notice(s_GlobalNoticer, "$*.org", "Mensaje Global: %s", msg); /* Organizaciones */
    notice(s_GlobalNoticer, "$*.edu", "Mensaje Global: %s", msg); /* Educativo */
# endif
#endif
    canalopers(s_GlobalNoticer, "%s ha enviado el GLOBAL (%s)", u->nick, msg);
}
/*************************************************************************/

/* STATS command. */

static void do_stats(User *u)
{
    time_t uptime = time(NULL) - start_time;
    char *extra = strtok(NULL, "");
    int days = uptime/86400, hours = (uptime/3600)%24,
        mins = (uptime/60)%60, secs = uptime%60;
    struct tm *tm;
    char timebuf[64];

    if (extra && stricmp(extra, "ALL") != 0) {
	if ((stricmp(extra, "AKILL") == 0) || (stricmp(extra, "GLINE") == 0)) {
	    int timeout = AutokillExpiry+59;
	    notice_lang(s_OperServ, u, OPER_STATS_AKILL_COUNT, num_akills());
	    if (timeout >= 172800)
		notice_lang(s_OperServ, u, OPER_STATS_AKILL_EXPIRE_DAYS,
			timeout/86400);
	    else if (timeout >= 86400)
		notice_lang(s_OperServ, u, OPER_STATS_AKILL_EXPIRE_DAY);
	    else if (timeout >= 7200)
		notice_lang(s_OperServ, u, OPER_STATS_AKILL_EXPIRE_HOURS,
			timeout/3600);
	    else if (timeout >= 3600)
		notice_lang(s_OperServ, u, OPER_STATS_AKILL_EXPIRE_HOUR);
	    else if (timeout >= 120)
		notice_lang(s_OperServ, u, OPER_STATS_AKILL_EXPIRE_MINS,
			timeout/60);
	    else if (timeout >= 60)
		notice_lang(s_OperServ, u, OPER_STATS_AKILL_EXPIRE_MIN);
	    else
		notice_lang(s_OperServ, u, OPER_STATS_AKILL_EXPIRE_NONE);
	    return;
	} else {
	    notice_lang(s_OperServ, u, OPER_STATS_UNKNOWN_OPTION,
			strupper(extra));
	}
    }

    notice_lang(s_OperServ, u, OPER_STATS_CURRENT_USERS, usercnt, opcnt);
    tm = localtime(&maxusertime);
    strftime_lang(timebuf, sizeof(timebuf), u, STRFTIME_DATE_TIME_FORMAT, tm);
    notice_lang(s_OperServ, u, OPER_STATS_MAX_USERS, maxusercnt, timebuf);
    notice_lang(s_OperServ, u, OPER_STATS_CURRENT_CHANS, chancnt);
    tm = localtime(&maxchantime);
    strftime_lang(timebuf, sizeof(timebuf), u, STRFTIME_DATE_TIME_FORMAT, tm);
    notice_lang(s_OperServ, u, OPER_STATS_MAX_CHANS, maxchancnt, timebuf);
                    
    if (days > 1) {
	notice_lang(s_OperServ, u, OPER_STATS_UPTIME_DHMS,
		days, hours, mins, secs);
    } else if (days == 1) {
	notice_lang(s_OperServ, u, OPER_STATS_UPTIME_1DHMS,
		days, hours, mins, secs);
    } else {
	if (hours > 1) {
	    if (mins != 1) {
		if (secs != 1) {
		    notice_lang(s_OperServ, u, OPER_STATS_UPTIME_HMS,
				hours, mins, secs);
		} else {
		    notice_lang(s_OperServ, u, OPER_STATS_UPTIME_HM1S,
				hours, mins, secs);
		}
	    } else {
		if (secs != 1) {
		    notice_lang(s_OperServ, u, OPER_STATS_UPTIME_H1MS,
				hours, mins, secs);
		} else {
		    notice_lang(s_OperServ, u, OPER_STATS_UPTIME_H1M1S,
				hours, mins, secs);
		}
	    }
	} else if (hours == 1) {
	    if (mins != 1) {
		if (secs != 1) {
		    notice_lang(s_OperServ, u, OPER_STATS_UPTIME_1HMS,
				hours, mins, secs);
		} else {
		    notice_lang(s_OperServ, u, OPER_STATS_UPTIME_1HM1S,
				hours, mins, secs);
		}
	    } else {
		if (secs != 1) {
		    notice_lang(s_OperServ, u, OPER_STATS_UPTIME_1H1MS,
				hours, mins, secs);
		} else {
		    notice_lang(s_OperServ, u, OPER_STATS_UPTIME_1H1M1S,
				hours, mins, secs);
		}
	    }
	} else {
	    if (mins != 1) {
		if (secs != 1) {
		    notice_lang(s_OperServ, u, OPER_STATS_UPTIME_MS,
				mins, secs);
		} else {
		    notice_lang(s_OperServ, u, OPER_STATS_UPTIME_M1S,
				mins, secs);
		}
	    } else {
		if (secs != 1) {
		    notice_lang(s_OperServ, u, OPER_STATS_UPTIME_1MS,
				mins, secs);
		} else {
		    notice_lang(s_OperServ, u, OPER_STATS_UPTIME_1M1S,
				mins, secs);
		}
	    }
	}
    }

    if (extra && stricmp(extra, "ALL") == 0 && is_services_admin(u)) {
        long count, mem, count2, mem2, caccess, cignore, cakick;
        long csuspend, cforbid, cmemos, cmemosnr;
        long memos = 0, memosnr = 0, akill = 0, news = 0;
#ifdef CYBER
        long cipnofija, cvhost;
#endif        

	notice_lang(s_OperServ, u, OPER_STATS_BYTES_READ, total_read / 1024);
	notice_lang(s_OperServ, u, OPER_STATS_BYTES_WRITTEN, 
			total_written / 1024);

        get_server_stats(&count, &mem);
        notice_lang(s_OperServ, u, OPER_STATS_SERVER_MEM,
                        count, (mem+512) / 1024);
                                        
	get_user_stats(&count, &mem);
	notice_lang(s_OperServ, u, OPER_STATS_USER_MEM,
			count, (mem+512) / 1024);
	get_channel_stats(&count, &mem);
	notice_lang(s_OperServ, u, OPER_STATS_CHANNEL_MEM,
			count, (mem+512) / 1024);
#ifdef CYBER
        get_clones_stats(&count, &mem);
        notice_lang(s_OperServ, u, OPER_STATS_SESSIONS_MEM,
                        count, (mem+512) / 1024);
#endif
        get_nickserv_stats(&count, &mem, &cforbid, &csuspend, &caccess,
                 &cignore, &cmemos, &cmemosnr);
	notice_lang(s_OperServ, u, OPER_STATS_NICKSERV_MEM,
			count, (mem+512) / 1024);
        notice_lang(s_OperServ, u, OPER_STATS_NICKSERV_MEM_2,
                        cforbid, csuspend);
        notice_lang(s_OperServ, u, OPER_STATS_NICKSERV_MEM_3,
                        caccess, cignore);
        notice_lang(s_OperServ, u, OPER_STATS_NICKSERV_MEM_4,
                        cmemos, cmemosnr);
        memos += cmemos;
        memosnr += cmemosnr;
        get_chanserv_stats(&count, &mem, &cforbid, &csuspend, &caccess,
                 &cakick, &cmemos, &cmemosnr);
	notice_lang(s_OperServ, u, OPER_STATS_CHANSERV_MEM,
			count, (mem+512) / 1024);
        notice_lang(s_OperServ, u, OPER_STATS_CHANSERV_MEM_2,
                        cforbid, csuspend);
        notice_lang(s_OperServ, u, OPER_STATS_CHANSERV_MEM_3,
                        caccess, cakick);
        notice_lang(s_OperServ, u, OPER_STATS_CHANSERV_MEM_4,
                        cmemos, cmemosnr);
        memos += cmemos;
        memosnr += cmemosnr;
#ifdef CYBER                                        
        get_iline_stats(&count, &mem, &csuspend, &cipnofija, &cvhost);
        notice_lang(s_OperServ, u, OPER_STATS_CYBERSERV_MEM,
                        count, (mem+512) / 1024);
        notice_lang(s_OperServ, u, OPER_STATS_CYBERSERV_MEM_2,
                        csuspend);
        notice_lang(s_OperServ, u, OPER_STATS_CYBERSERV_MEM_3,
                        cipnofija, cvhost);
#endif   
	get_akill_stats(&count2, &mem2);
	count += count2;
        akill += count2;
	mem += mem2;
	get_news_stats(&count2, &mem2);
	count += count2;
        news += count2;
	mem += mem2;
	notice_lang(s_OperServ, u, OPER_STATS_OPERSERV_MEM,
			count, (mem+512) / 1024);
        notice_lang(s_OperServ, u, OPER_STATS_OPERSERV_MEM_2,
                        akill, news);
        notice_lang(s_OperServ, u, OPER_STATS_MEMOSERV_TOTAL,
                        memos);
        notice_lang(s_OperServ, u, OPER_STATS_MEMOSERV_NOREAD,
                        memosnr);			

    }
}


/*************************************************************************/

/* Da la key (modo +k) de un canal */

static void do_getkey(User *u)
{
    char *chan = strtok(NULL, " ");
    Channel *c;

    if (!chan) {
        syntax_error(s_OperServ, u, "GETKEY", CHAN_GETKEY_SYNTAX);
    } else if (!(c = findchan(chan))) {
        notice_lang(s_OperServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (!c->key) {
        notice_lang(s_OperServ, u, CHAN_GETKEY_NOT_FOUND, chan);
    } else {
        notice_lang(s_OperServ, u, CHAN_GETKEY_FOUND, chan, c->key);
        canalopers(s_OperServ, "%s hizo GETKEY en %s", u->nick, chan);
    }

}

/*************************************************************************/

/* Op en un canal a traves del servidor */

static void do_os_op(User *u)
{
    char *chan = strtok(NULL, " ");
    char *op_params = strtok(NULL, " ");
    char *argv[3];
            
    Channel *c;
    
    if (!chan || !op_params) {
        syntax_error(s_OperServ, u, "OP", CHAN_OP_SYNTAX);
    } else if (!(c = findchan(chan))) {
        notice_lang(s_OperServ, u, CHAN_X_NOT_IN_USE, chan);
    } else {
        User *u2 =finduser(op_params);    
        if (u2) {
            send_cmd(ServerName, "MODE %s +o %s", chan, op_params);
            
            argv[0] = sstrdup(chan);
            argv[1] = sstrdup("+o");
            argv[2] = sstrdup(op_params);
            do_cmode(s_OperServ, 3, argv);
            free(argv[2]);
            free(argv[1]);
            free(argv[0]);                 
        } else
            notice_lang(s_OperServ, u, NICK_X_NOT_IN_USE, op_params);
    }
}

/*************************************************************************/

/* deop en un canal a traves de server */

static void do_os_deop(User *u)
{
    char *chan = strtok(NULL, " ");
    char *deop_params = strtok(NULL, " ");
    char *argv[3];
            
    Channel *c;

    if (!chan || !deop_params) {
        syntax_error(s_OperServ, u, "DEOP", CHAN_DEOP_SYNTAX);
    } else if (!(c = findchan(chan))) {
        notice_lang(s_OperServ, u, CHAN_X_NOT_IN_USE, chan);
    } else {
        User *u2 =finduser(deop_params);
        if (u2) {    
            send_cmd(ServerName, "MODE %s -o %s", chan, deop_params);
            
            argv[0] = sstrdup(chan);
            argv[1] = sstrdup("-o");
            argv[2] = sstrdup(deop_params);
            do_cmode(s_OperServ, 3, argv);
            free(argv[2]);
            free(argv[1]);
            free(argv[0]);
        } else
            notice_lang(s_OperServ, u, NICK_X_NOT_IN_USE, deop_params);
    }
}            

/*************************************************************************/

/* Channel mode changing (MODE command). */

static void do_os_mode(User *u)
{
    int argc;
    char **argv;
    char *s = strtok(NULL, "");
    char *chan, *modes;
    Channel *c;

    if (!s) {
	syntax_error(s_OperServ, u, "MODE", OPER_MODE_SYNTAX);
	return;
    }
    chan = s;
    s += strcspn(s, " ");
    if (!*s) {
	syntax_error(s_OperServ, u, "MODE", OPER_MODE_SYNTAX);
	return;
    }
    *s = 0;
    modes = (s+1) + strspn(s+1, " ");
    if (!*modes) {
	syntax_error(s_OperServ, u, "MODE", OPER_MODE_SYNTAX);
	return;
    }
    if (!(c = findchan(chan))) {
	notice_lang(s_OperServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (c->bouncy_modes) {
	notice_lang(s_OperServ, u, OPER_BOUNCY_MODES_U_LINE);
	return;
    } else {
	send_cmd(s_OperServ, "MODE %s %s", chan, modes);
        canalopers(s_OperServ, "%s usa MODE %s en %s", u->nick, modes, chan);
	*s = ' ';
	argc = split_buf(chan, &argv, 1);
	do_cmode(s_OperServ, argc, argv);
    }
}

/*************************************************************************/

/* Clear all modes from a channel. */

static void do_clearmodes(User *u)
{
    char *s;
    int i;
    char *argv[3];
    char *chan = strtok(NULL, " ");
    Channel *c;
    int all = 0;
    int count;		/* For saving ban info */
    char **bans;	/* For saving ban info */
    struct c_userlist *cu, *next;

    if (!chan) {
	syntax_error(s_OperServ, u, "CLEARMODES", OPER_CLEARMODES_SYNTAX);
    } else if (!(c = findchan(chan))) {
	notice_lang(s_OperServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (c->bouncy_modes) {
        notice_lang(s_OperServ, u, OPER_BOUNCY_MODES_U_LINE);
	return;
    } else {
	s = strtok(NULL, " ");
	if (s) {
	    if (stricmp(s, "ALL") == 0) {
		all = 1;
	    } else {
		syntax_error(s_OperServ,u,"CLEARMODES",OPER_CLEARMODES_SYNTAX);
		return;
	    }
	}
        canalopers(s_OperServ, "%s usa CLEARMODES%s en %s",
			u->nick, all ? " ALL" : "", chan);
	if (all) {
	    /* Clear mode +o */
	    for (cu = c->chanops; cu; cu = next) {
		next = cu->next;
		argv[0] = sstrdup(chan);
		argv[1] = sstrdup("-o");
		argv[2] = sstrdup(cu->user->nick);
		send_cmd(s_OperServ, "MODE %s %s :%s",
			argv[0], argv[1], argv[2]);
		do_cmode(s_ChanServ, 3, argv);
		free(argv[2]);
		free(argv[1]);
		free(argv[0]);
	    }

	    /* Clear mode +v */
	    for (cu = c->voices; cu; cu = next) {
		next = cu->next;
		argv[0] = sstrdup(chan);
		argv[1] = sstrdup("-v");
		argv[2] = sstrdup(cu->user->nick);
		send_cmd(s_OperServ, "MODE %s %s :%s",
			argv[0], argv[1], argv[2]);
		do_cmode(s_ChanServ, 3, argv);
		free(argv[2]);
		free(argv[1]);
		free(argv[0]);
	    }
	}

	/* Clear modes */
	if (c->key) {
            send_cmd(s_OperServ, "MODE %s -ilkmnpst :%s", chan, c->key);
        } else {
            send_cmd(s_OperServ, "MODE %s -ilmnpst", chan);	 	
        }
	argv[0] = sstrdup(chan);
        if (c->key)
            argv[1] = sstrdup("-iklmnpstR");
        else
            argv[1] = sstrdup("-ilmnpstR");
	argv[2] = c->key ? c->key : sstrdup("");
	do_cmode(s_OperServ, 2, argv);
	free(argv[0]);
	free(argv[1]);
	free(argv[2]);
	c->key = NULL;
	c->limit = 0;

	/* Clear bans */
        if (c->bancount) {
            count = c->bancount;
	    bans = smalloc(sizeof(char *) * count);
	    for (i = 0; i < count; i++)
	        bans[i] = sstrdup(c->bans[i]);
	    for (i = 0; i < count; i++) {
	        argv[0] = sstrdup(chan);
	        argv[1] = sstrdup("-b");
	        argv[2] = bans[i];
	        send_cmd(s_OperServ, "MODE %s %s :%s",
			argv[0], argv[1], argv[2]);
	        do_cmode(s_OperServ, 3, argv);
	        free(argv[2]);
	        free(argv[1]);
	        free(argv[0]);
	    }
	    free(bans);
        }
        if (all)
            notice_lang(s_OperServ, u, OPER_CLEARMODES_ALL_DONE, chan);
        else
            notice_lang(s_OperServ, u, OPER_CLEARMODES_DONE, chan);

    }
}

/*************************************************************************/

/* Kick a user from a channel (KICK command). */

static void do_os_kick(User *u)
{
    char *argv[3];
    char *chan, *nick, *s;
    Channel *c;
    User *u2;    

    chan = strtok(NULL, " ");
    nick = strtok(NULL, " ");
    s = strtok(NULL, "");
    if (!chan || !nick || !s) {
	syntax_error(s_OperServ, u, "KICK", OPER_KICK_SYNTAX);
	return;
    }
    if (!(c = findchan(chan))) {
	notice_lang(s_OperServ, u, CHAN_X_NOT_IN_USE, chan);
    } else if (c->bouncy_modes) {
	notice_lang(s_OperServ, u, OPER_BOUNCY_MODES_U_LINE);
        return;
    }
    u2 = finduser(nick);    
    if (u2) {    
        send_cmd(ServerName, "KICK %s %s :%s (%s)", chan, nick, u->nick, s);
    	canalopers(s_OperServ, "%s ha usado KICK en %s/%s", u->nick, nick, chan);
        argv[0] = sstrdup(chan);
        argv[1] = sstrdup(nick);
        argv[2] = sstrdup(s);
        do_kick(s_OperServ, 3, argv);
        free(argv[2]);
        free(argv[1]);
        free(argv[0]);
    } else
        notice_lang(s_OperServ, u, NICK_X_NOT_IN_USE, nick);        
}

/***************************************************************************/

/* Quitar los modos y lo silencia */

static void do_apodera(User *u)
{
    char *chan = strtok(NULL, " ");
    
    Channel *c;

    if (!chan) {
        syntax_error(s_OperServ, u, "APODERA", OPER_APODERA_SYNTAX);            
        return;
    } else if (!(c = findchan(chan))) {
        notice_lang(s_OperServ, u, CHAN_X_NOT_IN_USE, chan);
    } else {    
        char *av[3];
        struct c_userlist *cu, *next;
        send_cmd(s_ChanServ, "JOIN %s", chan);
        send_cmd(ServerName, "MODE %s +o %s", chan, s_ChanServ);
        send_cmd(s_ChanServ, "MODE %s :+tnsim", chan);        
        for (cu = c->users; cu; cu = next) {
            next = cu->next;        
            if (!is_services_oper(finduser(cu->user->nick))) {            
                av[0] = sstrdup(chan);        
                av[1] = sstrdup("-o");
                av[2] = sstrdup(cu->user->nick);
                send_cmd(s_ChanServ, "MODE %s %s %s",
                          av[0], av[1], av[2]);
                do_cmode(s_ChanServ, 3, av);
                free(av[2]);
                free(av[1]);
                free(av[0]);
            }            
            /* Poner timeout salida de chan... */
         }
         notice_lang(s_OperServ, u, OPER_APODERA_SUCCEEDED, chan);
         canalopers(s_OperServ, "%s se APODERA de %s", u->nick, chan);
    }
}                                                

/**************************************************************************/

static void do_limpia(User *u)
{
    char *chan = strtok(NULL, " ");
    char *reason = strtok(NULL, "");    
    
    Channel *c;
   
    if (!chan) {    
        syntax_error(s_OperServ, u, "LIMPIA", OPER_LIMPIA_SYNTAX);     
        return;
    } else if (!(c = findchan(chan))) {
        notice_lang(s_OperServ, u, CHAN_X_NOT_IN_USE, chan);
    } else {    
        char *av[3];
        struct c_userlist *cu, *next;       
        char buf[256];
        if (!reason)                        
            snprintf(buf, sizeof(buf), "No puedes permanecer en este canal");                
        else
            snprintf(buf, sizeof(buf), "%s", reason);            
        
        send_cmd(s_ChanServ, "JOIN %s", chan);
        send_cmd(ServerName, "MODE %s +o %s", chan, s_ChanServ);
        send_cmd(s_ChanServ, "MODE %s :+tnsim", chan);
        
        for (cu = c->users; cu; cu = next) {
            next = cu->next;        
            if (!is_services_oper(finduser(cu->user->nick))) {                    
                av[0] = sstrdup(chan);        
                av[1] = sstrdup(cu->user->nick);
                av[2] = sstrdup(buf);
                send_cmd(s_ChanServ, "KICK %s %s :%s",
                                 av[0], av[1], av[2]);            
                do_kick(s_ChanServ, 3, av);
                free(av[2]);
                free(av[1]);
                free(av[0]);
            }
            /* Poner timeout salida de chan... */
        }        
        notice_lang(s_OperServ, u, OPER_LIMPIA_SUCCEEDED, chan);
        canalopers(s_OperServ, "%s ha LIMPIADO %s", u->nick, chan);        
    }
}   

/**************************************************************************/

/* KILL al usuario */

static void do_os_kill(User *u)
{
    char *nick = strtok(NULL, " ");
    char *text = strtok(NULL, "");
    User *u2 = NULL;
            

    if (!text) {
        syntax_error(s_OperServ, u, "KILL", OPER_KILL_SYNTAX);
        return;
    }
    
    u2 = finduser(nick);
    
    if (!u2) {    
        notice_lang(s_OperServ, u, NICK_X_NOT_IN_USE, nick);
    } else {    
        char buf[NICKMAX+32];
        snprintf(buf, sizeof(buf), "%s", text);                            
        kill_user(s_OperServ, u2->nick, buf);
        notice_lang(s_OperServ, u, OPER_KILL_SUCCEEDED, u2->nick);
        canalopers(s_OperServ, "%s hace KILL a %s (%s)", u->nick, u2->nick, buf);
    }
}        

/**************************************************************************/

/* Gline de 5 minutos */

static void do_block(User *u)
{
    char *nick = strtok(NULL, " ");
    char *text = strtok(NULL, "");
    User *u2 = NULL;
#ifdef CYBER    
    Clones *clon;
    IlineInfo *il;
#endif    
    
    if (!text) {
        syntax_error(s_OperServ, u, "BLOCK", OPER_BLOCK_SYNTAX);
        return;
    }
                        
    u2 = finduser(nick);    
    
    if (!u2) {
        notice_lang(s_OperServ, u, NICK_X_NOT_IN_USE, nick);
#ifdef CYBER
    } else if ((il = find_iline_host(u2->host)) && !is_services_admin(u)) {     
        clon = findclones(u2->host);
        notice_lang(s_OperServ, u, OPER_BLOCK_CYBER, nick);
        canalopers(s_CyberServ, "%s intenta meter Block a %s[%s] del cyber %s"
         " (%d clones, limite %d)", u->nick, u2->nick, u2->host, il->comentario,
                clon->numeroclones, il->limite);
#endif        
    } else {         
        send_cmd(ServerName, "GLINE * +*@%s 300 :%s", u2->host, text);    
        notice_lang(s_OperServ, u, OPER_BLOCK_SUCCEEDED, nick);
        canalopers(s_OperServ, "BLOCK (5 min.) por %s para %s[%s]  (%s)",
                     u->nick, u2->nick, u2->host, text);
     /* Meter en la lista de akills */
    }
                  
}        


/**************************************************************************/

/* Quitar un block o gline */

static void do_unblock(User *u)
{
    char *mask = strtok(NULL, " ");
    
    if (!mask) {     
        syntax_error(s_OperServ, u, "UNBLOCK", OPER_UNBLOCK_SYNTAX);
    } else {
        send_cmd(ServerName ,"GLINE * -%s", mask);
        canalopers(s_OperServ, "%s ha usado UNBLOCK/UNGLINE en %s", u->nick, mask);
    }
}        

/*************************************************************************/

/* Sincronizar la red en tiempo real */

static void do_settime(User *u)
{
    time_t now = time(NULL);
    
    send_cmd(NULL, "SETTIME %lu", now);
    send_cmd(ServerName, "WALLOPS :Sincronizando la RED...");

    canalopers(s_OperServ, "%s ha usado SETTIME", u->nick);
}    

/*************************************************************************/

/* Services admin list viewing/modification. */

static void do_admin(User *u)
{
    char *cmd, *nick;
    NickInfo *ni;
    int i;

    if (skeleton) {
	notice_lang(s_OperServ, u, OPER_ADMIN_SKELETON);
	return;
    }
    cmd = strtok(NULL, " ");
    if (!cmd)
	cmd = "";

    if (stricmp(cmd, "ADD") == 0) {
	if (!is_services_root(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
	}
	nick = strtok(NULL, " ");
	if (nick) {
	    if (!(ni = findnick(nick))) {
		notice_lang(s_OperServ, u, NICK_X_NOT_REGISTERED, nick);
		return;
	    }
	    for (i = 0; i < MAX_SERVADMINS; i++) {
		if (!services_admins[i] || services_admins[i] == ni)
		    break;
	    }
	    if (services_admins[i] == ni) {
		notice_lang(s_OperServ, u, OPER_ADMIN_EXISTS, ni->nick);
	    } else if (i < MAX_SERVADMINS) {
		services_admins[i] = ni;
		ni->flags |= NI_ADMIN_SERV;
		notice_lang(s_OperServ, u, OPER_ADMIN_ADDED, ni->nick);
                canaladmins(s_OperServ, "%s añade a %s como ADMIN", u->nick, ni->nick);
	    } else {
		notice_lang(s_OperServ, u, OPER_ADMIN_TOO_MANY, MAX_SERVADMINS);
	    }
	    if (readonly)
		notice_lang(s_OperServ, u, READ_ONLY_MODE);
	} else {
	    syntax_error(s_OperServ, u, "ADMIN", OPER_ADMIN_ADD_SYNTAX);
	}

    } else if (stricmp(cmd, "DEL") == 0) {
	if (!is_services_root(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
	}
	nick = strtok(NULL, " ");
	if (nick) {
	    if (!(ni = findnick(nick))) {
		notice_lang(s_OperServ, u, NICK_X_NOT_REGISTERED, nick);
		return;
	    }
	    for (i = 0; i < MAX_SERVADMINS; i++) {
		if (services_admins[i] == ni)
		    break;
	    }
	    if (i < MAX_SERVADMINS) {
		services_admins[i] = NULL;
		ni->flags &= ~NI_ADMIN_SERV;
		notice_lang(s_OperServ, u, OPER_ADMIN_REMOVED, ni->nick);
                canaladmins(s_OperServ, "%s quita a %s de ADMIN", u->nick, ni->nick);
		if (readonly)
		    notice_lang(s_OperServ, u, READ_ONLY_MODE);
	    } else {
		notice_lang(s_OperServ, u, OPER_ADMIN_NOT_FOUND, ni->nick);
	    }
	} else {
	    syntax_error(s_OperServ, u, "ADMIN", OPER_ADMIN_DEL_SYNTAX);
	}

    } else if (stricmp(cmd, "LIST") == 0) {
	notice_lang(s_OperServ, u, OPER_ADMIN_LIST_HEADER);
	for (i = 0; i < MAX_SERVADMINS; i++) {
	    if (services_admins[i])
		privmsg(s_OperServ, u->nick, "%s", services_admins[i]->nick);
	}

    } else {
	syntax_error(s_OperServ, u, "ADMIN", OPER_ADMIN_SYNTAX);
    }
}

/*************************************************************************/

/* Services oper list viewing/modification. */

static void do_oper(User *u)
{
    char *cmd, *nick;
    NickInfo *ni;
    int i;

    if (skeleton) {
	notice_lang(s_OperServ, u, OPER_OPER_SKELETON);
	return;
    }
    cmd = strtok(NULL, " ");
    if (!cmd)
	cmd = "";

    if (stricmp(cmd, "ADD") == 0) {
	if (!is_services_admin(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
	}
	nick = strtok(NULL, " ");
	if (nick) {
	    if (!(ni = findnick(nick))) {
		notice_lang(s_OperServ, u, NICK_X_NOT_REGISTERED, nick);
		return;
	    }
	    for (i = 0; i < MAX_SERVOPERS; i++) {
		if (!services_opers[i] || services_opers[i] == ni)
		    break;
	    }
	    if (services_opers[i] == ni) {
		notice_lang(s_OperServ, u, OPER_OPER_EXISTS, ni->nick);
	    } else if (i < MAX_SERVOPERS) {
		services_opers[i] = ni;
		ni->flags |= NI_OPER_SERV;
		notice_lang(s_OperServ, u, OPER_OPER_ADDED, ni->nick);
                canaladmins(s_OperServ, "%s añade a %s como OPER", u->nick, ni->nick);
	    } else {
		notice_lang(s_OperServ, u, OPER_OPER_TOO_MANY, MAX_SERVOPERS);
	    }
	    if (readonly)
		notice_lang(s_OperServ, u, READ_ONLY_MODE);
	} else {
	    syntax_error(s_OperServ, u, "OPER", OPER_OPER_ADD_SYNTAX);
	}

    } else if (stricmp(cmd, "DEL") == 0) {
	if (!is_services_admin(u)) {
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);
	    return;
	}
	nick = strtok(NULL, " ");
	if (nick) {
	    if (!(ni = findnick(nick))) {
		notice_lang(s_OperServ, u, NICK_X_NOT_REGISTERED, nick);
		return;
	    }
	    for (i = 0; i < MAX_SERVOPERS; i++) {
		if (services_opers[i] == ni)
		    break;
	    }
	    if (i < MAX_SERVOPERS) {
		services_opers[i] = NULL;
		ni->flags &= ~NI_OPER_SERV;
		notice_lang(s_OperServ, u, OPER_OPER_REMOVED, ni->nick);
                canaladmins(s_OperServ, "%s borra a %s de OPER", u->nick, ni->nick);
		if (readonly)
		    notice_lang(s_OperServ, u, READ_ONLY_MODE);
	    } else {
		notice_lang(s_OperServ, u, OPER_OPER_NOT_FOUND, ni->nick);
	    }
	} else {
	    syntax_error(s_OperServ, u, "OPER", OPER_OPER_DEL_SYNTAX);
	}

    } else if (stricmp(cmd, "LIST") == 0) {
	notice_lang(s_OperServ, u, OPER_OPER_LIST_HEADER);
	for (i = 0; i < MAX_SERVOPERS; i++) {
	    if (services_opers[i])
		privmsg(s_OperServ, u->nick, "%s", services_opers[i]->nick);
	}

    } else {
	syntax_error(s_OperServ, u, "OPER", OPER_OPER_SYNTAX);
    }
}

/*************************************************************************/

/* Set various Services runtime options. */

static void do_set(User *u)
{
    char *option = strtok(NULL, " ");
    char *setting = strtok(NULL, " ");

    if (!option || !setting) {
	syntax_error(s_OperServ, u, "SET", OPER_SET_SYNTAX);

    } else if (stricmp(option, "IGNORE") == 0) {
	if (stricmp(setting, "on") == 0) {
	    allow_ignore = 1;
	    notice_lang(s_OperServ, u, OPER_SET_IGNORE_ON);
	} else if (stricmp(setting, "off") == 0) {
	    allow_ignore = 0;
	    notice_lang(s_OperServ, u, OPER_SET_IGNORE_OFF);
	} else {
	    notice_lang(s_OperServ, u, OPER_SET_IGNORE_ERROR);
	}

    } else if (stricmp(option, "READONLY") == 0) {
	if (stricmp(setting, "on") == 0) {
	    readonly = 1;
	    log("Read-only mode activated");
	    close_log();
	    notice_lang(s_OperServ, u, OPER_SET_READONLY_ON);
	} else if (stricmp(setting, "off") == 0) {
	    readonly = 0;
	    open_log();
	    log("Read-only mode deactivated");
	    notice_lang(s_OperServ, u, OPER_SET_READONLY_OFF);
	} else {
	    notice_lang(s_OperServ, u, OPER_SET_READONLY_ERROR);
	}

    } else if (stricmp(option, "DEBUG") == 0) {
	if (stricmp(setting, "on") == 0) {
	    debug = 1;
	    log("Debug mode activated");
	    notice_lang(s_OperServ, u, OPER_SET_DEBUG_ON);
	} else if (stricmp(setting, "off") == 0 ||
				(*setting == '0' && atoi(setting) == 0)) {
	    log("Debug mode deactivated");
	    debug = 0;
	    notice_lang(s_OperServ, u, OPER_SET_DEBUG_OFF);
	} else if (isdigit(*setting) && atoi(setting) > 0) {
	    debug = atoi(setting);
	    log("Debug mode activated (level %d)", debug);
	    notice_lang(s_OperServ, u, OPER_SET_DEBUG_LEVEL, debug);
	} else {
	    notice_lang(s_OperServ, u, OPER_SET_DEBUG_ERROR);
	}

    } else {
	notice_lang(s_OperServ, u, OPER_SET_UNKNOWN_OPTION, option);
    }
}

/*************************************************************************/

static void do_jupe(User *u)
{
    char *jserver = strtok(NULL, " ");
    char *reason = strtok(NULL, "");
    char buf[NICKMAX+16];

    privmsg(s_OperServ, u->nick, "Comando Desactivado");
    return;

    if (!jserver) {
	syntax_error(s_OperServ, u, "JUPE", OPER_JUPE_SYNTAX);
    } else {
	canalopers(s_OperServ, "%s JUPEA a %s",
		u->nick, jserver);
	if (!reason) {
	    snprintf(buf, sizeof(buf), "Jupitered by %s", u->nick);
	    reason = buf;
	}

	send_cmd(NULL, "SERVER %s 1 %lu %lu P10 :%s",
		jserver, time(NULL), time(NULL), reason);
    }
}

/*************************************************************************/

static void do_raw(User *u)
{
    char *text = strtok(NULL, "");

    if (!text)
	syntax_error(s_OperServ, u, "RAW", OPER_RAW_SYNTAX);
    else {
	send_cmd(NULL, "%s", text);
        canaladmins(s_OperServ, "%s usa RAW para: %s", u->nick, text);
    }
}

/*************************************************************************/

static void do_update(User *u)
{
    notice_lang(s_OperServ, u, OPER_UPDATING);
    canalopers(s_OperServ, "%s ejecuta UPDATE. Actualizando bases de datos..",
                   u->nick);
    save_data = 1;
}

/*************************************************************************/

static void do_os_quit(User *u)
{
    quitmsg = malloc(28 + strlen(u->nick));
    if (!quitmsg)
	quitmsg = "QUIT command received, but out of memory!";
    else
	sprintf(quitmsg, "QUIT command received from %s", u->nick);
    quitting = 1;
}

/*************************************************************************/

static void do_shutdown(User *u)
{
    quitmsg = malloc(32 + strlen(u->nick));
    if (!quitmsg)
	quitmsg = "SHUTDOWN command received, but out of memory!";
    else
	sprintf(quitmsg, "SHUTDOWN command received from %s", u->nick);
    save_data = 1;
    delayed_quit = 1;
}

/*************************************************************************/

static void do_restart(User *u)
{
#ifdef SERVICES_BIN
    quitmsg = malloc(31 + strlen(u->nick));
    if (!quitmsg)
	quitmsg = "RESTART command received, but out of memory!";
    else
	sprintf(quitmsg, "RESTART command received from %s", u->nick);
    raise(SIGHUP);
#else
    notice_lang(s_OperServ, u, OPER_CANNOT_RESTART);
#endif
}

/*************************************************************************/

/* XXX - this function is broken!! */

static void do_listignore(User *u)
{
    int sent_header = 0;
    IgnoreData *id;
    int i;

    privmsg(s_OperServ, u->nick, "Command disabled - it's broken.");
    return;
    
    for (i = 0; i < 256; i++) {
	for (id = ignore[i]; id; id = id->next) {
	    if (!sent_header) {
		notice_lang(s_OperServ, u, OPER_IGNORE_LIST);
		sent_header = 1;
	    }
	    privmsg(s_OperServ, u->nick, "%ld %s", id->time, id->who);
	}
    }
    if (!sent_header)
	notice_lang(s_OperServ, u, OPER_IGNORE_LIST_EMPTY);
}

/*************************************************************************/

#ifdef DEBUG_COMMANDS

static void do_matchwild(User *u)
{
    char *pat = strtok(NULL, " ");
    char *str = strtok(NULL, " ");
    if (pat && str)
	privmsg(s_OperServ, u->nick, "%d", match_wild(pat, str));
    else
	privmsg(s_OperServ, u->nick, "Syntax error.");
}

#endif	/* DEBUG_COMMANDS */

/*************************************************************************/

/* Kill all users matching a certain host. The host is obtained from the
 * supplied nick. The raw hostmsk is not supplied with the command in an effort
 * to prevent abuse and mistakes from being made - which might cause *.com to
 * be killed. It also makes it very quick and simple to use - which is usually
 * what you want when someone starts loading numerous clones. In addition to
 * killing the clones, we add a temporary AKILL to prevent them from 
 * immediately reconnecting.
 * Syntax: KILLCLONES nick
 * -TheShadow (29 Mar 1999) 
 */

static void do_killclones(User *u)
{
    char *clonenick = strtok(NULL, " ");
    int count=0;
    User *cloneuser, *user, *tempuser;
    char *clonemask, *akillmask;
    char killreason[NICKMAX+32];
    char akillreason[] = "Gline Temporal de KILLCLONES.";

    if (!clonenick) {
	notice_lang(s_OperServ, u, OPER_KILLCLONES_SYNTAX);

    } else if (!(cloneuser = finduser(clonenick))) {
	notice_lang(s_OperServ, u, OPER_KILLCLONES_UNKNOWN_NICK, clonenick);

    } else {
	clonemask = smalloc(strlen(cloneuser->host) + 5);
	sprintf(clonemask, "*!*@%s", cloneuser->host);

	akillmask = smalloc(strlen(cloneuser->host) + 3);
	sprintf(akillmask, "*@%s", strlower(cloneuser->host));
	
	user = firstuser();
	while (user) {
	    if (match_usermask(clonemask, user) != 0) {
		tempuser = nextuser();
		count++;
		snprintf(killreason, sizeof(killreason), 
					"Cloning [%d]", count);
		kill_user(NULL, user->nick, killreason);
		user = tempuser;
	    } else {
		user = nextuser();
	    }
	}

	add_akill(akillmask, akillreason, u->nick, 
			time(NULL) + KillClonesAkillExpire);

        canalopers(s_OperServ, "%s usa KILLCLONES para %s killeando "
                       "%d clones. Un Gline Temporal ha sido añadido "
                       "para %s.", u->nick, clonemask, count, akillmask);

	log("%s: KILLCLONES: %d clone(s) matching %s killed.",
			s_OperServ, count, clonemask);

	free(akillmask);
	free(clonemask);
    }
}

/*************************************************************************/

/* Autokill list functions.
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

typedef struct akill Akill;
struct akill {
    char *mask;
    char *reason;
    char who[NICKMAX];
    time_t time;
    time_t expires;	/* or 0 for no expiry */
};

static int32 nakill = 0;
static int32 akill_size = 0;
static struct akill *akills = NULL;

/*************************************************************************/
/****************************** Statistics *******************************/
/*************************************************************************/

void get_akill_stats(long *nrec, long *memuse)
{
    long mem;
    int i;

    mem = sizeof(struct akill) * akill_size;
    for (i = 0; i < nakill; i++) {
	mem += strlen(akills[i].mask)+1;
	mem += strlen(akills[i].reason)+1;
    }
    *nrec = nakill;
    *memuse = mem;
}


int num_akills(void)
{
    return (int) nakill;
}

/*************************************************************************/
/*********************** AKILL database load/save ************************/
/*************************************************************************/

#define SAFE(x) do {					\
    if ((x) < 0) {					\
	if (!forceload)					\
	    fatal("Error de lectura en %s", AutokillDBName);	\
	nakill = i;					\
	break;						\
    }							\
} while (0)

void load_akill(void)
{
    dbFILE *f;
    int i, ver;
    int16 tmp16;
    int32 tmp32;

    if (!(f = open_db("AKILL", AutokillDBName, "r", AKILL_VERSION)))
	return;

    ver = get_file_version(f);

    read_int16(&tmp16, f);
    nakill = tmp16;
    if (nakill < 8)
	akill_size = 16;
    else if (nakill >= 16384)
	akill_size = 32767;
    else
	akill_size = 2*nakill;
    akills = scalloc(sizeof(*akills), akill_size);

    switch (ver) {
      case 7:
      case 6:
      case 5:
	for (i = 0; i < nakill; i++) {
	    SAFE(read_string(&akills[i].mask, f));
	    SAFE(read_string(&akills[i].reason, f));
	    SAFE(read_buffer(akills[i].who, f));
	    SAFE(read_int32(&tmp32, f));
	    akills[i].time = tmp32;
	    SAFE(read_int32(&tmp32, f));
	    akills[i].expires = tmp32;
	}
	break;

      case 4:
      case 3: {
	struct {
	    char *mask;
	    char *reason;
	    char who[NICKMAX];
	    time_t time;
	    time_t expires;
	    long reserved[4];
	} old_akill;

	for (i = 0; i < nakill; i++) {
	    SAFE(read_variable(old_akill, f));
	    strscpy(akills[i].who, old_akill.who, NICKMAX);
	    akills[i].time = old_akill.time;
	    akills[i].expires = old_akill.expires;
	}
	for (i = 0; i < nakill; i++) {
	    SAFE(read_string(&akills[i].mask, f));
	    SAFE(read_string(&akills[i].reason, f));
	}
	break;
      } /* case 3/4 */

      case 2: {
	struct {
	    char *mask;
	    char *reason;
	    char who[NICKMAX];
	    time_t time;
	} old_akill;

	for (i = 0; i < nakill; i++) {
	    SAFE(read_variable(old_akill, f));
	    akills[i].time = old_akill.time;
	    strscpy(akills[i].who, old_akill.who, sizeof(akills[i].who));
	    akills[i].expires = 0;
	}
	for (i = 0; i < nakill; i++) {
	    SAFE(read_string(&akills[i].mask, f));
	    SAFE(read_string(&akills[i].reason, f));
	}
	break;
      } /* case 2 */

      case 1: {
	struct {
	    char *mask;
	    char *reason;
	    time_t time;
	} old_akill;

	for (i = 0; i < nakill; i++) {
	    SAFE(read_variable(old_akill, f));
	    akills[i].time = old_akill.time;
	    akills[i].who[0] = 0;
	    akills[i].expires = 0;
	}
	for (i = 0; i < nakill; i++) {
	    SAFE(read_string(&akills[i].mask, f));
	    SAFE(read_string(&akills[i].reason, f));
	}
	break;
      } /* case 1 */

      default:
	fatal("Version no soportada (%d) en %s", ver, AutokillDBName);
    } /* switch (version) */

    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do {							\
    if ((x) < 0) {							\
	restore_db(f);							\
	log_perror("Error de escritura en %s", AutokillDBName);		\
	if (time(NULL) - lastwarn > WarningTimeout) {			\
	    canalopers(NULL, "Error de escritura en %s: %s", AutokillDBName,	\
			strerror(errno));				\
	    lastwarn = time(NULL);					\
	}								\
	return;								\
    }									\
} while (0)

void save_akill(void)
{
    dbFILE *f;
    int i;
    static time_t lastwarn = 0;

    f = open_db("AKILL", AutokillDBName, "w", AKILL_VERSION);
    write_int16(nakill, f);
    for (i = 0; i < nakill; i++) {
	SAFE(write_string(akills[i].mask, f));
	SAFE(write_string(akills[i].reason, f));
	SAFE(write_buffer(akills[i].who, f));
	SAFE(write_int32(akills[i].time, f));
	SAFE(write_int32(akills[i].expires, f));
    }
    close_db(f);
}

#undef SAFE


/*************************************************************************/
/************************** Internal functions ***************************/
/*************************************************************************/

static void send_akill(const Akill *akill)
{
    char *username;
    char *host;
    time_t now = time(NULL);

    username = sstrdup(akill->mask);
    host = strchr(username, '@');
    if (!host) {
	/* Glurp... this oughtn't happen, but if it does, let's not
	 * play with null pointers.  Yell and bail out.
	 */
	canalopers(s_OperServ, "No hay @ en AKILL: %s", akill->mask);
	log("Missing @ in AKILL: %s", akill->mask);
	return;
    }
    *host++ = 0;

#ifdef IRC_BAHAMUT
    send_cmd(ServerName,
	    "AKILL %s %s %ld %s %ld :%s",
	    host, username, 
	    (akill->expires && akill->expires > now)
			? akill->expires - now 
			: 0,
	    akill->who ? akill->who : "<desconocido>", now, 
	    StaticAkillReason ? StaticAkillReason : akill->reason);
#elif defined(IRC_UNDERNET)
    send_cmd(ServerName,
	    "GLINE * +%s@%s %ld :%s",
            username, host,
	    (akills->expires && akills->expires > now)
			? akills->expires - now
			: 999999999,
	    StaticAkillReason ? StaticAkillReason : akill->reason);
#endif
    free(username);
}

/*************************************************************************/
/************************** External functions ***************************/
/*************************************************************************/

/* Does the user match any AKILLs? */

int check_akill(const char *nick, const char *username, const char *host)
{
    char buf[512];
    int i;
//    char *host2, *username2;

    strscpy(buf, username, sizeof(buf)-2);
    i = strlen(buf);
    buf[i++] = '@';
    strlower(strscpy(buf+i, host, sizeof(buf)-i));
    for (i = 0; i < nakill; i++) {
	if (match_wild_nocase(akills[i].mask, buf)) {
	    /* Don't use kill_user(); that's for people who have already
	     * signed on.  This is called before the User structure is
	     * created.
	     */
	    send_cmd(s_OperServ,
			"KILL %s :%s (%s)",
			nick, s_OperServ,
				StaticAkillReason 
				? StaticAkillReason 
				: akills[i].reason);
 	    send_akill(&akills[i]);
            return 1;
	}
    }
    return 0;
}

/*************************************************************************/

/* Delete any expired autokills. */

void expire_akills(void)
{
    int i;
    time_t now = time(NULL);
#ifdef IRC_BAHAMUT
    char *s;
#endif

    if (opt_noexpire)
        return;

    for (i = 0; i < nakill; i++) {
	if (akills[i].expires == 0 || akills[i].expires > now)
	    continue;
	canalopers(s_OperServ, "GLINE en %s ha expirado", akills[i].mask);
#ifdef IRC_BAHAMUT
	s = strchr(akills[i].mask, '@');
	if (s) {
	    *s++ = 0;
	    strlower(s);
	    send_cmd(ServerName, "RAKILL %s %s", s, akills[i].mask);
	}
#elif defined (IRC_UNDERNET)
        send_cmd(NULL, "GLINE * -%s", akills[i].mask);
#endif
	free(akills[i].mask);
	free(akills[i].reason);
	nakill--;
	if (i < nakill)
	    memmove(akills+i, akills+i+1, sizeof(*akills) * (nakill-i));
	i--;
    }
}

/*************************************************************************/
/************************** AKILL list editing ***************************/
/*************************************************************************/

/* Note that all parameters except expiry are assumed to be non-NULL.  A
 * value of NULL for expiry indicates that the AKILL should not expire.
 *
 * Not anymore. Now expiry represents the exact expiry time and may not be 
 * NULL. -TheShadow
 */

void add_akill(const char *mask, const char *reason, const char *who,
		      const time_t expiry)
{
    if (nakill >= 32767) {
	log("%s: Intento de añadir GLINE a la lista llena!", s_OperServ);
	return;
    }
    if (nakill >= akill_size) {
	if (akill_size < 8)
	    akill_size = 8;
	else
	    akill_size *= 2;
	akills = srealloc(akills, sizeof(*akills) * akill_size);
    }
    akills[nakill].mask = sstrdup(mask);
    akills[nakill].reason = sstrdup(reason);
    akills[nakill].time = time(NULL);
    akills[nakill].expires = expiry;
    strscpy(akills[nakill].who, who, NICKMAX);

    if (ImmediatelySendAkill)
	send_akill(&akills[nakill]);
    
    nakill++;
}

/*************************************************************************/

/* Return whether the mask was found in the AKILL list. */

static int del_akill(const char *mask)
{
    int i;

    for (i = 0; i < nakill && strcmp(akills[i].mask, mask) != 0; i++)
	;
    if (i < nakill) {
	free(akills[i].mask);
	free(akills[i].reason);
	nakill--;
	if (i < nakill)
	    memmove(akills+i, akills+i+1, sizeof(*akills) * (nakill-i));
	return 1;
    } else {
	return 0;
    }
}

/*************************************************************************/

/* Handle an OperServ AKILL command. */

void do_akill(User *u)
{
    char *cmd, *mask, *reason, *expiry, *s;
    time_t expires = time(NULL);
    int i;

    cmd = strtok(NULL, " ");
    if (!cmd)
	cmd = "";

    if (stricmp(cmd, "ADD") == 0) {
        time_t t = time(NULL);
        
	if (nakill >= 32767) {
	    notice_lang(s_OperServ, u, OPER_TOO_MANY_AKILLS);
	    return;
	}
	mask = strtok(NULL, " ");
	if (mask && *mask == '+') {
	    expiry = mask;
	    mask = strtok(NULL, " ");
	} else {
	    expiry = NULL;
	}

	expires = expiry ? dotime(expiry) : AutokillExpiry;
	if (expires < 0) {
	    notice_lang(s_OperServ, u, BAD_EXPIRY_TIME);
	    return;
	} else if (expires > 0) {
	    expires += t;
	}

	if (mask && (reason = strtok(NULL, ""))) {
            char buf[128];
            if (strchr(mask, '!')) {
                notice_lang(s_OperServ, u, OPER_AKILL_NO_NICK);
                notice_lang(s_OperServ, u, BAD_USERHOST_MASK);
                return;
            }                                            
 	    s = strchr(mask, '@');
	    if (!s) {
		notice_lang(s_OperServ, u, BAD_USERHOST_MASK);
		return;
	    }
	
            if (stricmp("*@*", mask) == 0) {
                notice_lang(s_OperServ, u, ACCESS_DENIED);
                canalopers(s_OperServ, "El LAMER , muuuuyyy LAMERRRRRRRRR, %s "
                           "intenta meter un GLINE GLOBAL *@*", u->nick);
                return;
            }	
            
            strlower(mask);	
	    add_akill(mask, reason, u->nick, expires);
     	    notice_lang(s_OperServ, u, OPER_AKILL_ADDED, mask);

            if (expires == 0)
                snprintf(buf, sizeof(buf),
                         getstring(u->nick, OPER_AKILL_NO_EXPIRE));
            else
                expires_in_lang(buf, sizeof(buf), u, expires - t + 59);
            canalopers(s_OperServ, "%s ha añadido un GLINE para %s (%s)",
                                u->nick, mask, buf);

	    if (readonly)
		notice_lang(s_OperServ, u, READ_ONLY_MODE);
	} else {
	    syntax_error(s_OperServ, u, "GLINE", OPER_AKILL_ADD_SYNTAX);
	}

    } else if (stricmp(cmd, "DEL") == 0) {
	mask = strtok(NULL, " ");
	if (mask) {
#ifdef IRC_BAHAMUT
	    s = strchr(mask, '@');
	    if (s)
		strlower(s);
#endif
	    if (del_akill(mask)) {
		notice_lang(s_OperServ, u, OPER_AKILL_REMOVED, mask);
#ifdef IRC_BAHAMUT
		if (s) {
		    *s++ = 0;
		    send_cmd(ServerName, "RAKILL %s %s", s, mask);
		} else {
		    /* We lose... can't figure out what's a username and what's
		     * a hostname.  Ah well.
		     */
		}
#elif defined (IRC_UNDERNET)
                send_cmd(NULL, "GLINE * -%s", mask);
#endif
	if (readonly)
		    notice_lang(s_OperServ, u, READ_ONLY_MODE);
	    } else {
		notice_lang(s_OperServ, u, OPER_AKILL_NOT_FOUND, mask);
	    }
	} else {
	    syntax_error(s_OperServ, u, "GLINE", OPER_AKILL_DEL_SYNTAX);
	}

    } else if (stricmp(cmd, "LIST") == 0) {
	char *expiry;
	int expires = -1;	/* Do not match on expiry time */
	     
	expire_akills();
	s = strtok(NULL, " ");
	if (!s)
	    s = "*";
	else {
	    expiry = strtok(NULL, " ");

	    /* This is a little longwinded for what it acheives - but we can
	     * extend it later to allow for user defined expiry times. */
	    if (expiry && stricmp(expiry, "NOEXPIRE") == 0)
		expires = 0;	/* Akills that never expire */
	}

	if (strchr(s, '@'))
	    strlower(strchr(s, '@'));
	notice_lang(s_OperServ, u, OPER_AKILL_LIST_HEADER);
	for (i = 0; i < nakill; i++) {
	    if (!s || (match_wild(s, akills[i].mask) &&
			(expires == -1 || akills[i].expires == expires))) {
		notice_lang(s_OperServ, u, OPER_AKILL_LIST_FORMAT,
					akills[i].mask, akills[i].reason);
	    }
	}

    } else if (stricmp(cmd, "VIEW") == 0) {
	char *expiry;
	int expires = -1;	/* Do not match on expiry time */

	expire_akills();
	s = strtok(NULL, " ");
	if (!s)
	    s = "*";
	else {
	    expiry = strtok(NULL, " ");

	    /* This is a little longwinded for what it acheives - but we can
	     * extend it later to allow for user defined expiry times. */
	    if (expiry && stricmp(expiry, "NOEXPIRE") == 0)
		expires = 0;	/* Akills that never expire */
	}

	if (strchr(s, '@'))
	    strlower(strchr(s, '@'));
	notice_lang(s_OperServ, u, OPER_AKILL_LIST_HEADER);
	for (i = 0; i < nakill; i++) {
	    if (!s || (match_wild(s, akills[i].mask) &&
                        (expires == -1 || akills[i].expires == expires))) {
		char timebuf[32], expirebuf[256];
		struct tm tm;
		time_t t = time(NULL);

		tm = *localtime(akills[i].time ? &akills[i].time : &t);
		strftime_lang(timebuf, sizeof(timebuf),
			u, STRFTIME_SHORT_DATE_FORMAT, &tm);
		if (akills[i].expires == 0) {
		    snprintf(expirebuf, sizeof(expirebuf),
				getstring(u->ni, OPER_AKILL_NO_EXPIRE));
		} else if (akills[i].expires <= t) {
		    snprintf(expirebuf, sizeof(expirebuf),
				getstring(u->ni, OPER_AKILL_EXPIRES_SOON));
		} else {
                    expires_in_lang(expirebuf, sizeof(expirebuf), u,
                           akills[i].expires - t + 59);				
		}
		notice_lang(s_OperServ, u, OPER_AKILL_VIEW_FORMAT,
				akills[i].mask,
				*akills[i].who ? akills[i].who : "<desconocido>",
				timebuf, expirebuf, akills[i].reason);
	    }
	}

    } else if (stricmp(cmd, "COUNT") == 0) {
	notice_lang(s_OperServ, u, OPER_AKILL_COUNT, nakill);
    } else {
	syntax_error(s_OperServ, u, "GLINE", OPER_AKILL_SYNTAX);
    }
}

/*************************************************************************/

/* Definitions of IRC message functions and list of messages.
 *
 * Services is copyright (c) 1996-1999 Andrew Church.
 *     E-mail: <achurch@dragonfire.net>
 * Services is copyright (c) 1999-2000 Andrew Kempe.
 *     E-mail: <theshadow@shadowfire.org>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#include "services.h"
#include "messages.h"
#include "language.h"

/* List of messages is at the bottom of the file. */

/*************************************************************************/
/*************************************************************************/

static void m_nickcoll(char *source, int ac, char **av)
{
    if (ac < 1)
	return;
    if (!skeleton && !readonly)
	introduce_user(av[0]);
}

/*************************************************************************/

static void m_ping(char *source, int ac, char **av)
{
    if (ac < 1)
	return;
    send_cmd(ServerName, "PONG %s %s", ac>1 ? av[1] : ServerName, av[0]);
}

/*************************************************************************/

static void m_away(char *source, int ac, char **av)
{
    User *u = finduser(source);

    if (u && (ac == 0 || *av[0] == 0)) {
       /* Quita el away */
        u->mode &= ~AWAY;
	check_memos(u);
    } else 	
       /* Se pone away */
        u->mode |= AWAY;
}

/*************************************************************************/

static void m_info(char *source, int ac, char **av)
{
    int i;
    struct tm *tm;
    char timebuf[64];

    tm = localtime(&start_time);
    strftime(timebuf, sizeof(timebuf), "%a %b %d %H:%M:%S %Y %Z", tm);

    for (i = 0; info_text[i]; i++)
	send_cmd(ServerName, "371 %s :%s", source, info_text[i]);
    send_cmd(ServerName, "371 %s :Version %s+Terra %s, %s", source, 
    		version_number, version_terra, version_build);
    send_cmd(ServerName, "371 %s :On-line since %s", source, timebuf);
    send_cmd(ServerName, "374 %s :End of /INFO list.", source);
}

/*************************************************************************/

static void m_join(char *source, int ac, char **av)
{
    if (ac != 1)
	return;
    do_join(source, ac, av);
}

/*************************************************************************/

static void m_kick(char *source, int ac, char **av)
{
    if (ac != 3)
	return;
    do_kick(source, ac, av);
}

/*************************************************************************/

static void m_kill(char *source, int ac, char **av)
{
    if (ac != 2)
	return;
    /* Recover if someone kills us. */
    if (stricmp(av[0], s_ChanServ) == 0) {
        introduce_user(av[0]);    
        join_chanserv();
    }    
    if (stricmp(av[0], s_NickServ) == 0 ||
        stricmp(av[0], s_OperServ) == 0 ||
        stricmp(av[0], s_MemoServ) == 0 ||
        stricmp(av[0], s_HelpServ) == 0 ||
#ifdef CYBER
        stricmp(av[0], s_CyberServ) == 0 ||
#endif        
        (s_IrcIIHelp && stricmp(av[0], s_IrcIIHelp) == 0) ||
        (s_DevNull && stricmp(av[0], s_DevNull) == 0) ||
        stricmp(av[0], s_GlobalNoticer) == 0
    ) {
	if (!readonly && !skeleton)
	    introduce_user(av[0]);
    } else {
	do_kill(source, ac, av);
    }
}

/*************************************************************************/

static void m_mode(char *source, int ac, char **av)
{
    if (*av[0] == '#' || *av[0] == '&') {
	if (ac < 2)
	    return;
	do_cmode(source, ac, av);
    } else {
	if (ac != 2)
	    return;
	do_umode(source, ac, av);
    }
}

/*************************************************************************/

static void m_motd(char *source, int ac, char **av)
{
    FILE *f;
    char buf[BUFSIZE];

    f = fopen(MOTDFilename, "r");
    send_cmd(ServerName, "375 %s :- %s Mensaje del día",
		source, ServerName);
   if (f) {
	while (fgets(buf, sizeof(buf), f)) {
	    buf[strlen(buf)-1] = 0;
	    send_cmd(ServerName, "372 %s :- %s", source, buf);
	}
	fclose(f);
    } else {
	send_cmd(ServerName, "372 %s :- MOTD no encontrado!  Por favor "
			"contacta con tu administrador del IRC.", source);
    }

    /* Look, people.  I'm not asking for payment, praise, or anything like
     * that for using Services... is it too much to ask that I at least get
     * some recognition for my work?  Please don't remove the copyright
     * message below.
     */

    send_cmd(ServerName, "372 %s :-", source);
    send_cmd(ServerName, "372 %s :- Servicies is copyright (c) "
                    "1996-1999 Andy Church.", source);                                        
    send_cmd(ServerName, "372 %s :- Servicios de Terra es copyright (c) "        
                    "2000-2001 Terra Networks S.A..", source);		                  
    send_cmd(ServerName, "376 %s :End of /MOTD command.", source);
}

/*************************************************************************/

static void m_nick(char *source, int ac, char **av)
{
    /* ircu sends the server as the source for a NICK message for a new
     * user. */
    if (strchr(source, '.'))
	*source = 0;
 
#ifdef IRC_UNDERNET
    if ((!*source && ac != 7) || (*source && ac != 2)) {
	if (debug) {
	    log("debug: NICK message: expecting 2 or 7 parameters after "
	        "parsing; got %d, source=`%s'", ac, source);
	}
	return;
#else /* IRC_BAHAMUT */
    if ((!*source && ac != 9) || (*source && ac != 2)) {
	if (debug) {
	    log("debug: NICK message: expecting 2 or 9 parameters after "
	        "parsing; got %d, source=`%s'", ac, source);
	}
	return;
    }

#endif
    }
    do_nick(source, ac, av);
}

/*************************************************************************/

static void m_part(char *source, int ac, char **av)
{
    if (ac < 1 || ac > 2)
	return;
    do_part(source, ac, av);
}

/*************************************************************************/

static void m_privmsg(char *source, int ac, char **av)
{
    time_t starttime, stoptime;	/* When processing started and finished */
    char *s;

    if (ac != 2)
	return;

    /* Check if we should ignore.  Operators always get through. */
    if (allow_ignore && !is_oper(source)) {
	IgnoreData *ign = get_ignore(source);
	if (ign && ign->time > time(NULL)) {
	    log("Ignored message from %s: \"%s\"", source, inbuf);
	    return;
	}
    }

    /* If a server is specified (nick@server format), make sure it matches
     * us, and strip it off. */
    s = strchr(av[0], '@');
    if (s) {
	*s++ = 0;
	if (stricmp(s, ServerName) != 0)
	    return;
    }

    starttime = time(NULL);

    if (stricmp(av[0], s_OperServ) == 0) {
	if (is_oper(source)) {
	    operserv(source, av[1]);
	} else {
	    User *u = finduser(source);
	    if (u) {
		notice_lang(s_OperServ, u, ACCESS_DENIED);
                if (!(u->mode & IGNORED))
                    canalopers(s_OperServ, "Denegando el acceso a %s desde %s (no es OPER)," 
                         " ignorando....", s_OperServ, source);
                u->mode |= IGNORED;         
            } else
               privmsg(s_OperServ, source, "Access denied.");
	}
    } else if (stricmp(av[0], s_NickServ) == 0) {
	nickserv(source, av[1]);
    } else if (stricmp(av[0], s_ChanServ) == 0) {
	chanserv(source, av[1]);
    } else if (stricmp(av[0], s_MemoServ) == 0) {
	memoserv(source, av[1]);
    } else if (stricmp(av[0], s_HelpServ) == 0) {
	helpserv(s_HelpServ, source, av[1]);
#ifdef CYBER
    } else if (stricmp(av[0], s_CyberServ) == 0) {
        cyberserv(source, av[1]);
#endif      
    } else if (s_IrcIIHelp && stricmp(av[0], s_IrcIIHelp) == 0) {
	char buf[BUFSIZE];
	snprintf(buf, sizeof(buf), "ircII %s", av[1]);
	helpserv(s_IrcIIHelp, source, buf);
    }

    /* Add to ignore list if the command took a significant amount of time. */
    if (allow_ignore) {
	stoptime = time(NULL);
	if (stoptime > starttime && *source && !strchr(source, '.'))
	    add_ignore(source, stoptime-starttime);
    }
}

/*************************************************************************/

static void m_quit(char *source, int ac, char **av)
{
    if (ac != 1)
	return;
    do_quit(source, ac, av);
}

/*************************************************************************/

static void m_server(char *source, int ac, char **av)
{
     do_server(source, ac, av);
     
}
    
/*************************************************************************/
     
static void m_squit(char *source, int ac, char **av)
{
     if (ac != 3)
         return;
              
     do_squit(source, ac, av);
                        
}

/*************************************************************************/

static void m_stats(char *source, int ac, char **av)
{
    if (ac < 1)
	return;
    switch (*av[0]) {
      case 'u': {
	int uptime = time(NULL) - start_time;
#ifdef IRC_UNDERNET
	send_cmd(ServerName, "242 %s :Services up %d day%s, %02d:%02d:%02d",
		source, uptime/86400, (uptime/86400 == 1) ? "" : "s",
		(uptime/3600) % 24, (uptime/60) % 60, uptime % 60);
	send_cmd(ServerName, "250 %s :Current users: %d (%d ops); maximum %d",
		source, usercnt, opcnt, maxusercnt);
	send_cmd(ServerName, "219 %s u :End of /STATS report.", source);
#else
	send_cmd(NULL, "242 %s :Services up %d day%s, %02d:%02d:%02d",
		source, uptime/86400, (uptime/86400 == 1) ? "" : "s",
		(uptime/3600) % 24, (uptime/60) % 60, uptime % 60);
	send_cmd(NULL, "250 %s :Current users: %d (%d ops); maximum %d",
		source, usercnt, opcnt, maxusercnt);
	send_cmd(NULL, "219 %s u :End of /STATS report.", source);

#endif
	break;
      } /* case 'u' */

      case 'l':
#ifdef IRC_UNDERNET
	send_cmd(ServerName, "211 %s Server SendBuf SentBytes SentMsgs RecvBuf "
		"RecvBytes RecvMsgs ConnTime", source);
	send_cmd(ServerName, "211 %s %s %d %d %d %d %d %d %ld", source, RemoteServer,
		read_buffer_len(), total_read, -1,
		write_buffer_len(), total_written, -1,
		start_time);
	send_cmd(ServerName, "219 %s l :End of /STATS report.", source);
#else
	send_cmd(NULL, "211 %s Server SendBuf SentBytes SentMsgs RecvBuf "
		"RecvBytes RecvMsgs ConnTime", source);
	send_cmd(NULL, "211 %s %s %d %d %d %d %d %d %ld", source, RemoteServer,
		read_buffer_len(), total_read, -1,
		write_buffer_len(), total_written, -1,
		start_time);
	send_cmd(NULL, "219 %s l :End of /STATS report.", source);

#endif
	break;

      case 'c':
      case 'h':
      case 'i':
      case 'k':
      case 'm':
      case 'o':
      case 'y':
	send_cmd(ServerName, "219 %s %c :/STATS %c not applicable or not supported.",
		source, *av[0], *av[0]);
	break;
    }
}

/*************************************************************************/

static void m_time(char *source, int ac, char **av)
{
    time_t t;
    struct tm *tm;
    char buf[64];

    time(&t);
    tm = localtime(&t);
    strftime(buf, sizeof(buf), "%a %b %d %H:%M:%S %Y %Z", tm);
    send_cmd(NULL, "391 :%s", buf);
}

/*************************************************************************/

static void m_topic(char *source, int ac, char **av)
{
    if (ac != 2)
	return;
    do_topic(source, ac, av);
}

/*************************************************************************/

static void m_user(char *source, int ac, char **av)
{

      /* En Undernet/Bahamut no existe este comando server-server
       * solo está para usuarios :)  */
}

/*************************************************************************/

void m_version(char *source, int ac, char **av)
{
    if (source)
	send_cmd(ServerName, "351 %s ircservices-%s+Terra-%s %s :[%s]",
            source, version_number, version_terra, ServerName, 
            version_branchstatus);
}

/*************************************************************************/

void m_whois(char *source, int ac, char **av)
{
    const char *clientdesc;

    if (source && ac >= 1) {
#ifdef IRC_UNDERNET
	if (stricmp(av[1], s_NickServ) == 0)
	    clientdesc = desc_NickServ;
	else if (stricmp(av[1], s_ChanServ) == 0)
	    clientdesc = desc_ChanServ;
	else if (stricmp(av[1], s_MemoServ) == 0)
	    clientdesc = desc_MemoServ;
	else if (stricmp(av[1], s_HelpServ) == 0)
	    clientdesc = desc_HelpServ;
#ifdef CYBER
        else if (stricmp(av[1], s_CyberServ) == 0)
            clientdesc = desc_CyberServ;
#endif 
	else if (s_IrcIIHelp && stricmp(av[1], s_IrcIIHelp) == 0)
	    clientdesc = desc_IrcIIHelp;
	else if (stricmp(av[1], s_OperServ) == 0)
	    clientdesc = desc_OperServ;
	else if (stricmp(av[1], s_GlobalNoticer) == 0)
	    clientdesc = desc_GlobalNoticer;
	else if (s_DevNull && stricmp(av[1], s_DevNull) == 0)
	    clientdesc = desc_DevNull;
#else /* IRC_BAHAMUT */
        if (stricmp(av[0], s_NickServ) == 0)
            clientdesc = desc_NickServ;
        else if (stricmp(av[0], s_ChanServ) == 0)
            clientdesc = desc_ChanServ;
        else if (stricmp(av[0], s_MemoServ) == 0)
            clientdesc = desc_MemoServ;
        else if (stricmp(av[0], s_HelpServ) == 0)
            clientdesc = desc_HelpServ;
#ifdef CYBER
        else if (stricmp(av[0], s_CyberServ) == 0)
            clientdesc = desc_CyberServ;
#endif
        else if (s_IrcIIHelp && stricmp(av[0], s_IrcIIHelp) == 0)
            clientdesc = desc_IrcIIHelp;
        else if (stricmp(av[0], s_OperServ) == 0)
            clientdesc = desc_OperServ;
        else if (stricmp(av[0], s_GlobalNoticer) == 0)
            clientdesc = desc_GlobalNoticer;
        else if (s_DevNull && stricmp(av[0], s_DevNull) == 0)
            clientdesc = desc_DevNull;
#endif
	else {
	    send_cmd(ServerName, "401 %s %s :No such service.", source, av[0]);
	    return;
	}
#ifdef IRC_UNDERNET
	send_cmd(ServerName, "311 %s %s %s %s :%s", source, av[1],
		ServiceUser, ServiceHost, clientdesc);
	send_cmd(ServerName, "312 %s %s %s :%s", source, av[1],
		ServerName, ServerDesc);
	send_cmd(ServerName, "309 %s %s :Es un bot oficial de la red",
	        source, av[1]);	
#else /* IRC_BAHAMUT */
        send_cmd(ServerName, "311 %s %s %s %s :%s", source, av[0],
                ServiceUser, ServiceHost, clientdesc);
        send_cmd(ServerName, "312 %s %s %s :%s", source, av[0],
                ServerName, ServerDesc);
        send_cmd(ServerName, "309 %s %s :Es un bot oficial de la red",
                source, av[0]);
#endif
	send_cmd(ServerName, "318 %s :End of /WHOIS response.", source);
    }
}

/*************************************************************************/
/************************ Bahamut Specific Functions *********************/
/*************************************************************************/

#ifdef IRC_BAHAMUT

static void m_sjoin(char *source, int ac, char **av)
{
    /* FIXME: this checking is an attempt to decipher SJOIN semantics. */
    if (ac < 5) {
	canalopers(NULL, "SJOIN error, wrong number of params! See log file.");
	log("SJOIN: expected atleast 5 params, got %d: %s",
			ac, strtok(NULL, ""));
	return;
    }
    do_sjoin(source, ac, av);
}

#endif /* IRC_BAHAMUT */

/*************************************************************************/
/*************************************************************************/

Message messages[] = {

    { "436",       m_nickcoll },
    { "ADMIN",     NULL },
    { "AWAY",      m_away },
    { "CLOSE",     NULL },
    { "CNOTICE",   NULL },
    { "CONNECT",   NULL },
    { "CPRIVMSG",  NULL },        
    { "DESTRUCT",  NULL },
    { "DESYNCH",   NULL },
    { "DIE",       NULL },
    { "DNS",       NULL },
    { "ERROR",     NULL },
    { "HASH",      NULL },    
    { "HELP",      NULL },
    { "INFO",      m_info },
    { "INVITE",    NULL },
    { "JOIN",      m_join },
    { "KICK",      m_kick },
    { "KILL",      m_kill },
    { "LINKS",     NULL },
    { "LIST",      NULL },
    { "LUSERS",    NULL },
    { "MAP",       NULL },    
    { "MODE",      m_mode },
    { "MOTD",      m_motd },
    { "NAMES",     NULL },
    { "NICK",      m_nick },
    { "NOTICE",    NULL },
    { "OPER",      NULL },    
    { "PART",      m_part },
    { "PASS",      NULL },
    { "PING",      m_ping },
    { "PONG",      NULL },    
    { "PRIVMSG",   m_privmsg },
    { "QUIT",      m_quit },
    { "REHASH",    NULL },
    { "RESTART",   NULL },
    { "RPING",     NULL },
    { "RPONG",     NULL },        
    { "SERVER",    m_server },
    { "SERVLIST",  NULL },
    { "SERVSET",   NULL },
    { "SILENCE",   NULL },    
    { "SQUIT",     m_squit },
    { "STATS",     m_stats },
    { "SETTIME",   NULL },    
    { "TIME",      m_time },
    { "TOPIC",     m_topic },
    { "TRACE",     NULL },
    { "UPING",     NULL },    
    { "USER",      m_user },
    { "VERSION",   m_version },
    { "WALLOPS",   NULL },
    { "WHO",       NULL },
    { "WHOIS",     m_whois },
    { "WHOWAS",    NULL },    

#ifdef IRC_UNDERNET
    { "GLINE",     NULL },
#endif

#ifdef IRC_BAHAMUT
    { "AKILL",     NULL },
    { "CAPAB",	   NULL },
    { "GLOBOPS",   NULL },
    { "GNOTICE",   NULL },
    { "GOPER",     NULL },
    { "SVINFO",    NULL },
    { "SJOIN",	   m_sjoin },
    { "SQLINE",	   NULL },
    { "RAKILL",    NULL },
#endif
    { NULL }

};

/*************************************************************************/

Message *find_message(const char *name)
{
    Message *m;

    for (m = messages; m->name; m++) {
	if (stricmp(name, m->name) == 0)
	    return m;
    }
    return NULL;
}

/*************************************************************************/

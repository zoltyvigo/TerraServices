/* Definitions of IRC message functions and list of messages.
 *
 * Services is copyright (c) 1996-1999 Andy Church.
 *     E-mail: <achurch@dragonfire.net>
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

    if (u && (ac == 0 || *av[0] == 0))	/* un-away */
	check_memos(u);
}

/*************************************************************************/

static void m_burst(char *source, int ac, char **av)
{

//     do_burst(source, ac, av);
     
}

/*************************************************************************/

static void m_create(char *source, int ac, char **av)
{

     do_create(source, ac, av);
     
}

/*************************************************************************/

static void m_end_of_burst(char *source, int ac, char **av)
{
     Server *server = find_servernumeric(source);

     if (!server)
         return;
         
     else if (stricmp(server->name, ServerHUB) == 0)
         send_cmd(NULL, "%c EB", convert2y[ServerNumeric]);
     else
         return;
}

/**************************************************************************/

static void m_eob_ack(char *source, int ac, char **av)
{
    Server *server = find_servernumeric(source);
        
    if (!server)
        return;
    else if (stricmp(server->name, ServerHUB) == 0)
        send_cmd(NULL, "%c EA", convert2y[ServerNumeric]);
    else
        return;
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
    if (stricmp(av[0], s_OperServP10) == 0 ||
        stricmp(av[0], s_NickServP10) == 0 ||
        stricmp(av[0], s_ChanServP10) == 0 ||
        stricmp(av[0], s_MemoServP10) == 0 ||
        stricmp(av[0], s_HelpServP10) == 0 ||
        (s_IrcIIHelp && stricmp(av[0], s_IrcIIHelpP10) == 0) ||
        (s_DevNull && stricmp(av[0], s_DevNullP10) == 0) ||
        stricmp(av[0], s_GlobalNoticerP10) == 0
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
    User *u = finduser(source);
    
    if (!u) 
        return;

    f = fopen(MOTDFilename, "r");
    send_cmd(ServerName, "375 %s :- %s Message of the Day",
		u->numeric, ServerName);
   if (f) {
	while (fgets(buf, sizeof(buf), f)) {
	    buf[strlen(buf)-1] = 0;
	    send_cmd(ServerName, "372 %s :- %s", u->numeric, buf);
	}
	fclose(f);
    } else {
	send_cmd(ServerName, "372 %s :- MOTD file not found!  Please "
			"contact your IRC administrator.", u->numeric);
    }

    /* Look, people.  I'm not asking for payment, praise, or anything like
     * that for using Services... is it too much to ask that I at least get
     * some recognition for my work?  Please don't remove the copyright
     * message below.
     */

    send_cmd(ServerName, "372 %s :-", u->numeric);
    send_cmd(ServerName, "372 %s :- Services is copyright (c) "
		"1996-1999 Andy Church.", u->numeric);
    send_cmd(ServerName, "376 %s :End of /MOTD command.", u->numeric);
}

/*************************************************************************/

static void m_nick(char *source, int ac, char **av)
{
    /* ircu sends the server as the source for a NICK message for a new
     * user. */
    if (strchr(source, '.'))
	*source = 0;

  /* En P10, el comando nick es mas largo de en otras redes :) */
    if ((ac != 8) && (ac != 9) && (ac != 2)) {
        if (debug) {
            log("debug: NICK message: expecting 2, 8 or 9 parameters after "
                   "parsing; got %d, source=%s'", ac, source);
        }
        return;
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

    if (stricmp(av[0], s_OperServP10) == 0) {
	if (is_oper(source)) {
	    operserv(source, av[1]);
	} else {
	    User *u = finduser(source);
	    if (u)
		notice_lang(s_OperServ, u, ACCESS_DENIED);
	    else
		privmsg(s_OperServ, source, "Acceso denegado.");
	    if (WallBadOS)
		wallops(s_OperServ, "Denied access to %s from %s (non-oper)",
			s_OperServ, source);
	}
    } else if (stricmp(av[0], s_NickServP10) == 0) {
	nickserv(source, av[1]);
    } else if (stricmp(av[0], s_ChanServP10) == 0) {
	chanserv(source, av[1]);
    } else if (stricmp(av[0], s_MemoServP10) == 0) {
	memoserv(source, av[1]);
    } else if (stricmp(av[0], s_HelpServP10) == 0) {
	helpserv(s_HelpServ, source, av[1]);
    } else if (s_IrcIIHelp && stricmp(av[0], s_IrcIIHelpP10) == 0) {
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
    User *u = finduser(source);
    if (ac < 1)
	return;
    	
    if (!u)
        return;
        	
    switch (*av[0]) {
      case 'u': {
	int uptime = time(NULL) - start_time;
	send_cmd(NULL, "242 %s :Services up %d day%s, %02d:%02d:%02d",
		u->numeric, uptime/86400, (uptime/86400 == 1) ? "" : "s",
		(uptime/3600) % 24, (uptime/60) % 60, uptime % 60);
	send_cmd(NULL, "250 %s :Current users: %d (%d ops); maximum %d",
		u->numeric, usercnt, opcnt, maxusercnt);
	send_cmd(NULL, "219 %s u :End of /STATS report.", u->numeric);
	break;
      } /* case 'u' */

      case 'l':
	send_cmd(NULL, "211 %s Server SendBuf SentBytes SentMsgs RecvBuf "
		"RecvBytes RecvMsgs ConnTime", u->numeric);
	send_cmd(NULL, "211 %s %s %d %d %d %d %d %d %ld", u->numeric, RemoteServer,
		read_buffer_len(), total_read, -1,
		write_buffer_len(), total_written, -1,
		start_time);
	send_cmd(NULL, "219 %s l :End of /STATS report.", u->numeric);
	break;

      case 'c':
      case 'h':
      case 'i':
      case 'k':
      case 'm':
      case 'o':
      case 'y':
	send_cmd(NULL, "219 %s %c :/STATS %c not applicable or not supported.",
		u->numeric, *av[0], *av[0]);
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
      /* En P10 no existe este comando server-server
       * solo está para usuarios :)  */
}

/*************************************************************************/

void m_version(char *source, int ac, char **av)
{
    if (source)
	send_cmd(ServerName, "351 %s TerraServices-%s %s :-- %s",
			source, version_number, ServerName, version_build);
}

/*************************************************************************/

void m_whois(char *source, int ac, char **av)
{
    const char *clientdesc;

    if (source && ac >= 1) {
	if (stricmp(av[0], s_NickServ) == 0)
	    clientdesc = desc_NickServ;
	else if (stricmp(av[0], s_ChanServ) == 0)
	    clientdesc = desc_ChanServ;
	else if (stricmp(av[0], s_MemoServ) == 0)
	    clientdesc = desc_MemoServ;
	else if (stricmp(av[0], s_HelpServ) == 0)
	    clientdesc = desc_HelpServ;
	else if (s_IrcIIHelp && stricmp(av[0], s_IrcIIHelp) == 0)
	    clientdesc = desc_IrcIIHelp;
	else if (stricmp(av[0], s_OperServ) == 0)
	    clientdesc = desc_OperServ;
	else if (stricmp(av[0], s_GlobalNoticer) == 0)
	    clientdesc = desc_GlobalNoticer;
	else if (s_DevNull && stricmp(av[0], s_DevNull) == 0)
	    clientdesc = desc_DevNull;
	else {
	    send_cmd(ServerName, "401 %s %s :No such service.", source, av[0]);
	    return;
	}
	send_cmd(ServerName, "311 %s %s %s %s :%s", source, av[0],
		ServiceUser, ServiceHost, clientdesc);
	send_cmd(ServerName, "312 %s %s %s :%s", source, av[0],
		ServerName, ServerDesc);
	send_cmd(ServerName, "318 End of /WHOIS response.");
    }
}

/*************************************************************************/
/*************************************************************************/

/* Pongo los tokens P10
 * zoltan
 */

Message messages[] = {

    { "436",       m_nickcoll }, /* Para pillar los colisiones de nick */
    { "ADMIN",     NULL },
    { "AD",        NULL },        
    { "AWAY",      m_away }, 
    { "A",         m_away },    
    { "BURST",     m_burst },
    { "B",         m_burst },
    { "CLOSE",      NULL },
    /* CLOSE no tiene token */        
    { "CNOTICE",   NULL },
    { "CN",        NULL },        
    { "CONNECT",   NULL },
    { "CO",        NULL },        
    { "CPRIVMSG",  NULL },
    { "CP",        NULL },            
    { "CREATE",    m_create },
    { "C",         m_create },   
    { "DESTRUCT",  NULL },
    { "DE",        NULL },        
    { "DESYNCH",   NULL },
    { "DS",        NULL },
    { "DIE",      NULL },
    /* DIE no tiene token */        
    { "DNS",       NULL },
    /* DNS no tiene token */                        
    { "END_OF_BURST", m_end_of_burst },
    { "EB",        m_end_of_burst },
    { "EOB_ACK",   m_eob_ack },
    { "EA",        m_eob_ack },
    { "ERROR",     NULL },
    { "Y",         NULL },  
    { "GLINE",     NULL },
    { "GL",        NULL },        
    { "HASH",      NULL },
    /* HASH no tiene token */                                      
    { "HELP",      NULL },
    /* HELP no tiene token */    
    { "INFO",      NULL },
    { "F",         NULL },        
    { "INVITE",    NULL },
    { "I",         NULL },        
    { "JOIN",      m_join },
    { "J",         m_join },
    { "KICK",      m_kick },
    { "K",         m_kick },
    { "KILL",      m_kill },
    { "D",         m_kill },
    { "LINKS",     NULL },
    { "LI",        NULL },            
    { "LIST",      NULL },
    /* LIST no tiene token */    
    { "LUSERS",    NULL },
    { "LU",        NULL },        
    { "MAP",       NULL },       
    /* MAP no tiene token */    
    { "MODE",      m_mode },
    { "M",         m_mode },
    { "MOTD",      m_motd },
    { "MO",        m_motd },
    { "NAMES",     NULL },
    { "E",         NULL },            
    { "NICK",      m_nick },
    { "N",         m_nick },
    { "NOTICE",    NULL },
    { "O",         NULL },
    { "OPER",      NULL },
    /* OPER no tiene token */        
    { "PART",      m_part },
    { "L",         m_part },
    { "PASS",      NULL },
    { "PA",        NULL },
    { "PING",      m_ping },
    { "G",         m_ping },
    { "PONG",      NULL },
    { "Z",         NULL },            
    { "PRIVMSG",   m_privmsg },
    { "P",         m_privmsg },    
    { "QUIT",      m_quit },
    { "Q",         m_quit },    
    { "REHASH",    NULL },
    /* REHASH no tiene token */
    { "RESTART",      NULL },
    /* RESTART no tiene token */                
    { "RPING",     NULL },
    { "RI",        NULL },
    { "RPONG",     NULL },
    { "RO",        NULL },                    
    { "SERVER",    m_server },
    { "S",         m_server },
    { "SERVLIST",  NULL },
    { "SERVSET",   NULL },   
    { "SILENCE",   NULL },
    { "U",         NULL },        
    { "SQUIT",     m_squit },
    { "SQ",        m_squit },    
    { "STATS",     m_stats },
    { "R",         m_stats },    
    { "SETTIME",   NULL },
    { "SE",        NULL },        
    { "TIME",      m_time },
    { "TI",        m_time },    
    { "TOPIC",     m_topic },
    { "T",         m_topic },
    { "TRACE",     NULL },
    { "TR",        NULL },        
    { "UPING",     NULL },
    { "UP",        NULL },        
    { "USER",      m_user },
    /* USER no tiene token */
    { "VERSION",   m_version },
    { "V",         m_version },    
    { "WALLCHOPS", NULL },
    { "WC",        NULL },        
    { "WALLOPS",   NULL },
    { "WA",        NULL },    
    { "WHO",       NULL },
    { "H",         NULL },        
    { "WHOIS",     m_whois },
    { "W",         m_whois },    
    { "WHOWAS",    NULL },
    { "X",         NULL },
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

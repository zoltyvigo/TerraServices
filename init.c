/* Initalization and related routines.
 *
 * Services is copyright (c) 1996-1999 Andrew Church.
 *     E-mail: <achurch@dragonfire.net>
 * Services is copyright (c) 1999-2000 Andrew Kempe.
 *     E-mail: <theshadow@shadowfire.org>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#include "services.h"

/*************************************************************************/

/* Send a NICK command for the given pseudo-client.  If `user' is NULL,
 * send NICK commands for all the pseudo-clients. */

#ifdef IRC_UNDERNET
# define NICK(nick,name) \
    do { \
	send_cmd(ServerName, "NICK %s 1 %ld %s %s %s :%s", (nick), time(NULL),\
		ServiceUser, ServiceHost, ServerName, (name)); \
    } while (0)
#else
/* IRC_BAHAMUT */
// NICK <nick> <hops> <TS> <umode> <user> <host> <server> <svsid> :<ircname>
#  define NICK(nick,name) \
    do { \
	send_cmd(NULL, "NICK %s 1 %ld + %s %s %s 0 :%s", (nick), time(NULL), \
		ServiceUser, ServiceHost, ServerName, (name)); \
    } while (0)
#endif

void introduce_user(const char *user)
{
    /* Watch out for infinite loops... */
#define LTSIZE 20
    static int lasttimes[LTSIZE];
    if (lasttimes[0] >= time(NULL)-3)
	fatal("introduce_user() loop detected");
    memmove(lasttimes, lasttimes+1, sizeof(lasttimes)-sizeof(int));
    lasttimes[LTSIZE-1] = time(NULL);
#undef LTSIZE

    if (!user || stricmp(user, s_NickServ) == 0) {
	NICK(s_NickServ, desc_NickServ);
	send_cmd(s_NickServ, "MODE %s +dkobB", s_NickServ);
        send_cmd(s_NickServ, "JOIN #%s", CanalOpers);
        send_cmd(s_NickServ, "MODE #%s +o %s", CanalOpers, s_NickServ);
    }
    if (!user || stricmp(user, s_ChanServ) == 0) {
	NICK(s_ChanServ, desc_ChanServ);
	send_cmd(s_ChanServ, "MODE %s +dkboB", s_ChanServ);
        send_cmd(s_ChanServ, "JOIN #%s", CanalOpers);	
        send_cmd(s_ChanServ, "MODE #%s +o %s", CanalOpers, s_ChanServ);        
    }
    if (!user || stricmp(user, s_HelpServ) == 0) {
	NICK(s_HelpServ, desc_HelpServ);
        send_cmd(s_HelpServ, "MODE %s +bdk", s_HelpServ);
        send_cmd(s_HelpServ, "JOIN #%s", CanalHelp);
        send_cmd(ServerName, "MODE #%s +v %s", CanalHelp, s_HelpServ);                        
    }
    if (s_IrcIIHelp && (!user || stricmp(user, s_IrcIIHelp) == 0)) {
	NICK(s_IrcIIHelp, desc_IrcIIHelp);
        send_cmd(s_IrcIIHelp, "MODE %s +bdk", s_IrcIIHelp);	
    }
    if (!user || stricmp(user, s_MemoServ) == 0) {
	NICK(s_MemoServ, desc_MemoServ);
	send_cmd(s_MemoServ, "MODE %s +bkd", s_MemoServ);
    }
    if (!user || stricmp(user, s_OperServ) == 0) {
	NICK(s_OperServ, desc_OperServ);
	send_cmd(s_OperServ, "MODE %s +oikbBd", s_OperServ);
        send_cmd(s_OperServ, "JOIN #%s", CanalOpers);	
        send_cmd(s_OperServ, "MODE #%s +o %s", CanalOpers, s_OperServ);
        send_cmd(s_OperServ, "JOIN #%s", CanalAdmins);      
        send_cmd(s_OperServ, "MODE #%s +o %s", CanalAdmins, s_OperServ);        
    }
    if (s_DevNull && (!user || stricmp(user, s_DevNull) == 0)) {
	NICK(s_DevNull, desc_DevNull);
	send_cmd(s_DevNull, "MODE %s +ibk", s_DevNull);
    }
    if (!user || stricmp(user, s_GlobalNoticer) == 0) {
	NICK(s_GlobalNoticer, desc_GlobalNoticer);
	send_cmd(s_GlobalNoticer, "MODE %s +oibdk", s_GlobalNoticer);
    }
    
#ifdef CYBER1
    if (!user || stricmp(user, s_CyberServ) == 0) {
        NICK(s_CyberServ, desc_CyberServ);
        send_cmd(s_CyberServ, "MODE %s +dkboB", s_CyberServ);
        send_cmd(s_CyberServ, "JOIN #%s", CanalOpers);
        send_cmd(s_CyberServ, "MODE #%s +o %s", CanalOpers, s_CyberServ);
        send_cmd(s_CyberServ, "JOIN #%s", CanalCybers);
        send_cmd(s_CyberServ, "MODE #%s +o %s", CanalCybers, s_CyberServ);
    }
#endif
}

#undef NICK

/*************************************************************************/

/* Set GID if necessary.  Return 0 if successful (or if RUNGROUP not
 * defined), else print an error message to logfile and return -1.
 */

static int set_group(void)
{
#if defined(RUNGROUP) && defined(HAVE_SETGRENT)
    struct group *gr;

    setgrent();
    while ((gr = getgrent()) != NULL) {
	if (strcmp(gr->gr_name, RUNGROUP) == 0)
	    break;
    }
    endgrent();
    if (gr) {
	setgid(gr->gr_gid);
	return 0;
    } else {
	log("Unknown group `%s'\n", RUNGROUP);
	return -1;
    }
#else
    return 0;
#endif
}

/*************************************************************************/

/* Parse command-line options for the "-dir" option only.  Return 0 if all
 * went well or -1 for a syntax error.
 */

/* XXX this could fail if we have "-some-option-taking-an-argument -dir" */

static int parse_dir_options(int ac, char **av)
{
    int i;
    char *s;

    for (i = 1; i < ac; i++) {
	s = av[i];
	if (*s == '-') {
	    s++;
	    if (strcmp(s, "dir") == 0) {
		if (++i >= ac) {
		    fprintf(stderr, "-dir requires a parameter\n");
		    return -1;
		}
		services_dir = av[i];
	    }
	}
    }
    return 0;
}

/*************************************************************************/

/* Parse command-line options.  Return 0 if all went well, -1 for an error
 * with an option, or 1 for -help.
 */

static int parse_options(int ac, char **av)
{
    int i;
    char *s, *t;

    for (i = 1; i < ac; i++) {
	s = av[i];
	if (*s == '-') {
	    s++;
	    if (strcmp(s, "remote") == 0) {
		if (++i >= ac) {
		    fprintf(stderr, "-remote requires hostname[:port]\n");
		    return -1;
		}
		s = av[i];
		t = strchr(s, ':');
		if (t) {
		    *t++ = 0;
		    if (atoi(t) > 0)
			RemotePort = atoi(t);
		    else {
			fprintf(stderr, "-remote: port number must be a positive integer.  Using default.");
			return -1;
		    }
		}
		RemoteServer = s;
	    } else if (strcmp(s, "local") == 0) {
		if (++i >= ac) {
		    fprintf(stderr, "-local requires hostname or [hostname]:[port]\n");
		    return -1;
		}
		s = av[i];
		t = strchr(s, ':');
		if (t) {
		    *t++ = 0;
		    if (atoi(t) >= 0)
			LocalPort = atoi(t);
		    else {
			fprintf(stderr, "-local: port number must be a positive integer or 0.  Using default.");
			return -1;
		    }
		}
		LocalHost = s;
	    } else if (strcmp(s, "name") == 0) {
		if (++i >= ac) {
		    fprintf(stderr, "-name requires a parameter\n");
		    return -1;
		}
		ServerName = av[i];
	    } else if (strcmp(s, "desc") == 0) {
		if (++i >= ac) {
		    fprintf(stderr, "-desc requires a parameter\n");
		    return -1;
		}
		ServerDesc = av[i];
	    } else if (strcmp(s, "user") == 0) {
		if (++i >= ac) {
		    fprintf(stderr, "-user requires a parameter\n");
		    return -1;
		}
		ServiceUser = av[i];
	    } else if (strcmp(s, "host") == 0) {
		if (++i >= ac) {
		    fprintf(stderr, "-host requires a parameter\n");
		    return -1;
		}
		ServiceHost = av[i];
	    } else if (strcmp(s, "dir") == 0) {
		/* Handled by parse_dir_options() */
		i++;  /* Skip parameter */
	    } else if (strcmp(s, "log") == 0) {
		if (++i >= ac) {
		    fprintf(stderr, "-log requires a parameter\n");
		    return -1;
		}
		log_filename = av[i];
	    } else if (strcmp(s, "update") == 0) {
		if (++i >= ac) {
		    fprintf(stderr, "-update requires a parameter\n");
		    return -1;
		}
		s = av[i];
		if (atoi(s) <= 0) {
		    fprintf(stderr, "-update: number of seconds must be positive");
		    return -1;
		} else
		    UpdateTimeout = atol(s);
	    } else if (strcmp(s, "expire") == 0) {
		if (++i >= ac) {
		    fprintf(stderr, "-expire requires a parameter\n");
		    return -1;
		}
		s = av[i];
		if (atoi(s) <= 0) {
		    fprintf(stderr, "-expire: number of seconds must be positive");
		    return -1;
		} else
		    ExpireTimeout = atol(s);
	    } else if (strcmp(s, "debug") == 0) {
		debug++;
	    } else if (strcmp(s, "readonly") == 0) {
		readonly = 1;
		skeleton = 0;
	    } else if (strcmp(s, "skeleton") == 0) {
		readonly = 0;
		skeleton = 1;
	    } else if (strcmp(s, "nofork") == 0) {
		nofork = 1;
	    } else if (strcmp(s, "forceload") == 0) {
		forceload = 1;
	    } else if (strcmp(s, "noexpire") == 0) {
		opt_noexpire = 1;
	    } else {
		fprintf(stderr, "Unknown option -%s\n", s);
		return -1;
	    }
	} else {
	    fprintf(stderr, "Non-option arguments not allowed\n");
	    return -1;
	}
    }
    return 0;
}

/*************************************************************************/

/* Remove our PID file.  Done at exit. */

static void remove_pidfile(void)
{
    remove(PIDFilename);
}

/*************************************************************************/

/* Create our PID file and write the PID to it. */

static void write_pidfile(void)
{
    FILE *pidfile;

    pidfile = fopen(PIDFilename, "w");
    if (pidfile) {
	fprintf(pidfile, "%d\n", (int)getpid());
	fclose(pidfile);
	atexit(remove_pidfile);
    } else {
	log_perror("Warning: cannot write to PID file %s", PIDFilename);
    }
}

/*************************************************************************/

/* Overall initialization routine.  Returns 0 on success, -1 on failure. */

int init(int ac, char **av)
{
    int i;
    int openlog_failed = 0, openlog_errno = 0;
    int started_from_term = isatty(0) && isatty(1) && isatty(2);

    /* Imported from main.c */
    extern void sighandler(int signum);


    /* Set file creation mask and group ID. */
#if defined(DEFUMASK) && HAVE_UMASK
    umask(DEFUMASK);
#endif
    if (set_group() < 0)
	return -1;
    
    /* Parse command line for -dir option. */
    parse_dir_options(ac, av);

    /* Chdir to Services data directory. */
    if (chdir(services_dir) < 0) {
	fprintf(stderr, "chdir(%s): %s\n", services_dir, strerror(errno));
	return -1;
    }

    /* Open logfile, and complain if we didn't. */
    if (open_log() < 0) {
	openlog_errno = errno;
	if (started_from_term) {
	    fprintf(stderr, "Warning: unable to open log file %s: %s\n",
			log_filename, strerror(errno));
	} else {
	    openlog_failed = 1;
	}
    }

    /* Read configuration file; exit if there are problems. */
    if (!read_config())
	return -1;

    /* Parse all remaining command-line options. */
    parse_options(ac, av);

    /* Detach ourselves if requested. */
    if (!nofork) {
	if ((i = fork()) < 0) {
	    perror("fork()");
	    return -1;
	} else if (i != 0) {
	    exit(0);
	}
	if (started_from_term) {
	    close(0);
	    close(1);
	    close(2);
	}
	if (setpgid(0, 0) < 0) {
	    perror("setpgid()");
	    return -1;
	}
    }

    /* Write our PID to the PID file. */
    write_pidfile();

    /* Announce ourselves to the logfile. */
    if (debug || readonly || skeleton) {
	log("Services %s (compiled for %s) starting up (options:%s%s%s)",
		version_number, version_protocol,
		debug ? " debug" : "", readonly ? " readonly" : "",
		skeleton ? " skeleton" : "");
    } else {
	log("Services %s (compiled for %s) starting up",
		version_number, version_protocol);
    }
    start_time = time(NULL);

    /* If in read-only mode, close the logfile again. */
    if (readonly)
	close_log();

    /* Set signal handlers.  Catch certain signals to let us do things or
     * panic as necessary, and ignore all others.
     */
#ifdef NSIG
    for (i = 1; i <= NSIG; i++)
#else
    for (i = 1; i <= 32; i++)
#endif
	signal(i, SIG_IGN);

    signal(SIGINT, sighandler);
    signal(SIGTERM, sighandler);
    signal(SIGQUIT, sighandler);
#ifndef DUMPCORE
    signal(SIGSEGV, sighandler);
#endif
    signal(SIGBUS, sighandler);
    signal(SIGQUIT, sighandler);
    signal(SIGHUP, sighandler);
    signal(SIGILL, sighandler);
    signal(SIGTRAP, sighandler);
#ifdef SIGIOT
    signal(SIGIOT, sighandler);
#endif
    signal(SIGFPE, sighandler);

    signal(SIGUSR1, sighandler);  /* This is our "out-of-memory" panic switch */

    /* Initialize multi-language support */
    lang_init();
    if (debug)
	log("debug: Loaded languages");

    /* Initialiize subservices */
    ns_init();
    cs_init();
    ms_init();
    os_init();
#ifdef CYBER
    cyber_init();
#endif         

    /* Load up databases */
    if (!skeleton) {
	load_ns_dbase();
	if (debug)
	    log("debug: Loaded %s database (1/6)", s_NickServ);
	load_cs_dbase();
	if (debug)
	    log("debug: Loaded %s database (2/6)", s_ChanServ);
    }
    load_os_dbase();
    if (debug)
	log("debug: Loaded %s database (3/6)", s_OperServ);
    load_akill();
    if (debug)
	log("debug: Loaded AKILL database (4/6)");
    load_news();
    if (debug)
	log("debug: Loaded news database (5/6)");
#ifdef CYBER
    load_cyber_dbase();
    if (debug)
        log("debug: Loaded Cyber database (6/6)");
#endif        
    log("Databases loaded");

    /* Connect to the remote server */
    servsock = conn(RemoteServer, RemotePort, LocalHost, LocalPort);
    if (servsock < 0)
	fatal_perror("Can't connect to server");
#ifdef IRC_UNDERNET
    send_cmd(NULL, "PASS :%s", RemotePassword);
    send_cmd(NULL, "SERVER %s 1 %lu %lu P09 :%s",
		ServerName, start_time, start_time, ServerDesc);
#else /* IRC_BAHAMUT */
    send_cmd(NULL, "PASS %s :TS", RemotePassword);
    send_cmd(NULL, "SERVER %s 1 :%s", ServerName, ServerDesc);
#endif
    sgets2(inbuf, sizeof(inbuf), servsock);
    if (strnicmp(inbuf, "ERROR", 5) == 0) {
	/* Close server socket first to stop wallops, since the other
	 * server doesn't want to listen to us anyway */
	disconn(servsock);
	servsock = -1;
	fatal("Remote server returned: %s", inbuf);
    }

#ifdef IRC_BAHAMUT
    send_cmd(NULL, "SVINFO 3 3 0 :%ld", time(NULL));
    send_cmd(NULL, "CAPAB: TS3");
#endif

    /* Announce a logfile error if there was one */
    if (openlog_failed) {
	canalopers(NULL, "Warning: couldn't open logfile: %s",
		strerror(openlog_errno));
    }

    /* Bring in our pseudo-clients */
    introduce_user(NULL);

#ifdef IRC_UNDERNET
    /* Sincroniza la red al tiempo real */
    send_cmd(ServerName, "SETTIME :%lu", time(NULL));
#endif    

    /* Manda global */
#ifdef PROVISIONAL    
#if HAVE_ALLWILD_NOTICE
    notice(s_GlobalNoticer, "$*", "Restablecidos los servicios de la red");
#else
# ifdef NETWORK_DOMAIN    
    notice(s_GlobalNoticer, "$*." NETWORK_DOMAIN, "Restablecidos los servicios de la red");
# else
    /* Go through all common top-level domains.  If you have others,
     * add them here.
     */
    notice(s_GlobalNoticer, "$*.es", "Restablecidos los servicios de la red");
    notice(s_GlobalNoticer, "$*.com", "Restablecidos los servicios de la red");
    notice(s_GlobalNoticer, "$*.net", "Restablecidos los servicios de la red");
    notice(s_GlobalNoticer, "$*.org", "Restablecidos los servicios de la red");
    notice(s_GlobalNoticer, "$*.edu", "Restablecidos los servicios de la red");
# endif
#endif
#endif
    /* Entra chan a los canales */
    if (CSInChannel)    
        join_chanserv();

    /* Success! */
    return 0;
}

/*************************************************************************/

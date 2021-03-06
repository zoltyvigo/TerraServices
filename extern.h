/* Prototypes and external variable declarations.
 *
 * Services is copyright (c) 1996-1999 Andrew Church.
 *     E-mail: <achurch@dragonfire.net>
 * Services is copyright (c) 1999-2000 Andrew Kempe.
 *     E-mail: <theshadow@shadowfire.org>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#ifndef EXTERN_H
#define EXTERN_H


#define E extern


/**** actions.c ****/

E void kill_user(const char *source, const char *user, const char *reason);
E void bad_password(User *u);


/**** akill.c ****/

E void get_akill_stats(long *nrec, long *memuse);
E int num_akills(void);
E void load_akill(void);
E void save_akill(void);
E int check_akill(const char *nick, const char *username, const char *host);
E void expire_akills(void);
E void do_akill(User *u);
E void add_akill(const char *mask, const char *reason, const char *who,
			const time_t expiry);

/**** channels.c ****/

#ifdef DEBUG_COMMANDS
E void send_channel_list(User *user);
E void send_channel_users(User *user);
#endif

E void get_channel_stats(long *nrec, long *memuse);
E Channel *findchan(const char *chan);
E Channel *firstchan(void);
E Channel *nextchan(void);

E void chan_adduser(User *user, const char *chan);
E void chan_deluser(User *user, Channel *c);

E void do_cmode(const char *source, int ac, char **av);
E void do_topic(const char *source, int ac, char **av);

E int only_one_user(const char *chan);


/**** chanserv.c ****/

E void listchans(int count_only, const char *chan);
E void get_chanserv_stats(long *nrec, long *memuse, long *nforbid, long *suspend, long *naccess, long *nakick, long *nmemos, long *nmemosnr);

E void cs_init(void);
E void chanserv(const char *source, char *buf);
E void load_cs_dbase(void);
E void save_cs_dbase(void);
E void check_modes(const char *chan);
E int check_valid_op(User *user, const char *chan, int newchan);
E int check_valid_voice(User *user, const char *chan, int newchan);
E int check_should_op(User *user, const char *chan);
E int check_should_voice(User *user, const char *chan);
E int check_leaveops(User *user, const char *chan, const char *source);
E int check_leavevoices(User *user, const char *chan, const char *source);
E int check_kick(User *user, const char *chan);
E void record_topic(const char *chan);
E void restore_topic(const char *chan);
E int check_topiclock(const char *chan);
E void expire_chans(void);
E void cs_remove_nick(const NickInfo *ni);

E ChannelInfo *cs_findchan(const char *chan);
E int check_access(User *user, ChannelInfo *ci, int what);
E void check_cs_access(User *u, NickInfo *ni);
E void join_chanserv();
E int is_services_bot(const char *nick);

/**** compat.c ****/

#if !HAVE_SNPRINTF
# if BAD_SNPRINTF
#  define snprintf my_snprintf
# endif
# define vsnprintf my_vsnprintf
E int vsnprintf(char *buf, size_t size, const char *fmt, va_list args);
E int snprintf(char *buf, size_t size, const char *fmt, ...);
#endif
#if !HAVE_STRICMP && !HAVE_STRCASECMP
E int stricmp(const char *s1, const char *s2);
E int strnicmp(const char *s1, const char *s2, size_t len);
#endif
#if !HAVE_STRDUP
E char *strdup(const char *s);
#endif
#if !HAVE_STRSPN
E size_t strspn(const char *s, const char *accept);
#endif
#if !HAVE_STRERROR
E char *strerror(int errnum);
#endif
#if !HAVE_STRSIGNAL
char *strsignal(int signum);
#endif


/**** config.c ****/

E char *RemoteServer;
E int   RemotePort;
E char *RemotePassword;
E char *LocalHost;
E int   LocalPort;

E char *ServerName;
E char *ServerDesc;
E char *ServerHUB;
E char *ServiceUser;
E char *ServiceHost;

E char *s_NickServ;
E char *s_ChanServ;
E char *s_MemoServ;
E char *s_HelpServ;
E char *s_CyberServ;
E char *s_OperServ;
E char *s_GlobalNoticer;
E char *s_IrcIIHelp;
E char *s_DevNull;
E char *desc_NickServ;
E char *desc_ChanServ;
E char *desc_MemoServ;
E char *desc_HelpServ;
E char *desc_CyberServ;
E char *desc_OperServ;
E char *desc_GlobalNoticer;
E char *desc_IrcIIHelp;
E char *desc_DevNull;

E char *PIDFilename;
E char *MOTDFilename;
E char *HelpDir;
E char *NickDBName;
E char *ChanDBName;
E char *OperDBName;
E char *AutokillDBName;
E char *NewsDBName;
E char *IlineDBName;

E char *SendMailPatch;
E char *SendFrom;
E char *WebNetwork;

E int   NoBackupOkay;
E int   NoSplitRecovery;
E int   StrictPasswords;
E int   BadPassLimit;
E int   BadPassTimeout;
E int   UpdateTimeout;
E int   ExpireTimeout;
E int   ReadTimeout;
E int   WarningTimeout;
E int   TimeoutCheck;
E int   SettimeTimeout;

E int   NSNicksMail;
E int   NSForceNickChange; 
E char *NSGuestNickPrefix;
E int   NSDefKill;
E int   NSDefKillQuick;
E int   NSDefSecure;
E int   NSDefPrivate;
E int   NSDefHideEmail;
E int   NSDefHideUsermask;
E int   NSDefHideQuit;
E int   NSDefMemoSignon;
E int   NSDefMemoReceive;
E int   NSRegDelay;
E int   NSPassChanged;
E int   NSExpire;
E int   NSAccessMax;
E char *NSEnforcerUser;
E char *NSEnforcerHost;
E int   NSReleaseTimeout;
E int   NSAllowKillImmed;
E int   NSDisableLinkCommand;
E int   NSListOpersOnly;
E int   NSListMax;
E int   NSSuspendExpire;
E int   NSSuspendGrace;

E int   CSInChannel;
E int   CSMaxReg;
E int   CSExpire;
E int   CSAccessMax;
E int   CSAutokickMax;
E char *CSAutokickReason;
E int   CSInhabit;
E int   CSRestrictDelay;
E int   CSListOpersOnly;
E int   CSListMax;
E int   CSSuspendExpire;
E int   CSSuspendGrace;

E int   MSMaxMemos;
E int   MSIgnoreMax;
E int   MSSendDelay;
E int   MSNotifyAll;

E char *CanalAdmins;
E char *CanalOpers;
E char *CanalHelp;
E char *ServicesRoot;
E int   LogMaxUsers;
E int   LogMaxChans;
E int   AutokillExpiry;
E char *StaticAkillReason;
E int   ImmediatelySendAkill;

E int   KillClonesAkillExpire;

E char *CanalCybers;
E int   ControlClones;
E int   LimiteClones;
E int   ExpIlineDefault;
E int   MaximoClones;
E int   CyberListMax;
E char *MensajeClones;
E char *WebClones;

E int read_config(void);


/**** correo.c ****/

E int send_mail(const char * destino, const char *subject, const char *body);


/**** cyberserv.c ****/

#ifdef CYBER
E void listilines(int count_only, const char *host);
E void get_clones_stats(long *nrec, long *memuse);
E void get_iline_stats(long *nrec, long *memuse, long *nsuspend, long *nipnofija, long *nvhost);

E void cyber_init(void);
E void cyberserv(const char *source, char *buf);
E void load_cyber_dbase(void);
E void save_cyber_dbase(void);
E void expire_ilines(void);

E int add_clones(const char *nick, const char *host);
E void del_clones(const char *host);
E Clones *findclones(const char *host);

E IlineInfo *find_iline_host(const char *host);
E IlineInfo *find_iline_admin(const char *nick);
E int is_cyber_admin(User *u);
E int nick_is_cyber_admin(NickInfo *ni);
E void cyber_remove_nick(const NickInfo *ni);
E void check_ip_iline(User *u);
E void check_cyber_iline(User *u, NickInfo *ni);
#endif

/**** helpserv.c ****/

E void helpserv(const char *whoami, const char *source, char *buf);


/**** init.c ****/

E void introduce_user(const char *user);
E int init(int ac, char **av);


/**** language.c ****/

E char **langtexts[NUM_LANGS];
E char *langnames[NUM_LANGS];
E int langlist[NUM_LANGS];

E void lang_init(void);
#define getstring(ni,index) \
	(langtexts[((ni)?((NickInfo*)ni)->language:DEF_LANGUAGE)][(index)])
E int strftime_lang(char *buf, int size, User *u, int format, struct tm *tm);
E void expires_in_lang(char *buf, int size, User *u, time_t seconds);
E void syntax_error(const char *service, User *u, const char *command,
		int msgnum);


/**** list.c ****/

E void do_listnicks(int ac, char **av);
E void do_listchans(int ac, char **av);
E void do_listilines(int ac, char **av);


/**** log.c ****/

E int open_log(void);
E void close_log(void);
E void log(const char *fmt, ...)		FORMAT(printf,1,2);
E void log_perror(const char *fmt, ...)		FORMAT(printf,1,2);
E void fatal(const char *fmt, ...)		FORMAT(printf,1,2);
E void fatal_perror(const char *fmt, ...)	FORMAT(printf,1,2);

E void rotate_log(User *u);


/**** main.c ****/

E const char version_branchstatus[];
E const char version_number[];
E const char version_terra[];
E const char version_build[];
E const char version_protocol[];
E const char *info_text[];

E char *services_dir;
E char *log_filename;
E int   debug;
E int   readonly;
E int   skeleton;
E int   nofork;
E int   forceload;
E int   opt_noexpire;

E int   quitting;
E int   delayed_quit;
E char *quitmsg;
E char  inbuf[BUFSIZE];
E int   servsock;
E int   save_data;
E int   got_alarm;
E time_t start_time;


/**** memory.c ****/

E void *smalloc(long size);
E void *scalloc(long elsize, long els);
E void *srealloc(void *oldptr, long newsize);
E char *sstrdup(const char *s);


/**** memoserv.c ****/

E void ms_init(void);
E void memoserv(const char *source, char *buf);
E void load_old_ms_dbase(void);
E void check_memos(User *u);
E void check_all_cs_memos(User *u);
E void check_cs_memos(User *u, ChannelInfo *ci);

/**** misc.c ****/

E char *strscpy(char *d, const char *s, size_t len);
E char *stristr(char *s1, char *s2);
E char *strupper(char *s);
E char *strlower(char *s);
E char *strLower(char *s);
E char *strnrepl(char *s, int32 size, const char *old, const char *new);
E int strCasecmp(const char *a, const char *b);
E int NTL_tolower_tab[];
E int NTL_toupper_tab[];
E char *strToken(char **save, char *str, char *fs);
E char *strTok(char *str, char *fs);

E char *merge_args(int argc, char **argv);

E int match_wild(const char *pattern, const char *str);
E int match_wild_nocase(const char *pattern, const char *str);

typedef int (*range_callback_t)(User *u, int num, va_list args);
E int process_numlist(const char *numstr, int *count_ret,
		range_callback_t callback, User *u, ...);
E int dotime(const char *s);


/**** news.c ****/

E void get_news_stats(long *nrec, long *memuse);
E void load_news(void);
E void save_news(void);
E void display_news(User *u, int16 type);
E void do_logonnews(User *u);
E void do_opernews(User *u);


/**** nickserv.c ****/

E void listnicks(int count_only, const char *nick);
E void get_nickserv_stats(long *nrec, long *memuse, long *nforbid, long *nsuspend, long *naccess, long *nignore, long *nmemos, long *nmemosnr);

E void ns_init(void);
E void nickserv(const char *source, char *buf);
E void load_ns_dbase(void);
E void save_ns_dbase(void);
E int validate_user(User *u);
E void cancel_user(User *u);
E int nick_identified(User *u);
E int nick_recognized(User *u);
E void expire_nicks(void);

E NickInfo *findnick(const char *nick);
E NickInfo *getlink(NickInfo *ni);


/**** operserv.c ****/

E void operserv(const char *source, char *buf);

E void os_init(void);
E void load_os_dbase(void);
E void save_os_dbase(void);
E int is_services_root(User *u);
E int is_services_admin(User *u);
E int is_services_oper(User *u);
E int is_services_devel(User *u); /* Una paranoia x"D */
E int nick_is_services_admin(NickInfo *ni);
E int nick_is_services_oper(NickInfo *ni);
E void os_remove_nick(const NickInfo *ni);

E void check_clones(User *user);


/**** process.c ****/

E int allow_ignore;
E IgnoreData *ignore[];

E void add_ignore(const char *nick, time_t delta);
E IgnoreData *get_ignore(const char *nick);

E int split_buf(char *buf, char ***argv, int colon_special);
E void process(void);


/**** send.c ****/

E void send_cmd(const char *source, const char *fmt, ...)
	FORMAT(printf,2,3);
E void vsend_cmd(const char *source, const char *fmt, va_list args)
	FORMAT(printf,2,0);
E void canalopers(const char *source, const char *fmt, ...);	
E void canaladmins(const char *source, const char *fmt, ...);
E void wallops(const char *source, const char *fmt, ...)
	FORMAT(printf,2,3);
E void notice(const char *source, const char *dest, const char *fmt, ...)
	FORMAT(printf,3,4);
E void notice_list(const char *source, const char *dest, const char **text);
E void notice_lang(const char *source, User *dest, int message, ...);
E void notice_help(const char *source, User *dest, int message, ...);
E void privmsg(const char *source, const char *dest, const char *fmt, ...)
	FORMAT(printf,3,4);
E void send_nick(const char *nick, const char *user, const char *host,
                const char *server, const char *name);

/**** servers.c ****/

E void get_server_stats(long *nrec, long *memuse);
E void do_server(const char *source, int ac, char **av);
E void do_squit(const char *source, int ac, char **av);
E Server *find_servername(const char *servername);
E Server *add_server(const char *servername);
E void del_server(Server *server);
E void recursive_squit(Server *parent, const char *reason);
E void del_users_server(Server *server);
E void do_servers(User *u);


/**** sockutil.c ****/

E int32 total_read, total_written;
E int32 read_buffer_len(void);
E int32 write_buffer_len(void);

E int sgetc(int s);
E char *sgets(char *buf, int len, int s);
E char *sgets2(char *buf, int len, int s);
E int sread(int s, char *buf, int len);
E int sputs(char *str, int s);
E int sockprintf(int s, char *fmt,...);
E int conn(const char *host, int port, const char *lhost, int lport);
E void disconn(int s);

/**** terra.c ****/

E char convert2y[];
E unsigned int base64toint(const char *s);
E const char *inttobase64(char *buf, unsigned int v, unsigned int count);
E void cifrado_tea(unsigned int v[], unsigned int k[], unsigned int x[]);
E const char *make_virtualhost(const char *host);
E const char *make_special_admin_host(const char *nick);
E const char *make_special_oper_host(const char *nick);
E const char *make_special_ircop_host(const char *nick);

/**** users.c ****/

E User *userlist[1024];

E int usercnt, chancnt, opcnt, maxusercnt, maxchancnt, servercnt;
E time_t maxusertime;
E time_t maxchantime;

#ifdef DEBUG_COMMANDS
E void send_user_list(User *user);
E void send_user_info(User *user);
#endif

E void get_user_stats(long *nusers, long *memuse);
E User *finduser(const char *nick);
E User *firstuser(void);
E User *nextuser(void);

E void do_nick(const char *source, int ac, char **av);
E void do_join(const char *source, int ac, char **av);
E void do_part(const char *source, int ac, char **av);
E void do_kick(const char *source, int ac, char **av);
E void do_umode(const char *source, int ac, char **av);
E void do_quit(const char *source, int ac, char **av);
E void do_kill(const char *source, int ac, char **av);

E int is_oper(const char *nick);
E int is_ChannelService(User *u);
E int is_hidden(User *u);
E int is_hiddenview(User *u);
E int is_on_chan(User *u, const char *chan);
E int is_chanop(const char *nick, Channel *c);
E int is_voiced(const char *nick, Channel *c);

E int match_usermask(const char *mask, User *user);
E int match_virtualmask(const char *mask, User *user);
E int match_cybermask(const char *mask, User *user);
E void split_usermask(const char *mask, char **nick, char **user, char **host);
E char *create_mask(User *u);

#endif	/* EXTERN_H */

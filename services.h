/* Main header for Services.
 *
 * Services is copyright (c) 1996-1999 Andy Church.
 *     E-mail: <achurch@dragonfire.net>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#ifndef SERVICES_H
#define SERVICES_H

/*************************************************************************/

#include "sysconf.h"
#include "config.h"

/* Some Linux boxes (or maybe glibc includes) require this for the
 * prototype of strsignal(). */
#define _GNU_SOURCE

/* Some AIX boxes define int16 and int32 on their own.  Blarph. */
#if INTTYPE_WORKAROUND
# define int16 builtin_int16
# define int32 builtin_int32
#endif

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <grp.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <setjmp.h>
#include <sys/socket.h>
#include <sys/stat.h>	/* for umask() on some systems */
#include <sys/types.h>
#include <sys/time.h>

#if HAVE_STRINGS_H
# include <strings.h>
#endif

#if HAVE_SYS_SELECT_H
# include <sys/select.h>
#endif

#ifdef _AIX
/* Some AIX boxes seem to have bogus includes that don't have these
 * prototypes. */
extern int strcasecmp(const char *, const char *);
extern int strncasecmp(const char *, const char *, size_t);
# if 0	/* These break on some AIX boxes (4.3.1 reported). */
extern int gettimeofday(struct timeval *, struct timezone *);
extern int socket(int, int, int);
extern int bind(int, struct sockaddr *, int);
extern int connect(int, struct sockaddr *, int);
extern int shutdown(int, int);
# endif
# undef FD_ZERO
# define FD_ZERO(p) memset((p), 0, sizeof(*(p)))
#endif /* _AIX */

/* Alias stricmp/strnicmp to strcasecmp/strncasecmp if we have the latter
 * but not the former. */
#if !HAVE_STRICMP && HAVE_STRCASECMP
# define stricmp strcasecmp
# define strnicmp strncasecmp
#endif

/* We have our own versions of toupper()/tolower(). */
#include <ctype.h>
#undef tolower
#undef toupper
#define tolower tolower_
#define toupper toupper_
extern int toupper(char), tolower(char);
#define toLower(c)      (NTL_tolower_tab[(c)-CHAR_MIN])
#define toUpper(c)      (NTL_toupper_tab[(c)-CHAR_MIN])

/* We also have our own encrypt(). */
#define encrypt encrypt_


#if INTTYPE_WORKAROUND
# undef int16
# undef int32
#endif


/* Miscellaneous definitions. */
#include "defs.h"

/*************************************************************************/

/* Configuration sanity-checking: */

#if CHANNEL_MAXREG > 32767
# undef CHANNEL_MAXREG
# define CHANNEL_MAXREG	0
#endif
#if DEF_MAX_MEMOS > 32767
# undef DEF_MAX_MEMOS
# define DEF_MAX_MEMOS	0
#endif
#if MAX_SERVOPERS > 32767
# undef MAX_SERVOPERS
# define MAX_SERVOPERS 32767
#endif
#if MAX_SERVADMINS > 32767
# undef MAX_SERVADMINS
# define MAX_SERVADMINS 32767
#endif

/*************************************************************************/
/*************************************************************************/

/* Version number for data files; if structures below change, increment
 * this.  (Otherwise -very- bad things will happen!) */

#define FILE_VERSION	7

/* Defino versiones de las DB de forma independiente... :) */

#define AKILL_VERSION   7
#define CHAN_VERSION    8
#define NICK_VERSION    9
#define OPER_VERSION    8
#define NEWS_VERSION    7
#ifdef CYBER
#define ILINE_VERSION   1
#endif
#ifdef CREG
#define CREG_VERSION    1
#endif

/*************************************************************************/
/* Estructura de los servidores */

typedef struct server_ Server;

struct server_ {
    Server *next, *prev;
    Server *hub;
    Server *hijo, *rehijo;
    int padre;
    char *name;
    int  users;
    char *numeric;
};


/*************************************************************************/

/* Memo info structures.  Since both nicknames and channels can have memos,
 * we encapsulate memo data in a MemoList to make it easier to handle. */

typedef struct memo_ Memo;
struct memo_ {
    uint32 number;	/* Index number -- not necessarily array position! */
    int16 flags;
    time_t time;	/* When it was sent */
    char sender[NICKMAX];
    char *text;
};

#define MF_UNREAD	0x0001	/* Memo has not yet been read */

typedef struct {
    int16 memocount, memomax;
    Memo *memos;
} MemoInfo;

/*************************************************************************/

/* Nickname info structure.  Each nick structure is stored in one of 256
 * lists; the list is determined by the first character of the nick.  Nicks
 * are stored in alphabetical order within lists. */


typedef struct mail_ Mail;
struct mail_ {
    Mail *next, *prev;
    char *domain;
};    
    


typedef struct nickinfo_ NickInfo;

struct nickinfo_ {
    NickInfo *next, *prev;
    char nick[NICKMAX];
    char pass[PASSMAX];
    char *url;
    char *email;
    char *emailreg;           /* Mail de registro del nick */    

    char *last_usermask;
    char *last_realname;
    char *last_quit;
    time_t time_registered;
    time_t last_seen;
//    time_t last_used_reg;      /* Ultimo REGISTRA/APOYO en Reg */
    int16 status;	/* See NS_* below */
    
    char *suspendby;           /* Quien lo suspendio */
    char *suspendreason;       /* Motivo de la suspension */
    time_t time_suspend;       /* Tiempo cuando suspendio el nick */
    time_t time_expiresuspend; /* Expiracion suspension */
    char *forbidby;            /* Quien lo forbideo */
    char *forbidreason;        /* Motivo del forbid */

    NickInfo *link;	/* If non-NULL, nick to which this one is linked */
    int16 linkcount;	/* Number of links to this nick */

    /* All information from this point down is governed by links.  Note,
     * however, that channelcount is always saved, even for linked nicks
     * (thus removing the need to recount channels when unlinking a nick). */

    int32 flags;	/* See NI_* below */

    int16 accesscount;	/* # of entries */
    char **access;	/* Array of strings */

    MemoInfo memos;

    uint16 channelcount;/* Number of channels currently registered */
    uint16 channelmax;	/* Maximum number of channels allowed */

    uint16 language;	/* Language selected by nickname owner (LANG_*) */

    time_t id_timestamp;/* TS8 timestamp of user who last ID'd for nick */
};


/* Nickname status flags: */
#define NS_ENCRYPTEDPW	0x0001      /* Nickname password is encrypted */
#define NS_VERBOTEN	0x0002      /* Nick may not be registered or used */
#define NS_NO_EXPIRE	0x0004      /* Nick never expires */
#define NS_SUSPENDED    0x0008      /* Nick SUSPENDido */

#define NS_IDENTIFIED	0x8000      /* User has IDENTIFY'd */
#define NS_RECOGNIZED	0x4000      /* ON_ACCESS true && SECURE flag not set */
#define NS_ON_ACCESS	0x2000      /* User comes from a known address */
#define NS_KILL_HELD	0x1000      /* Nick is being held after a kill */
#define NS_GUESTED	0x0100	    /* SVSNICK has been sent but nick has not
				     * yet changed. An enforcer will be
				     * introduced when it does change. */
#define NS_TEMPORARY	0xFF00      /* All temporary status flags */


/* Nickname setting flags: */
#define NI_KILLPROTECT	0x00000001  /* Kill others who take this nick */
#define NI_SECURE	0x00000002  /* Don't recognize unless IDENTIFY'd */
#define NI_MEMO_HARDMAX	0x00000008  /* Don't allow user to change memo limit */
#define NI_MEMO_SIGNON	0x00000010  /* Notify of memos at signon and un-away */
#define NI_MEMO_RECEIVE	0x00000020  /* Notify of new memos when sent */
#define NI_PRIVATE	0x00000040  /* Don't show in LIST to non-servadmins */
#define NI_HIDE_EMAIL	0x00000080  /* Don't show E-mail in INFO */
#define NI_HIDE_MASK	0x00000100  /* Don't show last seen address in INFO */
#define NI_HIDE_QUIT	0x00000200  /* Don't show last quit message in INFO */
#define NI_KILL_QUICK	0x00000400  /* Kill in 20 seconds instead of 60 */
#define NI_KILL_IMMED	0x00000800  /* Kill immediately instead of in 60 sec */
#define NI_REG_IGNORE	0x00001000  /* Nick IGNORADO para los apoyos/registros */

/* Languages.  Never insert anything in the middle of this list, or
 * everybody will start getting the wrong language!  If you want to change
 * the order the languages are displayed in for NickServ HELP SET LANGUAGE,
 * do it in language.c.
 */
#define LANG_ES         0       /* Castellano */
#define LANG_EN_US	1	/* United States English */
#define LANG_JA_JIS	2	/* Japanese (JIS encoding) */
#define LANG_JA_EUC	3	/* Japanese (EUC encoding) */
#define LANG_JA_SJIS	4	/* Japanese (SJIS encoding) */
#define LANG_PT		5	/* Portugese */
#define LANG_FR		6	/* French */
#define LANG_TR		7	/* Turkish */
#define LANG_IT		8	/* Italian */
#define LANG_CA         9       /* Catalan */
#define LANG_GA         10      /* Gallego */

#define NUM_LANGS	11	/* Number of languages */

/* Sanity-check on default language value */
#if DEF_LANGUAGE < 0 || DEF_LANGUAGE >= NUM_LANGS
# error Invalid value for DEF_LANGUAGE: must be >= 0 and < NUM_LANGS
#endif

/*************************************************************************/

/* Channel info structures.  Stored similarly to the nicks, except that
 * the second character of the channel name, not the first, is used to
 * determine the list.  (Hashing based on the first character of the name
 * wouldn't get very far. ;) ) */

/* Access levels for users. */
typedef struct {
    int16 in_use;	/* 1 if this entry is in use, else 0 */
    int16 level;
    NickInfo *ni;	/* Guaranteed to be non-NULL if in use, NULL if not */
} ChanAccess;

/* Note that these two levels also serve as exclusive boundaries for valid
 * access levels.  ACCESS_FOUNDER may be assumed to be strictly greater
 * than any valid access level, and ACCESS_INVALID may be assumed to be
 * strictly less than any valid access level.
 */
#define ACCESS_FOUNDER	500	/* Numeric level indicating founder access */
#define ACCESS_INVALID	-3	/* Used in levels[] for disabled settings */

/* AutoKick data. */
typedef struct {
    int16 in_use;
    int16 is_nick;	/* 1 if a regged nickname, 0 if a nick!user@host mask */
			/* Always 0 if not in use */
    union {
	char *mask;	/* Guaranteed to be non-NULL if in use, NULL if not */
	NickInfo *ni;	/* Same */
    } u;
    char *reason;
    char who[NICKMAX];  /* Nick de quien puso el akick */
} AutoKick;

typedef struct chaninfo_ ChannelInfo;
struct chaninfo_ {
    ChannelInfo *next, *prev;
    char name[CHANMAX];
    NickInfo *founder;
    NickInfo *successor;		/* Who gets the channel if the founder
					 * nick is dropped or expires */
    char founderpass[PASSMAX];
    char *desc;
    char *url;
    char *email;

    time_t time_registered;
    time_t last_used;
    char *last_topic;			/* Last topic on the channel */
    char last_topic_setter[NICKMAX];	/* Who set the last topic */
    time_t last_topic_time;		/* When the last topic was set */

    int32 flags;			/* See below */

    char *suspendby;                    /* Quien lo suspendio */
    char *suspendreason;                /* Motivo de la suspension */
    time_t time_suspend;                /* Tiempo cuando suspendio el nick */
    time_t time_expiresuspend;          /* Expiracion suspension */
    char *forbidby;                     /* Quien lo forbideo */
    char *forbidreason;                 /* Motivo del forbid */

    int16 *levels;			/* Access levels for commands */

    int16 accesscount;
    ChanAccess *access;			/* List of authorized users */
    int16 akickcount;
    AutoKick *akick;			/* List of users to kickban */

    int16 mlock_on, mlock_off;		/* See channel modes below */
    int32 mlock_limit;			/* 0 if no limit */
    char *mlock_key;			/* NULL if no key */

    char *entry_message;		/* Notice sent on entering channel */
    char entrymsg_setter[NICKMAX];      /* Quien ha puesto el entrymsg */

    MemoInfo memos;

    struct channel_ *c;			/* Pointer to channel record (if   *
					 *    channel is currently in use) */
};

/* Retain topic even after last person leaves channel */
#define CI_KEEPTOPIC	0x00000001
/* Don't allow non-authorized users to be opped */
#define CI_SECUREOPS	0x00000002
/* Hide channel from ChanServ LIST command */
#define CI_PRIVATE	0x00000004
/* Topic can only be changed by SET TOPIC */
#define CI_TOPICLOCK	0x00000008
/* Those not allowed ops are kickbanned */
#define CI_RESTRICTED	0x00000010
/* Don't auto-deop anyone */
#define CI_LEAVEOPS	0x00000020
/* Don't allow any privileges unless a user is IDENTIFY'd with NickServ */
#define CI_SECURE	0x00000040
/* Don't allow the channel to be registered or used */
#define CI_VERBOTEN	0x00000080
/* Channel password is encrypted */
#define CI_ENCRYPTEDPW	0x00000100
/* Channel does not expire */
#define CI_NO_EXPIRE	0x00000200
/* Channel memo limit may not be changed */
#define CI_MEMO_HARDMAX	0x00000400
/* Send notice to channel on use of OP/DEOP */
#define CI_OPNOTICE	0x00000800
/* Canal suspendido */
#define CI_SUSPENDED	0x00001000
/* Aviso de memos */
#define CI_MEMOALERT	0x00002000
/* Secure voices */
#define CI_SECUREVOICES	0x00004000
/* Leave Voices */
#define CI_LEAVEVOICES	0x00008000

/* Indices for cmd_access[]: */
#define CA_INVITE	0
#define CA_AKICK	1
#define CA_SET		2	/* but not FOUNDER or PASSWORD */
#define CA_UNBAN	3
#define CA_AUTOOP	4
#define CA_AUTODEOP	5	/* Maximum, not minimum */
#define CA_AUTOVOICE	6
#define CA_OPDEOP	7	/* ChanServ commands OP and DEOP */
#define CA_ACCESS_LIST	8
#define CA_CLEAR	9
#define CA_NOJOIN	10	/* Maximum */
#define CA_ACCESS_CHANGE 11
#define CA_MEMO_READ	12      /* Leer memos */
#define CA_MEMO_DEL	13      /* Borrar memos */
#define CA_AUTODEVOICE	14	/* Autodevoice */
#define CA_VOICEDEVOICE	15      /* Voice/devoice */
#define CA_KICK		16      /* kick */
#define CA_GETKEY	17	/* Dar la key del canal */

#define CA_SIZE		18

/*************************************************************************/

/* Online user and channel data. */

typedef struct user_ User;
typedef struct channel_ Channel;

struct user_ {
    User *next, *prev;
    char nick[NICKMAX];
    NickInfo *ni;			/* Effective NickInfo (not a link) */
    NickInfo *real_ni;			/* Real NickInfo (ni.nick==user.nick) */
    char *username;
    char *host;				/* User's hostname */
    char *realname;
    char *server;			/* Name of server user is on */
    time_t signon;			/* Time of signon (NOT nick change) */
    time_t my_signon;			/* When did _we_ see the user? */
    int32 mode;				/* See below */
    struct u_chanlist {
	struct u_chanlist *next, *prev;
	Channel *chan;
    } *chans;				/* Channels user has joined */
    struct u_chaninfolist {
	struct u_chaninfolist *next, *prev;
	ChannelInfo *chan;
    } *founder_chans;			/* Channels user has identified for */
    short invalid_pw_count;		/* # of invalid password attempts */
    time_t invalid_pw_time;		/* Time of last invalid password */
    time_t lastmemosend;		/* Last time MS SEND command used */
    time_t lastnickreg;			/* Last time NS REGISTER cmd used */
};

#define UMODE_O 0x00000001              /* IRCOP */
#define UMODE_I 0x00000002              /* Invisible */
#define UMODE_S 0x00000004              /* Noticias servidor */
#define UMODE_W 0x00000008              /* Wallops */
#define UMODE_G 0x00000010              /* Debug */
#define UMODE_R 0x00000020              /* Nick registrado */ 
#define UMODE_x 0x00000040              /* Ip virtual */
#define UMODE_X 0x00000080              /* Ver ips virtuales */
#define UMODE_H 0x00000100              /* Operador de la red */
#define UMODE_A 0x00000200              /* Administrador de la red */
#define UMODE_AWAY 0x00000400              /* MODO AWAY */

struct channel_ {
    Channel *next, *prev;
    char name[CHANMAX];
    ChannelInfo *ci;			/* Corresponding ChannelInfo */
    time_t creation_time;		/* When channel was created */

    char *topic;
    char topic_setter[NICKMAX];		/* Who set the topic */
    time_t topic_time;			/* When topic was set */

    int32 mode;				/* Binary modes only */
    int32 limit;			/* 0 if none */
    char *key;				/* NULL if none */

    int32 bancount, bansize;
    char **bans;

    struct c_userlist {
	struct c_userlist *next, *prev;
	User *user;
    } *users, *chanops, *voices;

    time_t server_modetime;		/* Time of last server MODE */
    time_t chanserv_modetime;		/* Time of last check_modes() */
    int16 server_modecount;		/* Number of server MODEs this second */
    int16 chanserv_modecount;		/* Number of check_mode()'s this sec */
    int16 bouncy_modes;			/* Did we fail to set modes here? */
};

#define CMODE_I 0x00000001
#define CMODE_M 0x00000002
#define CMODE_N 0x00000004
#define CMODE_P 0x00000008
#define CMODE_S 0x00000010
#define CMODE_T 0x00000020
#define CMODE_K 0x00000040		/* These two used only by ChanServ */
#define CMODE_L 0x00000080

/* The two modes below are for IRC_DAL4_4_15 servers only. */
#define CMODE_R 0x00000100		/* Only identified users can join */
#define CMODE_r 0x00000200		/* Set for all registered channels */


/*************************************************************************/
#ifdef CYBER
/* CyberServ, Control de clones y ilines */

typedef struct clones_ Clones;
struct clones_ {
    Clones *prev, *next;
    char *host;                        /* Host */
    int numeroclones;                  /* Numero de clones del host */
};
            
#define IL_IPNOFIJA     0x0001  /* Ip no fija */
#define IL_SUSPENDED	0x0002  /* Iline suspendida */
#define IL_NO_EXPIRE	0x0004  /* Iline indefinida */

typedef struct ilineinfo_ IlineInfo;
struct ilineinfo_ {
    IlineInfo *next, *prev;
    char *host;                 /* Host de la iline */
    char *host2;                /* Host 2º, para la ip numerica si hay Inversa */
    NickInfo *admin;            /* Nick del administrador */
    char *nombreadmin;          /* Nombre del admin */
    char *dniadmin;             /* DNI del admin */
    char *email;                /* Email del Admin */
    char *telefono;             /* Telefono */
    char *comentario;           /* Comentario */
    char *vhost;                /* Virtual host del ciber */
    char operwho[NICKMAX];      /* Admin que puso la iline */
    int16 limite;               /* Limite Iline */
    time_t time_concesion;
    time_t time_expiracion;
    int16 record_clones;
    time_t time_record;
    int16 estado;    
};
#endif
/*************************************************************************/
#ifdef CREG
/* Estructura de peticiones de registro en canales en medio de CregServ */

typedef struct {
    char nickapoyo[NICKMAX];
    char *emailapoyo;
    time_t time_apoyo;
} ApoyosCreg;
            
typedef struct {
     char nickoper[NICKMAX];
     char *marca;
     time_t time_marca;
} HistoryCreg;

struct creginfo_ {
    CregInfo *next, *prev;
    char name[CHANMAX];          /* Nombre del canal */
    char founder[NICKMAX];       /* Nick del founder */
    char *desc;                  /* Descripcion del canal */
    char *email;                 /* Email del founder */
    time_t time_peticion;        /* Hora de la peticion */

    char nickoper[NICKMAX];      /* Nick del OPER */
    time_t time_motivo;          /* Hora del cambio de estado del canal */
    char *motivo;                /* Motivo de la suspension, etc.. */
            
    char passapoyo[PASSMAX];     /* Contraseña de apoyo */
    time_t time_lastapoyo;       /* Hora del ultimo apoyo realizado */

    int32 estado;                /* Estado del canal :) CR_* */
    
    int16 apoyoscount;           /* Contador del numero de apoyos */
    ApoyosCreg *apoyos;          /* Lista de los apoyos realizados */
            
    int16 historycount;          /* Contador de Históricos */
    HistoryCreg *history;        /* Lista historico del canal */

};

/* Estados de las peticiones del canal  */
/* Canal en proceso de registro */
#define CR_PROCESO_REG  0x00000001
/* Canal ha expirado */
#define CR_EXPIRADO     0x00000002
/* Canal pendiente de aceptacion */
#define CR_PENDIENTE    0x00000004
/* Canal denegado */
#define CR_DENEGADO     0x00000008
/* Canal rechazado */
#define CR_RECHAZADO    0x00000010
/* Canal prohibido */
#define CR_PROHIBIDO    0x00000020
/* Canal dropado */
#define CR_DROPADO      0x00000040
/* Canal suspendido */
#define CR_SUSPENDIDO   0x00000080
/* Canal en estado desconocido */
#define CR_DESCONOCIDO  0x00000100
/* Canal aceptado y registrado en Chanserv */
#define CR_ACEPTADO     0x00000200
/* Canal registrado comericial */
#define CR_COMERCIAL    0x00000400
/* Canal registrado sin usar a creg */
#define CR_REGISTRADO   0x00000800
/* Canal registrado histórico */
#define CR_HISTORICO    0x00001000
                                                                                    
#endif                                                    


/* Who sends channel MODE (and KICK) commands? */
#if defined(IRC_DALNET) || (defined(IRC_UNDERNET) && !defined(IRC_UNDERNET_NEW))
# define MODE_SENDER(service) service
#else
# define MODE_SENDER(service) ServerName
#endif

#define NUMNICKLOG 6
#define NUMNICKBASE 64
#define NUMNICKMASK 63
#define NUMNICKMAXCHAR 'z'

/*************************************************************************/

/* Constants for news types. */

#define NEWS_LOGON	0
#define NEWS_OPER	1

/*************************************************************************/

/* Ignorance list data. */

typedef struct ignore_data {
    struct ignore_data *next;
    char who[NICKMAX];
    time_t time;	/* When do we stop ignoring them? */
} IgnoreData;

/*************************************************************************/

#include "extern.h"

/*************************************************************************/

#endif	/* SERVICES_H */

/* Services configuration.
 *
 * Services is copyright (c) 1996-1999 Andy Church.
 *     E-mail: <achurch@dragonfire.net>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#ifndef CONFIG_H
#define CONFIG_H

/* Note that most of the options which used to be here have been moved to
 * services.conf. */

/*************************************************************************/

/* Should we try and deal with old (v2.x) databases?  Define this if you're
 * upgrading from v2.2.26 or earlier. */
/* #define COMPATIBILITY_V2 */


/******* General configuration *******/

/* Name of configuration file (in Services directory) */
#define SERVICES_CONF	"services.conf"

/* Name of log file (in Services directory) */
#define LOG_FILENAME	"services.log"

/* Maximum amount of data from/to the network to buffer (bytes). */
#define NET_BUFSIZE	65536*32   /* 2 MB para Terra - zoltan */


/******* NickServ configuration *******/

/* Default language for newly registered nicks (and nicks imported from
 * old databases); see services.h for available languages (search for
 * "LANG_").  Unless you're running a regional network, you should probably
 * leave this at LANG_EN_US. */
#define DEF_LANGUAGE	LANG_ES /* ESPAÑOL para Terra - zoltan */


/******* OperServ configuration *******/

/* Registro de nicks vía mail */

#define REG_NICK_MAIL
#define MAILSPOOL "mailnick"
#define RUTA_SENDMAIL	"/usr/sbin/sendmail/"
#define SMTP_HOST	"mailhost.terra.es"
#define SMTP_PORT	"25"

/* Hay 3 formas de enviar correo, escoge una de estas */

#define SENDMAIL1

/* #define SENDMAIL2 */

/* #define SMTP */

/* Fin configuracion de correo */


/* What is the maximum number of Services admins we will allow? */
#define MAX_SERVADMINS	64    /* Terra - zoltan */

/* What is the maximum number of Services operators we will allow? */
#define MAX_SERVOPERS	256   /* Terra - zoltan */

/* How big a hostname list do we keep for clone detection?  On large nets
 * (over 500 simultaneous users or so), you may want to increase this if
 * you want a good chance of catching clones. */
#define CLONE_DETECT_SIZE 512 /* Terra - zoltan */

/* Define this to enable OperServ's debugging commands (Services root
 * only).  These commands are undocumented; "use the source, Luke!" */
/* #define DEBUG_COMMANDS */


/******************* END OF USER-CONFIGURABLE SECTION ********************/


/* Size of input buffer (note: this is different from BUFSIZ)
 * This must be big enough to hold at least one full IRC message, or messy
 * things will happen. */
#define BUFSIZE		1024 /* Suficiente, el ircu usa 512 */


/* Extra warning:  If you change these, your data files will be unusable! */

/* Maximum length of a channel name, including the trailing null.  Any
 * channels with a length longer than (CHANMAX-1) including the leading #
 * will not be usable with ChanServ. */
#define CHANMAX		200 /* El ircu usa 200 para los canales */

/* Maximum length of a nickname, including the trailing null.  This MUST be
 * at least one greater than the maximum allowable nickname length on your
 * network, or people will run into problems using Services!  The default
 * (32) works with all servers I know of. */
#define NICKMAX		32

/* Maximum length of a password */
#define PASSMAX		32

/**************************************************************************/

#endif	/* CONFIG_H */

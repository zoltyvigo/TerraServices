/* Initalization and related routines.
 *
 * Services is copyright (c) 1996-1999 Andrew Church.
 *     E-mail: <achurch@dragonfire.net>
 * Services is copyright (c) 1999-2000 Andrew Kempe.
 *     E-mail: <theshadow@shadowfire.org>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

/*************************************************************************/

/* Send a NICK command to the server with the appropriate formatting for
 * the type of server it is (dalnet, ircu, ircii, bahamut etc).
 */


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

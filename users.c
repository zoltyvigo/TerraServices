/* Routines to maintain a list of online users.
 *
 * Services is copyright (c) 1996-1999 Andy Church.
 *     E-mail: <achurch@dragonfire.net>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#include "services.h"

#define HASH(nick)	(((nick)[0]&31)<<5 | ((nick)[1]&31))
static User *userlist[1024];

int32 usercnt = 0, opcnt = 0, maxusercnt = 0;
time_t maxusertime;

/*************************************************************************/
/*************************************************************************/

/* Allocate a new User structure, fill in basic values, link it to the
 * overall list, and return it.  Always successful.
 */

static User *new_user(const char *nick)
{
    User *user, **list;

    user = scalloc(sizeof(User), 1);
    if (!nick)
	nick = "";
    strscpy(user->nick, nick, NICKMAX);
    list = &userlist[HASH(user->nick)];
    user->next = *list;
    if (*list)
	(*list)->prev = user;
    *list = user;
    user->real_ni = findnick(nick);
    if (user->real_ni)
	user->ni = getlink(user->real_ni);
    else
	user->ni = NULL;
    usercnt++;
    if (usercnt > maxusercnt) {
	maxusercnt = usercnt;
	maxusertime = time(NULL);
	if (LogMaxUsers)
	    log("user: New maximum user count: %d", maxusercnt);
    }
    return user;
}

/*************************************************************************/

/* Change the nickname of a user, and move pointers as necessary. */

static void change_user_nick(User *user, const char *nick)
{
    User **list;

    if (user->prev)
	user->prev->next = user->next;
    else
	userlist[HASH(user->nick)] = user->next;
    if (user->next)
	user->next->prev = user->prev;
    user->nick[1] = 0;	/* paranoia for zero-length nicks */
    strscpy(user->nick, nick, NICKMAX);
    list = &userlist[HASH(user->nick)];
    user->next = *list;
    user->prev = NULL;
    if (*list)
	(*list)->prev = user;
    *list = user;
    user->real_ni = findnick(nick);
    if (user->real_ni)
	user->ni = getlink(user->real_ni);
    else
	user->ni = NULL;
}

/*************************************************************************/

/* Remove and free a User structure. */

static void delete_user(User *user)
{
    struct u_chanlist *c, *c2;
    struct u_chaninfolist *ci, *ci2;

    if (debug >= 2)
	log("debug: delete_user() called");
    usercnt--;
    if (user->mode & UMODE_O)
	opcnt--;
    cancel_user(user);
    if (debug >= 2)
	log("debug: delete_user(): free user data");
    free(user->username);
    free(user->host);
    free(user->realname);
    free(user->server);
    if (debug >= 2)
	log("debug: delete_user(): remove from channels");
    c = user->chans;
    while (c) {
	c2 = c->next;
	chan_deluser(user, c->chan);
	free(c);
	c = c2;
    }
    if (debug >= 2)
	log("debug: delete_user(): free founder data");
    ci = user->founder_chans;
    while (ci) {
	ci2 = ci->next;
	free(ci);
	ci = ci2;
    }
    if (debug >= 2)
	log("debug: delete_user(): delete from list");
    if (user->prev)
	user->prev->next = user->next;
    else
	userlist[HASH(user->nick)] = user->next;
    if (user->next)
	user->next->prev = user->prev;
    if (debug >= 2)
	log("debug: delete_user(): free user structure");
    free(user);
    if (debug >= 2)
	log("debug: delete_user() done");
}

/*************************************************************************/
/*************************************************************************/

/* Return statistics.  Pointers are assumed to be valid. */

void get_user_stats(long *nusers, long *memuse)
{
    long count = 0, mem = 0;
    int i;
    User *user;
    struct u_chanlist *uc;
    struct u_chaninfolist *uci;

    for (i = 0; i < 1024; i++) {
	for (user = userlist[i]; user; user = user->next) {
	    count++;
	    mem += sizeof(*user);
	    if (user->username)
		mem += strlen(user->username)+1;
	    if (user->host)
		mem += strlen(user->host)+1;
	    if (user->realname)
		mem += strlen(user->realname)+1;
	    if (user->server)
		mem += strlen(user->server)+1;
	    for (uc = user->chans; uc; uc = uc->next)
		mem += sizeof(*uc);
	    for (uci = user->founder_chans; uci; uci = uci->next)
		mem += sizeof(*uci);
	}
    }
    *nusers = count;
    *memuse = mem;
}

/*************************************************************************/

#ifdef DEBUG_COMMANDS

/* Send the current list of users to the named user. */

void send_user_list(User *user)
{
    User *u;
    const char *source = user->nick;

    for (u = firstuser(); u; u = nextuser()) {
	char buf[BUFSIZE], *s;
	struct u_chanlist *c;
	struct u_chaninfolist *ci;

	notice(s_OperServ, source, "%s!%s@%s +%s%s%s%s%s %ld %s :%s",
		u->nick, u->username, u->host,
		(u->mode&UMODE_G)?"g":"", (u->mode&UMODE_I)?"i":"",
		(u->mode&UMODE_O)?"o":"", (u->mode&UMODE_S)?"s":"",
		(u->mode&UMODE_W)?"w":"", u->signon, u->server, u->realname);
	buf[0] = 0;
	s = buf;
	for (c = u->chans; c; c = c->next)
	    s += snprintf(s, sizeof(buf)-(s-buf), " %s", c->chan->name);
	notice(s_OperServ, source, "%s%s", u->nick, buf);
	buf[0] = 0;
	s = buf;
	for (ci = u->founder_chans; ci; ci = ci->next)
	    s += snprintf(s, sizeof(buf)-(s-buf), " %s", ci->chan->name);
	notice(s_OperServ, source, "%s%s", u->nick, buf);
    }
}


/* Send information about a single user to the named user.  Nick is taken
 * from strtok(). */

void send_user_info(User *user)
{
    char *nick = strtok(NULL, " ");
    User *u = nick ? finduser(nick) : NULL;
    char buf[BUFSIZE], *s;
    struct u_chanlist *c;
    struct u_chaninfolist *ci;
    const char *source = user->nick;

    if (!u) {
	notice(s_OperServ, source, "User %s not found!",
		nick ? nick : "(null)");
	return;
    }
    notice(s_OperServ, source, "%s!%s@%s +%s%s%s%s%s %ld %s :%s",
		u->nick, u->username, u->host,
		(u->mode&UMODE_G)?"g":"", (u->mode&UMODE_I)?"i":"",
		(u->mode&UMODE_O)?"o":"", (u->mode&UMODE_S)?"s":"",
		(u->mode&UMODE_W)?"w":"", u->signon, u->server, u->realname);
    buf[0] = 0;
    s = buf;
    for (c = u->chans; c; c = c->next)
	s += snprintf(s, sizeof(buf)-(s-buf), " %s", c->chan->name);
    notice(s_OperServ, source, "%s%s", u->nick, buf);
    buf[0] = 0;
    s = buf;
    for (ci = u->founder_chans; ci; ci = ci->next)
	s += snprintf(s, sizeof(buf)-(s-buf), " %s", ci->chan->name);
    notice(s_OperServ, source, "%s%s", u->nick, buf);
}

#endif	/* DEBUG_COMMANDS */

/*************************************************************************/

/* Find a user by nick.  Return NULL if user could not be found. */

User *finduser(const char *nick)
{
    User *user;

    if (debug >= 3)
	log("debug: finduser(%p)", nick);
    user = userlist[HASH(nick)];
    while (user && stricmp(user->nick, nick) != 0)
	user = user->next;
    if (debug >= 3)
	log("debug: finduser(%s) -> %p", nick, user);
    return user;
}

/*************************************************************************/

/* Iterate over all users in the user list.  Return NULL at end of list. */

static User *current;
static int next_index;

User *firstuser(void)
{
    next_index = 0;
    while (next_index < 1024 && current == NULL)
	current = userlist[next_index++];
    if (debug >= 3)
	log("debug: firstuser() returning %s",
			current ? current->nick : "NULL (end of list)");
    return current;
}

User *nextuser(void)
{
    if (current)
	current = current->next;
    if (!current && next_index < 1024) {
	while (next_index < 1024 && current == NULL)
	    current = userlist[next_index++];
    }
    if (debug >= 3)
	log("debug: nextuser() returning %s",
			current ? current->nick : "NULL (end of list)");
    return current;
}

/*************************************************************************/
/*************************************************************************/

/* Handle a server NICK command.
 *	av[0] = nick
 *	If a new user:
 *		av[1] = hop count
 *		av[2] = signon time
 *		av[3] = username
 *		av[4] = hostname
 *		av[5] = user's server
 *		av[6] = user's real name
 *	Else:
 *		av[1] = time of change
 */

void do_nick(const char *source, int ac, char **av)
{
    User *user;

    NickInfo *new_ni;	/* New master nick */
    int ni_changed = 1;	/* Did master nick change? */

    if (!*source) {
	/* This is a new user; create a User structure for it. */

	if (debug)
	    log("debug: new user: %s", av[0]);

	/* We used to ignore the ~ which a lot of ircd's use to indicate no
	 * identd response.  That caused channel bans to break, so now we
	 * just take what the server gives us.  People are still encouraged
	 * to read the RFCs and stop doing anything to usernames depending
	 * on the result of an identd lookup.
	 */

	/* First check for AKILLs. */
	if (check_akill(av[0], av[3], av[4]))
	    return;

#ifndef STREAMLINED
        /* Now check for session limits */
        if (LimitSessions && !add_session(av[0], av[4]))
            return;
#endif

	/* Allocate User structure and fill it in. */
	user = new_user(av[0]);
	user->signon = atol(av[2]);
	user->username = sstrdup(av[3]);
	user->host = sstrdup(av[4]);
	user->server = sstrdup(av[5]);
	user->realname = sstrdup(av[6]);
	user->my_signon = time(NULL);

	if (CheckClones) {
	    /* Check to see if it looks like clones. */
	    check_clones(user);
	}

	display_news(user, NEWS_LOGON);

    } else {
	/* An old user changing nicks. */

	user = finduser(source);
	if (!user) {
	    log("user: NICK from nonexistent nick %s: %s", source,
							merge_args(ac, av));
	    return;
	}
	if (debug)
	    log("debug: %s changes nick to %s", source, av[0]);

	/* Changing nickname case isn't a real change.  Only update
	 * my_signon if the nicks aren't the same, case-insensitively. */
	if (stricmp(av[0], user->nick) != 0)
	    user->my_signon = time(NULL);

	new_ni = findnick(av[0]);
	if (new_ni)
	    new_ni = getlink(new_ni);
	if (new_ni != user->ni)
	    cancel_user(user);
	else
	    ni_changed = 0;
	change_user_nick(user, av[0]);
    }

    if (ni_changed) {
	if (validate_user(user))
	    check_memos(user);
#ifdef IRC_DAL4_4_15
	if (nick_identified(user)) {
	    send_cmd(ServerName, "SVSMODE %s +r", av[0]);
	}
#endif
    }
}

/*************************************************************************/

/* Handle a JOIN command.
 *	av[0] = channels to join
 */

void do_join(const char *source, int ac, char **av)
{
    User *user;
    char *s, *t;
    struct u_chanlist *c, *nextc;
    ChannelInfo *ci;

    user = finduser(source);
    if (!user) {
	log("user: JOIN from nonexistent user %s: %s", source,
							merge_args(ac, av));
	return;
    }
    t = av[0];
    while (*(s=t)) {
	t = s + strcspn(s, ",");
	if (*t)
	    *t++ = 0;
	if (debug)
	    log("debug: %s joins %s", source, s);

	if (*s == '0') {
	    c = user->chans;
	    while (c) {
		nextc = c->next;
		chan_deluser(user, c->chan);
		free(c);
		c = nextc;
	    }
	    user->chans = NULL;
	    continue;
	}
	    
	/* Make sure check_kick comes before chan_adduser, so banned users
	 * don't get to see things like channel keys. */
	if (check_kick(user, s))
	    continue;
	chan_adduser(user, s);
	if ((ci = cs_findchan(s)) && ci->entry_message)
	    notice(s_ChanServ, user->nick, "%s", ci->entry_message);
	c = smalloc(sizeof(*c));
	c->next = user->chans;
	c->prev = NULL;
	if (user->chans)
	    user->chans->prev = c;
	user->chans = c;
	c->chan = findchan(s);
    }
}

/*************************************************************************/

/* Handle a PART command.
 *	av[0] = channels to leave
 *	av[1] = reason (optional)
 */

void do_part(const char *source, int ac, char **av)
{
    User *user;
    char *s, *t;
    struct u_chanlist *c;

    user = finduser(source);
    if (!user) {
	log("user: PART from nonexistent user %s: %s", source,
							merge_args(ac, av));
	return;
    }
    t = av[0];
    while (*(s=t)) {
	t = s + strcspn(s, ",");
	if (*t)
	    *t++ = 0;
	if (debug)
	    log("debug: %s leaves %s", source, s);
	for (c = user->chans; c && stricmp(s, c->chan->name) != 0; c = c->next)
	    ;
	if (c) {
	    if (!c->chan) {
		log("user: BUG parting %s: channel entry found but c->chan NULL"
			, s);
		return;
	    }
	    chan_deluser(user, c->chan);
	    if (c->next)
		c->next->prev = c->prev;
	    if (c->prev)
		c->prev->next = c->next;
	    else
		user->chans = c->next;
	    free(c);
	}
    }
}

/*************************************************************************/

/* Handle a KICK command.
 *	av[0] = channel
 *	av[1] = nick(s) being kicked
 *	av[2] = reason
 */

void do_kick(const char *source, int ac, char **av)
{
    User *user;
    char *s, *t;
    struct u_chanlist *c;

    t = av[1];
    while (*(s=t)) {
	t = s + strcspn(s, ",");
	if (*t)
	    *t++ = 0;
	user = finduser(s);
	if (!user) {
	    log("user: KICK for nonexistent user %s on %s: %s", s, av[0],
						merge_args(ac-2, av+2));
	    continue;
	}
	if (debug)
	    log("debug: kicking %s from %s", s, av[0]);
	for (c = user->chans; c && stricmp(av[0], c->chan->name) != 0;
								c = c->next)
	    ;
	if (c) {
	    chan_deluser(user, c->chan);
	    if (c->next)
		c->next->prev = c->prev;
	    if (c->prev)
		c->prev->next = c->next;
	    else
		user->chans = c->next;
	    free(c);
	}
    }
}

/*************************************************************************/

/* Handle a MODE command for a user.
 *	av[0] = nick to change mode for
 *	av[1] = modes
 */

void do_umode(const char *source, int ac, char **av)
{
    User *user;
    char *s;
    int add = 1;		/* 1 if adding modes, 0 if deleting */

    if (stricmp(source, av[0]) != 0) {
	log("user: MODE %s %s from different nick %s!", av[0], av[1], source);
	wallops(NULL, "%s attempted to change mode %s for %s",
		source, av[1], av[0]);
	return;
    }
    user = finduser(source);
    if (!user) {
	log("user: MODE %s for nonexistent nick %s: %s", av[1], source,
							merge_args(ac, av));
	return;
    }
    if (debug)
	log("debug: Changing mode for %s to %s", source, av[1]);
    s = av[1];
    while (*s) {
	switch (*s++) {
	    case '+': add = 1; break;
	    case '-': add = 0; break;
#ifdef IRC_DAL4_4_15
	    case 'r': 
	    	if (add && !nick_identified(user)) {
		    send_cmd(ServerName, "SVSMODE %s -r", av[0]);
		}
		break;
#endif
	    case 'i': add ? (user->mode |= UMODE_I) : (user->mode &= ~UMODE_I);
	              break;
	    case 'w': add ? (user->mode |= UMODE_W) : (user->mode &= ~UMODE_W);
	              break;
	    case 'g': add ? (user->mode |= UMODE_G) : (user->mode &= ~UMODE_G);
	              break;
	    case 's': add ? (user->mode |= UMODE_S) : (user->mode &= ~UMODE_S);
	              break;
	    case 'o':
		if (add) {
		    user->mode |= UMODE_O;
		    if (WallOper) {
			wallops(s_OperServ, "\2%s\2 is now an IRC operator.",
				user->nick);
		    }
		    display_news(user, NEWS_OPER);
		    opcnt++;
		} else {
		    user->mode &= ~UMODE_O;
		    opcnt--;
		}
		break;
	}
    }
}

/*************************************************************************/

/* Handle a QUIT command.
 *	av[0] = reason
 */

void do_quit(const char *source, int ac, char **av)
{
    User *user;
    NickInfo *ni;

    user = finduser(source);
    if (!user) {
	/* Reportedly Undernet IRC servers will sometimes send duplicate
	 * QUIT messages for quitting users, so suppress the log warning. */
#ifndef IRC_UNDERNET
	log("user: QUIT from nonexistent user %s: %s", source,
							merge_args(ac, av));
#endif
	return;
    }
    if (debug)
	log("debug: %s quits", source);
    if ((ni = user->ni) && (!(ni->status & NS_VERBOTEN)) &&
			(ni->status & (NS_IDENTIFIED | NS_RECOGNIZED))) {
	ni = user->real_ni;
	ni->last_seen = time(NULL);
	if (ni->last_quit)
	    free(ni->last_quit);
	ni->last_quit = *av[0] ? sstrdup(av[0]) : NULL;
    }
#ifndef STREAMLINED
    if (LimitSessions)
	del_session(user->host);
#endif
    delete_user(user);
}

/*************************************************************************/

/* Handle a KILL command.
 *	av[0] = nick being killed
 *	av[1] = reason
 */

void do_kill(const char *source, int ac, char **av)
{
    User *user;
    NickInfo *ni;

    user = finduser(av[0]);
    if (!user)
	return;
    if (debug)
	log("debug: %s killed", av[0]);
    if ((ni = user->ni) && (!(ni->status & NS_VERBOTEN)) &&
			(ni->status & (NS_IDENTIFIED | NS_RECOGNIZED))) {
	ni = user->real_ni;
	ni->last_seen = time(NULL);
	if (ni->last_quit)
	    free(ni->last_quit);
	ni->last_quit = *av[1] ? sstrdup(av[1]) : NULL;

    }
#ifndef STREAMLINED
    if (LimitSessions)
	del_session(user->host);
#endif
    delete_user(user);
}

/*************************************************************************/
/*************************************************************************/

/* Is the given nick an oper? */

int is_oper(const char *nick)
{
    User *user = finduser(nick);
    return user && (user->mode & UMODE_O);
}

/*************************************************************************/

/* Is the given nick on the given channel? */

int is_on_chan(const char *nick, const char *chan)
{
    User *u = finduser(nick);
    struct u_chanlist *c;

    if (!u)
	return 0;
    for (c = u->chans; c; c = c->next) {
	if (stricmp(c->chan->name, chan) == 0)
	    return 1;
    }
    return 0;
}

/*************************************************************************/

/* Is the given nick a channel operator on the given channel? */

int is_chanop(const char *nick, const char *chan)
{
    Channel *c = findchan(chan);
    struct c_userlist *u;

    if (!c)
	return 0;
    for (u = c->chanops; u; u = u->next) {
	if (stricmp(u->user->nick, nick) == 0)
	    return 1;
    }
    return 0;
}

/*************************************************************************/

/* Is the given nick voiced (channel mode +v) on the given channel? */

int is_voiced(const char *nick, const char *chan)
{
    Channel *c = findchan(chan);
    struct c_userlist *u;

    if (!c)
	return 0;
    for (u = c->voices; u; u = u->next) {
	if (stricmp(u->user->nick, nick) == 0)
	    return 1;
    }
    return 0;
}

/*************************************************************************/
/*************************************************************************/

/* Does the user's usermask match the given mask (either nick!user@host or
 * just user@host)?
 */

int match_usermask(const char *mask, User *user)
{
    char *mask2 = sstrdup(mask);
    char *nick, *username, *host, *nick2, *host2;
    int result;

    if (strchr(mask2, '!')) {
	nick = strlower(strtok(mask2, "!"));
	username = strtok(NULL, "@");
    } else {
	nick = NULL;
	username = strtok(mask2, "@");
    }
    host = strtok(NULL, "");
    if (!username || !host) {
	free(mask2);
	return 0;
    }
    strlower(host);
    host2 = strlower(sstrdup(user->host));
    if (nick) {
	nick2 = strlower(sstrdup(user->nick));
	result = match_wild(nick, nick2) &&
		 match_wild(username, user->username) &&
		 match_wild(host, host2);
	free(nick2);
    } else {
	result = match_wild(username, user->username) &&
		 match_wild(host, host2);
    }
    free(mask2);
    free(host2);
    return result;
}

/*************************************************************************/

/* Split a usermask up into its constitutent parts.  Returned strings are
 * malloc()'d, and should be free()'d when done with.  Returns "*" for
 * missing parts.
 */

void split_usermask(const char *mask, char **nick, char **user, char **host)
{
    char *mask2 = sstrdup(mask);

    *nick = strtok(mask2, "!");
    *user = strtok(NULL, "@");
    *host = strtok(NULL, "");
    /* Handle special case: mask == user@host */
    if (*nick && !*user && strchr(*nick, '@')) {
	*nick = NULL;
	*user = strtok(mask2, "@");
	*host = strtok(NULL, "");
    }
    if (!*nick)
	*nick = "*";
    if (!*user)
	*user = "*";
    if (!*host)
	*host = "*";
    *nick = sstrdup(*nick);
    *user = sstrdup(*user);
    *host = sstrdup(*host);
    free(mask2);
}

/*************************************************************************/

/* Given a user, return a mask that will most likely match any address the
 * user will have from that location.  For IP addresses, wildcards the
 * appropriate subnet mask (e.g. 35.1.1.1 -> 35.*; 128.2.1.1 -> 128.2.*);
 * for named addresses, wildcards the leftmost part of the name unless the
 * name only contains two parts.  If the username begins with a ~, delete
 * it.  The returned character string is malloc'd and should be free'd
 * when done with.
 */

char *create_mask(User *u)
{
    char *mask, *s, *end;

    /* Get us a buffer the size of the username plus hostname.  The result
     * will never be longer than this (and will often be shorter), thus we
     * can use strcpy() and sprintf() safely.
     */
    end = mask = smalloc(strlen(u->username) + strlen(u->host) + 2);
    end += sprintf(end, "%s@", u->username);
    if (strspn(u->host, "0123456789.") == strlen(u->host)
		&& (s = strchr(u->host, '.'))
		&& (s = strchr(s+1, '.'))
		&& (s = strchr(s+1, '.'))
		&& (   !strchr(s+1, '.'))) {	/* IP addr */
	s = sstrdup(u->host);
	*strrchr(s, '.') = 0;
	if (atoi(u->host) < 192)
	    *strrchr(s, '.') = 0;
	if (atoi(u->host) < 128)
	    *strrchr(s, '.') = 0;
	sprintf(end, "%s.*", s);
	free(s);
    } else {
	if ((s = strchr(u->host, '.')) && strchr(s+1, '.')) {
	    s = sstrdup(strchr(u->host, '.')-1);
	    *s = '*';
	} else {
	    s = sstrdup(u->host);
	}
	strcpy(end, s);
	free(s);
    }
    return mask;
}

/*************************************************************************/

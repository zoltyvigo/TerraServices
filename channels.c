/* Channel-handling routines.
 *
 * Services is copyright (c) 1996-1999 Andy Church.
 *     E-mail: <achurch@dragonfire.net>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#include "services.h"

#define HASH(chan)	((chan)[1] ? ((chan)[1]&31)<<5 | ((chan)[2]&31) : 0)
static Channel *chanlist[1024];

/*************************************************************************/

/* Return statistics.  Pointers are assumed to be valid. */

void get_channel_stats(long *nrec, long *memuse)
{
    long count = 0, mem = 0;
    Channel *chan;
    struct c_userlist *cu;
    int i, j;

    for (i = 0; i < 1024; i++) {
	for (chan = chanlist[i]; chan; chan = chan->next) {
	    count++;
	    mem += sizeof(*chan);
	    if (chan->topic)
		mem += strlen(chan->topic)+1;
	    if (chan->key)
		mem += strlen(chan->key)+1;
	    mem += sizeof(char *) * chan->bansize;
	    for (j = 0; j < chan->bancount; j++) {
		if (chan->bans[j])
		    mem += strlen(chan->bans[j])+1;
	    }
	    for (cu = chan->users; cu; cu = cu->next)
		mem += sizeof(*cu);
	    for (cu = chan->chanops; cu; cu = cu->next)
		mem += sizeof(*cu);
	    for (cu = chan->voices; cu; cu = cu->next)
		mem += sizeof(*cu);
	}
    }
    *nrec = count;
    *memuse = mem;
}

/*************************************************************************/

#ifdef DEBUG_COMMANDS

/* Send the current list of channels to the named user. */

void send_channel_list(User *user)
{
    Channel *c;
    char s[16], buf[512], *end;
    struct c_userlist *u, *u2;
    int isop, isvoice;
    const char *source = user->nick;

    for (c = firstchan(); c; c = nextchan()) {
	snprintf(s, sizeof(s), " %d", c->limit);
	notice(s_OperServ, source, "%s %lu +%s%s%s%s%s%s%s%s%s%s%s%s %s",
				c->name, c->creation_time,
				(c->mode&CMODE_I) ? "i" : "",
				(c->mode&CMODE_M) ? "m" : "",
				(c->mode&CMODE_N) ? "n" : "",
				(c->mode&CMODE_P) ? "p" : "",
				(c->mode&CMODE_S) ? "s" : "",
				(c->mode&CMODE_T) ? "t" : "",
#ifdef IRC_DAL4_4_15
				(c->mode&CMODE_R) ? "R" : "",
#else
				"",
#endif
				(c->limit)        ? "l" : "",
				(c->key)          ? "k" : "",
				(c->limit)        ?  s  : "",
				(c->key)          ? " " : "",
				(c->key)          ? c->key : "",
				c->topic ? c->topic : "");
	end = buf;
	end += snprintf(end, sizeof(buf)-(end-buf), "%s", c->name);
	for (u = c->users; u; u = u->next) {
	    isop = isvoice = 0;
	    for (u2 = c->chanops; u2; u2 = u2->next) {
		if (u2->user == u->user) {
		    isop = 1;
		    break;
		}
	    }
	    for (u2 = c->voices; u2; u2 = u2->next) {
		if (u2->user == u->user) {
		    isvoice = 1;
		    break;
		}
	    }
	    end += snprintf(end, sizeof(buf)-(end-buf),
					" %s%s%s", isvoice ? "+" : "",
					isop ? "@" : "", u->user->nick);
	}
	notice(s_OperServ, source, buf);
    }
}


/* Send list of users on a single channel, taken from strtok(). */

void send_channel_users(User *user)
{
    char *chan = strtok(NULL, " ");
    Channel *c = chan ? findchan(chan) : NULL;
    struct c_userlist *u;
    const char *source = user->nick;

    if (!c) {
	notice(s_OperServ, source, "Channel %s not found!",
		chan ? chan : "(null)");
	return;
    }
    notice(s_OperServ, source, "Channel %s users:", chan);
    for (u = c->users; u; u = u->next)
	notice(s_OperServ, source, "%s", u->user->nick);
    notice(s_OperServ, source, "Channel %s chanops:", chan);
    for (u = c->chanops; u; u = u->next)
	notice(s_OperServ, source, "%s", u->user->nick);
    notice(s_OperServ, source, "Channel %s voices:", chan);
    for (u = c->voices; u; u = u->next)
	notice(s_OperServ, source, "%s", u->user->nick);
}

#endif	/* DEBUG_COMMANDS */

/*************************************************************************/

/* Return the Channel structure corresponding to the named channel, or NULL
 * if the channel was not found.  chan is assumed to be non-NULL and valid
 * (i.e. pointing to a channel name of 2 or more characters). */

Channel *findchan(const char *chan)
{
    Channel *c;

    if (debug >= 3)
	log("debug: findchan(%p)", chan);
    c = chanlist[HASH(chan)];
    while (c) {
	if (stricmp(c->name, chan) == 0)
	    return c;
	c = c->next;
    }
    if (debug >= 3)
	log("debug: findchan(%s) -> %p", chan, c);
    return NULL;
}

/*************************************************************************/

/* Iterate over all channels in the channel list.  Return NULL at end of
 * list.
 */

static Channel *current;
static int next_index;

Channel *firstchan(void)
{
    next_index = 0;
    while (next_index < 1024 && current == NULL)
	current = chanlist[next_index++];
    if (debug >= 3)
	log("debug: firstchan() returning %s",
			current ? current->name : "NULL (end of list)");
    return current;
}

Channel *nextchan(void)
{
    if (current)
	current = current->next;
    if (!current && next_index < 1024) {
	while (next_index < 1024 && current == NULL)
	    current = chanlist[next_index++];
    }
    if (debug >= 3)
	log("debug: nextchan() returning %s",
			current ? current->name : "NULL (end of list)");
    return current;
}

/*************************************************************************/
/*************************************************************************/

/* Add/remove a user to/from a channel, creating or deleting the channel as
 * necessary.  If creating the channel, restore mode lock and topic as
 * necessary.  Also check for auto-opping and auto-voicing. */

void chan_adduser(User *user, const char *chan)
{
    Channel *c = findchan(chan);
    Channel **list;
    int newchan = !c;
    struct c_userlist *u;

    if (newchan) {
	if (debug)
	    log("debug: Creating channel %s", chan);
	/* Allocate pre-cleared memory */
	c = scalloc(sizeof(Channel), 1);
	strscpy(c->name, chan, sizeof(c->name));
	list = &chanlist[HASH(c->name)];
	c->next = *list;
	if (*list)
	    (*list)->prev = c;
	*list = c;
	c->creation_time = time(NULL);
	/* Store ChannelInfo pointer in channel record */
	c->ci = cs_findchan(chan);
	if (c->ci) {
	    /* This is a registered channel, ensure it's mode locked +r */
	    c->ci->mlock_on |= CMODE_r;
	    c->ci->mlock_off &= ~CMODE_r;	/* just to be safe */

	    /* Store return pointer in ChannelInfo record */
	    c->ci->c = c;
	}
	/* Restore locked modes and saved topic */
	check_modes(chan);
	restore_topic(chan);
    }
    if (check_should_op(user, chan)) {
	u = smalloc(sizeof(struct c_userlist));
	u->next = c->chanops;
	u->prev = NULL;
	if (c->chanops)
	    c->chanops->prev = u;
	c->chanops = u;
	u->user = user;
    } else if (check_should_voice(user, chan)) {
	u = smalloc(sizeof(struct c_userlist));
	u->next = c->voices;
	u->prev = NULL;
	if (c->voices)
	    c->voices->prev = u;
	c->voices = u;
	u->user = user;
    }
    u = smalloc(sizeof(struct c_userlist));
    u->next = c->users;
    u->prev = NULL;
    if (c->users)
	c->users->prev = u;
    c->users = u;
    u->user = user;
}


void chan_deluser(User *user, Channel *c)
{
    struct c_userlist *u;
    int i;

    for (u = c->users; u && u->user != user; u = u->next)
	;
    if (!u)
	return;
    if (u->next)
	u->next->prev = u->prev;
    if (u->prev)
	u->prev->next = u->next;
    else
	c->users = u->next;
    free(u);
    for (u = c->chanops; u && u->user != user; u = u->next)
	;
    if (u) {
	if (u->next)
	    u->next->prev = u->prev;
	if (u->prev)
	    u->prev->next = u->next;
	else
	    c->chanops = u->next;
	free(u);
    }
    for (u = c->voices; u && u->user != user; u = u->next)
	;
    if (u) {
	if (u->next)
	    u->next->prev = u->prev;
	if (u->prev)
	    u->prev->next = u->next;
	else
	    c->voices = u->next;
	free(u);
    }
    if (!c->users) {
	if (debug)
	    log("debug: Deleting channel %s", c->name);
	if (c->ci)
	    c->ci->c = NULL;
	if (c->topic)
	    free(c->topic);
	if (c->key)
	    free(c->key);
	for (i = 0; i < c->bancount; ++i) {
	    if (c->bans[i])
		free(c->bans[i]);
	    else
		log("channel: BUG freeing %s: bans[%d] is NULL!", c->name, i);
	}
	if (c->bansize)
	    free(c->bans);
	if (c->chanops || c->voices)
	    log("channel: Memory leak freeing %s: %s%s%s %s non-NULL!",
			c->name,
			c->chanops ? "c->chanops" : "",
			c->chanops && c->voices ? " and " : "",
			c->voices ? "c->voices" : "",
			c->chanops && c->voices ? "are" : "is");
	if (c->next)
	    c->next->prev = c->prev;
	if (c->prev)
	    c->prev->next = c->next;
	else
	    chanlist[HASH(c->name)] = c->next;
	free(c);
    }
}

/*************************************************************************/

/* Handle a channel MODE command. */

void do_cmode(const char *source, int ac, char **av)
{
    Channel *chan;
    struct c_userlist *u;
    User *user;
    char *s, *nick;
    int add = 1;		/* 1 if adding modes, 0 if deleting */
    char *modestr = av[1];

    chan = findchan(av[0]);
    if (!chan) {
	log("channel: MODE %s for nonexistent channel %s",
					merge_args(ac-1, av+1), av[0]);
	return;
    }

    /* This shouldn't trigger on +o, etc. */
    if (strchr(source, '.') && !modestr[strcspn(modestr, "bov")]) {
	if (time(NULL) != chan->server_modetime) {
	    chan->server_modecount = 0;
	    chan->server_modetime = time(NULL);
	}
	chan->server_modecount++;
    }

    s = modestr;
    ac -= 2;
    av += 2;

    while (*s) {

	switch (*s++) {

	case '+':
	    add = 1; break;

	case '-':
	    add = 0; break;

	case 'i':
	    if (add)
		chan->mode |= CMODE_I;
	    else
		chan->mode &= ~CMODE_I;
	    break;

	case 'm':
	    if (add)
		chan->mode |= CMODE_M;
	    else
		chan->mode &= ~CMODE_M;
	    break;

	case 'n':
	    if (add)
		chan->mode |= CMODE_N;
	    else
		chan->mode &= ~CMODE_N;
	    break;

	case 'p':
	    if (add)
		chan->mode |= CMODE_P;
	    else
		chan->mode &= ~CMODE_P;
	    break;

	case 's':
	    if (add)
		chan->mode |= CMODE_S;
	    else
		chan->mode &= ~CMODE_S;
	    break;

	case 't':
	    if (add)
		chan->mode |= CMODE_T;
	    else
		chan->mode &= ~CMODE_T;
	    break;

#ifdef IRC_DAL4_4_15
	case 'R':
	    if (add)
		chan->mode |= CMODE_R;
	    else
		chan->mode &= ~CMODE_R;
	    break;

	case 'r':
	    if (add)
		chan->mode |= CMODE_r;
	    else
		chan->mode &= ~CMODE_r;
	    break;
#endif

	case 'k':
	    if (--ac < 0) {
		log("channel: MODE %s %s: missing parameter for %ck",
					chan->name, modestr, add ? '+' : '-');
		break;
	    }
	    if (chan->key) {
		free(chan->key);
		chan->key = NULL;
	    }
	    if (add)
		chan->key = sstrdup(*av++);
	    break;

	case 'l':
	    if (add) {
		if (--ac < 0) {
		    log("channel: MODE %s %s: missing parameter for +l",
							chan->name, modestr);
		    break;
		}
		chan->limit = atoi(*av++);
	    } else {
		chan->limit = 0;
	    }
	    break;

	case 'b':
	    if (--ac < 0) {
		log("channel: MODE %s %s: missing parameter for %cb",
					chan->name, modestr, add ? '+' : '-');
		break;
	    }
	    if (add) {
		if (chan->bancount >= chan->bansize) {
		    chan->bansize += 8;
		    chan->bans = srealloc(chan->bans,
					sizeof(char *) * chan->bansize);
		}
		chan->bans[chan->bancount++] = sstrdup(*av++);
	    } else {
		char **s = chan->bans;
		int i = 0;
		while (i < chan->bancount && strcmp(*s, *av) != 0) {
		    i++;
		    s++;
		}
		if (i < chan->bancount) {
		    chan->bancount--;
		    if (i < chan->bancount)
			memmove(s, s+1, sizeof(char *) * (chan->bancount-i));
		}
		av++;
	    }
	    break;

	case 'o':
	    if (--ac < 0) {
		log("channel: MODE %s %s: missing parameter for %co",
					chan->name, modestr, add ? '+' : '-');
		break;
	    }
	    nick = *av++;
	    if (add) {
		for (u = chan->chanops; u && stricmp(u->user->nick, nick) != 0;
								u = u->next)
		    ;
		if (u)
		    break;
		user = finduser(nick);
		if (!user) {
		    log("channel: MODE %s +o for nonexistent user %s",
							chan->name, nick);
		    break;
		}
		if (debug)
		    log("debug: Setting +o on %s for %s", chan->name, nick);
		if (!check_valid_op(user, chan->name, !!strchr(source, '.')))
		    break;
		u = smalloc(sizeof(*u));
		u->next = chan->chanops;
		u->prev = NULL;
		if (chan->chanops)
		    chan->chanops->prev = u;
		chan->chanops = u;
		u->user = user;
	    } else {
		for (u = chan->chanops; u && stricmp(u->user->nick, nick);
								u = u->next)
		    ;
		if (!u)
		    break;
		if (u->next)
		    u->next->prev = u->prev;
		if (u->prev)
		    u->prev->next = u->next;
		else
		    chan->chanops = u->next;
		free(u);
	    }
	    break;

	case 'v':
	    if (--ac < 0) {
		log("channel: MODE %s %s: missing parameter for %cv",
					chan->name, modestr, add ? '+' : '-');
		break;
	    }
	    nick = *av++;
	    if (add) {
		for (u = chan->voices; u && stricmp(u->user->nick, nick);
								u = u->next)
		    ;
		if (u)
		    break;
		user = finduser(nick);
		if (!user) {
		    log("channe: MODE %s +v for nonexistent user %s",
							chan->name, nick);
		    break;
		}
		if (debug)
		    log("debug: Setting +v on %s for %s", chan->name, nick);
		u = smalloc(sizeof(*u));
		u->next = chan->voices;
		u->prev = NULL;
		if (chan->voices)
		    chan->voices->prev = u;
		chan->voices = u;
		u->user = user;
	    } else {
		for (u = chan->voices; u && stricmp(u->user->nick, nick);
								u = u->next)
		    ;
		if (!u)
		    break;
		if (u->next)
		    u->next->prev = u->prev;
		if (u->prev)
		    u->prev->next = u->next;
		else
		    chan->voices = u->next;
		free(u);
	    }
	    break;

	} /* switch */

    } /* while (*s) */

    /* Check modes against ChanServ mode lock */
    check_modes(chan->name);
}

/*************************************************************************/

/* Handle a TOPIC command. */

void do_topic(const char *source, int ac, char **av)
{
    Channel *c = findchan(av[0]);

    if (!c) {
	log("channel: TOPIC %s for nonexistent channel %s",
						merge_args(ac-1, av+1), av[0]);
	return;
    }
    if (check_topiclock(av[0]))
	return;
    strscpy(c->topic_setter, av[1], sizeof(c->topic_setter));
    c->topic_time = atol(av[2]);
    if (c->topic) {
	free(c->topic);
	c->topic = NULL;
    }
    if (ac > 3 && *av[3])
	c->topic = sstrdup(av[3]);
    record_topic(av[0]);
}

/*************************************************************************/

/* Does the given channel have only one user? */

/* Note:  This routine is not currently used, but is kept around in case it
 * might be handy someday. */

#if 0
int only_one_user(const char *chan)
{
    Channel *c = findchan(chan);
    return (c && c->users && !c->users->next) ? 1 : 0;
}
#endif

/*************************************************************************/

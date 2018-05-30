/* News functions.
 * Based on code by Andrew Kempe (TheShadow)
 *     E-mail: <theshadow@shadowfire.org>
 *
 * Services is copyright (c) 1996-1999 Andy Church.
 *     E-mail: <achurch@dragonfire.net>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#include "services.h"
#include "pseudo.h"

/*************************************************************************/

typedef struct newsitem_ NewsItem;
struct newsitem_ {
    int16 type;
    int32 num;		/* Numbering is separate for login and oper news */
    char *text;
    char who[NICKMAX];
    time_t time;
};

static int32 nnews = 0;
static int32 news_size = 0;
static NewsItem *news = NULL;

/*************************************************************************/

/* List of messages for each news type.  This simplifies message sending. */

#define MSG_SYNTAX	0
#define MSG_LIST_HEADER	1
#define MSG_LIST_ENTRY	2
#define MSG_LIST_NONE	3
#define MSG_ADD_SYNTAX	4
#define MSG_ADD_FULL	5
#define MSG_ADDED	6
#define MSG_DEL_SYNTAX	7
#define MSG_DEL_NOT_FOUND 8
#define MSG_DELETED	9
#define MSG_DEL_NONE	10
#define MSG_DELETED_ALL	11
#define MSG_MAX		11

struct newsmsgs {
    int16 type;
    char *name;
    int msgs[MSG_MAX+1];
};
struct newsmsgs msgarray[] = {
    { NEWS_LOGON, "LOGON",
	{ NEWS_LOGON_SYNTAX,
	  NEWS_LOGON_LIST_HEADER,
	  NEWS_LOGON_LIST_ENTRY,
	  NEWS_LOGON_LIST_NONE,
	  NEWS_LOGON_ADD_SYNTAX,
	  NEWS_LOGON_ADD_FULL,
	  NEWS_LOGON_ADDED,
	  NEWS_LOGON_DEL_SYNTAX,
	  NEWS_LOGON_DEL_NOT_FOUND,
	  NEWS_LOGON_DELETED,
	  NEWS_LOGON_DEL_NONE,
	  NEWS_LOGON_DELETED_ALL
	}
    },
    { NEWS_OPER, "OPER",
	{ NEWS_OPER_SYNTAX,
	  NEWS_OPER_LIST_HEADER,
	  NEWS_OPER_LIST_ENTRY,
	  NEWS_OPER_LIST_NONE,
	  NEWS_OPER_ADD_SYNTAX,
	  NEWS_OPER_ADD_FULL,
	  NEWS_OPER_ADDED,
	  NEWS_OPER_DEL_SYNTAX,
	  NEWS_OPER_DEL_NOT_FOUND,
	  NEWS_OPER_DELETED,
	  NEWS_OPER_DEL_NONE,
	  NEWS_OPER_DELETED_ALL
	}
    }
};

static int *findmsgs(int16 type, char **typename) {
    int i;
    for (i = 0; i < lenof(msgarray); i++) {
	if (msgarray[i].type == type) {
	    if (typename)
		*typename = msgarray[i].name;
	    return msgarray[i].msgs;
	}
    }
    return NULL;
}

/*************************************************************************/

/* Called by the main OperServ routine in response to a NEWS command. */
static void do_news(User *u, int16 type);

/* Lists all a certain type of news. */
static void do_news_list(User *u, int16 type, int *msgs);

/* Add news items. */ 
static void do_news_add(User *u, int16 type, int *msgs, const char *typename);
static int add_newsitem(User *u, const char *text, int16 type);

/* Delete news items. */
static void do_news_del(User *u, int16 type, int *msgs, const char *typename);
static int del_newsitem(int num, int16 type);

/*************************************************************************/
/****************************** Statistics *******************************/
/*************************************************************************/

void get_news_stats(long *nrec, long *memuse)
{
    long mem;
    int i;

    mem = sizeof(NewsItem) * news_size;
    for (i = 0; i < nnews; i++)
	mem += strlen(news[i].text)+1;
    *nrec = nnews;
    *memuse = mem;
}

/*************************************************************************/
/*********************** News item loading/saving ************************/
/*************************************************************************/

#define SAFE(x) do {					\
    if ((x) < 0) {					\
	if (!forceload)					\
	    fatal("Read error on %s", NewsDBName);	\
	nnews = i;					\
	break;						\
    }							\
} while (0)

void load_news()
{
    dbFILE *f;
    int i;
    int16 n;
    int32 tmp32;

    if (!(f = open_db(s_OperServ, NewsDBName, "r")))
	return;
    switch (i = get_file_version(f)) {
      case 7:
	SAFE(read_int16(&n, f));
	nnews = n;
	if (nnews < 8)
	    news_size = 16;
	else if (nnews >= 16384)
	    news_size = 32767;
	else
	    news_size = 2*nnews;
	news = smalloc(sizeof(*news) * news_size);
	if (!nnews) {
	    close_db(f);
	    return;
	}
	for (i = 0; i < nnews; i++) {
	    SAFE(read_int16(&news[i].type, f));
	    SAFE(read_int32(&news[i].num, f));
	    SAFE(read_string(&news[i].text, f));
	    SAFE(read_buffer(news[i].who, f));
	    SAFE(read_int32(&tmp32, f));
	    news[i].time = tmp32;
	}
	break;

      default:
	fatal("Unsupported version (%d) on %s", i, NewsDBName);
    } /* switch (ver) */

    close_db(f);
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do {						\
    if ((x) < 0) {						\
	restore_db(f);						\
	log_perror("Write error on %s", NewsDBName);		\
	if (time(NULL) - lastwarn > WarningTimeout) {		\
	    wallops(NULL, "Write error on %s: %s", NewsDBName,	\
			strerror(errno));			\
	    lastwarn = time(NULL);				\
	}							\
	return;							\
    }								\
} while (0)

void save_news()
{
    dbFILE *f;
    int i;
    static time_t lastwarn = 0;

    if (!(f = open_db(s_OperServ, NewsDBName, "w")))
	return;
    SAFE(write_int16(nnews, f));
    for (i = 0; i < nnews; i++) {
	SAFE(write_int16(news[i].type, f));
	SAFE(write_int32(news[i].num, f));
	SAFE(write_string(news[i].text, f));
	SAFE(write_buffer(news[i].who, f));
	SAFE(write_int32(news[i].time, f));
    }
    close_db(f);
}

#undef SAFE

/*************************************************************************/
/***************************** News display ******************************/
/*************************************************************************/

void display_news(User *u, int16 type)
{
    int i;
    int count = 0;	/* Number we're going to show--not more than 3 */
    int msg;

    if (type == NEWS_LOGON) {
	msg = NEWS_LOGON_TEXT;
    } else if (type == NEWS_OPER) {
	msg = NEWS_OPER_TEXT;
    } else {
	log("news: Invalid type (%d) to display_news()", type);
	return;
    }

    for (i = nnews-1; i >= 0; i--) {
	if (count >= 3)
	    break;
	if (news[i].type == type)
	    count++;
    }
    while (++i < nnews) {
	if (news[i].type == type) {
	    struct tm *tm;
	    char timebuf[64];

	    tm = localtime(&news[i].time);
	    strftime_lang(timebuf, sizeof(timebuf), u,
				STRFTIME_SHORT_DATE_FORMAT, tm);
	    notice_lang(s_GlobalNoticer, u, msg, timebuf, news[i].text);
	}
    }
}

/*************************************************************************/
/***************************** News editing ******************************/
/*************************************************************************/

/* Declared in extern.h */
void do_logonnews(User *u)
{
    do_news(u, NEWS_LOGON);
}

/* Declared in extern.h */
void do_opernews(User *u)
{
    do_news(u, NEWS_OPER);
}

/*************************************************************************/

/* Main news command handling routine. */
void do_news(User *u, short type)
{
    int is_servadmin = is_services_admin(u);
    char *cmd = strtok(NULL, " ");
    char *typename;
    int *msgs;

    msgs = findmsgs(type, &typename);
    if (!msgs) {
	log("news: Invalid type to do_news()");
	return;
    }

    if (!cmd)
	cmd = "";

    if (stricmp(cmd, "LIST") == 0) {
	do_news_list(u, type, msgs);

    } else if (stricmp(cmd, "ADD") == 0) {
	if (is_servadmin)
	    do_news_add(u, type, msgs, typename);
	else
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);

    } else if (stricmp(cmd, "DEL") == 0) {
	if (is_servadmin)
	    do_news_del(u, type, msgs, typename);
	else
	    notice_lang(s_OperServ, u, PERMISSION_DENIED);

    } else {
	char buf[32];
	snprintf(buf, sizeof(buf), "%sNEWS", typename);
	syntax_error(s_OperServ, u, buf, msgs[MSG_SYNTAX]);
    }
}

/*************************************************************************/

/* Handle a {LOGON,OPER}NEWS LIST command. */

static void do_news_list(User *u, int16 type, int *msgs)
{
    int i, count = 0;
    char timebuf[64];
    struct tm *tm;

    for (i = 0; i < nnews; i++) {
	if (news[i].type == type) {
	    if (count == 0)
		notice_lang(s_OperServ, u, msgs[MSG_LIST_HEADER]);
	    tm = localtime(&news[i].time);
	    strftime_lang(timebuf, sizeof(timebuf),
				u, STRFTIME_DATE_TIME_FORMAT, tm);
	    notice_lang(s_OperServ, u, msgs[MSG_LIST_ENTRY],
				news[i].num, timebuf,
				*news[i].who ? news[i].who : "<unknown>",
				news[i].text);
	    count++;
	}
    }
    if (count == 0)
	notice_lang(s_OperServ, u, msgs[MSG_LIST_NONE]);
}

/*************************************************************************/

/* Handle a {LOGON,OPER}NEWS ADD command. */

static void do_news_add(User *u, int16 type, int *msgs, const char *typename)
{
    char *text = strtok(NULL, "");

    if (!text) {
	char buf[32];
	snprintf(buf, sizeof(buf), "%sNEWS", typename);
	syntax_error(s_OperServ, u, buf, msgs[MSG_ADD_SYNTAX]);
    } else {
	int n = add_newsitem(u, text, type);
	if (n < 0)
	    notice_lang(s_OperServ, u, msgs[MSG_ADD_FULL]);
	else
	    notice_lang(s_OperServ, u, msgs[MSG_ADDED], n);
	if (readonly)
	    notice_lang(s_OperServ, u, READ_ONLY_MODE);
    }
}


/* Actually add a news item.  Return the number assigned to the item, or -1
 * if the news list is full (32767 items).
 */

static int add_newsitem(User *u, const char *text, short type)
{
    int i, num;

    if (nnews >= 32767)
	return -1;

    if (nnews >= news_size) {
	if (news_size < 8)
	    news_size = 8;
	else
	    news_size *= 2;
	news = srealloc(news, sizeof(*news) * news_size);
    }
    num = 0;
    for (i = nnews-1; i >= 0; i--) {
	if (news[i].type == type) {
	    num = news[i].num;
	    break;
	}
    }
    news[nnews].type = type;
    news[nnews].num = num+1;
    news[nnews].text = sstrdup(text);
    news[nnews].time = time(NULL);
    strscpy(news[nnews].who, u->nick, NICKMAX);
    nnews++;
    return num+1;
}

/*************************************************************************/

/* Handle a {LOGON,OPER}NEWS DEL command. */

static void do_news_del(User *u, int16 type, int *msgs, const char *typename)
{
    char *text = strtok(NULL, " ");

    if (!text) {
	char buf[32];
	snprintf(buf, sizeof(buf), "%sNEWS", typename);
	syntax_error(s_OperServ, u, buf, msgs[MSG_DEL_SYNTAX]);
    } else {
	if (stricmp(text, "ALL") != 0) {
	    int num = atoi(text);
	    if (num > 0 && del_newsitem(num, type))
		notice_lang(s_OperServ, u, msgs[MSG_DELETED], num);
	    else
		notice_lang(s_OperServ, u, msgs[MSG_DEL_NOT_FOUND], num);
	} else {
	    if (del_newsitem(0, type))
		notice_lang(s_OperServ, u, msgs[MSG_DELETED_ALL]);
	    else
		notice_lang(s_OperServ, u, msgs[MSG_DEL_NONE]);
	}
	if (readonly)
	    notice_lang(s_OperServ, u, READ_ONLY_MODE);
    }
}


/* Actually delete a news item.  If `num' is 0, delete all news items of
 * the given type.  Returns the number of items deleted.
 */

static int del_newsitem(int num, short type)
{
    int i;
    int count = 0;

    for (i = 0; i < nnews; i++) {
	if (news[i].type == type && (num == 0 || news[i].num == num)) {
	    free(news[i].text);
	    count++;
	    nnews--;
	    if (i < nnews)
		memcpy(news+i, news+i+1, sizeof(*news) * (nnews-i));
	    i--;
	}
    }
    return count;
}

/*************************************************************************/

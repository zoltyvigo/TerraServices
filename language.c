/* Multi-language support.
 *
 * Services is copyright (c) 1996-1999 Andrew Church.
 *     E-mail: <achurch@dragonfire.net>
 * Services is copyright (c) 1999-2000 Andrew Kempe.
 *     E-mail: <theshadow@shadowfire.org>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#include "services.h"
#include "language.h"

/*************************************************************************/

/* The list of lists of messages. */
char **langtexts[NUM_LANGS];

/* The list of names of languages. */
char *langnames[NUM_LANGS];

/* Indexes of available languages: */
int langlist[NUM_LANGS];

/* Order in which languages should be displayed: (alphabetical) */
static int langorder[NUM_LANGS] = {
    LANG_ES,            /* Castellano */
    LANG_CA,            /* Catalán */
    LANG_EN_US,		/* English (US) */
    LANG_FR,		/* French */
    LANG_GA,            /* Gallego */
    LANG_IT,		/* Italian */
    LANG_JA_JIS,	/* Japanese (JIS encoding) */
    LANG_JA_EUC,	/* Japanese (EUC encoding) */
    LANG_JA_SJIS,	/* Japanese (SJIS encoding) */
    LANG_PT,		/* Portugese */
    LANG_TR,		/* Turkish */
};

/*************************************************************************/

/* Load a language file. */

static int read_int32(int32 *ptr, FILE *f)
{
    int a = fgetc(f);
    int b = fgetc(f);
    int c = fgetc(f);
    int d = fgetc(f);
    if (a == EOF || b == EOF || c == EOF || d == EOF)
	return -1;
    *ptr = a<<24 | b<<16 | c<<8 | d;
    return 0;
}

static void load_lang(int index, const char *filename)
{
    char buf[256];
    FILE *f;
    int num, i;

    if (debug) {
	log("debug: Cargando lenguaje %d del archivo `languages/%s'",
		index, filename);
    }
    snprintf(buf, sizeof(buf), "languages/%s", filename);
    if (!(f = fopen(buf, "r"))) {
	log_perror("Ha fallado la carga del lenguaje %d (%s)", index, filename);
	return;
    } else if (read_int32(&num, f) < 0) {
	log("Failed to read number of strings for language %d (%s)",
		index, filename);
	return;
    } else if (num != NUM_STRINGS) {
	log("Warning: Bad number of strings (%d, wanted %d) "
	    "for language %d (%s)", num, NUM_STRINGS, index, filename);
    }
    langtexts[index] = scalloc(sizeof(char *), NUM_STRINGS);
    if (num > NUM_STRINGS)
	num = NUM_STRINGS;
    for (i = 0; i < num; i++) {
	int32 pos, len;
	fseek(f, i*8+4, SEEK_SET);
	if (read_int32(&pos, f) < 0 || read_int32(&len, f) < 0) {
	    log("Failed to read entry %d in language %d (%s) TOC",
			i, index, filename);
	    while (--i >= 0) {
		if (langtexts[index][i])
		    free(langtexts[index][i]);
	    }
	    free(langtexts[index]);
	    langtexts[index] = NULL;
	    return;
	}
	if (len == 0) {
	    langtexts[index][i] = NULL;
	} else if (len >= 65536) {
	    log("Entry %d in language %d (%s) is too long (over 64k)--"
		"corrupt TOC?", i, index, filename);
	    while (--i >= 0) {
		if (langtexts[index][i])
		    free(langtexts[index][i]);
	    }
	    free(langtexts[index]);
	    langtexts[index] = NULL;
	    return;
	} else if (len < 0) {
	    log("Entry %d in language %d (%s) has negative length--"
		"corrupt TOC?", i, index, filename);
	    while (--i >= 0) {
		if (langtexts[index][i])
		    free(langtexts[index][i]);
	    }
	    free(langtexts[index]);
	    langtexts[index] = NULL;
	    return;
	} else {
	    langtexts[index][i] = smalloc(len+1);
	    fseek(f, pos, SEEK_SET);
	    if (fread(langtexts[index][i], 1, len, f) != len) {
		log("Failed to read string %d in language %d (%s)",
			i, index, filename);
		while (--i >= 0) {
		    if (langtexts[index][i])
			free(langtexts[index][i]);
		}
		free(langtexts[index]);
		langtexts[index] = NULL;
		return;
	    }
	    langtexts[index][i][len] = 0;
	}
    }
    fclose(f);
}

/*************************************************************************/

/* Initialize list of lists. */

void lang_init()
{
    int i, j, n = 0;

    load_lang(LANG_ES, "es");
    load_lang(LANG_CA, "ca");
    load_lang(LANG_EN_US, "en_us");
    load_lang(LANG_GA, "ga");
    load_lang(LANG_IT, "it");
    load_lang(LANG_JA_JIS, "ja_jis");
    load_lang(LANG_JA_EUC, "ja_euc");
    load_lang(LANG_JA_SJIS, "ja_sjis");    
    load_lang(LANG_PT, "pt");
    load_lang(LANG_TR, "tr");

    for (i = 0; i < NUM_LANGS; i++) {
	if (langtexts[langorder[i]] != NULL) {
	    langnames[langorder[i]] = langtexts[langorder[i]][LANG_NAME];
	    langlist[n++] = langorder[i];
	    for (j = 0; j < NUM_STRINGS; j++) {
		if (!langtexts[langorder[i]][j]) {
		    langtexts[langorder[i]][j] =
				langtexts[langorder[DEF_LANGUAGE]][j];
		}
		if (!langtexts[langorder[i]][j]) {
		    langtexts[langorder[i]][j] =
				langtexts[langorder[LANG_EN_US]][j];
		}
	    }
	}
    }
    while (n < NUM_LANGS)
	langlist[n++] = -1;

    if (!langtexts[DEF_LANGUAGE])
	fatal("Unable to load default language");
    for (i = 0; i < NUM_LANGS; i++) {
	if (!langtexts[i])
	    langtexts[i] = langtexts[DEF_LANGUAGE];
    }
}

/*************************************************************************/
/*************************************************************************/

/* Format a string in a strftime()-like way, but heed the user's language
 * setting for month and day names.  The string stored in the buffer will
 * always be null-terminated, even if the actual string was longer than the
 * buffer size.
 * Assumption: No month or day name has a length (including trailing null)
 * greater than BUFSIZE.
 */

int strftime_lang(char *buf, int size, User *u, int format, struct tm *tm)
{
    int language = u && u->ni ? u->ni->language : DEF_LANGUAGE;
    char tmpbuf[BUFSIZE], buf2[BUFSIZE];
    char *s;
    int i, ret;

    strscpy(tmpbuf, langtexts[language][format], sizeof(tmpbuf));
    if ((s = langtexts[language][STRFTIME_DAYS_SHORT]) != NULL) {
	for (i = 0; i < tm->tm_wday; i++)
	    s += strcspn(s, "\n")+1;
	i = strcspn(s, "\n");
	strncpy(buf2, s, i);
	buf2[i] = 0;
	strnrepl(tmpbuf, sizeof(tmpbuf), "%a", buf2);
    }
    if ((s = langtexts[language][STRFTIME_DAYS_LONG]) != NULL) {
	for (i = 0; i < tm->tm_wday; i++)
	    s += strcspn(s, "\n")+1;
	i = strcspn(s, "\n");
	strncpy(buf2, s, i);
	buf2[i] = 0;
	strnrepl(tmpbuf, sizeof(tmpbuf), "%A", buf2);
    }
    if ((s = langtexts[language][STRFTIME_MONTHS_SHORT]) != NULL) {
	for (i = 0; i < tm->tm_mon; i++)
	    s += strcspn(s, "\n")+1;
	i = strcspn(s, "\n");
	strncpy(buf2, s, i);
	buf2[i] = 0;
	strnrepl(tmpbuf, sizeof(tmpbuf), "%b", buf2);
    }
    if ((s = langtexts[language][STRFTIME_MONTHS_LONG]) != NULL) {
	for (i = 0; i < tm->tm_mon; i++)
	    s += strcspn(s, "\n")+1;
	i = strcspn(s, "\n");
	strncpy(buf2, s, i);
	buf2[i] = 0;
	strnrepl(tmpbuf, sizeof(tmpbuf), "%B", buf2);
    }
    ret = strftime(buf, size, tmpbuf, tm);
    if (ret == size)
	buf[size-1] = 0;
    return ret;
}
/*************************************************************************/

/* Generates a description for seconds in the form of days, hours minutes,
 * seconds and/or a combination thereof. The resulting value is primarily used
 * to describe the expiry time for things, like AKILLs.
 *
 * Currently we abuse the AKILL_EXPIRES reponses, merely becuase AKILLs were
 * the first things to expire. Someday someone may like to rename these
 * reponses more appropriately, seeing as this function is used to describe
 * more that just AKILL expiry times.
 */

void expires_in_lang(char *buf, int size, User *u, time_t seconds)
{

    char expirebuf[BUFSIZE];
    
    if (seconds < 3600) {
        seconds /= 60;
        if (seconds == 1)
            snprintf(expirebuf, sizeof(expirebuf),
                getstring(u->ni, OPER_AKILL_EXPIRES_1M), seconds);
        else
            snprintf(expirebuf, sizeof(expirebuf),
                getstring(u->ni, OPER_AKILL_EXPIRES_M), seconds);
    } else if (seconds < 86400) {
        seconds /= 60;
        if (seconds/60 == 1) {
            if (seconds%60 == 1)
                snprintf(expirebuf, sizeof(expirebuf),
                    getstring(u->ni, OPER_AKILL_EXPIRES_1H1M),
                    seconds/60, seconds%60);
            else
                snprintf(expirebuf, sizeof(expirebuf),
                    getstring(u->ni, OPER_AKILL_EXPIRES_1HM),
                    seconds/60, seconds%60);
                                                                    
        } else {
           if (seconds%60 == 1)
                snprintf(expirebuf, sizeof(expirebuf),
                    getstring(u->ni, OPER_AKILL_EXPIRES_H1M),
                    seconds/60, seconds%60);
           else
                snprintf(expirebuf, sizeof(expirebuf),
                    getstring(u->ni, OPER_AKILL_EXPIRES_HM),
                    seconds/60, seconds%60);                                                                                                                                                                                
        }
    } else {
        seconds /= 86400;
        if (seconds == 1)
            snprintf(expirebuf, sizeof(expirebuf),
                getstring(u->ni, OPER_AKILL_EXPIRES_1D), seconds);    
        else
            snprintf(expirebuf, sizeof(expirebuf),
                getstring(u->ni, OPER_AKILL_EXPIRES_D), seconds);
    }
                                        
    strncpy(buf, expirebuf, size);
}    

/*************************************************************************/
/*************************************************************************/

/* Send a syntax-error message to the user. */

void syntax_error(const char *service, User *u, const char *command, int msgnum)
{
    const char *str = getstring(u->ni, msgnum);
    notice_lang(service, u, SYNTAX_ERROR, str);
    notice_lang(service, u, MORE_INFO, service, command);
}

/*************************************************************************/

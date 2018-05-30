/* Declarations of IRC message structures, variables, and functions.
 *
 * Services is copyright (c) 1996-1999 Andy Church.
 *     E-mail: <achurch@dragonfire.net>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

/*************************************************************************/

typedef struct {
    const char *name;
    void (*func)(char *source, int ac, char **av);
} Message;

extern Message messages[];

extern Message *find_message(const char *name);

/*************************************************************************/

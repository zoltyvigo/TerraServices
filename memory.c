/* Memory management routines.
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
/*************************************************************************/

/* smalloc, scalloc, srealloc, sstrdup:
 *	Versions of the memory allocation functions which will cause the
 *	program to terminate with an "Out of memory" error if the memory
 *	cannot be allocated.  (Hence, the return value from these functions
 *	is never NULL.)
 */

void *smalloc(long size)
{
    void *buf;

    if (!size) {
	log("smalloc: Illegal attempt to allocate 0 bytes");
	size = 1;
    }
    if(!(buf=(void *)malloc(size))) {
	log("smalloc: FATAL: IMPOSIBLE OBTENER %ld BYTES!!", size);
	raise(SIGUSR1);
    }
    return buf;
}

void *scalloc(long elsize, long els)
{
    void *buf;

    if (!elsize || !els) {
	log("scalloc: Illegal attempt to allocate 0 bytes");
	elsize = els = 1;
    }
    if(!(buf=(void *)calloc(elsize, els))) {
	log("scalloc: FATAL: IMPOSIBLE OBTENER %ld ESTRUCTURAS DE TAMAÑO %ld!!", elsize, els);
	raise(SIGUSR1);
    }
    return buf;
}

void *srealloc(void *oldptr, long newsize)
{
    void *buf;

    if (!newsize) {
	log("srealloc: Illegal attempt to allocate 0 bytes");
	newsize = 1;
    }
    if(!(buf=(void *)realloc(oldptr, newsize))) {
	log("realloc: FATAL: IMPOSIBLE REAJUSTAR EL TAMAÑO DEL PUNTERO %p A %ld BYTES!!",
            oldptr, newsize);
	raise(SIGUSR1);
    }
    return buf;
}

char *sstrdup(const char *s)
{
    char *t = strdup(s);
    if (!t)
	raise(SIGUSR1);
    return t;
}

/*************************************************************************/
/*************************************************************************/

/* In the future: malloc() replacements that tell us if we're leaking and
 * maybe do sanity checks too... */

/*************************************************************************/

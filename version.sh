#!/bin/sh
#
# Build the version.h file which contains all the version related info and
# needs to be updated on a per-build basis.


VERSION=4.4.9
BRANCHSTATUS=BETA-RELEASE

# Cambiar este siempre
# Las versiones seran 1.a.b

VERSION_TERRA=1.0RC9


# Increment Services build number
if [ -f version.h ] ; then
	BUILD=`fgrep '#define BUILD' version.h | sed 's/^#define BUILD.*"\([0-9]*\)".*$/\1/'`
	BUILD=`expr $BUILD + 1 2>/dev/null`
else
	BUILD=1
fi
if [ ! "$BUILD" ] ; then
	BUILD=1
fi

DATE=`date`
if [ $? -ne "0" ] ; then
    DATE="\" __DATE__ \" \" __TIME__ \""
fi

cat >version.h <<EOF
/* Version information for Services.
 *
 * Services is copyright (c) 1996-1999 Andy Church.
 *     E-mail: <achurch@dragonfire.net>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#define BUILD	"$BUILD"


const char version_branchstatus[] = "$BRANCHSTATUS";
const char version_number[] = "$VERSION";
const char version_terra[] = "$VERSION_TERRA";
const char version_build[] = "build #" BUILD ", compiled $DATE";
const char version_protocol[] =
#if defined(IRC_UNDERNET)
	"ircu 2.10+Terra P9"
#elif defined(IRC_BAHAMUT)
	"Bahamut + Terra"
#else
	"desconocido"
#endif 
	;


/* Look folks, please leave this INFO reply intact and unchanged. If you do
 * have the urge to metion yourself, please simply add your name to the list.
 * The other people listed below have just as much right, if not more, to be
 * mentioned. Leave everything else untouched. Thanks.
 */

const char *info_text[] =
    {
	"IRC Services developed by and copyright (c) 1996-2001",
	"Andrew Church <achurch@achurch.org>.",
	"Parts copyright (c) 1999-2000 Andrew Kempe and others.",
	"IRC Services may be freely redistributed under the GNU",
	"General Public License.",
	"-",
	"Many people have contributed to the ongoing development of",
	"IRC Services. Particularly noteworthy contributers include:",
	"Erdem Sener",
	"Jose R. Holzmann",
	"Mauritz Antunes",
	"Michael Raff",
	"Raul S. Villarreal",
	"A full list of contributers and their contributions can be",
	"found in the Changes file included in the IRC Services",
	"distribution archive. Many thanks to all of them!",
	"-",
	"For the more information and a list of distribution sites,",
	"please visit: http://www.ircservices.za.net/",
	"-",
	"Terra Services ha sido programado a partir de los Services",
	"por el equipo de Developers de Terra Networks:",
	"-",
	"Programador principal de los Terra Services",
        "Toni Garcia         zoltan    <zolty@terra.es>",
	"Otros programadores",
	"Daniel Fernandez    Freemind  <animedes@terra.es>",
	"Jordi Murgo         |savage|  <savage@apostols.org>",
	0,
    };
EOF

/* Version information for Services.
 *
 * Services is copyright (c) 1996-1999 Andy Church.
 *     E-mail: <achurch@dragonfire.net>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 */

#define BUILD	"354"


const char version_branchstatus[] = "BETA-STABLE";
const char version_number[] = "4.4.9";
const char version_terra[] = "1.0RC7";
const char version_build[] = "build #" BUILD ", compiled Tue Mar 20 02:07:46 CET 2001";
const char version_protocol[] =
#if defined(IRC_UNDERNET_P09)
	"ircu 2.10+Terra P9"
#elif defined(IRC_UNDERNET_P10)
	"ircu 2.10+Terra P10"
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
        "Toni Garcia         zoltan    <zoltan@terra.es>",
	"Otros programadores",
	"Daniel Fernandez    Freemind  <animedes@terra.es>",
	"Jordi Murgo         |savage|  <savage@apostols.org>",
	0,
    };

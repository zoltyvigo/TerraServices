# Makefile for Services.
#
# Services is copyright (c) 1996-1999 Andy Church.
#     E-mail: <achurch@dragonfire.net>
# This program is free but copyrighted software; see the file COPYING for
# details.


include Makefile.inc


###########################################################################
########################## Configuration section ##########################

# Note that changing any of these options (or, in fact, anything in this
# file) will automatically cause a full rebuild of Services.

# Compilation options:
#	-DCLEAN_COMPILE	 Attempt to compile without any warnings (note that
#			    this may reduce performance)
#	-DSTREAMLINED    Leave out "fancy" options to enhance performance

CDEFS =

# Add any extra flags you want here.  The default line enables warnings and
# debugging symbols on GCC.  If you have a non-GCC compiler, you may want
# to comment it out or change it.

MORE_CFLAGS = -Wall -g


######################## End configuration section ########################
###########################################################################


CFLAGS = $(CDEFS) $(BASE_CFLAGS) $(MORE_CFLAGS)


OBJS =	actions.o akill.o channels.o chanserv.o commands.o compat.o \
	config.o datafiles.o encrypt.o helpserv.o init.o language.o \
	list.o log.o main.o memory.o memoserv.o messages.o misc.o news.o \
	nickserv.o operserv.o process.o send.o sessions.o sockutil.o \
	timeout.o users.o \
	$(VSNPRINTF_O)
SRCS =	actions.c akill.c channels.c chanserv.c commands.c compat.c \
	config.c datafiles.c encrypt.c helpserv.c init.c language.c \
	list.c log.c main.c memory.c memoserv.c messages.c misc.c news.c \
	nickserv.c operserv.c process.c send.c sessions.c sockutil.c \
	timeout.c users.c \
	$(VSNPRINTF_C)

.c.o:
	$(CC) $(CFLAGS) -c $<


all: $(PROGRAM) languages
	@echo Now run \"$(MAKE) install\" to install Services.

myclean:
	rm -f *.o $(PROGRAM) import-db version.h.old

clean: myclean
	(cd lang ; $(MAKE) clean)

spotless: myclean
	(cd lang ; $(MAKE) spotless)
	rm -f config.cache configure.log sysconf.h Makefile.inc language.h

install: $(PROGRAM) languages
	$(INSTALL) services $(BINDEST)/services
	rm -f $(BINDEST)/listnicks $(BINDEST)/listchans
	ln $(BINDEST)/services $(BINDEST)/listnicks
	ln $(BINDEST)/services $(BINDEST)/listchans
	(cd lang ; $(MAKE) install)
	rm -rf $(DATDEST)/helpfiles/ircii
	$(CP_ALL) data/* $(DATDEST)
	@if [ "$(RUNGROUP)" ] ; then \
		echo chgrp -R $(RUNGROUP) $(DATDEST) ; \
		chgrp -R $(RUNGROUP) $(DATDEST) ; \
		echo chmod -R g+rw $(DATDEST) ; \
		chmod -R g+rw $(DATDEST) ; \
		echo find $(DATDEST) -type d -exec chmod g+xs \'\{\}\' \\\; ; \
		find $(DATDEST) -type d -exec chmod g+xs '{}' \; ; \
	fi
	@echo ""
	@echo "Don't forget to create/update your services.conf file!  See"
	@echo "the README for details."
	@echo ""

###########################################################################

$(PROGRAM): version.h $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) $(LIBS) -o $@

languages: FRC
	(cd lang ; $(MAKE) CFLAGS="$(CFLAGS)")


# Catch any changes in compilation options at the top of this file
$(OBJS): Makefile

actions.o:	actions.c	services.h
akill.o:	akill.c		services.h pseudo.h
channels.o:	channels.c	services.h
chanserv.o:	chanserv.c	services.h pseudo.h
commands.o:	commands.c	services.h commands.h language.h
compat.o:	compat.c	services.h
config.o:	config.c	services.h
datafiles.o:	datafiles.c	services.h datafiles.h
encrypt.o:	encrypt.c	encrypt.h sysconf.h
helpserv.o:	helpserv.c	services.h language.h
init.o:		init.c		services.h
language.o:	language.c	services.h language.h
list.o:		list.c		services.h
log.o:		log.c		services.h pseudo.h
main.o:		main.c		services.h timeout.h version.h
memory.o:	memory.c	services.h
memoserv.o:	memoserv.c	services.h pseudo.h
messages.o:	messages.c	services.h messages.h language.h
misc.o:		misc.c		services.h
news.o:		news.c		services.h pseudo.h
nickserv.o:	nickserv.c	services.h pseudo.h
operserv.o:	operserv.c	services.h pseudo.h
process.o:	process.c	services.h messages.h
send.o:		send.c		services.h
sessions.o:     sessions.c      services.h pseudo.h
sockutil.o:	sockutil.c	services.h
timeout.o:	timeout.c	services.h timeout.h
users.o:	users.c		services.h
vsnprintf.o:	vsnprintf.c


services.h: sysconf.h config.h extern.h
	touch $@

pseudo.h: commands.h language.h timeout.h encrypt.h datafiles.h
	touch $@

version.h: Makefile version.sh services.h pseudo.h messages.h $(SRCS)
	sh version.sh

language.h: lang/language.h
	cp -p lang/language.h .

lang/language.h: lang/Makefile lang/index
	(cd lang ; $(MAKE) language.h)


###########################################################################

IMPORT_DB_OBJS = import-db.o config-x.o datafiles-x.o compat.o misc.o \
	$(VSNPRINTF_O)

import-db: $(IMPORT_DB_OBJS)
	$(CC) $(LFLAGS) $(IMPORT_DB_OBJS) $(LIBS) -o $@
import-db.o: import-db.c services.h datafiles.h
config-x.o: config.c services.h
	$(CC) $(CFLAGS) -DNOT_MAIN -c config.c -o $@
datafiles-x.o: datafiles.c services.h datafiles.h
	$(CC) $(CFLAGS) -DNOT_MAIN -c datafiles.c -o $@

###########################################################################

FRC:

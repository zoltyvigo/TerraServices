# Archivo de idioma Español.
#
# Services esta protegido por derechos de autor (c) 1996-1999 Andy Church
#     E-mail: <achurch@dragonfire.net>
#g Este programa es gratis pero esta registrado; vea el archivo COPYING para
# detalles.
# Traducción por:
# José R. Holzmann "Joselito" joselito@sandnet.org
# Raúl S. Villarreal "CheMaN" cheman@sandnet.org

# When translating this file to another language, keep in mind that the
# order of parameters for sprintf() is fixed in the source code, so your
# messages need to take the same parameters in the same order as the
# English messages do.  (Obviously, this doesn't hold for the strftime()
# format lines immediately below.)  If you can't get a natural translation
# of a message without changing the order of the parameters, let me know
# (achurch@dragonfire.net) which message is causing a problem and I'll see
# what I can do.
#
# In help messages, "%S" (capital S, not lowercase) refers to the name of
# the service sending the message; for example, in NickServ help messages,
# "%S" is replaced by "NickServ" (or whatever it is renamed to in
# config.h).  The %S's do not count as sprintf() parameters, so they can be
# rearranged, removed, or added as necessary.

###########################################################################
#
# Nombre de este idioma
#
###########################################################################

# For languages other than English, this string should have the following
# format:
#     language-name-in-language (language-name-in-English)
# For example, "Español (Spanish)" or "Français (French)".

LANG_NAME
	Català (Catalan)

###########################################################################
#
# Mensajes Generales
#
###########################################################################

# strftime() format strings.  man 3 strftime for information on the
# meanings of the format specifiers.  Short version:
#	%a = weekday name (short)	%H = hour
#	%b = month name (short)		%M = minute
#	%d = day of month		%S = second
#	%Y = year			%Z = time zone

# This is used to display a date and time together.
STRFTIME_DATE_TIME_FORMAT
	%H:%M:%S %d/%b/%Y %Z
# This is used as the format string for strftime() for a date and time
# format (English: including weekday).
STRFTIME_LONG_DATE_FORMAT
	%a %b %d %Y
STRFTIME_SHORT_DATE_FORMAT
# This is used as the format string for strftime() for a date alone in
# short format (English: without weekday).
	%b %d %Y

# These tell our strftime() what the names of months and days are.  If you
# don't use %a, %A, %b, or %B in your strftime() strings above, you can
# leave these empty.  However, if you enter names, they MUST stay in order,
# one per line, and the list MUST be complete!

# %a
STRFTIME_DAYS_SHORT
	Diu
	Dil
	Dim
	Dic
	Dij
	Div
	Dis
# %A
STRFTIME_DAYS_LONG
	Diumenge
	Dilluns
	Dimarts
	Dimecres
	Dijous
	Divendres
	Dissabte
# %b
STRFTIME_MONTHS_SHORT
	Gen
	Feb
	Mar
	Abr
	Mai
	Jun
	Jul
	Ago
	Sep
	Oct
	Nov
	Dec
# %
STRFTIME_MONTHS_LONG
	Gener
	Febrer
	Març
	Abril
	Maig
	Juny
	Juliol
	Agost
	Septembre
	Octubre
	Novembre
	Decembre

# This is used in ChanServ/NickServ INFO displays.
COMMA_SPACE
	,

# Various error messages.
USER_RECORD_NOT_FOUND
	Error Intern,impossible processar comanda.
UNKNOWN_COMMAND
	Comanda desconeguda 12%s.
UNKNOWN_COMMAND_HELP
	Comanda desconeguda 12%s. "12/msg %s HELP" per a obtenir ajut.
SYNTAX_ERROR
	Sintaxis: 12%s
MORE_INFO
	12/msg %s HELP %s per a més informació.
NO_HELP_AVAILABLE
	No hi ha ajuda disponible per a 12%s.

BAD_USERHOST_MASK
	La Màscara ha de ser en format 12usuari@12host.

BAD_EXPIRY_TIME
	Temps d'expiració invàlido.

SERVICE_OFFLINE
	12%s està actualment fora de servei.
READ_ONLY_MODE
	4Noticia:12 Services està en mode de llegir solament; els canvis no seran grabats!
ACCESS_DENIED
	4Accès denegat.
PERMISSION_DENIED
	4Permís denegat.
PASSWORD_INCORRECT
	4Clau d'accès incorrecta.

MORE_OBSCURE_PASSWORD
	Ha d'intentar de nou amb una clau d'accès més difícil. Les claus d'accès deuen ser de 5 caracters mínim, no deu ser fàcil de desxifrar (exemple. el seu veritable nom o el seu nick), tampoc deu contenir espais.
PASSWORD_TRUNCATED
	4Notícia: La seva clau d'accès ha estat limitada a 12%d caracters.

NICK_NOT_REGISTERED
	El teu nick no està registrat.
NICK_NOT_REGISTERED_HELP
	El teu nick no està registrat. Escrigui 12/msg %s HELP12 per a més informació de com registrar el seu nick.
NICK_X_NOT_REGISTERED
	El nick 12%s no està registrat.
NICK_X_NOT_IN_USE
	El nick 12%s no es troba en ús en aquest moment.
NICK_X_FORBIDDEN
	El nick 12%s no pot ser registrat o utilitzat.
CHAN_X_NOT_REGISTERED
	El canal 12%s no està registrat.
CHAN_X_NOT_IN_USE
	El canal 12%s no existeix.
CHAN_X_FORBIDDEN
	El canal 12%s no pot ser registrat o utilitzat.
NICK_IDENTIFY_REQUIRED
	Clau d'accès requerida per aquesta comanda.
	Torni-ho a intentar desprès d'escriure 12/IDENTIFY contraseña.

CHAN_IDENTIFY_REQUIRED
	Clau d'accès requerida per aquesta comanda.
	Torni-ho a intentar desprès d'escriure 12/IDENTIFY %s contraseña.

###########################################################################
#
# Mensajes de Nickserv
#
###########################################################################

# Automatic messages
NICK_IS_REGISTERED
	4Aquest nick és d'una altra persona. Escull un altre nick.
	(Si es el teu, escriu 12/IDENTIFY clau.)
NICK_IS_SECURE
	Aquest nick està registrat i protegit.
	Si es el seu nick, escrigui 12/IDENTIFY contraseña.
	Si no ho és, escull un nick diferent.
NICK_MAY_NOT_BE_USED
	Aquest nick no es pot utilitzar. Escull un altre nick.
DISCONNECT_IN_1_MINUTE
	4Si no canvies el teu nick abans de un minut, seràs desconectat.
DISCONNECT_IN_20_SECONDS
	12Si no canvies el teu nick abans de 20 segons, seràs desconectat.
DISCONNECT_NOW
	Aquest nick ha estat registrat; no el pots utilitzar.
	Escull un altre nick abans de reconectar.
FORCENICKCHANGE_IN_1_MINUTE
	4Si no canvies el teu nick abans d'un minut, serà canviat el teu nick.
FORCENICKCHANGE_IN_20_SECONDS
	12Si no canvies el teu nick abans de 20 segons, serà canviat el teu nick.
FORCENICKCHANGE_NOW
	Aquest nick ha estat registrat; no el pots utilitzar.
	El teu nick ha estat canviat a 12%s.

# REGISTER responses
NICK_REGISTER_SYNTAX
	12REGISTER <password>
NICK_REGISTRATION_DISABLED
	Ho sento, el registre de nicks està temporalment deshabilitat.
NICK_REGISTRATION_FAILED
	Ho sento, el registre ha fallat.
NICK_REG_PLEASE_WAIT
	Espera 12%d segons abans de tornar a utilizar la comanda 12REGISTER.
NICK_CANNOT_BE_REGISTERED
	El nick 12%s no pot ser registrat.
NICK_ALREADY_REGISTERED
	El nick 12%s ja està registrat!
NICK_REGISTERED
	El nick 12%s està registrat baix el teu compte: 12%s
NICK_PASSWORD_IS
	La teva clau d'accès és 12%s, recorda-la per a ús posterior.

# IDENTIFY responses
NICK_IDENTIFY_SYNTAX
	12IDENTIFY <password>
NICK_IDENTIFY_FAILED
	4Clau d'accès incorrecta.
NICK_IDENTIFY_SUCCEEDED
	3Clau d'accès acceptada. Benvingut/da a casa ;)

# DROP responses
NICK_DROP_SYNTAX
	12DROP
NICK_DROP_DISABLED
	Ho sento, la cancel·lació de nicks està temporalment deshabilitada.
NICK_DROPPED
	El seu nick ha estat cancel·lat.
NICK_X_DROPPED
	Nick 12%s ha estat cancel·lat.

# SET responses
NICK_SET_SYNTAX
	12SET <opció> <paràmetres>
NICK_SET_SERVADMIN_SYNTAX
	12SET [nick] <option> <parameters>
NICK_SET_DISABLED
	Ho sento, la configuració d'opcions de nick està temporalment deshabilitada.
NICK_SET_UNKNOWN_OPTION
	4Opció SET12 %s desconoguda.
NICK_SET_UNKNOWN_OPTION_OR_BAD_NICK
	4Opció SET 12%s desconeguda, o el teu nick no està registrat.

# SET PASSWORD responses
NICK_SET_PASSWORD_FAILED
	Ho sento, la clau d'accès no s'ha pogut canviar.
NICK_SET_PASSWORD_CHANGED
	Clau d'accès canviada.
NICK_SET_PASSWORD_CHANGED_TO
	Clau d'accès canviada a 12%s.

# SET URL responses
NICK_SET_URL_CHANGED
	URL canviada a %s.
NICK_SET_URL_UNSET
	URL deshabilitada.

# SET EMAIL responses
NICK_SET_EMAIL_CHANGED
	Direcció d'E-mail canviada a 12%s.
NICK_SET_EMAIL_UNSET
	Direcció d'E-mail deshabilitada.

# SET LANGUAGE responses
NICK_SET_LANGUAGE_SYNTAX
	12SET LANGUAGE <nombre>
NICK_SET_LANGUAGE_UNKNOWN
	Nombre %d de llenguatge desconegut.  Escrigui 12/msg %s HELP SET LANGUAGE per a una llista de llenguatges disponibles.
NICK_SET_LANGUAGE_CHANGED
	Llenguatge canviat a 12Català.

# SET KILL responses
NICK_SET_KILL_SYNTAX
	12SET KILL {ON | QUICK | OFF}
NICK_SET_KILL_IMMED_SYNTAX
	12SET KILL {ON | QUICK | IMMED | OFF}
NICK_SET_KILL_ON
	Protecció de KILL 12activada.
NICK_SET_KILL_QUICK
	Protecció de KILL 12activada, amb espera reduïda.
NICK_SET_KILL_IMMED
	Protecció de KILL 12activada, sense espera.
NICK_SET_KILL_IMMED_DISABLED
	La opció 12IMMED no està disponible en aquesta xarxa.
NICK_SET_KILL_OFF
	Protecció de KILL 12desactivada.

# SET SECURE responses
NICK_SET_SECURE_SYNTAX
	12SET SECURE {ON | OFF}
NICK_SET_SECURE_ON
	Opció SECURE 12activada.
NICK_SET_SECURE_OFF
	Opció SECURE 12desactivada.

# SET PRIVATE responses
NICK_SET_PRIVATE_SYNTAX
	12SET PRIVATE {ON | OFF}
NICK_SET_PRIVATE_ON
	Opció PRIVATE 12activada.
NICK_SET_PRIVATE_OFF
	Opció PRIVATE 12desactivada.

# SET HIDE responses
NICK_SET_HIDE_SYNTAX
	12SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
NICK_SET_HIDE_EMAIL_ON
	La seva direcció d'E-mail està amagada per a exhibició de 12%s INFO.
NICK_SET_HIDE_EMAIL_OFF
	LA seva direcció d'E-mail està visible per a exhibició de 12%s INFO.
NICK_SET_HIDE_MASK_ON
	La seva última màscara d'usuari@host està amagada per a exhibició de 12%s INFO.
NICK_SET_HIDE_MASK_OFF
	La seva última màscara d'usuari@host està visible per a exhibició de 12%s INFO.
NICK_SET_HIDE_QUIT_ON
	El seu útlim missatge de sortida està amagat per a exhibició de 12%s INFO.
NICK_SET_HIDE_QUIT_OFF
	El seu últim missatge de sortida està visible per a exhibició de 12%s INFO.

# SET NOEXPIRE responses
NICK_SET_NOEXPIRE_SYNTAX
	12SET [nick] NOEXPIRE {ON | OFF}
NICK_SET_NOEXPIRE_ON
	Nick 12%s 4NO expirarà.
NICK_SET_NOEXPIRE_OFF
	Nick 12%s 4si expirarà.

# ACCESS responses
NICK_ACCESS_SYNTAX
	12ACCESS {ADD | DEL | LIST} [màscara]
NICK_ACCESS_ALREADY_PRESENT
	Màscara 12%s ja existeix a la seva llista d'accès.
NICK_ACCESS_REACHED_LIMIT
	Ho sento, sols pots tenir 12%d entrades a l'access pel teu nick.
NICK_ACCESS_ADDED
	12%s sumada a la seva llista d'accès.
NICK_ACCESS_NOT_FOUND
	12%s no trobada a la seva llista d'accès.
NICK_ACCESS_DELETED
	12%s treta de la seva llista d'accès.
NICK_ACCESS_LIST
	Llista d'accès:
NICK_ACCESS_LIST_X
	Llista d'accès per a 12%s:

# LINK responses
NICK_LINK_SYNTAX
	12LINK <nick> <password>
NICK_LINK_FAILED
	Ho sento, el link ha fallat.
NICK_NO_LINK_SAME
	No pot enllaçar el nick actual.
NICK_LINK_CIRCULAR
	Impossible enllaçar a nick 12%s: link circular detectat.
NICK_LINKED
	El teu nick ha estat enllaçat a 12%s.

# UNLINK responses
NICK_UNLINK_SYNTAX
	12UNLINK [nick password]
NICK_UNLINK_FAILED
	Ho sento, el deslink ha fallat.
NICK_NOT_LINKED
	El teu nick no està enllaçat.
NICK_UNLINKED
	El teu nick ha estat desenllaçat de 12%s.
NICK_X_NOT_LINKED
	Nick 12%s no està enllançat.
NICK_X_UNLINKED
	Nick 12%s ha estat desenllaçat de 12%s.

# LISTLINKS responses
NICK_LISTLINKS_SYNTAX
	12LISTLINKS <nick> [ALL]
NICK_LISTLINKS_HEADER
	Llista de nicks enllaçats a 12%s:
NICK_LISTLINKS_FOOTER
	12%d nicks enllaçats.

# INFO responses
NICK_INFO_SYNTAX
	12INFO nick [ALL]

NICK_INFO_REALNAME
	Realname de 12%s és 12%s
NICK_INFO_ADDRESS
	Última direcció: 12%s
NICK_INFO_ADDRESS_ONLINE
	Està on-line des de: 12%s
NICK_INFO_ADDRESS_ONLINE_NOHOST
	Està on-line, més informació escrigui 12/WHOIS %s.
NICK_INFO_TIME_REGGED
	Hora de registre: 12%s
NICK_INFO_LAST_SEEN
	Ultima hora per la xarxa: 12%s
NICK_INFO_LAST_QUIT
	Últim missatge de sortida: 12%s
NICK_INFO_URL
	URL: 12%s
NICK_INFO_EMAIL
	E-mail: 12%s
NICK_INFO_OPTIONS
	Opcions: %s
# These strings MUST NOT be empty
NICK_INFO_OPT_KILL
	12Protecció de KILL
NICK_INFO_OPT_SECURE
	12Segur
NICK_INFO_OPT_PRIVATE
	12Privat
NICK_INFO_OPT_NONE
	12Cap
NICK_INFO_NO_EXPIRE
	Aquest nick 4no expirarà.

# LIST responses
NICK_LIST_SYNTAX
	12LIST <patró>
NICK_LIST_SERVADMIN_SYNTAX
	12LIST <patró> [FORBID] [NOEXPIRE]
NICK_LIST_HEADER
	Llista d'entrades que satisfan 12%s:
NICK_LIST_RESULTS
	Fi de llista - 12%d/12%d entrades mostrades.

# RECOVER responses
NICK_RECOVER_SYNTAX
	12RECOVER <nick> [password]
NICK_NO_RECOVER_SELF
	No pot recuperar el seu propi nick!
NICK_RECOVERED
	Usuari utilitzant el seu nick ha estat desconectat.
	12/msg %s RELEASE %s per a recuperar-lo abans d'un minut.

# RELEASE responses
NICK_RELEASE_SYNTAX
	12RELEASE <nick> [password]
NICK_RELEASE_NOT_HELD
	Nick 12%s no està éssent protegit en aquest moment.
NICK_RELEASED
	La protecció de Services al seu nick ha estat alliberada.

# GHOST responses
NICK_GHOST_SYNTAX
	12GHOST <nick> [password]
NICK_NO_GHOST_SELF
	No pot aplicar-se ghost a si mateix.
NICK_GHOST_KILLED
	Ghost amb el seu nick ha estat desconectat.

# GETPASS responses
NICK_GETPASS_SYNTAX
	12GETPASS <nick>
NICK_GETPASS_UNAVAILABLE
	Comanda 12GETPASS no disponible quan encripció està en ús.
NICK_GETPASS_PASSWORD_IS
	Contrasenya per a 12%s és 12%s.

# FORBID responses
NICK_FORBID_SYNTAX
	12FORBID <nick>
NICK_FORBID_SUCCEEDED
	Nick 12%s està prohibit de ser usat.
NICK_FORBID_FAILED
	No es pot prohibir nick 12%s!

###########################################################################
#
# Mensajes de ChanServ
#
###########################################################################

# Access level descriptions
CHAN_LEVEL_AUTOOP
	Status d'operador de canal automàtic
CHAN_LEVEL_AUTOVOICE
	Mode +v automàtic
CHAN_LEVEL_AUTODEOP
	No pot ser operador del canal
CHAN_LEVEL_NOJOIN
	No pot entrar al canal si està en mode restringit(RESTRICTED)
CHAN_LEVEL_INVITE
	Li és permès usar la comanda INVITE
CHAN_LEVEL_AKICK
	Li és permès usar la comanda AKICK
CHAN_LEVEL_SET
	Li és permès usar la comanda SET (sense ser FUNDADOR)
CHAN_LEVEL_CLEAR
	Li és permès usar la comanda CLEAR
CHAN_LEVEL_UNBAN
	Li és permès usar la comanda UNBAN
CHAN_LEVEL_OPDEOP
	Li és permès usar la comanda OP/DEOP
CHAN_LEVEL_ACCESS_LIST
	Li és permés veure la llista d'accès
CHAN_LEVEL_ACCESS_CHANGE
	Li és permés modificar la llista d'accès
CHAN_LEVEL_MEMO
	Li és permés veure els missatges del canal

# Automatic responses
CHAN_IS_REGISTERED
	Aquest canal està registrat amb 12%s.
CHAN_NOT_ALLOWED_OP
	Vosté no pot ser operador del canal 12%s.
CHAN_MAY_NOT_BE_USED
	Aquest canal no pot ser utilitzat.
CHAN_NOT_ALLOWED_TO_JOIN
	Vosté no pot estar en aquest canal.

# REGISTER responses
CHAN_REGISTER_SYNTAX
	12REGISTER <canal> <password> <descripció>
CHAN_REGISTER_DISABLED
	Ho sento, registre de canal està temporalment desactivat.
CHAN_REGISTER_NOT_LOCAL
	Canals locals no poden ser registrats.
CHAN_MUST_REGISTER_NICK
	Vosté ha de registrar primer el seu nick. Escrigui 12/msg %s HELP para obtener más información de como registrar nicks.
CHAN_MUST_IDENTIFY_NICK
	Si us plau, identifiqui`s primer amb 12%s, utilitzant la comanda:
	12/IDENTIFY clau
CHAN_MAY_NOT_BE_REGISTERED
	Canal 12%s no pot ser registrat.
CHAN_ALREADY_REGISTERED
	Canal 12%s ja està registrat!
CHAN_MUST_BE_CHANOP
	Vosté ha de ser operador del canal per a poder registrar-lo.
CHAN_REACHED_CHANNEL_LIMIT
	Ho sento, vosté ja ha alcançat el seu límit de 12%d canals.
CHAN_EXCEEDED_CHANNEL_LIMIT
	Ho sento, vosté ja ha excedit el seu límit de 12%d canals.
CHAN_REGISTRATION_FAILED
	Ho sento, el registre ha fallat.
CHAN_REGISTERED
	Canal 12%s registrat sota el seu nick: 12%s
CHAN_PASSWORD_IS
	La clau del seu canal és 12%s, recordi-la per un ús posterior.

# IDENTIFY responses
CHAN_IDENTIFY_SYNTAX
	12IDENTIFY <canal> <password>
CHAN_IDENTIFY_FAILED
	4Clau incorrecta.
CHAN_IDENTIFY_SUCCEEDED
	Clau d'accès acceptada, ets reconegut amb nivell de fundador de 12%s.

# DROP responses
CHAN_DROP_SYNTAX
	12DROP 12<canal>
CHAN_DROP_DISABLED
	Ho sento, la cancel·lació de registre de canal està temporalment deshabilitada.
CHAN_DROPPED
	Canal 12%s ha estat cancel·lat.

# SET responses
CHAN_SET_SYNTAX
	12SET <canal> <opció> <paràmetres>

CHAN_SET_DISABLED
	Ho sento, l'ajust d'opcions de canal està temporalment deshabilitada.
CHAN_SET_UNKNOWN_OPTION
	4Opció SET 12%s desconeguda.

# SET FOUNDER responses
CHAN_SET_FOUNDER_TOO_MANY_CHANS
	12%s té massa canals registrats.
CHAN_FOUNDER_CHANGED
	Fundador de 12%s canviat a 12%s.

# SET SUCCESSOR responses
CHAN_SUCCESSOR_CHANGED
	Successor de 12%s canviat a 12%s.
CHAN_SUCCESSOR_UNSET
	Successor per a 12%s 12deshabilitat.

# SET PASSWORD responses
CHAN_SET_PASSWORD_FAILED
	Ho sento, no s'ha pogut canviar la clau.
CHAN_PASSWORD_CHANGED
	12%s clau canviada.
CHAN_PASSWORD_CHANGED_TO
	12%s clau canviada a 12%s.

# SET DESC responses
CHAN_DESC_CHANGED
	Descripció de 12%s canviada a 12%s.

# SET URL responses
CHAN_URL_CHANGED
	URL per a 12%s canviada a 12%s.
CHAN_URL_UNSET
	URL per a 12%s desactivada.

# SET EMAIL responses
CHAN_EMAIL_CHANGED
	Direcció d'E-mail per a 12%s canviada a 12%s.
CHAN_EMAIL_UNSET
	Direcció d'E-mail per a 12%s desactivada.

# SET ENTRYMSG responses
CHAN_ENTRY_MSG_CHANGED
	Missatge d'entrada per a 12%s canviat.
CHAN_ENTRY_MSG_UNSET
	Missatge d'entrada per a 12%s desactivat.

# SET TOPIC responses
CHAN_SET_TOPIC_FAILED
	Ho sento, no va ser possible posar el tópic.

# SET MLOCK responses
CHAN_SET_MLOCK_KEY_REQUIRED
	Paràmetre necessari per a MLOCK +k.
CHAN_SET_MLOCK_LIMIT_REQUIRED
	Paràmetre necessari per a MLOCK +l.
CHAN_SET_MLOCK_LIMIT_POSITIVE
	Paràmetre per a MLOCK +l ha de ser un nombre positiu.
CHAN_SET_MLOCK_UNKNOWN_CHAR
	Mode 12%c és desconegut i ignorat.
CHAN_MLOCK_CHANGED
	Candau de mode de canal 12%s canviat a 12%s.
CHAN_MLOCK_REMOVED
	Candau de mode de canal 12%s remogut.

# SET KEEPTOPIC responses
CHAN_SET_KEEPTOPIC_SYNTAX
	12SET <canal> KEEPTOPIC {ON | OFF}
CHAN_SET_KEEPTOPIC_ON
	Opció de retenció de tópic 12activada.
CHAN_SET_KEEPTOPIC_OFF
	Opció de retenció de tópic 12desactivada.

# SET TOPICLOCK responses
CHAN_SET_TOPICLOCK_SYNTAX
	12SET <canal> TOPICLOCK {ON | OFF}
CHAN_SET_TOPICLOCK_ON
	Opció de candau de tópic 12activada.
CHAN_SET_TOPICLOCK_OFF
	Opció de candau de tópic 12desactivada.

# SET PRIVATE responses
CHAN_SET_PRIVATE_SYNTAX
	12SET <canal> PRIVATE {ON | OFF}
CHAN_SET_PRIVATE_ON
	Opció de privacitat 12activada.
CHAN_SET_PRIVATE_OFF
	Opció de privacitat 12desactivada.
# SET SECUREOPS responses
CHAN_SET_SECUREOPS_SYNTAX
	12SET <canal> SECUREOPS {ON | OFF}
CHAN_SET_SECUREOPS_ON
	Opció de Secure ops 12activada.
CHAN_SET_SECUREOPS_OFF
	Opció de Secure ops 12desactivada.

# SET LEAVEOPS responses
CHAN_SET_LEAVEOPS_SYNTAX
	12SET <canal> LEAVEOPS {ON | OFF}
CHAN_SET_LEAVEOPS_ON
	Opció de Leave ops 12activada.
CHAN_SET_LEAVEOPS_OFF
	Opció de Leave ops 12desactivada.


# SET RESTRICTED responses
CHAN_SET_RESTRICTED_SYNTAX
	12SET <canal> RESTRICTED {ON | OFF}
CHAN_SET_RESTRICTED_ON
	Opció d'accès restringit 12activada.
CHAN_SET_RESTRICTED_OFF
	Opció d'accès restringit 12desactivada.

# SET SECURE responses
CHAN_SET_SECURE_SYNTAX
	12SET <canal> SECURE {ON | OFF}
CHAN_SET_SECURE_ON
	Opció Secure 12activada.
CHAN_SET_SECURE_OFF
	Opció Secure 12desactivada.

# SET OPNOTICE responses
CHAN_SET_OPNOTICE_SYNTAX
	12SET <canal> ISSUED {ON | OFF}
CHAN_SET_OPNOTICE_ON
	Opció issued 12activada.
CHAN_SET_OPNOTICE_OFF
	Opció issued 12desactivada.

# SET NOEXPIRE responses
CHAN_SET_NOEXPIRE_SYNTAX
	SET <canal> NOEXPIRE {ON | OFF}
CHAN_SET_NOEXPIRE_ON
	Canal 12%s 4NO expirarà.
CHAN_SET_NOEXPIRE_OFF
	Canal 12%s 4SI expirarà.

# ACCESS messages
CHAN_ACCESS_SYNTAX
	12ACCESS <canal> {ADD|DEL|LIST} [nick [nivell] | entrada-llista]
CHAN_ACCESS_DISABLED
	Ho sento, la modificació a la llista d'accès de canal està temporalment deshabilitada.
CHAN_ACCESS_LEVEL_NONZERO
	Nivell d'accès deu ser diferent de zero.
CHAN_ACCESS_LEVEL_RANGE
	Nivell d'accès ha d'estar entre 12%d y 12%d.
CHAN_ACCESS_NICKS_ONLY
	Llista d'accès de canal ha de contir nomès nicks registrats.
CHAN_ACCESS_REACHED_LIMIT
	Ho sento, sols pot haver 12%d entrades a l'accès d'un canal.
CHAN_ACCESS_LEVEL_UNCHANGED
	Nivell d'accès per a 12%s en 12%s no ha canviat de 12%d.
CHAN_ACCESS_LEVEL_CHANGED
	Nivell d'accès per a 12%s en 12%s ha estat canviat a 12%d.
CHAN_ACCESS_ADDED
	12%s ha estat introduït a llista d'accès de 12%s amb nivell 12%d.
CHAN_ACCESS_NO_SUCH_ENTRY
	Entrada desconeguda (12#%d) a la llista d'accès de 12%s.
CHAN_ACCESS_NOT_FOUND
	12%s no fou trobat a la llista d'acccès de 12%s.
CHAN_ACCESS_DELETED
	12%s tret de la llista d'accès de 12%s.
CHAN_ACCESS_DELETED_ONE
	Borrada12 1 entrada de la llista d'accès de 12%s.
CHAN_ACCESS_DELETED_SEVERAL
	Borrades 12%d entrades de la llista d'accès de 12%s.
CHAN_ACCESS_LIST_HEADER
	Llista d'accès de 12%s:
	  Num   Niv  Nick
CHAN_ACCESS_LIST_EMPTY
	Llista d'access de 12%d està buïda.
CHAN_ACCESS_LIST_FORMAT
	  %3d  %4d  %s%s%s%s

# AOP/SOP error response
CHAN_NO_AOP_SOP
	Per a asignar privilegis del canal a usuari, usa la comanda 12ACCESS.
	Escriu 12/msg %s HELP ACCESS per a més informació.

# AKICK responses
CHAN_AKICK_SYNTAX
	12AKICK <canal> {ADD | DEL | LIST | ENFORCE} [nick or mascara]
CHAN_AKICK_DISABLED
	Ho sento, la modificació de llista d'autokicks de canal està temporalment deshabilitada.
CHAN_AKICK_ALREADY_EXISTS
	12%s ja existeix a la llista d'autokicks de 12%s.
CHAN_AKICK_REACHED_LIMIT
	Ho sento, sols pot tenir 12%d mascares d'autokick en un canal.
CHAN_AKICK_ADDED
	12%s introduït a la llista d'autokick de 12%s.
CHAN_AKICK_NO_SUCH_ENTRY
	Entrada desconeguda (12#%d) a la llista d'autokick de 12%s.
CHAN_AKICK_NOT_FOUND
	12%s no es troba a la llista d'autokick de 12%s.
CHAN_AKICK_DELETED
	12%s borrat de la llista d'autokick de 12%s.
CHAN_AKICK_DELETED_ONE
	Deleted 1 entry from %s autokick list.
CHAN_AKICK_DELETED_SEVERAL
	Deleted %d entries from %s autokick list.
CHAN_AKICK_NO_MATCH
	No matching entries on %s autokick list.
CHAN_AKICK_LIST_EMPTY
	%s autokick list is empty.

CHAN_AKICK_LIST_HEADER
	Llista d'autokick de 12%s:
CHAN_AKICK_LIST_FORMAT
	  %3d %s%s
CHAN_AKICK_ENFORCE_DONE
	AKICK ENFORCE per a 12%s completat; 12%d usuaris són afectats.

# LEVELS responses
CHAN_LEVELS_SYNTAX
	12LEVELS <canal> {SET | DIS[ABLE] | LIST | RESET} [item [level]]
CHAN_LEVELS_RANGE
	El nivell ha d'estar entre 12%d i 12%d.
CHAN_LEVELS_CHANGED
	El nivell per a 12%s en canal 12%s ha canviat a 12%d.
CHAN_LEVELS_UNKNOWN
	Opció 12%s desconeguda.  Escrigui 12/msg %s HELP LEVELS DESC per a una llista d'opcions vàlides.
CHAN_LEVELS_DISABLED
	12%s deshabilitat en canal 12%s.
CHAN_LEVELS_LIST_HEADER
	Configuració de nivell d'accès per a canal 12%s:
CHAN_LEVELS_LIST_DISABLED
	    %-*s  (deshabilitat)
CHAN_LEVELS_LIST_FOUNDER
	    %-*s  (fundador solament)
CHAN_LEVELS_LIST_NORMAL
	    %-*s  %d
CHAN_LEVELS_RESET
	Nivells d'accès de 12%s configurats a nivells originals.

# INFO responses
CHAN_INFO_SYNTAX
	12INFO <canal> [ALL]
CHAN_INFO_HEADER
	Informació de canal 12%s:
CHAN_INFO_FOUNDER
	Fundador: 12%s (12%s)
CHAN_INFO_NO_FOUNDER
	Fundador: 12%s
CHAN_INFO_SUCCESSOR
	Successor: 12%s (12%s)
CHAN_INFO_NO_SUCCESSOR
	Successor: 12%s
CHAN_INFO_DESCRIPTION
	Descripció: 12%s
CHAN_INFO_ENTRYMSG
	Missatge d'entrada: 12%s
CHAN_INFO_TIME_REGGED
	Registrat: 12%s
CHAN_INFO_LAST_USED
	Ultimo uso: 12%s
CHAN_INFO_LAST_TOPIC
	Ultim tópic: 12%s
CHAN_INFO_TOPIC_SET_BY
	Tópic ajustat per: 12%s
CHAN_INFO_URL
	URL: 12%s
CHAN_INFO_EMAIL
	E-mail: 12%s
CHAN_INFO_OPTIONS
	Opcions: %s
CHAN_INFO_OPT_PRIVATE
	12Privat
CHAN_INFO_OPT_KEEPTOPIC
	12Retenció de tópic
CHAN_INFO_OPT_TOPICLOCK
	12Candau de tópic
CHAN_INFO_OPT_SECUREOPS
	12Secure Ops
CHAN_INFO_OPT_LEAVEOPS
	12Leave Ops
CHAN_INFO_OPT_RESTRICTED
	12Accès restringit
CHAN_INFO_OPT_SECURE
	12Segur
CHAN_INFO_OPT_NONE
	12Cap
CHAN_INFO_MODE_LOCK
	Candau de mode: 12%s
CHAN_INFO_NO_EXPIRE
	Aquest canal no expirarà.

# LIST responses
CHAN_LIST_SYNTAX
	12LIST <patron>
CHAN_LIST_HEADER
	Llista d'entrades que satisfan 12%s:
CHAN_LIST_FORMAT
	    %-20s  %s
CHAN_LIST_END
	Fi de llista - 12%d/12%d entrades mostrades.

# INVITE responses
CHAN_INVITE_SYNTAX
	12INVITE <canal>

# OP responses
CHAN_OP_SYNTAX
	12OP <canal> <nick>

# DEOP responses
CHAN_DEOP_SYNTAX
	12DEOP <canal> <nick>

# UNBAN responses
CHAN_UNBAN_SYNTAX
	12UNBAN <canal>

CHAN_UNBANNED
	Has estat desbanejat de 12%s.

# CLEAR responses
CHAN_CLEAR_SYNTAX
	12CLEAR <canal> <opcion>
CHAN_CLEARED_BANS
	Tots el bans a canal 12%s han estat esborrats.
CHAN_CLEARED_MODES
	Tots el modes a canal 12%s han estat esborrats.
CHAN_CLEARED_OPS
	Mode +o d'operadors han estat desactivats del canal 12%s.
CHAN_CLEARED_VOICES
	Mode +v d'alguns usuaris han estat desactivats del canal 12%s.
CHAN_CLEARED_USERS
	Tots els usuaris han estat kickejats del canal 12%s.

# GETPASS responses
CHAN_GETPASS_SYNTAX
	12GETPASS <canal>
CHAN_GETPASS_UNAVAILABLE
	Comanda 12GETPASS no està disponible quan encripció està en ús.
CHAN_GETPASS_PASSWORD_IS
	La clau del canal 12%s és 12%s.

# FORBID responses

CHAN_FORBID_SYNTAX
	12FORBID <canal>
CHAN_FORBID_SUCCEEDED
	Canal 12%s està prohibit de ser utilitzat.
CHAN_FORBID_FAILED
	No fou possible prohibir el canal 12%s!

###########################################################################
#
# Mensajes de MemoServ
#
###########################################################################

# Automatic messages
MEMO_HAVE_NEW_MEMO
	3Eo! tens un missatge nou.
MEMO_HAVE_NEW_MEMOS
	3Eo! tens %d missatges nous.
MEMO_TYPE_READ_LAST
	Escriu 12/msg %s READ LAST per a llegir l'últim.
MEMO_TYPE_READ_NUM
	Escriu 12/msg %s READ %d per a llegir-lo.
MEMO_TYPE_LIST_NEW
	Escriu 12/msg %s LIST NEW per a veure la llista dels nous missatges.
MEMO_AT_LIMIT
	4Atenció: has arribat al nombre màxim de missatges: (12%d). No podràs rebre missatges nous fins que borris alguns dels missatges que tens.
MEMO_OVER_LIMIT
	4Atenció: has passat el límit màxim de missatges: (12%d). No podràs rebre missatges nous fins que borris alguns dels missatges que tens.

MEMO_NEW_MEMO_ARRIVED
	Vosté té un missatge nou de 12%s.	Escriu 12/msg %s READ %d per a llegir-lo.
# Multi-use responses
MEMO_HAVE_NO_MEMOS
	No tens missatges.
MEMO_X_HAS_NO_MEMOS
	12%s no té missatges.
MEMO_DOES_NOT_EXIST
	Missatge 12%d no existeix!
MEMO_LIST_NOT_FOUND
	No s'han trobat memos.

# SEND responses
MEMO_SEND_SYNTAX
	12SEND {nick | canal} <text>
MEMO_SEND_DISABLED
	Ho sento, l'enviament de missatges està temporalment deshabilitat.
MEMO_SEND_PLEASE_WAIT
	Si us plau, esperi 12%d segons abans d'utilitzar la comanda 12SEND novament.
MEMO_X_GETS_NO_MEMOS
	12%s no pot rebre missatges.
MEMO_X_HAS_TOO_MANY_MEMOS
	12%s té massa missatges i no en pot rebre més.
MEMO_SENT
	Missatge enviat a 12%s.

# LIST responses
MEMO_LIST_SYNTAX
	12LIST [canal] [list | NEW]
MEMO_HAVE_NO_NEW_MEMOS
	No tens missatges nous.
MEMO_X_HAS_NO_NEW_MEMOS
	12%s no té missatges nous
MEMO_LIST_MEMOS
	Missatges per a 12%s. Per a llegir-lo, escriu: 12/msg %s READ <nombre>
MEMO_LIST_NEW_MEMOS
	Nous missatges per a 12%s. Per a llegir-los, escriu: 12/msg %s READ <nombre>
MEMO_LIST_CHAN_MEMOS
	Missatge per a 12%s. Per a llegir-los, escriu: 12/msg %s READ %s <nombre>
MEMO_LIST_CHAN_NEW_MEMOS
	Nous missatges per a 12%s.  Per a llegir-los, escriu: 12/msg %s READ %s <nombre>
MEMO_LIST_HEADER
	 Num  Remitent          Día/Hora
MEMO_LIST_FORMAT
	%c%3d  %-16s  %s

# READ responses
MEMO_READ_SYNTAX
	12READ [canal] {list | LAST | NEW}
MEMO_HEADER
	Missatge 12%d de 12%s (12%s). Per a esborrar-lo, escrigui: 12/msg %s DEL %d
MEMO_CHAN_HEADER
	Missatge 12%d de 12%s (12%s). Per a esborrar-lo, escrigui: 12/msg %s DEL %s %d
MEMO_TEXT
	%s

# DEL responses
MEMO_DEL_SYNTAX
	12DEL [canal] {numero | list | ALL}
MEMO_DELETED_NONE
	Cap missatge ha estat esborrat.
MEMO_DELETED_ONE
	Missatge 12%d ha estat esborrat.
MEMO_DELETED_SEVERAL
	12%d missatges han estat esborrats.
MEMO_DELETED_ALL
	Tots els seus missatges hane estat esborrats.

# SET responses
MEMO_SET_SYNTAX
	12SET <opció> <paràmetres>
MEMO_SET_DISABLED
	Ho sento, l'opció d'adjust de missatges està temporalment deshabilitada.
MEMO_SET_UNKNOWN_OPTION
	4Opció SET 12%s desconeguda.

# SET NOTIFY responses
MEMO_SET_NOTIFY_SYNTAX
	12SET NOTIFY {ON | LOGON | NEW | OFF}
MEMO_SET_NOTIFY_ON
	12%s et notificarà dels teus missatges quan et conectis o quan et siguin enviats.
MEMO_SET_NOTIFY_LOGON
	12%s et notificarà dels teus missatges quen et conectis o cancel·lis el teu mode /AWAY.
MEMO_SET_NOTIFY_NEW
	12%s et notificarà dels teus missatges quan et siguin enviats.
MEMO_SET_NOTIFY_OFF
	12%s no et notificarà els teus missatges.

# SET LIMIT responses
MEMO_SET_LIMIT_SYNTAX
	12SET LIMIT [canal_] <límit>
MEMO_SET_LIMIT_SERVADMIN_SYNTAX
	12SET LIMIT [ nick | canal] {límit | NONE} [HARD]
MEMO_SET_YOUR_LIMIT_FORBIDDEN
	No pots canviar el teu límit de missatges.
MEMO_SET_LIMIT_FORBIDDEN
	El límit de missatges per a 12%s no pot ser canviat.
MEMO_SET_YOUR_LIMIT_TOO_HIGH
	No pots adjustar el teu límit de missatges superior a 12%d.
MEMO_SET_LIMIT_TOO_HIGH
	No pots adjustar el límit de missatges per a 12%s més alt que 12%d.
MEMO_SET_LIMIT_OVERFLOW
	Limit de missatges molt alt; limitant a 12%d.
MEMO_SET_YOUR_LIMIT
	El teu límit de missatges ha estat adjustat a 12%d.
MEMO_SET_YOUR_LIMIT_ZERO
	No podràs rebre missatges.
MEMO_SET_LIMIT
	Límit de missatges per a 12%s adjustat a 12%d.
MEMO_SET_LIMIT_ZERO
	Límit de missatges per a 12%s adjustat a 120.
MEMO_UNSET_YOUR_LIMIT
	El teu límit de missatges ha estat deshabilitat.
MEMO_UNSET_LIMIT
	Límit de missatges desactivat per a 12%s.

# INFO responses
MEMO_INFO_SYNTAX
	12INFO [canal]
MEMO_INFO_NO_MEMOS
	No tens missatges.
MEMO_INFO_MEMO
	Tens12 1 missatge.
MEMO_INFO_MEMO_UNREAD
	Tens12 1 missatges, i no ha estat llegit.
MEMO_INFO_MEMOS
	Tens 12%d missatges.
MEMO_INFO_MEMOS_ONE_UNREAD
	Tens %d missatges, dels quals 1 no ha estat llegit.
MEMO_INFO_MEMOS_SOME_UNREAD
	Tens 12%d missatges, dels quals 12%d no han estat llegits.
MEMO_INFO_MEMOS_ALL_UNREAD
	Tens 12%d missatges; dels qual cap no ha estat llegit.
MEMO_INFO_LIMIT
	El teu límit de missatges és 12%d.
MEMO_INFO_HARD_LIMIT
	El teu límit de missatges és 12%d, i no pot ser canviat.
MEMO_INFO_LIMIT_ZERO
	El teu límit de missatges és12 0; no rebràs cap missatges nou.
MEMO_INFO_HARD_LIMIT_ZERO
	El teu límit de missatges és12 0; no rebràs cap missatge nou. No pots canviar aquest límit.
MEMO_INFO_NO_LIMIT
	No tens límit a la quantitat de missatges que pot guardar.
MEMO_INFO_X_NO_MEMOS
	12%s no té missatges.
MEMO_INFO_X_MEMO
	12%s té actualment12 1 missatge.
MEMO_INFO_X_MEMO_UNREAD
	12%s té actualment1 1 missatge, i no s'ha llegit encara.
MEMO_INFO_X_MEMOS
	12%s té actualment 12%d missatges
MEMO_INFO_X_MEMOS_ONE_UNREAD
	12%s té actualment 12%d missatges, dels quals12 1 està sense llegir.
MEMO_INFO_X_MEMOS_SOME_UNREAD
	12%s té actualment 12%d missatges, dels quals 12%d estan sense llegir.
MEMO_INFO_X_MEMOS_ALL_UNREAD
	12%s té actualment 12%d missatges; dels quals tots estan sense llegir.
MEMO_INFO_X_LIMIT
	El límit de missatges de 12%s és 12%d.
MEMO_INFO_X_HARD_LIMIT
	El límit de missatges de 12%s és 12%d, i no pot ser canviat per l'usuari.
MEMO_INFO_X_NO_LIMIT
	12%s no té límit de missatges.

###########################################################################
#
# Mensajes de OperServ
#
###########################################################################

# General messages
OPER_BOUNCY_MODES
	Services no pot canviar modes!
	Els teus servidors estan configurats correctament?
OPER_BOUNCY_MODES_U_LINE
	Services no pot canviar modes.
	Les línees U: dels seus servidors estan configurades correctament?

# GLOBAL responses
OPER_GLOBAL_SYNTAX
	12GLOBAL <missatge>

# STATS responses
OPER_STATS_UNKNOWN_OPTION
	4Opció STATS 12%s desconeguda.
OPER_STATS_CURRENT_USERS
	Usuaris actuals: 12%d (12%d ircops)
OPER_STATS_MAX_USERS
	Màxim d'usuaris: 12%d (12%s)
# This is ugly, but at least it's language-portable...
OPER_STATS_UPTIME_DHMS
	Services actius 12%d dies, 12%02d:%02d
OPER_STATS_UPTIME_1DHMS
	Services actius 12%d dia, 12%02d:%02d
OPER_STATS_UPTIME_HMS
	Services actius 12%d hores, 12%d minuts
OPER_STATS_UPTIME_HM1S
	Services actius 12%d hores, 12%d minuts
OPER_STATS_UPTIME_H1MS
	Services actius 12%d hores, 12%d minut
OPER_STATS_UPTIME_H1M1S
	Services actis 12%d hores, 12%d minut
OPER_STATS_UPTIME_1HMS
	Services actius 12%d hora, 12%d minuts
OPER_STATS_UPTIME_1HM1S
	Services actius 12%d hora, 12%d minuts
OPER_STATS_UPTIME_1H1MS
	Services actius 12%d hora, 12%d minut
OPER_STATS_UPTIME_1H1M1S
	Services actius 12%d hora, 12%d minut
OPER_STATS_UPTIME_MS
	Services actius 12%d minuts, 12%d segons
OPER_STATS_UPTIME_M1S
	Services actius 12%d minuts, 12%d segons
OPER_STATS_UPTIME_1MS
	Services actius 12%d minut, 12%d segons
OPER_STATS_UPTIME_1M1S
	Services actius 12%d minut, 12%d segon
OPER_STATS_BYTES_READ
	Bytes llegits  : 12%5d kB
OPER_STATS_BYTES_WRITTEN
	Bytes escrits  : 12%5d kB
OPER_STATS_USER_MEM
	Usuaris : 12%6d registres, 12%5d kB
OPER_STATS_CHANNEL_MEM
	Canals  : 12%6d registres, 12%5d kB
OPER_STATS_NICKSERV_MEM
	NiCK    : 12%6d registres, 12%5d kB
OPER_STATS_CHANSERV_MEM
	CHaN    : 12%6d registres, 12%5d kB
OPER_STATS_OPERSERV_MEM
	OPeR    : 12%6d registres, 12%5d kB
OPER_STATS_AKILL_COUNT
	Nombre actual d'AKILLs: 12%d
OPER_STATS_AKILL_EXPIRE_DAYS
	Temps default per a expirar AKILL: 12%d dies
OPER_STATS_AKILL_EXPIRE_DAY
	Temps default per a expirar AKILL:12 1 dea
OPER_STATS_AKILL_EXPIRE_HOURS
	Temps default per a expirar AKILL: 12%d hores
OPER_STATS_AKILL_EXPIRE_HOUR
	Temps default per a expirar AKILL:12 1 hora
OPER_STATS_AKILL_EXPIRE_MINS
	Temps default per a expirar AKILL: 12%d minutss
OPER_STATS_AKILL_EXPIRE_MIN
	Temps default per a expirar AKILL:12 1 minut
OPER_STATS_AKILL_EXPIRE_NONE
	Temps default per a expirar AKILL: 12No expira
OPER_STATS_SESSIONS_MEM
	Sessions: 12%6d records, 12%5d kB

# MODE responses
OPER_MODE_SYNTAX
	12MODE <canal> <modes>

# CLEARMODES responses
OPER_CLEARMODES_SYNTAX
	12CLEARMODES <canal> [ALL]

OPER_CLEARMODES_DONE
	Modes i bans del canal 12%s han estat netejats.

OPER_CLEARMODES_ALL_DONE
	Tots els modes del canal 12%s han estat netejats.

# KICK responses
OPER_KICK_SYNTAX
	12KICK <canal> <nick> <motiu>

# ADMIN responses
OPER_ADMIN_SYNTAX
	12ADMIN {ADD | DEL | LIST} [nick]
OPER_ADMIN_ADD_SYNTAX
	12ADMIN ADD <nick>
OPER_ADMIN_DEL_SYNTAX
	12ADMIN DEL <nick>

OPER_ADMIN_SKELETON
	Services està en mode skeleton; la comanda 12ADMIN no està disponible.
OPER_ADMIN_EXISTS
	12%s ja es troba a la llista d'Administradors de Services.
OPER_ADMIN_ADDED
	12%s introduït a la llista d'Administradors de Services.
OPER_ADMIN_TOO_MANY
	Massa entrades (12%d) a la llista d'Administradores de Services; no es poden introduïr més.
OPER_ADMIN_REMOVED
	12%s esborrat de la llista d'Administradors de Services.
OPER_ADMIN_NOT_FOUND
	12%s no fou trobat a la llista d'Administradors de Services.
OPER_ADMIN_LIST_HEADER
	Llista d'Administradors de Services:

# OPER responses
OPER_OPER_SYNTAX
	12OPER {ADD | DEL | LIST} [nick]
OPER_OPER_ADD_SYNTAX
	12OPER ADD <nick>
OPER_OPER_DEL_SYNTAX
	12OPER DEL <nick>
OPER_OPER_SKELETON
	Services està en mode skeleton; la comanda OPER no està disponible.
OPER_OPER_EXISTS
	12%s ja es trobava a la llista d'Operadors de Services.
OPER_OPER_ADDED
	%s introduït a la llista d'Operadors de Services.
OPER_OPER_TOO_MANY
	Moltes entrades (12%d) a la llista d'Operadors de Services; no es poden introduïr més.
OPER_OPER_REMOVED
	12%s esborrat de la llista d'Operadors de Services.
OPER_OPER_NOT_FOUND
	12%s no fou trobat a la llista d'Operadors de Services.
OPER_OPER_LIST_HEADER
	Llista d'Operadors de Services:

# AKILL responses
OPER_AKILL_SYNTAX
	12AKILL {ADD | DEL | LIST | VIEW} [[+expiracion] <mask> [motiu]]
OPER_AKILL_ADD_SYNTAX
	12AKILL ADD [+expiracion] <mask> <motiu>
OPER_AKILL_DEL_SYNTAX
	12AKILL DEL <mascara>
OPER_TOO_MANY_AKILLS
	La llista d'AKILL està plena!
OPER_AKILL_NO_NICK
	4Atenció: Màscares d'12AKILL no poden contenir nicks;
	Tingui la certesa de 4NO incloure una part de nick a la seva màscara.
OPER_AKILL_ADDED
	12%s introduït a la llista d'AKILL.
OPER_AKILL_REMOVED
	12%s eliminat de la llista d'AKILL.
OPER_AKILL_NOT_FOUND
	12%s no fou trobat a la llista d'AKILL.
OPER_AKILL_LIST_HEADER
	Llista actual d'AKILL:
# mask, reason
OPER_AKILL_LIST_FORMAT
	%-32s  %s
# mask, set-by, set-time, expires, reason
OPER_AKILL_VIEW_FORMAT
	%s (por %s en %s; %s)
	    %s
OPER_AKILL_NO_EXPIRE
	no expira
OPER_AKILL_EXPIRES_SOON
	expira a la següent actualització de base de dades
OPER_AKILL_EXPIRES_M
	expira en 12%d minuts
OPER_AKILL_EXPIRES_1M
	expira en 12%d minut
OPER_AKILL_EXPIRES_HM
	expira en 12%d hores, 12%d minuts
OPER_AKILL_EXPIRES_H1M
	expira en 12%d hores, 12%d minut
OPER_AKILL_EXPIRES_1HM
	expira en 12%d hora, 12%d minuts
OPER_AKILL_EXPIRES_1H1M
	expira en 12%d hora, 12%d minut
OPER_AKILL_EXPIRES_D
	expira en 12%d dies
OPER_AKILL_EXPIRES_1D
	expira en 12%d dia

# SET responses
OPER_SET_SYNTAX
	12SET <opció> <paràmetres>
OPER_SET_IGNORE_ON
	Ignore code serà usat.
OPER_SET_IGNORE_OFF
	Ignore code no serà usat.
OPER_SET_IGNORE_ERROR
	Paràmetre per a IGNORE deu ser ON o OFF.
OPER_SET_READONLY_ON
	Services està ara en mode llegir-solament read-only.
OPER_SET_READONLY_OFF
	Services està ara en mode llegir-escriure read-write.
OPER_SET_READONLY_ERROR
	Paràmetre per a READONLY deu ser ON o OFF.
OPER_SET_DEBUG_ON
	Services està ara en mode debug.
OPER_SET_DEBUG_OFF
	Services està ara en mode non-debug.
OPER_SET_DEBUG_LEVEL
	Services està ara en mode debug (nivell %d).
OPER_SET_DEBUG_ERROR
	Paràmetre per a DEBUG deu ser ON, OFF, o un nombre positiu.
OPER_SET_UNKNOWN_OPTION
	Opció %s desconeguda.

# JUPE responses
OPER_JUPE_SYNTAX
	12JUPE <servidor> [motiu]

# RAW responses
OPER_RAW_SYNTAX
	12RAW <text>

# UPDATE responses
OPER_UPDATING
	Actualitzant bases de dades.

# RESTART responses
OPER_CANNOT_RESTART
	SERVICES_BIN no definida; no és possible reiniciar. Executi novament l'script 12./configure i recompili Services per a habilitar la comanda 12RESTART.

# LISTIGNORE responses
OPER_IGNORE_LIST
	Llista d'ignoració de Services:
OPER_IGNORE_LIST_EMPTY
	Llista d'ignoració està buïda.

# KILLCLONES responses
OPER_KILLCLONES_SYNTAX
	12KILLCLONES <nick>
OPER_KILLCLONES_UNKNOWN_NICK
	No ha estat trobat el nick 12%s.

# ROTATELOG responses
OPER_ROTATELOG_FILE_EXISTS
	No ha pogut renombrar el log, un arxiu amb el nom 12%s encara existeix!
OPER_ROTATELOG_RENAME_DONE
	Log renombrat a 12%s
OPER_ROTATELOG_RENAME_FAIL
	Log no ha pogut renombrar-lo: 12%s
OPER_ROTATELOG_OPEN_LOG_FAIL
	Loguejant no ha pogut reiniciar: 12%s

###########################################################################
#
# Session Limiting and Exception messages
#
###########################################################################

# EXCEPTION responses
OPER_EXCEPTION_SYNTAX
	12EXCEPTION {ADD | DEL | MOVE | LIST | VIEW} [parametros]
OPER_EXCEPTION_ADD_SYNTAX
	12EXCEPTION ADD [+expiracion] <mascara> <limite> <razon>
OPER_EXCEPTION_DEL_SYNTAX
	12EXCEPTION DEL {mascara | list}
OPER_EXCEPTION_MOVE_SYNTAX
	12EXCEPTION MOVE <numero> <posicion>
OPER_EXCEPTION_DISABLED
	Session limiting is disabled.
OPER_EXCEPTION_ALREADY_PRESENT
	Mask 12%s already present on exception list.
OPER_EXCEPTION_TOO_MANY
	Session-limit exception list is full!
OPER_EXCEPTION_ADDED
	Session limit for 12%s set to 12%d.
OPER_EXCEPTION_MOVED
	Exception for 12%s (12#%d) moved to position 12%d.
OPER_EXCEPTION_NO_SUCH_ENTRY
	No such entry (12#%d) session-limit exception list.
OPER_EXCEPTION_NOT_FOUND
	12%s not found on session-limit exception list.
OPER_EXCEPTION_NO_MATCH
	No matching entries on session-limit exception list.
OPER_EXCEPTION_DELETED
	12%s deleted from session-limit exception list.
OPER_EXCEPTION_DELETED_ONE
	Deleted12 1 entry from session-limit exception list.
OPER_EXCEPTION_DELETED_SEVERAL
	Deleted 12%d entries from session-limit exception list.
OPER_EXCEPTION_LIST_HEADER
	Current Session Limit Exception list:
# mask, limit
OPER_EXCEPTION_LIST_FORMAT
	%3d  %4d   %s
OPER_EXCEPTION_LIST_COLHEAD
	Num  Limite  Host
# mask, set-by, set-time, expires, limit, reason
OPER_EXCEPTION_VIEW_FORMAT
	%3d.  %s  (by %s on %s; %s)
	    Limit: %-4d  - %s
OPER_EXCEPTION_INVALID_LIMIT
	Invalid session limit. It must be a valid integer greater than or equal
OPER_EXCEPTION_INVALID_HOSTMASK
	Invalid hostmask. Only real hostmasks are valid as exceptions are not m

# SESSION responses
OPER_SESSION_SYNTAX
	12SESSION {LIST limite | VIEW host}
OPER_SESSION_LIST_SYNTAX
	12SESSION LIST <limite>
OPER_SESSION_VIEW_SYNTAX
	12SESSION VIEW <host>
OPER_SESSION_DISABLED
	Session limiting is disabled.
OPER_SESSION_INVALID_THRESHOLD
	Invalid threshold value. It must be a valid integer greater than 1.
OPER_SESSION_NOT_FOUND
	12%s not found on session list.
OPER_SESSION_LIST_HEADER
	Hosts with atleast 12%d sessions:
OPER_SESSION_LIST_COLHEAD
	Sessions  Host
# limit, host
OPER_SESSION_LIST_FORMAT
	%6d    %s
# host, sessions, limit
OPER_SESSION_VIEW_FORMAT
	The host 12%s currently has B%dB sessions with a limit of 12%d.

###########################################################################
#
# News system messages
#
###########################################################################

NEWS_LOGON_TEXT
	[4Noticias de la red - 12%s] %s
NEWS_OPER_TEXT
	[4Noticias OPERS - 12%s] %s

NEWS_LOGON_SYNTAX
	Sintaxis: 12LOGONNEWS {ADD|DEL|LIST} [texto|numero]
NEWS_LOGON_LIST_HEADER
	Logon news items:
NEWS_LOGON_LIST_ENTRY
	%5d (%s by %s)
	    %s
NEWS_LOGON_LIST_NONE
	There is no logon news.
NEWS_LOGON_ADD_SYNTAX
	Sintaxis: 12LOGONNEWS ADD <text>
NEWS_LOGON_ADD_FULL
	News list is full!
NEWS_LOGON_ADDED
	Added new logon news item (12#%d).
NEWS_LOGON_DEL_SYNTAX
	Sintaxis: LOGONNEWS DEL {numero | ALL}
NEWS_LOGON_DEL_NOT_FOUND
	Logon news item 12#%d not found!
NEWS_LOGON_DELETED
	Logon news item 12#%d deleted.
NEWS_LOGON_DEL_NONE
	No logon news items to delete!
NEWS_LOGON_DELETED_ALL
	All logon news items deleted.

NEWS_OPER_SYNTAX
	Sintaxis: 12OPERNEWS {ADD|DEL|LIST} [texto|numero]
NEWS_OPER_LIST_HEADER
	Oper news items:
NEWS_OPER_LIST_ENTRY
	%5d (%s by %s)
	    %s
NEWS_OPER_LIST_NONE
	There is no oper news.
NEWS_OPER_ADD_SYNTAX
	Syntax: 12OPERNEWS ADD <texto>
NEWS_OPER_ADD_FULL
	News list is full!
NEWS_OPER_ADDED
	Added new oper news item (12#%d).
NEWS_OPER_DEL_SYNTAX
	Sintaxis: OPERNEWS DEL {numero | ALL}
NEWS_OPER_DEL_NOT_FOUND
	Oper news item 12#%d not found!
NEWS_OPER_DELETED
	Oper news item 12#%d deleted.
NEWS_OPER_DEL_NONE
	No oper news items to delete!
NEWS_OPER_DELETED_ALL
	All oper news items deleted.

NEWS_HELP_LOGON
	Sintaxis: 12LOGONNEWS ADD <text>
	          12LOGONNEWS DEL {nombre | ALL}
	          12LOGONNEWS LIST
	
	Editar o mostrar la llista de missatges de benviguda de notícies.
	Quan un usuari conecta a la xarxa, aquest missatges han de ser
	enviats a ells. Si hi ha més de 3 missatges, sols s'enviarà els
	3 missatges més nous.
	
	12LOGONNEWS LIST deu ser usat per algun IRCOP per a llistar els
	missatges de notícies actuals. 12ADD y 12DEL sols podràn ser utilitzats
	per 4Administradors de Services.

NEWS_HELP_OPER
	Sintaxis: 12OPERNEWS ADD texto
	          12OPERNEWS DEL {nombre | ALL}
	          12OPERNEWS LIST
	
	Editar o mostrar la llista de missatges d'IRCOPS de notícies.
	Quan un usuari fa IRCOP (amb la comanda /OPER), aquests
	missatges deuran ser enviats a ells. Si hi ha més de 3 missatges,
	sols s'enviaran els 3 missatges més nous.
	
	12OPERNNEWS LIST deu ser usat per algun IRCOP per a llistar els
	missatges de notícies actuals. 12ADD y 12DEL sols podran ser utilitzats
	per 4Administradors de Services

###########################################################################
#
# Mensajes de ayuda de NickServ
#
##########################################################################

NICK_HELP
	4%S et permet "registrar" un nick i prevenir que altres
	facin ús d'aquest. Si el nick NO s'utilitza durant
	12%d dies, el registre caducarà. Les següents comandes
	permeten el registre i manteniment de
	nicks; per a utilizar-los, escriu 12/msg %S comando.
	
	Per a més informació d'una comanda específica, escriu
	12/msg %S HELP comanda
	
	    12REGISTER   Registra un nick
	    12IDENTIFY   Identificar-te amb la teva clau d'accès
	    12ACCESS     Modificar la llista de direccions autoritzades
	    12LINK       Fer que el teu nick sigui alias d'un altre
	    12SET        Per a adjustar opcions, incloïnt-hi la protecció de kill
	    12DROP       Cancel·la el registre d'un nick
	    12RECOVER    Desconecta a un altre usuari que està utilitzant el teu nick
	    12RELEASE    Pren custodia del teu nick desprès d'utilitzar la
	               comanda RECOVER
	
	Altres comandes: 12UNLINK, 12GHOST, 12INFO, 12LIST, 12STATUS
	
	4NOTA: Aquest servei està dissenyat per a proveïr un mode en
	que els usuaris de IRC asseguren que la seva identitat no sigui
	suplantada. La seva intenció 4NO és per a facilitar el "robament"
	de nicks o altres accions malintencionades. Abús de
	4%S resultarà, al menys, de la pèrdida del/dels
	nick(s) abusiu(s).

NICK_HELP_EXPIRE_ZERO
	12%4 et permet "registrar" un nick i prevenir que altres
	facin ús d'aquest. Les següents comandes
	permeten el registre i manteniment de
	nicks; per a utilizar-los, escriu 12/msg %S comando.
	
	Per a més informació d'una comanda específica, escriu
	12/msg %S HELP comanda
	
	    12REGISTER   Registra un nick
	    12IDENTIFY   Identificar-te amb la teva clau d'accès
	    12ACCESS     Modificar la llista de direccions autoritzades
	    12LINK       Fer que el teu nick sigui alias d'un altre
	    12SET        Per a adjustar opcions, incloïnt-hi la protecció de kill
	    12DROP       Cancel·la el registre d'un nick
	    12RECOVER    Desconecta a un altre usuari que està utilitzant el teu nick
	    12RELEASE    Pren custodia del teu nick desprès d'utilitzar la
	               comanda RECOVER
	
	Altres comandes: 12UNLINK, 12GHOST, 12INFO, 12LIST, 12STATUS
	
	4NOTA: Aquest servei està dissenyat per a proveïr un mode en
	que els usuaris de IRC asseguren que la seva identitat no sigui
	suplantada. La seva intenció 4NO és per a facilitar el "robament"
	de nicks o altres accions malintencionades. Abús de
	12%S resultarà, al menys, de la pèrdida del/dels
	nick(s) abusiu(s).


NICK_HELP_REGISTER
	Sintaxis: 12REGISTER <clau d'accès>
	
	Registra el teu nick a la base de dades de 12%S. Un cop registrat
	el teu nick, vosté pot utilitzar les comandes 12SET i 12ACCESS per a
	configurar els paràmetres del teu nick com vosté els desitgi
	Asseguri's de recordar la clau que va utilitzar per a
	registrar-se, la necessitarà per a fer canviar al seu nick
	posteriorment. (Anoti's que les majúscules importen
	FIDO, Fido, i fido són diferents totes!)
	
	Sugerencies per a escollir una clau d'accès:
	
	Les claus d'accès no deuen ser fàcils d'endevinar. Per exemple,
	utilitzar el seu nom real com a clau és una mala idea.
	Utilitzar el teu nick com a clau és una idea pitjor ;) i, per
	descomptat que, 4%S no ho permetrà. També, claus
	curtes són vulnerables a búsquedes de proba i error, pel
	que vosté deus escollir una clau de al menys 5
	caracters. Finalment, el caràcter d'"espai" no es
	pot utilitzar en claus d'accès.

NICK_HELP_IDENTIFY
	Sintaxis: 12IDENTIFY <clau>
	
	Notifica a 12%S que vosté és l'autèntic amo d'aquest
	nick. Moltes de les comandes requereixen que t'identifiquis
	amb aquesta comanda abans de poder utilitzar-los. La
	clau deu ser la mateixa que va utilitzar amb la comanda
	12REGISTER.

NICK_HELP_DROP
	Sintaxis: 12DROP
	
	Esborra el teu nick de la base de dades de 4%S. Un nick
	que ha estat esborrat està disponible per a que qualsevol
	persona el torni a registar.
	
	Per a utilitzar aquesta comanda, tens que identificar-te
	amb la teva clau d'accès (12/msg %S HELP IDENTIFY per a més
	informació).

NICK_HELP_ACCESS
	Sintaxis: 12ACCESS ADD <mascara>
	          12ACCESS DEL <mascara>
	          12ACCESS LIST
	
	Modifica o mostra la llista d'accès per al seu nick. Aquesta
	és la llista de direccions que 4%S reconeixerà automaticament
	com a vàlides per a utilitzar aquest nick. Si desitja utilitzar aquest
	nick des d'una altra direcció, necessita enviar la comanda
	IDENTIFY per a que 4%S et reconegui.
	
	Exemples:
	
	    12ACCESS ADD achurch@*.dragonfire.net
	        Permet l'accès al usuari 12achurch de qualsevol
	        ordinador al domini 12dragonfire.net.
	
	    12ACCESS DEL achurch@*.dragonfire.net
	        Fa el contrari de la comanda anterior.
	
	    12ACCESS LIST
	        Ens mostra la llista d'accès.
	
NICK_HELP_LINK
	Sintaxis: 12LINK <nick> <clau>
	
	Crea un pseudònim del teu nick, o també un 'alias'
	Quan utilitzes aquesta comanda, la llista d'accès del
	nick que tens és esborrada i subtituïda per la del
	pseudònim del teu nick; tots els missatges per al nick
	actual són introduïts a la llista de missatges del pseudònim.
	(aquest pot causar que el nick s'excedeix al seu límit de
	missatges, en aquest cas necessitaràs esborrar alguns dels
	missatges abans de poder rebre missatges nous per a
	qualsevol d'ambdós nicks).
	
	Un cop has establert l'alias, el teu nick serà convertit
	transparentment al nick nou en totes les bases de
	dades de Services, excepte per a les comandes 12%S UNLINK i
	12DROP. Per exemple, pots utilitzar qualsevol dels
	nicks per a llegir els mateixos missatges (i els missatges que es
	envïen a qualsevol dels nicks aniran a la mateixa llista). Si
	s'identifica per a un nick, automàticament s'identificarà
	per a l'altre. Si qualsevol d'ambdós nicks està a la llista
	d'accès d'un canal, ambdós nicks tindràn els mateixos
	privilegis i accessos.
	
	Per a utilitzar aquesta comanda, deus identificar-te per al
	teu nick actual (utilitzant la comanda 12IDENTIFY), i deu
	proporcia la clau per al nick de l'alias.

NICK_HELP_UNLINK
	Sintaxis: 12UNLINK
	
	Esborra l'alias del teu nick. Quan l'alias
	s'esborra, els modes d'un nick i la llista d'accès del
	nick previament enllaçat són copiats al seu nick actual i
	poden ser modificats independentment. Missatges no són
	copiats; tots els missatges es queden amb el nick
	anterior.

NICK_HELP_SET
	Sintaxis: 12SET <opció> <paràmetres>
	
	Adjusta varis paràmtres del nick. Una opció pot ser:
	
	    12PASSWORD   Adjusta la clau d'accès del teu nick
	    12LANGUAGE   Adjusta el llenguatge que Services utilitzarà quan
	               t'enviï missatges
	    12URL        Associa una URL amb el teu nick
	    12EMAIL      Associa una direcció d'E-Mail amb el teu nick
	    12KILL       Activa/desactiva la protecció de kill
	    12SECURE     Activa/desactiva el mode SECURE per al teu nick
	    12PRIVATE    Fa que el seu nick no aparegui en 12/msg %S LIST
	    12HIDE       Amaga algunes informacions aprop el seu nick
	
	Per a utilitzar aquesta comanda és necessari que t'identifiquis abans
	amb la teva clau d'accès (12/msg %S HELP IDENTIFY per a més
	informació).
	
	Escriu 12/msg %S HELP SET <opció> per a més informació
	d'una opció específica.

NICK_HELP_SET_PASSWORD
	Sintaxis: 12SET PASSWORD <nova-clau>
	
	Canvia la clau d'accès que utilitza per a identificar-se com el
	propietari del nick.

NICK_HELP_SET_LANGUAGE
	Sintaxis: 12SET LANGUAGE <nombre>
	
	Canvia el llenguatge que Services utilitza quan envia
	missatges a vostè (per exemple quan repon a una comanda
	que vostè va enviar). 12nombre deu ser escollit de la següent
	llista de llenguatges soportats:

NICK_HELP_SET_URL
	Sintaxis: 12SET URL <url>
	
	Associa una URL donada amb el teu nick. Aquesta URL serà mostrada
	quan soliciti informació del seu nick amb la comanda 12INFO.

NICK_HELP_SET_EMAIL
	Sintaxis: 12SET EMAIL <direcció>
	
	Associa la direcció d'E-Mail donada amb el teu nick. Aquesta
	direcció serà mostrada quan algú soliciti informació
	del seu nick amb la comanda 12INFO.

NICK_HELP_SET_KILL
	Sintaxis: 12SET KILL {ON | QUICK | IMMED | OFF}
	
	Activa/Desactiva la protecció de kill per al seu nick. Amb
	protecció de kill activada, si algún altre usuari intenta
	utilitzar el teu nick, se li donarà un minut per a que canvïi a
	un altre, si no serà remogur forçadament de l'IRC per 4%S.
	
	Si selecciona 12QUICK, l'usuari sols tindrà vint segons per a
	canviar de nick en lloc de l'usual (60 segons). Si
	selecciona 12IMMED, l'usuari serà desconectat (kill)
	inmediatament 4sense ser avisat primer o donar-li una
	oportunitat de canviar de nick, feu el favor de no utilitzar aquesta
	opció, a menys que sigui realment necessari. Els
	Administradors de la xarxa poden haver deshabilitat aquesta opció.

NICK_HELP_SET_SECURE
	Sintaxis: 12SET SECURE {ON | OFF}
	
	Activa/Desactiva les funcions de seguretat de 4%S per al
	teu nick. Amb 12SECURE activat, vosté deu d'enviar la seva
	clau d'accès abans que se'l reconegui com el propietari del
	nick, sense importat si la seva direcció estigui o no a la llista
	d'accès. En canvi, si apareix a la llista d'accès, 12%S
	no el desconectarà automàticament, independentment de
	com estigui l'opció de 12KILL.

NICK_HELP_SET_PRIVATE
	Sintaxis: 12SET PRIVATE {ON | OFF}
	
	Activa/desactiva la opció privacitat de 4%S del teu
	nick. Amb 12PRIVATE activat, el teu nick no apareixerà a les
	llistes de nicks generades amb la comanda 12%S LIST.
	(En canvi, qualsevol que conegui el teu nick pot obtenir
	informació usant la comanda 12INFO.)

NICK_HELP_SET_HIDE
	Sintaxis: 12SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
	
	Permet i evita que determinades informacions siguin
	mostrades quan algú usa la comanda 12%S INFO al teu
	nick. Vosté pot amagar el seu E-Mail (12EMAIL), última
	màscara user@host (12USERMASK), o el seu últim missatge de sortida
	(12QUIT). El segon paràmetre especifica quina informació
	deu ser mostrada (12OFF) o amagada (12ON).

NICK_HELP_RECOVER
	Sintaxis: 12RECOVER <nick> [contraseña]
	
	Permet que recuperis el teu nick si algú més l'ha
	prés; aquest és el mateix que 4%S fa automàticament si
	algú intenta utilitzar un nick portegit amb kill.
	
	Quan vosté envia aquesta comanda, 4%S conectarà en linea a un
	usuari fals amb el mateix nick que l'usuari que vosté
	desitgi recuperar. Això causarà que els servidors de IRC
	desconectin a l'altre usuari. L'usuari fals permaneixerà
	en línea un minut per a assegurar que l'altre usuari no
	es reconecti inmediatament; desprès d'un minut, vosté
	ja podrà agafar el seu nick. Alternativament, usi la comanda
	12RELEASE (12/msg %S HELP RELEASE) per a obtenir el teu nick
	més ràpid.
	
	Per a usar la comanda 12RECOVER per a un nick, la teva direcció
	actual com es mostra en un /WHOIS deu d'estar a la
	llista d'accès del nick, o vosté deu proporcionar la
	clau d'accès correcta per al nick.

NICK_HELP_RELEASE
	Sintaxis: 12RELEASE <nick> [clau]
	
	Mana a 4%S esborrar qualsevol espera al seu nick
	causada per un kill automàtic de protecció o per l'ús de
	la comanda 12RECOVER. Per defecte, l'espera dura un minut;
	aquesta comanda el llibera més ràpidament.
	
	Per a usar la comanda 12RELEASE per a un nick, la seva direcció
	actual com es mostra en un /WHOIS deu d'estar a la
	llista d'accès del nick, o vostè deu de proporcionar la
	clau d'accès correcta per al nick.

NICK_HELP_GHOST
	Sintaxis: 12GHOST <nick> [clau]
	
	Esborrar un sessió "fantasma" d'IRC que estigui utilitzant el teu
	nick. Una sessió "fantasma" és aquella que no està
	realment conectada, però que un servidor de IRC acredita
	com activa per qualsevol raó. Típicament això succeeix si
	el seu ordinador es penja o la seva conexió a Internet es
	desconecta per un periode curt mentre es troba a l'IRC.
	
	Per a usar la comanda 12GHOST per a un nick, la seva direcció
	actual com es mostra en un /WHOIS deu d'estar a la
	llista d'accès del nick, o vostè deu de proporcionar la
	clau d'accès correcta per al nick.

NICK_HELP_INFO
	Sintaxis: 12INFO <nick>
	
	Ens mostra informació d'un nick donat, com qui és
	el propietari, última direcció utilitzada i hora, i les
	diferents opcions del nick.

NICK_HELP_LIST
	Sintaxis: 12LIST <patró>
	
	Llista tots els nicks registrats que concorden amb un
	patró donat en format 12nick!user@host. Nicks amb la opció
	de PRIVATE activada no seràn mostrats.
	
	Exemples:
	
	    12LIST *!joeuser@foo.com
	         Llista els nicks registrats per joeuser@foo.com
	
	    12LIST *Bot*!*@*
	        Llista tots els nicks registrats que contenguin Bot
		al seu nom (no importa majúscules).
		
	    12LIST *!*@*.bar.org
	        Llista tots els nicks registrats per usuaris del domini 12bar.org.

NICK_HELP_STATUS
	Sintaxis: 12STATUS <nick1> <nick2>...
	
	Informa si l'usuari d'un nick és reconegut com el propietari
	del mateix. La resposta té el següent format:
	
	    12nick 12code-de-status
	
	on 12nick és el nick enviat amb la comanda,
	12code-de-status és un dels següents:
	
	    0 - usuari no està conectat 12o nick no està registrat
	    1 - usuari no reconegut com a propietari del nick
	    2 - usuari reconegut per la llista d'accès solament
	    3 - usuari reconegut per identificació amb clau d'accès
	
	Fins 16 nicks poden ser enviats amb cada comanda: la
	resta seràn ignorats. No es genera missatge d'error si no
	s'envia nick.

NICK_SERVADMIN_HELP
	
	Les següents comandes estàn disponibles per als
	4Administradors de Services:
	
	    12SENDPASS
	    12GETPASS    Mostra la clau d'accès per a un nick
	    12SUSPEND
	    12UNSUSPEND
	    12FORBID     Evita que un nick sigui utilizat
	    12UNFORBID
	    12NICKREG
	    12VHOSTADD
	    12VHOSTDEL
	
	4Administradors de Services poden cancel·lar qualsevol nick
	sense necessitat d'identificar-se pel mateix, i poden veure la
	llista d'accès de qualsevol nick (12/msg %S ACCESS LIST <nick>).

NICK_SERVADMIN_HELP_DROP
	Sintaxis: 12DROP [nick]
	
	Sense paràmetres, cancel·la el registre del teu nick de la base de
	dades de 12%S.

	Amb un paràmetre, cancel·la el registre d'aquest nick a la base
	de dades. Aquesta comanda està registringida a 4Administradors
	4de Services.

NICK_SERVADMIN_HELP_SET
	
	4Administradors de Services poden seleccionar la opció
	12NOEXPIRE, amb la qual es pot prevenir que alguns nicks no
	expirin. Adicionalment, els 4Administradors de Services
	poden establir opcions per a qualsevol nick sense necessitat
	de proveïr una clau, utilitzant el format
	12SET <nick> <opció> <paràmetres>.

NICK_SERVADMIN_HELP_SET_NOEXPIRE
	Sintaxis: 12SET [nick] NOEXPIRE {ON | OFF}
	
	Defineix si el nick donat expirarà. Si es defineix 12ON prevé
	que el nick expiri. Si no s'inclou el nick, aleshores
	s'aplica al teu propi nick.
	
	Limitat a 4Administradors de Services.

NICK_SERVADMIN_HELP_UNLINK
	
	4Administradors de Services poden desenllaçar algun nick sense
	necessitat de proveïr una clau d'accès.

NICK_SERVADMIN_HELP_LISTLINKS
	Syntax: 12LISTLINKS <nick> [ALL]
	
	Llista els nicks els qual estàn enllaçats al nick donat. Si has
	posat 12ALL, llista tots els nicks que siguin enllaçats.
	
	Limitado a 4Administradors de Services.

NICK_SERVADMIN_HELP_INFO
	
	4Administradors de Services poden usar el paràmetre  12ALL
	amb algun nick.

NICK_SERVADMIN_HELP_LIST
	Sintaxis: 12LIST <patró> [FORBIDDEN] [NOEXPIRE]
	
	Llista tots els nicks registrats que concordin amb el
	patró definit, en format 12nick!usuario@host. Nicks
	amb la opció 12PRIVATE activada sols seràn mostrats a
	4Administradors de Services.
	
	Si has posat la opció 12FORBIDDEN o 12NOEXPIRE sols
	llista de nicks, respectivament, tenen el flag 12FORBIDden
	o el flag 12NOEXPIRE
	
	Aquestes opcions estan limitades 4Administradors de Services.
	
	Exemples:
	
	    12LIST *!joeuser@foo.com
	        Llista tots els nicks registrats per joeuser@foo.com.

	    12LIST *Bot*!*@*
	        Llista tots els nicks registrats que continguin 12Bot
		al seu nom (no importen les majúscules).
	
	    12LIST * NOEXPIRE
	        Llista tots els nicks registrats que no expiraràn.

NICK_SERVADMIN_HELP_GETPASS
	Sintaxis: 12GETPASS <nick>
	
	Mostra la clau d'accès per al nick donat. 4Nota que quan
	aquesta comanda és utlitzada, el seu missatge incloïnt-hi el nick de
	la persona que l'utlilitzarà, el nick sobre qual s'interroga
	és gravat al log i enviat amb un missatge global
	(WALLOPS/GLOBOPS).
	
	Limitat a 4Administradors de Services.
	
	Aquesta comanda no està disponible quan encripció està en
	ús.

NICK_SERVADMIN_HELP_FORBID
	Sintaxis: 12FORBID <nick>
	
	Prohibeix el registre i la utilització d'un nick. Es pot
	cancel·lar utlitzant la comanda 12DROP.
	
	Limitat a 4Administradors de Services.

###########################################################################
#
# Mensajes de Ayuda de ChanServ
#
###########################################################################

CHAN_HELP
	4%S permet registrar i controlar varis aspectes dels
	canals. 4%S pot prevenir que usuaris
	malintencionats poguin "prendre" el control limitat a qui
	se'l permet privilegis d'operador del canal. Les comandes
	disponibles són les següentes. Per a utilitzar-les, escrigui
	12/msg %S comanda. Per a obtenir més informació d'una comanda
	específica, escrigui 12/msg %S HELP comando.
	
	    12REGISTER   Registra un canal
	    12IDENTIFY   Per a identificar-se com a fundador del canal
	    12SET        Fixa opcions i informació del canal
	    12ACCESS     Modifica la llista d'usuaris privilegiats
	    12LEVELS     Redefineix els nivells d'accessos
	    12AKICK      Manté la llista d'Auto-Kick
	    12DROP       Cancel·la el registre d'un canal
	
	Altres comandes: 12INFO, 12LIST, 12INVITE, 12OP, 12DEOP, 12UNBAN,
	                 12CLEAR

CHAN_HELP_EXPIRES
	
	Anoti que si un canal no és utilitzat en 12%d dies (és a dir
	que cap usuari a la llista d'accès del canal entra en
	aquest periode de temps) serà automàticament cancel·lat.

CHAN_HELP_REGISTER
	Sintaxis: 12REGISTER <canal> <clau> <descripció>
	
	Registra un nou canal a la base de dades de 4%S.
	Per a poder utilitzar aquesta comanda, vosté primer deu ser
	operador del canal que està intentat registrar (1). La
	clau deurà ser utilitzada amb la comanda 12IDENTIFY
	quan necessiti fer modificacions posteriors a opcions
	del canal. L'últim paràmetre, que 12debe ser inclòs,
	és una descripció dels propòsits del canal.
	
	Quan vosté registra un canal, vosté queda registrat com a
	el "fundador" del canal. El fundador d'un canal pot
	modificar qualsevol de les opcions d'un canal (excepte el
	nom mateix del canal); 4%S li donarà automàticament
	privilegi d'operador al fundador del canal quan ell/ella
	ingressin al canal. Miri la comanda 12ACCESS
	(12/msg %S HELP ACCESS) per a obtenir informació de com
	donar privilegi d'operadors a altres usuaris del canal.
	
	(1) AVÍS: per a poder registrar un canal, el seu nick deu estar
	registrat. Si encara no el va registrar, escrigui
	12/msg %s HELP per a obtenir informació de com fer-ho.

CHAN_HELP_IDENTIFY
	Sintaxis: 12IDENTIFY <canal> <clau>
	
	Aquesta comanda, l'identifica a vostè a 4%S com el
	fundador del 12canal12. Moltes comandes requereixen que vosté
	utilitzi AQUESTA comanda abanar de poder utilitzar-les. La
	clau deu ser la mateixa que va ingressar al moment de
	registrar el canal (comanda 12REGISTER).

CHAN_HELP_DROP
	Sintaxis: 12DROP <canal>
	
	Esborra el 12canal de la base de 4%S. Pot ser
	utilitzar únicament pel 12fundador del canal, qui deurà
	primerament identificar-se amb la comanda 12IDENTIFY.

CHAN_HELP_SET
	Sintaxis: 12SET <canal> <opció> <paràmetres>
	
	Habilita al fundador del canal a definir varies opcions i
	altra informació. El fundador, deu identificar-se via
	comanda 12IDENTIFY abans d'utilitzar 12SET.
	
	Opcions disponibles:
	
	    12FOUNDER     Canvia el fundador del canal
	    12PASSWORD    Canvia la clau d'accès del fundador
	    12SUCCESSOR   Canvia el successor del canal
	    12DESC        Canvia la descripció del canal
	    12URL         Associa una URL al canal
	    12EMAIL       Assicia una direcció de correu al canal
	    12ENTRYMSG    Fixa un missatge que serà mostrat als usuaris
			quan entrin al canal
	    12TOPIC       Canvia el Tema del canal
	    12KEEPTOPIC   Reté el teme (topic) quan el canal no està en ús
	    12TOPICLOCK   El Tems SOLAMENT podrà ser canviat via SET TOPIC
	    12MLOCK       Fixa els modes del canal en 'ON' o 'OFF'
	    12PRIVATE     Amaga el canal (no es veu quan s'utilitza la comanda LIST)
	    12RESTRICTED  Restringeix l'accès al canal
	    12SECURE      Activa els indicis de seguretat de %S
	    12SECUREOPS   Control estricte de Status d'operador
	    12LEAVEOPS    Mai deopejar a usuaris excepte amb la comanda DEOP
	    12ISSUED      Mode DEBUG, envia una noticia al canal sobre les comandes usades
	
	Escrigui 12/msg %S HELP opció per a obtenir més
	informació d'una opció en particular.

CHAN_HELP_SET_FOUNDER
	Sintaxis: 12SET <canal> FOUNDER <nick>
	
	Canvia el fundador del 12canal. El nick donat, que serà el
	nou fundador del canal, deu estar registrat.

CHAN_HELP_SET_SUCCESSOR
	Syntax: 12SET <canal> SUCCESSOR <nick>
	
	Canvia el successor del canal. Si el nick del fundador expira o
	és dropejat, el canal perd el registre, amb el successor es
	transforma en el nou founder del canal i evita la pèrdua del
	canal. Però, si el successor té massa canals registrats
	(12%d), el canal serà dropejar al no haver-hi cap successor.
	El nick del successor deu estar registrat.

CHAN_HELP_SET_PASSWORD
	Sintaxis: 12SET <canal> PASSWORD <clau>
	
	S'utilitza per a definir la clau que serpa utilitzada
	per a identificar-se com a fundador del canal.

CHAN_HELP_SET_DESC
	Sintaxis: 12SET <canal> DESC <descripció>
	
	Fixa la descripció del canal, la qual serà mostrada quan
	s'utilitzin les comandes 12LIST i 12INFO. Sigui breu i concret.

CHAN_HELP_SET_URL
	Sintaxis: 12SET <canal> URL [url]
	
	Associa una URL al 12canal, la qual serà visualitzada quan
	es soliciti informació del canal (via comanda 12INFO).
	Habitualment s'utilitza per a indicar la direcció de la
	pàgina web del canal. Si no s'ingressa cap url, s'esborrarà
	la que tingui actualment el canal.

CHAN_HELP_SET_EMAIL
	Sintaxis: 12SET <canal> EMAIL [direcció]
	
	Associa la direcció deu correu donada al canal. Aquesta direcció
	serà mostrada quan algú soliciti (via comanda 12INFO)
	informació del canal. És molt útil, per exemple, per a que
	els usuaris tinguin una via de comunicació amb el fundador
	i/o operadors del canal. Si no es proporciona una
	direcció de correu, s'esborrarà la que actualment pogui
	tenir el canal.

CHAN_HELP_SET_ENTRYMSG
	Sintaxis: 12SET <canal> ENTRYMSG [missatge]
	
	Estbleix el missatge que serà enviat als usuaris (via
	/notice) quan ells ingressin al canal. Si mensaje no
	s'ingressa, res serà enviat als usuaris quan ingressin.

CHAN_HELP_SET_TOPIC
	Sintaxis: 12SET <canal> TOPIC <text>
	
	Fa que 4%S fixi el tema del canal al indicat en
	12text. Aquesta ordre és molt útil en conjunció amb
	12SET TOPICLOCK.

CHAN_HELP_SET_KEEPTOPIC
	Sintaxis: 12SET <canal> KEEPTOPIC {ON | OFF}
	
	Habilita o deshabilita la opció de 12retenció del tema per a
	el canal. Quan 12retenció del tema està en ON
	(habilitada), el tema del canal serà recordat per 4%S
	encara desprès que l'últim usuari s'hagi retirat, i es
	restauri el pròxim cop que algú ingressi al canal.

CHAN_HELP_SET_TOPICLOCK
	Sintaxis: 12SET <canal> TOPICLOCK {ON | OFF}
	
	Habilita o deshabilita la opció per a protegir el tópic del
	canal. Quan 12protegir el tópic està en ON, 4%S no
	habilitarà el canvi del tema (tópic) excepte via 12SET
	TOPIC.

CHAN_HELP_SET_MLOCK
	Sintaxis: 12SET <canal> MLOCK <modes>
	
	Fixa els distints modes per al canal. 4%S l'habilita a
	vosté per a definir determinats modes del canal i que quedin
	sempre habilitats (o no). Els modes que poden ser
	fixats són: i, k, l, m, n, p, s, i t; cada
	un d'aquests modes pot estar activat (ON), desactivat
	(OFF) o no fixat. Els distints modes s'indiquen
	exactament com si s'utilitzès la comanda 12/MODE; això és,
	mode seguit de + indica activat (ON), mode seguit de -
	indica desactivat (OFF).
	
	4Vigili!:  Si vosté fixa un mode protegit per clau d'accès
	com en el segon exemple , també deura fixar la opció
	12RESTRICTED per al canal (vea 12HELP SET RESTRICTED), o
	qualsevol que ingressi al canal quan el mateix estigui buit
	veurà la clau d'accès!!
	
	Exemples:
	
	    12SET #canal MLOCK +nt-iklps
	       Activa els modes n, i t, i desactiva els modes i, k,
	       l, p, i s. El mode m pot ser activat o desactivat.
	
	    12SET #canal MLOCK +knst-ilmp my-key
	       Activa els modes k, n, s, i t.
	       Desactiva els modes i, l, m, i p.
	       També estableix "my-key" com a clau d'accès al canal.
	
	    12SET #canal MLOCK +
	       Esborra totls els modes actius; tots els modes del canal
	       poden ser llibrement activats o desactivatspueden ser libremente activados o desactivados.

CHAN_HELP_SET_PRIVATE
	Sintaxis: 12SET <canal> PRIVATE {ON | OFF}
	
	Habilita o deshabilita l'opció de 12privat per al canal.
	Quan aquesta opció està activada, la comanda 12/msg %S LIST no
	inclourà el canal en cap llista.

CHAN_HELP_SET_RESTRICTED
	Sintaxis: 12SET <canal> RESTRICTED {ON | OFF}
	
	Habilita o deshabilita l'opció d'12accès restringit per al
	canal. Quan l'accès restringit està actiu (ON),
	usuaris que normalment no tenen privilegi d'operadors
	quan entren al canal (usuaris amb nivell d'accès
	negatiu i, si 12secure ops està activat usuaris que NO
	estan a la llista d'accès) seran expulsats (i se'ls
	prohibirà l'accès) al canal.

CHAN_HELP_SET_SECURE
	Sintaxis: 12SET <canal> SECURE {ON | OFF}
	
	Habilita o deshabilita la seguretat de 4%S per al
	canal. Quan 12SECURE està 12ACTIU, SOLS els usuaris que
	tenen registrats els seus nicks amb 4%s i s'han
	IDENTIFICAT amb les seves respectives claus tindran accès
	al canal si es que figuren a la llsita d'12ACCESS.

CHAN_HELP_SET_SECUREOPS
	Sintaxis: 12SET <canal> SECUREOPS {ON | OFF}
	
	Habilita o deshabilita l'opció d'12operadors segurs per al
	canal. Quan operadore segurs està activat (ON),
	usuaris que 12NO estiguin a la llista d'usuaris del canal NO
	podran obtenir status d'operadors

CHAN_HELP_SET_LEAVEOPS
	Syntax: 12SET <canal> LEAVEOPS {ON | OFF}
	
	Habilita o deshabilita l'opció de 12leave ops per al
	canal. Quan 12leave ops està activat (ON),
	12%S no deixarà deopejar a usuaris del canal
	excepte amb la comanda 12DEOP.

CHAN_HELP_SET_OPNOTICE
	Syntax: 12SET <canal> ISSUED {ON | OFF}
	
	Habilita o deshabilita l'opció de 12issued per al
	canal. Quan 12issued està activat (ON),
	12%S enviarà un notice al canal quan els usuaris usin les
	comandes al canal.

CHAN_HELP_ACCESS
	Sintaxis: 12ACCESS <canal> ADD <nick> <nivell>
	          12ACCESS <canal> DEL {nick | posició-nombre, list}
	          12ACCESS <canal> LIST [mascara]
	
	Manté la 12llista d'accessos del canal. La llista d'accessos
	estableix que usuaris estan habilitats a ser operadors
	del canal o accedir a comedes de 12%S al canal. Es poden
	establir diferents nivells d'usuaris per a accedir a
	diferents privilegis; utilitzi 12/msg %S HELP ACCESS LEVELS
	per a obtenir informació més específica. Qualsevol nick que
	no estigui a la llista d'accès té nivell d'usuari 0
	(zero).
	
	La comanda 12ACCESS ADD introdueix al 12nick amb el 12nivell donat a la
	llista d'accès; si l'usuari ja existeix a la llista, es
	modificarà el seu 12nivell. El 12nivell especificat deu ser menor
	que el que té l'usuari que està ingressant la comanda,
	i si el 12nick està actualment a la llista, el nivell actual
	de dit nick deu ser menor que el nivell de l'usuari que
	està ingressant la comanda.
	
	La comanda 12ACCESS DEL esborra un usuari de la llista
	d'accessos. Es pot esborrar un usuari ingressant el nick o
	ingressant el nombre que ocupa a la llista d'accessos.
	
	La comanda 12ACCESS LIST mostra la llista d'accessos al canal;
	es poden utilitzar caracters comodins o màscares, en qual
	cas sols les coincidències concurrents seran llistades.

CHAN_HELP_ACCESS_LEVELS
	12Nivells d'accès per a usuaris
	
	Per defecte, els següents nivells són definits:
	
	   12Founder   Accès FULL a les funcions de 4%S.
	                 Privilegi d'operador al ingressar al canal.
	                 Noti que únicament una sola persona pot
	                 tenir accès de fundador del canal (no es
	                 pot donar accès al founder amb la comanda
	                 ACCESS).
	   12    499   Accès a les comandes SET, OPDEOP, INVITE, UNBAN, AKICK, ACC, MEMO;
	                 operador automàtic al ingressar.
	   12    450   Accès a les comandes OPDEOP, INVITE, UNBAN, AKICK, ACC, MEMO;
	                 operador automàtic al ingressar.
	   12    300   Accès a les comandes OPDEOP, INVITE, UNBAN,
	                 operador automàtic al ingressar.
	   12    100   Estat de VEU automàtic (+v).
	   12      0   No té privilegis especials; pot obtenir
	                 status d'operador donat per un altre operador
	                 (a menys que secure-ops estigui activat).
	   12     <0   No pot ser operador, ni entrar al canal.
	
	Aquests nivells poden ser canviats, o nous poden ser
	introduïts utilitzant la comanda 12LEVELS; escrigui
	12/msg %S HELP LEVELS per a més informació.

CHAN_HELP_AKICK
	Sintaxis: 12AKICK <canal> ADD <mascara> [raó]
	          12AKICK <canal> DEL <mascara>
	          12AKICK <canal> LIST [mascara]
	          12AKICK <canal> ENFORCE
	
	Definim AKICK como "Expulsió automàtica".
	Definim BAN como "Entrada prohibida".
	
	Aquesta comanda, manté la llista d'AKICK del canal. Si un
	usuari està a la llista d'AKICK i intenta entrar al canal,
	4%S aitomàticament introdueix a dit usuari a la llista BAN
	del canal, i desprès l'expulsa del canal.
	
	La comanda 12AKICK ADD introdueix un usuari a la llista d'AKICK.
	Si una 12raó és donada amb la comanda, aleshores la raó serà
	utilitzada per 4%S quan expulsi a dit usuari; si
	no, el missatge que s'utilitzarà per defecte, és "Has estat
	banejat del canal".
	
	La comanda 12AKICK DEL esborra a l'usuari de la llista d'AKICK.
	Aquesta comanda no remou el BAN que pogui existir al
	canal, el qual deurà ser remogut manualment.
	
	La comanda 12AKICK LIST ens mostra la llista d'usuaris a la
	llista d'AKICK. Opcionalment, sols llista aquells
	subministrats amb la màscara donada.
	
	La comanda 12AKICK ENFORCE causa que 4%S impideixi que els
	usuaris borrin màscares d'AKICK a la llista d'AKICK.

CHAN_HELP_LEVELS
	Sintaxis: 12LEVELS <canal> SET <tipus> <nivell>
	          12LEVELS <canal> {DIS | DISABLE} <tipus>
	          12LEVELS <canal> LIST
	          12LEVELS <canal> RESET
	
	La comanda 12LEVELS permet un control fi sobre els accessos
	numèrics utilitzats pels canals. Amb aquesta comanda,
	vosté pot definir els nivells requerits per moltes de
	les funcions de 4%S. Les comandes 12SET FOUNDER,
	12SET PASSWORD, així com aquesta comanda estan sempre
	registringides al fundador.
	
	12LEVELS SET habilita l'accès per a una funció o grup de
	funcions a ser modificades.
	
	12LEVELS DISABLE (o 12DIS en forma abreujada) deshabilita un
	privilegi automàtic, o deshabilita l'accès per a
	qualsevol altre que no sigui el fundador del canal.
	
	12LEVELS LIST mostra els nivells actuals per a cada funció o
	grup de funcions.
	
	12LEVELS RESET torna tots els nivells als seus valor per
	defecte, els mateixos que quan es registrar per primer cop
	un canal (vegi 12HELP ACCESS LEVELS).
	
	Per a una llista de les funcions que poden ser establertes,
	utilitzi la comanda 12HELP LEVELS DESC.

CHAN_HELP_LEVELS_DESC
	La següent llista mostra els valors/funcions per
	defecte. Noti que els nivells per a AUTODEOP i NOJOIN són
	els nivells màxims, mentres que tots els demès, són els
	mínims.

CHAN_HELP_LEVELS_DESC_FORMAT
	    %-*s  %s

CHAN_HELP_INFO
	Sintaxis: 12INFO <canal> [ALL]
	
	Proveeix informació aprop del 12canal (o informa que no està
	registrat). Llista el fundador, hora i data de
	registre, última vegada que es va usar, descripció, i
	modes del canal (si hi ha). Si estàs identificat com a
	fundador del canal, pots utilitzar el paràmetre 12ALL, per a
	veure el successor i el missatge d'entrada del canal.

CHAN_HELP_LIST
	Sintaxis: 12LIST <especificació>
	
	Llista tots els canals que coincideixin amb l'especificació
	donada. Canals amb l'opció PRIVATE activada, no són
	llistats.

CHAN_HELP_OP
	Sintaxis: 12OP <canal> <nick>
	
	Fa Operador a l'usuari indicat en el canal
	indicat. Per defecte, està limitat als qui posseeixen nivell
	300 o major en el canal.

CHAN_HELP_DEOP
	Sintaxis: 12DEOP <canal> <nick>
	
	Treu l'estat d'Operador a l'usuari indicat en el canal
	indicat. Per defecte, està limitat als qui posseeixen nivell
	300 o major en el canal.

CHAN_HELP_INVITE
	Sintaxis: 12INVITE <canal>
	
	Li diu a 4%S que l'inviti a vosté al canal indicat.
	Per defecte, sols funciona si el seu nivell d'accès en dit
	canal és 300 o major.

CHAN_HELP_UNBAN
	Sintaxis: 12UNBAN <canal>
	
	Li diu a 4%S que esborri tots els accessos prohibits
	prevenint el seu ingrès a dit canal. Per defecte, sols
	funciona si el seu nivell d'accès a dit canal és 300 o més.

CHAN_HELP_CLEAR
	Sintaxis: 12CLEAR <canal> <opció>
	
	Li diu a 4%S que esborri certs paràmetres del canal.
	que pot ser un dels següents:

	     12MODES   Reseteja tots els modes del canal (exemple,
	                 neteja els modes i,k,l,m,n,p,s,t).
	     12BANS    Esborra tots els accessos prohibits al canal.
	     12OPS     Esborra (treu) el privilegi d'operador a
	                 tots els operdors (mode +o) del canal.
	     12VOICES  Esborra (treu) el privilegi de "veu" (mode
	                 +v) a qualsevol del canal que el tingués.
	     12USERS   Esborra (Pateja -kicks-) TOTS els usuaris del
	                 canal.
	
	Per defecte, el seu nivell d'accès en el canal deu ser al
	menys 499 per a utilitzar aquesta comanda.

CHAN_SERVADMIN_HELP
	
	Les següents comandes estan disponibles per als
	4Administradors dels Serveis:

	    12GETPASS    Torna la clau d'accès del fundador
	    12SUSPEND
	    12UNSUSPEND
	    12FORBID     Prevé que un canal pogui ser utilitzat
	    12UNFORBID
	    12STATUS     Torna el nivell d'accès actual d'un
	               usuari en un canal
	
	Els 4Administradors de Serveis també poden esborrar
	qualsevol canal sense necessitat d'identificar-se via
	clau, i poden veure la llista d'accessos, la llista
	d'AKICK, i llistar els valors de nivell (LEVELS) de qualsevol
	canal.

CHAN_SERVADMIN_HELP_DROP
	Sintaxis: 12DROP <canal>
	
	Elimina un canal de la llista de 4%S. Únicament
	4Administradors de Serveis poden esborrar un canal per
	lo qual ells no necessiten identificar-se.

CHAN_SERVADMIN_HELP_SET
	
	Administradors de Services també poden definir l'opció
	12NOEXPIRE, amb la qual algún canal es pot prevenir que
	expiri. Adicionalment, els Administradors de Services
	poden definir opcions per a qualsevol canal sense necessitat
	d'identificar-se amb clau per a aquest canal.

CHAN_SERVADMIN_HELP_SET_NOEXPIRE
	Sintaxis: 12SET <canal> NOEXPIRE {ON | OFF}
	
	Defineix si el canal donat expirarà. Si es defineix 12ON prevé
	que el canal expiri.

	Limitat a 4Administradors de Services.

CHAN_SERVADMIN_HELP_LIST
	Sintaxis: 12LIST <especificació>
	
	Llista tots els canals que concideixen amb l'especificació
	donada. Els canals amb l'opció PRIVATE  activada sols seran
	mostrats als 4Administradors de Serveis.

CHAN_SERVADMIN_HELP_GETPASS
	Sintaxis: 12GETPASS <canal>
	
	Torna la clau d'accès del canal donat.
	4Noti que quan aquesta comanda és utilitzada, un missatge
	incloïnt la persona que l'ha utilitzat i el canal sobre el
	qual l'utilitzà, serà grabat en un arxiu de registre, i
	serà enviat com a missatge (WALLOPS/GLOBOPS).
	
	Limitat a 4Administradors de Serveis.

CHAN_SERVADMIN_HELP_FORBID
	Sintaxis: 12FORBID <canal>
	
	Deshabilita a qualsevol per a utilitzar o registrar el canal
	donat. Pot ser cancel·lat eliminant el canal (dropping).
	
	Limitat a 4Administradors de Serveis.

CHAN_SERVADMIN_HELP_STATUS
	Sintaxis: 12STATUS <canal> <nick>
	
	Torna el nivell d'accès actual del nick donat en el canal
	donat. La resposta és de la forma:
	
	    12STATUS canal nick nivell-d'accès
	
	Limitat a 4Administradors de Serveis.

###########################################################################
#
# MemoServ help messages (Mensajes de ayuda de MemoServ)
#
###########################################################################

MEMO_HELP
	4%S és una utilitat que permet a usuaris de l'IRC
	enviar missatges curts a altres usuaris de l'IRC
	independentment de si estan en linea o no, igualment es
	poden enviar missatges a canals(*). Ambdós nicks (remitent
	i destinatari) deuen estar registrats, així mateix el
	canal deu d'estar registrat si es dessitja enviar un missatge
	a aquest.
	
	Comandes de 4%S inclouen:
	
	    12SEND   Envia un missatge a un nick/canal
	    12LIST   Llista tots els teus missatges
	    12READ   Llegeix un missatge
	    12DEL    Esborra un missatge (o tots)
	    12SET    Defineix opcions relacionades amb missatges
	
	Escrigui 12/msg %S HELP comanda per a ajuda més específica
	de les comandes amunt mencionades.
	
	(*) Per defecte, qualsevol usuari amb al menys nivell 450
	    d'accès en un canal pot llegir els missatges del canal.
	    Això pot ser canviat amb la comanda 12%s LEVELS.
MEMO_HELP_SEND
	Sintaxis: 12SEND <nick> <memo-text>
	
	Envia un memo a l'usuari especificat. Dit usuari
	rebrà una noticia de que té un nou memo. El
	rebrà inmeditament si es troba en linea, o si no al
	moment d'identificar-se la pròxima vegada que es conecti.k
	
	Exemple: /msg %S SEND joselito Molt bó el teu treball de traducció! ;)

MEMO_HELP_LIST
	Sintaxis: 12LIST [NEW]
	
	Llista els memos que vosté tingui actualment.
	Si s'indica el paràmetre 12NEW, sols els nous memos (els no
	llegits) seran mostrats. Els memos no llegits estan marcats
	amb un "*" a l'esquerra del nombre de memo.

MEMO_HELP_READ
	Sintaxis: 12READ {nombre | LAST}
	
	Mostra el contingut del memo indicant en nombre, o
	l'últim memo (per exemple, el rebut més recentment) si el
	paràmetre 12LAST es donat EN COMPTES DE 12nombre.

MEMO_HELP_DEL
	Sintaxis: 12DEL {nombre[-nombre][,nombre...] | ALL}
	
	Si un nombre 12num és donat, s'esborra dit memo. Vosté pot
	reemplaçar un únic nombre per un interval de nombres per a
	eliminar múltiples memos simultàneament, tal com es veurà
	en el segon exemple.
	
	Si s'ingressa 12ALL s'esborraran TOTS els memos.
	
	Exemples:
	
	   12DEL 1
	      Esborra el seu primer memo.
	
	   12DEL 2-5,7-9
	      Esborrar els memos 2 a 5 i 7 a 9.

MEMO_HELP_SET
	Sintaxis: 12SET <opció> <paràmetres>
	
	Estableix varies opcions per als memos. Les opcions
	poden ser:
	
	    12NOTIFY      Estableix QUAN deu ser notificat de
	                    nous memos
	    12LIMIT       Estableix el MÀXIM nombre de memos que
	                    vosté pot rebre
	
	Escrigio 12/msg %S HELP SET opció per a obtenir més
	informació aprop de l'opció específica.

MEMO_HELP_SET_NOTIFY
	Sintaxis: 12SET NOTIFY {ON | LOGON | NEW | OFF}
	
	Estableix QUAN deu ser notificat de nous memos:
	
	    12ON      Serà notificat quan es conecti, quan tregui
	                el seu mode /AWAY i quan un memo li sigui
	                enviat estant vosté conectat.
	    12LOGON   Serà notificat únicament quan es conecti,
			i quan quiti el seu mode /AWAY
	    12NEW     Serà notificat solament quan li siguin
	                enviats.
	    12OFF     Vosté no rebrà cap tipus de notificació de
	                memos.
	
	12ON és bàsicament la combinació de 12LOGON i 12NEW
	simultàneament.

MEMO_HELP_SET_LIMIT
	Sintaxis: 12SET LIMIT [canal] <limit>
	
	Estableix el màxim nombre de memos que vosté està
	habilitat a tenir. Si estableix 12limit a 0 (zero) ningú
	podrà enviar-li memos a vosté. De tots maneres, vosté no pot
	establir 12limit més alt que 12%d.

MEMO_HELP_INFO
	Sintaxis: 12INFO [canal]
	
	Mostra informació de la quantitat de memos que vosté té,
	quants d'ells no han estat llegits, i la quantitat de memos
	que vosté pot rebre

MEMO_SERVADMIN_HELP_SET_LIMIT
	Sintaxis: 12SET LIMIT [usuari] {limit | NONE} [HARD]
	
	Estableix el màxim nombre de memos que un usuari pot
	tenir. Establint el 12limit a 0 (zero), prevé que
	dit 12usuari pogui rebre memos; establint a 12NONE,
	habilita a l'12usuari a rebre i mantenir tants memos com
	desitji. Si vosté no ESPECIFICA usuari EL SEU propi límit
	él el que s'estableix.
	
	Sumant-hi el paràmetre 12HARD, preveu que l'usuari pogui
	canviar dit límit. No agregant 12HARD té l'efecte
	oposat, habilitant a l'usuari a canviar el límit (encara si
	previament havia estat establert amb el paràmetre HARD).
	
	L'ús de la comanda 12SET LIMIT està limitada als
	4Administradors de Serveis. Altres usuaris sols poden
	establir els seus propis limits, no poden remoure els seus
	limits, no poden establir límits superiors a 12%d, i no
	poden establir el límit 12HARD.

MEMO_SERVADMIN_HELP_INFO
	Sintaxis: 12INFO [usuari]
	
	Sense paràmetres, mostra informació del nombre de memos que
	tu tens, quants estan sense llegir, i quants memos pots
	rebre.
	
	Amb el paràmetre 12usuari, mostra la mateixa informació, pero
	de l'12usuari especificat. Aquesta opció està limitada
	únicament als 4Administradors de Serveis.

###########################################################################
#
# OperServ help messages (mensajes de ayuda de OperServ)
###########################################################################

OPER_HELP
	Comandes de 4%S:
	
	    12GLOBAL      Envia un missatge a TOTS els usuaris
	    12STATS       Mostra l'estat dels serveis i de la xarxa
	    12OPER LIST   Llista tots els Operadors de Serveis
	    12ADMIN LIST  Llista tots els Administradors de Serveis
	
	Comandes disponibles solament per a Operadors de Serveis i
	administradors:
	    12MODE        Canvia els modes d'un canal
	    12KICK        Pateja a un usuari d'un canal
	    12AKILL       Manipula la llista d'AKILL
	
	Comandes disponibles solament per als Administradors de
	Serveis:
	    12OPER        Modifica la llista d'Operadors de Serveis
	    12JUPE        "Jupiter" un servidor
	    12RAW         envia un code RAW al servidor IRC
	    12SET         Estableix varies opcions globals dels
	                    serveis
	    12UPDATE      Força a la base de dades dels Serveis a
			    ser actualitzada inmediatament al disc
	    12QUIT        Dona per finalitzada l'execució del programa
	                    de Serveis
	    12RESTART     Grava la base de dades i reinicia els
	                    Serveis
	
	Comandes disponibles únicament per als súper-usuaris dels
	serveis:
	    12ADMIN       Modifica la llista d'Administradors de Serveis
	
	4Avís: TOTES les comandes enviades a 4%S són
	registrades! (log)

OPER_HELP_GLOBAL
	Sintaxis: 12GLOBAL <missatge>
	
	Habilita als IRCops a enviar un 12missatge a tots els
	usuaris a la xarxa. El missatge pot ser enviat per a 4%s.

OPER_HELP_STATS
	Sintaxis: 12STATS [AKILL | ALL]
	
	Sense opcions, mostra la qantitat d'usuaris e IRCops en
	línea, el més alt nombre d'usuaris en linea des que els
	serveis es van posar en funcionament, i des de quan
	estan funcionant els serveis.
	
	Amb el paràmetre 12AKILL mostra la longitut de la llista de
	AKILL i la data actual d'expiració.
	
	El paràmetre 12ALL sols està disponible per als
	4Administradors de Serveis i mostra l'ús de memoria dels
	Serveis. Utilitzant aquesta opció pot congelar els
	Serveis per un breu periode de temps en grans xarxes,
	per tant no abusi d'ella.
	
	12UPTIME pot ser utilizat com a sinònim de 12STATS.

OPER_HELP_OPER
	Sintaxis: 12OPER ADD <nick>
	          12OPER DEL <nick>
	          12OPER LIST
	
	Habilita als 4Administradors de Serveis per a introduïr
	(ADD), esborrar (DEL) o llistar (LIST) usuaris de la llista
	d'operadors. Un usuari que es trobi a la llista
	d'operadors i que s'identifiqui a 4%s podrà accedir
	a les comandes d'Operador de Serveis.
	
	Qualsevol dels operadors de IRC (IRCops) pot utilitzar
	la comanda 12OPER LIST. Totes les altres comandes sols poden
	ser utilitzades pels 4Administradors de Serveis.

OPER_HELP_ADMIN
	Sintaxis: 12ADMIN ADD <nick>
	          12ADMIN DEL <nick>
	          12ADMIN LIST
	
	Habilita als 4Super-usuaris dels Serveis per a introduïr
	(ADD), esborrar (DEL) o llistar (LIST) usuaris de la llista
	d'administradors. Un usuari que es trobi a la llista
	d'operadors i que s'identifiqui a 4%s podrà accedir
	a les comandes d'Administrador de Serveis.
	
	Qualsevol dels operadors de IRC (IRCops) pot utilitzar
	la comanda 12OPER LIST. Totes les altres comandes sols poden
	ser utilitzades pels 4Super-usuaris de Serveis.

OPER_HELP_MODE
	Sintaxis: 12MODE <canal> <modes>
	
	Habilita als operadors de Serveis a establir els
	modes per a qualsevol canal. Els paràmetres són els mateixos
	que s'utilitzen a la forma estandar de /MODE
	
	Sols disponible per als 4Operadors de Serveis.

OPER_HELP_CLEARMODES
	Sintaxis: 12CLEARMODES <canal> [ALL]
	
	Elimina els BAN i els modes d'un canal (i,k,l,m,n,p,s,t).
	Si el paràmetre 12ALL és donat, també treu els modes
	Operador i veu a qui hagi al canal (modes +o i +v).
	
	Sols disponible per als 4Operadors de Serveis.

OPER_HELP_KICK
	Sintaxis: 12KICK <canal> <usuari> <raó>
		
	Habilita a un IRCop a treure un usuari de qualsevol canal.
	Els paràmetres són els mateixos que per a un /KICK común. El
	missatge de kick mostrarà a l'usuari el nombre de l'IRCop que
	està enviant la comanda. Per exemple:
		
	3*** Lammer ha estat kickeajat del canal #mi_canal per %S (ZoLtan (Insults))
	
	Sols disponible per als 4Operadors de Serveis.

OPER_HELP_AKILL
	Sintaxis: 12AKILL ADD [+expiració] <mascara> <raó>
	          12AKILL DEL <mascara>
	          12AKILL LIST [mascara]
	          12AKILL VIEW [mascara]
	
	Habilita als IRCops a manipular la llista d'12AKILL. Si un
	usuari que figura en dita llista, intenta conectar-se, els
	Serveis bloquejaràn la seva conexió i donaràn instruccions a
	tots els servidors que el soportin, que introdueixin un ban
	(k-line) per a la màscara que coincideixi amb la de l'usuari.
	
	12AKILL ADD introdueix a l'usuari donat (amb la mascara
	usuari@host) a la llista d'akill per la raó donada (que
	deu ser donada).
	
	12AKILL DEL treu l'usuari donat de la llista d'12AKILL si el
	mateix està present.
	
	12AKILL LIST mostra tots els usuaris que estan actualment
	a la llista. Si una màscara és donada, el llistat estarà
	limitat a les ocurrencies.
	
	12AKILL VIEW és més explícit que 12AKILL LIST, donat que mostra
	qui va agregar el 12AKILL, la data en que fou posat, quan
	expira, la mascara utilitza i la raó.
	
	Opcionalment, un temps d'expiració pot ser
	suministrat amb la comanda 12AKILL ADD. El temps de
	expiració PRECEDEIX a la mascara usuari@host i és
	especificat com un sencer (això és, sense decimals) seguit
	de: d per a especificar dies, h (hores), o m (minuts).
	Combinacions (como 1h30m) no són permeses. Si un
	espicificador d'unitats no és inclòs, per defecte
	s'asumeixen DIES (aleshores, posar +30 sense res, significa 30
	dies). Per a introduir un 12AKILL que NO expira, utilitzi +0.  Si
	la máscara d'usuari comença amb +, un periode
	d'expiració deurà ser indicat, encara si és el mateix periode
	que l'asignat per defecte. El temps d'expiració per
	defecete, es pot veure utilitzant la comanda STATS AKILL.
	
	La 12raó està indicada per a ús dels IRCops, i NO serà
	mostrada a l'usuari quan s'efectui el KILL.
	
	Sols disponible per als 4Operadors de Serveis.

OPER_HELP_JUPE
	Sintaxis: 12JUPE <server>
	
	Instrueix als Serveis a crear un servidor satèlit. Això
	és, per a simular un "servidor" que estigui conectat als
	Serveis els quals prevenen la conexió del servidor real
	amb aquest nom. Aquesta simulació pot ser remoguda,
	utilizant un 12SQUIT estándar.

	Sols disponible per als 4Administradors de Serveis.

OPER_HELP_RAW
	Sintaxis: 12RAW <text>
	
	Envia una cadena de caracters directament al servidor al
	qual estan conectats els Serveis.
	Aquesta ordre té un interval molt limitat d'usos, i pot
	cusar danys en una red si s'utilitza incorrectament.
	4NO USI AQUESTA COMANDA a menys que vosté estigui completament
	segur del que fa!

	Sols disponible per als 4Administradors de Serveis.

OPER_HELP_SET
	Sintaxis: 12SET <opció> <mode>
	
	Estableix varies de les opcions globals dels Serveis.
	Els noms de les opcions actualment definides són:
	    12READONLY   Estableix el mode de "sols-llegir" o
	                   "llegir-escriure"
	    12DEBUG      Activa o desactiva el mode depuració
	
	Sols disponible per als 4Administradors de Serveis.

OPER_HELP_SET_READONLY
	Sintaxis: 12SET READONLY {ON | OFF}
	
	Activa o desactiva el mode "sols-llegir". Si el mode
	"sols-llegir" està activat, els usuaris que tenen accès
	no estaran habilitats a modificar les dades dels
	Serveis, incloïnt-hi llistes de canals, nicks, etc. IRCops
	amb suficients privilegis sobre els serveis, podran
	modificiar la llista d'12AKILL, així com eliminar (DROP) un
	canal o un nick, però cap dels canvis seran gravats
	a menys que el mode "sols-llegir" es desactivi desprès que
	finalitzin els serveis, o siguin restaurats.
	
	Aquesta opció és equivalent a la opció 12-readonly de la
	linea de comandes.

OPER_HELP_SET_DEBUG
	Sintaxis: 12SET DEBUG {ON | OFF | nombre}
	
	Activa o desactiva el mode depuració. En mode depuració,
	totes les dades enviades i rebudes així com els missatges
	de depuració, són gravats en un arxiu de registre (log).
	Si nombre és donat, el mode de depuració es activat, amb
	nivell de depuració establert a 12nombre.
	
	Aquesta opció es equivalent a la opció 12-debug de la
	linea de comandes.

OPER_HELP_UPDATE
	Sintaxis: 12UPDATE
	
	Causa que els Serveis actualitzin les bases de dades tan
	mateix com vostè envïi la comanda.
	
	Limitat a 4Administradors de Serveis.

OPER_HELP_QUIT
	Sintaxis: 12QUIT
	
	Causa la desactivació dels Serveis; les bases de dades
	4NO es graven. Aquesta comanda no deu utilitzar-se a menys
	es sospiti d'un mal a les bases de dades en memoria i no
	desitjin gravar-se. Per a desactivació normal dels
	Serveusm utilitzi la comanda 12SHUTDOWN.
	
	Limitat a 4Administradors de Serveis.

OPER_HELP_SHUTDOWN
	Sintaxis: 12SHUTDOWN
	
	Causa que els serveis gravin totes les bases de dades i
	desprès es desactivin.
	
	Limitat a 4Administradors de Serveis.

OPER_HELP_RESTART
	Sintaxis: 12RESTART
	
	Causa que Services gravi totes les bases de dades i
	reinicïi (exemple: terminar i executar inmediatament el
	programa).
	
	Limitat a 4Administradors de Serveis.



OPER_HELP_KILLCLONES
	Syntax: 12KILLCLONES <nick>
	
	Kills all users who have the same hostname as 12nick. A
	temporary AKILL, in the form 12*@host, is added to
	prevent the offending clients from immediately
	reconnecting. A wallops is also sent indicating who
	used the command, which host was affected and how many
	users were killed. It's usefull for removing numerous
	clones from the network.
	
	Limitat a 4Administradors de Serveis.

OPER_HELP_ROTATELOG
	Syntax: 12ROTATELOG
	
	Renames service's log file. The current date, in the form
	YYYYMMDD, is used to generate the new filename.
	
	Limitat a 4Super-usuaris de Serveis.


# EXCEPTION help

OPER_HELP_EXCEPTION
	        12EXCEPTION DEL {mascara | list}
	        12EXCEPTION MOVE <numero> <posicion>
	        12EXCEPTION LIST [mascara | list]
	        12EXCEPTION VIEW [mascara | list]
	
	Allows Services admins to manipulate the list of hosts that
	have specific session limits - allowing certain machines,
	such as shell servers, to carry more than the default number
	of clients at a time. Once a host reaches it's session limit,
	all clients attempting to connect from that host will be
	killed. Before the user is killed, they are notified, via a
	/NOTICE from OperServ, of a source of help regarding session
	limiting. The content of this notice is a config setting.
	
	12EXCEPTION ADD adds the given host mask to the exception list.
	Note that 12nick!user@host and 12user@host masks are invalid!
	Only real host masks, such as 12box.host.dom and 12*.host.dom,
	are allowed because sessions limiting does not take nick or
	user names into account. 12limite must be a number greater than
	or equal to zero. This determines how many sessions this host
	may carry at a time. A value of zero means the host has an
	unlimited session limit. See the 12AKILL help for details about
	the format of the optional 12expiracion parameter.
	
	12EXCEPTION DEL removes the given mask from the exception list.
	
	12EXCEPTION MOVE moves exception 12numero to 12posicion. The
	exceptions inbetween will be shifted up or down to fill the gap.
	
	12EXCEPTION LIST and 12EXCEPTION VIEW show all current
	exceptions; if the optional mask is given, the list is limited
	to those exceptions matching the mask. The difference is that
	12EXCEPTION VIEW is more verbose, displaying the name of the
	person who added the exception, it's session limit, reason,
	host mask and the expiry date and time.
	
	Note that a connecting client will "use" the first exception
	their host matches. Large exception lists and widely matching
	exception masks are likely to degrade services' performance
	
	Limitat a 4Administradors de Serveis.

OPER_HELP_SESSION
	Syntax: 12SESSION LIST <threshold>
	        12SESSION VIEW <host>
	
	Allows Services admins to view the session list.
	
	12SESSION LIST lists hosts with atleast 12threshold sessions.
	The threshold must be a number greater than 1. This is to
	prevent accidental listing of the large number of single
	session hosts.
	
	12SESSION VIEW displays detailed information about a specific
	host - including the current session count and session limit.
	The 12host value may not include wildcards.
	
	See the 12EXCEPTION help for more information about session
	limiting and how to set session limits specific to certain
	hosts and groups thereof.
	
	Limitat a 4Administradors de Serveis.
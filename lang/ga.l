# Archivo de idioma Galego.
#
# Services esta protexido por dereitos de autor (c) 1996-1999 Andy Church.
#     E-mail: <achurch@dragonfire.net>
# Este programa é gratis pero está rexistrado; vexa o arquivo COPYING para
# detalles.
# Traducción por:
# # Toni Gacía Nunhez "ZoLtan" zolty@ctv.es

# Cando traduzas este arquivo a outra lingua, ten en mente que a orde
# dos parámetros para sprintf() é fica no código fonte, así que as túas
# mensaxes necesitarán toma-los mesmos parámetros na mesma orde como
# se fai no inglés. (Obviamete, isto non se sostén para o formato das
# liñas strftime() de máis abaixo.) Se non podes dar una traducción natural
# dunha mensaxe sen cambiar a orde dos parámetros, faime saber 
# (achurch@dragonfire.net) que mensaxe causa o problema e verei que podo facer.
#
# Nas mensaxes de axuda, "%S" (S maiúscula, non minúscula) refírese ó nome
# do servicio que envía a mensaxe; por exemplo, nas mensaxes de axuda de NickServ
# "%S" é reemplazado por "NickServ" (ou doutro xeito é renombrado a iso no config.h)
# Os %Ss non contan como os parámetros sprintf(), así que poderán ser quitados, 
# engadidos ou reordenados se é necesario

###########################################################################
#
# GALEGO
#
###########################################################################

# For languages other than English, this string should have the following
# format:
#     language-name-in-language (language-name-in-English)
# For example, "Español (Spanish)" or "Français (French)".

LANG_NAME
	Galego (Galicia)

###########################################################################
#
# Mensaxes Xerais
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
	%H:%M:%S %d %b %Y %Z
# This is used as the format string for strftime() for a date and time
# format (English: including weekday).
STRFTIME_LONG_DATE_FORMAT
	%a %d %b %Y
STRFTIME_SHORT_DATE_FORMAT
# This is used as the format string for strftime() for a date alone in
# short format (English: without weekday).
	%d %b %Y

# These tell our strftime() what the names of months and days are.  If you
# don't use %a, %A, %b, or %B in your strftime() strings above, you can
# leave these empty.  However, if you enter names, they MUST stay in order,
# one per line, and the list MUST be complete!

# %a
STRFTIME_DAYS_SHORT
	Dom
	Lun
	Mar
	Mer
	Xov
	Ven
	Sab
# %A
STRFTIME_DAYS_LONG
	Domingo
	Luns
	Martes
	Mércores
	Xoves
	Venres
	Sábado
# %b
STRFTIME_MONTHS_SHORT
	Xan
	Feb
	Mar
	Abr
	Mai
	Xun
	Xul
	Ago
	Set
	Out
	Nov
	Dec
# %B
STRFTIME_MONTHS_LONG
	Xaneiro
	Febreiro
	Marzo
	Abril
	Maio
	Juño
	Jullo
	Agosto
	Setembro
	Outubro
	Novembro
	Decembro


# This is used in ChanServ/NickServ INFO displays.
COMMA_SPACE
	,


# Various error messages.
USER_RECORD_NOT_FOUND
	Error Interno - imposible procesar comando.
UNKNOWN_COMMAND
	Comando descoñecido 12%s.
UNKNOWN_COMMAND_HELP
	Comando descoñecido 12%s. Teclea 12/msg %s HELP para obter información.
SYNTAX_ERROR
	Sintaxe: 12%s
MORE_INFO
	Teclea 12/msg %s HELP %s para máis información.
NO_HELP_AVAILABLE
	Non hai axuda disponible sobre 12%s.

BAD_USERHOST_MASK
	A máscara debe estar no formato 12usuario@host.

BAD_EXPIRY_TIME
	Tiempo de expiración inválido.

SERVICE_OFFLINE
	12%s está actualmente fóra de servicio.
READ_ONLY_MODE
	4Noticia: Services está en modo de ler soamente; ¡Os cambios non serán grabados!
ACCESS_DENIED
	4Acceso denegado.
PERMISSION_DENIED
	4Permiso denegado.
PASSWORD_INCORRECT
	4Contrasinal incorrecta.

MORE_OBSCURE_PASSWORD
	Por favor inténtao con un contrasinal máis . Os contrasinais han de ter ó menos 4 5 caracteres, non deben ser algo fácil de descifrar (Ex: 12o seu nome real ou o seu Nick), tampouco debe conter espacios.
PASSWORD_TRUNCATED
	4Atencion: O seu contrasinal foi limitada a 12%d caracteres.

NICK_NOT_REGISTERED
	O teu nick non está rexistrado.
NICK_NOT_REGISTERED_HELP
	O teu nick non está rexistrado. Escribe 12/msg %s HELP para obter información de cómo rexistra-lo teu nick.
NICK_X_NOT_REGISTERED
	O Nick 12%s non está rexistrado.
NICK_X_NOT_IN_USE
	O Nick 12%s non está en uso neste momento.
NICK_X_FORBIDDEN
	O Nick 12%s non pode ser rexistrado ou utilizado.
CHAN_X_NOT_REGISTERED
	O Canal 12%s non está rexistrado.
CHAN_X_NOT_IN_USE
	O Canal 12%s non existe.
CHAN_X_FORBIDDEN
	O Canal 12%s non pode ser rexistrado o utilizado.
NICK_IDENTIFY_REQUIRED
	Precisas autentificarte antes de usar este comando.
	Téntao despois de escribir 12/IDENTIFY contrasinal.
CHAN_IDENTIFY_REQUIRED
	Precisas autentificarte antes de usar este comando.
	Téntao despois de escribir 12/IDENTIFY %s contrasinal.

###########################################################################
# mensaxes de Nickserv
#
###########################################################################

# Automatic messages
NICK_IS_REGISTERED
	Este nick pertence a outra persoa. Por favor escolle outro. 
	(Se este é o teu nick, escribe 12/IDENTIFY contrasinal.)
NICK_IS_SECURE
	Este nick está rexistrado e protexido.
	Se é o teu nick, escribe 12/IDENTIFY contrasinal.
	Doutro xeito, escolle un nick diferente.
NICK_MAY_NOT_BE_USED
	Este nick non se pode utilizar. Por favor escolle outro.
DISCONNECT_IN_1_MINUTE
	4Se non cambias antes dun minutiño, serás desconectado.
DISCONNECT_IN_20_SECONDS
	4Si non cambia-lo teu nick antes de 20 segundos, serás desconectado.
DISCONNECT_NOW
	Este nick foi rexistrado; non podes usalo. Por favor
	escolle outro nick antes de reconectar.
FORCENICKCHANGE_IN_1_MINUTE
	4Se non cambias antes dun minutiño, serás cambiado tu nick.
FORCENICKCHANGE_IN_20_SECONDS
	4Si non cambia-lo teu nick antes de 20 segundos, será cambiado tu nick.
FORCENICKCHANGE_NOW
	Este nick foi rexistrado; non podes usalo.
	O teu nick ha sido cambiado a 12%s.


# REGISTER responses
NICK_REGISTER_SYNTAX
	12REGISTER <oteu-enderezo@email.es>
NICK_REGISTRATION_DISABLED
	Síntoo, o rexistro de nicks está temporalmente deshabilitado.
NICK_REGISTRATION_FAILED
	Síntoo, o rexistro fallou.
NICK_REG_PLEASE_WAIT
	Por favor, agarda 12%d segundos antes de volver utiliza-lo comando 12REGISTER.
NICK_CANNOT_BE_REGISTERED
	O Nick 12%s non pode ser rexistrado.
NICK_ALREADY_REGISTERED
	¡O Nick 12%s xa esta rexistrado!
NICK_REGISTERED
	O Nick 12%s está rexistrado baixo a conta: 12%s
NICK_PASSWORD_IS
	O teu contrasinal é 12%s,lémbraa para o seu uso posterior.

# IDENTIFY responses
NICK_IDENTIFY_SYNTAX
	12IDENTIFY <contrasinal>
NICK_IDENTIFY_FAILED
	4Contrasinal Incorrecta.
NICK_IDENTIFY_SUCCEEDED
	3Contrasinal aceptada, Benvid@ á casiña ;)

# DROP responses
NICK_DROP_SYNTAX
	12DROP
NICK_DROP_DISABLED
	Síntoo, a eliminación de niks está temporalmente deshabilitada.
NICK_DROPPED
	O seu nick foi cancelado.
NICK_X_DROPPED
	O nick 12%s foi cancelado.

# SET responses
NICK_SET_SYNTAX
	12SET <opción> <paramétros>
NICK_SET_SERVADMIN_SYNTAX
	12SET [nick] <opción> <paramétros>
NICK_SET_DISABLED
	Síntoo, a configuración de opcións de nick está temporalmente deshabilitada.
NICK_SET_UNKNOWN_OPTION
	4Opción SET 12%s descoñecida.
NICK_SET_UNKNOWN_OPTION_OR_BAD_NICK
	4Opción SET 12%s descoñecida, ou o seu nick non está rexistrado.

# SET PASSWORD responses
NICK_SET_PASSWORD_FAILED
	4Síntoo, o contrasinal non se poido cambiar.
NICK_SET_PASSWORD_CHANGED
	Contrasinal cambiado.
NICK_SET_PASSWORD_CHANGED_TO
	Contrasinal cambiado a 12%s.

# SET URL responses
NICK_SET_URL_CHANGED
	URL cambiada a 12%s.
NICK_SET_URL_UNSET
	URL deshabilitada.

# SET EMAIL responses
NICK_SET_EMAIL_CHANGED
	Enderezo E-mail cambiado a 12%s.
NICK_SET_EMAIL_UNSET
	Enderezo E-mail deshabilitado.

# SET LANGUAGE responses
NICK_SET_LANGUAGE_SYNTAX
	12SET LANGUAGE <nùmero>
NICK_SET_LANGUAGE_UNKNOWN
	Número 12%d de idioma descoñecido. Escribe 12/msg %s HELP SET LANGUAGE para obte-la lista de idiomas disponibles.
NICK_SET_LANGUAGE_CHANGED
	Idioma cambiado a 12Galego.

# SET KILL responses
NICK_SET_KILL_SYNTAX
	12SET KILL {ON | QUICK | OFF}
NICK_SET_KILL_IMMED_SYNTAX
	12SET KILL {ON | QUICK | IMMED | OFF}
NICK_SET_KILL_ON
	Protección de KILL 12activada.
NICK_SET_KILL_QUICK
	Protección de KILL 12activada, con unha espera reducida.
NICK_SET_KILL_IMMED
	Protección de KILL 12activada, sen espera.
NICK_SET_KILL_IMMED_DISABLED
	A opción 12IMMED non está disponible nesta rede.
NICK_SET_KILL_OFF
	Protección de KILL 12desactivada.

# SET SECURE responses
NICK_SET_SECURE_SYNTAX
	12SET SECURE {ON | OFF}
NICK_SET_SECURE_ON
	Opción SECURE 12activada.
NICK_SET_SECURE_OFF
	Opción SECURE 12desactivada.

# SET PRIVATE reponses
NICK_SET_PRIVATE_SYNTAX
	12SET PRIVATE {ON | OFF}
NICK_SET_PRIVATE_ON
	Opción PRIVATE 12activada.
NICK_SET_PRIVATE_OFF
	Opción PRIVATE 12desactivada.

# SET HIDE responses
NICK_SET_HIDE_SYNTAX
	12SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
NICK_SET_HIDE_EMAIL_ON
	O teu enderezo E-mail non será amosado nun 12%s INFO.
NICK_SET_HIDE_EMAIL_OFF
	O teu enderezo E-mail será visible nun 12%s INFO.
NICK_SET_HIDE_MASK_ON
	A túa última máscara non será amosada nun 12%s INFO.
NICK_SET_HIDE_MASK_OFF
	A túa última máscara será visible nun 12%s INFO.
NICK_SET_HIDE_QUIT_ON
	O teu último QUIT non será amosado nun 12%s INFO.
NICK_SET_HIDE_QUIT_OFF
	O teu último QUIT será amosado nun12%s INFO.

# SET NOEXPIRE responses
NICK_SET_NOEXPIRE_SYNTAX
	12SET [nick] NOEXPIRE {ON | OFF}
NICK_SET_NOEXPIRE_ON
	O Nick 12%s NON expirará.
NICK_SET_NOEXPIRE_OFF
	O Nick 12%s SI expirará.

# ACCESS responses
NICK_ACCESS_SYNTAX
	12ACCESS {ADD | DEL | LIST} [màscara]
NICK_ACCESS_ALREADY_PRESENT
	A máscara 12%s xa está na túa lista de máscaras.
NICK_ACCESS_REACHED_LIMIT
	Só podes ter 12%s máscaras de acceso por nick.
NICK_ACCESS_ADDED
	12%s engadida á túa lista de máscaras.
NICK_ACCESS_NOT_FOUND
	12%s non está na túa lista de máscaras.
NICK_ACCESS_DELETED
	12%s borrada da túa lista de máscaras.
NICK_ACCESS_LIST
	Lista de máscaras:
NICK_ACCESS_LIST_X
	Lista de máscaras de 12%s:

# LINK responses
NICK_LINK_SYNTAX
	12LINK <nick> <password>
NICK_LINK_DISABLED
	O comando 12LINK non está disponible.
NICK_LINK_FAILED
	Síntoo, o link fallou.
NICK_NO_LINK_SAME
	¡Non podes linka-lo teu nick ó actual!
NICK_LINK_CIRCULAR
	É imposible linkarse 12%s: Link circular detectado.
NICK_LINKED
	O teu nick foi linkado a 12%s.

# UNLINK responses
NICK_UNLINK_SYNTAX
	12UNLINK [nick password]
NICK_UNLINK_FAILED
	Síntoo, o deslink fallou.
NICK_NOT_LINKED
	O teu nick non está linkado.
NICK_UNLINKED
	O teu nick foi deslinkado de 12%s.
NICK_X_NOT_LINKED
	O nick 12%s non está linkado.
NICK_X_UNLINKED
	O nick 12%s foi deslinkado 12%s.

# LISTLINKS responses
NICK_LISTLINKS_SYNTAX
	12LISTLINKS <nick> [ALL]
NICK_LISTLINKS_HEADER
	Lista de nicks linkados a 12%s:
NICK_LISTLINKS_FOOTER
	12%d nicks linkados.

# INFO responses
NICK_INFO_SYNTAX
	12INFO nick [ALL]

NICK_INFO_REALNAME
	Realname de %s é 12%s
NICK_INFO_ADDRESS
	Último enderezo: 12%s
NICK_INFO_ADDRESS_ONLINE
	Esta on-line desde: 12%s
NICK_INFO_ADDRESS_ONLINE_NOHOST
	Esta on-line, máis información escribe 12/WHOIS %s
NICK_INFO_TIME_REGGED
	Hora de rexistro: 12%s
NICK_INFO_LAST_SEEN
	Última hora que se veu: 12%s
NICK_INFO_LAST_QUIT
	Último mensaxe de saída: 12%s
NICK_INFO_URL
	URL: 12%s
NICK_INFO_EMAIL
	E-mail: 12%s
NICK_INFO_OPTIONS
	Opcións: %s
# These strings MUST NOT be empty
NICK_INFO_OPT_KILL
	12Protección de KILL
NICK_INFO_OPT_SECURE
	12Seguro
NICK_INFO_OPT_PRIVATE
	12Privado
NICK_INFO_OPT_NONE
	12Ningunha
NICK_INFO_NO_EXPIRE
	Expiración do nick: 4NON12 expirará.

# LIST responses
NICK_LIST_SYNTAX
	12LIST <patrón>
NICK_LIST_SERVADMIN_SYNTAX
	12LIST <patrón> [FORBID] [NOEXPIRE] [SUSPEND]
NICK_LIST_HEADER
	Lista de entradas que satisfán 12%s:
NICK_LIST_RESULTS
	Fin de lista - 12%d/12%d entradas amosadas.

# RECOVER responses
NICK_RECOVER_SYNTAX
	12RECOVER <nick> [contrasinal]
NICK_NO_RECOVER_SELF
	¡Non podes recupera-lo teu propio nick!
NICK_RECOVERED
	O usuario co seu nick foi desconectado.
	Teclea 12/msg %s RELEASE %s contrasinal para liberalo.

# RELEASE responses
NICK_RELEASE_SYNTAX
	12RELEASE <nick> [contrasinal]
NICK_RELEASE_NOT_HELD
	O nick 12%s non está sendo protexido neste momento.
NICK_RELEASED
	A protección Services no seu nick foi liberada.

# GHOST responses
NICK_GHOST_SYNTAX
	12GHOST <nick> [contrasinal]
NICK_NO_GHOST_SELF
	¡Non podes ghostearte a ti mesmo!
NICK_GHOST_KILLED
	Invisible co seu nick foi desconectado.

# GETPASS responses
NICK_GETPASS_SYNTAX
	12GETPASS <nick>
NICK_GETPASS_UNAVAILABLE
	Comando GETPASS non disponible cando encriptación está en uso.
NICK_GETPASS_PASSWORD_IS
	O contrasinal de 12%s é 12%s

# FORBID responses
NICK_FORBID_SYNTAX
	12FORBID <nick>
NICK_FORBID_SUCCEEDED
	Nick 12%s FORBIDeado.
NICK_FORBID_FAILED
	Non podes FORBIDea-lo nick 12%s

###########################################################################
#
# mensaxes de ChanServ
#
###########################################################################

# Access level descriptions
CHAN_LEVEL_AUTOOP
	Status de operador de canal automático
CHAN_LEVEL_AUTOVOICE
	Modo +v automático
CHAN_LEVEL_AUTODEOP
	Non pode ser operador de canal
CHAN_LEVEL_NOJOIN
	Non pode entrar a canal se está en modo restrinxido (RESTRICTED)
CHAN_LEVEL_INVITE
	Permitido a usa-lo comando INVITE
CHAN_LEVEL_AKICK
	Permitido a usa-lo comando AKICK
CHAN_LEVEL_SET
	Permitido a usa-lo comando SET (non sendo FUNDADOR)
CHAN_LEVEL_CLEAR
	Permitido a usa-lo comando CLEAR
CHAN_LEVEL_UNBAN
	Permitido a usa-lo comando UNBAN
CHAN_LEVEL_OPDEOP
	Permitido a usa-los comandos OP/DEOP
CHAN_LEVEL_ACCESS_LIST
	Permitido a ve-la lista de acceso
CHAN_LEVEL_ACCESS_CHANGE
	Permitido a modifica-la lista de acceso
CHAN_LEVEL_MEMO
	Permitido a ve-las mensaxes do canal
#CHAN_LEVEL_RESET
#	Usuario con privilexios de resetea-lo canal canal.

# Automatic responses
CHAN_IS_REGISTERED
	Este canal está rexistrado con 12%s
CHAN_NOT_ALLOWED_OP
	Non podes ser operador do canal 12%s.
CHAN_MAY_NOT_BE_USED
	Este canal non pode ser utilizado.
CHAN_NOT_ALLOWED_TO_JOIN
	Non podes permanecer neste canal.

# REGISTER responses
CHAN_REGISTER_SYNTAX
	12REGISTER <canal> <contrasinal> <descripción>
CHAN_REGISTER_DISABLED
	Síntoo, o rexistro de canal está temporalmente desactivado.
CHAN_REGISTER_NOT_LOCAL
	Canales locais non poden ser rexistrados.
CHAN_MUST_REGISTER_NICK
	Debes registrar primeiro o teu nick. Escribe 12/msg %s HELP para obter información de como rexistra-lo tu nick.
CHAN_MUST_IDENTIFY_NICK
	Por favor identifíquese primeiro con 12%s, utilizando o comando:
	12/msg %s IDENTIFY contrasinal
CHAN_MAY_NOT_BE_REGISTERED
	O canal 12%s non pode ser rexistrado.
CHAN_ALREADY_REGISTERED
	¡O canal 12%s xa está rexistrado!
CHAN_MUST_BE_CHANOP
	Debes ser operador de canal (@) para poder rexistrarlo.
CHAN_REACHED_CHANNEL_LIMIT
	Síntoo, xa acadache-lo límite de 12%d canais.
CHAN_EXCEEDED_CHANNEL_LIMIT
	Síntoo, xa excediche-lo límite de 12%d canais.
CHAN_REGISTRATION_FAILED
	Síntoo, o rexistro fallou.
CHAN_REGISTERED
	O conal 12%s está rexistrado baixo teu nick: 12%s
CHAN_PASSWORD_IS
	O contrasinal do canal é 12%s, lémbraa para o seu uso posterior.

# IDENTIFY responses
CHAN_IDENTIFY_SYNTAX
	12IDENTIFY <canal> <contrasinal>
CHAN_IDENTIFY_FAILED
	Síntoo, a identificación fallou.
CHAN_IDENTIFY_SUCCEEDED
	Contrasinal aceptado, Agora es recoñecido con nivel de fundador de 12%s.

# DROP responses
CHAN_DROP_SYNTAX
	12DROP <canal>
CHAN_DROP_DISABLED
	Síntoo, a cancelación de rexistro de canal está temporalmente deshabilitada.
CHAN_DROPPED
	O Canal 12%s foi cancelado.

# SET responses
CHAN_SET_SYNTAX
	12SET <canal> <opción> <paramétros>
CHAN_SET_DISABLED
	Síntoo, o axuste de opcións do canal está temporalmente deshabilitado.
CHAN_SET_UNKNOWN_OPTION
	4Opción SET 12%s descoñecida.

# SET FOUNDER responses
CHAN_SET_FOUNDER_TOO_MANY_CHANS
	12%s ten demasiados canais rexistrados.
CHAN_FOUNDER_CHANGED
	Fundador de 12%s cambiado a 12%s.

# SET SUCCESSOR responses
CHAN_SUCCESSOR_CHANGED
	Sucesor de 12%s cambiado a 12%s.
CHAN_SUCCESSOR_UNSET
	Sucesor para 12%s 12desactivada.


# SET PASSWORD responses
CHAN_SET_PASSWORD_FAILED
	Síntoo, non se puido cambiar contrasinal.
CHAN_PASSWORD_CHANGED
	12%s contrasinal cambiado.
CHAN_PASSWORD_CHANGED_TO
	12%s contrasinal cambiado a 12%s.

# SET DESC responses
CHAN_DESC_CHANGED
	Descrición de 12%s cambiada a 12%s.

# SET URL responses
CHAN_URL_CHANGED
	URL de 12%s cambiada a 12%s.
CHAN_URL_UNSET
	URL de 12%s desactivada.

# SET EMAIL responses
CHAN_EMAIL_CHANGED
	Enderezo E-mail de 12%s cambiado a 12%s.
CHAN_EMAIL_UNSET
	Enderezo E-mail de 12%s desactivada.

# SET ENTRYMSG responses
CHAN_ENTRY_MSG_CHANGED
	Mensaxe de entrada de 12%s cambiada.
CHAN_ENTRY_MSG_UNSET
	Mensaxe de entrada de 12%s desactivada.

# SET TOPIC responses
CHAN_SET_TOPIC_FAILED
	Síntoo, non foi posible poñe-lo topic.

# SET MLOCK responses
CHAN_SET_MLOCK_KEY_REQUIRED
	Parámetro requerido para MLOCK +k.
CHAN_SET_MLOCK_LIMIT_REQUIRED
	Parámetro requerido para MLOCK +l.
CHAN_SET_MLOCK_LIMIT_POSITIVE
	Parámetro para MLOCK +l debe ser un número positivo.
CHAN_SET_MLOCK_UNKNOWN_CHAR
	Modo 12%c é descoñecido e ignorado.
CHAN_MLOCK_CHANGED
	Candado de modo do canal 12%s cambiado a 12%s.
CHAN_MLOCK_REMOVED
	Candado de modo de canal 12%s quitado.

# SET KEEPTOPIC responses
CHAN_SET_KEEPTOPIC_SYNTAX
	12SET <canal> KEEPTOPIC {ON | OFF}
CHAN_SET_KEEPTOPIC_ON
	Retención de topic 12activada.
CHAN_SET_KEEPTOPIC_OFF
	Retención de topic 12desactivada.

# SET TOPICLOCK responses
CHAN_SET_TOPICLOCK_SYNTAX
	12SET <canal> TOPICLOCK {ON | OFF}
CHAN_SET_TOPICLOCK_ON
	Opción de candado de topic 12activada.
CHAN_SET_TOPICLOCK_OFF
	Opción de candado de topic 12desactivada.

# SET PRIVATE responses
CHAN_SET_PRIVATE_SYNTAX
	12SET <canal> PRIVATE {ON | OFF}
CHAN_SET_PRIVATE_ON
	Opción de privacidade 12activada.
CHAN_SET_PRIVATE_OFF
	Opción de privacidade 12desactivada.

# SET SECUREOPS responses
CHAN_SET_SECUREOPS_SYNTAX
	12SET <canal> SECUREOPS {ON | OFF}
CHAN_SET_SECUREOPS_ON
	Opción Secure ops 12activada.
CHAN_SET_SECUREOPS_OFF
	Opción Secure ops 12desactivada.

# SET LEAVEOPS responses
CHAN_SET_LEAVEOPS_SYNTAX
	12SET <canal> LEAVEOPS {ON | OFF}
CHAN_SET_LEAVEOPS_ON
	Opción de Leave ops 12activada.
CHAN_SET_LEAVEOPS_OFF
	Opción de Leave ops 12desactivada.

# SET RESTRICTED responses
CHAN_SET_RESTRICTED_SYNTAX
	12SET <canal> RESTRICTED {ON | OFF}
CHAN_SET_RESTRICTED_ON
	Opción de acceso restrinxido 12activada.
CHAN_SET_RESTRICTED_OFF
	Opción de acceso restrinxido 12desactivada.

# SET SECURE responses
CHAN_SET_SECURE_SYNTAX
	12SET <canal> SECURE {ON | OFF}
CHAN_SET_SECURE_ON
	Opción Secure 12activada.
CHAN_SET_SECURE_OFF
	Opción Secure 12desactivada.


# SET OPNOTICE responses
CHAN_SET_OPNOTICE_SYNTAX
	12SET <canal> ISSUED {ON | OFF}
CHAN_SET_OPNOTICE_ON
	Opción Issued 12activado.
CHAN_SET_OPNOTICE_OFF
	Opción Issued 12desactivado.

# SET NOEXPIRE responses
CHAN_SET_NOEXPIRE_SYNTAX
	12SET <canal> NOEXPIRE {ON | OFF}
CHAN_SET_NOEXPIRE_ON
	O Canal 12%s NON expirará.
CHAN_SET_NOEXPIRE_OFF
	O Canal 12%s SI expirará.

# ACCESS messages
CHAN_ACCESS_SYNTAX
	12ACCESS <canal> {ADD|DEL|LIST} [nick [nivel] | entrada-lista]
CHAN_ACCESS_DISABLED
	Síntoo, a modificación da lista de acceso de canal esta temporalmente deshabilitada.
CHAN_ACCESS_LEVEL_NONZERO
	O Nivel de acceso debe ser diferente de cero.
CHAN_ACCESS_LEVEL_RANGE
	O Nivel de acceso debe estar entre 12%d y 12%d.
CHAN_ACCESS_NICKS_ONLY
	A lista de acceso do canal só debe conter nicks rexistrados.
CHAN_ACCESS_REACHED_LIMIT
	Só podes ter 12%s personas rexistradas no canal.
CHAN_ACCESS_LEVEL_UNCHANGED
	O Nivel de acceso de 12%s en 12%s non cambiou de 12%d.
CHAN_ACCESS_LEVEL_CHANGED
	Nivel de acceso para 12%s en 12%s cambiado a 12%d.
CHAN_ACCESS_ADDED
	12%s engadid@ á lista de acceso de 12%s con nivel 12%d.
CHAN_ACCESS_NO_SUCH_ENTRY
	Entrada descoñecida (12#%d) na lista de acceso de 12%s.
CHAN_ACCESS_NOT_FOUND
	12%s non foi atopad@ na lista de acceso de 12%s.
CHAN_ACCESS_NO_MATCH
	Non se atoparon entradas na lista de acceso de 12%s.
CHAN_ACCESS_DELETED
	12%s borrad@ da lista de acceso de 12%s.
CHAN_ACCESS_DELETED_ONE
	Borrada12 1 entrada da lista de acceso de 12%s.
CHAN_ACCESS_DELETED_SEVERAL
	Borradas 12%s entradas da lista de acceso de 12%s.
CHAN_ACCESS_LIST_EMPTY
	A lista de acceso do canal 12%s está valeira.
CHAN_ACCESS_LIST_HEADER
	Lista de acceso de 12%s:
	  Núm   Niv  Nick
CHAN_ACCESS_LIST_FORMAT
	  %3d  %4d  %s%s%s%s

# AOP/SOP error response
CHAN_NO_AOP_SOP
	Para asignar privilegios del canal a usuarios, usa el comando 12ACCESS
	Escribe 12/msg %s HELP ACCESS para más información.


# AKICK responses
CHAN_AKICK_SYNTAX
	12AKICK <canal> {ADD | DEL | LIST | ENFORCE} [nick or máscara]
CHAN_AKICK_DISABLED
	Síntoo, a modificación de lista de autokicks do canal está temporalmente deshabilitada.
CHAN_AKICK_ALREADY_EXISTS
	12%s xa está na lista de AKICK's do canal 12%s.
CHAN_AKICK_REACHED_LIMIT
	Síntoo, só podes ter 12%d máscaras de AKICK's por canal.
CHAN_AKICK_ADDED
	12%s engadid@ á lista de autokick de 12%s.
CHAN_AKICK_NO_SUCH_ENTRY
	Entrada descoñecida (12#%d) na lista de AKICK's de 12%s.
CHAN_AKICK_NOT_FOUND
	12%s non está na lista AKICK's de 12%s.
CHAN_AKICK_DELETED
	12%s borrad@ da lista de AKICK's do canal 12%s.
CHAN_AKICK_DELETED_ONE
	Borrada12 1 entrada da lista de AKICK's do canal 12%s.
CHAN_AKICK_DELETED_SEVERAL
	Borradas 12%s entradas da lista de AKICK's do canal 12%s.
CHAN_AKICK_NO_MATCH
	Non se encuentra entradas en la lista de AKICK's do canal 12%s.
CHAN_AKICK_LIST_HEADER
	Lista de AKICK's de 12%s:
CHAN_AKICK_LIST_FORMAT
	  %3d %s%s
CHAN_AKICK_LIST_EMPTY
	A lista de AKICK's do canal 12%s está valeira.
CHAN_AKICK_ENFORCE_DONE
	12AKICK ENFORCE para 12%s completado; 12%d usuarios son afectados

# LEVELS responses
CHAN_LEVELS_SYNTAX
	12LEVELS <canal> {SET | DIS[ABLE] | LIST | RESET} [item [level]]
CHAN_LEVELS_RANGE
	O Nivel ha estar entre 12%d y 12%d.
CHAN_LEVELS_CHANGED
	Nivel de 12%s no canal 12%s cambiado a %d.
CHAN_LEVELS_UNKNOWN
	Opción 12%s descoñecida.  Escribe 12/msg %s HELP LEVELS DESC para unha lista de opcións validas.
CHAN_LEVELS_DISABLED
	12%s deshabilitado do 12%s.
CHAN_LEVELS_LIST_HEADER
	Configuración de niveis de acceso do canal 12%s:
CHAN_LEVELS_LIST_DISABLED
	    %-*s  (deshabilitado)
CHAN_LEVELS_LIST_FOUNDER
	    %-*s  (fundador soamente)
CHAN_LEVELS_LIST_NORMAL
	    %-*s  %d
CHAN_LEVELS_RESET
	Niveis de acceso de 12%s configurados a niveles orixinais.

# INFO responses
CHAN_INFO_SYNTAX
	12INFO <canal> [ALL]
CHAN_INFO_HEADER
	Información do canal 12%s:
CHAN_INFO_FOUNDER
	Fundador: 12%s (%s)
CHAN_INFO_NO_FOUNDER
	Fundador: 12%s
CHAN_INFO_SUCCESSOR
	Sucesor: 12%s (12%s)
CHAN_INFO_NO_SUCCESSOR
	Sucesor: 12%s
CHAN_INFO_DESCRIPTION
	Descripción: 12%s
CHAN_INFO_ENTRYMSG
	Mensaxe de entrada: 12%s
CHAN_INFO_TIME_REGGED
	Rexistrado: 12%s
CHAN_INFO_LAST_USED
	Último uso: 12%s
CHAN_INFO_LAST_TOPIC
	Último topic: 12%s
CHAN_INFO_TOPIC_SET_BY
	Topic axustado por: 12%s
CHAN_INFO_URL
	URL: 12%s
CHAN_INFO_EMAIL
	E-mail: 12%s
CHAN_INFO_OPTIONS
	Opcións: %s
CHAN_INFO_OPT_PRIVATE
	12Privado
CHAN_INFO_OPT_KEEPTOPIC
	12Retención de topic
CHAN_INFO_OPT_TOPICLOCK
	12Candado de topic
CHAN_INFO_OPT_SECUREOPS
	12Secure Ops
CHAN_INFO_OPT_LEAVEOPS
	12Leave Ops
CHAN_INFO_OPT_RESTRICTED
	12Acceso restrinxido
CHAN_INFO_OPT_SECURE
	12Seguro
CHAN_INFO_OPT_NONE
	12Ningunha
CHAN_INFO_MODE_LOCK
	Candado de modo: 12%s
CHAN_INFO_NO_EXPIRE
	Expiración do canal: 4NON12 expirará.

# LIST responses
CHAN_LIST_SYNTAX
	12LIST <patron>
CHAN_LIST_HEADER
	Lista de entradas que satisfán 12%s:
CHAN_LIST_FORMAT
	    %-20s  %s
CHAN_LIST_END
	Fin da lista - 12%d/12%d entradas amosadas.

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
	Fuches desbaneado de 12%s.

# CLEAR responses
CHAN_CLEAR_SYNTAX
	12CLEAR <canal> <opcion>
CHAN_CLEARED_BANS
	Tódolos bans do canal 12%s foron borrados.
CHAN_CLEARED_MODES
	Tódolos modos do canal 12%s foron borrados.
CHAN_CLEARED_OPS
	Tódolos usuarios do canal 12%s foron DEOPeados.
CHAN_CLEARED_VOICES
	Tódolos usuarios do canal 12%s foron DEVOICEados.
CHAN_CLEARED_USERS
	Tódolos usuarios do canal 12%s foron kikeados.

# GETPASS responses
CHAN_GETPASS_SYNTAX
	12GETPASS <canal>
CHAN_GETPASS_UNAVAILABLE
	Comando GETPASS non está disponible cando encriptación está en uso.
CHAN_GETPASS_PASSWORD_IS
	O contrasinal do canal 12%s é 12%s.

# FORBID responses
CHAN_FORBID_SYNTAX
	12FORBID <canal>
CHAN_FORBID_SUCCEEDED
	O canal 12%s foi FORBIDeado.
CHAN_FORBID_FAILED
	O canal 12%s non pode ser FORBIDeado.

###########################################################################
#
# mensaxes de MemoServ
#
###########################################################################

# Automatic messages
MEMO_HAVE_NEW_MEMO
	3Ouuuu! Tés 1 mensaxe nova.
MEMO_HAVE_NEW_MEMOS
	3Ouuuu! tés 12%d 3mensaxes novas.
MEMO_TYPE_READ_LAST
	Escribe 12/msg %s READ LAST para lela.
MEMO_TYPE_READ_NUM
	Escribe 12/msg %s READ %d para ler esa mensaxe.
MEMO_TYPE_LIST_NEW
	Escribe 12/msg %s LIST NEW para lista-las mensaxes novas.
MEMO_AT_LIMIT
	4Atención: Chegaches ó máximo número de mensaxes (12%d). Non poderás recibir mensaxes novas ata que borres algunha das mensaxes que tés.
MEMO_OVER_LIMIT
	4Atención: Chegaches ó máximo número de mensaxes (12%d). Non poderás recibir mensaxes novas ata que borres algunha das mensaxes que tés.
MEMO_NEW_MEMO_ARRIVED
	3Ouuuu! tés unha mensaxe nova de 12%s.
	Escribe 12/msg %s READ %d para lela.

# Multi-use responses
MEMO_HAVE_NO_MEMOS
	Non tés mensaxes.
MEMO_X_HAS_NO_MEMOS
	12%s non ten mensaxes.
MEMO_DOES_NOT_EXIST
	¡A mensaxe 12%d non existe!
MEMO_LIST_NOT_FOUND
	Non foi encontrado memos.

# SEND responses
MEMO_SEND_SYNTAX
	12SEND {nick | canal} <texto>
MEMO_SEND_DISABLED
	Síntoo, o envío de mensaxes está temporalmente deshabilitado.
MEMO_SEND_PLEASE_WAIT
	Agarda 4%d segundiños antes de utiliza-lo comando SEND outra vez.
MEMO_X_GETS_NO_MEMOS
	12%s non pode recibir mensaxes.
MEMO_X_HAS_TOO_MANY_MEMOS
	12%s ten demasiadas mensaxes e non pode recibir máis.
MEMO_SENT
	Mensaxe enviada a 12%s.

# LIST responses
MEMO_LIST_SYNTAX
	12LIST [canal] [list | NEW]
MEMO_HAVE_NO_NEW_MEMOS
	Non tés mensaxes novas.
MEMO_X_HAS_NO_NEW_MEMOS
	12%s non ten mensaxes novas.
MEMO_LIST_MEMOS
	Mensaxes para 12%s. Para lela, escribe: 12/msg %s READ número
MEMO_LIST_NEW_MEMOS
	Novas mensaxes para 12%s.  Para ler, escribe: 12/msg %s READ número
MEMO_LIST_CHAN_MEMOS
	Mensaxe para 12%s.  Para ler, escribe: 12/msg %s READ %s número
MEMO_LIST_CHAN_NEW_MEMOS
	Novas mensaxes para 12%s.  Para ler, escribe: 12/msg %s READ %s número
MEMO_LIST_HEADER
	 Núm  Remitente         Día/Hora
MEMO_LIST_FORMAT
	%c%3d  %-16s  %s

# READ responses
MEMO_READ_SYNTAX
	12READ [canal] {list | LAST | NEW}
MEMO_HEADER
	Mensaxe 12%d de 12%s (12%s). Para borrala, escribe: 12/msg %s DEL %d
MEMO_CHAN_HEADER
	Mensaxe 12%d de 12%s (12%s). Para borrala, escribe: 12/msg %s DEL %s %d
MEMO_TEXT
	12%s

# DEL responses
MEMO_DEL_SYNTAX
	12DEL [canal] {numero | list | ALL}
MEMO_DELETED_NONE
	Ningunha mensaxe foi borrada.
MEMO_DELETED_ONE
	A Mensaxe 12%d foi borrada.
MEMO_DELETED_SEVERAL
	12%s mensaxes foron borrados.
MEMO_DELETED_ALL
	Tódalas túas mensaxes foron borradas.

# SET responses
MEMO_SET_SYNTAX
	12SET <opcion> <parametros>
MEMO_SET_DISABLED
	Síntoo, a opción de axuste de mensaxes está temporalmente deshabilitada.
MEMO_SET_UNKNOWN_OPTION
	Opción 12SET 12%s descoñecida.

# SET NOTIFY responses
MEMO_SET_NOTIFY_SYNTAX
	12SET NOTIFY {ON | LOGON | NEW | OFF}
MEMO_SET_NOTIFY_ON
	12%s notificaráche as túas mensaxes cando te conectes ou cando che sexan enviadas.
MEMO_SET_NOTIFY_LOGON
	12%s notificaráche as túas mensaxes cando te conectes cou cancele-lo teu modo /AWAY.
MEMO_SET_NOTIFY_NEW
	12%s notificaráche as túas mensaxes cando che sexan enviadas.
MEMO_SET_NOTIFY_OFF
	12%s non che notificará as túas mensaxes.

# SET LIMIT responses
MEMO_SET_LIMIT_SYNTAX
	12SET LIMIT [canal_] <limite>
MEMO_SET_LIMIT_SERVADMIN_SYNTAX
	12SET LIMIT [ nick | canal] {limite | NONE} [HARD]
MEMO_SET_YOUR_LIMIT_FORBIDDEN
	Non podes cambia-lo límite das mensaxes.
MEMO_SET_LIMIT_FORBIDDEN
	O límite de mensaxes para 12%s non pode ser cambiado.
MEMO_SET_YOUR_LIMIT_TOO_HIGH
	Ti non podes axusta-lo teu límite de mensaxes maior a 12%d.
MEMO_SET_LIMIT_TOO_HIGH
	Ti non podes axusta-lo límite de mensaxes para 12%s máis alto que 12%d.
MEMO_SET_LIMIT_OVERFLOW
	Límite de mensaxes moi alto; limitando a 12%d.
MEMO_SET_YOUR_LIMIT
	O teu límite de mensaxe foi axustado a 12%d.
MEMO_SET_YOUR_LIMIT_ZERO
	Ti non poderás recibir mensaxes.
MEMO_SET_LIMIT
	Limite de mensaxes para 12%s axustado a 12%d.
MEMO_SET_LIMIT_ZERO
	Límite de mensaxes para 12%s axustado a12 0.
MEMO_UNSET_YOUR_LIMIT
	O teu límite de mensaxes foi deshabilitado.
MEMO_UNSET_LIMIT
	Límite de mensaxes desactivado para 12%s.

# INFO responses
MEMO_INFO_SYNTAX
	12INFO [canal]
MEMO_INFO_SERVADMIN_SYNTAX
	12INFO [nick | canal]
MEMO_INFO_NO_MEMOS
	Non tés mensaxes.
MEMO_INFO_MEMO
	Tés12 1 mensaxe.
MEMO_INFO_MEMO_UNREAD
	Tés12 1 mensaxe, e non o liches.
MEMO_INFO_MEMOS
	Tés 12%d mensaxes.
MEMO_INFO_MEMOS_ONE_UNREAD
	Tés 12%d mensaxes, das que12 1 non foron lidos.
MEMO_INFO_MEMOS_SOME_UNREAD
	Tés 12%d mensaxes, das que %d non foron lidos.
MEMO_INFO_MEMOS_ALL_UNREAD
	Tés 12%d mensaxes, das que ningún foi lido.
MEMO_INFO_LIMIT
	O teu límite de mensaxes é 12%d.
MEMO_INFO_HARD_LIMIT
	O teu límite de mensaxes é 12%d, e non pode ser cambiado.
MEMO_INFO_LIMIT_ZERO
	O teu límite de mensaxes é12 0; non recibirás ningunha nova mensaxe.
MEMO_INFO_HARD_LIMIT_ZERO
	O teu límite de mensaxes é12 0; non recibirás ningunha nova mensaxe. Non podes cambiar este límite.
MEMO_INFO_NO_LIMIT
	Non tés límite na cantidade de mensaxes que podes gardar.
MEMO_INFO_X_NO_MEMOS
	12%s non ten mensaxes.
MEMO_INFO_X_MEMO
	12%s ten actualmente12 1 mensaxe.
MEMO_INFO_X_MEMO_UNREAD
	12%s ten actualmente12 1 mensaxe, e non foi lido aínda.
MEMO_INFO_X_MEMOS
	12%s ten actualmente 12%d mensaxes.
MEMO_INFO_X_MEMOS_ONE_UNREAD
	12%s ten actualmente 12%d mensaxes, das que12 1 está sen ler.
MEMO_INFO_X_MEMOS_SOME_UNREAD
	12%s ten actualmente 12%d mensaxes, das que 12%d están sen ler.
MEMO_INFO_X_MEMOS_ALL_UNREAD
	12%s ten actualmente 12%d mensaxes; das que todas están sen ler.
MEMO_INFO_X_LIMIT
	O límite de mensaxes de 12%s é %d.
MEMO_INFO_X_HARD_LIMIT
	O límite de mensaxes de 12%s é %d, e non pode ser cambiado polo usuario.
MEMO_INFO_X_NO_LIMIT
	12%s non ten límite de mensaxes.

###########################################################################
#
# mensaxes de OperServ
#
###########################################################################

# General messages
OPER_BOUNCY_MODES
	Services non pode cambiar modos.
	As súas servidoras están configuradas correctamente?
OPER_BOUNCY_MODES_U_LINE
	Services non pode cambiar modos.
	As liñas U: das súas servidoras están configuradas correctamente?

# GLOBAL responses
OPER_GLOBAL_SYNTAX
	12GLOBAL <message>

# STATS responses
OPER_STATS_UNKNOWN_OPTION
	Opción STATS 12%s descoñecida.
OPER_STATS_CURRENT_USERS
	Usuarios actuais  : 12%d (12%d ops)
OPER_STATS_MAX_USERS
	Máximo de usuarios: 12%d (12%s)
# This is ugly, but at least it's language-portable...
OPER_STATS_UPTIME_DHMS
	Services activos 12%d días, 12%02d:%02d
OPER_STATS_UPTIME_1DHMS
	Services activos 12%d día, 12%02d:%02d
OPER_STATS_UPTIME_HMS
	Services activos 12%d horas, 12%d minutos
OPER_STATS_UPTIME_HM1S
	Services activos 12%d horas, 12%d minutos
OPER_STATS_UPTIME_H1MS
	Services activos 12%d horas, 12%d minuto
OPER_STATS_UPTIME_H1M1S
	Services activos 12%d hora, 12%d minuto
OPER_STATS_UPTIME_1HMS
	Services activos 12%d hora, 12%d minutos
OPER_STATS_UPTIME_1HM1S
	Services activos 12%d hora, 12%d minutos
OPER_STATS_UPTIME_1H1MS
	Services activos 12%d hora, 12%d minuto
OPER_STATS_UPTIME_1H1M1S
	Services activos 12%d hora, 12%d minuto
OPER_STATS_UPTIME_MS
	Services activos 12%d minutos, 12%d segundos
OPER_STATS_UPTIME_M1S
	Services activos 12%d minutos, 12%d segundos
OPER_STATS_UPTIME_1MS
	Services activos 12%d minuto, 12%d segundos
OPER_STATS_UPTIME_1M1S
	Services activos 12%d minuto, 12%d segundo
OPER_STATS_BYTES_READ
	Bytes leidos   : 12%5d kB
OPER_STATS_BYTES_WRITTEN
	Bytes escritos : 12%5d kB
OPER_STATS_USER_MEM
	User    : 12%6d rexistros, 12%5d kB
OPER_STATS_CHANNEL_MEM
	Channel : 12%6d rexistros, 12%5d kB
OPER_STATS_NICKSERV_MEM
	NickServ: 12%6d rexistros, 12%5d kB
OPER_STATS_CHANSERV_MEM
	ChanServ: 12%6d rexistros, 12%5d kB
OPER_STATS_OPERSERV_MEM
	OperServ: 12%6d rexistros, 12%5d kB
OPER_STATS_AKILL_COUNT
	Número actual de AKILLs: 12%d
OPER_STATS_AKILL_EXPIRE_DAYS
	Tempo defecto para expirar AKILL: 12%d días
OPER_STATS_AKILL_EXPIRE_DAY
	Tempo defecto para expirar AKILL:12 1 día
OPER_STATS_AKILL_EXPIRE_HOURS
	Tempo defecto para expirar AKILL: 12%d horas
OPER_STATS_AKILL_EXPIRE_HOUR
	Tempo defecto para expirar AKILL:12 1 hora
OPER_STATS_AKILL_EXPIRE_MINS
	Tempo defecto para expirar AKILL: 12%d minutos
OPER_STATS_AKILL_EXPIRE_MIN
	Tiempo defecto para expirar AKILL:12 1 minuto
OPER_STATS_AKILL_EXPIRE_NONE
	Tiempo defecto para expirar AKILL: 4No expira
OPER_STATS_SESSIONS_MEM
	Sesiones: 12%6d rexistros, 12%5d kB

# MODE responses
OPER_MODE_SYNTAX
	12MODE <canal> <modos>

# CLEARMODES responses
OPER_CLEARMODES_SYNTAX
	12CLEARMODES <canal> [ALL]

OPER_CLEARMODES_DONE
	Modos e bans do canal 12%s foron eliminados.
OPER_CLEARMODES_ALL_DONE
	Tódolos modos do canal 12%s foron eliminados.

# KICK responses
OPER_KICK_SYNTAX
	12KICK <canal> <nick> <motivo>


# ADMIN responses
OPER_ADMIN_SYNTAX
	12ADMIN {ADD | DEL | LIST} [nick]
OPER_ADMIN_ADD_SYNTAX
	12ADMIN ADD <nick>
OPER_ADMIN_DEL_SYNTAX
	12ADMIN DEL <nick>
OPER_ADMIN_SKELETON
	Services está en modo skeleton; o comando ADMIN non está disponible.
OPER_ADMIN_EXISTS
	12%s xa existe na lista de Administradores de Services.
OPER_ADMIN_ADDED
	12%s engadido á lista de Administradores de Services.
OPER_ADMIN_TOO_MANY
	Moitas entradas (12%d) na lista de Administradores de Services; non se poden agregar máis.

OPER_ADMIN_REMOVED
	12%s borrado da lista de Administradores de Services.
OPER_ADMIN_NOT_FOUND
	12%s non foi atopado na lista de Administradores de Services.
OPER_ADMIN_LIST_HEADER
	Lista de Administradores de Services:

# OPER responses
OPER_OPER_SYNTAX
	12OPER {ADD | DEL | LIST} [nick]
OPER_OPER_ADD_SYNTAX
	12OPER ADD <nick>
OPER_OPER_DEL_SYNTAX
	12OPER DEL <nick>
OPER_OPER_SKELETON
	Services está en modo skeleton; o comando OPER non está disponible.
OPER_OPER_EXISTS
	12%s xa existe na lista de Operadores de Services.
OPER_OPER_ADDED
	12%s engadido á lista de Operadores de Services.
OPER_OPER_TOO_MANY
	Moitas entradas (12%d) na lista de Operadores de Services; non se poden agregar mas.
OPER_OPER_REMOVED
	12%s borrado da lista de Operadores de Services.
OPER_OPER_NOT_FOUND
	12%s non foi atopado na lista de Operadores de Services.
OPER_OPER_LIST_HEADER
	Lista de Operadores de Services:

# AKILL responses
OPER_AKILL_SYNTAX
	12AKILL {ADD | DEL | LIST | VIEW} [[+expiracion] <máscara> [motivo]]
OPER_AKILL_ADD_SYNTAX
	12AKILL ADD [+expiracion] <mask> <motivo>
OPER_AKILL_DEL_SYNTAX
	12AKILL DEL <máscara>

OPER_AKILL_NO_NICK
	4Atención: Máscaras de AKILL non poden conter nicks;
	Teña a certeza de 4NON incluir unha parte de nick na súa máscara.

OPER_AKILL_ADDED
	12%s engadido á lista de AKILL.
OPER_AKILL_REMOVED
	12%s eliminado da lista de AKILL.
OPER_AKILL_NOT_FOUND
	12%s non foi atopado na lista de AKILL.
OPER_AKILL_LIST_HEADER
	Lista actual de AKILL:
# mask, reason
OPER_AKILL_LIST_FORMAT
	%-32s  %s
# mask, set-by, set-time, expires, reason
OPER_AKILL_VIEW_FORMAT
	%s (por %s en %s; %s)
	    %s
OPER_AKILL_NO_EXPIRE
	non expira
OPER_AKILL_EXPIRES_SOON
	expira na seguinte actualización de base de datos
OPER_AKILL_EXPIRES_M
	expira en 12%d minutos
OPER_AKILL_EXPIRES_1M
	expira en 12%d minuto
OPER_AKILL_EXPIRES_HM
	expira en 12%d horas, 12%d minutos
OPER_AKILL_EXPIRES_H1M
	expira en 12%d horas, 12%d minuto
OPER_AKILL_EXPIRES_1HM
	expira en 12%d hora, 12%d minutos
OPER_AKILL_EXPIRES_1H1M
	expira en 12%d hora, 12%d minuto
OPER_AKILL_EXPIRES_D
	expira en 12%d días
OPER_AKILL_EXPIRES_1D
	expira en 12%d día

# SET responses
OPER_SET_IGNORE_ON
	Ignore code 4será usado.
OPER_SET_IGNORE_OFF
	Ignore code 4non será usado.
OPER_SET_IGNORE_ERROR
	Parámetro para IGNORE debe ser 12ON ou 12OFF.
OPER_SET_READONLY_ON
	Services está agora en modo ler-soamente 4read-only.
OPER_SET_READONLY_OFF
	Services está agora en modo ler-escribir 4read-write.
OPER_SET_READONLY_ERROR
	Parámetro para READONLY debe ser 12ON ou 12OFF.
OPER_SET_DEBUG_ON
	Services está agora en modo debug.
OPER_SET_DEBUG_OFF
	Services está agora en modo non-debug.

OPER_SET_DEBUG_LEVEL
	Services está ahora en modo debug (nivel %d).
OPER_SET_DEBUG_ERROR
	Parámetro para DEBUG debe ser 12ON, 12OFF, ou un numero positivo.
OPER_SET_UNKNOWN_OPTION
	Opción 12%s desconocida.

# JUPE responses
OPER_JUPE_SYNTAX
	12JUPE <servidor> [motivo]

# RAW responses
OPER_RAW_SYNTAX
	12RAW <text>

# UPDATE responses
OPER_UPDATING
	4Actualizando... bases de datos.

# RESTART responses
OPER_CANNOT_RESTART
	SERVICES_BIN non definida; non é posible reiniciar.  Execute de novo o script \2configure\2 e recompile Services para habilita-lo comando RESTART.

# LISTIGNORE responses
OPER_IGNORE_LIST
	Lista de ignoración de Services:
OPER_IGNORE_LIST_EMPTY
	Lista de ignoración está valeira.

# KILLCLONES responses
OPER_KILLCLONES_SYNTAX
	12KILLCLONES <nick>
OPER_KILLCLONES_UNKNOWN_NICK
	Non foi encontrado o nick 12%s.

# ROTATELOG responses
OPER_ROTATELOG_FILE_EXISTS
	Non ha podido renombrar el log, un archivo con o nombre 12%s todavia existe!.
OPER_ROTATELOG_RENAME_DONE
	Log renombrado a 12%s
OPER_ROTATELOG_RENAME_FAIL
	Log non ha podido renombrarlo: 12%s
OPER_ROTATELOG_OPEN_LOG_FAIL
	Logueando no ha podido resetear: 12%s




###########################################################################
#
# mensaxes de axuda de NickServ
#
###########################################################################

NICK_HELP
	4%S lle permite "rexgistrar" un nick e prevén que outros
	fagaun uso del. Se o nick non é utilizado por
	12%d días, o rexistro expirará. Os seguintes comandos
	permiten o rexistro e mantemento de nicks; para utilizalos,
	escribe 12/msg %S comando.
	 
	Para maior información dun comando específico, escribe
	12/msg %S HELP comando.
	
	    12REGISTER   Rexistra un nick
	    12IDENTIFY   Identificarse co teu contrasinal
	    12ACCESS     Modifica-la lista de enderezos (direccións) autorizados
	    12LINK       Facer do teu nick un alias doutro
	    12SET        Axustar opcións, incluindo protección de kill
	    12DROP       Cancela o rexistro dun nick
	    12RECOVER    Desconecta a outro usuario que está usando o teu nick
	    12RELEASE    Toma custodia do teu nick despois de utiliza-lo
	                comando RECOVER
	
	Outros comandos: 12UNLINK, 12GHOST, 12INFO, 12LIST, 12STATUS
	
	4NOTA: Este servicio esta deseñado para proveer un modo no
	que os usuarios de IRC aseguran que a súa dentidade non sexa
	comprometida.  A súa intención 4NON é para facilita-lo "roubo"
	de nicks ou otras accións malintencionadas. O abuso de
	%S resultará, polo menos, da perda do/dos nick(s) abusivo(s).

NICK_HELP_REGISTER
	Sintaxe: 12REGISTER <oteu-enderezo@email.es>
	
	Rexistra o teu nick na base de datos de 12%S. Unha vez rexistrado
	o seu nick, podes utiliza-los comandos 12SET e 12ACCESS para
	configura-los parámetros do teu nick como os desexes.
	Asegúrate de lembra-lo contrasinal que utilizaches para
	rexistrarte--necesitarlo para facer cambios no teu nick
	posteriormente. (Nótese que as maiúsculas importan
	MILO, Milo, y milo son diferentes todos!)
	
	Suxerencias para escoller un contrasinal:
	
	Os contrasinais non deben ser fáciles de adiviñar. Por exemplo,
	usa-lo teu verdadeiro nome como contrasinal é unha mala idea.
	Utiliza-lo teu nick como contrasinal é unha idea peor ;) e, por
	suposto que, %S non  o permitirá. Tamén, contrasinais
	curtas son vulnerables a búsquedas de proba e erro, polo
	que debes escoller un contrasinal de polo menos 5
	caracteres. Finalmente, o carácter de "espacio" non se
	puede utilizar en contrasinais.

NICK_HELP_IDENTIFY
	Sintaxe: 12IDENTIFY <contrasinal>
	
	Notifica a 12%S que ti é-lo verdadeiro dono deste
	nick. Moitos dos comandos requiren que ti te
	identifiques con este comando antes de poder utilizalos. O
	contrasinal debe se-lo mesmo que utilizaches co comando
	12REGISTER.

NICK_HELP_DROP
	Sintaxe: 12DROP
	
	Elimina o teu nick da base de datos de 12%S. Un nick
	que foi eliminado está disponible para que cualquera
	persoa o volva rexistrar.
	
	Para utilizar este comando, tés que identificarte
	co teu contrasinal (12/msg %S HELP IDENTIFY para maior
	información).

NICK_HELP_ACCESS
	Sintaxe:  12ACCESS ADD <máscara>
	          12ACCESS DEL <máscara>
	          12ACCESS LIST
	
	Modifica ou amosa a lista de acceso para o teu nick. Ésta
	é a lista de enderezos que 12%S recoñecerá automáticamente
	como válidas para utilizar este nick. Se desexa utilizar este
	nick desde outra dirección, necesitas envia-lo comando
	12IDENTIFY para que 12%S te recoñeza.
	
	Exemplos:
	
	    12ACCESS ADD Gollum@*.zolty.net
	        Permite o acceso ó usuario 12Gollum de calquera
		computadora no dominio 12zolty.net.
	
	    12ACCESS DEL Gollum@*.zolty.net
	        Fai o contrario do comando anterior.
	
	    12ACCESS LIST
	        Amosa a lista de acceso.

NICK_HELP_LINK
	Sintaxe: 12LINK <nick> <contrasinal>
	
	Liga o teu nick a outro, facendo efectivamente un alias para o
	nick que ti utilizas actualmente con outro nick
	especificado. Cando utilizas este comando, a lista
	de acceso do nick que tes é eliminada e reemplazada
	pola do nick coa que fa-lo enlace; tódalasmensaxes
	oara o nick actual son engadidos á lista de mensaxes do nick
	a ligar (isto pode causar que o nick se exceda no seu límite
	de mensaxes; neste caso necesitará borrar algunhas das
	mensaxes antes de poder recibir novas mensaxes para
	calquera de ambolos nicks).

	Unha vez establecida a liga, o teu nick será convertido
	transparentemente ó nick novo en tódalas bases de datos
	de Services, excepto para os comandos 12%S UNLINK e
	12DROP.  Por exemplo, podes utilizar calquera dos nicks
	para le-las mesmas mensaxes (e as mensaxes que se envían
	a calquera dos nicks irán á mesma lista). Se se identifica
	para un nick, automáticamente se identificará para o outro.
	Se calquera de ámbolos nicks está na lista de acceso dun canal,
	ámbolos nicks terán os mesmos privilexios e accesos.

	Para utilizar este comando, debes identificarte para
	o teu nick actual (usando o comando 12IDENTIFY), e debes
	proporciona-lo contrasinal para o nock ó que desexas ligar.

NICK_HELP_UNLINK
	Sintaxe: 12UNLINK
	
	Elimina a liga do teu nick cara outro. Cando a liga
	se elimina, os modos dun nick e a lista de acceso do
	nick previamente ligado son copiados ó teu nick actual e
	poden ser modificados independentemente. As mensaxes non son
	copiadas; tódalas mensaxes permanecen co nick previamente 
	ligado.

NICK_HELP_SET
	Sintaxe: 12SET <opción> <parámetros>
	
	Axusta varios parámetros do nick. Unha opción pode ser:
	
	    12PASSWORD   Axusta ou establece o contrasinal do teu nick
	    12LANGUAGE   Axusta ou establece a linguaxe que Services utilizará cando
	                   che envíe menaxes
	    12URL        Asocia unha URL co teu nick
	    12EMAIL      Asocia un enderezo de E-mail co teu nick
	    12KILL       Activa/desactiva a protección de kill
	    12SECURE     Activa/desactiva o modo SECURE para o teu nick
	    12PRIVATE    Evita que o teu nick apareza en
	                   12/msg %S LIST
	    12HIDE       Agacha certas informacións sobre o teu nick
	
	Para utilizar este comando é necesario identificarse antes
	co teu contrasinal (12/msg %S HELP IDENTIFY para maior
	información).
	
	Escribe 12/msg %S HELP SET <opción> para maeor información
	sobre unha opción específica.

NICK_HELP_SET_PASSWORD
	Sintaxe: 12SET PASSWORD <novo-contrasinal>
	
	Cambia o contrasinal que utiliza para identificarse como o
	dono do nick.

NICK_HELP_SET_LANGUAGE
	Sintaxe: 12SET LANGUAGE <número>

	Cambia a lingua que Services utiliza cando che envía
	mensaxes (por exemplo cando responde a un comando que
	ti lle enviaches). número debe ser escollido da seguinte
	lista de lenguas soportadas:
	

NICK_HELP_SET_URL
	Sintaxe: 12SET URL <url>
	
	Asocia un URL dado co teu nick. Este URL será amosada
	cando solicites información do teu nick co comando 12INFO.

NICK_HELP_SET_EMAIL
	Sintaxe: 12SET EMAIL <enderezo>

	Asocia o enderezo de E-mail dado co teu nick. Este
	enderezo será amosado cando alguén solicite información
	sobre o teu nick co comando 12INFO.

NICK_HELP_SET_KILL
	Sintaxe: 12SET KILL {ON | QUICK | IMMED | OFF}
	
	Activa/desactiva a protección de kill para o teu nick. Con
	protección de kill activada, se algún outro usuario intenta
	utiliza-lo teu nick, se lle dará un minuto para que cambie
	a outro; se non, se lle dará carril forzosamente do IRC por 12%S.

	Se seleccionas 12QUICK, o usuario só terá 20 segundiños para
	cambiar de nick en troques lugar do usual (60 segundos). Se
	seleccionas 12IMMED, o usuario será desconectado (kill)
	inmediatamente 4sin ser avisado primeiro ou darlle unha
	oportunidade de cambiar de nick. Por favor, non utilices esta
	opción a menos que sexa verdadeiramente necesario. Os
	Administradores da rede poden ter deshabilitada esta opción.

NICK_HELP_SET_SECURE
	Sintaxe: 12SET SECURE {ON | OFF}
	
	Activa/desactiva as funcións de seguridade de 12%S para
	o teu nick. Con 12SECURE activado, non debes envia-lo teu
	contrasinal antes de que se che recoñeza como o dono do nick,
	son importar se o teu enderezo está ou non na lista de
	acceso. Sen embargo, se aparece na lista de acceso, 12%S
	non te desconectará automáticamente, independentemente de
	cómo estea a opción de 12KILL.

NICK_HELP_SET_PRIVATE
	Sintaxe: 12SET PRIVATE {ON | OFF}
	
	Activa/desactiva a opción privacidade de %S sobre o teu
	nick. Con PRIVATE activado, o teu nick non aparecerá nas
	listas de nicks xeradas co comando 12%S LIST.
	(Sen embargo, calquera que coñeza o teu nick pode obter
	información usando o comando 12INFO.)

NICK_HELP_SET_HIDE
	Sintaxe: 12SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
	
	Permite que evites que certas informacións sexan amosadas
	cando alguén usa o comando 12%S INFO no teu nick. Podes
	agachar ou esconde-lo teu E-mail (12EMAIL), última
	máscara user@host (12USERMASK), ou o teu último mensaxe de saída
	(12QUIT). O segundo parámetro especifica qué información
	debe ser amosada (12OFF) o agachada (12ON).

NICK_HELP_RECOVER
	Sintaxe: 12RECOVER <nick> [contrasinal]
	
	Permite que recupérelo teu nick se alguén máis o tomou;
	isto é o mesmo que 12%S fai automáticamente se alguén
	trata de utilizar un nick protexido con kill.
	
	Cando envías este comando, 12%S conectará en línea a un
	usuario falso co mesmo nick que o usuario que ti desexas
	recuperar. Isto causará que os servidores de IRC desconecten
	ó outro usuario. O usuario falso permanecerá en línea por un
	minuto para asegurar que o outro usuario non se reconecte
	inmediatamente; despois dese minuto, podes toma-lo teu nick.
	Alternativamente, usa o comando 12RELEASE
	(12/msg %S HELP RELEASE) para obte-lo teu nick máis rápido.
	
	Para usa-lo comando 12RECOVER para un nick, o teu enderezo
	actual como se amosa nun /WHOIS debe de estar na lista de 
	acceso do nick, ou debes porporciona-lo contrasinal correcto 
	para o nick.

NICK_HELP_RELEASE
	Sintaxe: 12RELEASE <nick> [contrasinal]
	
	Ordena a 12%S eliminar calquera espera no teu nick
	causada por un kill automático de protección ou polo uso do
	comando 12RECOVER. Por defecto, a espera dura un minuto;
	este comando o libera máis rapidamente.
	
	Para usa-lo comando 12RELEASE para un nick, a túa dirección
	actual como se amosa nun /WHOIS ha de estar na lista de acceso
	do nick, ou debes proporciona-lo contrasinal correcto para o nick

NICK_HELP_GHOST
	Sintaxe: 12GHOST <nick> [contrasinal]
	
	Elimina unha sesión "pantasma" de IRC que estea utilizando o seu
	nick. Unha sesión "pantasma" é aquela que non está realmente
	conectada, pero que un servidor de IRC acredita como activa
	por calquera razón. Normalmente isto sucede se a túa computadora
	se bloquea ou a túa conexión a Internet se desconecta por un
	periodo curto mentres estás no IRC.

	Para usa-lo comando 2GHOST para un nick, a túa dirección
	actual como se amosa nun /WHOIS ha de estar na lista de acceso
	do nick, ou debes proporciona-lo contrasinal correcto para o nick

NICK_HELP_INFO
	Sintaxe: 12INFO <nick>
	
	Amosa información sobre un nick dado, como quen é
	o dono, última dirección utilizada e hora, e as
	diferentes opcións do nick.

NICK_HELP_LIST
	Sintaxe: 12LIST <patrón>
	
	Lista tódolos nicks rexistrados que concordan con un
	patrón dado en formato nick!user@host. Os Nicks coa opción
	de PRIVATE activada non serán amosados no listado.
	
	Exemplos:
	
	    12LIST *!bea@zolty.net
	         Lista os niks rexistrados por 12bea@zolty.net.
	
	    12LIST *bud*!*@*
	         Lista tódolos nicks rexistrados que conteñan 12bud
		   no seu nome (non importan as maiúsculas)
	
	    12LIST *!*@*.globalchat.org
	        Lista tódolos nicks rexistrados por usuarios do dominio 12globalchat.org.

NICK_HELP_STATUS
	Sintaxe: 12STATUS <nick>...
	
	Informa se o usuario dun nick é recoñecido como o dono
	do mesmo. A resposta ten o seguinte formato:
	
	    12nick código-de-status
	
	oonde 12nick é o nick enviado co comando;
	12código-de-status é un dos seguintes:
	
	    0 - o usuario non está conectado ou o nick non está rexistrado
	    1 - o usuario non recoñecido como o dono do nick
	    2 - o usuario recoñecido pola lista de acceso soamente
	    3 - o usuario recoñecido por identificación con contrasinal
	    4 - o usuario ista suspendido
	  
	Ata 16 nicks poden ser enviados en cada comando; o resto
	serán ignorados. Non se xenera mensaxe de erro se non se
	envía nick.

NICK_SERVADMIN_HELP
	
	Os seguintes comandos están disponibles para os
	4Operadores e Administradores de Services:
	
	    12SENDPASS   Manda o contrasinal á mail
	    12GETPASS    Amosa o contrasinal para un nick
	    12FORBID     Evita que un nick sexa utilizado
	    12UNFORBID   Elimina a prohibición de uso dun nick
	    12SUSPEND    Suspende o Uso dun NICK.
	    12UNSUSPEND  Rehabilita o Uso dun NICK.
	
	Os 4Administradores de Services tamén poden cancelar calquera nick
	sen necesidade de identificarse polo mesmo, e poden ve-la lista
	de acceso de calquera nick (12/msg %S ACCESS LIST <nick>).

NICK_SERVADMIN_HELP_DROP
	Sintaxe: 12DROP [nick]
	
	Sen parámetros, cancela o rexistro do teu nick da base
	de datos de 12%S.
	
	Con un parámetro, cancela o rexistro dese nick na base de datos.
	Este comando está restrinxido a 4Operadores de Services.

NICK_SERVADMIN_HELP_SET
	12Administradores de Services poden selecciona-la opción
	12NOEXPIRE, coa que se pode previr que algúns nicks non
	expiren. Ademais, os Administradores de Services poden
	establecer opcións para calquera nick sen necesidade
	de proveer un contrasinal, utilizando o formato
	12SET <nick> <opción> <parámetros>.

NICK_SERVADMIN_HELP_SET_NOEXPIRE
	Sintaxe: 12SET [nick] NOEXPIRE {ON | OFF}
	
	Define se o nick dado expirará. Se se define ON prevén
	que o nick expire. Se non se inclúe un nick, entón se aplica
	ó teu propio nick.

	Limitado a 4Administradores de Services.

NICK_SERVADMIN_HELP_LIST
	Sintaxe: 12LIST <patrón>
	
	Lista tódolos nicks rexistrados que concorden co patrón
	definido, en formato 12nick!user@host. Os Nicks coa opción
	de PRIVATE activada non serán amosados no listado.
	
	Exemplos:
	
	    LIST *!bea@zolty.net
	         Lista os niks rexistrados por 12bea@zolty.net.
	
	    12LIST *bud*!*@*
	         Lista tódolos nicks rexistrados que conteñan 12bud
		   no seu nome (non importan as maiúsculas)

NICK_SERVADMIN_HELP_GETPASS
	Sintaxe: 12GETPASS <nick>
	
	Amosa o contrasinal para o nick dado. Nota que cando
	este comando é utilizado, unha mensaxe incluindo o nick da
	persoa que o utiliza, o nock sobre o cal se pregunta
	é grabado no log e enviado como unha mensaxe global
	(WALLOPS/GLOBOPS).
	
	Limitado a 4Administradores de Services.

NICK_SERVADMIN_HELP_FORBID
	Sintaxe: 12FORBID <nick>
	
	Prohibe o rexistro e a utilización dun nick. Pódese cancelar
	utilizando o comando DROP.
	
	Limitado a 4Administradores de Services.

###########################################################################
#
# mensaxes de Axuda de ChanServ
#
###########################################################################

CHAN_HELP
	4%S habilita a rexistrar e controlar varios aspectos dos
	canais. 4%S pode previr que usuarios malintencionados
	podan "tomar-lo control" limitando a quén se permiten
	privilexios de operador do canal. Os comandos disponibles son
	os que se detallan a continuación. Para utilizalos, escribe
	12/msg %S comando.  Para obter máis información dun comando
	específico, escribe 12/msg %S HELP comando.
	
	    12REGISTER   Rexistra un canal
	    12IDENTIFY   Para identificarse como fundador do canal
	    12SET        Fixa opcións e información do canal
	    12ACCESS     Modifica a lista de usuarios privilexiados
	    12LEVELS     Redefine os niveis de accesos
	    12AKICK      Mantén a lista de Auto-Kick
	    12DROP       Cancela o rexistro dun canal
	    12IRCOPS     Amosa os IrcOps/Opers/Admins OnLine.

	Outros comandos: 12INFO, 12LIST, 12INVITE, 12OP, 12DEOP, 12UNBAN,
	                 12CLEAR

CHAN_HELP_EXPIRES
	
	Nota que se un canal non é utilizado por 12%d días (é dicir
	que ningún usuario na lista de acceso do canal entra nese
	periodo de tempo) será automáticamente cancelado.

CHAN_HELP_REGISTER
	Sintaxe: 12REGISTER <canal> <contrasinal> <descripción>
	
	Rexistra unnovo canal na base de datos de 12%S.
	Para poder utilizar este comando, primeiro debes ser
	operador do canal que está tratando de rexistrar (1). O
	contrasinal deberá ser utilizado co comando 12IDENTIFY
	cando precises facer modificacións posteriores a opcións
	do canal. O último parámetro, que 12debe ser incluido,
	é unha descripción dos propósitos do canal.

	Cando rexistras un canal, quedas rexistrado como o 
	"fundador" do canal. O fundador dun canal pode modificar
	calquera das opcións dun canal (excepto o nombre mesmo
	do canal); %S dará automáticamente privilexio de operador
	ó fundador do canal cando el/ela ingresen ó canal. Bota
	unha ollada ó comando 12ACCESS (12/msg %S HELP ACCESS) 
	para obter información de como dar privilexio de operadores
	a outros usuarios do canal.

	(1) AVISO: para poder rexistrar un canal, o teu nick ha de
	estar rexistrado. Se ainda non o rexistraches, escribe
	12/msg %s HELP para obter información de cómo facelo.

CHAN_HELP_IDENTIFY
	Sintaxe: 12IDENTIFY <canal> <contrasinal>
	
	Este comando, te identifica ante 12%S como o fundador do
	12canal. Moitos comandos requiren que utilices ESTE
	comando antes de poder utilizalos. O contrasinal debe
	se-lo mesmo que se introduciu no memoento de rexistra-lo
	canal (comando 12REGISTER).

CHAN_HELP_DROP
	Sintaxe: 12DROP <canal>
	
	Elimina o 12canal da base de 12%S. Pode ser utilizado
	unicamente polo 12fundador do canal, quen deberá
	primeiramente identificarse co comando 12IDENTIFY.

CHAN_HELP_SET
	Sintaxe: 12SET <canal> <opción> <parámetros>
	
	Habilita ó fundador do canal a definir varias opcións e
	outra información. O fundador, debe identificarse vía
	comando 12IDENTIFY antes de utilizar 12SET.
	
	Opcións disponibles:
	
	    12FOUNDER     Cambia o fundador del canal
	    12PASSWORD    Cambia o contrasinal do fundador
	    12DESC        Cambia a descripción do canal
	    12URL         Asocia unha URL ó canal
	    12EMAIL       Asocia unha dirección de correo ó canal
	    12ENTRYMSG    Fixa unha mensaxe que será amosada ós usuarios
	                cando entren ó canal
	    12TOPIC       Cambia o Tema do canal
	    12KEEPTOPIC   Retén o tema (topic) cando o canal non está en uso
	    12TOPICLOCK   O Tema SÓ poderá ser cambiado vía SET TOPIC
	    12MLOCK       Fixa os modos do canal en 'ON' ou 'OFF'
	    12PRIVATE     Oculta o canal (non se ve cando se utiliza o comando LIST)
	    12RESTRICTED  Restrinxe o acceso ó canal
	    12SECURE      Activa os rasgos de seguridade de %S
	    12SECUREOPS   Control estricto de Status de operador
	    12ISSUED	    Activa/desactiva o chivato de los canales
	
	Escribe 12/msg %S HELP <opción> para obter máis
	información dunha opción en particular.

CHAN_HELP_SET_FOUNDER
	Sintaxe: 12SET <canal> FOUNDER <nick>
	
	Cambia o dundador do canal 12canal. O nick dado, que será
	o novo fundador do canal, debe estar rexistrado.

CHAN_HELP_SET_PASSWORD
	Sintaxe: 12SET <canal> PASSWORD <contrasinal>
	
	Se utiliza para defini-lo contrasinal que será utilizado
	para identificarse como o fundador do canal.

CHAN_HELP_SET_DESC
	Sintaxe: 12SET <canal> DESC <descripción>
	
	Fixa a descripción do canal, que será amosada cando se utilicen
	os comandos 12LIST e 12INFO. Deberías ser breve e concreto.

CHAN_HELP_SET_URL
	Sintaxe: 12SET <canal> URL [url]
	
	Asocia unha URL ó <canal>, que será visualizada cando
	se solicite información do canal (vía comando 12INFO).
	Habitualmente se utiliza para indica-la dirección da páxina
	web do canal. Se non se introduce ningunha url, borraráse
	a que teña actualmente o canal.

CHAN_HELP_SET_EMAIL
	Sintaxe: 12SET <canal> EMAIL [dirección]
	
	Asocia a dirección de correo dada ó canal. Esta dirección
	será amosada cando alguén solicite (vía comando 12INFO)
	información do canal. É moi útil, por exemplo, para que
	os usuarios teñan unha vía de comunicación co fundador
	e/ou operadores do canal. Se non se proporciona unha
	dirección de correo, se eliminará a que actualmente poida
	ter un canal.

CHAN_HELP_SET_ENTRYMSG
	Sintaxe: 12SET <canal> ENTRYMSG [mensaxe]
	
	Establece a mensaxe que será enviada ós usuarios (vía
	/notice) cando eles ingresen ó canal. Se 12mensaxe non se
	ingresa, nada será enviado ós usuarios cando ingresen.

CHAN_HELP_SET_TOPIC
	Sintaxe: 12SET <canal> TOPIC <texto>
	
	Causa que 12%S fixe o tema do canal indicado en
	12texto.  Esta orden é moi útil en conxunción con
	12SET TOPICLOCK.

CHAN_HELP_SET_KEEPTOPIC
	Sintaxe: 12SET <canal> KEEPTOPIC {ON | OFF}
	
	Habilita ou deshabilita a opción de retención do tema para
	o canal. Cando retención do tema está en ON
	(habilitada), o tema do canal será recordado por 12%S
	ainda despois de que o último usuario se teña retirado, e se
	restaurará a próxima vez que alguén ingrese ó canal.

CHAN_HELP_SET_TOPICLOCK
	Sintaxe: 12SET <canal> TOPICLOCK {ON | OFF}
	
	Habilita ou deshabilita a opción para 12traba-lo topic do
	canal. Cando 12traba-lo topic está en ON, 12%S non habilitará
	o cambio do tema (topic) excepto via 12SET TOPIC.

CHAN_HELP_SET_MLOCK
	Sintaxe: 12SET <canal> MLOCK <modos>
	
	Fixa os distintos modos para o canal. 12%S te habilita para
	definir determinados modos do canal e que quden sempre
	habilitados (ou non). Os modos que poden ser fixados son:
	i, k, l, m, n, p, s, y t; cada un destes mdos
	pode estar activado (ON), desactivado (OFF) ou non fixado. Os
	distintos modos se indican exactamenete como se se utilizase
	o comando /MODE; isto é, modo seguido de + indica 
	activado (ON), modo seguido de - indica desactivado (OFF).
	
	4Cuidado!:  Se fixas un modo protexido por contrasinal,
	como no segundo exemplo, tamén deberás fixa-la opción
	RESTRICTED para o canal (mira HELP SET RESTRICTED), ou
	calquera que entre ó canal cando o mesmo estea vacío,
	verá o contrasinal!!
	
	Exemplos:
	
	    12SET #canal MLOCK +nt-iklps
	       Activa os modos n y t, e desactiva os modos i, k,
	       l, p, y s.  O modo m pode ser activado ou desactivado.
	
	    12SET #canal MLOCK +knst-ilmp my-key
	       Activa os modos k, n, s, y t.
	       Desactiva os modos i, l, m, y p.
	       Tamén establece "my-key" como contrasinal do canal.
	
	    12SET #canal MLOCK +
	       Elimina os modos activos; tódolos modos do canal
		 poden ser libremente activados ou desactivados.

CHAN_HELP_SET_PRIVATE
	Sintaxe: 12SET <canal> PRIVATE {ON | OFF}
	
	Habilita ou deshabilita a opción de privado para o canal.
	Cando esta opción está activada, o comando /msg %S LIST non
	incluirá o canal en ningunha lista.

CHAN_HELP_SET_RESTRICTED
	Sintaxe: 12SET <canal> RESTRICTED {ON | OFF}
	
	Habilita ou deshabilita a opción de acceso restrinxido para
	o canal.  Cando o acceso restrinxido está activo (ON), os
	usuarios que normalmente non teñen privilexio de operadores
	cando entran ó canal (usuarios con nivel de acceso
	negativo e, se 12secure ops está activada, os usuarios que NON
	están na lista de acceso) serán expulsados (e se lles
	prohibirá el acceso) ó canal.

CHAN_HELP_SET_SECURE
	Sintaxe: 12SET <canal> SECURE {ON | OFF}
	
	Habilita ou deshabilita a seguridade de 12%S para o
	canal. Cando SECURE está ACTIVO, So os usuarios que
	teñen rexistrado os seus nicks con 12%S e se teñan IDENTIFICADO
	coas súas respectivas contrasinais terán acceso ó canal
	se é que figuran na lista de ACCESS.

CHAN_HELP_SET_SECUREOPS
	Sintaxe: 12SET <canal> SECUREOPS {ON | OFF}
	
	Habilita ou deshabilita a opción de 12operadores seguros para
	o canal. Cando 12operadores seguros está activada (ON), os
	usuarios que NON estean na lista de usuarios do canal NON
	poderán obter status de operadores.

CHAN_HELP_ACCESS
	Sintaxe:  12ACCESS <canal> ADD <nick> <nivel>
	          12ACCESS <canal> DEL {nick | posición-numero}
	          12ACCESS <canal> LIST [mask]
	
	Mantén a 12lista de accesos do canal. A lista de accesos
	establece que usuarios están habilitados para ser operadores
	do canal ou acceder a comandos de 12%S no canal. Se poden
	establecer diferentes niveis de usuarios para acceder a
	diferentes privilexios; utiliza 12/msg %S HELP ACCESS LEVELS
	para obter información máis específica. Calquera nick que
	non estea na lista de acceso ten nivel de usuario 0 (cero).

	O comando 12ACCESS ADD agrega ó 12nick co 12nivel dado á
	lista de acceso; se o usuario xa existe na lista, se
	reemplazará o seu nivel. O nivel especificado debe ser menor
	que o que ten o usuario que está introducindo o comando,
	e se o nick está actualmente na lista, o nivel actual
	dese nick debe ser menor que o nivel do usuario que está
	introducindo o comando.

	O comando 12ACCESS DEL elimina un usuario da lista de
	accesos. Pódese eliminar un usuario introducindo o nick ou
	ingresando o número que ocupa na lista de accesos.
	
	O comando 12ACCESS LIST amosa a lista de accesos ó canal;
	pódense utilizar caracteres comodíns ou máscaras. Nese caso,
	só as coincidencias concurrentes están listadas.

CHAN_HELP_ACCESS_LEVELS
	Niveis de acceso para usuarios
	
	Por defecto, os siguientes niveis son definidos:
	
	   12Founder   Acceso FULL ás funcións de %S.
	                  Privilexio de operador ó ingresar ó canal.
	                  Nota que únicamente unha sola persona pode
	                  ter acceso de fundador do canal (non se
	                  pode dar acceso de founder co comando
	                  12ACCESS).
	   12    400   Acceso ó comando ACC-CHANGE.
	   12    300   Acceso ó comando AKICK.
	   12    200   Operador automático ó ingresar.
	   12    100   Estado de VOZ automático (+v).
	   12      0   Non ten privilexios especiais; pode obter
	                  status de operador dado por outro operador
	                  (a menos que 12secure-ops estea activado).
	   12     <0   Non pode ser operador.
	
	Estes niveis poden ser cambiados, ou novos engadidos
	utilizando o comando 12LEVELS; escribe
	12/msg %S HELP LEVELS para máis información.

CHAN_HELP_AKICK
	Sintaxe:  12AKICK <canal> ADD <mask> [razón]
	          12AKICK <canal> DEL <mask>
	          12AKICK <canal> LIST [mask]
	
	Definimos AKICK como "Expulsión automática".
	Definimos BAN como "Entrada prohibida".
	Este comando, mantén a lista de 12AKICK do canal. Se un
	usuario está na lista de 12AKICK e tenta entrar no canal,
	12%S automáticamente agrega a ese usuario á lista BAN
	do canal, e logo o expulsa do canal.

	O comando 12AKICK ADD agrega un usuario á lista de 12AKICK[B.
	Se unha 12razón é dada co comando, entón a razón será
	utilizada por 12%S cando expulse a ese usuario; se non, a
	mensaxe que se usará por defecto, é "You have been banned
	from the channel".

	O comando 12AKICK DEL elimina ó usuario da lista de AKICK.
	Este comando non quita o BAN que poda existir no canal,
	que deberá ser quitado manualmente.

	O comando 12AKICK LIST amosa a lista de usuarios na
	lista de AKICK. Opcionalmente, só lista aqueles
	suministrdos coa máscara dada.

CHAN_HELP_LEVELS
	Sintaxe:  12LEVELS <canal> SET <tipo> <nivel>
	          12LEVELS <canal> {DIS | DISABLE} <tipo>
	          12LEVELS <canal> LIST
	          12LEVELS <canal> RESET
	
	O comando 12LEVELS permite un control estricto sobre os accesos
	numéricos utilizados polos canais. Con este comando, podes
	defini-los niveis requeridos para moitas das funcións de 12%S.
	Os comandos 12SET FOUNDER, 12SET PASSWORD, así como este comando
	están sempre restrinxidos ó fundador.
	
	12LEVELS SET habilita o acceso para unha función ou grupo de
	funcións a ser modificadas.
	
	12LEVELS DISABLE ou 12DIS en forma abreviada) deshabilita un
	privilexio automático, ou deshabilita o acceso para
	calquera outro que non sexa o fundador do canal.
	12LEVELS LIST amosa os niveis actuais para cada función ou
	grupo de funcións.
	
	12LEVELS RESET volve tódolos niveis ós seus valores por
	defecto, os mesmos que cando se rexistra por primeira vez
	un canal (vexa 12HELP ACCESS LEVELS).
	
	Para unha lista as funcións que poden ser establecidas,
	utilice o comando 12HELP LEVELS DESC.

CHAN_HELP_LEVELS_DESC
	A seguinte lista amosa os valores/funcións por 
	defecto. Nota que os niveis para AUTODEOP e NOJOIN son
	os máximos niveis, mentres que tódolos demais son os mínimos.

CHAN_HELP_LEVELS_DESC_FORMAT
	    %-*s  %s

CHAN_HELP_INFO
	Sintaxe: 12INFO <canal>
	
	Provee información acerca do 12canal (ou informa que non está
	rexistrado). Lista o fundador, hora e data de rexistro,
	última vez que se utilizou, descrición, e modos
	do canal (se os houbera).

CHAN_HELP_LIST
	Sintaxe: 12LIST <especificación>
	
	Lista tódolos canais que coincidan coa especificación dada.
	Os canais coa opción 12PRIVATE activada, non son listados.

CHAN_HELP_OP
	Sintaxe: 12OP <canal> <nick>
	
	Convirte en Operador ó usuario indicado no canal indicado.
	Por defecto, está limitado a quen posexan nivel 5 ou máis
	no canal.

CHAN_HELP_DEOP
	Sintaxe: 12DEOP <canal> <nick>
	
	Quita o estado de Operador ó usuario indicado no canal indicado.
	Por defecto, está limitado a quen posexan nivel 5 ou maior
	no canal.

CHAN_HELP_INVITE
	Sintaxe: 12INVITE <canal>
	
	Dille a 12%S que te invite a ti ó 12canal indicado.
	Por defecto, só funciona se o teu nivel de acceso nese
	canal é maior que 0 (cero).

CHAN_HELP_UNBAN
	Sintaxe: 12UNBAN <canal>
	
	Dille a 12%S que elimine tódolos accesos prohibidos
	previndo o seu ingreso a ese canal. Por defecto, só
	funciona se o teu nivel de acceso nese canal é maior
	que 0 (cero).

CHAN_HELP_CLEAR
	Sintaxe: 12CLEAR <canal> <que>
	
	Dille a 12%S que elimine certos parámetros do canal.
	12que pode ser un dos seguintes:
	
	     12modes   Resetea tódolos modos do canal (exemplo,
	             limpia os modos i,k,l,m,n,p,s,r).
	     12bans    Elimina tódolos accesos prohibidos ó canal.
	     12ops     Elimina (quita) o privilexio de operador a
	             tódolos operadores (modo +o) do canal.
	     12voices  Elimina (quita) o privilexio de "voz" (modo
	             +v) a calquera do canal que o tivera.
	     12users   Elimina (Patea -kicks-) TÓDOLOS usuarios do
	             canal.
	
	Por defecto, o teu nivel de acceso no canal debe ser polo
	menos 10 (dez) para utilizar este comando.

CHAN_SERVADMIN_HELP

	Os seguintes comandos están disponibles para os
	4Operadores e Administradores dos Servicios:
	
	    12GETPASS    Devolve o contrasinal do fundador
	    12FORBID     Prevén que un canal poda ser utilizado
	    12UNFORBID   Elimina a prohibición de uso dun Canal.
	    12SAY        Di algo a un Canal.
	    12SUSPEND    Suspende o Uso dun Canal.
	    12UNSUSPEND  Rehabilita o Uso dun Canal.
	    12STATUS     Devolve o nivel de acceso actual dun
	                   usuario nun canal
	    12CSKILL     Killea a un Usuario da rede.
	    12CSBLOCK    Expulsa 5 minutos a un moinante.
	
	Os 4Operadoress de Servicios tamén poden eliminar
	calquera canal sen necesidade de identificarse vía
	contrasinal, e poden ve-la lista de accesos, a lista de 
	AKICK, e lista-los valores de nivel (LEVELS) de calquera
	canal.

CHAN_SERVADMIN_HELP_DROP
	Sintaxe: 12DROP <canal>
	
	Elimina un canal da lista de 12%S. Únicamente os
	4Administradores de Servicios poden eliminar un canal
	sen necesidade de identificarse.

CHAN_SERVADMIN_HELP_SET
	Os Administradores de Servicios tamén poden defini-la opción
	12NOEXPIRE, coa que algún canal se pode previr que expire.
	Adicionalmente, os 4Operadores de Servicios poden
	definir opcións para calquera canal sen necesidade de
	identificarse con contrasinal para ese canal.

CHAN_SERVADMIN_HELP_SET_NOEXPIRE
	Sintaxe: 12SET <canal> NOEXPIRE {ON | OFF}
	
	Define se el canal dado expirara.  Se se define ON prevén
	que o canal expire.
	
	Limitado a 4Administradores de Servicios.

CHAN_SERVADMIN_HELP_LIST
	Sintaxe: 12LIST <especificación>
	
	Lista tódolos canais que coinciden coa especificación dada.
	Os canais coa opción PRIVATE activada só serán amosados
	ós administradores de Servicios.

CHAN_SERVADMIN_HELP_GETPASS
	Sintaxe: 12GETPASS <canal>
	
	Devolve o contrasinal do canal dado.
	12Date conta de que cando este comando é usado, unha mensaxe
	incluindo a persoa que o utilizou e o canal sobre o que
	o usou, será gravado nun ficheiro de rexistro, e será
	enviado como mensaxe (WALLOPS/GLOBOPS).
	
	Limitado a 4Administradores de Servicios.

CHAN_SERVADMIN_HELP_FORBID
	Sintaxe: 12FORBID <canal>
	
	Deshabilita a calquera para utilizar ou rexistra-lo canal
	dado. Pode ser cancelado eliminando o canal (dropping).
	
	Limitado a 4Administradores de Servicios.

CHAN_SERVADMIN_HELP_STATUS
	Sintaxe: 12STATUS <canal> <nick>
	
	Devolve o nivel de acceso actual do nick dado no canal
	dado. A resposta é da forma:
	
	    12STATUS canal nick nivel-de-acceso
	
	Limitado a 4Operadores de Servicios.

###########################################################################
#
# MemoServ help messages (mensaxes de ayuda de MemoServ)
#
###########################################################################

MEMO_HELP
	4%S é unha utilidade que permite a usuarios de IRC
	enviar mensaxes curtas a outros usuarios de IRC,
	independentemente de se están en liña ou nonM igualmente se
	pode enviar mensaxes a canais(*). Ambos nicks (remitente
	e destinatario) deben estar rexistrados previamente, igual
	que o canal ha de estar rexistrado se se desexa enviar unha
	mensaxe a este.
	
	Os comandos de 4%S inclúen:
	
	    12SEND   Envía unha mensaxe a un nick/canal
	    12LIST   Lista tódalas túas mensaxes
	    12READ   Le unha mensaxe
	    12DEL    Borra unha mensaxe (ou todas)
	    12SET    Define opcións relacionadas con mensaxes
	
	Escribe 12/msg %S HELP comando para axuda máis especifica
	dos comandos mencionados.
	
	(*) Por defecto, calquera usuario con polo menos nivel 100
	    de acceso nun canal pode le-las mensaxes dese canal. Isto
	    pódese cambiar co comando 12%S LEVELS.

MEMO_HELP_SEND
	Sintaxe: 12SEND <nick> <memo-texto>
	
	Envía un memo ó usuario especificado. Ese usuario
	recibirá unha noticia de que ten un novo memo. Se recibirá
	inmediatamente se se atopa en liña, ou se non, ó momento
	de identificarse a próxima vez que se conecte.
	
	Exemplo: /msg %S SEND Mishakkal Moi bo o teu traballo de traducción! ;)

MEMO_HELP_LIST
	Sintaxe: 12LIST [NEW]
	
	Lista os memos que teñas actualmente. se se indica o parámetro
	NEW, só os novos memos (os non lidos) serán amosados. Os memos
	non lidos están marcados por un "*" á esquerda
	do número de memo.

MEMO_HELP_READ
	Sintaxe: 12READ { número | LAST}
	
	Amosa o contido do memo indicado en 12número, ou o
	último memo (por exemplo, o recibido máis recentemente) se o
	parámetro LAST é dado EN VEZ DE 12número.

MEMO_HELP_DEL
	Sintaxe: 12DEL { num[-num][,num...] | ALL}
	
	Se un número 12num é dado, elimina ese memo. Podes
	reemplazar un único número por un rango de números para
	eliminar múltiples memos simultáneamente, tal como se verá
	no segundo exemplo.

	Se se ingresa 12ALL eliminaránse TÓDOLOS memos.
	
	Exemplos:
	
	   12DEL 1
	      Elimina o teu primeiro memo.
	
	   12DEL 2-5,7-9
	      Elimina os memos 2 a 5 e 7 a 9.

MEMO_HELP_SET
	Sintaxe: 12SET <opción> <parámetros>
	
	Establece varias opcións para os memos. As 12opciones
	poden ser:
	
	    12NOTIFY      Establece CÁNDO debe ser notificado de
	                novos memos
	    12LIMIT       Establece o MÁXIMO número de memos que
	                podes recibir
	
	Escribe 12/msg %S HELP SET <opción> para obter máis
	información acerca da opción específica.

MEMO_HELP_SET_NOTIFY
	Sintaxe: 12SET NOTIFY {ON | LOGON | NEW | OFF}
	
	Establece CÁNDO debe ser notificado de novos memos:
	
	    12ON      Serás notificado cando te conectes, cando quíte-lo
	            teu modo /AWAY e cando un memo che sexa
	            enviado estando ti conectado.
	    12LOGON   Serás notificado únicamente cando te conectes,
	            e cando quíte-lo teu modo /AWAY.
	    12NEW     Serás notificado só cando che sexan
	            enviados.
	    12OFF     Non recibirás ningún tipo de notificación de
	            memos.
	
	ON é básicamente a combinación de LOGON e NEW
	simultáneamente.

MEMO_HELP_SET_LIMIT
	Sintaxe: 12SET LIMIT [canal] <limite>
	
	Establece o máximo número de memos que estás habilitado a ter.
	Se estableces 12limite a 0 (cero) ninguén
	poderá enviarche memos. De tódolos xeitos, non podes
	establecer 12limite máis alto que 12%d.

MEMO_HELP_INFO
	Sintaxe: 12INFO [canal]
	
	Amosa información da cantidade de memos que tes, cántos deles
	non foron lidos, e a cantidade de memos que podes recibir.

MEMO_SERVADMIN_HELP_SET_LIMIT
	Sintaxe: 12SET LIMIT [usuario] {limite | NONE} [HARD]
	
	Establece o máximo número de memos que un 12usuario pode
	ter. Establecendo o límite a 0 (cero), prevés que ese 
	12usuario poda recibir memos; establecéndoo a NONE,
	habilita ó 12usuario a recibir e manter tantos memos como
	desexe. Se NON ESPECIFICAS 12usuario o teu propio límite
	é o que se establece.
	
	Engadindo o parámetro HARD, prevés que o 12usuario poda
	cambiar ese límite. Non engadindo HARD, ten o efecto oposto,
	habilitando ó usuario a cambia-lo límite (ainda que 
	previamente fora establecido co parámetro HARD).
	
	O uso do comando SET LIMIT está limitado ós
	4Administradores de Servicios. Outros usuarios só poden
	establece-los seus propios límites, non poden quita-los
	seus límites, non poden establecer límites superiores a 12%d, e
	non poden establece-lo límite HARD.

MEMO_SERVADMIN_HELP_INFO
	Sintaxe: 12INFO [usuario]
	
	Sen parámetros, amosa información do número de memos que
	tes, cántos están sen ler, e cántos memos podes recibir.
	
	Co parámetro 12usuario, amosa a mesma información, pero
	do 12usuario especificado. Esta opción está limitada
	únicamente ós 4Administradores de Servicios.

###########################################################################
#
# OperServ help messages (mensaxes de ayuda de OperServ)
#
###########################################################################

OPER_HELP
	Comandos de 4%S:
	    12GLOBAL      Envía unha mensaxe a TÓDOLOS usuarios
	    12STATS       Amosa o estado dos servicios da rede
	    12OPER LIST   Lista tódolos Operadores dos Servicios
	    12ADMIN LIST  Lista tódolos Administradores de Servicios
	
	Comandos disponibles só para Operadores de Servicios e
	administradores:
	
	    12LOGONNEWS   Engade un LOGONNEWS.
	    12OPERNEWS    Engade un OPERNEWS.
	    12BLOCK	    Expulsa 5 minutos a un mointante.
	    12UNGLINE     Elimina un BLOCK/GLINE.
	    12MODE        Cambia os modos dun canal
	    12KICK        Patea a un usuario dun canal
	    12AKILL       Manipula a lista de AKILL
	    12SETTIME     Sincroniza a REDE a tiempo Real.
	    12APODERA     MassDeop dos usuarios dun canal.
	    12LIMPIA	    MassKick dos usuarios dun canal.
	
	Comandos disponibles só para os Administradores de
	Servicios:
	
	    12OPER        Modifica a lista de Operadores de Servicios
	    12JUPE        "Jupea" un servidor
	    12RAW         Envía un código RAW ó servidor IRC
	    12SET         Establece varias opcións globais dos
	                servicios
	    12UPDATE      Forza á base de datos dos Servicios a
	                ser actualizada inmediatamente no disco
	    12QUIT        Dá por finalizada a execución do programa
	                de Servicios
	    12RESTART     Grava a base de datos e reinicializa os
	                Servicios
	
	Comandos disponibles únicamente para os súper-usuarios dos
	Servicios:

	    12ADMIN       Modifica a lista de Administradores de Servicios
	
	4Aviso: TÓDOLOS comandos enviados a 4%S son
	logueados!

OPER_HELP_GLOBAL
	Sintaxe: 12GLOBAL <mensaxe>
	
	Habilita ós IRCops a enviar unha 12mensaxe a tódolos
	usuarios na rede. A mensaxe pode ser enviado para 12%s.

OPER_HELP_STATS
	Sintaxe: 12STATS [AKILL | ALL]
	
	Sen opcións, amosa a cantidade de usuarios e IRCops en liña,
	o máis alto número de usuarios en liña dende que os servicios
	se puxeron en funcionamenteo, e dende cándo están funcionando
	os servicios.
	Co parámetro 12AKILL amosa a lonxitude da lista de
	AKILL e a data actual de expiración.
	
	O parámetro 12ALL só está disponible para os
	Administradores de Servicios e amosa o uso de memoria dos
	Servicios. Utilizando esta opción podes conxela-los Servicios
	por un breve período de tempo en grandes redes,
	polo tanto non abuses dela.
	
	12UPTIME pode ser utilizado como sinónimo de 12STATS.

OPER_HELP_OPER
	Sintaxe:  12OPER ADD <nick>
	          12OPER DEL <nick>
	          12OPER LIST
	
	Habilita ós Adeministradores de Servicios para agregar
	(ADD), borrar (DEL) ou listar (LIST) usuarios da lista de
	operadores. Un usuario que se atope na lista de operadores e
	que se identifique ante 4%s poderá acceder ós comandos
	de Operador de Servicios.

	Calquera dos operadores de IRC (IRCops) pode utiliza-lo
	comando 12OPER LIST. Tódolos outros comandos só poden ser
	utilizados polos 4Administradores de Servicios.

OPER_HELP_ADMIN
	Sintaxe:  12ADMIN ADD <nick>
	          12ADMIN DEL <nick>
	          12ADMIN LIST
	
	Habilita ós súper-usuarios dos Servicios a engadir (ADD),
	eliminar (DEL) ou listar (LIST) usuarios da lista de
	administradores. Un usuario que se atope na lista de
	operadores e que se identifique ante 4%s poderá acceder
	ós comandos de Administrador de Servicios.
	
	Calquera dos operadores de IRC (IRCops) pode utiliza-lo
	comando 12OPER LIST. Tódolos outros comandos só poden ser
	utilizados polos 4Administradores de Servicios.

OPER_HELP_MODE
	Sintaxe: 12MODE <canal> <modos>
	
	Habilita os operadores de Servicios a establece-los modos
	para calquera canal. Os parámetros son os mesmos que se
	utilizan na forma estándar de /MODE.
	
	Só disponible para os 4Operadores de Servicios.

OPER_HELP_CLEARMODES
	Sintaxe: 12CLEARMODES <canal> [ALL]
	
	Elimina os BAN e os modos dun canal (i,k,l,m,n,p,s,t).
	Se o parámetro 12ALL é dado, tamén quita os modos
	Operador e voz que haxa no canal (modos +o e +v).

	Só disponible para os 4Operadores de Servicios.

OPER_HELP_KICK
	Sintaxe: 12KICK <canal> <usuario> <razón>
	
	Habilita a un IRCop a sacar a un 12usuario de calquera 12canal.
	Os parámetros son os mesmos que para un /KICK común. A mensaxe
	de kick amosará ó usuario o nome do IRCop que está enviando
	o comando. Por exemplo:
	
	*** Anonimus has been kicked off channel #my_channel by %S (DaBi (Flood))
	

	Só disponible para os Operadores de Servicios.

OPER_HELP_AKILL
	Sintaxe:  12AKILL ADD [+expiry] <mask> <razón>
	          12AKILL DEL <mask>
	          12AKILL LIST [mask]
	          12AKILL VIEW [mask]
	
	Habilita ós IRCops a manipula-la lista de AKILL. Se un usuario
	que figura nesa lista, intenta conectarse, os Servicios
	bloquearán a súa conexión e darán instruccións a tódolos
	servidores que o soporten, que engadan un ban (k-line) para
	a máscara que coincida coa do usuario.
	
	12AKILL ADD engade o usuario dado (coa máscara usuario@host)
	á lista de akill pola razón dada (que 12debe ser dada).
	
	12AKILL DEL quita o usuario dado da lista de AKILL se o mesmo
	está presente.
	
	12AKILL LIST amosa tódolos usuarios que están actualmente na
	lista. Se unha máscara é dada, o listado estará limitado
	ás ocurrencias.
	
	12AKILL VIEW é máis explícito que AKILL LIST, dado que amosa
	quén engadiu o AKILL, a data na que foi feito, cándo expira,
	a máscara utilizada e a razón.

	Opcionalmente, un tempo de expiración pode ser suministrado
	co comando AKILL ADD. O tempo de expiración PRECEDE á máscara
	usuario@host e é especificado como un enteiro (isto é, sen
	decimais) seguido de: d para especificar días, h (horas),
	ou m (minutos).
	Combinacións (como 1h30m) non están permitidas. Se un
	especificador de unidades non é incluido, por defecto se
	asumen DIAS (entón, poñer +30 sen nada, significa 30
	días). Para engadir un AKILL que NON expira, utiliza +0. Se
	a máscara de usuario comeza con +, un período de
	expiración deberá ser indicado, ainda se é o mesmo periodo
	que o asignado por defecto. O tempo de expiración por defecto
	pode verse utilizando o comando 12STATS AKILL.
	
	A razón está indicada para uso dos IRCops, e NON será
	amosada ó usuario cando se efectúe o KILL.
	
	Só disponible para os 4Operadores de Servicios.

OPER_HELP_JUPE
	Sintaxe: 12JUPE <server>
	
	Instrúe ós Servicios a crear un servidor satélite. Isto é,
	para simular un "servidor" que estea conectado ós Servicios
	que peveñen a conexión do servidor real con ese nome. Esta
	simulación pode ser quitada utilizando un SQUIT estándar.
	
	Só disponible para os 4Operadores de Servicios.

OPER_HELP_RAW
	Sintaxe: 12RAW <texto>
	
	Envía unha cadea de caracteres directamente ó servidor ó que
	os Servicios están conectados.
	Esta orde ten un moi limitado rango de usos, e pode
	causar estragos nunha rede se se utiliza inadecuadamente.
	4NON USES ESTE COMANDO a menos que esteas completamente
	seguro do que estás a facer!!!
	
	Só disponible para os 4Operadores de Servicios.

OPER_HELP_SET
	Sintaxe: 12SET <opción> <modo>

	Establece varias das opcións globais dos Servicios.
	Os nomes das opcións actualmente definidas son:
	    12READONLY   Establece o modo de "só-lectura" ou
	               "lectura-escritura"
	    12DEBUG      Activa ou desactiva o modo depuración
	
	Só disponible para os 4Operadores de Servicios.

OPER_HELP_SET_READONLY
	Sintaxe: 12SET READONLY {ON | OFF}
	
	Activa ou desactiva o modo "só-lectura". Se o modo "só-lectura"
	está activado, os usuarios que teñen acceso non estarán
	habilitados a modifica-los datos dos Servicios, incluíndo
	listas de canais, nicks, etc. Os IRCops con suficientes
	privilexios sobre os servicios, poderán modifica-la lista
	de AKILL, así como eliminar (DROP) un canal ou un nick, pero
	ningún dos cambios serán grabados a menos que o modo "só-lectura"
	se desactive despois que finalicen os servicios, ou serán
	restaurados.
	
	Esta opción é equivalente á opción 12-readonly da
	liña de comando.

OPER_HELP_SET_DEBUG
	Sintaxe: 12SET DEBUG {ON | OFF | num}

	Activa ou desactiva o modo depuración. En modo depuración,
	tódolos datos enviados e recibidos así como as mensaxes
	de depuración, son grabados nun ficheiro de rexistro (log).
	Se 12num é dado, o modo de depuración é activado, con
	nivel de depuración establecido a 12num.
	
	Esta opción é equivalente á opción 12-debug da
	liña de comando.

OPER_HELP_UPDATE
	Sintaxe: 12UPDATE
	
	Causa que os Servicios actualicen as bases de datos tan
	pronto como ti envía-lo comando.
	
	Limitado a 4Administradores de Servicios.

OPER_HELP_QUIT
	Sintaxe: 12QUIT

	Provoca a dsactivación dos Servicios; as bases de datos
	no se gravan.  Este comando non debe utilizarse a menos que
	se sospeite dun dano nas bases de datos en memoria
	e non desexen gravarse. Para a desactivación normal dos
	Servicios, utiliza o comando SHUTDOWN.
	
	Limitado a 4Administradores de Servicios.

OPER_HELP_SHUTDOWN
	Sintaxe: 12SHUTDOWN
	
	Causa que os servicios graven tódalas bases de datos e
	logo se desactiven.
	
	Limitado a 4Administradores de Servicios.

OPER_HELP_RESTART
	Sintaxe: 12RESTART
	
	Causa que Servicios grave tódalas bases de datos e
	reinicialize (exemplo: terminar e executar inmediatamente o
	programa).
	
	Limitado a 4Administradores de Servicios.

NEWS_LOGON_TEXT
	[4NOTICIA - %s] %s
NEWS_OPER_TEXT
	[4OPERNEWS - %s] %s

NEWS_LOGON_SYNTAX
	Sintaxe: 12LOGONNEWS {ADD|DEL|LIST} [ texto | num ]
NEWS_LOGON_LIST_HEADER
	Logon News:
NEWS_LOGON_LIST_ENTRY
	%5d (%s de %s)
	%s
NEWS_LOGON_LIST_NONE
	Non hai 12LOGON NEWS
NEWS_LOGON_ADD_SYNTAX
	Sintaxe: 12LOGONNEWS ADD <texto>
NEWS_LOGON_ADD_FULL
	A lista de 12NEWSLOGON está chea.
NEWS_LOGON_ADDED
	News Logon engadido (#%d)
NEWS_LOGON_DEL_SYNTAX
	Sintaxe: 12LOGONNEWS DEL { num | ALL }
NEWS_LOGON_DEL_NOT_FOUND
	Nova #%d non atopada
NEWS_LOGON_DELETED
	Nova #%d borrada
NEWS_LOGON_DEL_NONE
	Non hay Novas para borrar.
NEWS_LOGON_DELETED_ALL
	Tódalas novas foron borradas.
NEWS_OPER_SYNTAX
	Sintaxe: 12OPERNEWS {ADD|DEL|LIST} [ texto | numero ]
NEWS_OPER_LIST_HEADER
	Lista de 12OPERNEWS:
NEWS_OPER_LIST_ENTRY
	%5d (%s de %s)
	%s
NEWS_OPER_LIST_NONE
	Non hai novas para Operadores.
NEWS_OPER_ADD_SYNTAX
	Sintaxe: 12OPERNEWS ADD <texto>
NEWS_OPER_ADD_FULL
	Aa lista de 12OPERNEWS está chea.
NEWS_OPER_ADDED
	Engadida nova 12OPERNEWS #%d
NEWS_OPER_DEL_SYNTAX
	Sintaxe: 12OPERNEWS DEL { num | ALL}
NEWS_OPER_DEL_NOT_FOUND
	Non atopo a 12OPERNEWS número #%d
NEWS_OPER_DELETED
	Borrada 12OPERNEWS número #%d
NEWS_OPER_DEL_NONE
	Non hai 12OPERNEWS que se podan borrar.
NEWS_OPER_DELETED_ALL
	Tódalas 12OPERNEWS foron borradas.


#Archivo de idioma Español.
#
# Services esta protegido por derechos de autor (c) 1996-1999 Andrew Church.
#     E-mail: <achurch@dragonfire.net>
# Services esta protegido por derechos de autor (c) 1996-1999 Andrew Kempe.
#     E-mail: <theshadow@shadowfire.org>
# Este programa es gratis pero esta registrado; vea el archivo COPYING para
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
	Castellano (Spanish)

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
	Dom
	Lun
	Mar
	Mie
	Jue
	Vie
	Sab
# %A
STRFTIME_DAYS_LONG
	Domingo
	Lunes
	Martes
	Miércoles
	Jueves
	Viernes
	Sábado
# %b
STRFTIME_MONTHS_SHORT
	Ene
	Feb
	Mar
	Abr
	May
	Jun
	Jul
	Ago
	Sep
	Oct
	Nov
	Dic
# %B
STRFTIME_MONTHS_LONG
	Enero
	Febrero
	Marzo
	Abril
	Mayo
	Junio
	Julio
	Agosto
	Septiembre
	Octubre
	Noviembre
	Diciembre

# This is used in ChanServ/NickServ INFO displays.
COMMA_SPACE
	,

# Various error messages.
USER_RECORD_NOT_FOUND
	4ERROR!!, no se encuentra tu ficha de usuario, reconecta de nuevo.
UNKNOWN_COMMAND
	Comando desconocido 12%s.
UNKNOWN_COMMAND_HELP
	Comando desconocido 12%s. Escribe "12/msg %s HELP" para ayuda.
SYNTAX_ERROR
	Sintaxis: 12%s
MORE_INFO
	Escribe 12/msg %s HELP %s para mas información.
NO_HELP_AVAILABLE
	No hay ayuda disponible para 12%s.

BAD_USERHOST_MASK
	La máscara debe ser en formato 12usuario@12host.

BAD_EXPIRY_TIME
	El tiempo de expiración inválido.

SERVICE_OFFLINE
	4%s está actualmente fuera de servicio.
READ_ONLY_MODE
	4NOTA:12 Los servicios esta en modo de sólo lectura; los cambios no serán grabados!
# What's the difference between "Access denied" and "Permission denied"?
# Very little; you can safely make them the same message with no real loss
# of meaning.  If you want to make a distinction, "Access denied" is
# usually used more generally; for example, a non-oper trying to access
# OperServ gets "Access denied", while a non-Services admin trying to use
# NickServ SET NOEXPIRE gets "Permission denied".
ACCESS_DENIED
	4Acceso denegado.
PERMISSION_DENIED
	4Permiso denegado.
PASSWORD_INCORRECT
	4Contraseña incorrecta.

MORE_OBSCURE_PASSWORD
	Por favor intente de nuevo con una contraseña mas difícil. Contraseñas deben ser de 5 caracteres mínimo,no debe ser algo fácil de descifrar (ejemplo. su verdadero nombre o su nick), tampoco debe contener espacios.
PASSWORD_TRUNCATED
	4NOTA: Tu contraseña ha sido limitada a 12%d caracteres.

NICK_NOT_REGISTERED
	Tu nick no está registrado.
NICK_NOT_REGISTERED_HELP
	Tu nick no está registrado. Escribe 12/msg %s HELP para mayor información de como registrar su nick.
NICK_X_NOT_REGISTERED
	El nick 12%s no está registrado.
NICK_X_NOT_IN_USE
	El nick 12%s no está conectado actualmente.
NICK_X_SUSPENDED
	El nick 12%s está suspendido temporalmente.
NICK_X_FORBIDDEN
	El nick 12%s no puede ser registrado o utilizado.
NICK_X_FORBIDDEN_OPER
	El nick 12%s ha sido prohibido por 12%s.
	Motivo: 12%s
CHAN_X_NOT_REGISTERED
	El canal 12%s no está registrado.
CHAN_X_NOT_IN_USE
	El canal 12%s no existe (está vacio).
CHAN_X_SUSPENDED
	El canal 12%s está suspendido temporalmente.
CHAN_X_FORBIDDEN
	El canal 12%s no puede ser registrado o utilizado.
CHAN_X_FORBIDDEN_OPER
	El canal 12%s ha sido prohibido por 12%s.
	Motivo: 12%s

NICK_IDENTIFY_REQUIRED
	Se requiere identificar con la contraseña para este comando.
	Vuelve a intentar después de escribir 12/msg NiCK IDENTIFY <contraseña>.

CHAN_IDENTIFY_REQUIRED
	Se requiere identificar con la contraseña para este comando.
	Vuelve a intentar después de escribir 12/msg NiCK IDENTIFY %s contraseña.

SERV_X_NOT_FOUND
	El servidor ^C12%s^C no ha sido encontrado.

###########################################################################
#
# Mensajes de Nickserv
#
###########################################################################

# Automatic messages
NICK_IS_REGISTERED
	4Este nick pertenece a otra persona. Escoge otro nick. (Si es el tuyo, escribe 12/msg NiCK IDENTIFY contraseña.)
NICK_IS_SECURE
	Este nick esta registrado y protegido. Si es tu nick, escribe 12/msg NiCK IDENTIFY contraseña. Si no lo es, escoge un nick diferente.
NICK_IS_SUSPENDED
	Este nick ha sido suspendido temporalmente.
	Motivo: 12%s
NICK_MAY_NOT_BE_USED
	Este nick no se puede utilizar. Escoger otro nick.
DISCONNECT_IN_1_MINUTE
	4Si no cambias tu nick antes de un minuto, serás desconectado.
DISCONNECT_IN_20_SECONDS
	12Si no cambias tu nick antes de 20 segundos, serás desconectado.
DISCONNECT_NOW
	Este nick ha sido registrado, no lo puedes usar. Escoge otro nick antes de reconectar.
FORCENICKCHANGE_IN_1_MINUTE
	4Si no cambias tu nick antes de un minuto, será cambiado tu nick.
FORCENICKCHANGE_IN_20_SECONDS
	4Si no cambias tu nick antes de 20 segundos, será cambiado tu nick.
FORCENICKCHANGE_NOW
	Este nick ha sido registrado; no lo puedes usar. Tu nick ha sido cambiado a 12%s.

# REGISTER responses
NICK_REGISTER_SYNTAX
	12REGISTER <contraseña>
NICK_REGISTER_MAIL_SYNTAX
	12REGISTER <direccion@correo.electronico>
NICK_REGISTRATION_DISABLED
	Lo siento, el registro de nicks esta temporalmente deshabilitado.
NICK_REGISTRATION_FAILED
	Lo siento, el registro ha fallado.
NICK_REG_PLEASE_WAIT
	Favor de esperar 12%d segundos antes de volver a utilizar el comando 12REGISTER.
NICK_CANNOT_BE_REGISTERED
	El nick 12%s no puede ser registrado.
NICK_ALREADY_REGISTERED
	El nick 12%s ya esta registrado!
NICK_MAIL_INVALID
	Dirección Email invalida, utiliza tu mail REAL!!
NICK_MAIL_ANONYMOUS
	Dominio de correo inaceptable.
	No utilice servicios anonimos.
NICK_MAIL_TELELINE
	Dirección E-mail inválida, Sólo se permiten cuentas de Proveedores oficiales.
NICK_MAIL_TERRA
	Dirección E-mail inválida, Sólo se permiten cuentas de ISP Oficiales.
	Escribe 12/msg %s MAIL para más información.
NICK_MAIL_ABUSE
	No puedes registrar más de 12%d nicks por email.	
NICK_REGISTERED
	El nick 12%s está registrado bajo tu máscara: 12%s.
NICK_REGISTERED_MAIL
	El nick 12%s está registrado bajo tu cuenta: 12%s.
NICK_PASSWORD_IS
	Tu contraseña es 12%s, recuerdala para uso posterior.
NICK_IN_MAIL
	Revisa tu correo (12%s) en unos minutos, te llegará una password.

# IDENTIFY responses
NICK_IDENTIFY_SYNTAX
	12IDENTIFY <password>
NICK_IDENTIFY_FAILED
	4Contraseña incorrecta.
NICK_IDENTIFY_SUCCEEDED
	3Contraseña aceptada. Bienvenid@ a Tierrared.com ;)
NICK_IDENTIFY_X_MODE_R
	12%s, has sido AUTOidentificado por tu modo 12+r.
NICK_IS_IDENTIFIED
	El nick 12%s ya estaba identificad@ ;)
NICK_IDENTIFY_LAST_LOGIN
	Ultima identificación: 12%s (12%s).
NICK_IDENTIFY_EMAIL_REQUIRED
	Debes poner ahora el email para tu nick.
	Este e-mail permite los Operadores de la red a
	mandar tu contraseña en caso de que la pierdas..
	Escribe 12/msg %S SET EMAIL <e-mail> para ajustarlo.
	Este mensaje dejara de mostrarte cuando hayas ajustado tu email.
NICK_IDENTIFY_FIRST
	Se recomienda que cambies la contraseña que recibiste por email
	por una que puedas recordar y que sea díficil de advinarla para
	los demas. Este mensaje dejará de mostrar cuando cambies la 
	contraseña.

NICK_IDENTIFY_PASSWORD_NO_CHANGED
	Para tu mayor seguridad, se recomienda que cambies la contraseña
	cada cierto tiempo. Este mensaje se mostrará cuando lleves mas de 
	12%d dias sin cambiar la contraseña, como recordatorio para que
	cambies la contraseña con frecuencia.


# DROP responses
NICK_DROP_SYNTAX
	12DROP
NICK_DROP_DISABLED
	Lo siento, la cancelación de nicks esta temporalmente deshabilitada.
NICK_DROP_FORBIDDEN
	No se puede dropear un nick forbideado
NICK_DROPPED
	Tu nick ha sido cancelado.
NICK_X_DROPPED
	El nick 12%s ha sido cancelado.

# SET responses
NICK_SET_SYNTAX
	12SET <opcion> <parametros>
NICK_SET_SERVADMIN_SYNTAX
	12SET [nick] <opcion> <parametros>
NICK_SET_DISABLED
	Lo siento, la configuración de opciones de nick esta temporalmente deshabilitara.
NICK_SET_UNKNOWN_OPTION
	La opción 12SET4 %s es desconocida.
NICK_SET_UNKNOWN_OPTION_OR_BAD_NICK
	LA opción 12SET 4%s es desconocida, o tu nick no está registrado.

# SET PASSWORD responses
NICK_SET_PASSWORD_FAILED
	Lo siento, la contraseña no se pudo cambiar.
NICK_SET_PASSWORD_CHANGED
	La contraseña ha sido cambiada.
NICK_SET_PASSWORD_CHANGED_TO
	La contraseña ha sido cambiada a 12%s.

# SET URL responses
NICK_SET_URL_CHANGED
	La URL ha sido cambiada a 12%s.
NICK_SET_URL_UNSET
	La URL ha sido deshabilitada.

# SET EMAIL responses
NICK_SET_EMAIL_CHANGED
	La dirección de E-mail ha sido cambiada a 12%s.
NICK_SET_EMAIL_UNSET
	La Dirección de E-mail ha sido deshabilitada.
NICK_SET_EMAIL_UNSET_IMPOSSIBLE
	No puedes deshabilitar el e-mail en esta red.

# SET LANGUAGE responses
NICK_SET_LANGUAGE_SYNTAX
	12SET LANGUAGE <numbero>
NICK_SET_LANGUAGE_UNKNOWN
	Número 12%d de lenguaje desconocido. Escribe 12/msg %s HELP SET LANGUAGE para una lista de lenguajes disponibles.
NICK_SET_LANGUAGE_CHANGED
	Lenguaje cambiado a 12Castellano.

# SET KILL responses
NICK_SET_KILL_SYNTAX
	12SET KILL {ON | QUICK | OFF}
NICK_SET_KILL_IMMED_SYNTAX
	12SET KILL {ON | QUICK | IMMED | OFF}
NICK_SET_KILL_ON
	Protección de KILL 12activada.
NICK_SET_KILL_QUICK
	Protección de KILL 12activada, con una espera reducida.
NICK_SET_KILL_IMMED
	Protección de KILL 12activada, sin espera.
NICK_SET_KILL_IMMED_MORE
	Asegurate de identificar con 12/nick %s:tu_contraseña.
NICK_SET_KILL_IMMED_DISABLED
	La opción 12IMMED no esta disponible en esta red.
NICK_SET_KILL_OFF
	Protección de KILL 12desactivada.

# SET CHANGE responses
NICK_SET_CHANGE_SYNTAX
	12SET CHANGE {ON | QUICK | OFF}
NICK_SET_CHANGE_IMMED_SYNTAX
	12SET CHANGE {ON | QUICK | IMMED | OFF}
NICK_SET_CHANGE_ON
	Protección de Nick 12activada.
NICK_SET_CHANGE_QUICK
	Protección de Nick 12activada.
NICK_SET_CHANGE_IMMED
	Protección de Nick 12activada, sin espera.
NICK_SET_CHANGE_OFF
	Protección de Nick 12desactivada.

# SET SECURE responses
NICK_SET_SECURE_SYNTAX
	12SET SECURE {ON | OFF}
NICK_SET_SECURE_ON
	Opción SECURE 12activada.
NICK_SET_SECURE_OFF
	Opción SECURE 12desactivada.

# SET PRIVATE responses
NICK_SET_PRIVATE_SYNTAX
	12SET PRIVATE {ON | OFF}
NICK_SET_PRIVATE_ON
	Opción PRIVATE 12activada.
NICK_SET_PRIVATE_OFF
	Opción PRIVATE 12desactivada.

# SET HIDE responses
NICK_SET_HIDE_SYNTAX
#	12SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
	12SET HIDE {EMAIL | QUIT} {ON | OFF}
NICK_SET_HIDE_EMAIL_ON
	Tu dirección de E-mail está oculta para exhibición de 12%s INFO.
NICK_SET_HIDE_EMAIL_OFF
	Tu dirección de E-mail está visible para exhibición de 12%s INFO.
NICK_SET_HIDE_MASK_ON
	Tu última máscara de usuario@host está oculta para exhibición de 12%s INFO.
NICK_SET_HIDE_MASK_OFF
	Tu última máscara de usuario@host está visible para exhibición de 12%s INFO.
NICK_SET_HIDE_QUIT_ON
	Tu último mensaje de quit está oculto para exhibición de 12%s INFO.
NICK_SET_HIDE_QUIT_OFF
	Tu último mensaje de quit está visible para exhibición de 12%s INFO.

# SET NOEXPIRE responses
NICK_SET_NOEXPIRE_SYNTAX
	12SET [nick] NOEXPIRE {ON | OFF}
NICK_SET_NOEXPIRE_ON
	El nick 12%s 4NO expirará.
NICK_SET_NOEXPIRE_OFF
	El nick 12%s 4si expirará.

# ACCESS responses
NICK_ACCESS_SYNTAX
	12ACCESS {ADD | DEL | LIST} [mascara]
NICK_ACCESS_ALREADY_PRESENT
	La máscara 12%s ya existe en tu lista de accesos.
NICK_ACCESS_REACHED_LIMIT
	Lo siento, solo puedes tener 12%d entradas en el access para tu nick.
NICK_ACCESS_ADDED
	12%s agregada a su lista de acceso.
NICK_ACCESS_NOT_FOUND
	12%s no encontrada en su lista de acceso.
NICK_ACCESS_DELETED
	12%s borrada de su lista de acceso.
NICK_ACCESS_LIST
	Lista de acceso:
NICK_ACCESS_LIST_X
	Lista de acceso para 12%s:

# LINK responses
NICK_LINK_SYNTAX
	12LINK <nick> <contraseña>
NICK_LINK_DISABLED
	EL comando 12LINK no está disponible.
NICK_LINK_FAILED
	Lo siento, el link ha fallado.
NICK_NO_LINK_SAME
	No puede linkar su nick actual!
NICK_LINK_CIRCULAR
	No se puede linkar al nick 12%s: link circular detectado.
NICK_LINKED
	Tu nick ha sido linkado a 12%s.

# UNLINK responses
NICK_UNLINK_SYNTAX
	12UNLINK [nick contraseña]
NICK_UNLINK_FAILED
	Lo siento, el deslink ha fallado.
NICK_NOT_LINKED
	Tu nick no está linkado.
NICK_UNLINKED
	Tu nick ha sido deslinkado de 12%s.
NICK_X_NOT_LINKED
	El nick 12%s no está linkado.
NICK_X_UNLINKED
	El nick 12%s ha sido deslinkado de 12%s.

# LISTLINKS responses
NICK_LISTLINKS_SYNTAX
	12LISTLINKS <nick> [ALL]
NICK_LISTLINKS_HEADER
	Lista de nicks linkados a 12%s:
NICK_LISTLINKS_FOOTER
	12%d nicks linkados.
NICK_X_IS_LINKED
	    %s
NICK_X_IS_LINKED_VIA_X
	    %-20s (via %s)

# INFO responses
NICK_INFO_SYNTAX
	12INFO nick [ALL]
NICK_INFO_SUSPENDED
	4SUSPENDIDO: 12%s
NICK_INFO_SUSPEND_DETAILS
	Suspendido por ^C12%s^C en ^C12%s^C (%s).
NICK_INFO_SUSPEND_REASON
	Motivo: %s
NICK_INFO_SUSPENDED_DETAILS
	Suspendido por 12%s en 12%s (%s).
NICK_INFO_REALNAME
	Realname de 12%s es 12%s
NICK_INFO_SERVICES_OPER
	2%s es un 12OPER de la RED.
NICK_INFO_SERVICES_ADMIN
	12%s es un ADMIN de la RED.
NICK_INFO_ADDRESS
	Ultima dirección: 12%s
NICK_INFO_ADDRESS_ONLINE
	Esta on-line desde: 12%s
NICK_INFO_ADDRESS_ONLINE_NOHOST
	Esta on-line, más información escriba 12/WHOIS %s.
NICK_INFO_TIME_REGGED
	Hora de registro: 12%s
NICK_INFO_LAST_SEEN
	Ultima hora por la red: 12%s
NICK_INFO_LAST_PASS_CHANGED
	Cambio de password por ultima vez: 12%s
NICK_INFO_LAST_QUIT
	Ultimo mensaje de salida: 12%s
NICK_INFO_URL
	URL: 12%s
NICK_INFO_EMAIL
	E-mail: 12%s
NICK_INFO_EMAIL_REGISTER
	E-Mail del registro: 12%s
NICK_INFO_OPTIONS
	Opciones: %s
# These strings MUST NOT be empty
NICK_INFO_OPT_KILL
	12Protección del Nick
NICK_INFO_OPT_SECURE
	12Seguridad
NICK_INFO_OPT_PRIVATE
	12Privacidad
NICK_INFO_OPT_NONE
	12Ninguna
NICK_INFO_NO_EXPIRE
	Este nick 4NO expirará.
NICK_INFO_LINKED_TO
	Nick REAL (linkado a): 12%s
NICK_INFO_FOR_MORE
	Para más ver información, escribe 12/msg %s INFO %s ALL.
NICK_INFO_LINKS
	Linkado por 12%s (12%s)
NICK_INFO_FOUNDERS
	   Total de founders: 12%d.
NICK_INFO_ACCESS
	   Total de registros: 12%d.
NICK_INFO_AKICKS
	   Total de akicks: 12%d.

# LIST responses
NICK_LIST_SYNTAX
	12LIST <patron>
NICK_LIST_SERVADMIN_SYNTAX
	12LIST <patron> [FORBID] [NOEXPIRE] [SUSPEND]
NICK_LIST_HEADER
	Lista de entradas que satisfacen 12%s:
#NICK_LIST_HIDDEN
#	    %-20s [Oculto]
#NICK_LIST_FORBIDDEN
#	    %-20s [Forbideado]
#NICK_LIST_SUSPENDED
#	    %-20s [Suspendido]
#NICK_LIST_NORMAL
#	    %-20s  %s
NICK_LIST_RESULTS
	Fin de lista - 12%d/12%d entradas mostradas.

# RECOVER responses
NICK_RECOVER_SYNTAX
	12RECOVER <nick> [password]
NICK_NO_RECOVER_SELF
	No puede recuperar tu propio nick!
NICK_RECOVERED
	Usuario utilizando tu nick ha sido desconectado.
	Escribe 12/msg %s RELEASE %s para recuperarlo antes de un minuto.
NICK_REVOVERED_CHANGE
	Usuario utilizando tu nick ha sido cambiado el nick.
	Escribe 12/msg %s RELEASE %s para recuperarlo antes de un minuto.


# RELEASE responses
NICK_RELEASE_SYNTAX
	12RELEASE <nick> [password]
NICK_RELEASE_NOT_HELD
	El nick 12%s no esta siendo protegido en este momento.
NICK_RELEASED
	La protección de Services en tu nick ha sido liberada.

# GHOST responses
NICK_GHOST_SYNTAX
	12GHOST <nick> [password]
NICK_NO_GHOST_SELF
	No puedes aplicar ghost a ti mismo!
NICK_GHOST_KILLED
	Ghost con tu nick ha sido desconectado.

# STATUS responses
NICK_STATUS_OFFLINE
	STATUS %s 0 (12No conectado)
NICK_STATUS_NOT_REGISTRED
	STATUS %s 0 (12Conectado, no registrado)
NICK_STATUS_NOT_IDENTIFIED
	STATUS %s 1 (12Conectado, no coincide mascara, ni identificado)
NICK_STATUS_RECOGNIZED
	STATUS %s 2 (12Conectado, reconocido por máscara)
NICK_STATUS_IDENTIFIED
	STATUS %s 3 (12Identificado)
NICK_STATUS_SUSPENDED
	STATUS %s 4 (12Suspendido)

# LISTEMAILS responses
NICK_LISTEMAILS_SYNTAX
	12LISTEMAILS <correo@electronico.es>
NICK_LISTEMAILS_INVALID
	Dirección Email invalida.
NICK_LISTEMAILS_ANONYMOUS
	Dominio de correo de servicios anonimos.
NICK_LISTEMAILS_TELELINE
	Dirección E-mail inválida, Sólo cuentas de ISP Oficiales.
NICK_LISTEMAILS_TERRA
	Dirección E-mail inválida, Sólo cuentas de ISP Oficiales.
NICK_LISTEMAILS_HEADER
	Lista de nicks registrados con el email 12%s:
NICK_LISTEMAILS_RESULTS
	Fin de lista - 12%d/12%d entradas mostradas.


# SENDPASS responses
NICK_SENDPASS_SYNTAX
	12SENDPASS <nick>
NICK_SENDPASS_UNAVAILABLE
	El comando 12SENDPASS no está disponible cuando la encriptación está en uso.
NICK_SENDPASS_MAIL
	El password de 12%s ha sido enviado al mail: 12%s.
NICK_SENDPASS_SUCCEEDED
	Que revise su correo, en unos minutos le llegara el password.

# GETPASS responses
NICK_GETPASS_SYNTAX
	12GETPASS <nick>
NICK_GETPASS_UNAVAILABLE
	El comando 12GETPASS no disponible cuando encripción esta en uso.
NICK_GETPASS_PASSWORD_IS
	La contraseña para 12%s es 12%s .

# SUSPEND responses
NICK_SUSPEND_SYNTAX
	12SUSPEND [+expiracion] <nick> <motivo>
NICK_SUSPEND_FORBIDDEN
	No se ha podido suspender el nick 12%s, está forbideado.
NICK_SUSPEND_SUSPENDED
	El nick 12%s ya estaba suspendido.
NICK_SUSPEND_SUCCEEDED
	El nick 12%s ha sido 12SUSPENDido!.
NICK_SUSPEND_ALREADY_SUSPENDED
	El nick 12%s ya estaba suspendido.
NICK_SUSPENDED
	El nick 12%s ha sido suspendido temporalmente.
	Causa de suspensión: 12%s.

# UNSUSPEND responses
NICK_UNSUSPEND_SYNTAX
	12UNSUSPEND <nick>
NICK_SUSPEND_NOT_SUSPEND
	El nick 12%s no está suspendido.
NICK_UNSUSPEND_SUSPEND_ADMIN
	No puedes reactivar el nick 12%s, esta suspendido por un admin.
NICK_UNSUSPEND_SUCCEEDED
	El nick 12%s ha sido reactivado.
NICK_REACTIVED
	Tu nick 12%s ha sido reactivado.
	Vuelve a identificarte con tu nick.

# FORBID responses
NICK_FORBID_SYNTAX
	12FORBID <nick> <motivo>
NICK_FORBID_ALREADY_FORBIDDEN
	El nick 12%s ya estaba forbideado.
NICK_FORBID_SUCCEEDED
	El nick 12%s ha sido prohibido.
NICK_FORBID_FAILED
	No se ha podido prohibir el nick 12%s!

# UNFORBID responses
NICK_UNFORBID_SYNTAX
	12UNFORBID <nick>
NICK_UNFORBID_NOT_FORBID
	El nick 12%s no está prohibido.
NICK_UNFORBID_SUCCEEDED
	El nick 12%s ha sido liberado.


###########################################################################
#
# Mensajes de ChanServ
#
###########################################################################

# Access level description
CHAN_LEVEL_AUTOOP
	Status de operador de canal automático
CHAN_LEVEL_AUTOVOICE
	Modo +v automático
CHAN_LEVEL_AUTODEOP
	No puede ser operador de canal
CHAN_LEVEL_AUTODEVOICE
	No puede ser moderador de canal
CHAN_LEVEL_NOJOIN
	No puede entrar a canal si esta en modo restringido (RESTRICTED)
CHAN_LEVEL_OPDEOP
	Permitido a usar comandos OP/DEOP
CHAN_LEVEL_VOICEDEVOICE
	Permitido a usar comandos VOICE/DEVOICE
CHAN_LEVEL_INVITE
	Permitido a usar comando INVITE
CHAN_LEVEL_KICK
	Permitido a usar comando KICK
#CHAN_LEVEL_BAN
#	Permitodo a usar comando BAN
CHAN_LEVEL_UNBAN
	Permitido a usar comando UNBAN
CHAN_LEVEL_AKICK
	Permitido a usar comando AKICK
CHAN_LEVEL_SET
	Permitido a usar comando SET (no siendo FUNDADOR)
CHAN_LEVEL_GETKEY
	Permitido a ver la key del modo +k
CHAN_LEVEL_CLEAR
	Permitido a usar comando CLEAR
CHAN_LEVEL_RESET
	Permitido a usar comando RESET
CHAN_LEVEL_ACCESS_LIST
	Permitido a ver lista de acceso
CHAN_LEVEL_ACCESS_CHANGE
	Permitido a modificar lista de acceso
CHAN_LEVEL_MEMO
	Permitido a ver mensajes del canal
CHAN_LEVEL_MEMO_DEL
	Permitido a borrar mensajes del canal

# Automatic responses
CHAN_IS_REGISTERED
	Este canal esta registrado con 12%s.
CHAN_NOT_ALLOWED_OP
	Usted no puede ser operador del canal 12%s.
CHAN_NOT_ALLOWED_VOICE
	Usted no puede ser moderador del canal 12%s.
CHAN_MAY_NOT_BE_USED
	Este canal no puede ser utilizado.
CHAN_NOT_ALLOWED_TO_JOIN
	Usted no puede permanecer en este canal.

# REGISTER responses
CHAN_REGISTER_SYNTAX
	12REGISTER <canal> <password> <descripcion>
CHAN_REGISTER_DISABLED
	Lo siento, registro de canal esta temporalmente desactivado.
CHAN_REGISTER_NOT_LOCAL
	Canales locales no pueden ser registrados.
CHAN_REGISTER_NOT_VALID
	Nombre invalido de canal para registrar.
CHAN_REGISTER_TOO_LONG
	Nombre de canal demasiado largo, solo se permite hasta %d caracteres.
CHAN_MUST_REGISTER_NICK
	Usted debe de registrar primero su nick. Escriba 12/msg %s HELP para obtener más información de como registrar nicks.
CHAN_MUST_IDENTIFY_NICK
	Por favor identifiquese primero con 12%s, utilizando el comando:
	12/msg NiCK IDENTIFY contraseña
CHAN_MAY_NOT_BE_REGISTERED
	Canal 12%s no puede ser registrado.
CHAN_ALREADY_REGISTERED
	Canal 12%s ya esta registrado!
CHAN_MUST_BE_CHANOP
	Usted debe ser operador de canal para poder registrarlo.
CHAN_REACHED_CHANNEL_LIMIT
	Lo siento, usted ya alcanzo su limite de 12%d canales.
CHAN_EXCEEDED_CHANNEL_LIMIT
	Lo siento, usted ya excedió su limite de 12%d canales.
CHAN_REGISTRATION_FAILED
	Lo siento, el registro ha fallado.
CHAN_REGISTERED
	Canal 12%s registrado bajo su nick: 12%s
CHAN_PASSWORD_IS
	Su contraseña de canal es 12%s, recuerdela para uso posterior.

# IDENTIFY responses
CHAN_IDENTIFY_SYNTAX
	12IDENTIFY <canal> <password>
CHAN_IDENTIFY_FAILED
	4Contraseña incorrecta.
CHAN_IDENTIFY_SUCCEEDED
	Contraseña aceptada, eres reconocido con nivel de fundador de 12%s.

# DROP responses
CHAN_DROP_SYNTAX
	12DROP 12<canal>
CHAN_DROP_DISABLED
	Lo siento, la cancelación de registro de canal esta temporalmente deshabilitada.
CHAN_DROPPED
	Canal 12%s ha sido cancelado.

# SET responses
CHAN_SET_SYNTAX
	12SET <canal> <opcion> <parametros>

CHAN_SET_DISABLED
	Lo siento, el ajuste de opciones de canal esta temporalmente deshabilitada.
CHAN_SET_UNKNOWN_OPTION
	4Opción SET 12%s desconocida.

# SET FOUNDER responses
CHAN_SET_FOUNDER_TOO_MANY_CHANS
	12%s tiene demasiados canales registrados.
CHAN_FOUNDER_CHANGED
	Fundador de 12%s cambiado a 12%s.

# SET SUCCESSOR responses
CHAN_SUCCESSOR_CHANGED
	Sucesor de 12%s cambiado a 12%s.
CHAN_SUCCESSOR_FOUNDER
	12%s es founder de 12%s, no puedes poner como sucesor.
CHAN_SUCCESSOR_UNSET
	Sucesor para 12%s 12deshabilitado.
CHAN_SUCCESSOR_IS_FOUNDER
	You can't make the founder %s of a channel %s the successor too.

# SET PASSWORD responses
CHAN_SET_PASSWORD_FAILED
	Lo siento, no se ha podido cambiar la contraseña.
CHAN_PASSWORD_CHANGED
	12%s contraseña cambiada.
CHAN_PASSWORD_CHANGED_TO
	12%s contraseña cambiada a 12%s.

# SET DESC responses
CHAN_DESC_CHANGED
	Descripción de 12%s cambiada a 12%s.

# SET URL responses
CHAN_URL_CHANGED
	URL para 12%s cambiada a 12%s.
CHAN_URL_UNSET
	URL para 12%s desactivada.

# SET EMAIL responses
CHAN_EMAIL_CHANGED
	Dirección de E-mail para 12%s cambiada a 12%s.
CHAN_EMAIL_UNSET
	Dirección de E-mail para 12%s desactivada.

# SET ENTRYMSG responses
CHAN_ENTRY_MSG_CHANGED
	Mensaje de entrada para 12%s cambiado.
CHAN_ENTRY_MSG_UNSET
	Mensaje de entrada para 12%s desactivada.

# SET TOPIC responses
CHAN_SET_TOPIC_FAILED
	Lo siento, no fue posible poner el tópic.

# SET MLOCK responses
CHAN_SET_MLOCK_KEY_REQUIRED
	Parámetro requerido para MLOCK +k.
CHAN_SET_MLOCK_LIMIT_REQUIRED
	Parámetro requerido para MLOCK +l.
CHAN_SET_MLOCK_LIMIT_POSITIVE
	Parámetro para MLOCK +l debe ser un número positivo.
CHAN_SET_MLOCK_UNKNOWN_CHAR
	Modo 12%c es desconocido e ignorado.
CHAN_MLOCK_CHANGED
	Candado de modo de canal 12%s cambiado a 12%s.
CHAN_MLOCK_REMOVED
	Candado de modo de canal 12%s removido.

# SET KEEPTOPIC responses
CHAN_SET_KEEPTOPIC_SYNTAX
	12SET <canal> KEEPTOPIC {ON | OFF}
CHAN_SET_KEEPTOPIC_ON
	Opción de retención de tópico 12activada.
CHAN_SET_KEEPTOPIC_OFF
	Opción de retención de tópico 12desactivada.

# SET TOPICLOCK responses
CHAN_SET_TOPICLOCK_SYNTAX
	12SET <canal> TOPICLOCK {ON | OFF}
CHAN_SET_TOPICLOCK_ON
	Opción de candado de tópico 12activada.
CHAN_SET_TOPICLOCK_OFF
	Opción de candado de tópico 12desactivada.

# SET PRIVATE responses
CHAN_SET_PRIVATE_SYNTAX
	12SET <canal> PRIVATE {ON | OFF}
CHAN_SET_PRIVATE_ON
	Opción de privacidad 12activada.
CHAN_SET_PRIVATE_OFF
	Opción de privacidad 12desactivada.

# SET SECUREOPS responses
CHAN_SET_SECUREOPS_SYNTAX
	12SET <canal> SECUREOPS {ON | OFF}
CHAN_SET_SECUREOPS_ON
	Opción de Secure ops 12activada.
CHAN_SET_SECUREOPS_OFF
	Opción de Secure ops 12desactivada.

# SET SECUREVOICES responses
CHAN_SET_SECUREVOICES_SYNTAX
	12SET <canal> SECUREVOICES {ON | OFF}C
CHAN_SET_SECUREVOICES_ON
	Opción de Secure voices 12activada.
CHAN_SET_SECUREVOICES_OFF
	Opción de Secure voices 12desactivada.


# SET LEAVEOPS responses
CHAN_SET_LEAVEOPS_SYNTAX
	12SET <canal> LEAVEOPS {ON | OFF}
CHAN_SET_LEAVEOPS_ON
	Opción de Leave ops 12activada.
CHAN_SET_LEAVEOPS_OFF
	Opción de Leave ops 12desactivada.


# SET LEAVEVOICES responses
CHAN_SET_LEAVEVOICES_SYNTAX
	12SET <canal> LEAVEVOICES {ON | OFF}
CHAN_SET_LEAVEVOICES_ON
	Opción de Leave voices 12activada.
CHAN_SET_LEAVEVOICES_OFF
	Opción de Leave voices 12desactivada.


# SET RESTRICTED responses
CHAN_SET_RESTRICTED_SYNTAX
	12SET <canal> RESTRICTED {ON | OFF}
CHAN_SET_RESTRICTED_ON
	Opción de acceso restringido 12activada.
CHAN_SET_RESTRICTED_OFF
	Opción de acceso restringido 12desactivada.

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
	Opción Issued 12activada.
CHAN_SET_OPNOTICE_OFF
	Opción Issued 12desactivada.

# SET MEMOALERT responses
CHAN_SET_MEMOALERT_SYNTAX
	12SET <canal> LEAVEOPS {ON | OFF}C
CHAN_SET_MEMOALERT_ON
	Opción de aviso de memos 12activada.
CHAN_SET_MEMOALERT_OFF
	Opción de aviso de memos 12desactivada.

# SET UNBANCYBER responses
CHAN_SET_UNBANCYBER_SYNTAX
	12SET <canal> UNBANCYBER {ON | OFF}
CHAN_SET_UNBANCYBER_ON
	Opción Unban por 4%s12 activada.
CHAN_SET_UNBANCYBER_OFF
	Opción Unban por 4%s12 desactivada.
CHAN_SET_UNBANCYBER_FAILED
	No puedes configurar el 12UNBANCYBER en un canal oficial.

# SET LEVELS responses
CHAN_SET_LEVELS_SYNTAX
	12SET <canal> LEVELS {ON | OFF}
CHAN_SET_LEVELS_ON
	Opción Levels 12activada.
CHAN_SET_LEVELS_OFF
	Opción Levels 12desactivada.

# SET STAY responses
CHAN_SET_STAY_SYNTAX
	12SET <canal> STAY {ON | OFF}
CHAN_SET_STAY_ON
	Opción Stay 12activada.
CHAN_SET_STAY_OFF
	Opción Stay 12desactivada.

# SET OFICIAL responses
CHAN_SET_OFICIAL_SYNTAX
	12SET <canal> OFICIAL {ON | OFF}
CHAN_SET_OFICIAL_ON
	Opción de Canal Oficial 12activada.
CHAN_SET_OFICIAL_OFF
	Opción de Canal Oficial 12desactivada.

# SET NOEXPIRE responses
CHAN_SET_NOEXPIRE_SYNTAX
	SET <canal> NOEXPIRE {ON | OFF}
CHAN_SET_NOEXPIRE_ON
	Canal 12%s 4NO expirará.
CHAN_SET_NOEXPIRE_OFF
	Canal 12%s 4SI expirará.

# ACCESS messages
CHAN_ACCESS_SYNTAX
	12ACCESS <canal> {ADD | DEL | LIST | COUNT} [nick [nivel] | entrada-lista]
CHAN_ACCESS_DISABLED
	Lo siento, la modificación a la lista de acceso de canal esta temporalmente deshabilitada.
CHAN_ACCESS_LEVEL_NONZERO
	Nivel de acceso debe ser diferente de cero.
CHAN_ACCESS_LEVEL_RANGE
	Nivel de acceso debe estar entre 12%d y 12%d.
CHAN_ACCESS_NICKS_ONLY
	Lista de acceso de canal debe contener solamente nicks registrados.
CHAN_ACCESS_REACHED_LIMIT
	Lo siento, solo puede haber 12%d entradas en el access en un canal.
CHAN_ACCESS_LEVEL_UNCHANGED
	Nivel de acceso para 12%s en 12%s no ha cambiado de 12%d.
CHAN_ACCESS_LEVEL_CHANGED
	Nivel de acceso para 12%s en 12%s ha sido cambiado a 12%d.
CHAN_ACCESS_ADDED
	12%s ha sido agregad@ a lista de acceso de 12%s con nivel 12%d.
CHAN_ACCESS_NO_SUCH_ENTRY
	Entrada desconocida (12#%d) en la lista de acceso de 12%s.
CHAN_ACCESS_NOT_FOUND
	12%s no fue encontrad@ en la lista de acceso de 12%s.
CHAN_ACCESS_NO_MATCH
	No se han encontrado entradas en la lista de acceso de 12%s12.
CHAN_ACCESS_DELETED
	12%s borrad@ de la lista de acceso de 12%s.
CHAN_ACCESS_DELETED_ONE
	Borrada12 1 entrada de la lista de acceso de 12%s.
CHAN_ACCESS_DELETED_SEVERAL
	Borradas 12%s entradas de la lista de acceso de 12%s.
CHAN_ACCESS_LIST_HEADER
	Lista de acceso de 12%s:
	  Num   Niv  Nick
CHAN_ACCESS_LIST_EMPTY
	Lista de access de 12%s está vacia.
CHAN_ACCESS_COUNT
	Numero de registros del canal %s: 12%d.
CHAN_ACCESS_LIST_FORMAT
	  %3d  %4d  %s%s%s%s

# AOP/SOP error response
CHAN_NO_AOP_SOP
	Para asignar privilegios del canal a usuarios, usa el comando 12ACCESS.
	Escribe 12/msg %s HELP ACCESS para más información.

# AKICK responses
CHAN_AKICK_SYNTAX
	12AKICK <canal> {ADD | DEL | LIST | VIEW | ENFORCE} [nick o mascara]
CHAN_AKICK_DISABLED
	Lo siento, la modificación de lista de autokicks de canal esta temporalmente deshabilitada.
CHAN_AKICK_ALREADY_EXISTS
	12%s ya existe en la lista de autorkicks de 12%s.
CHAN_AKICK_REACHED_LIMIT
	Lo siento, solo puede tener 12%d mascaras de autokick en un canal.
CHAN_AKICK_ADDED
	12%s agregad@ a la lista de autokick de 12%s.
CHAN_AKICK_NO_SUCH_ENTRY
	Entrada desconocida (12#%d) en la lista de autokick de 12%s.
CHAN_AKICK_NOT_FOUND
	12%s no se encuentra en la lista de autokick de 12%s.
CHAN_AKICK_DELETED
	12%s borrad@ de la lista de autokick de 12%s.
CHAN_AKICK_DELETED_ONE
	Borrada12 1 entrada en la lista de autokick de 12%s.
CHAN_AKICK_DELETED_SEVERAL
	Borradas 12%s entradas en la lista de autokick de 12%s.
CHAN_AKICK_NO_MATCH
	No se encuentra entradas en la lista de autokick de 12%s.
CHAN_AKICK_LIST_EMPTY
	La lista de autokick de 12%s está vacia.

CHAN_AKICK_LIST_HEADER
	Lista de autokick de 12%s:
CHAN_AKICK_LIST_FORMAT
	  %3d %s%s
CHAN_AKICK_VIEW_FORMAT
	  %3d %s (por 12%s, el 12%s)
	    %s
CHAN_AKICK_ENFORCE_DONE
	12AKICK ENFORCE para 12%s completado; 12%d usuarios son afectados.
CHAN_AKICK_COUNT
	Numero de AKICKs en el canal %s: ^C12%d^C.

# LEVELS responses
CHAN_LEVELS_SYNTAX
	12LEVELS <canal> {SET | DIS[ABLE] | LIST | RESET} [item [level]]
CHAN_LEVELS_RANGE
	El nivel debe de estar entre 12%d y 12%d.
CHAN_LEVELS_CHANGED
	El nivel para 12%s en canal 12%s cambiado a 12%d.
CHAN_LEVELS_UNKNOWN
	Opción 12%s desconocida. Escribe 12/msg %s HELP LEVELS DESC para una lista de opciones validas.
CHAN_LEVELS_DISABLED
	12%s deshabilitado en el canal 12%s.
CHAN_LEVELS_LIST_HEADER
	Configuración de nivel de acceso para canal 12%s:
CHAN_LEVELS_LIST_DISABLED
	    %-*s  (deshabilitado)
CHAN_LEVELS_LIST_FOUNDER
	    %-*s  (sólo fundador)
CHAN_LEVELS_LIST_NORMAL
	    %-*s  %d
CHAN_LEVELS_RESET
	Niveles de acceso de 12%s configurados a niveles originales.

# INFO responses
CHAN_INFO_SYNTAX
	12INFO <canal> [ALL]
CHAN_INFO_HEADER
	Información de canal 12%s:
CHAN_INFO_OFICIAL
	Es un Canal Oficial de Tierrared
CHAN_INFO_ACTIVED
	Estado: 12ACTIVO
CHAN_INFO_SUSPENDED
	Estado: 4SUSPENDIDO
CHAN_INFO_SUSPENDED_REASON
	Motivo: 12%s
CHAN_INFO_SUSPENDED_DETAILS
	Suspendido por 12%s en 12%s (%s)
CHAN_INFO_FOUNDER
	Fundador: 12%s (12%s)
CHAN_INFO_NO_FOUNDER
	Fundador: 12%s
CHAN_INFO_SUCCESSOR
	Sucesor: 12%s (12%s)
CHAN_INFO_NO_SUCCESSOR
	Sucesor: 12%s
CHAN_INFO_DESCRIPTION
	Descripción: 12%s
CHAN_INFO_ENTRYMSG
	Mensaje de entrada: 12%s
CHAN_INFO_ENTRYMSG_SET_BY
	Mensaje de entrada ajustado por: 12%s
CHAN_INFO_TIME_REGGED
	Registrado: 12%s
CHAN_INFO_LAST_USED
	Ultimo uso: 12%s
CHAN_INFO_LAST_TOPIC
	Ultimo tópico: 12%s
CHAN_INFO_TOPIC_SET_BY
	Tópico ajustado por: 12%s
CHAN_INFO_URL
	URL: 12%s
CHAN_INFO_EMAIL
	E-mail: 12%s
CHAN_INFO_OPTIONS
	Opciones: %s
CHAN_INFO_OPT_PRIVATE
	12Privacidad
CHAN_INFO_OPT_KEEPTOPIC
	12Retención de topic
CHAN_INFO_OPT_TOPICLOCK
	12Candado de topic
CHAN_INFO_OPT_SECUREOPS
	12Secure Ops
CHAN_INFO_OPT_SECUREVOICES
	12Secure Voices
CHAN_INFO_OPT_LEAVEOPS
	12Leave Ops
CHAN_INFO_OPT_LEAVEVOICES
	12Leave Voices
CHAN_INFO_OPT_RESTRICTED
	12Acceso restringido
CHAN_INFO_OPT_SECURE
	12Seguridad
CHAN_INFO_OPT_ISSUED
	12Issued
CHAN_INFO_OPT_MEMOALERT
	12Memo Alert
CHAN_INFO_OPT_UNBANCYBER
	12Unban de Cyber
CHAN_INFO_OPT_LEVELS
	12Levels
CHAN_INFO_OPT_NONE
	12Ninguna
CHAN_INFO_MODE_LOCK
	Candado de modo: 12%s
CHAN_INFO_NO_EXPIRE
	Expiración del canal: 4NO12 expirará.

# LIST responses
CHAN_LIST_SYNTAX
	12LIST <patron>
CHAN_LIST_SERVADMIN_SYNTAX
	12LIST <patron> [FORBID] [NOEXPIRE] [SUSPENDED]
CHAN_LIST_HEADER
	Lista de entradas que satisfacen 12%s:
CHAN_LIST_FORMAT
	    %-20s  %s
CHAN_LIST_END
	Fin de lista - 12%d/12%d entradas mostradas.

# INVITE responses
CHAN_INVITE_SYNTAX
	12INVITE <canal>

# OP responses
CHAN_IS_BOT_SERVICE
	No puedes hacer 12%s a un Bot de Servicio de la red.
CHAN_IS_ADMIN_SERVICE
	No puedes hacer 12%s a un Administrador de la red.
CHAN_IS_OPER_SERVICE
	No puedes hacer 12%s a un Operador de la red.
CHAN_IS_LEVELS
	No puedes hacer 12%s a un usuario con igual o mayor level que el tuyo.
CHAN_NICK_IN_CHAN
	El nick 12%s ya está en el canal 12%s.
CHAN_NICK_NOT_IN_CHAN
	El nick 12%s no está en el canal 12%s.

CHAN_OP_SYNTAX
	12OP <canal> <nick>
CHAN_OP_ALREADY_OP
	El nick 12%s ya esta opeado en el canal 12%s.

# DEOP responses
CHAN_DEOP_SYNTAX
	12DEOP <canal> <nick>
CHAN_DEOP_ALREADY_DEOP
	El nick 12%s no está opeado en el canal 12%s.

# VOICE responses
CHAN_VOICE_SYNTAX
	12VOICE <canal> <nick>
CHAN_VOICE_ALREADY_VOICE
	El nick 12%s ya esta voiceado en el canal 12%s.

# DEVOICE responses
CHAN_DEVOICE_SYNTAX
	12DEVOICE <canal> <nick>
CHAN_DEVOICE_ALREADY_DEVOICE
	El nick 12%s no está voiceado en el canal 12%s.

# KICK responses
CHAN_KICK_SYNTAX
	12KICK <canal> <nick> [razón]

# BAN responses
#CHAN_BAN_SYNTAX
#	12BAN <canal> <mascara>

#UNBAN responses
CHAN_UNBAN_SYNTAX
	12UNBAN <canal>
CHAN_UNBAN_NOT_FOUND
	La lista de bans del canal 12%s está vacia.
CHAN_UNBAN_FAILED
#	No habia bans en el canal 12%s que te afecten.
	No se ha podido desbanearte de 12%s.
CHAN_UNBANNED
	Has sido desbaneado de 12%s.

# CLEAR responses
CHAN_CLEAR_SYNTAX
	12CLEAR <canal> <opcion>
CHAN_CLEARED_BANS
	Todos los bans en canal 12%s han sido borrados.
CHAN_CLEARED_MODES
	Todos los modos en canal 12%s han sido borrados.
CHAN_CLEARED_OPS
	Modo +o de operadores han sido desactivados del canal 12%s.
CHAN_CLEARED_VOICES
	Modo +v de algunos usuarios han sido desactivados del canal 12%s.
CHAN_CLEARED_USERS
	Todos los usuarios del han sido kickeados del canal 12%s.
CHAN_CLEARED_TOPIC
	El topic del canal 12%s ha sido reseteado.

# GETKEY responses
CHAN_GETKEY_SYNTAX
	GETKEY <canal>
CHAN_GETKEY_NOT_FOUND
	No hay key (no está en modo +k) en el canal 12%s.
CHAN_GETKEY_FOUND
	La key del canal 12%s es %s12 .

# RESET responses
CHAN_RESET_SYNTAX
	12RESET <canal>
CHAN_RESET_SUCCEEDED
	Ha sido reseteado el canal 12%s.


# GETPASS responses
CHAN_GETPASS_SYNTAX
	12GETPASS <canal>
CHAN_GETPASS_UNAVAILABLE
	Comando 12GETPASS no esta disponible cuando encripción esta en uso.
CHAN_GETPASS_PASSWORD_IS
	La contraseña del canal 12%s es 12%s.

# SUSPEND responses
CHAN_SUSPEND_SYNTAX
	12SUSPEND [+expiracion] <canal> <motivo>
CHAN_SUSPEND_FORBIDDEN
	No se ha podido suspender el canal 12%s, está forbideado.
CHAN_SUSPEND_SUSPENDED
	El canal 12%s ya estaba suspendido.
CHAN_SUSPEND_SUCCEEDED
	El canal 12%s ha sido 12SUSPENDido!.


# UNSUSPEND responses
CHAN_UNSUSPEND_SYNTAX
	12UNSUSPEND <canal>
CHAN_SUSPEND_NOT_SUSPEND
	El canal 12%s no está suspendido.
CHAN_UNSUSPEND_SUSPEND_ADMIN
	No puedes reactivar el canal 12%s, esta suspendido por un admin.
CHAN_UNSUSPEND_SUCCEEDED
	El canal 12%s ha sido reactivado.


# FORBID responses
CHAN_FORBID_SYNTAX
	12FORBID <canal> <motivo>
CHAN_FORBID_NOT_LOCAL
	Canales locales no pueden ser prohibidos.
CHAN_FORBID_NOT_VALID
	Nombre invalido de canal para prohibir.
CHAN_FORBID_TOO_LONG
	Nombre de canal demasiado largo, solo se permite hasta %d caracteres.
CHAN_FORBID_ALREADY_FORBIDDEN
	El canal 12%s ya estaba forbideado.
CHAN_FORBID_SUCCEEDED
	El canal 12%s está prohibido de ser utilizado.
CHAN_FORBID_FAILED
	No fue posible prohibir el canal 12%s!


# UNFORBID responses
CHAN_UNFORBID_SYNTAX
	12UNFORBID <canal>
CHAN_UNFORBID_NOT_FORBID
	El canal 12%s no está prohibido.
CHAN_UNFORBID_SUCCEEDED
	El canal 12%s ha sido liberado.

###########################################################################
#
# Mensajes de MemoServ
#
###########################################################################

# Automatic messages
MEMO_HAVE_NEW_MEMO
	3Eo! tienes12 13 mensaje nuevo.
MEMO_HAVE_NEW_MEMOS
	3Eo! tienes 12%d3 mensajes nuevos.
MEMO_TYPE_READ_LAST
	Escribe 12/msg %s READ LAST para leer el último.
MEMO_TYPE_READ_NUM
	Escribe 12/msg %s READ %d para leerlo.
MEMO_TYPE_LIST_NEW
	Escribe 12/msg %s LIST NEW para listar los mensajes nuevos.
MEMO_AT_LIMIT
	4Atención: has llegado al máximo numero de mensajes (12%d). No podrás recibir mensajes nuevos hasta que borres algunos de los mensajes que tienes.
MEMO_OVER_LIMIT
	4Atención: has pasado el limite máximo de mensajes (12%d). No podrás recibir mensajes nuevos hasta que borres algunos de los mensajes que tienes.
MEMO_NEW_MEMO_ARRIVED
	Tienes un mensaje nuevo de 12%s. Escribe 12/msg %s READ %d para leerlo.
# Multi-use responses
MEMO_HAVE_NO_MEMOS
	No tienes mensajes.
MEMO_X_HAS_NO_MEMOS
	12%s no tiene mensajes.
MEMO_DOES_NOT_EXIST
	El mensaje 12%d no existe!
MEMO_LIST_NOT_FOUND
	No se han encontrado mensajes.

# SEND responses
MEMO_SEND_SYNTAX
	12SEND {nick | canal} <texto>
MEMO_SEND_DISABLED
	Lo siento, el envío de mensajes esta temporalmente deshabilitado.
MEMO_SEND_PLEASE_WAIT
	Por favor espere 12%d segundos antes de utilizar el comando 12SEND nuevamente.
MEMO_X_GETS_NO_MEMOS
	12%s no puede recibir mensajes.
MEMO_X_HAS_TOO_MANY_MEMOS
	12%s tiene demasiados mensajes y no puede recibir más.
MEMO_X_FULLMEMO
	Mensaje FULLMEMO: 12%s
MEMO_SENT
	Mensaje enviado a 12%s.

# CANCELA responses
MEMO_CANCEL_SYNTAX
	12CANCEL {nick | canal}
MEMO_CANCEL_NONE
	No hay mensaje para cancelar.
MEMO_CANCEL_SUCCEEDED
	El último mensaje a 12%s ha sido borrado.

# LIST responses
MEMO_LIST_SYNTAX
	12LIST [canal] [list | NEW]
MEMO_HAVE_NO_NEW_MEMOS
	No tienes nuevos mensajes.
MEMO_X_HAS_NO_NEW_MEMOS
	12%s no tiene nuevos mensajes.
MEMO_LIST_MEMOS
	Mensajes para 12%s. Para leerlos, escribe: 12/msg %s READ <numero>
MEMO_LIST_NEW_MEMOS
	Nuevos mensajes para 12%s. Para leerlos, escribe: 12/msg %s READ <numero>
MEMO_LIST_CHAN_MEMOS
	Mensajes para 12%s. Para leerlos, escribe 12/msg %s READ %s <numero>
MEMO_LIST_CHAN_NEW_MEMOS
	Nuevos mensajes para 12%s. Para leerlos, escribe: 12/msg %s READ %s <numero>
MEMO_LIST_HEADER
	 Num  Remitente         Día/Hora
MEMO_LIST_FORMAT
	%c%3d  %-16s  %s

# READ responses
MEMO_READ_SYNTAX
	12READ [canal] {list | LAST | NEW}
MEMO_HEADER
	Mensaje 12%d de 12%s (12%s). Para borrarlo, escribe: 12/msg %s DEL %d
MEMO_CHAN_HEADER
	Mensaje 12%d de 12%s (12%s). Para borrarlo, escribe: 12/msg %s DEL %s %d
MEMO_TEXT
	12%s

# DEL responses
MEMO_DEL_SYNTAX
	12DEL [canal] {numero | list | ALL}
MEMO_DELETED_NONE
	Ningún mensaje ha sido borrado.
MEMO_DELETED_ONE
	El mensaje 12%d ha sido borrado.
MEMO_DELETED_SEVERAL
	12%s mensajes han sido borrados.
MEMO_DELETED_ALL
	Todos sus mensajes han sido borrados.

# SET responses
MEMO_SET_SYNTAX
	12SET <opcion> <parametros>
MEMO_SET_DISABLED
	Lo siento, la opción de ajuste de mensajes esta temporalmente deshabilitada.
MEMO_SET_UNKNOWN_OPTION
	4Opción SET 12%s desconocida.

# SET NOTIFY responses
MEMO_SET_NOTIFY_SYNTAX
	12SET NOTIFY {ON | LOGON | NEW | OFF}
MEMO_SET_NOTIFY_ON
	12%s te notificará tus mensajes cuando te conectes o cuando te sean enviados.
MEMO_SET_NOTIFY_LOGON
	12%s te notificará tus mensajes cuando te conectes o canceles tu modo /AWAY.
MEMO_SET_NOTIFY_NEW
	12%s te notificará tus mensajes cuando te sean enviados.
MEMO_SET_NOTIFY_OFF
	12%s no te notificará tus mensajes.

# SET LIMIT responses
MEMO_SET_LIMIT_SYNTAX
	12SET LIMIT [canal_] <limite>
MEMO_SET_LIMIT_SERVADMIN_SYNTAX
	12SET LIMIT [ nick | canal] {limite | NONE} [HARD]
MEMO_SET_YOUR_LIMIT_FORBIDDEN
	No puedes cambiar tu limite de mensajes.
MEMO_SET_LIMIT_FORBIDDEN
	El limite de mensajes para 12%s no puede ser cambiado.
MEMO_SET_YOUR_LIMIT_TOO_HIGH
	No puedes ajustar tu limite de mensajes mayor que 12%d.
MEMO_SET_LIMIT_TOO_HIGH
	No puedes ajustar el limite de mensajes para 12%s mas alto que 12%d.
MEMO_SET_LIMIT_OVERFLOW
	Limite de mensajes muy alto; limitando a 12%d.
MEMO_SET_YOUR_LIMIT
	Tu limite de mensaje ha sido ajustado a 12%d.
MEMO_SET_YOUR_LIMIT_ZERO
	No podrás recibir mensajes.
MEMO_SET_LIMIT
	Limite de mensajes para 12%s ajustado a 12%d.
MEMO_SET_LIMIT_ZERO
	Limite de mensajes para 12%s ajustado a 120.
MEMO_UNSET_YOUR_LIMIT
	Tu limite de mensajes ha sido deshabilitado.
MEMO_UNSET_LIMIT
	Limite de mensajes desactivado para 12%s.

# SET FULLMEMO responses
MEMO_SET_FULLMEMO_SYNTAX
	SET FULLMEMO [mensaje]
MEMO_SET_FULLMEMO_CHANGED
	Mensaje de Memos llenos ajustado a 12%s.
MEMO_SET_FULLMEMO_UNSET
	Mensaje de Memos llenos deshabilitado.

# INFO responses
MEMO_INFO_SYNTAX
	12INFO [canal]
MEMO_INFO_SERVADMIN_SYNTAX
	12INFO [nick | canal]
MEMO_INFO_HEAD
	Información de 4%s sobre 12%s:
MEMO_INFO_NO_MEMOS
	No tienes mensajes.
MEMO_INFO_MEMO
	Tienes12 1 mensaje.
MEMO_INFO_MEMO_UNREAD
	Tienes12 1 mensaje, y no ha sido leído.
MEMO_INFO_MEMOS
	Tienes 12%d mensajes.
MEMO_INFO_MEMOS_ONE_UNREAD
	Tienes 12%d mensajes, de los cuales12 1 no ha sido leído.
MEMO_INFO_MEMOS_SOME_UNREAD
	Tienes 12%d mensajes, de los cuales 12%d no han sido leídos.
MEMO_INFO_MEMOS_ALL_UNREAD
	Tienes 12%d mensajes; de los cuales ninguno ha sido leído.
MEMO_INFO_LIMIT
	Tu limite de mensajes es 12%d.
MEMO_INFO_HARD_LIMIT
	Tu limite de mensajes es 12%d, y no puede ser cambiado.
MEMO_INFO_LIMIT_ZERO
	Tu limite de mensajes es12 0; no recibirás ningún nuevo mensaje.
MEMO_INFO_HARD_LIMIT_ZERO
	Tu limite de mensajes es12 0; no recibirás ningún nuevo mensaje. No puedes cambiar este limite.
MEMO_INFO_NO_LIMIT
	No tienes limite en la cantidad de mensajes que puede guardar.
#MEMO_INFO_NOTIFY_OFF
#	You will not be notified of new memos.
#MEMO_INFO_NOTIFY_ON
#	You will be notified of new memos at logon and when they arrive.
MEMO_INFO_NOTIFY_RECEIVE
	You will be notified when new memos arrive.
MEMO_INFO_NOTIFY_SIGNON
	%s is notified of news memos at logon.
MEMO_INFO_X_NO_MEMOS
	12%s no tiene mensajes.
MEMO_INFO_X_MEMO
	12%s tiene actualmente12 1 mensaje.
MEMO_INFO_X_MEMO_UNREAD
	12%s tiene actualmente1 1 mensaje, y no ha sido leído aun.
MEMO_INFO_X_MEMOS
	12%s tiene actualmente 12%d mensajes.
MEMO_INFO_X_MEMOS_ONE_UNREAD
	12%s tiene actualmente 12%d mensajes, de los cuales12 1 esta sin leer.
MEMO_INFO_X_MEMOS_SOME_UNREAD
	12%s tiene actualmente 12%d mensajes, de los cuales 12%d están sin leer.
MEMO_INFO_X_MEMOS_ALL_UNREAD
	12%s tiene actualmente 12%d mensajes; de los cuales todos están sin leer.
MEMO_INFO_X_LIMIT
	El limite de mensajes de 12%s es 12%d.
MEMO_INFO_X_HARD_LIMIT
	El limite de mensajes de 12%s es 12%d, y no puede ser cambiado por el usuario.
MEMO_INFO_X_NO_LIMIT
	12%s no tiene limite de mensajes.
MEMO_INFO_NOT_MSG_FULLMEMO
	Mensaje de Memo lleno: 12No tiene.
MEMO_INFO_MSG_FULLMEMO
	Mensaje de Memo lleno: 12%s.
MEMO_INFO_X_NOTIFY_OFF
	%s is not notified of new memos.
MEMO_INFO_X_NOTIFY_ON
	%s is notified of new memos at logon and when they arrive.
MEMO_INFO_X_NOTIFY_RECEIVE
	%s is notified when new memos arrive.
MEMO_INFO_X_NOTIFY_SIGNON
	%s is notified of news memos at logon.
MEMO_INFO_NOTIFY
	Notificacion de memos: %s.
MEMO_INFO_NOTIFY_ON
	12Siempre (ON)
MEMO_INFO_NOTIFY_LOGON
	12Al conectar y away off (LOGON)
MEMO_INFO_NOTIFY_NEW
	12Solo al recibir (NEW)
MEMO_INFO_NOTIFY_OFF
	12Nunca (OFF)

###########################################################################
#
# Mensajes de CyberServ
#
###########################################################################

CYBER_NO_ADMIN_CYBER
	No estás registrado como admin de un Cyber.
CYBER_NICK_NOT_IN_CYBER
	El usuario 12%s no está en tu Cyber.
CYBER_ILINE_NOT_CONCEDED
	El host 12%s no tiene concedidos clones.
CYBER_ILINE_NOT_FOUND
	El host 12%s no se encuentra en la lista de ilines.
CYBER_ILINE_ADMIN
	El admin 12%s ya tiene una iline.
CYBER_ILINE_ALREADY_PRESENT
	El host 12%s ya tiene iline.
CYBER_ILINE_IS_SUSPENDED
	No puedes usar los comandos de Cyber, la iline a tu cyber está suspendida temporalmente.
CYBER_ILINE_SUSPENDED
	La iline a tu host 12%s ha sido suspendida temporalmente.
	Motivo: 12%s.
CYBER_ILINE_EXPIRE
	La iline a tu host 12%s expirará el dia 12%s (12%s).
	Consulta 12/msg %s CONTRATA para más informacion sobre la renovacion de la iline.

# ACTUALIZA responses
CYBER_ACTUALIZA_CHECK
	El permiso de Iline de tu cyber no está a tu IP actual.
	Si deseas tener actualizada la iline escribe 12/msg %s ACTUALIZA  .
CYBER_ACTUALIZA_SUSPENDED
	La iline al host %s está suspendida temporalmente
CYBER_ACTUALIZA_HOST
	El host 12%s, ya existe en la lista de ilines.
CYBER_ACTUALIZA_IPFIJA
	No puedes actualizar, el host 12%s es una ip fija.
CYBER_ACTUALIZA_SUCCEEDED
	Actualizada la iline, ahora el host 12%s tiene concedidas 12%d clones.
CYBER_ACTUALIZA_SUCCEEDED_ILIMITED
	Actualizada la iline, ahora el host 12%s tiene concedidas clones ilimitados.
# INFO responses
CYBER_INFO_HEADER
	Información sobre el Cyber: 12%s
CYBER_INFO_IPFIJA_ON
	Tiene IP 12Dinámica
CYBER_INFO_IPFIJA_OFF
	Tiene IP 12Fija
CYBER_INFO_IPFIJA_HOST
	IP actual: 12%s
CYBER_INFO_HOST
	IP Numérica: 12%s
CYBER_INFO_HOST2
	IP Inversa: 12%s
CYBER_INFO_LIMITE
	Numero de clones: 12%d
CYBER_INFO_LIMITE_ILIMITED
	Numero de clones: 12Ilimitados
CYBER_INFO_NICKADMIN
	Nick del admin: 12%s
CYBER_INFO_NAMEADMIN
	Nombre y apellido: 12%s
CYBER_INFO_DNI
	DNI del admin: 12%s
CYBER_INFO_EMAIL
	Email de contacto: 12%s
CYBER_INFO_TELEFONO
	Telefono de contacto: 12%s
CYBER_INFO_VHOST
	Vhost del ciber: 12%s
CYBER_INFO_TIME
	Dado de alta: 12%s, 12%s
CYBER_INFO_RECORD
	Numero más alto: 12%d clones, alcanzado el 12%s
CYBER_INFO_OPER
	Iline añadido por 12%s
CYBER_INFO_SUSPENDED
	Iline suspendida por 12%s
CYBER_INFO_SUSPENDED_DETAILS
	Motivo: %s
CYBER_INFO_CLONES
	El host 12%s tiene actualmente 12%d clones.
	El limite es de 12%d clones.
CYBER_INFO_CLONES_ILIMITED
	El host 12%s tiene actualmente 12%d clones.
	Tiene clones ilimitados.
CYBER_INFO_NO_CLONES
	El host 12%s no tiene actualmente ningún clon.

# Kill responses
CYBER_KILL_SYNTAX
	12KILL <nick> [motivo]
CYBER_KILL_SUCCEEDED
	El usuario 12%s de tu cyber KILLeado!.

# Gline responses
CYBER_GLINE_SYNTAX
	12GLINE <nick> [motivo]
CYBER_GLINE_SUCCEEDED
	El usuario 12%s de tu cyber GLINEeado!.

# UNBAN responses
CYBER_UNBAN_SYNTAX
	12UNBAN <canal>
CYBER_UNBAN_NOT_UNBAN
	No puedes desbanear en 12%s, no está activado el 12UNBANCYBER.
CYBER_UNBAN_FAILED
	No hay ban en 12%s que afecte a tu cyber.
CYBER_UNBAN_SUCCEEDED
	El Cyber desbaneado de 12%s.

# GLOBAL responses
CYBER_GLOBAL_SYNTAX
	12GLOBAL <mensaje>
CYBER_GLOBAL_SUCCEEDED
	Mensaje enviado a todos los clientes de tu cyber.

# VERIFY response
CYBER_VERIFY_SYNTAX
	12VERIFY <nick>
CYBER_VERIFY_NOT_CYBER
	12%s no está registrado como admin de un cyber.
CYBER_VERIFY_CYBER
	12%s es admin del iline 12%s (%d clones).

# LIST response
CYBER_LIST_SYNTAX
	12LIST <patron>
CYBER_LIST_SERVADMIN_SYNTAX
	12LIST <patron> [NOEXPIRE] [SUSPENDED] [NOFIJA]
CYBER_LIST_HEADER
	Lista de entradas que satisfacen 12%s:
CYBER_LIST_RESULTS
	Fin de lista - 12%d/12%d entradas mostradas.

# CLONES response
CYBER_CLONES_SYNTAX
	12CLONES {LIST numero | VIEW host}
CYBER_CLONES_LIST_SYNTAX
	12CLONES LIST <numero>
CYBER_CLONES_VIEW_SYNTAX
	12CLONES VIEW <host>
CYBER_CLONES_DISABLED
	El control de CLONES está desactivado.
CYBER_CLONES_INVALID_THRESHOLD
	Valor incorrecto. El valor debe ser mayor que 2.
CYBER_CLONES_NOT_FOUND
	El host 12%s no tiene clones.
CYBER_CLONES_LIST_HEADER
	Hosts con por lo menos 12%d clones:
CYBER_CLONES_LIST_COLHEAD
	Clones  Host
# limit, host
CYBER_CLONES_LIST_FORMAT
	%6d    %s
# host, sessions, limit
CYBER_CLONES_VIEW_FORMAT
	El host 12%s tiene actualmente 12%d clones con un limite de 12%d.

# ILINE responses
CYBER_ILINE_SYNTAX
	12ILINE { ADD | DEL } <host> [<admin> <limite> +[expiracion] <motivo>]
CYBER_ILINE_SYNTAX_ADD
	12ILINE ADD <host> <admin> <limite> +[expiracion] <motivo>
CYBER_ILINE_SYNTAX_DEL
	ILINE DEL <host>
CYBER_ILINE_INVALID_HOSTMASK
	Mascara invalido, las mask no puede contener nick ni user.
CYBER_ILINE_INVALID_LIMIT
	Limite invalido, solo puedes entre12 0 (Ilimitados) a 12%d.
CYBER_ILINE_ADD_FAILED
	Ha fallado al añadir iline.
CYBER_ILINE_ADD_SUCCEEDED
	Añadida Iline para 12%s, 12%d clones.
CYBER_ILINE_DEL_SUCCEEDED
	Iline de 12%s borrado de la lista de ilines.

# SET Responses
CYBER_SET_SYNTAX
	12SET <host> <opción> <parametros>
CYBER_SET_UNKNOWN_OPTION
	Opcion 4SET %s desconocida.
# SET HOST /HOST2
CYBER_SET_HOST_CHANGED
	El host 12%s ha sido cambiado a 12%s.
CYBER_SET_HOST2_CHANGED
	El host 12%s ha sido cambiado a 12%s.
CYBER_SET_HOST2_UNSET
	El host 12%s, ha sido deshabilitado su 2º host.

# SET NICK
CYBER_SET_NICK_CHANGED
	Nick responsable para iline 12%s cambiado a 12%s.


# SET DNI
CYBER_SET_DNI_CHANGED
	DNI responsable iline 12%s cambiado a 12%s.


# SET EMAIL
CYBER_SET_EMAIL_CHANGED
	Email para iline 12%s cambiado a 12%s.

# SET TELEFONO
CYBER_SET_TELEFONO_CHANGED
	Telefono para iline 12%s cambiado a 12%s.

# SET LIMITE
CYBER_SET_LIMITE_INVALID
	El parametro %s es invalido, tiene que ser un numero entero entre 0 (Ilimitados) y %d.
CYBER_SET_LIMITE_CHANGED
	Numero de clones para iline 12%s cambiado a 12%d.

# SET NOMBRE
CYBER_SET_NOMBRE_CHANGED
	Nombre responsable para iline 12%s cambiado a 12%s.

# SET CENTRO
CYBER_SET_CENTRO_CHANGED
	Centro para iline 12%s cambiado a 12%s.

# SET VHOST
CYBER_SET_VHOST_CHANGED
	Vhost para iline 12%s ha sido cambiado a 12%s.
CYBER_SET_VHOST_UNSET
	Vhost para iline 12%s deshabilitado.

# SET IPNOFIJA
CYBER_SET_IPNOFIJA_SYNTAX
	12SET <host> IPNOFIJA { ON | OFF }
CYBER_SET_IPNOFIJA_ON
	La Iline 12%s ahora tendrá el soporte de las ips dinamicas.
CYBER_SET_IPNOFIJA_OFF
	La Iline 12%s ya no tendra soporte de ips dinamicas.


# SET EXPIRE
CYBER_SET_EXPIRE_SYNTAX
	SET <host> EXPIRE <tiempo>
CYBER_SET_EXPIRE_SUCCEEDED
	LA expiracion de la iline 12%s ajustada (12%s).

# SUSPEND responses
CYBER_SUSPEND_SYNTAX
	SUSPEND <host> <motivo>
CYBER_SUSPEND_SUSPENDED
	La iline 12%s ya estaba suspendida.
CYBER_SUSPEND_SUCCEEDED
	La iline 12%s SUSPENDida!.

# UNSUSPEND responses
CYBER_UNSUSPEND_SYNTAX
	SUSPEND <host>
CYBER_UNSUSPEND_NOT_SUSPEND
	La iline 12%s no estaba suspendida.
CYBER_UNSUSPEND_SUCCEEDED
	La iline 12%s Reactivada!.

###########################################################################
#
# Mensajes de CregServ
#
###########################################################################

CREG_NICK_IDENTIFY_REQUIRED
	No estás identificado, identifícate con 12/msg NiCK IDENTIFY contraseña.
CREG_NOT_REGISTRED
	El canal 12%s no ha sido encontrado.
CREG_NOT_PROCESO_REG
	El canal 12%s no está en proceso de registro.
	Escribe 12/msg %s INFO %s para más información.

# REGISTER Responses
CREG_REGISTER_DISABLED
	El servicio de pre-registro de canales está desactivado temporalmente.
CREG_REGISTER_SYNTAX
	12REGISTRA <canal> <contraseña> <descripcion>
CREG_REGISTER_NOT_VALID
	Nombre de canal no válido, asegurate que empieza por #.
CREG_REGISTER_FAILED
	No se ha podido hacer la petición de registro del canal 12%s.
	Escribe 12/msg %s INFO %s para más información.
CREG_REGISTRATION_FAILED
	Ha fallado la petición de registro del canal 12%s.
	Intente de nuevo más tarde.
CREG_REGISTER_SUCCEEDED
	El canal 12%s aceptado para el proceso de registro.

# CANCEL Responses
CREG_CANCEL_SYNTAX
	12CANCELA <canal> <contraseña>
CREG_CANCEL_FAILED
	4Contraseña incorrecta.
	No se ha podido cancelar la peticion de registro del canal 12%s.
CREG_CANCEL_SUCCEEDED
	La petición de registro del canal 12%s cancelada.

###########################################################################
#
# StatServ messages
#
############################################################################

# General SERVERS responses
STAT_SERVERS_REMOVE_SERV_FIRST
	Server ^B%s^B is online. Remove it from the the network and try again.
STAT_SERVERS_SERVER_EXISTS
	Server ^B%s^B already exists.

# SERVERS command syntax
STAT_SERVERS_SYNTAX
	SERVERS ^_option^_ ^_parameters^_

# STATS responses
STAT_SERVERS_STATS_TOTAL
	Total Servers: %2d
STAT_SERVERS_STATS_ON_OFFLINE
	       Online: %2d (%d%%)  Offline: %2d (%d%%)
STAT_SERVERS_LASTQUIT_WAS
	    Last Quit: %-30s  %s

# LIST responses
STAT_SERVERS_LIST_HEADER
	Server Name                    Users      Opers
STAT_SERVERS_LIST_RESULTS
	End of list -- %d/%d online servers shown.

# VIEW responses
STAT_SERVERS_VIEW_HEADER_ONLINE
	%-30s  (^_online^_)
STAT_SERVERS_VIEW_HEADER_OFFLINE
	%-30s  (^_offline^_)
STAT_SERVERS_VIEW_LASTJOIN
	    Last join: %s
STAT_SERVERS_VIEW_LASTQUIT
	    Last quit: %s
STAT_SERVERS_VIEW_QUITMSG
	 Quit message: %s
STAT_SERVERS_VIEW_USERS_OPERS
	        Users: %3d (%2d%%)  Opers: %3d (%2d%%)
STAT_SERVERS_VIEW_RESULTS
	End of list -- %d/%d servers shown.

# DELETE responses
STAT_SERVERS_DELETE_SYNTAX
	SERVERS DELETE ^_server^_
STAT_SERVERS_DELETE_DONE
	Statistics for server ^B%s^B have been deleted.

# COPY responses
STAT_SERVERS_COPY_SYNTAX
	SERVERS COPY ^_server^_ ^_newname^_
STAT_SERVERS_COPY_DONE
	Statistics for server ^B%s^B copied to ^B%s^B

# RENAME responses
STAT_SERVERS_RENAME_SYNTAX
	SERVERS RENAME ^_server^_ ^_newname^_
STAT_SERVERS_RENAME_DONE
	Statistics for server ^B%s^B renamed to ^B%s^B

# USERS command syntax
STAT_USERS_SYNTAX
	USERS ^_option^_ ^_parameters^_


###########################################################################
#
# Mensajes de OperServ
#
###########################################################################

# General messages
OPER_BOUNCY_MODES
	Services no puede cambiar modos.
	Tus servidores están configurados correctamente?
OPER_BOUNCY_MODES_U_LINE
	Services no puede cambiar modos.
	La líneas U: de sus servidores están configurados correctamente?

# GLOBAL responses
OPER_GLOBAL_SYNTAX
	12GLOBAL <message>

OPER_GLOBALN_SYNTAX
	12GLOBALN <message>

# SERVERS responses


# STATS responses
OPER_STATS_UNKNOWN_OPTION
	4Opción STATS 12%s desconocida.
OPER_STATS_CURRENT_USERS
	Usuarios actuales : 12%d (12%d ircops)
OPER_STATS_MAX_USERS
	Máximo de usuarios: 12%d (12%s)
OPER_STATS_CURRENT_CHANS
	Canales actuales : 12%d
OPER_STATS_MAX_CHANS
	Máximo de canales: 12%d (12%s)

# This is ugly, but at least it's language-portable...
OPER_STATS_UPTIME_DHMS
	Services activos 12%d días, 12%02d:%02d
OPER_STATS_UPTIME_1DHMS
	Services activos 12%d día, 12%02d:%02d
OPER_STATS_UPTIME_HMS
	Services activos 12%d horas, 12%d minutos
OPER_STATS_UPTIME_HM1S
	Services activos 12%d horas, 12%d minutos
OPER_STATS_UPTIME_H1MS
	Services activos 12%d horas, 12%d minuto
OPER_STATS_UPTIME_H1M1S
	Services activos 12%d horas, 12%d minuto
OPER_STATS_UPTIME_1HMS
	Services activos 12%d hora, 12%d minutos
OPER_STATS_UPTIME_1HM1S
	Services activos 12%d hora, 12%d minutos
OPER_STATS_UPTIME_1H1MS
	Services activos 12%d hora, 12%d minuto
OPER_STATS_UPTIME_1H1M1S
	Services activos 12%d hora, 12%d minuto
OPER_STATS_UPTIME_MS
	Services activos 12%d minutos, 12%d segundos
OPER_STATS_UPTIME_M1S
	Services activos 12%d minutos, 12%d segundos
OPER_STATS_UPTIME_1MS
	Services activos 12%d minuto, 12%d segundos
OPER_STATS_UPTIME_1M1S
	Services activos 12%d minuto, 12%d segundo
OPER_STATS_BYTES_READ
	Bytes leidos   : 12%5d kB
OPER_STATS_BYTES_WRITTEN
	Bytes escritos : 12%5d kB
OPER_STATS_SERVER_MEM
	Servidores: 12%6d registros, 12%5d kB
OPER_STATS_USER_MEM
	Usuarios  : 12%6d registros, 12%5d kB
OPER_STATS_CHANNEL_MEM
	Canales   : 12%6d registros, 12%5d kB
OPER_STATS_NICKSERV_MEM
	NickServ  : 12%6d registros, 12%5d kB
OPER_STATS_NICKSERV_MEM_2
	12%6d nicks forbids,   12%6d nicks suspendidos
OPER_STATS_NICKSERV_MEM_3
	12%6d entradas access, 12%6d entradas ignore
OPER_STATS_NICKSERV_MEM_4
	12%6d memos totales,   12%6d memos sin leer
OPER_STATS_CHANSERV_MEM
	ChanServ  : 12%6d registros, 12%5d kB
OPER_STATS_CHANSERV_MEM_2
	12%6d canales forbids, 12%6d canales suspendidos
OPER_STATS_CHANSERV_MEM_3
	12%6d entradas access, 12%6d entradas akick
OPER_STATS_CHANSERV_MEM_4
	12%6d memos totales,   12%6d memos sin leer
OPER_STATS_OPERSERV_MEM
	OperServ  : 12%6d registros, 12%5d kB
OPER_STATS_OPERSERV_MEM_2
	12%6d entradas gline,  12%6d entradas News
OPER_STATS_CREGSERV_MEM
	CregServ  : 12%6d registros, 12%5d kB
OPER_STATS_CYBERSERV_MEM
	CyberServ : 12%6d registros, 12%5d kB
OPER_STATS_CYBERSERV_MEM_2
	12%6d ilines suspendidas
OPER_STATS_CYBERSERV_MEM_3
	12%6d ilines no ip fija, 12%6d ilines con vhost
OPER_STATS_STATSERV_MEM
	StatServ  : ^C12%6d^C registros, ^C12%5d^C kB
OPER_STATS_MEMOSERV_TOTAL
	Memos Totales : 12%d mensajes
OPER_STATS_MEMOSERV_NOREAD
	Memos por leer: 12%d mensajes


OPER_STATS_AKILL_EXPIRE_DAYS
	Tiempo default para expirar GLINE: 12%d días
OPER_STATS_AKILL_EXPIRE_DAY
	Tiempo default para expirar GLINE:12 1 día
OPER_STATS_AKILL_EXPIRE_HOURS
	Tiempo default para expirar GLINE: 12%d horas
OPER_STATS_AKILL_EXPIRE_HOUR
	Tiempo default para expirar GLINE:12 1 hora
OPER_STATS_AKILL_EXPIRE_MINS
	Tiempo default para expirar GLINE: 12%d minutos
OPER_STATS_AKILL_EXPIRE_MIN
	Tiempo default para expirar GLINE:12 1 minuto
OPER_STATS_AKILL_EXPIRE_NONE
	Tiempo default para expirar GLINE: 12No expira
OPER_STATS_SESSIONS_MEM
	Clones    : 12%6d registros, 12%5d kB

# MODE responses
OPER_MODE_SYNTAX
	12MODE <canal> <modos>

# CLEARMODES responses
OPER_CLEARMODES_SYNTAX
	12CLEARMODES <canal> [ALL]

OPER_CLEARMODES_DONE
	Modos y bans del canal 12%s han sido limpiados.

OPER_CLEARMODES_ALL_DONE
	Todos los modos del canal 12%s han sido limpiados.

# KICK responses
OPER_KICK_SYNTAX
	12KICK <canal> <nick> <motivo>

# APODERA responses
OPER_APODERA_SYNTAX
	12APODERA <canal>
OPER_APODERA_SUCCEEDED
	Has apoderado el canal 12%s.

# LIMPIA responses
OPER_LIMPIA_SYNTAX
	12LIMPIADO <canal>
OPER_LIMPIA_SUCCEEDED
	Has limpiado el canal 12%s.

# KILL responses
OPER_KILL_SYNTAX
	12KILL <nick> <motivo>
OPER_KILL_SUCCEEDED
	Has killeado al usuario 12%s.

# BLOCK responses
OPER_BLOCK_SYNTAX
	12BLOCK <nick> <motivo>
OPER_BLOCK_CYBER
	No puedes Glinear a 12%s, está en un cyber.
	Consulta con un admin.
OPER_BLOCK_SUCCEEDED
	Has Glineado a 12%s y a sus clones.

# UNBLOCK responses
OPER_UNBLOCK_SYNTAX
	12UNBLOCK <nick>



# ADMIN responses
OPER_ADMIN_SYNTAX
	12ADMIN {ADD | DEL | LIST} [nick]
OPER_ADMIN_ADD_SYNTAX
	12ADMIN ADD <nick>
OPER_ADMIN_DEL_SYNTAX
	12ADMIN DEL <nick>

OPER_ADMIN_SKELETON
	Services esta en modo skeleton; el comando 12ADMIN no esta disponible.
OPER_ADMIN_EXISTS
	12%s ya está en la lista de Administradores de Services.
OPER_ADMIN_ADDED
	12%s agregado a la lista de Administradores de Services.
OPER_ADMIN_TOO_MANY
	Demasiadas entradas (12%d) en la lista de Administradores de Services; no se puede agregar mas.
OPER_ADMIN_REMOVED
	12%s borrado de la lista de Administradores de Services.
OPER_ADMIN_NOT_FOUND
	12%s no fue encontrado en la lista de Administradores de Services.
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
	Services esta en modo skeleton; el comando OPER no esta disponible.
OPER_OPER_EXISTS
	12%s ya estaba en la lista de Operadores de Services.
OPER_OPER_ADDED
	12%s agregado a la lista de Operadores de Services.
OPER_OPER_TOO_MANY
	Muchas entradas (12%d) en la lista de Operadores de Services; no se pueden agregar mas.
OPER_OPER_REMOVED
	12%s borrado de la lista de Operadores de Services.
OPER_OPER_NOT_FOUND
	12%s no fue encontrado en la lista de Operadores de Services.
OPER_OPER_LIST_HEADER
	Lista de Operadores de Services:

# AKILL responses
OPER_AKILL_SYNTAX
	12GLINE {ADD | DEL | LIST | VIEW} [[+expiracion] <mascara> [motivo]]
OPER_AKILL_ADD_SYNTAX
	12GLINE ADD [+expiracion] <mascara> <motivo>
OPER_AKILL_DEL_SYNTAX
	12GLINE DEL <mascara>
OPER_TOO_MANY_AKILLS
	La lista de GLINEs esta 12llena.
OPER_AKILL_NO_NICK
	4Atención: Las máscaras de 12GLINE no pueden contener nicks;
	4NO incluyas la parte de nick en su mascara.
OPER_AKILL_MASK_TOO_GENERAL
	The AKILL mask is too general.
OPER_AKILL_ADDED
	12%s agregado a la lista de GLINEs.
OPER_AKILL_REMOVED
	12%s eliminado de la lista de GLINEs.
OPER_AKILL_NOT_FOUND
	12%s no fue encontrado en la lista de GLINEs.
OPER_AKILL_LIST_HEADER
	Lista actual de 12GLINEs:
# mask, reason
OPER_AKILL_LIST_FORMAT
	%-32s  %s
# mask, set-by, set-time, expires, reason
OPER_AKILL_VIEW_FORMAT
	%s (por %s en %s; %s)
	    %s
OPER_STATS_AKILL_COUNT
	Numero actual de GLINEs: ^C12%d^C
OPER_AKILL_NO_EXPIRE
	no expira
OPER_AKILL_EXPIRES_SOON
	expira en la siguiente actualización de base de datos
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
OPER_SET_SYNTAX
	12SET <opcion> <parametros>
OPER_SET_IGNORE_ON
	Ignore code sera usado.
OPER_SET_IGNORE_OFF
	Ignore code no sera usado.
OPER_SET_IGNORE_ERROR
	Parámetro para IGNORE debe ser ON o OFF.
OPER_SET_READONLY_ON
	Services esta ahora en modo leer-solamente read-only.
OPER_SET_READONLY_OFF
	Services esta ahora en modo leer-escribir read-write.
OPER_SET_READONLY_ERROR
	Parámetro para READONLY debe ser ON o OFF.
OPER_SET_DEBUG_ON
	Services esta ahora en modo debug.
OPER_SET_DEBUG_OFF
	Services esta ahora en modo non-debug.
OPER_SET_DEBUG_LEVEL
	Services esta ahora en modo debug (nivel %d).
OPER_SET_DEBUG_ERROR
	Parámetro para DEBUG debe ser ON, OFF, o un numero positivo.
OPER_SET_UNKNOWN_OPTION
	Opción %s desconocida.

# JUPE responses
OPER_JUPE_SYNTAX
	12JUPE <servidor> [motivo]
	

# RAW responses
OPER_RAW_SYNTAX
	12RAW <text>

# UPDATE responses
OPER_UPDATING
	4Actualizando bases de datos.

# RESTART responses
OPER_CANNOT_RESTART
	SERVICES_BIN no definida; no es posible reiniciar. Ejecute nuevamente el script 12./configure y recompile Services para habilitar el comando 12RESTART.

# LISTIGNORE responses
OPER_IGNORE_LIST
	Lista de ignoración de Services:
OPER_IGNORE_LIST_EMPTY
	Lista de ignoración esta vacía.

# ROTATELOG responses
OPER_ROTATELOG_FILE_EXISTS
	No ha podido renombrar el log, un archivo con el nombre 12%s todavia existe!
OPER_ROTATELOG_RENAME_DONE
	Log renombrado a 12%s
OPER_ROTATELOG_RENAME_FAIL
	Log no ha podido renombrarlo: 12%s
OPER_ROTATELOG_OPEN_LOG_FAIL
	Logueando no ha podido resetear: 12%s



###########################################################################
#
# Mensajes de CyberServ
#
###########################################################################

#CYBER_NO_ADMIN_CYBER
#	No eres un admin de un Cyber.
#CYBER_NICK_NOT_IN_CYBER
#	12%s no está en tu Cyber.

#Respuestas a KILL
#CYBER_KILL_SYNTAX
#	12KILL <nick> [motivo]
#CYBER_KILL_SUCCEEDED
#	El usuario 12%s de tu cyber KILLeado!.

#Respuestas a Gline
#CYBER_GLINE_SYNTAX
#	12GLINE <nick> [motivo]
#CYBER_GLINE_SUCCEEDED
#	El usuario 12%s de tu cyber GLINEeado!.

#Respuestas a UNBAN
#CYBER_UNBAN_SYNTAX
#	12UNBAN <canal>
#CYBER_UNBAN_FAILED
#	No hay ban en 12%s que afecte a tu cyber.
#CYBER_UNBAN_SUCCEEDED
#	El Cyber desbaneado de 12%s.

# EXCEPTION responses
OPER_EXCEPTION_SYNTAX
	12ILINE {ADD | DEL | MOVE | LIST | VIEW} [parametros]
OPER_EXCEPTION_ADD_SYNTAX
	12ILINE ADD [+expiracion] <mascara> <limite> <razon>
OPER_EXCEPTION_DEL_SYNTAX
	12ILINE DEL {mascara | list}
OPER_EXCEPTION_MOVE_SYNTAX
	12ILINE MOVE <numero> <posicion>
OPER_EXCEPTION_DISABLED
	El control de clones está 12desactivado.
OPER_EXCEPTION_ALREADY_PRESENT
	El host 12%s ya tiene concedidos clones.
OPER_EXCEPTION_TOO_MANY
	La lista de clones está 12llena.
OPER_EXCEPTION_ADDED
	Añadida Iline para 12%s, 12%d clones.
OPER_EXCEPTION_MOVED
	Iline para 12%s (12#%d) movida a la posicion 12%d.
OPER_EXCEPTION_NO_SUCH_ENTRY
	No existe entrada (12#%d) en la lista de Ilines.
OPER_EXCEPTION_NOT_FOUND
	El host 12%s no tiene concedidos clones.
OPER_EXCEPTION_NO_MATCH
	No hay ningun 12HOST en la lista de Ilines.
OPER_EXCEPTION_DELETED
	Iline para 12%s borrada en la lista de Ilines.
OPER_EXCEPTION_DELETED_ONE
	Borrada12 1 entrada en la lista de Ilines.
OPER_EXCEPTION_DELETED_SEVERAL
	Borradas 12%d entradas en la lista de ilines.
OPER_EXCEPTION_LIST_HEADER
	Lista de 12ILINES:
# mask, limit
OPER_EXCEPTION_LIST_FORMAT
	%3d  %4d   %s
OPER_EXCEPTION_LIST_COLHEAD
	Num  Limite  Host
# mask, set-by, set-time, expires, limit, reason
OPER_EXCEPTION_VIEW_FORMAT
	%3d.  %s  (por %s en %s; %s)
	    Limite: %-4d  - %s
OPER_EXCEPTION_INVALID_LIMIT
	Número de clones no valido. It must be a valid integer greater than or equal
OPER_EXCEPTION_INVALID_HOSTMASK
	Host no valido. Only real hostmasks are valid as exceptions are not m

# SESSION responses
OPER_SESSION_SYNTAX
	12CLONES {LIST numero | VIEW host}
OPER_SESSION_LIST_SYNTAX
	12CLONES LIST <numero>
OPER_SESSION_VIEW_SYNTAX
	12CLONES VIEW <host>
OPER_SESSION_DISABLED
	El control de clones esta 12desactivado.
OPER_SESSION_INVALID_THRESHOLD
	Valor incorrecto. El valor debe ser mayor que 1.
OPER_SESSION_NOT_FOUND
	El host 12%s no tiene clones.
OPER_SESSION_LIST_HEADER
	Hosts con por lo menos 12%d clones:
OPER_SESSION_LIST_COLHEAD
	Clones  Host
# limit, host
OPER_SESSION_LIST_FORMAT
	%6d    %s
# host, sessions, limit
OPER_SESSION_VIEW_FORMAT
	El host 12%s tiene actualmente 12%d clones con un limite de 12%d.
#CYBER_CLONES_IS_CYBER
#	Eres Cyber, tu host 12%s tiene ahora mismo 12%d clones (Limite 12%d clones)
#CYBER_CLONES_NOT_IS_CYBER
#	No eres Cyber

# KILLCLONES responses
OPER_KILLCLONES_SYNTAX
	12KILLCLONES <nick>
OPER_KILLCLONES_UNKNOWN_NICK
	No ha sido encontrado el nick 12%s.
#CYBER_KILLCLONES_SUCCEEDED
#	Han sido killeados 12%d clones del nick 12%s.

###########################################################################
#
# News system messages
#
###########################################################################

NEWS_LOGON_TEXT
	[4Noticias de la red - 12%s] %s
NEWS_OPER_TEXT
	[4Noticias OPERS/IRCOPS - 12%s] %s

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
	Sintaxis: 12LOGONNEWS ADD <texto>
	          12LOGONNEWS DEL {numero | ALL}
	          12LOGONNEWS LIST
	
	Editar o mostrar la lista de mensajes de bienvenida de  noticias.
	Cuando un usuario conecta a la red, esos mensjes deben ser
	enviados a ellos. Si hay mas de 3 mensajes, solo se enviará los
	3 mensajes mas recientes.
	
	12LOGONNEWS LIST debe ser usado por algun IRCOP para listar los
	mensajes de noticias actuales. 12ADD y 12DEL solo podrán usarlos
	por 4Administradores de Services.
	
NEWS_HELP_OPER
	Sintaxis: 12OPERNEWS ADD texto
	          12OPERNEWS DEL {numero | ALL}
	          12OPERNEWS LIST
	
	Editar o mostrar la lista de mensajes de IRCOPS de noticias.
	Cuando un usuario hace IRCOP (con el comando /OPER), esos
	mensajes deben ser enviados a ellos.Si hay mas de 3 mensajes,
	solo se enviará los 3 mensajes mas recientes.
	
	12OPERNNEWS LIST debe ser usado por algun IRCOP para listar los
	mensajes de noticias actuales. 12ADD y 12DEL solo podrán usarlos
	por 4Administradores de Services

###########################################################################
#
# Mensajes de ayuda de NickServ
#
##########################################################################

NICK_HELP
	4%S te permite registrar un nick y previene que otros
	hagan uso de él. Si el nick NO se utiliza durante
	12%d días, caducará el registro. Los siguientes comandos
	permiten el registro y mantenimiento de nicks; para
	utilizarlos, escribe 12/msg %S comando.
	
	Para más información sobre un comando especifico, escribe
	12/msg %S HELP comando.
	
	    12REGISTER   Registra un nick
	    12MAIL       Lista de mails permitidos para el registro del nick
	    12IDENTIFY   Identificarse con tu contraseña
	    12ACCESS     Modificar la lista de direcciones autorizadas
#	    12LINK       Hacer tu nick sea un alias de otro nick
#	    12UNLINK     Deshace un link de tu nick
	    12INFO       Muestra la informacion de un nick
	    12STATUS     Muestra el estado de un nick
	    12LIST       Lista los nicks registrados
	    12SET        Para ajustar opciones, incluyendo protección del nick
	    12GHOST      Desconectar el nick con una conexion fantasma
	    12RECOVER    Desconecta a otro usuario que está utilizando tu nick
	    12RELEASE    Toma custodia de tu nick después de utilizar el
	                comando RECOVER
	    12OPERS      Muestra los OPERS/ADMINS/IRCops on-line
	
	4NOTA: Este servicio esta diseñado para proveer un modo en
	que los usuarios de IRC aseguran que su identidad no sea
	suplantada. Su intención 4NO es para facilitar el "robo"
	de nicks o otras acciones mal intencionadas. Abuso de
	4%S resultara, por lo menos, de la perdida de el/los
	nick(s) abusivo(s).

NICK_HELP_EXPIRE_ZERO
	4%S te permite registrar un nick y previene que otros
	hagan uso de él. Los siguientes comandos permiten el registro
	y mantenimiento de nicks; para utilizarlos,
	escribe 12/msg %S comando.
	
	Para más información sobre un comando especifico, escribe
	12/msg %S HELP comando.
	
	    12REGISTER   Registra un nick
	    12MAIL       Lista de mails permitidos para el registro del nick
	    12IDENTIFY   Identificarse con tu contraseña
	    12ACCESS     Modificar la lista de direcciones autorizadas
#	    12LINK       Hacer tu nick sea un alias de otro nick
#	    12UNLINK	   Deshace un link de tu nick
	    12INFO       Muestra la informacion de un nick
	    12STATUS     Muestra el estado de un nick
	    12LIST       Lista los nicks registrados
	    12SET        Para ajustar opciones, incluyendo protección de nick
	    12GHOST      Desconectar el nick con una conexion fantasma
	    12RECOVER    Desconecta a otro usuario que eestá utilizando tu nick
	    12RELEASE    Toma custodia de tu nick después de utilizar el
	                comando RECOVER
	    12OPERS      Muestra los OPERS/ADMINS/IRCops on-line	 
	
	4NOTA: Este servicio esta diseñado para proveer un modo en
	que los usuarios de IRC aseguran que su identidad no sea
	suplantada. Su intención 4NO es para facilitar el "robo"
	de nicks o otras acciones mal intencionadas. Abuso de
	4%S resultara, por lo menos, de la perdida de el/los
	nick(s) abusivo(s).

NICK_HELP_REGISTER
	Sintaxis: 12REGISTER <direccion@correo.electronico>
	
	Registra tu nick la base de datos de 4%S.
	 
	La dirección de Email ha de ser una dirección REAL,
	para que puedas recibir el mensaje con la clave
	temporal de acceso en dicho buzón.
	 
	Una vez identificado siguiendo los pasos indicados
	en el mensaje que te enviaremos, podras utilizar los
	comandos 12SET y 12ACCESS para configurar los
	parámetros de tu nick como desees.

NICK_HELP_MAIL
	Para registrar el nick, el mail tiene que ser de una cuenta
	de un ISP Oficial, si no, no podrás registrar el nick.
	Consigue GRATIS una cuenta de correo de ISP's Oficiales y
	registra tu nick. Gracias.

NICK_HELP_IDENTIFY
	Sintaxis: 12IDENTIFY <contraseña>
	
	Notifica a 4%S que eres el verdadero dueño de este nick.
	Muchos de los comandos requieren que te indentifiques
	con este comando antes de poder utilizarlos. La
	contraseña debe ser la misma que utilizaste con el comando
	12REGISTER si no la has cambiado.

NICK_HELP_DROP
	Sintaxis: 12DROP
	
	Elimina tu nick de la base de datos de 4%S. Un nick
	que ha sido eliminado esta disponible para que cualquier
	persona lo vuelva a registrar.
	
	Para utilizar este comando , tienes que identificarte
	con tu contraseña (12/msg %S HELP IDENTIFY para mas
	información).

NICK_HELP_ACCESS
	Sintaxis: 12ACCESS ADD <mascara>
	          12ACCESS DEL <mascara>
	          12ACCESS LIST
	
	Modifica o muestra la lista de acceso para su nick. Esta
	es la lista de direcciones que 4%S reconocerá automáticamente
	como validas para utilizar este nick. Si desea utilizar este
	nick desde otra dirección, necesita enviar el comando
	12IDENTIFY para que 4%S te reconozca.
	
	Ejemplos:
	
	    12ACCESS ADD neo@*.tierrared.com
	        Permite el acceso al usuario 12neo de cualquier
	        ordenador en el dominio 12tierrared.com.
	
	    12ACCESS DEL neo@*.tierrared.com
	        Hace lo contrario de el comando anterior.
	
	    12ACCESS LIST
	        Muestra la lista de acceso.
	
NICK_HELP_LINK
	Sintaxis: 12LINK <nick> <contraseña>
	
	Crea un pseudónimo de tu nick, o tambien un 'alias'
	Cuando utilizas este comando, la lista de acceso de el
	nick que tienes es eliminada y reemplazada por la del
	pseudónimo de tu nick; todos los mensajes para el nick
	actual son agregados a la lista de mensajes del pseudónimo.
	(esto puede causar que el nick se exceda en su limite de
	mensajes, en este caso necesitarás borrar algunos de los
	mensajes antes de poder recibir nuevos mensajes para
	cualquiera de ambos nicks).
	
	Unas vez establecido el alias, tu nick será convertido
	transparentemente al nick nuevo en todas las bases de
	datos de Services, excepto para los comandos 12%S UNLINK y
	12DROP. Por ejemplo, puedes utilizar cualquiera de los
	nicks para leer los mismos mensajes (y los mensajes que se
	envían a cualquier de los nicks irán a la misma lista). Si
	se identifica para un nick, automáticamente se identificara
	para el otro. Si cualquiera de ambos nicks esta en la lista
	de acceso de un canal, ambos nicks tendrán los mismos
	privilegios y accesos.
	
	Para utilizar este comando, debes identificarte para
	tu nick actual (usando el comando 12IDENTIFY), y debe
	proporcionar la contraseña para el  nick del alias.

NICK_HELP_UNLINK
	Sintaxis: 12UNLINK
	
	Elimina el alias de tu nick. Cuando el alias se
	elimina, los modos de un nick y la lista de acceso del
	nick previamente linkado son copiados a su nick actual y
	pueden ser modificados independientemente.  Mensajes no son
	copiados; todos los mensajes permanecen con el nick
	anterior.

NICK_HELP_SET
	Sintaxis: 12SET <opción> <parámetros>
	
	Ajusta varios parámetros del nick. Una opción puede ser:
	
	    12PASSWORD   Ajusta la contraseña de tu nick
	    12LANGUAGE   Ajusta el lenguaje que Services utilizara cuando
	               te envié mensajes
	    12URL        Asocia un URL con tu nick
	    12EMAIL      Asocia una dirección de E-mail con tu nick
#	    12KILL       Activa/desactiva la protección de Kill
	    12CHANGE     Activa/desactiva la protección del nick
	    12SECURE     Activa/desactiva el modo SECURE para tu nick
	    12PRIVATE    Evita que su nick aparezca en 12/msg %S LIST
	    12HIDE       Esconde ciertas informaciones sobre tu nick
	
	Para utilizar este comando es necesario que te identifiques antes
	con tu contraseña (12/msg %S HELP IDENTIFY para más
	información).
	
	Escribe 12/msg %S HELP SET <opción> para más información
	sobre una opción especifica.

NICK_HELP_SET_PASSWORD
	Sintaxis: 12SET PASSWORD <nueva-contraseña>
	
	Cambia la contraseña que utiliza para identificarse como el
	dueño del nick.

NICK_HELP_SET_LANGUAGE
	Sintaxis: 12SET LANGUAGE <numero>
	
	Cambia el lenguaje que Services utiliza cuando envía
	mensajes a usted (por ejemplo cuando responde a un comando
	que usted envió). 12numero debe ser escogido de la siguiente
	lista de lenguajes soportados:

NICK_HELP_SET_URL
	Sintaxis: 12SET URL <url>
	
	Asocia un URL dado con tu nick. Este URL sera mostrado
	cuando solicite información de su nick con el comando 12INFO.

NICK_HELP_SET_EMAIL
	Sintaxis: 12SET EMAIL <dirección>
	
	Asocia la dirección de E-mail dada con tu nick. Esta
	dirección sera mostrada cuando alguien solicite información
	sobre su nick con el comando 12INFO.

NICK_HELP_SET_KILL
	Sintaxis: 12SET KILL {ON | QUICK | IMMED | OFF}
	
	Activa/desactiva la protección de kill para tu nick. Con
	protección de kill activada, si algún otro usuario intenta
	utilizar tu nick, se le dará un minuto para que cambie a
	otro, si no sera removido forzosamente de IRC por 4%S.
	
	Si seleccionas 12QUICK, el usuario solo tendrá 20 segundos para
	cambiar de nick en lugar de lo usual (60 segundos). Si
	seleccione 12IMMED, el usuario sera desconetcado (kill)
	inmediatamente 4sin ser avisado primero o darle una
	oportunidad de cambiar de nick, favor de no utilizar esta
	opción a menos que sea verdaderamente necesario. Los
	Administradores de la red pueden haber deshabilitado esta opción.

NICK_HELP_SET_CHANGE
	Sintaxis: 12SET CHANGE {ON | QUICK | IMMED | OFF}
	
	Activa/desactiva la protección de nick para tu nick. Con
	protección de nick activada, si algún otro usuario intenta
	utilizar tu nick, se le dará un minuto para que cambie a
	otro, si no será cambiado de nick forzosamente por 4%S.
	
	Si seleccionas 12QUICK, el usuario solo tendrá 20 segundos para
	cambiar de nick en lugar de lo usual (60 segundos). Si
	seleccione 12IMMED, el usuario sera cambiado el nick
	inmediatamente 4sin ser avisado primero o darle una
	oportunidad de cambiar de nick, favor de no utilizar esta
	opción a menos que sea verdaderamente necesario. Los
	Administradores de la red pueden haber deshabilitado esta opción.

NICK_HELP_SET_SECURE
	Sintaxis: 12SET SECURE {ON | OFF}
	
	Activa/desactiva las funciones de seguridad de 4%S para
	tu nick. Con 12SECURE activado, usted debe de enviar su
	contraseña antes de que se le reconozca como el dueño de el
	nick, sin importar si su dirección este o no en la lista de
	acceso. Sin embargo, si aparece en la lista de acceso, 12%S
	no lo desconectara automáticamente, independientemente de
#	como este la opción de 12KILL.
	como esté la opción de 12CHANGE.

NICK_HELP_SET_PRIVATE
	Sintaxis: 12SET PRIVATE {ON | OFF}
	
	Activa/desactiva la opción de privacidad de 4%S sobre tu
	nick. Con 12PRIVATE activado, tu nick no aparecerá en las
	listas de nicks generadas con el comando 12%S LIST.
	(Sin embargo, cualquiera que conozca tu nick puede obtener
	información usando el comando 12INFO.)

NICK_HELP_SET_HIDE
#	Sintaxis: 12SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
	Sintaxis: 12SET HIDE {EMAIL | QUIT} {ON | OFF}
	
	Permite evites que ciertas informaciones sean mostradas
	cuando alguien usa el comando 12%S INFO en tu nick. Usted
#	puede esconder su E-mail (12EMAIL), ultima mascara user@host
	puede esconder su E-mail (12EMAIL), o su ultimo mensaje de 
	salida (12QUIT). El segundo parámetro especifica que información
	debe ser mostrada (12OFF) o escondida (12ON).
#	(12USERMASK), o su ultimo mensaje de salida (12QUIT). El
#	segundo parámetro especifica que información debe ser mostrada
#	(12OFF) o escondida (12ON).

NICK_HELP_RECOVER
	Sintaxis: 12RECOVER <nick> [contraseña]
	
	Permite que recuperes tu nick si alguien mas lo ha
	tomado; esto es lo mismo que 4%S hace automáticamente si
#	alguien intenta utilizar un nick protegido con kill.
	alguien intenta utilizar un nick protegido con change.	
	
	Cuando usted envía este comando, 4%S conectara en línea a un
	usuario falso con el mismo nick que el usuario que usted
	desea recuperar. Esto causara que los servidores de IRC
	desconecten al otro usuario. El usuario falso permanecerá
	en línea por un minuto para asegurar que el otro usuario no
	se reconecte inmediatamente; después de ese minuto, usted
	puede tomar su nick. Alternativamente, use el comando
	12RELEASE (12/msg %S HELP RELEASE) para obtener tu nick
	mas rápido.
	
	Para usar el comando 12RECOVER para un nick, tu dirección
	actual como se muestra en un /WHOIS debe de estar en la
	lista de acceso de el nick, o usted debe de proporcionar la
	contraseña correcta para el nick.

NICK_HELP_RELEASE
	Sintaxis: 12RELEASE <nick> [contraseña]
	
	Ordena a 4%S eliminar cualquier espera en su nick
	causada por un kill automático de protección o por el uso de
	el comando 12RECOVER. Por defecto, la espera dura un minuto;
	este comando lo libera mas rápidamente.
	
	Para usar el comando 12RELEASE para un nick, su dirección
	actual como se muestra en un /WHOIS debe de estar en la
	lista de acceso del nick, o usted debe de proporcionar la
	contraseña correcta para el nick.

NICK_HELP_GHOST
	Sintaxis: 12GHOST <nick> [contraseña]
	
	Elimina una sesión "fantasma" de IRC que este utilizando tu
	nick. Una sesión "fantasma" es aquella que no esta
	realmente conectada, pero que un servidor de IRC acredita
	como activa por cualquier razón. Típicamente esto sucede si
	su ordenador se cuelga o su conexión a Internet se
	desconecta por un periodo corto mientras esta en IRC.
	
	Para usar el comando 12GHOST para un nick, tu dirección
	actual como se muestra en un /WHOIS debe de estar en la
	lista de acceso de el nick, o usted debe de proporcionar la
	contraseña correcta para el nick.

NICK_HELP_INFO
	Sintaxis: 12INFO <nick> [ALL]
	
	Muestra información sobre un nick dado, como el quien es
	el dueño, ultima hora y dirección utilizada, y las
	diferentes opciones del nick.
	
	Si especificas el parametro 12ALL, verás la información extra
	de tu nick, tales como nicks linkados a tu nick, founders,
	registros y akicks que tengas.

NICK_HELP_LIST
	Sintaxis: 12LIST <patrón>
	
	Lista todos los nicks registrados que concuerdan con un
	patrón dado en formato 12nick!user@host. Nicks con la opción
	de PRIVATE activada no serán mostrados.
	
	Ejemplos:
	
	    12LIST *!neo@tierrared.com
	         Lista los nicks registrados por neo@tierrared.com.
	
	    12LIST *Bot*!*@*
	        Lista todos los nicks registrados que contenga 12Bot
	        en su nombre (no importa mayúsculas).
		
	    12LIST *!*@*.tierrared.com
	        Lista todos los nicks registrados por usuarios del dominio 12tierrared.com.

NICK_HELP_STATUS
	Sintaxis: 12STATUS <nick1> <nick2>...
	
	Informa si el usuario de un nick es reconocido como el dueño
	del mismo. La respuesta tiene el siguiente formato:
	
	    12nick 12código-de-status
	
	donde 12nick es el nick enviado con el comando,
	12código-de-status es uno de los siguientes:
	
	    0 - usuario no esta conectado 12o nick no esta registrado
	    1 - usuario no reconocido como dueño del nick
	    2 - usuario reconocido por la lista de acceso solamente
	    3 - usuario reconocido por identificación con contraseña
	    4 - usuario con el nick suspendido
	
	Hasta 16 nicks pueden ser enviados con cada comando; el
	resto serán ignorados. No se genera mensaje de error si no
	se envía nick.

NICK_SERVADMIN_HELP
	
	Los siguientes comandos están disponibles para los
	4Operadores y Administradores de la RED:
	
	    12LISTEMAILS Lista todos los nicks asociados a un mail 
	    12LISTLINKS  Lista todos los links de un nick
	    12SENDPASS   Manda la contraseña al mail
	    12GETPASS    Muestra la contraseña para un nick
	    12DROP       Cancela el registro de un nick
	    12SUSPEND    Suspende el nick
	    12UNSUSPEND  Reactiva un nick suspendido
	    12FORBID     Evita que un nick sea utilizado
	    12UNFORBID   Libera un nick prohibido
	
	Los 4Administradores de la RED pueden usar los siguientes
	comandos sin necesidad de identificarse por el mismo:
	
	    12DROP, 12SET, 12ACCESS LIST, 12INFO ALL
	
	Lee la ayuda de cada comando para detalles especificos.

NICK_SERVADMIN_HELP_DROP
	Sintaxis: 12DROP [nick] <motivo>
	
	Sin parámetros, cancela el registro de tu nick de la base de
	datos de 4%S.

	Con un parámetro, cancela el registro de ese nick en la base
	de datos.
	 
	Limitado a 4Operadores de la RED.

NICK_SERVADMIN_HELP_SET
	
	Los 4Administradores de la RED pueden seleccionar la opción
	12NOEXPIRE, con la cual se puede prevenir que algunos nicks no
	expiren. Adicionalmente, los 4Administradores de la RED
	pueden establecer opciones para cualquier nick sin necesidad
	de proveer una contraseña, utilizando el formato
	12SET <nick> <opción> <parámetros>.

NICK_SERVADMIN_HELP_SET_NOEXPIRE
	Sintaxis: 12SET [nick] NOEXPIRE {ON | OFF}
	
	Define si el nick dado expirara. Si se define 12ON previene
	que el nick expire. Si no se incluye un nick, entonces se
	aplica a tu propio nick.
	
	Limitado a 4Administradores de la RED.

NICK_SERVADMIN_HELP_UNLINK
	
	Los 4Administradores de la RED pueden deslinkar algun nick sin
	necesidad de proveer una contraseña.

NICK_SERVADMIN_HELP_LISTEMAILS
	12Sintaxis: LISTEMAILS <email>
	
	Lista los nicks asociados al email dado.
	
	Limitado a 4Operadores de la RED.

NICK_SERVADMIN_HELP_LISTLINKS
	Sintaxis: 12LISTLINKS <nick> [ALL]
	
	Lista los nicks los cuales estan linkados al nick dado. Si has 
	puesto 12ALL, lista todos los nicks que estan linkados.
	
	Limitado a 4Operadores de la RED.

NICK_SERVADMIN_HELP_INFO
	
	Los 4Administradores de la RED pueden usar el parametro
	12ALL	con algun nick.

NICK_SERVADMIN_HELP_LIST
	Sintaxis: 12LIST <patrón> [FORBID] [NOEXPIRE] [SUSPEND]
	
	Lista todos los nicks registrados que concuerden con el
	patrón definido, en formato 12nick!usuario@host . Nicks
	con la opción 12PRIVATE activada solo serán mostrados a
	4Administradores de Services.
	
	Si has puesto la opcion 12FORBID o 12NOEXPIRE o 
	12SUSPEND solo lista los nicks, respectivamente, tienen 
	el flag 12FORBIDden o el flag 12NOEXPIRE o el flag
	12SUSPEND
	
	Estas opciones son limitados 4Administradores de Services.
	
	Ejemplos:
	
	    12LIST *!neo@tierrared.com
	        Lista todos los nicks registrados por neo@tierrared.com.

	    12LIST *Bot*!*@*
	        Lista todos los nicks registrados que contenga 12Bot
		en su nombre (no importa mayúsculas).
	
	    12LIST * NOEXPIRE
	        Lista todos los nicks registrados que no expirarán.

NICK_SERVADMIN_HELP_SENDPASS
	Sintaxis: 12SENDPASS <nick>
	
	Envia la contraseña del nick al mail asociado al nick.
	
	Limitado a 4Operadores de la RED.
	
NICK_SERVADMIN_HELP_GETPASS
	Sintaxis: 12GETPASS <nick>
	
	Muestra la contraseña para el nick dado.
	
	Limitado a 4Administradores de la RED.

NICK_SERVADMIN_HELP_SUSPEND
	Sintaxis: 12SUSPEND [+expiración] <nick> <motivo>
	
	Impide la identificación de un nick, y por lo tanto no poder
	usar los accesos de nicks y canales ni leer los mensajes. Se
	puede cancelar utilizando el comando 12UNSUSPEND.
	
	Mira la ayuda de 12OPER GLINE para más detalles sobre el formato
	del parametro opcional 12expiración.
	
	Limitado a 4Operadores de la RED.

NICK_SERVADMIN_HELP_UNSUSPEND
	Sintaxis: 12UNSUSPEND <nick>
	 
	Libera la suspensión de un nick, y por lo tanto permitir la
	identificación con el nick.
	
	Limitado a 4Operadores de la RED.

NICK_SERVADMIN_HELP_FORBID
	Sintaxis: 12FORBID <nick> <motivo>
	
	Prohibe el registro y la utilización de un nick. Se puede
	cancelar utilizando el comando 12UNFORBID.
	
	Limitado a 4Administradores de la RED.

NICK_SERVADMIN_HELP_UNFORBID
	Sintaxis: 12UNFORBID <nick>
	
	Levanta la prohibicion de uso de un nick para que se pueda
	usar y registrar el nick.
	
	Limitado a 4Administradores de la RED.


###########################################################################
#
# Mensajes de Ayuda de ChanServ
#
###########################################################################

CHAN_HELP
	4%S habilita a controlar varios aspectos de los canales. 4%S
	puede prevenir que usuarios malintencionados puedan "tomar" el
	control limitando a quién se permite privilegios de operador del
	canal. Los comandos disponibles son los siguientes. Para utilizarlos,
	escribe  12/msg %S comando. Para obtener más información de un
	comando específico, escribe 12/msg %S HELP comando.
	
#	    12REGISTER   Para registrar un canal
	    12IDENTIFY   Para identificarse como fundador del canal
	    12SET        Fija opciones e información del canal
	    12ACCESS     Modifica la lista de usuarios privilegiados
	    12LEVELS     Redefine los niveles de accesos
	    12AKICK      Mantiene la lista de Auto-Kick
#	    12DROP       Cancela la registración de un canal
	    12INFO       Muestra información de un canal
	    12LIST       Lista los canales registrados
	    12INVITE     Te invita a un canal
	    12DE|VOICE   Da o quita voz a un nick en un canal
	    12OP DEOP    Da o quita OP a un nick en un canal
	    12KICK       Kickea a un usuario en un canal
#	    12BAN        Poner un BAN en un canal
	    12UNBAN      Quitar BAN's de un canal
	    12GETKEY     Mostrar la key del canal si lo hay (modo +k)
	    12CLEAR      Reinicia los modos de un canal
#	    12RESET      Resetea el canal

	Para registrar un canal, tienes que hacerlo a traves de 4Reg
	escribe 12/msg Reg HELP para más información de cómo registrar
	un canal.

CHAN_HELP_EXPIRES
	
	Note que si un canal no es utilizado por 12%d días (es decir
	qué ningún usuario en la lista de acceso del canal entra en
	ese periodo de tiempo) será automáticamente cancelado.

CHAN_HELP_REGISTER
	Sintaxis: 12REGISTER <canal> <contraseña> <descripción>
	
	Registra un nuevo canal en la base de datos de 4%S.
	Para poder utilizar este comando, usted primero debe ser
	operador del canal que está tratando de registrar (1). La
	contraseña deberá ser utilizada con el comando 12IDENTIFY
	cuando necesite hacer modificaciones posteriores a opciones
	del canal.  El último parámetro, que 12debe ser incluido,
	es una descripción de los propósitos del canal.
	
	Cuando usted registra un canal, usted queda registrado como
	el "fundador" del canal. El fundador de un canal puede
	modificar cualquiera de las opciones del canal (excepto el
	nombre mismo del canal); 4%S le dará automáticamente
	privilegio de operador al fundador del canal cuando el/ella
	ingresen al canal.  Vea el comando 12ACCESS
	(12/msg %S HELP ACCESS) para obtener información de como
	dar privilegio de operadores a otros usuarios del canal.
	
	(1) AVISO: para poder registrar un canal, su nick debe estar
	registrado.  Si aún no lo registró, escriba
	12/msg %s HELP para obtener información de cómo hacerlo.

CHAN_HELP_IDENTIFY
	Sintaxis: 12IDENTIFY <canal> <contraseña>
	
	Este comando, lo identifica a usted ante 4%S como el
	fundador del 12canal. Muchos comandos requieren que usted
	utilice ESTE comando antes de poder utilizarlos. La
	contraseña debe ser la misma que se ingresó al momento de
	registrar el canal (comando 12REG REGISTRA).

CHAN_HELP_DROP
	Sintaxis: 12DROP <canal>
	
	Elimina el 12canal de la base de 4%S. Puede ser
	utilizado únicamente por el 12fundador del canal, quien deberá
	primeramente identificarse con el comando 12IDENTIFY.

CHAN_HELP_SET
	Sintaxis: 12SET <canal> <opción> <parámetros>
	
	Habilita al fundador del canal a definir varias opciones y
	otra información. El fundador, debe identificarse vía
	comando 12IDENTIFY antes de utilizar 12SET.
	
	Opciones disponibles:
	
	    12FOUNDER     Cambia el fundador del canal
	    12PASSWORD    Cambia la contraseña del fundador
	    12SUCCESSOR   Cambia el sucesor del canal
	    12DESC        Cambia la descripción del canal
	    12URL         Asocia una URL al canal
	    12EMAIL       Asocia una dirección de correo al canal
	    12ENTRYMSG    Fija un mensaje que será mostrado a los usuarios
	                 cuando entren al canal
	    12TOPIC       Cambia el Tema del canal
	    12KEEPTOPIC   Retiene el tema (topic) cuando el canal no está en uso
	    12TOPICLOCK   El Tema SOLO podrá ser cambiado vía SET TOPIC
	    12MLOCK       Fija los modos del canal en 'ON' u 'OFF'
	    12PRIVATE     Oculta el canal (no se ve cuando se utiliza el comando LIST)
	    12RESTRICTED  Restringe el acceso al canal
	    12SECURE      Activa los rasgos de seguridad de %S
	    12SECUREOPS   Control estricto de Status de operador
	    12SECUREVOICES Control estricto de Status de moderador
	    12LEAVEOPS    Nunca deopear a usuarios excepto con el comando DEOP
	    12LEAVEVOICES Nunca devoice a usuarios excepto con el comando DEVOICE
	    12MEMOALERT   Avisar cuando hay mensajes (memos) del canal
	    12UNBANCYBER  Permitir los desbaneos de cybers en los canales
	    12LEVELS      Evitar que usuarios con nivel inferior hagan
	                DEOP, DEVOICE o KICK a usuarios con mas nivel
	    12ISSUED      Modo DEBUG, Envia una noticia al canal sobre
	                los comandos usados
#	    12STAY        %S en el canal aunque no haya nadie en el canal
	
	Escribe 12/msg %S HELP opción para obtener más información
	de una opción en particular.

CHAN_HELP_SET_FOUNDER
	Sintaxis: 12SET <canal> FOUNDER <nick>
	
	Cambia el fundador del 12canal. El nick dado, que será el
	nuevo fundador del canal, debe estar registrado.

CHAN_HELP_SET_SUCCESSOR
	Syntax: 12SET <canal> SUCCESSOR <nick>
	
	Cambia el sucesor del canal. Si el nick del founder expira o
	es dropeado, el canal pierde el registro, con el sucesor se
	convierte en el nuevo founder del canal y evita la perdida del
	canal. Pero si el sucesor tiene demasiados canales registrados
	(12%d), el canal será dropeado al no haber ningun sucesor.
	El nick del sucesor debe estar registrado.

CHAN_HELP_SET_PASSWORD
	Sintaxis: 12SET <canal> PASSWORD <contraseña>
	
	Se utiliza para definir la contraseña que será utilizado
	para identificarse como el fundador del canal.

CHAN_HELP_SET_DESC
	Sintaxis: 12SET <canal> DESC <descripción>
	
	Fija la descripción del canal, la cual será mostrada cuando
	se utilicen los comandos 12LIST e 12INFO. Sea breve y concreto.

CHAN_HELP_SET_URL
	Sintaxis: 12SET <canal> URL [url]
	
	Asocia una URL al 12canal, la cual será visualizada cuando
	se solicite información del canal (vía comando 12INFO).
	Habitualmente se utiliza para indicar la dirección de la
	página web del canal. Si no se ingresa ninguna url, se
	borrará la que tenga actualmente el canal.

CHAN_HELP_SET_EMAIL
	Sintaxis: 12SET <canal> EMAIL [dirección]
	
	Asocia la dirección de correo dada al canal.  Esta dirección
	será mostrada cuando alguien solicite (vía comando 12INFO)
	información del canal. Es muy útil, por ejemplo, para que
	los usuarios tengan una vía de comunicación con el fundador
	y/u operadores del canal. Si no se proporciona una
	dirección de correo, se eliminará la que actualmente pueda
	tener el canal.

CHAN_HELP_SET_ENTRYMSG
	Sintaxis: 12SET <canal> ENTRYMSG [mensaje]
	
	Establece el mensaje que será enviado a los usuarios (vía
	/notice) cuando ellos ingresen al canal. Si 12mensaje no se
	ingresa, nada será enviado a los usuarios cuando ingresen.

CHAN_HELP_SET_TOPIC
	Sintaxis: 12SET <canal> TOPIC <texto>
		
	Causa que 4%S fije el tema del canal al indicado en
	12texto. Esta orden es muy útil en conjunción con
	12SET TOPICLOCK.

CHAN_HELP_SET_KEEPTOPIC
	Sintaxis: 12SET <canal> KEEPTOPIC {ON | OFF}
	
	Habilita o deshabilita la opción de 12retención del tema para
	el canal. Cuando 12retención del tema está en ON
	(habilitada), el tema del canal será recordado por 4%S
	aún después que el último usuario se haya retirado, y se
	restaurará la próxima vez que alguien ingrese al canal.

CHAN_HELP_SET_TOPICLOCK
	Sintaxis: 12SET <canal> TOPICLOCK {ON | OFF}
	
	Habilita o deshabilita la opción para 12trabar el tópico del
	canal. Cuando 12trabar el tópico está en ON, 4%S no
	habilitará el cambio del tema (tópico) excepto vía 12SET
	TOPIC.

CHAN_HELP_SET_MLOCK
	Sintaxis: 12SET <canal> MLOCK <modos>
	
	Fija los distintos modos para el canal. 4%S lo habilita a
	usted para definir determinados modos del canal y que queden
	siempre habilitados (o no).  Los modos que pueden ser
	fijados son: i, k, l, m, n, p, s, y t; cada
	uno de estos modos puede estar activado (ON), desactivado
	(OFF) o no fijado.  Los distintos modos se indican
	exactamente como si se utilizase el comando 12/MODE; esto es,
	modo seguido de + indica activado (ON), modo seguido de -
	indica desactivado (OFF).
	
	4Cuidado!:  Si usted fija un modo protegido por contraseña,
	como en el segundo ejemplo, también deberá fijar la opción
	12RESTRICTED para el canal (vea 12HELP SET RESTRICTED), o
	cualquiera que ingrese al canal cuando el mismo esté vacío,
	verá la contraseña!!
	
	Ejemplos:
	
	    12SET #canal MLOCK +nt-iklps
	       Activa los modos n y t, y desactiva los modos i, k,
	       l, p, y s.  El modo m puede ser activado o desactivado.
	
	    12SET #canal MLOCK +knst-ilmp my-key
	       Activa los modos k, n, s, y t.
	       Desactiva los modos i, l, m, y p.
	       También establece "my-key" como la contraseña del canal.
	
	    12SET #canal MLOCK +
	       Elimina los modos activos; todos los modos del canal
	       pueden ser libremente activados o desactivados.

CHAN_HELP_SET_PRIVATE
	Sintaxis: 12SET <canal> PRIVATE {ON | OFF}
	
	Habilita o deshabilita la opción de 12privado para el canal.
	Cuando esta opción está activada, el comando 12/msg %S LIST no
	incluirá el canal en ninguna lista.

CHAN_HELP_SET_RESTRICTED
	Sintaxis: 12SET <canal> RESTRICTED {ON | OFF}
	
	Habilita o deshabilita la opción de 12acceso restringido para
	el canal. Cuando el 12acceso restringido está activo (ON),
	usuarios que normalmente no tienen privilegio de operadores
	cuando entran al canal (usuarios con nivel de acceso
	negativo y, si 12secure ops está activada, usuarios que NO
	están en la lista de acceso) serán expulsados (y se les
	prohibirá el acceso) al canal.

CHAN_HELP_SET_SECURE
	Sintaxis: 12SET <canal> SECURE {ON | OFF}
	
	Habilita o deshabilita la seguridad de 12%S para el
	canal. Cuando 12SECURE está 12ACTIVO, SOLO los usuarios que
	tienen registrado sus nicks con 4%s y se han
	IDENTIFICADO con sus respectivas contraseñas tendrán acceso
	al canal si es que figuran en la lista de 12ACCESS.

CHAN_HELP_SET_SECUREOPS
	Sintaxis: 12SET <canal> SECUREOPS {ON | OFF}
	
	Habilita o deshabilita la opción de 12operadores seguros para
	el canal. Cuando 12operadores seguros está activada (ON),
	usuarios que 12NO estén en la lista de usuarios del canal NO
	podrán obtener status de operadores

CHAN_HELP_SET_SECUREVOICES
	Sintaxis: 12SET <canal> SECUREVOICES {ON | OFF}
	
	Habilita o deshabilita la opción de 12moderadores seguros para
	el canal. Cuando 12moderadores seguros está activada (ON),
	usuarios que 12NO estén en la lista de usuarios del canal NO
	podrán obtener status de moderadores

CHAN_HELP_SET_LEAVEOPS
	Sintaxis: 12SET <canal> LEAVEOPS {ON | OFF}
	
	Habilita o deshabilita la opción de 12leave ops para el
	canal. Cuando 12leave ops está activada (ON),
	4%S no dejara nunca de-opear a usuarios en el canal
	excepto con el comando 12DEOP.

CHAN_HELP_SET_LEAVEVOICES
	Sintaxis: 12SET <canal> LEAVEVOICES {ON | OFF}
	
	Habilita o deshabilita la opción de 12leave voices para el
	canal. Cuando 12leave voices está activada (ON),
	4%S no dejara nunca de-opear a usuarios en el canal
	excepto con el comando 12DEVOICE.

CHAN_HELP_SET_OPNOTICE
	Syntax: 12SET <canal> ISSUED {ON | OFF}
	
	Habilita o deshabilita la opción de 12issued para el
	canal. Cuando 12issued está activada (ON),
	4%S enviará un notice al canal cuando los usuarios usen los
	comandos en el canal.

CHAN_HELP_SET_STAY
	Syntax: 12SET <canal> STAY {ON | OFF}
	 
	Habilita o deshabilita la opción de 12stay para el
	canal. Cuando 12stay está activada (ON),
	4%S entrara en el canal y estara todo el tiempo aunque
	no haya nadie en el canal.

CHAN_HELP_SET_MEMOALERT
	Sintaxis: 12SET <canal> MEMOALERT {ON | OFF}
	
	Habilita o deshabilita la opción de 12aviso de mensajes
	para el canal. Cuando 12aviso de mensajes está activada (ON),
	4%s avisará los mensajes que tiene el canal a los usuarios 
	con nivel de MEMO-READ.

CHAN_HELP_SET_UNBANCYBER
	Sintaxis: 12SET <canal> UNBANCYBER {ON | OFF}
	
	Habilita o deshabilita la opción de 12unban por Cyber para
	el canal. Cuando 12UNBANCYBER está activada (ON), 4%S
	permitirá que los cybers pueda desbanear su IP en el canal
	a través de 4%Cyber.

	Esta opción en canales oficiales sólo pueden cambiarlo los
	4Administradores de la Red.	

CHAN_HELP_SET_LEVELS
	Sintaxis: 12SET <canal> LEVELS {ON | OFF}
	
	Habilita o deshabilita la opción de LEVELS para el canal.
	Cuando LEVELS está activada (ON), %S no dejará que usuarios
	hagan DEOP o DEVOICE o KICK a usuarios con nivel igual o
	superior al suyo.
CHAN_HELP_ACCESS
	Sintaxis: 12ACCESS <canal> ADD <nick> <nivel>
	          12ACCESS <canal> DEL {nick | posición-numero, list}
#	          12ACCESS <canal> CLEAR
	          12ACCESS <canal> LIST [mascara]
	          12ACCESS <canal> COUNT
	
	Mantiene la 12lista de accesos del canal. La lista de accesos
	establece que usuarios están habilitados a ser operadores
	del canal o acceder a comandos de 12%S en el canal. Se pueden
	establecer diferentes niveles de usuarios para acceder a
	diferentes privilegios; utilice 12/msg %S HELP ACCESS LEVELS
	para obtener información mas específica. Cualquier nick que
	no esté en la lista de acceso tiene nivel de usuario 0
	(cero).
	
	El comando 12ACCESS ADD agrega al 12nick con el 12nivel dado a la
	lista de acceso; si el usuario ya existe en la lista, se
	reemplazará su 12nivel. El 12nivel especificado debe ser menor
	que el que tiene el usuario que está ingresando el comando,
	y si el 12nick está actualmente en la lista, el nivel actual
	de dicho nick debe ser menor que el nivel del usuario que
	está ingresando el comando.
	
	El comando 12ACCESS DEL elimina un usuario de la lista de
	accesos. Se puede eliminar un usuario ingresando el nick o
	ingresando el número que ocupa en la lista de accesos.
	
#	El comando 12ACCESS CLEAR borra todos los usuarios de la 
#	lista de accesos. Sólo accesible para el founder.
#	
	El comando 12ACCESS LIST muestra la lista de accesos al canal;
	se pueden utilizar caracteres comodines o mascaras, en cuyo
	caso solo las coincidencias concurrentes serán listadas.

	  ACCESS #channel LIST 2-5,7-
	      Lists access entries numbered 2 through 5 and
	      7 through 9.9 
	
	El comando 12ACCESS COUNT muestra el número de registros que
	tiene la lista de accesos del canal. Necesitas tener el nivel
	de ACC-LIST para visualizar la lista.

CHAN_HELP_ACCESS_LEVELS
	12Niveles de acceso para usuarios
	
	Por defecto, los siguientes niveles son definidos:
	
	   12Founder   Acceso FULL a las funciones de 12%S.
	                 Privilegio de operador al ingresar al canal.
	                 Note que únicamente una sola persona puede
	                 tener acceso de fundador del canal (no se
	                 puede dar acceso de founder con el comando
	                 ACCESS).
	   12    499   Acceso al comando SET, OPDEOP, INVITE, UNBAN, AKICK, ACC, MEMO;
	                 operador automático al ingresar.
	   12    450   Acceso al comando OPDEOP, INVITE, UNBAN, AKICK, ACC, MEMO;
	                 operador automático al ingresar.
	   12    300   Acceso al comando OPDEOP, INVITE, UNBAN,
	                 operador automático al ingresar.
	   12    100   Estado de VOZ automático (+v).
	   12      0   No tiene privilegios especiales; puede obtener
	                 status de operador dado por otro operador
	                 (a menos que secure-ops esté activado).
	   12     <0   No puede ser operador, ni entrar al canal.
	
	Estos niveles pueden ser cambiados, o nuevos pueden ser
	agregados utilizando el comando 12LEVELS; escriba
	12/msg %S HELP LEVELS para información.

CHAN_HELP_AKICK
	Sintaxis: 12AKICK <canal> ADD <mascara> [razón]
	          12AKICK <canal> DEL <mascara>
	          12AKICK <canal> LIST [mascara]
	          12AKICK <canal> VIEW [mascara]
	          12AKICK <canal> ENFORCE
	          12AKICK <canal> COUNT
	
	Definimos AKICK como "Expulsión automática".
	Definimos BAN como "Entrada prohibida".
	
	Este comando, mantiene la lista de AKICK del canal. Si un
	usuario está en la lista de AKICK e intenta entrar al canal,
	12%S automáticamente agrega dicho usuario a la lista BAN
	del canal, y luego lo expulsa del canal.
	
	El comando 12AKICK ADD agrega un usuario a la lista de AKICK.
	Si una 12razón es dada con el comando, entonces la razón será
	utilizada por 12%S cuando expulse a dicho usuario; si
	no, el mensaje que se utilizará por defecto, es "Has sido
	baneado del canal".
	
	El comando 12AKICK DEL elimina al usuario de la lista de
	AKICK. Este comando no remueve el BAN que pueda existir en
	el canal, el cual deberá ser removido manualmente.
	
	El comando 12AKICK LIST muestra la lista de usuarios en la
	lista de AKICK. Opcionalmente, solo lista aquellos
	suministrados con la mascara dada.
	
	El comando 12AKICK VIEW contiene más información que el
	AKICK LIST, mostrando el autor del akick.
	
	El comando 12AKICK ENFORCE causa que 12%S impide que los
	usuarios con mascara de AKICK en la lista de AKICK estén en 
	el canal. Es parecido a CLEAR USERS, pero que solo afecta a
	los que tienen AKICK.

CHAN_HELP_LEVELS
	Sintaxis: 12LEVELS <canal> SET <tipo> <nivel>
	          12LEVELS <canal> {DIS | DISABLE} <tipo>
	          12LEVELS <canal> LIST
	          12LEVELS <canal> RESET
	
	El comando 12LEVELS permite un control fino sobre los accesos
	numéricos utilizados por los canales.  Con este comando,
	usted puede definir los niveles requeridos para muchas de
	las funciones de 12%S. Los comandos 12SET FOUNDER,
	12SET PASSWORD, así como éste comando están siempre
	restringidos al fundador.
	
	12LEVELS SET habilita el acceso para una función o grupo de
	funciones a ser modificadas.
	
	12LEVELS DISABLE (o 12DIS en forma abreviada) deshabilita un
	privilegio automático, o deshabilita el acceso para
	cualquier otro que no sea el fundador del canal.
	
	12LEVELS LIST muestra los niveles actuales para cada función o
	grupo de funciones.
	
	12LEVELS RESET vuelve todos los niveles a sus valores por
	defecto, los mismos que cuando se registra por primera vez
	un canal (vea 12HELP ACCESS LEVELS).
	
	Para una lista de las funciones que pueden ser establecidas,
	utilice el comando 12HELP LEVELS DESC.

CHAN_HELP_LEVELS_DESC
	La siguiente lista muestra los valores/funciones por
	defecto. Note que los niveles para AUTODEOP y NOJOIN son
	los máximos niveles, mientras que todos los demás, son los
	mínimos.

CHAN_HELP_LEVELS_DESC_FORMAT
	    %-*s  %s

CHAN_HELP_INFO
	Sintaxis: 12INFO <canal> [ALL]
	
	Provee información acerca del 12canal (o informa que no está
	registrado). Lista el fundador, hora y fecha de
	registración, última vez que se utilizó, descripción, y
	modos del canal (si los hubiese). Si estas identificado como
	el founder del canal, puedes usar el parametro 12ALL, para
	ver el sucesor y el mensaje de entrada del canal.

CHAN_HELP_LIST
	Sintaxis: 12LIST <especificación>
	
	Lista todos los canales que coincidan con la especificación
	dada. Canales con la opción PRIVATE activada, no son
	listados.

CHAN_HELP_OP
	Sintaxis: 12OP <canal> <nick>
	
	Convierte en Operador al usuario indicado en el canal
	indicado. Por defecto, está limitado a quienes posean nivel
	300 o mayor en el canal.

CHAN_HELP_DEOP
	Sintaxis: 12DEOP <canal> <nick>
	
	Quita el estado de Operador al usuario indicado en el canal
	indicado. Por defecto, está limitado a quienes posean nivel
	300 o mayor en el canal.

CHAN_HELP_VOICE
	Sintaxis: 12VOICE <canal> <nick>
	 
	Convierte en moderador al usuario indicado en el canal
	indicado. Por defecto, está limitado a quienes posean nivel
	100 o mayor en el canal.

CHAN_HELP_DEVOICE
	Sintaxis: 12DEVOICE <canal> <nick>
	 
	Quita el estado de moderador al usuario indicado en el canal
	indicado. Por defecto, está limitado a quienes posean nivel
	100 o mayor en el canal.

CHAN_HELP_INVITE
	Sintaxis: 12INVITE <canal>
	
	Le dice a 4%S que lo invite a usted al canal indicado.
	Por defecto, solo funciona si su nivel de acceso en dicho
	canal es 300 o mayor.

CHAN_HELP_KICK
	Sintaxis: 12KICK <canal> <nick> [razón]
	 
	Le dice a 4%S que kickee del canal a una persona.
	Por defecto, solo funciona si su nivel de acceso en dicho
	canal es 300 o mayor.

#CHAN_HELP_BAN
#	Sintaxis: 12BAN <canal> <mask>
#	 
#	Le dice a 12%S que banee del canal a una mascara.
#	Por defecto, solo funciona si su nivel de acceso en dicho
#	canal es 300 o mayor.

CHAN_HELP_UNBAN
	Sintaxis: 12UNBAN <canal>
	
	Le dice a 12%S que elimine todos los accesos prohibidos
	previniendo su ingreso a dicho canal. Por defecto, solo
	funciona si su nivel de acceso en dicho canal es 300 o mayor.


CHAN_HELP_GETKEY
	Sintaxis: GETKEY <canal>
	
	Le dice a %S que muestre la key del canal, si la tiene, es decir, 
	que esta en modo +k. Por defecto solo funciona si su nivel de
	acceso en dicho canal es 200 o mayor.

CHAN_HELP_CLEAR
	Sintaxis: 12CLEAR <canal> <opcion>
	
	Le dice a 12%S que elimine ciertos parámetros del canal.
	que puede ser uno de los siguientes:

	     12MODES   Resetea todos los modos del canal (ejemplo,
	                 limpia los modos i,k,l,m,n,p,s,t).
	     12BANS    Elimina todos los accesos prohibidos al canal.
	     12OPS     Elimina (quita) el privilegio de operador a
	                 todos los operadores (modo +o) del canal.
	     12VOICES  Elimina (quita) el privilegio de "voz" (modo
	                 +v) a cualquiera del canal que lo tuviese.
	     12USERS   Elimina (Patea -kicks-) TODOS los usuarios del
	                 canal.
	     12TOPIC   Resetea el topic.
	
	Por defecto, su nivel de acceso en el canal debe ser al
	menos 499 para utilizar este comanndo.

CHAN_HELP_RESET
	Sintaxis: 12RESET <canal> <opcion>
	 
	Resetea el canal para sincronizar el canal en casos de desincroni-
	zación del canal.
	 
	Por defecto, su nivel de acceso en el canal debe ser al
	menos 499 para utilizar este comando.


CHAN_SERVADMIN_HELP
	
	Los siguiente comandos están disponibles para los
	4Operadores de los Servicios:

	    12REGISTER   Para registrar un canal
	    12GETPASS    Devuelve la contraseña del fundador
	    12DROP       Cancela la registración de un canal
	    12SUSPEND    Suspende un canal
	    12UNSUSPEND  Reactiva un canal suspendido
	    12FORBID     Previene que un canal pueda ser utilizado
	    12UNFORBID   Libera la prohibicion de un canal prohibido
	    12STATUS     Devuelve el nivel de acceso actual de un
	               usuario en un canal
	
	Los 4Administradores de Servicios también pueden eliminar
	cualquier canal sin necesidad de identificarse vía
	contraseña, y pueden ver la lista de accesos, la lista de
	AKICK, y listar los valores de nivel (LEVELS) de cualquier
	canal.

CHAN_SERVADMIN_HELP_DROP
	Sintaxis: 12DROP <canal> <motivo>
	
	Elimina un canal de la lista de 4%S. Únicamente
	4Administradores de Servicios pueden eliminar un canal para
	lo cual ellos no necesitan identificarse.

CHAN_SERVADMIN_HELP_SET
	
	Administradores de Services también pueden definir la opción
	12NOEXPIRE, con la cual algún canal se puede prevenir que
	expire; y la opcion 12OFICIAL para activar el flag de Canal
	Oficial al canal. Adicionalmente, los Administradores de Services
	pueden definir opciones para cualquier canal sin necesidad
	de identificarse con contraseña para ese canal.

CHAN_SERVADMIN_HELP_SET_OFICIAL
	Sintaxis: 12SET <canal> OFICIAL {ON | OFF}
	
	Define si el canal dado es un Canal Oficial de Tierrared o Tierrared.com.
	
	Limitado a 4Administradores de la RED.

CHAN_SERVADMIN_HELP_SET_NOEXPIRE
	Sintaxis: 12SET <canal> NOEXPIRE {ON | OFF}
	
	Define si el canal dado expirara. Si se define 12ON previene
	que el canal expire.

	Limitado a 4Administradores de la RED.

CHAN_SERVADMIN_HELP_INFO
	
	4Operadores de Services pueden usar el parametro 12ALL con
	algun canal.

CHAN_SERVADMIN_HELP_LIST
	Sintaxis: 12LIST <especificación>
	
	Lista todos los canales que coinciden con la especificación
	dada. Los canales con la opción PRIVATE activada solo serán
	mostrados a los 4Administradores de Servicios.

CHAN_SERVADMIN_HELP_GETPASS
	Sintaxis: 12GETPASS <canal>
	
	Devuelve la contraseña del canal dado.
	
	Limitado a 4Administradores de la RED.


CHAN_SERVADMIN_HELP_SUSPEND
	Sintaxis: 12SUSPEND [+expiracion] <canal> <motivo>
	
	Suspende el canal temporalmente para ke no sea utilizado.
	
	Mira la ayuda de 12OPER GLINE para más detalles sobre el formato
	del parametro opcional 12expiración.
	
	Limitado a 4Operadores de la RED.


CHAN_SERVADMIN_HELP_UNSUSPEND
	Sintaxis: 12UNSUSPEND <canal>
	
	Reactiva un canal suspendido para que pueda ser utilizado
	
	Limitado a 4Operadores de la RED.


CHAN_SERVADMIN_HELP_FORBID
	Sintaxis: 12FORBID <canal> <motivo>
	
	Deshabilita a cualquiera para utilizar o registrar el canal
	dado. Puede ser cancelado con el comando 12UNFORBID.
	
	Limitado a 4Administradores de la RED.

CHAN_SERVADMIN_HELP_UNFORBID
	Sintaxis: 12UNFORBID <canal>
	
	Levanta la prohibicion de utilizar o registrar el canal
	dado.
	
	Limitado a 4Administradores de la RED.


CHAN_SERVADMIN_HELP_STATUS
	Sintaxis: 12STATUS <canal> [nick]
	
	Devuelve el nivel de acceso actual del nick dado en el canal
	dado. La respuesta es de la forma:
	
	    12STATUS canal nick nivel-de-acceso
	
	Si no se especifica el nick, mostrara el status del canal
	si es que existe en el canal, con los modos, topics, ops,
	voices y bans.
	
	Limitado a 4Operadores de la RED.

###########################################################################
#
# MemoServ help messages (Mensajes de ayuda de MemoServ)
#
###########################################################################

MEMO_HELP
	4%S es una utilidad que permite a usuarios de IRC
	enviar mensajes cortos a otros usuarios de IRC,
	independientemente de si están en línea o no, igualmente se
	puede enviar mensajes a canales(*). Ambos nicks (remitente
	y destinatario) deben de estar registrados, así mismo el
	canal debe de estar registrado si se desea enviar un mensaje
	a este.
	
	Comandos de 4%S incluyen:
	
	    12SEND   Envía un mensaje a un nick/canal
	    12CANCEL Cancela el ultimo mensaje enviado
	    12LIST   Lista todos tus mensajes
	    12READ   Lee un mensaje
	    12DEL    Borra un mensaje (o todos)
	    12SET    Define opciones relacionadas con mensajes
	
	Escriba 12/msg %S HELP comando para ayuda mas especifica
	de los comandos arriba mencionados.
	
	(*) Por defecto, cualquier usuario con al menos nivel 450 de
	    acceso en un canal puede leer los mensajes de ese canal.
	    Esto puede ser cambiado con el comando 12%s LEVELS.
MEMO_HELP_SEND
	Sintaxis: 12SEND { nick | canal } <memo-texto>
	
	Envía un mensaje al usuario especificado. Dicho usuario
	recibirá una noticia de que tiene un nuevo mensaje. Lo
	recibirá inmediatamente si se encuentra en línea, o si no al
	momento de identificarse la próxima vez que se conecte.
	
	Ejemplo: /msg %S SEND Anonimus Muy bueno tu trabajo de traducción! ;)

MEMO_HELP_CANCEL
	Sintaxis: 12CANCEL { nick | canal }
	
	Cancela el último mensaje que enviaste al usuario o canal
	dicho, si el mensaje aún no ha sido leido.

MEMO_HELP_LIST
	Sintaxis: 12LIST [NEW]
	
	Lista los memos que usted tenga actualmente.
	Si se indica el parámetro 12NEW, solo los nuevos mensajes
	(los no	leídos) serán mostrados. Los memos no leídos están
	marcados con un "*" a la izquierda del numero del mensaje.

MEMO_HELP_READ
	Sintaxis: 12READ {numero | LAST}
	
	Muestra el contenido del memo indicado en 12número, o el
	ultimo mensaje (por ejemplo, el recibido mas recientemente)
	si el parámetro 12LAST es dado EN VEZ DE 12número.

MEMO_HELP_DEL
	Sintaxis: 12DEL {num[-num][,num...] | ALL}
	
	Si un número 12num es dado, elimina dicho mensaje.
	Usted puede reemplazar un único numero por un rango de 
	números para eliminar múltiples mensajess simultáneamente,
	tal como se verá en el segundo ejemplo.
	
	Si se ingresa 12ALL se eliminaran TODOS los memos.
	
	Ejemplos:
	
	   12DEL 1
	      Elimina tu primer mensaje.
	
	   12DEL 2-5,7-9
	      Elimina los mensajes de 2 a 5 y de 7 a 9.

MEMO_HELP_SET
	Sintaxis: 12SET <opción> <parámetros>
	
	Establece varias opciones para los mensajes. Las opciones
	pueden ser:
	
	    12NOTIFY      Establece CUANDO debe ser notificado de
	                    nuevos mensajes
	    12LIMIT       Establece el MAXIMO número de mensajes que
	                    usted puede recibir
	    12FULLMEMO    Establece el mensaje que %S mostrara cuando
	                     el buzon está lleno
	
	Escriba 12/msg %S HELP SET opción para obtener más
	información acerca de la opción específica.

MEMO_HELP_SET_NOTIFY
	Sintaxis: 12SET NOTIFY {ON | LOGON | NEW | OFF}
	
	Establece CUANDO debe ser notificado de nuevos mensajes:
	
	    12ON      Será notificado cuando se conecte, cuando quite
	                su modo /AWAY y cuando un mensaje le sea
	                enviado estando usted conectado.
	    12LOGON   Será notificado únicamente cuando se conecte,
			y cuando quite su modo /AWAY.
	    12NEW     Será notificado solamente cuando le sean
	                enviados.
	    12OFF     Usted no recibirá ningún tipo de notificación de
	                mensajes.
	
	12ON es básicamente la combinación de 12LOGON y 12NEW
	simultáneamente.

MEMO_HELP_SET_LIMIT
	Sintaxis: 12SET LIMIT [canal] <limite>
	
	Establece el máximo numero de mensajes que usted está
	habilitado a tener. Si establece 12limite a 0 (cero)
	nadie podrá enviarle mensajes a usted. De todos modos,
	usted no puede establecer 12limite más alto que 12%d.

MEMO_HELP_SET_FULLMEMO
	Sintaxis: 12SET FULLMEMO [mensaje]
	
	Establece el mensaje que 4%S mostrará al usuario que intenta
	mandarte mensaje pero que tu buzón está lleno. Si no especificas
	el mensaje, deshabilitas la funcion.

MEMO_HELP_INFO
	Sintaxis: 12INFO [canal]
	
	Muestra información de la cantidad de mensajes que usted
	tiene, cuantos de ellos no han sido leídos, y la cantidad
	de memos que usted puede recibir.

MEMO_SERVADMIN_HELP_SET_LIMIT
	Sintaxis: 12SET LIMIT [usuario] {limite | NONE} [HARD]
	
	Establece el máximo número de mensajes que un 12usuario
	puede tener. Estableciendo el 12limite a 0 (cero), previene
	que dicho 12usuario pueda recibir mensajes; estableciéndolo
	a 12NONE, habilita al 12usuario a recibir y mantener
	tantos mensajess como el desee. Si usted NO ESPECIFICA 12usuario
	SU propio límite es el que se establece.
	
	Agregando el parámetro 12HARD, previene que el 12usuario
	pueda cambiar dicho límite. No agregando 12HARD tiene el efecto
	opuesto, habilitando al usuario a cambiar el límite (aun si
	previamente había sido establecido con el parámetro HARD).
	
	El uso del comando 12SET LIMIT está limitado a los
	4Administradores de la RED. Otros usuarios solo pueden
	establecer sus propios límites, no pueden remover sus
	límites, no pueden establecer límites superiores a 12%d, y no
	pueden establecer el limite 12HARD.

MEMO_SERVADMIN_HELP_INFO
	Sintaxis: 12INFO [usuario]
	
	Sin parámetros, muestra información del número de mensajes
	que tu tienes, cuantos están sin leer, y cuantos memos puedes
	recibir.
	
	Con el parámetro 12usuario, muestra la misma información, pero
	del 12usuario especificado. Esta opción está limitada
	únicamente a los 4Administradores de la RED.

###########################################################################
#
# Mensajes de ayuda de CyberServ
#
###########################################################################

CYBER_HELP
	4%S es un servicio que la red pone a disposición de los
	responsables de cybers, universidades, etc.. con el fin de
	proporcionar una mayor facilidad a dichos locales y sus
	múltiples conexiones simultaneas (o también llamados clones)
	que tiene. Para utilizar los comandos escribe 12/msg %S comando.
	
	Para mayor informacion sobre un comando especifico escribe
	12/msg %S HELP comando.
	
	    12INFO       Informa de los clones disponibles a tu ip
	    12CONTRATA   Información de como contratar clones
	    12ACTUALIZA  Para en casos de ip dinámica, actualizar la
	                ip y asi tener derecho a los clones
	    12KILL       Killea a un Usuario de TU Cyber
	    12GLINE      Glinea a un Usuario de TU Cyber
	    12UNBAN      Desbanea la IP de TU Cyber de un canal.
	    12GLOBAL     Manda mensajes a todos los usuarios de TU Cyber
	
	4NOTA: Este servicio esta diseñado para proveer a los responsables
	de los cybers.. del estado de sus conexiones y de protección en la
	red. Su intencion 4NO es para fomentar el mal uso. El abuso de
	4%S resultará la retirada del servicio al cyber o centro.


CYBER_HELP_INFO
	Sintaxis: 12INFO
	
	Muestra información sobre la conexion que tengas.
	Si lo usa un usuario normal, mostrará las conexiones que
	tiene y el limite máximo.
	Si lo usa un administrador de cyber, mostrará además de lo
	anterior, la fecha de expiración de la iline, información
	que 4%S dispone sobre tu cyber.


CYBER_HELP_CONTRATA
	12Contratación de clones.
	
	En esta red, los cybers, universidades, centros de enseñanza,
	etc.. tienen derecho a tener un número de clones (un clon es
	una conexion a la red). No se necesita IP fija para los clones.
	Para solicitarlos, tienes que acudir a la siguiente dirección:
	12http://www.tierrared.com/clones/
	Y cubrir el formulario para la solicitud de clones y en menos
	de 24 horas tendrás los clones concedidos.

CYBER_HELP_ACTUALIZA
	Sintaxis: 12ACTUALIZA
	
	Sólo para en conexiones con ip dinámica, permite actualizar
	la ip dinámica de tu conexion para la ip de la iline concedida.
	
	Limitado a los 4Administradores de Cyber


CYBER_HELP_KILL
	Sintaxis: 12KILL <nick> [motivo]
	
	Killea al usuario on-line de tu cyber.
	
	Limitado a 4Admininistradores de Cybers.

CYBER_HELP_GLINE
	Sintaxis: 12GLINE <nick> [motivo]
	
	Glinea durante 5 minutos al usuario on-line de tu cyber. Se
	recomienda que todos los ordenadores de tu cyber tengan idents
	(usernames) diferentes ya que el gline es al user@host completo.
	
	Limitado a 4Administradores de Cybers.

CYBER_HELP_UNBAN
	Sintaxis: 12UNBAN <canal>
	
	Le dice a 4%S que elimine todos los accesos prohibidos
	previniendo el ingreso de tu Cyber a dicho canal. Solo podras
	desbanear en canales registrados que sean oficiales o que tengan
	la opcion UNBANCYBER de Chan activado en el canal dicho.
	
	Limitado a 4Administradores de Cybers.

CYBER_HELP_GLOBAL
	Sintaxis: 12GLOBAL <mensaje>
	
	Manda un mensaje a todos los clientes de tu cyber, para notificar
	de cualquier cosa.
	
	Limitado a 4Administradores de Cybers.

CYBER_HELP_SET
	Sintaxis: SET ....
	
	No hay nada....


CYBER_HELP_LIST
	Sintaxis: 12LIST <patron>
	
	No hay nada...

CYBER_SERVADMIN_HELP
	
	Los siguientes comandos están disponibles para los
	4Operadores de Servicios:
	
	    12VERIFY     Verifica si un nick tiene Iline
	    12LIST       Lista los ilines
	    12CLONES     Informacion sobre clones
	
	Comandos disponibles para 4Administradores de Servicios:
	
	    12ILINE      Añade clones a un determinado nick/host
	    12SET        Ajusta opciones para los ilines
	    12SUSPEND    Suspende una iline Temporalmente
	    12UNSUSPEND  Reactiva una iline
	    12KILLCLONES Killea a todos los usuarios de una ip
	
	Los 4Administradores de la RED pueden ejecutar los comandos
	con cualquier cyber.


CYBER_SERVADMIN_HELP_INFO
	Sintaxis: 12INFO [host]
	
	Muestra la informacion sobre el host dado.
	
	Limitado a Operadores de la RED.

CYBER_SERVADMIN_HELP_VERIFY
	Sintaxis: C12VERIFY <nick>
	
	Verifica si el dicho nick, es un admin de cyber o no, en el caso
	de que sea admin, mostrará su host actual.
	
	Limitado a Operadores de la RED.

CYBER_SERVADMIN_HELP_LIST
	Sintaxis: 12LIST <patron> [SUSPEND] [NOEXPIRE] [NOFIJA]
	
	Bla bla
	
	Limitado a Operadores de la RED.

CYBER_SERVADMIN_HELP_SET
	Las siguientes opciones está limitadas a Administradores de
	la RED:
	
	HOST      Ajusta el host principal de la iline
	HOST2     Ajusta el host secundario
	ADMIN     Ajusta el Admin de la iline
	DNI       Ajusta el DNI del responsable
	EMAIL     Ajusta el Email del responsable
	TELEFONO  Ajusta el telefono del responsable
	NOMBRE    Ajusta el nombre del responsable
	CENTRO    Ajusta el nombre del Centro
	VHOST     Ajusta el vhost de todas las conexiones
	          de la iline (NO DISPONIBLE TODAVIA)
	EXPIRE    Ajusta la expiracion de la iline
	IPNOFIJA  Ajusta si la ip de la iline es fija o no

	Bla bla...

CYBER_SERVADMIN_HELP_SET_HOST
	Sintaxis: SET <host> HOST <nuevo host>
	
	Bla bla
	
	Limitado a Administradores de la RED.

CYBER_SERVADMIN_HELP_SET_HOST2
	Sintaxis: SET <host> HOST [host secundario]
	
	bla bla
	
	Limitado a Administradores de la RED.

CYBER_SERVADMIN_HELP_SET_ADMIN
	Sintaxis: SET <host> ADMIN <nick>
	
	Bla bla
	
	Limitado a Administradores de la RED.

CYBER_SERVADMIN_HELP_SET_DNI
	Sintaxis: SET <host> DNI <numero DNI>
	
	bla bla
	
	Limitado a Administradores de la RED.

CYBER_SERVADMIN_HELP_SET_EMAIL
	Sintaxis: SET <host> EMAIL <direccion email>
	
	Bla bla
	
	Limitado a Administradores de la RED.

CYBER_SERVADMIN_HELP_SET_TELEFONO
	Sintaxis: SET <host> TELEFONO <numero telefono>
	
	Bla bla
	
	Limitado a Administradores de la RED.

CYBER_SERVADMIN_HELP_SET_NOMBRE
	Sintaxis: SET <host> NOMBRE <nombre admin>
	
	Bla bla
	
	Limitado a Administradores de la RED.

CYBER_SERVADMIN_HELP_SET_CENTRO
	Sintaxis: SET <host> CENTRO <nombre del centro>
	
	Bla bla
	
	Limitado a Administradores de la RED.

CYBER_SERVADMIN_HELP_SET_VHOST
	Sintaxis: SET <host> VHOST [direccion vhost]
	
	bla bla
	
	Limitado a Administradores de la RED.

CYBER_SERVADMIN_HELP_SET_EXPIRE
	Sintaxis: SET <host> EXPIRE <tiempo>
	
	Bla bla
	
	Limitado a Administradores de la RED.

CYBER_SERVADMIN_HELP_SET_IPNOFIJA
	Sintaxis: SET <host> IPNOFIJA {ON | OFF}
	
	Bla bla
	
	Limitado a Administradores de la RED.

CYBER_SERVADMIN_HELP_SUSPEND
	Sintaxis: 12SUSPEND <host> <motivo>
	
	Suspende la Iline temporalmente, cuando una iline esta en
	suspenso, solo podran conectar los clones genericos.
	
	Limitado a Administradores de la RED.

CYBER_SERVADMIN_HELP_UNSUSPEND
	Sintaxis: 12UNSUSPEND <host> <motivo>
	
	Reactiva una iline suspendida, para que vuelva a usar el
	permiso de clones.
	
	Limitado a Administradores de la RED.

CYBER_SERVADMIN_HELP_ILINE
	Sintaxis: 12ILINE ADD <host> <nick> [+expiracion] <limite> <motivo>
	          12ILINE DEL <host>

	Gestiona las ilines.
	
	ILINE ADD añade una iline
	
	ILINE DEL botta una iline

CYBER_SERVADMIN_HELP_CLONES
	Sintaxis: 12CLONES LIST <número>
	          12CLONES VIEW <host>
	
	Permite a los C4Operadores de la REDC listar los clones en
	uso de la red.
	
	12CLONES LIST lista los hosts con hasta C12numeroC de clones.
	El numero debe ser un numero mayor que 2. Esto es para prevenir
	listados accidentales de hosts con 1 o 2 clones.
	
	12CLONES VIEW muestra informacion detallada sobre un 12host
	especifico, incluyendo el numero de clones actual y el limite
	máximo de clones que tiene concedidos.
	El valor del 12host no debe tener signos (! o @).
	
	Ver la ayuda de 12ILINE para más informacion sobre el limite de
	clones y como poner limites de clones especificos para ciertos hosts
	y grupos.
	
	Limitado a 4Operadores de la RED.

CYBER_SERVADMIN_HELP_KILLCLONES
	Sintaxis: 12KILLCLONES <nick>
	
	Killea a todos los users con el mismo host (clones) que
	el usuario llamado 12nick. Un Gline temporal, en la
	forma 12*@host, es añadido para prevenir que los clientes
	reconectaran inmediatamente. Un mensaje en el canal de control
	se enviara cuando sea usado el comando, con el host afectado y
	cuantos usuarios han sido killeados.
	Esto se usa para borrar muchos clones en una red.
		
	Limitado a 4Administradores de la RED.


########################################################################
#
# CReG SERVER
#
########################################################################


###########################################################################
#
# OperServ help messages (mensajes de ayuda de OperServ)
#
###########################################################################

OPER_HELP
	Comandos de 4%S:
	
	    12STATS       Muestra el estado de los servicios y de la red
	    12SERVERS     Muestra los servidores de la red
	    12OPER LIST   Lista todos los Operadores de los Servicios
	    12ADMIN LIST  Lista todos los Administradores de Servicios
	
	Comandos disponibles solo para Operadores de Servicios y
	administradores:
	
	    12OP DEOP     Da op o deop por el servidor
	    12GETKEY      Da la key (modo +k) de un canal
	    12MODE        Cambia los modos de un canal
	    12CLEARMODES  Quita todos los modos de un canal
	    12KICK        Patea a un usuario de un canal
	    12KILL        Expulsa a un tipejo
	    12BLOCK       Expulsa 5 minutos a un tipejo
	    12UNGLINE     Elimina un BLOCK/GLINE
	    12APODERA     MassDeop de los usuarios de un canal
	    12LIMPIA      MassKick de los usuarios de un canal
	
	Comandos disponibles solo para los Administradores de
	Servicios:
	
	    12OPER        Modifica la lista de Operadores de Servicios
	    12LOGONNEWS   Añade un LOGONNEWS
	    12OPERNEWS   Añade un OPERNEWS
	    12GLOBAL      Envía un mensaje a TODOS los usuarios por privmsg
	    12GLOBALN     Envía un mensaje a TODOS los usuarios por notice
	    12GLINE       Manipula la lista de GLINEs
	    12JUPE        "Jupiter" un servidor
	    12SETTIME     Sincroniza la RED a tiempo real
	    12RAW         Envía un código RAW al servidor IRC
	    12SET         Establece varias opciones globales de los
	                servicios
	    12UPDATE      Fuerza a la base de datos de los Servicios a
	                ser actualizada inmediatamente en el disco
	    12QUIT        Da por finalizada la ejecución del programa
	                de Servicios
	    12SHUTDOWN    Graba la base de datos y da por finalizada la
	                ejecucion del programa servicios 
	    12RESTART     Graba la base de datos y reinicializa los
	                Servicios
	
	Comandos disponibles únicamente para los súper-usuarios de los
	servicios:
	
	    12ADMIN       Modifica la lista de Administradores de Servicios
	    12ROTATELOG   Rota los logs
#	    12ROTATEDB    Rota las db y hace una copia de seguridad
	
	4Aviso: TODOS los comandos enviados a 12%S son
	registrados! (log)

OPER_HELP_GLOBAL
	Sintaxis: 12GLOBAL <mensaje>
	
	Habilita a los IRCops a enviar un 12mensaje a todos los
	usuarios en la red. El mensaje puede ser enviado para 12%s.


OPER_HELP_GLOBALN
	Sintaxis: 12GLOBALN <mensaje>
	
	Habilita a los IRCops a enviar un 12notice a todos los
	usuarios en la red. El mensaje puede ser enviado para 12%s.

OPER_HELP_STATS
	Sintaxis: 12STATS [GLINE | ALL]
	
	Sin opciones, muestra la cantidad de usuarios e IRCops en
	línea, el mas alto numero de usuarios en línea desde que los
	servicios se pusieron en funcionamiento, y desde cuando
	están funcionando los servicios.
	
	Con el parámetro 12GLINE muestra la longitud de la lista de
	AKILL y la fecha actual de expiración.
	
	El parámetro 12ALL solo está disponible para los
	4Administradores de Servicios y muestra el uso de memoria de
	los Servicios. Utilizando esta opción puede congelar los
	Servicios por un breve período de tiempo en grandes redes,
	por lo tanto no abuse de ella.
	
	12UPTIME puede ser utilizado como sinónimo de 12STATS.

OPER_HELP_OPER
	Sintaxis: 12OPER ADD <nick>
	          12OPER DEL <nick>
	          12OPER LIST
	
	Habilita a los 4Administradores de Servicios para agregar
	(ADD), borrar (DEL) o listar (LIST) usuarios de la lista de
	operadores. Un usuario que se encuentre en la lista de
	operadores y que se identifique ante 12%s podrá acceder
	a los comandos de Operador de Servicios.
	
	Cualquiera de los operadores de IRC (IRCops) puede utilizar
	el comando 12OPER LIST. Todos los otros comandos solo pueden
	ser utilizados por los 4Administradores de Servicios.

OPER_HELP_ADMIN
	Sintaxis: 12ADMIN ADD <nick>
	          12ADMIN DEL <nick>
	          12ADMIN LIST
	
	Habilita a los 4súper-usuarios de los Servicios a agregar
	(ADD), eliminar (DEL) o listar (LIST) usuarios de la lista
	de administradores. Un usuario que se encuentre en la lista
	de operadores y que se identifique ante 12%s podrá
	acceder a los comandos de Administrador de Servicios.
	
	Cualquiera de los operadores de IRC (IRCops) puede utilizar
	el comando 12ADMIN LIST. Todos los otros comandos solo pueden
	ser utilizados por el 4súper-usuarios de los Servicios.
	
OPER_HELP_MODE
	Sintaxis: 12MODE <canal> <modos>
	
	Habilita a los operadores de Servicios a establecer los
	modos para cualquier canal. Los parámetros son los mismos
	que se utilizan en la forma estándar de /MODE.
	
	Solo disponible para los 4Operadores de Servicios.

OPER_HELP_CLEARMODES
	Sintaxis: 12CLEARMODES <canal> [ALL]
	
	Elimina los BAN y los modos de un canal (i,k,l,m,n,p,s,t).
	Si el parámetro 12ALL es dado, también quita los modos
	Operador y voz que haya en el canal (modos +o y +v).
	
	Solo disponible para los 4Operadores de Servicios.

OPER_HELP_KICK
	Sintaxis: 12KICK <canal> <usuario> <razón>
		
	Habilita a un IRCop a sacar a un usuario de cualquier canal.
	Los parámetros son los mismos que para un /KICK común. El
	mensaje de kick mostrará al usuario el nombre del IRCop que
	está enviando el comando. Por ejemplo:
		
	3*** Lammer ha sido kickeado del canal #mi_canal por %S (ZoLtan (Insultos))
	
	Solo disponible para los 4Operadores de Servicios.

OPER_HELP_KILL
	Sintaxis: KILL <usuario> <razon>
	
	Habilita a un IRCop a sacar un usuario de la Red.
	Los parámetros son los mismos que para un /KILL común. El
	mensaje de kill mostrará al usuario el nombre del IRCop que
	está enviando el comando. Por ejemplo:
	
	*** Marcha: Lammer (Killed (Zoltan (Insultos reiterados)))
	
	Solo disponible para los Operadores de Servicios.

OPER_HELP_BLOCK
	Sintaxis: BLOCK <usuario> <razon>
	
	Mete un GLINE de 5 minutos al usuario dicho. Si el usuario
	 está en un cyber (tiene iline en Cyber) solo podrán glinear
	los Admnistradores de Servicios.
	
	Solo disponible para los Operadores de Servicios.

OPER_HELP_UNBLOCK
	Sintaxis: UNBLOCK { user@host | host }
	
	Quita un GLINE al user@host o al host (*@host) especificado.
	
	Solo disponible para los Operadores de Servicios.

OPER_HELP_LIMPIA
	Sintaxis: LIMPIA <canal> [motivo]
	
	Limpia un canal. Pone el canal en modo +ismnt, y kickea a todos
	los usuarios presentes en el canal, excepto los operadores y 
	administradores.
	
	Solo disponible para los Operadores de Servicios.

OPER_HELP_APODERA
	Sintaxis: APODERA <canal>
	
	Apodera un canal. Pone el canal en +ismnt, quita op y voices
	a todos los usuarios excepto los operadores y administradores
	y los silencia.
	
	Solo disponible para los Operadores de Servicios.

OPER_HELP_AKILL
	Sintaxis: 12GLINE ADD [+expiracion] <mascara> <razón>
	          12GLINE DEL <mascara>
	          12GLINE LIST [mascara]
	          12GLINE VIEW [mascara]
	
	Habilita a los IRCops a manipular la lista de 12GLINE. Si un
	usuario que figura en dicha lista, intenta conectarse, los
	Servicios bloquearán su conexión y darán instrucciones a
	todos los servidores que lo soporten, que agreguen un ban
	(k-line) para la máscara que coincida con la del usuario.
	
	12GLINE ADD agrega el usuario dado (con la mascara
	usuario@host) a la lista de akill por la razón dada (que
	debe ser dada).
	
	12GLINE DEL quita el usuario dado de la lista de 12GLINE si el
	mismo está presente.
	
	12GLINE LIST muestra todos los usuarios que están actualmente
	en la lista. Si una máscara es dada, el listado estará
	limitado a las ocurrencias.
	
	12GLINE VIEW es mas explícito que 12GLINE LIST, dado que muestra
	quien agregó el 12GLINE, la fecha en que fue hecho, cuando
	expira, la máscara utilizada y la razón.
	
	Opcionalmente, un tiempo de expiración puede ser
	suministrado con el comando 12GLINE ADD. El tiempo de
	expiración PRECEDE a la máscara usuario@host y es
	especificado como un entero (esto es, sin decimales) seguido
	de: d para especificar días, h (horas), o m (minutos).
	Combinaciones (como 1h30m) no están permitidas.  Si un
	especificador de unidades no es incluido, por defecto se
	asumen DIAS (entonces, poner +30 sin nada, significa 30
	días). Para agregar un 12GLINE que NO expira, utilice +0.  Si
	la máscara de usuario comienza con +, un período de
	expiración deberá ser indicado, aún si es el mismo período
	que el asignado por defecto. El tiempo de expiración por
	defecto, se puede ver utilizando el comando STATS GLINE.
	
	La 12razón está indicada para uso de los IRCops, y NO será
	mostrada al usuario cuando se efectúe el KILL.
	
	Solo disponible para los 4Operadores de Servicios.

OPER_HELP_JUPE
	Sintaxis: 12JUPE <server>
	
	Instruye a los Servicios a crear un servidor satélite. Esto
	es, para simular un "servidor" que esté conectado a los
	Servicios los cuales previenen la conexión del servidor real
	con ese nombre. Esta simulación puede ser removida,
	utilizando un 12SQUIT estándar.

	Solo disponible para los 4Administradores de Servicios.

OPER_HELP_RAW
	Sintaxis: 12RAW <texto>
	
	Envía una cadena de caracteres directamente al servidor al
	cual los Servicios están conectados.
	Esta orden tiene un muy limitado rango de usos, y puede
	causar estragos en una red si se utiliza inadecuadamente.
	4NO USE ESTE COMANDO a menos que usted esté completamente
	seguro de lo que está haciendo!

	Solo disponible para los 4Administradores de Servicios.

OPER_HELP_SET
	Sintaxis: 12SET <opción> <modo>
	
	Establece varias de las opciones globales de los Servicios.
	Los nombres de las opciones actualmente definidas son:
	    12READONLY   Establece el modo de "solo-lectura" o
	                   "lectura-escritura"
	    12DEBUG      Activa o desactiva el modo depuración
	
	Solo disponible para los 4Administradores de Servicios.

OPER_HELP_SET_READONLY
	Sintaxis: 12SET READONLY {ON | OFF}
	
	Activa o desactiva el modo "solo-lectura". Si el modo
	"solo-lectura" está activado, los usuarios que tienen acceso
	no estarán habilitados a modificar los datos de los
	Servicios, incluyendo listas de canales, nicks, etc. IRCops
	con suficientes privilegios sobre los servicios, podrán
	modificar la lista de 12AKILL, así como eliminar (DROP) un
	canal o un nick, pero ninguno de los cambios serán grabados
	a menos que el modo "solo-lectura" se desactive después que
	finalicen los servicios, o sean restaurados.
	
	Esta opción es equivalente a la opción 12-readonly de la
	línea de comando.

OPER_HELP_SET_DEBUG
	Sintaxis: 12SET DEBUG {ON | OFF | numero}
	
	Activa o desactiva el modo depuración.  En modo depuración,
	todos los datos enviados y recibidos así como los mensajes
	de depuración, son grabados en un archivo de registro (log).
	Si numero es dado, el modo de depuración es activado, con
	nivel de depuración establecido a 12numero.
	
	Esta opción es equivalente a la opción 12-debug de la
	línea de comando.

OPER_HELP_UPDATE
	Sintaxis: 12UPDATE
	
	Causa que los Servicios actualicen las bases de datos tan
	pronto como usted envía el comando.
	
	Limitado a 4Administradores de Servicios.

OPER_HELP_QUIT
	Sintaxis: 12QUIT
	
	Causa la desactivación de los Servicios; las bases de datos
	4NO se graban. Este comando no debe utilizarse a menos que
	se sospeche de un daño en las bases de datos en-memoria y no
	deseen grabarse. Para desactivación normal de los
	Servicios, utilice el comando 12SHUTDOWN.
	
	Limitado a 4Administradores de Servicios.

OPER_HELP_SHUTDOWN
	Sintaxis: 12SHUTDOWN
	
	Causa que los servicios graben todas las bases de datos y
	luego se desactiven.
	
	Limitado a 4Administradores de Servicios.

OPER_HELP_RESTART
	Sintaxis: 12RESTART
	
	Causa que Services grabe todas las bases de datos y
	reinicialize (ejemplo: terminar y ejecutar inmediatamente el
	programa).
	
	Limitado a 4Administradores de Servicios.

OPER_HELP_ROTATELOG
	Syntax: 12ROTATELOG
	
	Renames service's log file. The current date, in the form
	YYYYMMDD, is used to generate the new filename.
	
	Limitado a 4súper-usuarios de Servicios


###########################################################################
#
# Mensajes de ayuda de CyberServ
#
###########################################################################

#CYBER_HELP
#	4%S es un servicio que la RED pone a disposicion de los
#	CyberCafes, con el fin de proporcionar una mayor facilidad a
#	dichos locales y sus multiples conexiones simultaneas que
#	que tiene (Clones).
#	Para utilizar los comandos teclee 12/msg %S comando.
#	
#	#Para mayor informacion sobre un comando especifico teclee
#	12/msg %S HELP comando.
#	
#	    12KILL       Killea a un Usuario de tu Cyber
#	    12GLINE      Glinea a un Usuario de su Cyber
#	    12UNBAN      Desbanea la IP de su Cyber de un canal.
#	    12CLONES     Mira los clones que estan conectados de tu Cyber.
#	
#	4NOTA: Este servicio esta diseñado para dotar a los CyberCafes
#	de una "Pseudo-protección" de estos en la RED. Su intencion
#	no es la de fomentar su mal uso.
#	El mal uso de 4%S llevará a la denegacion de dicho servicio
#	por parte de la RED a dicho CyberCafé.
#
#CYBER_HELP_KILL
#	Sintaxis: 12KILL <nick> [motivo]
#	
#	Killea al usuario on-line de tu cyber.
#	
#	Limitado a 4Admininistradores de Cybers.
#
#CYBER_HELP_GLINE
#	Sintaxis: 12GLINE <nick> [motivo]
#	
#	Glinea durante 5 minutos al usuario on-line de tu cyber.
#	
#	Limitado a 4Administradores de Cybers.
#
#CYBER_HELP_UNBAN
#	Sintaxis: 12UNBAN <canal>
#	
#	Le dice a 12%S que elimine todos los accesos prohibidos
#	previniendo el ingreso de tu Cyber a dicho canal.
#	
#	Limitado a 4Administradores de Cybers.
#
#CYBER_HELP_CLONES
#	Sintaxis: 12CLONES
#	
#	Te dice cuantos clones, bla bla. xDDDD
#
#CYBER_SERVADMIN_HELP
#	
#	Los siguientes comandos están disponibles para los
#	4Administradores de Services:
#	
#	    12ILINE      Añade clones a un determinado nick/host
#	    12CLONES	   Información sobre clones
#	    12KILLCLONES Killea a todos los usuarios de una ip
#	
#	Los 4Administradores de Services bla bla.
#
OPER_HELP_EXCEPTION
	Sintaxis: 12ILINE ADD [+expiracion]
	          12ILINE DEL {mascara | list}
	          12ILINE MOVE <numero> <posicion>
	          12ILINE LIST [mascara | list]
	          12ILINE VIEW [mascara | list]
	
	Allows Services admins to manipulate the list of hosts that
	have specific session limits - allowing certain machines,
	such as shell servers, to carry more than the default number
	of clients at a time. Once a host reaches it's session limit,
	all clients attempting to connect from that host will be
	killed. Before the user is killed, they are notified, via a
	/NOTICE from OperServ, of a source of help regarding session
	limiting. The content of this notice is a config setting.
	
	12ILINE ADD adds the given host mask to the exception list.
	Note that 12nick!user@host and 12user@host masks are invalid!
	Only real host masks, such as 12box.host.dom and 12*.host.dom,
	are allowed because sessions limiting does not take nick or
	user names into account. 12limite must be a number greater than
	or equal to zero. This determines how many sessions this host
	may carry at a time. A value of zero means the host has an
	unlimited session limit. See the 12AKILL help for details about
	the format of the optional 12expiracion parameter.
	
	12ILINE DEL borra el host de la lista de Ilines..
	
	12ILINE MOVE mueve el Iline 12numero a la 12posicion. The
	exceptions inbetween will be shifted up or down to fill the gap.
	
	12ILINE LIST y 12ILINE VIEW muestra todos los Ilines actuales
	exceptions; if the optional mask is given, the list is limited
	to those exceptions matching the mask. The difference is that
	12ILINE VIEW is more verbose, displaying the name of the
	person who added the exception, it's session limit, reason,
	host mask and the expiry date and time.
	
	Note that a connecting client will "use" the first exception
	their host matches. Large exception lists and widely matching
	exception masks are likely to degrade services' performance
	
	Limitado a 4Administradores de Servicios.

OPER_HELP_SESSION
	Sintaxis: 12CLONES LIST <número>
	          12CLONES VIEW <host>
	
	Permite a los 4Administradores de Services listar los clones en
	uso de la red.
	
	12CLONES LIST lista los hosts con hasta 12numero de clones.
	El numero debe ser un numero mayor que 1. Esto es para prevenir
	listados accidentales de hosts con un 1 solo clon.
	
	12CLONES VIEW muestra informacion detallada sobre un 12host
	especifico, incluyendo el numero de clones actual y el limite 
	máximo de clones que tiene concedidos.
	El valor del 12host no debe tener signos (! o @).
	
	Ver la ayuda de 12ILINE para más informacion sobre el limite de
	clones y como poner limites de clones especificos para ciertos hosts
	y grupos.
	
	Limitado a 4Administradores de Servicios.

OPER_HELP_KILLCLONES
	Sintaxis: 12KILLCLONES <nick>
	
	Killea a todos los users con el mismo host (clones) que
	el usuario llamado 12nick. Un Gline temporal, en la
	forma 12*@host, es añadido para prevenir que los clientes
	reconectaran inmediatamente. Un mensaje en el canal de control
	se enviara cuando sea usado el comando, con el host afectado y
	cuantos usuarios han sido killeados.
	Esto se usa para borrar muchos clones en una red.
	
	Limitado a 4Administradores de Servicies.

#######################################################################
#
# CReG SERVER
#
########################################################################

#CREG_HELP
#	4%S le permite realizar una petición de registro de un canal
#	e introducir a éste en la fase de registro. Para poder registrar
#	un canal, necesita el apoyo de12 3 personas. Los siguientes comandos
#	le permiten manejar el pre-registro de un canal; para utilizarlos,
#	escriba 12/msg %S comando. Para más información sobre un comando
#	específico, escriba 12/msg %S HELP comando.
#	
#	   12REGISTRA   Realiza una petición de registro de un canal.
#	   12APOYA      Muestra su apoyo al registro de un canal.
#	   12CANCELA    Cancela una petición de registro de un canal.
#	   12ESTADO     Permite consultar el estado de un canal.
#	   12APOYOS     Lista los apoyos recibidos por un canal o
#	              los registros/apoyos emitidos por un usuario.
#	 
#	4AVISO: 12%S realiza únicamente funciones de pre-registro de
#	un canal, siendo cada petición revisada por la administración
#	de la red. La red se reserva el derecho a denegar el registro a
#	cualquier canal si sus usuarios se comportan indebidamente o si
#	el canal no se ajusta a las normas de registro para los canales
#	disponibles en http://www.upworld.org/canales/normas.html
#
#
#CREG_HELP_REGISTRA
#	Sintaxis: REGISTRA <canal> <contraseña> <descripción>
#	
#	Realiza una petición de registro de un nuevo canal.
#	
#	El canal que intenta registrar no puede estar ya previamente
#	registrado con el bot 4%s. Consulte el comando 12ESTADO para
#	obtener información sobre como conocer el estado actual de un
#	canal. La contraseña que proporcione servirá para que pueda
#	identificarse como fundador del canal sin estar con su nick
#	habitual. El último parámetro debe ser una descripción delión
#	 propósito del canal.
#	
#	Para realizar una petición de registro, el nick desde el que la
#	ha hecho debe estar registrado, y si el registro es aceptado, ese
#	nick pasará a ser el fundador del canal.
#	
#	Para que una petición de registro sea válida, necesita el apoyo de
#	al menos 12%s personas en un plazo de siete días, no contando
#	como apoyos válidos distintos nicks registrados con el mismo email.
#	Si en ese plazo no recibe los apoyos necesarios, el canal expirará.
#	y será necesaria la intervenci¢n de un administrador de la red para
#	que se pueda proceder a una petición de registro de nuevo. Consulte
#	el comando APOYA (12/msg %S HELP APOYA) para obtener
#	información sobre como se puede apoyar el registro de un canal.
#	
#	4NOTA: Sólo puede realizar UNA operación sobre canales al día. Esto
#	es, únicamente puede utilizar el comando 12REGISTRA una vez cada
#	veinticuatro horas. Antes de utilizarlo, piense sabiamente y
#	no lo u en vano, ya que no existen excepciones posibles a esta
#	limitación.
#
#
#CREG_HELP_APOYA
#	Sintaxis: 12APOYA <canal> [contraseña]
#	
#	Muestra su apoyo a la petición de registro de un canal.
#	
#	El canal que introduzca no puede estar ya registrado, sino que debe
#	estar en un estado de registro pendiente en el bot 4%S. (Debe haber
#	utilizado el comando REGISTRA para iniciar este proceso) Consulte el
#	comando ESTADO (/msg CReG AYUDA estado) para obtener información
#	sobre como conocer el estado de un canal.
#	
#	La contraseña que introduzca no debe ser la contraseña del canal,
#	sino la contraseña que 4%S le proporcionará cuando ejecute
#	12/msg %S APOYA #canal, con el propósito de verificar su aprobación
#	al registro del canal.
#	
#	Para que un apoyo sea válido, su nick debe estar registrado y no
#	puede haber apoyado ese canal previamente desde ese nico desde
#	cualquier otro nick que posea. Además, no se permiten apyos que
#	provengan de nicks registrados con emails anónimos.
#	Tenga en cuenta que para evitar abusos por parte de los usuarios,
#	el máximo número de apoyos que un canal puede recibir es uno por
#	minuto. De esta manera, 4%S le informará de si su apoyo ha sido
#	procesado o de si por lo contrario, ha de esperar a que haya
#	transcurrido cierto periodo de tiempo.
#	
#	4NOTA: Sólo puede realizar UNA operación sobre canales al día. Esto
#	es, únicamente puede utilizar el comando 12APOYA una vez cada
#	veinticuatro horas. Antes de utilizarlo, piense sabiamente y
#	no lo use en vano, ya que no existen excepciones posibles a esta
#	limitación.
#
#
#CREG_HELP_CANCELA
#	Sintaxis: 12CANCELA <canal>
#	
#	Cancela la peticion de un registro de canal. Solo el founder (el que
#	ha hecho la peticion de registro) puede ejecutar este comando.
#
#
#
#CREG_HELP_ESTADO
#	Sintaxis: 12ESTADO <canal>
#	
#	Muestra el estado actual del canal que especifique.
#	
#	Los posibles estados de un canal son los siguientes:
#	
#	    12PENDIENTE    El canal no ha obtenido todavía el numero
#	                 necesario de apoyos para que pueda ser procesada
#	                 la petición.
#	    12ENREGISTRO   La petición de registro del canal está siendo
#	                 revisada por la administración de canales de la
#	                 red.
#	    12ACEPTADO     La petición de registro ha sido aprobada.
#	    12DENEGADO     La petición de registro ha sido denegada.
#	    12REGISTRADO   El canal ya está actualmente registrado.
#	    12SUSPENDIDO   El registro del canal ha sido suspendido.
#	    12COMERCIAL    Es un canal comercial.
#	    12DROPADO      El registro del canal ha sido elminado por la
#	                 administración de la red.
#
#
#CREG_HELP_APOYOS
#	Sintaxis: 12APOYOS {canal|nick|email}
#	
#	Lista los nicks de las personas que apoyan la petición de
#	registro de un canal si especificamos el nombre de un canal, o
#	los registros y/o apoyos que ha emitido un/os usuario si
#	especificamos un nick/email.
#	
#	4NOTA: Sólo es posible listar los nicks de las personas que apoyan
#	el canal si se está utilizando el nick que env¡o la petición de
#	registro (el futuro fundador del canal), y solo es posible
#	listar los apoyos/registros del nick que estamos utilizando.
#
#
#CREG_SERVADMIN_HELP
#	Los siguientes comandos están disponibles para los Operadores
#	de services:
#	
#	Información sobre Canales:
#	    INFO      Devuelve información ampliada sobre un canal.
#	    LISTA     Lista los canales pendientes, denegados, prohibidos,
#	              expirados, enregistro, aceptados, suspendidos,
#	              comerciales o dropados.
#	Administración de Peticiones de Registro:
#	    ACEPTA    Acepta la petici¢n de registro de un canal
#	              y lo registra en el bot CHaN. (Admins)
#	    RESTAURA  Re-registra un canal eT CHaN. (Admins)
#	 REGCOMERCIAL Registra un canal comercial (Restringido)
#	    ANULA     Anula la petici¢n de registro de un canal.
#	    DENIEGA   Deniega la petición de registro de un canal. (Admins)
#	    PROHIBE   Prohibe el registro de un canal. (Admins)
#	    RECHAZA   Rechaza el registro de un canal. (Admins)
#	    PERMITE   Levanta la prohibición de registro de un canal.
#	
#	Administración de Canales:
#	    SUSPEND   Suspende cautelarmente un canal registrado.
#	    UNSUSPEND Levanta la suspensión de un canal registrado.
#	    DROP      Borra el registro de un canal registrado.
#	    LIMPIA    Glinea a todos los miembros de un canal. (Admins)
#	    APODERA   Se apodera de un canal y lo silencia.
#	    MARCA     Añade un comentario al histórico de un canal.
#	
#	Funciones de Control:
#	    ILIST     Administra la lista de nicks de los cuales se
#	              ignorarán las peticiones de registro.
#	    DNICK     Administra la lista de nicks dropados automáticamente
#	              por estar registrados com mail an¢nimo.
#	    ACTIVA    Activa el registro/apoyo de canales. (Admins)
#	    DESACTIVA Desactiva el registro/apoyo de canales. (Admins)
#	    REFRESCA  Actualiza la lista de nicks con acceso de
#	              operadores/administradores de services a CReG.
#	    REINICIA  Reinicia el bot CReG.
#	Comandos varios:
#	    ILINE     Consulta la DB de ilines.
#	    TESTMAIL  Consulta la DB de dominios an¢nimos.
#	
#	Operadores de services pueden también listar los apoyos que ha
#	recibido un canal sin ser el fundador del mismo y los apoyos y
#	registros de cualquier usuario.
#
SERVICES_CREDITS
	Services es copyright (c) 1996-2000 de Andrew Church
	<12achurch@achurch.org>.
	
	Estos bots han sido reprogramados, usando la base de
	iRCServices 4.3.3, por Toni García <12zoltan@upworld.org>.
	
	Estos bots han sido cedidos para su uso a 12Upworls.Org
	mientras Toni García siga llevando el servidor de irc,
	12irc.upworld.org y siga en el grupo de trabajo del mismo.
	
	Estos bots tienen soporte para los siguientes protocolos:
	        12Undernet 2.9.x (P9)
	        12Undernet 2.10.x (P10) (no tiene en los Services originales)
	        12DreamForge Dalnet
	        12Bahamut Dalnet (codigo sacado del ircservices-4.5.0)
	        12Irc Classic (con y sin TS8)
	
	Más informacion de los Services (Licencia GNU):
	Las ultimas versiones de los Services pueden ser obtenidas de:
	La web de los Services es: <12http://ender.shadowfire.org/ircservices/>
	El FTP de los services es: <12ftp://ender.shadowfire.org/pub/ircservices/>
	
	Estos bots son de licencia privada, no se pueden conseguir en ningun
	sitio por ahora. En un futuro próximo, tendrá liciencia GNU/GPL.
	Proximamente disponible en http://upworld.sourceforge.net

SERVICES_CREDITS_TERRA
	Services es copyright (c) 1996-2000 de Andy Church <achurch@achurch.org>
	y de Andrew Keempe <theshadow@shadowfire.org>.

	TerraServices es copyright (c) 2000-2001 de sus desarrolladores.
	Estos bots han sido reprogramados por el comite técnico de developers
	usando la base de los ircservices-4.3.3 original.

	Miembros del Comite tecnico de developers:
	   Marcos Rey          TeX         <tex@terra.es>
	   Daniel Fernandez    FreeMind    <animedes@terra.es>
	   Toni García         zoltan      <zoltan@terra.es>
	   Jordi Murgo         |savage|    <savage@apostols.org>
	y los betateasters:
	   Antonio Fernandes   KoGe        <koge@terra.es>
	   Ripe, NiKoLaS y  CarlesBCN
	Y agradecimientos a los ircops, opers, y usuarios de la red por
	las sugerencias, criticas... :)

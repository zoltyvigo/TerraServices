# Services is copyright (c) 1996-1999 Andy Church.
#     E-mail: <achurch@dragonfire.net>
# This program is free but copyrighted software; see the file COPYING for
# details.

LANG_NAME
	Turkce (Turkish)
#############################################
# Translated by mikado (mikado@holyfire.com)#
#############################################

###########################################################################
#
# General messages
#
###########################################################################

# strftime() format strings.  man 3 strftime for information on the
# meanings of the format specifiers.  Short version:
#	%a = weekday name (short)	%H = hour
#	%b = month name (short)		%M = minute
#	%d = day of month		%S = second
#	%Y = year			%Z = time zone

# This is used as the format string for strftime() for a date and time
# together.
STRFTIME_DATE_TIME_FORMAT
	%b %d %H:%M:%S %Y %Z
# This is used as the format string for strftime() for a date alone in long
# format (English: including weekday).
STRFTIME_LONG_DATE_FORMAT
	%a %b %d %Y
# This is used as the format string for strftime() for a date alone in
# short format (English: without weekday).
STRFTIME_SHORT_DATE_FORMAT
	%b %d %Y

# These tell our strftime() what the names of months and days are.  If you
# don't use %a, %A, %b, or %B in your strftime() strings above, you can
# leave these empty.  However, if you enter names, they MUST stay in order,
# one per line, and the list MUST be complete!

# %a
STRFTIME_DAYS_SHORT
	Paz
	Pzt
	Sal
	Car
	Per
	Cum
	Cmt
# %A
STRFTIME_DAYS_LONG
	Pazar
	Pazartesi
	Sali
	Carsamba
	Persembe
	Cuma
	Cumartesi
# %b
STRFTIME_MONTHS_SHORT
	Oca
	Sub
	Mar
	Nis
	May
	Haz
	Tem
	Agu
	Eyl
	Ekm
	Ksm
	Ara
# %B
STRFTIME_MONTHS_LONG
	Ocak
	Subat
	Mart
	Nisan
	Mayis
	Haziran
	Temmuz
	Agustos
	Eylul
	Ekim
	Kasim
	Aralik

# This is used in ChanServ/NickServ INFO displays.
COMMA_SPACE
	,

# Various error messages.
USER_RECORD_NOT_FOUND
	Dahili hata - Kullanici kaydi bulunamadi.	
UNKNOWN_COMMAND
	%s diye bir komut yok.
UNKNOWN_COMMAND_HELP
	%s diye bir komut yok. "/msg %s HELP" yaziniz.
SYNTAX_ERROR
	Kullanimi: %s
MORE_INFO
	Daha fazla bilgi icin /msg %s HELP %s yaziniz.
NO_HELP_AVAILABLE
	%s hakkinda yardim bulunamadi.
	
BAD_USERHOST_MASK
	"mask"  kullanici@IP seklinde tanimlanmali.

SERVICE_OFFLINE
	%s su anda devre disi.
READ_ONLY_MODE
	Notice: Services read-only calisiyor; degisiklikler kaydedilmeyecek !
PASSWORD_INCORRECT
	Gecersiz sifre.
ACCESS_DENIED
	Bu komuta erisiminiz yok.
PERMISSION_DENIED
	Bu komutu kullanma izniniz yok.

MORE_OBSCURE_PASSWORD
	Lutfen daha az basit bir sifre ile yeniden deneyiniz. Sifreler en az bes karakter ve tahmin edilmesi kolay olan (adiniz,dogum tarihiniz vb.) seyler olmamali ve bosluk icermemelidir.
PASSWORD_TRUNCATED
	Uyari:  Sifreniz %d karaktere kisaltilmistir.

NICK_NOT_REGISTERED
	Nick'iniz kayitli degil.
NICK_NOT_REGISTERED_HELP
	Nick'iniz kayitli degil./msg %s HELP yazarak nasil kaydedebileceginiz konusunda ayrintili bilgi alabilirsiniz.

NICK_X_NOT_REGISTERED
	%s kayitli bir nick degil.
NICK_X_NOT_IN_USE
	%s nick'i su anda kullanimda degil.
NICK_X_FORBIDDEN
	%s kaydedilemez ve/veya kullanilamaz.
CHAN_X_NOT_REGISTERED
	%s kanali kayitli degil.
CHAN_X_NOT_IN_USE
	%s kanali su an kullanimda degil.
CHAN_X_FORBIDDEN
	%s kanali kaydedilemez ve/veya kullanilamaz.
NICK_IDENTIFY_REQUIRED
	Bu komutu kullanabilmeniz icin sifrenizi girmelisiniz.
	/msg %s IDENTIFY sifreniz yazarak yeniden deneyiniz.
CHAN_IDENTIFY_REQUIRED
	Bu komutu kullanabilmeniz icin sifrenizi girmelisiniz.
	(/msg %s IDENTIFY %s sifreniz) yazarak yeniden deneyiniz.
	
###########################################################################
#
# NickServ messages
#
###########################################################################

# Automatic messages
NICK_IS_REGISTERED
	Bu kayitli bir nick'tir. Lutfen degistiriniz.
	(Eger sizinse,/msg %s IDENTIFY sifreniz yaziniz).
NICK_IS_SECURE
	Bu kayitli ve sifre korumali bir nick'tir.Eger sizinse
	/msg %s IDENTIFY sifreniz yaziniz. Aksi takdirde lutfen
	baska bir nick seciniz.
NICK_MAY_NOT_BE_USED
	Bu nick'in kullanimi yasaklanmistir.  Lutfen degistiriniz.
DISCONNECT_IN_1_MINUTE
	Eger 1 dakika icinde degistirmezseniz, baglantiniz kesilecektir.
DISCONNECT_IN_20_SECONDS
	Eger 20 saniye icinde degistirmezseniz, baglantiniz kesilecektir.
DISCONNECT_NOW
	Bu nick bir baskasinin adina kayitli oldugundan kullanamazsiniz.
	Lutfen baska bir nick alarak yeniden baglaniniz.

# REGISTER responses
NICK_REGISTRATION_DISABLED
	Nick kaydi gecici olarak devre disidir.
NICK_REGISTRATION_FAILED
	Nick kaydi basarisiz.
NICK_REG_PLEASE_WAIT
	Lutfen %d saniye bekleyerek yeniden deneyiniz.
NICK_CANNOT_BE_REGISTERED
	%s nick'i kaydedilemez.
NICK_ALREADY_REGISTERED
	%s daha onceden kaydedilmis.
NICK_REGISTERED
	%s nick'i basari ile kaydedilmistir.
NICK_PASSWORD_IS
	Nick sifreniz: %s 'dir. Lutfen sifrenizi unutmayiniz ve kimseye soylemeyiniz.

# IDENTIFY responses
NICK_IDENTIFY_FAILED
	Tanimlama basarisiz.
NICK_IDENTIFY_SUCCEEDED
	Sifre kabul edildi.

# DROP responses
NICK_DROP_DISABLED
	Nick kaydi silinmesi gecici olarak devre disidir,
NICK_DROPPED
	Nick'inizin kaydi silinmistir (dropped).
NICK_X_DROPPED
	%s nick'inin kaydi silinmistir (dropped).

# SET responses
NICK_SET_DISABLED
	NickServ'un SET komutu gecici olarak devre disidir.
NICK_SET_UNKNOWN_OPTION
	Varolmayan SET secenegi: %s.
NICK_SET_UNKNOWN_OPTION_OR_BAD_NICK
	Varolmayan SET secenegi: %s, veya nick kayitli degil.

# SET PASSWORD responses
NICK_SET_PASSWORD_FAILED
	Sifre degistirilemedi.
NICK_SET_PASSWORD_CHANGED
	Sifreniz degistirildi.
NICK_SET_PASSWORD_CHANGED_TO
	Nick sifresi %s olarak degistirildi.

# SET URL responses
NICK_SET_URL_CHANGED
	URL %s olarak degistirildi.
NICK_SET_URL_UNSET
	URL silindi.

# SET EMAIL responses
NICK_SET_EMAIL_CHANGED
	E-mail adresi %s olarak degistirildi.
NICK_SET_EMAIL_UNSET
	E-mail adresi silindi.

# SET LANGUAGE responses
NICK_SET_LANGUAGE_UNKNOWN
	Varolmayan dil numarasi: %d . /msg %s HELP SET LANGUAGE yazarak mevcut dillerin bir listesini alabilirsiniz.
NICK_SET_LANGUAGE_CHANGED
	Dil Turkce 'ye cevrilmistir.

# SET KILL responses
NICK_SET_KILL_ON
	Kill korumasi: AKTIF.
NICK_SET_KILL_QUICK
	Kill korumasi: zaman limitli olarak AKTIF,
NICK_SET_KILL_IMMED
	Aninda Kill korumasi: AKTIF
NICK_SET_KILL_IMMED_DISABLED
	IMMED secenegi bu network'te aktif degil.
NICK_SET_KILL_OFF
	Kill korumasi: IPTAL.

# SET SECURE responses
NICK_SET_SECURE_ON
	Secure secenegi: AKTIF.
NICK_SET_SECURE_OFF
	Secure secenegi: IPTAL.

# SET PRIVATE responses
NICK_SET_PRIVATE_ON
	Private secenegi: AKTIF.
NICK_SET_PRIVATE_OFF
	Private secenegi: IPTAL.

# SET HIDE responses
NICK_SET_HIDE_EMAIL_ON
	E-mail adresiniz %s INFO listelerinden gizlendi.
NICK_SET_HIDE_EMAIL_OFF
	E-mail adresiniz %s INFO listelerinde gorulebilecek.
NICK_SET_HIDE_MASK_ON
	"last seen" 'iniz %s INFO listelerinden gizlendi.
NICK_SET_HIDE_MASK_OFF
	"last seen" 'iniz %s INFO listelerinde gorulebilecek.
NICK_SET_HIDE_QUIT_ON
	Son "/quit" mesajiniz %s INFO listelerinden gizlendi.
NICK_SET_HIDE_QUIT_OFF
	Son "/quit" mesajiniz %s INFO listelerinde gorulebilecek.

# SET NOEXPIRE responses
NICK_SET_NOEXPIRE_ON
	%s nick'i zaman asimindan cikarildi
NICK_SET_NOEXPIRE_OFF
	%s nick'i zaman asimina eklendi .

# ACCESS responses
NICK_ACCESS_ALREADY_PRESENT
	%s erisim listenizde zaten var.
NICK_ACCESS_ADDED
	%s erisim listenize eklendi.
NICK_ACCESS_NOT_FOUND
	%s erisim listenizde bulunamadi.
NICK_ACCESS_DELETED
	%s erisim listenizden silindi.
NICK_ACCESS_LIST
	Erisim Listesi:
NICK_ACCESS_LIST_X
	%s nick'inin erisim listesi:

# LINK responses
NICK_LINK_FAILED
	Baglama (linking) basarisiz.
NICK_NO_LINK_SAME
	Bir nick kendine linklenemez!
NICK_LINK_CIRCULAR
	%s nick'i linklenemez: mevcut link.
NICK_LINKED
	Nick'iniz %s 'e linklendi.

# UNLINK responses
NICK_NOT_LINKED
	Nick'iniz bagli (linkli) degil.
NICK_UNLINKED
	Nick'inizin %s ile olan baglantisi (link) silindi.

# INFO responses
NICK_INFO_REALNAME
	      %s     isim: %s
NICK_INFO_ADDRESS
	Son gorulen adres: %s
NICK_INFO_TIME_REGGED
	     Kayit zamani: %s
NICK_INFO_LAST_SEEN
	Son gorulen zaman: %s
NICK_INFO_LAST_QUIT
	  Son quit mesaji: %s
NICK_INFO_URL
	              URL: %s
NICK_INFO_EMAIL
	    E-mail adresi: %s
NICK_INFO_OPTIONS
	            Ekler: %s
# These strings MUST NOT be empty
NICK_INFO_OPT_KILL
	Kill korumasi
NICK_INFO_OPT_SECURE
	Ek Guvenlik
NICK_INFO_OPT_PRIVATE
	Ozel
NICK_INFO_OPT_NONE
	YOK

# LIST responses
NICK_LIST_HEADER
	%s 'a uyan veriler:
NICK_LIST_RESULTS
	liste sonu - %d/%d .

# RECOVER responses
NICK_NO_RECOVER_SELF
	NickServ'e kendinizi killetemezsiniz!
NICK_RECOVERED
	Nick'inizi kullanan kisinin IRC baglantisi kesilmistir.
	/msg %s RELEASE %s yazarak bir dakikalik sureden once nick'inizi alabilirsiniz.

# RELEASE responses
NICK_RELEASE_NOT_HELD
	%s nick'i zaten serbest.
NICK_RELEASED
	Nickiniz serbest birakildi.

# GHOST responses
NICK_NO_GHOST_SELF
	NickServ'e kendinizi killetemezsiniz!
NICK_GHOST_KILLED
	Asili kalan nick'inizin baglantisi kesilmistir.

# GETPASS responses
NICK_GETPASS_UNAVAILABLE
	GETPASS komutunu sifreleme (encryption) devredeyken kullanamazsiniz.
NICK_GETPASS_PASSWORD_IS
	%s nick'inin sifresi : %s.

# FORBID responses
NICK_FORBID_SUCCEEDED
	%s nick'inin kullanimi yasaklandi.
NICK_FORBID_FAILED
	%s nick'inin kullanimi yasaklanamadi!

###########################################################################
#
# ChanServ messages
#
###########################################################################

# Access level descriptions
CHAN_LEVEL_AUTOOP
	Kanala giriste ChanServ tarafindan otomatik op.
CHAN_LEVEL_AUTOVOICE
	Kanala giriste ChanServ tarafindan otomatik voice (+v)
CHAN_LEVEL_AUTODEOP
	Kanal icinde op verilemez/alamaz.
CHAN_LEVEL_NOJOIN
	RESTRICTED ozelliginin acik olmasi durumunda kanala girilemez.
CHAN_LEVEL_INVITE
	INVITE komutunu kullanmaya yetkili.
CHAN_LEVEL_AKICK
	AKICK komutunu kullanmaya yetkili.
CHAN_LEVEL_SET
	SET komutunu kullanmaya yetkili (FOUNDER/PASSWORD haric).
CHAN_LEVEL_CLEAR
	CLEAR komutunu kullanmaya yetkili.
CHAN_LEVEL_UNBAN
	UNBAN komutunu kullanmaya yetkili.
CHAN_LEVEL_OPDEOP
	OP/DEOP komutlarini kullanmaya yetkili.
CHAN_LEVEL_ACCESS_LIST
	Kanalin erisim listesini (access list) gormeye yetkili.
CHAN_LEVEL_ACCESS_CHANGE
	Kanalin erisim listesini (access list)
	degistirmeye yetkili.
CHAN_LEVEL_MEMO
	Kanala gelen notlari okumaya yetkili.

# Automatic responses
CHAN_IS_REGISTERED
	Bu kanal %s ile kaydedilmistir.
CHAN_NOT_ALLOWED_OP
	%s kanalinda op olma yetkiniz yok.
CHAN_MAY_NOT_BE_USED
	Bu kanal kullanilamaz.
CHAN_NOT_ALLOWED_TO_JOIN
	Bu kanalda bulunmaya yetkili degilsiniz.

# REGISTER responses
CHAN_REGISTER_DISABLED
	Kanal kaydi (REGISTER) gecici olarak devre disidir.
CHAN_REGISTER_NOT_LOCAL
	Local kanallar kaydedilemezler.
CHAN_MUST_REGISTER_NICK
	Oncelikle nick'inizi kaydetmelisiniz. /msg %s HELP yazarak daha fazla bilgi alabilirsiniz.
CHAN_MUST_IDENTIFY_NICK
	Lutfen once /msg %s IDENTIFY sifre
	komutu ile kendinizi tanitiniz.
CHAN_MAY_NOT_BE_REGISTERED
	%s kanali kaydedilemez.
CHAN_ALREADY_REGISTERED
	%s kanali daha onceden kaydedilmis.
CHAN_MUST_BE_CHANOP
	Kanali kaydedebilmek icin op olmalisiniz.
CHAN_REACHED_CHANNEL_LIMIT
	%d kanallik limitinizi doldurdunuz.
CHAN_EXCEEDED_CHANNEL_LIMIT
	%d kanallik limitinizi astiniz.
CHAN_REGISTRATION_FAILED
	Kanal kaydi (registration) basarisiz.
CHAN_REGISTERED
	%s kanali %s nick'inize kaydedilmistir.
CHAN_PASSWORD_IS
	Kanal sifrenizi ( %s ) kimseye soylemeyiniz ve unutmayiniz.

# IDENTIFY responses
CHAN_IDENTIFY_FAILED
	Gecersiz sifre.
CHAN_IDENTIFY_SUCCEEDED
	Sifre kabul edildi : %s kanalina en yuksek duzeyde erisim kazandiniz.

# DROP responses
CHAN_DROP_DISABLED
	Kanal kaydinin silinmesi (DROP) gecici olarak devre disidir.
CHAN_DROPPED
	%s isimli kanalinizin kaydi silinmistir (dropped).

# SET responses
CHAN_SET_DISABLED
	Set komutu gecici olarak devre disidir.
CHAN_SET_UNKNOWN_OPTION
	Varolmayan SET ozelligi : %s.

# SET FOUNDER responses
CHAN_SET_FOUNDER_TOO_MANY_CHANS
	%s cok fazla kanala sahip.
CHAN_FOUNDER_CHANGED
	%s kanalinin sahibi (founder) %s olarak degisti.

# SET SUCCESSOR responses

# SET PASSWORD responses
CHAN_SET_PASSWORD_FAILED
	Sifre degisimi basarisiz.
CHAN_PASSWORD_CHANGED
	%s kanalinin sifresi degisti.
CHAN_PASSWORD_CHANGED_TO
	%s kanalinin sifresi %s olarak degisti.

# SET DESC responses
CHAN_DESC_CHANGED
	%s kanalinin aciklamasi (Description) %s olarak degisti.

# SET URL responses
CHAN_URL_CHANGED
	%s kanalinin web adresi (URL) %s olarak degisti.
CHAN_URL_UNSET
	%s kanalinin web adresi (URL) silindi.

# SET EMAIL responses
CHAN_EMAIL_CHANGED
	%s kanalinin E-Mail adresi %s olarak degisti.
CHAN_EMAIL_UNSET
	%s kanalinin E-mail adresi silindi.

# SET ENTRYMSG responses
CHAN_ENTRY_MSG_CHANGED
	%s kanali icin giris mesaji degisti.
CHAN_ENTRY_MSG_UNSET
	%s kanali icin giris mesaji silindi.

# SET TOPIC responses
CHAN_SET_TOPIC_FAILED
	Topic yazimi basarisiz.

# SET MLOCK responses
CHAN_SET_MLOCK_KEY_REQUIRED
	MLOCK +k komutu icin bir anahtar (key) belirtmelisiniz.
CHAN_SET_MLOCK_LIMIT_REQUIRED
	MLOCK +l komutu icin bir "limit" belirtmelisiniz.
CHAN_SET_MLOCK_LIMIT_POSITIVE
	MLOCK +l olarak pozitif bir sayi kullanmalisiniz.
CHAN_SET_MLOCK_UNKNOWN_CHAR
	Varolmayan mode %c dikkate alinmadi.
CHAN_MLOCK_CHANGED
	%s kanalindaki "mode lock" %s olarak degisti.
CHAN_MLOCK_REMOVED
	%s kanalindaki "mode lock" silindi.

# SET KEEPTOPIC responses
CHAN_SET_KEEPTOPIC_ON
	Topic hatirlama (retention) AKTIF.
CHAN_SET_KEEPTOPIC_OFF
	Topic hatirlama (retention) KAPALI.

# SET TOPICLOCK responses
CHAN_SET_TOPICLOCK_ON
	Topic kilidi (topiclock) AKTIF.
CHAN_SET_TOPICLOCK_OFF
	Topic kilidi (topiclock) KAPALI.

# SET PRIVATE responses
CHAN_SET_PRIVATE_ON
	Ozel (PRIVATE) AKTIF.
CHAN_SET_PRIVATE_OFF
	Ozel (PRIVATE) KAPALI.

# SET SECUREOPS responses
CHAN_SET_SECUREOPS_ON
	Kisitli Op (SECUREOPS) AKTIF.
CHAN_SET_SECUREOPS_OFF
	Kisitli Op (SECUREOPS) KAPALI.

# SET LEAVEOPS responses

# SET RESTRICTED responses
CHAN_SET_RESTRICTED_ON
	Kisitli erisim AKTIF.
CHAN_SET_RESTRICTED_OFF
	Kisitli Erisim KAPALI.

# SET SECURE responses
CHAN_SET_SECURE_ON
	Guvenlik AKTIF.
CHAN_SET_SECURE_OFF
	Guvenlik KAPALI.

# SET OPNOTICE responses

# SET NOEXPIRE responses
CHAN_SET_NOEXPIRE_ON
	%s kanali zaman asimindan cikarildi .
CHAN_SET_NOEXPIRE_OFF
	%s kanali zaman asimina eklendi.

# ACCESS messages
CHAN_ACCESS_DISABLED
	Kanal erisim listesinin degistirilmesi gecici olarak devre disidir.
CHAN_ACCESS_LEVEL_NONZERO
	Erisim seviyesi sifirdan farkli bir sayi olmalidir.
CHAN_ACCESS_LEVEL_RANGE
	Erisim seviyesi %d ve %d arasinda olmalidir.
CHAN_ACCESS_NICKS_ONLY
	Kanalin erisim listesi sadece kayitli (registered) nick'lerden olusabilir.
CHAN_ACCESS_LEVEL_UNCHANGED
	%s nick'inin %s kanalindaki erisim seviyesi zaten %d.
CHAN_ACCESS_LEVEL_CHANGED
	%s nick'inin %s kanalindaki erisim seviyesi %d olarak degisti.
CHAN_ACCESS_ADDED
	%s nick'i %s kanalinin erisim listesine %d seviyeden eklendi.
CHAN_ACCESS_NO_SUCH_ENTRY
	(#%d) seklinde bir kayit %s kanalinin erisim listesinde bulunamadi.
CHAN_ACCESS_NOT_FOUND
	%s  %s kanalinin erisim listesinde bulunamadi.
CHAN_ACCESS_DELETED
	%s  %s kanalinin erisim listesinden silindi.
CHAN_ACCESS_LIST_HEADER
	%s Kanali Erisim Listesi:
	  Sira   Seviye  Nick
CHAN_ACCESS_LIST_FORMAT
	  %3d  %4d  %s%s%s%s

# AKICK responses
CHAN_AKICK_DISABLED
	Kanal otomatik kick (akick) listesinin degistirilmesi gecici olarak devre disidir.
CHAN_AKICK_ALREADY_EXISTS
	%s nick'i %s kanalinin akick listesinde zaten var.
CHAN_AKICK_REACHED_LIMIT
	Bir kanalin akick listesinde en fazla %d kisi olabilir.
CHAN_AKICK_ADDED
	%s nick'i %s kanalinin akick listesine eklendi.
CHAN_AKICK_NO_SUCH_ENTRY
	(#%d) seklinde bir kayit %s kanalinin akick listesinde bulunamadi.
CHAN_AKICK_NOT_FOUND
	%s  %s kanalinin akick listesinde bulunamadi.
CHAN_AKICK_DELETED
	%s  %s kanalinin akick listesinden silindi.
CHAN_AKICK_LIST_HEADER
	%s kanalinin akick listesi:
CHAN_AKICK_LIST_FORMAT
	  %3d %s%s

# LEVELS responses
CHAN_LEVELS_RANGE
	Seviye %d ve %d arasinda olmalidir.
CHAN_LEVELS_CHANGED
	%s kanalinda %s icin gereken seviye %d olarak degisti.
CHAN_LEVELS_UNKNOWN
	Varolmayan secenek %s .  /msg %s HELP LEVELS DESC komutu ile gecerli listeyi aliniz.
CHAN_LEVELS_DISABLED
	%s %s kanalinda iptal edildi.
CHAN_LEVELS_LIST_HEADER
	%s kanalindaki erisim haklari:
CHAN_LEVELS_LIST_DISABLED
	    %-*s  (devre disi)
CHAN_LEVELS_LIST_FOUNDER
	    %-*s  (sadece founder)
CHAN_LEVELS_LIST_NORMAL
	    %-*s  %d
CHAN_LEVELS_RESET
	%s icin gereken erisim haklari sifirlanmistir.

# INFO responses
CHAN_INFO_HEADER
	  %s Kanali Bilgisi:
CHAN_INFO_FOUNDER
	  Kanal Sahibi : %s (%s)
CHAN_INFO_NO_FOUNDER
	  Kanal Sahibi : %s
CHAN_INFO_DESCRIPTION
	       Aciklama: %s
CHAN_INFO_TIME_REGGED
	   Kayit zamani: %s
CHAN_INFO_LAST_USED
	   Son Kullanim: %s
CHAN_INFO_LAST_TOPIC
	      Son Topic: %s
CHAN_INFO_TOPIC_SET_BY
	   Topici yazan: %s
CHAN_INFO_URL
	            URL: %s
CHAN_INFO_EMAIL
	  E-mail adresi: %s
CHAN_INFO_OPTIONS
	          Ekler: %s
CHAN_INFO_OPT_PRIVATE
	  Gizli (LIST komutunda cikmaz)
CHAN_INFO_OPT_KEEPTOPIC
	  Topic Hatirlama (retention)
CHAN_INFO_OPT_TOPICLOCK
	  Topic Kilidi (topiclock)
CHAN_INFO_OPT_SECUREOPS
	  Kisitli Op
CHAN_INFO_OPT_RESTRICTED
	  Kisitli Giris
CHAN_INFO_OPT_SECURE
	  Ek guvenlik
CHAN_INFO_OPT_NONE
	  YOK
CHAN_INFO_MODE_LOCK
	  Mode Kilidi: %s

# LIST responses
CHAN_LIST_HEADER
	%s 'a uyan verilerin listesi:
CHAN_LIST_FORMAT
	    %-20s  %s
CHAN_LIST_END
	Liste sonu - %d/%d veri listelendi.

# INVITE responses

# OP responses

# DEOP responses

# UNBAN responses
CHAN_UNBANNED
	%s kanalindaki ban'iniz kaldirildi.

# CLEAR responses
CHAN_CLEARED_BANS
	%s kanalindaki butun ban'lar (+b) kaldirildi.
CHAN_CLEARED_MODES
	%s kanalindaki butun mode'lar (+ovbntispklm) kaldirildi.
CHAN_CLEARED_OPS
	%s kanalindaki +o mode'u kaldirildi.(mass deop)
CHAN_CLEARED_VOICES
	%s kanalindaki +v mode'u kaldirildi.(mass devoice)
CHAN_CLEARED_USERS
	%s kanalindaki tum kullanicilar atildi.

# GETPASS responses
CHAN_GETPASS_UNAVAILABLE
	GETPASS komutunu sifreleme (encryption) devredeyken kullanamazsiniz.
CHAN_GETPASS_PASSWORD_IS
	%s kanalinin sifresi : %s.

# FORBID responses
CHAN_FORBID_SUCCEEDED
	%s kanalinin kullanimi yasaklandi.(forbidden)
CHAN_FORBID_FAILED
	%s kanalinin kullanimi yasaklanamadi!

###########################################################################
#
# MemoServ messages
#
###########################################################################

# Automatic messages
MEMO_HAVE_NEW_MEMO
	1 yeni notunuz var.
MEMO_HAVE_NEW_MEMOS
	%d yeni notunuz var.
MEMO_TYPE_READ_LAST
	/msg %s READ LAST yazarak okuyabilirsiniz.
MEMO_TYPE_READ_NUM
	/msg %s READ %d yazarak okuyabilirsiniz.
MEMO_TYPE_LIST_NEW
	/msg %s LIST NEW yazarak bir liste alabilirsiniz.
MEMO_AT_LIMIT
	UYARI: Maximum not sayiniza ulastiniz (%d).  Mevcutlardan bir kismini silmediginiz takdirde	yeni notlar alamayacaksiniz.
MEMO_OVER_LIMIT
	UYARI: Maximum not sayinizi astiniz (%d). Mevcutlardan bir kismini silmediginiz takdirde yeni notlar alamayacaksiniz.
MEMO_NEW_MEMO_ARRIVED
	%s nick'inden yeni bir notunuz var.
	/msg %s READ %d yazarak okuyabilirsiniz.

# Multi-use responses
MEMO_HAVE_NO_MEMOS
	Size herhangi bir not yok.
MEMO_X_HAS_NO_MEMOS
	%s nick'inin herhangi bir notu yok.
MEMO_DOES_NOT_EXIST
	%d numarali not bulunamadi!

# SEND responses
MEMO_SEND_DISABLED
	Not birakma (SEND) gecici olarak devre disidir.
MEMO_SEND_PLEASE_WAIT
	Lutfen SEND komutunu yeniden kullanmadan once %d saniye bekleyiniz.
MEMO_X_GETS_NO_MEMOS
	%s nick'ine not birakilamaz.
MEMO_X_HAS_TOO_MANY_MEMOS
	%s nick'i su anda limitini doldurdugundan daha fazla not alamaz.
MEMO_SENT
	Notunuz  %s nick'ine gonderilmistir..

# LIST responses
MEMO_HAVE_NO_NEW_MEMOS
	Herhangi bir notunuz yok.
MEMO_X_HAS_NO_NEW_MEMOS
	%s nick'inin yeni notu yok.
MEMO_LIST_MEMOS
	%s nick'ine ait notlar.  Okumak icin, /msg %s READ num yaziniz.
MEMO_LIST_NEW_MEMOS
	%s nick'i icin yeni notlar var. Okumak icin, /msg %s READ num yaziniz.
MEMO_LIST_CHAN_MEMOS
	%s kanali icin notlar var. Okumak icin, /msg %s READ %s num yaziniz.
MEMO_LIST_CHAN_NEW_MEMOS
	%s kanalinin yeni notu var. Okumak icin, /msg %s READ %s num yaziniz.
MEMO_LIST_HEADER
	 Sira  Gonderen            Tarih/Saat
MEMO_LIST_FORMAT
	%c%3d  %-16s  %s

# READ responses
MEMO_HEADER
	%d numarali not %s nick'inden (%s) .  Silmek icin, /msg %s DEL %d yaziniz.
MEMO_CHAN_HEADER
	%d numarali not %s nick'inden (%s).  Silmek icin, /msg %s DEL %s %d yaziniz.
MEMO_TEXT
	%s

# DEL responses
MEMO_DELETED_NONE
	Herhangi bir not silinmedi.
MEMO_DELETED_ONE
	%d numarali not silindi.
MEMO_DELETED_SEVERAL
	%s notlari silindi.
MEMO_DELETED_ALL
	Butun notlariniz silindi.

# SET responses
MEMO_SET_DISABLED
	MemoServ'un SET komutu gecici olarak devre disidir.
MEMO_SET_UNKNOWN_OPTION
	Varolmayan secenek: %s.

# SET NOTIFY responses
MEMO_SET_NOTIFY_ON
	%s artik size gonderilen notlarda online oldugunuzda ve/veya aninda uyari verecek.
MEMO_SET_NOTIFY_LOGON
	%s artik size gonderilen notlarda online oldugunuzda ve/veya /AWAY'den dondugunuzde uyari verecek.
MEMO_SET_NOTIFY_NEW
	%s artik size gonderilen notlarda aninda uyari verecek.
MEMO_SET_NOTIFY_OFF
	%s artik size herhangi bir uyari vermeyecek.

# SET LIMIT responses
MEMO_SET_YOUR_LIMIT_FORBIDDEN
	Not limitinizi belirleme yetkiniz yok.
MEMO_SET_LIMIT_FORBIDDEN
	%s nick'inin not limiti degistirilemez.
MEMO_SET_YOUR_LIMIT_TOO_HIGH
	Not limitiniz en fazla %d olabilir.
MEMO_SET_LIMIT_TOO_HIGH
	%s nick'inin limiti en fazla %d olabilir.
MEMO_SET_LIMIT_OVERFLOW
	Not limitiniz fazla.Limit %d olarak dusuruldu.
MEMO_SET_YOUR_LIMIT
	Not limitiniz %d olarak ayarlandi.
MEMO_SET_YOUR_LIMIT_ZERO
	Limitiniz sifir oldugundan bir daha not alamayacaksiniz.
MEMO_UNSET_YOUR_LIMIT
	Not limitiniz iptal edildi.
MEMO_SET_LIMIT
	%s nick'inin not limiti: %d.
MEMO_SET_LIMIT_ZERO
	%s nick'inin not limiti: 0.
MEMO_UNSET_LIMIT
	%s nick'inin not limiti: devre disi .

# INFO responses
MEMO_INFO_NO_MEMOS
	Su anda notunuz yok.
MEMO_INFO_MEMO
	Su anda 1 yeni notunuz var.
MEMO_INFO_MEMO_UNREAD
	Su anda 1 notunuz var, ve henuz okumadiniz.
MEMO_INFO_MEMOS
	Su anda %d notunuz var.
MEMO_INFO_MEMOS_ONE_UNREAD
	Su anda 1 'i okunmamis olmak uzere %d notunuz var.
MEMO_INFO_MEMOS_SOME_UNREAD
	Su anda %d adedi okunmamis olmak uzere %d notunuz var.
MEMO_INFO_MEMOS_ALL_UNREAD
	Su anda hicbirini okumadiginiz %d notunuz var.
MEMO_INFO_LIMIT
	Not limiti: %d.
MEMO_INFO_HARD_LIMIT
	Not limiti: %d, ve degistirme yetkiniz yok.
MEMO_INFO_LIMIT_ZERO
	Not limiti: 0; herhangi bir not alamayacaksiniz.
MEMO_INFO_HARD_LIMIT_ZERO
	Not limitiniz: 0; ve degistirme yetkiniz yok. Herhangi bir not alamayacaksiniz!
MEMO_INFO_NO_LIMIT
	Not limiti yok.
MEMO_INFO_X_NO_MEMOS
	%s nick'inin su anda notu yok.
MEMO_INFO_X_MEMO
	%s nick'inin su anda 1 notu var.
MEMO_INFO_X_MEMO_UNREAD
	%s nick'inin su anda 1 notu var, ve henuz okunmamis.
MEMO_INFO_X_MEMOS
	%s nick'inin %d notu var.
MEMO_INFO_X_MEMOS_ONE_UNREAD
	%s nick'inin 1 okunmamis olmak uzere %d notu var.
MEMO_INFO_X_MEMOS_SOME_UNREAD
	%s nick'inin %d okunmamis olmak uzere %d notu var.
MEMO_INFO_X_MEMOS_ALL_UNREAD
	%s nick'inin su anda hepsi okunmus %d notu var.
MEMO_INFO_X_LIMIT
	%s nick'inin memo limiti: %d.
MEMO_INFO_X_HARD_LIMIT
	%s nick'inin memo limiti: %d.
MEMO_INFO_X_NO_LIMIT
	%s nick'inin memo limiti yok.

###########################################################################
#
# OperServ messages
#
###########################################################################

# General messages
OPER_BOUNCY_MODES
	Services mode degistiremiyor. Server'larinizin dogru ayarlandigina emin misiniz?
OPER_BOUNCY_MODES_U_LINE
	Services mode degistiremiyor. Server'larinizin U:line 'larini kontrol edin.

# GLOBAL responses

# STATS responses
OPER_STATS_UNKNOWN_OPTION
	Varolmayan STATS secenegi: %s.
OPER_STATS_CURRENT_USERS
	Mevcut Kullanici : %d (%d ops)
OPER_STATS_MAX_USERS
	Maximum Kullanici: %d (%s)
# This is ugly, but at least it's language-portable...
OPER_STATS_UPTIME_DHMS
	Services %d gundur calisiyor.
OPER_STATS_UPTIME_1DHMS
	Services %d gundur calisiyor.
OPER_STATS_UPTIME_HMS
	Services %d saat, %d dakikadir calisiyor.
OPER_STATS_UPTIME_HM1S
	Services %d saat, %d dakikadir calisiyor.
OPER_STATS_UPTIME_H1MS
	Services %d saat, %d dakikadir calisiyor.
OPER_STATS_UPTIME_H1M1S
	Services %d saat, %d dakikadir calisiyor.
OPER_STATS_UPTIME_1HMS
	Services %d saat, %d dakikadir calisiyor.
OPER_STATS_UPTIME_1HM1S
	Services %d saat, %d dakikadir calisiyor.
OPER_STATS_UPTIME_1H1MS
	Services %d saat, %d dakikadir calisiyor.
OPER_STATS_UPTIME_1H1M1S
	Services %d saat, %d dakikadir calisiyor.
OPER_STATS_UPTIME_MS
	Services %d saat, %d dakikadir calisiyor.
OPER_STATS_UPTIME_M1S
	Services %d dakika, %d saniyedir calisiyor.
OPER_STATS_UPTIME_1MS
	Services %d dakika, %d saniyedir calisiyor.
OPER_STATS_UPTIME_1M1S
	Services %d dakika, %d saniyedir calisiyor.
OPER_STATS_USER_MEM
	Kullanici: %6d kayit, %5d kB
OPER_STATS_CHANNEL_MEM
	Kanal    : %6d kayit, %5d kB
OPER_STATS_NICKSERV_MEM
	NickServ : %6d kayit, %5d kB
OPER_STATS_CHANSERV_MEM
	ChanServ : %6d kayit, %5d kB
OPER_STATS_OPERSERV_MEM
	Haydar   : %6d kayit, %5d kB
OPER_STATS_AKILL_COUNT
	Su anki AKILL adedi         : %d
OPER_STATS_AKILL_EXPIRE_DAYS
	Varsayilan AKILL zaman asimi: %d gun
OPER_STATS_AKILL_EXPIRE_DAY
	Varsayilan AKILL zaman asimi: %d gun1 gun
OPER_STATS_AKILL_EXPIRE_HOURS
	Varsayilan AKILL zaman asimi: %d gun%d saat
OPER_STATS_AKILL_EXPIRE_HOUR
	Varsayilan AKILL zaman asimi: %d gun1 saat
OPER_STATS_AKILL_EXPIRE_MINS
	Varsayilan AKILL zaman asimi: %d gun%d dakika
OPER_STATS_AKILL_EXPIRE_MIN
	Varsayilan AKILL zaman asimi: %d gun1 dakika
OPER_STATS_AKILL_EXPIRE_NONE
	Varsayilan AKILL zaman asimi: %d gunYOK

# MODE responses

# CLEARMODES responses
OPER_CLEARMODES_DONE
	Kanal mode'lari ve banlar %s kanalinda temizlendi.
OPER_CLEARMODES_ALL_DONE
	%s kanalindaki butun mode'lar temizlendi.

# KICK responses

# ADMIN responses
OPER_ADMIN_SKELETON
	Services iskelet mode'da (skeleton); ADMIN komutlari devre disi.
OPER_ADMIN_EXISTS
	%s zaten Services admin listesinde.
OPER_ADMIN_ADDED
	%s Services admin listesine eklendi.
OPER_ADMIN_TOO_MANY
	Services admin listesi dolu (%d); ekleme iptal edildi.	
OPER_ADMIN_REMOVED
	%s Services admin listesinden silindi.
OPER_ADMIN_NOT_FOUND
	%s Services admin listesinde bulunamadi.
OPER_ADMIN_LIST_HEADER
	Services admin listesi:

# OPER responses
OPER_OPER_SKELETON
	Services iskelet mode'da (skeleton); OPER komutu devre disi.
OPER_OPER_EXISTS
	%s zaten Services operator listesinde.
OPER_OPER_ADDED
	%s Services operator listesine eklendi.
OPER_OPER_TOO_MANY
	Services operator listesi dolu (%d); ekleme iptal edildi.
OPER_OPER_REMOVED
	%s Services operator listesinden silindi.
OPER_OPER_NOT_FOUND
	%s Services operator listesinde bulunamadi.
OPER_OPER_LIST_HEADER
	Services operator listesi:
	
# AKILL responses
OPER_AKILL_NO_NICK
	Hatirlatma: AKILL'lerde nick bulunamaz.AKILL'inize nick yazmadiginizdan emin olun.
OPER_AKILL_ADDED
	%s AKILL listesine eklendi.
OPER_AKILL_REMOVED
	%s AKILL listesinden silindi.
OPER_AKILL_NOT_FOUND
	%s AKILL listesinde bulunamadi.
OPER_AKILL_LIST_HEADER
	Su Anki AKILL Listesi:
# mask, reason
OPER_AKILL_LIST_FORMAT
	%-32s  %s
# mask, set-by, set-time, expires, reason
OPER_AKILL_VIEW_FORMAT
	%s (by %s on %s; %s)
	    %s
OPER_AKILL_NO_EXPIRE
	Zaman asimi yok.
OPER_AKILL_EXPIRES_SOON
	Ilk veritabani guncellemesinde silinecek.
OPER_AKILL_EXPIRES_M
	%d dakika sonra silinecek.
OPER_AKILL_EXPIRES_1M
	%d dakika sonra silinecek.
OPER_AKILL_EXPIRES_HM
	%d saat, %d dakika sonra silinecek.
OPER_AKILL_EXPIRES_H1M
	%d saat, %d dakika sonra silinecek.
OPER_AKILL_EXPIRES_1HM
	%d saat, %d dakika sonra silinecek.
OPER_AKILL_EXPIRES_1H1M
	%d saat, %d dakika sonra silinecek.
OPER_AKILL_EXPIRES_D
	%d gun sonra silinecek.
OPER_AKILL_EXPIRES_1D
	%d gun sonra silinecek.

# SET responses
OPER_SET_IGNORE_ON
	Ignore kodu AKTIF .
OPER_SET_IGNORE_OFF
	Ignore kodu KAPALI .
OPER_SET_IGNORE_ERROR
	IGNORE ayari ON veya OFF seklinde olmali.
OPER_SET_READONLY_ON
	Services su anda read-only calisiyor.
OPER_SET_READONLY_OFF
	Services su anda read-write calisiyor.
OPER_SET_READONLY_ERROR
	READONLY ayari ON veya OFF seklinde olmali.
OPER_SET_DEBUG_ON
	Services su anda debug mode'unda calisiyor.
OPER_SET_DEBUG_OFF
	Services su anda non-debug mode'unda calisiyor.
OPER_SET_DEBUG_LEVEL
	Services su anda debug mode'unda (level %d).
OPER_SET_DEBUG_ERROR
	DEBUG ayari ON, OFF formatinda veya pozitif bir sayi olmali.
OPER_SET_UNKNOWN_OPTION
	Varolmayan secenek: %s.

# JUPE responses

# RAW responses

# UPDATE responses
OPER_UPDATING
	Veritabani guncelleniyor.

# RESTART responses
OPER_CANNOT_RESTART
	SERVICES_BIN tanimlanmamis; restart edilemiyor.  Yeniden \2configure\2 ederek Services'i RESTART komutu eklenmis olarak derleyin.

# LISTIGNORE responses
OPER_IGNORE_LIST
	Services ignore listesi:
OPER_IGNORE_LIST_EMPTY
	Ignore listesi bos.

### Changes 5 September Monday / 15.58




###########################################################################
#
# NickServ help messages
#
###########################################################################

NICK_HELP
	%S size bir nick'i kaydetme ve baskalarinin
	kullanmasini engelleme imkani saglar.Eger nick %d gun
	kullanilmassa otomatik olarak drop edilecektir.Asagidaki
	komutlari nick'inizi keydedebilmeniz ve sonrasi icin
	/msg %S komut seklinde kullanabilirsiniz.
	Belirli bir komut hakkinda daha fazla bilgi almak icinse
	/msg %S help komut yazmaniz yeterlidir.
	
	    REGISTER   O anki nick'i sizin adiniza kaydeder.
	    IDENTIFY   Sizi nick'in sahibi olarak tanitir.
	    ACCESS     Nick'inizin erisim listesini duzenler.
	    SET        Cesitli %S ozelliklerini duzenler.
	    DROP       Nick'inizin kaydini siler.
	    RECOVER    Nickinizi kullanan bir baskasini KILL'ler.
	    RELEASE    RECOVER komutundan sonra tutulan nick'i birakir.	
	
	Diger Komutlar: UNLINK, GHOST, INFO, LIST, STATUS
	
	ONEMLI: %S kullanicilarin IRC'deki kimliklerini
	guvence altina almak amaci ile duzenlenmistir.Kesinlikle bir
	baskasinin nick'ini calmayi kolaylastirma amacli degildir.
	%S'un amac disi kullanimi kesinlikle yasaktir ve
	tesbit edilmesi durumunda adiniza kayitli nick ve kanallarin
	yasaklanmasi ile sonuclanacaktir.

NICK_HELP_REGISTER
	Kullanimi: REGISTER sifre
	
	Nick'inizi %S veritabanina kaydeder.Nick'iniz kaydedildikten
	sonra (register) SET ve ACCESS komutlarini kullanarak
	ayarlarinizi istediginiz sekilde degistirebilirsiniz.Kayit
	sirasinda kullandiginiz sifreyi unutmamaniz onemlidir.
	Sifrenizde kucuk ve buyuk harfler farkli karakterlerdir!
	
	Sifreniz hakkinda oneriler:
	
	Sifrenizi secerken gercek adiniz gibi kolay tahmin
	edilebilecek seyler kullanmayin.Kisa sifreler de guvenilir
	degildir.Bu nedenle en azindan 5 karakter uzunlugunda ve
	icinde space karakteri bulunmayan,hatta icinde rakam olan
	karakter serileri secmeniz yarariniza olacaktir.

NICK_HELP_IDENTIFY
	Kullanimi: IDENTIFY sifre
	
	Kendinizi %S 'e nick'in sahibi olarak tanitmanizi saglar.
	Pekcok komutu kullanabilmeniz icin bu gereklidir.Sifreniz
	REGISTER komutu sirasinda kullandiginiz ile ayni olmalidir.

NICK_HELP_DROP
	Kullanimi: DROP
	
	Nick'inizin %S veritabanindaki kaydini siler.Drop
	edilen bir nick'i bir baskasi kaydedebilir.Bu komutu
	kullanabilmeniz icin once sifrenizi kullanarak kendinizi
	tanitmalisiniz.(/msg %S HELP IDENTIFY yazarak daha
	genis bilgi alabilirsiniz).

NICK_HELP_ACCESS
	Kullanimi: ACCESS ADD mask
	           ACCESS DEL mask
	           ACCESS LIST
	
	Nick'inizin erisim listesini duzenler ve/veya goruntuler.
	Bu liste %S tarafindan otomatik olarak taninacak
	adresleri belirler.Bu durumda eger farkli bir adresle
	nickinizi kullanacaginizda IDENTIFY komutunu ile once
	kendinizi tanitmaniz gerekir.
	
	Ornekler:
	
	    ACCESS ADD *!mikado@*.holyfire.com
	        mikado isimli kullanicinin holyfire.com
	        domain'indeki herhangi bir makineden taninmasi.
	
	    ACCESS DEL *!mikado@*.holyfire.com
	        Onceki komutu geri alir.
	
	    ACCESS LIST
	        O anki access list'i goruntuler.

NICK_HELP_LINK
	Kullanimi: LINK nick sifre
	
	Nick'inizi bir baska nick ile "linkler".Linklemenin mantigi
	iki farkli nick'in birbiri ile ayni ozelliklere (ayricalik
	ve kisitlamalar) sahip bir nick haline getirmektir.Link
	gerceklestigi anda notlar,access list ortaklasa hale
	gelecektir.Bu yuzden ornegin yenilerini alabilmek icin bazi
	notlari silmeniz gerekebilir.Link "DROP" komutunu
	kapsamayacak,bir nick'in kaydinin silinmesi halinde sadece
	link ortadan kalkacaktir.
	
	Bu komutu kullanabilmeniz icin once sifrenizi kullanarak
	kendinizi tanitmali ve linklemek istediginiz nick'in de
	sifresini belirtmelisiniz.

NICK_HELP_UNLINK
	Kullanimi: UNLINK
	
	Nick'inizin bir baskasi ile olan linkini siler.Link
	silindigi zaman ornegin ortak erisim listesi alinmakla
	beraber ortak notlar kopyalanmaz.Tum notlar linki ayrilan
	nick'in veritabaninda kayitli kalir.

NICK_HELP_SET
	Kullanimi: SET secenek parametreler
	
	Cesitli %S seceneklerini ayarlar.
	Gecerli secenek'ler:
	
	    PASSWORD   Nick'inizin sifresini degistirir.
	    LANGUAGE   Services'in size hitap edecegi dili belirler.
	    URL        Belirtilen URL'yi nick'inizle iliskilendirir.
	    EMAIL      Belirtilen E-Mail'i nick'inizle iliskilendirir.
	    KILL       Kill secenegini acar/kapar.
	    SECURE     Security secenegini acar/kapar.
	    PRIVATE    /msg %S LIST komutu ile cikacak listede
	                  nick'inizin gorunmesini engeller.
	    HIDE       Nick bilgilerinizin bir kismini "INFO"
	                  kismindan saklar.
	
	Bu komutu kullanabilmeniz icin once sifrenizi kullanarak
	kendinizi tanitmalisiniz.(/msg %S HELP IDENTIFY
	yazarak daha genis bilgi alabilirsiniz).
	
	Belirli bir komut hakkinda daha fazla bilgi almak icin
	/msg %S HELP SET secenek yazabilirsiniz.

NICK_HELP_SET_PASSWORD
	Kullanimi: SET PASSWORD yeni-sifre
	
	Sizi %S'e nick'in sahibi olarak tanitacak olan sifreyi
	degistirir.

NICK_HELP_SET_LANGUAGE
	Kullanimi: SET LANGUAGE numara
	
	Services'in size hitap edecegi dili degistirir.numara
	desteklenen dillerden birine ait bir numara olmalidir:

NICK_HELP_SET_URL
	Kullanimi: SET URL url
	
	Belirtilen URL'yi nick'inizle iliskilendirir.Bu URL INFO
	komutu ile nick'iniz hakkinda alinabilecek bilgiye
	eklenecektir.

NICK_HELP_SET_EMAIL
	Kullanimi: SET EMAIL adres
	
	Belirtilen E-Mail adresini nick'inizle iliskilendirir.Bu
	E-Mail INFO komutu ile nick'iniz hakkinda alinabilecek
	bilgiye eklenecektir.

NICK_HELP_SET_KILL
	Kullanimi: SET KILL {ON | QUICK | IMMED | OFF}
	
	Otomatik Kill secenegini acar/kapar.Kill acik oldugu zaman
	nick'inizi almaya calisan baska bir kullaniciya degistirmesi
	icin bir dakika taninacak ve eger degistirmezse %S
	tarafindan IRC baglantisi kesilerek "KILL" edilecektir.
	
	Eger QUICK secenegini secerseniz,kullaniciya taninan sure
	1 dakika yerine 20 saniye olur.Eger IMMED secenegi aktifse
	kullanici uyarilmadan "KILL" edilir.Lutfen bu ozelligi
	gereksiz yere kullanmayin.Ayrica network yoneticiniz bu
	secenegi devreden cikarmis olabilir.

NICK_HELP_SET_SECURE
	Kullanimi: SET SECURE {ON | OFF}
	
	%S's guvenlik fonksiyonlarini acar/kapar. SECURE
	secenegi aktif iken nick'inizin sahibi olarak taninmaniz
	icin erisim listenize bakilmaksizin sifrenizi kullanarak
	kendinizi %S'e tanitmaniz gerekir.Ancak %S 'un
	erisim listesinde iseniz eger,sizi tanimamasina ragmen
	"KILL" 'lemeyecektir.

NICK_HELP_SET_PRIVATE
	Kullanimi: SET PRIVATE {ON | OFF}
	
	/msg %S LIST komutu ile cikacak listede nick'inizin
	gorunmesini engeller.Ancak yine de INFO komutu ile
	nick'iniz hakkinda bilgi alabilir.

NICK_HELP_SET_HIDE
	Kullanimi: SET HIDE {EMAIL | USERMASK | QUIT} {ON | OFF}
	
	Nick bilgilerinizdeki bazi kisimlari saklamanizi saglar.Her
	kullanicinin "/msg %S INFO" komutu ile gorebilecegi
	bilgilerden E-mail adresinizi (EMAIL), IRC'de son olarak
	goruldugunuz zaman (last seen) , user@host'u (USERMASK) ve
	son quit mesajinizdan (QUIT) istediklerinizi
	saklayabilirsiniz.Hangi kismin saklanacagindan hemen sonraki
	parametre (OFF) veya (ON) seklinde olmalidir.

NICK_HELP_RECOVER
	Kullanimi: RECOVER nickiniz [sifreniz]
	
	Nick'inizi kullanan bir kullaniciyi server'dan atmanizi
	saglar. Bu , "KILL" seceneginin aktif olmasi halinde
	%S 'un otomatik olarak yapacagi islemdir.
	
	Bu komutu verdiginizde , %S server'a belirtilen nick'i
	tasiyan bir clone sokar.Bu durum da IRC server'larinin oteki
	kullaniciyi hattan atmalarina yol acar.Bu "clone" karsi
	tarafin hemen yeniden baglanip nick'i yeniden almasina imkan
	vermemek icin bir dakika sureyle hatta kalir.Nick'inizi bu
	bir dakikalik surenin sonunda geri alabilir veya RELEASE
	komutunu kullanarak daha erken serbest birakilmasini
	saglayabilirsiniz.(/msg %S HELP RELEASE)
	
	Bu komutu kullanabilmeniz icin o anki /WHOIS 'iniz erisim
	listenizde olmali veya sifrenizi kullanarak kendinizi
	%S'e tanitmalisiniz.

NICK_HELP_RELEASE
	Kullanimi: RELEASE nickiniz [sifreniz]
	
	%S tarafindan tutulan nick'inizin 1 dakikalik sure
	dolmadan serbest birakilmasini saglar.
	
	Bu komutu kullanabilmeniz icin o anki /WHOIS 'iniz erisim
	listenizde olmali veya sifrenizi kullanarak kendinizi
	%S'e tanitmalisiniz.

NICK_HELP_GHOST
	Kullanimi: GHOST nickiniz [sifreniz]
	
	IRC'de asili kalmis olan nick'inizi temizler."GHOST" genelde
	bilgisayarinizin takilmasi gibi bir sebeple siz IRC'den
	cikmadan internet baglantinizin kesilmesi sonucunda
	server'da asili kalan nick'inize verilen addir.
	
	Bu komutu kullanabilmeniz icin o anki /WHOIS 'iniz erisim
	listenizde olmali veya sifrenizi kullanarak kendinizi
	%S'e tanitmalisiniz.	

NICK_HELP_INFO
	Kullanimi: INFO nick
	
	Belirtilen nick'in bilgilerini (nick sahibi,secenekler,URL
	vs.) listeler.

NICK_HELP_LIST
	Kullanimi: LIST parametre
	
	Belirtilen parametreye uyan butun kayitli nick'leri
	nick!user@host formatinda listeler.PRIVATE ozelligi aktif
	olan nick'ler bu listede gorunmezler.
	
	Ornekler:
	
	    LIST *!mikado@holyfire.com
	        Sahibinin *!mikado@holyfire.com oldugu butun kayitli
	        nickleri listeler.
	
	    LIST *Bot*!*@*
	        Isminde Bot kelimesi gecen kayitli nick'leri
	        listeler.(kucuk buyuk harf farki vardir.yani "a" ve
	        "A" farklidir).
	
	    LIST *!*@*.holyfire.com
	        holyfire.com domain'ine ait butun nick'leri
	        listeler.

NICK_HELP_STATUS
	Kullanimi: STATUS [nick]
	
	Belirtilen kullanicinin nick'in sahibi olrak taninip
	taninmadigini goruntuler.Cevap su sekildedir:
	
	    nick statu-kodu
	
	Burada nick sizin komutta belirttiginiz nick iken statu-kodu
	asagidakilerden biri olabilir:
	
	    0 - Bu kullanici hatta deil (offline) veya bu kayitli
	            bir nick degil.
	    1 - Bu kullanici %S tarafindan nick'in sahibi
	            olarak taninmamis.
	    2 - Bu kullanici erisim listesi ile taninmis.
	    3 - Bu kullanici nick sifresi ile  taninmis.
	
	Her komutta 16 nick'e kadar belirtilebilir.Kalanlar dikkate
	alinmayacaktir.Eger nick belirtilmez ise herhangi bir hata
	mesaji verilmez.

NICK_SERVADMIN_HELP
	
	Asagidaki komutlar sadece Services admin'ler icindir:
	
	    GETPASS    Belirtilen nick'in sifresini verir.
	    FORBID     Belirtilen nick'in kullanimini yasaklar.
	
	Services admin'ler ayrica "IDENTIFY" komutunu kullanmaksizin
	bir nick'in kaydini silebilir (DROP), sifresini
	degistirebilir ve/veya erisim listesini
	(/msg %S ACCESS LIST nick) komutu ile
	goruntuleyebilirler.

NICK_SERVADMIN_HELP_DROP
	Kullanimi: DROP nick
	
	Herhangi bir ek parametre kullanilmadan,nickinizi %S
	veritabanindan silen bu komutla,sadece Services admin 'ler
	belirtecekleri baska nick'leri de %S veritabanindan
	silebilirler (DROP).

NICK_SERVADMIN_HELP_SET
	
	Services admin'ler ayrica NOEXPIRE komutunu da kullanmaya
	ve bu sekilde belirtilen nick'lerin zaman asimi yuzunden
	silinmelerini (EXPIRE) engellemeye de yetkilidirler.Services
	admin'ler sifreyi girmelerine gerek olmaksizin
	belirtecekleri her nick'in ayarlarini
	SET nick secenek parametre komutu ile degistirme yetkisine
	sahiptirler.

NICK_SERVADMIN_HELP_SET_NOEXPIRE
	Kullanimi: SET nick NOEXPIRE {ON | OFF}
	
	ON parametresinin kullanilmasi halinde,belirtilen nick zaman
	asimi nedeni ile %S veritabanindan silinmeyecektir.
	
	Bu komutu sadece Services admin'ler kullanabilir.

#NICK_SERVADMIN_HELP_LIST
#	Kullanimi: LIST degisken
#	
#	Belirtilen degiskene uyan butun kayitli nick'leri
#	nick!user@host formatinda listeler.Services admin'ler
#	PRIVATE seceneg aktif olan nick'leri de gorebilirler.
#	
#	Ornekler:
#	
#	    LIST *!mikado@*.holyfire.com
#	        *!mikado@*.holyfire.com'un sahibi oldugu tum kayitli
#	        nick'leri listeler.
#	
#	    LIST *Bot*!*@*
#	        Isminde Bot kelimesi gecen kayitli nick'leri
#	        listeler.(kucuk buyuk harf farki vardir.yani "a" ve
#	        "A" farklidir).

NICK_SERVADMIN_HELP_GETPASS
	Kullanimi: GETPASS nick
	
	Belirtilen nick'in sifresini verir.Bu komut kullanildiginda
	komutu kullanan Services admin'in nick'ini de iceren bir
	server mesaji (WALLOPS veya GLOBOPS seklinde) da ayni anda
	atilir.
	
	Bu komutu sadece Services admin'ler kullanabilir ve
	sifreleme (encryption) aktif iken devre disidir.

NICK_SERVADMIN_HELP_FORBID
	Kullanimi: FORBID nick
	
	Belirtilen nick'in kullanimini yasaklar.Yasagin kaldirilmasi icin
	sozkonusu nick'in %S veritabanindan silinmesi gerekir.(DROP)
	
	Bu komutu sadece Services admin'ler kullanabilir.

###########################################################################
#
# ChanServ help messages
#
###########################################################################

CHAN_HELP
	%S size bir kanali kendi adiniza kaydetme ve onu
	cesitli yonetme imkani saglar. %S cogu zaman kotu
	niyetli kullanicilarin kanalinizi elegecirmelerini
	(takeover) , ornegin kanalda sadece belirli bir listedeki
	kisilerin op olmalarina izin vererek engeller.Mevcut
	komutlar asagida listelenmistir.Kullanmak icin
	/msg %S komut yazabilirsiniz.Belirli bir komut hakkinda daha
	ayrintili bilgi almak icinse /msg %S HELP komut yazmaniz
	yeterlidir.
	
	    REGISTER   Kanali sizin adiniza %S veritabanina kaydeder.
	    IDENTIFY   Sifreniz ile birlikte sizi kanal sahibi olarak tanitir.
	    SET        Cesitli kanal ozelliklerini ve kanal bilgisinini ayarlar.
	    ACCESS     Ayricalikli kullanicilarin listesini duzenler.
	    LEVELS     Kullanicilarin erisim seviyelerini yeniden duzenler.
	    AKICK      OtoKick listesini duzenler.
	    DROP       Kanalin kaydini %S veritabanindan siler.
	
	Diger Komutlar: INFO, LIST, INVITE, OP, DEOP, UNBAN,
	                CLEAR

CHAN_HELP_EXPIRES
	
	Unutulmamalidir ki %d gun suresince kullanilmayan kanallar otomatik
	olarak silinirler.(ornegin access list'indeki kimsenin bu sure icerisinde
	kanala girmemesi durumunda)

CHAN_HELP_REGISTER
	Kullanimi: REGISTER kanal sifre aciklama
	
	Bir kanali sizin adiniza kaydeder.Bu komutu kullanabilmek
	icin sozkonusu kanalda operator olmaniz gerekir.Sifreniz
	daha sonra IDENTIFY komutunu kullanarak kendinizi kanalin
	sahibi olarak %S'e tanitacaginiz sifre oldugundan
	kolay tahmin edilemeyecek ve sizin de unutmayacaginiz bir
	sifre secmeniz onemlidir.Aciklama kismi ise,kanal hakkinda
	genel bir aciklama niteligindedir.Bir kanali kaydettiginizde
	(register) o kanalin sahibi olarak "founder" taninirsiniz.
	Kanal founder'i kanalda bazi ayar ve degisiklikler yapma
	hakkina sahiptir.Ayrica %S founder nick'ine kanala her
	girisinde otomatik olarak op verecektir.ACCESS ve/veya
	LEVELS komutlarini kullanarak (/msg %S HELP ACCESS) founder
	yetkilerinden bazilarini diger kullanicilara da vermek
	mumkundur.
	
	ONEMLI NOT: Bir kanali adiniza register edebilmek icin
	oncelikle nick'inizi register etmeniz gerekir.Eger
	nick'inizi register etmediyseniz /msg %S HELP yazarak
	yardim alabilirsiniz.

CHAN_HELP_IDENTIFY
	Kullanimi: IDENTIFY kanal sifre
	
	Sizi %S'e belirtilen kanalin founder'i olarak tanitir.
	Pek cok komutu kullanabilmek icin once kendinizi founder
	olarak tanitmaniz gerekir.Sifre kismi kanali register
	ederken kullanilan

CHAN_HELP_DROP
	Kullanimi: DROP kanal
	Belirtilen kanalin kaydini siler.Sadece founder tarafindan
	IDENTIFY komutundan sonra kullanilabilir.

CHAN_HELP_SET
	Kullanimi: SET kanal secenek parametre
	
	Kanal founder'inin cesitli kanal opsiyonlarini ve
	bilgilerini degistirmesi icindir.Founder once IDENTIFY
	komutunu kullanarak kendini %S'e tanitmalidir.
	
	Kanal Secenekleri:
	
	    FOUNDER     Kanal founder'ini belirtir.
	    PASSWORD    Founder sifresini degistirir.
	    DESC        Kanal hakkindaki aciklamayi degistirir.
	    URL         Bir internet adresini kanal ile iliskilendirir.
	    EMAIL       Bir E-Mail adresini kanal ile iliskilendirir.
	    TOPIC       Kanal topic'ini degistirir.
	    MLOCK       Kanal modlarini kilitler/acar.
	    KEEPTOPIC   Kanal kullanilmadigi zaman topici hafizada
	                   tutar.
	    TOPICLOCK   Kullanilmasi durumunda topic ancak SET TOPIC
	                   ile degisir.
	    PRIVATE     Kanali %S listesinden saklar.
	    SECUREOPS   Kanal access list'indeki oplar disinda kimse
	                   op alamaz.
	    RESTRICTED  Kanala access list'te olanlar disindakiler
	                   giremez.
	    SECURE      %S guvenlik fonksiyonlarini aktif hale
	                   getirir.
	
	/msg %S HELP secenek yazarak belirli bir secenek hakkinda
	daha ayrintili bilgi alabilirsiniz.

CHAN_HELP_SET_FOUNDER
	Kullanimi: SET kanal FOUNDER nick
	
	Belirtilen kanalin founder'ini (sahibini) degistirir.Yeni
	nick te %s'e kaydedilmis olmalidir.

CHAN_HELP_SET_PASSWORD
	Kullanimi: SET kanal PASSWORD yenisifre
	
	Kullanicinin kanalin sahibi olarak taninacagi sifreyi
	belirler.

CHAN_HELP_SET_DESC
	Kullanimi: SET kanal DESC aciklama
	
	Belirtilen kanal hakkindaki,LIST ve INFO komutlari ile
	gorunecek olan aciklamayi belirler.Kullanabilmek icin
	founder level access gerekir.

CHAN_HELP_SET_URL
	Kullanimi: SET kanal URL webadresi
	
	Belirtilmis URL'yi kanal ile iliskilendirir.Bu URL "INFO"
	komutu ile kanal hakkinda bilgi istendiginde gorunecektir.
	Eger "webadresi" belirtilmezse o anki mevcut kanal "URL" 'si
	silinecektir.

CHAN_HELP_SET_EMAIL
	Kullanimi: SET kanal EMAIL e-mail adresi
	
	Belirtilen e-mail adresini yine belirtilen kanal ile iliskilendirir.
	Bir kullanici kanal hakkinda INFO komutu ile bilgi istediginde bu e-mail
	adresi de gozukur.Eger "e-mail adresi" belirtilmezse o anki mevcut
	kanal "EMAIL" 'i silinecektir.

CHAN_HELP_SET_ENTRYMSG
	Kullanimi: SET kanal ENTRYMSG mesaj
	
	Kullanicilarin kanala giriste /notice seklinde alacaklari
	mesaji belirler.Eger parametre kullanilmazsa kanala giriste
	mesaj atilmaz.

CHAN_HELP_SET_TOPIC
	Kullanimi: SET kanal TOPIC topic
	
	%S 'un kanala topic atmasini saglar.Ozellikle
	TOPICLOCK ozelliginin aktif oldugu zamanlarda
	kullanislidir.

CHAN_HELP_SET_KEEPTOPIC
	Kullanimi: SET kanal KEEPTOPIC {ON|OFF}
	
	Kanalin topic hatirlama (retention) opsiyonunu acar/kapar.
	topic retention aktifken, kanalin topici %S tarafindan
	son kullanici da kanaldan ayrildiktan sonra dahi
	hatirlanacak ve kanala bir kullanici geldiginde yeniden
	yerine yazilacaktir.	

CHAN_HELP_SET_TOPICLOCK
	Kullanimi: SET kanal TOPICLOCK {ON|OFF}
	
	Kanalin topic kilidi (topiclock) opsiyonunu acar/kapar.
	topic lock aktifken, %S kanal topicinin SET TOPIC
	disindaki herhangi bir komutla degistirilmesine izin
	vermeyecektir.

CHAN_HELP_SET_MLOCK
	Kullanimi: SET kanal MLOCK modlar
	
	Kanalin mod-kilidi (mode-lock) parametresini acar/kapar.
	%S size bazi kanal modlarinin daimi olarak aktif veya
	kapali tutma imkani saglar.Sozkonusu modlar i, k, l, m, n,
	p, s, ve t arasindan bir veya birkaci olabilir.modlar
	parametresinin sekli /MODE komutundaki kullanimi ile
	aynidir.(Ornegin +nt , -isp gibi.)
	
	UYARI:  Eger asagidaki ikinci ornek seklinde bir "MLOCK"
	yapacaksaniz ek olarak RESTRICTED opsiyonunu da
	kullanmalisiniz (bkz. HELP SET RESTRICTED).Aksi takdirde
	kanal bos iken kanala giren herhangi biri kanal anahtarini
	(KEY) gorebilecektir!
	
	Ornekler:
	
	    SET #kanal MLOCK +nt-iklps
	        Kanalda +nt modlari surekli aktif (+) iken, i, k, l,
	        p, ve s off surekli devre disi (-) kalacaktir.Kanal
	        kodu m ise serbest birakilmistir.
	
	    SET #kanal MLOCK +knst-ilmp anahtarim
	        k, n, s, and t modlari surekli aktifken i, l, m, ve
	        p modlari surekli devre disidir.Ayrica kanalin
	        anahtari da (KEY) "anahtarim" seklinde sabit
	        tutulur.
	
	    SET #kanal MLOCK +
	        Mode-lock opsiyonunu kaldirir.Boylece butun kanal
	        modlari serbest kalir.

CHAN_HELP_SET_PRIVATE
	Kullanimi: SET kanal PRIVATE {ON|OFF}
	
	Kanalin private ozelligini acar/kapar.private ozelligi aktif
	olan kanallar /msg %S LIST komutu ile alinabilecek listede
	gorunmezler.
	
CHAN_HELP_SET_RESTRICTED
	Kullanimi: SET kanal RESTRICTED {ON|OFF}
	
	Kanalin RESTRICTED ozelligini acar/kapar.Bu ozelligin aktif
	oldugu bir kanalda, normalde kanalda op alamayan
	kullanicilar (yani negatif erisim seviyesi olanlar) kanala
	giremeyeceklerdir.

CHAN_HELP_SET_SECURE
	Kullanimi: SET kanal SECURE {ON|OFF}
	
	%S'un guvenlik ozelliklerini acar/kapar.SECURE
	aktifken, kanala sadece kayitli nick'li kullanicilar
	kendilerini "IDENTIFY" komutu ile %s'e tanittiktan
	sonra girebilirler.

CHAN_HELP_SET_SECUREOPS
	Kullanimi: SET kanal SECUREOPS {ON|OFF}
	
	Kanalin secure ops ozelligini acar/kapar.Bu ozellik aktifken
	kanalin erisim listesinde olmayan kullancilar op alamazlar.

#CHAN_HELP_ACCESS
#	Kullanimi: ACCESS kanal ADD [nick] seviye}
#		   ACCESS kanal DEL {nick | sira-no}
#		   ACCESS kanal LIST [mask]
#		
#	Kanalin erisim listesi'ni (access list) duzenler.Bu liste
#	kanalda kimlerin oto-op olacagi ve/veya %S komutlarina
#	kimlerin erisebilecegi gibi bilgileri saklar.Degisik erisim
#	haklari icin farkli erisim seviyeleri (access level)
#	belirlenmistir.Standart olan bu seviyelerin buyuk bir kismi
#	kanal sahibi tarafindan degistirilebilir.(bkz.
#	/msg %S HELP ACCESS LEVELS) Bir kanalin kullanici
#	listesinde (access list) bulunmayan her nick'in seviyesi
#	varsayilan deger olarak 0'dir.
#	
#	ACCESS ADD komutu belirtilen nick'i, yine belirtilen seviye
#	ile kanalin erisim listesine eklemek icin kullanilir.Burada
#	sozedilen seviye komutu kullanan kullanicininkinden sayica
#	daha dusuk olmak zorundadir.Eger eklenmek istenen kullanici
#	zaten listedeyse de komutu veren kullanicinin seviyesi
#	(access level) daha yuksek olmalidir.Baska bir deyisle
#	sizinkinden yuksek seviyeli bir kullanici icin bu komutu
#	kullanamazsiniz.
#	
#	ACCESS DEL komutu belirtilen nick'i kanalin erisim
#	listesinden siler.
#	
#	ACCESS LIST komutu kanalin erisim listesini (access list)
#	goruntuler.Eger ek bir parametre belirtilmis ise,sadece buna
#	uyan veriler listelenir.

CHAN_HELP_ACCESS_LEVELS
	Kullanici Seviyeleri
	
	Varsayilan degerler olarak asagidaki seviyeler
	belirlenmistir:
	
	   Founder  Kanal sahibi olarak %S komutlarina tam
	                yetki, kanala giriste otomatik op.Dikkat
	                edilirse sadece bir kisi founder
	                ozelliklerine sahip olabilir.(ACCESS komutu
	                kullanilarak paylasilamaz).
	        10  AKICK komutunu kullanma yetkisi,otomatik op.
	         5  Kanala giriste otomatik op.
	         3  Kanala giriste otomatik voice (+v).
	         0  Siradan kullanici.secure-ops ozelliginin aktif
			olmadigi durumlarda op veya voice verilebilir.
	        <0  Kullanici kanalda op olamaz.
	
	Bu seviyeler LEVELS komutu kullanilarak degisebilir ve/veya
	yenileri eklenebilir.Daha ayrintili bilgi icin
	/msg %S HELP LEVELS yaziniz.

CHAN_HELP_AKICK
	Kullanimi: AKICK kanal ADD mask [sebep]
	           AKICK kanal DEL mask
	           AKICK kanal LIST	
	
	Kanalin AutoKick listesi'ni duzenler.Eger bu listedeki bir
	kullanici kanala girerse, %S once bu kullaniciyi
	banlayacak,hemen ardindan da kickleyecektir.
	
	AKICK ADD komutu belirtilen nick veya mask'i kanalin akick
	listesine alir.Eger belirtilmis ise sebep kick mesaji olarak
	kullanilir.
	
	AKICK DEL belirlenen nick veya mask'i kanalin akick
	listesinden siler.Bu nick veya mask'a ait kanaldaki herhangi
	bir ban'i silmez.Bu ban'lar kanal op'lari tarafindan
	kaldirilmalidir.
	
	AKICK LIST komutu kanalin akick listesini goruntuler.Eger ek
	bir parametre belirtilmis ise,sadece buna uyan veriler
	listelenir.

CHAN_HELP_LEVELS
	Kullanimi: LEVELS kanal SET ozellik seviye
	           LEVELS kanal {DIS | DISABLE} ozellik
	           LEVELS kanal RESET
	
	LEVELS komutu kanaldaki erisim seviyelerinin varsayilan
	degerlerini duzenlemek icin kullanilir.Surekli kullanilan
	%S ozelliklerine degisik numerik seviyeler vererek
	onlari daha cok sayida kullaniciya acar veya kaparsiniz.
	Ancak SET FOUNDER ve SET PASSWORD komutlari hala kanal
	sahibine (founder) ozel birakilmistir.
	
	LEVELS SET komutu ile bir veya birkac ozelligin varsayilan
	numerik degerleri degistirilebilir.LEVELS DISABLE veya DIS
	komutu ileyse bu ozellik(ler) iptal edilebilir.
	
	LEVELS LIST komutuysa o anki erisim seviyelerinin numerik
	degerlerini listeler.LEVELS RESET komutu butun numerik
	degerleri baslangictaki konumlarina getirir.

CHAN_HELP_LEVELS_DESC
	Gecerli ozelliklerin listesi asagidadir.Dikkat edilirse
	AUTOOP ve NOJOIN maximum degerlerken; diger hepsi minimum
	degerlerdir.

CHAN_HELP_LEVELS_DESC_FORMAT
	    %-*s  %s

CHAN_HELP_INFO
	Kullanimi: INFO kanal
	
	Belirtilen kanalin bilgilerini goruntuler.Kanal bilgileri
	icinde bazi kisimlar saklanmis veya yazilmamis olabilir.

CHAN_HELP_LIST
	Kullanimi: LIST degisken
	
	Belirtilen degiskene uyan butun kayitli kanallari listeler.
	(PRIVATE secenegi aktif olan kanallar listelenmez).
CHAN_HELP_OP
	Kullanimi: OP kanal nick
	
	Belirtilen nick'e sozkonusu kanalda op verir.Varsayilan
	deger olarak sadece kanaldaki erisim seviyesi 5 ve uzeri
	kisiler bu komutu kullanabilir.

CHAN_HELP_DEOP
	Kullanimi: DEOP kanal nick
	
	Belirtilen nick'in sozkonusu kanaldaki op'unu alir.
	Varsayilan deger olarak sadece kanaldaki erisim seviyesi 5
	ve uzeri olan kisiler bu komutu kullanabilir.

CHAN_HELP_INVITE
	Kullanimi: INVITE kanal
	
	%S 'un sizi belirtilen kanala cagirmasini (INVITE)
	saglar.Varsayilan deger olarak sadece kanaldaki erisim
	seviyesi 0'dan buyuk olan kisiler bu komutu kullanabilir.

CHAN_HELP_UNBAN
	Kullanimi: UNBAN kanal
	
	%S 'un sizin kanala girisinizi engelleyen tum ban'lari
	kaldirmasini saglar.Varsayilan deger olarak sadece kanaldaki
	erisim seviyesi 0'dan buyuk olan kisiler bu komutu
	kullanabilir.

CHAN_HELP_CLEAR
	Kullanimi: CLEAR kanal parametre
	
	%S'un kanaldaki belirtilen parametre'yi sifirlamasini
	saglar.Gecerli parametre'ler sunlardir:
	
	     MODES    Kanaldaki butun mode'lari sifirlar.
	                  (i,k,l,m,n,p,s,t).
	     BANS     Kanaldaki butun ban'lari sifirlar.
	     OPS      Kanaldaki +o mode'unu (tum kanal oplarini)
	                  sifirlar.
	     VOICES   Kanaldaki +v mode'unu (tum +'lari) sifirlar.
	     USERS    Kanaldaki tum kullanicilari atar.
	
	Varsayilan deger olarak sadece kanaldaki erisim seviyesi 10
	veya uzeri olan kisiler bu komutu kullanabilir.

CHAN_SERVADMIN_HELP
	
	Asagidaki komutlari sadece Services admin'ler kullanabilir.:
	
	    GETPASS   Belirtilen kanalin sifresini verir.
	                 (eger sifreleme (encryption) devre disiyken)
	    FORBID    Belirtilen kanalin kullanimini yasaklar.
	    STATUS    Bir kullanicinin kanaldaki erisim seviyesini
	                 verir.
	
	Services admin'ler ayrica IDENTIFY komutunu kullanmaksizin
	bir kanalin kaydini silebilir (DROP), sifresini
	degistirebilir ve/veya erisim listesine
	(/msg %S ACCESS kanal {ADD | DEL | LIST}) komutu ile
	mudahale edebilirler.

CHAN_SERVADMIN_HELP_DROP
	Kullanimi: DROP kanal
	
	Belirtilen kanalin kaydini siler.Sadece Services admin'ler
	sifreyi girmelerine gerek olmadan istedikleri kanalin
	kaydini silebilirler.

CHAN_SERVADMIN_HELP_SET
	
	Services admin'ler NOEXPIRE komutu ile herhangi bir kanalin
	zaman asimi yuzunden silinmesi ozelligini kapatabilirler.
	Buna ek olarak Services admin'ler herhangi bir kanalin her
	ozelligini de kanal sifresini girmelerine gerek olmaksizin
	degistirebilirler.

CHAN_SERVADMIN_HELP_SET_NOEXPIRE
	Kullanimi: SET kanal NOEXPIRE {ON | OFF}
	
	Belirtilen kanalin zaman asimi nedeniyle silinecegi veya
	silinmeyecegini belirler.Bu ozelligin ON seklinde
	ayarlanmasi kanalin zaman asimi ile silinmesini
	engelleyecektir.
	
	Bu komutu sadece Services admin'ler kullanabilir.

CHAN_SERVADMIN_HELP_LIST
	Kullanimi: LIST degisken
	
	Belirtilen degiskene uyan tum kanallari,PRIVATE ozelligi
	aktif olanlari da icermek uzere listeler.

CHAN_SERVADMIN_HELP_GETPASS
	Kullanimi: GETPASS kanal
	
	Belirtilen kanalin sifresini verir.Bu komut kullanildiginda
	butun IRCop'larin gorebilecegi sekilde ve komutu kullananin
	nick'ini de iceren bir notice atilir.
	
	Bu komutu sadece Services admin'ler kullanabilir.

CHAN_SERVADMIN_HELP_FORBID
	Kullanimi: FORBID kanal
	
	Belirtilen kanalin kullanimini yasaklar.Yasagin kalkmasi icin
	sozkonucu nick'in %S veritabanindan silinmesi gerekir
	(DROP)
	
	Bu komutu sadece Services admin'ler kullanabilir.

CHAN_SERVADMIN_HELP_STATUS
	Kullanimi: STATUS kanal nick
	
	Belirtilen nick'in kanal'daki erisim seviyesini goruntuler.
	Cevabin formu su sekildedir:
	
	    STATUS kanal nick erisim-seviyesi
	
	Bu komutu sadece Services admin'ler kullanabilir.

###########################################################################
#
# MemoServ help messages
#
###########################################################################

#MEMO_HELP
#	%S o anda IRC'de olan veya olmayan kullanicilara not
#	birakmanizi saglar.Notu hem gonderen,hem de alacak kisinin
#	nickleri kayitli olmalidir.
#	
#	%S komutlari:
#	
#	    SEND   Belirtilen nick'e not birakir.
#	    LIST   Notlarinizi listeler.
#	    READ   Bir notu okumanizi saglar.
#	    DEL    Bir notu (veya hepsini) siler.
#	    SET    Notlarinizla ilgili secenekleri duzenler.
#	
#	/msg %S HELP komut yazarak herhangi bir komut hakkinda
#	daha ayrintili bilgi alabilirsiniz.
#	
#	(*) Standart olarak,kanala erisim seviyesi en az 10 olan her
#	kullanici kanala birakilan notlari okuyabilir.Bu seviye
#	%s LEVELS komutu ile degistirilebilir.

MEMO_HELP_SEND
	Kullanimi: SEND {nick | kanal} not-metni
	
	Belirtilen nick veya kanal'a not-metni'ni gonderir.
	Not gonderildiginde karsi taraf notice seklinde bir uyari
	alacaktir.Karsi taraftaki kanal veya nick kayitli olmalidir.

#MEMO_HELP_LIST
#	Kullanimi: LIST kanal [NEW]
#	
#	O anki notlarinizi listeler.NEW parametresi kullanildiginda
#	sadece yeni (yani okunmamis) notlarinizin bir listesini
#	alirsiniz.Okunmamis notlarin basinda "*" isareti olacaktir.

#MEMO_HELP_READ
#	Kullanimi: READ [kanal] {num | LAST}
#	
#	num numarali notu, veya LAST parametresi ile en son notunuzu
#	goruntuler.

#MEMO_HELP_DEL
#	Kullanimi: DEL [kanal] {num[-num][,num...] | ALL}
#	
#	Eger num kisminda bir sayi verilmisse o notu siler.
#	Birden fazla numara veya bir aralik belirtebilirsiniz.
#	
#	ALL yazarak size ait tum notlari silebilirsiniz.
#	
#	Ornekler:
#	
#	   DEL 1
#	      Ilk notunuzu siler.
#	
#	   DEL 2-5,7-9
#	      2 ile 5 ve 7 ile 9 arasindaki notlari siler.

MEMO_HELP_SET
	Kullanimi: SET secenek parametre
	
	Cesitli not seceneklerini duzenler.Secenek olarak:
	
	    NOTIFY      Yeni notlarda ne zaman uyarilacaginizi
	                    belirler.(sadece nick'ler icin)
	    LIMIT       Alabileceginiz en fazla not sayisini
	                    belirler.
	
	/msg %S HELP SET secenek yazarak belirli bir komut
	hakkinda ayrintili bilgi alabilirsiniz.	

MEMO_HELP_SET_NOTIFY
	Kullanimi: SET NOTIFY {ON | LOGON | NEW | OFF}
	
	Yeni notlar geldiginde ne zaman uyari alacaginizi belirler.
	
	    ON      IRC'ye girer girmez /AWAY 'den doner donmez ve
	                notlar size gonderildikleri anda
	                uyarilirsiniz.
	    LOGON   IRC'ye girer girmez ve /AWAY 'den doner donmez
	                uyarilirsiniz.
	    NEW     Sadece notlar size gonderildikleri anda
	                uyarilirsiniz.
	    OFF     Bu secenekle herhangi bir uyari almazsiniz.
	
	ON secenegi aslinda LOGON ve NEW seklindedir.

MEMO_HELP_SET_LIMIT
	Kullanimi: SET LIMIT [kanal] limit
	
	Sizin veya belirtilen kanalin alabilecegi en fazla not
	sayisini belirler.Eger bu limiti 0 olarak ayarlarsaniz
	size not birakilamaz.Bu limit en fazla %d olabilir.

MEMO_HELP_INFO
	Kullanimi: INFO [kanal]
	
	Notlarinizi ve ilgili secenekleri listeler.Notlariniz
	okunmus ve okunmamislar olarak ayrilirken,alabileceginiz
	en fazla not sayisini da bu listede gorebilirsiniz.Ek bir
	parametre ile belirtilen bir kanal hakkinda da benzer bir
	liste alinabilir.

MEMO_SERVADMIN_HELP_SET_LIMIT
	Kullanimi: SET LIMIT [kullanici | kanal] {limit | NONE} [HARD]
	
	Bir kullanici veya kanalin alabilecegi en fazla not sayisini
	belirler.Bu limiti 0 yapmak kullanicinin not alamamasini ve
	NONE yapmak ta kullanicinin not limitinin kalkmasini saglar.
	Eger bir nick veya kanal belirtmezseniz kendi limitinizi
	belirlersiniz.
	
	HARD parametresini eklemek kullanicinin limitini
	degistirmesini engeller.
	
	SET LIMIT komutunu baska bir nick belirterek sadece
	Services admin'ler kullanabilir.Diger kullanicilar sadece
	kendi veya erisimleri olan kanallarin limitlerini
	belirleyebilirler,kendi limitlerini kaldiramazlar ve/veya
	kendilerine %d 'den yuksek bir limit veremezler.

MEMO_SERVADMIN_HELP_INFO
	Kullanimi: INFO [nick | kanal]
	
	Bu komut tek basina kullanildiginda not sayinizi,okunmus ve
	okunmamis olarak ayirarak,not limitinizle beraber listeler.
	
	Eger bir kanal belirtilmissea ayni bilgiyi o kanal icin
	listeler.
	
	Eger bir nick belirtilmisse ayni bilgiyi o kanal icin
	listeler.Bu haliyle sadece Services admin'ler kullanabilir.

###########################################################################
#
# OperServ help messages #mikado#
#
###########################################################################

#OPER_HELP
#	%S komutlar:
#	    GLOBAL      Butun kullanicilara notice atar.
#	    STATS       Services'in ve network'un durumu.
#	    OPER LIST   Services operator'leri listeler.
#	    ADMIN LIST  Services admin'leri listeler.
#	
#	Services operator ve admin'lere ozel komutlar:
#	    MODE        Bir kanalin mode'unu degistirir.
#	    KICK        Kanaldaki bir kullaniciyi atar.
#	    AKILL       AKILL listesini duzenler.
#	
#	Services admin'lere ozel komutlar:
#	    OPER        Services operator listesini duzenler
#	    JUPE        Bir server'i "Jupiter" eder
#	    RAW         IRC sunucusuna bir RAW komutu yollar
#	    SET         Cesitli Services seceneklerini duzenler
#	    UPDATE      Services veritabanini gunceller.
#	    QUIT        Services'i kapatir.
#	    RESTART     Veritabanini kaydederek Services'i
#	                  yeniden baslatir.
#	
#	Services root'a ozel komutlar:
#	    ADMIN       Services admin listesini duzenler
#	
#	Onemli Uyari: %S 'a giden butun komutlar kaydedilir!

OPER_HELP_GLOBAL
	Kullanimi: GLOBAL metin
	
	IRCop'larin network'teki tum kullanicilara mesaj
	gondermelerini saglar.
	
	Mesaj %s nick'inden gelen bir notice seklinde
	gorunecektir.

OPER_HELP_STATS
	Kullanimi: STATS [AKILL | ALL]
	
	Bu komut tek basina kullanildiginda mevcut kullanici ve
	IRCop sayisini (Services haric) , maximum kullaniciyi,
	sayisini, Services'in calismaya basladigi tarihi ve ne
	kadar zamandir calistigini goruntuler.
	
	AKILL secenegi ile beraber kullanildiginda ise o anki AKILL
	listesinin durumunu ve varsayilan zaman asimini goruntuler.
	
	ALL secenegini sadece Services admin'ler kullanabilir.Bu
	komut Services'in kullandigi RAM'i goruntuler.Buyuk
	network'larda kullanilmasi Services'i kisa sureyle
	dondurabileceginden gereksiz yere kullanmayiniz.
	
	STATS yerine UPTIME'i da kullanabilirsiniz.

OPER_HELP_OPER
	Kullanimi: OPER ADD nick
	           OPER DEL nick
	           OPER LIST
	
	Services admin'lerin Services operator listesini
	duzenlemelerini saglar.Bu listedeki her kullanici %s'e
	sifresini girdikten sonra Services operator komutlarini
	kullanabilecektir.
	
	Komutun OPER LIST seklini her IRCop kullanabilir.Butun diger
	kullanimlar Services admin'lere ozeldir.

OPER_HELP_ADMIN
	Kullanimi: ADMIN ADD nick
	           ADMIN DEL nick
	           ADMIN LIST
	
	Services root'un Services admin listesini duzenlemesini
	saglar.Bu listedeki her kullanici %s'e sifresini
	girdikten sonra Services admin komutlarini
	kullanabilecektir.
	
	Komutun ADMIN LIST seklini her IRCop kullanabilir.Butun
	diger kullanimlar Services root'a ozeldir.

OPER_HELP_MODE
	Kullanimi: MODE kanal mode(lar)
	
	Services operator'larin herhangi bir kanalin mode'larini
	duzenlemelerini saglar.Kullanilicak parametreler /MODE
	komutununkilerle aynidir.
	
	Bu komutu sadece Services operator'lar kullanabilir.

OPER_HELP_CLEARMODES
	Kullanimi: CLEARMODES kanal [ALL]
	
	Kanaldaki butun "binary mode"'lari (i,k,l,m,n,p,s,t) ve
	banlari sifirlar.ALL parametresi ile kullanildiginda op ve
	voice'ler de (+o ve +v) sifirlanir.
	
	Bu komutu sadece Services operator'lar kullanabilir.

OPER_HELP_KICK
	Kullanimi: KICK kanal kullanici [sebep]
	
	IRCop'larin herhangi bir kanaldaki kullaniciyi kanaldan
	atmalarini saglar.Kullanilicak parametreler /KICK
	komutununkilerle aynidir.Kick mesajinin yaninda komutu
	kullanan IRCop'un nick'i de gorunecektir.Ornegin :
	
	*** SpamMan has been kicked off channel #kanal by %S
	(mikado (Flood))
	
	Bu komutu sadece Services operator'lar kullanabilir.

OPER_HELP_AKILL
	Kullanimi: AKILL ADD [+sure] mask sebep
	           AKILL DEL mask
	           AKILL LIST [mask]
	           AKILL VIEW [mask]
	
	Services operators'larin AKILL listesini duzenlemelerini
	saglar.AKILL listesindeki bir kullanici baglanmaya
	calistiginda Services o kullaniciyi KILL edecek ve
	destekleyen sunucu turlerinde network'teki tum sunuculardan
	da kullaniciyi banlayacaktir (K-Line).
	
	AKILL ADD komutu belirtilen user@host formatindaki nick'i
	AKILL listesine belirtilmek zorunda olan sebep ile ekler.
	
	AKILL DEL komutu belirtilen veriyi AKILL listesinden siler.
	
	AKILL LIST tek basina AKILL listesinin tamamini listeler.
	Eger bir secenek verilmisse sadece ona uyan veriler
	listelenir.
	
	AKILL VIEW komutu ise akill'i ekleyen kisinin nick'i,
	otomatik olarak silinecegi suregibi ayrintilari da
	goruntulemesi acisindan AKILL LIST'e gore daha
	kullanislidir.
	
	AKILL ADD komutu ile beraber bir zaman asimi suresi de
	belirtilebilir.Bu sure d (gun), h (saat) veya m (dakika)
	seklinde olabilir.(1h30m) gibi kombinasyonlar gecersizdir.
	Varsayilan secenek gundur.Yani +30 30 gun anlamina gelir.Bir
	AKILL'in otomatik olarak silinmemesi icin sure kisminda +0
	yazilmasi gerekir.
	
	sebep sadece diger IRCop'larin gormesi icindir.Kullanicilar
	KILL'lenirken bu mesaj kullanilmaz.
	
	Bu komutu sadece Services operator'lar kullanabilir.

OPER_HELP_JUPE
	Kullanimi: JUPE sunucu
	
	Services bu komutu kullanildiginda,belirtilen sunucu ile
	ayni isimdeki sahte bir sunucuyu network'e dahil ederek
	aslinin baglanmasini engeller.Komut standart olarak
	SQUIT komutu ile geri alinabilir.
	
	Bu komutu sadece Services admin'ler kullanabilir.

OPER_HELP_RAW
	Kullanimi: RAW [metin]
	
	Direk olarak Services'in bagli oldugu sunucuya bir metin
	gonderir. Bu komutun oldukca kisitli bir kullanim alani
	vardir ve ne yapildigindan emin olmadikca kesinlikle
	BU KOMUTU KULLANMAYIN
	
	Bu komutu sadece Services admin'ler kullanabilir.
	
OPER_HELP_SET
	Kullanimi: SET secenek ayar
	
	Cesitli Services seceneklerini ayarlar.Mevcut secenekler:
	
	    READONLY   read-only ve read-write arasinda gecis
	    DEBUG      debug mode'u acar/kapar.
	
	Bu komutu Services admin'ler kullanabilir.

OPER_HELP_SET_READONLY
	Kullanimi: SET READONLY {ON | OFF}
	
	read-only secenegini acar/kapar. Bu secenek aktifken normal
	kullanicilar Services veritabani uzerinde herhangi bir
	degisiklik yaratacak komutlari (nick ve kanal erisim
	listeleri gibi).Gerekli yetkilere sahip IRCop'lar AKILL
	listesini duzenleyebildikleri gibi nick ve kanallari
	yasaklayabilir (FORBID) ve/veya kayitlarini silebilirler
	(DROP).Ancak bu degisikliklerin hicbiri Services
	kapatilmadan veya yeniden baslatilmadan once read-only
	ozelliginin kapatilmamasi halinde kaydedilmeyecektir.
	
	Bu ozellik komut satirindaki -readonly ile aynidir.

OPER_HELP_SET_DEBUG
	Kullanimi: SET DEBUG {ON | OFF | num}
	
	Debug ozelligini acar/kapar.Bu ozellik aktifken Services'a
	gelen ve Services'den gonderilen her veri kaydedilir.Eger
	num belirtilmisse debug ozelligi bu seviyede baslatilir.
	
	Bu ozellik komut satirindaki -debug ile aynidir.

OPER_HELP_UPDATE
	Kullanimi: UPDATE
	
	Services veritabanini belirtilen sureden once,yani siz
	komutu yazar yazmaz guncellenmesini saglar.
	
	Bu komutu sadece Services admin'ler kullanabilir.

OPER_HELP_QUIT
	Kullanimi: QUIT
	
	Services' kapatan bu komut kullanildiginda veritabani
	GUNCELLENMEZ. Bu yuzden veritabaninda veya Services'in
	calistigi makinede bir sorun ciktigi durumlar disinda
	kullanilmamalidir.
	
	Bu komutu sadece Services admin'ler kullanabilir.

OPER_HELP_SHUTDOWN
	Kullanimi: SHUTDOWN
	
	QUIT'in aksine bu komut kullanildiginda Services butun
	veritabanini guncelledikten sonra kapanir.
	
	Bu komutu sadece Services admin'ler kullanabilir.

OPER_HELP_RESTART
	Kullanimi: RESTART
	
	Services'i, butun veritabanini guncelledikten sonra yeniden
	baslatir.
	
	Bu komutu sadece Services admin'ler kullanabilir.

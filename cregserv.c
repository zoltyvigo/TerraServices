/* Servicios Extra para Terra Networks S.A.
 *
 * Developers:
 *
 * Toni García       zoltan    zolty@terra.es
 * Daniel Fernández  FreeMind  animedes@terra.es
 * Marcos Rey        TeX       marcos.rey@terra.es
 *
 * Este programa es de licencia privada.
 */
 
/*************************************************************************/
 
#include "services.h"
#include "pseudo.h"
 
/*************************************************************************/
#ifdef CREG
static CregInfo *creglists[1024];
 
static void do_help(User *u);
static void do_register(User *u);
static void do_cancel(User *u);
static void do_apoya(User *u);
static void do_apolla(User *u);
static void do_info(User *u);
static void do_apoyos(User *u);

/* Pa luego 
static void do_list(User *u);
static void do_suspend(User *u);
static void do_unsuspend(User *u);
static void do_marca(User *u);
static void do_ignore(User *u);
static void do_anula(User *u);
static void do_acepta(User *u);
static void do_restaura(User *u);
static void do_regcanal(User *u);
static void do_rechaza(User *u);
static void do_deniega(User *u);
static void do_drop(User *u);
static void do_prohibe(User *u);
static void do_permite(User *u);
static void do_activa(User *u);
static void do_desactiva(User *u);
*/

static Command cmds[] = {
    { "HELP",       do_help,     NULL,  -1,                      -1,-1,-1,-1 },
    { "AYUDA",      do_help,     NULL,  -1,                      -1,-1,-1,-1 },
    { ":?",         do_help,     NULL,  -1,                      -1,-1,-1,-1 },
    { "?",          do_help,     NULL,  -1,                      -1,-1,-1,-1 },
    { "REGISTRA",   do_register, NULL,  CREG_HELP_REGISTRA,      -1,-1,-1,-1 },
    { "CANCELA",    do_cancel,  NULL,   CREG_HELP_CANCELA,       -1,-1,-1,-1 },
    { "APOYA",      do_apoya,    NULL,  CREG_HELP_APOYA,         -1,-1,-1,-1 },
    { "APOLLA",     do_apolla,   NULL,  -1,                      -1,-1,-1,-1 },
    { "APOYOS",     do_apoyos,   NULL,  CREG_HELP_APOYOS,        -1,-1,-1,-1 },
    { "INFO",       do_info,     NULL,  CREG_HELP_INFO,          -1,-1,-1,-1 },
/*
    { "LISTA",      do_lista,    is_services_oper, -1            -1,-1,-1,-1 },
    { "INFO",       do_info,     is_services_oper, -1            -1,-1,-1,-1 },
    { "SUSPEND",    do_suspend,  is_services_oper, -1            -1,-1,-1,-1 },
    { "UNSUSPEND",  do_unsuspend, is_services_oper, -1           -1,-1,-1,-1 },
    { "MARCA",      do_marca,    is_services_oper, -1            -1,-1,-1,-1 },
    { "IGNORE",     do_ignore,   is_services_oper, -1            -1,-1,-1,-1 },
    { "ANULA",      do_anula,    is_services_oper, -1            -1,-1,-1,-1 },
    { "ACEPTA",     do_acepta,   is_services_admin, -1           -1,-1,-1,-1 },
    { "RESTAURA",   do_restaura, is_services_admin, -1           -1,-1,-1,-1 },
    { "REGCANAL",   do_regcanal, is_services_admin, -1           -1,-1,-1,-1 },
    { "RECHAZA",    do_rechaza,  is_services_admin, -1           -1,-1,-1,-1 },
    { "DENIEGA",    do_deniega,  is_services_admin, -1           -1,-1,-1,-1 },
    { "DROP",       do_drop,     is_services_admin, -1           -1,-1,-1,-1 },
    { "PROHIBE",    do_prohibe,  is_services_admin, -1           -1,-1,-1,-1 },
    { "PERMITE",    do_permite,  is_services_admin, -1           -1,-1,-1,-1 },
    { "ACTIVA",     do_activa,   is_services_admin, -1           -1,-1,-1,-1 },
    { "DESACTIVA",  do_desactiva, is_services_admin, -1          -1,-1,-1,-1 },
*/
};

/*************************************************************************/
/*************************************************************************/

/* creglists */

/*************************************************************************/

/* Return information on memory use.  Assumes pointers are valid. */

void get_cregserv_stats(long *nrec, long *memuse)
{              
    long count = 0, mem = 0;
    int i;
    CregInfo *cr;

    for (i = 0; i < 256; i++) {
        for (cr = creglists[i]; cr; cr = cr->next) {
            count++;
            mem += sizeof(*cr);
            if (cr->desc)
                mem += strlen(cr->desc)+1;            
            if (cr->email)
                mem += strlen(cr->email)+1;                
            if (cr->motivo)
                mem += strlen(cr->motivo)+1;
            mem += cr->apoyoscount * sizeof(ApoyosCreg);
            mem += cr->historycount * sizeof(HistoryCreg);
        }
    }
    *nrec = count;
    *memuse = mem;
}
                                                                                                                                                                   
/*************************************************************************/
/*************************************************************************/

/* Creg initialization. */

void creg_init(void)
{

}

/*************************************************************************/

/* Main CregServ routine. */

void cregserv(const char *source, char *buf)
{

    char *cmd, *s;
    User *u = finduser(source);
        
    if (!u) {
        log("%s: user record for %s not found", s_CregServ, source);
        return;
    }
            
    cmd = strtok(buf, " ");
    if (!cmd) {
        return;
    } else if (stricmp(cmd, "\1PING") == 0) {
        if (!(s = strtok(NULL, "")))
        s = "\1";                        
        privmsg(s_CregServP10, source, "\1PING %s", s);
    } else if (skeleton) {
        notice_lang(s_CregServ, u, SERVICE_OFFLINE, s_CregServ);
    } else {        
        run_cmd(s_CyberServ, u, cmds, cmd);
    }
            
}    

/*************************************************************************/

/* Load/save data files. */

#define SAFE(x) do {                                    \
    if ((x) < 0) {                                      \
        if (!forceload)                                 \
            fatal("Error de Lectura en %s", CregDBName);      \
        failed = 1;                                     \
        break;                                          \
    }                                                   \
} while(0)

void load_creg_dbase(void)
{
    dbFILE *f;
    int ver, i, j, c;
    CregInfo *cr, **last, *prev;
    int failed = 0;    
    
    if (!(f = open_db(s_CregServ, CregDBName, "r", CREG_VERSION)))
        return;
            
    switch (ver = get_file_version(f)) {    
      case 1:

        for (i = 0; i < 256 && !failed; i++) {
            int32 tmp32;
                    
            last = &creglists[i];
            prev = NULL;                    
            while ((c = getc_db(f)) != 0) {
                if (c != 1)
                    fatal("Invalid format in %s", CregDBName);
                cr = smalloc(sizeof(CregInfo));
                *last = cr;
                last = &cr->next;
                cr->prev = prev;
                prev = cr;
                SAFE(read_buffer(cr->name, f));
                SAFE(read_buffer(cr->founder, f));
                SAFE(read_buffer(cr->founderpass, f));
                SAFE(read_string(&cr->desc, f));
                SAFE(read_string(&cr->email, f));
                SAFE(read_int32(&tmp32, f));
                cr->time_peticion = tmp32;
                SAFE(read_buffer(cr->nickoper, f));
                SAFE(read_string(&cr->motivo, f));
                SAFE(read_int32(&tmp32, f));
                cr->time_motivo = tmp32;
                SAFE(read_int32(&cr->estado, f));
                SAFE(read_int16(&cr->apoyoscount, f));
                if (cr->apoyoscount) {
                    cr->apoyos = scalloc(cr->apoyoscount, sizeof(ApoyosCreg));
                    for (j = 0; j < cr->apoyoscount; j++) {
                        SAFE(read_string(&cr->apoyos[j].nickapoyo, f));
                        SAFE(read_string(&cr->apoyos[j].emailapoyo, f));
                        SAFE(read_int32(&tmp32, f));
                        cr->apoyos[j].time_apoyo = tmp32;
                    }                                                                                                                                                        
                } else {
                    cr->apoyos = NULL;
                }                                                
                SAFE(read_int16(&cr->historycount, f));
                if (cr->historycount) {
                    cr->history = scalloc(cr->historycount, sizeof(HistoryCreg));
                    for (j = 0; j < cr->historycount; j++) {
                        SAFE(read_string(&cr->history[j].nickoper, f));
                        SAFE(read_string(&cr->history[j].marca, f));
                        SAFE(read_int32(&tmp32, f));
                        cr->history[j].time_marca = tmp32;
                    }
                } else {
                    cr->history = NULL;
                }
            }  /* while (getc_db(f) != 0) */
            *last = NULL;
                                                                                                                                                                                                                                                                                   
        }  /* for (i) */
        break;
     default:                                                                                                                                                    

        fatal("Unsupported version number (%d) on %s", ver, CregDBName);
        
    }  /* switch (version) */
            
    close_db(f);     
}

#undef SAFE

/*************************************************************************/

#define SAFE(x) do {                                            \
    if ((x) < 0) {                                              \
        restore_db(f);                                          \
        log_perror("Write error on %s", CregDBName);            \
        if (time(NULL) - lastwarn > WarningTimeout) {           \
            canalopers(NULL, "Write error on %s: %s", CregDBName,  \
                        strerror(errno));                       \
            lastwarn = time(NULL);                              \
        }                                                       \
        return;                                                 \
    }                                                           \
} while (0)                                                                       
                                                
void save_creg_dbase(void)
{
    dbFILE *f;
    int i, j;
    CregInfo *cr;
    static time_t lastwarn = 0;                                                                                                                                            
    
    if (!(f = open_db(s_CregServ, CregDBName, "w")))
        return;
            
    for (i = 0; i < 256; i++) {
        for (cr = creglists[i]; cr; cr = cr->next) {
            SAFE(write_int8(1, f));
            SAFE(write_buffer(cr->name, f));
            SAFE(write_buffer(cr->founder, f));
            SAFE(write_buffer(cr->founderpass, f));
            SAFE(write_string(cr->desc, f));
            SAFE(write_string(cr->email, f));
            SAFE(write_int32(cr->time_peticion, f));
            SAFE(write_buffer(cr->nickoper, f));
            SAFE(write_string(cr->motivo, f));
            SAFE(write_int32(cr->time_motivo, f));
            SAFE(write_int32(cr->estado, f));
            SAFE(write_int16(cr->apoyoscount, f));
            for (j = 0; j < cr->apoyoscount; j++) {
                SAFE(write_string(cr->apoyos[j].nickapoyo, f));
                SAFE(write_string(cr->apoyos[j].emailapoyo, f));
                SAFE(write_int32(cr->apoyos[j].time_apoyo, f));
            }                                                                                                                                                  
            SAFE(write_int16(cr->historycount, f));
            for (j = 0; j < cr->historycount; j++) {
                SAFE(write_string(cr->history[j].nickoper, f));
                SAFE(write_string(cr->history[j].marca, f));
                SAFE(write_int32(cr->history[j].time_marca, f));
            }                                      
        } /* for (creglists[i]) */
        
        SAFE(write_int8(0, f));
    } /* for (i) */
    
    close_db(f);
}

/*************************************************************************/

/* Devuelve la estructura CregInfo del canal dado, o NULL si el canal no
 * existe en las DB */
 
CregInfo *cr_findcreg(const char *chan)
{
     CregInfo *cr;
     for (cr = creglists[tolower(chan[1])]; cr; cr = cr->next) {
         if (stricmp(cr->name, chan) == 0)
             return cr;
     }       
     return NULL;
} 

/*************************************************************************/
/*********************** CregServ private routines ***********************/
/*************************************************************************/

/* Insert a channel alphabetically into the database. */

static void alpha_insert_creg(CregInfo *cr)
{
    CregInfo *ptr, *prev;
    char *chan = cr->name;        
    
    for (prev = NULL, ptr = creglists[tolower(chan[1])];
                        ptr != NULL && stricmp(ptr->name, chan) < 0;
                        prev = ptr, ptr = ptr->next)
        ;    
    cr->prev = prev;
    cr->next = ptr;
    if (!prev)
        creglists[tolower(chan[1])] = cr;
    else        
        prev->next = cr;
    if (ptr)
        ptr->prev = cr;
}
                        
/*************************************************************************/

/* Añade un canal a las bases de datos... */

static CregInfo *makecreg(const char *chan)
{
    CregInfo *cr;
    
    cr = scalloc(sizeof(CregInfo), 1);
    strscpy(cr->name, chan, CHANMAX);
    alpha_insert_creg(cr);
    return cr;
}    

/*************************************************************************/

/* Borra un canal, devuelve 1 si fue borrado, 0 si no se ha podido */

static int delcreg(CregInfo *cr)
{

}
    
                                    
/*************************************************************************/
/* Return a help message. */

static void do_help(User *u)
{
    char *cmd = strtok(NULL, "");
    
    if (!cmd) {
        privmsg_help(s_CregServ, u, CREG_HELP);
  /*      if (is_services_oper(u))
          notice_help(s_CregServ, u, CREG_SERVADMIN_HELP); */
    } else {
        help_cmd(s_CregServ, u, cmds, cmd);
    }
}                                                    

/*************************************************************************/

static void do_register(User *u)
{

    char *chan = strtok(NULL, " ");
    char *email = strtok(NULL, " ");
    char *pass = strtok(NULL, " ");
    char *desc = strtok(NULL, "");
    
    CregInfo *cr;
  
  /* Para en el futuro */  
//    char passtemp[16];    
            
    if (readonly) {
        privmsg_lang(s_CregServ, u, CREG_REGISTER_DISABLED);
        return;
    }            
    if (!desc) {    
        syntax_error(s_CregServ, u, "REGISTRA", CREG_REGISTER_SYNTAX); 
    } else if (is_identified(u)) {
        privmsg_lang(s_CregServ, u, CREG_NICK_IDENTIFY_REQUIRED);
    } else if (!(*chan == '#')) {            
        privmsg_lang(s_CregServ, u, CREG_REGISTER_NOT_VALID);   
    } else if (cr_findcreg(chan)) {    
        privmsg_lang(s_CregServ, u, CREG_REGISTER_FAILED, chan, s_CregServ, chan);
    } else if (!(cr = makecreg(chan))) {
        log("%s: makecreg() failed for REGISTER %s", s_CregServ, chan);
        privmsg_lang(s_CregServ, u, CREG_REGISTRATION_FAILED);
    } else {
        cr = makecreg(chan);
        
        strscpy(cr->founder, u->nick, PASSMAX);
        if (strlen(pass) > PASSMAX-1) /* -1 for null byte */
            privmsg_lang(s_CregServ, u, PASSWORD_TRUNCATED, PASSMAX-1);
        strscpy(cr->founderpass, pass, PASSMAX);

        cr->email = sstrdup(email);
/* en el futuro */
//        cr->email = ni->email;                 
        cr->desc = sstrdup(desc);                                                                
        cr->time_peticion = time(NULL);
        cr->estado = CR_PROCESO_REG;
/* En el futuro        
        srand(time(NULL));
        sprintf(passtemp, "%05u",1+(int)(rand()%99999) );
        strscpy(cr->passapoyo, passtemp, PASSMAX);
*/

        cr->time_lastapoyo = time(NULL);
        
        privmsg_lang(s_CregServ, u, CREG_REGISTER_SUCCEEDED);
        canalopers(s_CregServP10, "%s ha solicitado el registro del canal %s",
                                               u->nick, chan);
    }
}        
                        
        
/*************************************************************************/

static void do_cancela(User *u)
{
    char *chan = strtok(NULL, " ");
    char *pass = strtok(NULL, " ");                        
    CregInfo *cr;

    if (readonly) {
        privmsg_lang(s_CregServ, u, CREG_REGISTER_DISABLED);
        return;
    }
    if (!pass) {
        syntax_error(s_CregServ, u, "CANCELA", CREG_CANCEL_SYNTAX);
    } else if (is_identified(u)) {
        privmsg_lang(s_CregServ, u, CREG_NICK_IDENTIFY_REQUIRED);
    } else if (!(cr = cr_findcreg)) 
        privmsg_lang(s_CregServ, u, CREG_NOT_REGISTRED, chan);    
    } else if (!(cr->estado & CR_PROCESO_REG))
        privmsg_lang(s_CregServ, u, CREG_NOT_PROCESO_REG, chan, s_CregServ, chan);
    } else if (stricmp(pass, cr->passfounder) != 0) {
        privmsg_lang(s_CregServ, u, CREG_CANCEL_FAILED, chan);    
    } else {
//       delcreg(cr);    

       privmsg_lang(s_CregServ, u, CREG_CANCEL_SUCCEEDED, chan);
       canalopers(s_CregServP10, "%s cancela la solicitud de registro del canal %s",
                              u->nick, chan);    
    }
}    

/*************************************************************************/

static void do_apoya(User *u)
{
    char *chan = strtok(NULL, " ");
    char *email = strtok (NULL, " ");
/* Para el futuro */
//    char *pass = strtok(NULL, " ");
        
    CregInfo *cr;
    ApoyosCreg *apoyos;
    int i;
            
/* Para el futuro */            
//    char passtemp[16];        

    if (readonly) {
        privmsg_lang(s_CregServ, u, CREG_REGISTER_DISABLED);
        return;
    }
    if (!pass) {
        syntax_error(s_CregServ, u, "APOYA", CREG_APOYA_SYNTAX);
    } else if (is_identified(u)) {
        privmsg_lang(s_CregServ, u, CREG_NICK_IDENTIFY_REQUIRED);
    } else if (!(cr = cr_findcreg))
        privmsg_lang(s_CregServ, u, CREG_NOT_REGISTRED, chan);
    } else if (!(cr->estado & CR_PROCESO_REG))
        privmsg_lang(s_CregServ, u, CREG_NOT_PROCESO_REG, chan, s_CregServ, chan);
    } else {
/*  Implementar control de tiempo! */
/* Para en el futuro
        if (!cr->passapoyo) {
            srand(time(NULL));
            sprintf(passtemp, "%05u",1+(int)(rand()%99999) );
            strscpy(cr->passapoyo, passtemp, PASSMAX);
        }              
*/
        if (stricmp(u->nick, cr->founder) == 0) {
            privmsg_lang(s_CregServ, u->nick, "Ya apoyaste como founder");
            return;
        }         
        
        for (apoyos = cr->apoyos, i = 0; i < cr->apoyoscount; apoyos++, i++) {
            if (stricmp(u->nick, apoyos->nickapoyo) == 0) {
                privmsg(s_CregServ, u->nick, "Ya has apoyado al canal");
                return;
            }
        }
 
         if (!pass) {
          privmsg(s_CregServ, u->nick, "No apoye el canal solamente porque le hayan dich
           privmsg(s_CregServ, u->nick, "escriba C12/msg %s APOYA %sC. Infórmese sobre la
            privmsg(s_CregServ, u->nick, "del canal, sus usuarios, etc.");
             privmsg(s_CregServ, u->nick, "Si decide finalmente apoyar al canal C12%sC hága
              privmsg(s_CregServ, u->nick, "C12/msg %s APOYA %s %sC", s_CregServ, chan, cr->
                         return;
                                 }

        if (stricmp(pass, cr->passapoyo) != 0) {
                    privmsg(s_CregServ, u->nick, "Clave inválida");
                                privmsg(s_CregServ, u->nick, "Para confirmar tu apoyo al canal C12%
                                            privmsg(s_CregServ, u->nick, "C12/msg %s APOYA %s %sC", s_CregServ,
                                                        return;
                                                                }
        cr->apoyoscount++;
        cr->apoyos = srealloc(cr->apoyos, sizeof(ApoyosCreg) * cr->apoyoscount);
            
        apoyos = &cr->apoyos[cr->apoyoscount-1];
        apoyos->nickapoyo = sstrdup(u->nick);
        apoyos->emailapoyo = sstrdup(ni->email);
        apoyos->time_apoyo = time(NULL);                                                                                                                                                                                

        cr->time_lastapoyo = time(NULL);
        privmsg(s_CregServ, u->nick, "Anotado tu apoyo al canal C12%sC", chan);
            
        if ((cr->apoyoscount) >= 2) {
            cr->estado &= ~CR_PROCESO_REG;
            cr->estado |= CR_PENDIENTE;
        } else {            
            srand(time(NULL));
            sprintf(passtemp, "%05u",1+(int)(rand()%99999) );
            strscpy(cr->passapoyo, passtemp, PASSMAX);
        }
    }
}      

/*************************************************************************/

static void do_apolla(User *u)
{

    privmsg_lang(s_CregServ, u, CREG_APOLLA);
    canalopers(s_CregServ, "%s ha APOLLAdo!!!!, xDDDDDDDDDDD", u->nick);
}
                
                
/*************************************************************************/

static void do_apoyos(User *u)
{
    char *param = strtok(NULL, " ");
    CregInfo *cr;                

    if (!param) {
        syntax_error(s_CregServ, u, "APOYOS", CREG_APOYOS_SYNTAX);
        return;
    }  
    
    if (param && *param == '#') {
        privmsg(s_CregServ, u->nick, "No hay información disponible del canal");
    } else if (param && strchr(param, '@')) {
        if (is_services_oper(u)) {
            privmsg(s_CregServ, u->nick, "Información de los apoyos del mail %s", param);
            privmsg(s_CregServ, u->nick, "No ha realizado apoyos hasta la fecha");
        } else
            privmsg_lang(s_CregServ, u, ACCESS_DENIED);
   } else {
        if ((nick_identified(u) && (stricmp(u->nick, param) == 0)) ||
                                             is_services_oper(u)) {
           privmsg(s_CregServ, u->nick, "Información de los apoyos de C12%sC:", param);
           privmsg(s_CregServ, u->nick, "No ha realizado apoyos hasta la fecha");
        }
        else                                                                                                               
           privmsg_lang(s_CregServ, u, ACCESS_DENIED);
           
   }
}        

/*************************************************************************/

static void do_info(User *u)
{

    char *chan = strtok(NULL, " ");
//    ChannelInfo *ci;
//    NickInfo *ni;
    CregInfo *cr;
    ApoyosCreg *apoyos;

    char buf[BUFSIZE];
    struct tm *tm;
    int i;    

#endif
            

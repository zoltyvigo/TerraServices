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

#ifdef CYBER

#define HASH(host)      (((host)[0]&31)<<5 | ((host)[1]&31))

static Clones *cloneslist[1024];
static int32 nclones = 0;
static Clones *findclones(const char *host);


static IlineInfo *ilinelists[256];

static void alpha_insert_iline(IlineInfo *il);
static IlineInfo *makeiline(const char *host);
static int deliline(IlineInfo *il);


static void do_help(User *u);
static void do_contrata(User *u);
static void do_info(User *u);
static void do_actualiza(User *u);
static void do_cyberkill(User *u);
static void do_cybergline(User *u);
static void do_cyberunban(User *u);
static void do_cyberglobal(User *u);
static void do_list(User *u);
static void do_clones(User *u);
static void do_iline(User *u);
static void do_set_cyber(User *u);
static void do_set_host(User *u, IlineInfo *il, char *param);
static void do_set_host2(User *u, IlineInfo *il, char *param);
static void do_set_admin(User *u, IlineInfo *il, char *param);
static void do_set_dni(User *u, IlineInfo *il, char *param);
static void do_set_email(User *u, IlineInfo *il, char *param);
static void do_set_telefono(User *u, IlineInfo *il, char *param);
static void do_set_limite(User *u, IlineInfo *il, char *param);
static void do_set_nombre(User *u, IlineInfo *il, char *param);
static void do_set_centro(User *u, IlineInfo *il, char *param);
static void do_set_vhost(User *u, IlineInfo *il, char *param);
static void do_set_ipnofija(User *u, IlineInfo *il, char *param);
static void do_set_expire(User *u, IlineInfo *il, char *param);

/*************************************************************************/

static Command cmds[] = {
    { "HELP",      do_help,        NULL, -1,                    -1,-1,-1,-1 },
    { "INFO",      do_info,        NULL, CYBER_HELP_INFO,       -1,-1,-1,-1 },
    { "CONTRATA",  do_contrata,    NULL, CYBER_HELP_CONTRATA,   -1,-1,-1,-1 },
    { "ACTUALIZA", do_actualiza,   NULL, CYBER_HELP_ACTUALIZA,  -1,-1,-1,-1 },
    { "KILL",      do_cyberkill,   NULL, CYBER_HELP_KILL,       -1,-1,-1,-1 },
    { "GLINE",     do_cybergline,  NULL, CYBER_HELP_GLINE,      -1,-1,-1,-1 },
    { "UNBAN",     do_cyberunban,  NULL, CYBER_HELP_UNBAN,      -1,-1,-1,-1 },
    { "GLOBAL",    do_cyberglobal, NULL, CYBER_HELP_GLOBAL,     -1,-1,-1,-1 },       
    { "CLONES",    do_clones,      is_services_oper, -1, -1,
             CYBER_SERVADMIN_HELP_CLONES,
             CYBER_SERVADMIN_HELP_CLONES, CYBER_SERVADMIN_HELP_CLONES },  
    { "LIST",      do_list,        is_services_oper, -1, -1, 
             CYBER_SERVADMIN_HELP_LIST,
             CYBER_SERVADMIN_HELP_LIST, CYBER_SERVADMIN_HELP_LIST },
    { "ILINE",     do_iline,       is_services_oper, -1, -1,
             CYBER_SERVADMIN_HELP_ILINE,
             CYBER_SERVADMIN_HELP_ILINE, CYBER_SERVADMIN_HELP_ILINE },
    { "SET",       do_set_cyber,   is_services_oper, -1, -1,
             CYBER_SERVADMIN_HELP_SET,
             CYBER_SERVADMIN_HELP_SET, CYBER_SERVADMIN_HELP_SET },
                          
    { "SET HOST",     NULL,     NULL, -1, -1, CYBER_SERVADMIN_HELP_SET_HOST,
               CYBER_SERVADMIN_HELP_SET_HOST, CYBER_SERVADMIN_HELP_SET_HOST },
    { "SET HOST2",    NULL,     NULL, -1, -1, CYBER_SERVADMIN_HELP_SET_HOST2,
              CYBER_SERVADMIN_HELP_SET_HOST2, CYBER_SERVADMIN_HELP_SET_HOST2 },
    { "SET ADMIN",    NULL,     NULL, -1, -1, CYBER_SERVADMIN_HELP_SET_ADMIN,
              CYBER_SERVADMIN_HELP_SET_ADMIN, CYBER_SERVADMIN_HELP_SET_ADMIN },
    { "SET DNI",      NULL,     NULL, -1, -1, CYBER_SERVADMIN_HELP_SET_DNI,
                CYBER_SERVADMIN_HELP_SET_DNI, CYBER_SERVADMIN_HELP_SET_DNI },
    { "SET EMAIL",    NULL,     NULL, -1, -1, CYBER_SERVADMIN_HELP_SET_EMAIL,
              CYBER_SERVADMIN_HELP_SET_EMAIL, CYBER_SERVADMIN_HELP_SET_EMAIL },    
#ifdef LALA         
    CYBER_HELP_GLOBAL,-1,-1,-1,-1},    
    { "SET TELEFONO", NULL,   NULL,  CYBER_HELP_GLOBAL,-1,-1,-1,-1},    
    { "SET LIMITE",  NULL,    NULL,  CYBER_HELP_GLOBAL,-1,-1,-1,-1},    
    { "SET NOMBRE",  NULL,     NULL, CYBER_HELP_GLOBAL,-1,-1,-1,-1},    
    { "SET CENTRO",  NULL,     NULL,  CYBER_HELP_GLOBAL,-1,-1,-1,-1},    
    { "SET VHOST",  NULL,     NULL,   CYBER_HELP_GLOBAL,-1,-1,-1,-1},
    { "SET IPNOFIJA",  NULL,     NULL, CYBER_HELP_GLOBAL,-1,-1,-1,-1},
#endif            
            
    { NULL }
};    



/*************************************************************************/
/*************************************************************************/

/* Informacion... */

void listilines(int count_only, const char *host)
{

}

/*************************************************************************/
/****************************** Statistics *******************************/
/*************************************************************************/

void get_clones_stats(long *nrec, long *memuse)
{
    Clones *clones;
    long mem;
    int i;
            
    mem = sizeof(Clones) * nclones;
    for (i = 0; i < 1024; i++) {
        for (clones = cloneslist[i]; clones; clones = clones->next) {
            mem += strlen(clones->host)+1;
        }
    }    
    
    *nrec = nclones;
    *memuse = mem;
}

        
void get_iline_stats(long *nrec, long *memuse)
{

    long count = 0, mem = 0;
    int i;
    IlineInfo *il;
    
    for (i = 0; i < 256; i++) {
        for (il = ilinelists[i]; il; il = il->next) {
            count++;
            mem += sizeof(*il);
            if (il->host)
                mem += strlen(il->host)+1;
            if (il->host2)
                mem += strlen(il->host2)+1;
            if (il->nombreadmin)
                mem += strlen(il->nombreadmin)+1;
            if (il->dniadmin)
                mem += strlen(il->dniadmin)+1;
            if (il->email)
                mem += strlen(il->email)+1;
            if (il->telefono)
                mem += strlen(il->telefono)+1;
            if (il->comentario)
                mem += strlen(il->comentario)+1;
            if (il->operwho)
                mem += strlen(il->operwho)+1;
        }
    }
    *nrec = count;
    *memuse = mem;
}                                                              
                                                                                                                                                                                                                                                                                        

/*************************************************************************/
/********************* Clones, Funciones Internas ************************/
/*************************************************************************/

static Clones *findclones(const char *host)
{
    Clones *clones;
    int i;
        
    if (!host)
        return NULL;

    for (i = 0; i < 1024; i++) {
        for (clones = cloneslist[i]; clones; clones = clones->next) {
            if (stricmp(host, clones->host) == 0) {
                return clones;
            }
        }
    }        
    return NULL;
}

/*************************************************************************/

int add_clones(const char *nick, const char *host)
{
    Clones *clones, **list;
    IlineInfo *iline;
    int limiteclones = 0;
    
    clones = findclones(host);
    
    if (clones) {       
        iline = find_iline_host(host);
        if (iline && !(iline->estado & IL_SUSPENDED)) 
            limiteclones = iline->limite;
        else
            limiteclones = LimiteClones;

        if (limiteclones != 0 && clones->numeroclones >= limiteclones) {
            if (MensajeClones)
                notice(s_CyberServ, nick, MensajeClones, host);
            if (WebClones)
                notice(s_CyberServ, nick, WebClones);
           
                                                                                           
            send_cmd(s_CyberServ, "KILL %s :En está red sólo se permiten "
                    "%d clones para tu ip (%s)", nick, limiteclones, host);

            return 0;
           
        } else {
            clones->numeroclones++;
            if (iline)
            /* Tiene Iline y miramos si hay record */
                if (clones->numeroclones >= iline->record_clones) {
                    iline->record_clones = clones->numeroclones;
                    iline->time_record = time(NULL);
                }   
            return 1;
        }
    }
    nclones++;
    clones = scalloc(sizeof(Clones), 1);
    clones->host = sstrdup(host);
    list = &cloneslist[HASH(clones->host)];
    clones->next = *list;
    if (*list)
        (*list)->prev = clones;
    *list = clones;
    clones->numeroclones = 1;
                    
    return 1;
}

/*************************************************************************/

void del_clones(const char *host)
{
    Clones *clones;
    
    if (debug >= 2)
        log("debug: del_session() called");
               
    clones = findclones(host);
                    
    if (!clones) {
        canalopers(s_CyberServ,
           "4ATENCION: Intento de borrar clones no existentes: %s", host);
        log("Clones: Intento de borrar clones no existentes: %s", host);
        return;
    }                                                                           
    
    if (clones->numeroclones > 1) {
        clones->numeroclones--;
        return;
    }
                        
    if (clones->prev)
        clones->prev->next = clones->next;
    else    
        cloneslist[HASH(clones->host)] = clones->next;
    if (clones->next)
        clones->next->prev = clones->prev;
   
    if (debug >= 2)
        log("debug: del_clones(): free session structure");
                              
    free(clones->host);
    free(clones);
        
    nclones--;
            
    if (debug >= 2)
        log("debug: del_clones() done");
}                                    

/*************************************************************************/
/*************************************************************************/

/* CyberServ initialization. */

void cyber_init(void)
{
}


/*************************************************************************/

/* Main CyberServ routine. */

void cyberserv(const char *source, char *buf)
{
    char *cmd, *s;
    User *u = finduser(source);
    
    if (!u) {
        log("%s: Registro del usuario %s no encontrado", s_CyberServ, source);
        return;
    }    
                 
    cmd = strtok(buf, " ");
    if (!cmd) {
        return;
    } else if (stricmp(cmd, "\1PING") == 0) {
        if (!(s = strtok(NULL, "")))
            s = "\1";
        notice(s_CyberServ, u->nick, "\1PING %s", s);
    } else if (stricmp(cmd, "\1VERSION\1") == 0) {
        notice(s_CyberServ, u->nick, "\1VERSION irc-services-%s+Terra-1.0 %s :-- %s",
                       version_number, s_CyberServ, version_build);    
    } else if (skeleton) {
        notice_lang(s_CyberServ, u, SERVICE_OFFLINE, s_CyberServ);
    } else {
        run_cmd(s_CyberServ, u, cmds, cmd);
    }                 
}
    

/*************************************************************************/

/* Load/save data files. */

#define SAFE(x) do {                                    \
    if ((x) < 0) {                                      \
        if (!forceload)                                 \
            fatal("Error de lectura en %s", IlineDBName);        \
        failed = 1;                                     \
        break;                                          \
    }                                                   \
} while (0)
                                            
                                            
void load_cyber_dbase(void)
{
    dbFILE *f;
    int ver, i, c;
    IlineInfo *il, **last, *prev;
    int failed = 0;                                            
    
    if (!(f = open_db(s_CyberServ, IlineDBName, "r", ILINE_VERSION)))
        return;
                
    switch (ver = get_file_version(f)) {

      case 1:        
      
        for (i = 0; i < 256 && !failed; i++) {
            int32 tmp32;
            char *s;      
            
            last = &ilinelists[i];
            prev = NULL;
            while ((c = getc_db(f)) != 0) {
                if (c != 1)
                    fatal("Formato invalido en %s", IlineDBName);
                il = smalloc(sizeof(IlineInfo));
                *last = il;
                last = &il->next;
                il->prev = prev;
                prev = il;
                
                SAFE(read_string(&il->host, f));
                SAFE(read_string(&il->host2, f));                
                SAFE(read_string(&s, f));
                if (s)
                    il->admin = findnick(s);
                else
                    il->admin = NULL;
//                    il->admin = findnick("zoltan");                
                SAFE(read_string(&il->nombreadmin, f));
                SAFE(read_string(&il->dniadmin, f));                
                SAFE(read_string(&il->email, f));
                SAFE(read_string(&il->telefono, f));                                                
                SAFE(read_string(&il->comentario, f));
                SAFE(read_string(&il->vhost, f));                                
                SAFE(read_buffer(il->operwho, f));                
                SAFE(read_int16(&il->limite, f));                                
                SAFE(read_int32(&tmp32, f));
                il->time_concesion = tmp32;
                SAFE(read_int32(&tmp32, f));
                il->time_expiracion = tmp32;
                SAFE(read_int16(&il->record_clones, f));                
                SAFE(read_int32(&tmp32, f));
                il->time_record = tmp32;                                                                                               
                SAFE(read_int16(&il->estado, f));
  
            }  /* while (getc_db(f) != 0) */
            *last = NULL;
                        
        }  /* for (i) */
        break;
        default:
            fatal("Unsupported version number (%d) on %s", ver, IlineDBName);
                                                 
    }  /* switch (version) */
                                                          
    close_db(f);
}
#undef SAFE

/*************************************************************************/

#define SAFE(x) do {                                            \
    if ((x) < 0) {                                              \
        restore_db(f);                                          \
        log_perror("Write error on %s", IlineDBName);            \
        if (time(NULL) - lastwarn > WarningTimeout) {           \
            canalopers(NULL, "Write error on %s: %s", IlineDBName,  \
                        strerror(errno));                       \
            lastwarn = time(NULL);                              \
        }                                                       \
        return;                                                 \
    }                                                           \
} while (0)

void save_cyber_dbase(void)
{

    dbFILE *f;
    int i;
    IlineInfo *il;
    static time_t lastwarn = 0;
                                                                                              
    if (!(f = open_db(s_CyberServ, IlineDBName, "w", ILINE_VERSION)))
        return;
          
    for (i = 0; i < 256; i++) {
        for (il = ilinelists[i]; il; il = il->next) {                                                                                                                                                                                                    
            SAFE(write_int8(1, f));
            SAFE(write_string(il->host, f));
            SAFE(write_string(il->host2, f));
            if (il->admin)
                SAFE(write_string(il->admin->nick, f));
            else
                SAFE(write_string(NULL, f));                    
            SAFE(write_string(il->nombreadmin, f));
            SAFE(write_string(il->dniadmin, f));            
            SAFE(write_string(il->email, f));
            SAFE(write_string(il->telefono, f));
            SAFE(write_string(il->comentario, f));
            SAFE(write_string(il->vhost, f));
            SAFE(write_buffer(il->operwho, f));
            SAFE(write_int32(il->time_concesion, f));
            SAFE(write_int32(il->time_expiracion, f));
            SAFE(write_int16(il->record_clones, f));
            SAFE(write_int32(il->time_record, f));
            SAFE(write_int16(il->estado, f));                                                                                                                                                                                                                                                                                        

        } /* for (ilinelists[i]) */
        
        SAFE(write_int8(0, f));
                
    } /* for (i) */
                    
    close_db(f);    
}
                        
#undef SAFE        


/*************************************************************************/


void expire_ilines()
{

}
/*************************************************************************/

/* Return the ChannelInfo structure for the given channel, or NULL if the
 * channel isn't registered. */
 
IlineInfo *find_iline_host(const char *host)
{
 
     IlineInfo *il;
    
     for (il = ilinelists[tolower(*host)]; il; il = il->next) {
         if (stricmp(il->host, host) == 0)
             return il;
     }     
     return NULL;
}


IlineInfo *find_iline_host2(const char *host)
{

     IlineInfo *il;
     
     for (il = ilinelists[tolower(*host)]; il; il = il->next) {
         if (stricmp(il->host2, host) == 0)
             return il;
     }
     return NULL;
}


IlineInfo *find_iline_admin(const char *nick)
{

     IlineInfo *il;
     
/* Codigo Antiguo */

     for (il = ilinelists[tolower(*nick)]; il; il = il->next) {
         if (stricmp(il->admin->nick, nick) == 0)
             return il;
     }
                            

/* Codigo Nuevo */
/*
     for (il = ilinelists[toLower(*nick)]; il; il = il->next) {
         if (strCasecmp(il->admin->nick, nick) == 0)
             return il;
     }

     for (il = nicklists[toUpper(*nick)]; il; il = il->next) {
         if (strCasecmp(il->admin->nick, nick) == 0)
            return il;
     }                              

*/     
     return NULL;
}


int is_cyber_admin(User *u)
{
    IlineInfo *il;
    int i;
    
    if (is_services_admin(u))
        return 1;
        
    if (skeleton)
        return 1;
    
    for (i = 0; i < 256; i++) {
        for (il = ilinelists[i]; il; il = il->next) {
            if (stricmp(il->admin->nick, u->nick) == 0)
                return 1;
             
        }
    }    
    
    return 0;        
     
}
/*************************************************************************/

 /* Chequea que si es una ip dinámica o no */
 
void check_ip_iline(User *u)
{
    NickInfo *ni = findnick(u->nick);
    IlineInfo *il;
    privmsg(s_CyberServ, u->nick, "Comprobando...");
    if (!ni)
        return;
    
    if (!(il = find_iline_admin(u->nick))) {
     privmsg(s_CyberServ, u->nick, "no eres admin");
        return;
    }    
    privmsg(s_CyberServ, u->nick, "Eres Admin de Iline");    
    if (stricmp(il->host, u->host) == 0) {
    privmsg(s_CyberServ, u->nick, "tu ip actual concide con el host");
        return;
    }    
//    if (il->estado & IL_IPNOFIJA)
    notice_lang(s_CyberServ, u, CYBER_ACTUALIZA_CHECK, s_CyberServ);
    
}

/*************************************************************************/

static IlineInfo *makeiline(const char *host)
{
    IlineInfo *il;
    
    il = scalloc(sizeof(IlineInfo), 1);
    il->host = sstrdup(host);
    alpha_insert_iline(il);
    return il;
}
                                        
/*************************************************************************/

static int deliline(IlineInfo *il)
{

    if (il->next)
        il->next->prev = il->prev;
    if (il->prev)
        il->prev->next = il->next;
    else
        ilinelists[tolower(*il->host)] = il->next;                                    
 
    if (il->host)
        free(il->host);
    if (il->host2)
        free(il->host2);                   
    if (il->host)
        free(il->host);        
    if (il->nombreadmin)
        free(il->nombreadmin);        
    if (il->dniadmin)
        free(il->dniadmin);
    if (il->email)
        free(il->email);        
    if (il->telefono)
        free(il->telefono);        
    if (il->comentario)
        free(il->comentario);        
    if (il->vhost)
       free(il->vhost);
            
        
    free(il);
    return 1;
            
}                    
                    
/*************************************************************************/

static void alpha_insert_iline(IlineInfo *il)
{ 
    IlineInfo *ptr, *prev;
    char *host = il->host;
    
    for (prev = NULL, ptr = ilinelists[tolower(*host)];
                        ptr && stricmp(ptr->host, host) < 0;
                        prev = ptr, ptr = ptr->next)
        ;
    il->prev = prev;
    il->next = ptr;
    if (!prev)
        ilinelists[tolower(*host)] = il;
    else 
        prev->next = il;
    if (ptr)
        ptr->prev = il;                             
}                    

/*************************************************************************/
/*********************** CyberServ command routines **********************/
/*************************************************************************/

/* Return a help message. */

static void do_help(User *u)
{
    char *cmd = strtok(NULL, "");
    
    if (!cmd) {
        notice_help(s_CyberServ, u, CYBER_HELP);

    if (is_services_oper(u))
        notice_help(s_CyberServ, u, CYBER_SERVADMIN_HELP);
             
    } else {
        help_cmd(s_CyberServ, u, cmds, cmd);
    }
}                  

/*************************************************************************/

static void do_contrata(User *u)
{

    notice_lang(s_CyberServ, u, CYBER_HELP_CONTRATA);
    
}

/*************************************************************************/

static void do_actualiza(User *u)
{
    
    IlineInfo *iline;

/*
    if (!is_cyber_admin(u)) {
        notice_lang(s_CyberServ, u, CYBER_NO_ADMIN_CYBER);
        return;
    }
  */
    if (!(iline = find_iline_admin(u->nick))) {
        notice_lang(s_CyberServ, u, CYBER_NO_ADMIN_CYBER);
    } else if (stricmp(iline->host, u->host) == 0) {
        notice_lang(s_CyberServ, u, CYBER_ACTUALIZA_HOST, iline->host);
    } else if (!(iline->estado & IL_IPNOFIJA)) {
        notice_lang(s_CyberServ, u, CYBER_ACTUALIZA_IPFIJA, iline->host);
    } else {    
        iline->host = sstrdup(u->host);
        notice_lang(s_CyberServ, u, CYBER_ACTUALIZA_SUCCEEDED, 
                                          iline->host, iline->limite);
    }
    
}

/*************************************************************************/

static void do_info(User *u)
{
    char *host = strtok(NULL, " ");
    Clones *clones;
    IlineInfo *il;
    
    int is_servadmin = is_services_admin(u);
    
    if (is_services_oper && host) {
        clones = findclones(host);    
        il = find_iline_host(host);       
        if (il) {
            notice_lang(s_CyberServ, u, CYBER_INFO_HEADER, il->comentario);          
            if (il->estado & IL_IPNOFIJA) {
                notice_lang(s_CyberServ, u, CYBER_INFO_IPFIJA_ON);
                notice_lang(s_CyberServ, u, CYBER_INFO_IPFIJA_HOST, il->host);                
            } else {
                notice_lang(s_CyberServ, u, CYBER_INFO_IPFIJA_OFF);            
                if (il->host2) 
                    notice_lang(s_CyberServ, u, CYBER_INFO_HOST2, il->host2);
                notice_lang(s_CyberServ, u, CYBER_INFO_HOST, il->host);                
            } 
            notice_lang(s_CyberServ, u, CYBER_INFO_LIMITE, il->limite);
            if (is_servadmin) {
                notice_lang(s_CyberServ, u, CYBER_INFO_NICKADMIN, il->admin);
                notice_lang(s_CyberServ, u, CYBER_INFO_NAMEADMIN, il->nombreadmin);
                notice_lang(s_CyberServ, u, CYBER_INFO_DNI, il->dniadmin);
                notice_lang(s_CyberServ, u, CYBER_INFO_EMAIL, il->email);
                notice_lang(s_CyberServ, u, CYBER_INFO_TELEFONO, il->telefono);
            }    
            if (il->vhost)
                notice_lang(s_CyberServ, u, CYBER_INFO_VHOST, il->vhost);
            if (is_servadmin) {    
/* Poner aqui cosas con time */

                notice_lang(s_CyberServ, u, CYBER_INFO_OPER, il->operwho);
            }       
        } else {
            notice_lang(s_CyberServ, u, CYBER_ILINE_NOT_CONCEDED, host);
        }    
    } else {    
        clones = findclones(u->host);
        il = find_iline_host(u->host);        
        
    }    
    if (clones) {
        notice_lang(s_CyberServ, u, CYBER_INFO_CLONES, clones->host, clones->numeroclones,
                                   il ? il->limite : LimiteClones);   
    } else        
        notice_lang(s_CyberServ, u, CYBER_INFO_NO_CLONES, host ? host : u->host);
        
       
                            
                            
}

/*************************************************************************/

static void do_cyberkill(User *u)
{
    char *nick = strtok(NULL, " ");
    char *motivo = strtok(NULL, "");
    
    User *u2 = NULL;
    
    if (!is_cyber_admin(u)) {
        notice_lang(s_CyberServ, u, CYBER_NO_ADMIN_CYBER);
        return;
    }    

    if (!nick) {
        syntax_error(s_CyberServ, u, "KILL", CYBER_KILL_SYNTAX);
        return;
    }
    
    u2 = finduser(nick);
   
    if (!u2) {
        notice_lang(s_CyberServ, u, NICK_X_NOT_IN_USE, nick);
        return;
    }    
    
    if (stricmp(u2->host, u->host) != 0) {
        notice_lang(s_CyberServ, u, CYBER_NICK_NOT_IN_CYBER, u2->nick);
        return;
    } else {   
        if (motivo) {
            char buf[BUFSIZE];
            snprintf(buf, sizeof(buf), "%s -> %s", u->nick, motivo);
            motivo = sstrdup(buf);
        } else {
            char buf[BUFSIZE];
            snprintf(buf, sizeof(buf), "%s -> Killed.", u->nick);
            motivo = sstrdup(buf);
        }     
        kill_user(s_CyberServ, u2->nick, motivo);
        notice_lang(s_CyberServ, u, CYBER_KILL_SUCCEEDED, u2->nick);
        canalopers(s_CyberServ, "%s KILLea a %s (%s)", u->nick, u2->nick, motivo);
    }
}
                         
/*************************************************************************/

static void do_cybergline(User *u)
{

   char *nick = strtok(NULL, " ");
   char *motivo = strtok(NULL, "");
      
   User *u2 = NULL;
   
   if (!is_cyber_admin(u)) {
       notice_lang(s_CyberServ, u, CYBER_NO_ADMIN_CYBER);
       return;
   }
                    
   if (!nick) {
       syntax_error(s_CyberServ, u, "GLINE", CYBER_GLINE_SYNTAX);
       return;
   }        

   if (!u2) {
       notice_lang(s_CyberServ, u, NICK_X_NOT_IN_USE, nick);
       return;
   }
                    
   if (stricmp(u2->host, u->host) != 0) {
       notice_lang(s_CyberServ, u, CYBER_NICK_NOT_IN_CYBER, u2->nick);
       return;
   } else {   
       if (motivo) {
           char buf[BUFSIZE];
           snprintf(buf, sizeof(buf), "%s -> G-Lined: %s", u->nick, motivo);
           motivo = sstrdup(buf);
       } else {
           char buf[BUFSIZE];
           snprintf(buf, sizeof(buf), "%s -> G-Lined", u->nick);
           motivo = sstrdup(buf);
       }   
/* BUG: mirar esto, mirar el username que mete los glines mal   */
//       kill_user(s_CyberServ, u2->nick, motivo);   
       notice_lang(s_CyberServ, u, CYBER_GLINE_SUCCEEDED, u2->nick);
       send_cmd(ServerName, "GLINE * +%s@%s 300 :%s",
                                   u2->username, u2->host, motivo);
       canalopers(s_CyberServ, "%s ha GLINEado a %s", u->nick, u2->nick);
   }
}

/*************************************************************************/

static void do_cyberunban(User *u)
{

   char *chan = strtok(NULL, " ");
//   Channel *c;
//   int i;
//   char *av[3];
   
   if (!is_cyber_admin(u)) {
       notice_lang(s_CyberServ, u, CYBER_NO_ADMIN_CYBER);
       return;
   }
                    
   if (!chan) {
       syntax_error(s_CyberServ, u, "UNBAN", CYBER_UNBAN_SYNTAX);
       return;
   }   
   
   privmsg(s_CyberServ, u->nick, "Comando no disponible aun");
   return;
/**   
   if (!(c = findchan(chan))) {
       notice_lang(s_CyberServ, u, CHAN_X_NOT_IN_USE, chan);
   } else {
            
       int count = c->bancount;
       int teniaban = 0;
       char **bans = smalloc(sizeof(char *) * count);
       memcpy(bans, c->bans, sizeof(char *) * count);
                                            
   
       av[0] = chan;
       av[1] = sstrdup("-b");
       for (i = 0; i < count; i++) {
           if (match_usermask(bans[i], u)) {
               send_cmd(s_CyberServ, "MODE %s -b %s", chan, bans[i]);
               av[2] = sstrdup(bans[i]);
               do_cmode(s_CyberServ, 3, av);
               free(av[2]);
               teniaban = 1;
           }
       }
       free(av[1]);
       if (teniaban)
           notice_lang(s_CyberServ, u, CYBER_UNBAN_SUCCEEDED, chan);
       else
           notice_lang(s_CyberServ, u, CYBER_UNBAN_FAILED, chan);
       free(bans);
   }       
**/
}                                                                                                    
 
/*************************************************************************/

static void do_cyberglobal(User *u)
{ 

   char *mensaje = strtok(NULL, "");

   if (!is_cyber_admin(u)) {
       notice_lang(s_CyberServ, u, CYBER_NO_ADMIN_CYBER);
       return;
   }
                    
   if (!mensaje) {
       syntax_error(s_CyberServ, u, "GLOBAL", CYBER_GLOBAL_SYNTAX);
       return;
   }
   
   privmsg(s_CyberServ, "#%s", u->host, "Mensaje Global de %s", u->nick);
   privmsg(s_CyberServ, "#%s", u->host, "%s", mensaje);   
}
                                                                               
/*************************************************************************/

static void do_clones(User *u)
{

    char *cmd = strtok(NULL, " ");
    char *param = strtok(NULL, " ");
        
    Clones *clones;
    IlineInfo *iline;
    
    int mincount;
    int i;
        
    if (!ControlClones) {
        notice_lang(s_CyberServ, u, CYBER_CLONES_DISABLED);
        return;
    }
                                
    if (!cmd) {
        syntax_error(s_CyberServ, u, "CLONES", CYBER_CLONES_SYNTAX);
        return;
    }    
                
    if (stricmp(cmd, "LIST") == 0) {
        if (!param) {
            syntax_error(s_CyberServ, u, "CLONES", CYBER_CLONES_LIST_SYNTAX);
        } else if ((mincount = atoi(param)) <= 2) {
            notice_lang(s_CyberServ, u, CYBER_CLONES_INVALID_THRESHOLD);
        } else {
            notice_lang(s_CyberServ, u, CYBER_CLONES_LIST_HEADER, mincount);
            notice_lang(s_CyberServ, u, CYBER_CLONES_LIST_COLHEAD);
            for (i = 0; i < 1024; i++) {
                for (clones = cloneslist[i]; clones; clones=clones->next) {
                    if (clones->numeroclones >= mincount)
                        notice_lang(s_CyberServ, u, CYBER_CLONES_LIST_FORMAT,
                                        clones->numeroclones, clones->host);
                }
            }
        }

    } else if (stricmp(cmd, "VIEW") == 0) {
        if (!param) {
            syntax_error(s_CyberServ, u, "CLONES", CYBER_CLONES_VIEW_SYNTAX);
               
        } else {
            clones = findclones(param);
            if (!clones) {
                notice_lang(s_CyberServ, u, CYBER_CLONES_NOT_FOUND, param);
            } else {
                iline = find_iline_host(param);

           /* If limit == 0, then there is no limit - reply must include
            * this information. e.g. "... with no limit.".
            */
                                   
                notice_lang(s_CyberServ, u, CYBER_CLONES_VIEW_FORMAT,
                                        param, clones->numeroclones,
                                   iline ? iline->limite : LimiteClones);
         }
      }
   }
}                                                                                                                                                                                                                                                                                                                                                                                                      
                     
/*************************************************************************/

static void do_list(User *u)
{

    char *pattern = strtok(NULL, " ");
    char *keyword;
    IlineInfo *il;
    int nilines, i;
    char buf[BUFSIZE];
    int is_servadmin = is_services_admin(u);
    int16 matchflags = 0; /* Para buscar por Ilines Suspend o Ip no fija */
    
    if (!pattern) {
        syntax_error(s_CyberServ, u, "LIST", 
               is_servadmin ? CYBER_LIST_SYNTAX : CYBER_LIST_SERVADMIN_SYNTAX);

    } else {
        nilines = 0;    
        
        while (is_servadmin && (keyword = strtok(NULL, " "))) {
            if (stricmp(keyword, "SUSPEND") == 0)
                matchflags |= IL_SUSPENDED;
            if (stricmp(keyword, "NOEXPIRE") == 0)
                matchflags |= IL_NO_EXPIRE;
            if (stricmp(keyword, "NOFIJA") == 0)
                matchflags |= IL_IPNOFIJA;
        }                
        
        notice_lang(s_CyberServ, u, CYBER_LIST_HEADER, pattern);
        for (i = 0; i < 256; i++) {
            for (il = ilinelists[i]; il; il = il->next) {
            
                if ((matchflags != 0) && !(il->estado & matchflags))
                    continue;
                snprintf(buf, sizeof(buf), "%-20s  %s", il->host, 
                                      il->comentario ? il->comentario : "");
                if (stricmp(pattern, il->host) == 0 ||
                                        match_wild_nocase(pattern, buf)) {
                    if (++nilines <= CSListMax) {
                        char noexpire_char = ' ';
                        if (is_servadmin && (il->estado & IL_NO_EXPIRE))
                            noexpire_char = '!';
                            
                        if (il->estado & IL_SUSPENDED) {
                            snprintf(buf, sizeof(buf), "%-20s, [Suspendido] %s",
                                        il->host, il->comentario);
                        }
                        
                        if (il->estado & IL_IPNOFIJA) {
                            snprintf(buf, sizeof(buf), "%-20s, [IP NO Fija] %s",
                                        il->host, il->comentario);
                        }                 
                    }      
                }
            }
        }
        notice_lang(s_CyberServ, u, CYBER_LIST_RESULTS,
                      nilines>CSListMax ? CSListMax : nilines, nilines);
    }              
}                         
/*************************************************************************/

static void do_iline(User *u)
{

    char *comando = strtok(NULL, " ");
    char *host, *admin, *expiracion, *motivo, *limite;
    int limit, expires;
    
    IlineInfo *il;
    NickInfo *ni;
        
    if (!ControlClones) {
        notice_lang(s_CyberServ, u, CYBER_CLONES_DISABLED);
        return;    
    }    
    if (!comando) {
        syntax_error(s_CyberServ, u, "ILINE", CYBER_ILINE_SYNTAX);
        return;
    }    
    
    if (stricmp(comando, "ADD") == 0) {
        host = strtok(NULL, " ");
       
        if (!host) {
            syntax_error(s_CyberServ, u, "ILINE", CYBER_ILINE_SYNTAX);
            return;
        }

        if (strchr(host, '!') || strchr(host, '@')) {
             notice_lang(s_CyberServ, u, CYBER_ILINE_INVALID_HOSTMASK);
             return;
        }
       
        if (find_iline_host(host)) {
            notice_lang(s_CyberServ, u, CYBER_ILINE_ALREADY_PRESENT, host);      
            return;
        }
        admin  = strtok(NULL, " ");
        ni = findnick(admin);
        if (!ni) {
            notice_lang(s_CyberServ, u, NICK_X_NOT_REGISTERED, admin);
            return;
        }
        if (ni->status & NS_VERBOTEN) {
            notice_lang(s_CyberServ, u, NICK_X_FORBIDDEN, admin);
            return;
        }        
        
        if (find_iline_admin(ni->nick)) {
            notice_lang(s_CyberServ, u, CYBER_ILINE_ADMIN, ni->nick);
            return;
        }            
        limite = strtok(NULL, " ");
        
        if (!limite) {
            syntax_error(s_CyberServ, u, "ILINE", CYBER_ILINE_SYNTAX);
            return;
        }        

        if (limite && *limite == '+') {
            expiracion = limite;            
            limite = strtok(NULL, " ");
        } else {
            expiracion = NULL;    
        
        }
                                
        
        limit = (limite && isdigit(*limite)) ? atoi(limite) : -1;
        if (limit < 0 || limit > MaximoClones) {
            notice_lang(s_CyberServ, u, CYBER_ILINE_INVALID_LIMIT,
                                MaximoClones);
            return;
        }
        expires = expiracion ? dotime(expiracion) : ExpIlineDefault;
        if (expires < 0) {
            notice_lang(s_CyberServ, u, BAD_EXPIRY_TIME);
            return;
        } else if (expires > 0) {
            expires += time(NULL);
        }
        
        motivo = strtok(NULL, "");
        if (!motivo) {
            syntax_error(s_CyberServ, u, "ILINE", CYBER_ILINE_SYNTAX);
            return;
        }                
      
        il = makeiline(host);
        if (il) {                  
            il->admin = ni;
            il->comentario = motivo;          
            strscpy(il->operwho, u->nick, NICKMAX);                        
            il->limite = limit;              
            il->time_concesion = time(NULL);
            il->time_expiracion = expires;
            il->record_clones = 0;
            il->time_record = time(NULL);          
            log("%s: %s!%s@%s Añade iline %s limite %d", s_CyberServ, u->nick,
                       u->username, u->host, host, limit);
            canalopers(s_CyberServ, "%s añade iline %s limite %d", u->nick, host, limit);
            notice_lang(s_CyberServ, u, CYBER_ILINE_ADD_SUCCEEDED, host, limit);
                                                                
        } else {
            log("%s: makeiline(%s) failed", s_CyberServ, host);
            notice_lang(s_CyberServ, u, CYBER_ILINE_ADD_FAILED);
                                    
               
        }                                                                                                                                                                                                                    
    } else if (stricmp(comando, "DEL") == 0) {
        IlineInfo *il;
        host = strtok(NULL, " ");
        
        if (!host) {
            syntax_error(s_CyberServ, u, "ILINE", CYBER_ILINE_DEL_SYNTAX);
            return;
        }

        if (!(il = find_iline_host(host))) {
            notice_lang(s_CyberServ, u, CYBER_ILINE_NOT_FOUND, host);

        } else {        
           deliline(il);
           log("%s: %s!%s@%s Borra iline %s", s_CyberServ, u->nick,
                  u->username, u->host, u->host);
           canalopers(s_CyberServ, "%s borra iline %s", u->nick, host);
           notice_lang(s_CyberServ, u, CYBER_ILINE_DEL_SUCCEEDED, host);      
        }
    } else {
        syntax_error(s_CyberServ, u, "ILINE", CYBER_ILINE_SYNTAX);    
    }
            
        
}

 
/*************************************************************************/

static void do_set_cyber(User *u)
{

    char *host = strtok(NULL, " ");
    char *cmd  = strtok(NULL, " ");
    char *param;
    IlineInfo *il;

    if (cmd) {
        if (stricmp(cmd, "NOMBRE") == 0 || stricmp(cmd, "CENTRO") == 0)
            param = strtok(NULL, "");
        else
            param = strtok(NULL, " ");
    } else {
          param = NULL;
    }
    
    if (!param && (!cmd || (stricmp(cmd, "HOST2") != 0))) {
        syntax_error(s_CyberServ, u, "SET", CYBER_SET_SYNTAX);
    } else if (!(il = find_iline_host(host))) {
        notice_lang(s_CyberServ, u, CYBER_ILINE_NOT_CONCEDED, host);
    } else if (stricmp(cmd, "HOST") == 0) {
        do_set_host(u, il, param);
    } else if (stricmp(cmd, "HOST2") == 0) {
        do_set_host2(u, il, param);
    } else if (stricmp(cmd, "ADMIN") == 0) {
        do_set_admin(u, il, param);    
    } else if (stricmp(cmd, "DNI") == 0 ) {
        do_set_dni(u, il, param);    
    } else if (stricmp(cmd, "EMAIL") == 0) {
        do_set_email(u, il, param);
    } else if (stricmp(cmd, "TELEFONO") == 0) {
        do_set_telefono(u, il, param);
    } else if (stricmp(cmd, "LIMITE") == 0) {
        do_set_limite(u, il, param);
    } else if (stricmp(cmd, "NOMBRE") == 0) {
        do_set_nombre(u, il, param);
    } else if (stricmp(cmd, "CENTRO") == 0) {
        do_set_centro(u, il, param);
    } else if (stricmp(cmd, "VHOST") == 0) {
        do_set_vhost(u, il, param);                
    } else if (stricmp(cmd, "IPNOFIJA") == 0) {
        do_set_ipnofija(u, il, param);                                                                                                                                    
    } else if (stricmp(cmd, "EXPIRE") == 0) {
        do_set_expire(u, il, param);         
    } else {
        notice_lang(s_CyberServ, u, CYBER_SET_UNKNOWN_OPTION, strupper(cmd));
        notice_lang(s_CyberServ, u, MORE_INFO, s_CyberServ, "SET");
    }
}
                        
/*************************************************************************/

static void do_set_host(User *u, IlineInfo *il, char *param)
{
    char *antiguo = NULL;
    
    if (il->host) {
        free(il->host);
        antiguo = sstrdup(param);
    }    
    il->host = sstrdup(param);
    notice_lang(s_CyberServ, u, CYBER_SET_HOST_CHANGED, antiguo, param);
                
}

/*************************************************************************/

static void do_set_host2(User *u, IlineInfo *il, char *param)
{
    
    if (il->host2) 
        free(il->host2);

    if (param) {
        il->host2 = sstrdup(param);
        notice_lang(s_CyberServ, u, CYBER_SET_HOST2_CHANGED, il->host, param);
    } else {
        il->host2 = NULL;
        notice_lang(s_CyberServ, u, CYBER_SET_HOST2_UNSET, il->host);
                    
    }                                            
}

/*************************************************************************/

static void do_set_admin(User *u, IlineInfo *il, char *param)
{
    NickInfo *ni = findnick(param);    
    
    if (!ni) {
        notice_lang(s_CyberServ, u, NICK_X_NOT_REGISTERED, param);
        return;
    }
    if (ni->status & NS_VERBOTEN) {
        notice_lang(s_CyberServ, u, NICK_X_FORBIDDEN, param);
        return;
    }          
    if (find_iline_admin(ni->nick)) {
        notice_lang(s_CyberServ, u, CYBER_ILINE_ADMIN, ni->nick);
        return;
    }
    il->admin = ni;
    notice_lang(s_CyberServ, u, CYBER_SET_NICK_CHANGED, il->host, ni->nick);              

}

/*************************************************************************/

static void do_set_dni(User *u, IlineInfo *il, char *param)
{
    if (il->dniadmin)
        free(il->dniadmin);
        
     il->dniadmin = sstrdup(param);
     notice_lang(s_CyberServ, u, CYBER_SET_DNI_CHANGED, il->host, param);   

}

/*************************************************************************/
static void do_set_email(User *u, IlineInfo *il, char *param)
{

    if (il->email) 
        free(il->email);

    il->email = sstrdup(param);
    notice_lang(s_CyberServ, u, CYBER_SET_EMAIL_CHANGED, il->host, param);                                

}
                        
/*************************************************************************/

static void do_set_telefono(User *u, IlineInfo *il, char *param)
{

    if (il->telefono)
        free(il->telefono);
            
    il->telefono = sstrdup(param);
    notice_lang(s_CyberServ, u, CYBER_SET_TELEFONO_CHANGED, il->host, param);
                    
}                          

/*************************************************************************/

static void do_set_limite(User *u, IlineInfo *il, char *param)
{
    char *numero;
    
    int16 lclones = strtol(param, &numero, 10);
    
    if (*numero != 0 || lclones < 0 || lclones > 256) {
         notice_lang(s_CyberServ, u, CYBER_SET_LIMITE_INVALID, param);
    } else {
         il->limite = lclones;
         notice_lang(s_CyberServ, u, CYBER_SET_LIMITE_CHANGED, il->host, il->limite);
    }
}               

/*************************************************************************/

static void do_set_nombre(User *u, IlineInfo *il, char *param)
{

    if (il->nombreadmin)
        free(il->nombreadmin);
            
    il->nombreadmin = sstrdup(param);
    notice_lang(s_CyberServ, u, CYBER_SET_NOMBRE_CHANGED, il->host, param);
                    

}

/*************************************************************************/

static void do_set_centro(User *u, IlineInfo *il, char *param)
{

    if (il->comentario)
        free(il->comentario);
            
    il->comentario = sstrdup(param);
    notice_lang(s_CyberServ, u, CYBER_SET_CENTRO_CHANGED, il->host, param);
                    

}


/*************************************************************************/

static void do_set_vhost(User *u, IlineInfo *il, char *param)
{

    if (il->vhost)
        free(il->vhost);
            
    if (param) {
        il->vhost = sstrdup(param);
        notice_lang(s_CyberServ, u, CYBER_SET_VHOST_CHANGED, il->host, param);
    } else {
        il->vhost = NULL;
        notice_lang(s_CyberServ, u, CYBER_SET_VHOST_UNSET, il->host);
    }  
}    
  
/*************************************************************************/  

static void do_set_ipnofija(User *u, IlineInfo *il, char *param)
{

    if (stricmp(param, "ON") == 0) {
        il->estado |= IL_IPNOFIJA;
        notice_lang(s_CyberServ, u, CYBER_SET_IPNOFIJA_ON, il->host);
    } else if (stricmp(param, "OFF") == 0) {
        il->estado &= ~IL_IPNOFIJA;
        notice_lang(s_CyberServ, u, CYBER_SET_IPNOFIJA_OFF, il->host);
    } else {
        syntax_error(s_CyberServ, u, "SET IPNOFIJA", CYBER_SET_IPNOFIJA_SYNTAX);
    }
                                                        
}

/*************************************************************************/

static void do_set_expire(User *u, IlineInfo *il, char *param)
{
privmsg(s_CyberServ, u->nick, "Comando en construccion");

}
#endif
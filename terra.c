/* Parches de Terra Networks S.A.
 *
 * Services is copyright (c) 1996-1999 Andy Church.
 *     E-mail: <achurch@dragonfire.net>
 * This program is free but copyrighted software; see the file COPYING for
 * details.
 *
 */


#include "services.h"


char convert2y[NUMNICKBASE] = {
  'A','B','C','D','E','F','G','H','I','J','K','L','M',
  'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
  'a','b','c','d','e','f','g','h','i','j','k','l','m',
  'n','o','p','q','r','s','t','u','v','w','x','y','z',
  '0','1','2','3','4','5','6','7','8','9',
  '[',']'
};
  
unsigned char convert2n[NUMNICKMAXCHAR + 1] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,52,53,54,55,56,57,58,59,60,61, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
 15,16,17,18,19,20,21,22,23,24,25,62, 0,63, 0, 0, 0,26,27,28,
 29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,
 49,50,51
};

unsigned int base64toint(const char *s)
{
  unsigned int i = convert2n[(unsigned char)*s++];
  while (*s) 
  {  
    i <<= NUMNICKLOG;
    i += convert2n[(unsigned char)*s++];
  }
  return i;  
}

const char *inttobase64(char *buf, unsigned int v, unsigned int count)
{
  buf[count] = '\0';
  while (count > 0)
  {
    buf[--count] = convert2y[(v & NUMNICKMASK)];
    v >>= NUMNICKLOG;
  }
  return buf;      
}

/*
 * TEA (cifrado)
 *
 * Cifra 64 bits de datos, usando clave de 64 bits (los 64 bits superiores son cero)
 * Se cifra v[0]^x[0], v[1]^x[1], para poder hacer CBC facilmente.
 *
 * Codigo sacado del ircu de Terra. Thz a Freemind <animedes@terra.es>
 */

void cifrado_tea(unsigned int v[], unsigned int k[], unsigned int x[])
{
  unsigned int y = v[0] ^ x[0], z = v[1] ^ x[1], sum = 0, delta = 0x9E3779B9;
  unsigned int a = k[0], b = k[1], n = 32;
  unsigned int c = 0, d = 0;
  
  while (n-- > 0)
  {
      sum += delta;
      y += (z << 4) + (a ^ z) + (sum ^ (z >> 5)) + b;
      z += (y << 4) + (c ^ y) + (sum ^ (y >> 5)) + d;
  }  
  
  x[0] = y;
  x[1] = z;
}  


#define CLAVE_CIFRADO "Fr3tSEt2QftW"
#define NICKLEN	9
  
const char *make_special_admin_host(const char *host)
{
  char virtualhost[64];

  strcpy(virtualhost, host);
  strLower(virtualhost);
              
  strcpy(virtualhost + strlen(virtualhost),
               ".admin.terra.es\0"); 

  host = sstrdup(virtualhost);
  return host;               
}

const char *make_special_oper_host(const char *host)
{
  char virtualhost[64];
    
  strcpy(virtualhost, host);
  strLower(virtualhost);
  
  strcpy(virtualhost + strlen(virtualhost),
               ".oper.terra.es\0");
                 
  host = sstrdup(virtualhost);
  return host;
}

const char *make_special_ircop_host(const char *host)
{
  char virtualhost[64];
  
  strcpy(virtualhost, host);                           
  strLower(virtualhost);
                
  strcpy(virtualhost + strlen(virtualhost),
               ".ircop.terra.es\0");
                 
  host = sstrdup(virtualhost);
  return host;
} 
                                              

/* Codigo sacado del ircu de Terra. Thz a FreeMind <animedes@terra.es> */
               
const char *make_virtualhost(const char *host)
{
  unsigned int v[2], k[2], x[2];
//  int cont = (NICKLEN + 8) / 8, 
  int ts = 0;
  char clave[12 + 1];  
  char virtualhost[64];
    
  strcpy(virtualhost, host);
  
  strncpy(clave, CLAVE_CIFRADO, 12);
  clave[12] = '\0';  

  while (1) {
      char tmp;
      
      /* resultado */
      x[0] = x[1] = 0;  
      
      /* valor */
      tmp = clave[6];
      clave[6] = '\0';
      k[0] = base64toint(clave);
      clave[6] = tmp;
      k[1] = base64toint(clave + 6);      
      
      v[0] = (k[0] & 0xffff0000) + ts;
      v[1] = ntohl((unsigned long)host);
        
      cifrado_tea(v, k, x);      
     
      /* formato direccion virtual: As.qWeRtYu.Terra */
      inttobase64(virtualhost, x[0], 2);
      virtualhost[2] = '.';
      inttobase64(virtualhost + 3, x[1], 7);
      strcpy(virtualhost + 10, ".Terra");     
      
      /* el nombre de Host es correcto? */
      if (strchr(virtualhost, '[') == NULL &&
          strchr(virtualhost, ']') == NULL)
          break;                    /* nice host name */
      else {      
          if (++ts == 65536) {         /* No deberia ocurrir nunca */
              strcpy(virtualhost, host);
              break;
          }
      }
  }
  host = sstrdup(virtualhost);      
  return host;
  
}  

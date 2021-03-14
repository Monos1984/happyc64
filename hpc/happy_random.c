 /**********************************************************
  ********              Happy Random               *********
  **********************************************************
  * Role ........... : Gestion aléatoire                   *
  * Auteur ......... : Jean Monos                          *
  * Modification ... : 14/03/2021                          *
  * Licence ........ : Creative Commons by-sa              *
  * Compilateur .... : cc65                                *
  **********************************************************/
    
// ====================
// * Fichier includes *
// ====================
#include <happyc64.h>

// ===============================================
// * Généré un nombre pseudo aléatoire du 8 bits *
// ===============================================
unsigned char get_rnd(unsigned char max_number)
{
  // -------------------------------------
  // * Declaration des variables locales *
  // -------------------------------------
  unsigned char valeur_genere = 0;
  unsigned char bc_time;    
  
  // ----------------------------------
  // * Boucle de génération aléatoire *
  // ----------------------------------
  do
  {
    for (bc_time=0;bc_time<(get_timer_a()&256);bc_time++)
  //  for (bc_time=0;bc_time<PEEK(0xDC08)&&16;bc_time++)
    {
      POKE(0xD40E,0xFF);
      POKE(0xD40F,0xFF);
      POKE(0xD412,0x80);
      valeur_genere = PEEK(0xD41B);
    }
  } while (valeur_genere > max_number);
  
  return valeur_genere;
  
}

// =================================================
// * Généré un nombre pseudo aléatoire sur 16 bits *
// =================================================
unsigned int get_rnd16(unsigned int max_number)
{
   // -------------------------------------
   // * Declaration des variables locales *
   // -------------------------------------
   unsigned char valeur_genere_a = 0;
   unsigned char valeur_genere_b = 0;
   unsigned char bc_time; 
  
  do
  {
    for (bc_time=0;bc_time<(get_timer_a()&256);bc_time++)
    {
      POKE(0xD40E,0xFF);
      POKE(0xD40F,0xFF);
      POKE(0xD412,0x80);
      valeur_genere_a = PEEK(0xD41B);
    }
    
    for (bc_time=0;bc_time<(get_timer_a()&256);bc_time++)
    {
      POKE(0xD40E,0xFF);
      POKE(0xD40F,0xFF);
      POKE(0xD412,0x80);
      valeur_genere_b = PEEK(0xD41B) + (valeur_genere_a<<8);
    }
 
  }while (valeur_genere_b > max_number);
  
  return valeur_genere_b;  
}
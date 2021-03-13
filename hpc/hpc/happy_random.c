 /**********************************************************
  ********              Happy Random               *********
  **********************************************************
  * Role ........... : Gestion aléatoire                   *
  * Auteur ......... : Jean Monos                          *
  * Modification ... : 13/03/2021                          *
  * Licence ........ : Creative Commons by-sa              *
  * Compilateur .... : cc65                                *
  **********************************************************/
  
  
// ====================
// * Fichier includes *
// ====================
#include <happyc64.h>

// ==============================================
// * Généré un nombre pseudo aléatoire du 8bits *
// ==============================================
unsigned char get_rnd(unsigned char max_number)
{
  unsigned char valeur_genere = 0;
  
  do
  {
    POKE(0xD40E,0xFF);
    POKE(0xD40F,0xFF);
    POKE(0xD412,0x80);
    valeur_genere = PEEK(0xD41B);
  } while (valeur_genere > max_number);
  
  return valeur_genere;
  
}

// =================================================
// * Généré un nombre pseudo aléatoire sur 16 bits *
// =================================================
unsigned int get_rnd16(unsigned int max_number)
{
   unsigned char valeur_genere_a = 0;
   unsigned char valeur_genere_b = 0;
  do
  {
    POKE(0xD40E,0xFF);
    POKE(0xD40F,0xFF);
    POKE(0xD412,0x80);
    valeur_genere_a = PEEK(0xD41B);
    
    POKE(0xD40E,0xFF);
    POKE(0xD40F,0xFF);
    POKE(0xD412,0x80);
    valeur_genere_b = PEEK(0xD41B) + (valeur_genere_a<<8) ;
 
 } while (valeur_genere_b > max_number);
  
  return valeur_genere_b;
  
}
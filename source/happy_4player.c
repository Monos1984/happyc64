 /**********************************************************
  ********              Happy 4 player          ************
  **********************************************************
  * Role ........... : Utilisation du 4 player interface   *
  * Auteur ......... : Jean Monos                          *
  * Modification ... : 28/09/2021                          *
  * Licence ........ : Creative Commons by-sa              *
  * Compilateur .... : cc65                                *
  **********************************************************/

// ====================
// * Fichier includes *
// ====================
#include <happyc64.h>

// ==========
// * Define *
// ==========
#define USERPORT_DATA 0xDD01
#define USERPORT_DDR 0xDD03

// =====================
// * Initiation du 4pi *
// =====================
void init_4pi()
{ 
 POKE(USERPORT_DDR,0b10000000);
 POKE(USERPORT_DATA,0);
}

// ====================
// * Lecture du joy 3 *
// ====================
unsigned char get_joystick_3()
{
  unsigned char temps;
  

  POKE (USERPORT_DATA,0x80);
  temps = PEEK(USERPORT_DATA)&0x1F;
  
  
  return temps;
}

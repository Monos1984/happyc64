 /**********************************************************
  ********              Happy Charset           ************
  **********************************************************
  * Role ........... :                      *
  * Auteur ......... : Jean Monos                          *
  * Modification ... : 13/03/2021                          *
  * Licence ........ : Creative Commons by-sa              *
  * Compilateur .... : cc65                                *
  **********************************************************/

// ====================
// * Fichier includes *
// ====================
#include <happyc64.h>
#include <string.h>


void copy_charset_rom()
{
  POKE(56334l,PEEK(56334l)&254); // Interrupts deactivate
  POKE(1,PEEK(1)&251);
  memcpy((char)0x8000,(char)53248l,256);
  

  POKE(56334l,PEEK(56334l)|1);
  set_vic_bank(VIC_BANK_3);
  set_adresse_screen_memory(SM_2000) ;
  set_location_character(10);
}
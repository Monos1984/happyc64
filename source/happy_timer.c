 /**********************************************************
  ********              Happy Timer            ************
  **********************************************************
  * Role ........... : Gestion du Timer                    *
  * Auteur ......... : Jean Monos                          *
  * Modification ... : 14/03/2021                          *
  * Licence ........ : Creative Commons by-sa              *
  * Compilateur .... : cc65                                *
  **********************************************************/

// ====================
// * Fichier includes *
// ====================
#include <happyc64.h>



// ===========
// * Timer A *
// ===========
unsigned int get_timer_a(void)
{
  unsigned int time = (PEEK(0xDC05)<<8 + PEEK( 0xDC04));
  return time;
  
}

// ===========
// * Timer B *
// ===========
unsigned int get_timer_b(void)
{
  unsigned int time = (PEEK(0xDC07)<<8 + PEEK( 0xDC06));
  return time;
  
}
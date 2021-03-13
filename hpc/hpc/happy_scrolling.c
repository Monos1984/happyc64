 /**********************************************************
  ********              Happy Scrolling            *********
  **********************************************************
  * Role ........... : Gestion du scrolling                *
  * Auteur ......... : Jean Monos                          *
  * Modification ... : 13/03/2021                          *
  * Licence ........ : Creative Commons by-sa              *
  * Compilateur .... : cc65                                *
  **********************************************************/
  
  
// ====================
// * Fichier includes *
// ====================
#include <happyc64.h>

// ========================
// * Scrolling Horizontal *
// ========================
void set_scrolling_horizontal(signed char Scroll_X)
{
  POKE(53270L,(PEEK(53270L)&248)+Scroll_X);
}

// ======================
// * Scrolling Vertical *
// ======================
void set_scrolling_vertical(unsigned char Scroll_Y)
{
  POKE(53265L,(PEEK(53265L)&248)+Scroll_Y);
}
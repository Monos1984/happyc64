 /**********************************************************
  ********              Happy IO                ************
  **********************************************************
  * Role ........... : Gestion des entrer                  *
  * Auteur ......... : Jean Monos                          *
  * Modification ... : 13/03/2021                          *
  * Licence ........ : Creative Commons by-sa              *
  * Compilateur .... : cc65                                *
  **********************************************************/

// ====================
// * Fichier includes *
// ====================
#include <happyc64.h>

// ==================================
// * Attendre l'appuis d'une touche *
// ==================================
/*
 La boucle key_empty utile pour le mode bloc text et wait key !!!
*/
void wait_key(unsigned char id_key)
{
  if (id_key==KEY_EMPTY)
  {
    while(get_keyboard_key() ==KEY_EMPTY)
    {
      wait_vbl();
    }
  }
  else
  {
    while(get_keyboard_key() !=id_key)
    {
      wait_vbl();
    }
  }
}


void wait_key_release(unsigned char id_key)
{
  while(get_keyboard_key()!=id_key)
  {
    wait_vbl();
  }
  
  while(get_keyboard_key()!=KEY_EMPTY)
  {
    wait_vbl();
  }
  
}
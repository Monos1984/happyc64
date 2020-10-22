/******************************************************
********              charset exemple     *************
*******************************************************
* Role ........... : exemple pour poser un charset    *
* Auteur ......... : Jean Monos                       *
* Version ........ : V 2.0.0.0                        *
* Modification ... : 22/10/2020                       *
* Licence ........ : Creative Commons by-sa           *
* Compilateur .... : cc65                             *
*******************************************************/

#include <happyc64.h>

// ===================
//  * Data des tiles *
//  ==================
unsigned char data_tiles[]=
{
 // Tiles 0
 0,0,0,0,0,0,0,0,
 // Tiles 1
 255,129,129,129,129,129,129,255 
   
};


// ======================
// * La fonction main() *
// ======================
void main()
{

  SCREEN_OFF;    // L'écran est désactivé.
  set_loram_ram(); // Desactivation de la Rom Basic. 
  set_location_character(2); // La lecture des paterns se fait à l'adresse $0800
  set_data_character(0x0800,data_tiles,2); // Mise en mémoire des tiles à l'adresse $0800
  cls(0); // On efface l'écran avec le patern numero 0 des tiles.
  draw_full_character(10,12,1,5); // On affiche le tile 1, à la position 10-12 avec la couleur numero 5.
  wait_vbl(); // on attend le début du Vblank.
  SCREEN_ON; // On active l'écran.
  
  // -----------------------------------------------------------------
  //  * Boucle infini pour stoper le programme et voir le résultat ! *
  // -----------------------------------------------------------------
  while(1)
  {
    
  }
  
  
  
}
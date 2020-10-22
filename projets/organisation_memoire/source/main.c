/******************************************************
********             Organisation Memoire *************
*******************************************************
* Role ........... : exemple organisation memoire     *
* Auteur ......... : Jean Monos                       *
* Version ........ : V 1.0.0.0                        *
* Modification ... : 08/09/2020                       *
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
  
  // =================================
  // * Configuration du Commodore 64 *
  // =================================
  
  set_loram_ram(); // Desactivation de la Rom Basic. 
  set_vic_bank(1); // Deplacement du vic_bank en $8000
  set_adresse_screen_memory(0); // Lecture du screen_memory à l'offet $0 ($8000)
  set_location_character(2); // La lecture des paterns se fait à offset $0800($8800)
  
  /*
    Vous pouvez placer vos sprites a partir de l'adresse $9000 (pointeur 144).
    par pas de 64 octets ! (Adresse vic + 64*pointeur).
  */
  
  
  // ===================================
  // * Chargement des pattern en $8800 *
  // ===================================
  set_data_character(0x8800,data_tiles,2); // Mise en mémoire des tiles à l'adresse $8800

  cls(0); // Effacement de l'écran
  
  // ======================================================================
  // * Exemple Affichage d'un charset avec mise à jour de la color screen *
  // ======================================================================
    draw_full_character(10,12,1,5); // On affiche le tile 1, à la position 10-12 avec la couleur numero 5.


  SCREEN_ON; // On active l'écran.
  
  // -----------------------------------------------------------------
  //  * Boucle infini pour stoper le programme et voir le résultat ! *
  // -----------------------------------------------------------------
  while(1)
  {
    wait_vbl(); // on attend le début du Vblank.
  }
  
  
  
}
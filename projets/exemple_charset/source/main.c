/**************************************************
 *                     Happy C64                  *
 * ---------------------------------------------- * 
 *                     Exemple 1                  *
 * ---------------------------------------------- *
 * Afficher un charset avec deplacement du VIC II *
 **************************************************/
 
// ===================
// * Fichier include *
// ===================
#include <happyc64.h>

// ======================
// * Tableau de pattern *
// ======================
unsigned char charset_pattern[]=
{
  // -------------
  // * Pattern 0 *
  // -------------
  0,0,0,0,0,0,0,0,
  
  // -------------
  // * Pattern 1 *
  // -------------
  0b11111111,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b11111111,
};

// ======================
// * La fonction main() *
// ======================
void main()
{
  // ----------------------------------
  // * Deplacement du VIC II en $8000 *
  // ----------------------------------
  set_vic_bank(VIC_BANK_2);
  
  // -------------------------------------------------------
  // * Deplacement sur screen memory a l'offet 0 du vic II *
  // -------------------------------------------------------
  set_adresse_screen_memory(SM_0);
  
  // ------------------------------------------------------------------
  // * Deplacement du pointeur de tiles après le screen memory : $800 *
  // ------------------------------------------------------------------
  set_location_character(2);
  
  // ----------------------------------
  // * Copier les 2 patterns en $8800 *
  // ----------------------------------
  set_data_character(0x8800,charset_pattern,2);
  
  // ----------------------------------
  // * Effacer l'ecran avec le tile 0 *
  // ----------------------------------
  cls(0);
  
  // ------------------------------------------
  // * Modifier le fond avec la couleur noire *
  // ------------------------------------------
  set_color_background (C_BLACK);
  
  // -------------------------------------------
  // * Modifier le cadre avec la couleur grise *
  // -------------------------------------------
  set_color_border(C_GREY);
    
  // --------------------------------
  // * Afficher le tiles 1 en bleu  *
  // --------------------------------
  draw_full_character(0,0,1,C_BLUE);
    
  // ------------------------
  // * Activation du VIC II *
  // ------------------------
  SCREEN_ON;

  // ------------------------------------------
  //  * Boucle infini pour voir le résultat ! *
  // ------------------------------------------
  while(1)
  {
    wait_vbl(); // on attend le début du Vblank.
  } // end while
    
} // end main
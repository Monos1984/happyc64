/**************************************************
 *                     Happy C64                  *
 * ---------------------------------------------- * 
 *                   Texte Engine                 *
 * ---------------------------------------------- *
 * Afficher du texte avec Happy C64               *
 **************************************************/
 
// ===================
// * Fichier include *
// ===================
#include <happyc64.h>

// =============================
// * Declaration des variables *
// =============================
unsigned char v1 = 169;
unsigned char tab_text[]="Bonjour";

// ======================
// * La fonction main() *
// ======================
void main()
{
  // --------------------------------
  // * Desactiver l'affichage video *
  // --------------------------------
  SCREEN_OFF;
  
  
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
    
  // ------------------------
  // * Chargement des fonts *
  // ------------------------
  load_file("c64,s",(void*)0x8800,8);
 
  // ---------------------------------------
  // * Initiation du text engine en tile 0 *
  // ---------------------------------------
  set_text_pointer(0);
 
  // ------------------------
  // * Activation du VIC II *
  // ------------------------
  SCREEN_ON;

  // ---------------------------
  // * Afficher un text simple *
  // ---------------------------
  draw_text(0,0,"Hello World",C_YELLOW,0);

  // ----------------------------------
  // * Attendre une touche du clavier *
  // ----------------------------------
  wait_key(KEY_ANY);

  // ----------------------------------------------------------------
  // * Afficher un text simple en mode d'affichage lettre par lettre *
  // -----------------------------------------------------------------
  draw_text(0,1,"Affichage Lettre par Lettre",C_YELLOW,5);

    // ----------------------------------
  // * Attendre une touche du clavier *
  // ----------------------------------
  wait_key(KEY_ANY);

  // ----------------------------------------------------------------
  // * Afficher un text simple d'un tableau *
  // -----------------------------------------------------------------
  draw_text(0,2,tab_text,C_YELLOW,5);

  // ----------------------------------
  // * Attendre une touche du clavier *
  // ----------------------------------
  wait_key(KEY_ANY);
    
  // ------------------------------
  // * Afficher une valeur 8 bits *
  // ------------------------------
  draw_text_value_8(0,3,10,C_YELLOW);

  // ----------------------------------
  // * Attendre une touche du clavier *
  // ----------------------------------
  wait_key(KEY_ANY);

  // ---------------------------------------------
  // * Afficher une valeur 8 bits d'une variable *
  // ---------------------------------------------
  draw_text_value_8(0,4,v1,C_YELLOW);

  // ------------------------------------------
  //  * Boucle infini pour voir le résultat ! *
  // ------------------------------------------
  while(1)
  {
    wait_vbl(); // on attend le début du Vblank.
  } // end while
    
} // end main
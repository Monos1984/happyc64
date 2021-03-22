/**************************************************
 *                     Happy C64                  *
 * ---------------------------------------------- * 
 *                   Peek et Poke                 *
 * ---------------------------------------------- *
 * Lire et écrire dans la mémoire du c64          *
 **************************************************/
 
// ===================
// * Fichier include *
// ===================
#include <happyc64.h>

// =============================
// * Declaration des variables *
// =============================
unsigned char v1,octet_1,octet_2; 
unsigned int  v2;

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

  // ======================
  // * Valeur sur 1 octet *
  // ======================
  /*
    PEEK et POKE permet de travailler sur 1 octet. (8 bits)
  */

  // --------------------------------
  // * Entrer une valeur en mémoire *
  // --------------------------------
  POKE(0x400,69); // POKE(Adresse,value)

  // ----------------------------------
  // * Memoriser la valeur en mémoire *
  // ----------------------------------
  v1 = PEEK(0x400); // PEEK(adresse)
  
  // ------------------------------
  // * Afficher le contenue de v1 *
  // ------------------------------
  draw_text(1,1,"Valeur de V1 (1 octet) (unsigned char)",C_RED,0);
  draw_text_value_8(1,2,v1,C_YELLOW);

  // =============================
  // * Valeur sur 2 octets (int) *
  // =============================
  /*
    POKEW et PEEKW permet de travailler sur un mots (ou word) donc 2 octets (16 bits) sur commodore 64)
  */
  
  
  // --------------------------------
  // * Entrer une valeur en mémoire *
  // --------------------------------
  POKEW(0x400,28000);
  
  // ----------------------------------
  // * Memoriser la valeur en mémoire *
  // ----------------------------------
  v2 = PEEKW(0x400); // PEEK(adresse)

  // ------------------------------
  // * Afficher le contenue de v2 *
  // ------------------------------
  draw_text(1,4,"Valeur de V2 (2 octets) (unsigned int)",C_RED,0);
  draw_text_value_16(1,5,v2,C_YELLOW);
  
  // ===================================================
  // * Affichage des deux octets qui représente le int *
  // ===================================================

  /*
    Pour recomposer la valeur sur 16 bits :
    - (octet_2 * 256) + octet_1  
  */

  octet_1 = PEEK(0x400);
  octet_2 = PEEK(0x401);
  
  draw_text(1,7,"octet 1 et octet 2 sur le unsigned int",C_RED,0);
  draw_text_value_8(1,8,octet_1,C_YELLOW);
  draw_text_value_8(1,9,octet_2,C_YELLOW);


  draw_text(1,11,"Formule :",C_RED,0);
  draw_text(1,12,"(octet_2 * 256) + octet_1",C_RED,0);
  
  // ------------------------------------------
  //  * Boucle infini pour voir le résultat ! *
  // ------------------------------------------
  while(1)
  {
    wait_vbl(); // on attend le début du Vblank.
  } // end while
    
} // end main
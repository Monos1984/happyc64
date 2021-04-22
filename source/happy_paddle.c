 /**********************************************************
  ********              Happy paddle            ************
  **********************************************************
  * Role ........... : Gestion du paddle                   *
  * Auteur ......... : Jean Monos                          *
  * Modification ... : 14/04/2021                          *
  * Licence ........ : Creative Commons by-sa              *
  * Compilateur .... : cc65                                *
  **********************************************************/

// ====================
// * Fichier includes *
// ====================
#include <happyc64.h>


// ===================
// * get_paddle_fire *
// ===================
unsigned char get_paddle_fire(unsigned char port,unsigned char id_paddle)
{
  // -----------------------------
  // * Declaration des variables *
  // -----------------------------
  unsigned char buffer_value;
  
 
  // -------------------------
  // * Desactiver le clavier *
  // -------------------------
  POKE(0xDC02,224);
  
  
  // ---------------------
  // Recuperer la valeur *
  // ---------------------
  if (port == 1)
  {
   buffer_value = PEEK(0xDC01);  
  }
  else if (port == 2)
  {
   buffer_value = PEEK(0xDC00);  
  }
  
  
  // --------------------------
  // * Formatage de la valeur *
  // --------------------------
  if (id_paddle == 1)
  {
    buffer_value = (buffer_value & 0b00000100)>>2;  
  }
  else if (id_paddle == 2)
  {
   buffer_value = (buffer_value & 0b00001000)>>3;  
  }
  
  
  
  // -------------------------
  // * Activation du clavier *
  // -------------------------
  POKE(0xDC02,255);
  
  // -----------------------
  // * retourner la valeur *
  // -----------------------
  return (buffer_value);  
}




// ==============
// * get_paddle *
// ==============
unsigned char get_paddle(unsigned char port,unsigned char id_paddle)
{
  // -----------------------------
  // * Declaration des variables *
  // -----------------------------
  unsigned char buffer_value;
  
  // ---------------------------
  // * Choix du port du paddle *
  // ---------------------------
    
  if (port == 1)
  {
    POKE(0xDC00,0b01000000);
  }
  else if (port == 2)
  {
    POKE(0xDC00,0b10000000);   
  }
    
  // -------------------------
  // * Desactiver le clavier *
  // -------------------------
  POKE(0xDC02,224);
  
  
  // ---------------------
  // Recuperer la valeur *
  // ---------------------
  if (id_paddle == 1)
  {
   buffer_value = PEEK(0xD419);  
  }
  else if (id_paddle == 2)
  {
   buffer_value = PEEK(0xD41A);  
  }
  
  // -------------------------
  // * Activation du clavier *
  // -------------------------
  POKE(0xDC02,255);
  
  // -----------------------
  // * retourner la valeur *
  // -----------------------
  return buffer_value;
  
}
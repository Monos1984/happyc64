 /**********************************************************
  ********              Happy RLE               ************
  **********************************************************
  * Role ........... : Gestion du cryptage RLE             *
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

// =====================
// * Decompression RLE *
// =====================
void rle_decrompression(unsigned int source,unsigned int destination)
{
  unsigned char duplicate,valeur;
  unsigned int offset,offset_cible,adr_source;
  offset = 0;
  offset_cible = 0;
   
  while(PEEK(source+(offset<<1))!=0)
  {
    adr_source = source+(offset<<1);
    duplicate = PEEK(adr_source);
    valeur = PEEK(adr_source+1);
    
    memset((char*)destination+offset_cible,valeur,duplicate);
    offset_cible = offset_cible + duplicate;   
    offset++;     
  }
    
}

// ===================
// * Compression RLE *
// ===================
void rle_compression(unsigned int source,unsigned int destination,unsigned int size)
{
  // -----------------------------
  // * Declaration des variables *
  // -----------------------------
  unsigned char offset_source,offset_cible;
  unsigned char read_value,nb_value,buffer_value;
  // ---------------------------
  // * Initation des variables *
  // ---------------------------
  
  offset_cible = 0;
  read_value = 0;
  
  // ------------------------
  // * Initiation du 1er octet *
  // ------------------------
  offset_source = 1;
  nb_value = 1;
  buffer_value = PEEK(source);
  // ------------------------
  // * Boucle de la routine *
  // ------------------------
  while (offset_source < size)
  {
    // ----------------------
    // * Lecture de l'octet *
    // ----------------------
    read_value = PEEK(source+offset_source);
    
    // -----------------------------------------------
    // * Test de l'octet si elle identique au buffer *
    // -----------------------------------------------
    if (buffer_value == read_value)
    {
      nb_value++;
    }
   
    // ---------------------------
    // * Octet non identique !!! *
    // ---------------------------
    else
    {
      // -----------------------------------------
      // * Ranger en mémoire les deux octets rle *
      // -----------------------------------------
      POKE(destination+offset_cible,nb_value);
      POKE(destination+offset_cible+1,buffer_value);
    
      // ---------------------------------
      // * Modifier l'offset de la cible *
      // ---------------------------------
      offset_cible = offset_cible +2;
    
      // ----------------------------------------------
      // * Mise en mémoire buffer de la valeur trouvé *
      // ----------------------------------------------
      buffer_value = read_value;
      
      // --------------------------
      // * Remise à 1 du nb_value *
      // --------------------------
      nb_value = 1;
    }
  
    // ---------------------------------------
    // * Modification de l'offset de lecture *
    // ---------------------------------------
    offset_source++;
  
  }
  // ------------------------------------------------
  // * Fin de la routine de compression, ajout du 0 *
  // ------------------------------------------------
  POKE(destination+offset_cible,nb_value);
  POKE(destination+offset_cible+1,buffer_value);
  POKE(offset_cible+destination+2,0);
  
}
 /**********************************************************
  ********              Happy Raster            ************
  **********************************************************
  * Role ........... : Gestion du raster                   *
  * Auteur ......... : Jean Monos                          *
  * Modification ... : 13/03/2021                          *
  * Licence ........ : Creative Commons by-sa              *
  * Compilateur .... : cc65                                *
  **********************************************************/

// ====================
// * Fichier includes *
// ====================
#include <happyc64.h>

// =====================
// * init interruption *
// =====================
void init_adr_irq(unsigned int adresse)
{    
  POKE(REG_ADR_HAUT_IRQ,(adresse & 0b1111111100000000)>>8);
  POKE(REG_ADR_BASS_IRQ,(adresse & 0b0000000011111111)   );  
}
  
// ================================
// * Recuperer la ligne du raster *
// ================================
unsigned int get_raster(void)
{
  unsigned int raster;
  
  raster = (PEEK(0xD011)&1)<<8+PEEK(0xD012);
  return raster;     
}

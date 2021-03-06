 /**********************************************************
  ********              Happy Bitmap            ************
  **********************************************************
  * Role ........... : Gestion du mode bitmap              *
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

// ===================  
// * Variable extern *
// ===================
extern unsigned int  G_pointeur_pattern;
extern unsigned int  G_adr_tilemap;
extern unsigned char buffer_vic_bank;
  
// ==============
// * draw pixel *
// ==============
void draw_pixel(unsigned int px, unsigned int py)
{
    unsigned int adr,py2;
    py2 = (py>>3);
    adr=(buffer_vic_bank<<14)+G_pointeur_pattern+((py2)<<8)+((py2)<<6) +((px>>3)<<3)+(py&7);  
    POKE(adr,PEEK(adr)|pow(2,7-(px&7)  ));
}

// ========================
// * Set_bitmap_color_map *
// ========================
void set_bitmap_color_map(unsigned char px, unsigned char py, unsigned char color_ink,unsigned char color_background)
{
  POKE(G_adr_tilemap+py*40+px,color_ink*16+color_background);
}
  
// =============
// * Puissance *
// =============
unsigned int pow(unsigned int value, unsigned int power)
{
  unsigned int resultat,i;
  resultat = 1;
  
 if (power > 0)
 {
  for (i=1;i<power+1;i++)
  {
    resultat = resultat * value;
  } 
 
 }
 else
 {
  resultat = 1;
 }
  return resultat;
}

// ========================
// * Effacer la color ram *
// ========================
void cls_bitmap_color_ram(unsigned char ink_color,unsigned char background_color)
{
   memset((char*)G_adr_tilemap,ink_color*16+background_color,0x400);
}

// ==============
// * CLS Bitmap *
// ==============
void cls_bitmap()
{
  memset((char*)((buffer_vic_bank<<14)+G_pointeur_pattern),0,8000);
}
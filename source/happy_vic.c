 /**********************************************************
  ********              Happy VIC               ************
  **********************************************************
  * Role ........... : Gestion du vic                      *
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
// * Variable Extern *
// ===================
extern unsigned int  G_adr_tilemap;
extern unsigned int  G_pointeur_pattern;
extern unsigned char buffer_vic_bank;
extern unsigned char buffer_id_screen;
extern const unsigned int adr_case[];

// ====================================
// * Charger un pattern en mémoire    *
// ====================================
void set_data_character(unsigned int memory_adresse,unsigned char *data_character,unsigned char nb_pattern)
{
  unsigned int nb_octet = nb_pattern<<3;  
  memcpy((char*)memory_adresse,(char*)data_character,nb_octet);  
}

// =========================================
// ** Afficher un character à l'ecran     **
// =========================================
void draw_full_character(unsigned char position_x, unsigned char position_y, unsigned char id_character, unsigned char color_id)
{
  // Position Y * 40 + position X
  unsigned int calcule_adresse;
  // calcule_adresse = (position_y<<5) + (position_y<<3)+position_x;
  
  calcule_adresse=adr_case[position_y]+position_x;
  
  POKE(G_adr_tilemap+calcule_adresse,id_character);
  POKE(REG_COLOR_MAP+calcule_adresse,color_id);
}

// ====================
// * Afficher un tile *
// ====================
void draw_character(unsigned char position_x, unsigned char position_y, unsigned char id_character)
{
  POKE(G_adr_tilemap+position_x+adr_case[position_y],id_character);
}

void draw_character_line_H(unsigned char px,unsigned char py,unsigned char size, unsigned char id_character,unsigned char color)
{ 
  unsigned int offset_start = py*40+px;
  memset((char*)REG_COLOR_MAP+offset_start,color,size);
  memset((char*)G_adr_tilemap+offset_start,id_character,size);
}

// ===========================================================
// * Afficher une ligne avec le même character en Vertical   *
// ===========================================================
void draw_character_line_V(unsigned char px,unsigned char py,unsigned char size, unsigned char id_character,unsigned char color)
{
  unsigned char i;
  for (i=0;i<size;i++)
  {
    draw_full_character(px,py+i,id_character,color); 
  }
  
}


// =======================================
// * Configurer la couleur de la cellule *
// =======================================
void set_color_map(unsigned char position_x, unsigned char position_y, unsigned char color_id)
{ 
  POKE(REG_COLOR_MAP+position_x+adr_case[position_y],color_id);
}

// =======================================
// ** Modifier la couleur de la bordure **
// =======================================
void set_color_border(unsigned char color_id)
{
  POKE(REG_COLOR_BORDER,color_id);
}

// =======================================
// ** Modifier la couleur du fond       **
// =======================================
void set_color_background(unsigned char color_id)
{
  POKE(REG_COLOR_BACKGROUND,color_id);
}

// =========================================
// ** Modifier la couleur du background_1 **
// =========================================
void set_color_background_1(unsigned char color_id)
{
  POKE(REG_COLOR_BACKGROUND_1 ,color_id);
}

// =========================================
// ** Modifier la couleur du background_2 **
// =========================================
void set_color_background_2(unsigned char color_id)
{
  POKE(REG_COLOR_BACKGROUND_2 ,color_id);
}

// =========================================
// ** Modifier la couleur du background_3 **
// =========================================
void set_color_background_3(unsigned char color_id)
{
  POKE(REG_COLOR_BACKGROUND_3 ,color_id);
}

// =====================
// ** Effacer l'écran **
// =====================
void cls(unsigned char id_tiles)
{ 
  memset((char*)G_adr_tilemap,id_tiles,1000); 
}
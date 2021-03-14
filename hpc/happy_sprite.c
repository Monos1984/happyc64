 /**********************************************************
  ********              Happy Sprite            ************
  **********************************************************
  * Role ........... : Routine de sprite                   *
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

// ===============================
// * Copier des datas en mémoire *
// ===============================
void set_sprite_data(unsigned int adr_cible,unsigned char *adr_data,unsigned char nb_sprite)
{
  unsigned int nb_octet = nb_sprite<<6;
  memcpy((char*)adr_cible,(char*)adr_data,nb_octet);  
}

// ====================================
// * Configurer le pointeur de sprite * 
// ====================================
void set_pointers_sprite(unsigned char id_sprite,unsigned char value)
{
  POKE(G_adr_tilemap+1016+id_sprite,value);
}

// =====================
// * Activer un sprite *
// =====================
void show_sprite(unsigned char id_sprite)
{	
  POKE(REG_SHOW_SPRITE,PEEK(REG_SHOW_SPRITE)|(1<<(id_sprite)));	
}

// ========================
// * Desactiver un sprite *
// ========================
void hide_sprite(unsigned char id_sprite)
{	
  POKE(REG_SHOW_SPRITE,(PEEK(REG_SHOW_SPRITE) &255-(1<<(id_sprite)) ));	
}

// =================================
// * Position des sprites avec MSB *
// =================================
void draw_sprite(unsigned char id_sprite,unsigned int position_x,unsigned char position_y)
{
  // -------------------
  // * Variable locale *
  // -------------------
	unsigned char position_x_finale ;
	
  // --------------------------------
  // * Tester la limitation d'écran *
  // --------------------------------
	if (position_x>320)
	{
    position_x=320;
  }
	
  // ------------------------------------------
  // * Calcule d'activation du bit msb ou non *
  // ------------------------------------------
  if(position_x>255)
	{
		position_x_finale = (unsigned char)(position_x-256);
		POKE(R_VIC+16,PEEK(R_VIC+16)|(1<<(id_sprite)));			
  }
	else
	{
		position_x_finale=(unsigned char)(position_x);
		POKE(R_VIC+16,PEEK(R_VIC+16)&(255-(1<<(id_sprite))));
  }
	
  // --------------------------
  // * Poker les datas en ram *
  // --------------------------
	POKE(R_VIC+(id_sprite<<1),position_x_finale);	
	POKE(R_VIC+(id_sprite<<1)+1,position_y);
}

// ==============================================
// * Activer le mode multicolore pour un sprite *
// ==============================================
void set_sprite_multicolore_on(unsigned char id_sprite)
{	
  POKE(0xD01C,PEEK(0xD01C)|(1<<(id_sprite)));	
}

// ==================================================
// * Desactiver le mode multicolore pour un sprite  *
// ==================================================
void set_sprite_multicolore_off(unsigned char id_sprite)
{	
  POKE(0xD01C,PEEK(0xD01C)&(255-(1<<(id_sprite))));	
}

// ======================================
// * Activer le double height du sprite *
// ======================================
void double_height_sprite_on(unsigned char id_sprite)
{	
  POKE(0xD017,PEEK(0xD017)|(1<<(id_sprite)));	
}

// =========================================
// * Desactiver le double height du sprite *
// =========================================
void double_height_sprite_off(unsigned char id_sprite)
{	
  POKE(0xD017,PEEK(0xD017)&(255-(1<<(id_sprite))));	
}

// =====================================
// * Activer le double width du sprite *
// =====================================
void double_width_sprite_on(unsigned char id_sprite)
{	
  POKE(0xD01D,PEEK(0xD01D)|(1<<(id_sprite)));	
}

// ========================================
// * Desactiver le double width du sprite *
// ========================================
void double_width_sprite_off(unsigned char id_sprite)
{	
  POKE(0xD01D,PEEK(0xD01D)&(255-(1<<(id_sprite))));	
}

// ===================================
// * Activer la priorité des sprites *
// ===================================
void  sprite_priority_on(unsigned char id_sprite)
{	
  POKE(0xD01B,PEEK(0xD01B)|(1<<(id_sprite)));	
}

// =====================================
// * Desactiver la priorité des sprites *
// ======================================
void sprite_priority_off(unsigned char id_sprite)
{	
  POKE(0xD01B,PEEK(0xD01B)&(255-(1<<(id_sprite))));	
}

// =======================
// * Couleur des sprites *
// =======================
void  set_color_sprite(unsigned char id_sprite,unsigned char color_id)
{
	POKE(0xD027+id_sprite,color_id);	
}

// ============================================================
// * Configure le registre de couleur 1 du sprite du mode MCC * 
// ============================================================
void set_sprite_color_1(unsigned char color_id)
{
	POKE(0xD025,color_id);
}

// =============================================================
// * MConfigure le registre de couleur 2 du sprite du mode MCC *
// =============================================================
void  set_sprite_color_2(unsigned char  color_id)
{
	POKE(0xD026,color_id);
}

/******************************************************
********              Happy C64            *************
*******************************************************
* Role ........... : Entête du sdk                    *
* Auteur ......... : Jean Monos                       *
* Version ........ : V 0.0.3.3                        *
* Modification ... : 6/09/2020                       *
* Licence ........ : Creative Commons by-sa           *
* Compilateur .... : cc65                             *
*******************************************************/


#include <happyc64.h>
#include <cbm.h>
#include <string.h>
// ===============================
// ** Variable Global de Hapy64 **
// ===============================
unsigned int G_adr_tilemap = 1024l;

// ====================
// ** NTSC(0)/PAL(1) **
// ====================
unsigned char get_system()
{
  return PEEK(0x2A6);
}

// =======================================
// ** Modifier la couleur de la bordure **
// =======================================
// * color_id : Numeros de la couleur    *
// =======================================
void set_color_border(unsigned char color_id)
{
		POKE(REG_COLOR_BORDER,color_id);
}

// =======================================
// ** Modifier la couleur du fond       **
// =======================================
// * color_id : Numeros de la couleur    *
// =======================================
void set_color_background(unsigned char color_id)
{
		POKE(REG_COLOR_BACKGROUND,color_id);
}


// =========================================
// ** Modifier la couleur du background_1 **
// =========================================
// * color_id : Numeros de la couleur      *
// =========================================
void set_color_background_1(unsigned char color_id)
{
		POKE(REG_COLOR_BACKGROUND_1 ,color_id);
}

// =========================================
// ** Modifier la couleur du background_2 **
// =========================================
// * color_id : Numeros de la couleur      *
// =========================================
void set_color_background_2(unsigned char color_id)
{
		POKE(REG_COLOR_BACKGROUND_2 ,color_id);
}


// =====================
// ** Effacer l'écran **
// =====================
void cls(unsigned char id_tiles)
{
 

 

 unsigned int index;
  for (index = 0; index <1000; index++)
  {
    POKE(G_adr_tilemap+index,id_tiles);
  }

  
}

// =======================================
// ** Afficher un charset à l'ecran     **
// =======================================

void draw_full_charset(unsigned char position_x, unsigned char position_y, unsigned char id_charset, unsigned char color_id)
{
  unsigned int calcule_adresse;
  calcule_adresse = (position_y<<5) + (position_y<<3)+position_x;
    
		POKE(G_adr_tilemap+calcule_adresse,id_charset);
    POKE(REG_COLOR_MAP+calcule_adresse,color_id);
}


void draw_charset(unsigned char position_x, unsigned char position_y, unsigned char id_charset)
{
    
		POKE(G_adr_tilemap+position_x+40*position_y,id_charset);
  
}


void set_color_map(unsigned char position_x, unsigned char position_y, unsigned char color_id)
{
    		
    POKE(REG_COLOR_MAP+position_x+40*position_y,color_id);
}


// =======================================
// ** Selectionner la Bank du vic 2     **
// =======================================
void set_vic_bank(unsigned char id_bank)
{
  POKE (56578L,PEEK(56578L)|3);               // Mode Outputs
  POKE(REG_CIA2,(PEEK(REG_CIA2)& 252) | id_bank); // Selection de la bank.
  
}

// =================================================
// ** Selectionner l'adresse du screen memory     **
// =================================================
void set_adresse_screen_memory (unsigned char screen_memory_id_pointeur)
{
   POKE(53272L,(PEEK(53272L)& 15) | screen_memory_id_pointeur); // Selection de l'emplacement en fonction de l'id du pointeur.
   G_adr_tilemap = screen_memory_id_pointeur << 6; // Memorisation de l'adresse en dans la variable global G_adr_tilemap
}

// =================================================
// ** Récupéré l'adresse mémoire du screen memory **
// =================================================
/*
 int get_adresse_screen_memory()
{
  return G_adr_tilemap;
}*/

// ======================================
// ** Modifier l'emplacement des tiles **
// =======================================

void set_location_character(unsigned char id)
{
  POKE(53272L,(PEEK(53272L)& 240) | id); // Selection de la bank.
}


// ======================================
// ** Charger un pattern en mémoire    **
// ======================================

void load_pattern(unsigned int adr_cible,unsigned char *data_charset,unsigned char nb_pattern)
{
  unsigned int nb_octet = nb_pattern<<3;
      /* unsigned int i;
  

  for (i=0;i<nb_octet;i++)
  {    
    POKE(adr_cible+i,data_charset[i]);
  }  
     */
  


  memcpy((char*)adr_cible,(char*)data_charset,nb_octet);
  
}

  // ====================================
  // - Parametrer le pointeur de sprite - 
  // ====================================
  void set_pointeurs_sprites(unsigned char id_sprite,unsigned char id_pointeur)
  {
    POKE(G_adr_tilemap+1016+id_sprite,id_pointeur);
  }

  // =====================
  // - Activer un sprite -
  // =====================
  void show_sprite(unsigned char id_sprite)
{	
	 POKE(REG_SHOW_SPRITE,PEEK(REG_SHOW_SPRITE)|(1<<(id_sprite)));	
}

// ========================
// - Desactiver un sprite -
// ========================
void hide_sprite(unsigned char id_sprite)
{	
 POKE(REG_SHOW_SPRITE,(PEEK(REG_SHOW_SPRITE) &255-(1<<(id_sprite)) ));	
}

// =======================================
// ** Position des sprites avec MSB     **
// =======================================
// * id_sprite: Numeros du sprite        *
// * position_x :Sa position x           *
// * position_x :Sa position y           *
// ***************************************
void draw_sprite(unsigned char id_sprite,unsigned int position_x,unsigned char position_y)
{
	unsigned char position_x_finale ;
	
	if (position_x>320)
	{
	position_x=320;
  }
	
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
	
	POKE(R_VIC+(id_sprite<<1),position_x_finale);	
	POKE(R_VIC+(id_sprite<<1)+1,position_y);
}




// ****************************************************
// ** Activer le mode multicolore pour un sprite     **
// ****************************************************
// * id_sprite: Numero du sprite                      *
// ****************************************************
void set_sprite_multicolore_on(unsigned char id_sprite)
{	
	 POKE(0xD01C,PEEK(0xD01C)|(1<<(id_sprite)));	
}

// ****************************************************
// ** Desactiver le mode multicolore pour un sprite  **
// ****************************************************
// * id_sprite: Numero du sprite                      *
// ****************************************************
void set_sprite_multicolore_off(unsigned char id_sprite)
{	
	 POKE(0xD01C,PEEK(0xD01C)&(255-(1<<(id_sprite))));	
}

// ****************************************************
// ** Activer le double height du sprite             **
// ****************************************************
// * id_sprite: Numero du sprite                      *
// ****************************************************
void double_height_sprite_on(unsigned char id_sprite)
{	
	 POKE(0xD017,PEEK(0xD017)|(1<<(id_sprite)));	
}

// ****************************************************
// ** Desactiver le double height du sprite          **
// ****************************************************
// * id_sprite: Numero du sprite                      *
// ****************************************************
void double_height_sprite_off(unsigned char id_sprite)
{	
	 POKE(0xD017,PEEK(0xD017)&(255-(1<<(id_sprite))));	
}

// ****************************************************
// ** Activer le double height du sprite             **
// ****************************************************
// * id_sprite: Numero du sprite                      *
// ****************************************************
void double_width_sprite_on(unsigned char id_sprite)
{	
	 POKE(0xD01D,PEEK(0xD01D)|(1<<(id_sprite)));	
}

// ****************************************************
// ** Desactiver le double height du sprite          **
// ****************************************************
// * id_sprite: Numero du sprite                      *
// ****************************************************
void double_width_sprite_off(unsigned char id_sprite)
{	
	 POKE(0xD01D,PEEK(0xD01D)&(255-(1<<(id_sprite))));	
}

// ****************************************************
// ** Activer la priorité des sprites                **
// ****************************************************
// * id_sprite: Numero du sprite                      *
// ****************************************************
void  sprite_priority_on(unsigned char id_sprite)
{	
	 POKE(0xD01B,PEEK(0xD01B)|(1<<(id_sprite)));	
}

// ****************************************************
// ** Desactiver la priorité des sprites             **
// ****************************************************
// * id_sprite: Numero du sprite                     *
// ********************************* *******************
void sprite_priority_off(unsigned char id_sprite)
{	
	 POKE(0xD01B,PEEK(0xD01B)&(255-(1<<(id_sprite))));	
}

// ***************************************
// ** Couleur des sprites               **
// ***************************************
// * id sprite: Numero du sprite         *
// * color_id : Numero de la couleur     *
// ***************************************
	
void  set_color_sprite(unsigned char id_sprite,unsigned char color_id)
{
	POKE(0xD027+id_sprite,color_id);	
}

// ************************************************************
// ** Modifie le registre de couleur 1 du sprite du mode MCC ** 
// ************************************************************
// * color id ..... : id de la couleur                        *
// ************************************************************
void set_sprite_color_1(unsigned char color_id)
{
	POKE(0xD025,color_id);
}

// ************************************************************
// ** Modifie le registre de couleur 1 du sprite du mode MCC ** 
// ************************************************************
// * color id ..... : id de la couleur                        *
// ************************************************************
void  set_sprite_color_2(unsigned char  color_id)
{
	POKE(0xD026,color_id);
}

// ************************************************************
// ** Copie d'un tableau de sprite                           ** 
// ************************************************************
// *                                                          *
// ************************************************************
void set_sprite_data(unsigned int adr_cible,unsigned char *adr_data,unsigned char nb_sprite)
{
  
  unsigned int nb_octet = nb_sprite<<6;
 
  /* unsigned int i;
  for (i=0;i<nb_octet;i++)
  {    
    POKE(adr_cible+i,adr_data[i]);
  }  
  */
    memcpy((char*)adr_cible,(char*)adr_data,nb_octet);
  
}


	// ------------------------
	// - Scrolling Horizontal -
	// ------------------------
	void set_scrolling_horizontal(signed char Scroll_X)
	{
		POKE(53270L,(PEEK(53270L)&248)+Scroll_X);
	}
	
	// ----------------------
	// - Scrolling Vertical -
	// ----------------------
	void set_scrolling_verticale(unsigned char Scroll_Y)
	{
		POKE(53265L,(PEEK(53265L)&248)+Scroll_Y);
	}


// -----------------
// - Jouer sun son -
// -----------------

  void set_sound (
                  unsigned char voice,
                  unsigned char lb_freq,
                  unsigned char hb_freq,
                  unsigned char lb_pulse,
                  unsigned char hb_pulse,
                  unsigned char waveforme,
                  unsigned char attaque_decay,
                  unsigned char sustain_release            
                 )
   
  {
   

   
    POKE(R_SID+voice,lb_freq);
    POKE(R_SID+voice+1,hb_freq);
    POKE(R_SID+voice+2,lb_pulse);
    POKE(R_SID+voice+3,hb_pulse);
    POKE(R_SID+voice+4,waveforme);
    POKE(R_SID+voice+5,attaque_decay);
    POKE(R_SID+voice+6,sustain_release);
           
  }
  
 // ----------------------
 // - Modifier le volume -
 // ---------------------- 
 void set_volume(unsigned char volume)
 {
   POKE(R_SID+24,volume);
 }
  
  
  unsigned int get_timer_a(void)
 {
  unsigned int time = (PEEK(0xDC06)<<8 + PEEK( 0xDC04));
   return time;

 }
 
   unsigned int get_timer_b(void)
 {
  unsigned int time = (PEEK(0xDC06)<<8 + PEEK( 0xDC04));
   return time;

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
  
  
  // ===================
  // * Attendre le VBL *
  // ===================
 void wait_vbl(void)
  {
    
    waitvsync();

   

 
  }

  
  // ==============================================
  // * Généré un nombre pseudo aléatoire du 8bits *
  // ==============================================
  unsigned char get_rnd(unsigned char nombre_max)
  {
    unsigned char valeur_genere = 0;
     do
     {
      POKE(0xD40E,0xFF);
      POKE(0xD40F,0xFF);
      POKE(0xD412,0x80);
      valeur_genere = PEEK(0xD41B);
     } while (valeur_genere > nombre_max);
     
     return valeur_genere;
    
  }
 
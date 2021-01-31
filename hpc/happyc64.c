 /********************************************************
  ********              Happy C64            ************
  *******************************************************
  * Role ........... : Entête du sdk                    *
  * Auteur ......... : Jean Monos                       *
  * Version ........ : V 0.1.5.0                        *
  * Modification ... : 31/01/2021                       *
  * Licence ........ : Creative Commons by-sa           *
  * Compilateur .... : cc65                             *
  ******************************************************* */ 

#include <happyc64.h>
#include <cbm.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>


// ===============================
// ** Variable Global de Hapy64 **
// ===============================
unsigned int  G_adr_tilemap = 1024l;
unsigned int  G_pointeur_pattern;
unsigned char buffer_vic_bank = 0;
unsigned char buffer_id_screen = 16;
unsigned char text_pointeur=0;

unsigned char buffer_8[8];
unsigned char buffer_16[16];

// =================
// * Data case adr *
// =================
const unsigned int adr_case[]=
{
0,40,80,120,160,200,240,280,320,360,
400,440,480,520,560,600,640,680,720,760,
800,840,880,920,960,
};

/*
  
  // =====================
  // * init interruption *
  // =====================
  void init_adr_irq(unsigned int adresse)
  {
  
  
  POKE(REG_ADR_HAUT_IRQ,(adresse & 0b1111111100000000)>>8);
  POKE(REG_ADR_BASS_IRQ,(adresse & 0b0000000011111111)   );
  
  }
  
*/


// =====================================================
// ** void set_pointeur_text(unsigned char pointeur); **
// =====================================================
void set_text_pointer(unsigned char pointer)
{
  text_pointeur = pointer;
}


void draw_text_value_8 (unsigned char px,unsigned char py,unsigned char value,unsigned char color)
{
  sprintf(buffer_8,"%d",value);
  draw_text( px,py,buffer_8,color,0);
}


void draw_text_value_16 (unsigned char px,unsigned char py,  unsigned int value,unsigned char color)
{
  sprintf(buffer_16,"%u",value);
  draw_text( px,py,buffer_16,color,0);
}


void draw_bloc_text(unsigned char px,unsigned char py,unsigned char* text,unsigned char color,unsigned char size_ligne, unsigned char slow_wait_letter)
{
  
  unsigned int i=0;
  unsigned char py_curseur=py;
  unsigned char px_curseur=px;
  unsigned char id_tiles;
  unsigned char buffer_times;
  unsigned char buffer_boucle=0;
  unsigned char py_end=0;
  unsigned char BX,BY;
  
  
  while ('\0' != text[i])
  {
    
      // &  text[i+1]=='S'
    if(text[i]=='@' )
     
    switch(text[i+1])
    {
    
      case 'S':
        buffer_boucle=0;
        px_curseur = px;
        py_curseur++;
        
        i=i+2;  
      break;
     
      case 'W':
       wait_key(KEY_EMPTY);
       i=i+2;
      break;
      
      case 'C':
        py_end=py_curseur;
    
         for (BY=0;BY<py_end;BY++)
         {
            for(BX=0;BX<size_ligne;BX++)
            {
              draw_text(BX+px,BY+py," ",0,0);
            }
          
         }
        i=i+2; 
        py_curseur = py;
        px_curseur = px;
        buffer_boucle=0;
      break;
      
    }
    else
    {
    
    id_tiles = text[i];
 
    buffer_times = slow_wait_letter;
    
    // -------------------------------------
    // * Redirection ASCCI/COMMODORE TILES *
    // -------------------------------------
    if ( (id_tiles>64) & (id_tiles<90))
    {
      id_tiles = id_tiles+32;
    }   
    else if (id_tiles>192)
    {
      id_tiles = id_tiles - 128;
    }
  
    
    
    draw_full_character(px_curseur,py_curseur,id_tiles-32+text_pointeur,color);
   
    buffer_boucle++;
    px_curseur++;    
    i++;
    
  if ((buffer_boucle>=size_ligne) & (size_ligne !=0))
    {
        buffer_boucle=0;
        px_curseur = px;
        py_curseur++;
    }
    
    
    while (buffer_times>0)
    {
        buffer_times--;
        wait_vbl();
    }
 
    } 
 
 
  } // Fin While Texte
  
}


// ===============
// ** Draw Text **
// ===============
void draw_text(unsigned char px,unsigned char py,unsigned char* text,unsigned char color,unsigned char slow_wait_letter)
{
  unsigned char i=0;
  unsigned char  id_tiles;
  unsigned char buffer_times;
  while ('\0' != text[i])
  {
    
    id_tiles = text[i];
 
    buffer_times = slow_wait_letter;
    
    // -------------------------------------
    // * Redirection ASCCI/COMMODORE TILES *
    // -------------------------------------
    if ( (id_tiles>64) & (id_tiles<90))
    {
      id_tiles = id_tiles+32;
    }   
    else if (id_tiles>192)
    {
      id_tiles = id_tiles - 128;
    }
    
    
    draw_full_character(px, py,id_tiles-32+text_pointeur,color);
   
    px++;
    
    i++;
    
    while (buffer_times>0)
    {
        buffer_times--;
        wait_vbl();
    }
 
  } // Fin While Texte
 
 
}
// ==================================
// * Attendre l'appuis d'une touche *
// ==================================
void wait_key(unsigned char id_key)
{
  if (id_key==KEY_EMPTY)
  {
    while(get_keyboard_key() ==KEY_EMPTY)
    {
      wait_vbl();
    }
  }
  else
  {
    while(get_keyboard_key() !=id_key)
    {
      wait_vbl();
    }
  }
}



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

// =========================================
// ** Modifier la couleur du background_3 **
// =========================================
// * color_id : Numeros de la couleur      *
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


void draw_character(unsigned char position_x, unsigned char position_y, unsigned char id_character)
{
  
//  POKE(G_adr_tilemap+position_x+40*position_y,id_character);
  POKE(G_adr_tilemap+position_x+adr_case[position_y],id_character);
}


void set_color_map(unsigned char position_x, unsigned char position_y, unsigned char color_id)
{
  
  POKE(REG_COLOR_MAP+position_x+adr_case[position_y],color_id);
}


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

// =======================================
// ** Selectionner la Bank du vic 2     **
// =======================================
void set_vic_bank(unsigned char id_bank)
{
  POKE (56578L,PEEK(56578L)|3);               // Mode Outputs
  POKE(REG_CIA2,(PEEK(REG_CIA2)& 252) | id_bank); // Selection de la bank.
  
  
  switch(id_bank)
  {
    case 3:
    buffer_vic_bank = 0;
    break;
    
    case 2:
    buffer_vic_bank = 1;
    break;
    
    case 1:
    buffer_vic_bank = 2;
    break;
    
    case 0:
    buffer_vic_bank = 3;
    break;
  }
  
  
  G_adr_tilemap = (buffer_id_screen<<6)+(buffer_vic_bank<<14);
  
}


// =================================================
// ** Selectionner l'adresse du screen memory     **
// =================================================
void set_adresse_screen_memory (unsigned char screen_memory_id_pointeur)
{
  POKE(53272L,(PEEK(53272L)& 15) | screen_memory_id_pointeur); // Selection de l'emplacement en fonction de l'id du pointeur.
  buffer_id_screen = screen_memory_id_pointeur;
  G_adr_tilemap = (screen_memory_id_pointeur<<6)+(buffer_vic_bank<<14);
}

//  ================================================================
//  * Modifier la variable generique pour poser un tiles à l'écran *
//  ================================================================
void set_adresse_tilemap(unsigned int adresse)
{
  
  G_adr_tilemap = adresse;
}


// =================================================
// ** Récupéré l'adresse mémoire du screen memory **
// =================================================
/*
    note : c'est l'adresse contenu dans la variable interne de happyc64 du pointeur de screen momory
    pour l'utilisation des fonctions draw_character et draw_full_character...
*/
  int get_adresse_screen_memory()
  {
    return G_adr_tilemap;
  }


// ======================================
// ** Modifier l'emplacement des tiles **
// =======================================

void set_location_character(unsigned char id)
{
  POKE(53272L,(PEEK(53272L)& 240) | id); // Selection de la bank.
  G_pointeur_pattern = id*0x400;
}


// ======================================
// ** Charger un pattern en mémoire    **
// ======================================

void set_data_character(unsigned int memory_adresse,unsigned char *data_character,unsigned char nb_pattern)
{
  unsigned int nb_octet = nb_pattern<<3;  
  memcpy((char*)memory_adresse,(char*)data_character,nb_octet);  
}

// ====================================
// - Parametrer le pointeur de sprite - 
// ====================================
void set_pointers_sprite(unsigned char id_sprite,unsigned char value)
{
  POKE(G_adr_tilemap+1016+id_sprite,value);
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
void set_scrolling_vertical(unsigned char Scroll_Y)
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
  unsigned int time = (PEEK(0xDC05)<<8 + PEEK( 0xDC04));
  return time;
  
}

unsigned int get_timer_b(void)
{
  unsigned int time = (PEEK(0xDC07)<<8 + PEEK( 0xDC06));
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
unsigned char get_rnd(unsigned char max_number)
{
  unsigned char valeur_genere = 0;
  do
  {
    POKE(0xD40E,0xFF);
    POKE(0xD40F,0xFF);
    POKE(0xD412,0x80);
    valeur_genere = PEEK(0xD41B);
  } while (valeur_genere > max_number);
  
  return valeur_genere;
  
}

// =================================================
// * Généré un nombre pseudo aléatoire sur 16 bits *
// =================================================
unsigned int get_rnd16(unsigned int max_number)
{
   unsigned char valeur_genere_a = 0;
   unsigned char valeur_genere_b = 0;
  do
  {
    POKE(0xD40E,0xFF);
    POKE(0xD40F,0xFF);
    POKE(0xD412,0x80);
    valeur_genere_a = PEEK(0xD41B);
    
    POKE(0xD40E,0xFF);
    POKE(0xD40F,0xFF);
    POKE(0xD412,0x80);
  valeur_genere_b = PEEK(0xD41B) + (valeur_genere_a<<8) ;
 
 } while (valeur_genere_b > max_number);
  
  return valeur_genere_b;
  
}

// =========================================
// * Sauvegarder dans un fichier un buffer *
// =========================================

unsigned char save_file(unsigned char*name,const void* buffer, unsigned int size,unsigned char device)
{ 
  unsigned char error;
  
  cbm_k_setlfs (1, device,1);
  cbm_k_setnam (name);
  
  error = cbm_k_save((int)buffer,(int)buffer+size);
  return error;
}


// ================================================
// * Charger les data d'un fichier dans un buffer *
// ================================================

unsigned int load_file(const char*name, const void* buffer, unsigned char device)
{
  unsigned int error;
  error = cbm_load (name, device, buffer);
  return error;
 
  
}

unsigned char get_error(void)
{
  return _oserror;
}

// =========
// * Tools *
// =========


void cls_color_ram(unsigned char color)
{
  memset((char*)REG_COLOR_MAP,color,1000);
}



void cls_bitmap_color_ram(unsigned char ink_color,unsigned char background_color)
{
   memset((char*)G_adr_tilemap,ink_color*16+background_color,0x400);
}

void cls_bitmap()
{
  memset((char*)((buffer_vic_bank<<14)+G_pointeur_pattern),0,8000);
}

// =============================================
// * Afficher une ligne avec le même character *
// =============================================
void draw_character_line_H(unsigned char px,unsigned char py,unsigned char size, unsigned char id_character,unsigned char color)
{ 
  unsigned int offset_start = py*40+px;
  memset((char*)REG_COLOR_MAP+offset_start,color,size);
  memset((char*)G_adr_tilemap+offset_start,id_character,size);
}

void draw_character_line_V(unsigned char px,unsigned char py,unsigned char size, unsigned char id_character,unsigned char color)
{
  unsigned char i;
  for (i=0;i<size;i++)
  {
    draw_full_character(px,py+i,id_character,color); 
  }
  
}


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



  // ================
  // * REU Fonction *
  // ================
  void reu_set_adresse_c64(unsigned int adresse)
  {
    POKEW(0xDF02,adresse);
  }
  
  void reu_set_adresse_reu(unsigned int adresse,unsigned char id_bank)
  {
    POKEW(0xDF04,adresse);
    POKE(0xDF06,id_bank);
  }
  void reu_set_size(unsigned int size)
  {
    POKEW(0xDF07,size);
  }
  void reu_start_dma(unsigned char value)
  {
    POKE(0xDF01,value);
  }
  
// ******************  
// * Gestion de bit *
// ******************

// =============
// * get_bit() *
// =============
unsigned char get_bit(unsigned char id_bit,unsigned char value)
{
  return value = (value >> id_bit)&0b00000001;
}

// =============================================
// * set_bit(numero du bit, valeur à modifier) *
// =============================================
unsigned char set_bit(unsigned char id_bit, unsigned char value)
{
    return value = value |(1<<id_bit);
}

// =============================================
// * set_bit(numero du bit, valeur à modifier) *
// =============================================
unsigned char unset_bit(unsigned char id_bit, unsigned char value)
{
    return value = value &(~(1<<id_bit));
}



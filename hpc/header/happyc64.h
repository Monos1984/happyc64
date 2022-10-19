/******************************************************
********              Happy C64           *************
*******************************************************
* Role ........... : Entête du sdk                    *
* Auteur ......... : Jean Monos                       *
* Version ........ : V 0.2.4.1                        *
* Modification ... : 19/10/2022                       *
* Licence ........ : Creative Commons by-sa           *
* Compilateur .... : cc65                             *
*******************************************************/

#ifndef HAPY_C64_H
	#define HAPY_C64_H
  // ===================================
  // ** Les Registres du Commodore 64 **
  // ===================================
  
  // -------------------
  // * Registre System *
  // -------------------
  #define NTSC 0
  #define PAL  1
  
  // ----------------------
  // * Define du joystick *
  // ----------------------
  #define J_UP    1<<0
  #define J_DOWN  1<<1
  #define J_LEFT  1<<2
  #define J_RIGHT 1<<3
  #define J_FIRE  1<<4
  
  // ------------------------------------
  // * Les registres libre de la page 0 *
  // ------------------------------------
  /* 
    -> 4 registres libre d'utilisation sont situés en Page 0 de la Ram du C64.   
  */
  
  #define REG_P0_A 0xFB
  #define REG_P0_B 0xFC
  #define REG_P0_C 0xFD
  #define REG_P0_D 0xFE
  
  
  // ====================
  // ** Registres bloc **
  // ====================
  #define R_VIC     0xD000 // 0xD000 (Sprites et mémoire video)
  #define R_SID     54272l // (Musique)
  #define R_COLOUR  55296l
  #define R_CIA1    53620l 
  #define R_CIA2    56576l
  #define R_KERNEL  0xE000 //0xE000  
  
  // ---------
  // * VIC 2 *
  // ----------
  #define REG_CIA2     0xDD00
  #define VIC_BANK_0        3   // Adresse $0000 -> $3FFF * Valeur par defaut
  #define VIC_BANK_1        2   // Adresse $4000 -> $7FFF * La Rom Tiles n'est pas dispo.
  #define VIC_BANK_2        1   // Adresse $8000 -> $BFFF
  #define VIC_BANK_3        0   // Adresse $C000 -> $FFFF * La Rom Tiles n'est pas dispo.
  
  // ---------------------------
  // *Gestion du screen memory *
  // ---------------------------
  /* Gestion du pointeur de la tilemap */
  
  #define SM_0                       0  // Adresse $0
  #define SM_0000                    0  // Adresse $0
  #define SM_0400                   16  // Adresse $0400 (par defaut)
  #define SM_0800                   32  // Adresse $0800
  #define SM_0C00                   48  // Adresse $0C00
  #define SM_1000                   64  // Adresse $1000
  #define SM_1400                   80  // Adresse $1400
  #define SM_1800                   96  // Adresse $1800
  #define SM_1C00                   112 // Adresse $1C00
  #define SM_2000                   128 // Adresse $2000
  #define SM_2400                   144 // Adresse $2400
  #define SM_2800                   160 // Adresse $2800
  #define SM_2C00                   176 // Adresse $2C00
  #define SM_3000                   192 // Adresse $3000
  #define SM_3400                   208 // Adresse $3400
  #define SM_3800                   224 // Adresse $3800
  #define SM_3C00                   240 // Adresse $3C00
  // -----------------------
  // * Les registres video *
  // ----------------------- 
  
  #define REG_SCREEN_MEMORY_PT         0xD018 // Registre du pointeur du Screen Memory
  #define REG_COLOR_BORDER             53280L // Registre pour modifier la couleur du BORDER
	#define REG_COLOR_BACKGROUND         53281L // Registre pour modifier la couleur du PAPER
  #define REG_COLOR_BACKGROUND_1       53282L // Registre pour modifier la couleur du PAPER
  #define REG_COLOR_BACKGROUND_2       53283L // Registre pour modifier la couleur du PAPER
  #define REG_COLOR_BACKGROUND_3       53284L // Registre pour modifier la couleur du PAPER
  
  #define REG_TILEMAP                  1024L // Registre de départ de la mémoire video pour les tilemaps
  #define REG_COLOR_MAP                55296L // Registre de départ de la mémoire video pour la color map
  
  // ----------------------------
  // * Les registres de couleur *
  // ----------------------------
  #define BACKGROUND_0 53281L          // Paire de Bit 00 en multicouleur. (Screen Color)
  #define BACKGROUND_1 53282L          // Paire de Bit 01 en Multicouleur
  #define BACKGROUND_2 53283L          // Paire de Bit 10 en Multicouleur
                                       // Paire de Bit 11 Couleurs Specifique de l'emplacement du character. (Maximum 3 bits)                             
  
  // -----------------------------
  // * Les registres des sprites *
  // -----------------------------
  #define REG_SHOW_SPRITE 0xD015          // Bit x = 1 : Affichage du sprite x. Bit x = 0 Cacher le sprite X. 
  
  #define REG_COLOR_SPRITE_0 0xD027       // Registre couleur du sprite 0
  #define REG_COLOR_SPRITE_1 0xD028       // Registre couleur du sprite 1
  #define REG_COLOR_SPRITE_2 0xD029       // Registre couleur du sprite 2
  #define REG_COLOR_SPRITE_3 0xD02A       // Registre couleur du sprite 3
  #define REG_COLOR_SPRITE_4 0xD02B       // Registre couleur du sprite 4
  #define REG_COLOR_SPRITE_5 0xD02C       // Registre couleur du sprite 5
  #define REG_COLOR_SPRITE_6 0xD02D       // Registre couleur du sprite 6
  #define REG_COLOR_SPRITE_7 0xD02E       // Registre couleur du sprite 7
  #define REG_COLOR_MS_0     0xD025       // Couleur général 0 des sprites multicouleur 
  #define REG_COLOR_MS_1     0xD026       // Couleur général 1 des sprites multicouleur
  
  
  // ----------------
  // * Les couleurs *
  // ----------------
  #define C_BLACK           0
  #define C_WHITE           1
  #define C_RED             2
  #define C_TURQUOISE       3
  #define C_PURPLE          4
  #define C_GREEN           5
  #define C_BLUE            6
  #define C_YELLOW          7
  #define C_ORANGE          8  
  #define C_BROWN           9
  #define C_LIGHT_RED      10
  #define C_GREY           11
  #define C_GREY_2         12
  #define C_LIGHT_GREEN    13
  #define C_LIGHT_BLUE_2   14
  #define C_GREY_3         15
  
  
  // ****************************
	// ** Numeros Touche Clavier **
	// **    adresse 203         **
	// ****************************
	
	// ============================
	// ** Lettre de l'alphabet   **
	// ============================
	#define KEY_A 10
	#define KEY_B 28
	#define KEY_C 20
	#define KEY_D 18
	#define KEY_E 14
	#define KEY_F 21
	#define KEY_G 26
	#define KEY_H 29
	#define KEY_I 33
	#define KEY_J 34
	#define KEY_K 37
	#define KEY_L 42
	#define KEY_M 36
	#define KEY_N 39
	#define KEY_O 38
	#define KEY_P 41
	#define KEY_Q 62
	#define KEY_R 17
	#define KEY_S 13
	#define KEY_T 22
	#define KEY_U 30
	#define KEY_V 31
	#define KEY_W 9
	#define KEY_X 23
	#define KEY_Y 25
	#define KEY_Z 12
	
	// ============================
	// ** Valeurs numeriques     **
	// ============================
	#define KEY_0 35
	#define KEY_1 56
	#define KEY_2 59
	#define KEY_3 8
	#define KEY_4 11
	#define KEY_5 16
	#define KEY_6 19
	#define KEY_7 24
	#define KEY_8 27
	#define KEY_9 32
	
	// ============================
	// ** Touche Divers          **
	// ============================
	#define KEY_L_ARR 57
	#define KEY_CLR 51
	#define KEY_DEL 0
	#define KEY_RET 1
	#define KEY_DN 4
	#define KEY_RT 2
	#define KEY_STOP 63 // Echape
	#define KEY_SPC 60 // Espace
	#define KEY_EMPTY 64 // Pas de touche
	
  #define KEY_ANY 64 // N'importe qu'elle touche pour le wait_key
  
  
	// ============================
	// ** Touches Arithmétiques  **
	// ============================
	#define KEY_PLUS 40
	#define KEY_MOINS 43
	#define KEY_DIVISER 48
	#define KEY_MULTIPLIER 49
	
	// ============================
	// ** Touches de Fonctions   **
	// ============================
	#define KEY_F1 4
	#define KEY_F3 5
	#define KEY_F5 6
	#define KEY_F7 3
  
  
  // =======================
  // * Interruption VIC II *
  // =======================
  #define REG_IRQ $D019 
  
  /* 
  BIT :           Effet :
  -----------------------------------------------
  7........: IRQ VIC II (Vic en interuption si 1)
  -----------------------------------------------
  6 .......: OSEF
  ------------------------------------------------
  5 .......: OSEF
  ------------------------------------------------
  4
  ------------------------------------------------
  3 .......: Photostyle
  ------------------------------------------------
  2 .......: Collision Sprite/Sprite
  ------------------------------------------------
  1 .......: Collision Tiles/Sprites
  ------------------------------------------------
  0 .......: Balayagte Ecran atteintes (ligne raster ?)
  ------------------------------------------------
  
  */
  
  #define REG_ADR_HAUT_IRQ 0x315
  #define REG_ADR_BASS_IRQ 0x314
  
  
  
  
  unsigned char test();
  
  
  // =====================
  // * Initiation facile *
  // =====================
  void init_vic_hpc();
  
  //  --------------------------
  //  * Configuration suivante *
  //  -------------------------- 
  //  VIC II ............... $C000
  //  Screen Memory......... $E000
  //  Pointeur de patern.... $E800 
    
  
  // ============================
  // * Gestion des interuptions *
  // ============================
  void init_adr_irq(unsigned int adresse);
  #define end_fonction_irq() __asm__("jmp $ea31")
  
  // ========================
  // ** Les Fonctions Text **
  // ========================
  
 // ----------------------------------------------------- 
 // * Pointeur de text *
 // ----------------------------------------------------- 
  /*
    Permet de definir le character lié à l'espace dans la zone des caractères. (Code ASCII)
  */
  void set_text_pointer(unsigned char pointer); 
  
 // ----------------------------------------------------------------------------------------------- 
 // *  void draw_text(unsigned char px,unsigned char py,unsigned char* text,unsigned char color)  *
 // -----------------------------------------------------------------------------------------------
 /*
  Permet d'afficher un text à l'écran.
 */
  void draw_text(unsigned char px,unsigned char py,unsigned char* text,unsigned char color,unsigned char slow_wait_letter);
  
  void draw_bloc_text(unsigned char px,unsigned char py,unsigned char* text,unsigned char color,unsigned char size_ligne, unsigned char slow_wait_letter);
 // --------------------------------------------------------------------------------------------------- 
 // * void draw_valeur_8 (unsigned char px,unsigned char py,unsigned char valeur,unsigned char color) *
 // ---------------------------------------------------------------------------------------------------
 /*
  Permet d'afficher une valeur 8 bits à l'écran
 */
  void draw_text_value_8 (unsigned char px,unsigned char py,unsigned char value,unsigned char color);
  
 // --------------------------------------------------------------------------------------------------- 
 // * void draw_valeur_16 (unsigned char px,unsigned char py,unsigned char valeur,unsigned char color) *
 // ---------------------------------------------------------------------------------------------------
 /*
  Permet d'afficher une valeur 16 bits à l'écran
 */
  void draw_text_value_16 (unsigned char px,unsigned char py,unsigned int value,unsigned char color);
   
  // ===============================
  // ** Les Fonctions Video       **
  // ===============================
  
  #define SCREEN_ON   POKE(0xD011,PEEK(0xD011)|16)  // Allumage de l'écran
  #define SCREEN_OFF  POKE(0xD011,PEEK(0xD011)&239) // Eteindre l'écran
  
  // ----------------
  // * get_system() *
  // ----------------
  /*
    - Retourne le type de processeur. pal(1) ou ntsc(1)
  */
  
  unsigned char get_system();
  
  // --------------------------------------------------------
  // * set_adresse_screen_memory(screen_memory_id_pointeur) *
  // --------------------------------------------------------
  /*
    - Permet de choisir l'emplacement de départ de la tilemap.
     # screen_memory_id_pointeur : index de l'emplacement. (voir define).
  */
  void set_adresse_screen_memory (unsigned char screen_memory_id_pointeur); 
  
  
  // ---------------------------------------------
  // * set_adresse_tilemap(unsigned int adresse) *
  // ---------------------------------------------
  /*
    Permet de configurer manuellement l'adresse interne de la tilemap(screen memory) 
    
    Adresse : Adresse complet 
    Note :  Configuration indispensable pour utiliser les fonctions draw_tiles ceci dit en modifiant 
    la bank du vic et en utilisant le set_adresse_screen_memory, la variable se met à jour automatiquement.
    
  */
  void set_adresse_tilemap(unsigned int adresse);
  
  // --------------------------------------------------------
  // * get_adresse_screen_memory()                          *
  // --------------------------------------------------------
  /*
    - Permet de récupérer l'emplacement de l'adresse mémoire.
    
  */
 int get_adresse_screen_memory();
  
  // --------------------------------------------------------------------
  // * set_data_character(adresse cible , adresse source , nombre de pattern) *
  // --------------------------------------------------------------------
  /* Permet de mémoriser dans le C64 les données des pattern des tiles à  l'endroit voulu */
  void set_data_character(unsigned int memory_adresse,unsigned char *data_character,unsigned char nb_pattern);
  
   
  // ------------------------------
  // * set_location_character(id) *
  // ------------------------------
  /*
    - Permet de choisir l'emplacement des patern.
     # id : index de l'emplacement du jeu de charactère (tiles/Font...)
    
     ==============================================================================  
       ID : Adr Decimal : Adr Hexadecimal : Note   
     ============================================================================== 
     #  0 :      0          $0000-$07FF
     ------------------------------------------------------------------------------
     #  2 :   2048          $0800-$0FFF     (Semble être le plus fréquent)
     ------------------------------------------------------------------------------
     #  4 :   4096          $1000-$17FF     (Rom Bloc 0 et 2)
     ------------------------------------------------------------------------------
     #  6 :   6144          $1800-$1FFF     (Rom Bloc 0 et 2)
     ------------------------------------------------------------------------------
     #  8 :   8192          $2000-$27FF
     ------------------------------------------------------------------------------
     # 10 :  10240          $2800-$2FFF
     ------------------------------------------------------------------------------
     # 12 :  12288          $3000-$27FF
     ------------------------------------------------------------------------------
     # 14 :  14336          $3800-$3FFF
     ------------------------------------------------------------------------------
  */
  void set_location_character(unsigned char id); 
  
  // -----------------------------------------------------
  // * SET_MULTICOLOR_MODE_ON *
  // -----------------------------------------------------
  /*
    - Permet d'activer le mode multicolor pour les characters.
    
  */
  #define SET_MULTICOLOR_MODE_ON    POKE(53270L,(PEEK(53270L)  | 16 )) 
  
  // -----------------------------------------------------
  // * SET_MULTICOLOR_MODE_OFF *
  // -----------------------------------------------------
  /*
    - Permet d'activer le mode standard pour les characters.
    
  */
  #define SET_MULTICOLOR_MODE_OFF  POKE(53270L,(PEEK(53270L)  & 239 )); 

  // -----------------------------------------------------
  // * SET_EXTENDED_BACKGROUND_COLOR_ON *
  // -----------------------------------------------------
  /*
    - Permet d'activer le mode  EXTENDED_BACKGROUND_COLOR..
    
  */
  #define SET_EXTENDED_BACKGROUND_COLOR_ON  POKE(532650L,(PEEK(53265L)  |64 ));
  
  // -----------------------------------------------------
  // * SET_EXTENDED_BACKGROUND_COLOR_OFF *
  // -----------------------------------------------------
  /*
    - Permet de desactiver mode EXTENDED_BACKGROUND_COLOR.
    
  */
  #define SET_EXTENDED_BACKGROUND_COLOR_OFF  POKE(53265L,(PEEK(53265L)  & 191 )); 
  
  
  // -----------------------------------------------------
  // * SET_STANDARD_HIGHT_RESOLUTION_BMM_ON *
  // -----------------------------------------------------
  /*
    - Permet d'activer le mode BIT MAP. (53265)
    
  */
  #define SET_STANDARD_HIGHT_RESOLUTION_BMM_ON  POKE(0xD011,(PEEK(0xD011)  |32 )); 
  
  // -----------------------------------------------------
  // * SET_STANDARD_HIGHT_RESOLUTION_BMM_OFF *
  // -----------------------------------------------------
  /*
    - Permet d'esactiver le mode BIT MAP.
    
  */
  #define SET_STANDARD_HIGHT_RESOLUTION_BMM_OFF  POKE(53265L,(PEEK(53265L)  & 223 )); 
  
  // ---------------------------------------
  // * cls()                               *
  // ---------------------------------------
  /*   
    - Permet d'effacer l'écran 
  */ 
 void cls(unsigned char id_tiles);    

    
  // ---------------------------------------
  // * set_color_border(color_id)          *
  // ---------------------------------------
  /*
    - Permet de modifier la couleur de la bordure de l'écran.
     # color_id : index de la couleur du nuancier du C64.
  */
  void set_color_border (unsigned char color_id); 

    
  // -------------------------------------------
  // * set_color_background(color_id)          *
  // -------------------------------------------
  /*
    - Permet de modifier la couleur du papier du C64
     # color_id : index de la couleur du nuancier du C64.
  */
  void set_color_background (unsigned char color_id); 
  
  // ---------------------------------------------
  // * set_color_background_1(color_id)          *
  // ---------------------------------------------
  /*
    - Permet de modifier la couleur du background 1 du C64
     # color_id : index de la couleur du nuancier du C64.
  */
  void set_color_background_1 (unsigned char color_id); 
  
  // ---------------------------------------------
  // * set_color_background_2(color_id)          *
  // ---------------------------------------------
  /*
    - Permet de modifier la couleur du background 2 du C64
     # color_id : index de la couleur du nuancier du C64.
  */
  void set_color_background_2 (unsigned char color_id); 


  // ---------------------------------------------
  // * set_color_background_3(color_id)          *
  // ---------------------------------------------
  /*
    - Permet de modifier la couleur du background 3 du C64
     # color_id : index de la couleur du nuancier du C64.
  */
  void set_color_background_3 (unsigned char color_id); 



 // * draw_meta_tiles(unsigned char position_x, unsigned char position_y, unsigned char id_character, 
 // unsigned char color_id) *
 /*
 - Permet d'afficher un meta tile (4 tiles)
 */


  void draw_meta_tiles(unsigned char position_x, unsigned char position_y, unsigned char id_character, unsigned char color_id);

  // --------------------------------------------------------------------------
  // * draw_full_character(position_x, position_y,id_character, color_id)     *
  // --------------------------------------------------------------------e-----
  /*
    - Permet d'afficher un character à l'écran et la couleur de la case 
     # position_x : position horizontale du character sur le quadrillage 8x8. (0-255)
     # position_y : position verticale du character sur le quadrillage 8x8.(0-255)
     # id_character : index du character à poser. (0-255)
     # color_id   : couleur du character.    
  */
  void draw_full_character(unsigned char position_x, unsigned char position_y, unsigned char id_character,unsigned char color_id);
  
  
  // ----------------------------------------------------------------------------------------------
  // * draw_character(unsigned char position_x, unsigned char position_y, unsigned char id_character) *
  // ----------------------------------------------------------------------------------------------
  /*
    - Permet d'afficher un character à l'écran 
     # position_x : position horizontale du character sur le quadrillage 8x8. (0-255)
     # position_x : position verticale du character sur le quadrillage 8x8.(0-255)
     # id_character : index du character à poser. (0-255)
        
  */ 
  void draw_character(unsigned char position_x, unsigned char position_y, unsigned char id_character);
  
  // ------------------
  // * get_id_charset *
  // ------------------
  unsigned char get_id_character(unsigned char position_x,unsigned char position_y);
  
  // --------------------------------------------------------------------------------------------
  // * set_color_map(unsigned char position_x, unsigned char position_y,unsigned char color_id) *
  // --------------------------------------------------------------------------------------------
  /*
    - Permet de modifier la color map à un emplacement !
    # position_x : position horizontale du character sur le quadrillage 8x8. (0-255)
    # position_x : position verticale du character sur le quadrillage 8x8.(0-255)
    # color_id   : couleur du character.    
  */
  void set_color_map(unsigned char position_x, unsigned char position_y,unsigned char color_id);
  
  
  unsigned char get_color_map(unsigned char position_x, unsigned char position_y);
  
  void set_bitmap_color_map(unsigned char px, unsigned char py, unsigned char color_ink,unsigned char color_background);
  
  
  // -------------------------------------------
  // * void cls_color_ram(unsigned char color) *
  // -------------------------------------------
  /*
    - Permet de remplire la color_ram d'une couleur unique :
    # color : Numero de la couleur
  */
  void cls_color_ram(unsigned char color);
  void cls_bitmap_color_ram(unsigned char ink_color,unsigned char background_color); 
  void cls_bitmap();
  // ================================
  // ** Configuration video       **
  // ================================
  
  // ------------------------------------------
  // * Configuration en mode 38 ou 40 colones *
  // ------------------------------------------
  #define SET_38_COLUMNS       POKE(53270L,(PEEK(53270L)&247))
  #define SET_40_COLUMNS       POKE(53270L,(PEEK(53270L)|8))
 
  // -----------------------------------------
  // * Configuration en mode 24 ou 25 lignes *
  // -----------------------------------------
  #define SET_24_RAWS 	POKE(53265L,(PEEK(53265L)&247));
  #define SET_25_RAWS   POKE(53265L,(PEEK(53265L)|8));
  
  
  // ===============
  // ** Scrolling **
  // ===============
  void set_scrolling_horizontal(signed char Scroll_X);
  void set_scrolling_vertical(unsigned char Scroll_Y);
  
  // =========================
  // ** Gestion des sprites **
  // =========================
  
 
  // --------------------------------------------------------------------------------------------
  // * set_sprite_data(unsigned char adr_cible,unsigned char *adr_data,unsigned char nb_sprite) *
  // --------------------------------------------------------------------------------------------
  /* - Copy les datas d'un sprite (6 4octets) ou plusieurs à partir d'une adresse de départ (ou tableau)
     # adr_cible : Adresse cible
     # *adr_data : adresse de départ. (Nom du tableau le plus souvent) 
     # nb_sprite : Nombre de sprite à copier.
  */
  void set_sprite_data(unsigned int adr_cible,unsigned char *adr_data,unsigned char nb_sprite);
  
  // ------------------------------------------------
  // * set_pointeurs_sprites(id_sprite,id_pointeur) *
  // -------------------------------------------------
  /* - Modifie le pointeur de sprite
     # id_sprites : Numéros du pointeur du sprite à modifier.
     # id_pointeur  : Valeur du pointeur. 
     l'emplacement finale se trouve donc à l'adresse du bank vic + Valeur du pointeur*64
  */
  void set_pointers_sprite(unsigned char id_sprite,unsigned char id_pointer);
  
  // ---------------------------
  // * hide_sprite(id_sprite) *
  // --------------------------
  /* - Desactive un sprite à l'écran
     # id_sprites : Numéros du sprite .    
  */
 void hide_sprite(unsigned char id_sprite);
 
  // ------------------------------------------------
  // * show_sprite(id_sprite) *
  // -------------------------------------------------
  /* - Active un sprite à l'écran
     # id_sprites : Numéros du sprite .    
  */
  
 void show_sprite(unsigned char id_sprite);
 
 
  // ------------------------------------------------
  // * draw_sprite(id_sprite, position_x, position_y); *
  // -------------------------------------------------
  /* - modifie l'emplacement du sprite à l'écran
     # id_sprites : Numéros du sprite .  
     # position_x : placement X du sprite. (Le bit de controle est activé automatiquement si x >255)
     # position_y  : placement y du sprite
  */
 void draw_sprite(unsigned char id_sprite,unsigned int position_x,unsigned char position_y);
 
  // ----------------------------------------------------
  // * double_height_sprite_on(unsigned char id_sprite) *
  // ----------------------------------------------------
  /* - Double la hauteur du sprite
     # id_sprites : Numéros du sprite .   
  */
 void double_height_sprite_on(unsigned char id_sprite);
  // ----------------------------------------------------
  // * double_height_sprite_off(unsigned char id_sprite) *
  // ----------------------------------------------------
  /* - Taille simple du sprite en hauteur
     # id_sprites : Numéros du sprite .   
  */
 void double_height_sprite_off(unsigned char id_sprite);
 
 void double_width_sprite_on(unsigned char id_sprite);
 void double_width_sprite_off(unsigned char id_sprite);
 
 void sprite_priority_on(unsigned char id_sprite);
 void sprite_priority_off(unsigned char id_sprite);
 
 void set_sprite_multicolore_on(unsigned char id_sprite);
 void set_sprite_multicolore_off(unsigned char id_sprite);
 
 void set_color_sprite(unsigned char id_sprite,unsigned char color_id);
 void set_sprite_color_1(unsigned char color_id);
 void set_sprite_color_2(unsigned char  color_id);
 
 // ----------------------------------------------------------------
 // * Récupérer la collision du sprite sur un sprite ou un character *
 // ----------------------------------------------------------------
 /*
   Bit x = 0 par de collision
   Bit X = 1 colision.
 
   Bit 7 = sprite 7 en collision
   Bit 6 = sprite 6 en collision
   Bit 5 = sprite 5 en collision
   Bit 4 = sprite 4 en collision
   Bit 3 = sprite 3 en collision
   Bit 2 = sprite 2 en collision
   Bit 1 = sprite 1 en collision
   Bit 0 = sprite0  en collision
 */
 
 #define get_collision_sprite()  PEEK(0xD01E)
 #define get_collision_character() PEEK(0xD01F)
 
 
  // ================================
  // ** Gestion des commandes     **
  // ================================
  #define get_joystick_2() (PEEK(0xDC00)^255) // $FF 0b11111111 = 0
  #define get_joystick_1() (PEEK(0xDC01)^255)
 
  // ** Récupérer touche du clavier **
  #define get_keyboard_key() PEEK(203L)
 
  // ** Desactiver la touche shift **
  #define set_shift_off() POKE(657,128)
  
  // ** Active la touche shift
  #define set_shift_on() POKE(657,0)
 
 
  // =========================================
  // ** Attendre qu'une touche soit presser **
  // =========================================
  void wait_key(unsigned char id_key);
 
  // ================================
  // ** Gestion de la mémoire      **
  // ================================
  
  // ------------------
  // * set_loram...() *
  // ------------------
  /*  - Active ou desactive la Rom Basic à l'adresse 40960 ($A000) 
      -  Permet d'avoir 8ko de ram.
  */
  
  #define set_loram_basic()   POKE(0x1,PEEK(0x1)|1)
  #define set_loram_ram()     POKE(0x1,PEEK(0x1)&254)
  
  // ------------------
  // * set_hiram..() *
  // ------------------
  /*  - Active ou desactive le kernel à l'adresse 57344 ($E000) 
      -  Permet d'avoir 8ko de ram.
      - note : bug ?
  */
  #define set_hiram_kernal()  POKE(0x1,PEEK(0x1)|3)
  #define set_hiram_ram()     POKE(0x1,PEEK(0x1)&253)
  
 
  
  // ---------------------------------------
  // * set_vic_bank(id_bank)               *
  // ---------------------------------------
  /* - Permet de selectionner la bank mémoire du vic2
     # id_bank valeur entre 0 et 3
  */
  void set_vic_bank(unsigned char id_bank);
  
  
  
  // ---------------------------------------
  // * set_interruption_on()               *
  // * set_interruption_off()              *
  // ---------------------------------------
  /* Desactive (off)/Reactive (on) les interruptions*/
 
   #define set_interruption_on()  POKE(0xDC0D,129) 
   #define set_interruption_off() POKE(0xDC0D,127) 
  
  
  // ==================================
  // * Gestion du SID pour la musique *
  // ==================================
  
  // * Macro pour le canal *
  #define VOICE_1 0
  #define VOICE_2 7
  #define VOICE_3 14
  
  // * Macro pour le Type du canal
  #define TRIANGLE   17
  #define SAWTOOTH   33
  #define PULSE      65
  #define NOISE     129
  
  
  // ----------------
  // * Jouer un son *
  // ----------------
 
  void set_sound (
              unsigned char voice, // Utiliser le macro VOICE_1 , VOICE_2 , VOICE_3
              unsigned char lb_freq,
              unsigned char hb_freq,
              unsigned char lb_pulse,
              unsigned char hb_pulse,
              unsigned char waveforme, // Utiliser le macro TRIANGLE , SAWTOOTH, PULSE , NOISE
          
              unsigned char attaque_decay,
              unsigned char sustain_release
            
  );
  
  // -----------------------
  // * Modifier le volume. *
  // -----------------------
  void set_volume(unsigned char volume);
  
  // =========
  // * Timer *
  // =========
  
  
  unsigned int get_timer_a(void);
  unsigned int get_timer_b(void);
  
  
  // ==================
  // * VBL and Raster *
  // ==================
   unsigned int get_raster(void); // Récupére la ligne du raster
   void wait_vbl(void);  // Attendre jusque l'entrée du retour du balayage.
   void wait_time(unsigned char value); // Attendre un nombre de fois le VBL
   
  // ==============================================
  // * Générateur aléatoire de nombre sur 1 octet *
  // ==============================================
   unsigned char get_rnd(unsigned char max_number);
  // ==============================================
  // * Générateur aléatoire de nombre sur 2 octet *
  // ==============================================
   unsigned int get_rnd16(unsigned int max_number);
  
  // ===================
  // * Gestion Mémoire *
  // ===================
  
  // ---------------------------------------
  // * PEEK(addr)                          *
  // ---------------------------------------
  /* 
    - Permet de lire un octet à une adresse 
     # addr : Adresse mémoire sur 2 octets (int)
  */
 
  #define PEEK(addr)         (*(unsigned char*) (addr))
  
  // ---------------------------------------
  // * POKE(adrr,val)                      *
  // ---------------------------------------
  /* 
    - Permet d'écrire un octet à une adresse
     # addr : Adresse mémoire sur 2 octets (int)
     # val  : valeur sur 1 octet (0-255) 
  */
  
  #define POKE(addr,val)     (*(unsigned char*) (addr) = (val))
  
 
  // ---------------------------------------
  // * PEEKW(addr)                          *
  // ---------------------------------------
  /* 
    - Permet de lire 2 octets à une adresse 
     # addr : Adresse mémoire sur 2 octets (int)
  */
 
  #define PEEKW(addr)         (*(unsigned int*) (addr))
  
  // ---------------------------------------
  // * POKEW(adrr,val)                      *
  // ---------------------------------------
  /* 
    - Permet d'écrire un octet à une adresse
     # addr : Adresse mémoire sur 2 octets (int)
     # val  : valeur sur 2 octet (0-65535) 
  */
  
  #define POKEW(addr,val)     (*(unsigned int*) (addr) = (val))
  
  // ------------------------------------------
  // * get_bit(numero du bit,valeur à tester) *
  // ------------------------------------------
  /*
    -Permet de lire l'état d'un bit dans un octet.
    # id_bit : Numeros du bit à tester.
    # value  ; Nombre à tester. 
  */
  unsigned char get_bit(unsigned char id_bit,unsigned char value);
 
 
  // ---------------------------------------------
  // * set_bit(numero du bit, valeur à modifier) *
  // ---------------------------------------------
  unsigned char set_bit(unsigned char id_bit, unsigned char value);
  
  // =============================================
  // * set_bit(numero du bit, valeur à modifier) *
  // =============================================
  unsigned char unset_bit(unsigned char id_bit, unsigned char value);
  
 
  // ========================  
  // * Gestion de Save Data *
  // ========================
  
  
  // --------------------------------------------------------------------------------------------
  // * save_file(unsigned char*name,const void* buffer, unsigned int size,unsigned char device) *
  // --------------------------------------------------------------------------------------------
  /* - Permet d'écrire dans un fichier le contenue d'un buffer.
       #name : Le nom du fichier. un ,"option" permet de typer le fichier.
              d : del 
              s : Sequenciel (seq)
              u : USR
              p : PRG (defaut)
              l : REL
              exemple : "data,s"
       #buffer : pointeur ou Nom du tableau
       #size   : Taille du fichier à enregistrer. (Sur disquette 2 octets va s'ajouter au début du fichier)
       #device : Id du device. 1 pour casette, 8 pour lecteur disquette 1, 9 pour lecteur disquette 2 ... 
  */
  unsigned char save_file(unsigned char*name,const void* buffer, unsigned int size,unsigned char device);
  
  // ------------------------------------------------------------------------
  // * load_file(const char*name, const void* buffer, unsigned char device) *
  // ------------------------------------------------------------------------
  /* - Permet de charger dans un buffer le contenue d'un fichier
       #name : Le nom du fichier. un ,"option" permet de typer le fichier.
              d : del 
              s : Sequenciel (seq)
              u : USR
              p : PRG (defaut)
              l : REL
              exemple : "data,s"
              
       #buffer: pointeur ou nom du tableau de buffer.
       #device : Id du device. 1 pour casette, 8 pour lecteur disquette 1, 9 pour lecteur disquette 2 ... 
       
       Note : Les deux octets du "header" ne sont pas enregistré dans le buffer.
       Renvois le nombre d'octet chargé. (pour cela que c'est un int)
  */
  unsigned int load_file(const char*name, const void* buffer, unsigned char device);
  
  // -------------------------------------------
  // * Recupere le code erreur d'un chargement *
  // -------------------------------------------
      /*
       1  =   too many files
       2  =   file open
       3  =   file not open
       4  =   file not found
       5  =   device not present
       6  =   not input-file
       7  =   not output-file
       8  =   missing file-name
       9  =   illegal device-number

      10  =   STOP-key pushed
      11  =   general I/O-error
      */
  
  unsigned char get_error(void);
  
  // ---------
  // * Tools *
  // ---------
  void draw_character_line_V(unsigned char px,unsigned char py,unsigned char size, unsigned char id_character,unsigned char color);
  void draw_character_line_H(unsigned char px,unsigned char py,unsigned char size, unsigned char id_character,unsigned char color);
  
  unsigned int pow(unsigned int value, unsigned int power);
 // ----------------------
 // * rle_decrompression *
 // ----------------------
 /*
  Permet de decompresser une série de valeur en mode RLE.
  Attention une valeur 0 au nombre de fois q'une valeur est dupliqué, met fin à la routine de decryptage. Ce qui veux dire qu'il faut terminer sa série de compression par un 0.
  C'est un simple format RLE ! 1,2 veux dire copie 1 fois la valeur 2.
  5,12 veux dire copie en mémoire 5 fois la valeur 12.
   
 */ 
  void rle_decrompression(unsigned int source,unsigned int destination);
  unsigned int rle_compression(unsigned int source,unsigned int destination,unsigned int size);
  
  
  // ===================================
  // * REU Extensention memoire : Bêta *
  // ===================================
  
  // * Define pour le start dma *
  #define MODE_C64_REU  0b10010000
  #define MODE_REU_C64  0b10010001
  #define MODE_SWAP     0b10010010
  
  
  void reu_set_adresse_c64(unsigned int adresse);
  void reu_set_adresse_reu(unsigned int adresse,unsigned char id_bank);
  void reu_set_size(unsigned int size);
  void reu_start_dma(unsigned char value);
  
  // ===================
  // * Bitmap Fonction *
  // ===================
  void draw_pixel(unsigned int px, unsigned int py);
  
  
  // ==========
  // * Paddle *
  // ==========
  unsigned char get_paddle(unsigned char port,unsigned char id_paddle);
  unsigned char get_paddle_fire(unsigned char port,unsigned char id_paddle);
  
  // ======================
  // * 4 player interface *
  // ======================
  void init_4pi();
  unsigned char get_joystick_3();
  
  // ****************************
  // * Happy C64 Map            *
  // ****************************
  
  // --------------------------------
  // * Modifier la taille de la map *
  // --------------------------------
  void hm_set_map_size_x(unsigned char value);
  void hm_set_map_size_y(unsigned char value);
  
  // -----------------------------------------------
  // * Modifier les coordonnee de depart de la map *
  // -----------------------------------------------
  void hm_set_map_offset_x(unsigned char value);
  void hm_set_map_offset_y(unsigned char value);
  
  // -----------------------------------------------
  // * Modifier le numero du meta tile dans la map *
  // -----------------------------------------------
  void hm_set_buffer_map(unsigned char px,unsigned char py,unsigned char value);
  
  // ------------------------------------
  // * Modifier les datas des meta tile *
  // ------------------------------------
  /*
  id_mt = index du meta tile (0-61)
  
  id_1 = index du tile haut gauche. (0-256)
  id_2 = index du tile haut droite. (0-256)
  id_3 = index du tile bas gauche. (0-256)
  id_4 = index du tile bas droite. (0-256)
  
  color_1 = index de couleur du tile haut gauche (0-15)
  color_2 = index de couleur du tile haut droite (0-15)
  color_3 = index de couleur du tile bas gauche (0-15)
  color_4 = index de couleur du tile bas droite (0-15)
  */
  
  void hm_set_tile_data(unsigned char id_mt,unsigned char id_1,unsigned char id_2,unsigned char id_3,unsigned char id_4,unsigned char color_1,unsigned char color_2,unsigned char color_3,unsigned char color_4);
  
  // -----------------------------
  // * Afficher la map à l'ecran *
  // -----------------------------
  void hm_draw_map();
  
  
#endif
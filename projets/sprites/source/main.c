/*******************************************************
 ********  Sprite exemple avec mouvement   *************
 *******************************************************
 * Role ........... : exemple pour poser un sprites    *
 * Auteur ......... : Jean Monos                       *
 * Version ........ : V 1.0.0.0                        *
 * Modification ... : 01/03/2020                       *
 * Licence ........ : Creative Commons by-sa           *
 * Compilateur .... : cc65                             *
 *******************************************************/

// ===================
// * Fichier include *
// ===================
#include <happyc64.h>

// =================
// * Fonction main *
// =================
void main()
{
  // -------------------------------------
  // * Declaration des variables locales *
  // -------------------------------------
  unsigned char data_tiles[]=
  {
    0,0,0,0,0,0,0,0
  };
  
  unsigned char data_sprite[]=
  {
    255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,
  
    255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255
    
  };

  unsigned int  sp_x = 100;
  unsigned char sp_y = 100;

  // --------------------------
  // * Ïnitation du programme *
  // --------------------------
  SCREEN_OFF;
  set_loram_ram();
  set_location_character(2); // 0x0800 lecture des tiles.
  load_pattern(0x0800,data_tiles,1);
  cls(1);
  set_hiram_ram();
  set_hiram_kernal();
  wait_vbl();
  SCREEN_ON;
  
  // -----------------------------
  // * Configuration des sprites *
  // -----------------------------
  set_pointeurs_sprites(0,33);
  set_sprite_data(2112,data_sprite,1);
  set_color_sprite(0,10);
  draw_sprite(0,sp_x,sp_y);
  show_sprite(0);
 
  // -----------------------
  // * Boucle du programme *
  // -----------------------
  while(1)
  {
    if(get_keyboard_key() == KEY_B)
    {
      wait_vbl();
      cls(0);
    }

    if(get_keyboard_key() == KEY_A)
    {
      sp_y = get_rnd(255);              
    }
    
  
    // ----------------------------------------
    // * Tester la direction Droite ou Gauche *
    // ----------------------------------------
    if ((get_joystick_1()&RIGHT))
    {
      if (sp_x<320)
      {
        sp_x++;
      }
    }

    else if ((get_joystick_1()&LEFT))
    {
      if (sp_x>0)
      {
        sp_x--;
      }
    }

    // ----------------------------------------
    // * Mise à jour de l'affichage du sprite *
    // ----------------------------------------
    wait_vbl();
    draw_sprite(0,sp_x,sp_y);
   
  }
  
  
  
  
  
  
  
  
  
}
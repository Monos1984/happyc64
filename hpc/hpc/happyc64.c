 /********************************************************
  ********              Happy C64            ************
  *******************************************************
  * Role ........... : Entête du sdk                    *
  * Auteur ......... : Jean Monos                       *
  * Version ........ : V 0.2.0.0                        *
  * Modification ... : 13/03/2021                       *
  * Licence ........ : Creative Commons by-sa           *
  * Compilateur .... : cc65                             *
  ******************************************************* */ 

// ====================
// * Fichier includes *
// ====================
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


// ====================
// ** NTSC(0)/PAL(1) **
// ====================
unsigned char get_system()
{
  return PEEK(0x2A6);
}

// ===================
// * Attendre le VBL *
// ===================
void wait_vbl(void)
{
  waitvsync();  
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





// =========
// * Tools *
// =========
void cls_color_ram(unsigned char color)
{
  memset((char*)REG_COLOR_MAP,color,1000);
}





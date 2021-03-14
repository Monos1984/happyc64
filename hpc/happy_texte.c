 /**********************************************************
  ********              Happy Texte             ************
  **********************************************************
  * Role ........... : Texte Engine                        *
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
#include <stdio.h>

// ===================
// * Variable extern *
// ===================
extern unsigned char text_pointeur;
extern unsigned char buffer_8[8];
extern unsigned char buffer_16[16];
 
// ==================================
// *Configurer le pointeur de texte *
// ==================================
void set_text_pointer(unsigned char pointer)
{
  text_pointeur = pointer;
}

// ==============================
// * Afficher une valeur 8 bits *
// ==============================
void draw_text_value_8 (unsigned char px,unsigned char py,unsigned char value,unsigned char color)
{
  sprintf(buffer_8,"%d",value);
  draw_text( px,py,buffer_8,color,0);
}

// ===============================
// * Afficher une valeur 16 bits *
// ===============================
void draw_text_value_16 (unsigned char px,unsigned char py,  unsigned int value,unsigned char color)
{
  sprintf(buffer_16,"%u",value);
  draw_text( px,py,buffer_16,color,0);
}

// ============================
// * Afficher un bloc de text *
// ============================
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

// =======================
// ** Afficher un texte **
// =======================
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
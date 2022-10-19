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
  unsigned char centaine,dizaine,unite,intermed;
    
  centaine = value / 100;
  intermed = value - 100*centaine;
  dizaine = intermed/10;
  unite = intermed-dizaine*10;
  
  buffer_8[0]=centaine+48;
  buffer_8[1]=dizaine+48;
  buffer_8[2]=unite+48;
  buffer_8[3]=0;
  
  
  // sprintf(buffer_8,"%d",value);
  draw_text( px,py,buffer_8,color,0);
}

// ===============================
// * Afficher une valeur 16 bits *
// ===============================
void draw_text_value_16 (unsigned char px,unsigned char py,  unsigned int value,unsigned char color)
{

  unsigned int buffer;
  
  buffer_16[0] = value/10000;
  buffer = value-( buffer_16[0]*10000);
  
  buffer_16[1] = value/1000;
  buffer = value-( buffer_16[1]*1000);
  
   buffer_16[2] = value/100;
  buffer = value-( buffer_16[2]*100);
  
   buffer_16[3] = value/10;

  
 
   buffer_16[4] = value-( buffer_16[3]*10);
   buffer_16[5] = 0;
  /*
   0->65535
   
   B1=value/10000 (6)
   buffer = value-(B1*10000) = 5535
   
   B2 = buffer / 1000  = 5.535
   buffer = buffer-(B2*1000)  535
   
   B3 = buffer / 100  5.35
   buffer = buffer-(B3*100)  35
   
      
   B4 = buffer / 10  3.5
   B5 = buffer-(B4*10) 5
   
      

   
  */
  
 // sprintf(buffer_16,"%u",value);
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
 /**********************************************************
  ********              Happy Random               *********
  **********************************************************
  * Role ........... : Gestion aléatoire                   *
  * Auteur ......... : Jean Monos                          *
  * Modification ... : 14/03/2021                          *
  * Licence ........ : Creative Commons by-sa              *
  * Compilateur .... : cc65                                *
  **********************************************************/
    
// ====================
// * Fichier includes *
// ====================
#include <happyc64.h>
#include <stdlib.h>
// ===============================================
// * Généré un nombre pseudo aléatoire du 8 bits *
// ===============================================
unsigned char get_rnd(unsigned char max_number)
{
  // -------------------------------------
  // * Declaration des variables locales *
  // -------------------------------------
  unsigned char valeur_genere = 0;
 
  
  // ----------------------------------
  // * Boucle de génération aléatoire *
  // ----------------------------------
 
   
   do 
   {
     valeur_genere = rand()&0xFF;
     
     
   } while (valeur_genere>max_number);

  
  
  return valeur_genere;
  
}

// =================================================
// * Généré un nombre pseudo aléatoire sur 16 bits *
// =================================================
unsigned int get_rnd16(unsigned int max_number)
{
   // -------------------------------------
   // * Declaration des variables locales *
   // -------------------------------------
   unsigned int valeur_genere = 0;
 


   do 
   {
     valeur_genere = rand()&0xFFFF;
     
   } while (valeur_genere>max_number);

  return valeur_genere;  
}
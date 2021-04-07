 /**********************************************************
  ********              Happy D7                ************
  **********************************************************
  * Role ........... : Gestion disquette                   *
  * Auteur ......... : Jean Monos                          *
  * Modification ... : 13/03/2021                          *
  * Licence ........ : Creative Commons by-sa              *
  * Compilateur .... : cc65                                *
  **********************************************************/
  
// ====================
// * Fichier includes *
// ====================
#include <happyc64.h>
#include <cbm.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

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

// ================================================
// * Recuperer erreur d'une opération de diquette *
// ================================================
unsigned char get_error(void)
{
  return _oserror;
}
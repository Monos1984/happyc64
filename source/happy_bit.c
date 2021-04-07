 /**********************************************************
  ********              Happy BIT               ************
  **********************************************************
  * Role ........... : Gestion sur les octets              *
  * Auteur ......... : Jean Monos                          *
  * Modification ... : 13/03/2021                          *
  * Licence ........ : Creative Commons by-sa              *
  * Compilateur .... : cc65                                *
  **********************************************************/

// ====================
// * Fichier includes *
// ====================
#include <happyc64.h>

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
// * unset_bit(numero du bit, valeur à modifier) *
// =============================================
unsigned char unset_bit(unsigned char id_bit, unsigned char value)
{
    return value = value &(~(1<<id_bit));
}

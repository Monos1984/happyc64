 /**********************************************************
  ********              Happy Sid               ************
  **********************************************************
  * Role ........... : Routine sonore                      *
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

// =================
// * Jouer sun son *
// =================

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
  // -------------------------------------
  // * Mise à 0 des registres de la voix *
  // -------------------------------------
  memset((void*)(54272L+voice),0,7); 
  
  // --------------------------------
  // * Poker les valeurs en mémoire *
  // --------------------------------
  POKE(R_SID+voice,lb_freq);
  POKE(R_SID+voice+1,hb_freq);
  POKE(R_SID+voice+2,lb_pulse);
  POKE(R_SID+voice+3,hb_pulse);
  POKE(R_SID+voice+4,waveforme);
  POKE(R_SID+voice+5,attaque_decay);
  POKE(R_SID+voice+6,sustain_release);
  
}

// ======================
// * Modifier le volume *
// ====================== 
void set_volume(unsigned char volume)
{
  POKE(R_SID+24,volume);
}

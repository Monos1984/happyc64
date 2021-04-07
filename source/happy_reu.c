 /**********************************************************
  ********              Happy Reu               ************
  **********************************************************
  * Role ........... : Gestion ramcard                     *
  * Auteur ......... : Jean Monos                          *
  * Modification ... : 13/03/2021                          *
  * Licence ........ : Creative Commons by-sa              *
  * Compilateur .... : cc65                                *
  **********************************************************/
  
  // ====================
  // * Fichier includes *
  // ====================
  #include <happyc64.h>
  
  // =============================
  // * Configurer adresse du C64 *
  // =============================
  void reu_set_adresse_c64(unsigned int adresse)
  {
    POKEW(0xDF02,adresse);
  }
  
  // ===============================
  // * Configurer l'adresse du Reu *
  // ===============================
  void reu_set_adresse_reu(unsigned int adresse,unsigned char id_bank)
  {
    POKEW(0xDF04,adresse);
    POKE(0xDF06,id_bank);
  }
  
  // =========================================
  // * Configurer la taille d'octet à copier *
  // =========================================
  void reu_set_size(unsigned int size)
  {
    POKEW(0xDF07,size);
  }
  
  // =========================
  // * Lancement de la copie *
  // =========================
  void reu_start_dma(unsigned char value)
  {
    POKE(0xDF01,value);
  }
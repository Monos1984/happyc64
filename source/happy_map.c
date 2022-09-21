 /**********************************************************
  ********              Happy Map               ************
  **********************************************************
  * Role ........... : Gestion Map                         *
  * Auteur ......... : Jean Monos                          *
  * Modification ... : 20/09/2022                          *
  * Licence ........ : Creative Commons by-sa              *
  * Compilateur .... : cc65                                *
  **********************************************************/
  
  // ====================
  // * Fichier includes *
  // ====================
  #include <happyc64.h>
  
  // ===================
  // * Variable Global *
  // ===================
  unsigned char hm_size_x;
  unsigned char hm_size_y;
  
  unsigned char hm_offset_x;
  unsigned char hm_offset_y;
  
  unsigned char tiles_buffer[512];
  unsigned char buffer_map[240];
  
  // ===============================
  // * Taille en largeur de la map *
  // ===============================
  void hm_set_map_size_x(unsigned char value)
  {
    hm_size_x = value;
  }
  
  // ===============================
  // * Taille en hauteur de la map *
  // ===============================
  void hm_set_map_size_y(unsigned char value)
  {
    hm_size_y = value;
  }

  // =========================================
  // * Position X du premier tiles de la map *
  // =========================================  
  void hm_set_map_offset_x(unsigned char value)
  {
    hm_offset_x = value;
  }
  
  // ========================================
  // * Position Y du premier tile de la map *
  // ========================================
  void hm_set_map_offset_y(unsigned char value)
  {
    hm_offset_y = value;
  }

  // =================================
  // * Modifier l'id tiles de la map *
  // =================================
  void hm_set_buffer_map(unsigned char px,unsigned char py,unsigned char value)
  {
    buffer_map[py*hm_size_x+px]=value;    
  }


  // ==================
  // * Set Tiles Data *
  // ==================
  void hm_set_tile_data(unsigned char id_mt,unsigned char id_1,unsigned char id_2,unsigned char id_3,unsigned char id_4,unsigned char color_1,unsigned char color_2,unsigned char color_3,unsigned char color_4)
  {
    // -------------------
    // * Variable locale *
    // -------------------
    unsigned int offset_id_mt;
    
    // ----------------------------
    // * Calcule de l'index tiles *
    // ----------------------------
    offset_id_mt = id_mt * 8;
    
    // -----------------------------------
    // * enregistrement des informations *
    // -----------------------------------
    tiles_buffer[offset_id_mt]   = id_1;
    tiles_buffer[offset_id_mt+1] = id_2;
    tiles_buffer[offset_id_mt+2] = id_3;
    tiles_buffer[offset_id_mt+3] = id_4;
    tiles_buffer[offset_id_mt+4] = color_1;
    tiles_buffer[offset_id_mt+5] = color_2;
    tiles_buffer[offset_id_mt+6] = color_3;
    tiles_buffer[offset_id_mt+7] = color_4;  
  }

  // =============================
  // * Afficher la map à l'ecran *
  // =============================
  void hm_draw_map()
  {
    // -----------------------------
    // * Declaration des variables *
    // -----------------------------
    unsigned char px,py,id_tiles,pxt,pyt;
    unsigned int offset_octet_tiles,offset_id_tiles;
    
    // --------------------------------
    // * Boucle d'affichage de la map *
    // --------------------------------
    for (py=0;py<hm_size_y;py++)
    {
      for (px=0;px<hm_size_x;px++)
      {
        // ----------------------------
        // * Calcule des informations *
        // ----------------------------
        offset_octet_tiles = py*hm_size_x + px;
        id_tiles = buffer_map[offset_octet_tiles];
        offset_id_tiles = id_tiles*8;
        pxt = px*2+hm_offset_x;
        pyt = py*2+hm_offset_y;
        
        // -----------------------
        // * Affichage de la map *
        // -----------------------
        draw_full_character(pxt,pyt,tiles_buffer[offset_id_tiles],tiles_buffer[offset_id_tiles+4]);
        draw_full_character(pxt+1,pyt,tiles_buffer[offset_id_tiles+1],tiles_buffer[offset_id_tiles+5]);
        draw_full_character(pxt,pyt+1,tiles_buffer[offset_id_tiles+2],tiles_buffer[offset_id_tiles+6]);
        draw_full_character(pxt+1,pyt+1,tiles_buffer[offset_id_tiles+3],tiles_buffer[offset_id_tiles+7]);
       
      }
            
    }
    
  }
  
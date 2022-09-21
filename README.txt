**************************************
***            Happy C64           ***
**************************************
Librairie de fonction en C pour programmer le commodore 64 avec le compilateur CC65
Ecrit par Loïc Lété (Jean Monos)

=========================
* Licence d'utilisation *
=========================
- La librairie ne peux pas être vendu.
- L'utilisation de la librairie dans les programmes commerciaux est autorisé.
- Le Droit auteur : Un petit "Fait avec HappyC64" Ou ce genre de chose est très apréciable. 
- Le code source de Happy C64 est présent, vous pouvez le modifier pour votre utilisation et le redistribuer sous les mêmes conditions.

==============================
* Changement de la librairie *
==============================
mise à jour le 21/09/2022

===============================================
============= Version 0.2.x.x =================
===============================================

===================================
* Changement 0.2.4.0 (21/09/2022) *
===================================
- Ajout de fonction pour gérer une map en toute simplicité.

=======================
* Changement Hors Lib *
=======================
- Ajout du dossier cartridge qui contient deux fichier cfg, deux fichier objet 
- Ajout du logiciel mcart.exe recompilé pour fonctionner sur un os windows64bits.
 

======================
* Changement 0.2.3.5 *
======================
- Correction dans le header de la fonction set_sprite_multicolore_on()
- Ajout de fonction pour gérer le paddle. (Bêta et non documenté)
- Modification du makefile pour compiler vos projets en cartouche standard 8 et 16ko.
- Ajout de .bat de compilation

======================
* Changement 0.2.3.0 *
======================
- Ajout de la fonction get_color_map(...)
- Ajout de la fonction get_id_character(...) 

======================
* Changement 0.2.2.0 *
======================
- Activation de la fonction init_adr_irq();

======================
* Changement 0.2.1.1 *
======================
- Correction sur la fonction draw_sprite().

======================
* Changement 0.2.1.0 *
======================
- Ajout de la fonction wait_time(value); qui permet d'attendre un certain nombre de VBL.
- Amélioration de la fonction get_rnd() et get_rnd16().

======================
* Changement 0.2.0.0 *
======================
- Mise à jour du code source de la librairie. Le code source est séparé par theme.
- Diminution de la taille du programme dans la plupars des cas.  

===============================================
============= Version 0.1.x.x =================
===============================================

======================
* Changement 0.1.5.1 *
======================
- Correction de la fonction set_sound() pour jouer du son sur commodore 64.

======================
* Changement 0.1.5.0 *
======================
Ajout de fonction pour manipuler le mode bitmap
- Void draw_pixel(unsigned int px,unsigned int py)
- Void set_bitmap_color_map(unsigned char px, unsigned char py, unsigned char color_ink, unsigned char color_background)
- Void cls_bitmap_color_ram(unsigned char ink_color,unsigned char background_color)
- Void cls_bitmap()

======================
* Changement 0.1.4.0 *
======================
Ajout de trois fonction pour tester un bit dans un octet.
- get_bit(id,value)
- set_bit(id,value)
- unset_bit(id,value)

======================
* Changement 0.1.3.0 *
======================
- ajout de commande pour utiliser une extension REU simplement
- amélioration interne de la fonction draw_character_line_H()
- Ajout de get_rnd16(max_number)
- Ajout de set_shift_off()
- Ajout de set_shift_on()

======================
* Changement 0.1.2.0 *
======================
- Ajout du paramètre slow_wait_letter dans draw_text();
- Ajout de la fonction draw_bloc_text();
- Ajout de la fonction wait_key();
- Les define du joystick débute maintenant par un J_


======================
* Changement 0.1.1.0 *
======================
- Ajout de la fonction get_error() qui permet de renvoyer le code d'erreur d'un chargement de fichier.
- la fonction load_file(...) renvois le nombre d'octet chargé en mémoire. (Si 0 = une erreur)

======================
* Changement 0.1.0.0 *
======================
Grosse modification des noms de fonctions.

-load_pattern devient set_data_character()
-draw_full_charset devient draw_full_character
-draw_charset devient draw_character
-draw_charsetligne_v (et h) passe en draw_character...
(note le terme charset est remplacé par character)
-set_pointeurs_sprites devient set sprite pointers
- draw_valeur_8 (et 16) devient draw_text_value_8 (et 16)
- set_pointeur_text devient set_text_pointer()
- activation de get_adresse_screen_memory


===============================================
============= Version 0.0.x.x =================
===============================================

=======================
* Changement 0.0.10.0 *
=======================
- Ajout de la fonction void rle_decompression(); qui permet de decompresser des datas en mode RLE.

----------------------
* Changement 0.0.9.0 *
----------------------
- Ajout de PEEKW() et POKEW() qui permet de lire une valeur 16 bits dans la mémoire.

----------------------
* Changement 0.0.8.0 *
----------------------
- Ajout de la fonction draw_charset_line_H() et draw_charset_line_V()
- Ajout de la fonction cls_color_map()


----------------------
* Changement 0.0.7.0 *
----------------------
- Ajout de la fonction draw_text();
- Ajout de la fonction set_pointeur_text();
- Ajout de la fonction draw_valeur_16() et draw_valeur_8() qui permettent d'afficher des valeurs 8 et 16 bits meme contenue dans une variable char ou int.
- modification interne du cls(id_tiles). On passe par un memset au lieu de boucle. Amélioration de vitesse.

----------------------
* Changement 0.0.6.0 *
----------------------
- Ajout de la fonction pour changer le background 3 pour le mode extended.

----------------------
* Changement 0.0.5.0 *
----------------------
- Ajout de la fonction load_file() 
- Ajout de la fonction save_file()
- Correction des adresses du timer A et B.

----------------------
* Changement 0.0.4.0 *
----------------------
- Correction de bug lord du changement de vic bank. La variable generique pour poser un tiles n'était pas mis à jour au bonne endroit.
- Ajout d'une fonction pour modifier l'adresse (internet) de la tilemap pour utiliser les fonctions propre draw_tiles.
- Changer de vic_bank et de pointeur de screen change automatiquement cette variable !

----------------------
* Changement 0.0.3.3 *
----------------------
- Le chargement des Assets (Sprite et charset) ne se font plus par boucle for, mais par memcpy !

----------------------
* Changement 0.0.3.2 *
----------------------
- Correction d'une parenthèse dans la fonction set_interruption_on();
- Wait VBL opérationel. (Ce n'étais pas le cas jusque la)
- Les fonctions du fichier cbm.h sont accecible.
 
----------------------
* Changement 0.0.3.1 *
----------------------
- Correction d'une erreur avec le choix de la couleur du paper
- léger Amélioration de vitesse pour afficher un tile à l'écran 

----------------------
* Changement 0.0.3.0 *
----------------------
Ajout de get_system() qui permet de tester si la machine est en PAL ou en NTSC

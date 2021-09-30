README.TXT for mcart 0.64 (25. Apr 2006)

mcart is Copyright (C) 1998-2006 Markus Brenner
homepage: http://markus.brenner.de


========================================
= Introduction                         =
========================================

    mcart is a command line tool for generating C64 emulator cartridge files
    (.CRT) from standard 8k or 16k cartridge ROM dumps. ROM dumps can either
    be in .PRG form (first two bytes are start address of ROM dump in low-high
    byte order) or plain data files (.ROM suffix). mcart also handles a number
    of utility and X-Large (bankswitching) cartridge types.


   REQUIREMENTS:

   - MS-DOS executable was compiled using the DJGPP GNU-C compiler, so you
     need the cwsdpmi.exe file for running.

   mcart is *free* software released under the GNU General Public License,
   and as such comes with full source code. If you like the program and want
   to show your appreciation, send me a C64- or C16-cartridge!


========================================
= Usage                                =
========================================

   mcart [-carttype] <input> <"game name">

   <input> is the input file (cartridge dump), either in .PRG or .ROM
     format.

   <"game name"> is the title string of the game.

   [-carttype] specifies one of the following NON-STANDARD cartridges:

   -ar  Action Replay
   -at  Atomic Power
   -b   Simons' BASIC
   -d   Dinamic (Narco Police)
   -e   Epyx Fastload
   -fc1 Final Cartridge I
   -fc3 Final Cartridge III
   -fp  Fun Play, Power Play
   -g   C64GS cartridge, System 3
   -k   KCS Power Cartridge
   -ma  MIKRO Assembler
   -md  Magic Desk, Domark, HES Australia
   -n   Nordic Power
   -o   Ocean 1 (Standard)
   -o2  Ocean 2 (Chase H.Q. 2)
   -r   Rex Utility
   -s   Super Games (Commodore)
   -u   Ultimax
   -we  Westermann learning cartridges
   -ws  Warpspeed (Cinemaware)
   -z   Zaxxon/Super Zaxxon (Sega)

   Ultimax carts use a different hardware configuration and typically
   start at $e000.


   examples:

   mcart pitfall.prg "PITFALL"
   mcart -e epyxfl.rom "EPYX FASTLOAD"
   mcart -u clowns.rom "CLOWNS"
  

========================================
= History                              =
========================================

   0.31  experimental (for standard 8k, 16k and Ultimax cartridges)
   0.33  fixed ULTIMAX ROM start address
   0.34  fixed EPYX FASTLOAD cartridge
   0.35  added WESTERMANN type
   0.36  better ROM dump recognition
   0.37  added ACTION REPLAY type
   0.38  added FINAL CARTRIDGE III type
   0.39  added SIMONS' BASIC type
   0.40  fixed bug in 'Standard 16K' type
   0.41  added REX Datentechnik type
   0.42  added FINAL CARTRIDGE 1 type
   0.43  cleaned up program
   0.44  added ATOMIC POWER / NORDIC POWER type
   0.45  fixed OCEAN 128K Carts
   0.46  added OCEAN 512K Cart support (T2)
   0.47  added KCS Power Cartridge type
   0.48  added preliminary C64GS type support
   0.49  added preliminary Comal-80 support
   0.50  modified ULTIMAX support (now allows $1000 carts)
   0.51  changed some cartridge numbers ($0e/$0f)
   0.52  added WARPSPEED type
   0.53  added Magic Desk support (preliminatry)
   0.54  changed flags for OCEAN carts to EXROM=GAME=0
   0.55  added DINAMIC type (Narco Police)
   0.56  Minor fix of screen output for 32kB Ocean type (Ghostbusters)
   0.57  added 'Badlands' support as Ocean 64kB type
   0.58  cleaned up program
   0.59  added 'Zaxxon' (SEGA) support (preliminary)
   0.60  added automatic $a000 'BASIC' detection
   0.61  fixed some bugs in doublecode() function
   0.62  extended Magic Desk type to Domark and HES-Australia
   0.63  added COMAL-80 and Super Snapshot 5
   0.64  added MIKRO ASSEMBLER


========================================
= Links and additional Information     =
========================================

  The latest version of this program is available on
  http://arnold.ml.org/~minstrel/


   - Hakan Sundell's .CRT specification
     http://www.computerbrains.com/crtformat.htm

   - Instructions on dumping cartridges
     http://arnold.c64.org/~minstrel/cartridge/

   - Ben Castricums's cartridge archive at
     http://cia.c64.org/

   - Mat Allen's Mayhem in Monsterland page, containing cover scans and
     rom dumps of his massive cartridge collection
     http://www.mayhem64.co.uk/


   "Thank you!" to all people who helped me out with information:

   - Mat Allen
   - Andreas Boose
   - Ben Castricum
   - Peter Fischer
   - Joe Forster
   - Pav Gill
   - Marco van den Heuvel
   - Holger Klipsch
   - Chris Link
   - Adam Lorentzon
   - Hans Pieters
   - Peter Schepers
   - Hakan Sundell


# ===========================
# Makefile Happy C64
# par Jean Monos
# version 1.2 du 01/10/2021
# ===========================

# ====================
# Lancer le makefile #
# ====================

# -----------------------------------------
# ..\..\outils\makefile\make
# Compilation simple du programme.prg
# -----------------------------------------

# -----------------------------------------
# ..\..\outils\makefile\make FLOPPY
# Compilation prg + D7
# -----------------------------------------

# -----------------------------------------
# ..\..\outils\makefile\make tap
# Compilation prg + tap
# -----------------------------------------

# -----------------------------------------
# ..\..\outils\makefile\make floptap
# Compilation prg + tap + d7
# -----------------------------------------


# ================================
# Configuration Manuel du makefile 
# ================================

# ----------------
# Nom du programme
# ---------------- 
NAME=cassebr

# ------------------
# Nom de la diquette
# ------------------
name_d64=cassebr.d64

# -----------------
# Nom de la casette
# -----------------
name_tape=cassebr.tap

# ------------------
# Nom du fichier crt
# -----------------
name_crt=cartouche

# -----------------
# Dossier de sortie
# -----------------
OUT=bin

# -------------------
# Dossier Code source 
# -------------------
SOURCE= $(CURDIR)/source

# -------------------
# Dossier  mcart64
# -------------------
make_mcart64=../../outils/mcart64/mcart.exe
# -------------------
# Dossier Cartouche 
# -------------------
ADR_CARTOUCHE=../../cartridge
# ------------------------------------
# Dossier des datas seq et prg externe
#--------------------------------------
dossier_data = data

# ================================================================
# Autre configuration ou pas touche a cela petit con si tu debutes
# ================================================================

# -----------------------------
# Adresse divers pre configurer 
# -----------------------------
CC = $(CURDIR)/../../cc65/bin/cl65.exe 
create_d64= $(CURDIR)/../../outils/cc1541/cc1541.exe
create_tape= $(CURDIR)/../../outils/waw-prg/prg2wav.exe


ADROUT=$(CURDIR)/$(OUT)

HAPPY=$(CURDIR)/../../hpc
CRULE=-o $(ADROUT)/$(NAME).prg -u __EXEHDR__  -O -t c64 --include-dir $(HAPPY)/header 
CRULE8K=-o $(ADROUT)/$(NAME).bin -O --config ../../cartridge/cart64_8k.cfg --include-dir $(HAPPY)/header 
CRULE16K=-o $(ADROUT)/$(NAME).bin -O --config ../../cartridge/cart64_16k.cfg --include-dir $(HAPPY)/header 
CFILES := $(sort $(wildcard $(SOURCE)/*.c))


# -------------------------------------------------
# Memorisation des fichier seq et prg du mode data 
# -------------------------------------------------
DATAFILESSEQ=  $(notdir $(wildcard $(dossier_data)/*.seq))
DATASEQ = $(DATAFILESSEQ:.seq=)

DATAFILESPRG=$(notdir $(wildcard $(dossier_data)/*.prg))
DATAPRG = $(DATAFILESPRG:.prg=)

# -------------------
# Luncher du makefile 
# -------------------
.PHONY: all
all:  introduction clean_bin compilation 
floppy:  introduction clean_bin compilation d64
tap:  introduction clean_bin compilation tape
floptap:  introduction clean_bin compilation d64 tape
crt8k:  introduction clean_bin compilation8k makecrt
crt16k:  introduction clean_bin compilation16k makecrt

# ========================
# Introduction du makefile 
# ========================
introduction:
	@echo ======================
	@echo = MAKEFILE HAPPY C64 =
	@echo = Version 1.2.0      =
	@echo ======================

	
# ===========
# Compilation 
# ===========
compilation: 
	@echo ============================
	@echo = Compilation Commodore 64 =
	@echo ============================
 	
	@$(CC) $(CRULE) $(CFILES) $(HAPPY)/happyc64.lib
	@echo compilation $(NAME).prg

# ==================
# Compilation crt 8k 
# ==================
compilation8k: 
	@echo ===================================
	@echo = Compilation Commodore 64 CRT 8k =
	@echo ===================================
	
	@$(CC) $(CRULE8K) $(CFILES)  $(HAPPY)/happyc64.lib $(ADR_CARTOUCHE)/cart64_8k.o
	@echo compilation $(NAME).bin

# ==================
# Compilation crt 16k 
# ==================
compilation16k: 
	@echo ===================================
	@echo = Compilation Commodore 64 CRT 16k =
	@echo ===================================
	
	@$(CC) $(CRULE16K) $(CFILES)  $(HAPPY)/happyc64.lib $(ADR_CARTOUCHE)/cart64_8k.o
	@echo compilation $(NAME).bin

# ======================== 
# Effacement du dossier bin 
# =========================
clean_bin:
	@echo ===========================
	@echo = Effacement des fichiers =
	@echo ===========================
	@rm -f $(ADROUT)/*.prg
	@rm -f $(ADROUT)/*.d64
	@rm -f $(ADROUT)/*.rp9
	@rm -f $(ADROUT)/*.tap
	@rm -f $(ADROUT)/*.bin
	@rm -f $(ADROUT)/*.CRT
	@echo erase files prg, d64 et rp9 tap bin crt 	

# =========================================================
# Creation de la disquette avec les datas si elles existent
# =========================================================
d64:
	@echo ---------------------------
	@echo = Creation de la diquette =
	@echo ---------------------------
	@$(create_d64) -f $(NAME) -T PRG   -w $(ADROUT)/$(NAME).prg   -n $(NAME) $(ADROUT)/$(name_d64)

		
	@echo ---------------
	@echo = Fichier SEQ =
	@echo ---------------
	@for fileseq in $(DATASEQ); do\
		echo $$fileseq;\
		$(create_d64) -f $$fileseq -T SEQ   -w $(CURDIR)/$(dossier_data)/$$fileseq.seq   -n $(NAME) $(ADROUT)/$(name_d64) ;\
	done

	
	@echo ---------------
	@echo = Fichier PRG =
	@echo ---------------
	@for fileprg in $(DATAPRG); do\
		echo $$fileprg;\
		$(create_d64) -f $$fileprg -T PRG   -w $(CURDIR)/$(dossier_data)/$$fileprg.prg   -n $(NAME) $(ADROUT)/$(name_d64) ;\
	done	
  

# ======================== #
# Creation du fichier TAPE #
# ======================== #

tape:
	@echo ----------------
	@echo = Fichier TAPE =
	@echo ----------------
	@$(create_tape) -t $(ADROUT)/$(name_tape) $(ADROUT)/$(NAME).prg


# ======================== #
# Creation du fichier CRT #
# ======================== #
makecrt:
	@echo ----------------
	@echo = Fichier CRT  =
	@echo ----------------
	@$(make_mcart64) $(ADROUT)/$(NAME).bin $(name_crt)
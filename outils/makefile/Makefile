# ===========================
# Makefile Happy C64
# par Jean Monos
# version 1.1 du 10/04/2021
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
NAME=exemple

# ------------------
# Nom de la diquette
# ------------------
name_d64=exemple.d64

# -----------------
# Nom de la casette
# -----------------
name_tape=exemple.tap

# -----------------
# Dossier de sortie
# -----------------
OUT=bin

# -------------------
# Dossier Code source 
# -------------------
SOURCE= $(CURDIR)/source

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
# ========================
# Introduction du makefile 
# ========================
introduction:
	@echo ======================
	@echo = MAKEFILE HAPPY C64 =
	@echo = Version 1.0.0      =
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

# =========================
# Effacement du dossier bin 
# =========================
clean_bin:
	@echo ===========================
	@echo = Effacement des fichiers =
	@echo ===========================
	@rm -f $(ADROUT)/*.prg
	@rm -f $(ADROUT)/*.d64
	@rm -f $(ADROUT)/*.rp9
	@echo erase files prg, d64 et rp9 	

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
  
tape:
	@echo ----------------
	@echo = Fichier TAPE =
	@echo ----------------
	@$(create_tape) -t $(ADROUT)/$(name_tape) $(ADROUT)/$(NAME).prg
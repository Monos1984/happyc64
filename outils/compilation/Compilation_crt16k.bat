@echo off

echo *********************************************************************
echo * Fichier bat de compilation hors makefile version 2.0 du 4/10/2021 *
echo *                           version crt16k                           * 
echo * *******************************************************************

echo ----------------------------------------
echo * Compilation pour C64 en cartouche 16k *
echo ----------------------------------------

rem -------------------------------------------
rem * Configuration du fichier de compilation *
rem -------------------------------------------

rem --------------------
rem * Nom du programme *
rem -------------------- 
set prg_prog=c64

rem -------------------------------
rem * Autre lien de configuration *
rem -------------------------------
set cl65=..\..\cc65\bin\cl65
set cc65=..\..\cc65\bin\
set adr_source=source\
set adr_out=bin
set adr_happy=..\..\hpc
set fichier= %adr_source%main.c 
set ADR_CARTOUCHE=..\..\cartridge
set mcart64=..\..\outils\mcart64\mcart.exe
 
rem --------------------------------------
rem * preparation du dossier exportation *
rem --------------------------------------
if exist "%adr_out%\*.prg" del %adr_out%\*.prg
if exist "%adr_out%\*.d64" del %adr_out%\*.d64
if exist "%adr_out%\*.t64" del %adr_out%\*.t64
if exist "%adr_out%\*.tap" del %adr_out%\*.tap
if exist "%adr_out%\*.rp9" del %adr_out%\*.rp9
if exist "%adr_out%\*.bin" del %adr_out%\*.bin
if exist "%adr_out%\*.CRT" del %adr_out%\*.CRT

rem ---------------
rem * compilation *
rem ---------------

%cl65% -o %adr_out%/%prg_prog%.bin -O --config ../../cartridge/cart64_16k.cfg  --include-dir %adr_happy%/header %fichier% %adr_happy%\happyc64.lib %ADR_CARTOUCHE%/cart64_16k.o

if exist %adr_out%/%prg_prog%.bin echo %prg_prog%.bin present dans le dossier %adr_out%


rem ------------------
rem * Cration du crt *
rem ------------------

%mcart64% %adr_out%/%prg_prog%.bin %prg_prog%

echo ------------------------------------------------
if exist %adr_out%/%prg_prog%.crt echo %prg_prog%.crt present dans le dossier %adr_out%

rem ----------
rem * menage *
rem ----------
echo -----------------------------
echo * Effacement des fichier .o *
echo -----------------------------
pause
if exist "%adr_source%*.o" del %adr_source%*.o
pause
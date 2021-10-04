@echo off

echo *********************************************************************
echo * Fichier bat de compilation hors makefile version 2.0 du 4/10/2021 *
echo *                           version tap (cassette)                  * 
echo * *******************************************************************

echo -------------------------------
echo * Compilation pour C64 en tap *
echo -------------------------------

rem -------------------------------------------
rem * Configuration du fichier de compilation *
rem -------------------------------------------

rem --------------------
rem * Nom du programme *
rem -------------------- 
set prg_prog=c64.prg
set tap_prog=c64.tap
rem -------------------------------
rem * Autre lien de configuration *
rem -------------------------------
set cl65=..\..\cc65\bin\cl65
set cc65=..\..\cc65\bin\
set adr_source=source\
set adr_out=bin
set adr_happy=..\..\hpc
set fichier= %adr_source%main.c 
set prg2wav=..\..\outils\waw-prg\prg2wav.exe 
 
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

%cl65% -o %adr_out%/%prg_prog% -u __EXEHDR__  -O -t c64  --include-dir %adr_happy%/header %fichier% %adr_happy%\happyc64.lib

if exist %adr_out%/%prg_prog% echo %prg_prog% present dans le dossier %adr_out%


rem --------------------------
rem * Cration de la cassette *
rem --------------------------

echo ---------------------------------
echo * Generation de la cassette c64 *
echo ---------------------------------
%prg2wav% -t %adr_out%/%tap_prog%  %adr_out%/%prg_prog%
echo ------------------------------------------------
if exist %adr_out%/%tap_prog% echo %tap_prog% present dans le dossier %adr_out%

rem ----------
rem * menage *
rem ----------
echo -----------------------------
echo * Effacement des fichier .o *
echo -----------------------------
pause
if exist "%adr_source%*.o" del %adr_source%*.o
pause
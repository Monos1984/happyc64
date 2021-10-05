@echo off

echo *********************************************************************
echo * Fichier bat de compilation hors makefile version 2.1 du 5/10/2021 *
echo *                           version d64                             * 
echo * *******************************************************************

echo -------------------------------
echo * Compilation pour C64 en d64 *
echo -------------------------------

rem -------------------------------------------
rem * Configuration du fichier de compilation *
rem -------------------------------------------

rem --------------------
rem * Nom du programme *
rem -------------------- 
set prg_prog=c64.prg
set name_d7=disquette.d64

rem -----------
rem * Dossier *
rem -----------
set adr_source=source\
set dossier_data=data
set adr_out=bin

rem ----------------------
rem * Fichier à compiler *
rem ----------------------
set fichier=%adr_source%main.c 

rem -------------------------------
rem * Autre lien de configuration *
rem -------------------------------
set cl65=..\..\cc65\bin\cl65
set cc65=..\..\cc65\bin\

set adr_happy=..\..\hpc
set cc1541=..\..\outils\cc1541\cc1541.exe 

 
rem --------------------------------------
rem * preparation du dossier exportation *
rem --------------------------------------
if exist "%adr_out%\*.prg" del %adr_out%\*.prg
if exist "%adr_out%\*.d64" del %adr_out%\*.d64
if exist "%adr_out%\*.t64" del %adr_out%\*.t64
if exist "%adr_out%\*.rp9" del %adr_out%\*.rp9
if exist "%adr_out%\*.bin" del %adr_out%\*.bin
if exist "%adr_out%\*.CRT" del %adr_out%\*.CRT
if exist "%adr_out%\*.tap" del %adr_out%\*.tap

rem ---------------
rem * compilation *
rem ---------------

%cl65% -o %adr_out%/%prg_prog% -u __EXEHDR__  -O -t c64  --include-dir %adr_happy%/header %fichier% %adr_happy%\happyc64.lib

if exist %adr_out%/%prg_prog% echo %prg_prog% present dans le dossier %adr_out%


rem --------------------------------
rem * Creation de la disquette d64 *
rem --------------------------------
%cc1541% -f %prg_prog% -T PRG -w %adr_out%/%prg_prog% -n %prg_prog% %adr_out%/%name_d7%


rem ------------------------------------------------------------------------------
rem * integration de fichier externe manuellement : Une ligne par fichier extern *
rem ------------------------------------------------------------------------------

for %%i in (%dossier_data%\*.seq) do ( 
echo ******************
echo %%~nxi
echo ******************
%cc1541% -f %%~ni -T SEQ -w %dossier_data%/%%~nxi -n %prg_prog% %adr_out%/%name_d7%
)


for %%i in (%dossier_data%\*.prg) do ( 
echo ******************
echo %%~nxi
echo ******************
%cc1541% -f %%~ni -T PRG -w %dossier_data%/%%~nxi -n %prg_prog% %adr_out%/%name_d7%
)

for %%i in (%dossier_data%\*.usr) do ( 
echo ******************
echo %%~nxi
echo ******************
%cc1541% -f %%~ni -T USR -w %dossier_data%/%%~nxi -n %prg_prog% %adr_out%/%name_d7%
)

rem %cc1541% -f nom_fichier -T PRG -w data/nom_fichier -n %prg_prog% %adr_out%/%name_d7%
rem %cc1541% -f nom_fichier -T SEQ -w data/nom_fichier -n %prg_prog% %adr_out%/%name_d7%
pause

echo *************************************************************
if exist %adr_out%/%name_d7% echo %prg_prog% present dans le dossier %adr_out%/%name_d7%
echo *************************************************************

rem ----------
rem * clear  *
rem ----------
echo -----------------------------
echo * Effacement des fichier .o *
echo -----------------------------
pause
if exist "%adr_source%*.o" del %adr_source%*.o
pause
echo off
rem -------------------------------------------
rem * Configuration du fichier de compilation *
rem -------------------------------------------

set cl65=..\..\cc65\bin\cl65
set cc65=..\..\cc65\bin\
set adr_source=source\
set adr_out=bin
set prg_prog=sprite.prg
set adr_happy=..\..\hpc

rem --------------------------------------
rem * preparation du dossier exportation *
rem --------------------------------------
if exist "%adr_out%\*.prg" del %adr_out%\*.prg
if exist "%adr_out%\*.rp9" del %adr_out%\*.rp9
rem ---------------
rem * compilation *
rem ---------------



%cl65% -o %adr_out%/%prg_prog% -O -t c64 --include-dir %adr_happy%/header %adr_source%main.c %adr_happy%\happyc64.lib 
pause

rem ----------
rem * menage *
rem ----------
if exist "%adr_source%*.o" del %adr_source%*.o
pause
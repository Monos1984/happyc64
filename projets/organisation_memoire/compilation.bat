echo off
rem -------------------------------------------
rem * Configuration du fichier de compilation *
rem -------------------------------------------

set cl65=..\..\cc65\bin\cl65
set cc65=..\..\cc65\bin\
set adr_source=source\
set adr_out=bin
set prg_prog=organisation.d64
set adr_happy=..\..\hpc

set fichier=%adr_source%main.c

rem --------------------------------------
rem * preparation du dossier exportation *
rem --------------------------------------
if exist "%adr_out%\*.prg" del %adr_out%\*.prg
if exist "%adr_out%\*.d64" del %adr_out%\*.d64
if exist "%adr_out%\*.rp9" del %adr_out%\*.t64

if exist "%adr_out%\*.rp9" del %adr_out%\*.rp9

rem ---------------
rem * compilation *
rem ---------------

%cl65% -o %adr_out%/%prg_prog% -u __EXEHDR__  -O -t c64  --include-dir %adr_happy%/header %fichier% %adr_happy%\happyc64.lib
pause

rem ----------
rem * menage *
rem ----------
if exist "%adr_source%*.o" del %adr_source%*.o
pause
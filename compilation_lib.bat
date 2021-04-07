@echo off

echo --------------------------------------------------
echo - Script de compilation de la librarie happy C64 -
echo -               Codeur : Jean Monos              -
echo - Modification du 07/04/21                       -
echo --------------------------------------------------

rem  *********************************
rem  * Configuration de la librairie *
rem  *********************************
set adr_source=source
set adr_lib=hpc
set adr_nom=happyc64

echo --------------------------------
echo - Preprocesseur et compilation -
echo --------------------------------

for %%i in (%adr_source%\*.c) do ( 
echo %%~nxi
 )

cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happyc64.c
cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happy_sid.c
cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happy_sprite.c
cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happy_texte.c
cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happy_d7.c
cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happy_reu.c
cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happy_bitmap.c
cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happy_io.c
cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happy_rle.c
cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happy_vic.c
cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happy_random.c
cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happy_scrolling.c
cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happy_bit.c
cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happy_raster.c
cc65\bin\cc65 -O -t c64 --include-dir %adr_source%/header %adr_source%/happy_timer.c

echo --------------
echo - Assemblage -
echo --------------
for %%i in (%adr_source%\*.s) do ( 
echo %%~nxi
 )
cc65\bin\ca65 %adr_source%/happyc64.s 
cc65\bin\ca65 %adr_source%/happy_sid.s 
cc65\bin\ca65 %adr_source%/happy_sprite.s 
cc65\bin\ca65 %adr_source%/happy_texte.s 
cc65\bin\ca65 %adr_source%/happy_d7.s
cc65\bin\ca65 %adr_source%/happy_reu.s
cc65\bin\ca65 %adr_source%/happy_bitmap.s
cc65\bin\ca65 %adr_source%/happy_io.s
cc65\bin\ca65 %adr_source%/happy_rle.s
cc65\bin\ca65 %adr_source%/happy_vic.s
cc65\bin\ca65 %adr_source%/happy_random.s
cc65\bin\ca65 %adr_source%/happy_scrolling.s
cc65\bin\ca65 %adr_source%/happy_bit.s
cc65\bin\ca65 %adr_source%/happy_raster.s
cc65\bin\ca65 %adr_source%/happy_timer.s

echo -------------------
echo - Editeur de lien -
echo -------------------
for %%i in (%adr_source%\*.o) do ( 
echo %%~nxi
 )
cc65\bin\ar65 r %adr_lib%/happyc64.lib %adr_source%/happyc64.o %adr_source%/happy_sid.o %adr_source%/happy_sprite.o %adr_source%/happy_texte.o %adr_source%/happy_d7.o %adr_source%/happy_reu.o %adr_source%/happy_bitmap.o %adr_source%/happy_io.o %adr_source%/happy_rle.o %adr_source%/happy_vic.o %adr_source%/happy_random.o %adr_source%/happy_scrolling.o %adr_source%/happy_bit.o %adr_source%/happy_raster.o %adr_source%/happy_timer.o 


pause

echo -------------------
echo - Deplacement lib -
echo -------------------
del  %adr_lib%\header\happyc64.h
copy %adr_source%\header\happyc64.h %adr_lib%\header\happyc64.h

echo ------------
echo - Netoyage -
echo ------------
del %adr_source%\*.o
del %adr_source%\*.s


pause
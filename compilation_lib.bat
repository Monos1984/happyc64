@echo off

echo --------------------------------------------------
echo - Script de compilation de la librarie happy C64 -
echo -               Codeur : Jean Monos              -
echo --------------------------------------------------

rem  *********************************
rem  * Configuration de la librairie *
rem  *********************************
set adr_lib=hpc
set adr_nom=happyc64

echo --------------------------------
echo - Preprocesseur et compilation -
echo --------------------------------

for %%i in (%adr_lib%\*.c) do ( 
echo %%~nxi
 )

cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happyc64.c
cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happy_sid.c
cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happy_sprite.c
cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happy_texte.c
cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happy_d7.c
cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happy_reu.c
cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happy_bitmap.c
cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happy_io.c
cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happy_rle.c
cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happy_vic.c
cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happy_random.c
cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happy_scrolling.c
cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happy_bit.c
cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happy_raster.c
cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happy_timer.c

echo --------------
echo - Assemblage -
echo --------------
for %%i in (%adr_lib%\*.s) do ( 
echo %%~nxi
 )
cc65\bin\ca65 hpc/happyc64.s 
cc65\bin\ca65 hpc/happy_sid.s 
cc65\bin\ca65 hpc/happy_sprite.s 
cc65\bin\ca65 hpc/happy_texte.s 
cc65\bin\ca65 hpc/happy_d7.s
cc65\bin\ca65 hpc/happy_reu.s
cc65\bin\ca65 hpc/happy_bitmap.s
cc65\bin\ca65 hpc/happy_io.s
cc65\bin\ca65 hpc/happy_rle.s
cc65\bin\ca65 hpc/happy_vic.s
cc65\bin\ca65 hpc/happy_random.s
cc65\bin\ca65 hpc/happy_scrolling.s
cc65\bin\ca65 hpc/happy_bit.s
cc65\bin\ca65 hpc/happy_raster.s
cc65\bin\ca65 hpc/happy_timer.s

echo -------------------
echo - Editeur de lien -
echo -------------------
for %%i in (%adr_lib%\*.o) do ( 
echo %%~nxi
 )
cc65\bin\ar65  r hpc/happyc64.lib hpc/happyc64.o hpc/happy_sid.o hpc/happy_sprite.o hpc/happy_texte.o hpc/happy_d7.o hpc/happy_reu.o hpc/happy_bitmap.o hpc/happy_io.o hpc/happy_rle.o hpc/happy_vic.o hpc/happy_random.o hpc/happy_scrolling.o hpc/happy_bit.o hpc/happy_raster.o hpc/happy_timer.o

echo ------------
echo - Netoyage -
echo ------------
del hpc\*.o
del hpc\*.s
pause
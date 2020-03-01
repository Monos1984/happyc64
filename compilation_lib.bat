echo off
set adr_lib=hpc
set adr_nom=happyc64

cc65\bin\cc65 -O -t c64 --include-dir hpc/header hpc/happyc64.c
cc65\bin\ca65 hpc/happyc64.s
cc65\bin\ar65  r hpc/happyc64.lib hpc/happyc64.o

del hpc\*.o
del hpc\*.s
pause
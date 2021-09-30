/* mcart - Markus Brenner's .prg to .crt converter

        V 0.31 - experimental (for standard 8k, 16k and Ultimax cartridges)
        V 0.33 - fixed ULTIMAX ROM start address
        V 0.34 - fixed EPYX FASTLOAD cartridge
        V 0.35 - added WESTERMANN type
        V 0.36 - better ROM dump recognition
        V 0.37 - added ACTION REPLAY type
        V 0.38 - added FINAL CARTRIDGE III type
        V 0.39 - added SIMONS' BASIC type
        V 0.40 - fixed bug with 'Standard 16K' type
        V 0.41 - added REX Datentechnik type
        V 0.42 - added FINAL CARTRIDGE 1 type
        V 0.43 - cleaned up program
        V 0.44 - added ATOMIC POWER / NORDIC POWER cartridge type
        V 0.45 - fixed OCEAN 128K Carts
        V 0.46 - added OCEAN 512K Cart support (T2)
        V 0.47 - added KCS Power Cartridge type
        V 0.48 - added preliminary C64GS type support
        V 0.49 - added preliminary COMAL-80 support
        V 0.50 - modified ULTIMAX support (now allows $1000 carts)
        V 0.51 - changed some cartridge numbers ($0e/$0f)
        V 0.52 - added WARPSPEED type
        V 0.53 - added Magic Desk support (preliminary)
        V 0.54 - changed flags for OCEAN carts to EXROM=GAME=0
        V 0.55 - added DINAMIC type (Narco Police)
        V 0.56 - Minor fix of screen output for 32kB Ocean type (Ghostbusters)
        V 0.57 - added 'Badlands' support as Ocean 64kB type
        V 0.58 - cleaned up program
        V 0.59 - added 'Zaxxon' (SEGA) support (preliminary)"
        V 0.60 - added automatic $a000 'BASIC' detection
        V 0.61 - fixed some bugs in doublecode() function
        V 0.62 - extended Magic Desk type to Domark and HES-Australia
        V 0.63 - added COMAL-80 and Super Snapshot 5
        V 0.64 - added MIKRO ASSEMBLER

        (C) 1998-2006 Markus Brenner <markus@brenner.de>
        
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define VERSION 0.64

/* assigned cartridge numbers */
#define NORMALCART     0x00
#define ULTIMAX        0x100
#define ACTIONREPLAY   0x01
#define KCSPOWER       0x02
#define FINAL3         0x03
#define SIMONSBASIC    0x04
#define OCEAN          0x05
#define OCEAN2         0x105
#define FUNPLAY        0x07
#define SUPERGAMES     0x08
#define NORDICPOWER    0x09
#define EPYXFASTLOAD   0x0a
#define WESTERMANN     0x0b
#define REX            0x0c
#define FINAL1         0x0d
#define MAGICFORMEL    0x0e
#define GS             0x0f
#define WARPSPEED      0x10
#define DINAMIC        0x11
#define ZAXXON         0x12
#define MAGICDESK      0x13
#define SUPERSNPSHT5   0x14
#define COMAL          0x15
#define MIKROASSEMBLER 0x1c

/* preliminary */
#define MACH5         0x110


/* Chiptypes */
#define CHIP_ROM 0

#define ROMTYPE 0
#define PRGTYPE 1


void fprintlong(FILE *fpout, unsigned long value)
{
    int i, outvec[4];

    for (i=3; i >= 0; i--)
    {
        outvec[i] = value % 0x100;
        value /= 0x100;
    }
    for (i=0; i < 4; i++) fputc(outvec[i], fpout);
}

void fprintword(FILE *fpout, unsigned long value)
{
    int i, outvec[2];

    for (i=1; i >= 0; i--)
    {
        outvec[i] = value % 0x100;
        value /= 0x100;
    }
    for (i=0; i < 2; i++) fputc(outvec[i], fpout);
}

int check_datalen(long datalen, long rightlen)
{
    if (datalen != rightlen)
    {
        fprintf(stderr, "Bad ROM data length!\n");
        exit(5);
    }
    else return (1);
}

void usage(void)
{
    fprintf(stderr, "usage: mcart [-carttype] <input> <\"game name\">\n");
    fprintf(stderr, " -ar  Action Replay\n");
    fprintf(stderr, " -at  Atomic Power\n");
    fprintf(stderr, " -b   Simons' BASIC\n");
    fprintf(stderr, " -c   COMAL-80\n");
    fprintf(stderr, " -d   Dinamic\n");
    fprintf(stderr, " -e   Epyx Fastload\n");
    fprintf(stderr, " -fc1 Final Cartridge I\n");
    fprintf(stderr, " -fc3 Final Cartridge III\n");
    fprintf(stderr, " -fp  Fun Play, Power Play\n");
    fprintf(stderr, " -g   C64GS cartridge, System 3\n");
    fprintf(stderr, " -k   KCS Power Cartridge\n");
/*    fprintf(stderr, " -m5  Mach-5\n"); */
    fprintf(stderr, " -ma  MIKRO Assembler\n");
    fprintf(stderr, " -md  Magic Desk, Domark, HES Australia\n");
    fprintf(stderr, " -n   Nordic Power\n");
    fprintf(stderr, " -o   Ocean 1 (Standard)\n");
    fprintf(stderr, " -o2  Ocean 2 (Chase H.Q. 2)\n");
    fprintf(stderr, " -r   Rex Utility\n");
    fprintf(stderr, " -s   Super Games\n");
    fprintf(stderr, " -u   Ultimax\n");
    fprintf(stderr, " -we  Westermann\n");
    fprintf(stderr, " -ws  Warpspeed\n");
    fprintf(stderr, " -z   Zaxxon/Super Zaxxon (SEGA)\n");
    exit(1);
}

void SetFileExtension(char *str, char *ext)
{
    /* sets the file extension of String *str to *ext */
    int i, len;

    for (i=0, len = strlen(str); (i < len) && (str[i] != '.'); i++);
    str[i] = '\0';
    strcat(str, ext);
}

void WriteChipPackage(FILE *fpin, FILE *fpout, int bank,
                     long address, long packetlen)
{
    int byte;

    fprintf(fpout,"CHIP");
    fprintlong(fpout, packetlen+0x10); /* total length of CHIP chunk */
    fprintword(fpout, CHIP_ROM);       /* chiptype */
    fprintword(fpout, bank);           /* bank     */
    fprintword(fpout, address);        /* address  */
    fprintword(fpout, packetlen);      /* length   */

    for (; packetlen > 0; packetlen--)
    {
        if ((byte = fgetc(fpin)) == EOF) 
        {
            fprintf(stderr, "Unexpected End of File!\n");
            exit(7);
        }
        fputc(byte, fpout);
    }
}


int doublecode(FILE *fpin)
{
    fpos_t oldpos;
    unsigned char code[0x2000];
    unsigned char *pos1, *pos2;
    int i;

    fgetpos(fpin, &oldpos);
    fread(code, sizeof(unsigned char), 0x2000, fpin);
    fsetpos(fpin, &oldpos);

    pos1 = &code[0];
    pos2 = &code[0x1000];
    for (i = 0; i < 0x1000; i++)
    {
        if (*pos1 != *pos2) return (0);
    }
    return (1);
}



int check_basic(FILE *fpin)
{
    unsigned long checksum;
    unsigned char crc;
    int byte;
    int i;
    fpos_t oldpos;

    fgetpos(fpin, &oldpos);
    fseek(fpin, 0x2000, SEEK_CUR);

    checksum = 0;
    crc = 0;
    for (i = 0; i < 0x2000; i++)
    {
        if ((byte = fgetc(fpin)) == EOF) break;
        checksum += (unsigned long) byte;
        crc ^= (unsigned char) byte;
    }

    fsetpos(fpin, &oldpos);

    if ((checksum == 0xe3d56) && (crc == 0xbe))
        return(1);
    else
        return(0);
}


int main(int argc, char **argv)
{
    FILE *fpin, *fpout;
    long address;
    long datalen;
    char inname[100];   /* input file name */
    char outname[100];  /* output (CRT) file name */
    char cartname[100]; /* full Cartridge name */
    int i;
    int game_line, exrom_line; /* /GAME and /EXROM lines */
    int carttype;       /* CRT type according to CRT specification */
    int fp_bank[] = {0x00,0x08,0x10,0x18,0x20,0x28,0x30,0x38,0x01,0x09,0x11,0x19,0x21,0x29,0x31,0x39};
    int bank;
    int dumptype;       /* file type of dump: ROMTYPE or PRGTYPE */



    printf("\nmcart - Commodore CRT file Converter w64bit compatible v%.2f\n\n ", VERSION);

    if (argc < 3) usage();

    carttype = NORMALCART; /* default CRT type is standard cart */

    while (--argc && (*(++argv)[0] == '-'))
    {
        switch (tolower((*argv)[1]))
        {
            case 'a':
                if (tolower((*argv)[2]) == 'r')
                {
                    carttype = ACTIONREPLAY;
                    printf("ACTION REPLAY\n");
                }
                else if ((tolower((*argv)[2]) == 't') ||
                         (tolower((*argv)[2]) == 'p'))
                {
                    carttype = NORDICPOWER;
                    printf("ATOMIC POWER\n");
                }
		else usage();
                break;
            case 'b':
                carttype = SIMONSBASIC;
                printf("SIMONS' BASIC\n");
                break;
            case 'c':
                carttype = COMAL;
                printf("COMAL-80\n");
                break;
            case 'd':
                carttype = DINAMIC;
                printf("DINAMIC\n");
                break;
            case 'r':
                carttype = REX;
                printf("REX UTILITY\n");
                break;
            case 's':
                carttype = SUPERGAMES;
                printf("SUPER GAMES\n");
                break;
            case 'f':
                if (tolower((*argv)[2]) == 'p')
                {
                    carttype = FUNPLAY;
                    printf("FUNPLAY\n");
                }
                else if (tolower((*argv)[2]) == 'c')
                {
                    if ((*argv)[3] == '1')
                    {
                        carttype = FINAL1;
                        printf("FINAL CARTRIDGE I\n");
                    }
                    else if ((*argv)[3] == '3')
                    {
                        carttype = FINAL3;
                        printf("FINAL CARTRIDGE III\n");
                    }
                }
		else usage();
                break;
            case 'k':
                carttype = KCSPOWER;
                printf("KCS POWER CARTRIDGE\n");
                break;
            case 'm':
                if (tolower((*argv)[2]) == 'a')
                {
                    carttype = MIKROASSEMBLER;
                    printf("MIKRO ASSEMBLER\n");
                }
		else if (tolower((*argv)[2]) == 'd')
                {
                    carttype = MAGICDESK;
                    printf("MAGIC DESK\n");
                }
                else if (tolower((*argv)[2]) == '5')
                {
                    carttype = MACH5;
                    printf("MACH-5\n");
                }
		else usage();
                break;
            case 'n':
                carttype = NORDICPOWER;
                printf("NORDIC POWER\n");
                break;
            case 'o':
                if (tolower((*argv)[2]) == '2')
                {
                    carttype = OCEAN2;
                    printf("OCEAN 2 (Use only with Chase H.Q. 2!)\n");
                }
                else
                {
                    carttype = OCEAN;
                    printf("OCEAN\n");
                }
                break;
            case 'u':
                carttype = ULTIMAX;
                break;
            case 'w':
                if (tolower((*argv)[2]) == 'e')
                {
                    carttype = WESTERMANN;
                    printf("WESTERMANN\n");
                }
                else if (tolower((*argv)[2]) == 's')
                {
                    carttype = WARPSPEED;
                    printf("WARPSPEED\n");
                }
		else usage();
                break;
            case 'e':
                carttype = EPYXFASTLOAD;
                printf("EPYX FASTLOAD\n");
                break;
            case 'g':
                carttype = GS;
                printf("GAME SYSTEM/SYSTEM 3\n");
                break;
            case 'z':
                carttype = ZAXXON;
                printf("ZAXXON (SEGA)\n");
                break;
            default:
                break;
        }
    }

    if (argc < 2) usage();

    strcpy(inname, argv[0]);
    strcpy(outname, argv[0]);

    for (i = 0; i < 4; i++)
    {
        switch(i)
        {
            /* try several file extensions */
            case 0: break; /* try user-given extension */
            case 1: SetFileExtension(inname, ".ROM"); break;
            case 2: SetFileExtension(inname, ".PRG"); break;
            case 3: SetFileExtension(inname, "."); break;
            default: break;
        }
        if ((fpin = fopen(inname,"rb")) != NULL) break;
    }

    if (fpin == NULL)
    {
        fprintf(stderr, "Couldn't open input file %s!\n", argv[0]);
        exit(2);
    }
	
    SetFileExtension(outname, ".CRT");
    if ((fpout = fopen(outname,"wb")) == NULL)
    {
        fprintf(stderr, "Couldn't open output file %s!\n", outname);
        exit(3);
    }

    /* determine data length */
    fseek(fpin, 0, SEEK_END);
    datalen = ftell(fpin);
    printf("datalen: %x\n", datalen);

    if ((datalen % 0x1000) == 2) dumptype = PRGTYPE;
    else if ((datalen % 0x1000) == 0) dumptype = ROMTYPE;
    else
    {
        fprintf(stderr, "Invalid input file size!\n");
        exit(4);
    }

    rewind(fpin);

    if (dumptype == PRGTYPE)
    {
        fseek(fpin, 2, SEEK_SET);
        datalen -= 2;
    }

    if ((datalen == 0x4000) && (check_basic(fpin) == 1))
    {
        fprintf(stderr, "Stripping BASIC ROM\n");
        datalen = 0x2000;
    }
 
    address = 0x8000;
    switch(carttype)
    {
        case NORMALCART:
            if (datalen == 0x2000)
            {
                printf("Standard 8K Cartridge\n");
                exrom_line = 0;
                game_line = 1;
            }
            else if (check_datalen(datalen, 0x4000))
            {
                printf("Standard 16K Cartridge\n");
                exrom_line = 0;
                game_line = 0;
            }
            break;

        case ULTIMAX:
            if (datalen == 0x1000)
            {
                printf("Ultimax 4K Cartridge\n");
                address = 0xf000;
            }
            else if (datalen == 0x2000)
            {
                printf("Ultimax 8K Cartridge\n");
                address = 0xe000;
            }
            else if (check_datalen(datalen, 0x4000))
                printf("Ultimax 16K Cartridge\n");
            exrom_line = 1;
            game_line = 0;
            break;

        case FINAL3:
            exrom_line = 1;
            game_line = 1;
            break;

        case SIMONSBASIC:
            check_datalen(datalen, 0x4000);
            exrom_line = 0;
            game_line = 1;
            break;

        case FUNPLAY:
        case SUPERGAMES:
        case ACTIONREPLAY:
            exrom_line = 0;
            game_line = 0;
            break;

        case OCEAN:
        case OCEAN2:
            /* default: 8kB ROM access at $a000-$bfff */
            exrom_line = 0;
            game_line = 1;
            if (datalen == 0x8000)
                printf("Ocean 32K Cartridge\n");
            else if (datalen == 0x10000)
                printf("Ocean 64K Cartridge\n");
            else if (datalen == 0x20000)
                printf("Ocean 128K Cartridge\n");
            else if (datalen == 0x40000)
            {
                printf("Ocean 256K Cartridge\n");
                if (carttype == OCEAN2)
                {
                    exrom_line = 0;
                    game_line = 0;
                }
            }
            else if (datalen == 0x80000)
                printf("Ocean 512 Cartridge\n");
            else
            {
                fprintf(stderr, "Bad ROM data length!\n");
                exit(5);
            }
            break;

        case GS:
            check_datalen(datalen, 0x80000);
            exrom_line = 0;
            game_line = 1;
            break;

        case DINAMIC:
            check_datalen(datalen, 0x20000);
            exrom_line = 0;
            game_line = 1;
            break;

        case NORDICPOWER:
            check_datalen(datalen, 0x8000);
            exrom_line = 0;
            game_line = 0;
            break;

        case EPYXFASTLOAD:
            check_datalen(datalen, 0x2000);
            exrom_line = 1;
            game_line = 1;
            break;

        case WESTERMANN:
            check_datalen(datalen, 0x4000);
            exrom_line = 0;
            game_line = 0;
            break;

        case REX:
            check_datalen(datalen, 0x2000);
            exrom_line = 0;
            game_line = 1;
            break;

        case FINAL1:
            check_datalen(datalen, 0x4000);
            exrom_line = 1;
            game_line = 1;
            break;

        case KCSPOWER:
            check_datalen(datalen, 0x4000);
            exrom_line = 0;
            game_line = 0;
            break;

        case WARPSPEED:
            check_datalen(datalen, 0x4000);
            exrom_line = 1;
            game_line = 1;
            break;

        case MAGICDESK:
            exrom_line = 0;
            game_line = 1;
            break;

        case MIKROASSEMBLER:
            check_datalen(datalen, 0x2000);
            exrom_line = 0;
            game_line = 1;
	    break;

        case MACH5:
            check_datalen(datalen, 0x2000);
            exrom_line = 1;
            game_line = 1;
            break;

        case COMAL:
            check_datalen(datalen, 0x10000);
            exrom_line = 0;
            game_line = 0;
            break;

        case ZAXXON:
            if (datalen != 0x5000) check_datalen(datalen, 0x6000);
            exrom_line = 0;
            game_line = 0;
            break;

        default:
            break;
    }


    /* Write the Cartridge header */

    fprintf(fpout,"C64 CARTRIDGE   ");
    fprintlong(fpout, 0x0040L);
    fprintword(fpout, 0x0100L);

    /* header: Cartridge type */
    /* cast ULTIMAX to NORMALCART, MACH5 to WARPSPEED, OCEAN2 to OCEAN */
    fprintword(fpout, (carttype & 0xff));

    fputc(exrom_line, fpout); /* /EXROM line */
    fputc(game_line, fpout);  /* /GAME  line */
    for (i=0; i < 6; i++) fputc(0, fpout); /* future use */

    /* fill cartridge name up to 0x20 characters */
    for (i=0; i < 0x20; i++) cartname[i] = '\0';
    sprintf(cartname,"%s",argv[1]);
    cartname[0x20] = '\0';
    for (i=0; i < 0x20; i++) fputc(cartname[i], fpout);
		
    switch (carttype)
    {
        case NORMALCART:
            if (datalen == 0x2000)
                WriteChipPackage(fpin, fpout, 0, 0x8000, 0x2000);
            else /* datalen = 0x4000 */
                WriteChipPackage(fpin, fpout, 0, 0x8000, 0x4000);
            break;

        case ULTIMAX:
            if (datalen == 0x1000)
            {
                WriteChipPackage(fpin, fpout, 0, 0xf000, 0x1000);
            }
            else if (datalen == 0x2000)
            {
                WriteChipPackage(fpin, fpout, 0, 0xe000, 0x2000);
            }
            else /* 0x4000 */
            {
                WriteChipPackage(fpin, fpout, 0, 0x8000, 0x2000);
                WriteChipPackage(fpin, fpout, 0, 0xe000, 0x2000);
            }
            break;

        case EPYXFASTLOAD:
        case REX:
        case MACH5:
        case MIKROASSEMBLER:
            WriteChipPackage(fpin, fpout, 0, 0x8000, 0x2000);
            break;

        case WESTERMANN:
        case FINAL1:
        case WARPSPEED:
            WriteChipPackage(fpin, fpout, 0, 0x8000, 0x4000);
            break;

        case ACTIONREPLAY:
        case NORDICPOWER:
        case GS:
        case MAGICDESK:
        case DINAMIC:
            for (bank = 0; datalen > 0; bank++)
            {
                WriteChipPackage(fpin, fpout, bank, 0x8000, 0x2000);
                datalen -= 0x2000;
            }
            break;

        case SIMONSBASIC:
            WriteChipPackage(fpin, fpout, 0, 0x8000, 0x2000);
            WriteChipPackage(fpin, fpout, 0, 0xa000, 0x2000);
            break;

        case OCEAN:
        case OCEAN2:
            if ((datalen == 0x40000) && (carttype != OCEAN2))
            {
                for (bank = 0; datalen > 0; bank++)
                {
                    WriteChipPackage(fpin, fpout, bank, (bank < 0x10) ? 0x8000 : 0xa000, 0x2000);
                    datalen -= 0x2000;
                }
            }
            else
            {
                for (bank = 0; datalen > 0; bank++)
                {
                    WriteChipPackage(fpin, fpout, bank, 0x8000, 0x2000);
                    datalen -= 0x2000;
                }
            }
            break;

        case FUNPLAY:
            for (bank = 0; datalen > 0; bank++)
            {
                WriteChipPackage(fpin, fpout, fp_bank[bank], 0x8000, 0x2000);
                datalen -= 0x2000;
            }
            break;

        case SUPERGAMES:
        case FINAL3:
        case COMAL:
            for (bank = 0; datalen > 0; bank++)
            {
                WriteChipPackage(fpin, fpout, bank, 0x8000, 0x4000);
                datalen -= 0x4000;
            }
            break;

        case KCSPOWER:
            WriteChipPackage(fpin, fpout, 0, 0x8000, 0x2000);
            WriteChipPackage(fpin, fpout, 0, 0xa000, 0x2000);
            break;

        case ZAXXON:
            if (datalen == 0x5000)
                WriteChipPackage(fpin, fpout, 0, 0x8000, 0x1000);
            else if (doublecode(fpin))
            {
                fseek(fpin, 0x1000, SEEK_CUR);
                WriteChipPackage(fpin, fpout, 0, 0x8000, 0x1000);
            }
            else
                WriteChipPackage(fpin, fpout, 0, 0x8000, 0x2000);

            WriteChipPackage(fpin, fpout, 0, 0xa000, 0x2000);
            WriteChipPackage(fpin, fpout, 1, 0xa000, 0x2000);
            break;

        default:
            fprintf(stderr, "Invalid Cartridge Type!\n");
            exit(6);
            break;
    }

    fclose(fpin);
    fclose(fpout);
    exit(0);
}

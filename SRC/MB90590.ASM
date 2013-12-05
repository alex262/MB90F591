/* FFMC-16 IO-MAP HEADER FILE                                                */
/* ==========================                                                */
/* CREATED BY IO-WIZARD V2.16                                                */
/* Id: mb90590.asm,v 4.3 2003/08/29 12:39:28 dfisch Exp $ */
/* ***********************************************************               */
/*               FUJITSU MIKROELEKTRONIK GMBH                                */
/*               Am Siebenstein 6-10, 63303 Dreieich                         */
/*               Tel.:++49/6103/690-0,Fax - 122                              */
/*                                                                           */
/* The following software is for demonstration purposes only.                */
/* It is not fully tested, nor validated in order to fullfill                */
/* its task under all circumstances. Therefore, this software                */
/* or any part of it must only be used in an evaluation                      */
/* laboratory environment.                                                   */
/* This software is subject to the rules of our standard                     */
/* DISCLAIMER, that is delivered with our SW-tools (on the CD                */
/* "Micros Documentation & Software V3.0" see "\START.HTM" or                */
/* see our Internet Page -                                                   */
/* http://www.fujitsu-ede.com/products/micro/disclaimer.html                 */
/* ***********************************************************               */
/* ----------------------------------------------------------------------    */
/* Id: mb90590.iow,v 4.0 2003/05/07 15:30:54 dfisch Exp                      */
/* ----------------------------------------------------------------------    */
/* History:                                                                  */
/* Date		Version	Author	Description                                          */
/* 01.02.99 	1.0 	TKA	- created                                              */
/* 18.02.99 	1.2 	HLO                                                        */
/*  - ICR now included (icr.h)                                               */
/*  - IO-Wizard 1.7 uses IO_EXTENDED now                                     */
/*  - WTBR now included (wtbr.h)                                             */
/* 09.04.99 	1.3 	HLO	- '_' removed from "!I"-symbols, now done by IO-Wizard */
/* 14.04.99 	1.4	JRO	- generation of header and c file with IO-Wizard V 1.9  */
/* 22.04.99 	1.5 	VSA	- Bitdefinitions for parallelports are changed to Pxx, Dxx */
/* 06.05.99 	1.6 	HLO                                                        */
/*  - disclaimer added                                                       */
/*  - unspecified registers removed                                          */
/* 15.07.99 	1.7 	VSA	- PADRx 3 are renamed to PADRx_L 1, PADRx_H 1, PADRx_H 1 */
/* 10.08.99 	1.8 	VSA	- WTCR low and high bytes are exchanged                */
/* 23.08.99 	1.9 	VSA	- SMCS bitdefinitions are modified                     */
/* 03.07.00	1.10	VSA	- ADC unit included (adc_01.h)                          */
/* 01.11.00     1.11    NMP     - ADC Structure realignment                  */
/* 06.03.01     1.12    HLO     - ADC dummy bit before STS (using correct ADC_01.h) */
/* 21.02.02     -       HWE     - Bit groups defined for PWCn                */
/* 23.07.02     1.13    HWe     - new adc_01.h, icr.h (RMW-Problem)          */
/* 09.12.02     1.14    HWe     - Register CDCR: Bit MD added                */
/* 30.01.03     1.15    HWe     - wordaccess to PPGCx/y: PPGC01, .. , PPGCAB */
/* 30.01.03                     - wordaccess to PPG Reload: PRL0, .. , PRLB  */
/* 30.01.03                     - longwordaccess to PPG Reload: PRL01, .. , PRLAB */
/* Id: mb90590.iow,v 4.0 2003/05/07 15:30:54 dfisch Exp                      */
/*      - CVS and make controlled                                            */
/* ----------------------------------------------------------------------    */
/* Id: elvr.h,v 2.1 2003/06/27 14:30:51 dfisch Exp                           */
/* ----------------------------------------------------------------------    */
/* External Interrupt Input Level register                                   */
/*                                                                           */
/* This declaration is intended to be included in IO-Wizard source           */
/* files.                                                                    */
/* V0.1 still missing prefix '_'                                             */
/* V1.0 symbol prefix '_' added                                              */
/* V1.2 "extern" changed to pre-defined macro of IO-Wizrad, re-              */
/*      quires IO-Wizard 1.7 or later                                        */
/* Id: elvr.h,v 2.0 2003/05/06 09:03:53 dfisch Exp                           */
/*      - CVS and make controlled                                            */
/* Id: elvr.h,v 2.1 2003/06/27 14:30:51 dfisch Exp                           */
/*      - adapted to BITFIELD_ORDER_MSB                                      */
/* ----------------------------------------------------------------------    */
/* Id: adc_01.h,v 2.2 2003/08/19 09:46:21 dfisch Exp                         */
/* ----------------------------------------------------------------------    */
/* DESCRIPTION:  Interrupt Control Register Declaration                      */
/*                                                                           */
/* AUTHOR:       Fujitsu Mikroelektronik GmbH                                */
/*                                                                           */
/* HISTORY:                                                                  */
/* Version 1.0      03.07.00   : original version                            */
/*         1.1      01.11.00   : Structure alignment                         */
/* Version 1.2      22.07.2002 : HW  ADCS0, ADCR-Bitdefinitions as const, no RMV allowed */
/* Id: adc_01.h,v 2.0 2003/05/06 13:59:57 dfisch Exp                         */
/*      - CVS and make controlled                                            */
/* Id: adc_01.h,v 2.1 2003/06/27 14:30:51 dfisch Exp                         */
/*      - adapted to BITFIELD_ORDER_MSB                                      */
/* Id: adc_01.h,v 2.2 2003/08/19 09:46:21 dfisch Exp                         */
/*      - ADCS1 Bit-defs as const, only Byte-write                           */
/* ----------------------------------------------------------------------    */
/* Id: ICR.H,v 2.1 2003/06/27 14:30:51 dfisch Exp                            */
/* ----------------------------------------------------------------------    */
/*                                                                           */
/* DESCRIPTION:  Interrupt Control Register Declaration                      */
/*                                                                           */
/* AUTHOR:       Fujitsu Mikroelektronik GmbH                                */
/*                                                                           */
/* HISTORY:                                                                  */
/* Version 1.0      26.01.99:                                                */
/*      - original version                                                   */
/* Version 1.2      11.02.99                                                 */
/*      - "extern" changed to pre-defined macro of IO-Wizard                 */
/*        (__IO_EXTERN), requires IO-Wizard 1.7 or later                     */
/*                                                                           */
/* Version 1.3      17.07.2002  HW  Bitdefinitions as const, no RMV allowed  */
/* Id: ICR.H,v 2.0 2003/05/06 09:03:53 dfisch Exp                            */
/*      - CVS and make controlled                                            */
/* Id: ICR.H,v 2.1 2003/06/27 14:30:51 dfisch Exp                            */
/*      - adapted to BITFIELD_ORDER_MSB                                      */
/* ----------------------------------------------------------------------    */
/* Id: WTBR.H,v 2.0 2003/05/06 09:03:53 dfisch Exp                           */
/* ----------------------------------------------------------------------    */
/* DESCRIPTION:  Watch clock sub-second register                             */
/*                                                                           */
/* AUTHOR:       HL, Fujitsu Mikroelektronik GmbH                            */
/*                                                                           */
/* HISTORY:                                                                  */
/* Version 1.0      18.02.99:                                                */
/*      - original version                                                   */
/* Version 1.1      09.04.99:                                                */
/*      - '_' symbol prefix added                                            */
/* Id: WTBR.H,v 2.0 2003/05/06 09:03:53 dfisch Exp                           */
/*      - CVS and make controlled                                            */
/* ----------------------------------------------------------------------    */
/* Id: CANSTR.H,v 3.1 2003/06/27 14:30:51 dfisch Exp                         */
/* ----------------------------------------------------------------------    */
/* CANIO: control structures of CAN for LX-controllers                       */
/*                                                                           */
/* Version: 1.0            23.01.99     HL                                   */
/*      - original version                                                   */
/* Version: 2.0            26.02.99     HL                                   */
/*      - unsigned int replace by IO_WORD (FR/LX have diff int)              */
/*      - unsigned char replace by IO_BYTE                                   */
/* Version: 2.1            26.08.02     HLo                                  */
/*      - const specifier used for RTEC union                                */
/*      - REC and TEC of RTEC changed from bit group to Byte type            */
/*      - short type addded to DTR register for compatibility                */
/* Id: CANSTR.H,v 3.0 2003/05/06 09:02:30 dfisch Exp                         */
/*      - CVS and make controlled                                            */
/* Id: CANSTR.H,v 3.1 2003/06/27 14:30:51 dfisch Exp                         */
/*      - adapted to BITFIELD_ORDER_MSB                                      */
/* ----------------------------------------------------------------------    */
/* Id: canmac01.h,v 5.0 2003/05/06 09:01:20 dfisch Exp                       */
/* ----------------------------------------------------------------------    */
/* CANIO: control structures for LX-controllers                              */
/*        version 1.0 to 2.2 for double CAN                                  */
/*                                                                           */
/* Version: 1.0            23.01.99     FMG, HLO                             */
/*      - original version                                                   */
/* Version: 1.1            27.01.99     FMG, tka                             */
/*      - idrx0 changed to IDRX0                                             */
/* Version: 1.2            11.02.99     FMG, HLO                             */
/*      - "extern" declaration changed to predefined macros of               */
/*        IO-Wizard, requires IO-Wizard 1.7 or later                         */
/*      - DRT1_LWPTR changed to DTR1_DWPTR macro                             */
/* Version: 2.0            28.05.01     HLO                                  */
/*      - LX-version adopted to FR                                           */
/*      - __IO_EXTENDED changed to __IO_EXTERN, CAN is on external bus       */
/* Version: 2.1            08.06.01     HLO                                  */
/*      - macro for short type in DTR added                                  */
/* Version: 2.2            11.06.01     MEN                                  */
/*      - DLC changed to IO_WORD                                             */
/* Version: 3.0            05.08.02     DF                                   */
/*      - removed CAN1                                                       */
/* Version: 3.1            23.08.02     DF                                   */
/*      - DTR_LWPTR and DTR_DWPTR for compatibility                          */
/* Version: 4.0            23.08.02     HLO                                  */
/*      - changed to batch generation                                        */
/* Id: canmac01.h,v 5.0 2003/05/06 09:01:20 dfisch Exp                       */
/*      - CVS and make controlled                                            */
 .PROGRAM MB90590
 .TITLE   MB90590
 ;.REG_PASS
;------------------------
; IO-AREA DEFINITIONS :
;------------------------



 .section IOBASE, IO, locate=0x0000  ; /*  PORT DATA */
 .GLOBAL __pdr0,     __pdr1,     __pdr2,     __pdr3,     __pdr4,     __pdr5
 .GLOBAL __pdr6,     __pdr7,     __pdr8,     __pdr9,     __ddr0,     __ddr1
 .GLOBAL __ddr2,     __ddr3,     __ddr4,     __ddr5,     __ddr6,     __ddr7
 .GLOBAL __ddr8,     __ddr9,     __res_1,    __ader,     __umc0,     __usr0
 .GLOBAL __uidr0,    __uodr0,    __urd0,     __umc1,     __usr1,     __uidr1
 .GLOBAL __uodr1,    __urd1,     __umc2,     __usr2,     __uidr2,    __uodr2
 .GLOBAL __urd2,     __smcs,     __sdr,      __ses,      __enir,     __eirr
 .GLOBAL __elvr,     __adcs,     __adcs0,    __adcs1,    __adcr,     __adcr0
 .GLOBAL __adcr1,    __ppgc01,   __ppgc0,    __ppgc1,    __ppg01,    __ppgc23
 .GLOBAL __ppgc2,    __ppgc3,    __ppg23,    __ppgc45,   __ppgc4,    __ppgc5
 .GLOBAL __ppg45,    __ppgc67,   __ppgc6,    __ppgc7,    __ppg67,    __ppgc89
 .GLOBAL __ppgc8,    __ppgc9,    __ppg89,    __ppgcab,   __ppgca,    __ppgcb
 .GLOBAL __ppgab,    __tmcsr0,   __tmcsr1,   __ics01,    __ics23,    __ics45
 .GLOBAL __ocs01,    __ocs0,     __ocs1,     __ocs23,    __ocs2,     __ocs3
 .GLOBAL __ocs45,    __ocs4,     __ocs5,     __sgcr,     __wtcr,     __pwc0
 .GLOBAL __pwc1,     __pwc2,     __pwc3,     __cdcr,     __tccs,     __romm
 .GLOBAL __canl0,    __canl1,    __pacsr,    __dirr,     __lpmcr,    __ckscr
 .GLOBAL __wdtc,     __tbtc,     __fmcs,     __icr

__pdr0   .res.b 1             ;000000  /*  PORT DATA */
PDR0    .equ 0x0000
__pdr1   .res.b 1             ;000001
PDR1    .equ 0x0001
__pdr2   .res.b 1             ;000002
PDR2    .equ 0x0002
__pdr3   .res.b 1             ;000003
PDR3    .equ 0x0003
__pdr4   .res.b 1             ;000004
PDR4    .equ 0x0004
__pdr5   .res.b 1             ;000005
PDR5    .equ 0x0005
__pdr6   .res.b 1             ;000006
PDR6    .equ 0x0006
__pdr7   .res.b 1             ;000007
PDR7    .equ 0x0007
__pdr8   .res.b 1             ;000008
PDR8    .equ 0x0008
__pdr9   .res.b 1             ;000009
PDR9    .equ 0x0009
 .org 0x0010
__ddr0   .res.b 1             ;000010  /*  PORT DIRECTION */
DDR0    .equ 0x0010
__ddr1   .res.b 1             ;000011
DDR1    .equ 0x0011
__ddr2   .res.b 1             ;000012
DDR2    .equ 0x0012
__ddr3   .res.b 1             ;000013
DDR3    .equ 0x0013
__ddr4   .res.b 1             ;000014
DDR4    .equ 0x0014
__ddr5   .res.b 1             ;000015
DDR5    .equ 0x0015
__ddr6   .res.b 1             ;000016
DDR6    .equ 0x0016
__ddr7   .res.b 1             ;000017
DDR7    .equ 0x0017
__ddr8   .res.b 1             ;000018
DDR8    .equ 0x0018
__ddr9   .res.b 1             ;000019
DDR9    .equ 0x0019
__res_1   .res.b 1             ;00001A
RES_1    .equ 0x001A
__ader   .res.b 1             ;00001B
ADER    .equ 0x001B
 .org 0x0020
__umc0   .res.b 1             ;000020  /*  UART0 */
UMC0    .equ 0x0020
__usr0   .res.b 1             ;000021
USR0    .equ 0x0021
__uidr0   .res.b 1             ;000022
UIDR0    .equ 0x0022
 .org 0x0022
__uodr0   .res.b 1             ;000022
UODR0    .equ 0x0022
__urd0   .res.b 1             ;000023
URD0    .equ 0x0023
__umc1   .res.b 1             ;000024  /*  UART1 */
UMC1    .equ 0x0024
__usr1   .res.b 1             ;000025
USR1    .equ 0x0025
__uidr1   .res.b 1             ;000026
UIDR1    .equ 0x0026
 .org 0x0026
__uodr1   .res.b 1             ;000026
UODR1    .equ 0x0026
__urd1   .res.b 1             ;000027
URD1    .equ 0x0027
__umc2   .res.b 1             ;000028  /*  UART2 */
UMC2    .equ 0x0028
__usr2   .res.b 1             ;000029
USR2    .equ 0x0029
__uidr2   .res.b 1             ;00002A
UIDR2    .equ 0x002A
 .org 0x002A
__uodr2   .res.b 1             ;00002A
UODR2    .equ 0x002A
__urd2   .res.b 1             ;00002B
URD2    .equ 0x002B
__smcs   .res.b 2             ;00002C  /*  SIO with clock selection */
SMCS    .equ 0x002C
__sdr   .res.b 1             ;00002E
SDR    .equ 0x002E
__ses   .res.b 1             ;00002F
SES    .equ 0x002F
__enir   .res.b 1             ;000030  /*  DTP, External Interrupts */
ENIR    .equ 0x0030
__eirr   .res.b 1             ;000031
EIRR    .equ 0x0031
__elvr   .res.b 2             ;000032
ELVR    .equ 0x0032
__adcs   .res.b 2             ;000034  /*  AD Converter  */
ADCS    .equ 0x0034
 .org 0x0034
__adcs0   .res.b 1             ;000034
ADCS0    .equ 0x0034
__adcs1   .res.b 1             ;000035
ADCS1    .equ 0x0035
__adcr   .res.b 2             ;000036
ADCR    .equ 0x0036
 .org 0x0036
__adcr0   .res.b 1             ;000036
ADCR0    .equ 0x0036
__adcr1   .res.b 1             ;000037
ADCR1    .equ 0x0037
__ppgc01   .res.b 2             ;000038  /*  PPG control */
PPGC01    .equ 0x0038
 .org 0x0038
__ppgc0   .res.b 1             ;000038
PPGC0    .equ 0x0038
__ppgc1   .res.b 1             ;000039
PPGC1    .equ 0x0039
__ppg01   .res.b 1             ;00003A
PPG01    .equ 0x003A
 .org 0x003C
__ppgc23   .res.b 2             ;00003C
PPGC23    .equ 0x003C
 .org 0x003C
__ppgc2   .res.b 1             ;00003C
PPGC2    .equ 0x003C
__ppgc3   .res.b 1             ;00003D
PPGC3    .equ 0x003D
__ppg23   .res.b 1             ;00003E
PPG23    .equ 0x003E
 .org 0x0040
__ppgc45   .res.b 2             ;000040
PPGC45    .equ 0x0040
 .org 0x0040
__ppgc4   .res.b 1             ;000040
PPGC4    .equ 0x0040
__ppgc5   .res.b 1             ;000041
PPGC5    .equ 0x0041
__ppg45   .res.b 1             ;000042
PPG45    .equ 0x0042
 .org 0x0044
__ppgc67   .res.b 2             ;000044
PPGC67    .equ 0x0044
 .org 0x0044
__ppgc6   .res.b 1             ;000044
PPGC6    .equ 0x0044
__ppgc7   .res.b 1             ;000045
PPGC7    .equ 0x0045
__ppg67   .res.b 1             ;000046
PPG67    .equ 0x0046
 .org 0x0048
__ppgc89   .res.b 2             ;000048
PPGC89    .equ 0x0048
 .org 0x0048
__ppgc8   .res.b 1             ;000048
PPGC8    .equ 0x0048
__ppgc9   .res.b 1             ;000049
PPGC9    .equ 0x0049
__ppg89   .res.b 1             ;00004A
PPG89    .equ 0x004A
 .org 0x004C
__ppgcab   .res.b 2             ;00004C
PPGCAB    .equ 0x004C
 .org 0x004C
__ppgca   .res.b 1             ;00004C
PPGCA    .equ 0x004C
__ppgcb   .res.b 1             ;00004D
PPGCB    .equ 0x004D
__ppgab   .res.b 1             ;00004E
PPGAB    .equ 0x004E
 .org 0x0050
__tmcsr0   .res.b 2             ;000050  /*  Reload Timer */
TMCSR0    .equ 0x0050
__tmcsr1   .res.b 2             ;000052
TMCSR1    .equ 0x0052
__ics01   .res.b 1             ;000054  /*  Input Capture */
ICS01    .equ 0x0054
__ics23   .res.b 1             ;000055
ICS23    .equ 0x0055
__ics45   .res.b 1             ;000056
ICS45    .equ 0x0056
 .org 0x0058
__ocs01   .res.b 2             ;000058  /*  Output compare */
OCS01    .equ 0x0058
 .org 0x0058
__ocs0   .res.b 1             ;000058
OCS0    .equ 0x0058
__ocs1   .res.b 1             ;000059
OCS1    .equ 0x0059
__ocs23   .res.b 2             ;00005A
OCS23    .equ 0x005A
 .org 0x005A
__ocs2   .res.b 1             ;00005A
OCS2    .equ 0x005A
__ocs3   .res.b 1             ;00005B
OCS3    .equ 0x005B
__ocs45   .res.b 2             ;00005C
OCS45    .equ 0x005C
 .org 0x005C
__ocs4   .res.b 1             ;00005C
OCS4    .equ 0x005C
__ocs5   .res.b 1             ;00005D
OCS5    .equ 0x005D
__sgcr   .res.b 2             ;00005E  /* Sound control */
SGCR    .equ 0x005E
__wtcr   .res.b 2             ;000060  /*  Watch Timer */
WTCR    .equ 0x0060
__pwc0   .res.b 1             ;000062  /* PWM0 */
PWC0    .equ 0x0062
 .org 0x0064
__pwc1   .res.b 1             ;000064
PWC1    .equ 0x0064
 .org 0x0066
__pwc2   .res.b 1             ;000066
PWC2    .equ 0x0066
 .org 0x0068
__pwc3   .res.b 1             ;000068
PWC3    .equ 0x0068
 .org 0x006D
__cdcr   .res.b 1             ;00006D  /* Serial IO Prescaler */
CDCR    .equ 0x006D
__tccs   .res.b 1             ;00006E  /* IO timer */
TCCS    .equ 0x006E
__romm   .res.b 1             ;00006F  /*  ROM Mirror */
ROMM    .equ 0x006F
__canl0   .res.b 0x10          ;000070  /*  CAN buffer control, lower part */
CANL0    .equ 0x0070
__canl1   .res.b 0x10          ;000080
CANL1    .equ 0x0080
 .org 0x009E
__pacsr   .res.b 1             ;00009E  /*  ROM Correction */
PACSR    .equ 0x009E
__dirr   .res.b 1             ;00009F  /*  Delay interrupt enable */
DIRR    .equ 0x009F
__lpmcr   .res.b 1             ;0000A0  /*  Low power mode control */
LPMCR    .equ 0x00A0
__ckscr   .res.b 1             ;0000A1  /*  Clock selection */
CKSCR    .equ 0x00A1
 .org 0x00A8
__wdtc   .res.b 2             ;0000A8  /* Watchdog Control */
WDTC    .equ 0x00A8
 .org 0x00A9
__tbtc   .res.b 1             ;0000A9  /*  Time Base timer */
TBTC    .equ 0x00A9
 .org 0x00AE
__fmcs   .res.b 1             ;0000AE  /* Flash Control Register */
FMCS    .equ 0x00AE
 .org 0x00B0
__icr   .res.b 0x10          ;0000B0  /* Interrupt Control Registers */
ICR    .equ 0x00B0

 .section IOXTND, DATA, locate=0x1900  ; /*  PPG data */
 .GLOBAL __prl01,    __prl0,     __prll0,    __prlh0,    __prl1,     __prll1
 .GLOBAL __prlh1,    __prl23,    __prl2,     __prll2,    __prlh2,    __prl3
 .GLOBAL __prll3,    __prlh3,    __prl45,    __prl4,     __prll4,    __prlh4
 .GLOBAL __prl5,     __prll5,    __prlh5,    __prl67,    __prl6,     __prll6
 .GLOBAL __prlh6,    __prl7,     __prll7,    __prlh7,    __prl89,    __prl8
 .GLOBAL __prll8,    __prlh8,    __prl9,     __prll9,    __prlh9,    __prlab
 .GLOBAL __prla,     __prlla,    __prlha,    __prlb,     __prllb,    __prlhb
 .GLOBAL __ipcp0,    __ipcp1,    __ipcp2,    __ipcp3,    __ipcp4,    __ipcp5
 .GLOBAL __occp0,    __occp1,    __occp2,    __occp3,    __occp4,    __occp5
 .GLOBAL __tmr0,     __tmrlr0,   __tmr1,     __tmrlr1,   __tcdt,     __sgfr
 .GLOBAL __sgar,     __sgdr,     __sgtr,     __wtbr,     __wtsr,     __wtmr
 .GLOBAL __wthr,     __pwc10,    __pwc20,    __pws10,    __pws20,    __pwc11
 .GLOBAL __pwc21,    __pws11,    __pws21,    __pwc12,    __pwc22,    __pws12
 .GLOBAL __pws22,    __pwc13,    __pwc23,    __pws13,    __pws23,    __padr0_l
 .GLOBAL __padr0_m,  __padr0_h,  __padr1_l,  __padr1_m,  __padr1_h,  __canm0
 .GLOBAL ___dmyc0,   ___dmyc1,   ___dmyc2,   __canm1,    ___dmyc3,   ___dmyc4
 .GLOBAL ___dmyc5,   __canh0,    __canh1,    ___endio

__prl01   .res.b 4             ;001900  /*  PPG data */
PRL01    .equ 0x1900
 .org 0x1900
__prl0   .res.b 2             ;001900
PRL0    .equ 0x1900
 .org 0x1900
__prll0   .res.b 1             ;001900
PRLL0    .equ 0x1900
__prlh0   .res.b 1             ;001901
PRLH0    .equ 0x1901
__prl1   .res.b 2             ;001902
PRL1    .equ 0x1902
 .org 0x1902
__prll1   .res.b 1             ;001902
PRLL1    .equ 0x1902
__prlh1   .res.b 1             ;001903
PRLH1    .equ 0x1903
__prl23   .res.b 4             ;001904
PRL23    .equ 0x1904
 .org 0x1904
__prl2   .res.b 2             ;001904
PRL2    .equ 0x1904
 .org 0x1904
__prll2   .res.b 1             ;001904
PRLL2    .equ 0x1904
__prlh2   .res.b 1             ;001905
PRLH2    .equ 0x1905
__prl3   .res.b 2             ;001906
PRL3    .equ 0x1906
 .org 0x1906
__prll3   .res.b 1             ;001906
PRLL3    .equ 0x1906
__prlh3   .res.b 1             ;001907
PRLH3    .equ 0x1907
__prl45   .res.b 4             ;001908
PRL45    .equ 0x1908
 .org 0x1908
__prl4   .res.b 2             ;001908
PRL4    .equ 0x1908
 .org 0x1908
__prll4   .res.b 1             ;001908
PRLL4    .equ 0x1908
__prlh4   .res.b 1             ;001909
PRLH4    .equ 0x1909
__prl5   .res.b 2             ;00190A
PRL5    .equ 0x190A
 .org 0x190A
__prll5   .res.b 1             ;00190A
PRLL5    .equ 0x190A
__prlh5   .res.b 1             ;00190B
PRLH5    .equ 0x190B
__prl67   .res.b 4             ;00190C
PRL67    .equ 0x190C
 .org 0x190C
__prl6   .res.b 2             ;00190C
PRL6    .equ 0x190C
 .org 0x190C
__prll6   .res.b 1             ;00190C
PRLL6    .equ 0x190C
__prlh6   .res.b 1             ;00190D
PRLH6    .equ 0x190D
__prl7   .res.b 2             ;00190E
PRL7    .equ 0x190E
 .org 0x190E
__prll7   .res.b 1             ;00190E
PRLL7    .equ 0x190E
__prlh7   .res.b 1             ;00190F
PRLH7    .equ 0x190F
__prl89   .res.b 4             ;001910
PRL89    .equ 0x1910
 .org 0x1910
__prl8   .res.b 2             ;001910
PRL8    .equ 0x1910
 .org 0x1910
__prll8   .res.b 1             ;001910
PRLL8    .equ 0x1910
__prlh8   .res.b 1             ;001911
PRLH8    .equ 0x1911
__prl9   .res.b 2             ;001912
PRL9    .equ 0x1912
 .org 0x1912
__prll9   .res.b 1             ;001912
PRLL9    .equ 0x1912
__prlh9   .res.b 1             ;001913
PRLH9    .equ 0x1913
__prlab   .res.b 4             ;001914
PRLAB    .equ 0x1914
 .org 0x1914
__prla   .res.b 2             ;001914
PRLA    .equ 0x1914
 .org 0x1914
__prlla   .res.b 1             ;001914
PRLLA    .equ 0x1914
__prlha   .res.b 1             ;001915
PRLHA    .equ 0x1915
__prlb   .res.b 2             ;001916
PRLB    .equ 0x1916
 .org 0x1916
__prllb   .res.b 1             ;001916
PRLLB    .equ 0x1916
__prlhb   .res.b 1             ;001917
PRLHB    .equ 0x1917
 .org 0x1920
__ipcp0   .res.b 2             ;001920
IPCP0    .equ 0x1920
__ipcp1   .res.b 2             ;001922
IPCP1    .equ 0x1922
__ipcp2   .res.b 2             ;001924
IPCP2    .equ 0x1924
__ipcp3   .res.b 2             ;001926
IPCP3    .equ 0x1926
__ipcp4   .res.b 2             ;001928
IPCP4    .equ 0x1928
__ipcp5   .res.b 2             ;00192A
IPCP5    .equ 0x192A
 .org 0x1930
__occp0   .res.b 2             ;001930
OCCP0    .equ 0x1930
__occp1   .res.b 2             ;001932
OCCP1    .equ 0x1932
__occp2   .res.b 2             ;001934
OCCP2    .equ 0x1934
__occp3   .res.b 2             ;001936
OCCP3    .equ 0x1936
__occp4   .res.b 2             ;001938
OCCP4    .equ 0x1938
__occp5   .res.b 2             ;00193A
OCCP5    .equ 0x193A
 .org 0x1940
__tmr0   .res.b 2             ;001940  /* Timer Reload Register */
TMR0    .equ 0x1940
 .org 0x1940
__tmrlr0   .res.b 2             ;001940
TMRLR0    .equ 0x1940
__tmr1   .res.b 2             ;001942
TMR1    .equ 0x1942
 .org 0x1942
__tmrlr1   .res.b 2             ;001942
TMRLR1    .equ 0x1942
__tcdt   .res.b 2             ;001944  /* IO Timer Data */
TCDT    .equ 0x1944
__sgfr   .res.b 1             ;001946  /* Sound Generator */
SGFR    .equ 0x1946
__sgar   .res.b 1             ;001947
SGAR    .equ 0x1947
__sgdr   .res.b 1             ;001948
SGDR    .equ 0x1948
__sgtr   .res.b 1             ;001949
SGTR    .equ 0x1949
__wtbr   .res.b 3             ;00194A  /* Watch Timer */
WTBR    .equ 0x194A
__wtsr   .res.b 1             ;00194D
WTSR    .equ 0x194D
__wtmr   .res.b 1             ;00194E
WTMR    .equ 0x194E
__wthr   .res.b 1             ;00194F
WTHR    .equ 0x194F
__pwc10   .res.b 1             ;001950  /*  Stepping motor controller 0 */
PWC10    .equ 0x1950
__pwc20   .res.b 1             ;001951
PWC20    .equ 0x1951
__pws10   .res.b 1             ;001952
PWS10    .equ 0x1952
__pws20   .res.b 1             ;001953
PWS20    .equ 0x1953
__pwc11   .res.b 1             ;001954  /*  Stepping motor controller 1 */
PWC11    .equ 0x1954
__pwc21   .res.b 1             ;001955
PWC21    .equ 0x1955
__pws11   .res.b 1             ;001956
PWS11    .equ 0x1956
__pws21   .res.b 1             ;001957
PWS21    .equ 0x1957
__pwc12   .res.b 1             ;001958  /*  Stepping motor controller 2 */
PWC12    .equ 0x1958
__pwc22   .res.b 1             ;001959
PWC22    .equ 0x1959
__pws12   .res.b 1             ;00195A
PWS12    .equ 0x195A
__pws22   .res.b 1             ;00195B
PWS22    .equ 0x195B
__pwc13   .res.b 1             ;00195C  /*  Stepping motor controller 3 */
PWC13    .equ 0x195C
__pwc23   .res.b 1             ;00195D
PWC23    .equ 0x195D
__pws13   .res.b 1             ;00195E
PWS13    .equ 0x195E
__pws23   .res.b 1             ;00195F
PWS23    .equ 0x195F
 .org 0x1FF0
__padr0_l   .res.b 1             ;001FF0  /* ROM CORRECTION */
PADR0_L    .equ 0x1FF0
__padr0_m   .res.b 1             ;001FF1
PADR0_M    .equ 0x1FF1
__padr0_h   .res.b 1             ;001FF2
PADR0_H    .equ 0x1FF2
__padr1_l   .res.b 1             ;001FF3
PADR1_L    .equ 0x1FF3
__padr1_m   .res.b 1             ;001FF4
PADR1_M    .equ 0x1FF4
__padr1_h   .res.b 1             ;001FF5
PADR1_H    .equ 0x1FF5
 .org 0x1A00
__canm0   .res.b 0x40          ;001A00  /* CAN message buffer */
CANM0    .equ 0x1A00
___dmyc0   .res.b 0x40          ;001A40
_DMYC0    .equ 0x1A40
___dmyc1   .res.b 0x40          ;001A80
_DMYC1    .equ 0x1A80
___dmyc2   .res.b 0x40          ;001AC0
_DMYC2    .equ 0x1AC0
__canm1   .res.b 0x40          ;001B00
CANM1    .equ 0x1B00
___dmyc3   .res.b 0x40          ;001B40
_DMYC3    .equ 0x1B40
___dmyc4   .res.b 0x40          ;001B80
_DMYC4    .equ 0x1B80
 .org 0x1CC0
___dmyc5   .res.b 0x40          ;001CC0
_DMYC5    .equ 0x1CC0
 .org 0x1C00
__canh0   .res.b 0x1C          ;001C00  /* Status and control register, higher part */
CANH0    .equ 0x1C00
 .org 0x1D00
__canh1   .res.b 0x1C          ;001D00  /* Status and control register, higher part */
CANH1    .equ 0x1D00
 .org 0x1FFF
___endio   .res.b 1             ;001FFF
_ENDIO    .equ 0x1FFF


 .end

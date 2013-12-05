

#ifndef __ISD_H
#define __ISD_H

#ifndef _NUM_ISD
#define _NUM_ISD 3
#endif

#if _NUM_ISD < 1 || _NUM_ISD > 16
#  error Invalid number of EIIOS descriptors
#endif


/* structure of ISD */
typedef union {
    struct 
    {
        unsigned char   BAPL;       /* lower  8 Bit of Buffer Address Pointer */
        unsigned char   BAPM;       /* middle 8 Bit of Buffer Address Pointer */
        unsigned char   BAPH ;      /* upper  8 Bit of Buffer Address Pointer */
        unsigned char   ISCS ;      /* Interrupt Service Control and Status   */
        unsigned short  IOA  ;      /* IO-Address in bank zero */
        unsigned short  DCT  ;      /* current Data Counter */
    } reg;
    struct 
    {
        unsigned short  BAPML;      /* use this when asigning __near pointers */
    } regc;                     
} ISDSTR;

extern ISDSTR Isd[];

#if _NUM_ISD >= 1 
#  define ISD0_BAPML     (Isd[0].regc.BAPML)
#  define ISD0_BAPL      (Isd[0].reg.BAPL)
#  define ISD0_BAPM      (Isd[0].reg.BAPM)
#  define ISD0_BAPH      (Isd[0].reg.BAPH)
#  define ISD0_ISCS      (Isd[0].reg.ISCS)
#  define ISD0_IOA       (Isd[0].reg.IOA)
#  define ISD0_DCT       (Isd[0].reg.DCT)
#  if _NUM_ISD == 1
#    define ISD_BAPML    (Isd[0].regc.BAPML)
#    define ISD_BAPL     (Isd[0].reg.BAPL)
#    define ISD_BAPM     (Isd[0].reg.BAPM)
#    define ISD_BAPH     (Isd[0].reg.BAPH)
#    define ISD_ISCS     (Isd[0].reg.ISCS)
#    define ISD_IOA      (Isd[0].reg.IOA)
#    define ISD_DCT      (Isd[0].reg.DCT)
#  endif
#endif
#if _NUM_ISD >= 2 
#  define ISD1_BAPML     (Isd[1].regc.BAPML)
#  define ISD1_BAPL      (Isd[1].reg.BAPL)
#  define ISD1_BAPM      (Isd[1].reg.BAPM)
#  define ISD1_BAPH      (Isd[1].reg.BAPH)
#  define ISD1_ISCS      (Isd[1].reg.ISCS)
#  define ISD1_IOA       (Isd[1].reg.IOA)
#  define ISD1_DCT       (Isd[1].reg.DCT)
#endif
#if _NUM_ISD >= 3 
#  define ISD2_BAPML     (Isd[2].regc.BAPML)
#  define ISD2_BAPL      (Isd[2].reg.BAPL)
#  define ISD2_BAPM      (Isd[2].reg.BAPM)
#  define ISD2_BAPH      (Isd[2].reg.BAPH)
#  define ISD2_ISCS      (Isd[2].reg.ISCS)
#  define ISD2_IOA       (Isd[2].reg.IOA)
#  define ISD2_DCT       (Isd[2].reg.DCT)
#endif
#if _NUM_ISD >= 4 
#  define ISD3_BAPML     (Isd[3].regc.BAPML)
#  define ISD3_BAPL      (Isd[3].reg.BAPL)
#  define ISD3_BAPM      (Isd[3].reg.BAPM)
#  define ISD3_BAPH      (Isd[3].reg.BAPH)
#  define ISD3_ISCS      (Isd[3].reg.ISCS)
#  define ISD3_IOA       (Isd[3].reg.IOA)
#  define ISD3_DCT       (Isd[3].reg.DCT)
#endif
#if _NUM_ISD >= 5 
#  define ISD4_BAPML     (Isd[4].regc.BAPML)
#  define ISD4_BAPL      (Isd[4].reg.BAPL)
#  define ISD4_BAPM      (Isd[4].reg.BAPM)
#  define ISD4_BAPH      (Isd[4].reg.BAPH)
#  define ISD4_ISCS      (Isd[4].reg.ISCS)
#  define ISD4_IOA       (Isd[4].reg.IOA)
#  define ISD4_DCT       (Isd[4].reg.DCT)
#endif



#endif /* __ISD_H */
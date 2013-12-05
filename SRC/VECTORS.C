/*------------------------------------------------------------------------
  VECTORS.C
  - Interrupt level (priority) setting
  - Interrupt vector definition

------------------------------------------------------------------------*/

#include "mb90590.h"
#include "global.h"

/*------------------------------------------------------------------------
   InitIrqLevels()

   This function  pre-sets all interrupt control registers. It can be used
   to set all interrupt priorities in static applications. If this file
   contains assignments to dedicated resources, verify  that the
   appropriate controller is used.

   NOTE: value 7 disables the interrupt and value 0 sets highest priority.
   NOTE: Two resource interrupts always share one ICR register.
*/
void InitIrqLevels(void)
{
/*  ICRxx               shared IRQs for ICR */

//#ifdef PLATA_ADC
 //   ICR00 = 5;      /*  IRQ11-IRQ12 */
//#else
    ICR00 = 7;      /*  IRQ11-IRQ12 */
//#endif
    
    ICR01 = 2;      /*  IRQ13
                        IRQ14 */
    ICR02 = 2;      /*  IRQ15
                        IRQ16 */
    ICR03 = 7;      /*  IRQ17
                        IRQ18 */
    ICR04 = 7;      /*  IRQ19
                        IRQ20 */
    ICR05 = 7;      /*  IRQ21
                        IRQ22 */
    ICR06 = 4;      /*  IRQ23
                        IRQ24 */
    ICR07 = 7;      /*  IRQ25
                        IRQ26 */
    ICR08 = 7;      /*  IRQ27
                        IRQ28 */
    ICR09 = 7;      /*  IRQ29
                        IRQ30 */
    ICR10 = 7;      /*  IRQ31
                        IRQ32 */
    ICR11 = 7;      /*  IRQ33
                        IRQ34 */
    ICR12 = 3;      /*  IRQ35
                        IRQ36 */
    ICR13 = 7;      /*  IRQ37
                        IRQ38 */
    ICR14 = 7;      /*  IRQ39
                        IRQ40 */
    ICR15 = 7;      /*  IRQ41
                        IRQ42 */
}
/*------------------------------------------------------------------------
   Prototypes
   
   Add your own prototypes here. Each vector definition needs is proto-
   type. Either do it here or include a header file containing them.

*/
__interrupt void DefaultIRQHandler (void);
__interrupt void Getch0 (void);
//__interrupt void Getch1 (void);
//__interrupt void Getch2 (void);
__interrupt void ReloadTimer0(void);
__interrupt void ReloadTimer1(void);
__interrupt void TimeBaseTimer(void);
//__interrupt void inputcapture23(void);
//__interrupt void inputcapture45(void);
//__interrupt void iq_frt_ovr(void);
__interrupt void onCANTransmit_0(void);
__interrupt void onCANTransmit_1(void);
__interrupt void onCANReceive_0(void);
__interrupt void onCANReceive_1(void);

//#ifdef PLATA_ADC
//__interrupt void INT2(void);
//#endif


#pragma intvect DefaultIRQHandler  9    /* software interrupt 9         */
#pragma intvect DefaultIRQHandler 10    /* exeception handler           */
#pragma intvect DefaultIRQHandler 11    /* Time-base timer              */
#pragma intvect DefaultIRQHandler 12    /* External interrupt(INT0-INT7)*/
#pragma intvect onCANReceive_0    13    /* CAN 0 RX                     */
#pragma intvect onCANTransmit_0   14    /* CAN 0 TX/NX                  */
#pragma intvect onCANReceive_1    15    /* CAN 1 RX                     */
#pragma intvect onCANTransmit_1   16    /* CAN 1 TX/NX                  */
#pragma intvect DefaultIRQHandler 17    /* PPG 0/1                      */
#pragma intvect DefaultIRQHandler 18    /* PPG 2/3                      */
#pragma intvect DefaultIRQHandler 19    /* PPG 4/5                      */
#pragma intvect DefaultIRQHandler 20    /* PPG 6/7                      */
#pragma intvect DefaultIRQHandler 21    /* PPG 8/9                      */
#pragma intvect DefaultIRQHandler 22    /* PPG A/B                      */
#pragma intvect ReloadTimer0	  23    /* 16-bit Reload Timer 0        */
#pragma intvect ReloadTimer1	  24    /* 16-bit Reload Timer 1        */
#pragma intvect DefaultIRQHandler 25    /* Input Capture 0/1            */
#pragma intvect DefaultIRQHandler 26    /* Output Capture 0/1           */
#pragma intvect DefaultIRQHandler 27    /* Input Capture 2/3            */
#pragma intvect DefaultIRQHandler 28    /* Output Capture 2/3           */
#pragma intvect DefaultIRQHandler 29    /* Input Capture 4/5            */
#pragma intvect DefaultIRQHandler 30    /* Output Capture 4/5           */
#pragma intvect DefaultIRQHandler 31    /* A/D Converter                */
#pragma intvect DefaultIRQHandler 32    /* I/O Timer / Watch Timer      */
#pragma intvect DefaultIRQHandler 33    /* Serial I/O                   */
#pragma intvect DefaultIRQHandler 34    /* Sound Generator              */
#pragma intvect Getch0			  35    /* UART 0 RX                    */
#pragma intvect DefaultIRQHandler 36    /* UART 0 TX                    */
#pragma intvect DefaultIRQHandler 37    /* UART 1 RX                    */
#pragma intvect DefaultIRQHandler 38    /* UART 1 TX                    */
#pragma intvect DefaultIRQHandler 39    /* UART 2 RX                    */
#pragma intvect DefaultIRQHandler 40    /* UART 2 TX                    */
#pragma intvect DefaultIRQHandler 41    /* Flash Memory                 */
#pragma intvect DefaultIRQHandler 42    /* Delayed interrupt            */

/*------------------------------------------------------------------------
   DefaultIRQHandler()

   This function is a placeholder for all vector definitions. Either use
   your own placeholder or add necessary code here. 
*/
__interrupt void DefaultIRQHandler (void)
{
    __DI();                              /* disable interrupts */
    while(1)
    	__wait_nop();                    /* halt system */
}

#ifndef _UART_H
#define _UART_H



#define DOS_LF  TRUE            /* assumes DOS-format outside for strings
								   use internal LF external CR/LF */
/* configure transmission queue */

/*-------------------- prototypes ---------------------*/

void initUART_0 (void);			/* set parameter */
//void InitUART_1(void);
//void InitUART_2(void);
void InitUART(void);

void put_p(unsigned char N);
void Putch (unsigned char ch);      /* sends a char */
void puts (unsigned char *Name2);	/* Puts a String to UART0 */
char Getch(void);
void Putch1 (unsigned char ch);     /* sends a char */
void puts1 (unsigned char *Name2);	/* Puts a String to UART1 */
void Putch2 (unsigned char ch);     /* sends a char */
void puts2 (unsigned char *Name2);	/* Puts a String to UART2 */

#endif /* _UARTF_H */

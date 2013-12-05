
#ifndef _SIO_H
#define _SIO_H

#define SIO_2MHz 	1
#define SIO_1MHz	2
#define SIO_250KHz 	3
#define SIO_125KHz	4
		


#define WRITE_SIO(data)		while(SMCS_BUSY == 1);SDR=data;

void InitSIO(unsigned char speed);
void start_sio(void);
void stop_sio(void);
unsigned char  Send_SIO(unsigned char data);
void SetInvertSIO(unsigned char Invert);
void SetMSBFirstSIO(void);
void SetLSBFirstSIO(void);



#endif

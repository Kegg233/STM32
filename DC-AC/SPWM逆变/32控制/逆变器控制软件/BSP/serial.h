
#ifndef   SERIAL_H
#define   SERIAL_H


extern volatile INT8U command[100];

extern volatile INT8U commandcounter,commandflag,comcounter;

void 			Usart1Init			(INT32S val);
void 			Usart2Init			(INT32S val);
void 			PutUsart1			(INT8U ch);
INT32S 			Put_Uart			(INT8U *q);
INT32S 			Put_Uarts			(INT8U *q,INT32U number);
void 			UartPrintf			(const char *fmt,...);
void 			Uart2Printf			(const char *fmt,...);
INT32S 			Put_Uart2			(INT8U *q);
INT32S 			GetUartBufferCtr	(void);




#endif









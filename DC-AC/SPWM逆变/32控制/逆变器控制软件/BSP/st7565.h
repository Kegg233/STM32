
#ifndef   ST7576_H
#define   ST7576_H

void ST7576Reg_Init(void);
void Init_ST7576(void);
void gotoxy(INT8U x,INT8U y);
INT8U dprintf(INT8U *fmt, ...);
INT8U dprintf24(INT8U *fmt, ...);
void cls(void);
INT8U dprintf8(INT8U *fmt, ...);
void dgotoxy(INT8U x,INT8U y);

#endif


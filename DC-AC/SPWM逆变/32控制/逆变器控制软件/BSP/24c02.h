
#ifndef EEPROM24C02_H
#define EEPROM24C02_H


#define NUMBERADDRESS     1u	    //��¼�ű����ַ
#define LINGDIANADDRESS   3u		//��㱣���ַ
#define MISHIADDRESS	  8u		//����ģʽ�����ַ
#define FUZHIADDRESS	  13u		//��������ֵ�����ַ
#define DAYINOUTADDRESS	18u		//���ߴ�ӡ�����ַ
#define JILUADDRESS		  200u		//�������Ļ�ַ
#define NBFLAG			  44u		//�������Խ��ռ��rom��С



void 		I2C_Init		(void);
void 		I2C_Clean		(void);
void 		WrToROM			(INT16U address,INT8U Data);
INT8U 	RdFromROM		(INT16U address);
void 		WriteFloat	(INT16U address,float data);
float 	ReadFloat		(INT16U address);
void 		WriteINT32U	(INT16U address,INT32U data);
INT32U 	ReadINT32U	(INT16U address);
void 		WriteINT16U	(INT16U address,INT16U data);
INT16U 	ReadINT16U	(INT16U address);





#endif


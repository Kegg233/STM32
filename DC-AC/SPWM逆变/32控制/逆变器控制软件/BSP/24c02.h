
#ifndef EEPROM24C02_H
#define EEPROM24C02_H


#define NUMBERADDRESS     1u	    //记录号保存地址
#define LINGDIANADDRESS   3u		//零点保存地址
#define MISHIADDRESS	  8u		//测试模式保存地址
#define FUZHIADDRESS	  13u		//传感器幅值保存地址
#define DAYINOUTADDRESS	18u		//曲线打印输出地址
#define JILUADDRESS		  200u		//结果记入的基址
#define NBFLAG			  44u		//单个测试结果占用rom大小



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


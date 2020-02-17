/****************************************************************
* Copyright (c) 2010 ,
* All rights reserved. 
*
*
*文件名称：卡尔曼滤波 
*文件标示：
*摘要	 ：
*
*
*当前版本：v1.0
*作者	 ：李良万
*完成日期：2012.6.6
*****************************************************************/
#include <math.h> 

    /*initial values for the kalman filter */
static     float x_est_last = 0; 
static     float P_last = 0; 
    /*/the noise in the system */
static     float Q = 0.1; 
static     float R = 0.9;     
static     float K; 
static     float P; 
static     float P_temp; 
static     float x_temp_est; 
static     float x_est; 
static     float z_measured; /*/the 'noisy' value we measured  */
 //   float z_real = 0.5; /*/the ideal value we wish to measure */
static     float sum_error_kalman = 0; 
static     float sum_error_measure = 0;

float kalman(float z_real) 
{ 		
	/*/do a prediction */
	x_temp_est = x_est_last; 
	P_temp = P_last + Q; 
	/*/calculate the Kalman gain */
	K = P_temp * (1.0/(P_temp + R)); 
	/*/measure*/
	z_measured = z_real ;
	x_est = x_temp_est + K * (z_measured - x_temp_est);  
	P = (1- K) * P_temp; 
	 
	sum_error_kalman += fabs(z_real - x_est); 
	sum_error_measure += fabs(z_real-z_measured); 
	 
	P_last = P; 
	x_est_last = x_est; 

	return x_est; 
}





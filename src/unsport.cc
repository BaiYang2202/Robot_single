#ifndef _UNSPORT_H_
#define _UNSPORT_H_

#include <iostream>
#include "unsport.h"
#include "platform_conf.h"

float upmotor_rot_w(float t)
{
	return (2.0f*PI*MAX_POS/Tm) * sin(2.0f*PI*t/Tm);
}

float dnmotor_rot_w(float upmotor_r, float dnmotor_r, float upmotor_w)
{
	float upleg_r = INIT_TA_SL + upmotor_r;
	float dnleg_r = dnmotor_r + INIT_TB_SL + upleg_r;
	float l1cup = UP_LEG_LEN * cos(upleg_r);
	float l2cdn = DN_LEG_LEN * cos(dnleg_r);
	float tmp1 = (l1cup + l2cdn) * upmotor_w;
	return -tmp1/l2cdn;
}

float dnleg_motor_r(float upmotor_r)
{
	float upleg_r = INIT_TA_SL + upmotor_r;
	float dnleg_r = asin(-UP_LEG_LEN*sin(upleg_r)/DN_LEG_LEN);
	return dnleg_r - upleg_r - INIT_TB_SL;
}

float upleg_motor_r(float t)
{
	float pwave = MAX_POS * (1.0f - cos(2.0f*PI*t/Tm));
	return pwave + LV1_TA_SL - INIT_TA_SL;
}

float cul_foot(float upmotor_r, float dnmotor_r)
{
	float upleg_r = INIT_TA_SL + upmotor_r;
	float dnleg_r = dnmotor_r + INIT_TB_SL + upleg_r;
	float l1c1 = UP_LEG_LEN * cos(upleg_r);
	float l2c2 = DN_LEG_LEN * cos(dnleg_r);
	float ftom = l1c1 + l2c2;
	return INIT_FTM_LEN - ftom; 
}

float foot_v(float upmotor_r, float dnmotor_r, float upmotor_w, float dnmotor_w)
{
	float upleg_r = INIT_TA_SL + upmotor_r;
	float dnleg_r = dnmotor_r + INIT_TB_SL + upleg_r;
	float l1sup_w = UP_LEG_LEN * sin(upleg_r) * upmotor_w;
	float l2sdn_w12 = DN_LEG_LEN * sin(dnleg_r) * (upmotor_w + dnmotor_w);
	return l1sup_w + l2sdn_w12;
}

#endif
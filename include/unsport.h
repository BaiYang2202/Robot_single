#ifndef _LEG_CONFIG_H_
#define _LEG_CONFIG_H_

float upleg_motor_r(float t);
float dnleg_motor_r(float upmotor_r);

float upmotor_rot_w(float t);
float dnmotor_rot_w(float upmotor_r, float dnmotor_r, float upmotor_w);

float cul_foot(float upmotor_r, float dnmotor_r);
float foot_v(float upmotor_r, float dnmotor_r, float upmotor_w, float dnmotor_w);

#endif
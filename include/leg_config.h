#ifndef _LEG_CONFIG_H_
#define _LEG_CONFIG_H_

#include <iostream>
#include "motor.h"
#include "platform_conf.h"
class leg_t
{
    public:
        leg_t(float leg_len_) : leg_len(leg_len_) {}
        float leg_len;
        float slant_offset;
        motor_para motor_in;  
};

float unsport(float theta1)
{
	//逆解，大腿电机偏转角做形参，反馈小腿电机偏转角
	float theta2=asin((-UP_LEG_LEN/DN_LEG_LEN)*sin(theta1));
	theta2 = theta2 - theta1;
	// printf("theta1 = %f,theta2 = %f\n",theta1,theta2);
    std::cout << "theta1:" << theta1 << " theta2:" << theta2 << std::endl;
	return theta2;
	
}
#endif
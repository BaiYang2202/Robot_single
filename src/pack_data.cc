#ifndef _PACK_DATA_CC_
#define _PACK_DATA_CC_

#include "pack_data.h"

can_data_type pack_data(float pos, float kp, float kd, float vel, float t)
{
    can_data_type data = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd};
    uint P_span = 0xffff, V_span = 0xfff, KP_span = 0xfff, KD_span = 0xfff, T_span = 0xfff;
    float pos_dif = pos + POS_MAX;
    float vel_dif = vel + VEL_MAX;
    float kp_dif  = kp;
    float kd_dif  = kd;
    float t_dif   = t + T_MAX;
    uint p_data = (pos_dif / POS_MAX / 2.0f) * P_span;
    uint v_data = (vel_dif / VEL_MAX / 2.0f) * V_span;
    uint kp_data = (kp_dif / KP_MAX) * KP_span;
    uint kd_data = (kd_dif / KD_MAX) * KD_span;
    uint t_data  = (t_dif  / T_MAX / 2.0f) * T_span;

    data[0] = (p_data >> 8) & 0xff;
    data[1] = p_data & 0xff;
    data[2] = (v_data >> 4) & 0xff;
    data[3] = ((v_data & 0xf) << 4) | ((kp_data >> 8) & 0xf);
    data[4] = kp_data & 0xff;
    data[5] = (kd_data >> 4) & 0xff;
    data[6] = ((kd_data & 0xf) << 4) | ((t_data >> 8) & 0xf);
    data[7] = t_data & 0xff;

    return data;
}

#endif
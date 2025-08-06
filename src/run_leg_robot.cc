#ifndef _RUN_LEG_ROBOT_CC_
#define _RUN_LEG_ROBOT_CC_

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "unsport.h"
#include "pack_data.h"
#include "init_send.h"
#include "key_input.h"

using namespace std;

extern float high_offset;
extern float move_offset;

void init_communication()
{
    can0_send_init();
    usleep(500000);
    can1_send_init();
    usleep(500000);

    return;
}

void init_motor()
{
    cout << "if you are ready, please input any one number to initialize the motors >>";
    int one_ = 0;
    cin >> one_;
    cout << endl;

    //motor step into motor mode
    can0_send(init_motor_data);
    can1_send(init_motor_data);
    usleep(500000);

    //turn on motor and rotate to zero position
    can_data_type motor_zero = pack_data(0,5.0,0.2);
    for(int i = 0; i < 8; i++)
        cout << "data[" << i << "]: " << hex << setw(2) << setfill('0') << motor_zero[i] << endl;
    cout << "size: " << motor_zero.size() << endl;
    can0_send(motor_zero);
    can1_send(motor_zero);
    usleep(1000000);
    motor_zero.clear();

    //Torque output
    can_data_type motor_a = pack_data(0, DN0_KP, DN0_KD);
    can_data_type motor_b = pack_data(0, DN1_KP, DN1_KD);
    can0_send(motor_a);
    can1_send(motor_b);
    cout << "please input any one number to curl up the leg >>";
    cin >> one_;
    cout << endl;

    motor_a = pack_data(LV1_TA_SL, 5.0f, 0.2f);
    motor_b = pack_data(LV1_TB_SL, 5.0f, 0.2f);
    can0_send(motor_a);
    can1_send(motor_b);
    usleep(500000);
    motor_a = pack_data(LV1_TA_SL, DN0_KP, DN0_KD);
    motor_b = pack_data(LV1_TB_SL, DN1_KP, DN1_KD);
    can0_send(motor_a);
    can1_send(motor_b);
    usleep(500000);

    // curling leg and being ready to jump 
    for(float tt = 0;tt < Tm/2.0f;tt += 0.002f)
    {
        //curl leg's process   
        //Foot trajectory planning and kinematic inverse solution
        float up_motor_p = upleg_motor_r(tt);
        float dn_motor_p = dnleg_motor_r(up_motor_p);
        //Calculated expected speed
        // foot_vell = vel_down(tt);
        cout << "up_pos: " << up_motor_p << " down_pos:" << dn_motor_p << endl; 
        motor_a = pack_data(up_motor_p+move_offset, DN0_KP, DN0_KD);
        motor_b = pack_data(dn_motor_p, DN1_KP, DN1_KD);
        can0_send(motor_a);
        can1_send(motor_b);
        usleep(10000);
    }
    cout << "Input any one number to run the platform >>";
    cin >> one_;
    cout << endl;
}

void leg_jump()
{
    extern bool exit_run;
    can_data_type up_data;
    can_data_type dn_data;
    while(!exit_run)
    {
        for(float tt = Tm/2;tt < Tm;tt += 0.002f)
        {
            //stretch leg's process

            //Foot trajectory planning and kinematic inverse solution
            float up_motor_p = upleg_motor_r(tt);
            float dn_motor_p = dnleg_motor_r(up_motor_p);
            //Calculated expected speed
            // foot_vell = vel_down(tt);
            cout << "up_pos: " << up_motor_p << " down_pos:" << dn_motor_p << endl; 
            up_data = pack_data(up_motor_p+move_offset, UP0_KP+high_offset, UP0_KD+(high_offset*1.5f));
            dn_data = pack_data(dn_motor_p, UP1_KP+high_offset, UP1_KD+(high_offset*1.5f));
            can0_send(up_data);
            can1_send(dn_data);
            up_data.clear();
            dn_data.clear();
            usleep(UP_D_INTV);
        }
        usleep(UP_T_INTV);
        for(float tt = 0.000;tt < Tm/2.0f;tt += 0.002f)
        {
            //curl leg's process

            //Foot trajectory planning and kinematic inverse solution
            float up_motor_p = upleg_motor_r(tt);
            float dn_motor_p = dnleg_motor_r(up_motor_p);
            //Calculated expected speed
            // foot_vell = vel_down(tt);
            cout << "up_pos: " << up_motor_p << " down_pos:" << dn_motor_p << endl; 
            up_data = pack_data(up_motor_p+move_offset, DN0_KP, DN0_KD);
            dn_data = pack_data(dn_motor_p, DN1_KP, DN1_KD);
            can0_send(up_data);
            can1_send(dn_data);
            up_data.clear();
            dn_data.clear();
            usleep(UP_D_INTV);
        }
        usleep(DN_T_INTV);
    }
    return;
}

int main(){

    pthread_t keyboard_input;
    
    init_communication();
    init_motor();
    pthread_create(&keyboard_input, NULL, key_input, NULL);
    cout << "Manual starting!!!" << endl;
    leg_jump();
    close_communication();
}

#endif
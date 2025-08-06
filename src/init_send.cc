#ifndef _INIT_CAN_CC_
#define _INIT_CAN_CC_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include "platform_conf.h"

struct can_frame frame_s0;
struct can_frame frame_s1;
struct sockaddr_can addr0;
struct sockaddr_can addr1;
struct ifreq ifr0;
struct ifreq ifr1;

int s0 = 0;
int s1 = 0;


void can0_send(can_data_type can_num)
{
    
	int nbytes = 0;
    //5.Set send data
    frame_s0.can_id = CAN_0;
    frame_s0.can_dlc = 8;
    frame_s0.data[0] = can_num[0];
    frame_s0.data[1] = can_num[1];
    frame_s0.data[2] = can_num[2];
    frame_s0.data[3] = can_num[3];
    frame_s0.data[4] = can_num[4];
    frame_s0.data[5] = can_num[5];
    frame_s0.data[6] = can_num[6];
    frame_s0.data[7] = can_num[7];

    //6.Send message
    nbytes = write(s0, &frame_s0, sizeof(frame_s0)); 
    // if(nbytes != sizeof(frame_s0)) {
    //     //printf("Send Error frame[0]!\r\n");
    //     //system("sudo ifconfig can0 down");
    // }
    return;
}

void can1_send(can_data_type can_num)
{
    
	int nbytes1 = 0;
    //5.Set send data
    frame_s1.can_id = CAN_1;
    frame_s1.can_dlc = 8;
    frame_s1.data[0] = can_num[0];
    frame_s1.data[1] = can_num[1];
    frame_s1.data[2] = can_num[2];
    frame_s1.data[3] = can_num[3];
    frame_s1.data[4] = can_num[4];
    frame_s1.data[5] = can_num[5];
    frame_s1.data[6] = can_num[6];
    frame_s1.data[7] = can_num[7];

    
    //6.Send message
    nbytes1 = write(s1, &frame_s1, sizeof(frame_s1)); 
    // if(nbytes1 != sizeof(frame_s1)) {
    //     //printf("nbytes1=%d\n",nbytes1);
    //     //printf("Send Error frame[1]!\r\n");
    //     //system("sudo ifconfig can1 down");
    // }
    return;
}

void can0_send_init()
{
    int ret;
    memset(&frame_s0, 0, sizeof(struct can_frame));
    system("sudo ip link set can0 type can bitrate 1000000");
    system("sudo ifconfig can0 up");
        
    //1.Create socket
    s0 = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (s0 < 0) {
        perror("socket PF_CAN failed");
        return;
    }
    //2.Specify can0 device
    strcpy(ifr0.ifr_name, "can0");
    ret = ioctl(s0, SIOCGIFINDEX, &ifr0);
    if (ret < 0) {
        perror("ioctl failed");
        return;
    }
    //3.Bind the socket to can0
    addr0.can_family = AF_CAN;
    addr0.can_ifindex = ifr0.ifr_ifindex;
    ret = bind(s0, (struct sockaddr *)&addr0, sizeof(addr0));
    if (ret < 0) {
        perror("bind failed");
        return;
    }
    //4.Define receive rules
    // struct can_filter rfilter[1];
    // rfilter[0].can_id = 0x000;
    // rfilter[0].can_mask = CAN_SFF_MASK;
    // setsockopt(s0, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter)); 

    return;
}


void can1_send_init()
{
    int ret;

    memset(&frame_s1, 0, sizeof(struct can_frame));

    system("sudo ip link set can1 type can bitrate 1000000");
    system("sudo ifconfig can1 up");
    //printf("this is a can send demo\r\n");
    //1.Create socket
    s1 = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (s1 < 0) {
        perror("socket PF_CAN failed");
        return;
    }
    
    //2.Specify can0 device
    strcpy(ifr1.ifr_name, "can1");
    ret = ioctl(s1, SIOCGIFINDEX, &ifr1);
    if (ret < 0) {
        perror("ioctl failed");
        return;
    }
    
    //3.Bind the socket to can0
    addr1.can_family = AF_CAN;
    addr1.can_ifindex = ifr1.ifr_ifindex;
    ret = bind(s1, (struct sockaddr *)&addr1, sizeof(addr1));
    if (ret < 0) {
        perror("bind failed");
        return;
    }
    //4.Define receive rules
    // struct can_filter rfilter[1];
    // rfilter[0].can_id = CAN_1;
    // rfilter[0].can_mask = CAN_SFF_MASK;
    // setsockopt(s1, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter)); 

    return;
}

void close_communication()
{
    system("sudo ifconfig can0 down");
    system("sudo ifconfig can1 down");
    return;
}

#endif
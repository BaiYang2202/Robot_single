#ifndef _INIT_SEND_H_
#define _INIT_SEND_H_

void can0_send_init();
void can1_send_init();
void can0_send(can_data_type can_num);
void can1_send(can_data_type can_num);
void close_communication();

#endif
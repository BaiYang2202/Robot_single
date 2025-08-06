#ifndef _PLATFORM_CONF_H_
#define _PLATFORM_CONF_H_
#include <vector>
#include <math.h>

#define PI              3.14159f

#define CAN_0           0x0
#define CAN_1           0x1
#define DATA_LEN        8

#define UP_LEG_LEN      200.0f
#define DN_LEG_LEN      220.0f
#define LEG_ROT_MAX     -0.001f
#define LEG_ROT_MIN     -0.524f

//need change
#define INIT_FTM_LEN    387.5f
// #define INIT_TA_SL      (-acos((std::pow(UP_LEG_LEN,2)+pow(INIT_FTM_LEN,2)-pow(DN_LEG_LEN,2))/(2*UP_LEG_LEN*INIT_FTM_LEN)))
#define INIT_TA_SL      -0.416386f
#define INIT_TB_SL      0.792909f
#define LV1_FTM_LEN     365.0f
#define LV1_TA_SL       -0.545312f
#define LV1_TB_SL       1.036338f
#define MAX_POS         -0.524

#define LEG_ROT_SPAN    0.0008
#define UP_D_INTV       3000
#define DN_D_INTV       3000
#define UP_T_INTV       500000
#define DN_T_INTV       500000

#define Tm              1.0f
#define MAX_CURL        280.0f
#define INIT_LEN_FTOM   497.0f
#define INIT_LEN_ROD    274.0f
#define INIT_SLINT_UP   
#define ROD_SLANT_THE   0.123 // ?
#define ANGLE_B         0.155
#define LEN_FIX_VERT    53.0f
#define ROD_TO_SPIN     (PI / 16.0f)


#define UP0_KP          30.0f
#define UP1_KP          40.0f
#define DN0_KP          25.0f
#define DN1_KP          25.0f
#define UP0_KD          1.5f
#define UP1_KD          1.8f
#define DN0_KD          1.5f
#define DN1_KD          1.5f
#define EX0_KP          20.0f
#define EX0_KD          1.8f
#define EX1_KP          20.0f
#define EX1_KD          2.0f
#define DEF_T           0.0f
#define DEF_VEL         0.0f

#define POS_MAX         15.0f
#define VEL_MAX         45.0f
#define KP_MAX          500.0f
#define KD_MAX          5.0f
#define T_MAX           18.0f

typedef unsigned uint;
typedef std::vector<uint> can_data_type;
const can_data_type init_motor_data = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc};
const can_data_type exit_run_motor_data = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc};
#endif

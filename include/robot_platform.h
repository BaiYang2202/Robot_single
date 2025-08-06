#ifndef _ROBOT_PLATFORM_H_
#define _ROBOT_PLATFORM_H_

#include <math.h>
#include "foot.h"
#include "leg_config.h"

class platform_t
{
    public:
        platform_t(float up_leg_, float down_leg_)
        {
            up_leg = new leg_t(up_leg_);
            down_leg = new leg_t(down_leg_);
            The_foot = new foot_t();
        }
        class foot_t* The_foot;
        class leg_t*  up_leg;
        class leg_t*  down_leg;
};

#endif
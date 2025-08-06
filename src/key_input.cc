#include <iostream>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#define POS_MAX 12.5
#define POS_MIN -12.5

static struct termios initial_settings, new_settings;
static int peek_character = -1;
bool exit_run = false;
float high_offset = 0;
float move_offset = 0;

void init_keyboard()
{
    tcgetattr(0,&initial_settings);//obtain parameter and save it in initial_settings
    new_settings = initial_settings;
    new_settings.c_iflag |= IGNCR;//ignore enter input

    new_settings.c_lflag |= ~ICANON;
    new_settings.c_lflag |= ~ECHO;
    new_settings.c_lflag |= ~ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);//set terminal parameter;TCSANOW change state at once;
    //new_settings place preserve parameter of revision
}

void close_keyboard()
{
    tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit()
{
    unsigned char ch;
    int nread;

    if (peek_character != -1) return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
    if(nread == 1)
    {
        peek_character = ch;
        return 1;
    }
    return 0;
}

int readch()
{
    char ch;

    if(peek_character != -1)
    {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0,&ch,1);
    return ch;
}

void* key_input(void* args)
{
    init_keyboard();
    int key_num[3] = {0};
    float step = 0.1;
    while(1)
    {
        for(int count = 0;count < 3;count++)
        {
            kbhit();
            key_num[count] = readch();
            if(key_num[0] != 27) break;
        }
        if(key_num[0] == 32)
        {    
            exit_run = true;
            std::cout << "exit_run!" << std::endl;
            break;
        }
        else if(key_num[0] == 27)
	    {
            switch(key_num[2])
            {
                case 65: std::cout << "Jump higher!" << std::endl;
                    if(high_offset < 10.0f) high_offset += 2.0f;
                    else high_offset = 10.0f;
                    break;
                case 66: std::cout << "Jump lower!" << std::endl;
                    if(high_offset > -8.0f) high_offset -= 2.0f;
                    else high_offset = -8.0f;
                    break;
                case 67: std::cout << "Jump Right!" << std::endl;
                    if(move_offset < -0.2f) move_offset = -0.2f;
                    else move_offset -= 0.04f;
                    break;
                case 68: std::cout << "Jump Left!" << std::endl;
                    if(move_offset > 0.2f) move_offset = 0.2f;
                    else move_offset += 0.04f;
                    break;
                default: std::cout << "Invalid inputing! Please input again:" << std::endl;
            }
        }
        else std::cout << "Invalid inputing! Please input again:" << std::endl;

	    memset(key_num,0,sizeof(key_num));
        usleep(10000);
    }
    close_keyboard();
    return 0;
}

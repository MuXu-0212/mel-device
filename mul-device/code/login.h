#ifndef __login_h
#define __login_h

#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <strings.h>
#include <time.h>
#include <string.h>
#include "datastructure.h"



#define MAXSIZE_STAR 5	//四位数的登录密码
#define MAXSIZE_PS 20	//存放密码的最大长度

#define PATH_BACKGROUND "./bmp/login/background.bmp" //登录界面
#define PATH_PS_1 "./bmp/login/ps_1.bmp"
#define PATH_PS_2 "./bmp/login/ps_2.bmp"
#define PATH_PS_3 "./bmp/login/ps_3.bmp"
#define PATH_PS_4 "./bmp/login/ps_4.bmp"
#define PATH_PS_ERROR "./bmp/login/ps_error1.bmp" //密码输入错误的提示




/*---------------------用户登录界面-----------------*/
// int fd_ts;
// struct input_event ts;

extern void init_ts(); //打开触摸屏驱动文件

//图像显示
extern int PicPrint(char* path, int width, int height, int x, int y);

extern void delay_ms(int ms); //延迟函数
extern char get_usr_input(int x, int y);//获取用户从键盘输入的值

//用户点击屏幕, 获取点击坐标
extern void point_ts( int* x, int* y);

//在随机位置显示图片
int Show_bmp(char* path, int x,int y);

extern int login();

#endif
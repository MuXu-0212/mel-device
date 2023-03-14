#include "menu.h"

//打开lcd驱动
void init_lcd()
{
	int fd_lcd = open(PATH_LCD, O_RDWR);
	if (fd_lcd < 0)
	{
		perror("Don't open the file of lcd!\n");
	}	

	//申请虚拟共享内存
	share_addr = mmap(
		NULL,
		800*480*4,
		PROT_READ|PROT_WRITE,
		MAP_SHARED,
		fd_lcd,
		0
		);
}

//打开触摸屏驱动
void init_ts()
{
	//1.打开触摸屏的驱动文件
	// int fd_ts = open(PATH_TS, O_RDWR);
	fd_ts = open(PATH_TS, O_RDWR);
	if (fd_ts == -1)
	{
		perror("触摸屏驱动文件打开失败!\n");
	}

	//2.从触摸屏当中去读取数据
	// struct input_event ts;
}

//获取文本中的密码
int get_file( char* path, char* passcode)
{
	int fd = open( path, O_RDWR);
	if (fd == -1)
	{
		printf("打开文件失败\n");
		return 0;
	}
	// printf("文件描述符为：%d\n",fd);

	char temp[MAXSIZE_PS] = {0};

	ssize_t ret = read( fd, temp, MAXSIZE_PS);
	strcpy( passcode, temp);

	close(fd);
	return 1;
}


//图像显示
int PicPrint(char* path, int width, int height, int x, int y)
{
	//1.打开lcd驱动文件
	// int fd_lcd = open(PATH_LCD, O_RDWR);
	// if (fd_lcd < 0)
	// {
	// 	perror("Don't open the file of lcd!\n");
	// 	return 0;
	// }

	//2.打开bmp图片
	int fd_bmp = open(path, O_RDWR);
	if (fd_bmp < 0)
	{
		perror("Don't open this picture!\n");
		return 0;
	}

	// //3.申请虚拟共享内存
	// share_addr = mmap(
	// 	NULL,
	// 	height*width*4,
	// 	PROT_READ|PROT_WRITE,
	// 	MAP_SHARED,
	// 	fd_lcd,
	// 	0
	// 	);

	//4.从bmp图片把24位的颜色数据读出来
	char bmp_data[height*width*3];
	bzero(bmp_data, height*width*3);

	int share_addr_temp[height*width];
	bzero(share_addr_temp, height*width);

	//偏移54个字节头信息
	lseek(fd_bmp, 54, SEEK_SET);

	int ret = read(fd_bmp, bmp_data, height*width*3);

	if (ret < 0)
	{
		perror("fail!\n");
		return 0;
	}

	int i,j;

	for (i=0; i<height; i++)
	{
		for (j=0; j<width; j++)
		{
			share_addr_temp[i*width+j] = bmp_data[0+(j+i*width)*3];
			share_addr_temp[i*width+j] |= bmp_data[1+(j+i*width)*3]<<8;
			share_addr_temp[i*width+j] |= bmp_data[2+(j+i*width)*3]<<16;
		}
	}

	//将处理好的图片数据写入到LCD屏,进行映射.
	for(j = 0; j < height; j++)
	{
		for(i = 0; i < width; i++)
		{
			*(share_addr + i + j*width + x + y*width) = share_addr_temp[i+(height-1-j)*width];
		}
	}

	close(fd_bmp);
	return 0;
}


void delay_ms(int ms)
{
	usleep( 1000 * ms);
}

//获取用户从键盘输入的值
char get_usr_input(int x, int y)
{
	while (1)
	{
		//键盘输入1~3
		if (x>194 && x<290
			&& y>177 && y<209)
		{
			return '1';
		}
		if (x>342 && x<454
			&& y>172 && y<209)
		{
			return '2';
		}
		if (x>497 && x<610
			&& y>177 && y<209)
		{
			return '3';
		}
		//键盘输入4~6
		if (x>194 && x<290
			&& y>250 && y<280)
		{
			return '4';
		}
		if (x>342 && x<445
			&& y>250 && y<280)
		{
			return '5';
		}
		if (x>497 && x<605
			&& y>250 && y<280)
		{
			return '6';
		}
		//键盘输入7~9
		if (x>194 && x<290
			&& y>290 && y<330)
		{
			return '7';
		}
		if (x>342 && x<445
			&& y>290 && y<330)
		{
			return '8';
		}
		if (x>497 && x<605
			&& y>290 && y<330)
		{
			return '9';
		}
		//键盘输入'.', '0', 'x'
		if (x>194 && x<290
			&& y>350 && y<400)
		{
			return '.';
		}
		if (x>342 && x<450
			&& y>350 && y<400)
		{
			return '0';
		}
		if (x>497 && x<605
			&& y>350 && y<400)
		{
			return 'x';
		}
		else
		{
			return 'a';	//表示用户触摸在键盘外
		}
	}
}

//在随机位置显示图片
int Show_bmp(char* path, int x, int y)
{
	// int lcd_fd = open( PATH_LCD, O_RDWR);

	// if (lcd_fd < 0)
	// {
	// 	perror("Don't open the file of lcd!\n");
	// 	return 0;
	// }

	int ret;
	char head_buf[54]={0};
	int i, j;

	int bmp_fd = open( path, O_RDWR);   //打开指定路径图片
	//判断是否打开成功
	if(bmp_fd<0)                           
	{
		printf("open bmp failed\n");
		return -1;
	}

	read(bmp_fd, head_buf, 54);            //因为图片数据前54个字节为图片信息,读取54字节

	int width  = head_buf[18] | head_buf[19]<<8 | head_buf[20]<<16 | head_buf[21]<<24;  //图片的宽度
	int height = head_buf[22] | head_buf[23]<<8 | head_buf[24]<<16 | head_buf[25]<<24; //图片的高度
	// printf("width=%d\n", width);
	// printf("height=%d\n", height);

	// if((width*3)%4 != 0) 
	// {
	// 	width = width*3 + 4 -(width*3)%4;
	// }

	int size = head_buf[5]<<24 | head_buf[4]<<16 | head_buf[3]<<8 | head_buf[2];
	if (size > (800*480*3+54) )
	{
		perror("图片太大，该屏幕无法装下\n");
		return -2;
	}
	// printf("11111\n");
	if ((width + x) > 800 || (height + y) > 480)
	{
		perror("在该位置传入图片无法装下\n");
		//越界则标志位flag++
		return -3;
	}

	// printf("22222\n");

	char bmp_buf[width*height*3];      //用于存放图片信息
	bzero(bmp_buf, width*height*3);    //清空数组,用于存放图片信息
	int lcd_buf[width*height];         //LCD屏数存放图片信息.
	bzero(lcd_buf, width*height);      //清空数组,用于LCD显示屏内存映射



	         //跳过54字节，也可以使用lseek()函数偏移光标指针,跳过54字节
	read(bmp_fd, bmp_buf, width*height*3); //读取图片像素色彩信息.

	// printf("33333\n");


	for(j = 0; j < height; j++) 
	{                            //将char类型的图片数据存放到int类型的lcd_buf中，是小端序，字节位移存放
	     //一个char类型的反码是8位，所以移动的是8的倍数，移动2位就是16
		for(i = 0; i < width; i++)
		{
			lcd_buf[i+j*width] = bmp_buf[3*(i+j*width)+0];
			lcd_buf[i+j*width] |= bmp_buf[3*(i+j*width)+1]<<8;
			lcd_buf[i+j*width] |= bmp_buf[3*(i+j*width)+2]<<16;
		}
	}

	share_addr = mmap(
		NULL,
		800*480*4,
		PROT_READ|PROT_WRITE,
		MAP_SHARED,
		fd_lcd,
		0
		);


	//将处理好的图片数据写入到LCD屏,进行映射.
	for(j = 0; j < height; j++)    
	{
		// printf("55555\n");

		for(i = 0; i < width; i++)   
		{
			/*
				shared_addr + i + j*800 + x + y*800    x + y*800  代表是的该图片是在第y行，第x列位置开始显示
				随着i，j的增加， i j也对应着行 列 所以也是 i+j*800   

				lcd_buf[i+(height-1-j)*width]  是倒着显示， width是它的宽度，也对应着800， 
				刚开始是将图片最后一行的第一列的数据赋值到lcd屏幕上对应位置的第一行第一列的数。
			*/
			*(share_addr + i + j*800 + x + y*800) = lcd_buf[i+(height-1-j)*width];
		}
		// printf("77777\n");

	}

	close(bmp_fd);    //关闭图片
	return 0;         //结束该函数
}

//用户点击屏幕, 获取点击坐标
void point_ts( int* x, int* y)
{
	void init_ts();
	while (1)
	{
		read(fd_ts, &ts, sizeof(ts));
		//3.判断当前发生了什么样的事件
		if (ts.type == EV_ABS)
		{
			if (ts.code == ABS_X)
			{
				//4.发生该事件后得到了什么样的结果
				*x = ts.value;
				// printf("x : %d\n", ts.value);
			}
			if (ts.code == ABS_Y)
			{
				//4.发生该事件后得到了什么样的结果
				*y = ts.value;
				// printf("y : %d\n", ts.value);
			}
		}
		//判斷手指是否离开屏幕 
		if(ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0)
		{
	        //坐标轴效验
	        *x = (*x)*800/1024;
			*y = (*y)*480/614;
			// delay_ms(100);
			printf("x = %d ,y = %d \n", *x, *y);
			break;
		}
	} /*while(1)*/

	close(fd_ts);

}



int login()
{

	char login_ps[MAXSIZE_PS] = {0};

	get_file( PATH_FILE_PS, login_ps);

	//记录密码星号的个数
	char* star[MAXSIZE_STAR] = {
		PATH_BACKGROUND,
		PATH_PS_1,
		PATH_PS_2,
		PATH_PS_3,
		PATH_PS_4
	};

	//记录用户输入的密码
	char usr_input[MAXSIZE_PS];
	bzero(usr_input, MAXSIZE_PS);

	//记录用户的键盘输入
	char input = 0;

	int x=0, y=0, flag=0;

	PicPrint( star[flag], 800,  480, 0, 0);

	while (1)
	{
		// printf("11111\n");
		printf("login_ps:%s\n", login_ps);
		printf("usr_input:%s\n", usr_input);
		if (strcmp(usr_input, login_ps) == 0)
		{

			PicPrint( PATH_HOME, 800,  480, 0, 0);
			// while (1)
			// {
			// 	point_ts( &x, &y);
			// }
			break;
		}

		if (flag == 4 && (strcmp(usr_input, login_ps) != 0))
		{
			flag = 0;
			bzero(usr_input, MAXSIZE_PS);
			PicPrint( PATH_PS_ERROR, 800,  480, 0, 0);
			delay_ms(100);
			point_ts( &x, &y);
			PicPrint( PATH_BACKGROUND, 800,  480, 0, 0);
		}
			
		// printf("44444\n");

		//用户点击屏幕, 获取点击坐标
	    point_ts(&x, &y);

		// printf("55555\n");

	    input = get_usr_input( x, y);
	    printf("%c\n", input);

		// printf("22222\n");

	    switch (input)
	    {
			// printf("33333\n");
	    	case '0' ... '9':
	    			*(usr_input+flag)=input;	//保存用户输入
	    			flag++;
					PicPrint( star[flag], 800,  480, 0, 0);//星号加一

					// delay_ms(500);
					for (int i=0; i<MAXSIZE_PS; i++)
					{
						printf("%c", usr_input[i]);
					}
					printf("\n");
					if (flag == MAXSIZE_STAR-1)
					{
						usr_input[flag] = 0;
					}
	    			break;
	    	case 'x' :
	    			if (flag != 0)
	    			{
						PicPrint( star[--flag], 800,  480, 0, 0);//星号减一
						// delay_ms(500);
	    			}
	    			break;
	    	// case '.' : 
	    	// 		break;
	    	default:
	    			break;
	    } /*switch (input)*/
	}  /*while (1)*/


	return 0;
}


// void login()
// {
// 	input_ps();
// }

// int main(int argc, char const *argv[])
// {
// 	// PicPrint(PATH_BACKGROUND, 800, 480, 0, 0);
// 	PicPrint(PATH_BACKGROUND, 800, 480, 0, 0);
// 	test();
// 	return 0;

// }



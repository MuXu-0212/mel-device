#include "menu.h"



//图片从上至下显示
int PicPrint_UpToBottom(char* path, int width, int height, int x, int y)
{
	//1.打开lcd驱动文件
	int fd_lcd = open(PATH_LCD, O_RDWR);
	if (fd_lcd < 0)
	{
		perror("Don't open the file of lcd!\n");
		return 0;
	}

	//2.打开bmp图片
	int fd_bmp = open(path, O_RDWR);
	if (fd_bmp < 0)
	{
		perror("Don't open this picture!\n");
		return 0;
	}

	//3.申请虚拟共享内存
	int* share_addr = mmap(
		NULL,
		height*width*4,
		PROT_READ|PROT_WRITE,
		MAP_SHARED,
		fd_lcd,
		0
		);

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

		if ((j+1)%5 == 0)	//从上往下的关键
		{
			delay_ms(15);
		}
	}

	close(fd_lcd);
	close(fd_bmp);
	munmap(share_addr, height*width*4);
	return 0;
}

//图片从下至上显示
int PicPrint_BottomToUp(char* path, int width, int height, int x, int y)
{
	//1.打开lcd驱动文件
	int fd_lcd = open(PATH_LCD, O_RDWR);
	if (fd_lcd < 0)
	{
		perror("Don't open the file of lcd!\n");
		return 0;
	}

	//2.打开bmp图片
	int fd_bmp = open(path, O_RDWR);
	if (fd_bmp < 0)
	{
		perror("Don't open this picture!\n");
		return 0;
	}

	//3.申请虚拟共享内存
	int* share_addr = mmap(
		NULL,
		height*width*4,
		PROT_READ|PROT_WRITE,
		MAP_SHARED,
		fd_lcd,
		0
		);

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
	for(j = height-1; j >= 0; j--)
	{
		for(i = width-1; i >= 0; i--)
		{
			*(share_addr + i + j*width + x + y*width) = share_addr_temp[i+(height-1-j)*width];
		}

		if (j%5 == 0)	//从上往下的关键
		{
			delay_ms(15);
		}
	}

	close(fd_lcd);
	close(fd_bmp);
	munmap(share_addr, height*width*4);
	return 0;
}

//图片从左至右显示
int PicPrint_LeftToRight(char* path, int width, int height, int x, int y)
{
	//1.打开lcd驱动文件
	int fd_lcd = open(PATH_LCD, O_RDWR);
	if (fd_lcd < 0)
	{
		perror("Don't open the file of lcd!\n");
		return 0;
	}

	//2.打开bmp图片
	int fd_bmp = open(path, O_RDWR);
	if (fd_bmp < 0)
	{
		perror("Don't open this picture!\n");
		return 0;
	}

	//3.申请虚拟共享内存
	int* share_addr = mmap(
		NULL,
		height*width*4,
		PROT_READ|PROT_WRITE,
		MAP_SHARED,
		fd_lcd,
		0
		);

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
	for(i = 0; i < width; i++)
	{
		for(j = 0; j < height; j++)
		{
			*(share_addr + i + j*width + x + y*width) = share_addr_temp[i+(height-1-j)*width];

		}
			if (i%5 == 0)	
			{
				delay_ms(15);
			}
	}

	close(fd_lcd);
	close(fd_bmp);
	munmap(share_addr, height*width*4);
	return 0;
}

//图片从右至左显示
int PicPrint_RightToLeft(char* path, int width, int height, int x, int y)
{
	//1.打开lcd驱动文件
	int fd_lcd = open(PATH_LCD, O_RDWR);
	if (fd_lcd < 0)
	{
		perror("Don't open the file of lcd!\n");
		return 0;
	}

	//2.打开bmp图片
	int fd_bmp = open(path, O_RDWR);
	if (fd_bmp < 0)
	{
		perror("Don't open this picture!\n");
		return 0;
	}

	//3.申请虚拟共享内存
	int* share_addr = mmap(
		NULL,
		height*width*4,
		PROT_READ|PROT_WRITE,
		MAP_SHARED,
		fd_lcd,
		0
		);

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
	for(i = width-1; i >= 0; i--)
	{
		for(j = height-1; j >= 0; j--)
		{
			*(share_addr + i + j*width + x + y*width) = share_addr_temp[i+(height-1-j)*width];

		}
			if (i%5 == 0)	
			{
				delay_ms(15);
			}
	}

	close(fd_lcd);
	close(fd_bmp);
	munmap(share_addr, height*width*4);
	return 0;	
}

//图片以点击的屏幕为圆心,由圆心向外显示
int PicPrint_Circle(char* path, int width, int height, int x, int y)
{
	//1.打开lcd驱动文件
	int fd_lcd = open(PATH_LCD, O_RDWR);
	if (fd_lcd < 0)
	{
		perror("Don't open the file of lcd!\n");
		return 0;
	}

	//2.打开bmp图片
	int fd_bmp = open(path, O_RDWR);
	if (fd_bmp < 0)
	{
		perror("Don't open this picture!\n");
		return 0;
	}

	//3.申请虚拟共享内存
	int* share_addr = mmap(
		NULL,
		height*width*4,
		PROT_READ|PROT_WRITE,
		MAP_SHARED,
		fd_lcd,
		0
		);

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

	//打印圆
	for(i = 0; i < width; i++)
	{
		for(j = 0; j < height; j++)
		{
			//判断是否符合圆的方程
			if (4.14*(i - y)*(i - y) + (j - x)*(j - x) <= 40 * 40)
			{
				*(share_addr + i + j*width + x + y*width) = share_addr_temp[i+(height-1-j)*width];
			}
		}
		if (i%5 == 0)
		{
			delay_ms(15);
		}
	}

	// //将处理好的图片数据写入到LCD屏,进行映射.
	// for(i = 0; i < width; i++)
	// {
	// 	for(j = 0; j < height; j++)
	// 	{
	// 		*(share_addr + i + j*width + x + y*width) = share_addr_temp[i+(height-1-j)*width];
	// 	}

	// }

	close(fd_lcd);
	close(fd_bmp);
	munmap(share_addr, height*width*4);
	return 0;		
}

//用户单击切换
int ClickPic(char** path)
{
	int flag=-1;
	int x,y;
	int a,b;
	int i=0;

	//存放图片切换特效的函数
	int (*fun[4])(char* , int, int, int, int ) = {
		PicPrint_UpToBottom,
		PicPrint_BottomToUp,
		PicPrint_LeftToRight,
		PicPrint_RightToLeft
	};

	while (1)
	{
		point_ts( &x, &y);

		//原退出坐标范围
		// if(x>=30 && x<=105 
		// 	&& y>=65 && y<=120)
		// {
		// 	break;
		// }

		if(x>=0 && x<=120 
			&& y>=0 && y<=120)
		{
			break;
		}

		if (i == 4)
		{
			i = 0;
		}

		//用户点击右半边屏幕
		if (x>=400 && x<800)
		{
			flag = (flag+1)%3;
			fun[i++]( path[flag], 800, 480, 0, 0); 
		}
		//用户点击左半边屏幕
		if (x>=0 && x<400
			&& y>120 && y<480)
		{
			if (flag == -1)
			{
				flag = 3;
			}
			if (flag == 0)
			{
				flag = 3;
			}
			flag = (flag-1)%3;
			fun[i++]( path[flag], 800, 480, 0, 0); 
		}

	} /*while(1)*/
		return 0;
}

//自动播放
int AutoPrint(char** path)
{
	int flag=0;
	int x,y;
	int a,b;
	int i=0;

	//存放图片切换特效的函数
	int (*fun[4])(char* , int, int, int, int ) = {
		PicPrint_UpToBottom,
		PicPrint_BottomToUp,
		PicPrint_LeftToRight,
		PicPrint_RightToLeft
	};

	while (1)
	{
		// point_ts( &x, &y);

		//原退出坐标范围
		// if(x>=30 && x<=105 
		// 	&& y>=65 && y<=120)
		// {
		// 	break;
		// }
		if (flag == 3)
		{
			break;
		}

		fun[i++](path[flag++], 800, 480, 0, 0);
		delay_ms(1500);

	} /*while(1)*/
}

int album()
{
	char* path_pixiv[3] = {
		PATH_PIC_PIXIV_1,
		PATH_PIC_PIXIV_2,
		PATH_PIC_PIXIV_3
	};

	char* path_wall[3] = {
		PATH_PIC_WALL_1,
		PATH_PIC_WALL_2,
		PATH_PIC_WALL_3
	};
	int x=0, y=0;
	int a=0, b=0;

	// point_ts( &x, &y);
	// delay_ms(100);

	while (1)
	{
		PicPrint(PATH_ALBUM_MENU, 800, 480, 0, 0);
		Show_bmp( PATH_ALBUM_DOC_PIXIV, 160, 185);
		Show_bmp( PATH_ALBUM_DOC_WALL, 370, 185);
		point_ts( &x, &y);
		if(x>=30 && x<=104 
			&& y>=63 && y<=118)
		{
			PicPrint( PATH_HOME, 800,  480, 0, 0);
			break;
		}

		//选择pixiv文件夹
		if (x>160 && x<240 
			&& y>185 && y<285)
		{
			// ClickPic( path_pixiv);
			// Show_bmp( PATH_ALBUM_DOC_SELECT, 530, 162);
			Show_bmp( PATH_ALBUM_DOC_SELECT, 532, 164);

			point_ts( &x, &y);
			//单击切换
			if (x>550 && x<660
				&& y>185 && y<270)
			{
				//用户单击切换
				ClickPic( path_pixiv);
			}

			//自动循环
			if (x>550 && x<660
				&& y>310 && y<380)
			{
				//自动播放
				AutoPrint( path_pixiv);
			}
		}

		//选择wallhaven文件夹
		if (x>370 && x<450
			&& y>185 && y<285)
		{
			// ClickPic( path_wall);
			// Show_bmp( PATH_ALBUM_DOC_SELECT, 400, 150);
			Show_bmp( PATH_ALBUM_DOC_SELECT, 532, 162);

			point_ts( &x, &y);
			//单击切换
			if (x>550 && x<660
				&& y>199 && y<255)
			{
				//用户单击切换
				ClickPic( path_wall);
			}

			//自动循环
			if (x>550 && x<660
				&& y>310 && y<360)
			{
				//自动播放
				AutoPrint( path_wall);
			}
		}
		// delay_ms(300);

	} /*while(1)*/
		return 0;
}


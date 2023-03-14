#include "menu.h"



int main(int argc, char const *argv[])
{
	init_ts();
	init_lcd();

	int x=0, y=0;
	login();

	while (1)
	{
		point_ts( &x, &y);
		// delay_ms(100);

		if (x>=180 && x<292 
		&& y>=180 && y<260)
		{
			//实现相册功能
			album(); 
		}
		// if ()
		// {
			//2048
			// game();
		// }
		// else if ()
		// {
		// 	//点菜机
		// 	order();
		// }
		// else if ()
		// {
		// 	//设置
		// 	setting();
		// }

		//返回登录界面
		if(x>=30 && x<=104 
		&& y>=63 && y<=118)
		{
			login();
		}
	}
	close(fd_lcd);
	close(fd_ts);
	munmap(share_addr, 800*480*4);
	return 0;
}
#ifndef __album_h
#define __album_h

#include "menu.h"

#define PATH_ALBUM_MENU "./bmp/ele-album/album_background.bmp"
#define PATH_ALBUM_DOC_PIXIV "./bmp/ele-album/doc_pixiv.bmp"
#define PATH_ALBUM_DOC_WALL "./bmp/ele-album/doc_wall.bmp"
#define PATH_ALBUM_DOC_SELECT "./bmp/ele-album/album_select.bmp"

#define PATH_PIC_PIXIV_1 "./bmp/ele-album/pixiv/1.bmp"
#define PATH_PIC_PIXIV_2 "./bmp/ele-album/pixiv/2.bmp"
#define PATH_PIC_PIXIV_3 "./bmp/ele-album/pixiv/3.bmp"

#define PATH_PIC_WALL_1 "./bmp/ele-album/wallhaven/1.bmp"
#define PATH_PIC_WALL_2 "./bmp/ele-album/wallhaven/2.bmp"
#define PATH_PIC_WALL_3 "./bmp/ele-album/wallhaven/3.bmp"


//图片从上至下显示
extern int PicPrint_UpToBottom(char* path, int width, int height, int x, int y);
//图片从下至上显示
extern int PicPrint_BottomToUp(char* path, int width, int height, int x, int y);
//图片从左至右显示
extern int PicPrint_LeftToRight(char* path, int width, int height, int x, int y);
//图片从右至左显示
extern int PicPrint_RightToLeft(char* path, int width, int height, int x, int y);
//图片以点击的屏幕为圆心,由圆心向外显示
extern int PicPrint_Circle(char* path, int width, int height, int x, int y);
//用户单击切换图片
extern int ClickPic(char** path);

extern int album();


#endif
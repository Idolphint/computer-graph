#ifndef DRAW_H
#define DRAW_H
#define MAX_PIXEL 400
#define BGCOLOR 255
#define MIN_DEPTH -21470
#define DIM MAX_PIXEL
#define DM1 (DIM-1)
#include "3DS.h"


/*
typedef long LONG;

typedef unsigned char BYTE;

typedef unsigned long DWORD;

typedef unsigned short WORD;



//位图文件头文件定义

//其中不包括文件类型信息（由于结构体的内存结构决定，要是加了的话将不能正确的读取文件信息）

typedef struct {

	WORD    bfType;//文件类型，必须是0x424D,即字符“BM”

	DWORD   bfSize;//文件大小

	WORD    bfReserved1;//保留字

	WORD    bfReserved2;//保留字

	DWORD   bfOffBits;//从文件头到实际位图数据的偏移字节数

} BMPFILEHEADER_T;



struct BMPFILEHEADER_S{

	WORD    bfType; //????not it??

	DWORD   bfSize;

	WORD    bfReserved1;

	WORD    bfReserved2;

	DWORD   bfOffBits;

};

typedef struct{

	DWORD      biSize;//信息头大小

	LONG       biWidth;//图像宽度

	LONG       biHeight;//图像高度

	WORD       biPlanes;//位平面数，必须为1

	WORD       biBitCount;//每像素位数

	DWORD      biCompression;//压缩类型

	DWORD      biSizeImage;//压缩图像大小字节数

	LONG       biXPelsPerMeter;//水平分辨率

	LONG       biYPelsPerMeter;//垂直分辨率

	DWORD      biClrUsed;//位图实际用到的色彩数

	DWORD      biClrImportant;//本位图中重要的色彩数

} BMPINFOHEADER_T;//位图信息头定义
*/

// 交换整数 a 、b 的值
inline void Swap(int *a, int *b) {
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

inline void Swap(float *a, float *b) {
    float tmp = *b;
    *b = *a;
    *a = tmp;
}
inline void Swap(CVector2 *a, CVector2 *b) { //???
	CVector2 tmp = *a;
	*a = *b;
    *b = tmp;
}

inline void Swap(CVector3 *a, CVector3 *b) { //???
	CVector3 tmp = *a;
	*a = *b;
    *b = tmp;
}

class Drawer{
	public:
		float zbuffer[MAX_PIXEL][MAX_PIXEL];

		unsigned char R_color[MAX_PIXEL][MAX_PIXEL];
		unsigned char G_color[MAX_PIXEL][MAX_PIXEL];
		unsigned char B_color[MAX_PIXEL][MAX_PIXEL];
		Drawer(float max_l);
		~Drawer();
		void init();
		//void draw_line(CVector2 p1, CVector2 p2,unsigned char color[3], CVector3 norm, CVector3 offset); // when use it, point can be convert to suitable size
		void drawTriangle(CVector3 p1, CVector3 p2, CVector3 p3,unsigned char color[3], float offset[9], int dx, int dy); // convert also
		void show(const char filename[]);
	private:
		void draw_line(int minX, int maxX, int y,unsigned char color[3], CVector3 norm, CVector3 point);
		float getDep(CVector3 norm, int x, int y, CVector3 point);
		void putpixel(int cx, int cy,unsigned char color[3], float dep);
		void drawFlatBottomTriangle(CVector2 top, CVector2 left,
                    CVector2 right,unsigned char color[3], CVector3 norm, CVector3 mid3);
		void drawFlatTopTriangle(CVector2 bottom, CVector2 left,
					 CVector2 right,unsigned char color[3], CVector3 norm, CVector3 mid3);
};

#endif

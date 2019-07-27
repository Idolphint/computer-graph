#include "draw.h"
#include "3DS.h"
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <cstdlib>
#include <WinGDI.h>

#include <pshpack2.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//typedef long BOOL;
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
	WORD    bfType;
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

//TODO: caul norm and change useage
//TODO: drawtriangle
float max_length;
int center;

Drawer::Drawer(float max_l) {
	int i;
	int j;
    max_length = max_l;
    center = MAX_PIXEL / 2;
	for (i = 0; i<MAX_PIXEL; i++) {
		for(j=0; j<MAX_PIXEL; j++) {
			zbuffer[i][j] = MIN_DEPTH;
			R_color[i][j] = BGCOLOR;
			G_color[i][j] = BGCOLOR;
			B_color[i][j] = BGCOLOR;

		}
	}
}

Drawer::~Drawer() {

}
// Bresenham's line algorithm
/*
void Drawer::draw_line(CVector2 p1, CVector2 p2, unsigned char color[3], CVector3 norm, CVector3 offset) {



    p1.x = p1.x / max_length * MAX_PIXEL / 2 + center;
    p1.y = p1.y / max_length * MAX_PIXEL / 2 + center;
    p2.x = p2.x / max_length * MAX_PIXEL / 2 + center;
    p2.y = p2.y / max_length * MAX_PIXEL / 2 + center;

    // 参数 c 为颜色值
    int dx = abs(p2.x - p1.x),
        dy = abs(p2.y - p1.y),
        yy = 0;

    if (dx < dy) {
        yy = 1;
        Swap(&(p1.x), &(p1.y));
        Swap(&(p2.x), &(p2.y));
        Swap(&dx, &dy);
    }

    int ix = (p2.x - p1.x) > 0 ? 1 : -1,
         iy = (p2.y - p1.y) > 0 ? 1 : -1,
         cx = p1.x,
         cy = p1.y,
         n2dy = dy * 2,
         n2dydx = (dy - dx) * 2,
         d = dy * 2 - dx;

    if (yy) { // 如果直线与 x 轴的夹角大于 45 度
        while (cx != p2.x) {
            if (d < 0) {
                d += n2dy;
            } else {
                cy += iy;
                d += n2dydx;
            }
            putpixel(cy, cx, color, norm);
            cx += ix;
        }
    } else { // 如果直线与 x 轴的夹角小于 45 度
        while (cx != p2.x) {
            if (d < 0) {
                d += n2dy;
            } else {
                cy += iy;
                d += n2dydx;
            }
            putpixel(cx, cy, color, norm);
            cx += ix;
        }
    }
}
*/
void Drawer::draw_line(int minX, int maxX, int y,unsigned char color[3], CVector3 norm, CVector3 point)
{
    //if (minX <= 0 || maxX >= MAX_PIXEL) cout<<"line out of range,y is "<<y<<endl;
    if (y < 0 || y >= MAX_PIXEL) return;
    if (maxX >= MAX_PIXEL) maxX = MAX_PIXEL - 1;

    for (int x = minX < 0 ? 0 : minX; x <= maxX; ++x)
    {
        float dep = getDep(norm, x,y, point);
        if (dep > zbuffer[x][y]) {
        	putpixel(x, y, color,dep);
		}
    }
}

float Drawer::getDep(CVector3 norm, int x, int y, CVector3 point) {
	float z = -1*(norm.x*(x - point.x)+norm.y*(y - point.y));
	z = z/norm.z + point.z;
	//cout<<z<<endl;
	return z;
}

void Drawer::putpixel(int cx, int cy,unsigned char color[3], float dep) { // img should be Z-buffer???
	float ori = zbuffer[cx][cy];
	if (dep > ori) {
		zbuffer[cx][cy] = dep;
		R_color[cx][cy] = color[0];
		G_color[cx][cy] = color[1];
		B_color[cx][cy] = color[2];
	}
}


void Drawer::drawTriangle(CVector3 p1, CVector3 p2, CVector3 p3,unsigned char color[3], float offset[9], int dx, int dy)
{

    p1 = p1.rotate_(offset);
    p2 = p2.rotate_(offset);
    p3 = p3.rotate_(offset);

    p1.x = p1.x / max_length * MAX_PIXEL / 2.5 + center + dx;
    p1.y = p1.y / max_length * MAX_PIXEL /2.5  + center + dy;
    p1.z = p1.z / max_length * MAX_PIXEL/2.5 + MAX_PIXEL;
    p2.x = p2.x / max_length * MAX_PIXEL /2.5 + center+dx;
    p2.y = p2.y / max_length * MAX_PIXEL /2.5+ center+dy;
    p2.z = p2.z / max_length * MAX_PIXEL /2.5+ MAX_PIXEL;
    p3.x = p3.x / max_length * MAX_PIXEL /2.5+ center+dx;
    p3.y = p3.y / max_length * MAX_PIXEL /2.5+ center+dy;
    p3.z = p3.z / max_length * MAX_PIXEL /2.5+ MAX_PIXEL;

    //cout<<"in this triangle : \n";
    CVector2 p[3];
	// sort by y
    if (p2.y > p1.y) Swap(&p1, &p2);
    if (p3.y > p1.y) Swap(&p1, &p3);
    if (p3.y > p2.y) Swap(&p2, &p3);
    /*p1.print();
    p2.print();
    p3.print();*/
    p[0].x = p1.x;
    p[1].x = p2.x;
    p[2].x = p3.x;
    p[0].y = p1.y;
    p[1].y = p2.y;
    p[2].y = p3.y;
    float px = float(p2.y - p1.y) / (p3.y - p1.y) * (p3.x - p1.x) + p1.x;
    float pz = float(p2.y - p1.y) / (p3.y - p1.y) * (p3.z - p1.z) + p1.z;
    CVector2 mid(px, p[1].y); //切割产生的点
    CVector3 mid3(px,p[1].y, pz);
    //cout<<"mid: ";
    //mid3.print();
	CVector3 norm = CLoad3DS::ComputeNormals(p1,p2,p3);
	// norm.print();
    drawFlatBottomTriangle(p[0], p[1], mid, color,norm, mid3);
    drawFlatTopTriangle(p[2], p[1], mid, color,norm, mid3);
}

void Drawer::drawFlatTopTriangle(CVector2 bottom, CVector2 left,
				CVector2 right,unsigned char color[3], CVector3 norm, CVector3 point) //left may not be left
{
    if (round(bottom.y) == round(left.y) || round(bottom.y) == round(right.y) ||
            abs(left.y - bottom.y)<1 ) {
        //cout<<"\n\ntop triangle:"<<endl;
        //cout<<"y: "<<left.y<<"\tactul_y: "<<round(left.y);
        //draw_line(((left.x > right.x)? right.x:left.x),
          //        (left.x>right.x)?left.x:right.x, round(left.x), color, norm, point);
        return;
    }
    int y;
    for (y = round(bottom.y); y <= round(left.y); y++) {
        float x1 = (bottom.x - left.x)/(bottom.y-left.y)*(y-left.y)+left.x;
        float x2 = (bottom.x - right.x)/(bottom.y-right.y)*(y-right.y)+right.x;

        int max_ = (x1>x2)?(int)x1:(int)x2;
        int min_ = (x1<x2)?(int)x1:(int)x2;

        draw_line(min_, max_, y,color, norm, point);
    }
    /*
    float dy = bottom.y - left.y;
    float min_ = (left.x > right.x)? right.x:left.x;
    float max_ = (left.x > right.x)? left.x : right.x;
    float stepX1 = (min_ - bottom.x) / dy; // stepX1 < X2
    float stepX2 = (max_ - bottom.x) / dy;
    //cout<<"max_ : "<<max_<<"min_: "<<min_<<"stepX1: "<<stepX1<<"stepx2"<<stepX2<<endl;
    float leftX = bottom.x;
    float rightX = bottom.x;

    //如果stepX1比较大就可能出现多画一条线的情况，应该加以识别并且避免
    //cout<<"stepX1: "<<stepX1<<", stepX2: "<<stepX2<<endl;
    for (int y = bottom.y; y <= left.y; ++y)
    {
        //leftX = leftX < min_? min_ : leftX;
        //rightX = rightX > max_? max_: rightX;
        if (leftX > rightX) {
            cout<<"error"<<endl;
        }
        if (leftX<rightX)
            draw_line((int)(leftX < min_? min_: leftX),
                      (int)(rightX > max_? max_: rightX), y, color, norm, point);
        leftX -= stepX1;
        rightX -= stepX2;
    }
    */
}

void Drawer::drawFlatBottomTriangle(CVector2 top, CVector2 left,
				 CVector2 right,unsigned char color[3], CVector3 norm, CVector3 point)
{
    if (round(top.y) == round(left.y) || round(top.y) == round(right.y) ||
            abs(top.y - left.y) < 1) {
       // cout<<"\n\nbottom triangle:"<<endl;
        //cout<<"y: "<<left.y<<"\tactul_y: "<<round(left.y);

        //draw_line(((left.x > right.x)? right.x:left.x),
          //        (left.x>right.x)?left.x:right.x, round(left.x), color, norm, point);
        return;
    }

    int y;
    for (y = round(top.y); y >= round(left.y); y--) {
        float x1 = (top.x - left.x)/(top.y-left.y)*(y-left.y)+left.x;
        float x2 = (top.x - right.x)/(top.y-right.y)*(y-right.y)+right.x;
        int max_ = (x1>x2)?(int)x1:(int)x2;
        int min_ = (x1<x2)?(int)x1:(int)x2;

        /* float max_tri = top.x;
        max_tri = (max_tri < left.x)? left.x: max_tri;
        max_tri = (max_tri < right.x)?right.x:max_tri;
        if (max_ > max_tri + 4) {
            cout<<"top.x: "<<top.x<<"\ty: "<<top.y<<endl;
            cout<<"left.x: "<<left.x<<"\ty: "<<left.y<<endl;
            cout<<"right.x: "<<right.x<<"\ty: "<<right.y<<endl;
            cout<<"max: "<<max_<<"\tmin: "<<min_<<"\ty:"<<y<<endl;
            cout<<"\n\n";
        }*/
        /*if ((max_ > top.x + 50) || (min_ < left.x - 50)) {
            cout<<"max_x: "<<max_<<" min_x: "<<min_<<" but should in <"<<left.x<<", "<<top.x<<">\n";
        }*/
        draw_line(min_ , max_, y,color, norm, point);
    }
    /*
    float dy = top.y - left.y;
    float min_ = (left.x > right.x)? right.x:left.x;
    float max_ = (left.x > right.x)? left.x : right.x;
    float stepX1 = (top.x - min_) / dy;
    float stepX2 = (top.x - max_) / dy;
    float leftX = top.x;
    float rightX = top.x;

    for (int y = top.y; y >= left.y; --y)
    {
        if (rightX < leftX){
            cout<<"something bad happen"<<endl;
        }
        draw_line((int)(leftX < min_? min_: leftX),
                  (int)(rightX > max_? max_: rightX), y, color, norm, point);
        leftX -= stepX1;
        rightX -= stepX2;
    }
    */
}

/*
void Init_bmp_header(FILE* fp) {
    int size_ = DIM*DIM*3;
    BMPFILEHEADER_T bfh;
    bfh.bfType = 0X4d42;  //bm
	bfh.bfSize = size_  // data size
		+ sizeof( BMPFILEHEADER_T ) // first section size
		+ sizeof( BMPINFOHEADER_T ) // second section size
		;
	bfh.bfReserved1 = 0; // reserved
	bfh.bfReserved2 = 0; // reserved
	bfh.bfOffBits = bfh.bfSize - size_;

	// 位图第二部分，数据信息
	BMPINFOHEADER_T bih;
	bih.biSize = sizeof(BMPINFOHEADER_T);
	bih.biWidth = DIM;
	bih.biHeight = DIM;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = 0;
	bih.biSizeImage = size_;
	bih.biXPelsPerMeter = 0x60;
	bih.biYPelsPerMeter = 0x60;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	fwrite( &bfh, 1, sizeof(BMPFILEHEADER_T), fp );
	fwrite( &bih, 1, sizeof(BMPINFOHEADER_T), fp );

	/*for(int i=0;i<DIM;i++)
        for(int j=0;j<DIM;j++) {
            char color[3] = {R_color[i][j], G_color[i][j], B_color[i][j]};
            fwrite(color, 3, 1, fp);
		}
    fclose(fp);
}*/
void Drawer::show(const char filename[]) {
     // 每个像素点3个字节
	// 位图第一部分，文件信息

	int size_ = DIM*DIM*3;
    BMPFILEHEADER_T bfh;
    bfh.bfType = 0X4d42;  //bm
	bfh.bfSize = size_  // data size
		+ sizeof( BMPFILEHEADER_T ) // first section size
		+ sizeof( BMPINFOHEADER_T ) // second section size
		;
	bfh.bfReserved1 = 0; // reserved
	bfh.bfReserved2 = 0; // reserved
	bfh.bfOffBits = bfh.bfSize - size_;

	// 位图第二部分，数据信息
	BMPINFOHEADER_T bih;
	bih.biSize = sizeof(BMPINFOHEADER_T);
	bih.biWidth = DIM;
	bih.biHeight = DIM;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = 0;
	bih.biSizeImage = size_;
	bih.biXPelsPerMeter = 0x60;
	bih.biYPelsPerMeter = 0x60;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	FILE * fp = fopen( filename,"wb" );
	if( !fp ) return;
	fwrite( &bfh, 1, sizeof(BMPFILEHEADER_T), fp );
	fwrite( &bih, 1, sizeof(BMPINFOHEADER_T), fp );


	unsigned char color[3];
	printf("ok\n");
	for(int i=0;i<DIM;i++)
        for(int j=0;j<DIM;j++) {
            color[0] = R_color[j][i];
            color[1] = G_color[j][i];
            color[2] = B_color[j][i];
            fwrite(&color, 1, 3, fp);
		}


    fclose(fp);
}




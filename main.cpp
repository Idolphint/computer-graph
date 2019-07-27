#include <iostream>
#include<ctime>
#include<fstream>
#include "3DS.h"
#include "draw.h"
#include <cmath>
#include <string>
#include<windows.h>
#include <string.h>

#include <pshpack2.h>

#include "stdio.h"

#include "stdlib.h"
#define PI 3.14159
using namespace std;

//int g_Texture[10][MAX_TEXTURES];
t3DModel g_3DModel[2];


void matrix_multi(float* a, float* b, float* res) {

        res[0] = a[0]*b[0]+a[1]*b[3]+a[2]*b[6];
        res[1] = a[0]*b[1]+a[1]*b[4]+a[2]*b[7];
        res[2] = a[0]*b[2]+a[1]*b[5]+a[2]*b[8];
        res[3] = a[3]*b[0]+a[4]*b[3]+a[5]*b[6];
        res[4] = a[3]*b[1]+a[4]*b[4]+a[5]*b[7];
        res[5] = a[3]*b[2]+a[4]*b[5]+a[5]*b[8];
        res[6] = a[6]*b[0]+a[7]*b[3]+a[8]*b[6];
        res[7] = a[6]*b[1]+a[7]*b[4]+a[8]*b[7];
        res[8] = a[6]*b[2]+a[7]*b[5]+a[8]*b[8];

}

void make_rotate_matrix(float theta1, float theta2, float theta3, float* res) {
        theta1 = theta1 * PI /180;
        theta2 = theta2 * PI /180;
        theta3 = theta3 * PI /180;
        float matrix1[9] = {1,0,0,0,cos(theta1), -sin(theta1), 0, sin(theta1),
            cos(theta1)};
        float matrix2[9] = {cos(theta2), 0, sin(theta2), 0,1,0,
            -sin(theta2), 0, cos(theta2)};
        float matrix3[9] = {cos(theta3), -sin(theta3), 0, sin(theta3), cos(theta3),
            0,0,0,1};
        float buffer[9];
        matrix_multi(res, matrix1, buffer);
        matrix_multi(buffer, matrix2, res);
        matrix_multi(res, matrix3, buffer);

        int i;
        for (i = 0; i< 9; i++) {
            res[i] = buffer[i];
        }

}


int main() {

	char* filename = "../cloudmesh0-vp.3ds";
    char * buffer;

    long Fsize;
    ifstream file;
    file.open(filename, ios::in|ios::binary|ios::ate); // 打开就在文件结尾
    if (!file) {
        printf("open error\n");
    }
    Fsize = file.tellg();
    printf("file size is:%ld\n",Fsize);
    file.seekg(0, ios::beg);
    buffer = new char [Fsize];
    file.read(buffer, Fsize);
    /*-----------------------------------*/
    file.close();
    CLoad3DS loader;
    loader.Init(filename, 0);
    t3DModel myModel = g_3DModel[0];
    int objNum = myModel.numOfObjects;
    printf("obj num is:%d\n",objNum);

    int max_pixel = loader.get_max_length(); // record max length
    cout<<"\t\t******max_pixel is :"<<max_pixel<<endl;

    float theta1, theta2, theta3;
    cout<<"######please enter the rotate angle you want(-180 - 180) :y, z, x"<<endl;
    cin>>theta1>>theta2>>theta3;

    float enlarge;
    cout<<"######please enter the enlargement factor"<<endl;
    cin>>enlarge;

    int dx,dy;
    cout<<"######please enter dx, dy"<<endl;
    cin>>dx>>dy;

    float offset[9] = {enlarge,0,0,0,enlarge,0,0,0,enlarge};

    make_rotate_matrix(theta1, theta2, theta3, offset);
    int i;
    Drawer mydraw(max_pixel);
    unsigned char basecolor = 20;
    //unsigned char color[3];
    for (i = 0; i< objNum; i++) {
    	t3DObject oneObj = myModel.pObject.at(i);
    	int materialId = oneObj.materialID;
    	printf("mat id:%d\n",materialId);
    	if (!(materialId < 0 || materialId >= myModel.numOfMaterials)) {
    	    tMatInfo matInfo = myModel.pMaterials.at(materialId);
    	    if (!oneObj.bHasTexture) {
    	        /*color[0] = matInfo.color[0];
                color[1] = matInfo.color[1];
                color[2] = matInfo.color[2];*/
    	        printf("red: %d, green: %d, black: %d\n",matInfo.color[0], matInfo.color[1], matInfo.color[2]);
			} else {
                printf("it has texture\n");
                /*color[0] = color[1] = color[2] = basecolor;
                basecolor+=20;*/
            }
		}else {
            printf("it is not have mat\n");
            /*color[0] = color[1] = color[2] = basecolor;
            basecolor+=20;*/
		}
    	int faceNum = oneObj.numOfFaces;
    	printf("in obj[%d], face num is:%d\n",i,faceNum);
    	int j;

    	for(j = 0; j< faceNum;j++) {
    		tFace oneFace = oneObj.pFaces[j];
    		CVector3 point[3];
    		point[0] = oneObj.pVerts[oneFace.vertIndex[0]];
    		point[1] = oneObj.pVerts[oneFace.vertIndex[1]];
    		point[2] = oneObj.pVerts[oneFace.vertIndex[2]];

    		unsigned char color[3] = {basecolor, basecolor, basecolor};
            basecolor += 10;
			mydraw.drawTriangle(point[0], point[1], point[2], color, offset, dx, dy);
			//cout<<"draw face:"<<j<<"\n\n\n"<<endl;
    		//printf("\n");
		}
	}
	/*---------------------------------*/

    /*myModel*/

    const char* name = "res.bmp";
    //const char* testname = "test.bmp";
	mydraw.show(name);

    cout <<"the complete file is in a buffer";
    delete[] buffer;
    cout<<"end\n";
    return 0;

}


//draw lines

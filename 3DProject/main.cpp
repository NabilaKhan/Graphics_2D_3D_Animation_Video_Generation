#include <stdlib.h>
#include<Windows.h>
#ifdef __APPLE__
#else
#include <GL/glut.h>
#endif
#include<math.h>

#include<time.h>

#include<stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/GLAUX.h>
#include <math.h>
#include <string.h>


#define PI 3.14152653597689786
#define RandomFactor 2.0
#define ESCAPE 27
#define TEXTID      3

unsigned int i;
int flag=0,f=2,fl=0,fll=0;

GLfloat X[3];
GLint ListNum;

GLfloat OuterRadius = 2.4;
GLfloat OuterRadius1 = 3;
GLfloat InnerRadius = 2.0;
GLint NumOfVerticesStone = 6;
GLfloat StoneHeight = 0.5;
GLfloat WaterHeight = 0.45;
clock_t start;
double elapse;
int el,x=5;
float yy1=0.0,yy2=0.0,yy3=0.0,yy4=0.0,yy5=0.0;
double a=0.0,b=0.0,c=24.5;
double d=0.0;
GLfloat	l_t=0,r=0,rr=0;
GLuint texture[50];

struct SVertex
{
	GLfloat x,y,z;
};


class CDrop
{
private:
	GLfloat time;
	SVertex ConstantSpeed;
	GLfloat AccFactor;
public:
	void SetConstantSpeed (SVertex NewSpeed);
	void SetAccFactor(GLfloat NewAccFactor);
	void SetTime(GLfloat NewTime);
	void GetNewPosition(SVertex * PositionVertex);
};

void CDrop::SetConstantSpeed(SVertex NewSpeed)
{
	ConstantSpeed = NewSpeed;
}

void CDrop::SetAccFactor (GLfloat NewAccFactor)
{
	AccFactor = NewAccFactor;
}

void CDrop::SetTime(GLfloat NewTime)
{
	time = NewTime;
}

void CDrop::GetNewPosition(SVertex * PositionVertex)
{
	SVertex Position;
	time += 0.15;
	Position.x = ConstantSpeed.x * time;
	Position.y = ConstantSpeed.y * time - AccFactor * time *time;
	Position.z = ConstantSpeed.z * time;
	PositionVertex->x = Position.x;
	PositionVertex->y = Position.y + WaterHeight;
	PositionVertex->z = Position.z;
	if (Position.y < 0.0)
	{
		time = time - int(time);
		if (time > 0.0) time -= 1.0;
	}

}

CDrop * FountainDrops;
SVertex * FountainVertices;
GLint Steps = 4;
GLint RaysPerStep =8;
GLint DropsPerRay = 80;
GLfloat DropsComplete = Steps * RaysPerStep * DropsPerRay;
GLfloat AngleOfDeepestStep = 80;
GLfloat AccFactor = 0.011;



void LoadGLTextures()
{
	AUX_RGBImageRec* TextureImage;

	glGenTextures(50,texture);

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\sky2.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\staircase13.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\b6.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\tile3.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\frame.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\white.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\chair.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\grass2.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[7]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\back_wall.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[8]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\scene.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[9]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\mist.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[10]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\2014.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[11]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\2015.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[12]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\2016.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[13]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\2017.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[14]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l1\\1.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[15]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l1\\2.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[16]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l1\\3.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[17]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l1\\4.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[18]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l1\\5.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[19]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l1\\6.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[20]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l1\\7.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[21]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l2\\1.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[22]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l2\\2.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[23]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l2\\3.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[24]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l2\\4.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[25]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l2\\5.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[26]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l2\\6.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[27]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l2\\7.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[28]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l3\\1.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[29]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l3\\2.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[30]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l3\\3.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[31]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l3\\4.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[32]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l3\\5.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[33]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l3\\6.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[34]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l3\\7.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[35]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l4\\1.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[36]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l4\\2.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[37]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l4\\3.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[38]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l4\\4.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[39]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l4\\5.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[40]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l4\\6.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[41]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

    if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l4\\7.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[42]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l4\\end.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[43]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\l4\\window.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[44]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\chair.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[45]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\table.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[46]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\road.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[47]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage = auxDIBImageLoad("F:\\Nabila\\level 4 term II\\Graphics413\\lab\\3DProject\\bin\\Debug\\door.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, texture[48]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

}



void quad()
{
    // left wall

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);

        glTexCoord2f(0.0f,1.0f); glVertex3f(-2.0f,1.0f,8.0f);					// Top front Of The Quad (left)
        glTexCoord2f(1.0f,1.0f); glVertex3f(-2.0f,1.0f,1.0f);					// Top back Of The Quad (left)
        glTexCoord2f(1.0f,0.0f); glVertex3f(-2.0f,-1.0f,1.0f);					// Bottom back Of The Quad (left)
        glTexCoord2f(0.0f,0.0f); glVertex3f(-2.0f,-1.0f,8.0f);

    glEnd();

    // right wall
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);

        glTexCoord2f(0.0f,1.0f); glVertex3f(2.0f,1.0f,8.0f);					    // Top front Of The Quad (right)
        glTexCoord2f(1.0f,1.0f); glVertex3f(2.0f,1.0f,1.0f);					    // Top back Of The Quad (right)
        glTexCoord2f(1.0f,0.0f); glVertex3f(2.0f,-1.0f,1.0f);					// Bottom back Of The Quad (right)
        glTexCoord2f(0.0f,0.0f); glVertex3f(2.0f,-1.0f,8.0f);					// Bottom front Of The Quad (right)

    glEnd();

    //floor;

    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_QUADS);			    // Left front Of The Quad (top)

        glTexCoord2f(0.0f,1.0f); glVertex3f(2.0f,-1.0f,8.0f);					// Right front Of The Quad (bottom)
        glTexCoord2f(1.0f,1.0f); glVertex3f(2.0f,-1.0f,1.0f);					// Right back Of The Quad (bottom)
        glTexCoord2f(1.0f,0.0f); glVertex3f(-2.0f,-1.0f,1.0f);				    // Left back Of The Quad (bottom)
        glTexCoord2f(0.0f,0.0f); glVertex3f(-2.0f,-1.0f,8.0f);				    // Left front Of The Quad (bottom)

    glEnd();

    //back
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);

        //back
        glTexCoord2f(0.0f,1.0f); glVertex3f(2.0f,1.0f,1.0f);					    // Top Right Of The Quad (Back)
        glTexCoord2f(1.0f,1.0f); glVertex3f(-2.0f,1.0f,1.0f);					// Top Left Of The Quad (Back)
        glTexCoord2f(1.0f,0.0f); glVertex3f(-2.0f,-1.0f,1.0f);					// Bottom Left Of The Quad (Back)
        glTexCoord2f(0.0f,0.0f); glVertex3f(2.0f,-1.0f,1.0f);
    glEnd();

    //back2
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glBegin(GL_QUADS);

        //back
        glTexCoord2f(0.0f,1.0f); glVertex3f(2.0f,1.0f,1.01f);					    // Top Right Of The Quad (Back)
        glTexCoord2f(1.0f,1.0f); glVertex3f(-2.0f,1.0f,1.01);					// Top Left Of The Quad (Back)
        glTexCoord2f(1.0f,0.0f); glVertex3f(-2.0f,-1.0f,1.01f);					// Bottom Left Of The Quad (Back)
        glTexCoord2f(0.0f,0.0f); glVertex3f(2.0f,-1.0f,1.01f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);

        //front
        glTexCoord2f(1.0f,1.0f); glVertex3f(2.0f,1.0f,8.0f);					    // Top Right Of The Quad (Front)
        glTexCoord2f(0.0f,1.0f); glVertex3f(-2.0f,1.0f,8.0f);					// Top Left Of The Quad (Front)
        glTexCoord2f(0.0f,0.0f); glVertex3f(-2.0f,-1.0f,8.0f);					// Bottom Left Of The Quad (Front)
        glTexCoord2f(1.0f,0.0f); glVertex3f(2.0f,-1.0f,8.0f);

    glEnd();

    glColor3f(1.0f,1.0f,1.0f);
}



void ceiling(){

     glBegin(GL_QUADS);

            glColor3f(1.0f,1.0f,1.0f);
            glVertex3f(2.0f,1.0f,8.0f);					    // Right front Of The Quad (top)
            glVertex3f(2.0f,1.0f,1.0f);					    // Right back Of The Quad (top)
            glVertex3f(-2.0f,1.0f,1.0f);				    // Left back Of The Quad (top)
            glVertex3f(-2.0f,1.0f,8.0f);

    glEnd();

    glColor3f(1.0f,1.0f,1.0f);
}

void tv(){
     glBindTexture(GL_TEXTURE_2D, texture[4]);
     glBegin(GL_QUADS);

        glTexCoord2f(0.95f,0.93f); glVertex3f(1.8f,0.8f,1.1f);					    // Top Right Of The Quad (Back)
        glTexCoord2f(0.05f,0.93); glVertex3f(-1.8f,0.8f,1.1);					// Top Left Of The Quad (Back)
        glTexCoord2f(0.05f,0.07f); glVertex3f(-1.8f,-0.8f,1.1f);					// Bottom Left Of The Quad (Back)
        glTexCoord2f(0.95f,0.07f); glVertex3f(1.8f,-0.8f,1.1f);				// Bottom Right Of The Quad (Back)
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[x]);
    glBegin(GL_QUADS);

        glTexCoord2f(0.95f,0.93f); glVertex3f(1.7f,0.7f,1.12f);					    // Top Right Of The Quad (Back)
        glTexCoord2f(0.05f,0.93); glVertex3f(-1.7f,0.7f,1.12);					// Top Left Of The Quad (Back)
        glTexCoord2f(0.05f,0.07f); glVertex3f(-1.7f,-0.7f,1.12f);					// Bottom Left Of The Quad (Back)
        glTexCoord2f(0.95f,0.07f); glVertex3f(1.7f,-0.7f,1.12f);				// Bottom Right Of The Quad (Back)
    glEnd();
    glColor3f(1.0f,1.0f,1.0f);
}



void sky(){
    glBindTexture(GL_TEXTURE_2D, texture[0]);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0f,1.0f); glVertex3f(25.0f,20.0f,-3.0f);					    // Top Right Of The Quad (Back)
        glTexCoord2f(0.0f,1.0f); glVertex3f(-25.0f,20.0f,-3.0f);					// Top Left Of The Quad (Back)
        glTexCoord2f(0.0f,0.0f); glVertex3f(-25.0f,-1.0f,-3.0f);					// Bottom Left Of The Quad (Back)
        glTexCoord2f(1.0f,0.0f); glVertex3f(25.0f,-1.0f,-3.0f);					// Bottom Right Of The Quad (Back)
    glEnd();
    glColor3f(1.0f,1.0f,1.0f);
}
// Creating reservoir boundary

void door(){

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);

        glTexCoord2f(0.0f,1.0f); glVertex3f(1.95f,0.5f,7.0f);					    // Top front Of The Quad (right)
        glTexCoord2f(1.0f,1.0f); glVertex3f(1.95f,0.5f,4.5f);					    // Top back Of The Quad (right)
        glTexCoord2f(1.0f,0.0f); glVertex3f(1.95f,-0.5f,4.5f);					// Bottom back Of The Quad (right)
        glTexCoord2f(0.0f,0.0f); glVertex3f(1.95f,-0.5f,7.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[44]);
    glBegin(GL_QUADS);

        glTexCoord2f(0.0f,1.0f); glVertex3f(1.945f,0.45f,6.95f);					    // Top front Of The Quad (right)
        glTexCoord2f(1.0f,1.0f); glVertex3f(1.945f,0.45f,4.65f);					    // Top back Of The Quad (right)
        glTexCoord2f(1.0f,0.0f); glVertex3f(1.945f,-0.45f,4.65f);					// Bottom back Of The Quad (right)
        glTexCoord2f(0.0f,0.0f); glVertex3f(1.945f,-0.45f,6.95f);
    glEnd();
    glColor3f(1.0f,1.0f,1.0f);
}

void door2(){

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);

        glTexCoord2f(0.0f,1.0f); glVertex3f(1.95f,0.5f,4.5f);					    // Top front Of The Quad (right)
        glTexCoord2f(1.0f,1.0f); glVertex3f(1.95f,0.5f,2.0f);					    // Top back Of The Quad (right)
        glTexCoord2f(1.0f,0.0f); glVertex3f(1.95f,-0.5f,2.0f);					// Bottom back Of The Quad (right)
        glTexCoord2f(0.0f,0.0f); glVertex3f(1.95f,-0.5f,4.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[44]);
    glBegin(GL_QUADS);

        glTexCoord2f(0.0f,1.0f); glVertex3f(1.945f,0.45f,4.45f);					    // Top front Of The Quad (right)
        glTexCoord2f(1.0f,1.0f); glVertex3f(1.945f,0.45f,2.05f);					    // Top back Of The Quad (right)
        glTexCoord2f(1.0f,0.0f); glVertex3f(1.945f,-0.45f,2.05f);					// Bottom back Of The Quad (right)
        glTexCoord2f(0.0f,0.0f); glVertex3f(1.945f,-0.45f,4.45f);
    glEnd();
    glColor3f(1.0f,1.0f,1.0f);
}

void chair(){
         glBindTexture(GL_TEXTURE_2D, texture[45]);
         glBegin(GL_QUADS);

            glTexCoord2f(1.0f,1.0f); glVertex3f(0.1f,0.2f,4.25f);					    // Top Right Of The Quad (Back)
            glTexCoord2f(0.0f,1.0f); glVertex3f(-0.1f,0.2f,4.25f);					// Top Left Of The Quad (Back)
            glTexCoord2f(0.0f,0.0f); glVertex3f(-0.1f,0.0f,4.25f);					// Bottom Left Of The Quad (Back)
            glTexCoord2f(1.0f,0.0f); glVertex3f(0.1f,0.0f,4.25f);					// Bottom Right Of The Quad (Back)

         glEnd();
         //glColor3f(1.0f,1.0f,1.0f);

         glBegin(GL_QUADS);

         //glColor3f(0.55f,0.27f,0.07f);
         glTexCoord2f(0.0f,1.0f); glVertex3f(0.1f,0.0f,4.0f);					    // Top Right Of The Quad (Back)
         glTexCoord2f(1.0f,1.0f); glVertex3f(-0.1f,0.0f,4.0f);					// Top Left Of The Quad (Back)
         glTexCoord2f(1.0f,0.0f); glVertex3f(-0.1f,0.0f,4.25f);					// Bottom Left Of The Quad (Back)
         glTexCoord2f(0.0f,0.0f); glVertex3f(0.1f,0.0f,4.25f);					// Bottom Right Of The Quad (Back)

         glEnd();

         glBegin(GL_QUADS);
         glColor3f(0.55f,0.27f,0.07f);

         glTexCoord2f(0.0f,1.0f); glVertex3f(-0.08f,0.0f,4.0f);					    // Top Right Of The Quad (Back)
         glTexCoord2f(1.0f,1.0f); glVertex3f(-0.1f,0.0f,4.0f);					// Top Left Of The Quad (Back)
         glTexCoord2f(1.0f,0.0f); glVertex3f(-0.1f,-0.2f,4.0f);					// Bottom Left Of The Quad (Back)
         glTexCoord2f(0.0f,0.0f); glVertex3f(-0.08f,-0.2f,4.0f);					// Bottom Right Of The Quad (Back)

         glEnd();
         //leg2

         glBegin(GL_QUADS);
        // glColor3f(0.55f,0.27f,0.07f);

         glTexCoord2f(0.0f,1.0f); glVertex3f(-0.08f,0.0f,4.25f);					    // Top Right Of The Quad (Back)
         glTexCoord2f(1.0f,1.0f); glVertex3f(-0.1f,0.0f,4.25f);					// Top Left Of The Quad (Back)
         glTexCoord2f(1.0f,0.0f); glVertex3f(-0.1f,-0.2f,4.25f);					// Bottom Left Of The Quad (Back)
         glTexCoord2f(0.0f,0.0f); glVertex3f(-0.08f,-0.2f,4.25f);					// Bottom Right Of The Quad (Back)

         glEnd();

         glBegin(GL_QUADS);

         //glColor3f(0.55f,0.27f,0.07f);
         glTexCoord2f(0.0f,1.0f); glVertex3f(0.08f,0.0f,4.0f);					    // Top Right Of The Quad (Back)
         glTexCoord2f(1.0f,1.0f); glVertex3f(0.1f,0.0f,4.0f);					// Top Left Of The Quad (Back)
         glTexCoord2f(1.0f,0.0f); glVertex3f(0.1f,-0.2f,4.0f);					// Bottom Left Of The Quad (Back)
         glTexCoord2f(0.0f,0.0f); glVertex3f(0.08f,-0.2f,4.0f);					// Bottom Right Of The Quad (Back)

         glEnd();
         //glColor3f(1.0f,1.0f,1.0f);

         //leg2
         glBegin(GL_QUADS);

         //glColor3f(0.55f,0.27f,0.07f);
         glTexCoord2f(0.0f,1.0f); glVertex3f(0.08f,0.0f,4.25f);					    // Top Right Of The Quad (Back)
         glTexCoord2f(1.0f,1.0f); glVertex3f(0.1f,0.0f,4.25f);					// Top Left Of The Quad (Back)
         glTexCoord2f(1.0f,0.0f); glVertex3f(0.1f,-0.2f,4.25f);					// Bottom Left Of The Quad (Back)
         glTexCoord2f(0.0f,0.0f); glVertex3f(0.08f,-0.2f,4.25f);						// Bottom Right Of The Quad (Back)

         glEnd();
         glColor3f(1.0f,1.0f,1.0f);
}

void table(){
        glBindTexture(GL_TEXTURE_2D, texture[46]);

        glBegin(GL_QUADS);

         glColor3f(0.55f,0.27f,0.07f);
         glTexCoord2f(0.0f,1.0f); glVertex3f(0.2f,0.0f,4.0f);					    // Top Right Of The Quad (Back)
         glTexCoord2f(1.0f,1.0f); glVertex3f(-0.2f,0.0f,4.0f);					// Top Left Of The Quad (Back)
         glTexCoord2f(1.0f,0.0f); glVertex3f(-0.2f,0.0f,4.3f);					// Bottom Left Of The Quad (Back)
         glTexCoord2f(0.0f,0.0f); glVertex3f(0.2f,0.0f,4.3f);					// Bottom Right Of The Quad (Back)

         glEnd();

         glBegin(GL_QUADS);
         glColor3f(0.55f,0.27f,0.07f);

         glTexCoord2f(0.0f,1.0f); glVertex3f(-0.16f,0.0f,4.0f);					    // Top Right Of The Quad (Back)
         glTexCoord2f(1.0f,1.0f); glVertex3f(-0.2f,0.0f,4.0f);					// Top Left Of The Quad (Back)
         glTexCoord2f(1.0f,0.0f); glVertex3f(-0.2f,-0.3f,4.0f);					// Bottom Left Of The Quad (Back)
         glTexCoord2f(0.0f,0.0f); glVertex3f(-0.16f,-0.3f,4.0f);					// Bottom Right Of The Quad (Back)

         glEnd();
         //leg2

         glBegin(GL_QUADS);
         glColor3f(0.55f,0.27f,0.07f);

         glTexCoord2f(0.0f,1.0f); glVertex3f(-0.16f,0.0f,4.3f);					    // Top Right Of The Quad (Back)
         glTexCoord2f(1.0f,1.0f); glVertex3f(-0.2f,0.0f,4.3f);					// Top Left Of The Quad (Back)
         glTexCoord2f(1.0f,0.0f); glVertex3f(-0.2f,-0.3f,4.3f);					// Bottom Left Of The Quad (Back)
         glTexCoord2f(0.0f,0.0f); glVertex3f(-0.16f,-0.3f,4.3f);					// Bottom Right Of The Quad (Back)

         glEnd();

         glBegin(GL_QUADS);

         glColor3f(0.55f,0.27f,0.07f);
         glTexCoord2f(0.0f,1.0f); glVertex3f(0.16f,0.0f,4.0f);					    // Top Right Of The Quad (Back)
         glTexCoord2f(1.0f,1.0f); glVertex3f(0.2f,0.0f,4.0f);					// Top Left Of The Quad (Back)
         glTexCoord2f(1.0f,0.0f); glVertex3f(0.2f,-0.3f,4.0f);					// Bottom Left Of The Quad (Back)
         glTexCoord2f(0.0f,0.0f); glVertex3f(0.16f,-0.3f,4.0f);					// Bottom Right Of The Quad (Back)

         glEnd();
         //glColor3f(1.0f,1.0f,1.0f);

         //leg2
         glBegin(GL_QUADS);

         glColor3f(0.55f,0.27f,0.07f);
         glTexCoord2f(0.0f,1.0f); glVertex3f(0.16f,0.0f,4.3f);					    // Top Right Of The Quad (Back)
         glTexCoord2f(1.0f,1.0f); glVertex3f(0.2f,0.0f,4.3f);					// Top Left Of The Quad (Back)
         glTexCoord2f(1.0f,0.0f); glVertex3f(0.2f,-0.3f,4.3f);					// Bottom Left Of The Quad (Back)
         glTexCoord2f(0.0f,0.0f); glVertex3f(0.16f,-0.3f,4.3f);						// Bottom Right Of The Quad (Back)

         glEnd();
         glColor3f(1.0f,1.0f,1.0f);
}

void road(){

    glBindTexture(GL_TEXTURE_2D, texture[46]);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f,1.0f);  glVertex3f(-25.0,0.1,22.0);
    glTexCoord2f(0.0f,0.0f);  glVertex3f(-25.0,0.1,25.0);
    glTexCoord2f(1.0f,0.0f);  glVertex3f(25,0.1,25.0);
    glTexCoord2f(1.0f,1.0f);  glVertex3f(25,0.1,22.0);
    glEnd();

}


void calendar(){

    int cc=10;

    if(fll==1){
        //start=el;
        a=0.0,b=0.0,c=8.0,l_t=0.0,d=-8.0;
        fl=1;
        fll=0;
    }
    if(fl==1){
        if(el>=0 && el<=35) {
            cc=11;
            if(el>7){
                a=0,b=0,c=6,d=0,l_t=0;
                if(el>=8 && el<=11) x=15;
                else if(el>=12 && el<=15) x=16;
                else if(el>=16 && el<=19) x=17;
                else if(el>=20 && el<=23) x=18;
                else if(el>=24 && el<=27) x=19;
                else if(el>=28 && el<=31) x=20;
                else if(el>=32 && el<=35) x=21;
            }
        }
        else if(el>=36 && el<=71) {
            cc=12;
            a=0.0,b=0.0,c=8.0,l_t=0.0,d=-8.0;
            if(el>43){
                a=0,b=0,c=6,d=0,l_t=0;
                if(el>=44 && el<=47) x=22;
                else if(el>=48 && el<=51) x=23;
                else if(el>=52 && el<=55) x=24;
                else if(el>=56 && el<=59) x=25;
                else if(el>=60 && el<=63) x=26;
                else if(el>=64 && el<=67) x=27;
                else if(el>=68 && el<=71) x=28;
            }
        }
        else if(el>=72 && el<=107) {
            cc=13;
            a=0.0,b=0.0,c=8.0,l_t=0.0,d=-8.0;
            if(el>79){
                a=0,b=0,c=6,d=0,l_t=0;
                if(el>=80 && el<=83) x=29;
                else if(el>=84 && el<=87) x=30;
                else if(el>=88 && el<=91) x=31;
                else if(el>=92 && el<=95) x=32;
                else if(el>=96 && el<=99) x=33;
                else if(el>=100 && el<=103) x=34;
                else if(el>=104 && el<=107) x=35;
            }
        }
        else if(el>=108 && el<=151) {
            cc=14;
            a=0.0,b=0.0,c=8.0,l_t=0.0,d=-8.0;
            if(el>115){
                a=0,b=0,c=6,d=0,l_t=0;
                if(el>=116 && el<=119) x=36;
                else if(el>=120 && el<=123) x=37;
                else if(el>=124 && el<=127) x=38;
                else if(el>=128 && el<=131) x=39;
                else if(el>=132 && el<=135) x=40;
                else if(el>=136 && el<=139) x=41;
                else if(el>=140 && el<=143) x=42;
                else if(el>=144 && el<=147) x=43;
                else if(el>=148 && el<=151) x=5;
            }
        }
        else if(el>=152 && el<=164) {
           // cc=14;
            if(el<=155) r=0;
             a=0.0,b=0.0,c=8.0,l_t=0.0,d=8.0;
            if(el>155){

                if(el>=156 && el<=157) r=r-0.5;
                else if(el>=158 && el<=159) r=r-0.5;
                else if(el>=160 && el<=161) r=r-0.5;
                else if(el>=162 && el<=163) r=r-0.5;
                else if(el>=163 && el<=164) r=r-0.5;

            }
        }
        else {
                a=0,b=0,c=6,d=0,l_t=0;
                x=5;
                cc=10;
                fl=0;
                r=0;
        }
    }
    glBindTexture(GL_TEXTURE_2D, texture[cc]);
    glBegin(GL_QUADS);

        glTexCoord2f(0.0f,1.0f); glVertex3f(-1.95f,0.5f,5.5f);					// Top front Of The Quad (left)
        glTexCoord2f(1.0f,1.0f); glVertex3f(-1.95f,0.5f,3.5f);					// Top back Of The Quad (left)
        glTexCoord2f(1.0f,0.0f); glVertex3f(-1.95f,-0.5f,3.5f);					// Bottom back Of The Quad (left)
        glTexCoord2f(0.0f,0.0f); glVertex3f(-1.95f,-0.5f,5.5f);

    glEnd();

}


void scene(){

    glBindTexture(GL_TEXTURE_2D, texture[9]);
    glBegin(GL_QUADS);

        glTexCoord2f(0.0f,1.0f); glVertex3f(1.98f,0.5f,6.9f);					    // Top front Of The Quad (right)
        glTexCoord2f(1.0f,1.0f); glVertex3f(1.98f,0.5f,4.3f);					    // Top back Of The Quad (right)
        glTexCoord2f(1.0f,0.0f); glVertex3f(1.98f,-0.5f,4.3f);					// Bottom back Of The Quad (right)
        glTexCoord2f(0.0f,0.0f); glVertex3f(1.98f,-0.5f,6.9f);
    glEnd();
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);

        glTexCoord2f(0.0f,1.0f); glVertex3f(1.97f,0.5f,6.9f);					    // Top front Of The Quad (right)
        glTexCoord2f(1.0f,1.0f); glVertex3f(1.97f,0.5f,4.3f);					    // Top back Of The Quad (right)
        glTexCoord2f(1.0f,0.0f); glVertex3f(1.97f,-0.5f,4.3f);					// Bottom back Of The Quad (right)
        glTexCoord2f(0.0f,0.0f); glVertex3f(1.97f,-0.5f,6.9f);
    glEnd();
    glColor3f(1.0f,1.0f,1.0f);
}


void CreateList(void)
{
	SVertex * Vertices = new SVertex[NumOfVerticesStone*3];
	ListNum = glGenLists(1);
  for (GLint i = 0; i<NumOfVerticesStone; i++)
	{
		Vertices[i].x = cos(2.0 * PI / NumOfVerticesStone * i) * OuterRadius;
		Vertices[i].y = StoneHeight;  //Top
		Vertices[i].z = sin(2.0 * PI / NumOfVerticesStone * i) * OuterRadius;
	}
  for (i = 0; i<NumOfVerticesStone; i++)
	{
		Vertices[i + NumOfVerticesStone*1].x = cos(2.0 * PI / NumOfVerticesStone * i) * InnerRadius;
		Vertices[i + NumOfVerticesStone*1].y = StoneHeight;  //Top
		Vertices[i + NumOfVerticesStone*1].z = sin(2.0 * PI / NumOfVerticesStone * i) * InnerRadius;
	}
  for (i = 0; i<NumOfVerticesStone; i++)
	{
		Vertices[i + NumOfVerticesStone*2].x = cos(2.0 * PI / NumOfVerticesStone * i) * OuterRadius;
		Vertices[i + NumOfVerticesStone*2].y = 0.0;  //Bottom
		Vertices[i + NumOfVerticesStone*2].z = sin(2.0 * PI / NumOfVerticesStone * i) * OuterRadius;
	}


	glNewList(ListNum, GL_COMPILE);


        glBindTexture(GL_TEXTURE_2D, texture[7]);
        glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		//ground quad:

		glTexCoord2f(0.0f,1.0f);  glVertex3f(-19,0.0,OuterRadius1*2.0);
		glTexCoord2f(0.0f,0.0f);  glVertex3f(-19.0,0.0,-OuterRadius1*5.0);
		glTexCoord2f(1.0f,0.0f);  glVertex3f(19,0.0,-OuterRadius1*5.0);
		glTexCoord2f(1.0f,1.0f);  glVertex3f(19,0.0,OuterRadius1*2.0);
		glEnd();
        glDisable(GL_TEXTURE_2D);



		glBegin(GL_QUADS);

		for (int j = 1; j < 3; j++)
		{
			if (j == 1) glColor3f(0.66,0.2,0.2);
			if (j == 2) glColor3f(0.4,0.2,0.1);
			for (i = 0; i<NumOfVerticesStone-1; i++)
			{
				glVertex3fv(&Vertices[i+NumOfVerticesStone*j].x);
				glVertex3fv(&Vertices[i].x);
				glVertex3fv(&Vertices[i+1].x);
				glVertex3fv(&Vertices[i+NumOfVerticesStone*j+1].x);
			}
			glVertex3fv(&Vertices[i+NumOfVerticesStone*j].x);
			glVertex3fv(&Vertices[i].x);
	        glVertex3fv(&Vertices[0].x);
			glVertex3fv(&Vertices[NumOfVerticesStone*j].x);
		}

		glEnd();


		glTranslatef(0.0,WaterHeight - StoneHeight, 0.0);
	    glBegin(GL_POLYGON);
        for (i = 0; i<NumOfVerticesStone; i++)
		{


			glVertex3fv(&Vertices[i+NumOfVerticesStone].x);
			GLint m1,n1,p1;
	         m1=rand()%255;
             n1=rand()%255;
             p1=rand()%255;

	         glColor3ub(m1,n1,p1);


		}

		glEnd();
		glEndList();
}

GLfloat GetRandomFloat(GLfloat range)
{
	return (GLfloat)rand() / (GLfloat)RAND_MAX * range * RandomFactor;
}

void InitFountain(void)
{

	FountainDrops = new CDrop [ (int)DropsComplete ];
	FountainVertices = new SVertex [ (int)DropsComplete ];
	SVertex NewSpeed;
	GLfloat DropAccFactor;
	GLfloat TimeNeeded;
	GLfloat StepAngle;
	GLfloat RayAngle;
	GLint i,j,k;
	for (k = 0; k <Steps; k++)
	{
		for (j = 0; j < RaysPerStep; j++)
		{
			for (i = 0; i < DropsPerRay; i++)
			{
				DropAccFactor = AccFactor + GetRandomFloat(0.0005);
				StepAngle = AngleOfDeepestStep + (90.0-AngleOfDeepestStep)
						* GLfloat(k) / (Steps-1) + GetRandomFloat(0.2+0.8*(Steps-k-1)/(Steps-1));

				NewSpeed.x = cos ( StepAngle * PI / 180.0) * (0.2+0.04*k);
				NewSpeed.y = sin ( StepAngle * PI / 180.0) * (0.2+0.04*k);


				RayAngle = (GLfloat)j / (GLfloat)RaysPerStep * 360.0;

				NewSpeed.z = NewSpeed.x * sin ( RayAngle * PI /180.0);
				NewSpeed.x = NewSpeed.x * cos ( RayAngle * PI /180.0);


				TimeNeeded = NewSpeed.y/ DropAccFactor;
				FountainDrops[i+j*DropsPerRay+k*DropsPerRay*RaysPerStep].SetConstantSpeed ( NewSpeed );
				FountainDrops[i+j*DropsPerRay+k*DropsPerRay*RaysPerStep].SetAccFactor (DropAccFactor);
				FountainDrops[i+j*DropsPerRay+k*DropsPerRay*RaysPerStep].SetTime(TimeNeeded * i / DropsPerRay);
			}
		}
	}



	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(	3,
						GL_FLOAT,
					    0,
	FountainVertices);

}

void DrawFountain(void)
{

	glColor3f(1,1,1);


	for (int i = 0; i < DropsComplete; i++)
	{
		FountainDrops[i].GetNewPosition(&FountainVertices[i]);
	}
	glDrawArrays(	GL_POINTS,
					0,
					DropsComplete);
glutPostRedisplay();
}

void maindoor(){
    glBindTexture(GL_TEXTURE_2D, texture[48]);
    glBegin(GL_QUADS);

        //front
        glTexCoord2f(1.0f,1.0f); glVertex3f(0.8f,-0.02f,8.02f);					    // Top Right Of The Quad (Front)
        glTexCoord2f(0.0f,1.0f); glVertex3f(-0.8f,-0.02f,8.02f);					// Top Left Of The Quad (Front)
        glTexCoord2f(0.0f,0.0f); glVertex3f(-0.8f,-0.85f,8.02f);					// Bottom Left Of The Quad (Front)
        glTexCoord2f(1.0f,0.0f); glVertex3f(0.8f,-0.85f,8.02f);

    glEnd();

    glColor3f(1.0f,1.0f,1.0f);
}


void Display(void)
{
    elapse = (double)(clock()/ CLOCKS_PER_SEC)-start;
    el= (int)elapse;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glClearColor(0,0,100,1.0);
	glLoadIdentity();
    gluLookAt(                       //  eyex, eyey, eyez specify the position of the eye point, centerx, centery, centerz specify the position of reference point, upx, upy, upz specify the direction of up vector
               a,b,c,
               d,0,0,
               0,1,0
             );

	glPushMatrix();
	glTranslatef(0.0f,-1.1f,15.0f);
	glRotatef(l_t,0.0f,1.0f,0.0f);
    glEnable(GL_TEXTURE_2D);
    glCallList(ListNum);
    glDisable(GL_TEXTURE_2D);
    DrawFountain();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0f,-0.7f,0.0f);
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glEnable(GL_TEXTURE_2D);
    sky();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,-0.7f,0.0f);
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glEnable(GL_TEXTURE_2D);
    road();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glTranslatef(0.0f,0.0f,r);
    glEnable(GL_TEXTURE_2D);
    door();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glEnable(GL_TEXTURE_2D);
    door2();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glTranslatef(0.0f,-0.7f,1.28f);
    glTranslatef(0.0f,0.0f,yy1);
    glEnable(GL_TEXTURE_2D);
    chair();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glTranslatef(0.0f,-0.6f,1.2f);
    glEnable(GL_TEXTURE_2D);
    table();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glTranslatef(-0.7f,-0.7f,1.28f);
    glTranslatef(0.0f,0.0f,yy2);
    glEnable(GL_TEXTURE_2D);
    chair();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glTranslatef(-0.7f,-0.6f,1.2f);
    glEnable(GL_TEXTURE_2D);
    table();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glTranslatef(-1.4f,-0.7f,1.28f);
    glTranslatef(0.0f,0.0f,yy3);
    glEnable(GL_TEXTURE_2D);
    chair();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glTranslatef(-1.4f,-0.6f,1.2f);
    glEnable(GL_TEXTURE_2D);
    table();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glTranslatef(0.7f,-0.7f,1.28f);
    glTranslatef(0.0f,0.0f,yy4);
    glEnable(GL_TEXTURE_2D);
    chair();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glTranslatef(0.7f,-0.6f,1.2f);
    glEnable(GL_TEXTURE_2D);
    table();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glTranslatef(1.4f,-0.7f,1.28f);
    glTranslatef(0.0f,0.0f,yy5);
    glEnable(GL_TEXTURE_2D);
    chair();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glTranslatef(1.4f,-0.6f,1.2f);
    glEnable(GL_TEXTURE_2D);
    table();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glEnable(GL_TEXTURE_2D);
    scene();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glRotatef(l_t,0.0f,1.0f,0.0f);
    glEnable(GL_TEXTURE_2D);
    calendar();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();


        glPushMatrix();
        glRotatef(l_t,0.0f,1.0f,0.0f);
        glColor3f(1.0f,1.0f,1.0f);
        ceiling();
        glPopMatrix();


        glPushMatrix();
        glRotatef(l_t,0.0f,1.0f,0.0f);
        glEnable(GL_TEXTURE_2D);
        quad();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
        glRotatef(l_t,0.0f,1.0f,0.0f);
        glEnable(GL_TEXTURE_2D);
        maindoor();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
        glRotatef(l_t,0.0f,1.0f,0.0f);
        glEnable(GL_TEXTURE_2D);
        tv();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();


    glPopMatrix();

    glFlush();			//Finish rendering
	glutSwapBuffers();


}

void my_keyboard(unsigned char key, int p, int q)
{
switch (key)
{
    case 'f':  //front view
        a=0.0,b=0.0,c=13.0,l_t=0,d=0;
        PlaySound("waterfall.wav", NULL, SND_FILENAME| SND_ASYNC);
        glutPostRedisplay();
		break;
    case 'r': //bottom view
        a=0.0,b=0.0,c=8.0,l_t=0.0,d=8.0;
        glutPostRedisplay();
		break;
    case 'l': //bottom view
        a=0.0,b=0.0,c=8.0,l_t=0.0,d=-8.0;
        glutPostRedisplay();
		break;
    case 'o': //bottom view
        //a=0.0,b=-100.0,c=5.0,l_t=0.0;
        if(r>-2.5)
        r=r-0.5;
        glutPostRedisplay();
		break;
     case 'c': //bottom view
        //a=0.0,b=-100.0,c=5.0,l_t=0.0;

        if(r<0)
        r=r+0.5;
        glutPostRedisplay();
		break;
    case 's': //bottom view
        fll=1;
        start=clock()/CLOCKS_PER_SEC;
        PlaySound("Bondhu_Chol_-_Open_Tee_Bioscope_-_Anupam_Roy_Anind.wav", NULL, SND_FILENAME| SND_ASYNC);
        glutPostRedisplay();
		break;
    case 'S': //bottom view
        fl=0;
        x=5;
         PlaySound("waterfall.wav", NULL, SND_FILENAME| SND_ASYNC);
        a=0.0,b=0.0,c=8.0,l_t=0.0,d=0.0;
        start=0;
        glutPostRedisplay();
		break;
    case '3': //bottom view
        if(yy1==0)
        yy1=yy1+0.3;
        else yy1=0;
        glutPostRedisplay();
		break;
    case '2': //bottom view
        if(yy2==0)
        yy2=yy2+0.3;
        else yy2=0;
        glutPostRedisplay();
		break;
    case '1': //bottom view
        if(yy3==0)
        yy3=yy3+0.3;
        else yy3=0;
        glutPostRedisplay();
		break;
    case '4': //bottom view
        if(yy4==0)
        yy4=yy4+0.3;
        else yy4=0;
        glutPostRedisplay();
		break;
    case '5': //bottom view
        if(yy5==0)
        yy5=yy5+0.3;
        else yy5=0;
        glutPostRedisplay();
		break;
    case 'y': //bottom view
         a+=0.1;
        glutPostRedisplay();
		break;
    case 'n': //bottom view
        a-=0.1;
        glutPostRedisplay();
		break;
    default:
        break;
}
}

void specialKeys(int key,int x,int y)
{
    if(key==GLUT_KEY_RIGHT){
        if(c>8){
            if(d<6)
            d+=0.1;
        }
        else d+=0.1;;

    }

    else if(key==GLUT_KEY_LEFT){
         if(c>12){
           if(d>-6)
           d-=0.1;
         }
         else d-=0.1;
    }

    else if(key==GLUT_KEY_UP){
        if(c>-2)
        c--;


    }

   else if(key==GLUT_KEY_DOWN){
        if(c<25)
        c++;

   }
    glutPostRedisplay();
}


void Reshape(int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.10,50.0);
	glMatrixMode(GL_MODELVIEW);
    glPointSize(GLfloat(x)/600.0);
}


void init(void)
{
   LoadGLTextures();
   glClearColor (0.39, 0.78, 0.52, 0.0);
}


int main(int argc, char **argv)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Photo Exhibition");
	init();
	PlaySound("waterfall.wav", NULL, SND_FILENAME| SND_ASYNC);

	glutSpecialFunc(specialKeys);
    glEnable(GL_DEPTH_TEST);
    glutKeyboardFunc(my_keyboard);
    glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	InitFountain();
	CreateList();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Display);
    glutMainLoop();
    return 0;
}

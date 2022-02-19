#include<windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include<iostream>//for strlen
using namespace std;

#define PI 3.1416

static GLfloat spin = 0.0;

int i,q, n;
int score = 0;//for score counting
int screen = 0, D=7;
bool collide = false, raining=false, night=false, stop=false;//check if car collide to make game over
char buffer[10];


int divx = 10, divy = -22.5, movd=0, flag=0,flagg=0;
double tx=0, cx=-15, cx2=15, hy=0, time=100, sx=0, sy=0, time_interval=100, hh=0;
double sky=0;
double zx[5],arr[5];


void sun_circle(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
		    if(i==0)  { glColor3f(1, 0.27 , 0); }
		    else if(i==20)  {glColor3f(1,0.55,0);}
		    else if(i==40)  {glColor3f(0.86,0.8,0.56);}

			angle = 2 * PI * i / 100;
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
		}

	glEnd();
}

void circle(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
		}

	glEnd();
}

void circle2(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 52; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
		}

	glEnd();
}

void circle3(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_LINE_STRIP);

		for(i = 10; i < 100; i++)
		{
		    if(i<10 || i>50){
               angle = 2 * PI * i / 100;
                glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
		    }

		}

	glEnd();
}

void whole_sky(){
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(sky*0.15, sky*0.15, sky*.5);
     //glColor3f(0,0,1);

    glVertex2f (-25, 25);
    glVertex2f (25, 25);
    if(sky*0.15+0.50<0.96)
    glColor3f(sky*0.15+0.60,sky*0.15+0.5,sky*0.15+0.5);
    else
    glColor3f(0.67,0.72,0.73);
    glVertex2f (25,-20);
    glVertex2f (-25, -20);


    glEnd();
    glPopMatrix();
}

void circle4(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 51; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
		}

	glEnd();
}



void sun(){
    glPushMatrix();
    glTranslatef(sx,sy,0);
    glTranslatef(-26,5,0);
   // glColor3f(1.0, 0.0, 0.0);
    sun_circle(2,3);
    glPopMatrix();
}

void whole_rain(){
    glPushMatrix();
        glColor3f(1,1,1);


        int rain=1000;
        for(int i = 1; i<= rain ; i++)
        {


              float a = rand() % 225 - 25;
              float b = rand() % 225 - 25;

              glBegin(GL_LINE_STRIP);
              glVertex3f (a,b, 0.0);
              glVertex3f (a+1 ,b+3, 0.0);
              glEnd();
        }

        glPopMatrix();
}

void whole_star(){

    glPushMatrix();
     glColor3f(1,1,1);

    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(0,0,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(-10,15,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(5,20,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(10,10,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(7,17,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(4,14,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(2,11,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(0,19,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(0,10,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(01,5,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(8,12,0);
    glEnd();
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(3,12,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(-2,8,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(0,16,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(-4,5,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(-8,12,0);
    glEnd();
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(-13,12,0);
    glEnd();
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(3,9,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(-1,8,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(0,3,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(4,16,0);
    glEnd();
     glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(-9,10,0);
    glEnd();

    glPopMatrix();
}


void drawRoad()
{
    glBegin(GL_QUADS);
        glColor3f(0.55,0.55,0.55);
        glVertex2f(-25, -25);
        glVertex2f(25, -25);
        glColor3f(0,0,0);
        glVertex2f(25, -20);
        glVertex2f(-25, -20);



    glEnd();
}

void dexter(){
     glPushMatrix();
     //glTranslatef(-3,-2.5,0);
     glTranslatef(0,hy,0);
     glTranslatef(-17,-11,0);
     //body
     glColor3f(0, 0, 0);
     glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,-5);
     glVertex2d(3.2,-5);
     glVertex2d(3.2,-9);
     glVertex2d(0,-9);
     glEnd();

     glColor3f(1, 1, 1);
     glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,-5.5);
     glVertex2d(2.5,-7.5);
     glVertex2d(3.2,-6.5);
     glVertex2d(3.2,-9);
     glVertex2d(0,-9);
     glEnd();

     glColor3f(1, 1, 1);
     glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,-7.5);
     glVertex2d(3.2,-7.5);
     glVertex2d(3.2,-9);
     glVertex2d(0,-9);
     glEnd();

     glColor3f(1, 1, 1);
     glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,-5.5);
     glVertex2d(2.5,-7.5);
     glVertex2d(0,-9);
     glEnd();

     glColor3f(1, 1, 1);
     glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
     glVertex2d(3.2,-6.5);
     glVertex2d(2.5,-7.5);
     glVertex2d(3.2,-9);
     glEnd();

     glColor3f(0, 0, 0);
     glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
     glVertex2d(1.4,-6.2);
     glVertex2d(1.6,-6.4);
     glVertex2d(1.6,-9);
     glVertex2d(1.4,-9);
     glEnd();

     glColor3f(0, 0, 0);
     glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
     glVertex2d(0.4,-6.2);
     glVertex2d(0.5,-6.4);
     glVertex2d(0.5,-7.7);
     glVertex2d(0.4,-7.7);
     glEnd();

     glColor3f(0, 0, 0);
     glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
     glVertex2d(0.9,-6.4);
     glVertex2d(1.0,-6.6);
     glVertex2d(1.0,-7.7);
     glVertex2d(0.9,-7.7);
     glEnd();


    //face

     glColor3f(1.0, 0.94, 0.84);
     glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,0);
     glVertex2d(3.8,0);
     glVertex2d(3.8,-5);
     glVertex2d(0,-5);
     glEnd();
     glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
     glVertex2d(3.8,-5);
     glVertex2d(2.3,-6.7);
     glVertex2d(0,-5);
     glEnd();

      //hair
     glTranslatef(2,0,0);
     glColor3f(1, 0.27 , 0);
     circle(2,0.4);
     glTranslatef(1,-0.7,0);
     glColor3f(1, 0.27 , 0);
     circle(1.5,1);
     glTranslatef(0.3,-0.5,0);
     glColor3f(1, 0.27 , 0);
     circle(0.5,1);
     glTranslatef(-0.5,-0.2,0);
     glColor3f(1, 0.27 , 0);
     circle(0.5,0.5);
     glTranslatef(-1,0.5,0);
     glColor3f(1, 0.27 , 0);
     circle(1,0.4);
     glTranslatef(-1.9,1,0);
     glColor3f(1.0, 0.27, 0);
     glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,0);
     glVertex2d(1, -0.9);
     glVertex2d(2,-0.9);
     glEnd();
     glTranslatef(1.2,-0.2,0);
     glColor3f(1, 0.27 , 0);
     circle(1,0.5);
     //border
     glTranslatef(2.3,-0.6,0);
     glColor3f(0, 0 , 0);
     circle3(1,1);
     glTranslatef(-1.5,0.4,0);
     glColor3f(0, 0 , 0);
     circle3(1,1);
     glTranslatef(-1,-0.5,0);
     glColor3f(0, 0, 0);
     glBegin(GL_LINE_STRIP); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,0);
     glVertex2d(-1, 0.8);
     glVertex2d(0,1);
     glVertex2d(2,1);
     glVertex2d(3,0.8);
     glVertex2d(3.5,0.5);
     glEnd();

     //hair

     glTranslatef(1.88,-3.4,0);
     glTranslatef(-0.5,-0.9,0);
     glTranslatef(0.6,0.2,0);


     //glasses
     glTranslatef(-2.3,2.15,0);
     glColor3f(0, 0, 0);
     glBegin(GL_POLYGON); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,0);
     glVertex2d(4,0);
     glVertex2d(4,0.3);
     glVertex2d(0,0.3);
     glEnd();
     glTranslatef(3,0.2,0);
     circle4(1,2);
     glTranslatef(-2,0.2,0);
     circle4(1.1,2.2);

     glColor3f(0.53, 0.81, 0.98);
     glTranslatef(2,-0.2,0);
     circle4(0.7,1.7);
     glTranslatef(-2,0,0);
     circle4(0.8,1.8);

     glColor3f(0, 0, 0);
     glTranslatef(2,0,0);
     circle4(0.4,1);
     glTranslatef(-2,0,0);
     circle4(0.4,1);
     glTranslatef(-0.7,0,0);
     glBegin(GL_POLYGON); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,0);
     glVertex2d(-1,1);
     glVertex2d(-1,0.6);
     glVertex2d(-0.4,0);
     glEnd();

     //ear
     glColor3f(1.0, 0.94, 0.84);
     glTranslatef(-1,-0.2,0);
     circle(0.4,0.7);

     glColor3f(1.0, 0.94, 0.84);
     glTranslatef(2.88,-2.4,0);
     circle(0.8,0.8);
     glTranslatef(-1,-0.5,0);
     circle(0.4,0.4);
     glTranslatef(0.6,-0.3,0);
     circle(0.3,0.7);
     glTranslatef(0.05,0.1,0);
     circle(0.7,0.7);
     //glColor3f(0, 0.94, 0.84);
     glTranslatef(0.55,0,0);
     circle(0.2,0.3);

     //nose
     glColor3f(0, 0, 0);
     glTranslatef(-0.7,1.7,0);
     glBegin(GL_POLYGON); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,0);
     glVertex2d(1.3,0);
     glVertex2d(1.3,0.2);
     glVertex2d(0,0.2);
     glEnd();
     glBegin(GL_POLYGON); // It can be any type Gl_POINT,_LINE
     glVertex2d(1.3,0);
     glVertex2d(0.6,-0.9);
     glVertex2d(0.4,-0.9);
     glVertex2d(1.1,0);
     glEnd();
     glBegin(GL_POLYGON); // It can be any type Gl_POINT,_LINE
     glVertex2d(0.6,-0.9);
     glVertex2d(0.8,-1.7);
     glVertex2d(0.6,-1.6);
     glVertex2d(0.4,-0.9);
     glEnd();

     glBegin(GL_POLYGON); // It can be any type Gl_POINT,_LINE

     glVertex2d(0.8,-1.7);
     glVertex2d(0,-1.2);
     glVertex2d(0.1,-1.1);
     glVertex2d(0.6,-1.5);
     glEnd();

     glColor3f(0, 0, 0);
     glTranslatef(-0.3,-3.8,0);
     circle(0.2,0.8);

    //shoes
     glTranslatef(-1.2,-0.7,0);
     glColor3f(0, 0, 0);
     glBegin(GL_POLYGON); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,-0.4);
     glVertex2d(-1,-2.5);
     glVertex2d(0.2,-1.1);
     glVertex2d(0,-2.2);
     glVertex2d(0.8,-1.3);
     glVertex2d(1,-1.2);
     glVertex2d(0.8,-1.3);
     glVertex2d(1,-1.3);
     glVertex2d(1.2,-1.3);
     glVertex2d(1.4,-1.5);
     glVertex2d(1.6,-1.7);
     glVertex2d(1.8,-2.2);
     glVertex2d(1.5,-1.1);
     glVertex2d(2.8,-2.5);
     glVertex2d(2.3,-0.4);
     glEnd();

     //hand

     glColor3f(0.6, 0.2, 0.8);
     glTranslatef(-1,1,0);
     glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
     glVertex2d(0.2,0);
     glVertex2d(1.8,0);
     glVertex2d(1,-1);
     glEnd();

     glColor3f(0, 0, 0);
     glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
     glVertex2d(0.2,0);
     glVertex2d(1.8,0);
     glVertex2d(1,-1);
     glEnd();

     glColor3f(0, 0, 0);
     glTranslatef(1,-1.3,0);
     circle(0.4,1.1);

     glColor3f(0.6, 0.2, 0.8);
     circle(0.3,1);

     glTranslatef(0,1,0);
     glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,0);
     glVertex2d(0,-1);
     glVertex2d(-1,-1.3);
     glVertex2d(-1,-0.8);
     glEnd();

     glColor3f(0, 0, 0);
     glBegin(GL_LINE_STRIP); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,0);
     glVertex2d(-1,-0.8);
     glVertex2d(-1,-1.3);
     glVertex2d(0,-1);

     glEnd();

     glColor3f(0.6, 0.2, 0.8);
     glTranslatef(0,0,0);
     glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,0);
     glVertex2d(0,-1);
     glVertex2d(1,-1.3);
     glVertex2d(1,-0.8);
     glEnd();

     glColor3f(0, 0, 0);
     glBegin(GL_LINE_STRIP); // It can be any type Gl_POINT,_LINE
     glVertex2d(0,0);
     glVertex2d(1,-0.8);
     glVertex2d(1,-1.3);
     glVertex2d(0,-1);
     glEnd();

     glColor3f(0.6, 0.2, 0.8);
     glTranslatef(0,-0.4,0);
     circle(0.2,0.9);

     glPopMatrix();

}

void drawDivider()//black patch drawn in middle of road
{
    //glLoadIdentity();

    for(int i = -5; i <= 5; i++)
    {
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
        glVertex2f(divx * i - 1, -22);
        glVertex2f(divx * i - 1+.3, -23);
        glVertex2f(divx * i + 1+.3, -23);
        glVertex2f(divx * i + 1, -22);
    glEnd();
    glTranslatef(tx, 0, 0);

    glutPostRedisplay();
    }
    glLoadIdentity();
}

void cloud(){
    glPushMatrix();
    glTranslatef(cx,20,0);
    glColor3f(1.0, 1.0, 1.0);
    circle(3,2);
    glTranslatef(-5,0,0);
    glColor3f(1.0, 1.0, 1.0);
    circle(3,2);
    glTranslatef(5,-5,0);
    glColor3f(1.0, 1.0, 1.0);
    circle(3,2);
    glTranslatef(-5,-.5,0);
    glColor3f(1.0, 1.0, 1.0);
    circle(3,2);
	glTranslatef(2,3,0);
    glColor3f(1.0, 1.0, 1.0);
    circle(8,3);
    glPopMatrix();

}

void cloud2(){
    glPushMatrix();
    glTranslatef(cx2,15,0);
    glColor3f(1.0, 1.0, 1.0);
    circle(3,2);
    glTranslatef(-5,0,0);
    glColor3f(1.0, 1.0, 1.0);
    circle(3,2);
    glTranslatef(5,-5,0);
    glColor3f(1.0, 1.0, 1.0);
    circle(3,2);
    glTranslatef(-5,-.5,0);
    glColor3f(1.0, 1.0, 1.0);
    circle(3,2);
	glTranslatef(2,3,0);
    glColor3f(1.0, 1.0, 1.0);
    circle(8,3);
    glPopMatrix();

}

void zombie(int i){
    glPushMatrix();
    glTranslatef(zx[i],-7.8,0);

    //head
    glColor3f(0.0, 0.8 , 0.0);
    circle(1.4,3);

    glTranslatef(-1,1,0);
   glColor3f(0.4, 0.8, 0);
    circle(1.8,0.5);

    glTranslatef(0,-3,0);
   // glColor3f(0, 1, 0);
    circle(1.5,0.8);

    glTranslatef(-1.6,2.2,0);
    //glColor3f(0, 1, 0);
    glBegin(GL_LINE_STRIP); // It can be any type Gl_POINT,_LINE
        glVertex2d(3, -1.8);
        glVertex2d(3, 1);
        glVertex2d(-0.3, 0.7);
        glVertex2d(0.3, 0);
        glVertex2d(1.0, 0);
        glVertex2d(1.3, -0.2);
        glVertex2d(1.6, -0.5);
        glVertex2d(1.8, -0.8);
        glVertex2d(1.6, -1);
        glVertex2d(1.4, -1.2);
        glVertex2d(1, -1.2);
        glVertex2d(0.7, -1.2);
        glVertex2d(0.4, -1.8);
        glVertex2d(0.4, -2.3);
    glEnd();

    glColor3f(0.4, 0.8, 0);
    glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
        glVertex2d(3, -1.8);
        glVertex2d(3, 1);
        glVertex2d(-0.3, 0.7);
    glEnd();

    //glColor3f(0, 1, 0);
    glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
        glVertex2d(0.7, -1.2);
        glVertex2d(0.4, -1.8);
        glVertex2d(0.4, -2.3);
    glEnd();

    glTranslatef(0,-1.2,0);
   // glColor3f(0, 1, 0);
    glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
       glVertex2d(0.5, -0.1);
        glVertex2d(2, 0.3);
        glVertex2d(1, -1);
    glEnd();


    glTranslatef(0.5,1.6,0);
    //glColor3f(0, 1, 0);
    circle(0.6,0.3);

    glTranslatef(1,1.3,0);
    //glColor3f(0, 1, 0);
    circle(0.9,0.6);


    glTranslatef(-1,-1,0);
    //glColor3f(0, 1, 0);
    glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
       glVertex2d(0, 0);
        glVertex2d(0, 1);
        glVertex2d(1, 0.3);
    glEnd();




    //eye


    glTranslatef(1,1.3,0);
    glColor3f(1, 1, 1);
    circle(0.8,1);


    glTranslatef(-0.5,0.2,0);
    glColor3f(0.63, 0.32, 0.18);
    circle(0.4,0.8);


    //teeth

    glTranslatef(-1,-1.9,0);
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
       glVertex2d(0, 0);
        glVertex2d(0.3, 0);
        glVertex2d(0.2, -1);
    glEnd();

    glTranslatef(0.5,-0.2,0);
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
       glVertex2d(0, 0);
        glVertex2d(0.3, 0);
        glVertex2d(0.2, -1);
    glEnd();

    //body

    glTranslatef(2,-9,0);
    glColor3f(0, 1, 0);
    circle2(1.5,6);

    glTranslatef(-1,4,0);
    glColor3f(0.8, 0.5 ,0);
    glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
    glVertex2d(-0.1,1);
    glVertex2d(2,2);
    glVertex2d(2.7, -4);
    glVertex2d(-0.7, -4);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(-0.1,1);
    glVertex2d(2,2);
    glVertex2d(2.7, -4);
    glVertex2d(-0.7, -4);
    glEnd();

    //pnt

    glTranslatef(0,-5,0);
    glColor3f(0, 0.5, 1);
    glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
    glVertex2d(-0.7,1);
    glVertex2d(2,1);
    glVertex2d(0.3, -6);
    glVertex2d(-0.5, -6);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(-0.7,1);
    glVertex2d(2,1);
    glVertex2d(0.3, -6);
    glVertex2d(-0.5, -6);
    glEnd();

    glTranslatef(0,0,0);
    glColor3f(0, 0.5, 1);
    glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
    glVertex2d(-0.7,1);
    glVertex2d(2.5,1);
    glVertex2d(2, -6);
    glVertex2d(1.2, -6);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(-0.7,1);
    glVertex2d(2.5,1);
    glVertex2d(2, -6);
    glVertex2d(1.2, -6);
    glEnd();

    glTranslatef(-0.5,-2.9,0);
    glColor3f(0, 1 ,0);
    glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
    glVertex2d(0,-3);
    glVertex2d(0.8,-3);
    glVertex2d(0.7, -4);
    glVertex2d(0.3, -4);
    glEnd();

    glTranslatef(-0.8,-4,0);
    glColor3f(0, 1, 0);
    circle(1.5,0.4);

    glTranslatef(2.5,4,0);
    glColor3f(0, 1 ,0);
    glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
    glVertex2d(0,-3);
    glVertex2d(0.7,-3);
    glVertex2d(0.7, -4);
    glVertex2d(0.3, -4);
    glEnd();

     glTranslatef(-0.8,-4,0);
    glColor3f(0, 1, 0);
    circle(1.5,0.4);


     //hand1


    glTranslatef(0.5,11.5,0);
    glColor3f(0.8, 0.6 ,0.113);
    glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
    glVertex2d(0,0);
    glVertex2d(0,-1.5);
    glVertex2d(-2.5, -3.4);
    glVertex2d(-2.5, -2.5);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_STRIP); // It can be any type Gl_POINT,_LINE
    glVertex2d(0,-1.5);
    glVertex2d(-2.5, -3.4);
    glVertex2d(-2.5, -2.5);
    glVertex2d(0,0);
    glEnd();

    glColor3f(0.4, 0.8, 0);
    glTranslatef(-2.5,-2.5,0);
    glBegin(GL_POLYGON); // It can be any type Gl_POINT,_LINE
    glVertex2d(0,0);
    glVertex2d(-1, 0.5);
    glVertex2d(-2, 0);
    glVertex2d(-2.5, -0.3);
    glVertex2d(-1, 0);
    glVertex2d(0, -1);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(0,0);
    glVertex2d(-1, 0.5);
    glVertex2d(-2, 0);
    glVertex2d(-2.5, -0.3);
    glVertex2d(-1, 0);
    glVertex2d(0, -1);
    glEnd();

    //hnd2

    glTranslatef(1.3,2.5,0);
    glColor3f(0.8, 0.6 ,0.113);
    glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
    glVertex2d(0,0);
    glVertex2d(0,-1);
    glVertex2d(-1.7, -0.5);
    glVertex2d(-1.7, 0);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_STRIP); // It can be any type Gl_POINT,_LINE
    glVertex2d(0,-1);
    glVertex2d(-1.7, -0.5);
    glVertex2d(-1.7, 0);
    glVertex2d(0,0);
    glEnd();

    glColor3f(0.4, 0.8, 0);
    glTranslatef(-1.3,0,0);
    glBegin(GL_POLYGON); // It can be any type Gl_POINT,_LINE
    glVertex2d(0,0);
    glVertex2d(-1, 0.5);
    glVertex2d(-2, 0);
    glVertex2d(-2.5, -0.3);
    glVertex2d(-1, 0);
    glVertex2d(0, -1);
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(0,0);
    glVertex2d(-1, 0.5);
    glVertex2d(-2, 0);
    glVertex2d(-2.5, -0.3);
    glVertex2d(-1, 0);
    glVertex2d(0, -1);
    glEnd();


    //feet





    glPopMatrix();
}

void spinDisplay_left(void)
{
   spin = spin + 0.05;
   if (spin > 360.0)
      spin = spin - 360.0;
   glutPostRedisplay();
}


void house1(double x, double y){

     glPushMatrix();

    glTranslatef(x,0,0);
    glColor3f(0.85, 0.85 ,0.85);

    glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
    glVertex2d(-25,-20);
    glVertex2d(-25,-16);
    glVertex2d(-22, -16);
    glVertex2d(-22, -20);
    glEnd();
    glColor3f(0.3, 0.3 ,0.3);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(-25,-20);
    glVertex2d(-25,-16);
    glVertex2d(-22, -16);
    glVertex2d(-22, -20);
    glEnd();

    //firt light
    if(y==0)
    glColor3f(0.55,0.45,0.33);
    else glColor3f(1,1,0);

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-24,-19,0);
    glEnd();

   // glColor3f(0.55,0.45,0.33);

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-24,-17,0);
    glEnd();

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-23,-17,0);
    glEnd();

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-23,-19,0);
    glEnd();

    glColor3f(0.85, 0.85 ,0.85);

    glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
    glVertex2d(-22,-20);
    glVertex2d(-22,-12);
    glVertex2d(-19, -12);
    glVertex2d(-19, -20);
    glEnd();
    glColor3f(0.3, 0.3 ,0.3);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(-22,-20);
    glVertex2d(-22,-12);
    glVertex2d(-19, -12);
    glVertex2d(-19, -20);
    glEnd();

    if(y==0)
    glColor3f(0.55,0.45,0.33);
    else glColor3f(1,1,0);

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-21,-19,0);
    glEnd();

   // glColor3f(0.55,0.45,0.33);

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-21,-17,0);
    glEnd();

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-20,-17,0);
    glEnd();

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-20,-19,0);
    glEnd();

    //glColor3f(0.55,0.45,0.33);

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-21,-15,0);
    glEnd();

    //glColor3f(0.55,0.45,0.33);

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-21,-13,0);
    glEnd();

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-20,-15,0);
    glEnd();

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-20,-13,0);
    glEnd();

    glColor3f(0.85, 0.85 ,0.85);

    glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
    glVertex2d(-19,-20);
    glVertex2d(-19,-17);
    glVertex2d(-16, -17);
    glVertex2d(-16, -20);
    glEnd();
    glColor3f(0.3, 0.3 ,0.3);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(-19,-20);
    glVertex2d(-19,-17);
    glVertex2d(-16, -17);
    glVertex2d(-16, -20);
    glEnd();

    if(y==0)
    glColor3f(0.55,0.45,0.33);
    else glColor3f(1,1,0);

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-18,-19,0);
    glEnd();

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-17,-19,0);
    glEnd();

    glColor3f(0.85, 0.85 ,0.85);



    glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
    glVertex2d(-16,-20);
    glVertex2d(-16,-14);
    glVertex2d(-13, -14);
    glVertex2d(-13, -20);
    glEnd();
    glColor3f(0.3, 0.3 ,0.3);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(-16,-20);
    glVertex2d(-16,-14);
    glVertex2d(-13, -14);
    glVertex2d(-13, -20);
    glEnd();

    if(y==0)
    glColor3f(0.55,0.45,0.33);
    else glColor3f(1,1,0);

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-15,-19,0);
    glEnd();

   // glColor3f(0.55,0.45,0.33);

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-15,-17,0);
    glEnd();

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-14,-17,0);
    glEnd();

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-14,-19,0);
    glEnd();

    //glColor3f(0.55,0.45,0.33);

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-15,-15,0);
    glEnd();

    //glColor3f(0.55,0.45,0.33);

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-14,-15,0);
    glEnd();

    glColor3f(0.85, 0.85 ,0.85);

    glBegin(GL_QUADS); // It can be any type Gl_POINT,_LINE
    glVertex2d(-13,-20);
    glVertex2d(-13,-18);
    glVertex2d(-10, -18);
    glVertex2d(-10, -20);
    glEnd();
    glColor3f(0.3, 0.3 ,0.3);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(-13,-20);
    glVertex2d(-13,-18);
    glVertex2d(-10, -18);
    glVertex2d(-10, -20);
    glEnd();

    if(y==0)
    glColor3f(0.55,0.45,0.33);
    else glColor3f(1,1,0);

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-11,-19,0);
    glEnd();

    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex3f(-12,-19,0);
    glEnd();


    glPopMatrix();


}

void fn(double x){
   spinDisplay_left();

   glPushMatrix();
   glTranslatef(x,0,0);

   glColor3f(0.85, 0.85 ,0.85);
    glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
    glVertex2d(-10,-20);
    glVertex2d(-8,-20);
    glVertex2d(-9, -14);
    glEnd();

    glColor3f(0.3, 0.3 ,0.3);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(-10,-20);
    glVertex2d(-8,-20);
    glVertex2d(-9, -14);
    glEnd();

    //glPushMatrix();


   //glRotatef(spin, 0.0, 0.0, 1);//  error************************************************************************************************************
   //************************************************************************************************************************************************
   //*****************************************************************************************************************************



    glColor3f(0.43, 0.545 ,0.24);

    glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
    glVertex2d(-9, -14);
    glVertex2d(-8.5,-11);
    glVertex2d(-9.5, -11);

    glEnd();
    glColor3f(0.3, 0.3 ,0.3);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(-9, -14);
    glVertex2d(-8.5,-11);
    glVertex2d(-9.5, -11);
    glEnd();

    glColor3f(0.43, 0.545 ,0.24);

    glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
    glVertex2d(-9, -14);
    glVertex2d(-11,-13.5);
    glVertex2d(-11, -14.5);

    glEnd();
    glColor3f(0.3, 0.3 ,0.3);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(-9, -14);
    glVertex2d(-11,-13.5);
    glVertex2d(-11, -14.5);
    glEnd();

     glColor3f(0.43, 0.545 ,0.24);

    glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
    glVertex2d(-9, -14);
    glVertex2d(-7,-13.5);
    glVertex2d(-7, -14.5);

    glEnd();
    glColor3f(0.3, 0.3 ,0.3);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(-9, -14);
    glVertex2d(-7,-13.5);
    glVertex2d(-7, -14.5);
    glEnd();



    glColor3f(0.43, 0.545 ,0.24);

    glBegin(GL_TRIANGLES); // It can be any type Gl_POINT,_LINE
    glVertex2d(-9, -14);
    glVertex2d(-8.5,-17);
    glVertex2d(-9.5, -17);

    glEnd();
    glColor3f(0.3, 0.3 ,0.3);
    glBegin(GL_LINE_LOOP); // It can be any type Gl_POINT,_LINE
    glVertex2d(-9, -14);
    glVertex2d(-8.5,-17);
    glVertex2d(-9.5, -17);
    glEnd();


     glPopMatrix();
}


void drawText(char ch[],int xpos, int ypos)//draw the text for score and game over
{
    int numofchar = strlen(ch);
   // glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (int i = 0; i <= numofchar - 1; i++)
    {

    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ch[i]);//font used here, may use other font also
    }
}


void drawTextNum(char ch[],int numtext,int xpos, int ypos)//counting the score
{
    int len;
    int k;
    k = 0;
    len = numtext - strlen (ch);
    //glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (int i = 0; i <=numtext - 1; i++)
    {
    if ( i < len )
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0');
    else
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
        k++;
    }

    }
}


void init()
{

glClearColor (0.0, 0.0, 0.0, 0.0);
glOrtho(-25.0, 25.0, -25.0, 25.0, -25.0, 25.0);
if(score==0){
    arr[1]=25;
    arr[2]=55;
   // arr[3]=55;
    zx[1]=25;
    zx[2]=55;
    //zx[3]=55;
}

}

void complete_house(){

    glPushMatrix();

    glTranslatef(hh, 0, 0);
    glutPostRedisplay();

    house1(0,flagg);
	fn(0);

	//glTranslatef(15,0,0);


    house1(17,flagg);
	fn(17);




    house1(34,flagg);
	fn(34);

	house1(51,flagg);
	fn(51);
	house1(68,flagg);
	fn(68);
	house1(85,flagg);
	fn(85);

	glPopMatrix();
}


void display()
{

    glClear(GL_COLOR_BUFFER_BIT);

    //sky+sun

    whole_sky();
    if(score%200==0) {
        night=true;
        n=3000;
       // l=score%

    }

    if(night==true){

    whole_star();
    flagg=9;
    n--;

            if(n==0) {
            night=false;
            //flag=0;
             }
    }
    else{
       flagg=0;
    }





    if(raining==false){
    glPushMatrix();
    sun();
	glPopMatrix();
    }



    if(score%5==0 ){
        if((score/100)%2!=0) sky-=.004;
        else  sky+=.004;
    }

    if(score%200==0) sx=0,sy=0;
    else sx=sx+0.006;

     if((score/100)%2!=0) sy-=.001;
        else  sy+=.003;

    //sky+sun

    if((score%250==0 && score!=0) || score==50) {
        raining=true;
        flag=score+50;
    }

    if(raining==true){
        whole_rain();
        if(score==flag) raining=false;
    }

    drawRoad();

    glPushMatrix();
    drawDivider();
   //
	glPopMatrix();

	tx=tx-0.003;
    if (tx<-3) tx=0;

    hh=hh-0.003;
    if (hh<-9) hh=0;

    glPushMatrix();
    cloud();
	glPopMatrix();

    if(cx<40)
	cx=cx+0.003;
	else cx=-30;

	glPushMatrix();
    cloud2();
	glPopMatrix();

    if(cx2<40)
	cx2=cx2+0.003;
	else cx2=-30;



	if(hy>0){
        hy=hy-0.09;
	}
    float r;

    complete_house();





    glPushMatrix();
    if(D==8){
    glTranslatef(2, 5, 0);
    glScalef(1.3,1.3,0);
    dexter();
	}
    dexter();

	glPopMatrix();



    for(int i=1;i<3;i++){

	    //else zx[i]=arr[i];
	     glPushMatrix();
         zombie(i);
         glPopMatrix();


        if(zx[i]>-75+arr[i])
	    {
//	        cout<<i<<" YES"<<endl;
            if(stop==false){
	        zx[i]=zx[i]-.05; }
	    }
	    else
        {
            float r=rand()%16;
            r=r+1;
            r=r/10.0;
//            cout<<i<<" "<<r<<endl;
            if(r>0.9){
                zx[i]=arr[i]*(rand()%3+1);
            }
            else{
                zx[i]-=rand()%100;
            }
        }
    }


    for(i=1;i<3;i++){
        if(zx[i]<=-13 && zx[i]>=-15){
        if(hy<14) collide=true;
        }
    }





	//color change of sky





    if(time==0) score = score + 1;

    if(time==0) time=100;
    else time=time-2;


    glColor3f(0,0,0);
    drawText("Score:", 15,20);
    itoa (score, buffer, 10);
    drawTextNum(buffer, 6, 20,20);
    glutSwapBuffers();

    if(collide == true)
    {
        PlaySound("Horn Honk-SoundBible.com-1162546405.wav", NULL, SND_FILENAME| SND_ASYNC);
        glColor3f(1,0,0);
        drawText("YOU ARE DEAD", -3,0);
        glutSwapBuffers();
        getchar();
        //exit(0);
    }






}

void spe_key(int key, int x, int y)
{
     switch (key) {

      case GLUT_KEY_UP:
                if(hy<=0){
                   // PlaySound("powerup.wav", NULL, SND_FILENAME| SND_ASYNC);
                    hy=34;
                    glutPostRedisplay();
                   // PlaySound("imperial_march.wav", NULL, SND_FILENAME| SND_ASYNC);
                }

				break;
	  default:
			break;
	}
}

void my_keyboard(unsigned char key, int x, int y)
{

	switch (key) {

		case 'd':
			D=7;
			break;

		case 'l':
			D=8;
			break;
        case 'p':
            stop=true;


			break;
         case 'r':
            stop=false;

			break;



	  default:
			break;
	}
}





int main()
{
   // glutInit(&argc,argv);
    PlaySound("imperial_march.wav", NULL, SND_FILENAME| SND_ASYNC| SND_LOOP);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,500);
    glutCreateWindow("Zombie Land");
    //ovpos();
    init();
    glutDisplayFunc(display);
	glutSpecialFunc(spe_key);
    glutKeyboardFunc(my_keyboard);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}

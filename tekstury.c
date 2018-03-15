#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
#include <windows.h>            // Window defines
#include <gl\gl.h>              // OpenGL
#include <gl\glu.h>             // GLU library
#include <math.h>				// Define for sqrt
#include <stdio.h>
#include "resource.h"           // About box resource identifiers.
#include <stdlib.h>


#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)
#define BITMAP_ID 0x4D42		// identyfikator formatu BMP
#define GL_PI 3.14

// Color Palette handle
HPALETTE hPalette = NULL;

// Application name and instance storeage
static LPCTSTR lpszAppName = "GL Template";
static HINSTANCE hInstance;

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
int sciana = 0;
int otw = 1;

double x=0,y=0,z=0,i,kierunek,kierunek1,kierunek2,liczba;
float a=0.0f,b=0.0f,c=0.0f;
float deltax=100.0f,deltay=0.0f,deltaz=300.0f;


static GLsizei lastHeight;
static GLsizei lastWidth;

// Opis tekstury
BITMAPINFOHEADER	bitmapInfoHeader;	// nag³ówek obrazu
unsigned char*		bitmapData;			// dane tekstury
unsigned int		texture[2];			// obiekt tekstury


// Declaration for Window procedure
LRESULT CALLBACK WndProc(   HWND    hWnd,
							UINT    message,
							WPARAM  wParam,
							LPARAM  lParam);

// Dialog procedure for about box
BOOL APIENTRY AboutDlgProc (HWND hDlg, UINT message, UINT wParam, LONG lParam);

// Set Pixel Format function - forward declaration
void SetDCPixelFormat(HDC hDC);

// Reduces a normal vector specified as a set of three coordinates,
// to a unit normal vector of length one.
void ReduceToUnit(float vector[3])
	{
	float length;
	
	// Calculate the length of the vector		
	length = (float)sqrt((vector[0]*vector[0]) + 
						(vector[1]*vector[1]) +
						(vector[2]*vector[2]));

	// Keep the program from blowing up by providing an exceptable
	// value for vectors that may calculated too close to zero.
	if(length == 0.0f)
		length = 1.0f;

	// Dividing each element by the length will result in a
	// unit normal vector.
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
	}


// Points p1, p2, & p3 specified in counter clock-wise order
void calcNormal(float v[3][3], float out[3])
	{
	float v1[3],v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	// Calculate two vectors from the three points
	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];

	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];

	// Take the cross product of the two vectors to get
	// the normal vector which will be stored in out
	out[x] = v1[y]*v2[z] - v1[z]*v2[y];
	out[y] = v1[z]*v2[x] - v1[x]*v2[z];
	out[z] = v1[x]*v2[y] - v1[y]*v2[x];

	// Normalize the vector (shorten length to one)
	ReduceToUnit(out);
	}



// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(GLsizei w, GLsizei h)
	{
	GLfloat nRange = 500.0f;
	GLfloat fAspect;
	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	lastWidth = w;
	lastHeight = h;
		
	fAspect=(GLfloat)w/(GLfloat)h;
	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);
	
	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluLookAt( 0.0, 0.0, 0.7, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0 );
	// Establish clipping volume (left, right, bottom, top, near, far)
    /*
	if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
		*/
	// Establish perspective: 
	
	gluPerspective(60.0f,fAspect,1.0,2000);
	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	}



// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
	{
	// Light values and coordinates
	/*
	GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat	 lightPos[] = { 150.0f, 150.0f, 150.0f, 1.0f };
	GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
	*/
//~~~~~~~~~~~~~~~~
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
//~~~~~~~~~~~~~~~~
	//glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	// Enable lighting
	//glEnable(GL_LIGHTING);

	// Setup and enable light 0
	
	//glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	//glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	
	
	//glEnable(GL_LIGHT0);
	// Enable color tracking
	//glEnable(GL_COLOR_MATERIAL);
	
	// Set Material properties to follow glColor values
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	//glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
	//glMateriali(GL_FRONT,GL_SHININESS,128);

//~~~~~~~~~~~~~~	
	// White background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
	// Black brush
	glColor3f(0.0,0.0,0.0);
}
void ziemia(int i)
{	GLUquadricObj*obj;
	obj=gluNewQuadric();
	gluQuadricTexture(obj,GL_TRUE);
	glBindTexture(GL_TEXTURE_2D,texture[i]);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glColor3d(1.0,0.8,0.8);
	glEnable(GL_TEXTURE_2D);
	gluSphere(obj,200,100,15);
	glDisable(GL_TEXTURE_2D);
}
void kula(int i)
{	GLUquadricObj*obj;
	obj=gluNewQuadric();
	gluQuadricTexture(obj,GL_TRUE);
	glBindTexture(GL_TEXTURE_2D,texture[i]);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glColor3d(1.0,0.8,0.8);
	glEnable(GL_TEXTURE_2D);
	gluSphere(obj,850,100,15);
	glDisable(GL_TEXTURE_2D);
}
void ksiezyc(int i)
{
	GLUquadricObj*obj;
	obj=gluNewQuadric();
	gluQuadricTexture(obj,GL_TRUE);
	glBindTexture(GL_TEXTURE_2D,texture[i]);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glColor3d(1.0,0.8,0.8);
	glEnable(GL_TEXTURE_2D);
	gluSphere(obj,50,100,15);
	glDisable(GL_TEXTURE_2D);

}
void mars(int i)
{
	GLUquadricObj*obj;
	obj=gluNewQuadric();
	gluQuadricTexture(obj,GL_TRUE);
	glBindTexture(GL_TEXTURE_2D,texture[i]);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glColor3d(1.0,0.8,0.8);
	glEnable(GL_TEXTURE_2D);
	gluSphere(obj,80,100,15);
	glDisable(GL_TEXTURE_2D);

}
void saturn(int i)
{
	GLUquadricObj*obj;
	obj=gluNewQuadric();
	gluQuadricTexture(obj,GL_TRUE);
	glBindTexture(GL_TEXTURE_2D,texture[i]);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glColor3d(1.0,0.8,0.8);
	glEnable(GL_TEXTURE_2D);
	gluSphere(obj,120,100,15);
	glDisable(GL_TEXTURE_2D);

}
void neptun(int i)
{
	GLUquadricObj*obj;
	obj=gluNewQuadric();
	gluQuadricTexture(obj,GL_TRUE);
	glBindTexture(GL_TEXTURE_2D,texture[i]);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glColor3d(1.0,0.8,0.8);
	glEnable(GL_TEXTURE_2D);
	gluSphere(obj,60,100,15);
	glDisable(GL_TEXTURE_2D);

}
void fire(double x,double y,double z)
{
	double PI=3.14,alpha;

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glEnable(GL_TEXTURE_2D);
	
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	{
		glColor3d(1,1,1);
		
		glBegin(GL_QUAD_STRIP);

		for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 20 * sin(alpha);
		y = 20 * cos(alpha);
		glTexCoord2f(0,0);
		glVertex3d(x, y, 0);
		glTexCoord2f(1,1);
		glVertex3d(0, 0, -50);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10*sin(alpha) - 20;
		y = 10*cos(alpha) - 20;
		glTexCoord2f(0,0);
		glVertex3d(x, y, 0);
		glTexCoord2f(1,1);
		glVertex3d(-20, -20, -30);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10*sin(alpha) + 20;
		y = 10*cos(alpha) - 20;
		glTexCoord2f(0,0);
		glVertex3d(x, y, 0);
		glTexCoord2f(1,1);
		glVertex3d(20, -20, -30);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10*sin(alpha) - 20;
		y = 10*cos(alpha) + 20;
		glTexCoord2f(0,0);
		glVertex3d(x, y, 0);
		glTexCoord2f(1,1);
		glVertex3d(-20, 20, -30);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10*sin(alpha) + 20;
		y = 10*cos(alpha) + 20;
		glTexCoord2f(0,0);
		glVertex3d(x, y, 0);
		glTexCoord2f(1,1);
		glVertex3d(20, 20, -30);
	}
	glEnd();
	}

}
void planeta(double q,double w, double e, double r, double h,int i)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	{
	double a,b,PI=3.14, alpha;
	a=q;
	b=w;
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	glEnable(GL_TEXTURE_2D);
	glColor3d(1,1,1);
	
	glBegin(GL_TRIANGLE_FAN);
	//glColor3d(0.6, 0.1, 0.3);
	glVertex3d(q,w, e+h/2);
	for (alpha = 0;alpha <= 2 * PI; alpha += PI / 8)
	{
		q = r/2 * sin(alpha)+a;
		w = r/2 * cos(alpha)+b;
		glTexCoord2f(0,0);
		glVertex3d(q, w, e+h/2);
		
	}
	glEnd();
	
	glBegin(GL_QUAD_STRIP);
	glColor3d(1,1,1);
	for (alpha = 0;alpha <= 2 * PI; alpha += PI/8)
	{
		q = r * sin(alpha)+a;
		w = r * cos(alpha)+b;
		glTexCoord2f(0,0);
		glVertex3d(q,w,e);
		glTexCoord2f(1,1);
		glVertex3d(q/2+a/2,w/2+b/2,e+h/2);
	}
	glEnd();
	
	glBegin(GL_QUAD_STRIP);
	glColor3d(1, 1, 1);
	for (alpha = 0;alpha <= 2 * PI; alpha += PI / 8)
	{
		q = r * sin(alpha)+a;
		w = r * cos(alpha)+b;
		glTexCoord2f(0,0);
		glVertex3d(q, w, e-h);
		glTexCoord2f(1,1);
		glVertex3d(q, w, e);
	}
	glEnd();
	
	glBegin(GL_QUAD_STRIP);
	glColor3d(1,1,1);
	for (alpha = 0;alpha <= 2 * PI; alpha += PI/8)
	{
		q = r * sin(alpha)+a;
		w = r * cos(alpha)+b;
		glTexCoord2f(0,0);
		glVertex3d(q/2+a/2,w/2+b/2,e-h-h/2);
		glTexCoord2f(1,1);
		glVertex3d(q,w,e-h);
	}
	glEnd();
	
	glBegin(GL_TRIANGLE_FAN);
	glColor3d(1, 1, 1);
	glVertex3d(q/2+a/2,w/2+b/2,(e-h)-h/2);

	for (alpha = 0;alpha >= -2 * PI; alpha -= PI / 8)
	{
		q = r * sin(alpha)+a;
		w = r * cos(alpha)+b;
		glTexCoord2f(0,0);
		glVertex3d(q/2+a/2,w/2+b/2,(e-h)-h/2);
		glTexCoord2f(1,1);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	}
}


void podstawa1(void)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	{
	
	GLfloat sa[3]={-200.0f,200.0f,-200.0f};
	GLfloat sb[3]={200.0f,200.0f,-200.0f};
	GLfloat sc[3]={200.0f,-200.0f,-200.0f};
	GLfloat sd[3]={-200.0f,-200.0f,-200.0f};
	GLfloat se[3]={-200.0f,200.0f,200.0f};
	GLfloat sf[3]={200.0f,200.0f,200.0f};
	GLfloat sg[3]={200.0f,-200.0f,200.0f};
	GLfloat sh[3]={-200.0f,-200.0f,200.0f};

	
	glBindTexture(GL_TEXTURE_2D, texture[0]);	//aktywujemy teksturê 0
	glEnable(GL_TEXTURE_2D);					//aktywujemy tekstuorowanie
	glColor3f(1, 1, 1);							//ustawiamy kolor tekstury na bia³y, ¿eby by³a widoczna taka, jak¹ jest
		glBegin(GL_POLYGON);					//rysowanie wielok¹ta
		glTexCoord2f(0, 0);						//przypisujemy lewy dolny róg teksury kolejnemy wierzcho³kowi
		glVertex3f(0,0,0);						//rysujemy lewy dolny punkt
		glTexCoord2f(1, 0);						//przypisujemy prawy dolny róg tekstury kolejnemu wierzcho³kowi
		glVertex3f(20, 0, 0);					//rysujemy prawy dolny punkt
		glTexCoord2f(1, 1);						//przypisujemy prawy górny róg tekstury
		glVertex3f(20, 20, 0);					//rysujemy prawy górny punkt
		glTexCoord2f(0, 1);						//przypisujemy lewy górny róg tesktury
		glVertex3f(0, 20, 0);					//rysujemy lewy górny punkt
		glEnd();								//koniec rysowania
	glDisable(GL_TEXTURE_2D);					//wy³¹czamy teksturowanie
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glEnable(GL_TEXTURE_2D);
	glColor3d(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sa);
		glTexCoord2f(1,0);
		glVertex3fv(sb);
		glTexCoord2f(1,1);
		glVertex3fv(sc);
		glTexCoord2f(0,1);
		glVertex3fv(sd);
	glEnd();
	

		//glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sb);
		glTexCoord2f(1,0);
		glVertex3fv(sf);
		glTexCoord2f(1,1);
		glVertex3fv(sg);
		glTexCoord2f(0,1);
		glVertex3fv(sc);
	glEnd();

	//glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sf);
		glTexCoord2f(1,0);
		glVertex3fv(se);
		glTexCoord2f(1,1);
		glVertex3fv(sh);
		glTexCoord2f(0,1);
		glVertex3fv(sg);
	glEnd();

		//glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(se);
		glTexCoord2f(1,0);
		glVertex3fv(sa);
		glTexCoord2f(1,1);
		glVertex3fv(sd);
		glTexCoord2f(0,1);
		glVertex3fv(sh);
	glEnd();

		//glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sd);
		glTexCoord2f(1,0);
		glVertex3fv(sc);
		glTexCoord2f(1,1);
		glVertex3fv(sg);
		glTexCoord2f(0,1);
		glVertex3fv(sh);
	glEnd();

	//glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sa);
		glTexCoord2f(1,0);
		glVertex3fv(sb);
		glTexCoord2f(1,1);
		glVertex3fv(sf);
		glTexCoord2f(0,1);
		glVertex3fv(se);
	glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}




void podstawa(double r, double h,double p)
{
	double x, y, PI = 3.14, alpha;

	glBegin(GL_TRIANGLE_FAN);
	glColor3d(0.6, 0.1, 0.3);
	glVertex3d(0, 0, -30);

	for (alpha = 0;alpha <= 2 * PI; alpha += PI / p)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(x, y, -30);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3d(0.7, 0.7, 0.8);
	for (alpha = 0;alpha <= 2 * PI; alpha += PI / p)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(x, y, -30);
		glVertex3d(x, y, h);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3d(0.2, 0.4, 0.1);
	glVertex3d(0, 0, h);

	for (alpha = 0;alpha >= -2 * PI; alpha -= PI / p)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(x, y, h);
	}
	glEnd();
}
void tlo()
{
	double x, y, PI = 3.14, alpha;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	{
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glEnable(GL_TEXTURE_2D);
	

	glBegin(GL_TRIANGLE_FAN);
	glColor3d(1, 1, 1);
	

	for (alpha = 0;alpha <= 2 * PI; alpha += PI / 20)
	{
		x = 650 * sin(alpha);
		y = 650 * cos(alpha);
		glTexCoord2f(0,0);
		glVertex3d(x, y, -500);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	//glColor3d(0.7, 0.7, 0.8);
	for (alpha = 0;alpha <=  2*PI; alpha += PI / 20)
	{
		x = 650 * sin(alpha);
		y = 650 * cos(alpha);
		glTexCoord2f(0,0);
		glVertex3d(x, y, -500);
		glTexCoord2f(1,1);
		glVertex3d(x, y, 500);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3d(1, 1, 1);
	//glVertex3d(0, 0, h);

	for (alpha = 0;alpha >= -2 * PI; alpha -= PI / 20)
	{
		x = 650 * sin(alpha);
		y = 650 * cos(alpha);
		glTexCoord2f(0,0);
		glVertex3d(x, y, 500);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	}
}
void skrzydla(double x1,double x2,double x3)
{	
	x1=0;
	x2=0;
	x3=0;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	{
	GLfloat sa[3]={x1-63.0f,x2+18.0f,x3+10.0f};
	GLfloat sb[3]={x1+65.0f,x2-28.0f,x3+10.0f};
	GLfloat sc[3]={x1+68.0f,x2-20.0f,x3+10.0f};
	GLfloat sd[3]={x1-60.0f,x2+26.0f,x3+10.0f};
	GLfloat se[3]={x1-63.0f,x2+18.0f,x3+30.0f};
	GLfloat sf[3]={x1+65.0f,x2-28.0f,x3+30.0f};
	GLfloat sg[3]={x1+68.0f,x2-20.0f,x3+30.0f};
	GLfloat sh[3]={x1-60.0f,x2+26.0f,x3+30.0f};


		// Parametry wierzcholkow
	
	// Sciany skladowe
	//glColor3f(1.0f, 0.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glEnable(GL_TEXTURE_2D);
	glColor3d(1.0,1.0,1.0);
	

	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sa);
		glTexCoord2f(1,0);
		glVertex3fv(sb);
		glTexCoord2f(1,1);
		glVertex3fv(sc);
		glTexCoord2f(0,1);
		glVertex3fv(sd);
	glEnd();

		//glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sb);
		glTexCoord2f(1,0);
		glVertex3fv(sf);
		glTexCoord2f(1,1);
		glVertex3fv(sg);
		glTexCoord2f(0,1);
		glVertex3fv(sc);
	glEnd();

	//glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sf);
		glTexCoord2f(1,0);
		glVertex3fv(se);
		glTexCoord2f(1,1);
		glVertex3fv(sh);
		glTexCoord2f(0,1);
		glVertex3fv(sg);
	glEnd();

		//glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(se);
		glTexCoord2f(1,0);
		glVertex3fv(sa);
		glTexCoord2f(1,1);
		glVertex3fv(sd);
		glTexCoord2f(0,1);
		glVertex3fv(sh);
	glEnd();

		//glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sd);
		glTexCoord2f(1,0);
		glVertex3fv(sc);
		glTexCoord2f(1,1);
		glVertex3fv(sg);
		glTexCoord2f(0,1);
		glVertex3fv(sh);
	glEnd();

	//glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sa);
		glTexCoord2f(1,0);
		glVertex3fv(sb);
		glTexCoord2f(1,1);
		glVertex3fv(sf);
		glTexCoord2f(0,1);
		glVertex3fv(se);
	glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	{
	
	GLfloat sa[3]={x1-63.0f,x2-18.0f,x3+10.0f};
	GLfloat sb[3]={x1+65.0f,x2+28.0f,x3+10.0f};
	GLfloat sc[3]={x1+68.0f,x2+20.0f,x3+10.0f};
	GLfloat sd[3]={x1-60.0f,x2-26.0f,x3+10.0f};
	GLfloat se[3]={x1-63.0f,x2-18.0f,x3+30.0f};
	GLfloat sf[3]={x1+65.0f,x2+28.0f,x3+30.0f};
	GLfloat sg[3]={x1+68.0f,x2+20.0f,x3+30.0f};
	GLfloat sh[3]={x1-60.0f,x2-26.0f,x3+30.0f};

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glEnable(GL_TEXTURE_2D);
	glColor3d(1.0,1.0,1.0);
	
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sa);
		glTexCoord2f(1,0);
		glVertex3fv(sb);
		glTexCoord2f(1,1);
		glVertex3fv(sc);
		glTexCoord2f(0,1);
		glVertex3fv(sd);
	glEnd();

		//glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sb);
		glTexCoord2f(1,0);
		glVertex3fv(sf);
		glTexCoord2f(1,1);
		glVertex3fv(sg);
		glTexCoord2f(0,1);
		glVertex3fv(sc);
	glEnd();

	//glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sf);
		glTexCoord2f(1,0);
		glVertex3fv(se);
		glTexCoord2f(1,1);
		glVertex3fv(sh);
		glTexCoord2f(0,1);
		glVertex3fv(sg);
	glEnd();

		//glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(se);
		glTexCoord2f(1,0);
		glVertex3fv(sa);
		glTexCoord2f(1,1);
		glVertex3fv(sd);
		glTexCoord2f(0,1);
		glVertex3fv(sh);
	glEnd();

		//glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sd);
		glTexCoord2f(1,0);
		glVertex3fv(sc);
		glTexCoord2f(1,1);
		glVertex3fv(sg);
		glTexCoord2f(0,1);
		glVertex3fv(sh);
	glEnd();

	//glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3fv(sa);
		glTexCoord2f(1,0);
		glVertex3fv(sb);
		glTexCoord2f(1,1);
		glVertex3fv(sf);
		glTexCoord2f(0,1);
		glVertex3fv(se);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	}
}

void statek(double x,double y, double z)
{
	double  PI = 3.14, alpha,x1=0,x2=0,x3=0;
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glEnable(GL_TEXTURE_2D);
	glColor3d(1.0,1.0,1.0);
	glBegin(GL_TRIANGLE_FAN);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 20*sin(alpha);
		y = 20*cos(alpha);
		glTexCoord2f(0,0);
		glVertex3d(x,y,0);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP); //korpus
	//glColor3d(0.6, 0.4, 0.7);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 20*sin(alpha)+x1;
		y = 20*cos(alpha)+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 0+x3);
		glTexCoord2f(1,1);
		glVertex3d(x+x1, y+x2, 100+x3);
	}
	

	//glColor3d(1, 1, 1);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 20 * sin(alpha)+x1;
		y = 20 * cos(alpha)+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 100+x3);
		glTexCoord2f(1,1);
		glVertex3d(x/2+x1, y/2+x2, 150+x3);
	}
	glEnd();
	
	
	glBegin(GL_QUAD_STRIP);
	glColor3d(1,1,1);
	for (alpha = 0;alpha >= -2 * PI;alpha -= PI / 6)
	{
		x = 10 * sin(alpha)+x1;
		y = 10 * cos(alpha)+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 145+x3);
		glTexCoord2f(1,1);
		glVertex3d(0+x1, 0+x2, 170+x3);
	}
	glEnd();
	
	
	glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glEnable(GL_TEXTURE_2D);
	glColor3d(1, 1, 1);
	glBegin(GL_TRIANGLE_FAN);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10*sin(alpha) -20;
		y = 10*cos(alpha) -20;
		glTexCoord2f(0,0);
		glVertex3d(x,y,0);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10*sin(alpha) -20;
		y = 10*cos(alpha) +20;
		glTexCoord2f(0,0);
		glVertex3d(x,y,0);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10*sin(alpha) +20;
		y = 10*cos(alpha) -20;
		glTexCoord2f(0,0);
		glVertex3d(x,y,0);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10*sin(alpha) +20;
		y = 10*cos(alpha) +20;
		glTexCoord2f(0,0);
		glVertex3d(x,y,0);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);//lewy dolny silnik
	
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10*sin(alpha) - 20+x1;
		y = 10*cos(alpha) - 20+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 0+x3);
		glTexCoord2f(1,1);
		glVertex3d(x+x1, y+x2, 40+x3);
	}
	
	//glColor3d(0.4, 0.6, 0.2);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10 * sin(alpha) - 20+x1;
		y = 10 * cos(alpha) - 20+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 40+x3);
		glTexCoord2f(1,1);
		glVertex3d(-20+x1, -20+x2, 50+x3);
		
	}
	
	glEnd();
	

	glBegin(GL_QUAD_STRIP);//lewy górny silnik
	//glColor3d(0.6, 0.4, 0.7);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10 * sin(alpha) - 20+x1;
		y = 10 * cos(alpha) + 20+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 0+x3);
		glTexCoord2f(1,1);
		glVertex3d(x+x1, y+x2, 40+x3);
	}
	//glColor3d(0.4, 0.6, 0.2);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10 * sin(alpha) - 20+x1;
		y = 10 * cos(alpha) + 20+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 40+x3);
		glTexCoord2f(1,1);
		glVertex3d(-20+x1, 20+x2, 50+x3);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);//prawy dolny silnik
	//glColor3d(0.6, 0.4, 0.7);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10 * sin(alpha) + 20+x1;
		y = 10 * cos(alpha) - 20+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 0+x3);
		glTexCoord2f(1,1);
		glVertex3d(x+x1, y+x2, 40+x3);
		
	}
	//glColor3d(0.4, 0.6, 0.2);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10 * sin(alpha) + 20+x1;
		y = 10 * cos(alpha) - 20+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 40+x3);
		glTexCoord2f(1,1);
		glVertex3d(x1+20, -20+x2, 50+x3);
		
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);//prawy górny silnik
	//glColor3d(0.6, 0.4, 0.7);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10 * sin(alpha) + 20+x1;
		y = 10 * cos(alpha) + 20+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 0+x3);
		glTexCoord2f(1,1);
		glVertex3d(x+x1, y+x2, 40+x3);
		
	}
	glColor3d(1, 1, 1);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10 * sin(alpha) + 20+x1;
		y = 10 * cos(alpha) + 20+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 40+x3);
		glTexCoord2f(1,1);
		glVertex3d(20+x1, 20+x2, 50+x3);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//////////////////////skrzyd³a
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glEnable(GL_TEXTURE_2D);
	glColor3d(1,1,1);
	glBegin(GL_TRIANGLE_FAN);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5*sin(alpha) -60;
		y = 5*cos(alpha) +30;
		glTexCoord2f(0,0);
		glVertex3d(x,y,10);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5*sin(alpha) -60;
		y = 5*cos(alpha) -30;
		glTexCoord2f(0,0);
		glVertex3d(x,y,10);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5*sin(alpha) +60;
		y = 5*cos(alpha) -30;
		glTexCoord2f(0,0);
		glVertex3d(x,y,10);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5*sin(alpha) +60;
		y = 5*cos(alpha) +30;
		glTexCoord2f(0,0);
		glVertex3d(x,y,10);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glColor3d(1, 1, 1);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5*sin(alpha) - 60+x1;
		y = 5*cos(alpha) + 30+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 10+x3);
		glTexCoord2f(1,1);
		glVertex3d(x+x1, y+x2, 30+x3);
	}
	glColor3d(1, 1, 1);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5 * sin(alpha) - 60+x1;
		y = 5 * cos(alpha) + 30+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 30+x3);
		glTexCoord2f(1,1);
		glVertex3d(-60+x1, 30+x2, 35+x3);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3d(1, 1, 1);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5*sin(alpha) - 60+x1;
		y = 5*cos(alpha) - 30+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 10+x3);
		glTexCoord2f(1,1);
		glVertex3d(x+x1, y+x2, 30+x3);
	}
	glColor3d(1, 1, 1);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5 * sin(alpha) - 60+x1;
		y = 5 * cos(alpha) - 30+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 30+x3);
		glTexCoord2f(1,1);
		glVertex3d(-60+x1, -30+x2, 35+x3);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3d(1, 1, 1);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5*sin(alpha) + 60+x1;
		y = 5*cos(alpha) - 30+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 10+x3);
		glTexCoord2f(1,1);
		glVertex3d(x+x1, y+x2, 30+x3);
	}
	glColor3d(1, 1, 1);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5 * sin(alpha) + 60+x1;
		y = 5 * cos(alpha) - 30+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 30+x3);
		glTexCoord2f(1,1);
		glVertex3d(60+x1, -30+x2, 35+x3);
	}
	glEnd();


	glBegin(GL_QUAD_STRIP);
	glColor3d(1, 1, 1);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5*sin(alpha) + 60+x1;
		y = 5*cos(alpha) + 30+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 10+x3);
		glTexCoord2f(1,1);
		glVertex3d(x+x1, y+x2, 30+x3);
	}
	glColor3d(1, 1, 1);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5 * sin(alpha) + 60+x1;
		y = 5 * cos(alpha) + 30+x2;
		glTexCoord2f(0,0);
		glVertex3d(x+x1, y+x2, 30+x3);
		glTexCoord2f(1,1);
		glVertex3d(60+x1, 30+x2, 35+x3);
	}
	glEnd(); 
	glDisable(GL_TEXTURE_2D);
	}
	
}
void szescian(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);	//aktywujemy teksturê 0
	glEnable(GL_TEXTURE_2D);					//aktywujemy tekstuorowanie
	glColor3f(1, 1, 1);							//ustawiamy kolor tekstury na bia³y, ¿eby by³a widoczna taka, jak¹ jest
		glBegin(GL_POLYGON);					//rysowanie wielok¹ta
		glTexCoord2f(0, 0);						//przypisujemy lewy dolny róg teksury kolejnemy wierzcho³kowi
		glVertex3f(0,0,0);						//rysujemy lewy dolny punkt
		glTexCoord2f(1, 0);						//przypisujemy prawy dolny róg tekstury kolejnemu wierzcho³kowi
		glVertex3f(20, 0, 0);					//rysujemy prawy dolny punkt
		glTexCoord2f(1, 1);						//przypisujemy prawy górny róg tekstury
		glVertex3f(20, 20, 0);					//rysujemy prawy górny punkt
		glTexCoord2f(0, 1);						//przypisujemy lewy górny róg tesktury
		glVertex3f(0, 20, 0);					//rysujemy lewy górny punkt
		glEnd();								//koniec rysowania
	glDisable(GL_TEXTURE_2D);					//wy³¹czamy teksturowanie

}


// LoadBitmapFile
// opis: ³aduje mapê bitow¹ z pliku i zwraca jej adres.
//       Wype³nia strukturê nag³ówka.
//	 Nie obs³uguje map 8-bitowych.
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;							// wskaŸnik pozycji pliku
	BITMAPFILEHEADER	bitmapFileHeader;		// nag³ówek pliku
	unsigned char		*bitmapImage;			// dane obrazu
	int					imageIdx = 0;		// licznik pikseli
	unsigned char		tempRGB;				// zmienna zamiany sk³adowych

	// otwiera plik w trybie "read binary"
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// wczytuje nag³ówek pliku
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	
	// sprawdza, czy jest to plik formatu BMP
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// wczytuje nag³ówek obrazu
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// ustawia wskaŸnik pozycji pliku na pocz¹tku danych obrazu
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// przydziela pamiêæ buforowi obrazu
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// sprawdza, czy uda³o siê przydzieliæ pamiêæ
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// wczytuje dane obrazu
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// sprawdza, czy dane zosta³y wczytane
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// zamienia miejscami sk³adowe R i B 
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// zamyka plik i zwraca wskaŸnik bufora zawieraj¹cego wczytany obraz
	fclose(filePtr);
	return bitmapImage;
}


// Called to draw scene
void RenderScene(void)
	{
	//float normal[3];	// Storeage for calculated surface normal

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Save the matrix state and do the rotations
	glPushMatrix();
	glTranslatef(deltax,deltay,-deltaz);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	/////////////////////////////////////////////////////////////////
	// MIEJSCE NA KOD OPENGL DO TWORZENIA WLASNYCH SCEN:		   //
	/////////////////////////////////////////////////////////////////

	//Sposób na odróŸnienie "przedniej" i "tylniej" œciany wielok¹ta:
	glPolygonMode(GL_BACK,GL_LINE);
	
	//Uzyskanie siatki:
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	//Rysowanie obiektów:
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//szescian();
	//podstawa(200,400,200);
	//podstawa1();
	//tlo();

	glPushMatrix();
	glRotated(kierunek,0.1,0,0);
	glRotated(kierunek1,0,0.1,0);
	glRotated(kierunek2,0,0,0.1);

	glTranslatef(x,y,z);
	statek(x,y,z);
	skrzydla(x,y,z);
	if( GetAsyncKeyState( 'E' ) & 0x8000 )
{
    fire(x,y,z);
}
	glPopMatrix();
	
	//planeta(0,0,0,50,50);
	glPushMatrix();
	glRotatef(10.0*liczba,0.1,0,0);
	glTranslated(-a,0,0);
	planeta(400,100,60,10,10,0);
	glPopMatrix();
	glPushMatrix();
	glTranslated(a,b,0);
	planeta(-300,-100,30,20,20,0);
	glPopMatrix();
	glPushMatrix();
	glRotated(10.0*liczba,1,0,0);
	glTranslated(0,-b,-c);
	planeta(-100,460,370,15,15,0);
	glPopMatrix();
	glPushMatrix();
	glRotated(10.0*liczba,1,1,0);
	glTranslated(a,b,-c);
	planeta(-400,-50,190,13,13,0);
	glPopMatrix();
	glPushMatrix();
	glRotated(10.0*liczba,1,0,1);
	glTranslated(a,0,c);
	planeta(-20,10,-50,25,20,0);
	glPopMatrix();
	//planeta(0,0,-300,100,100,200,0);
	kula(4);

	glPushMatrix();
	glTranslated(0,0,-600);
	glRotated(liczba,0,-1,0);
	glTranslated(a,b,c);
	ksiezyc(7);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,0,-300);
	glRotated(liczba,0.1,0,0.1);
	ziemia(6);
	glPopMatrix();

	glPushMatrix();
	glTranslated(200,-200,400);
	glRotated(-liczba,0.1,0.1,0);
	mars(9);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-200,200,450);
	glRotated(5.0*liczba,0.1,0.1,0);
	saturn(11);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-400,-200,-400);
	glRotated(-6.0*liczba,0.1,0.1,0);
	neptun(10);
	glPopMatrix();
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	// Flush drawing commands
	glFlush();
	}


// Select the pixel format for a given device context
void SetDCPixelFormat(HDC hDC)
	{
	int nPixelFormat;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  // Size of this structure
		1,                                                              // Version of this structure    
		PFD_DRAW_TO_WINDOW |                    // Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |					// Support OpenGL calls in window
		PFD_DOUBLEBUFFER,                       // Double buffered
		PFD_TYPE_RGBA,                          // RGBA Color mode
		24,                                     // Want 24bit color 
		0,0,0,0,0,0,                            // Not used to select mode
		0,0,                                    // Not used to select mode
		0,0,0,0,0,                              // Not used to select mode
		32,                                     // Size of depth buffer
		0,                                      // Not used to select mode
		0,                                      // Not used to select mode
		PFD_MAIN_PLANE,                         // Draw in main plane
		0,                                      // Not used to select mode
		0,0,0 };                                // Not used to select mode

	// Choose a pixel format that best matches that described in pfd
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);

	// Set the pixel format for the device context
	SetPixelFormat(hDC, nPixelFormat, &pfd);
	}



// If necessary, creates a 3-3-2 palette for the device context listed.
HPALETTE GetOpenGLPalette(HDC hDC)
	{
	HPALETTE hRetPal = NULL;	// Handle to palette to be created
	PIXELFORMATDESCRIPTOR pfd;	// Pixel Format Descriptor
	LOGPALETTE *pPal;			// Pointer to memory for logical palette
	int nPixelFormat;			// Pixel format index
	int nColors;				// Number of entries in palette
	int i;						// Counting variable
	BYTE RedRange,GreenRange,BlueRange;
								// Range for each color entry (7,7,and 3)


	// Get the pixel format index and retrieve the pixel format description
	nPixelFormat = GetPixelFormat(hDC);
	DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Does this pixel format require a palette?  If not, do not create a
	// palette and just return NULL
	if(!(pfd.dwFlags & PFD_NEED_PALETTE))
		return NULL;

	// Number of entries in palette.  8 bits yeilds 256 entries
	nColors = 1 << pfd.cColorBits;	

	// Allocate space for a logical palette structure plus all the palette entries
	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) +nColors*sizeof(PALETTEENTRY));

	// Fill in palette header 
	pPal->palVersion = 0x300;		// Windows 3.0
	pPal->palNumEntries = nColors; // table size

	// Build mask of all 1's.  This creates a number represented by having
	// the low order x bits set, where x = pfd.cRedBits, pfd.cGreenBits, and
	// pfd.cBlueBits.  
	RedRange = (1 << pfd.cRedBits) -1;
	GreenRange = (1 << pfd.cGreenBits) - 1;
	BlueRange = (1 << pfd.cBlueBits) -1;

	// Loop through all the palette entries
	for(i = 0; i < nColors; i++)
		{
		// Fill in the 8-bit equivalents for each component
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double) pPal->palPalEntry[i].peRed * 255.0 / RedRange);

		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);

		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
		pPal->palPalEntry[i].peBlue = (unsigned char)(
			(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);

		pPal->palPalEntry[i].peFlags = (unsigned char) NULL;
		}
		

	// Create the palette
	hRetPal = CreatePalette(pPal);

	// Go ahead and select and realize the palette for this device context
	SelectPalette(hDC,hRetPal,FALSE);
	RealizePalette(hDC);

	// Free the memory used for the logical palette structure
	free(pPal);

	// Return the handle to the new palette
	return hRetPal;
	}


// Entry point of all Windows programs
int APIENTRY WinMain(   HINSTANCE       hInst,
						HINSTANCE       hPrevInstance,
						LPSTR           lpCmdLine,
						int                     nCmdShow)
	{
	MSG                     msg;            // Windows message structure
	WNDCLASS        wc;                     // Windows class structure
	HWND            hWnd;           // Storeage for window handle

	hInstance = hInst;

	// Register Window style
	wc.style                        = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc          = (WNDPROC) WndProc;
	wc.cbClsExtra           = 0;
	wc.cbWndExtra           = 0;
	wc.hInstance            = hInstance;
	wc.hIcon                        = NULL;
	wc.hCursor                      = LoadCursor(NULL, IDC_ARROW);
	
	// No need for background brush for OpenGL window
	wc.hbrBackground        = NULL;         
	
	wc.lpszMenuName         = MAKEINTRESOURCE(IDR_MENU);
	wc.lpszClassName        = lpszAppName;

	// Register the window class
	if(RegisterClass(&wc) == 0)
		return FALSE;


	// Create the main application window
	hWnd = CreateWindow(
				lpszAppName,
				lpszAppName,
				
				// OpenGL requires WS_CLIPCHILDREN and WS_CLIPSIBLINGS
				WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
	
				// Window position and size
				50, 50,
				400, 400,
				NULL,
				NULL,
				hInstance,
				NULL);

	// If window was not created, quit
	if(hWnd == NULL)
		return FALSE;

	SetTimer(hWnd,101,33,(TIMERPROC) NULL);

	// Display the window
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);

	// Process application messages until the application closes
	while( GetMessage(&msg, NULL, 0, 0))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}

	return msg.wParam;
	}




// Window procedure, handles all messages for this program
LRESULT CALLBACK WndProc(       HWND    hWnd,
							UINT    message,
							WPARAM  wParam,
							LPARAM  lParam)
	{
	static HGLRC hRC;               // Permenant Rendering context
	static HDC hDC;                 // Private GDI Device context

	switch (message)
		{
		// Window creation, setup for OpenGL
		case WM_CREATE:
			// Store the device context
			hDC = GetDC(hWnd);              

			// Select the pixel format
			SetDCPixelFormat(hDC);          

			// Create palette if needed
			hPalette = GetOpenGLPalette(hDC);

			// Create the rendering context and make it current
			hRC = wglCreateContext(hDC);
			wglMakeCurrent(hDC, hRC);
			SetupRC();
			glGenTextures(12, &texture[0]);                  // tworzy obiekt tekstury			
			
			// ³aduje pierwszy obraz tekstury:
			bitmapData = LoadBitmapFile("Bitmapy\\rock.bmp", &bitmapInfoHeader);
			
			glBindTexture(GL_TEXTURE_2D, texture[0]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);

			// ³aduje drugi obraz tekstury:
			bitmapData = LoadBitmapFile("Bitmapy\\sciana.bmp", &bitmapInfoHeader);
			glBindTexture(GL_TEXTURE_2D, texture[1]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);
			// trzeci obraz tekstury
			bitmapData = LoadBitmapFile("Bitmapy\\water.bmp", &bitmapInfoHeader);
			
			glBindTexture(GL_TEXTURE_2D, texture[2]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);

			// trzeci obraz tekstury
			bitmapData = LoadBitmapFile("Bitmapy\\metal2.bmp", &bitmapInfoHeader);
			
			glBindTexture(GL_TEXTURE_2D, texture[3]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			//if(bitmapData)
			//free(bitmapData);

			// pi¹ty obraz tekstury
			if(bitmapData)
			free(bitmapData);
			bitmapData = LoadBitmapFile("Bitmapy\\stars.bmp", &bitmapInfoHeader);
			glBindTexture(GL_TEXTURE_2D, texture[4]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);

			//szósty obraz tekstury
			bitmapData = LoadBitmapFile("Bitmapy\\fire.bmp", &bitmapInfoHeader);
			
			glBindTexture(GL_TEXTURE_2D, texture[5]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);
			
			
			// siódmy obraz tekstury
			bitmapData = LoadBitmapFile("Bitmapy\\earth.bmp", &bitmapInfoHeader);
			
			glBindTexture(GL_TEXTURE_2D, texture[6]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);

			// ósmy obraz tekstury
			bitmapData = LoadBitmapFile("Bitmapy\\moon.bmp", &bitmapInfoHeader);
			
			glBindTexture(GL_TEXTURE_2D, texture[7]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);

			// dziewi¹ty obraz tekstury
			bitmapData = LoadBitmapFile("Bitmapy\\engine.bmp", &bitmapInfoHeader);
			
			glBindTexture(GL_TEXTURE_2D, texture[8]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);

			// dziesi¹ty obraz tekstury
			bitmapData = LoadBitmapFile("Bitmapy\\mars.bmp", &bitmapInfoHeader);
			glBindTexture(GL_TEXTURE_2D, texture[9]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);

			//jedenasty obraz tekstury
			bitmapData = LoadBitmapFile("Bitmapy\\neptun.bmp", &bitmapInfoHeader);
			glBindTexture(GL_TEXTURE_2D, texture[10]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);

			//dwunasty obraz tekstury
			bitmapData = LoadBitmapFile("Bitmapy\\saturn.bmp", &bitmapInfoHeader);
			glBindTexture(GL_TEXTURE_2D, texture[11]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);
			// ustalenie sposobu mieszania tekstury z t³em
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
			break;

		// Window is being destroyed, cleanup
		case WM_DESTROY:
			// Deselect the current rendering context and delete it
			wglMakeCurrent(hDC,NULL);
			wglDeleteContext(hRC);

			// Delete the palette if it was created
			if(hPalette != NULL)
				DeleteObject(hPalette);

			// Tell the application to terminate after the window
			// is gone.
			PostQuitMessage(0);
			break;

		// Window is resized.
		case WM_SIZE:
			// Call our function which modifies the clipping
			// volume and viewport
			ChangeSize(LOWORD(lParam), HIWORD(lParam));
			break;


		// The painting function.  This message sent by Windows 
		// whenever the screen needs updating.
		case WM_PAINT:
			{
			// Call OpenGL drawing code

			RenderScene();

			SwapBuffers(hDC);

			// Validate the newly painted client area
			ValidateRect(hWnd,NULL);
			}
			break;

		// Windows is telling the application that it may modify
		// the system palette.  This message in essance asks the 
		// application for a new palette.
		case WM_QUERYNEWPALETTE:
			// If the palette was created.
			if(hPalette)
				{
				int nRet;

				// Selects the palette into the current device context
				SelectPalette(hDC, hPalette, FALSE);

				// Map entries from the currently selected palette to
				// the system palette.  The return value is the number 
				// of palette entries modified.
				nRet = RealizePalette(hDC);

				// Repaint, forces remap of palette in current window
				InvalidateRect(hWnd,NULL,FALSE);

				return nRet;
				}
			break;

	
		// This window may set the palette, even though it is not the 
		// currently active window.
		case WM_PALETTECHANGED:
			// Don't do anything if the palette does not exist, or if
			// this is the window that changed the palette.
			if((hPalette != NULL) && ((HWND)wParam != hWnd))
				{
				// Select the palette into the device context
				SelectPalette(hDC,hPalette,FALSE);

				// Map entries to system palette
				RealizePalette(hDC);
				
				// Remap the current colors to the newly realized palette
				UpdateColors(hDC);
				return 0;
				}
			break;


			case WM_TIMER:
				if(wParam == 101)
				{
					z--;
					if(z<=-100)
						z=-100;
					a+=1.0;				
					b+=0.5f;
					c+=0.5f;
					liczba+=0.1;
				}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		// Key press, check for arrow keys to do cube rotation.
		case WM_KEYDOWN:
			
			{
			if(wParam == VK_UP)
				
				xRot-= 5.0f;
				
			if(wParam == VK_DOWN)
				xRot += 5.0f;
				
			if(wParam == VK_LEFT)
				yRot -= 5.0f;
				
			if(wParam == VK_RIGHT)
				yRot += 5.0f;
				
			if(wParam == 0x57)
				y=y+3;

			if(wParam == 0x53)
				y=y-2;

			if(wParam == 0x41)
				x=x-2;

			if(wParam == 0x44)
				x=x+2;
				
			if(wParam == 0x45)
				z=z+2;
			if(wParam == 0x51)
				z=z-2;
			if(wParam == 0x5A)
				kierunek++;
			if(wParam == 0x58)
				kierunek--;
			if(wParam == 0x43)
				kierunek1++;
			if(wParam == 0x56)
				kierunek1--;
			if(wParam == 0x42)
				kierunek2++;
			if(wParam == VK_NUMPAD4)
				deltax+=20;
			if(wParam == VK_NUMPAD1)
				deltay-=20;
			if(wParam == VK_NUMPAD5)
				deltay+=20;
			if(wParam == VK_NUMPAD2)
				deltay-=20;
			if(wParam == VK_NUMPAD6)
				deltaz+=20;
			if(wParam == VK_NUMPAD3)
				deltaz-=20;
			//if(wParam == 0x51)
				//z=z-2;
			xRot = (const int)xRot % 360;
			yRot = (const int)yRot % 360;

			InvalidateRect(hWnd,NULL,FALSE);
			}
			break;

		// A menu command
		case WM_COMMAND:
			{
			switch(LOWORD(wParam))
				{
				// Exit the program
				case ID_FILE_EXIT:
					DestroyWindow(hWnd);
					break;

				// Display the about box
				case ID_HELP_ABOUT:
					DialogBox (hInstance,
						MAKEINTRESOURCE(IDD_DIALOG_ABOUT),
						hWnd,
						AboutDlgProc);
					break;
				}
			}
			break;


	default:   // Passes it on if unproccessed
	    return (DefWindowProc(hWnd, message, wParam, lParam));

	}

    return (0L);
	}




// Dialog procedure.
BOOL APIENTRY AboutDlgProc (HWND hDlg, UINT message, UINT wParam, LONG lParam)
	{
	
    switch (message)
	{
		// Initialize the dialog box
	    case WM_INITDIALOG:
			{
			int i;
			GLenum glError;

			// glGetString demo
			SetDlgItemText(hDlg,IDC_OPENGL_VENDOR,glGetString(GL_VENDOR));
			SetDlgItemText(hDlg,IDC_OPENGL_RENDERER,glGetString(GL_RENDERER));
			SetDlgItemText(hDlg,IDC_OPENGL_VERSION,glGetString(GL_VERSION));
			SetDlgItemText(hDlg,IDC_OPENGL_EXTENSIONS,glGetString(GL_EXTENSIONS));

			// gluGetString demo
			SetDlgItemText(hDlg,IDC_GLU_VERSION,gluGetString(GLU_VERSION));
			SetDlgItemText(hDlg,IDC_GLU_EXTENSIONS,gluGetString(GLU_EXTENSIONS));


			// Display any recent error messages
			i = 0;
			do {
				glError = glGetError();
				SetDlgItemText(hDlg,IDC_ERROR1+i,gluErrorString(glError));
				i++;
				}
			while(i < 6 && glError != GL_NO_ERROR);


			return (TRUE);
			}
			break;

		// Process command messages
	    case WM_COMMAND:      
			{
			// Validate and Make the changes
			if(LOWORD(wParam) == IDOK)
				EndDialog(hDlg,TRUE);
		    }
			break;

		// Closed from sysbox
		case WM_CLOSE:
			EndDialog(hDlg,TRUE);
			break;
		}

	return FALSE;
	}

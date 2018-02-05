#include<math.h>
#include"function_opengl.h"

#include<lua.hpp>

#define pi 3.1415926
#define ZERO 0.0000001

#define Max_plot 10000

/////////////////// control communications /////////////////
double CH1 = 0,CH1_MAX = 30,CH1_MIN = -30,CH1_STEP = 0.01;
double CH2 = 0,CH2_MAX = 30,CH2_MIN = -30,CH2_STEP = 0.001;

///////////////////  function definations /////////////////
//
lua_State *L;
double getDouble(char funcname[]);
int setDouble(char funcname[],double x);
//

double buffer_draw2 = 0;
double plot_y_max = 0;
double plot_x_max = 0;
double datalog[Max_plot];

///////////////////  functions  ///////////////////////////
int function_exit()
{
	// lua function exit()
	lua_settop(L,0);
	lua_getglobal(L,"exit"); // stack 1 is the function
	if (lua_pcall(L,0,0,0) != 0)    // one para, one return
		{printf("call exit func fail %s\n",lua_tostring(L,-1)); return -1;}

	return 0;
}

int function_init()
{
	L = luaL_newstate();
	luaL_openlibs(L);
	if ((luaL_loadfile(L,"../src/mainloop.lua")) || (lua_pcall(L,0,0,0)))
		{printf("open lua file fail : %s\n",lua_tostring(L,-1));return -1;}

	// lua function init()
	lua_settop(L,0);
	lua_getglobal(L,"init"); // stack 1 is the function
	if (lua_pcall(L,0,0,0) != 0)    // one para, one return
		{printf("call init func fail %s\n",lua_tostring(L,-1)); return -1;}


	return 0;
}

int function_step()
{
	// lua function step()
	setDouble("setW",CH1);
	setDouble("setV",CH2);

	lua_settop(L,0);
	lua_getglobal(L,"step"); // stack 1 is the function
	if (lua_pcall(L,0,0,0) != 0)    // one para, one return
		{printf("call step func fail %s\n",lua_tostring(L,-1)); return -1;}

	return 0;
}

double getDouble(char funcname[])
{
	lua_settop(L,0);
	lua_getglobal(L,funcname); // stack 1 is the function
	if (lua_pcall(L,0,1,0) != 0)    // one para, one return
		{printf("call getDouble func %s fail %s\n",funcname,lua_tostring(L,-1)); return -1;}

	double res;
	res = lua_tonumber(L,1);
	return res;
}

int setDouble(char funcname[],double x)
{
	lua_settop(L,0);
	lua_getglobal(L,funcname); // stack 1 is the function
	lua_pushnumber(L,x);
	if (lua_pcall(L,1,0,0) != 0)    // one para, one return
		{printf("call getDouble func %s fail %s\n",funcname,lua_tostring(L,-1)); return -1;}

	return 0;
}

////////////////////////// draw ///////////////////
int function_draw()
{
	double x,y,z,dx,dy,dz,ux,uy,uz;
	x = getDouble("getLX");
	y = getDouble("getLY");
	z = getDouble("getLZ");

	dx = getDouble("getDX");
	dy = getDouble("getDY");
	dz = getDouble("getDZ");

	ux = getDouble("getUX");
	uy = getDouble("getUY");
	uz = getDouble("getUZ");
	
	drawSphere(x,y,z,0.02);
	drawCylinder(0.01, 0.01, 0.1,	//base top height
				 x,y,z,
				 dx,dy,dz
			);
	drawCylinder(0.01, 0.01, 0.1,	//base top height
				 x,y,z,
				 ux,uy,uz
			);

	return 0;
}

int function_draw2()
{
	/*
	for (int i = 1; i <= herd.time; i++)
	{
		if (herd.time < plot_x_max)
		{
		glBegin(GL_LINES);
			glVertex3f( (i-1)/plot_x_max,	datalog[i-1]/plot_y_max,0.0f);
			glVertex3f(  i/plot_x_max,		datalog[i] / plot_y_max,0.0f);
		glEnd();
		}
		else
		{
		glBegin(GL_LINES);
			glVertex3f( 1.0*(i-1)/herd.time,	datalog[i-1]/plot_y_max,0.0f);
			glVertex3f( 1.0* i/herd.time,		datalog[i] / plot_y_max,0.0f);
		glEnd();
		}
	}
	*/
		
	return 0;
}


////////////////////////////// drawings  /////////////////////////
int drawSphere(double x, double y, double z, double r)
{
	glTranslatef(x,y,z);
	glutSolidSphere(r,10,10);
	glTranslatef(-x,-y,-z);

	return 0;
}

int drawCube(double half, double x, double y, double z, 
						  double ex,double ey,double ez)
{
	double xaxis,yaxis,zaxis,angleaxis;
	double xbase,ybase,zbase;
	double e;

	int rotateflag = 1;

	if (((ex-0)*(ex-0)<ZERO) && ((ey-0)*(ey-0)<ZERO) && ((ez-1)*(ez-1)<ZERO))
		rotateflag = 0;

	if (rotateflag == 1)
	{
		e = sqrt(ex * ex + ey * ey + ez * ez);
		if (e == 0) return -1;

		xbase = 0; ybase = 0; zbase = 1;
		xaxis = ybase * ez - zbase * ey;
		yaxis = zbase * ex - xbase * ez;
		zaxis = xbase * ey - ybase * ex;
		angleaxis = acos((xbase*ex+ybase*ey+zbase*ez)/e) + pi;

		//printf("%lf %lf %lf %lf\n",angleaxis,xaxis,yaxis,zaxis);
	}

	glTranslatef(x,y,z);
	if (rotateflag == 1)
		glRotatef(angleaxis*180/pi,xaxis,yaxis,zaxis);
	glutSolidCube(half);
	if (rotateflag == 1)
		glRotatef(-angleaxis*180/pi,xaxis,yaxis,zaxis);
	glTranslatef(-x,-y,-z);

	return 0;
}

int drawCylinder(	double base, double top, double height,
				double lx,	double ly, double lz,
				double ex,	double ey, double ez
			)
{
	double xaxis,yaxis,zaxis,angleaxis;
	double xbase,ybase,zbase;
	double e;
	int rotateflag = 1;
	GLUquadricObj *quadratic;

	quadratic = gluNewQuadric();

	//printf("l: %lf %lf %lf\n",lx,ly,lz);
	//printf("e: %lf %lf %lf\n",ex,ey,ez);

	if (((ex-0)*(ex-0)<ZERO) && ((ey-0)*(ey-0)<ZERO) && ((ez-1)*(ez-1)<ZERO))
		rotateflag = 0;

	if (rotateflag == 1)
	{
		e = sqrt(ex * ex + ey * ey + ez * ez);
		if (e == 0) return -1;

		xbase = 0; ybase = 0; zbase = 1;
		xaxis = ybase * ez - zbase * ey;
		yaxis = zbase * ex - xbase * ez;
		zaxis = xbase * ey - ybase * ex;
		//angleaxis = acos((xbase*ex+ybase*ey+zbase*ez)/e) + pi;
		angleaxis = acos((xbase*ex+ybase*ey+zbase*ez)/e);

		//printf("%lf %lf %lf %lf\n",angleaxis,xaxis,yaxis,zaxis);

	}

	glTranslatef(lx,ly,lz);

	if (rotateflag == 1)
		glRotatef(angleaxis*180/pi,xaxis,yaxis,zaxis);

	gluCylinder(quadratic,base,top,height,32,32);//»­Ô²Öù	base top height
	if (rotateflag == 1)
		glRotatef(-angleaxis*180/pi,xaxis,yaxis,zaxis);

	glTranslatef(-lx,-ly,-lz);
	return 0;
}

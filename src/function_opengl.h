//#define mac
#ifdef mac
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif

/////////////  function include  /////////////
extern double CH1,CH1_MAX,CH1_MIN,CH1_STEP;
extern double CH2,CH2_MAX,CH2_MIN,CH2_STEP;

///////////////////  drawings /////////////////
int drawSphere(double x, double y, double z, double r);
int drawCube(double half, double x, double y, double z,
						  double ex,double ey,double ez);

int drawCylinder(	double base, double top, double height,
				double lx,	double ly, double lz,
				double ex,	double ey, double ez
			);

/////////////////// functions //////////////////
int function_init();
int function_draw();
int function_draw2();
int function_step();
int function_exit();

#include <windows.h> // use proper includes for your system
#include <math.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/Glut.h>
const int screenWidth = 400;	   // width of the screen window in pixels 
const int screenHeight = 400;	   // height of the screen window in pixels
#define PI 3.141592
#define TWOPI 2*3.141592

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);       // the background color is white
	glColor3f(0.0f, 0.0f, 0.0f);         // the drawing color is black 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, 1.0, 1.0, 10.0);

}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen 
	gluLookAt(2.0, 5.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	double u = 0;
	double v = 0;
	int N = 50;
	glBegin(GL_POINTS);
	for (u = 0; u <= 2 * PI; u += 2 * PI / double(N))
	{
		for (v = 0; v <= N; v++)
		{
			glVertex3f(v / double(N) * cos(u), 3 * v / double(N), v / double(N) * sin(u));
		}
	}
	glEnd();
	glFlush();		   // send all output to display 
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set the display mode
	glutInitWindowSize(screenWidth, screenHeight); // set the window size
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 150); // set the window position on screen
	glutCreateWindow("Dot Plot of a Function"); // open the screen window
	glutDisplayFunc(myDisplay);     // register the redraw function
	myInit();
	glutMainLoop(); 		     // go into a perpetual loop
}
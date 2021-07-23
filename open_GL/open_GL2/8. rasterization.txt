#include <cstdlib>
#include <GL/glut.h>

void pickPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

int round(float z)
{
    int y;
    y = z > 0.0 ? int(z + 0.5) : int(z - 0.5);
    return y;
}

void DDA(int i1, int j1, int i2, int j2) // Assume i2 > i1.
{
    float y = j1;
    float m = float(j2 - j1) / (i2 - i1); // Assume -1 <= m <= 1.
    for (int x = i1; x <= i2; x++)
    {
        pickPixel(x, round(y));
        y += m;
    }
}

void drawScene(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);

    DDA(100, 100, 300, 200);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA.cpp");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(drawScene);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glutMainLoop();

    return 0;
}
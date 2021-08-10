
#include<windows.h>
#include<GL/glu.h>
#include<GL/glut.h>

GLfloat T = 0;

void Spin()     //rotation initialization
{
    T = T + 0.1;
    if(T>360)
        T = 0;
    glutPostRedisplay();
}

void Draw()
{
    GLfloat Pos[] = {0,1,0,1};   //position of the light source x,y,z,distant light
    GLfloat Col[] = {1,0.2,0.2,1};   // color of light

    GLfloat M[] = {0,1,0,1};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glLightfv(GL_LIGHT0,GL_POSITION,Pos);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,Col);


    gluLookAt(0,1,3,0,0,0,0,1,0); //camera function value pos look origin tilt

    glRotatef(T,0,1,0);       //rotate in respect to y-axis

    glPushMatrix();
        glScalef(1,0.05,1);
        glutSolidCube(1);    //1 cube for table top
    glPopMatrix();

     glPushMatrix();
        glTranslatef(-0.45,-0.5,-0.45);
        glScalef(0.05,1,0.05);
        glutSolidCube(1);      //2 cube for leg
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.45,-0.5,-0.45);
        glScalef(0.05,1,0.05);
        glutSolidCube(1);    //cube3/leg2
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.45,-0.5,0.45);
        glScalef(0.05,1,0.05);
        glutSolidCube(1);     //cube4/leg3
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.45,-0.5,0.45);
        glScalef(0.05,1,0.05);
        glutSolidCube(1);       //cube5/leg4
    glPopMatrix();

    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,M);
        glPushMatrix();
            glTranslatef(0,0.25,0); //place teapot on table
            glutSolidTeapot(0.25);
        glPopMatrix();
    glPopAttrib();

    glutSwapBuffers();
}

void MyInit()
{
    glEnable(GL_DEPTH_TEST);    //enable z buffer

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1,-1,1,2,10); //left,right,bottom,top,near&far plane
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);      //light source 4 shading property
}

int main(int argC,char *argV[])
{
    glutInit(&argC,argV);    // initializes the FreeGLUT library

    glutInitWindowSize(600,600);      //set window size
    glutInitWindowPosition(100,100);     //set window position
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Table & TeaPot");
    MyInit();
    glutDisplayFunc(Draw);              //// Tell GLUT to use the method "display" for rendering
    glutIdleFunc(Spin);   //rotation

    glutMainLoop();
    return 0;
}

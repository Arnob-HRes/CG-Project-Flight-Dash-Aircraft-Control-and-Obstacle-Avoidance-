#include <windows.h>
#include<fstream>
#include <GL/glut.h>
#include <cmath>

float PI = 3.14159265f;
void idle() {
 glutPostRedisplay();
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius)
{
    int triangleAmount = 40;
    GLfloat twicePi = 2.0f * PI;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for(int i = 0; i <= triangleAmount; i++)
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),
                       y + (radius * sin(i * twicePi / triangleAmount)));
    glEnd();
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int lineAmount = 100;

	GLfloat twicePi = 2.0f * PI;
	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++)
        {
			glVertex2f( x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount)));
		}
	glEnd();
}

void BackGround()
{
    glBegin(GL_QUADS);
        glColor3ub(240, 234, 223);
        glVertex2f(0.0f,70.0f);
        glVertex2f(0.0f,540.0f);
        glVertex2f(-500.0f,540.0f);
        glVertex2f(-500.0f,70.0f);
    glEnd();
    glColor3ub(192, 187, 178);
    drawFilledCircle(-320.0f,335.0f,50);
    drawFilledCircle(-455,435,10);
    drawFilledCircle(-355,435,10);
    drawFilledCircle(-455,235,10);
    drawFilledCircle(-355,235,10);
    glBegin(GL_QUADS);
        glColor3ub(192, 187, 178);

        glVertex2f(-455.0f,435.0f);
        glVertex2f(-455.0f,425.0f);
        glVertex2f(-355.0f,425.0f);
        glVertex2f(-355.0f,435.0f);

        glVertex2f(-455.0f,235.0f);
        glVertex2f(-455.0f,225.0f);
        glVertex2f(-355.0f,225.0f);
        glVertex2f(-355.0f,235.0f);

        glVertex2f(-250.0f,285.0f);
        glVertex2f(-250.0f,385.0f);
        glVertex2f(-325.0f,385.0f);
        glVertex2f(-325.0f,285.0f);

        glVertex2f(-73.0f,145.0f);
        glVertex2f(-73.0f,520.0f);
        glVertex2f(-230.0f,520.0f);
        glVertex2f(-230.0f,145.0f);

        glColor3ub(116, 184, 47);
        glVertex2f(-460.0f,230.0f);
        glVertex2f(-360.0f,230.0f);
        glVertex2f(-360.0f,250.0f);
        glVertex2f(-460.0f,250.0f);

        glVertex2f(-460.0f,430.0f);
        glVertex2f(-360.0f,430.0f);
        glVertex2f(-360.0f,450.0f);
        glVertex2f(-460.0f,450.0f);
    glEnd();

    glColor3ub(116, 184, 47);
    drawFilledCircle(-460,440,10);
    drawFilledCircle(-360,440,10);
    drawFilledCircle(-460,240,10);
    drawFilledCircle(-360,240,10);
    glLineWidth(4.0f);
    glColor3ub(0,0,0);
    drawFilledCircle(0,0,150);
    glLineWidth(4.0f);
    glColor3ub(255,255,255);
    drawHollowCircle(0,0,138);
    glColor3ub(199, 227, 225);
    drawFilledCircle(-330.0f,345.0f,50);

    glBegin(GL_QUADS);
        glColor3ub(0,0,0);
        glVertex2f(-70.0f, 540.0f);
        glVertex2f(-70.0f, -540.0f);
        glVertex2f(70.0f, -540.0f);
        glVertex2f(70.0f, 540.0f);

        glColor3ub(0,0,0);
        glVertex2f(-960.0f, 70.0f);
        glVertex2f(-960.0f, -70.0f);
        glVertex2f(960.0f, -70.0f);
        glVertex2f(960.0f, 70.0f);

    glEnd();

    glLineWidth(4.0f);
    glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex2f(-60.0f,540.0f);
        glVertex2f(-60.0f,70.0f);

        glVertex2f(60.0f,540.0f);
        glVertex2f(60.0f,70.0f);

        glVertex2f(-960.0f,60.0f);
        glVertex2f(-70.0f,60.0f);

        glVertex2f(-960.0f,-60.0f);
        glVertex2f(-70.0f,-60.0f);

        glVertex2f(960.0f,60.0f);
        glVertex2f(70.0f,60.0f);

        glVertex2f(960.0f,-60.0f);
        glVertex2f(70.0f,-60.0f);

        glVertex2f(-60.0f,-540.0f);
        glVertex2f(-60.0f,-70.0f);

        glVertex2f(60.0f,-540.0f);
        glVertex2f(60.0f,-70.0f);

    glEnd();

    glLineWidth(4.0f);
    glColor3ub(0,0,0);
    drawFilledCircle(0,0,135);

    glLineWidth(4.0f);
    glColor3ub(255,255,255);
    drawHollowCircle(0,0,80);

    glLineWidth(4.0f);
    glColor3ub(116, 184, 47);
    drawFilledCircle(0,0,65);

    glLineWidth(11.0f);
    glBegin(GL_LINES);
        glColor3ub(255,255,255);
        //top
        glVertex2f(0,500);
        glVertex2f(0,450);

        glVertex2f(0,400);
        glVertex2f(0,350);

        glVertex2f(0,300);
        glVertex2f(0,250);

        //cross
        glVertex2f(0,200);
        glVertex2f(0,150);

        glVertex2f(-20,200);
        glVertex2f(-20,150);

        glVertex2f(-40,200);
        glVertex2f(-40,150);

        glVertex2f(20,200);
        glVertex2f(20,150);

        glVertex2f(40,200);
        glVertex2f(40,150);

        //Left

        glVertex2f(-910,0);
        glVertex2f(-860,0);

        glVertex2f(-810,0);
        glVertex2f(-760,0);

        glVertex2f(-710,0);
        glVertex2f(-660,0);

        glVertex2f(-610,0);
        glVertex2f(-560,0);

        glVertex2f(-510,0);
        glVertex2f(-460,0);

        glVertex2f(-410,0);
        glVertex2f(-360,0);

        glVertex2f(-310,0);
        glVertex2f(-260,0);

        //cross
        glVertex2f(-210,0);
        glVertex2f(-160,0);

        glVertex2f(-210,-20);
        glVertex2f(-160,-20);

        glVertex2f(-210,-40);
        glVertex2f(-160,-40);

        glVertex2f(-210,20);
        glVertex2f(-160,20);

        glVertex2f(-210,40);
        glVertex2f(-160,40);

        //bottom

        glVertex2f(0,-500);
        glVertex2f(0,-450);

        glVertex2f(0,-400);
        glVertex2f(0,-350);

        glVertex2f(0,-300);
        glVertex2f(0,-250);

        //cross
        glVertex2f(0,-200);
        glVertex2f(0,-150);

        glVertex2f(-20,-200);
        glVertex2f(-20,-150);

        glVertex2f(-40,-200);
        glVertex2f(-40,-150);

        glVertex2f(20,-200);
        glVertex2f(20,-150);

        glVertex2f(40,-200);
        glVertex2f(40,-150);

        //right

        glVertex2f(910,0);
        glVertex2f(860,0);

        glVertex2f(810,0);
        glVertex2f(760,0);

        glVertex2f(710,0);
        glVertex2f(660,0);

        glVertex2f(610,0);
        glVertex2f(560,0);

        glVertex2f(510,0);
        glVertex2f(460,0);

        glVertex2f(410,0);
        glVertex2f(360,0);

        glVertex2f(310,0);
        glVertex2f(260,0);

        //cross
        glVertex2f(210,0);
        glVertex2f(160,0);

        glVertex2f(210,-20);
        glVertex2f(160,-20);

        glVertex2f(210,-40);
        glVertex2f(160,-40);

        glVertex2f(210,20);
        glVertex2f(160,20);

        glVertex2f(210,40);
        glVertex2f(160,40);

    glEnd();

    //Buildings
    glBegin(GL_QUADS);
        glColor3ub(255,255,255);
        glVertex2f(-80.0f,160.0f);
        glVertex2f(-80.0f,530.0f);
        glVertex2f(-250.0f,530.0f);
        glVertex2f(-250.0f,160.0f);

        glColor3ub(195, 195, 195);
        glVertex2f(-100.0f,180.0f);
        glVertex2f(-100.0f,510.0f);
        glVertex2f(-230.0f,510.0f);
        glVertex2f(-230.0f,180.0f);

        glColor3ub(255,255,255);
        glVertex2f(-250.0f,295.0f);
        glVertex2f(-250.0f,395.0f);
        glVertex2f(-325.0f,395.0f);
        glVertex2f(-325.0f,295.0f);

        glColor3ub(199, 227, 225);
        glVertex2f(-130.0f,200.0f);
        glVertex2f(-130.0f,230.0f);
        glVertex2f(-200.0f,230.0f);
        glVertex2f(-200.0f,200.0f);

        glVertex2f(-130.0f,280.0f);
        glVertex2f(-130.0f,310.0f);
        glVertex2f(-200.0f,310.0f);
        glVertex2f(-200.0f,280.0f);

        glVertex2f(-130.0f,360.0f);
        glVertex2f(-130.0f,390.0f);
        glVertex2f(-200.0f,390.0f);
        glVertex2f(-200.0f,360.0f);

        glVertex2f(-130.0f,440.0f);
        glVertex2f(-130.0f,470.0f);
        glVertex2f(-200.0f,470.0f);
        glVertex2f(-200.0f,440.0f);

        glColor3ub(255,255,255);
        glVertex2f(-410.0f,284.0f);
        glVertex2f(-410.0f,405.0f);
        glVertex2f(-460.0f,405.0f);
        glVertex2f(-460.0f,284.0f);

        glColor3ub(0, 255, 255);
        glVertex2f(-420.0f,294.0f);
        glVertex2f(-420.0f,395.0f);
        glVertex2f(-450.0f,395.0f);
        glVertex2f(-450.0f,294.0f);

        glColor3ub(255,255,255);
        glVertex2f(-400.0f,315.0f);
        glVertex2f(-400.0f,375.0f);
        glVertex2f(-470.0f,375.0f);
        glVertex2f(-470.0f,315.0f);

        glColor3ub(0, 255, 255);
        glVertex2f(-405.0f,320.0f);
        glVertex2f(-405.0f,370.0f);
        glVertex2f(-465.0f,370.0f);
        glVertex2f(-465.0f,320.0f);

    glEnd();

    glColor3ub(255,255,255);
    drawFilledCircle(-325.0f,345.0f,50);
    glColor3ub(199, 227, 225);
    drawFilledCircle(-325.0f,345.0f,45);

    glLineWidth(4.0f);
    glBegin(GL_POINTS);
        glColor3ub(0,0,0);
        glVertex2f(-260.0f,390.0f);
        glVertex2f(-260.0f,380.0f);
        glVertex2f(-260.0f,370.0f);

        glVertex2f(-260.0f,320.0f);
        glVertex2f(-260.0f,310.0f);
        glVertex2f(-260.0f,300.0f);
    glEnd();

    glColor3ub(255,255,255);
    drawFilledCircle(-325.0f,345.0f,20);
    glColor3ub(0,0,0);
    drawFilledCircle(-325.0f,345.0f,7);
    glColor3ub(255,255,0);
    drawFilledCircle(-325.0f,345.0f,4);

    glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex2f(-310.0f,345.0f);
        glVertex2f(-280.0f,345.0f);

        glVertex2f(-340.0f,345.0f);
        glVertex2f(-370.0f,345.0f);

        glVertex2f(-325.0f,355.0f);
        glVertex2f(-325.0f,390.0f);

        glVertex2f(-325.0f,335.0f);
        glVertex2f(-325.0f,300.0f);
    glEnd();


}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    BackGround();

    glutSwapBuffers();
}

void MyInit()
{
    glClearColor(0.455f, 0.722f, 0.184f, 1.0f); //Grass Color Background
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-960, 960, -540, 540);
}

void reshape(GLsizei width, GLsizei height)
{
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-960, 960, -540, 540);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int startMainGame(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Flight Dash");
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    MyInit();
    glutDisplayFunc(display);
    glutMainLoop();
}

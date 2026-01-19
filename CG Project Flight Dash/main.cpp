#include<iostream>
#include<string.h>
#include <cmath>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <GL/glut.h>
#include <mysql.h>
#include <sstream>
using namespace std;

bool inStartScreen = true;
bool musicPaused = false;

float btnUpX1 = -40, btnUpX2 = 40, btnUpY1 = -200, btnUpY2 = -140;
float btnDownX1 = -40, btnDownX2 = 40, btnDownY1 = -320, btnDownY2 = -260;
float btnLeftX1 = -120, btnLeftX2 = -60, btnLeftY1 = -260, btnLeftY2 = -200;
float btnRightX1 = 60, btnRightX2 = 120, btnRightY1 = -260, btnRightY2 = -200;

const int MAX_COINS = 20;
float coinX[MAX_COINS];
float coinY[MAX_COINS];
float coinSpeed[MAX_COINS];
bool  coinActive[MAX_COINS];


const int MAX_BOMBS = 17;

float bombX[MAX_BOMBS];
float bombY[MAX_BOMBS];
float bombSpeed[MAX_BOMBS];
bool  bombActive[MAX_BOMBS];

bool gameOver = false;

int score,level=1,cscore=0,life=3;
string user;
float flightX=-800.0f, flightY=0.0f;
float speed1 = 2.0f,speed2 = 3.0f,speed3 = 4.0f,speed4 = 2.0f,speed5 = 1.0f;
float cloudPosition = 960.9f, cloudPosition2 = 960.9f, cloudPosition3 = 960.9f, cloudPosition4 = 960.9f, cloudPosition5 = 960.9f;
float shipposition1=960.9f,shipposition2=-960.9f;
float sspeed=3.0f;
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

void drawArrowButtons()
{
    // Button color
    glColor3f(0.25f, 0.25f, 0.25f);

    // UP box
    glBegin(GL_QUADS);
    glVertex2f(-40, -300);
    glVertex2f(40, -300);
    glVertex2f(40, -240);
    glVertex2f(-40, -240);
    glEnd();

    // DOWN box
    glBegin(GL_QUADS);
    glVertex2f(-40, -420);
    glVertex2f(40, -420);
    glVertex2f(40, -360);
    glVertex2f(-40, -360);
    glEnd();

    // LEFT box
    glBegin(GL_QUADS);
    glVertex2f(-120, -360);
    glVertex2f(-60, -360);
    glVertex2f(-60, -300);
    glVertex2f(-120, -300);
    glEnd();

    // RIGHT box
    glBegin(GL_QUADS);
    glVertex2f(60, -360);
    glVertex2f(120, -360);
    glVertex2f(120, -300);
    glVertex2f(60, -300);
    glEnd();

    // Arrow symbols (lighter color)
    glColor3f(0.9f, 0.9f, 0.9f);

    // UP arrow
    glBegin(GL_TRIANGLES);
    glVertex2f(0, -250);
    glVertex2f(-15, -280);
    glVertex2f(15, -280);
    glEnd();

    // DOWN arrow
    glBegin(GL_TRIANGLES);
    glVertex2f(0, -410);
    glVertex2f(-15, -380);
    glVertex2f(15, -380);
    glEnd();

    // LEFT arrow
    glBegin(GL_TRIANGLES);
    glVertex2f(-110, -330);
    glVertex2f(-80, -315);
    glVertex2f(-80, -345);
    glEnd();

    // RIGHT arrow
    glBegin(GL_TRIANGLES);
    glVertex2f(110, -330);
    glVertex2f(80, -315);
    glVertex2f(80, -345);
    glEnd();
}




void BuildindOneAndRoad()
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
        glVertex2f(-70.0f, 0.0f);
        glVertex2f(70.0f, 0.0f);
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
void BuildingTwo(){

    //Shadow
    glBegin(GL_QUADS);
    glColor3ub(104, 166, 42);

    glVertex2f(-650.0f,80.0f);
    glVertex2f(-650.0f,450.0f);
    glVertex2f(-770.0f,450.0f);
    glVertex2f(-770.0f,80.0f);

    glVertex2f(-670.0f,230.0f);
    glVertex2f(-510.0f,230.0f);
    glVertex2f(-510.0f,380.0f);
    glVertex2f(-670.0f,380.0f);

    glEnd();

    glBegin(GL_QUADS);

    //White Part

    glColor3ub(255,255,255);

    glVertex2f(-670.0f,90.0f);
    glVertex2f(-670.0f,250.0f);
    glVertex2f(-830.0f,350.0f);
    glVertex2f(-830.0f,150.0f);

    glVertex2f(-670.0f,250.0f);
    glVertex2f(-520.0f,250.0f);
    glVertex2f(-580.0f,350.0f);
    glVertex2f(-830.0f,350.0f);

    glVertex2f(-670.0f,90.0f);
    glVertex2f(-830.0f,150.0f);
    glVertex2f(-950.0f,150.0f);
    glVertex2f(-790.0f,90.0f);

    glVertex2f(-520.0f,250.0f);
    glVertex2f(-520.0f,400.0f);
    glVertex2f(-580.0f,530.0f);
    glVertex2f(-580.0f,350.0f);

    //Glass Part

    glColor3ub(199, 227, 225);

    glVertex2f(-680.0f,100.0f);
    glVertex2f(-680.0f,250.0f);
    glVertex2f(-820.0f,340.0f);
    glVertex2f(-820.0f,155.0f);

    glVertex2f(-670.0f,260.0f);
    glVertex2f(-530.0f,260.0f);
    glVertex2f(-583.0f,340.0f);
    glVertex2f(-800.0f,340.0f);

    glVertex2f(-695.0f,95.0f);
    glVertex2f(-825.0f,140.0f);
    glVertex2f(-935.0f,145.0f);
    glVertex2f(-790.0f,95.0f);

    glVertex2f(-525.0f,265.0f);
    glVertex2f(-525.0f,390.0f);
    glVertex2f(-575.0f,505.0f);
    glVertex2f(-570.0f,345.0f);

    glEnd();

    //Roof

    glBegin(GL_QUADS);

    glColor3ub(255,255,255);

    //white
    glVertex2f(-950,150);
    glVertex2f(-830,150);
    glVertex2f(-830,530);
    glVertex2f(-950,530);

    glVertex2f(-830,350);
    glVertex2f(-580,350);
    glVertex2f(-580,530);
    glVertex2f(-830,530);

    //gray
    glColor3ub(211, 211, 211);
    glVertex2f(-940,160);
    glVertex2f(-840,160);
    glVertex2f(-840,520);
    glVertex2f(-940,520);
stringstream ss;
    glVertex2f(-840,360);
    glVertex2f(-590,360);
    glVertex2f(-590,520);
    glVertex2f(-840,520);

    glEnd();

    //roof details

    glBegin(GL_QUADS);



    glEnd();

    //window
    glLineWidth(3.0f);
    glBegin(GL_LINES);

    glColor3ub(255,255,255);

    glVertex2f(-680.0f,120.0f);
    glVertex2f(-840.0f,195.0f);

    glVertex2f(-680.0f,150.0f);
    glVertex2f(-840.0f,225.0f);

    glVertex2f(-680.0f,180.0f);
    glVertex2f(-840.0f,255.0f);

    glVertex2f(-680.0f,210.0f);
    glVertex2f(-840.0f,285.0f);

    glVertex2f(-680.0f,235.0f);
    glVertex2f(-840.0f,325.0f);

    //
    glVertex2f(-780.0f,130.0f);
    glVertex2f(-785.0f,330.0f);

    glVertex2f(-740.0f,115.0f);
    glVertex2f(-745.0f,300.0f);

    glVertex2f(-700.0f,100.0f);
    glVertex2f(-705.0f,270.0f);
    //

    glVertex2f(-640.0f,255.0f);
    glVertex2f(-775.0f,350.0f);

    glVertex2f(-610.0f,255.0f);
    glVertex2f(-725.0f,350.0f);

    glVertex2f(-580.0f,255.0f);
    glVertex2f(-680.0f,350.0f);

    glVertex2f(-550.0f,255.0f);
    glVertex2f(-635.0f,350.0f);

    //
    glVertex2f(-775.0f,320.0f);
    glVertex2f(-560.0f,320.0f);

    glVertex2f(-745.0f,290.0f);
    glVertex2f(-545.0f,290.0f);

    glVertex2f(-700.0f,270.0f);
    glVertex2f(-530.0f,270.0f);
    //

    glVertex2f(-720.0f,93.0f);
    glVertex2f(-885.0f,150.0f);

    glVertex2f(-760.0f,93.0f);
    glVertex2f(-925.0f,150.0f);

    //
    glVertex2f(-907.0f,135.0f);
    glVertex2f(-790.0f,130.0f);

    glVertex2f(-868.0f,120.0f);
    glVertex2f(-740.0f,115.0f);

    glVertex2f(-827.0f,105.0f);
    glVertex2f(-690.0f,100.0f);

    //

    glVertex2f(-523.0f,285.0f);
    glVertex2f(-575.0f,370.0f);

    glVertex2f(-523.0f,315.0f);
    glVertex2f(-575.0f,420.0f);

    glVertex2f(-523.0f,355.0f);
    glVertex2f(-575.0f,460.0f);

    //
    glVertex2f(-560.0f,320.0f);
    glVertex2f(-565.0f,485.0f);

    glVertex2f(-545.0f,290.0f);
    glVertex2f(-550.0f,450.0f);

    glVertex2f(-530.0f,270.0f);
    glVertex2f(-535.0f,425.0f);
    //

    glEnd();

    //fountain shadow

    glColor3ub(104, 166, 42);
    drawFilledCircle(-570.0f,150.0f,60);

    //fountain

    glColor3ub(255,255,255);
    drawFilledCircle(-580.0f,160.0f,60);

    glColor3ub(64, 164, 223);
    drawFilledCircle(-580.0f,160.0f,50);

    glColor3ub(255,255,255);
    drawHollowCircle(-580.0f,160.0f,42);

    glColor3ub(255,255,255);
    drawFilledCircle(-580.0f,160.0f,20);

    glColor3ub(64, 164, 223);
    drawFilledCircle(-580.0f,160.0f,10);

    glColor3ub(255,255,255);
    drawFilledCircle(-580.0f,160.0f,5);

}

void FootballField(){

    //Ground

    glBegin(GL_QUADS);

    glColor3ub(194, 178, 128);

    glVertex2f(130.0f,130.0f);
    glVertex2f(870.0f,130.0f);
    glVertex2f(870.0f,490.0f);
    glVertex2f(130.0f,490.0f);

    glEnd();

    //Football field
    glBegin(GL_QUADS);

    glColor3ub(34, 139, 34);
    glVertex2f(170.0f,170.0f);
    glVertex2f(230.0f,170.0f);
    glVertex2f(230.0f,450.0f);
    glVertex2f(170.0f,450.0f);

    glColor3ub(85, 170, 85);
    glVertex2f(230.0f,170.0f);
    glVertex2f(290.0f,170.0f);
    glVertex2f(290.0f,450.0f);
    glVertex2f(230.0f,450.0f);

    glColor3ub(34, 139, 34);
    glVertex2f(290.0f,170.0f);
    glVertex2f(350.0f,170.0f);
    glVertex2f(350.0f,450.0f);
    glVertex2f(290.0f,450.0f);

    glColor3ub(85, 170, 85);
    glVertex2f(350.0f,170.0f);
    glVertex2f(410.0f,170.0f);
    glVertex2f(410.0f,450.0f);
    glVertex2f(350.0f,450.0f);

    glColor3ub(34, 139, 34);
    glVertex2f(410.0f,170.0f);
    glVertex2f(470.0f,170.0f);
    glVertex2f(470.0f,450.0f);
    glVertex2f(410.0f,450.0f);

    glColor3ub(85, 170, 85);
    glVertex2f(470.0f,170.0f);
    glVertex2f(530.0f,170.0f);
    glVertex2f(530.0f,450.0f);
    glVertex2f(470.0f,450.0f);

    glColor3ub(34, 139, 34);
    glVertex2f(530.0f,170.0f);
    glVertex2f(590.0f,170.0f);
    glVertex2f(590.0f,450.0f);
    glVertex2f(530.0f,450.0f);

    glColor3ub(85, 170, 85);
    glVertex2f(590.0f,170.0f);
    glVertex2f(650.0f,170.0f);
    glVertex2f(650.0f,450.0f);
    glVertex2f(590.0f,450.0f);

    glColor3ub(34, 139, 34);
    glVertex2f(650.0f,170.0f);
    glVertex2f(710.0f,170.0f);
    glVertex2f(710.0f,450.0f);
    glVertex2f(650.0f,450.0f);

    glColor3ub(85, 170, 85);
    glVertex2f(710.0f,170.0f);
    glVertex2f(770.0f,170.0f);
    glVertex2f(770.0f,450.0f);
    glVertex2f(710.0f,450.0f);

    glColor3ub(34, 139, 34);
    glVertex2f(770.0f,170.0f);
    glVertex2f(830.0f,170.0f);
    glVertex2f(830.0f,450.0f);
    glVertex2f(770.0f,450.0f);

    glEnd();

    //lines

    glLineWidth(3.0f);
    glBegin(GL_LINES);

    glColor3ub(255,255,255);
    glVertex2f(180.0f,180.0f);
    glVertex2f(820.0f,180.0f);

    glVertex2f(820.0f,180.0f);
    glVertex2f(820.0f,440.0f);

    glVertex2f(820.0f,440.0f);
    glVertex2f(180.0f,440.0f);

    glVertex2f(180.0f,440.0f);
    glVertex2f(180.0f,180.0f);

    glVertex2f(500.0f,180.0f);
    glVertex2f(500.0f,440.0f);

    //left big line

    glVertex2f(180.0f,220.0f);
    glVertex2f(260.0f,220.0f);

    glVertex2f(260.0f,220.0f);
    glVertex2f(260.0f,400.0f);

    glVertex2f(260.0f,400.0f);
    glVertex2f(180.0f,400.0f);

    //left small line

    glVertex2f(180.0f,260.0f);
    glVertex2f(220.0f,260.0f);

    glVertex2f(220.0f,260.0f);
    glVertex2f(220.0f,360.0f);

    glVertex2f(220.0f,360.0f);
    glVertex2f(180.0f,360.0f);

    //Right big line

    glVertex2f(820.0f,220.0f);
    glVertex2f(740.0f,220.0f);

    glVertex2f(740.0f,220.0f);
    glVertex2f(740.0f,400.0f);

    glVertex2f(740.0f,400.0f);
    glVertex2f(820.0f,400.0f);

    //Right small line

    glVertex2f(820.0f,260.0f);
    glVertex2f(780.0f,260.0f);

    glVertex2f(780.0f,260.0f);
    glVertex2f(780.0f,360.0f);

    glVertex2f(780.0f,360.0f);
    glVertex2f(820.0f,360.0f);

    glEnd();

    //rings

    glColor3ub(255,255,255);
    drawHollowCircle(500.0f,310.0f,60);
}
void drawSmallShip(float centerX, float centerY) {
    glColor3ub(50, 50, 60);
    glBegin(GL_POLYGON);
        glVertex2f(centerX - 90, centerY);
        glVertex2f(centerX - 70, centerY + 25);
        glVertex2f(centerX + 70, centerY + 25);
        glVertex2f(centerX + 90, centerY);
        glVertex2f(centerX + 80, centerY - 35);
        glVertex2f(centerX - 80, centerY - 35);
    glEnd();

    glColor3ub(180, 20, 20);
    glBegin(GL_QUADS);
        glVertex2f(centerX - 80, centerY - 5);
        glVertex2f(centerX + 80, centerY - 5);
        glVertex2f(centerX + 80, centerY + 10);
        glVertex2f(centerX - 80, centerY + 10);
    glEnd();

    glColor3ub(220, 220, 230);
    glBegin(GL_QUADS);
        glVertex2f(centerX - 30, centerY + 25);
        glVertex2f(centerX + 30, centerY + 25);
        glVertex2f(centerX + 25, centerY + 50);
        glVertex2f(centerX - 25, centerY + 50);
    glEnd();

    glColor3ub(40, 120, 180);
    glBegin(GL_QUADS);
        glVertex2f(centerX - 12, centerY + 50);
        glVertex2f(centerX + 12, centerY + 50);
        glVertex2f(centerX + 12, centerY + 70);
        glVertex2f(centerX - 12, centerY + 70);
    glEnd();
}
void Beach()
{
    glColor3ub(234,182,79);
    glBegin(GL_QUADS);
        glVertex2f(-960.0f,0.0f);
        glVertex2f(-960.0f,-540.0f);
        glVertex2f(960.0f,-540.0f);
        glVertex2f(960.0f,0.0f);
    glEnd();
    glColor3ub(69, 212, 248);
    glBegin(GL_QUADS);
        glVertex2f(-960.0f,-300.0f);
        glVertex2f(-960.0f,-540.0f);
        glVertex2f(960.0f,-540.0f);
        glVertex2f(960.0f,-300.0f);
    glEnd();
    drawFilledCircle(-690,-480,200);
    drawFilledCircle(-670,-470,200);
    drawFilledCircle(-720,-470,200);
    drawFilledCircle(-820,-470,200);
    drawFilledCircle(-920,-470,200);
    drawFilledCircle(-620,-470,200);
    drawFilledCircle(-580,-470,200);
    drawFilledCircle(-500,-470,200);
    drawFilledCircle(-450,-440,200);
    drawFilledCircle(-400,-470,200);
    drawFilledCircle(-350,-470,200);
    drawFilledCircle(-250,-470,200);
    drawFilledCircle(-150,-470,200);
    drawFilledCircle(-50,-400,150);
    drawFilledCircle(100,-470,200);
    drawFilledCircle(200,-470,200);
    drawFilledCircle(350,-470,220);
    drawFilledCircle(450,-470,200);
    drawFilledCircle(600,-440,200);
    drawFilledCircle(700,-470,200);
    drawFilledCircle(800,-470,200);
    drawFilledCircle(900,-440,200);

    drawSmallShip(shipposition1, -350);
    drawSmallShip(shipposition2, -450);

    glColor3ub(60, 180, 80);
    glBegin(GL_QUADS);
        glVertex2f(-900.0f,-80.0f);
        glVertex2f(-900.0f,-110.0f);
        glVertex2f(-800.0f,-110.0f);
        glVertex2f(-800.0f,-80.0f);

        glVertex2f(-700.0f,-80.0f);
        glVertex2f(-700.0f,-110.0f);
        glVertex2f(-600.0f,-110.0f);
        glVertex2f(-600.0f,-80.0f);

        glVertex2f(-500.0f,-80.0f);
        glVertex2f(-500.0f,-110.0f);
        glVertex2f(-400.0f,-110.0f);
        glVertex2f(-400.0f,-80.0f);

        glVertex2f(-300.0f,-80.0f);
        glVertex2f(-300.0f,-110.0f);
        glVertex2f(-200.0f,-110.0f);
        glVertex2f(-200.0f,-80.0f);

        glVertex2f(200.0f,-80.0f);
        glVertex2f(200.0f,-110.0f);
        glVertex2f(300.0f,-110.0f);
        glVertex2f(300.0f,-80.0f);

        glVertex2f(400.0f,-80.0f);
        glVertex2f(400.0f,-110.0f);
        glVertex2f(500.0f,-110.0f);
        glVertex2f(500.0f,-80.0f);

        glVertex2f(600.0f,-80.0f);
        glVertex2f(600.0f,-110.0f);
        glVertex2f(700.0f,-110.0f);
        glVertex2f(700.0f,-80.0f);

        glVertex2f(800.0f,-80.0f);
        glVertex2f(800.0f,-110.0f);
        glVertex2f(900.0f,-110.0f);
        glVertex2f(900.0f,-80.0f);
    glEnd();
}

void drawCoin(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1.0f);

    glColor3ub(255, 191, 0);
    drawFilledCircle(0, 0, 14);

    glColor3ub(255, 215, 0);
    drawFilledCircle(0, 0, 11);

    glColor3ub(218, 165, 32);
    drawHollowCircle(0, 0, 11);

    glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
    drawFilledCircle(-4, 4, 3);

    glPopMatrix();
}
void drawBomb(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1.0f);

    glColor3ub(30, 30, 30);
    drawFilledCircle(0, 0, 14);

    glColor3ub(80, 80, 80);
    drawFilledCircle(-4, 4, 4);

    glColor3ub(200, 200, 200);
    glBegin(GL_LINES);
        glVertex2f(0, 14);
        glVertex2f(6, 22);
    glEnd();

    glColor3ub(255, 80, 0);
    drawFilledCircle(6, 22, 3);

    glPopMatrix();
}
void initCoins()
{
    for (int i = 0; i < MAX_COINS; i++)
        coinActive[i] = false;
}
void initBombs()
{
    for (int i = 0; i < MAX_BOMBS; i++)
        bombActive[i] = false;
}
void spawnCoin()
{
    for (int i = 0; i < MAX_COINS; i++)
    {
        if (!coinActive[i])
        {
            coinX[i] = 980.0f;
            coinY[i] = -400 + rand() % 800;
            coinSpeed[i] = 5.0f + rand() % 3;
            coinActive[i] = true;
            break;
        }
    }
}
void spawnBomb()
{
    for (int i = 0; i < MAX_BOMBS; i++)
    {
        if (!bombActive[i])
        {
            bombX[i] = 980.0f;
            bombY[i] = -400 + rand() % 800;
            bombSpeed[i] = 9.0f;
            bombActive[i] = true;
            break;
        }
    }
}
void renderTextBig(float x, float y, float scale, const char* text)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3ub(255,255,255);

    for (int i = 0; text[i] != '\0'; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, text[i]);
    }

    glPopMatrix();
}

void topblur(float x, float y, float z, float w){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(x,y,z,w);
    glBegin(GL_QUADS);
    glVertex2f(-960.0f,-540.0f);
    glVertex2f(960.0f,-540.0f);
    glVertex2f(960.0f,540.0f);
    glVertex2f(-960.0f,540.0f);
    glEnd();
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
void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}
void FighterPlaneTopView(float x, float y, float scale, float angle)
{
    glPushMatrix();

    glTranslatef(x, y, 0.0f);
    glRotatef(angle, 0, 0, 1);
    glScalef(scale, scale, 1.0f);

    glBegin(GL_POLYGON);
    glColor3ub(120,120,120);
    glVertex2f(0, 120);
    glVertex2f(15, 60);
    glVertex2f(15, -80);
    glVertex2f(-15, -80);
    glVertex2f(-15, 60);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(90,90,90);

    glVertex2f(-15, 30);
    glVertex2f(-120, -10);
    glVertex2f(-15, -40);

    glVertex2f(15, 30);
    glVertex2f(120, -10);
    glVertex2f(15, -40);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(80,80,80);

    glVertex2f(-15, -60);
    glVertex2f(-60, -90);
    glVertex2f(-15, -90);

    glVertex2f(15, -60);
    glVertex2f(60, -90);
    glVertex2f(15, -90);
    glEnd();

    glColor3ub(0,180,220);
    drawFilledCircle(0, 40, 12);

    glPopMatrix();
}
void checkCoinCollisionWithPlane()
{
    const float planeRadius = 75.0f;
    const float coinRadius  = 14.0f;

    for (int i = 0; i < MAX_COINS; i++)
    {
        if (!coinActive[i])
        {
            continue;
        }
        float dx = flightX - coinX[i];
        float dy = flightY - coinY[i];
        float distSq = dx * dx + dy * dy;
        float radiusSum = planeRadius + coinRadius;
        if (distSq <= radiusSum * radiusSum)
        {
            coinActive[i] = false;
            cscore ++;
            PlaySound("A:\\Documents\\FALL 2025-2026\\COMPUTER GRAPHICS J\\CG Project Flight Dash\\CG Project Flight Dash\\CG Project Flight Dash\\resource\\coin-recieved-230517.wav", NULL, SND_FILENAME | SND_ASYNC);
        }
    }
}
void checkBombCollisionWithPlane()
{
    const float planeRadius = 75.0f;
    const float bombRadius  = 14.0f;

    for (int i = 0; i < MAX_BOMBS; i++)
    {
        if (!bombActive[i])
        {
            continue;
        }
        float dx = flightX - bombX[i];
        float dy = flightY - bombY[i];
        float distSq = dx * dx + dy * dy;
        float radiusSum = planeRadius + bombRadius;
        if (distSq <= radiusSum * radiusSum)
        {
            bombActive[i] = false;
            life--;
            PlaySound("A:\\Documents\\FALL 2025-2026\\COMPUTER GRAPHICS J\\CG Project Flight Dash\\CG Project Flight Dash\\CG Project Flight Dash\\resource\\explosion-fx-343683.wav", NULL, SND_FILENAME | SND_ASYNC);
            if (life <= 0)
            {
                life = 0;
                gameOver = true;
            }
            return;
        }
    }
}
void BackGround(){

    Beach();
    BuildindOneAndRoad();
    BuildingTwo();
    FootballField();
    topblur(0.78f, 0.83f, 0.88f, 0.45f);
    glColor3ub(255,255,255);
    drawCircle(cloudPosition-10.0f, 200.0f, 60.0f);
    drawCircle(cloudPosition, 220.0f, 50.0f);
    drawCircle(cloudPosition + 15.0f, 180.0f, 40.0f);
    drawCircle(cloudPosition + 10.0f, 210.0f, 40.0f);
    drawCircle(cloudPosition + 50.0f, 200.0f, 40.0f);

    drawCircle(cloudPosition2-50.0f, 400.0f, 30.0f);
    drawCircle(cloudPosition2, 420.0f, 50.0f);
    drawCircle(cloudPosition2 + 15.0f, 380.0f, 40.0f);
    drawCircle(cloudPosition2 + 50.0f, 400.0f, 40.0f);

    drawCircle(cloudPosition3-10.0f, -190.0f, 50.0f);
    drawCircle(cloudPosition3, -210.0f, 50.0f);
    drawCircle(cloudPosition3 + 15.0f, -180.0f, 50.0f);
    drawCircle(cloudPosition3 + 10.0f, -210.0f, 40.0f);
    drawCircle(cloudPosition3 + 50.0f, -200.0f, 60.0f);

    drawCircle(cloudPosition4-50.0f, -350.0f, 30.0f);
    drawCircle(cloudPosition4, -370.0f, 50.0f);
    drawCircle(cloudPosition4 + 15.0f, -330.0f, 40.0f);
    drawCircle(cloudPosition4 + 50.0f, -350.0f, 40.0f);

    drawCircle(cloudPosition5-50.0f, 0.0f, 30.0f);
    drawCircle(cloudPosition5, -20.0f, 50.0f);
    drawCircle(cloudPosition5 + 15.0f, -60.0f, 40.0f);
    drawCircle(cloudPosition5 + 50.0f, -20.0f, 40.0f);
    FighterPlaneTopView(flightX, flightY, 1.0f, -90.0f);
    for (int i = 0; i < MAX_COINS; i++)
    {
        if (coinActive[i])
            drawCoin(coinX[i], coinY[i], 1.5f);
    }

    for (int i = 0; i < MAX_BOMBS; i++)
    {
        if (bombActive[i])
            drawBomb(bombX[i], bombY[i], 1.4f);
    }

    std::stringstream ss;
    std::stringstream ss2;
    std::stringstream ss3;
    std::stringstream ss4;
    std::stringstream ss5;
    std::stringstream ss6;
    std::stringstream ss7;
    std::stringstream ss8;
    std::stringstream ss9;

    if(cscore>5){
        level=2;
    }
    if(cscore>10){
        level=3;
    }
    if(cscore>15){
        level=4;
    }
    if(cscore>20){
        level=5;
    }
    if(cscore>25){
        level=6;
    }
    if(score>cscore){
        ss << "Your highest score is: " <<score;
        renderTextBig(-940, -520, 0.15f, ss.str().c_str());
    }
    else{
        ss << "You highest score is: " <<cscore;
        renderTextBig(-940, -520, 0.15f, ss.str().c_str());
    }

    ss2 << "Current score: "<<cscore;
    renderTextBig(-940, -490, 0.18f, ss2.str().c_str());

    ss3 << "LEVEL:"<<level;
    renderTextBig(-120, 490, 0.35f, ss3.str().c_str());

    ss9 << "Life Left:"<<life;
    renderTextBig(-930, 490, 0.30f, ss9.str().c_str());

    ss4 << "(A/Left arrow) -> Go Left";
    renderTextBig(440, -430, 0.18f, ss4.str().c_str());

    ss5 << "(D/Right arrow) -> Go Right";
    renderTextBig(440, -460, 0.18f, ss5.str().c_str());

    ss6 << "(W/Up arrow) -> Go UP";
    renderTextBig(440, -490, 0.18f, ss6.str().c_str());

    ss7 << "(S/Down arrow) -> Go Down";
    renderTextBig(440, -520, 0.18f, ss7.str().c_str());

    drawArrowButtons();

    if (gameOver)
    {
        glColor3ub(255,255,255);
        glBegin(GL_QUADS);
        glVertex2f(-880,280);
        glVertex2f(-880,-380);
        glVertex2f(880,-380);
        glVertex2f(880,280);
        glEnd();
        glColor3ub(60, 180, 80);
        glBegin(GL_QUADS);
        glVertex2f(-850,250);
        glVertex2f(-850,-350);
        glVertex2f(850,-350);
        glVertex2f(850,250);
        glEnd();
        renderTextBig(-440, 100, 1.0f, "GAME OVER");
        renderTextBig(-550, -60, 0.7f, "Press ESC to Exit");
        ss8<<"Your highest score is: "<<cscore;
        renderTextBig(-750, -300, 0.6f, ss8.str().c_str());
        if(cscore>score){
            MYSQL* conn;
            conn=mysql_init(0);
            conn=mysql_real_connect(conn, "127.0.0.1", "root","","flight_dash",0,NULL,0);
            int q2=0;
            stringstream ssscore;
            ssscore<<"UPDATE user SET score = '"<<cscore<<"' WHERE username = '"<<user<<"'";
            string query2=ssscore.str();
            const char* qq2=query2.c_str();
            q2=mysql_query(conn, qq2);
        }
    }
}
void playmainmusic(const string& path)
{
    PlaySound(path.c_str(), NULL, SND_FILENAME|SND_ASYNC|SND_LOOP);
}
void displayStartScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    BackGround();
    float btnX = -200;
    float btnY = -100;
    float btnW = 400;
    float btnH = 200;
    glColor3ub(60, 180, 80);
    glBegin(GL_QUADS);
    glVertex2f(btnX,btnY);
    glVertex2f(btnX + btnW, btnY);
    glVertex2f(btnX + btnW, btnY + btnH);
    glVertex2f(btnX,btnY + btnH);
    glEnd();
    glColor3ub(255, 255, 255);
    renderTextBig(btnX + 30, btnY + 55, 0.70f, "START");
    glLineWidth(8.0f);
    glColor3ub(255, 255, 255);
    glBegin(GL_LINE_LOOP);
    glVertex2f(btnX,       btnY);
    glVertex2f(btnX + btnW, btnY);
    glVertex2f(btnX + btnW, btnY + btnH);
    glVertex2f(btnX,       btnY + btnH);
    glEnd();

    glutSwapBuffers();
}
void display() {
    if (inStartScreen) {
        displayStartScreen();
    }
    else {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        BackGround();
        glutSwapBuffers();
    }
}
void update(int value){
    if (inStartScreen) {
        glutTimerFunc(16, update, 0);
        glutPostRedisplay();
        return;
    }
    if (gameOver)
    {
        glutPostRedisplay();
        glutTimerFunc(16, update, 0);
        return;
    }
    cloudPosition -= speed1;
    cloudPosition2 -= speed2;
    cloudPosition3 -= speed3;
    cloudPosition4 -= speed4;
    cloudPosition5 -= speed5;
    shipposition1 -= sspeed;
    shipposition2 += sspeed;
    if (cloudPosition < -980.9f) {
        cloudPosition = 960.9f;
    }
    if (cloudPosition2 < -980.9f) {
        cloudPosition2 = 960.9f;
    }
    if (cloudPosition3 < -980.9f) {
        cloudPosition3 = 960.9f;
    }
    if (cloudPosition4 < -980.9f) {
        cloudPosition4 = 960.9f;
    }
    if (cloudPosition5 < -980.9f) {
        cloudPosition5 = 960.9f;
    }
    if (shipposition1 < -980.9f) {
        shipposition1 = 960.9f;
    }
    if (shipposition2 > 980.9f) {
        shipposition2 = -960.9f;
    }
    if(flightX < -860.0f){
        flightX=-860.0f;
    }
    if(flightX > 840.0f){
        flightX=840.0f;
    }
    if(flightY > 400.0f){
        flightY=400.0f;
    }
    if(flightY < -400.0f){
        flightY=-400.0f;
    }

    if (rand() % 120 == 0){
        spawnCoin();
    }

    for (int i = 0; i < MAX_COINS; i++)
    {
        if (coinActive[i])
        {
            coinX[i] -= coinSpeed[i];

            if (coinX[i] < -980.0f){
                coinActive[i] = false;
            }
        }
    }
    for (int i = 0; i < MAX_BOMBS; i++)
    {
        if (bombActive[i])
        {
            bombX[i] -= bombSpeed[i];

            if (bombX[i] < -980.0f)
                bombActive[i] = false;
        }
    }

    if (rand() % 260 == 0)
    {
        spawnBomb();
    }
    for (int i = 0; i < MAX_COINS; i++)
    {
        if (coinActive[i])
        {
            coinX[i] -= coinSpeed[i];

            if (coinX[i] < -980.0f)
                coinActive[i] = false;
        }
    }

    if(level==1){
        for (int i = 0; i < MAX_COINS; i++)
        {
            if (coinActive[i])
            {
                coinSpeed[i] = 5.0f;
            }
        }
        for (int i = 0; i < MAX_BOMBS; i++)
        {
            if (bombActive[i])
            {
                bombSpeed[i] = 11.0f;
            }
        }

    }
    if(level==2){
        for (int i = 0; i < MAX_COINS; i++)
        {
            if (coinActive[i])
            {
                coinSpeed[i] = 4.7f;
            }
        }
        for (int i = 0; i < MAX_BOMBS; i++)
        {
            if (bombActive[i])
            {
                bombSpeed[i] = 15.0f;
            }
        }

    }
    if(level==3){
        for (int i = 0; i < MAX_COINS; i++)
        {
            if (coinActive[i])
            {
                coinSpeed[i] = 4.3f;
            }
        }
        for (int i = 0; i < MAX_BOMBS; i++)
        {
            if (bombActive[i])
            {
                bombSpeed[i] = 18.0f;
            }
        }

    }
    if(level==4){
        for (int i = 0; i < MAX_COINS; i++)
        {
            if (coinActive[i])
            {
                coinSpeed[i] = 4.1f;
            }
        }
        for (int i = 0; i < MAX_BOMBS; i++)
        {
            if (bombActive[i])
            {
                bombSpeed[i] = 20.0f;
            }
        }

    }
    if(level==5){
        for (int i = 0; i < MAX_COINS; i++)
        {
            if (coinActive[i])
            {
                coinSpeed[i] = 3.0f;
            }
        }
        for (int i = 0; i < MAX_BOMBS; i++)
        {
            if (bombActive[i])
            {
                bombSpeed[i] = 25.0f;
            }
        }

    }
    checkCoinCollisionWithPlane();
    checkBombCollisionWithPlane();
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}
void MyInit()
{
    glClearColor(0.455f, 0.722f, 0.184f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-960, 960, -540, 540);
}
void handleKeypress(unsigned char key, int x, int y) {
        switch (key) {
    case 'a':
        flightX -= 10.0f;
        break;
    case 'A':
        flightX -= 10.0f;
        break;
    case 'w':
        flightY += 10.0f;
        break;
    case 'W':
        flightY += 10.0f;
        break;
    case 's':
        flightY -= 10.0f;
        break;
    case 'S':
        flightY -= 10.0f;
        break;
    case 'd':
        flightX += 10.0f;
        break;
    case 'D':
        flightX += 10.0f;
        break;
    case 27:
        exit(0);
        break;
    glutPostRedisplay();
	}
}
void handleSpecialKeypress(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
            flightX -= 10.0f;
            break;

        case GLUT_KEY_RIGHT:
            flightX += 10.0f;
            break;

        case GLUT_KEY_UP:
            flightY += 10.0f;
            break;

        case GLUT_KEY_DOWN:
            flightY -= 10.0f;
            break;
    }

    glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
    if (state != GLUT_DOWN){
        return;
    }

    float mx = (x / (float)glutGet(GLUT_WINDOW_WIDTH)) * 1920 - 960;
    float my = 540 - (y / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 1080;

    if (inStartScreen)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            if (mx >= -220 && mx <= 220 && my >= -80 && my <= 80)
            {
                inStartScreen = false;
                PlaySound(NULL, NULL, 0);
                musicPaused = true;
                glutPostRedisplay();
            }
        }
        return;
    }
    if (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON)
    {
        if (mx >= -40 && mx <= 40 && my >= -300 && my <= -240){
            flightY += 15;
        }
        else if (mx >= -40 && mx <= 40 && my >= -420 && my <= -360){
            flightY -= 15;
        }
        else if (mx >= -120 && mx <= -60 && my >= -360 && my <= -300){
            flightX -= 15;
        }
        else if (mx >= 60 && mx <= 120 && my >= -360 && my <= -300){
            flightX += 15;
        }
        else
        {
            if (button == GLUT_LEFT_BUTTON)
            {
                speed1 += 1.0f;
                speed2 += 1.0f;
                speed3 += 1.0f;
                speed4 += 1.0f;
                speed5 += 1.0f;
            }
            else if (button == GLUT_RIGHT_BUTTON)
            {
                speed1 -= 1.0f;
                speed2 -= 1.0f;
                speed3 -= 1.0f;
                speed4 -= 1.0f;
                speed5 -= 1.0f;
            }
        }

        glutPostRedisplay();
    }
}
void handleKeyStartScreen(unsigned char key, int x, int y) {
    if (inStartScreen) {
        if (key == 13 || key == 10) {
            inStartScreen = false;
            musicPaused = true;
            glutPostRedisplay();
        }
        else if (key == 27) {
            exit(0);
        }
    }
    else {
        handleKeypress(key, x, y);
    }
}
void setScoreandUser(int S, string s){
    score=S;
    user=s;
}
int startMainGame(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Flight Dash");
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    MyInit();
    if (inStartScreen) {
        playmainmusic("A:/Documents/FALL 2025-2026/COMPUTER GRAPHICS J/CG Project Flight Dash/CG Project Flight Dash/CG Project Flight Dash/resource/edm-gaming-music-335408.wav");
    }
    glutKeyboardFunc(handleKeyStartScreen);
    glutSpecialFunc(handleSpecialKeypress);
    glutMouseFunc(mouse);
    initCoins();
    initBombs();
    glutMainLoop();
    return 0;
}



void LOGIN_PAGE();
void Registration();
void showGameDescription();

int main(){
    int key;
    char C;
    bool A=true;
    cout<<"\t\t\t\t\t|-----------------FLIGHT DASH-----------------|\n\t\t\t\t\t|                                             |\n";
    cout<<"\t\t\t\t\t|     WELCOME TO A 2D FLIGHT SIMULATING GAME  |\n\t\t\t\t\t|                                             |\n";
    cout<<"\t\t\t\t\t|------------------HOME PAGE------------------|\n\n\n\n";
    cout<<"________________________________________________________________________________________________________________________\n\n";
    cout<<"\t\t\t\t\t    GO TO LOGIN PAGE             PRESS [1]\n\n";
    cout<<"\t\t\t\t\t    GO TO REGISTRATION PAGE      PRESS [2]\n\n";
    cout<<"\t\t\t\t\t    GO TO GAME INFORMATION PAGE  PRESS [3]\n\n";
    cout<<"\t\t\t\t\t    EXIT                         PRESS [0]\n\n";
    cout<<"________________________________________________________________________________________________________________________\n\n";
    cout<<" WHAT IS YOUR CHOOISE: ";
    cin>>key;
    switch(key){
        case 1:
            LOGIN_PAGE();
            break;
        case 2:
            Registration();
            break;
        case 3:
            showGameDescription();
            break;
        case 0:
            break;
        default:
            cout<<" INVALIDE INPUT. PRESS 1/2/3/0 TO CONTINUE\n";
            while(A){
                    cout<<" DO YOU WANT TO CONTINUE [y/n]: ";
                    cin>>C;
                    switch(C){
                        case 'y':
                            system("cls");
                            main();
                        case 'n':
                            A=false;
                            break;
                        default:
                            cout<<" INVALIDE INPUT. TRY AGAIN [y/n]\n";
                    }
            }
    }

}

void showGameDescription() {
    string dc;
    system("cls");
    cout << "================ FLIGHT DASH =================\n";
    cout << "Flight Dash is a 2D arcade-style flying game.\n\n";

    cout << "Gameplay Mechanics:\n";
    cout << "- Control a fighter plane in 2D space.\n";
    cout << "- Collect coins to increase score.\n";
    cout << "- Avoid bombs; collision reduces your lives.\n";
    cout << "- You start with 3 lives.\n\n";

    cout << "Levels and Difficulty:\n";
    cout << "- 6 levels in total, each progressively harder.\n";
    cout << "- Higher levels: faster bombs, slower coins.\n";
    cout << "- Reach score thresholds to advance levels.\n\n";

    cout << "Scoring:\n";
    cout << "- Each coin increases score by 1.\n";
    cout << "- Highest score is tracked.\n\n";

    cout << "Controls:\n";
    cout << "- Keyboard: W/Up Arrow = Up, S/Down Arrow = Down, A/Left Arrow = Left, D/Right Arrow = Right\n";
    cout << "- On-Screen Arrows: Click arrows to move the plane.\n\n";

    cout << "Collision Detection:\n";
    cout << "- Coins: increases score\n";
    cout << "- Bombs: reduces life and triggers effect\n\n";

    cout << "Visuals:\n";
    cout << "- Buildings, roads, football fields, beaches, ships, clouds\n";
    cout << "- Smooth animations for environment\n\n";

    cout << "Audio:\n";
    cout << "- Sound effects for coins and bomb collisions\n\n";

    cout << "==============================================\n";

    cout<<" Want to go to Home Page [Y]: ";
    cin>>dc;
    if(dc=="Y" || dc =="y"){
        system("cls");
        main();
    }
    }

void LOGIN_PAGE(){
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn=mysql_init(0);
    conn=mysql_real_connect(conn, "127.0.0.1", "root","","flight_dash",0,NULL,0);
    string USER,PASS, user;
    int score;
    bool Validity=false;
    system("cls");
    cout<<"\t\t\t\t\t|-----------------FLIGHT DASH-----------------|\n\t\t\t\t\t|                                             |\n";
    cout<<"\t\t\t\t\t|     WELCOME TO A 2D FLIGHT SIMULATING GAME  |\n\t\t\t\t\t|                                             |\n";
    cout<<"\t\t\t\t\t|------------------LOGIN PAGE-----------------|\n\n\n\n";
    cout<<"\t\t\t\t_______________________________________________________________\n\n";
    cout<<"\t\t\t\t                   USERNAME: ";
    cin>>USER;
    cout<<"\t\t\t\t                   PASSWORD: ";
    cin>>PASS;

    if(conn){
        int qstate=mysql_query(conn, "SELECT username,password,score FROM user");

        if(!qstate){
            res=mysql_store_result(conn);

            while(row=mysql_fetch_row(res)){
                if(USER==row[0] && PASS==row[1]){
                    score=atoi(row[2]);
                    Validity=true;
                }
            }
        }
    }

    if(Validity){
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        cout<<"\n\t\t\t\t                   Login Successful!\n";
        cout<<"\n\t\t\t\t                   USER: "<<USER<<"\n\n";
        cout<<"\n\t\t\t\t      Highest score of the user: "<<score<<" Points\n\n";
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        system("pause");
        system("cls");
        cout<<"\t\t\t\t\t|-----------------FLIGHT DASH-----------------|\n\t\t\t\t\t|                                             |\n";
        cout<<"\t\t\t\t\t|     WELCOME TO A 2D FLIGHT SIMULATING GAME  |\n\t\t\t\t\t|                                             |\n";
        cout<<"\t\t\t\t\t|----------------LAUNCHING GAME---------------|\n\n\n\n";
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        cout<<"\t\t\t\t                Launching Flight Dash...\n\n";
        char a=221;
        cout<<"\t\t\t\t       Loading: ";
        for(int i=0;i<=30;i++){
            cout<<a;
            Sleep(100+i+i);
        }
        cout<<"\n\n\t\t\t\t                 100% Loading Successful\n\n";
        cout<<"\t\t\t\t_______________________________________________________________\n\n\n\n\t\t\t\t";
        system("pause");
        setScoreandUser(score, USER);
        startMainGame(__argc, __argv);
    }
    else{
        system("cls");
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        cout<<"\t\t\t\t[Unsuccessful Login [Invalid username or password ["<<USER<<"] ]\n\n";
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        main();
    }

}

void Registration(){
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn=mysql_init(0);
    conn=mysql_real_connect(conn, "127.0.0.1", "root","","flight_dash",0,NULL,0);
    string USER, PASS;
    bool Validity = false;
    int score=0,q=0;
    stringstream ss;

    system("cls");
    cout<<"\t\t\t\t\t|-----------------FLIGHT DASH-----------------|\n\t\t\t\t\t|                                             |\n";
    cout<<"\t\t\t\t\t|     WELCOME TO A 2D FLIGHT SIMULATING GAME  |\n\t\t\t\t\t|                                             |\n";
    cout<<"\t\t\t\t\t|---------------REGISTRATION PAGE-------------|\n\n\n\n";
    cout<<"\t\t\t\t_______________________________________________________________\n\n";
    cout<<"\t\t\t\t                   USERNAME: ";
    cin>>USER;
    cout<<"\t\t\t\t                   PASSWORD: ";
    cin>>PASS;
    cout<<"\t\t\t\t_______________________________________________________________\n\n";

    if(conn){
        int qstate=mysql_query(conn, "SELECT username FROM user");

        if(!qstate){
            res=mysql_store_result(conn);

            while(row=mysql_fetch_row(res)){
                if(USER==row[0]){
                    Validity=true;
                }
            }
        }
    }
    if(Validity){
        system("cls");
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        cout<<"\t\t\t\t   User [ "<<USER<<"] already registered! Please Login\n\n";
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        main();
    }
    else{
        ss<<"INSERT INTO user(username, password, score) values('"<<USER<<"','"<<PASS<<"','"<<score<<"')";

    string query=ss.str();
    const char* qq=query.c_str();
    q=mysql_query(conn, qq);
    system("cls");
    cout << "\nUser [" << USER << "] successfully registered!\n\n";
    main();
    }
}


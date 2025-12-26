#include <windows.h>
#include <GL/glut.h>
#include <cmath>

float PI = 3.14159265f;

/* ================= CIRCLE ================= */
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

/* ================= ROADS ================= */
void drawRoad(float x1, float y1, float x2, float y2)
{
    glColor3f(0.35f, 0.35f, 0.35f); // dark gray
    glBegin(GL_QUADS);
        glVertex2f(x1, y1); glVertex2f(x2, y1);
        glVertex2f(x2, y2); glVertex2f(x1, y2);
    glEnd();
}

/* ================= DASHED CENTER LINE ================= */
void drawDashedCenter(bool horizontal, float pos, float start, float end)
{
    glColor3f(1.0f, 0.9f, 0.0f);
    glLineWidth(3.0f);
    float dash = 15.0f, gap = 15.0f;
    float total = horizontal ? (end - start) : (end - start);
    for(float i = 0; i < total; i += dash + gap)
    {
        float s = i;
        float e = i + dash;
        if(e > total) e = total;
        glBegin(GL_LINES);
        if(horizontal)
        {
            glVertex2f(start + s, pos);
            glVertex2f(start + e, pos);
        }
        else
        {
            glVertex2f(pos, start + s);
            glVertex2f(pos, start + e);
        }
        glEnd();
    }
}

/* ================= ZEBRA CROSSING ================= */
void drawZebra(float x, float y, bool horizontal, int lanes = 8)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    float stripeW = 8.0f, gap = 8.0f;
    for(int i = 0; i < lanes; i++)
    {
        float offset = i * (stripeW + gap);
        glBegin(GL_QUADS);
        if(horizontal)
        {
            glVertex2f(x + offset, y - 45);
            glVertex2f(x + offset + stripeW, y - 45);
            glVertex2f(x + offset + stripeW, y + 45);
            glVertex2f(x + offset, y + 45);
        }
        else
        {
            glVertex2f(x - 45, y + offset);
            glVertex2f(x + 45, y + offset);
            glVertex2f(x + 45, y + offset + stripeW);
            glVertex2f(x - 45, y + offset + stripeW);
        }
        glEnd();
    }
}

/* ================= RED-ROOF HOUSE ================= */
void drawRedHouse(float cx, float cy)
{
    // Base
    glColor3f(0.95f, 0.95f, 0.85f);
    glBegin(GL_QUADS);
        glVertex2f(cx-25, cy-25);
        glVertex2f(cx+25, cy-25);
        glVertex2f(cx+25, cy+20);
        glVertex2f(cx-25, cy+20);
    glEnd();
    // Red roof
    glColor3f(0.9f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx-30, cy+20);
        glVertex2f(cx+30, cy+20);
        glVertex2f(cx, cy+45);
    glEnd();
}

/* ================= TREE (NORMAL & PALM) ================= */
void drawTree(float x, float y, bool palm = false)
{
    if(palm)
    {
        // Trunk
        glColor3f(0.55f, 0.35f, 0.15f);
        glBegin(GL_QUADS);
            glVertex2f(x-5, y-20); glVertex2f(x+5, y-20);
            glVertex2f(x+5, y+15); glVertex2f(x-5, y+15);
        glEnd();
        // Leaves
        glColor3f(0.1f, 0.7f, 0.1f);
        for(int i=0; i<7; i++)
        {
            float ang = i * (360.0f/7) * PI / 180.0f;
            drawFilledCircle(x + 15*cos(ang), y+15 + 10*sin(ang), 10);
        }
    }
    else
    {
        glColor3f(0.55f, 0.35f, 0.15f);
        glBegin(GL_QUADS);
            glVertex2f(x-6, y-15); glVertex2f(x+6, y-15);
            glVertex2f(x+6, y+10); glVertex2f(x-6, y+10);
        glEnd();
        glColor3f(0.1f, 0.7f, 0.1f);
        drawFilledCircle(x, y+15, 15);
    }
}

/* ================= SIMPLE CAR ================= */
void drawSimpleCar(float x, float y, float angle, float r, float g, float b)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(-10, -18); glVertex2f(10, -18);
        glVertex2f(10, 18); glVertex2f(-10, 18);
    glEnd();
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-7, -12); glVertex2f(7, -12);
        glVertex2f(7, 12); glVertex2f(-7, 12);
    glEnd();
    glPopMatrix();
}

/* ================= DISPLAY ================= */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Green grass background
    glColor3f(0.35f, 0.8f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-300,-300); glVertex2f(300,-300);
        glVertex2f(300,300); glVertex2f(-300,300);
    glEnd();

    // Main roads
    drawRoad(-300, 120, 300, 200);   // top horizontal
    drawRoad(-300, -200, 300, -120); // bottom horizontal
    drawRoad(-200, -300, -120, 300); // left vertical
    drawRoad(120, -300, 200, 300);   // right vertical
    drawRoad(-30, -300, 30, 300);    // central railway road

    // Railway tracks
    glColor3f(0.55f, 0.35f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-35,-300); glVertex2f(-25,-300); glVertex2f(-25,300); glVertex2f(-35,300);
        glVertex2f(25,-300); glVertex2f(35,-300); glVertex2f(35,300); glVertex2f(25,300);
    glEnd();

    // Dashed lines
    drawDashedCenter(true, 160, -300, 300); // top road
    drawDashedCenter(true, -160, -300, 300); // bottom road
    drawDashedCenter(false, -160, -300, 300); // left road
    drawDashedCenter(false, 160, -300, 300); // right road

    // Zebra crossings
    drawZebra(-160, 160, true);  // top-left
    drawZebra(-160, -160, true); // bottom-left
    drawZebra(160, 160, true);   // top-right
    drawZebra(160, -160, true);  // bottom-right
    drawZebra(-160, 0, false);   // central left
    drawZebra(160, 0, false);    // central right

    // Train
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-25,140); glVertex2f(25,140); glVertex2f(25,200); glVertex2f(-25,200);
        glVertex2f(-25,60); glVertex2f(25,60); glVertex2f(25,120); glVertex2f(-25,120);
        glVertex2f(-25,-20); glVertex2f(25,-20); glVertex2f(25,40); glVertex2f(-25,40);
        glVertex2f(-25,-100); glVertex2f(25,-100); glVertex2f(25,-40); glVertex2f(-25,-40);
    glEnd();
    glColor3f(0.1f, 0.5f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-25,200); glVertex2f(25,200); glVertex2f(25,240); glVertex2f(-25,240);
    glEnd();

    // Top-left small buildings
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-280,220); glVertex2f(-220,220); glVertex2f(-220,280); glVertex2f(-280,280);
        glVertex2f(-280,160); glVertex2f(-220,160); glVertex2f(-220,200); glVertex2f(-280,200);
    glEnd();

    // Small pool top-left
    glColor3f(0.2f, 0.7f, 1.0f);
    drawFilledCircle(-100, 240, 22);

    // Helipad
    glColor3f(0.15f, 0.15f, 0.4f);
    drawFilledCircle(-60, 170, 35);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
        glVertex2f(-60,130); glVertex2f(-60,210);
        glVertex2f(-100,170); glVertex2f(-20,170);
    glEnd();
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(-60,140); glVertex2f(-60,200);
        glVertex2f(-90,170); glVertex2f(-30,170);
    glEnd();

    // Red houses top
    drawRedHouse(-80, 240);
    drawRedHouse(-20, 240);
    drawRedHouse(-50, 160);

    // Stadium top-right
    glColor3f(0.95f, 0.85f, 0.7f);
    drawFilledCircle(120, 180, 90); // track
    glColor3f(0.2f, 0.8f, 0.2f);
    drawFilledCircle(120, 180, 65); // field
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(4.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(55,115); glVertex2f(185,115);
        glVertex2f(185,245); glVertex2f(55,245);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(120,115); glVertex2f(120,245);
    glEnd();
    drawFilledCircle(120,180,12);

    // Benches around stadium
    glColor3f(0.8f, 0.4f, 0.2f);
    for(int i=0; i<8; i++)
    {
        float ang = i*45*PI/180.0f;
        float bx = 120 + 100*cos(ang);
        float by = 180 + 100*sin(ang);
        glBegin(GL_QUADS);
            glVertex2f(bx-8,by-4); glVertex2f(bx+8,by-4);
            glVertex2f(bx+8,by+4); glVertex2f(bx-8,by+4);
        glEnd();
    }

    // Beach bottom-left
    glColor3f(1.0f, 0.9f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(-300,-300); glVertex2f(-80,-300);
        glVertex2f(-180,-140); glVertex2f(-300,-180);
    glEnd();
    glColor3f(0.2f, 0.6f, 1.0f);
    drawFilledCircle(-220, -200, 55);
    // Umbrellas
    glColor3f(1.0f, 0.2f, 0.2f);
    drawFilledCircle(-260,-220,15);
    drawFilledCircle(-180,-230,15);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
        glVertex2f(-260,-235); glVertex2f(-260,-190);
        glVertex2f(-180,-245); glVertex2f(-180,-200);
    glEnd();
    // Palm trees
    drawTree(-280,-160,true); drawTree(-240,-180,true);
    drawTree(-200,-200,true); drawTree(-160,-180,true);
    drawTree(-220,-240,true);

    // Central red houses + small pool
    drawRedHouse(-80, -20);
    drawRedHouse(-20, -20);
    drawRedHouse(-80, -100);
    drawRedHouse(-20, -100);
    glColor3f(0.2f, 0.7f, 1.0f);
    drawFilledCircle(-50, -60, 20);

    // Parking lot bottom-right
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(40,-220); glVertex2f(280,-220);
        glVertex2f(280,-20); glVertex2f(40,-20);
    glEnd();
    glColor3f(0.9f, 0.7f, 0.2f);
    glLineWidth(6.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(40,-220); glVertex2f(280,-220);
        glVertex2f(280,-20); glVertex2f(40,-20);
    glEnd();

    // Parked cars
    drawSimpleCar(80,-40, 0, 0.9,0.2,0.2);    // red
    drawSimpleCar(130,-40, 0, 0.2,0.8,0.2);   // green
    drawSimpleCar(180,-40, 0, 1.0,1.0,0.0);   // yellow
    drawSimpleCar(230,-40, 0, 0.5,0.0,1.0);   // purple

    drawSimpleCar(80,-90, 180, 0.0,0.5,1.0);  // blue
    drawSimpleCar(130,-90, 180, 1.0,0.5,0.0); // orange
    drawSimpleCar(180,-90, 180, 0.8,0.8,0.8); // gray
    drawSimpleCar(230,-90, 180, 1.0,0.0,1.0); // magenta

    drawSimpleCar(80,-140, 0, 0.2,0.8,0.8);   // cyan
    drawSimpleCar(130,-140, 0, 0.0,0.0,0.0);  // black

    // Hospital symbol
    glColor3f(0.2f, 0.7f, 1.0f);
    drawFilledCircle(240, -160, 18);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(5);
    glBegin(GL_LINES);
        glVertex2f(240, -178); glVertex2f(240, -142);
        glVertex2f(222, -160); glVertex2f(258, -160);
    glEnd();

    // Bottom long buildings
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-100,-280); glVertex2f(-20,-280); glVertex2f(-20,-230); glVertex2f(-100,-230);
        glVertex2f(40,-280); glVertex2f(140,-280); glVertex2f(140,-230); glVertex2f(40,-230);
        glVertex2f(160,-280); glVertex2f(280,-280); glVertex2f(280,-230); glVertex2f(160,-230);
    glEnd();

    // Trees scattered
    drawTree(-220,80,false);
    drawTree(220,120,false);
    drawTree(220,-80,false);
    drawTree(-220,-240,false);
    drawTree(240,-100,false);

    // Cars on roads
    drawSimpleCar(-10,160,0,1.0,0.8,0.0);     // yellow on top road
    drawSimpleCar(160,10,270,0.9,0.3,0.1);    // red on right road
    drawSimpleCar(-10,-160,180,0.0,0.6,1.0);  // blue on bottom
    drawSimpleCar(-160,-10,90,0.2,0.8,0.2);   // green on left

    glutSwapBuffers();
}

/* ================= INIT ================= */
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);
    glMatrixMode(GL_MODELVIEW);
}

/* ================= MAIN ================= */
void startMainGame(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1080, 720);
    glutCreateWindow("Exact City Scene Matching Your Picture");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}

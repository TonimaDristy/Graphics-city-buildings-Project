#include <windows.h>
#include<GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <ctime>
//COMMON ITEMS


//Variables
GLfloat shiftX = 0;
GLfloat shiftY = 0;

GLfloat scaleX = 0;
GLfloat scaleY = 0;

GLfloat shiftXanimation=0;
// Windmill Changes
float angle = 0.0f;
float spinSpeed = 1.0f; // Adjust the spinning speed as needed


//SUN
float sunX = -0.6f; // Initial x-coordinate of the sun
float sunY = 0.5f; // Initial y-coordinate of the sun
float targetY = 0.875f; // Target y-coordinate for the sun to stop
float sunRadius = 0.07f; // Radius of the sun
int numSegments = 50; // Number of segments for drawing the sun


//CARS
float carPosX = -1.8;
float carPosX2 = -2.2;


float truckPosX = -2.6; // Initial X position of the truck

float yachtPositionX = 0.6; // Initial x-coordinate for the yacht

//RIVERLINES
float xOffset = 0.0; // Initial x offset for shifting the lines

//KB controls
bool isRightKeyPressed = false;
bool isLeftKeyPressed = false;

// Function to draw the glowing sun
void drawGlowingSun(float x, float y, float radius, int numSegments)
{
    // Draw outer glow
    glColor4f(1.0f, 1.0f, 0.0f, 0.5f); // Yellow color with 50% opacity
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the sun
    for (int i = 0; i <= numSegments; i++)
    {
        float angle = i * 2.0f * M_PI / numSegments;
        float newX = x + (radius * cos(angle));
        float newY = y + (radius * sin(angle));
        glVertex2f(newX, newY);
    }
    glEnd();

    // Draw middle glow
    glColor4f(1.0f, 1.0f, 0.0f, 0.3f); // Yellow color with 30% opacity
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the sun
    for (int i = 0; i <= numSegments; i++)
    {
        float angle = i * 2.0f * M_PI / numSegments;
        float newX = x + ((radius - 0.005f) * cos(angle)); // Slightly smaller radius
        float newY = y + ((radius - 0.005f) * sin(angle)); // Slightly smaller radius
        glVertex2f(newX, newY);
    }
    glEnd();

    // Draw inner glow
    glColor4f(1.0f, 1.0f, 0.0f, 0.2f); // Yellow color with 20% opacity
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the sun
    for (int i = 0; i <= numSegments; i++)
    {
        float angle = i * 2.0f * M_PI / numSegments;
        float newX = x + ((radius - 0.01f) * cos(angle)); // Smaller radius
        float newY = y + ((radius - 0.01f) * sin(angle)); // Smaller radius
        glVertex2f(newX, newY);
    }
    glEnd();
}


// Function to update the position of the sun
void updateSunPosition()
{
    // Move the sun towards the target y-coordinate
    if (sunY < targetY)
    {
        sunY += 0.0006f; // Adjust the speed of movement here
    }
}
void CircleBorder(float radius, float xc, float yc, float width)
{
    glLineWidth(width);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    for(int i=0; i<200; i++)
    {
        glColor3ub(0,0,0);
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc );
    }
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void drawCircle(float x, float y, float radius)
{
    int numSegments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle
    for (int i = 0; i <= numSegments; i++)
    {
        float angle = i * 2.0f * M_PI / numSegments;
        float newX = x + (radius * cos(angle));
        float newY = y + (radius * sin(angle));
        glVertex2f(newX, newY);
    }
    glEnd();
}



void drawLines()
{
    // Draw horizontal line
    glColor3f(0.0, 0.0, 0.0); // Set color to black
    glBegin(GL_LINES);
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    glEnd();

    // Draw vertical line
    glBegin(GL_LINES);
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();
}


void drawskyline()
{
    // Draw horizontal brown line
    glColor3f(0.647, 0.165, 0.165); // Set color to brown
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(-1.0, 0.5);
    glVertex2f(1.0, 0.5);
    glEnd();
}
void createSky()
{
    glBegin(GL_QUADS);

    // Bottom
    glColor3f(1, 0.93, 0.12);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);

    // Top
    glColor3f(0.47, 0.66, 0.99);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);

    glEnd();
}




void createRiver() {
    // Blue color for the river
    glColor4f(0.0, 0.0, 1.0, 0.7); // Semi-transparent blue color for the water
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(1.0, 0.5);
    glVertex2f(-1.0, 0.5);
    glEnd();


}
void riverlines() {

    // Draw the lines with an offset
    float xOffset1 = xOffset;
    glColor3f(0.08, 0, 0.58);
    glBegin(GL_LINES);
    for (float x = -1.95 + xOffset1; x <= 1.0 + xOffset1; x += 0.2) {
        for (float y = 0.45; y >= -1; y -= 0.125) {
            glVertex2f(x, y);
            glVertex2f(x + 0.1, y);
        }
    }
    glEnd();

    // Draw the second set of lines with an offset
    float xOffset2 = xOffset - 0.05; // Adjust the offset to create a staggered effect
    glColor3f(0.28, 0.36, 0.92);
    glBegin(GL_LINES);
    for (float x = -1.2 + xOffset2; x <= 1.0 + xOffset2; x += 0.2) {
        for (float y = 0.40; y >= -1; y -= 0.125) {
            glVertex2f(x, y);
            glVertex2f(x + 0.1, y);
        }
    }
    glEnd();
}



void createurbanground()
{
    glColor3f(0.16, 0.46, 0.15); // ground color
    glBegin(GL_POLYGON);
    glVertex2f(1.0,.5);
    glVertex2f(-1.0,.5);
    glVertex2f(0.26,0.4);
    glVertex2f(0.34, 0.25);
    glVertex2f(.4, 0.175);
    glVertex2f(0.46, 0.0);
    glVertex2f(0.34,-.12);
    glVertex2f(0.2, -0.2);
    glVertex2f(0.2, -0.4);
    glVertex2f(0.14, -0.5);
    glVertex2f(0.2, -0.625);
    glVertex2f(0.4, -0.875);
    glVertex2f(0.5, -1.0);
    glVertex2f(1.0, -1.0);



    glEnd();
}

void createslumground()
{
    glColor3f(0.16, 0.46, 0.15); // ground color
    glBegin(GL_POLYGON);
    glVertex2f(-1.0,.175);
    glVertex2f(-0.8,0.25);
    glVertex2f(-0.6,0.275);
    glVertex2f(-0.4,0.175);
    glVertex2f(-0.2, 0.075);
    glVertex2f(-0.16, 0.0);
    glVertex2f(-0.2, -0.125);
    glVertex2f(-0.3,-.35);
    glVertex2f(-0.4, -0.575);
    glVertex2f(-0.48, -0.75);
    glVertex2f(-0.68, -1.0);
    glVertex2f(-1.0, -1.0);



    glEnd();
}

void drawTree1(float height, float width, float xPos, float yPos, float scale)
{
    glPushMatrix();
    glTranslatef(xPos, yPos, 0.0f);
    glScalef(scale, scale, 1.0f); // Apply scaling

    // Draw tree trunk
    glColor3ub(139, 69, 19); // Brown color
    glBegin(GL_QUADS);
    glVertex2f(-width / 4.0f, -height / 2.0f);
    glVertex2f(width / 4.0f, -height / 2.0f);
    glVertex2f(width / 4.0f, 0.0f);
    glVertex2f(-width / 4.0f, 0.0f);
    glEnd();

    // Draw tree leaves
    glColor3ub(34, 139, 34); // Green color
    glBegin(GL_TRIANGLES);
    glVertex2f(-width, 0.0f);
    glVertex2f(width, 0.0f);
    glVertex2f(0.0f, height);
    glEnd();

    // Draw tree leaves
    glColor3ub(34, 139, 34); // Green color
    glBegin(GL_TRIANGLES);
    glVertex2f(-width, .300f);
    glVertex2f(width, .300f);
    glVertex2f(0.0f, height+.10);
    glEnd();

    glPopMatrix();
}

void drawTree2(float height, float width, float xPos, float yPos, float scale)
{
    glPushMatrix();
    glTranslatef(xPos, yPos, 0.0f);
    glScalef(scale, scale, 1.0f); // Apply scaling

    // Draw tree trunk
    glColor3f(0.36, 0.27, 0.06); // Brown color
    glBegin(GL_QUADS);
    glVertex2f(-width / 4.0f, -height / 2.0f);
    glVertex2f(width / 4.0f, -height / 2.0f);
    glVertex2f(width / 4.0f, .40f);
    glVertex2f(-width / 4.0f, .40f);
    glEnd();

    // Draw tree leaves

    int numCircles = 4; // Number of circles for the leaves
    float leafRadius = width * 0.6f; // Radius of each leaf circle
    float leafSpacing = width * 0.4f; // Spacing between leaf circles
    for (int i = 0; i < numCircles; ++i)
    {
        glColor3f(0.06, 0.36, 0.1);

        float angle = 2 * M_PI * i / numCircles;
        float x = sin(angle) * leafSpacing;
        float y = cos(angle) * leafSpacing + height / 2.0f; // Adjusted y-coordinate
        drawCircle(x, y, leafRadius);


    }

    glPopMatrix();
}

void drawBush(float xPos, float yPos, float radius, int numCircles, float offset)
{
    glColor3f(0.09, 0.17, 0.04); // Green color for the bush

    // Draw the central circle
    drawCircle(xPos, yPos, radius);

    // Draw additional circles to add volume to the bush
    for (int i = 0; i < numCircles; ++i)
    {
        float angle = i * (360.0f / numCircles) + offset;
        float x = xPos + radius * 0.7f * cos(angle * M_PI / 180.0f);
        float y = yPos + radius * 0.7f * sin(angle * M_PI / 180.0f);
        drawCircle(x, y, radius * 0.4f);
    }
}


void drawbush2(float x, float y, float scale)
{
    scaleX = scale;
    scaleY = scale;
    shiftX=x;
    shiftY=y;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);

    glColor3f(0.06, 0.39, 0.02);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(0,0.-.04);
    glVertex2f(0.08,-0.04);
    glVertex2f(0.08,0);
    glEnd();

    drawCircle(0, 0,0.04);
    drawCircle(0.04,0.025,0.04);
    drawCircle(0.08, 0,0.04);
    glPopMatrix();

    glPopMatrix();
}

void renderBitmapString(float x, float y, void *font, const char *string) {
    glRasterPos2f(x, y);
    while (*string) {
        glutBitmapCharacter(font, *string);
        string++;
    }
}

/*-----------------------INDUSTRY PART START-----------------------------------*/


/* WINDMILL HERE*/


// Function to create the windmill
void createwindmill()
{
    // Base
    glColor3f(0.62, 0.34, 0.11);
    glBegin(GL_POLYGON);
    glVertex2f(0.2, 0);
    glVertex2f(0.26, 0.75);
    glVertex2f(0.3, 0.8);
    glVertex2f(0.34, 0.75);
    glVertex2f(0.4, 0);
    glEnd();

    // Door
    glColor3f(0.08, 0.05, 0.02);
    glBegin(GL_POLYGON);
    glVertex2f(0.26, 0.175);
    glVertex2f(0.34, 0.175);
    glVertex2f(0.34, 0);
    glVertex2f(0.26, 0);
    glEnd();



    // Rotating wings
    glPushMatrix();
    glTranslatef(0.3f, 0.675f, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.3f, -0.675f, 0.0f);

    //wing-1

    glColor3f(0.06, 0.06, 0.06);
    glBegin(GL_POLYGON);
    glVertex2f(0.3, 0.675);
    glVertex2f(0.54, 0.675);
    glVertex2f(0.54, 0.7);
    glVertex2f(0.3, 0.7);
    glEnd();
    glColor3f(0.49, 0.49, 0.48);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.3, 0.7);
    glVertex2f(0.54, 0.775);
    glVertex2f(0.54, 0.7);
    glEnd();


//wing2
    glColor3f(0.06, 0.06, 0.06);
    glBegin(GL_POLYGON);
    glVertex2f(0.3, 0.675);
    glVertex2f(0.06, 0.675);
    glVertex2f(0.06, 0.65);
    glVertex2f(0.3, 0.65);
    glEnd();

    glColor3f(0.49, 0.49, 0.48);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.3, 0.65);
    glVertex2f(0.06, 0.575);
    glVertex2f(0.06, 0.65);
    glEnd();

//wing 3
    glColor3f(0.06, 0.06, 0.06);
    glBegin(GL_POLYGON);
    glVertex2f(0.3, 0.675);
    glVertex2f(0.3, 0.975);
    glVertex2f(0.28, 0.975);
    glVertex2f(0.28, 0.675);
    glEnd();
    glColor3f(0.49, 0.49, 0.48);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.32, 0.375);
    glVertex2f(0.38, 0.375);
    glVertex2f(0.32, 0.675);
    glEnd();

//wing4
    glColor3f(0.06, 0.06, 0.06);
    glBegin(GL_POLYGON);
    glVertex2f(0.3, 0.675);
    glVertex2f(0.3, 0.375);
    glVertex2f(0.32, 0.375);
    glVertex2f(0.32, 0.675);
    glEnd();

    glColor3f(0.49, 0.49, 0.48);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.22, 0.975);
    glVertex2f(0.28, 0.975);
    glVertex2f(0.28, 0.675);
    glEnd();



    glPopMatrix();

    // Circle
    glColor3f(1, 0, 0.0);
    drawCircle(0.3f, 0.675f, 0.03f);
    //circleborder
    glColor3f(0, 0, 0);
    CircleBorder(.03f,0.3f, 0.675f,0.2f);
}



//WATERBUILDING
void createwaterbuilding()
{
    //backbuild
    // Base
    glColor3f(0.27, 0.6, 0.18);
    glBegin(GL_QUADS);
    glVertex2f(-0.1, 0);
    glVertex2f(-0.1, 0.7);
    glVertex2f(-0.5, 0.7);
    glVertex2f(-0.5, 0);
    glEnd();

    glColor3f(0.13, 0.31, 0.09);
    glBegin(GL_QUADS);
    glVertex2f(-0.1, 0);
    glVertex2f(-0.1, 0.7);
    glVertex2f(-0.24, 0.7);
    glVertex2f(-0.24, 0);
    glEnd();

    //frontside
    glColor3f(0.86, 0.86, 0.89);
    glBegin(GL_QUADS);
    glVertex2f(-0.3, 0);
    glVertex2f(-0.3, 0.5);
    glVertex2f(-0.8, 0.5);
    glVertex2f(-0.8, 0);
    glEnd();

    glColor3f(0.59, 0.59, 0.6);
    glBegin(GL_QUADS);
    glVertex2f(-0.64, 0);
    glVertex2f(-0.64, 0.5);
    glVertex2f(-0.8, 0.5);
    glVertex2f(-0.8, 0);
    glEnd();

    //stairs
    glLineWidth(2.0);

    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(-0.68, 0.0);
    glVertex2f(-0.68, 0.55);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(-0.76, 0.0);
    glVertex2f(-0.76, 0.55);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(-0.68, 0.0);
    glVertex2f(-0.76, 0.125);

    glVertex2f(-0.76, 0.125);
    glVertex2f(-0.68, 0.25);

    glVertex2f(-0.68, 0.25);
    glVertex2f(-0.76, 0.375);

    glVertex2f(-0.76, 0.375);
    glVertex2f(-0.68, 0.5);

    glEnd();



    //PIPE

    glColor3f(0.07, 0.12, 0.15);
    glBegin(GL_QUADS);
    glVertex2f(-0.38, 0.575);
    glVertex2f(-0.32, 0.575);
    glVertex2f(-0.32, 0.8);
    glVertex2f(-0.38, 0.8);

    glVertex2f(-0.38, 0.725);
    glVertex2f(-0.12, 0.725);
    glVertex2f(-0.12, 0.8);
    glVertex2f(-0.38, 0.8);

    glVertex2f(-0.12, 0.8);
    glVertex2f(-0.12, 0.7);
    glVertex2f(-0.18, 0.7);
    glVertex2f(-0.18, 0.8);

    glVertex2f(-0.38, 0.575);
    glVertex2f(-0.38, 0.65);
    glVertex2f(-0.58, 0.65);
    glVertex2f(-0.58, 0.575);

    glVertex2f(-0.58, 0.575);
    glVertex2f(-0.58, 0.5);
    glVertex2f(-0.52, 0.5);
    glVertex2f(-0.52, 0.575);
    glEnd();


//windows1
    glColor3f(0.05, 0.52, 0.74);
    glBegin(GL_QUADS);

    glVertex2f(-0.14, 0.2);
    glVertex2f(-0.14, 0.275);
    glVertex2f(-0.2, 0.275);
    glVertex2f(-0.2, 0.2);

    glEnd();

    glBegin(GL_QUADS);

    glVertex2f(-0.14, 0.375);
    glVertex2f(-0.14, 0.45);
    glVertex2f(-0.2, 0.45);
    glVertex2f(-0.2, 0.375);

    glEnd();

    glBegin(GL_QUADS);

    glVertex2f(-0.14, 0.55);
    glVertex2f(-0.14, 0.625);
    glVertex2f(-0.2, 0.625);
    glVertex2f(-0.2, 0.55);

    glEnd();


//windows2
    glBegin(GL_QUADS);

    glVertex2f(-0.36, 0.3);
    glVertex2f(-0.42, 0.3);
    glVertex2f(-0.42, 0.375);
    glVertex2f(-0.36, 0.375);

    glEnd();

    glBegin(GL_QUADS);

    glVertex2f(-0.36, 0.125);
    glVertex2f(-0.42, 0.125);
    glVertex2f(-0.42, 0.2);
    glVertex2f(-0.36, 0.2);

    glEnd();
///

    glBegin(GL_QUADS);

    glVertex2f(-0.5, 0.3);
    glVertex2f(-0.56, 0.3);
    glVertex2f(-0.56, 0.375);
    glVertex2f(-0.5, 0.375);

    glEnd();

    glBegin(GL_QUADS);

    glVertex2f(-0.5, 0.125);
    glVertex2f(-0.56, 0.125);
    glVertex2f(-0.56, 0.2);
    glVertex2f(-0.5, 0.2);

    glEnd();


}


void createBrickField()
{
    //Base
    glColor3f(0.97, 0.97, 0.98);//white
    glBegin(GL_POLYGON);
    glVertex2f(.64,.25);
    glVertex2f(.6,0);
    glVertex2f(.8,0);
    glVertex2f(.66,.75);
    glVertex2f(.74,.75);
    glVertex2f(.76,.25);
    glVertex2f(.8,0);
    glEnd();

    //detail-1 redlines
    glColor3f(1.0,.0,.0);//red
    glBegin(GL_POLYGON);
    glVertex2f(.655,.625);
    glVertex2f(.745,.625);
    glVertex2f(.748,.575);
    glVertex2f(.652,.575);

    glEnd();

    glColor3f(1.0,.0,.0);//red
    glBegin(GL_POLYGON);
    glVertex2f(.643,.325);
    glVertex2f(.756,.325);
    glVertex2f(.76,.25);
    glVertex2f(.64,.25);

    glEnd();

    //Detail-2 antenna

    glColor3f(.0,.0,.0);//white
    glBegin(GL_LINES);
    glVertex2f(.662,.75);
    glVertex2f(.662,.8755);

    glEnd();

    shiftX = 1.0f;
    shiftY = 1.2;

    scaleX = 0.4f;
    scaleY = 0.4f;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);

    //Detail smoke (animation)
    srand(time(NULL)); // Seed for random number generation
    for (int i = 0; i < 10; i++)
    {
        float smokeX = 0.66f + (rand() % 40) / 100.0f; // Randomize x-coordinate
        float smokeY = 0.85f + (rand() % 20) / 100.0f; // Randomize y-coordinate
        float smokeSize = 0.02f + (rand() % 20) / 100.0f; // Randomize size
        glColor4f(0.8f, 0.8f, 0.8f, 0.5f); // Light gray color with slight transparency
        drawCircle(smokeX, smokeY, smokeSize);
        glColor4f(0.15, 0.18, 0.2, 0.5); // Light gray color with slight transparency
        drawCircle(smokeX, smokeY, smokeSize/5.0);
    }
    glPopMatrix();


}

void industry()
{
    //WINDMILL
    shiftX = -0.5f;
    shiftY = 1.2;

    scaleX = 0.4f;
    scaleY = 0.4f;


    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);

    createwindmill();
    glPopMatrix();
    glPopMatrix();



    //WATERBUILDING
    shiftX = -0.7f;
    shiftY = 1.6;

    scaleX = 0.3f;
    scaleY = 0.3f;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    createwaterbuilding();
    glPopMatrix();


    //BrickMill
    shiftX = -0.4f;
    shiftY = 0.9;

    scaleX = 0.5f;
    scaleY = 0.5f;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);

    createBrickField();
    glPopMatrix();


    drawTree1(.8,.3,-.63,.57,.2);
    drawTree1(0.81, 0.29, -0.67, 0.58, 0.21);
    drawTree1(0.81, 0.29, -0.74, 0.58, 0.21);
    drawTree1(0.81, 0.29, -0.47, 0.52, 0.1);
    drawTree1(0.81, 0.29, -0.2, 0.53, 0.2);
    drawTree2(1.0, 0.29, 0.0, 0.52, 0.2);
    drawTree2(0.8, 0.2, -.64, 0.56, 0.2);



}


/*-----------------------INDUSTRY PART END-----------------------------------*/








/*-----------------------BRIDGE-----------------------------------*/
void createBridge()
{
    // Draw the main road
    glColor3f(0.07f, 0.07f, 0.07f); // Gray color for road
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.575f); // Bottom-left corner
    glVertex2f(1.0f, -0.575f); // Bottom-right corner
    glVertex2f(1.0f, -0.375f); // Top-right corner
    glVertex2f(-1.0f, -0.375f); // Top-left corner
    glEnd();

    // Draw lane lines
    glColor3f(1.0f, 1.0f, 1.0f); // White color for lane lines
    glLineWidth(2.0f); // Set the line width
    glBegin(GL_LINES);
    // First lane line
    glVertex2f(-1.0f, -0.475f); // Left point
    glVertex2f(-0.7f, -0.475f); // Right point
    // Second lane line
    glVertex2f(-0.4f, -0.475f); // Left point
    glVertex2f(-0.1f, -0.475f); // Right point
    // Third lane line
    glVertex2f(0.1f, -0.475f); // Left point
    glVertex2f(0.4f, -0.475f); // Right point
    // Fourth lane line
    glVertex2f(0.7f, -0.475f); // Left point
    glVertex2f(1.0f, -0.475f); // Right point
    glEnd();

    //Railings2
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3f(0.31, 0.31, 0.31);
    glVertex2f(-1.0f, -0.575f);
    glVertex2f(1.0f, -0.575f);
    // Second railing line
    glVertex2f(-1.0f, -0.525f);
    glVertex2f(1.0f, -0.525f);
    glEnd();

    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for(float x=-1; x<=1 ; x=x+ 0.04)
    {
        glVertex2f(x, -0.575f);
        glVertex2f(x, -0.525f);

    }
    glEnd();


    //Bridgeholders
    glColor3f(0.08, 0.14, 0.74); // Blue color for the river
    drawCircle(-.33,-.75,0.05);
    glColor3f(0.37, 0.37, 0.37); // Gray color for road
    glBegin(GL_POLYGON);

    glVertex2f(-.36f, -0.65f);
    glVertex2f(-.42f, -0.6f);
    glVertex2f(-.42f, -0.55f);
    glVertex2f(-.24f, -0.55f);
    glVertex2f(-.24, -0.6f);
    glVertex2f(-.3f, -0.65f);
    glVertex2f(-.3f, -0.75f);
    glVertex2f(-.36f, -0.75f);
    glEnd();




    shiftX=0.27;
    shiftY=0;
    glPushMatrix();
    glTranslatef(shiftX, shiftY, 0.0f);

    glColor3f(0.08, 0.14, 0.74); // Blue color for the river
    drawCircle(-.33,-.75,0.05);

    glColor3f(0.37, 0.37, 0.37); // Gray color for road
    glBegin(GL_POLYGON);

    glVertex2f(-.36f, -0.65f);
    glVertex2f(-.42f, -0.6f);
    glVertex2f(-.42f, -0.55f);
    glVertex2f(-.24f, -0.55f);
    glVertex2f(-.24, -0.6f);
    glVertex2f(-.3f, -0.65f);
    glVertex2f(-.3f, -0.75f);
    glVertex2f(-.36f, -0.75f);
    glEnd();

    glPopMatrix();



    shiftX=0.54;
    shiftY=0;
    glPushMatrix();
    glTranslatef(shiftX, shiftY, 0.0f);

    glColor3f(0.08, 0.14, 0.74); // Blue color for the river
    drawCircle(-.33,-.75,0.05);

    glColor3f(0.37, 0.37, 0.37); // Gray color for road
    glBegin(GL_POLYGON);

    glVertex2f(-.36f, -0.65f);
    glVertex2f(-.42f, -0.6f);
    glVertex2f(-.42f, -0.55f);
    glVertex2f(-.24f, -0.55f);
    glVertex2f(-.24, -0.6f);
    glVertex2f(-.3f, -0.65f);
    glVertex2f(-.3f, -0.75f);
    glVertex2f(-.36f, -0.75f);
    glEnd();
    glPopMatrix();

    //Railings
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3f(0.31, 0.31, 0.31);
    glVertex2f(-1.0f, -0.375f);
    glVertex2f(1.0f, -0.375f);
// Second railing line
    glVertex2f(-1.0f, -0.325f);
    glVertex2f(1.0f, -0.325f);
    glEnd();

    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for(float x=-1; x<=1 ; x=x+ 0.04)
    {
        glVertex2f(x, -0.375f);
        glVertex2f(x, -0.325f);

    }
    glEnd();


}

/*------------------------URBAN AREA START----------------------------*/


void urbanbuilding1()
{



    //blue slim


    glColor3f(.38, 0.47, .66);
    glBegin(GL_POLYGON);
    glVertex2f(-.18, 0);
    glVertex2f(-.18, .50);
    glVertex2f(-.32,.5);
    glVertex2f(-.32, 0);
    glEnd();

    glColor3f(.3, .6, 1.15);
    glBegin(GL_POLYGON);
    glVertex2f(-.28, 0);
    glVertex2f(-.28, .50);
    glVertex2f(-.32,.5);
    glVertex2f(-.32, 0);
    glEnd();

    glColor3f(.38, 0.47, .66);
    glBegin(GL_POLYGON);
    glVertex2f(-.30, .50);
    glVertex2f(-.30, .60);
    glVertex2f(-.36,.6);
    glVertex2f(-.36, .5);
    glEnd();

    glColor3f(.38, 0.47, .66);
    glBegin(GL_POLYGON);
    glVertex2f(-.32, .50);
    glVertex2f(-.36, .50);
    glVertex2f(-.36,0.0);
    glVertex2f(-.32, 0.0);
    glEnd();

    glColor3f(.3, .6, 1.15);
    glBegin(GL_POLYGON);
    glVertex2f(-.36, .0);
    glVertex2f(-.36, .60);
    glVertex2f(-.42,0.60);
    glVertex2f(-.42, 0.0);
    glEnd();

}

void urbanbuilding2()
{
    glColor3f(0.0, 0.0, 0.0);
    glColor3f(.53, 0.53, 1.30);
    //glColor3f(.22, .55, 1.25);
    glBegin(GL_POLYGON);
    glVertex2f(0.8, 0);
    glVertex2f(.65, 0);
    glVertex2f(.65,.6);
    glVertex2f(0.8, 0.7);
    glEnd();

    glColor3f(.3, .6, 1.15);
    glBegin(GL_POLYGON);
    glVertex2f(0.8, 0);
    glVertex2f(.85, 0);
    glVertex2f(.85,.61);
    glVertex2f(0.8, 0.6);
    glEnd();


    glColor3f(.38, 0.47, .66);
    glBegin(GL_POLYGON);
    glVertex2f(0.8, 0.7);
    glVertex2f(0.82, 0.7);
    glVertex2f(0.82, 0.6);
    glVertex2f(0.8, 0.6);
    glEnd();

    glColor3f(.38, 0.47, .66);
    glBegin(GL_POLYGON);
    glVertex2f(0.85, 0);
    glVertex2f(.95, 0);
    glVertex2f(.95,.6);
    glVertex2f(0.85, 0.61);
    glEnd();
    //end

}


void urbanbuilding3()
{

    //last tall building

    glColor3f(.77, .28, .17);
    glBegin(GL_POLYGON);
    glVertex2f(-.6, .0);
    glVertex2f(-.6, .70);
    glVertex2f(-.7,0.70);
    glVertex2f(-.7, 0.0);
    glEnd();

    glColor3f(.92, .49, .2);
    glBegin(GL_POLYGON);
    glVertex2f(-.7, .0);
    glVertex2f(-.7, .70);
    glVertex2f(-.8,0.70);
    glVertex2f(-.8, 0.0);
    glEnd();

    glColor3f(.77, .28, .17);
    glBegin(GL_POLYGON);
    glVertex2f(-.6, .70);
    glVertex2f(-.59, .72);
    glVertex2f(-.69,0.72);
    glVertex2f(-.7, 0.7);
    glEnd();

    glColor3f(.92, .49, .2);
    glBegin(GL_POLYGON);
    glVertex2f(-.7, .70);
    glVertex2f(-.69, .72);
    glVertex2f(-.81,0.72);
    glVertex2f(-.80, 0.7);
    glEnd();




    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.64);
    glVertex2f(-.71, 0.64);
    glVertex2f(-.71, 0.68);
    glVertex2f(-.79, 0.68);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.64);
    glVertex2f(-.61, 0.64);
    glVertex2f(-.61, 0.68);
    glVertex2f(-.69, 0.68);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.56);
    glVertex2f(-.71, 0.56);
    glVertex2f(-.71, 0.6);
    glVertex2f(-.79, 0.6);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.56);
    glVertex2f(-.61, 0.56);
    glVertex2f(-.61, 0.6);
    glVertex2f(-.69, 0.6);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.48);
    glVertex2f(-.71, 0.48);
    glVertex2f(-.71, 0.52);
    glVertex2f(-.79, 0.52);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.48);
    glVertex2f(-.61, 0.48);
    glVertex2f(-.61, 0.52);
    glVertex2f(-.69, 0.52);
    glEnd();


    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.4);
    glVertex2f(-.71, 0.4);
    glVertex2f(-.71, 0.44);
    glVertex2f(-.79, 0.44);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.4);
    glVertex2f(-.61, 0.4);
    glVertex2f(-.61, 0.44);
    glVertex2f(-.69, 0.44);
    glEnd();


    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.32);
    glVertex2f(-.71, 0.32);
    glVertex2f(-.71, 0.36);
    glVertex2f(-.79, 0.36);
    glEnd();


    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.32);
    glVertex2f(-.61, 0.32);
    glVertex2f(-.61, 0.36);
    glVertex2f(-.69, 0.36);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.24);
    glVertex2f(-.61, 0.24);
    glVertex2f(-.61, 0.28);
    glVertex2f(-.69, 0.28);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.24);
    glVertex2f(-.71, 0.24);
    glVertex2f(-.71, 0.28);
    glVertex2f(-.79, 0.28);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.16);
    glVertex2f(-.71, 0.16);
    glVertex2f(-.71, 0.20);
    glVertex2f(-.79, 0.20);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.16);
    glVertex2f(-.61, 0.16);
    glVertex2f(-.61, 0.20);
    glVertex2f(-.69, 0.20);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.08);
    glVertex2f(-.71, 0.08);
    glVertex2f(-.71, 0.12);
    glVertex2f(-.79, 0.12);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.08);
    glVertex2f(-.61, 0.08);
    glVertex2f(-.61, 0.12);
    glVertex2f(-.69, 0.12);
    glEnd();
}
void urbanbuilding4()
{
    //2nd gray

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0.25,0.0);
    glVertex2f(0.25, 0.60);
    glVertex2f(0.45, 0.60);
    glVertex2f(0.45, 0.0);
    glPopMatrix();
    glEnd();

    glColor3f(.22, .55, 1.25);
    glBegin(GL_POLYGON);
    glVertex2f(0.25, 0);
    glVertex2f(.25, 0.6);
    glVertex2f(.45,.6);
    glVertex2f(0.45, 0);
    glEnd();

    glColor3f(0.31, 0.36, 0.43);
    glBegin(GL_POLYGON);
    glVertex2f(0.45, 0);
    glVertex2f(.45, 0.6);
    glVertex2f(.53,.6);
    glVertex2f(0.53, 0);
    glEnd();

    glColor3f(.62, .65, .68);
    glBegin(GL_POLYGON);
    glVertex2f(0.25, 0);
    glVertex2f(.25, 0.6);
    glVertex2f(.29,.6);
    glVertex2f(0.29, 0);
    glEnd();

    glColor3f(.62, .65, .68);
    glBegin(GL_POLYGON);
    glVertex2f(0.33, 0);
    glVertex2f(.33, 0.6);
    glVertex2f(.37,.6);
    glVertex2f(0.37, 0);
    glEnd();

    glColor3f(.62, .65, .68);
    glBegin(GL_POLYGON);
    glVertex2f(0.41, 0);
    glVertex2f(.41, 0.6);
    glVertex2f(.45,.6);
    glVertex2f(0.45, 0);
    glEnd();

    glColor3f(.62, .65, .68);
    glBegin(GL_POLYGON);
    glVertex2f(0.25, .60);
    glVertex2f(.45,.6);
    glVertex2f(0.45, .55);
    glVertex2f(0.25, .55);
    glEnd();

    glColor3f(.62, .65, .68);
    glBegin(GL_POLYGON);
    glVertex2f(0.25, .50);
    glVertex2f(.45,.50);
    glVertex2f(0.45, .45);
    glVertex2f(0.25, .45);
    glEnd();


    glColor3f(.62, .65, .68);
    glBegin(GL_POLYGON);
    glVertex2f(0.25, .40);
    glVertex2f(.45,.40);
    glVertex2f(0.45, .35);
    glVertex2f(0.25, .35);
    glEnd();

    glColor3f(.62, .65, .68);
    glBegin(GL_POLYGON);
    glVertex2f(0.25, .3);
    glVertex2f(.45,.3);
    glVertex2f(0.45, .25);
    glVertex2f(0.25, .25);
    glEnd();

    glColor3f(.62, .65, .68);
    glBegin(GL_POLYGON);
    glVertex2f(0.25, .2);
    glVertex2f(.45,.2);
    glVertex2f(0.45, .15);
    glVertex2f(0.25, .15);
    glEnd();


    glColor3f(.62, .65, .68);
    glBegin(GL_POLYGON);
    glVertex2f(0.25, .0);
    glVertex2f(.45,.0);
    glVertex2f(0.45, .05);
    glVertex2f(0.25, .05);
    glEnd();

    glColor3f(.62, .65, .68);
    glBegin(GL_POLYGON);
    glVertex2f(0.25, .05);
    glVertex2f(.45,.05);
    glVertex2f(0.45, .1);
    glVertex2f(0.25, .1);
    glEnd();



    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(0.28, .0);
    glVertex2f(.42,.0);
    glVertex2f(0.42, .08);
    glVertex2f(0.28, .08);
    glEnd();

}
void urbanbuilding5(float r,float g,float b)
{
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    glVertex2f(-.4,-.75);
    glVertex2f(-.4,-.25);
    glVertex2f(-.6,-.25);
    glVertex2f(-.6,-.75);
    glEnd();



    //Windows

    glColor3f(0.14, 0.14, 0.14);
    glBegin(GL_QUADS);
    glVertex2f(-.58,-.3);
    glVertex2f(-.52,-.3);
    glVertex2f(-.52,-.375);
    glVertex2f(-.58,-.375);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-.58,-.45);
    glVertex2f(-.52,-.45);
    glVertex2f(-.52,-.525);
    glVertex2f(-.58,-.525);
    glEnd();


    glBegin(GL_QUADS);
    glVertex2f(-.58,-.6);
    glVertex2f(-.52,-.6);
    glVertex2f(-.52,-.675);
    glVertex2f(-.58,-.675);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-.48,-.3);
    glVertex2f(-.42,-.3);
    glVertex2f(-.42,-.375);
    glVertex2f(-.48,-.375);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-.48,-.45);
    glVertex2f(-.42,-.45);
    glVertex2f(-.42,-.525);
    glVertex2f(-.48,-.525);
    glEnd();


    glBegin(GL_QUADS);
    glVertex2f(-.48,-.6);
    glVertex2f(-.42,-.6);
    glVertex2f(-.42,-.675);
    glVertex2f(-.48,-.675);
    glEnd();

}

void urbanbuilding6(float r,float g,float b)
{
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    glVertex2f(-.4,-.75);
    glVertex2f(-.4,-.25);
    glVertex2f(-.6,-.25);
    glVertex2f(-.6,-.75);
    glEnd();



    glColor3f(0.14, 0.14, 0.14);
    glBegin(GL_QUADS);
    glVertex2f(-.58,-.3);
    glVertex2f(-.52,-.3);
    glVertex2f(-.52,-.375);
    glVertex2f(-.58,-.375);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-.58,-.45);
    glVertex2f(-.52,-.45);
    glVertex2f(-.52,-.525);
    glVertex2f(-.58,-.525);
    glEnd();


    glBegin(GL_QUADS);
    glVertex2f(-.58,-.6);
    glVertex2f(-.52,-.6);
    glVertex2f(-.52,-.675);
    glVertex2f(-.58,-.675);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-.48,-.3);
    glVertex2f(-.42,-.3);
    glVertex2f(-.42,-.375);
    glVertex2f(-.48,-.375);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-.48,-.45);
    glVertex2f(-.42,-.45);
    glVertex2f(-.42,-.525);
    glVertex2f(-.48,-.525);
    glEnd();


    glBegin(GL_QUADS);
    glVertex2f(-.48,-.6);
    glVertex2f(-.42,-.6);
    glVertex2f(-.42,-.675);
    glVertex2f(-.48,-.675);
    glEnd();

}


urbanbuilding7()
{

    //last tall building

    glColor3f(0.49, 0.2, 0.45);
    glBegin(GL_POLYGON);
    glVertex2f(-.6, .0);
    glVertex2f(-.6, .70);
    glVertex2f(-.7,0.70);
    glVertex2f(-.7, 0.0);
    glEnd();

    glColor3f(0.85, 0.36, 0.77);
    glBegin(GL_POLYGON);
    glVertex2f(-.7, .0);
    glVertex2f(-.7, .70);
    glVertex2f(-.8,0.70);
    glVertex2f(-.8, 0.0);
    glEnd();

    glColor3f(0.49, 0.2, 0.45);
    glBegin(GL_POLYGON);
    glVertex2f(-.6, .70);
    glVertex2f(-.59, .72);
    glVertex2f(-.69,0.72);
    glVertex2f(-.7, 0.7);
    glEnd();

    glColor3f(0.85, 0.36, 0.77);
    glBegin(GL_POLYGON);
    glVertex2f(-.7, .70);
    glVertex2f(-.69, .72);
    glVertex2f(-.81,0.72);
    glVertex2f(-.80, 0.7);
    glEnd();




    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.64);
    glVertex2f(-.71, 0.64);
    glVertex2f(-.71, 0.68);
    glVertex2f(-.79, 0.68);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.64);
    glVertex2f(-.61, 0.64);
    glVertex2f(-.61, 0.68);
    glVertex2f(-.69, 0.68);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.56);
    glVertex2f(-.71, 0.56);
    glVertex2f(-.71, 0.6);
    glVertex2f(-.79, 0.6);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.56);
    glVertex2f(-.61, 0.56);
    glVertex2f(-.61, 0.6);
    glVertex2f(-.69, 0.6);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.48);
    glVertex2f(-.71, 0.48);
    glVertex2f(-.71, 0.52);
    glVertex2f(-.79, 0.52);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.48);
    glVertex2f(-.61, 0.48);
    glVertex2f(-.61, 0.52);
    glVertex2f(-.69, 0.52);
    glEnd();


    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.4);
    glVertex2f(-.71, 0.4);
    glVertex2f(-.71, 0.44);
    glVertex2f(-.79, 0.44);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.4);
    glVertex2f(-.61, 0.4);
    glVertex2f(-.61, 0.44);
    glVertex2f(-.69, 0.44);
    glEnd();


    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.32);
    glVertex2f(-.71, 0.32);
    glVertex2f(-.71, 0.36);
    glVertex2f(-.79, 0.36);
    glEnd();


    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.32);
    glVertex2f(-.61, 0.32);
    glVertex2f(-.61, 0.36);
    glVertex2f(-.69, 0.36);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.24);
    glVertex2f(-.61, 0.24);
    glVertex2f(-.61, 0.28);
    glVertex2f(-.69, 0.28);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.24);
    glVertex2f(-.71, 0.24);
    glVertex2f(-.71, 0.28);
    glVertex2f(-.79, 0.28);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.16);
    glVertex2f(-.71, 0.16);
    glVertex2f(-.71, 0.20);
    glVertex2f(-.79, 0.20);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.16);
    glVertex2f(-.61, 0.16);
    glVertex2f(-.61, 0.20);
    glVertex2f(-.69, 0.20);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.79, 0.08);
    glVertex2f(-.71, 0.08);
    glVertex2f(-.71, 0.12);
    glVertex2f(-.79, 0.12);
    glEnd();

    glColor3f(.37, .36, .36);
    glBegin(GL_POLYGON);
    glVertex2f(-.69, 0.08);
    glVertex2f(-.61, 0.08);
    glVertex2f(-.61, 0.12);
    glVertex2f(-.69, 0.12);
    glEnd();
}
void urbanareatopofbridge()
{
    drawTree1(.6,.2,.3,.6,.4);
    drawTree2(.6,.2,.32,.5,.4);
    drawTree2(.6,.2,.6,.5,.4);
    //LAYER 1
    shiftX = -0.2;
    shiftY = 0.3;
    scaleX = 0.8;
    scaleY = 0.8;
    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    urbanbuilding2();
    glPopMatrix();

    shiftX = 1.6;
    shiftY = 0.3;
    scaleX = 0.9;
    scaleY = 0.9;
    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    urbanbuilding7();
    glPopMatrix();

    drawTree1(.6,.2,.9,.3,.4);


    //LAYER 2


    shiftX = 1;
    shiftY = 0.6;
    scaleX = 1;
    scaleY = 1.2;
    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    urbanbuilding5(0.48, 0.76, 0.99);
    glPopMatrix();

    shiftX = 1.24;
    shiftY = 0.6;
    scaleX = 1;
    scaleY = 1.8;
    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    urbanbuilding6(0.91, 0.34, 0.22);
    glPopMatrix();

    //front
    shiftX = 1;
    shiftY = -.35;

    scaleX = 1.2;
    scaleY = 1.2;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    urbanbuilding1();
    glPopMatrix();



    shiftX = 1.27;
    shiftY = -.4;

    scaleX = 1;
    scaleY = 1;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    urbanbuilding3();
    glPopMatrix();


    shiftX = 0.04;
    shiftY = -.45;

    scaleX = 0.8;
    scaleY = 0.9;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    urbanbuilding4();
    glPopMatrix();







}

//URBAN FRONTSIDE

void urbanshop1()
{
    glColor3f(.69, .11, .11);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(0.20, 0.0);
    glVertex2f(0.20, 0.30);
    glVertex2f(0, 0.30);
    glEnd();

    glColor3f(.44, 0.06, 0.06);
    glBegin(GL_POLYGON);
    glVertex2f(0.20, 0.0);
    glVertex2f(0.25, 0.0);
    glVertex2f(0.25, 0.30);
    glVertex2f(0.2, 0.30);
    glEnd();


    glColor3f(0.24, 0.22, 0.22);
    glBegin(GL_POLYGON);
    glVertex2f(0.02, .14);
    glVertex2f(0.18, 0.14);
    glVertex2f(0.18, 0.26);
    glVertex2f(0.02, 0.26);
    glEnd();

    glColor3f(.69, .11, .11);
    glLineWidth(5.0);
    glBegin(GL_LINES);//line
    glVertex2f(0.07,0.0);
    glVertex2f(0.07,0.3);
    glEnd();

    glColor3f(.69, .11, .11);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex2f(0.13,0.0);
    glVertex2f(0.13,0.3);
    glEnd();

    glColor3f(.69, .11, .11);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex2f(0.0,0.20);
    glVertex2f(0.20,0.20);
    glEnd();


    glColor3f(0.24, 0.22, 0.22);
    glBegin(GL_POLYGON);
    glVertex2f(0.07, .0);
    glVertex2f(0.13, 0.0);
    glVertex2f(0.13, 0.08);
    glVertex2f(0.07, 0.08);
    glEnd();


    glColor3f(0.95, 0.7, 0.39);
    glBegin(GL_POLYGON);
    glVertex2f(0.06, .08);
    glVertex2f(0.14, 0.08);
    glVertex2f(0.14, 0.10);
    glVertex2f(0.06, 0.10);
    glEnd();

}
void urbanshop2()
{


    glColor3f(0.98, 0.78, 0.02);
    glBegin(GL_POLYGON);
    glVertex2f(0.25, .0);
    glVertex2f(0.45, 0.0);
    glVertex2f(0.45, 0.13);
    glVertex2f(0.25, 0.13);
    glEnd();


    glColor3f(0.98, 0.78, 0.02);
    glBegin(GL_POLYGON);
    glVertex2f(0.45, 0.13);
    glVertex2f(0.46, 0.15);
    glVertex2f(0.24, 0.15);
    glVertex2f(0.25, 0.13);
    glEnd();


    glColor3f(0.47, 0.47, 0.45);
    glBegin(GL_POLYGON);
    glVertex2f(0.26, 0.04);
    glVertex2f(0.44, 0.04);
    glVertex2f(0.44, 0.11);
    glVertex2f(0.26, 0.11);
    glEnd();

    glColor3f(0.98, 0.78, 0.02);
    glLineWidth(5.0);
    glBegin(GL_LINES);//line
    glVertex2f(0.32,0.0);
    glVertex2f(0.32,0.15);
    glEnd();

    glColor3f(0.98, 0.78, 0.02);
    glLineWidth(5.0);
    glBegin(GL_LINES);//line
    glVertex2f(0.39,0.0);
    glVertex2f(0.39,0.15);
    glEnd();

    glColor3f(0.98, 0.78, 0.02);
    glLineWidth(3.0);
    glBegin(GL_LINES);//line
    glVertex2f(0.35,0.0);
    glVertex2f(0.35,0.15);
    glEnd();





}
void urbanshop3()
{
    glColor3f(0.05, 0.43, 0.53);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(0.20, 0.0);
    glVertex2f(0.20, 0.30);
    glVertex2f(0, 0.30);
    glEnd();
    glColor3f(0.06, 0.07, 0.08);
    glBegin(GL_POLYGON);
    glVertex2f(0.02, .14);
    glVertex2f(0.18, 0.14);
    glVertex2f(0.18, 0.26);
    glVertex2f(0.02, 0.26);
    glEnd();

    glColor3f(0.05, 0.43, 0.53);
    glLineWidth(5.0);
    glBegin(GL_LINES);//line
    glVertex2f(0.07,0.0);
    glVertex2f(0.07,0.3);
    glEnd();

    glColor3f(0.05, 0.43, 0.53);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex2f(0.13,0.0);
    glVertex2f(0.13,0.3);
    glEnd();

    glColor3f(0.05, 0.43, 0.53);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex2f(0.0,0.20);
    glVertex2f(0.20,0.20);
    glEnd();


    glColor3f(0.47, 0.15, 0.01);
    glBegin(GL_POLYGON);
    glVertex2f(0.07, .0);
    glVertex2f(0.13, 0.0);
    glVertex2f(0.13, 0.08);
    glVertex2f(0.07, 0.08);
    glEnd();


    glColor3f(0.95, 0.7, 0.39);
    glBegin(GL_POLYGON);
    glVertex2f(0.06, .08);
    glVertex2f(0.14, 0.08);
    glVertex2f(0.14, 0.10);
    glVertex2f(0.06, 0.10);
    glEnd();

}


void urbanareabottomofbridge()
{
    shiftX = 01;
    shiftY = -.8;

    scaleX = .8;
    scaleY = 1;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    urbanshop1();
    glPopMatrix();


    shiftX = 0.2;
    shiftY = -.5;

    scaleX = 1.2;
    scaleY = 1.6;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    urbanshop2();
    glPopMatrix();



    shiftX = 0.46;
    shiftY = -.67;

    scaleX = .8;
    scaleY = 1.2;
    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    urbanshop3();
    glPopMatrix();


    //Walking Road
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(0.38, -.795);
    glVertex2f(1, -.795);
    glVertex2f(1, -.845);
    glVertex2f(.4,-.845);
    glEnd();


    drawbush2(0.54, -1.18,0.7);

    drawBush(.54, -.85, 0.02, 3, 0.1);
    drawBush(.54, -.78, 0.02,5, 0.1);
    drawBush(.8, -.78, 0.03,5, 0.1);
    drawTree2(.4, .2, .8, -.82, .4);
    drawTree1(.4, .2, .76, -.86, .2);
    drawTree2(.4, .2, .84, -.91, .3);
    drawTree1(.4, .2, .65, -.86, .3);
    drawTree2(.4, .2, .53, -.82, .35);
    drawTree2(.4, .2, .57, -.9, .35);
    drawTree1(.36, .2, .51, -.9, .35);
    drawTree1(.36, .2, .91, -.9, .35);
}

/*------------------------------------URBAN AREA END----------------------*/


/*--------------------------------------SLUM AREA START-----------------------------*/
void village1(float r1,float g1,float b1,float r2,float g2, float b2)
{
    glColor3f(r1,g1,b1);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f,0.0f) ;
    glVertex2f(0.4f,0.0f);
    glVertex2f(0.4f,0.26f);
    glVertex2f(0.0f,0.26f);
    glVertex2f(0.0f,0.0f) ;

    glEnd();


    glColor3f(r2,g2,b2);
    glBegin(GL_POLYGON);
    glVertex2f(0.04f,0.2f) ;
    glVertex2f(0.44f,0.2f);
    glVertex2f(0.4f,0.26f);
    glVertex2f(0.0f,0.26f);
    glVertex2f(-0.04f,0.2f) ;

    glEnd();


    glColor3f(0.0f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(0.26f,0.0f) ;
    glVertex2f(0.34f,0.0f);
    glVertex2f(0.34f,0.16f);
    glVertex2f(0.26f,0.16f);
    glVertex2f(0.26f,0.0f) ;

    glEnd();


    glColor3f(0.0f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(0.02f,0.1f) ;
    glVertex2f(0.08f,0.1f);
    glVertex2f(0.08f,0.16f);
    glVertex2f(0.02f,0.16f);
    glVertex2f(0.02f,0.1f) ;

    glEnd();

    glColor3f(0.0f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(0.12f,0.1f) ;
    glVertex2f(0.18f,0.1f);
    glVertex2f(0.18f,0.16f);
    glVertex2f(0.12f,0.16f);
    glVertex2f(0.12f,0.1f) ;

    glEnd();

}
void village2(float r1,float g1,float b1,float r2,float g2, float b2)
{
    glColor3f(r1,g1,b1);
    glBegin(GL_POLYGON);
    glVertex2f(0.52f,0.0f) ;
    glVertex2f(0.92f,0.0f);
    glVertex2f(0.92f,0.32f);
    glVertex2f(0.52f,0.26f);
    glVertex2f(0.52f,0.0f) ;

    glEnd();

    glColor3f(r2,g2,b2);
    glBegin(GL_POLYGON);
    glVertex2f(0.5f,0.28f) ;
    glVertex2f(0.5f,0.25f);
    glVertex2f(0.94f,0.31f);
    glVertex2f(0.94f,0.34f);
    glVertex2f(0.5f,0.28f) ;

    glEnd();

    glColor3f(0.06f, 0.04f, 0.03f);
    glBegin(GL_POLYGON);
    glVertex2f(0.78f,0.0f) ;
    glVertex2f(0.9f,0.0f);
    glVertex2f(0.9f,0.26f);
    glVertex2f(0.78f,0.26f);
    glVertex2f(0.78f,0.0f) ;

    glEnd();


    glColor3f(0.84f, 0.67f, 0.57f);
    glBegin(GL_POLYGON);
    glVertex2f(0.8f,0.0f) ;
    glVertex2f(0.88f,0.0f);
    glVertex2f(0.88f,0.24f);
    glVertex2f(0.8f,0.24f);
    glVertex2f(0.8f,0.0f) ;

    glEnd();


    glColor3f(0.06f, 0.04f, 0.03f);
    glBegin(GL_POLYGON);
    glVertex2f(0.58f,0.12f) ;
    glVertex2f(0.72f,0.12f);
    glVertex2f(0.72f,0.26f);
    glVertex2f(0.58f,0.26f);
    glVertex2f(0.58f,0.12f) ;

    glEnd();
}

void village3(float r1,float g1,float b1,float r2,float g2, float b2)
{

    glColor3f(r1,g1,b1);
    glBegin(GL_POLYGON);
    glVertex2f(-0.52f,0.0f) ;
    glVertex2f(-0.22f,0.0f);
    glVertex2f(-0.22f,0.2f);
    glVertex2f(-0.52f,0.2f);
    glVertex2f(-0.52f,0.0f) ;

    glEnd();

    glColor3f(r2,g2,b2);
    glBegin(GL_POLYGON);
    glVertex2f(-0.54f,0.2f) ;
    glVertex2f(-0.2f,0.2f);
    glVertex2f(-0.2f,0.22f);
    glVertex2f(-0.54f,0.22f);
    glVertex2f(-0.54f,0.2f) ;

    glEnd();

    glColor3f(r1,g1,b1);
    glBegin(GL_POLYGON);
    glVertex2f(-0.52f,0.22f) ;
    glVertex2f(-0.22f,0.22f);
    glVertex2f(-0.22f,0.42f);
    glVertex2f(-0.52f,0.42f);
    glVertex2f(-0.52f,0.22f) ;

    glEnd();
    glColor3f(r2,g2,b2);
    glBegin(GL_POLYGON);
    glVertex2f(-0.54f,0.42f) ;
    glVertex2f(-0.2f,0.42f);
    glVertex2f(-0.2f,0.44f);
    glVertex2f(-0.54f,0.44f);
    glVertex2f(-0.54f,0.42f) ;

    glEnd();


    glColor3f(0.28f, 0.21f, 0.16f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.32f,0.16f) ;
    glVertex2f(-0.26f,0.16f);
    glVertex2f(-0.26f,0.06f);
    glVertex2f(-0.32f,0.06f);
    glVertex2f(-0.32f,0.16f) ;

    glEnd();



}

void village4(float r1,float g1,float b1,float r2,float g2, float b2)
{
    glColor3f(0.44f, 0.57f, 0.52f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.88f,0.0f) ;
    glVertex2f(-0.60f,0.0f);
    glVertex2f(-0.60f,0.2f);
    glVertex2f(-0.88f,0.26f);
    glVertex2f(-0.88f,0.0f) ;

    glEnd();

    glColor3f(0.24f, 0.17f, 0.08f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.90f,0.26f) ;
    glVertex2f(-0.90f,0.29f);
    glVertex2f(-0.58f,0.21f);
    glVertex2f(-0.58f,0.19f);
    glVertex2f(-0.90f,0.27f) ;

    glEnd();


    glColor3f(0.14f, 0.12f, 0.38f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.86f,0.0f) ;
    glVertex2f(-0.78f,0.0f);
    glVertex2f(-0.78f,0.16f);
    glVertex2f(-0.86f,0.16f);
    glVertex2f(-0.86f,0.0f) ;

    glEnd();

    glColor3f(0.14f, 0.12f, 0.38f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.74f,0.08f) ;
    glVertex2f(-0.62f,0.08f);
    glVertex2f(-0.62f,0.16f);
    glVertex2f(-0.74f,0.16f);
    glVertex2f(-0.74f,0.08f) ;

    glEnd();


}

void village5()
{
    glColor3f(0.69, 0.56, 0.06);
    glBegin(GL_QUADS);
    glVertex2f(0.2, -0.375);
    glVertex2f(0.6, -0.375);
    glVertex2f(0.6, -0.75);
    glVertex2f(0.2, -0.75);
    glEnd();

    glColor3f(0.18, 0.17, 0.14);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.14,- 0.375);
    glVertex2f(0.4,- 0.075);
    glVertex2f(0.66, -0.375);
    glEnd();

    glColor3f(0.05, 0.05, 0.05);
    glBegin(GL_QUADS);
    glVertex2f(0.36, -0.75);
    glVertex2f(0.44, -0.75);
    glVertex2f(0.44, -0.6);
    glVertex2f(0.36, -0.6);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.26, -0.55);
    glVertex2f(0.32, -0.55);
    glVertex2f(0.32, -0.475);
    glVertex2f(0.26, -0.475);
    glEnd();


    glBegin(GL_QUADS);
    glVertex2f(0.48, -0.55);
    glVertex2f(0.54, -0.55);
    glVertex2f(0.54, -0.475);
    glVertex2f(0.48, -0.475);
    glEnd();




}

void villageareatopofbridge()
{


    drawTree2(.45,.2,-.7,.225,0.45);
    drawTree2(.4,.2,-.56,.225,0.2);
    drawTree1(.55,.2,-.6,.2,0.3);

    drawTree2(.4,.2,-.74,.225,0.2);

    drawTree1(.52,.2,-.72,.2,0.3);
    drawTree1(.52,.2,-.8,.2,0.2);





    shiftX = -.88;
    shiftY = 0;

    scaleX = .4;
    scaleY = 0.6;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    village1(0.88f, 0.75f, 0.18f,0.52, 0.68, 0.77);
    glPopMatrix();


    shiftX = -1.7;
    shiftY = .02;

    scaleX = 0.5;
    scaleY = 0.5;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    village2(0.37, 0.32, 0.14,0.2, 0.2, 0.2);
    glPopMatrix();


    shiftX = -.7;
    shiftY = .01;

    scaleX = 0.8;
    scaleY = 0.8;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    village3(0.82, 0.71, 0.3,0.5, 0.99, 0.79);
    glPopMatrix();

    glColor3f(0,0,0);
    renderBitmapString(-0.95, 0.30, GLUT_BITMAP_TIMES_ROMAN_24, "ABC PRIMARY");
    renderBitmapString(-0.92, 0.25, GLUT_BITMAP_TIMES_ROMAN_24, "SCHOOL");


    drawTree1(.52,.2,-.8,00,0.2);
    drawTree1(.52,.2,-.85,-0.01,0.2);
    drawTree1(.52,.2,-.9,-0.0,0.2);
    drawTree1(.52,.2,-.65,-0.0,0.2);
    drawTree2(.52,.2,-.7,0.01,0.2);

    //LAYER 2 START

    shiftX = 0.3;
    shiftY = -.2;

    scaleX = 0.8;
    scaleY = 0.8;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    village4(0.38, 0.54, 0.85,0.5, 0.99, 0.79);
    glPopMatrix();


    shiftX = -1.3;
    shiftY = -.2;

    scaleX = 0.6;
    scaleY = 0.8;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    village1(0.82, 0.71, 0.3,0.5, 0.99, 0.79);
    glPopMatrix();

    //Layer 3 start


    shiftX = -1.5;
    shiftY = 0;

    scaleX = 0.5;
    scaleY = 0.5;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    village5();
    glPopMatrix();


    shiftX = -0.2;
    shiftY = -.4;

    scaleX = 0.9;
    scaleY = 0.9;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    village4(0.57, 0.4, 0.06,0.5, 0.99, 0.79);
    glPopMatrix();
    drawTree2(.52,.2,-.36,-0.3,0.2);
    drawTree1(.52,.2,-.4,-0.3,0.2);






}

void villagemarket()
{
    glColor3f(0.81, 0.3, 0.01);
    glBegin(GL_QUADS);
    glVertex2f(-0.62, -0.725);
    glVertex2f(-0.62, -0.875);
    glVertex2f(-0.86, -0.875);
    glVertex2f(-0.86, -0.725);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.63, -0.725);
    glVertex2f(-0.63, -0.625);

    glVertex2f(-0.85, -0.725);
    glVertex2f(-0.85, -0.625);
    glEnd();


    glColor3f(0.81, 0.3, 0.01);
    glBegin(GL_QUADS);
    glVertex2f(-0.62, -0.625);
    glVertex2f(-0.62, -0.55);
    glVertex2f(-0.86, -0.55);
    glVertex2f(-0.86, -0.625);
    glEnd();

    glColor3f(0.23, 0.21, 0.19);
    glBegin(GL_QUADS);
    glVertex2f(-0.63, -0.75);
    glVertex2f(-0.63, -0.85);
    glVertex2f(-0.85, -0.85);
    glVertex2f(-0.85, -0.75);
    glEnd();

glColor3f(0, 0, 0);
    renderBitmapString(-0.8, -0.6, GLUT_BITMAP_TIMES_ROMAN_24, "MARKET");





}

//-------------------------VILLAGE AREA ENDDD-----------------------------------------------//


//--------------------------------VEHICLES----------------------------------//



void car1() {
    // Base
    glColor3f(0.71, 0.01, 0.07);
    glBegin(GL_POLYGON);
    glVertex2f(carPosX, 0.125);
    glVertex2f(carPosX, 0.2);
    glVertex2f(carPosX + 0.14, 0.2);
    glVertex2f(carPosX + 0.2, 0.175);
    glVertex2f(carPosX + 0.2, 0.125);
    glVertex2f(carPosX, 0.125);
    glEnd();

    // Windows
    glColor3f(0.44, 0.75, 0.93);
    glBegin(GL_POLYGON);
    glVertex2f(carPosX + 0.02, 0.2);
    glVertex2f(carPosX + 0.04, 0.25);
    glVertex2f(carPosX + 0.12, 0.25);
    glVertex2f(carPosX + 0.14, 0.2);
    glVertex2f(carPosX + 0.02, 0.2);
    glEnd();

    // Window border
    glLineWidth(2.0f);
    glColor3f(0.71, 0.01, 0.07);
    glBegin(GL_LINES);
    glVertex2f(carPosX + 0.08, 0.2);
    glVertex2f(carPosX + 0.08, 0.25);
    glEnd();

    // Wheels
    glColor3f(0, 0, 0);
    drawCircle(carPosX + 0.04, 0.125, 0.02);
    drawCircle(carPosX+.14, 0.125, 0.02);
}


void car2(float r,float g,float b)
{
    // Base
    glColor3f(r,g,b);
    glBegin(GL_POLYGON);
    glVertex2f(carPosX2, 0.125);
    glVertex2f(carPosX2, 0.2);
    glVertex2f(carPosX2 + 0.14, 0.2);
    glVertex2f(carPosX2 + 0.2, 0.175);
    glVertex2f(carPosX2 + 0.2, 0.125);
    glVertex2f(carPosX2, 0.125);
    glEnd();

    // Windows
    glColor3f(0.44, 0.75, 0.93);
    glBegin(GL_POLYGON);
    glVertex2f(carPosX2 + 0.02, 0.2);
    glVertex2f(carPosX2 + 0.04, 0.25);
    glVertex2f(carPosX2 + 0.12, 0.25);
    glVertex2f(carPosX2 + 0.14, 0.2);
    glVertex2f(carPosX2 + 0.02, 0.2);
    glEnd();

    // Window border
    glLineWidth(2.0f);
    glColor3f(r,g,b);
    glBegin(GL_LINES);
    glVertex2f(carPosX2 + 0.08, 0.2);
    glVertex2f(carPosX2 + 0.08, 0.25);
    glEnd();

    // Wheels
    glColor3f(0, 0, 0);
    drawCircle(carPosX2 + 0.04, 0.125, 0.02);
    drawCircle(carPosX2 + 0.14, 0.125, 0.02);
}


void truck1() {
    // Base
    glColor3f(0.71, 0.01, 0.07);
    glBegin(GL_POLYGON);
    glVertex2f(truckPosX, 0.125);
    glVertex2f(truckPosX, 0.175);
    glVertex2f(truckPosX + 0.2, 0.175);
    glVertex2f(truckPosX + 0.2, 0.125);
    glEnd();

    // Upper Part
    glColor3f(0.71, 0.01, 0.07);
    glBegin(GL_POLYGON);
    glVertex2f(truckPosX + 0.1, 0.175);
    glVertex2f(truckPosX + 0.1, 0.225);
    glVertex2f(truckPosX + 0.16, 0.225);
    glVertex2f(truckPosX + 0.18, 0.175);
    glEnd();

    // Cabin
    glColor3f(0.79, 0.91, 0.98);
    glBegin(GL_POLYGON);
    glVertex2f(truckPosX + 0.12, 0.175);
    glVertex2f(truckPosX + 0.12, 0.225);
    glVertex2f(truckPosX + 0.162, 0.225);
    glVertex2f(truckPosX + 0.182, 0.175);
    glEnd();

    // Wheels
    glColor3f(0, 0, 0);
    drawCircle(truckPosX + 0.145, 0.125, 0.015);
    drawCircle(truckPosX + 0.055, 0.125, 0.015);
}
void truck2() {
    // Base
    glColor3f(0.1, 0, 0.44);
    glBegin(GL_POLYGON);
    glVertex2f(truckPosX, 0.125);
    glVertex2f(truckPosX, 0.175);
    glVertex2f(truckPosX + 0.2, 0.175);
    glVertex2f(truckPosX + 0.2, 0.125);
    glEnd();

    // Upper Part
    glColor3f(0.1, 0, 0.44);
    glBegin(GL_POLYGON);
    glVertex2f(truckPosX + 0.1, 0.175);
    glVertex2f(truckPosX + 0.1, 0.225);
    glVertex2f(truckPosX + 0.16, 0.225);
    glVertex2f(truckPosX + 0.18, 0.175);
    glEnd();

    // Cabin
    glColor3f(0.79, 0.91, 0.98);
    glBegin(GL_POLYGON);
    glVertex2f(truckPosX + 0.12, 0.175);
    glVertex2f(truckPosX + 0.12, 0.225);
    glVertex2f(truckPosX + 0.162, 0.225);
    glVertex2f(truckPosX + 0.182, 0.175);
    glEnd();

    // Wheels
    glColor3f(0, 0, 0);
    drawCircle(truckPosX + 0.145, 0.125, 0.015);
    drawCircle(truckPosX + 0.055, 0.125, 0.015);
}


void drawYacht(float x) {
    // Draw the body of the yacht
    glColor3f(0.94, 0.94, 0.94); // Gray color
    glBegin(GL_POLYGON);
    glVertex2f(0.26 + x, 0.075);
    glVertex2f(0.42 + x, 0.075);
    glVertex2f(0.4 + x, 0.125);
    glVertex2f(0.2 + x, 0.125);
    glEnd();

    //roof
    glColor3f(0.23, 0.75, 0.81);
    glBegin(GL_POLYGON);
    glVertex2f(0.26 + x, 0.125);
    glVertex2f(0.28 + x, 0.15);
    glVertex2f(0.36 + x, 0.15);
    glVertex2f(0.38 + x, 0.125);
    glEnd();

    //window
    glColor3f(0.11, 0.12, 0.13);
    glBegin(GL_LINES);
    glVertex2f(0.32 + x, 0.125);
    glVertex2f(0.32 + x, 0.15);
    glEnd();

    //bottom
    glColor3f(0.02, 0.1, 0.25); // Gray color
    glBegin(GL_POLYGON);
    glVertex2f(0.26 + x, 0.075);
    glVertex2f(0.42 + x, 0.075);
    glVertex2f(0.41 + x, 0.0875);
    glVertex2f(0.25 + x, 0.0875);
    glEnd();
}


void vehicles()
{
     shiftX = 0;
    shiftY = -.7;

    scaleX = .7;
    scaleY = .7;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    car1();
    glPopMatrix();

    shiftX = 0;
    shiftY = -.7;

    scaleX = .7;
    scaleY = .7;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    car2(0.52, 0, 0.39);
    glPopMatrix();

    shiftX = 0;
    shiftY = -0.7;

    scaleX = .7;
    scaleY = .7;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    truck1();
    glPopMatrix();


    shiftX = 0;
    shiftY = -0.8;

    scaleX = -.7;
    scaleY = .75;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    truck2();
    glPopMatrix();


    shiftX = 0;
    shiftY = -0.8;

    scaleX = -.7;
    scaleY = .75;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    car2(0.01, 0.77, 0.67);
    glPopMatrix();

}




/*----------------ANIMATION UPDATE FUNCTIONS HERE----------------------------*/
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            isRightKeyPressed = true;
            isLeftKeyPressed = false;
            break;
        case GLUT_KEY_LEFT:
            isLeftKeyPressed = true;
            isRightKeyPressed = false;
            break;
    }
}

void specialKeysUp(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            isRightKeyPressed = false;
            break;
        case GLUT_KEY_LEFT:
            isLeftKeyPressed = false;
            break;
    }
}



void updatesun(int value)
{
    updateSunPosition();
    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(16, updatesun, 0); // Schedule the next update
}

// Function to update rotation angle
void updatewindmill(int value)
{
    angle += spinSpeed;
    if (angle > 360)
    {
        angle -= 360;
    }
    glutPostRedisplay();
    glutTimerFunc(16, updatewindmill, 0);
}

void updatecar1(int value) {
     float speedAdjustment = 0.01; // Base speed adjustment
    if (isRightKeyPressed) {
        speedAdjustment += 0.005; // Increase speed if right arrow is pressed
    } else if (isLeftKeyPressed) {
        speedAdjustment -= 0.005; // Decrease speed if left arrow is pressed
    }

    // Update the car's position
    carPosX += speedAdjustment;

    // Check if the car has reached the right edge of the screen
    if (carPosX > 2.6) {
        carPosX = -1.8; // Reset car position to the left side of the screen
    }

    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(16, updatecar1, 0); // Call update function after 16 milliseconds

}
void updatecar2(int value) {
    float speedAdjustment = 0.01; // Base speed adjustment
    if (isRightKeyPressed) {
        speedAdjustment += 0.005; // Increase speed if right arrow is pressed
    } else if (isLeftKeyPressed) {
        speedAdjustment -= 0.005; // Decrease speed if left arrow is pressed
    }

    // Update the car's position
    carPosX2 += speedAdjustment;

    // Check if the car has reached the right edge of the screen
    if (carPosX2 > 2.2) {
        carPosX2 = -2.2; // Reset car position to the left side of the screen
    }

    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(16, updatecar2, 0); // Call update function after 16 milliseconds
}

void updatetruck1(int value) {
    float speedAdjustment = 0.01; // Base speed adjustment
    if (isRightKeyPressed) {
        speedAdjustment += 0.005; // Increase speed if right arrow is pressed
    } else if (isLeftKeyPressed) {
        speedAdjustment -= 0.005; // Decrease speed if left arrow is pressed
    }

    // Update the truck's position
    truckPosX += speedAdjustment;

    // Check if the truck has reached the right edge of the screen
    if (truckPosX > 1.8) {
        truckPosX = -2.6; // Reset truck position to the left side of the screen
    }

    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(16, updatetruck1, 0); // Call update function after 16 milliseconds
}



void updateriver(int value) {
    // Update the offset to shift the lines
    xOffset += 0.001;

    // Wrap around the offset to create an endless loop
    if (xOffset > 0.2)
        xOffset = 0.0;

    glutPostRedisplay(); // Trigger a redraw
    glutTimerFunc(16, updateriver, 0); // Call update function after 16 milliseconds (for ~60 FPS)
}

void updateyacht(int value) {
    // Update the x-coordinate to move the yacht from right to left
    yachtPositionX -= 0.00098;

    // Reset the position if it goes off the left edge of the screen
    if (yachtPositionX < -1.0)
        yachtPositionX = 0.60;

    glutPostRedisplay(); // Trigger a redraw
    glutTimerFunc(16, updateyacht, 0); // Call update function after 16 milliseconds (for ~60 FPS)
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Call the function to draw lines
    drawLines();
    drawskyline();
    createSky();
    drawGlowingSun(sunX, sunY, sunRadius, numSegments);

    createRiver();
    riverlines();
    industry();
    createurbanground();
    createslumground();
    urbanareatopofbridge();

    shiftX = -1;
    shiftY = 0.38;

    scaleX = 0.7;
    scaleY = 0.7;

    glPushMatrix();
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(shiftX, shiftY, 0.0f);
    drawYacht(yachtPositionX);

    glPopMatrix();

    villageareatopofbridge();
    createBridge();
    vehicles();
    urbanareabottomofbridge();
    villagemarket();






    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1); // Set the coordinate system from -1 to 1 in both directions
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1600, 1200);
    glutCreateWindow("SCENE-1");

    // Set background color to white
    glClearColor(1.0, 1.0, 1.0, 1.0);


    //ANIMATION FUNCTIONS
    glutTimerFunc(0, updatewindmill, 0);
    glutTimerFunc(0,updatecar1, 0);
    glutTimerFunc(0,updatecar2, 0);
    glutTimerFunc(16, updatetruck1, 0);
    glutTimerFunc(0, updatesun, 0); // Start the update loop
    glutTimerFunc(0, updateriver, 0); // Start the update loop
    glutTimerFunc(0, updateyacht, 0); // Start the update loop
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutSpecialUpFunc(specialKeysUp);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

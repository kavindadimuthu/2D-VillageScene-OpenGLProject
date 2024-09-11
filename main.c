#include <GL/glew.h>
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint doorTexture;
GLuint roofTexture;

bool horseMoveFlag = false;
bool boatMoveFlag = false;
bool tailRotateFlag = false;
bool batMoveFlag = false;
bool horseFlipFlag = false;
bool sunMoveFlag = false;

int horsePosX = 500;
int boatPosX = 200;
int sunPosX = 0;

float horseFlipAngle = 1.0;
float batAngle = 0.0;
int horseTailRotation = 0;

const int screenWidth = 1200;
const int horseWidth = 200;
const int boatWidth = 250;

float increasingScale = 1;
float decreasingScale = 1;
float bigFlowerPotRightScale = 1.5f;


GLuint LoadTexture(const char* filename) {
    int width, height, nrChannels;
    GLuint textureID;
    printf("Loading texture: %s\n", filename);

    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
        printf("Texture loaded successfully\n");
    } else {
        printf("Failed to load texture\n");
        textureID = 0;
    }

    return textureID;
}

void setColor(int r, int g, int b)
{
    glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
}

void Circle(int x, int y, int radius, int r, int g, int b)
{
    setColor(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float theta = i * M_PI / 180.0f; // M_PI is from <cmath>
        glVertex2f(x + radius * cos(theta), y + radius * sin(theta));
    }
    glEnd();
}

void Background()
{
    glBegin(GL_POLYGON); //Sky
        setColor(255, 255, 255);
        glVertex2i(0,0);
        glVertex2i(1200,0);
        setColor(255, 230, 0);
        glVertex2i(1200,700);
        glVertex2i(0,700);
    glEnd();
    glBegin(GL_POLYGON); //River
        setColor(20, 101, 230);
        glVertex2i(0, 150);
        glVertex2i(1200, 150);
        glVertex2i(1200, 0);
        glVertex2i(0, 0);
    glEnd();

glBegin(GL_POLYGON); // Land
    setColor(0,177,1);
    glVertex2i(0, 150);
    glVertex2i(0, 200);
    glVertex2i(100, 220);
    glVertex2i(150, 230);
    glVertex2i(200, 240);
    glVertex2i(250, 250);
    glVertex2i(300, 260);
    glVertex2i(350, 270);
    glVertex2i(400, 280);
    glVertex2i(450, 290);
    glVertex2i(500, 295);
    glVertex2i(550, 300);
    glVertex2i(600, 305);
    glVertex2i(650, 310);
    glVertex2i(700, 315);
    glVertex2i(750, 320);
    glVertex2i(800, 325);
    glVertex2i(850, 330);
    glVertex2i(900, 335);
    glVertex2i(950, 340);
    glVertex2i(1000, 345);
    glVertex2i(1050, 350);
    glVertex2i(1100, 355);
    glVertex2i(1150, 360);
    glVertex2i(1200, 365);
    glVertex2i(1200, 150);
glEnd();

}

void Tree(int x, int y)
{
	glBegin(GL_POLYGON);		//rectangular trunk
	glColor3f(0.3, 0.2, 0.1);
	glVertex2i(0 + x, 0 + y);
	glVertex2i(0 + x, 120 + y);
	glVertex2i(20 + x, 120 + y);
	glVertex2i(20 + x, 0 + y);
	glEnd();

	glBegin(GL_POLYGON);		//triangle lower
	setColor(34, 139, 34);
	glVertex2i(x - 60, 120 + y);
	glVertex2i(x + 80, 120 + y);
	glVertex2i(x + 10, 230 + y);
	glEnd();

	glBegin(GL_POLYGON);		//triangle middle
	setColor(34, 139, 34);
	glVertex2i(x - 40, 190 + y);
	glVertex2i(x + 60, 190 + y);
	glVertex2i(x + 10, 300 + y);
	glEnd();

	glBegin(GL_POLYGON);		//triangle upper
	setColor(34, 139, 34);
	glVertex2i(x - 20, 260 + y);
	glVertex2i(x + 40, 260 + y);
	glVertex2i(x + 10, 360 + y);
	glEnd();
}

void TreeWithCircles(int x, int y)
{
	glBegin(GL_POLYGON);		//rectangular trunk
	glColor3f(0.3, 0.2, 0.1);
	glVertex2i(0 + x, 0 + y);
	glVertex2i(0 + x, 120 + y);
	glVertex2i(20 + x, 120 + y);
	glVertex2i(20 + x, 0 + y);
	glEnd();

	glBegin(GL_POLYGON);		//triangle lower
	setColor(34, 139, 34);
	glVertex2i(x - 60, 120 + y);
	glVertex2i(x + 80, 120 + y);
	glVertex2i(x + 10, 230 + y);
	glEnd();

	glBegin(GL_POLYGON);		//triangle middle
	setColor(34, 139, 34);
	glVertex2i(x - 40, 190 + y);
	glVertex2i(x + 60, 190 + y);
	glVertex2i(x + 10, 300 + y);
	glEnd();

	glBegin(GL_POLYGON);		//triangle upper
	setColor(34, 139, 34);
	glVertex2i(x - 20, 260 + y);
	glVertex2i(x + 40, 260 + y);
	glVertex2i(x + 10, 360 + y);
	glEnd();


    glLineWidth(4.0f);
    glBegin(GL_LINES);  //Fruit 1
    setColor(0, 0, 0);
    glVertex2i(x + 40, y + 120);
    glVertex2i(x + 40, y + 80);
    glEnd();
    Circle(x+40, y+80, 10, 225, 5, 0);

    glBegin(GL_LINES); //Fruit 2
    setColor(0, 0, 0);
    glVertex2i(x - 20, y + 120);
    glVertex2i(x - 20, y + 80);
    glEnd();
    Circle(x-20, y+80, 10, 225, 5, 0);
}

void House(int x, int y, float red, float green, float blue)
{
	glBegin(GL_POLYGON);	//House
        setColor(red, green, blue);
        glVertex2i(0 + x, 0 + y);
        glVertex2i(120 + x, 0 + y);
        glVertex2i(120 + x, 116 + y);
        glVertex2i(0 + x, 116 + y);
	glEnd();

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, roofTexture);
	glBegin(GL_POLYGON);	//Roof
        setColor(255, 0, 0); //
        glTexCoord2f(0.0, 1.0); glVertex2i(x - 10, 116 + y);
        glTexCoord2f(1.0, 1.0); glVertex2i(x + 130, 116 + y);
        glTexCoord2f(1.0, 0.0); glVertex2i(x + 100, 156 + y);
        glTexCoord2f(0.0, 0.0); glVertex2i(x + 20, 156 + y);
	glEnd();
    glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, doorTexture);
	glBegin(GL_POLYGON);	 //Door
        setColor(255, 255, 255);
        glTexCoord2f(0.0, 1.0); glVertex2i(x + 40, y + 0);
        glTexCoord2f(1.0, 1.0); glVertex2i(x + 80, y + 0);
        glTexCoord2f(1.0, 0.0); glVertex2i(x + 80, y + 75);
        glTexCoord2f(0.0, 0.0); glVertex2i(x + 40, y + 75);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Boat()
{
    glBegin(GL_POLYGON);	//boat
        glColor3f(0.9, 0.5, 0.1);
        glVertex2i(250, 20);
        glVertex2i(220, 100);
        glVertex2i(550, 100);
        glVertex2i(500, 20);
	glEnd();

    glBegin(GL_POLYGON);	//man body
        glColor3f(1, 1, 1);
        glVertex2i(270, 100);
        glVertex2i(330, 100);
        glVertex2i(310, 150);
        glVertex2i(290, 150);
        glVertex2i(310, 200);
        glVertex2i(270, 200);
        glVertex2i(270, 100);
	glEnd();

    glBegin(GL_POLYGON);	//face
        glColor3f(1.2, 0.5, 0.4);
        glVertex2i(275, 200);
        glVertex2i(295, 200);
        glVertex2i(295, 220);
        glVertex2i(300, 220);
        glVertex2i(295, 250);
        glVertex2i(275, 250);
        glVertex2i(275, 200);
	glEnd();

	glBegin(GL_POLYGON);	//hair
        glColor3f(0.0, 0.0, 0.0);
        glVertex2i(295, 250);
        glVertex2i(300, 270);
        glVertex2i(275, 260);
        glVertex2i(275, 250);
        glVertex2i(295, 250);
	glEnd();

    glPushMatrix();
    glTranslatef(310 , 160, 0.0);
    glRotatef(-batAngle, 0.0, 0.0, 1.0);
    glTranslatef(-310, -160, 0.0);
    glBegin(GL_POLYGON);	//bat
        glColor3f(0.0, 0.0, 0.0);
        glVertex2i(310, 150);
        glVertex2i(250, 0);
        glVertex2i(270, 0);
        glVertex2i(310, 160);
	glEnd();
	glPopMatrix();
}

void Horse()
{
    glBegin(GL_POLYGON);       //horse f-leg
        setColor(255, 255, 255);
        glVertex2i(100, 200);
        glVertex2i(110, 200);
        glVertex2i(110, 250);
        glVertex2i(100, 250);
    glEnd();

    glBegin(GL_POLYGON);    //horse b-leg
        setColor(255, 255, 255);
        glVertex2i(190, 200);
        glVertex2i(180, 200);
        glVertex2i(180, 250);
        glVertex2i(190, 250);
    glEnd();

    glBegin(GL_POLYGON);        //horse body
        setColor(150, 101, 50);
        glVertex2i(100, 250);
        glVertex2i(190, 250);
        glVertex2i(190, 300);
        glVertex2i(100, 300);
    glEnd();

    glBegin(GL_POLYGON);        //horse head
        setColor(150, 101, 50);
        glVertex2i(120, 300);
        glVertex2i(90, 390);
        glVertex2i(60, 330);
        glVertex2i(60, 350);
        glVertex2i(80, 350);
        glVertex2i(100, 300);
    glEnd();

    glBegin(GL_POLYGON); //horse mouth
        setColor(150, 101, 50);
        glVertex2i(150, 300);
        glVertex2i(90, 390);
        glVertex2i(120, 300);
        glVertex2i(150, 300);
    glEnd();

    glBegin(GL_POLYGON);        //horse muscle
        setColor(0, 0, 0);
        glVertex2i(70, 325);
        glVertex2i(70, 351);
        glVertex2i(72, 352);
        glVertex2i(72, 324);
    glEnd();

    glPushMatrix();     //horse tail
    glTranslatef(190, 300, 0.0);
    glRotatef(-horseTailRotation, 0.0, 0.0, 1.0);
    glTranslatef(-190, -300, 0.0);
    glBegin(GL_POLYGON);
        setColor(255, 255, 255);
        glVertex2i(190, 300);
        glVertex2i(200, 220);
        glVertex2i(210, 300);
    glEnd();
    glPopMatrix();

    glPointSize(4);     //horse eye
    glBegin(GL_POINTS);
        setColor(0, 0, 0);
        glVertex2i(85, 360);
    glEnd();
}


void FlowerPot(float x, float y)
{
    //flowers
Circle(x - 20, y + 25, 10, 255, 105, 180); // Pink
Circle(x + 20, y + 35, 10, 128, 0, 128);  // Purple
Circle(x, y + 60, 10, 255, 0, 0);          // Red


    // Pot
    setColor(204, 153, 51);
    glBegin(GL_POLYGON);
    glVertex2f(x - 10, y - 40);
    glVertex2f(x + 10, y - 40);
    glVertex2f(x + 20, y);
    glVertex2f(x - 20, y);
    glEnd();

    // Branches
    setColor(204, 153, 51);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y + 50);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(x, y + 25);
    glVertex2f(x - 10, y + 25);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(x, y + 35);
    glVertex2f(x + 10, y + 35);
    glEnd();
}

void YellowFish(int x, int y)
{
    // Draw the body of the fish (a quad)
    glBegin(GL_QUADS);
    setColor(255, 255, 0); // Yellow color
    glVertex2i(x + 24, y);
    glVertex2i(x, y + 18);
    glVertex2i(x - 24, y);
    glVertex2i(x, y - 18);
    glEnd();

    // Draw the tail (a triangle)
    glBegin(GL_TRIANGLES);
    setColor(255, 0, 0); // Red color
    glVertex2i(x - 24, y);
    glVertex2i(x - 48, y + 18);
    glVertex2i(x - 48, y - 18);
    glEnd();

    // Draw the top fin (a triangle)
    glBegin(GL_TRIANGLES);
    setColor(255, 0, 0); // Red color
    glVertex2i(x - 12, y - 9);
    glVertex2i(x - 18, y - 27);
    glVertex2i(x, y - 18);
    glEnd();

    // Draw the bottom fin (a triangle)
    glBegin(GL_TRIANGLES);
    setColor(255, 0, 0); // Red color
    glVertex2i(x - 12, y + 9);
    glVertex2i(x - 18, y + 27);
    glVertex2i(x, y + 18);
    glEnd();

    // Draw the eye (a point)
    glPointSize(5.0); // Set the size of the point
    glBegin(GL_POINTS);
    setColor(0, 0, 0);
    glVertex2i(x + 15, y);
    glEnd();

    glLineWidth(1.0f);
    // Draw the middle lines (two vertical lines)
    glBegin(GL_LINES);
    setColor(0, 0, 0); // Black color
    glVertex2i(x, y - 18);
    glVertex2i(x, y + 18);
    glEnd();

    glBegin(GL_LINES);
    setColor(0, 0, 0); // Black color
    glVertex2i(x - 12, y - 9);
    glVertex2i(x - 12, y + 9);
    glEnd();
}

void PurpleFish(int x, int y)
{
    // Draw the body of the fish (a quad)
    glBegin(GL_QUADS);
    setColor(128, 0, 128); // Purple color
    glVertex2i(x - 24, y);    // Left vertex
    glVertex2i(x, y - 18); // Bottom vertex
    glVertex2i(x + 24, y);   // Right vertex
    glVertex2i(x, y + 18);  // Top vertex
    glEnd();

    // Draw the tail (a triangle)
    glBegin(GL_TRIANGLES);
    setColor(246, 2, 231); // Pink color
    glVertex2i(x + 24, y);
    glVertex2i(x + 48, y - 18); // Bottom of the tail
    glVertex2i(x + 48, y + 18); // Top of the tail
    glEnd();

    // Draw the top fin (a triangle)
    glBegin(GL_POLYGON);
    setColor(246, 2, 231); // Pink color
    glVertex2i(x, y + 18);      // Base of the fin
    glVertex2i(x-10, y + 40);      // Base of the fin
    glVertex2i(x, y + 30);      // Base of the fin
    glVertex2i(x+10, y + 40);      // Base of the fin
    glEnd();

    // Draw the bottom fin (a triangle)
    glBegin(GL_POLYGON);
    setColor(246, 2, 231); // Pink color
    glVertex2i(x, y - 18);      // Base of the fin
    glVertex2i(x-10, y - 40);      // Base of the fin
    glVertex2i(x, y - 30);      // Base of the fin
    glVertex2i(x+10, y - 40);      // Base of the fin
    glEnd();

    // Draw the eye (a point)
    glPointSize(5.0); // Set the size of the point
    glBegin(GL_POINTS);
    setColor(0, 0, 0); // Black color
    glVertex2i(x - 15, y); // Position of the eye
    glEnd();

    glLineWidth(1.0f);
    // Draw the middle lines (two vertical lines)
    glBegin(GL_LINES);
    setColor(0, 0, 0); // Black color
    glVertex2i(x, y + 18); // Top vertical line
    glVertex2i(x, y - 18); // Bottom vertical line
    glEnd();

    glBegin(GL_LINES);
    setColor(0, 0, 0); // Black color
    glVertex2i(x + 12, y + 9); // Top vertical line of the fin
    glVertex2i(x + 12, y - 9); // Bottom vertical line of the fin
    glEnd();
}

void Keyboard(unsigned char key, int x, int y)
{
    switch(key){
    case 'f':
    case 'F':
        horseMoveFlag = !horseMoveFlag;
        break;
    case 'r':
    case 'R':
        tailRotateFlag = !tailRotateFlag;
        break;
    case 'q':
    case 'Q':
        horseFlipFlag = !horseFlipFlag;
        break;
    case 'b':
    case 'B':
        boatMoveFlag = !boatMoveFlag;
        break;
    case 'w':
    case 'W':
        batMoveFlag = !batMoveFlag;
        break;
    case 'u':
    case 'U':
        increasingScale *= 2;
        break;
    case 's':
    case 'S':
        decreasingScale *= 0.5;
        bigFlowerPotRightScale *= 0.5f;
        break;
    case ' ':
        sunMoveFlag = !sunMoveFlag;
        bigFlowerPotRightScale = 0.5f;

    default:
        break;
    }
    glutPostRedisplay();
}


void Animations(int value){
    if (horseMoveFlag & !horseFlipFlag) {
        horsePosX -= 3;

    }
    if (horseMoveFlag & horseFlipFlag) {
        horsePosX += 3;

    }
    if (boatMoveFlag) {
        boatPosX += 3;
    }
    if (tailRotateFlag) {
        horseTailRotation += 5;
        if (horseTailRotation >= 360) {
            horseTailRotation -= 360;
        }
    }
    if (batMoveFlag) {
        batAngle += 0.5;
        if(batAngle >45){
            batAngle = 0;
        }
    }
    if (sunMoveFlag) {
        sunPosX -= 2.0f;
    }

    //horse re-position
    if (horsePosX < -horseWidth) {
        horsePosX = screenWidth;
    } else if (horsePosX > screenWidth) {
        horsePosX = -horseWidth;
    }

    //boat re-position
    if (boatPosX < -boatWidth) {
        boatPosX = screenWidth;
    } else if (boatPosX > screenWidth) {
        boatPosX = -boatWidth;
    }

    glutPostRedisplay();
    glutTimerFunc(16, Animations, 0);
}

void Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1200.0, 0.0, 700.0);
    doorTexture = LoadTexture("image1.jpg");
    roofTexture = LoadTexture("image2.jpeg");
}

void DrawSun() {
    glPushMatrix();
    glTranslatef(sunPosX, 0.0, 0.0);
    Circle(1100, 600, 40, 237, 131, 19);
    glPopMatrix();
}

void DrawScaledFlowerPot(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glScalef(scale, scale, 1.0);
    glTranslatef(-x, -y, 0.0);
    FlowerPot(x, y);
    glPopMatrix();
}

void DrawFlippedHorse() {
    glPushMatrix();
    glTranslatef(horsePosX, 0.0, 0.0);
    if (horseFlipFlag) {
        glTranslatef(300, 0.0, 0.0);
        glScalef(-1.0f, 1.0f, 1.0f);
    }
    Horse(0);
    glPopMatrix();
}

void DrawScaledFish(float x, float y, float scale, void (*drawFishFunc)(int, int)) {
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glScalef(scale, scale, 1.0);
    glTranslatef(-x, -y, 0.0);
    drawFishFunc(x, y);
    glPopMatrix();
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);

    Background();
    DrawSun();

    Tree(50, 200);
    TreeWithCircles(600, 290);
    TreeWithCircles(1000, 280);
    House(300, 250, 125, 0, 127);
    House(800, 250, 199, 72, 123);

    DrawScaledFlowerPot(150.0, 250.0, increasingScale);
    DrawScaledFlowerPot(230.0, 280.0, increasingScale);

    DrawScaledFlowerPot(1100.0, 300.0, decreasingScale);
    DrawScaledFlowerPot(1150.0, 340.0, bigFlowerPotRightScale);

    YellowFish(300, 50);
    YellowFish(200, 70);

    DrawScaledFish(1000.0, 70.0, increasingScale, PurpleFish);
    DrawScaledFish(1100.0, 50.0, increasingScale, PurpleFish);

    DrawFlippedHorse();

    glPushMatrix();
    glTranslatef(boatPosX, 0.0, 0.0);
    Boat();
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1200, 700);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Program");
    Init();
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glutTimerFunc(16, Animations, 0);
    glutMainLoop();
    return 0;
}

#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <thread>
using namespace std;

void cloudTraverse(int value);
void sunTraverse(int value);
//void changeBackground(int value);

float xCloudCoordMove = 0.0;
float xSunCoord = -1.0f;
float ySunCoord= 0.6f;
float r = 0.53f, g = 0.81f, b = 0.92f;
bool evening = false;

void displayCloud() {
    glColor3ub(192, 192, 192);

    glBegin(GL_POLYGON);
    glVertex2f(-1.4f + xCloudCoordMove, 0.6f);
    glVertex2f(-1.3f + xCloudCoordMove, 0.67f);
    glVertex2f(-1.2f + xCloudCoordMove, 0.63f);
    glVertex2f(-1.1f + xCloudCoordMove, 0.7f);
    glVertex2f(-1.0f + xCloudCoordMove, 0.68f);
    glVertex2f(-0.9f + xCloudCoordMove, 0.73f);
    glVertex2f(-0.8f + xCloudCoordMove, 0.65f);
    glVertex2f(-0.7f + xCloudCoordMove, 0.6f);
    glVertex2f(-0.8f + xCloudCoordMove, 0.62f);
    glVertex2f(-0.9f + xCloudCoordMove, 0.61f);
    glVertex2f(-1.0f + xCloudCoordMove, 0.63f);
    glVertex2f(-1.1f + xCloudCoordMove, 0.61f);
    glEnd();
}

void drawWindowHandles() {

    glLineWidth(5.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-0.7f, 0.1f);
    glVertex2f(-0.7f, 1.0f);

    glVertex2f(0.7f, 0.1f);
    glVertex2f(0.7f, 1.0f);

	glVertex2f(0.0f, 0.1f);
	glVertex2f(0.0f, 1.0f);

    glVertex2f(-1.0f, 0.1f);
	glVertex2f(1.0f, 0.1f);

    glEnd();
}

void drawFloor() {

    GLfloat quadsVertex[] = {
    -1.0f, -1.0f, 0.0f,
    -1.0f,  0.1f, 0.0f,
     1.0f,  0.1f, 0.0f,
     1.0f, -1.0f, 0.0f,

    };

    GLubyte indices[] = { 0, 1, 2, 3 };

    GLuint VBOid, VBOindex;
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadsVertex), quadsVertex, GL_STATIC_DRAW);

    glGenBuffers(1, &VBOindex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3ub(240, 178, 104);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, 0);

    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &VBOid);
    glDeleteBuffers(1, &VBOindex);

}

void displaySun() {
    glPushMatrix();
    glTranslatef(xSunCoord, ySunCoord, 0.0f); 
	glColor3ub(253, 184, 19); 
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
}

void drawWall() {
    GLfloat quadsVertex[] = {
        -1.0f, 0.1f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -0.7f, 1.0f, 0.0f,
        -0.7f, 0.1f, 0.0f,

		0.7f, 0.1f, 0.0f,
        0.7f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.1f, 0.0f,
    };

    GLubyte indices[] = { 0, 1, 2, 3, 4, 5, 6, 7};

    GLuint VBOid, VBOindex;
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadsVertex), quadsVertex, GL_STATIC_DRAW);

    glGenBuffers(1, &VBOindex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3ub(126, 102, 136); 
    glDrawElements(GL_QUADS , 8, GL_UNSIGNED_BYTE, 0);

    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &VBOid);
    glDeleteBuffers(1, &VBOindex);
}

void drawGrass() {
    GLfloat polygonVertex[] = {
        -0.7f, 0.1f, 0.0f,
        -0.7f, 0.3f, 0.0f,
        -0.55f, 0.45f, 0.0f,
         0.55f, 0.45f, 0.0f,
		 0.7f, 0.3f, 0.0f,
         0.7f, 0.1f, 0.0f,
    };

    GLubyte indices[] = { 0, 1, 2, 3, 4, 5 };

    GLuint VBOid, VBOindex;
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygonVertex), polygonVertex, GL_STATIC_DRAW);

    glGenBuffers(1, &VBOindex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3ub(55, 125, 34); 
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, 0);

    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &VBOid);
    glDeleteBuffers(1, &VBOindex);
}

void drawFences() {
    GLfloat polygonVertex[] = {
        -0.7f, 0.3f, 0.0f,
        -0.7f, 0.46f, 0.0f,
        -0.66f, 0.55f, 0.0f,
        -0.62f, 0.51f, 0.0f,
        -0.62f, 0.38f, 0.0f,

        -0.62f, 0.38f, 0.0f,
        -0.62f, 0.51f, 0.0f,
        -0.58f, 0.57f, 0.0f,
        -0.55f, 0.53f, 0.0f,
        -0.55f, 0.45f, 0.0f,

        -0.55f, 0.45f, 0.0f,
        -0.55f, 0.53f, 0.0f,
        -0.50f, 0.57f, 0.0f,
        -0.47f, 0.53f, 0.0f,
        -0.47f, 0.45f, 0.0f,

        -0.47f, 0.45f, 0.0f,
        -0.47f, 0.53f, 0.0f,
        -0.42f, 0.57f, 0.0f,
        -0.39f, 0.53f, 0.0f,
        -0.39f, 0.45f, 0.0f,

        -0.39f, 0.45f, 0.0f,
        -0.39f, 0.53f, 0.0f,
        -0.34f, 0.57f, 0.0f,
        -0.31f, 0.53f, 0.0f,
        -0.31f, 0.45f, 0.0f,

        -0.31f, 0.45f, 0.0f,
        -0.31f, 0.53f, 0.0f,
        -0.26f, 0.57f, 0.0f,
        -0.23f, 0.53f, 0.0f,
        -0.23f, 0.45f, 0.0f,

        -0.23f, 0.45f, 0.0f,
        -0.23f, 0.53f, 0.0f,
        -0.18f, 0.57f, 0.0f,
        -0.15f, 0.53f, 0.0f,
        -0.15f, 0.45f, 0.0f,

        -0.15f, 0.45f, 0.0f,
        -0.15f, 0.53f, 0.0f,
        -0.10f, 0.57f, 0.0f,
        -0.07f, 0.53f, 0.0f,
        -0.07f, 0.45f, 0.0f,

        -0.07f, 0.45f, 0.0f,
        -0.07f, 0.53f, 0.0f,
        -0.02f, 0.57f, 0.0f,
         0.01f, 0.53f, 0.0f,
         0.01f, 0.45f, 0.0f,

         0.01f, 0.45f, 0.0f,
         0.01f, 0.53f, 0.0f,
         0.06f, 0.57f, 0.0f,
         0.09f, 0.53f, 0.0f,
         0.09f, 0.45f, 0.0f,

         0.09f, 0.45f, 0.0f,
         0.09f, 0.53f, 0.0f,
         0.14f, 0.57f, 0.0f,
         0.17f, 0.53f, 0.0f,
         0.17f, 0.45f, 0.0f,

         0.17f, 0.45f, 0.0f,
         0.17f, 0.53f, 0.0f,
         0.22f, 0.57f, 0.0f,
         0.25f, 0.53f, 0.0f,
         0.25f, 0.45f, 0.0f,

         0.25f, 0.45f, 0.0f,
         0.25f, 0.53f, 0.0f,
         0.30f, 0.57f, 0.0f,
         0.33f, 0.53f, 0.0f,
         0.33f, 0.45f, 0.0f,

         0.33f, 0.45f, 0.0f,
         0.33f, 0.53f, 0.0f,
         0.38f, 0.57f, 0.0f,
         0.41f, 0.53f, 0.0f,
         0.41f, 0.45f, 0.0f,

         0.41f, 0.45f, 0.0f,
         0.41f, 0.53f, 0.0f,
         0.46f, 0.57f, 0.0f,
         0.49f, 0.53f, 0.0f,
         0.49f, 0.45f, 0.0f,

         0.49f, 0.45f, 0.0f,
         0.49f, 0.53f, 0.0f,
		 0.52f, 0.57f, 0.0f,
         0.55f, 0.53f, 0.0f,
         0.55f, 0.45f, 0.0f,

         0.7f, 0.3f, 0.0f,
         0.7f, 0.46f, 0.0f,
         0.66f, 0.57f, 0.0f,
         0.62f, 0.51f, 0.0f,
         0.62f, 0.38f, 0.0f,

         0.62f, 0.38f, 0.0f,
         0.62f, 0.51f, 0.0f,
         0.58f, 0.57f, 0.0f,
         0.55f, 0.53f, 0.0f,
         0.55f, 0.45f, 0.0f,


    };

    glColor3ub(120, 67, 21);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, polygonVertex);

    // Draw 16 fences first row + 2 second row
    for (int i = 0; i < 18; i++) {
        glDrawArrays(GL_POLYGON, i * 5, 5);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    displaySun();
    drawGrass();
    drawFences();
    displayCloud();
	drawWall();
    drawWindowHandles();
    drawFloor();

    glutSwapBuffers();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Final Project");

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glutTimerFunc(30, sunTraverse, 0);
    glutTimerFunc(1000, cloudTraverse, 0);
    //glutTimerFunc(30, changeBackground, 0);

    glutDisplayFunc(display);
    GLenum err = glewInit();
    if (err == GLEW_OK) {
        glutMainLoop();
    }

    return 0;
}

//void changeBackground(int value) {
//    if (!evening) {
//        r += 0.001f;
//        g -= 0.001f;
//        b -= 0.0005f;
//        if (r >= 1.0f) evening = true;  // reached sunset
//    }
//    else {
//        r -= 0.001f;
//        g += 0.001f;
//        b += 0.0005f;
//        if (r <= 0.0f) evening = false; // back to morning
//    }
//
//    glClearColor(r, g, b, 1.0f);
//    glutPostRedisplay();
//    glutTimerFunc(30, changeBackground, 0); // smooth transition
//}


void sunTraverse(int value) {
   
    xSunCoord += 0.002f;

    ySunCoord = 0.6f + 0.4f * sinf((xSunCoord + 1.0f) * 3.14159f / 2.0f);

    if (xSunCoord > 1.0f) { 
        xSunCoord = -1.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(30, sunTraverse, 0); 
}


void cloudTraverse(int value) {
    xCloudCoordMove += 0.002f;
    if (xCloudCoordMove > 2.5f)
        xCloudCoordMove = -2.0f;

    glutPostRedisplay();
    glutTimerFunc(8, cloudTraverse, 0);
}



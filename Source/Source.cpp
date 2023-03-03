//#include <GL/glut.h>
#pragma once
//#include "header.h"
#include <vector>
#include <cstdlib> 
#include <iostream>
#include "SOIL.h"

const double pi = 3.141592653589793238462643383279502884197169399;

//#include "MouseFunctions.cpp"
/*
* OGL02Animation.cpp: 3D Shapes with animation
*/
#include <windows.h> // for MS Windows
#include <GL/glut.h> // GLUT, include glu.h and gl.h
/* Global variables */
const int res = 100;
char title[] = "3D Shapes with animation";
float rotation_speed = 0.75f;
GLfloat degree = 30.0f; //nghieng 30 do
GLfloat anglePyramid = 0.0f; // Rotational angle for pyramid [NEW]
GLfloat angleCube = 0.0f; // Rotational angle for cube [NEW] //Khong xai may code nay
int refreshMills = 16; // refresh interval in milliseconds [NEW]
GLuint texture[1];
double piA[res];
double piB[res];
/* Initialize OpenGL Graphics */
int loadGLTextures() // Load Bitmaps And Convert To Textures
{
    /* load an image file directly as a new OpenGL texture */
    texture[0] = SOIL_load_OGL_texture
    (
        "test.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (texture[0] == 0)
        return false;
    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return true;
}

void initGL() {
    for (int i = 0; i < res; i++)
    {
        piA[i] = (i * double(2)* pi / res);
        piB[i] = piA[i] + 2*pi/res;
    };

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f); // Set background depth to farthest
    glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL); // Set the type of depth-test
    glShadeModel(GL_SMOOTH); // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Nice perspective corrections
}
/* Handler for window-repaint event. Called back when the window first appears and
whenever the window needs to be re-painted. */
void ran_text(int c)
{
    srand(c*15);
    float a = float(rand() % 100) / 100;
    float b = float(rand() % 100) / 100;
    glTexCoord2f(a, b);
};
void draw_band(double radius_1, double radius_2, double height, double x_ct, double y_ct, double z_ct, int random)
{
    double x = x_ct, y = y_ct, z = z_ct;
    glBegin(GL_TRIANGLES); // Begin drawing the triangles with 3 cordinate
    //glColor3f(1.0f, 0.0f, 0.0f); // Red
    ran_text(random);
    for (int i = 1; i < res; i++)
    {
        ran_text(random*i);
        //if (i == res / 2+1) glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(x_ct + cos(piA[i - 1]) * radius_1, z_ct, y_ct + sin(piA[i - 1]) * radius_1);
        ran_text(random * i+1);
        glVertex3f(x_ct + cos(piB[i - 1]) * radius_2, z_ct + height, y_ct + sin(piB[i - 1]) * radius_2);
        ran_text(random * i+2);
        glVertex3f(x_ct + cos(piA[i]) * radius_1, z_ct, y_ct + sin(piA[i]) * radius_1);

        //if (i==res/2) glColor3f(0.0f, 1.0f, 0.0f);
        ran_text(random*i + 4);
        glVertex3f(x_ct + cos(piB[i - 1]) * radius_2, z_ct + height, y_ct + sin(piB[i - 1]) * radius_2);
        ran_text(random * i + 5);
        glVertex3f(x_ct + cos(piA[i]) * radius_1, z_ct, y_ct + sin(piA[i]) * radius_1);
        ran_text(random * i + 6);
        glVertex3f(x_ct + cos(piB[i]) * radius_2, z_ct + height, y_ct + sin(piB[i]) * radius_2);
    };
    //glColor3f(0.0f, 1.0f, 0.0f); // green
    ran_text(random + 2);
    glVertex3f(x_ct + cos(piA[res - 1]) * radius_1, z_ct, y_ct + sin(piA[res - 1]) * radius_1);
    ran_text(random + 3);
    glVertex3f(x_ct + cos(piB[res - 1]) * radius_2, z_ct + height, y_ct + sin(piB[res - 1]) * radius_2);
    ran_text(random + 4);
    glVertex3f(x_ct + cos(piA[0]) * radius_1, z_ct, y_ct + sin(piA[0]) * radius_1);
    ran_text(random + 5);
    glVertex3f(x_ct + cos(piB[res - 1]) * radius_2, z_ct + height, y_ct + sin(piB[res - 1]) * radius_2);
    ran_text(random + 6);
    glVertex3f(x_ct + cos(piA[0]) * radius_1, z_ct, y_ct + sin(piA[0]) * radius_1);
    ran_text(random + 7);
    glVertex3f(x_ct + cos(piB[0]) * radius_2, z_ct + height, y_ct + sin(piB[0]) * radius_2);
    glEnd();
};
bool a = false;
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW); // To operate on model-view matrix
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.75f, 0.0f, -5.0f); // Move right and into the screen
    glRotatef(angleCube, 0.0f, 1.0f, 0.0f); // Rotate about (1,1,1)-axis [NEW]
    glRotatef(degree, 1.0f * cos((angleCube/180.0)*pi), 0.0f, 1.0f * sin((angleCube / 180.0) * pi)); // Rotate about (1,1,1)-axis [NEW]
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    //CONE 1
    //glRotatef(0, 0.0f, 1.0f, 0.0f); // Rotate about (1,1,1)-axis [NEW]
    //glRotatef(20, 1.0f, 0.0f, 0);
    //glRotatef(90, 0.0f, 1.0f, 0.0f); // Rotate about (1,1,1)-axis [NEW]
    //glRotatef(20, 0.0f, 0.0f, 1.0f);
    //glRotatef(180, 0.0f, 1.0f, 0.0f); // Rotate about (1,1,1)-axis [NEW]
    //glRotatef(20, -1.0f, 0.0f, 0.0f);
    //glRotatef(270, 0.0f, 1.0f, 0.0f); // Rotate about (1,1,1)-axis [NEW]
    //glRotatef(20, 0.0f, 0.0f, -1.0f);
    draw_band(0.4, 0.4, 1, 0, 0, 0,1);
    draw_band(0.4, 0, 0, 0, 0, 1,2);

    //CONE
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(2.0f, 0.0f, -5.0f); // Move right and into the screen
    glRotatef(angleCube, 0.0f, 1.0f, 0.0f); // Rotate about (1,1,1)-axis [NEW]
    glRotatef(degree, 1.0f * cos((angleCube / 180.0) * pi), 0.0f, 1.0f * sin((angleCube / 180.0) * pi)); // Rotate about (1,1,1)-axis [NEW]
    draw_band(0.6, 0, 1.25, 0, 0, 0,3);

    //Circle
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(-0.5f, 0.35f, -5.25f); // Move right and into the screen
    glRotatef(angleCube, 0.0f, 1.0f, 0.0f); // Rotate about (1,1,1)-axis [NEW]
    glRotatef(degree, 1.0f * cos((angleCube / 180.0) * pi), 0.0f, 1.0f * sin((angleCube / 180.0) * pi)); // Rotate about (1,1,1)-axis [NEW]
    double bk = 0.5; //bankinh);
    //std::cout << "YE\n";
    int res_2 = res / 2;
    for (int i = 0; i < res_2; i++)
    {
        draw_band(
            cos(double(i)/double(res_2)*pi/2)*bk,
            cos(double(i+1) / double(res_2) * pi / 2) * bk,
            sin(double(i+1) / double(res_2) * pi / 2) * bk - sin(double(i) / double(res_2) * pi / 2) * bk,
            0, 
            0, 
            //cos(double(i) / double(res / 3) * pi / 2) * bk
            sin(double(i) / double(res_2) * pi / 2) * bk
            //double(i) / double(res / 3) * bk
        ,4*i);
        draw_band(
            cos(double(i) / double(res_2) * pi / 2) * bk,
            cos(double(i + 1) / double(res_2) * pi / 2) * bk,
            -  sin(double(i+1) / double(res_2) * pi / 2) * bk + sin(double(i) / double(res_2) * pi / 2) * bk,
            0,
            0,
            -sin(double(i) / double(res_2) * pi / 2) * bk
        ,5*i);
    };


    //Torus
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(-0.5f, -0.5f, -3.5f); // Move right and into the screen
    glRotatef(angleCube, 0.0f, 1.0f, 0.0f); // Rotate about (1,1,1)-axis [NEW]
    glRotatef(degree, 1.0f * cos((angleCube / 180.0) * pi), 0.0f, 1.0f * sin((angleCube / 180.0) * pi)); // Rotate about (1,1,1)-axis [NEW]
    bk = 0.1; //bankinh);
    double bk_torus = 0.4;
    //std::cout << "YE\n";
    for (int i = 0; i < res_2; i++)
    {
        draw_band(
            cos(double(i) / double(res_2) * pi / 2) * bk + bk_torus,
            cos(double(i + 1) / double(res_2) * pi / 2) * bk + bk_torus,
            sin(double(i + 1) / double(res_2) * pi / 2) * bk - sin(double(i) / double(res_2) * pi / 2) * bk,
            0,
            0,
            //cos(double(i) / double(res / 3) * pi / 2) * bk
            sin(double(i) / double(res_2) * pi / 2) * bk
            //double(i) / double(res / 3) * bk
        ,6*i);
        draw_band(
            -cos(double(i) / double(res_2) * pi / 2) * bk + bk_torus,
            -cos(double(i + 1) / double(res_2) * pi / 2) * bk + bk_torus,
            sin(double(i + 1) / double(res_2) * pi / 2) * bk - sin(double(i) / double(res_2) * pi / 2) * bk,
            0,
            0,
            +sin(double(i) / double(res_2) * pi / 2) * bk
        ,7 * i);

        draw_band(
            cos(double(i) / double(res_2) * pi / 2) * bk + bk_torus,
            cos(double(i + 1) / double(res_2) * pi / 2) * bk + bk_torus,
            -sin(double(i + 1) / double(res_2) * pi / 2) * bk + sin(double(i) / double(res_2) * pi / 2) * bk,
            0,
            0,
            //cos(double(i) / double(res / 3) * pi / 2) * bk
            -sin(double(i) / double(res_2) * pi / 2) * bk
            //double(i) / double(res / 3) * bk
        ,8 * i);
        draw_band(
            -cos(double(i) / double(res_2) * pi / 2) * bk + bk_torus,
            -cos(double(i + 1) / double(res_2) * pi / 2) * bk + bk_torus,
            -sin(double(i + 1) / double(res_2) * pi / 2) * bk + sin(double(i) / double(res_2) * pi / 2) * bk,
            0,
            0,
            -sin(double(i) / double(res_2) * pi / 2) * bk
        ,9 * i);
    };


    //wat
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.6f, -0.5f, -3.5f); // Move right and into the screen
    glRotatef(angleCube, 0.0f, 1.0f, 0.0f); // Rotate about (1,1,1)-axis [NEW]
    glRotatef(degree, 1.0f * cos((angleCube / 180.0) * pi), 0.0f, 1.0f * sin((angleCube / 180.0) * pi)); // Rotate about (1,1,1)-axis [NEW]
    bk = 0.25; //bankinh);
    double bk_cone2 = 0.6;
    //std::cout << "YE\n";
    for (int i = 0; i + 1 < res_2; i++)
    {
        draw_band(
            -cos(double(i) / double(res_2) * pi / 2) * bk / 1.69 + bk_torus,
            -cos(double(i + 1) / double(res_2) * pi / 2) * bk / 1.69 + bk_torus,
            sin(double(i + 1) / double(res_2) * pi / 2) * bk - sin(double(i) / double(res_2) * pi / 2) * bk,
            0,
            0,
            +sin(double(i) / double(res_2) * pi / 2) * bk
        ,10*i);

        draw_band(
            -cos(double(i) / double(res_2) * pi / 2) * bk / 1.69 + bk_torus,
            -cos(double(i + 1) / double(res_2) * pi / 2) * bk / 1.69 + bk_torus,
            -sin(double(i + 1) / double(res_2) * pi / 2) * bk + sin(double(i) / double(res_2) * pi / 2) * bk,
            0,
            0,
            -sin(double(i) / double(res_2) * pi / 2) * bk
        ,11*i);
    };
    draw_band(
        bk_torus,
        0,
        0,
        0,
        0,
        +sin(pi / 2) * bk
    ,12);
    draw_band(
        bk_torus,
        0,
        0,
        0,
        0,
        -sin(pi / 2) * bk
    ,13);


    //Cone3
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(2.5f, -0.5f, -5.2f); // Move right and into the screen
    glRotatef(angleCube, 0.0f, 1.0f, 0.0f); // Rotate about (1,1,1)-axis [NEW]
    glRotatef(degree, 1.0f * cos((angleCube / 180.0) * pi), 0.0f, 1.0f * sin((angleCube / 180.0) * pi)); // Rotate about (1,1,1)-axis [NEW]
    double he_so = 0.8; //ban kinh = x^2 * he_so
    bk = 0.75; //height
    //std::cout << "YE\n";
    for (int i = 0; i + 1 < res_2; i++)
    {
        draw_band(
            pow((double(i) / double(res_2)) * bk,0.5) * he_so,
            pow((double(i+1) / double(res_2)) * bk, 0.5) * he_so,
            -(bk / double(res_2)),
            0,
            0,
            -(double(i) / double(res_2)) * bk
        ,14*i);
    };

    //CUBE
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(-5.5f, 1.f, -15.25f); // Move right and into the screen
    glRotatef(angleCube, 0.0f, 1.0f, 0.0f); // Rotate about (1,1,1)-axis [NEW]
    glRotatef(degree, 1.0f * cos((angleCube / 180.0) * pi), 0.0f, 1.0f * sin((angleCube / 180.0) * pi)); // Rotate about (1,1,1)-axis [NEW]
    glBegin(GL_QUADS);
    //glColor3f(1.0f, 0.0f, 0.0f);
    ran_text(15);
    glVertex3f(1.0f, 1.0f, -1.0f);
    ran_text(16);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    ran_text(17);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    ran_text(18);
    glVertex3f(1.0f, 1.0f, 1.0f);
    // Bottom face (y = -1.0f)
    ran_text(19);
    glVertex3f(1.0f, -1.0f, 1.0f);
    ran_text(20);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    ran_text(21);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    ran_text(22);
    glVertex3f(1.0f, -1.0f, -1.0f);
    // Front face (z = 1.0f)
    ran_text(23);
    glVertex3f(1.0f, 1.0f, 1.0f);
    ran_text(24);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    ran_text(25);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    ran_text(26);
    glVertex3f(1.0f, -1.0f, 1.0f);
    // Back face (z = -1.0f)
    ran_text(27);
    glVertex3f(1.0f, -1.0f, -1.0f);
    ran_text(28);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    ran_text(29);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    ran_text(30);
    glVertex3f(1.0f, 1.0f, -1.0f);
    // Left face (x = -1.0f)
    ran_text(31);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    ran_text(32);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    ran_text(33);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    ran_text(34);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    // Right face (x = 1.0f)
    ran_text(35);
    //glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    ran_text(36);
    glVertex3f(1.0f, 1.0f, 1.0f);
    ran_text(37);
    glVertex3f(1.0f, -1.0f, 1.0f);
    ran_text(38);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd(); // End of drawing color-cube

    glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)
    // Update the rotational angle after each refresh [NEW]
    angleCube -= rotation_speed;
}
/* Called back when timer expired [NEW] */
void timer(int value) {
    glutPostRedisplay(); // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}
/* Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) { // GLsizei for non-negative integer
// Compute aspect ratio of the new window
    if (height == 0) height = 1; // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);
    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity(); // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(640, 480); // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow(title); // Create window with the given title
    glutDisplayFunc(display); // Register callback handler for window re-paint event
    glutReshapeFunc(reshape); // Register callback handler for window re-size event
    initGL(); // Our own OpenGL initialization
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    loadGLTextures(); //Load anh vao GL
    glutTimerFunc(0, timer, 0); // First timer call immediately [NEW]
    glutMainLoop(); // Enter the infinite event-processing loop
    return 0;
}


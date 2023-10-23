#ifdef __APPLE__
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

using std::stringstream;
using std::cout;
using std::endl;
using std::ends;
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

using std::stringstream;
using std::cout;
using std::endl;
using std::ends;

// constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int BUFFER_SIZE = 512;
const float X_SCALE = 0.2f;
const float PI = acos(-1);
const float PI2 = PI * 2;

// GLUT CALLBACK functions
void displayCB();
void reshapeCB(int w, int h);
void timerCB(int millisec);
void idleCB();
void keyboardCB(unsigned char key, int x, int y);
void mouseCB(int button, int stat, int x, int y);
void mouseMotionCB(int x, int y);

// CALLBACK function when exit() called ///////////////////////////////////////
void exitCB();

void initGL();
int  initGLUT(int argc, char **argv);
bool initSharedMem();
void clearSharedMem();
void initLights();
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);
void drawString(const char *str, int x, int y, float color[4], void *font);
void drawString3D(const char *str, float pos[3], float color[4], void *font);
void showInfo();
void drawComplexPlane(float size=2.0f);
void drawGraph();
void computeComplexExp(float x, int n, float& outRe, float& outIm);

struct Vector3{
    float x;
    float y;
    float z;
    
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    
    // cross product
    Vector3  operator*(const Vector3& rhs) const {
        return Vector3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
    }
    
    //subtract
    Vector3  operator-(const Vector3& rhs) const {
        return Vector3(x-rhs.x, y-rhs.y, z-rhs.z);
    }

    Vector3& operator-=(const Vector3& rhs){
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    //normalize
    Vector3& normalize(){
        float invLength = 1.0f / sqrt(x*x + y*y + z*z);
        x *= invLength;
        y *= invLength;
        z *= invLength;
        return *this;
    }
};



// global variables
int screenWidth, screenHeight;
void *font = GLUT_BITMAP_8_BY_13;
bool mouseLeftDown;
bool mouseRightDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance;
int drawMode = 0;
float input[BUFFER_SIZE];
float output[BUFFER_SIZE][2];   // (Re, Im)
Vector3 normals[BUFFER_SIZE][2];  // (in, out)
int count;

///////////////////////////////////////////////////////////////////////////////
// draw the local axis of an object
///////////////////////////////////////////////////////////////////////////////
void drawComplexPlane(float size){
    const float MARK_SIZE = 0.05f;

    glDepthFunc(GL_ALWAYS);     // to avoid visual artifacts with grid lines
    glDisable(GL_LIGHTING);

    glColor3f(0.5f, 0.5f, 0.5f);

    // draw axis
    glLineWidth(2);
    glBegin(GL_LINES);
        // Real axis
        glVertex3f(-size, 0, 0);
        glVertex3f(size, 0, 0);
        // unit scale
        glVertex3f(1, MARK_SIZE, 0);
        glVertex3f(1, -MARK_SIZE, 0);
        glVertex3f(-1, MARK_SIZE, 0);
        glVertex3f(-1, -MARK_SIZE, 0);
        // Imaginary axis
        glVertex3f(0, -size, 0);
        glVertex3f(0, size, 0);
        // unit scale
        glVertex3f(MARK_SIZE, 1, 0);
        glVertex3f(-MARK_SIZE, 1, 0);
        glVertex3f(MARK_SIZE, -1, 0);
        glVertex3f(-MARK_SIZE, -1, 0);
        // variable axis
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 5*PI2*X_SCALE);
        // unit scale (2pi)
        glVertex3f( MARK_SIZE, 0, PI2*X_SCALE);
        glVertex3f(-MARK_SIZE, 0, PI2*X_SCALE);
        glVertex3f( MARK_SIZE, 0, PI2*2*X_SCALE);
        glVertex3f(-MARK_SIZE, 0, PI2*2*X_SCALE);
        glVertex3f( MARK_SIZE, 0, PI2*3*X_SCALE);
        glVertex3f(-MARK_SIZE, 0, PI2*3*X_SCALE);
        glVertex3f( MARK_SIZE, 0, PI2*4*X_SCALE);
        glVertex3f(-MARK_SIZE, 0, PI2*4*X_SCALE);
    glEnd();
    glLineWidth(1);

    // draw arrows(actually big square dots)
    glPointSize(5);
    glBegin(GL_POINTS);
        glVertex3f(size, 0, 0);
        glVertex3f(0, size, 0);
        glVertex3f(0, 0, PI2*X_SCALE*5);
    glEnd();
    glPointSize(1);

    // legend
    float position[3];
    float fontColor[4] = {1,1,1,1};
    position[0] = size + (size*0.05f);
    position[1] = 0;
    position[2] = 0;
    drawString3D("Re", position, fontColor, font);
    position[0] = 0;
    position[1] = size + (size*0.05f);
    position[2] = 0;
    drawString3D("Im", position, fontColor, font);
    position[0] = 0;
    position[1] = 0;
    position[2] = PI2*X_SCALE*5.05f;
    drawString3D("x", position, fontColor, font);
    position[0] = 1 + MARK_SIZE;
    position[1] = MARK_SIZE;
    position[2] = 0;
    drawString3D("1", position, fontColor, font);
    position[0] = -1 - MARK_SIZE*3;
    position[1] = MARK_SIZE;
    position[2] = 0;
    drawString3D("-1", position, fontColor, font);
    position[0] = MARK_SIZE;
    position[1] = 1 + MARK_SIZE;
    position[2] = 0;
    drawString3D("i", position, fontColor, font);
    position[0] = MARK_SIZE;
    position[1] = -1 - MARK_SIZE*2;
    position[2] = 0;
    drawString3D("-i", position, fontColor, font);
    position[0] = MARK_SIZE;
    position[1] = 0;
    position[2] = PI2*X_SCALE;
    drawString3D("2pi", position, fontColor, font);
    position[0] = MARK_SIZE;
    position[1] = 0;
    position[2] = PI2*X_SCALE*2;
    drawString3D("4pi", position, fontColor, font);
    position[0] = MARK_SIZE;
    position[1] = 0;
    position[2] = PI2*X_SCALE*3;
    drawString3D("6pi", position, fontColor, font);
    position[0] = MARK_SIZE;
    position[1] = 0;
    position[2] = PI2*X_SCALE*4;
    drawString3D("8pi", position, fontColor, font);

    // restore default settings
    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LEQUAL);
}



///////////////////////////////////////////////////////////////////////////////
// compute e^{ix} by using Taylor series
// x: input variable of the function
// n: the number of terms
///////////////////////////////////////////////////////////////////////////////
void computeComplexExp(float x, int n, float& outRe, float& outIm){
    double term;
    double factorial;
    double sumRe;
    double sumIm;
    int i, j;

    sumRe = sumIm = 0;
    for(i = 0; i < n; ++i)
    {
        // compute x^i
        term = pow(x, i);

        // compute i!
        factorial = 1;
        for(j = i; j > 1; --j)
            factorial *= j;

        // compute the term
        term /= factorial;

        // compute sums (Re and Im)
        switch(i%4)
        {
        case 0:
            sumRe += term;
            break;
        case 1:
            sumIm += term;
            break;
        case 2:
            sumRe -= term;
            break;
        case 3:
            sumIm -= term;
        }
    }

    outRe = (float)sumRe;
    outIm = (float)sumIm;
}



void drawGraph(){
    int i;

    if(drawMode == 0)   // line
    {
        glDisable(GL_LIGHTING);
        glLineWidth(3);
        glColor3f(1,0.5f,0);
        glBegin(GL_LINE_STRIP);
        for(i = 0; i <= count; ++i)
            glVertex3f(output[i][0], output[i][1], input[i]*X_SCALE);
        glEnd();
        glLineWidth(1);

        glColor3f(1,1,1);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0xCCCC);
        glBegin(GL_LINES);
        glVertex3f(0, 0, input[count]*X_SCALE);
        glVertex3f(output[count][0], output[count][1], input[count]*X_SCALE);
        glEnd();
        glDisable(GL_LINE_STIPPLE);

        glPointSize(7);
        glBegin(GL_POINTS);
        glColor3f(1, 1, 0);
        glVertex3f(output[count][0], output[count][1], input[count]*X_SCALE);
        glColor3f(1, 1, 1);
        glVertex3f(0, 0, input[count]*X_SCALE);
        glEnd();
        glPointSize(1);
        glEnable(GL_LIGHTING);
    }

    else if(drawMode == 1) // surface
    {
        float shininess = 15.0f;
        float diffuseColor[4] = {0.929524f, 0.796542f, 0.178823f, 1.0f};
        float specularColor[4] = {1.00000f, 0.980392f, 0.549020f, 1.0f};

        // set specular and shiniess using glMaterial
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess); // range 0 ~ 128
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularColor);

        // set ambient and diffuse color using glColorMaterial (gold-yellow)
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glColor4fv(diffuseColor);

        Vector3 v1, v2, v3, v4, v5, vz, n1, n2, n3, n4;

        for(int i = 1; i <= count; ++i)
        {
            // find the normal vector of each face
            v1.x = 0;               v1.y = 0;               v1.z = input[i-1]*X_SCALE;
            v2.x = output[i-1][0];  v2.y = output[i-1][1];  v2.z = input[i-1]*X_SCALE;
            v3.x = output[i][0];    v3.y = output[i][1];    v3.z = input[i]*X_SCALE;
            vz.x = 0,               vz.y = 0;               vz.z = 1;

            n1 = (v3 - v1) * vz;
            normals[i][0] = n1.normalize();
            n2 = (v2 - v1) * (v3 - v1);
            normals[i][1] = n2.normalize();

            glBegin(GL_TRIANGLE_FAN);
            glNormal3fv(&normals[i-1][0].x);
            glVertex3f(0, 0, input[i-1]*X_SCALE);
            glNormal3fv(&normals[i-1][1].x);
            glVertex3f(output[i-1][0], output[i-1][1], input[i-1]*X_SCALE);
            glNormal3fv(&normals[i][1].x);
            glVertex3f(output[i][0], output[i][1], input[i]*X_SCALE);
            glNormal3fv(&normals[i][0].x);
            glVertex3f(0, 0, input[i]*X_SCALE);
            glEnd();
        }

        glDisable(GL_LIGHTING);

        glColor3f(1, 1, 1);
        glBegin(GL_LINES);
        glVertex3f(0, 0, input[count]*X_SCALE);
        glVertex3f(output[count][0], output[count][1], input[count]*X_SCALE);
        glEnd();
        glLineWidth(1);

        glColor3f(1,0.6f,0);
        glLineWidth(3);
        glBegin(GL_LINE_STRIP);
        for(i = 0; i <= count; ++i)
            glVertex3f(output[i][0], output[i][1], input[i]*X_SCALE);
        glEnd();
        glLineWidth(1);

        glPointSize(7);
        glBegin(GL_POINTS);
        glColor3f(1, 1, 0);
        glVertex3f(output[count][0], output[count][1], input[count]*X_SCALE);
        glColor3f(1, 1, 1);
        glVertex3f(0, 0, input[count]*X_SCALE);
        glEnd();
        glPointSize(1);

        glEnable(GL_LIGHTING);
    }
}



///////////////////////////////////////////////////////////////////////////////
// initialize GLUT for windowing
///////////////////////////////////////////////////////////////////////////////
int initGLUT(int argc, char **argv)
{
    // GLUT stuff for windowing
    // initialization openGL window.
    // it is called before any other GLUT routine
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);   // display mode

    glutInitWindowSize(screenWidth, screenHeight); // window size

    glutInitWindowPosition(100, 100);           // window location

    // finally, create a window with openGL context
    // Window will not displayed until glutMainLoop() is called
    // it returns a unique ID
    int handle = glutCreateWindow(argv[0]);     // param is the title of window

    // register GLUT callback functions
    glutDisplayFunc(displayCB);
    glutTimerFunc(33, timerCB, 33);             // redraw only every given millisec
    //glutIdleFunc(idleCB);                       // redraw whenever system is idle
    glutReshapeFunc(reshapeCB);
    glutKeyboardFunc(keyboardCB);
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);

    return handle;
}



///////////////////////////////////////////////////////////////////////////////
// initialize OpenGL
// disable unused features
///////////////////////////////////////////////////////////////////////////////
void initGL()
{
    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    //glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);

    // anti-aliasing, line/polygon smooth
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);

     // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);

    initLights();
    setCamera(0, 0, 20, 0, 0, 0);
}



///////////////////////////////////////////////////////////////////////////////
// write 2d text using GLUT
// The projection matrix must be set to orthogonal before call this function.
///////////////////////////////////////////////////////////////////////////////
void drawString(const char *str, int x, int y, float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color

    glColor4fv(color);          // set text color
    glRasterPos2i(x, y);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glEnable(GL_LIGHTING);
    glPopAttrib();
}



///////////////////////////////////////////////////////////////////////////////
// draw a string in 3D space
///////////////////////////////////////////////////////////////////////////////
void drawString3D(const char *str, float pos[3], float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color

    glColor4fv(color);          // set text color
    glRasterPos3fv(pos);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glEnable(GL_LIGHTING);
    glPopAttrib();
}



///////////////////////////////////////////////////////////////////////////////
// initialize global variables
///////////////////////////////////////////////////////////////////////////////
bool initSharedMem()
{
    screenWidth = SCREEN_WIDTH;
    screenHeight = SCREEN_HEIGHT;
    mouseLeftDown = mouseRightDown = false;

    for(int i = 0; i < BUFFER_SIZE; ++i)
    {
        input[i] = i * 0.05f;
        output[i][0] = output[i][1] = 0;
        normals[i][0].x = normals[i][0].z = 0;
        normals[i][0].y = -1;
        normals[i][1].x = normals[i][1].y = 0;
        normals[i][1].z = 1;
    }

    return true;
}



///////////////////////////////////////////////////////////////////////////////
// clean up shared memory
///////////////////////////////////////////////////////////////////////////////
void clearSharedMem()
{
}



///////////////////////////////////////////////////////////////////////////////
// initialize lights
///////////////////////////////////////////////////////////////////////////////
void initLights()
{
    // set up light colors (ambient, diffuse, specular)
    GLfloat lightKa[] = {.1f, .1f, .1f, 1.0f};  // ambient light
    GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light
    GLfloat lightKs[] = {1, 1, 1, 1};           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

    // position the light
    float lightPos[4] = {0, 0, 20, 1}; // positional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration
}



///////////////////////////////////////////////////////////////////////////////
// set camera position and lookat direction
///////////////////////////////////////////////////////////////////////////////
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}



///////////////////////////////////////////////////////////////////////////////
// display info messages
///////////////////////////////////////////////////////////////////////////////
void showInfo()
{
    // backup current model-view matrix
    glPushMatrix();                     // save current modelview matrix
    glLoadIdentity();                   // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);        // switch to projection matrix
    glPushMatrix();                     // save current projection matrix
    glLoadIdentity();                   // reset projection matrix
    gluOrtho2D(0, screenWidth, 0, screenHeight); // set to orthogonal projection

    const int FONT_HEIGHT = 14;
    float color[4] = {1, 1, 1, 1};

    stringstream ss;
    ss << std::fixed << std::setprecision(3);

    drawString("===== e^(ix) =====", 0, screenHeight-FONT_HEIGHT, color, font);
    ss << "  input x: " << input[count] << ends;
    drawString(ss.str().c_str(), 0, screenHeight-(FONT_HEIGHT*2), color, font);
    ss.str("");
    ss << "output Re: " << output[count][0] << ends;
    drawString(ss.str().c_str(), 0, screenHeight-(FONT_HEIGHT*3), color, font);
    ss.str("");
    ss << "output Im: " << output[count][1] << ends;
    drawString(ss.str().c_str(), 0, screenHeight-(FONT_HEIGHT*4), color, font);
    ss.str("");

    drawString("Press 'D' to switch drawing modes.", 0, 0, color, font);
    drawString("Press 'R' to reset the view.", 0, FONT_HEIGHT, color, font);
    drawString("Press '1 or 2' to change axis", 0, FONT_HEIGHT*2, color, font);

    // unset floating format
    ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);

    // restore projection matrix
    glPopMatrix();                   // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
    glPopMatrix();                   // restore to previous modelview matrix
}








//=============================================================================
// CALLBACKS
//=============================================================================

void displayCB()
{
    // compute e^{ix}
    // N should be inceased while input variable(x) is increased
    computeComplexExp(input[count], 80, output[count][0], output[count][1]);

    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // save the initial ModelView matrix before modifying ModelView matrix
    glPushMatrix();

    // tramsform world
    glRotatef(cameraAngleX, 1, 0, 0);   // pitch
    glRotatef(cameraAngleY, 0, 1, 0);   // heading
    //glTranslatef(0, 0, -PI2*X_SCALE*2);

    // draw graph
    drawComplexPlane();
    drawGraph();

    // draw info messages
    showInfo();

    glPopMatrix();

    glutSwapBuffers();

    ++count;
    if(count >= BUFFER_SIZE)
        count = 0;
}


void reshapeCB(int width, int height)
{
    screenWidth = width;
    screenHeight = height;

    // set viewport to be the entire window
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    // set perspective viewing frustum
    float aspectRatio = (float)width / height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-aspectRatio, aspectRatio, -1, 1, 1, 100);
    //gluPerspective(60.0f, (float)(w)/h, 0.3f, 50.0f); // FOV, AspectRatio, NearClip, FarClip
    glOrtho(-2.3*aspectRatio, 2.3*aspectRatio, -2.3, 2.3, 1, 100);

    // switch to modelview matrix in order to set scene
    glMatrixMode(GL_MODELVIEW);
}


void timerCB(int millisec)
{
    glutTimerFunc(millisec, timerCB, millisec);
    glutPostRedisplay();
}


void idleCB()
{
    glutPostRedisplay();
}


void keyboardCB(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27: // ESCAPE
        exit(0);
        break;

    case 'r':
        cameraAngleX = cameraAngleY = 0;
        cameraDistance = -20;
        break;

    case '1':
        cameraAngleX = 0;
        cameraAngleY = 90;
        cameraDistance = -20;
        break;

    case '2':
        cameraAngleX = 90;
        cameraAngleY = 90;
        cameraDistance = -20;
        break;

    case 'd': // switch rendering modes (line -> surface)
    case 'D':
        drawMode = ++drawMode % 2;
        break;

    default:
        ;
    }

    glutPostRedisplay();
}


void mouseCB(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }
}


void mouseMotionCB(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    /* We don't use zoom because of orthographic projection
    if(mouseRightDown)
    {
        cameraDistance += (y - mouseY) * 0.2f;
        mouseY = y;
    }
    */

    //glutPostRedisplay();
}



void exitCB()
{
    clearSharedMem();
}

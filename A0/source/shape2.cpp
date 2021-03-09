/*
 * OGL01Shape3D.cpp: 3D Shapes
 */
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
#include <unistd.h>

struct rot_state {
    bool rotating;    // animation/movement happening
    float x,y,z;      // current rotation values
    float movex, movey, movez;
    bool lookat;
    float camx,camy,camz;
    bool spin_around_object;
    float angle;
    int current_axis; // 0 for x, 1 for y, 2 for z
} app_state;

/* Global variables */
char title[] = "3D Shapes";
 
/* Initialize OpenGL Graphics */
void initGL() {
   app_state.rotating = false;
   app_state.x = app_state.y = app_state.z = 0.0f;
   app_state.current_axis = -1;
   app_state.camx = app_state.camy = app_state.camz = 0.5f;
   app_state.movex = app_state.movey =app_state.movez = 0.0f;
   app_state.spin_around_object = false;
   app_state.angle = 0.0f;

   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
 
/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */


void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   // glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
   // // Render a color-cube consisting of 6 quads with different colors
   // glLoadIdentity();                 // Reset the model-view matrix
   glPushMatrix();
   glTranslatef(0.0f, 0.0f, -7.0f);  // Move right and into the screen
   float a = 1, h = 1.5f, s30 = 0.5f, c30 = sqrt(3)/2;
   double pi = 2 * acos(0.0);
   float radius = 10.0f;
     
   float camX = sin(pi/3) * radius;

   gluLookAt(app_state.camx, app_state.camy, app_state.camz,
			0.0f, 0.0f,  0.0f,
			0.0f, 1.0f,  0.0f);
   glTranslatef(app_state.movex,app_state.movey,app_state.movez); 
   glRotatef(app_state.x, 1, 0, 0);
   glRotatef(app_state.y, 0, 1, 0);
   glRotatef(app_state.z, 0, 0, 1);
    //   decagonal prism
    glBegin(GL_QUADS);               
    //side coords
    glColor3f(0.1f, 1.0f, 0.0f );
    glVertex3f(-a ,0.0f, 0.0f); 

    glColor3f(0.1f, 1.0f, 0.0f );
    glVertex3f(-a*sin(54*pi/180) ,0.0f, a*cos(54*pi/180)); 

    glColor3f(0.1f, 1.0f, 0.0f );
    glVertex3f(-a*sin(54*pi/180) ,h, a*cos(54*pi/180)); 

    glColor3f(0.1f, 1.0f, 0.0f );
    glVertex3f(-a ,h, 0.0f); 

    glColor3f(0.5f, 0.6f, 0.0f );
    glVertex3f(-a*sin(54*pi/180) ,0.0f, a*cos(54*pi/180)); 

    glColor3f(0.5f, 0.6f, 0.0f );
    glVertex3f(-a*sin(18*pi/180) ,0.0f, a*cos(18*pi/180)); 

    glColor3f(0.5f, 0.6f, 0.0f );
    glVertex3f(-a*sin(18*pi/180) ,h, a*cos(18*pi/180)); 

    glColor3f(0.5f, 0.6f, 0.0f );
    glVertex3f(-a*sin(54*pi/180) ,h, a*cos(54*pi/180)); 

    glColor3f(0.2f, 1.0f, 0.4f );
    glVertex3f(-a*sin(18*pi/180) ,0.0f, a*cos(18*pi/180)); 

    glColor3f(0.2f, 1.0f, 0.4f );
    glVertex3f(a*sin(18*pi/180) ,0.0f, a*cos(18*pi/180)); 

    glColor3f(0.2f, 1.0f, 0.4f );
    glVertex3f(a*sin(18*pi/180) ,h, a*cos(18*pi/180)); 

    glColor3f(0.2f, 1.0f, 0.4f );
    glVertex3f(-a*sin(18*pi/180) ,h, a*cos(18*pi/180)); 

    glColor3f(0.5f, 0.3f, 0.8f );
    glVertex3f(a*sin(18*pi/180) ,0.0f, a*cos(18*pi/180)); 

    glColor3f(0.5f, 0.3f, 0.8f );
    glVertex3f(a*sin(54*pi/180) ,0.0f, a*cos(54*pi/180)); 

    glColor3f(0.5f, 0.3f, 0.8f );
    glVertex3f(a*sin(54*pi/180) ,h, a*cos(54*pi/180)); 

    glColor3f(0.5f, 0.3f, 0.8f );
    glVertex3f(a*sin(18*pi/180) ,h, a*cos(18*pi/180)); 

    glColor3f(0.3f, 0.9f, 0.5f );
    glVertex3f(a*sin(54*pi/180) ,0.0f, a*cos(54*pi/180)); 

    glColor3f(0.3f, 0.9f, 0.5f );
    glVertex3f(a ,0.0f, 0.0f); 

    glColor3f(0.3f, 0.9f, 0.5f );
    glVertex3f(a ,h, 0.0f); 

    glColor3f(0.3f, 0.9f, 0.5f );
    glVertex3f(a*sin(54*pi/180) ,h, a*cos(54*pi/180)); 

    glColor3f(0.3f, 0.8f, 0.2f );
    glVertex3f(a ,0.0f, 0.0f); 

    glColor3f(0.3f, 0.8f, 0.2f );
    glVertex3f(a*sin(54*pi/180) ,0.0f, -a*cos(54*pi/180)); 

    glColor3f(0.3f, 0.8f, 0.2f );
    glVertex3f(a*sin(54*pi/180) ,h, -a*cos(54*pi/180)); 

    glColor3f(0.3f, 0.8f, 0.2f );
    glVertex3f(a ,h, 0.0f); 

    glColor3f(0.9f, 0.6f, 0.1f );
    glVertex3f(a*sin(54*pi/180) ,0.0f, -a*cos(54*pi/180)); 

    glColor3f(0.9f, 0.6f, 0.1f );
    glVertex3f(a*sin(18*pi/180) ,0.0f, -a*cos(18*pi/180)); 

    glColor3f(0.9f, 0.6f, 0.1f );
    glVertex3f(a*sin(18*pi/180) ,h, -a*cos(18*pi/180)); 

    glColor3f(0.9f, 0.6f, 0.1f );
    glVertex3f(a*sin(54*pi/180) ,h, -a*cos(54*pi/180)); 

    glColor3f(0.6f, 0.1f, 0.5f );
    glVertex3f(a*sin(18*pi/180) ,0.0f, -a*cos(18*pi/180)); 

    glColor3f(0.6f, 0.1f, 0.5f );
    glVertex3f(-a*sin(18*pi/180) ,0.0f, -a*cos(18*pi/180)); 

    glColor3f(0.6f, 0.1f, 0.5f );
    glVertex3f(-a*sin(18*pi/180) ,h, -a*cos(18*pi/180)); 

    glColor3f(0.6f, 0.1f, 0.5f );
    glVertex3f(a*sin(18*pi/180) ,h, -a*cos(18*pi/180)); 

    glColor3f(0.8f, 0.1f, 0.5f );
    glVertex3f(-a*sin(18*pi/180) ,0.0f, -a*cos(18*pi/180)); 

    glColor3f(0.8f, 0.1f, 0.5f );
    glVertex3f(-a*sin(54*pi/180) ,0.0f, -a*cos(54*pi/180)); 

    glColor3f(0.8f, 0.1f, 0.5f );
    glVertex3f(-a*sin(54*pi/180) ,h, -a*cos(54*pi/180)); 

    glColor3f(0.8f, 0.1f, 0.5f );
    glVertex3f(-a*sin(18*pi/180) ,h, -a*cos(18*pi/180)); 

    glColor3f(0.2f, 0.2f, 0.4f );
    glVertex3f(-a*sin(54*pi/180) ,0.0f, -a*cos(54*pi/180)); 

    glColor3f(0.2f, 0.2f, 0.4f );
    glVertex3f(-a ,0.0f, 0.0f); 

    glColor3f(0.2f, 0.2f, 0.4f );
    glVertex3f(-a ,h, 0.0f); 

    glColor3f(0.2f, 0.2f, 0.4f );
    glVertex3f(-a*sin(54*pi/180) ,h, -a*cos(54*pi/180)); 

    //bottom face
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a ,0.0f, 0.0f); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a*sin(54*pi/180) ,0.0f, a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.0f , 0.0f, 0.0f); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a ,0.0f, 0.0f); 
    

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a*sin(54*pi/180) ,0.0f, a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a*sin(18*pi/180) ,0.0f, a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.0f , 0.0f, 0.0f); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a*sin(54*pi/180) ,0.0f, a*cos(54*pi/180)); 
    

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a*sin(18*pi/180) ,0.0f, a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a*sin(18*pi/180) ,0.0f, a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.0f , 0.0f, 0.0f); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a*sin(18*pi/180) ,0.0f, a*cos(18*pi/180)); 
    

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a*sin(18*pi/180) ,0.0f, a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a*sin(54*pi/180) ,0.0f, a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.0f , 0.0f, 0.0f); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a*sin(18*pi/180) ,0.0f, a*cos(18*pi/180)); 
    

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a*sin(54*pi/180) ,0.0f, a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a ,0.0f, 0.0f); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.0f , 0.0f, 0.0f); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a*sin(54*pi/180) ,0.0f, a*cos(54*pi/180)); 
    

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a ,0.0f, 0.0f); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a*sin(54*pi/180) ,0.0f, -a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.0f , 0.0f, 0.0f); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a ,0.0f, 0.0f); 
    

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a*sin(54*pi/180) ,0.0f, -a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a*sin(18*pi/180) ,0.0f, -a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.0f , 0.0f, 0.0f); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a*sin(54*pi/180) ,0.0f, -a*cos(54*pi/180)); 
    

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a*sin(18*pi/180) ,0.0f, -a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a*sin(18*pi/180) ,0.0f, -a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.0f , 0.0f, 0.0f); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(a*sin(18*pi/180) ,0.0f, -a*cos(18*pi/180)); 
    

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a*sin(18*pi/180) ,0.0f, -a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a*sin(54*pi/180) ,0.0f, -a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.0f , 0.0f, 0.0f); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a*sin(18*pi/180) ,0.0f, -a*cos(18*pi/180)); 
    

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a*sin(54*pi/180) ,0.0f, -a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a ,0.0f, 0.0f); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.0f , 0.0f, 0.0f); 

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-a*sin(54*pi/180) ,0.0f, -a*cos(54*pi/180)); 
    

    //top face
    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a ,h, 0.0f); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a*sin(54*pi/180) ,h, a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(0.0f , h, 0.0f); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a ,h, 0.0f); 
    

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a*sin(54*pi/180) ,h, a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a*sin(18*pi/180) ,h, a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(0.0f , h, 0.0f); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a*sin(54*pi/180) ,h, a*cos(54*pi/180)); 
    

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a*sin(18*pi/180) ,h, a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a*sin(18*pi/180) ,h, a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(0.0f , h, 0.0f); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a*sin(18*pi/180) ,h, a*cos(18*pi/180)); 
    

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a*sin(18*pi/180) ,h, a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a*sin(54*pi/180) ,h, a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(0.0f , h, 0.0f); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a*sin(18*pi/180) ,h, a*cos(18*pi/180)); 
    

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a*sin(54*pi/180) ,h, a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a ,h, 0.0f); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(0.0f , h, 0.0f); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a*sin(54*pi/180) ,h, a*cos(54*pi/180)); 
    

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a ,h, 0.0f); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a*sin(54*pi/180) ,h, -a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(0.0f , h, 0.0f); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a ,h, 0.0f); 
    

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a*sin(54*pi/180) ,h, -a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a*sin(18*pi/180) ,h, -a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(0.0f , h, 0.0f); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a*sin(54*pi/180) ,h, -a*cos(54*pi/180)); 
    

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a*sin(18*pi/180) ,h, -a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a*sin(18*pi/180) ,h, -a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(0.0f , h, 0.0f); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(a*sin(18*pi/180) ,h, -a*cos(18*pi/180)); 
    

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a*sin(18*pi/180) ,h, -a*cos(18*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a*sin(54*pi/180) ,h, -a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(0.0f , h, 0.0f); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a*sin(18*pi/180) ,h, -a*cos(18*pi/180)); 
    

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a*sin(54*pi/180) ,h, -a*cos(54*pi/180)); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a ,h, 0.0f); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(0.0f , h, 0.0f); 

    glColor3f(0.0f, 0.0f, 0.2f);
    glVertex3f(-a*sin(54*pi/180) ,h, -a*cos(54*pi/180)); 
   glEnd();  // End of drawing color-cube
   // glLoadIdentity();                  // Reset the model-view matrix
   glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen
   // glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
   glPopMatrix();
    glutSwapBuffers();
    glFlush();
}
 
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void action(void)
{
    // Animate the rotations/spinning
    float increment = 0.05f;
    switch (app_state.current_axis)
    {
    case 0:
        app_state.x += increment;
        break;
    case 1:
        app_state.y += increment;
        break;
    case 2:
        app_state.z += increment;
        break;
    default:
        break;
    }
    //spinning camera around object
    if(app_state.spin_around_object)
    {
      double pi = 2 * acos(0.0);
      float radius = 10.0f;
      app_state.angle += pi/10000;
      app_state.camx = sin(app_state.angle) * radius;

    }

    glutPostRedisplay();
}

 //keyboard event handler
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // Escape key
        exit(0);
        break;
   // move object along 3 different axis
   case 'a':
        app_state.movex += 1;
        break;
    case 'b':
        app_state.movey += 1;
        break;
    case 'c':
        app_state.movez += 1;
        break;
   case 'l':
        app_state.movex -= 1;
        break;
    case 'm':
        app_state.movey -= 1;
        break;
    case 'n':
        app_state.movez -= 1;
        break;
    // object spin around any one axis
    case 'x':
        app_state.current_axis = 0;
        break;
    case 'y':
        app_state.current_axis = 1;
        break;
    case 'z':
        app_state.current_axis = 2;
        break;
   // change camera positions
    case 'p':
        app_state.camx += 1;
        break;
    case 'q':
        app_state.camy += 1;
        break;
    case 's':
        app_state.camz += 1;
        break;
    case 'e':
      app_state.camx -= 1;
      break;
    case 'f':
      app_state.camy -= 1;
      break;
    case 'g':
      app_state.camz -= 1;
      break;
   //move to pre-decided poistions of camera
    case 'd':
      app_state.camx = 1;
      app_state.camy = 1;
      app_state.camz = 1;
      break;
   case 'o':
      app_state.camx = 2;
      app_state.camy = 2;
      app_state.camz = 2;
      break;
   case 'j':
      app_state.camx = 5;
      app_state.camy = 2;
      app_state.camz = 2;
      break;
   case 'v':
      app_state.spin_around_object = true;
      break;
    case 'r':
        app_state.rotating ^= 1;
        glutIdleFunc(app_state.rotating ? action : NULL);
        break;
   
    }
    glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                       // Our own OpenGL initialization
   glutKeyboardFunc(keyboard);
   glutIdleFunc(action);
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
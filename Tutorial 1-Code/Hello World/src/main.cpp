#include "main.h"
#include "timer.h"
#include "ball.h"
#include "vwall.h"
#include "hwall.h"
#include "plane.h"
// #include "circle.h"
#include "seven_segment_display.h"
#include <GL/glut.h>
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Ball ball2;
Plane plane1;




// Circle circle1;
std::vector<Seven_Segment_Display> displays;

int health=200;
int score=100;
int score3=100;
float score2=0.0;

Ball ending[7];

int endnumber=7;
Ball barbwire[10];
int barbnumber=10;
int history=0;
Vwall t1;
Hwall t2;
int wallv=0;
int wallh=0;
int wallind=0;
const int mazesize=20;
const int wallsno=mazesize*mazesize;
int vwallsno=0,hwallsno=0;
Vwall vwalls[100000];
Hwall hwalls[100000];
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float eyez=1;
float eyex,eyey;
float zoom=25;
Timer t60(1.0 / 60);

Hwall hborder[2*mazesize];
Vwall vborder[2*mazesize];


/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    eyex=ball1.ballx();
    eyey=ball1.bally();
    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
     glm::vec3 eye ( eyex,eyey,eyez);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    glm::vec3 target (eyex, eyey, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

    lightPos[0]=eyex;
    lightPos[1]=eyey;
    lightPos[2]=eyez;
    
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // // Scene render
    plane1.draw(VP);
    for(int i=0;i<2*mazesize;i++){
        vborder[i].set_position(vborder[i].getx(),vborder[i].gety());
        hborder[i].set_position(hborder[i].getx(),hborder[i].gety());

        vborder[i].draw(VP);
        hborder[i].draw(VP);
    }
    ball1.draw(VP);
    ball2.draw(VP);


    // t1.set_position(0,0);
    // t2.set_position(0,0);
    // t1.draw(VP);
    // t2.draw(VP);
    // circle1.draw(VP);
    for (int i=0;i<barbnumber;i++)
    {
        barbwire[i].draw(VP);
    }
    
    for(int i=0;i<vwallsno;i++){
        // printf("v %f %f\n",vwalls[i].getx(),vwalls[i].gety());
        vwalls[i].set_position(vwalls[i].getx(),vwalls[i].gety());
        vwalls[i].draw(VP);
    }
    for(int i=0;i<hwallsno;i++){
        // printf("h %f %f\n",hwalls[i].getx(),hwalls[i].gety());
        
        hwalls[i].set_position(hwalls[i].getx(),hwalls[i].gety());
        hwalls[i].draw(VP);
    }

    if (score >= 0) {
        displays[0].set_number((score % 1000) / 100);
        displays[0].draw (VP);
        displays[1].set_number((score % 100) / 10);
        displays[1].draw (VP);
        displays[2].set_number((score % 10));
        displays[2].draw (VP);
    }
    for(int i=0;i<endnumber;i++)
    ending[i].draw(VP);
    if (health >= 0) {
        displays[3].set_number((health % 1000) / 100);
        displays[3].draw (VP);
        displays[4].set_number((health % 100) / 10);
        displays[4].draw (VP);
        displays[5].set_number((health % 10));
        displays[5].draw (VP);
    }
}

int directions(float x1, float y1, float x2, float y2)
{
    
    if(x1 <= x2 && y1 <= y2)
    {
        return 1;
    }
    if(x1 >= x2 && y1 <= y2)
    {
        return 2;
    }
    if(x1 <= x2 && y1 >= y2)
    {
        return 3;
    }
    if(x1 >= x2 && y1 >= y2)
    {
        return 4;
    }

    return 0;
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int minus = glfwGetKey(window, GLFW_KEY_MINUS);
    int equal = glfwGetKey(window, GLFW_KEY_EQUAL);
    if (left) {
        // Do something
        eyex-=0.5;
        ball1.set_position(eyex,eyey);
        // circle1.set_position(eyex,eyey);
        history=1;
    }
    if(right)
    {
        eyex+=0.5;
        ball1.set_position(eyex,eyey);
        // circle1.set_position(eyex,eyey);
        history=2;
    }
    if(down)
    {
        eyey-=0.5;
        ball1.set_position(eyex,eyey);
        // circle1.set_position(eyex,eyey);
        history=3;
    }
    if(up)
    {
        eyey+=0.5;
        ball1.set_position(eyex,eyey);
        // circle1.set_position(eyex,eyey);
        history=4;
    }
    if (minus) {
        zoom+=0.3;
        if(zoom >=16) zoom =16;
        reset_screen();
    }
    if (equal) {
        zoom-=0.3;
        if(zoom<1) zoom=1;
        reset_screen();
    }
}

void tick_elements() {

    score2+=0.01;
    score = 400-int(score2)+(health*health);
    if(health==0)
    {   score=0;
        exit(0);
    }
    ball1.tick();
    // camera_rotation_angle += 1;
    for(int i=0;i<endnumber;i++)
    if(detect_collision(ball1.return_bounding_box(),ending[i].return_bounding_box()))
    {
        exit(0);
    }
    int val=directions(ball2.ballx(),ball2.bally(),ball1.ballx(),ball1.bally());
    if(detect_collision(ball1.return_bounding_box(),ball2.return_bounding_box()))
    {   score=0;
        exit(0);
    }
    float enemyx, enemyy;
    enemyx = ball2.ballx();
    enemyy = ball2.bally();
    // printf("VAL IS %d\n",val);
    // printf("%f %f \n",enemyx,enemyy);
    if(val==1)
    {
        enemyx += 0.05;
        enemyy += 0.05;
        ball2.set_position(enemyx,enemyy);
        
    }
    else if(val==2)
    {
        enemyx -= 0.05;
        enemyy += 0.05;
        ball2.set_position(enemyx,enemyy);
    }
    else if (val==3)
    {
       enemyx += 0.05;
       enemyy -= 0.05;
       ball2.set_position(enemyx,enemyy);   
    }
    else if (val==4)
    {
        enemyx -= 0.05;
        enemyy -= 0.05;
        ball2.set_position(enemyx,enemyy);

    }


    for(int i=0;i<vwallsno-1;i++){
        // vwalls[i].draw(VP);
        if(detect_collision(ball1.return_bounding_box(),vwalls[i].return_bounding_box()))
        {
            if(history==1)
            {
                eyex+=0.5;
                ball1.set_position(eyex,eyey);
            }
            if(history==2)
            {
                eyex-=0.5;
                ball1.set_position(eyex,eyey);
            }
            if(history==3)
            {
                eyey+=0.5;
                ball1.set_position(eyex,eyey);
            }
            if(history==4)
            {
                eyey-=0.5;
                ball1.set_position(eyex,eyey);
            }
        }
    }
    for(int i=0;i<hwallsno-1;i++){
        if(detect_collision(ball1.return_bounding_box(),hwalls[i].return_bounding_box()))
        {
            if(history==1)
            {
                eyex+=0.5;
                ball1.set_position(eyex,eyey);
            }
            if(history==2)
            {
                eyex-=0.5;
                ball1.set_position(eyex,eyey);
            }
            if(history==3)
            {
                eyey+=0.5;
                ball1.set_position(eyex,eyey);
            }
            if(history==4)
            {
                eyey-=0.5;
                ball1.set_position(eyex,eyey);
            }
        }
    }
    float gap=0;
    for(int i=0;i<3;i++)
    {
        displays[i].set_position(eyex-10+gap,eyey+10);
        gap+=0.4;
    }
    gap=0;
       for(int i=3;i<6;i++)
    {
        displays[i].set_position(eyex+gap-0.4,eyey);
        gap+=0.4;
    }
      for(int i=0;i<barbnumber;i++)
    {
        if(detect_collision(ball1.return_bounding_box(),barbwire[i].return_bounding_box()))
        health=health-5;
    }

}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height,int walls[wallsno][2][2]) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0, 0, COLOR_RED);
    ball2       = Ball(-5,0,COLOR_GREEN);
    for(int i=0;i<endnumber;i++)
    ending[i] = Ball(rand()%wallsno,rand()%wallsno,COLOR_RED);
    t1=Vwall(0,0,COLOR_BLACK);
    t2=Hwall(0,0,COLOR_BLACK);
    plane1 = Plane(0,0,COLOR_YELLOW);
    // circle1 = Circle(0,0,COLOR_BACKGROUND);

        // level = Seven_Segment_Display (0, 4.3, 1);
    float gap=0;
    for (int i = 0; i < 3; ++i) {
        // printf("gap->%d\n", gap);
        displays.push_back (Seven_Segment_Display (0+gap, 0, 0));
        gap += 0.4;
    }
    // float gap = 0;
    for (int i = 3; i < 6; ++i) {
        // printf("gap->%d\n", gap);
        displays.push_back (Seven_Segment_Display (eyex+3, eyey+gap, 1));
        gap += 0.4;
    }

    gap = 0.2;
    


    for(int xc=0;xc<mazesize-1;xc++){

        for(int yc=0;yc<mazesize-1;yc++){

            int present=0;


            for(int i=0;i<wallsno-1;i++){
                if(walls[i][0][0]>walls[i][1][0]){
                    printf("less %d\n",i);

                    if(walls[i][1][0]==xc && walls[i][0][1]==yc)
                        present=1;
                    // vwallsno++;
                    // vwalls[vwallsno-1]=Vwall(walls[i][1][0],walls[i][0][1],COLOR_RED);
                }
                else if(walls[i][0][0]<walls[i][1][0]){
                    printf("more %d\n",i);
                    if(walls[i][0][0]==xc && walls[i][0][1]==yc)
                        present=1;
                    // vwallsno++;
                    // vwalls[vwallsno-1]=Vwall(walls[i][0][0],walls[i][0][1],COLOR_RED);

                }
            }
            if(present==0){
                printf("vw for x %d y %d\n",xc,yc);
                vwallsno++;
                vwalls[vwallsno-1]=Vwall(xc-1,yc-1,COLOR_RED);
            }
        }

    }


    for(int xc=0;xc<mazesize-1;xc++){

        for(int yc=0;yc<mazesize-1;yc++){

            int present=0;

            for(int i=0;i<wallsno-1;i++){
                if(walls[i][0][1]>walls[i][1][1]){
                    printf("less %d\n",i);
                    // hwallsno++;
                    // hwalls[hwallsno-1]=Hwall(walls[i][1][0],walls[i][0][1],COLOR_RED);
                    if(walls[i][1][0]==xc && walls[i][1][1]==yc)
                        present=1;

                }
                else if(walls[i][0][1]<walls[i][1][1]){
                    printf("more %d\n",i);

                    if(walls[i][0][0]==xc && walls[i][0][1]==yc)
                        present=1;                    
                    // hwallsno++;
                    // hwalls[hwallsno-1]=Hwall(walls[i][0][0],walls[i][0][1],COLOR_RED);

                }
            }
            if(present==0){
                printf("hw for x %d y %d\n",xc,yc);
                hwallsno++;
                hwalls[hwallsno-1]=Hwall(xc-1,yc-1,COLOR_RED);
            }
        }

    }

    for(int i=-1;i<mazesize-1;i++){
        hborder[i+1]=Hwall(i,-2,COLOR_BLACK);
        hborder[mazesize+i+1]=Hwall(i,mazesize-2,COLOR_BLACK);
        printf("%d big\n",mazesize+i+2);
    }
    for(int i=-1;i<mazesize-1;i++){
        vborder[i+1]=Vwall(-2,i,COLOR_BLACK);
        vborder[mazesize+i+1]=Vwall(mazesize-2,i,COLOR_BLACK);
    }


      for(int i=0;i<barbnumber;i++)
    {
        barbwire[i] = Ball(rand()%wallsno,rand()%wallsno,COLOR_BLACK);
    }
    

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene

    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

//Recursively generating maze
void maze_generator(int walls[wallsno][2][2], int visited[mazesize][mazesize], int current[2]){
    int nextx=0,nexty=0;
    visited[current[0]][current[1]]=1;

    int poss[]={0,0,0,0};
    int flag=0;
    while(flag!=1){
        flag=1;
        for(int i=0;i<4;i++){
            if(poss[i]==0)
            flag=0;
        }
        if(flag==1) break;
        int randval;
        while(1){
            randval=rand()%4;

            if(poss[randval]==0){
                poss[randval]=1;
                break;
            }
        }
        if(randval==0)
        
        if(current[0]>0 and visited[current[0]-1][current[1]]==0){
            nextx=current[0]-1;
            nexty=current[1];
            walls[wallind][0][0]=current[0];
            walls[wallind][0][1]=current[1];
            walls[wallind][1][0]=nextx;
            walls[wallind][1][1]=nexty;
            wallind++;
            int next[]={nextx,nexty};
            maze_generator(walls,visited,next);
        }
        if(randval==1)
        if(current[0]<mazesize-1 and visited[current[0]+1][current[1]]==0){
            nextx=current[0]+1;
            nexty=current[1];
            walls[wallind][0][0]=current[0];
            walls[wallind][0][1]=current[1];
            walls[wallind][1][0]=nextx;
            walls[wallind][1][1]=nexty;
            wallind++;
            int next[]={nextx,nexty};
            maze_generator(walls,visited,next);
        }
        if(randval==2)
        if(current[1]>0 and visited[current[0]][current[1]-1]==0){
            nextx=current[0];
            nexty=current[1]-1;
            walls[wallind][0][0]=current[0];
            walls[wallind][0][1]=current[1];
            walls[wallind][1][0]=nextx;
            walls[wallind][1][1]=nexty;
            wallind++;
            int next[]={nextx,nexty};
            maze_generator(walls,visited,next);
        }
        if(randval==3)
        if(current[1]<mazesize-1 and visited[current[0]][current[1]+1]==0){
            nextx=current[0];
            nexty=current[1]+1;
            walls[wallind][0][0]=current[0];
            walls[wallind][0][1]=current[1];
            walls[wallind][1][0]=nextx;
            walls[wallind][1][1]=nexty;
            wallind++;
            int next[]={nextx,nexty};
            maze_generator(walls,visited,next);
        }
    }

}

int main(int argc, char **argv) {
    srand(time(0));

    int visited[mazesize][mazesize];
    for(int i=0;i<mazesize;i++){
        for(int j=0;j<mazesize;j++){
            visited[i][j]=0;
        }
    }
    int walls[wallsno][2][2];
    for(int i=0;i<wallsno;i++){
        walls[i][0][0]=-1;
    }

    
    int current[2]={0,0};
    
    maze_generator(walls,visited,current);

    for(int i=0;i<wallind;i++){
        printf("wall %d: %d,%d -> %d,%d\n",i,walls[i][0][0],walls[i][0][1],walls[i][1][0],walls[i][1][1]);
    }

    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height,walls);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    // printf("%f %f %f %f %f %f %f %f\n",a.x,b.x,a.width,b.width,a.y,b.y,a.height,b.height);
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left-zoom, right+zoom, bottom-zoom, top+zoom, 0.1f, 500.0f);
}

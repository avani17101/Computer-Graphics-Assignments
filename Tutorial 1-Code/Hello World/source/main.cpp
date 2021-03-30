#include "main.h"
#include "timer.h"
#include "player.h"
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

map < pair <int, int> , int > H;
map < pair <int, int> , int > V; 

map < pair <int, int> , int > U;
map < pair <int, int> , int > L;

const int min_x = -10;
const int max_x = 10;
const int min_y = -10;
const int max_y = 10;
const int difficulty = 2;

struct EDGE{
    int fromx, fromy;
    int tox, toy;
};
int N;
const int MAXN = 1e6 + 5;
vector <EDGE> edges;
int parent[MAXN];
int sz[MAXN];
int root(int node)
{
	if(parent[node] == node)return node;
	return parent[node] = root(parent[node]);
}
void _union(int a, int b)
{
	if(a==b)return;
	a = root(a);
	b = root(b);
	if(sz[a]<sz[b]){
		sz[b]+=sz[a];
		parent[a] = parent[b];
	}
	else
	{
		sz[a]+=sz[b];
		parent[b] = parent[a];
	}
}

void generate_maze(){
    N = 0;
    for(int i = min_x; i <= max_x; ++i)
    {
        for(int j = min_y; j <= max_y; ++j){
            if(i != max_x){
                EDGE tmp;
                tmp.fromx = i;
                tmp.fromy = j;
                tmp.tox = i + 1;
                tmp.toy = j;
                edges.push_back(tmp);
            }
            
            if(j != max_y){
                EDGE tmp;
                tmp.fromx = i;
                tmp.fromy = j;
                tmp.tox = i;
                tmp.toy = j + 1;
                edges.push_back(tmp);
            }
            N++;
        }
    }
    for(int i = 1; i <= N; ++i)
    {
        sz[i] = 1;
        parent[i] = i;
    }
    while(edges.size() > 0)
    {
        int pick_idx = rand() % edges.size();
        int from = (edges[pick_idx].fromx - min_x) * (max_y - min_y + 1) + (edges[pick_idx].fromy - min_y);
        int to = (edges[pick_idx].tox - min_x) * (max_y - min_y + 1) + (edges[pick_idx].toy - min_y);
        int u = root(from);
        int v = root(to);
        if(u != v){
            _union(u, v);
        }
        else{
            int toss = rand() % difficulty;
            if(toss == 1)
            {
                _union(u, v);
            }
            else{
                if((to - from) == 1){
                    U[{edges[pick_idx].fromx, edges[pick_idx].fromy}] = 1;
                }
                else{
                    L[{edges[pick_idx].tox, edges[pick_idx].toy}] = 1;
                }
            }            
        }
        edges.erase(edges.begin() + pick_idx);
    }
}

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

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

    // Scene render
    V.clear();
    H.clear();

 

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    if (left) {
        // Do something
    }
}

void tick_elements() {
    
    camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    for(int i = min_x; i <= max_x; ++i){
        for(int j = min_y; j <= max_y; ++j)
        {
            int u = 0;
            int l = 0;
            if(U.find({i, j}) != U.end())
                u = 1;
            if(L.find({i, j}) != L.end())
                l = 1;
            string filename;
            if(u == 0 && l == 0){
                filename = "assets/empty.bmp";
            }
            else if(u == 0 && l == 1){
                filename = "assets/left.bmp";
            }
            else if(u == 1 && l == 0){
                filename = "assets/top.bmp";
            }
            else if(u == 1 && l == 1){
                filename = "assets/left_top.bmp";
            }
            else{
                assert(false);
            }
        }
    }            

    

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
    // distance_id = glGetUniformLocation(programID, "distance");
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(TextureID, 0);


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


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);
    generate_maze();

    initGL (window, width, height);

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
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

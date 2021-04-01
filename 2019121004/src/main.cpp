#include "main.h"
#include "player.h"
#include "enemy.h"
#include "timer.h"
#include "goal.h"
#include "lives.h"
#include "treasure.h"
#include "scoreboard.h"
#include <bits/stdc++.h>
#include <unistd.h>
#include "empty.h"
#include "fire.h"
#include "battery.h"

glm::mat4 VP;

using namespace std;
int hh=0;
int score = 0, lives = 0, range = 10, WIN = 0,CRASH = 0, LOSE = 0 , N, unlock_obstacles=0;
Scoreboard sc;
const int st_x = 0, st_y = 0,  min_x = -10, max_x = 10, max_y = 10,  min_y = -10, MAXN = 1e6 + 5;
int difficulty = 2;
float max_offset = 10, min_offset = 4, offset = 6, powerups_collected=0, lives_collected = 0;
int kill_task = 0, collect_task = 0, task2_complete=0, tasks_completed = 0, light=0;

struct EDGE{
    int x_src, y_src;
    int x_dest, y_dest;
};


map < pair <int, int> , int > U;
map < pair <int, int> , int > L;

vector <EDGE> edges;
int sz[MAXN];
int parent[MAXN];

int root(int node)
{
	if(parent[node] != node)return parent[node] = root(parent[node]);
	return node;
}
bool equal_var;
void _union(int a, int b)
{
	if(a==b)return;
	a = root(a);
	b = root(b);
    if(a == b){
        equal_var = true;
    }
	if(sz[a]>=sz[b]){
        parent[b] = parent[a];	
        sz[a]+=sz[b];
        
	}
	else
	{
        parent[a] = parent[b];
        sz[b]+=sz[a];
		
	}
}
vector <EDGE> blocks;
void generate_maze(){
    N = 0;
    for(int i = min_x; i <= max_x; ++i)
    {
        int src_x = -1;
        for(int j = min_y; j <= max_y; ++j){
            if(i != max_x){
                EDGE tmp;
                tmp.x_src = i;
                tmp.y_src = j;
                src_x = i;
                int next=i + 1;
                tmp.x_dest = next;
                next=next+1;
                tmp.y_dest = j;
                edges.push_back(tmp);
            }
            
            if(j == max_y) hh=hh+2;
            else {
                EDGE tmp;
                tmp.x_src = i;
                if(hh==1) hh=hh+1;
                tmp.y_src = j;
                tmp.x_dest = i;
                src_x = i;
                tmp.y_dest = j + 1;
                edges.push_back(tmp);
            }
            N++;
        }
    }
    int i = 1;
    while(i<=N)
    {
        sz[i] = 1;
        parent[i] = i;
        i ++;
    }
    while(edges.size() > 0)
    {
        int pick_idx = rand() % edges.size();
        int from = (edges[pick_idx].x_src - min_x);
        from *=  (max_y - min_y + 1);
        from += (edges[pick_idx].y_src - min_y);

        int to = (edges[pick_idx].x_dest - min_x);
        to *= (max_y - min_y + 1); 
        to += (edges[pick_idx].y_dest - min_y);

        int u = root(from);
        int v = root(to);
        if(u != v){
            _union(u, v);
        }
        else{
            if(rand() % difficulty == 1)
            {
                _union(u, v);
            }
            else{
                int diff = to - from;
                hh=7777777;
                if(diff != 1)
                    L[{edges[pick_idx].x_dest, edges[pick_idx].y_dest}] = 1;
                else if(hh==2) hh=hh+1;
                else if (diff==1)
                     U[{edges[pick_idx].x_src, edges[pick_idx].y_src}] = 1;
            }            
        }
        if(hh==2) hh=hh+1;
        edges.erase(edges.begin() + pick_idx);
    }
}
GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
GLuint distance_id;
/**************************
* Customizable functions *
**************************/
Player player;
vector <Fire> fires;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0,camera_rotation_angle = 0;
int EXIT = 0;
vector <Empty> empty;
Goal goal;
Goal treasure;

map < pair <int, int> , int > V; 
Enemy enemy;
vector <Lives> hearts;
Timer t60(1.0 / 30);
vector <Battery> batteries;
map < pair <int, int> , int > H;

// Eye - Location of camera. Don't change unless you are sure!!
glm::vec3 eye ( 0, 0, 5 );
// Target - Where is the camera looking at.  Don't change unless you are sure!!
glm::vec3 target (0, 0, 0);
// Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
glm::vec3 up (0, 1, 0);


bool check_wall(float x, float y, float prev_x, float prev_y)
{
    int diff = x - prev_x;
    if( diff == 1){
        // Right has been pressed.
        if(x > max_x)
            return true;
        auto itr = L.find({x, y});
        if( itr != L.end())
            return true;
    }
    diff = prev_x - x;
    if(diff == 1){
        // Left has been pressed
        auto itr = L.find({prev_x, prev_y});
        if( itr != L.end())
            return true;
        if(x < min_x)
            return true;
    }
    diff = y - prev_y;
    if( diff == 1){
        // Up has been pressed.
        auto itr = U.find({prev_x, prev_y}) ;
        if(itr != U.end())
            return true;
        if(y > max_y)
            return true;
    }
    diff = prev_y - y;
    if(diff == 1){
        // Down has been pressed
        auto itr = U.find({x, y});
        if(itr != U.end())
            return true;
        if(y < min_y)
            return true;
    }
    return false;
}


void dfs(int x, int y, int depth)
{
    queue < pair < pair <int, int> , int> > Q;
    int aa=0;
    Q.push({{x, y}, depth});
    if(hh==2) hh=hh+1;
    while(Q.empty() == false)
    {
        int r,c,d;
        d = Q.front().second;
        if(d) hh=hh-1;
        r = Q.front().first.first;
        if(r==d) hh=hh+1;
        c = Q.front().first.second;
        int temp;
        Q.pop();
        if(d <= range) {
            H[{r, c}] = d;
            V[{r, c}] = true;
            int i = min_x;
            while( i<=max_x)
            {
                for(int j = min_y; j <= max_y; ++j){
                    temp=(abs(i) + abs(j)) ;
                    if(temp!= 1)
                        continue;
                    
                    if(!check_wall(r + i, c + j, r, c))
                    {
                        if(V.find({r + i, c + j}) == V.end())
                        {
                             Q.push({{r + i, c + j}, d + 1});
                            V[{r + i, c + j}] = true;

                        }

                    } 
                }
                i += 1;
            }
        }
        else break;
        
    }
}

void check_collision()
{
    bounding_box_t p; 
    p.height = 1;
    p.width = 1;
    p.x = player.position.x;
    p.y = player.position.y;
   
    int i = 0;

    // for(int i = 0; i < fires.size(); ++i){
        while(i < fires.size()){
            bounding_box_t a; 
            a.x = fires[i].position.x; 
            a.width = 1; 
            if(hh==2) hh=hh+2;
            a.y = fires[i].position.y; 
            a.height = 1;
            if(detect_collision(a, p)){
                if(hh==2) hh+1;
                fires.erase(fires.begin() + i);
                score = score- 30;
                i = i - 1;
            }
            i ++;
    }
    
    i = 0;
    int col = 1;
     while(i < batteries.size()){
        if(batteries[i].position.x == player.position.x) {
        if(col==1) col=col+1;
        if(batteries[i].position.y == player.position.y)
        {
            cout<< "collected powerup! \n";
            
            powerups_collected += 1;
            cout<< ""<<powerups_collected ;
            score = score+ 25;
            batteries.erase(batteries.begin() + i);
            range= range+3;
            i = i - 1;
        }
        }
        i ++;
    }
    i = 0;
    while(i < hearts.size()){
        if(hearts[i].position.x == player.position.x){
        if(col==1) col=col+1;
        if(hearts[i].position.y == player.position.y)
        {
            lives_collected += 1;
            score =score+40;
            cout<< "life_collected! \n" ;
            cout<< ""<<lives_collected ;
            hearts.erase(hearts.begin() + i);
            lives=lives+1;
            i = i - 1;
            
        }
        }
        i ++;
    }

    if(player.position.x == enemy.position.x && kill_task==0){
    if((player.position.y == enemy.position.y ) || range == 0){
        lives--;
        if(lives < 0){
            cout << "OOPS :( You lose! \n";
            CRASH = 1;
            LOSE = 1;
        }
        else{
        
            if(range != 0) score=score-50;
            else range=8;
            CRASH = 1;
        }
    }
    }

    if(player.position.x == goal.position.x && kill_task==0){
    if(player.position.y == goal.position.y)
    {
        cout << "Task 1 completed, Vapourize button found! \n";
        cout<< "yay you killed enemy! \n" ;
        kill_task = 1;
        tasks_completed += 1;
        enemy.set_position(max_x, max_y);
       
        
    }
    }
    if(player.position.x == treasure.position.x && unlock_obstacles!=1)
    {
        if(player.position.y == treasure.position.y)
        {
            unlock_obstacles = 1;

            cout<< "yay, you found the key to treasure! lives and powerups realeased! \n";
            // place powerups and lives randomly
            
            int num = 2;
            int arr_x[5] = {st_x+3, st_x-1, st_x-5, st_x+8};
            int arr_y[5] = {st_y+3, st_y-1, st_y-5, st_y+8};

            int arr2_x[5] = {st_x+2, st_x-2, st_x-7, st_x+4};
            int arr2_y[5] = {st_y+1, st_y-3, st_y-9, st_y+12};

            int arr3_x[5] = {st_x+1, st_x-4, st_x-16, st_x+20};
            int arr3_y[5] = {st_y+2, st_y+4, st_y-16, st_y+20};

            batteries = {}, hearts= {}, fires = {};

            for(int i = 0; i< num; i++)
            {
                for(int j =0; j<num;j++)
                {
                    
                    batteries.push_back(Battery(arr_x[i], arr_y[j], COLOR_WHITE, "assets/battery.bmp"));
                    hearts.push_back(Lives(arr2_x[i], arr2_y[i], COLOR_MAGENTA, ""));
                    fires.push_back(Fire(arr3_x[i], arr3_y[j], COLOR_WOOD, "assets/fire.bmp"));

                }
            
            }
        }
    
    }

    if( lives_collected >=2 && powerups_collected>=2 && task2_complete==0)
    {
        cout<< "Task 2 complete! \n";
        task2_complete = 1;
        tasks_completed += 1;

    } 
    
    if(kill_task == 1 && lives_collected>=2 && powerups_collected>=2)
    {
        cout<< "Both tasks Completed. \n";
        cout<< "Congratulations, You Won! \n";
        WIN = 1;
    }
    
}


void change_light(){
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    if(light==1) programID = LoadShaders("Sample_GL.vert", "Sample_GL2.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
    distance_id = glGetUniformLocation(programID, "distance");
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(TextureID, 0);
}


/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {

    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    if(light==1) programID = LoadShaders("Sample_GL.vert", "Sample_GL2.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
    distance_id = glGetUniformLocation(programID, "distance");
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(TextureID, 0);
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);


    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    VP = Matrices.projection * Matrices.view;


    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // glm::vec3 CameraPos;
    // glm::mat4 ConversionMatrix;

    // ConversionMatrix = glm::inverse(VP);
    // CameraPos = ConversionMatrix[3];

    if(light == 1) glUniform1f((0,0,0), 1);
    // Scene render
    V.clear();
    H.clear();
    dfs(player.position.x, player.position.y, 0);

    int size = empty.size();
    for(int i = 0; i < size; ++i){
        auto itr2 = H.end();
        auto itr = H.find({empty[i].position.x, empty[i].position.y});
        
        if( itr!= itr2)
        {
            empty[i].draw(VP);
            
            
        } 
        if( itr!= itr2)
        {
            float res = range - H[{empty[i].position.x, empty[i].position.y}] * 1.0 ;
            if(light==0) glUniform1f(distance_id, res/ range);
            
        } 
            
    }

    if(unlock_obstacles==1)
    {

        size = fires.size();
        for(int i = 0; i < size; ++i){
            auto itr2 = H.end();
            auto itr = H.find({fires[i].position.x, fires[i].position.y});
            
            if( itr!= itr2)
            {
                fires[i].draw(VP);
                
                
            } 
            if( itr!= itr2)
            {
                float res = range - H[{fires[i].position.x, fires[i].position.y}] * 1.0 ;
                if(light==0) glUniform1f(distance_id, res/ range);
                
            } 
                
        }
        size = batteries.size();
        for(int i = 0; i < size; ++i){
            auto itr2 = H.end();
            auto itr = H.find({batteries[i].position.x, batteries[i].position.y});
            
            if( itr!= itr2) batteries[i].draw(VP);  
            
            if( itr!= itr2)
            {
                float res = range - H[{batteries[i].position.x, batteries[i].position.y}] * 1.0 ;
                if(light==0) glUniform1f(distance_id, res/ range);
                
            } 
                
        }

        size = hearts.size();
        for(int i = 0; i < size; ++i){
            auto itr2 = H.end();
            auto itr = H.find({hearts[i].position.x, hearts[i].position.y});
            
            if( itr!= itr2) hearts[i].draw(VP);    
            
            if( itr!= itr2)
            {
                float res = range - H[{hearts[i].position.x, hearts[i].position.y}] * 1.0 ;
                if(light==0) glUniform1f(distance_id, res/ range);
                
            } 
                
        }

    }
    

    auto itr = H.find({goal.position.x, goal.position.y});
    if( itr!= H.end()){
        goal.draw(VP);
        float res = range - H[{goal.position.x, goal.position.y}] * 1.0 ;
        if(light==0) glUniform1f(distance_id, res/ range);
        
    }
    itr = H.find({treasure.position.x, treasure.position.y});
    if( itr!= H.end()){
        treasure.draw(VP);
        float res = range - H[{treasure.position.x, treasure.position.y}] * 1.0 ;
        if(light==0) glUniform1f(distance_id, res/ range);
        
    }
    if(light==0) glUniform1f(distance_id, 1.0);
    player.draw(VP);
    itr = H.find({enemy.position.x, enemy.position.y});
    enemy.draw(VP);
    if(itr != H.end())
    {
        enemy.draw(VP);
        float res = range - H[{enemy.position.x, enemy.position.y}] * 1.0;
        if(light==0) glUniform1f(distance_id, res/ range);
        
    }
    if(light==0) glUniform1f(distance_id, 1.0);
    sc.draw(VP);
    check_collision();
}
int visited[max_x - min_x + 1][max_y - min_y + 1];
int tick_count = 0;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    int z_keypressed;
    if(key == GLFW_KEY_1){
        difficulty = 2;
        reset_screen();
    }
    if(key == GLFW_KEY_2){
        difficulty = 3;
        reset_screen();
    }
    if(key == GLFW_KEY_Z){
        offset= offset-0.02;
        if(hh==2) hh=hh+1;
        offset = max(min(offset, max_offset), min_offset);
        z_keypressed = 1;
        reset_screen();
    }
    if(key == GLFW_KEY_L){
        light = 1;
        change_light();
        reset_screen();
    }
    else if(key == GLFW_KEY_A){
        if(action == GLFW_RELEASE)
        {
        eye.x -= 1;
        target.x -= 1;
        }
        //screen_center_x -= 1;
    }
    else if(key == GLFW_KEY_W)
    {
        if(action == GLFW_RELEASE){
        eye.y += 1;
        target.y += 1;
        //screen_center_y += 1;
        }
    }
     
    else if(key == GLFW_KEY_D)
    {
        if(action == GLFW_RELEASE){
            eye.x += 1;
            target.x += 1;
            //screen_center_x += 1;
        }
        
    }
    else if(key == GLFW_KEY_X)
    {
        offset+=0.02;
        offset = max( min(offset, max_offset), min_offset);
        reset_screen();
    }
    else if(key == GLFW_KEY_S)
    {
        if(action == GLFW_RELEASE)
        {
            eye.y -= 1;
            target.y -= 1;
            //screen_center_y -= 1;
        }
    }
    
    if (key == GLFW_KEY_RIGHT)
    {
        bool is_wall = check_wall(player.position.x + 1, player.position.y, player.position.x, player.position.y);
        if(action == GLFW_RELEASE)
        {
            if(is_wall== false) player.position.x += 1, player.direction = 90;

        }

    }

    if (key == GLFW_KEY_LEFT)
    {
        bool is_wall = check_wall(player.position.x - 1, player.position.y, player.position.x, player.position.y);
        if(action == GLFW_RELEASE)
        {
            if(is_wall== false) player.position.x -= 1, player.direction = 270;

        }

    }

     if (key == GLFW_KEY_UP)
    {
        bool is_wall = check_wall(player.position.x , player.position.y + 1, player.position.x, player.position.y);
        if(action == GLFW_RELEASE)
        {
            if(is_wall== false) player.position.y += 1, player.direction = 180;

        }

    }

    if (key == GLFW_KEY_DOWN)
    {
        bool is_wall = check_wall(player.position.x , player.position.y - 1, player.position.x, player.position.y);
        if(action == GLFW_RELEASE)
        {
            if(is_wall== false) player.position.y -= 1, player.direction = 0;

        }

    }
    if(key == GLFW_KEY_ESCAPE)
        quit(window);
}




int Px[max_x - min_x + 1][max_y - min_y + 1];
int gg=0;


void tick_input(GLFWwindow *window) {
    
    
}

int Py[max_x - min_x + 1][max_y - min_y + 1];

void bfs(int r, int c)
{
    int eq = 0;
    queue < pair <int, int> > Q;
    int iters = 0;
    Q.push({r, c});
    while(!Q.empty())
    {
        pair <int, int> tmp = Q.front();
        iters += 1;
        Q.pop();
        if(r==c)
        {
            eq = 1;
        }
        int r = tmp.first;
        int c = tmp.second;
  
        if(r == player.position.x)
        {
            if(c == player.position.y) break;

        }
        int i = -1;
        visited[r - min_x][c - min_y] = true;
        
        while(i <=1){
            int j = -1;
            int pos;
            int a = 0;
            
            for(int j = -1; j <= 1; ++j){
                int a = abs(i) + abs(j);
                if(a != 1)
                    continue;
                if(a==0)
                {
                    pos = -1;
                }
                assert(abs(i) + abs(j) == 1);
                if(!check_wall(r + i, c + j, r, c))
                {
                    
                    int one=c + j - min_y;
                    int two=r + i - min_x;
                    if(!visited[two][one]){
                        if(hh==2) hh=hh+1;
                        Px[two][one] = r;
                        Py[two][one] = c;
                        int r_c = r;

                        int vis = true;
                      
                        assert((abs(r + i - Px[two][one]) + abs(c + j - Py[two][one])) == 1);
                        Q.push({r + i, c + j});

                    }   
                }
            }
            i += 1;
        }
    }
}



void tick_elements() {
    // Update Scoreboard
    sc.score = score;
    sc.screen_x = eye.x;
    sc.lives = lives;
    sc.light = light;
    sc.tasks_completed = tasks_completed;
    sc.range = range;
    sc.screen_y = eye.y;
    sc.offset = offset;
    sc.max_range = 2 * max(max_x - min_x, max_y - min_y);
    int i = 0;
    while(i< empty.size()){
        empty[i].tick();
        i += 1;
    }
    while(i< fires.size()){
        fires[i].tick();
        i += 1;
    }
    while(i< batteries.size()){
        batteries[i].tick();
        i += 1;
    }
    while(i< hearts.size()){
        hearts[i].tick();
        i += 1;
    }
    player.tick();


    tick_count += 1;
    tick_count = tick_count % 100;
    
    if(tick_count == 0){
        int i = 0;
        while(i < (max_x - min_x + 1)){
            int j = 0;
            int vis_cur = -1;
            for(int j = 0; j < (max_y - min_y + 1); ++j)
            {
                Px[i][j] = -1;
                Py[i][j] = -1;
                if(Px[i][j]==Py[i][j])
                {
                    vis_cur = 1;

                }
                visited[i][j] = false;
            }
            i += 1;
        }
        // enemy chases player via shortest path.
        if(kill_task == 0)
        {
            bfs(enemy.position.x, enemy.position.y);
            int eq_x = 0;
            int resx = enemy.position.x;
            int currx = player.position.x;
            if(resx == currx)
            {
                eq_x = 1;
            }
            int eq_y = 0;
            int resy = enemy.position.y;
            int curry = player.position.y;
            if(resy == curry)
            {
                eq_y = 1;
            }
            
            int eq_nodes;
            while(!(currx == enemy.position.x && curry == enemy.position.y)){
                resx = currx;
                resy = curry;
                eq_nodes += 1;
                currx = Px[resx - min_x][resy - min_y];
                curry = Py[resx - min_x][resy - min_y];
                
            }
            int dir = 0;
            int diff = (enemy.position.x - resx);
            if(diff == 1){
                dir = 270;
                enemy.direction = dir;
            }
            else if((resx - enemy.position.x) == 1){
                dir = 90;
                enemy.direction = dir;
            }
            else if((enemy.position.y - resy) == 1){
                dir = 0;
                enemy.direction = dir;
            }
            else if((resy - enemy.position.y) == 1){
                dir = 180;
                enemy.direction = dir;
            }
            score=score- 1;
            enemy.position.x = resx;
            range = range-1;
            enemy.position.y = resy;

        }
        
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    sc = Scoreboard(screen_center_x, screen_center_y, COLOR_BLACK, "");
    

    int x_range = (max_x/2 - min_x/2)+1;
    int x_pos_goal = min_x + rand() % range;


    int y_range = (max_y - min_y)+1;
    int y_pos_goal;
    
    if(difficulty == 2) y_pos_goal = st_y+3;
    if(difficulty == 3) y_pos_goal = min_y + rand() % range;
    y_pos_goal = st_y;
    goal = Goal(x_pos_goal, y_pos_goal, COLOR_WHITE, "assets/circle.bmp");
    
    int x_pos_treasure = st_x;
    int y_pos_treasure = st_y + 1;
    treasure = Goal(x_pos_treasure, y_pos_treasure, COLOR_RED, "assets/treasure.bmp");
    int x_pos_enemy = min_x + rand() % range;
    int y_pos_enemy = min_y + rand() % range;

    if(x_pos_enemy != x_pos_goal && y_pos_enemy != y_pos_goal)  //make sure enemy and goal are not placed at same position
    {
        enemy = Enemy(x_pos_enemy, y_pos_enemy, COLOR_RED, "");
    }
    else{
        enemy = Enemy(5, y_pos_enemy, COLOR_RED, "");
    }
    
    for(int i = min_x; i <= max_x; ++i){
        int first = 0;
        int curr = 0;
        for(int j = min_y; j <= max_y; ++j)
        {
            if(first==0) curr = i;
            int u = 0;
            if(U.find({i, j}) != U.end())
                u = 1;

            int l = 0;
            if(L.find({i, j}) != L.end())
                l = 1;
            string filename;
            if(u == 0)
            {
                if(l == 1) filename = "assets/left.bmp";
                if(hh==1) hh=hh+1;
                if(l == 0)filename = "assets/empty.bmp";
            }
            else if(u != 1) assert(false);
            else{
                if(l == 1) filename = "assets/left_top.bmp";
                if(l == 0) filename = "assets/top.bmp";
                
            }
            empty.push_back(Empty(i, j, COLOR_BLACK, filename));
            if((st_x == i && st_y == j) || (max_x == i && max_y == j)) continue;
         
            
        }
        
    }
    player = Player(st_x, st_y, COLOR_RED, "assets/player.bmp");
   
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    if(light==1) programID = LoadShaders("Sample_GL.vert", "Sample_GL2.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
    distance_id = glGetUniformLocation(programID, "distance");
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(TextureID, 0);
    

    reshapeWindow (window, width, height);
    glClearColor (0.0 / 256.0, 0.0 / 256.0, 0.0 / 256.0, 0.0f); // R, G, B, A
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
    int width  = 768;
    int height = 768;

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
        glfwSetKeyCallback(window, key_callback);
        // Poll for Keyboard and mouse events
        glfwPollEvents();

        if(WIN)
            quit(window);
        else hh=hh+1;
        if(CRASH)
        {
            if(LOSE) quit(window);
            else{
                enemy.position.y = max_y;
                CRASH = 0;
                hh=hh+1;
                enemy.position.x = min_x;
                
            }
        }
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    if(a.x == b.x && a.y == b.y)
        return true;
    return false;
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + offset / screen_zoom;
    float bottom = screen_center_y - offset / screen_zoom;
    float left   = screen_center_x - offset / screen_zoom;
    float right  = screen_center_x + offset / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
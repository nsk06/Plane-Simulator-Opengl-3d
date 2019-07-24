#include "main.h"
#include "timer.h"
#include "plane.h"
#include "water.h"
#include "island.h"
#include "cuboid.h"
#include "sphere.h"
#include "volcanoe.h"
#include "missile.h"
#include "bomb.h"
#include "dashboard.h"
#include "powerups.h"
#include "compass.h"
#include "sphere.h"
#include "pointer.h"
#include "boat_enemy.h"
#include "ring.h"
#include "parachute.h"

using namespace std;
GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Plane plane;
Water water;
std::vector<Island> islands;
std::vector<Island>rand_islands;
std::vector<Missile> missiles;
std::vector<Bomb> bombs;
std::vector<Powerups> fuels;
std::vector<Volcanoe> volcanoes;
Dashboard dashboard;
Compass compass;
Pointer pointer;
std::vector<Boat_Enemy> boats;
std::vector<Ring> rings;
std::vector<Parachute> paras;

bounding_box_t plane_box;
bounding_box_t fuel_box;
bounding_box_t cannon_ball;
bounding_box_t island_box;
bounding_box_t missile_box;
bounding_box_t bomb_box;
bounding_box_t boat_box;
bounding_box_t para_box_person;
bounding_box_t para_box_goodies;
bounding_box_t ring_box;

int width  = 1080;
int height = 960;
double curx = 0,cury = 0,helix = 0,heliy = 0,prevx = 0,prevy = 0;
int pointer_position = 0;
int missile_shoot = -1;
int bomb_shoot = -1;
int cam_view = 1;
glm::vec3 targetpos;
int nummissiles = 10,numbombs = 5,target = 5;
int smoke_timer = -1;
int special = -1;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0,camera_zoom = 0;
float camera_rotation_angle = 40;
long long int frame_count = 0,view_button_change = -1;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    glm::vec3 eye2 ( 0, 0, 5);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target2 (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up2 (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view2 = glm::lookAt( eye2, target2, up2);
    glm::mat4 VP2 = Matrices.projection2 * Matrices.view2;
    if(abs(compass.cplane_position.x) < .7 && abs(compass.cplane_position.y) < .7)
    {
        compass.cplane_position = glm::vec3((plane.position.x*.8)/400.0,-(plane.position.z*.8)/800.0,0);
    }
    compass.rotation = plane.rotationy;
    dashboard.draw(VP2);
    compass.draw(VP2);
    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;

    if(cam_view == 1)             //Follow UP
    {
        glm::vec3 eye ( plane.position.x +8*sin(plane.rotationy*M_PI/180.0), plane.position.y+4,plane.position.z+8*cos(plane.rotationy*M_PI/180.0));
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        glm::vec3 target (plane.position.x,plane.position.y,plane.position.z);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 up (0, 1, 0);
    }
    else if(cam_view == 2)                     //FRONT
    {
        glm::vec3 eye ( plane.position.x-4*cos(plane.rotationx*M_PI/180.0)*sin(plane.rotationy*M_PI/180.0),plane.position.y +4*sin(plane.rotationx*M_PI/180.0),plane.position.z -4*cos(plane.rotationx*M_PI/180.0)*cos(plane.rotationy*M_PI/180.0));
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 target ( plane.position.x-8*cos(plane.rotationx*M_PI/180.0)*sin(plane.rotationy*M_PI/180.0),plane.position.y +8*sin(plane.rotationx*M_PI/180.0),plane.position.z -8*cos(plane.rotationx*M_PI/180.0)*cos(plane.rotationy*M_PI/180.0));
        glm::vec3 up (0, 1, 0);
    }
    else if(cam_view == 3)                      //TOP
    {
        glm::vec3 eye ( plane.position.x,plane.position.y+25,plane.position.z);
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        glm::vec3 target (plane.position.x,plane.position.y, plane.position.z);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 up (0,0,-1);
    }
    else if(cam_view == 4)                     //Tower
    {
        glm::vec3 eye ( 16,10,plane.position.z+10);
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        glm::vec3 target (plane.position.x,plane.position.y, plane.position.z-2);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 up (0,1,0);
    }
    else if(cam_view == 5)             //Cam_view             
    {
        glfwGetCursorPos(window,&curx,&cury);
        helix += (curx -prevx)*90/width;
        heliy -= (cury -prevy)*90/height;
        prevx = curx;
        prevy = cury;
         glm::vec3 eye ( plane.position.x+(12 - 8*camera_zoom)*cos(helix*M_PI/180)*sin(heliy*M_PI/180),
                        plane.position.y+(12 - 8*camera_zoom)*cos(heliy*M_PI/180),
                        plane.position.z -(20 - 8*camera_zoom)*sin(helix*M_PI/180)*sin(heliy*M_PI/180));
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        glm::vec3 target (plane.position.x ,plane.position.y, plane.position.z);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 up (0, 1, 0);
    }
    else if(cam_view == 6)   //Normal
    {
        glm::vec3 eye ( 0,5,10);
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        glm::vec3 target (plane.position.x,plane.position.y, plane.position.z-2);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        glm::vec3 up (0,1,0);
    }
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP ; 
    VP = Matrices.view;
    VP  = Matrices.projection *VP;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model


    
    // Scene render
    dashboard.draw(Matrices.projection2);
    water.draw(VP);
    vector<Island>:: iterator itru;
    for(auto itru = islands.begin();itru!=islands.end();itru++)
    {
        if(dist_between_objects((*itru).position.x,(*itru).position.y,(*itru).position.z,plane.position.x,plane.position.y,plane.position.z) < 75)
        {
            (*itru).draw(VP);
        }
    }
     for(auto itru = rand_islands.begin();itru!=rand_islands.end();itru++)
    {
            (*itru).draw(VP);
    }
      for(auto itru = volcanoes.begin();itru!=volcanoes.end();itru++)
    {
            (*itru).draw(VP);
    }
      for(auto itru = rings.begin();itru!=rings.end();itru++)
    {
            (*itru).draw(VP);
    }
    vector<Missile>:: iterator my_itr;
    if(missiles.size()>0)
    {
        for(auto my_itr = missiles.begin();my_itr!=missiles.end();my_itr++)
        {
                (*my_itr).draw(VP);
        }
    }
    vector<Bomb>:: iterator my_itr2;
    if(bombs.size()>0)
    {
        for(auto my_itr2 = bombs.begin();my_itr2!=bombs.end();my_itr2++)
        {
                (*my_itr2).draw(VP);
        }
    }
     vector<Powerups>:: iterator my_itr3;
    if(fuels.size()>0)
    {
        for(auto my_itr3 = fuels.begin();my_itr3!=fuels.end();my_itr3++)
        {
                (*my_itr3).draw(VP);
        }
    }
    if(boats.size() > 0)
    {
        for(auto my_itr3 = boats.begin();my_itr3!=boats.end();my_itr3++)
        {
                (*my_itr3).draw(VP);
        }
    }
     if(paras.size() > 0)
    {
        for(auto my_itr3 = paras.begin();my_itr3!=paras.end();my_itr3++)
        {
                (*my_itr3).draw(VP);
        }
    }
    plane.draw(VP);
    glDisable (GL_DEPTH_TEST);
    glClear (GL_DEPTH_BUFFER_BIT);
    pointer.draw(VP);
    glEnable (GL_DEPTH_TEST);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up  = glfwGetKey(window,GLFW_KEY_UP);
    int down  = glfwGetKey(window,GLFW_KEY_DOWN);
    int tow  = glfwGetKey(window,GLFW_KEY_T);
    int first = glfwGetKey(window,GLFW_KEY_F);
    int change_view = glfwGetKey(window,GLFW_KEY_V);
    int altitude_up = glfwGetKey(window,GLFW_KEY_SPACE);
    int altitude_down = glfwGetKey(window,GLFW_KEY_0);
    int tilt_left = glfwGetKey(window,GLFW_KEY_A);
    int tilt_right = glfwGetKey(window,GLFW_KEY_D);
    int rotate_left = glfwGetKey(window,GLFW_KEY_Q);
    int rotate_right = glfwGetKey(window,GLFW_KEY_E);
    int pitch_up = glfwGetKey(window,GLFW_KEY_Z);
    int pitch_down = glfwGetKey(window,GLFW_KEY_C);
    int missile_throw = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT);
    int bomb_throw = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT);
    int target_missile = glfwGetKey(window,GLFW_KEY_T);
    int barrel_role = glfwGetKey(window,GLFW_KEY_B);
    if (left) {
        plane.position.x -= plane.speed;
    }
    else if(right)
    {
        plane.position.x += plane.speed;
    }
    else if(up)
    {
        plane.position.z -= plane.speed*cos(plane.rotationx*M_PI/180.0)*cos(plane.rotationy*M_PI/180.0);
        plane.position.x -= plane.speed*cos(plane.rotationx*M_PI/180.0)*sin(plane.rotationy*M_PI/180.0);
        plane.position.y += plane.speed*sin(plane.rotationx*M_PI/180.0);
        plane.keypress = 1;
    }
    else if(down)
    {
        plane.position.z += plane.speed*cos(plane.rotationx*M_PI/180.0)*cos(plane.rotationy*M_PI/180.0);
        plane.position.x += plane.speed*cos(plane.rotationx*M_PI/180.0)*sin(plane.rotationy*M_PI/180.0);
        plane.position.y -= plane.speed*sin(plane.rotationx*M_PI/180.0);
    }
    else if(change_view && view_button_change < 0)
    {
        cam_view = (cam_view)%6+1;
        view_button_change = 0;
    }
    else if(altitude_up)
    {
        plane.position.y += plane.speed/3;
    }
    else if(altitude_down)
    {
        plane.position.y -= plane.speed/2;
    }
    else if(tilt_left)
    {
        plane.rotationz += 3;
       // plane.axes_of_rotation = glm::vec3(0,0,1);
    }
    else if(tilt_right)
    {
        plane.rotationz -= 3;
        //plane.axes_of_rotation = glm::vec3(0,0,1);
    }
    else if(rotate_left)
    {
        plane.rotationy += 2;
        //plane.axes_of_rotation = glm::vec3(0,1,0);
    }
    else if(rotate_right)
    {
        plane.rotationy -= 2;
        //plane.axes_of_rotation = glm::vec3(0,1,0);
    }
    else if(pitch_down)
    {
        plane.rotationx +=1;
    }
    else if(pitch_up)
    {
        plane.rotationx -=1;
    }
    else if(missile_throw && missile_shoot < 0 &&nummissiles > 0) 
    {
        Missile newmissile = Missile(plane.position.x,plane.position.y,plane.position.z);
        newmissile.rotationx = plane.rotationx;
        newmissile.rotationy = plane.rotationy;
        newmissile.shoot_dir = glm::normalize(targetpos);
        nummissiles -=1;
        newmissile.type = 0;
        missiles.push_back(newmissile);
        missile_shoot = 0;
        system("aplay missile.wav&");                    
    }
    else if(bomb_throw && bomb_shoot < 0 &&numbombs > 0) 
    {
        Bomb newbomb = Bomb(plane.position.x,plane.position.y,plane.position.z);
        bombs.push_back(newbomb);
        bomb_shoot = 0;
        numbombs -= 1;
        system("aplay bomb.wav&");                    
    }
    else if(target_missile && target > 0 && missile_shoot < 0)
    {
        Missile newmissile = Missile(plane.position.x,plane.position.y,plane.position.z);
        newmissile.rotationx = plane.rotationx;
        newmissile.rotationy = plane.rotationy;
        newmissile.shoot_dir = glm::normalize(targetpos);
        target -=1;
        newmissile.type = 1;
        missiles.push_back(newmissile);
        missile_shoot = 0;
        system("aplay missile.wav&");                    
    }
    else if(barrel_role)
    {
        special = 0;
    }
}

void tick_elements() {
    plane.tick();
    compass.tick();
  for(auto itru = paras.begin();itru!=paras.end();itru++)
    {
        if(dist_between_objects((*itru).position.x,(*itru).position.y,(*itru).position.z,plane.position.x,plane.position.y,plane.position.z) < 25)
            (*itru).tick();
    }
      for(auto itru = rand_islands.begin();itru!=rand_islands.end();itru++)
    {
            (*itru).tick();
    }
 for(auto itru = rings.begin();itru!=rings.end();itru++)
    {
            (*itru).tick();
    }

    vector<Island>:: iterator itru;
    int k = 0;
    pointer_position = 0;
    for(auto itru = islands.begin();itru!=islands.end();itru++)
    {
        if((*itru).lives <= 0)
        {
            compass.cpos[k].type = 1;
            pointer_position++;
            if(pointer_position == 5)
            {
                cout << "YOU WON" << endl;
                quit(window);
            }
        }
        if(dist_between_objects((*itru).position.x,(*itru).position.y,(*itru).position.z,plane.position.x,plane.position.y,plane.position.z) < 40)
        {
            (*itru).tick();
          
        }
          if((*itru).fireballs.size() > 0)
            {
                std::vector<Sphere>::iterator it;
                for(auto it = (*itru).fireballs.begin();it!=(*itru).fireballs.end();it++)
                {
                    (*it).tick();
                    cannon_ball.x = (*it).position.x;
                    cannon_ball.y = (*it).position.y;
                    cannon_ball.z = (*it).position.z;
                    if(detect_collision(cannon_ball,plane_box) == true && plane.powertime < 0)
                    {
                        dashboard.scale_factor_health.y -= .2;
                        plane.score -= 50;
                        (*itru).fireballs.erase(it);
                        break;
                    }
                    if((*it).position.y > 6 )
                    {
                        (*itru).fireballs.erase(it);
                        break;
                    }
                }
            }
        k++;
    }
    for(auto it = boats.begin();it != boats.end();it++)
    {
        if(dist_between_objects((*it).position.x,(*it).position.y,(*it).position.z,plane.position.x,plane.position.y,plane.position.z) < 30)
        {
            (*it).start_fire = true;
        }
        else
        {
            (*it).start_fire = false;
        }
        (*it).tick();
        if((*it).type == 1)
        {
            (*it).Cannon.rotationx = glm::acos(glm::dot(normalize(plane.position - (*it).position),normalize(glm::vec3(0,1,0))))*180/M_PI;
            glm::vec3 temp = plane.position - (*it).position;
            temp.y = 0;
            (*it).Cannon.rotationy =  glm::acos(glm::dot(normalize(temp),normalize(glm::vec3(0,0,1))))*180/M_PI;
            if(temp.x < 0)
            {
                (*it).Cannon.rotationy = -glm::acos(glm::dot(normalize(temp),normalize(glm::vec3(0,0,1))))*180/M_PI;
            }
            (*it).tick();
            if((*it).cannonballs.size() > 0)
                    {
                        for(auto itr = (*it).cannonballs.begin();itr!=(*it).cannonballs.end();itr++)
                        {
                            (*itr).tick();
                            cannon_ball.x = (*itr).position.x;
                            cannon_ball.y = (*itr).position.y;
                            cannon_ball.z = (*itr).position.z;
                            if(detect_collision(cannon_ball,plane_box) == true &&plane.powertime < 0)
                            {
                                dashboard.scale_factor_health.y -= .2;
                                plane.score -= 10;
                                (*it).cannonballs.erase(itr);
                                break;
                            }
                            if((*itr).position.y > 6 )
                            {
                                (*it).cannonballs.erase(itr);
                                break;
                            }
                        }  
                    }
        }
    }
     vector<Missile>:: iterator my_itr;
    if(missiles.size()>0)
    {
        for(auto my_itr = missiles.begin();my_itr!=missiles.end();my_itr++)
        {
                (*my_itr).tick();
        }
    }
     vector<Bomb>:: iterator my_itr2;
     if(bombs.size()>0)
    {
        for(auto my_itr2 = bombs.begin();my_itr2!=bombs.end();my_itr2++)
        {
                (*my_itr2).tick();
        }
    }
    pointer.set_position(islands[pointer_position].position.x,islands[pointer_position].position.y+18,islands[pointer_position].position.z);
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane  = Plane(0,0,0,COLOR_RED);
    targetpos = glm::vec3(plane.position.x,plane.position.y,plane.position.z-8);
    water  = Water(0,-15,0,COLOR_BLUE);
    dashboard = Dashboard(-2.5,-3,0);
    compass   = Compass(-3,3,0);
    islands.push_back(Island(0,-14.9,-50,COLOR_GREEN));
    islands.push_back(Island(50,-14.9,-120,COLOR_GREEN));
    islands.push_back(Island(-40,-14.9,-225,COLOR_GREEN));
    islands.push_back(Island(-150,-14.9,-420,COLOR_GREEN));
    islands.push_back(Island(250,-14.9,-600,COLOR_GREEN));
    pointer = Pointer(islands[0].position.x,islands[0].position.y+18,islands[0].position.z);
    vector<Island>:: iterator my;
    for(auto my = islands.begin();my!=islands.end();my++)
    {
       glm::vec3 pos =  glm::vec3((*my).position.x*.8/400.0,-(*my).position.z*.8/800.0,0.0);
        compass.comp_positions.push_back(pos);
    }
    for(int i = 0;i<5;i++)
    {
      compass.cpos[i] = Circle(compass.comp_positions[i].x-3,compass.comp_positions[i].y+3,0,.04,COLOR_RED);
    }
    for (int i = 0;i<30;i++)
    {
        rings.push_back(Ring(rand()%130-70,-rand()%5,-(i+1)*50));
    }
    for (int i = 0;i<8;i++)
    {
        Parachute my = Parachute(rand()%120-45,2,-(i+1)*90) ;
        my.type = rand()%3;
        paras.push_back(my);     
    }
    for (int i = 0;i<30;i++)
    {
        fuels.push_back(Powerups(rand()%70-70,-5,-(i+1)*40));
    }
    for(int j = 100;j > -800;j-=100)
    {
        for(int i = -75;i<=120;i+=40)
        {
            Island isl = Island(i,-14.9,j,COLOR_Lime);
            isl.type = 1;
            rand_islands.push_back(isl);
        }
    }
     for(int j = 100;j > -800;j-=100)
    {
        for(int i = -50;i<=120;i+=40)
        {
            Boat_Enemy isl = Boat_Enemy(i,-14.9,j);
            isl.type = rand()%2;
            boats.push_back(isl);
        }
    }
    for(int j = 100;j > -800;j-=100)
    {
        for(int i = -90;i<=120;i+=75)
        {
            Volcanoe isl = Volcanoe(i,-15,j,COLOR_Sienaa);
            volcanoes.push_back(isl);
        }
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_Cyan.r / 256.0, COLOR_Cyan.g / 256.0, COLOR_Cyan.b / 256.0, 0.0f); // R, G, B, A
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
    

    plane_box.height = .8;
    plane_box.width = 2;
    plane_box.depth = 4.5;

    fuel_box.height = .8;
    fuel_box.width = 1;
    fuel_box.depth = 0;

    cannon_ball.height = .4;
    cannon_ball.width =  .4;
    cannon_ball.depth =  .4;

    island_box.height = 0;
    island_box.width = 15;
    island_box.depth = 15;

    missile_box.height = .3;
    missile_box.width = .3;
    missile_box.depth = 1.5;

    bomb_box.height = .6;
    bomb_box.width = .6;
    bomb_box.depth = .6;

    boat_box.height = 4;
    boat_box.width = 4.5;
    boat_box.depth = 4;

    para_box_goodies.height = 1.5;
    para_box_goodies.width = 1.5;
    para_box_goodies.depth = 2;

    para_box_person.height = 1.2;
    para_box_person.width = .7;
    para_box_person.depth = 0;

    ring_box.height = 5;
    ring_box.height = 5;
    ring_box.depth = 0;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
             system("clear");
            cout << "SCORE" << "::" << plane.score << endl;
            cout << "Speed:: Dark Green" <<endl;
            cout << "Health:: Green" <<endl; 
            cout << "Altitude Warning:: Red" <<endl; 
            cout << "Fuel-Bar:: Yellow" <<endl; 

            string score = " ***Fighter Jet ****  SCORE::  " + to_string(plane.score) + "  Missiles::" +to_string(nummissiles) +"  Bombs::" +to_string(numbombs) +"  Targets::" +to_string(target);
            if(plane.powertime > 0)
            {
                score += "   Power-Time " + to_string(5-int(plane.powertime/60));
            }
            const char *_score = score.c_str();
            glfwSetWindowTitle(window,_score);
            frame_count++;
            if(frame_count%60)
            {
                plane.score += 1;
            }
            if(special >= 0)
            {
                special ++;
                plane.rotationz -= 2;
                if(special > 180)
                {
                    special = -1;
                }
            }
            if(smoke_timer >= 0)
            {
                smoke_timer++;
                if(smoke_timer > 180)
                {
                    smoke_timer = -1;
                    glDisable(GL_BLEND);
                }
            }
            glm::vec3 v(plane.target_dir);
            //cout << v.x << "yo" << v.y << "hey" << v.z << endl;
            targetpos = glm::normalize(v);
            //cout << targetpos.x << "qqqqqqqq" << targetpos.y << "ppppppp" << targetpos.z << endl;
            if(missile_shoot >= 0)
            {
                missile_shoot++;
                if(missile_shoot > 45)
                {
                    missile_shoot = -1;
                }
            }
            if(bomb_shoot >= 0)
            {
                bomb_shoot++;
                if(bomb_shoot >120)
                {
                    bomb_shoot = -1;
                }
            }
            plane.keypress = 0;
            plane_box.x = plane.position.x;
            plane_box.y = plane.position.y;
            plane_box.z = plane.position.z;
            if(dashboard.scale_factor_health.y < .1 || dashboard.scale_factor_fuel.x < .1)
            {
               // cout << "health/fuel" << endl;
                if(dashboard.scale_factor_fuel.x < .1)
                {
                    cout << "The Fuel is finished" << endl;                    
                }
                else
                {
                    cout << "You were Destroyed" << endl;                                        
                }
                
                quit(window);
            }
            if(dashboard.scale_factor_speed.x < 1)
            {
                dashboard.scale_factor_speed.x = plane.speed/3;
            }
            if(plane.position.y < -15)
            {
                cout << "The Plane crashed into the Sea" << endl;
                quit(window);
            }
            if(plane.position.y <= 0 && dashboard.scale_factor_altitude.x < 1)
            {
                dashboard.scale_factor_altitude.x = 1 - (15+plane.position.y)/17.0;
            }
            if(frame_count%300 == 0)
            {
                if(dashboard.scale_factor_fuel.x > .1)
                {
                    dashboard.scale_factor_fuel.x -= .1;
                }
            }
            if(view_button_change >= 0)
            {
                view_button_change++;
                if(view_button_change > 60)
                {
                    view_button_change = -1;
                }
            }
            for(auto itru = islands.begin();itru!=islands.end();itru++)
            {
                if(dist_between_objects((*itru).position.x,(*itru).position.y,(*itru).position.z,plane.position.x,plane.position.y,plane.position.z) < 35)
                {
                    (*itru).start_fire = true;
                }
                else
                {
                    (*itru).start_fire = false;
                }
                island_box.x = (*itru).position.x;
                island_box.y = (*itru).position.y;
                island_box.z = (*itru).position.z;
                  if(missiles.size()>0)
                {
                    for(auto my_itr = missiles.begin();my_itr!=missiles.end();my_itr++)
                    {
                            missile_box.x = (*my_itr).position.x;
                            missile_box.y = (*my_itr).position.y;
                            missile_box.z = (*my_itr).position.z;

                            if(detect_collision(island_box,missile_box)== true)
                            {
                                system("aplay explosion.wav&");                    
                                missiles.erase(my_itr);
                                plane.score+=40;
                                (*itru).lives -=1;
                                break;
                            }
                    }
                }
                 if(bombs.size()>0)
                {
                    for(auto my_itr2 = bombs.begin();my_itr2!=bombs.end();my_itr2++)
                    {
                        bomb_box.x = (*my_itr2).position.x;
                        bomb_box.y = (*my_itr2).position.y;
                        bomb_box.z = (*my_itr2).position.z;   
                        if(detect_collision(island_box,bomb_box)== true)
                            {
                                system("aplay explosion.wav&");                    
                                bombs.erase(my_itr2);
                                plane.score+=100;
                                (*itru).lives -=3;
                                break;
                            }     
                    }
                }
                
            }
            for(auto it = volcanoes.begin();it != volcanoes.end();it++)
            {
                if(abs(plane.position.x-(*it).position.x) < 5 && abs(plane.position.z-(*it).position.z) < 5  && plane.powertime < 0)
                {
                    cout << "The Plane blasted due to proximity of volcanoe" << endl;                                    
                    quit(window);
                }
            }
            if(missiles.size()>0)
                {
                    for(auto my_itr = missiles.begin();my_itr!=missiles.end();my_itr++)
                    {
                            if((*my_itr).position.y < -16)
                            {
                                missiles.erase(my_itr);
                                break;
                            }
                    }
                }
            vector<Bomb>:: iterator my_itr2;
            if(bombs.size()>0)
                {
                    for(auto my_itr2 = bombs.begin();my_itr2!=bombs.end();my_itr2++)
                    {
                        if((*my_itr2).position.y < -16)
                            {
                                bombs.erase(my_itr2);
                                break;
                            }       
                    }
                } 
            vector<Powerups>:: iterator my_itr3;
            if(fuels.size()>0)
            {
                for(auto my_itr3 = fuels.begin();my_itr3!=fuels.end();my_itr3++)
                {
                        fuel_box.x = (*my_itr3).position.x;
                        fuel_box.y = (*my_itr3).position.y;
                        fuel_box.z = (*my_itr3).position.z;
                        if(detect_collision(plane_box,fuel_box)==true)
                        {
                            if(dashboard.scale_factor_fuel.x < 1)
                            {
                                    dashboard.scale_factor_fuel.x += .2;
                            }
                            fuels.erase(my_itr3);
                            break;
                        }
                }
            }
                 for(auto itru = boats.begin();itru!=boats.end();itru++)
            {
                boat_box.x = (*itru).position.x;
                boat_box.y = (*itru).position.y;
                boat_box.z = (*itru).position.z;
                  if(missiles.size()>0)
                {
                    for(auto my_itr = missiles.begin();my_itr!=missiles.end();my_itr++)
                    {
                            missile_box.x = (*my_itr).position.x;
                            missile_box.y = (*my_itr).position.y;
                            missile_box.z = (*my_itr).position.z;

                            if(detect_collision(boat_box,missile_box)== true)
                            {
                                system("aplay explosion.wav&");                    
                                missiles.erase(my_itr);
                                if((*itru).type == 0)
                                {
                                    plane.score+=10;
                                }
                                else
                                {   
                                    plane.score+=50;
                                }
                                boats.erase(itru);
                                break;
                            }
                    }
                }
                 if(bombs.size()>0)
                {
                    for(auto my_itr2 = bombs.begin();my_itr2!=bombs.end();my_itr2++)
                    {
                        bomb_box.x = (*my_itr2).position.x;
                        bomb_box.y = (*my_itr2).position.y;
                        bomb_box.z = (*my_itr2).position.z;   
                        if(detect_collision(boat_box,bomb_box)== true)
                            {
                                bombs.erase(my_itr2);
                                system("aplay explosion.wav&");                    
                                boats.erase(itru);
                                break;
                            }     
                    }
                }
                
            }
                 for(auto itru = paras.begin();itru!=paras.end();itru++)
            {
                if((*itru).type == 0)
                {
                    para_box_person.x = (*itru).position.x;
                    para_box_person.y = (*itru).position.y;
                    para_box_person.z = (*itru).position.z;
                      if(missiles.size()>0)
                {
                    for(auto my_itr = missiles.begin();my_itr!=missiles.end();my_itr++)
                    {
                            missile_box.x = (*my_itr).position.x;
                            missile_box.y = (*my_itr).position.y;
                            missile_box.z = (*my_itr).position.z;

                            if(detect_collision(para_box_person,missile_box)== true)
                            {
                                system("aplay explosion.wav&");                    
                                missiles.erase(my_itr);
                                paras.erase(itru);
                                break;
                            }
                    }
                }
                }
                else
                {
                    para_box_goodies.x = (*itru).position.x;
                    para_box_goodies.y = (*itru).position.y;
                    para_box_goodies.z = (*itru).position.z;
                    if(detect_collision(para_box_goodies,plane_box) == true)
                    {
                        if((*itru).type == 1)
                        {
                            if(dashboard.scale_factor_health.y < 1)
                            {
                                dashboard.scale_factor_health.y = 1;
                                
                            }
                            paras.erase(itru);
                            break;
                        }
                        else
                        {
                            plane.powertime = 0;
                            paras.erase(itru);
                            break;
                        }
                    }
                }
                

            }
            for(auto itru = rings.begin();itru!=rings.end();itru++)
            {
                ring_box.x = (*itru).position.x;
                ring_box.y = (*itru).position.y;
                ring_box.z = (*itru).position.z;
                if(detect_collision(plane_box,ring_box)==true)
                {
                    glEnable(GL_BLEND);
                   glBlendFunc( GL_ZERO, GL_SRC_COLOR );
                   smoke_timer = 0;
                    plane.score+=25;
                    rings.erase(itru);
                    break;
                }
            }

            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_input(window);
            tick_elements();

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}
float dist_between_objects(float xa,float ya,float za,float xb,float yb,float zb)
{
    return sqrt( pow((xa -xb),2) + pow((ya -yb),2) + pow((za -zb),2));
}
bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
                (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
                    (abs(a.z - b.z) * 2 < (a.depth + b.depth));
}
void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(45.0f,4.0f/3.0f,0.1f,120.0f);
    Matrices.projection2 = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

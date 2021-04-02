#include "scoreboard.h"
#include "bits/stdc++.h"
using namespace std;
#include "main.h"

Scoreboard::Scoreboard(float x, float y, color_t color, string textureFile) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->direction = 0;
    this->score = 0;
    this->lives = 0;
    this-> status = -1;
    this -> tasks_completed = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat uv_buffer_data[] = {
        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f
    };
    static GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, -0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, -0.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };
    
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, uv_buffer_data, COLOR_OLIVE, GL_FILL, textureFile);
}

void Scoreboard::draw(glm::mat4 VP) {
    
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (glm::vec3(this->screen_x - this->offset, this->screen_y - this->offset + 1, 0));    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

    // Draw number of tasks completed
    for(int i = 1; i <= this->tasks_completed; ++i){
        static GLfloat vertex_buffer_data[] = {
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f
        };
        static GLfloat uv_buffer_data[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f, 
            0.0f, 1.0f, 
            0.0f, 0.0f, 
            1.0f, 0.0f
        };
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (glm::vec3(this->screen_x - this->offset + i - 1 + 6, this->screen_y + this->offset, 0));    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
        // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
        // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        VAO* obj = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, uv_buffer_data, COLOR_GREEN, GL_FILL, "assets/tick.bmp");
        draw3DObject(obj);
    }
    // Draw central light : off
   if(this->light ==0)
   {
        static GLfloat vertex_buffer_data[] = {
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f
        };
        static GLfloat uv_buffer_data[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f, 
            0.0f, 1.0f, 
            0.0f, 0.0f, 
            1.0f, 0.0f
        };
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (glm::vec3(this->screen_x - this->offset + 8, this->screen_y + this->offset, 0));    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
        // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
        // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        VAO* obj = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, uv_buffer_data, COLOR_GREEN, GL_FILL, "assets/light_off.bmp");
        draw3DObject(obj);
    }



    // Draw Score
    
    if(this->score != 0)
    {
        
        int abs_score = abs(this->score);
        int count = 0;
        while(abs_score > 0){
            static GLfloat uv_buffer_data[] = {
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f, 
                0.0f, 1.0f, 
                0.0f, 0.0f, 
                1.0f, 0.0f
            };
            int digit = abs_score % 10;
            count = count + 1;
            
            
            static GLfloat vertex_buffer_data[] = {
                0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f
            };

            abs_score = abs_score/10;
            Matrices.model = glm::mat4(1.0f);
            glm::mat4 translate = glm::translate (glm::vec3(this->screen_x + this->offset - count, this->screen_y + this->offset, 0));    // glTranslatef
            glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
            // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
            // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
            Matrices.model *= (translate * rotate);
            glm::mat4 MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            string file;
            if(this->status == -1)
            {
                switch(digit)
                {
                    case 0:
                        file = "assets/0.bmp";
                        break;
                    case 1:
                        file = "assets/1.bmp";
                        break;
                    case 2:
                        file = "assets/2.bmp";
                        break;
                    case 3:
                        file = "assets/3.bmp";
                        break;
                    case 4:
                        file = "assets/4.bmp";
                        break;
                    case 5:
                        file = "assets/5.bmp";
                        break;
                    case 6:
                        file = "assets/6.bmp";
                        break;
                    case 7:
                        file = "assets/7.bmp";
                        break;
                    case 8:
                        file = "assets/8.bmp";
                        break;
                    case 9:
                        file = "assets/9.bmp";
                        break;

                }

            }
            
            if(this -> status == 0) file = "assets/loose.bmp";
            if(this -> status == 1) file = "assets/win.bmp";
            
            VAO* obj = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, uv_buffer_data, COLOR_GREEN, GL_FILL, file);
            draw3DObject(obj);
        }
        if(this->score < 0 && this->status==-1){
            count++;
            static GLfloat vertex_buffer_data[] = {
                0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f
            };
            static GLfloat uv_buffer_data[] = {
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f, 
                0.0f, 1.0f, 
                0.0f, 0.0f, 
                1.0f, 0.0f
            };
            Matrices.model = glm::mat4(1.0f);
            glm::mat4 translate = glm::translate (glm::vec3(this->screen_x + this->offset - count, this->screen_y + this->offset, 0));    // glTranslatef
            glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
            // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
            // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
            Matrices.model *= (translate * rotate);
            glm::mat4 MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            string file = "assets/is_negative.bmp";
            VAO* obj = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, uv_buffer_data, COLOR_GREEN, GL_FILL, file);
            draw3DObject(obj);
        }
       
    }
    else if(this->status!=-1){
         static GLfloat uv_buffer_data[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f, 
            0.0f, 1.0f, 
            0.0f, 0.0f, 
            1.0f, 0.0f
        };
        static GLfloat vertex_buffer_data[] = {
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f
        };
        
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (glm::vec3(this->screen_x + this->offset - 1, this->screen_y + this->offset, 0));    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
        // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
        // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        VAO* obj = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, uv_buffer_data, COLOR_GREEN, GL_FILL, "assets/0.bmp");
        draw3DObject(obj);

    }


    for(int i = 1; i <= this->lives; ++i){
        static GLfloat vertex_buffer_data[] = {
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f
        };
        static GLfloat uv_buffer_data[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f, 
            0.0f, 1.0f, 
            0.0f, 0.0f, 
            1.0f, 0.0f
        };
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (glm::vec3(this->screen_x - this->offset + i - 1, this->screen_y + this->offset, 0));    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
        // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
        // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        VAO* obj = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, uv_buffer_data, COLOR_GREEN, GL_FILL, "assets/lives.bmp");
        draw3DObject(obj);
    }
    
}

void Scoreboard::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Scoreboard::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}


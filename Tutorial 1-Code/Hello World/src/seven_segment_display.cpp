#include "main.h"
#include "seven_segment_display.h"
#include <iostream>
#include <stdio.h>

Seven_Segment_Display :: Seven_Segment_Display (float x, float y, float number) {
	this->position = glm::vec3 (x, y, 0);
    this->rotation = 0;
    this->number = number;

    static const GLfloat one [] = {
        -0.08f, -0.02f, 0.0f,
        -0.08f,  0.02f, 0.0f,
         0.08f,  0.02f, 0.0f,
         0.08f,  0.02f, 0.0f,
        -0.08f, -0.02f, 0.0f,
         0.08,  -0.02f, 0.0f,
    };
    static const GLfloat two [] = {
        -0.08f, -0.02f+0.20f, 0.0f,
        -0.08f,  0.02f+0.20f, 0.0f,
         0.08f,  0.02f+0.20f, 0.0f,
         0.08f,  0.02f+0.20f, 0.0f,
        -0.08f, -0.02f+0.20f, 0.0f,
         0.08,  -0.02f+0.20f, 0.0f,
    };
    static const GLfloat three [] = {
        -0.08f, -0.02f-0.20f, 0.0f,
        -0.08f,  0.02f-0.20f, 0.0f,
         0.08f,  0.02f-0.20f, 0.0f,
         0.08f,  0.02f-0.20f, 0.0f,
        -0.08f, -0.02f-0.20f, 0.0f,
         0.08,  -0.02f-0.20f, 0.0f,
    };
    static const GLfloat four [] = {
        -0.02f-0.11f, -0.08f+0.10f, 0.0f,
         0.02f-0.11f, -0.08f+0.10f, 0.0f,
         0.02f-0.11f,  0.08f+0.10f, 0.0f,
         0.02f-0.11f,  0.08f+0.10f, 0.0f,
        -0.02f-0.11f, -0.08f+0.10f, 0.0f,
        -0.02f-0.11f,  0.08f+0.10f,  0.0f,
    };
    static const GLfloat five [] = {
        -0.02f+0.11f, -0.08f+0.10f, 0.0f,
         0.02f+0.11f, -0.08f+0.10f, 0.0f,
         0.02f+0.11f,  0.08f+0.10f, 0.0f,
         0.02f+0.11f,  0.08f+0.10f, 0.0f,
        -0.02f+0.11f, -0.08f+0.10f, 0.0f,
        -0.02f+0.11f,  0.08f+0.10f,  0.0f,
    };
    static const GLfloat six [] = {
        -0.02f-0.11f, -0.08f-0.10f, 0.0f,
         0.02f-0.11f, -0.08f-0.10f, 0.0f,
         0.02f-0.11f,  0.08f-0.10f, 0.0f,
         0.02f-0.11f,  0.08f-0.10f, 0.0f,
        -0.02f-0.11f, -0.08f-0.10f, 0.0f,
        -0.02f-0.11f,  0.08f-0.10f,  0.0f,
    };
    static const GLfloat seven [] = {
        -0.02f+0.11f, -0.08f-0.10f, 0.0f,
         0.02f+0.11f, -0.08f-0.10f, 0.0f,
         0.02f+0.11f,  0.08f-0.10f, 0.0f,
         0.02f+0.11f,  0.08f-0.10f, 0.0f,
        -0.02f+0.11f, -0.08f-0.10f, 0.0f,
        -0.02f+0.11f,  0.08f-0.10f,  0.0f,
    };

    this->one = create3DObject(GL_TRIANGLES, 6, one, COLOR_BLACK, GL_FILL);
    this->two = create3DObject(GL_TRIANGLES, 6, two, COLOR_BLACK, GL_FILL);
    this->three = create3DObject(GL_TRIANGLES, 6, three, COLOR_BLACK, GL_FILL);
    this->four = create3DObject(GL_TRIANGLES, 6, four, COLOR_BLACK, GL_FILL);
    this->five = create3DObject(GL_TRIANGLES, 6, five, COLOR_BLACK, GL_FILL);
    this->six = create3DObject(GL_TRIANGLES, 6, six, COLOR_BLACK, GL_FILL);
    this->seven = create3DObject(GL_TRIANGLES, 6, seven, COLOR_BLACK, GL_FILL);
}

void Seven_Segment_Display :: draw (glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->number==2||this->number==3||this->number==4||this->number==5||this->number==6||this->number==8||this->number==9)
        draw3DObject(this->one);
    if(this->number==0||this->number==2||this->number==3||this->number==5||this->number==6||this->number==7||this->number==8||this->number==9)
        draw3DObject(this->two);
    if(this->number==0||this->number==2||this->number==3||this->number==5||this->number==6||this->number==8||this->number==9)
        draw3DObject(this->three);
    if(this->number==0||this->number==4||this->number==5||this->number==6||this->number==8||this->number==9)
        draw3DObject(this->four);
    if(this->number==0||this->number==1||this->number==2||this->number==3||this->number==4||this->number==7||this->number==8||this->number==9)
        draw3DObject(this->five);
    if(this->number==0||this->number==2||this->number==6||this->number==8)
        draw3DObject(this->six);
    if(this->number==0||this->number==1||this->number==3||this->number==4||this->number==5||this->number==6||this->number==7||this->number==8||this->number==9)
        draw3DObject(this->seven);
}

void Seven_Segment_Display :: set_number (float number) {
    this->number = number;
}

void Seven_Segment_Display :: update () {
    this->position.x += 0.1;
}

void Seven_Segment_Display::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
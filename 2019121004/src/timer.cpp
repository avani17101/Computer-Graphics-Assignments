#include "timer.h"
#include <GLFW/glfw3.h>

Timer::Timer(double time) {
    past = 0;
    curr = 0;
    this->time = time;
}

bool Timer::processTick() {
    double cur = glfwGetTime();
    if (cur - past >= time) {
        past = cur;
        
        if(past == curr){
            curr = cur;
        }
        return true;
    } else
        return false;
}

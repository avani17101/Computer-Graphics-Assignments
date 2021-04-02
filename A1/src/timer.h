#ifndef TIMER_H
#define TIMER_H


class Timer {
public:
    Timer() {
        past = 0;
        curr = 0;
    }
    Timer(double time);
    bool processTick();
    double time;
    
private:
    double past;
    double curr;
};

#endif // TIMER_H

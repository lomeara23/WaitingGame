#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include "Customer.h"

using namespace std;

class Window{
    private:
        Customer *student;
        bool idle;

        int idleTime;
        
    public:
        Window(); //Default constructor
        ~Window(); //Destructor

        int timeRemaining;

        void assign(Customer *newStudent);
        void clear();

        void setIdle(bool);

        bool isIdle();
        Customer* getStudent();

        void incrementIdleTime();
        void resetIdleTime();
        int getIdleTime();

};
#endif
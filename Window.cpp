#include "Window.h"

// Default ctor
Window::Window(){
    student = NULL;
    idle = true;
    timeRemaining = -1;
}

Window::~Window(){
    delete student;
}

// Assign student to window
void Window::assign(Customer *newStudent){
    student = newStudent;
    idle = false;
    timeRemaining = student->getNextTime();
}

// remove student from window
void Window::clear(){
    student = NULL;
    
}

// Set idle state
void Window::setIdle(bool status){
    idle = status;
}

// Check idle state
bool Window::isIdle(){
    return idle;
}

// Get student at window
Customer* Window::getStudent(){
    return student;
}

// Increment window's idle time by 1
void Window::incrementIdleTime(){
    idleTime++;
}

// Reset window's idle time to 0(when new student arrives)
void Window::resetIdleTime(){
    idleTime = 0;
}

// Return idle time
int Window::getIdleTime(){
    return idleTime;
}
#include "CustomerQueue.h"

CustomerQueue::~CustomerQueue(){
    delete myQueue;
}

// Increment all students in queue's wait timers by 1
void CustomerQueue::incrementWaitTimers(){
    for(int i = 0 ; i < myQueue->getSize() ; i++){
        myQueue->get(i)->data->incrementTimeWaiting();
    }
}

// Reset a students wait timer when the are removed from a queue
Customer* CustomerQueue::remove(){
    myQueue->front->data->resetTimeWaiting();
    return myQueue->removeFront();
}
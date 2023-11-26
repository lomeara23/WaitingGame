#include "Office.h"

// Default constructor, initialize all necessary variables and 3 Windows
Office::Office(){
    windowCount = 3;
    windows = new Window*[windowCount];
    for(int i = 0 ; i < windowCount ; i++){
        windows[i] = new Window();
    }

    queue = new CustomerQueue();
    done = new CustomerQueue();

    idleWindows = windowCount;

    // stats
    meanWaitTime = 0;
    maxWaitTime = 0;
    tenPlusWaitTimes = 0;
    meanWindowIdleTime = 0;
    maxWindowIdleTime = 0;
    fivePlusIdleTime = 0;


    // auxiliary stats
    totalStudents = 0;
    totalWaitTime = 0;
    totalWindowIdleTime = 0;
    totalTimesIdle = 0;
}

// Overload constructor, initialize all necessary variables and the input amount of windows
Office::Office(int windowNum){
    windowCount = windowNum;
    windows = new Window*[windowCount];
    for(int i = 0 ; i < windowCount ; i++){
        windows[i] = new Window();
    }

    queue = new CustomerQueue();
    done = new CustomerQueue();   

    idleWindows = windowCount; 

    // stats
    meanWaitTime = 0;
    maxWaitTime = 0;
    tenPlusWaitTimes = 0;
    meanWindowIdleTime = 0;
    maxWindowIdleTime = 0;
    fivePlusIdleTime = 0;


    // auxiliary stats
    totalStudents = 0;
    totalWaitTime = 0;
    totalWindowIdleTime = 0;
    totalTimesIdle = 0;
}

Office::~Office(){
    delete[] windows;
    delete queue;
    delete done;
}

// Check if any more students need to be sent to windows(Are in queue)
bool Office::isQueueEmpty(){
    return queue->isEmpty();
}

// Add student to queue
void Office::enqueue(Customer *student){
    queue->insert(student);
}

// Process students in queue
void Office::process(){
    Window *curr;
    for(int i = 0 ; i < windowCount ; i++){
        curr = windows[i];
        if(curr->isIdle()){
            if(curr->getIdleTime() == 1){
                totalTimesIdle++;
            }
            if(queue->isEmpty()){
                totalWindowIdleTime++;
                curr->incrementIdleTime();
            } else {
                if(queue->peek()->getTimeWaiting() > 10){
                    tenPlusWaitTimes++;
                }
                if(queue->peek()->getTimeWaiting() > maxWaitTime){
                    maxWaitTime = queue->peek()->getTimeWaiting();
                }
                if(curr->getIdleTime() > 5){
                    fivePlusIdleTime++;
                }
                if(curr->getIdleTime() > maxWindowIdleTime){
                    maxWindowIdleTime = curr->getIdleTime();
                }
                totalStudents++;
                totalWaitTime += queue->peek()->getTimeWaiting();
                curr->assign(queue->remove());
                curr->resetIdleTime();
                curr->setIdle(false);
            }
        }
        if(!curr->isIdle()){
            curr->timeRemaining--;
            if(curr->timeRemaining <= 0){
                if(curr->getStudent()->getRemainingDest() != 0)
                    done->insert(curr->getStudent());
                else
                    curr->getStudent();
                curr->setIdle(true);
                curr->clear();
            }
        }
    }
    if(isOfficeIdle()){
        allWindowsIdle = true;
    } else {
        allWindowsIdle = false;
    }
    queue->incrementWaitTimers();
}

// Check if any students need to leave the office
bool Office::isDoneEmpty(){
    return done->isEmpty();
}

// Return next student to leave
Customer* Office::getNextDone(){
    return done->remove();
}

// Print necessary statistics
void Office::getStats(){
    calcStats();
    cout << "Mean wait time: " << meanWaitTime << endl;
    cout << "Longest wait time: " << maxWaitTime << endl;
    cout << "Mean idle time: " << meanWindowIdleTime << endl;
    cout << "Longest idle time: " << maxWindowIdleTime << endl << endl;
}

// Calculate statistics that need math before printing
void Office::calcStats(){
    if(totalWindowIdleTime != 0)
        meanWindowIdleTime = (double)totalWindowIdleTime/totalTimesIdle;
    if(totalWaitTime != 0)
        meanWaitTime = (double)totalWaitTime/totalStudents;
}

// Return number of times window was idle for more than 5 mins
int Office::getFiveMinIdleCount(){
    return fivePlusIdleTime;
}

// Return number of times student was waiting for more than 10 minutes
int Office::getTenMinWaitCount(){
    return tenPlusWaitTimes;
}

// Check if all windows are idle
bool Office::isOfficeIdle(){
    for(int i = 0 ; i < windowCount ; i++){
        if(windows[i]->isIdle() == false)
            return false;
    }
    return true;
}

// Get final cycle of idle times
void Office::getFinalIdles(){
    for(int i = 0 ; i < windowCount ; i++){
        if(windows[i]->getIdleTime() > 5){
            fivePlusIdleTime++;
        }
        if(windows[i]->getIdleTime() > maxWindowIdleTime){
            maxWindowIdleTime = windows[i]->getIdleTime();
        }
    }
}

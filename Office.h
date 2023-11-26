#ifndef OFFICE_H
#define OFFICE_H

#include <iostream>
#include "Window.h"
#include "CustomerQueue.h"

using namespace std;

class Office{
    private:
        Window **windows;
        CustomerQueue *queue;
        CustomerQueue *done;

        int windowCount;

        int idleWindows;

        // stats
        int meanWaitTime;
        int maxWaitTime;
        int tenPlusWaitTimes;
        double meanWindowIdleTime;
        double maxWindowIdleTime;
        int fivePlusIdleTime;


        // auxiliary stats
        int totalStudents;
        int totalWaitTime;
        int totalWindowIdleTime;
        int totalTimesIdle;

        
    public:
        Office(); //Default constructor
        Office(int Windows); //Overloaded constructor
        ~Office(); //Destructor

        bool isQueueEmpty();
        bool isDoneEmpty();
        bool isOfficeIdle();

        void getFinalIdles();

        bool allWindowsIdle;
        void enqueue(Customer *student);
        void process();

        Customer* getNextDone();
        int getFiveMinIdleCount();
        int getTenMinWaitCount();

        void getStats();
        void calcStats();

};
#endif
#ifndef SERVICECENTER_H
#define SERVICECENTER_H

#include <iostream>
#include <fstream>
#include "Office.h"
#include "CustomerQueue.h"

using namespace std;


class ServiceCenter{
    private:
        ifstream in;

        Office *registrar;
        Office *cashier;
        Office *finAid;

        CustomerQueue *studentsWaiting;

        int currTime;
        int nextReadTime;

        bool moreStudents;
        bool finished;

        int totalFiveMinIdles;
        int totalTenMinuteWaits;

        bool checkFinished();
        void assignStudentsWaiting();

        int totalStudents;
        
    public:
        ServiceCenter(); //Default constructor
        ServiceCenter(string filePath); //Overloaded constructor
        ~ServiceCenter(); //Destructor

        void processStudents();

        void getStats();
        void calcStats();
};
#endif
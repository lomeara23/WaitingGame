#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include "ListQueue.h"

using namespace std;

class Customer{
    private:
        ListQueue<char> *destinations;
        ListQueue<int> *times;
        unsigned int timeWaiting;
        bool inQueue;

        
    public:
        Customer(); //Default constructor
        Customer(string input); //Overloaded constructor
        ~Customer(); //Destructor

        char getNextDest();
        int getNextTime();
        int peekNextTime();

        int getRemainingDest();

        void setQueue(bool);

        void incrementTimeWaiting();
        int getTimeWaiting();
        void resetTimeWaiting();

        void printCustomer();

        int studentCount;



};
#endif
#ifndef CUSTOMERQUEUE_H
#define CUSTOMERQUEUE_H

#include <iostream>
#include "ListQueue.h"
#include "Customer.h"

using namespace std;

class CustomerQueue : public ListQueue<Customer*>{
    public:
        CustomerQueue() : ListQueue<Customer*>(){};
        ~CustomerQueue();

        void incrementWaitTimers();
        Customer* remove();
};
#endif
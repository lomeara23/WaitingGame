#include "ServiceCenter.h"

// Default constructor
ServiceCenter::ServiceCenter(){
    in.open(NULL);

    registrar = new Office(3);
    cashier = new Office(3);
    finAid = new Office(3);

    studentsWaiting = new CustomerQueue();

    currTime = 0;
    finished = false;
    moreStudents = true;

    totalFiveMinIdles = 0;
    totalTenMinuteWaits = 0;

    totalStudents = 0;
}

// Overload constructor takes in filepath to process
ServiceCenter::ServiceCenter(string filePath){
    in.open(filePath);

    string tempStr[4];
    for(int i = 0 ; i < 4 ; i++){
        getline(in,tempStr[i]);
    }
    registrar = new Office(stoi(tempStr[0]));
    cashier = new Office(stoi(tempStr[1]));
    finAid = new Office(stoi(tempStr[2]));

    studentsWaiting = new CustomerQueue();

    currTime = 0;
    nextReadTime = stoi(tempStr[3]);
    finished = false;
    moreStudents = true;

    totalFiveMinIdles = 0;
    totalTenMinuteWaits = 0;

    totalStudents = 0;
}

// process students through all offices
void ServiceCenter::processStudents(){
    while(!finished && currTime < 40){
        currTime++;
        cout << "Current Time: " << currTime << endl;
        while(!cashier->isDoneEmpty()){
            studentsWaiting->insert(cashier->getNextDone());
        }
        while(!finAid->isDoneEmpty()){
            studentsWaiting->insert(finAid->getNextDone());
        }
        while(!registrar->isDoneEmpty()){
            studentsWaiting->insert(registrar->getNextDone());
        }

        if(currTime == nextReadTime){
            string line;
            getline(in, line);
            int studentsToQueue = stoi(line);
            for(int i = 0 ; i < studentsToQueue ; i++){
                getline(in,line);
                Customer* temp = new Customer(line);
                temp->studentCount = ++totalStudents;
                studentsWaiting->insert(temp);
            }

            getline(in, line);
            if(!in.eof()){
                nextReadTime = stoi(line);
            }
            else
                moreStudents = false;
        }
        // Process offices
        assignStudentsWaiting();

        cout << "Registrar" << endl;
        registrar->process();

        cout << "Cashier" << endl;
        cashier->process();

        cout << "FinAid" << endl;
        finAid->process();
        cout << endl;
        if(checkFinished()){
            return;
        }
        finished = checkFinished();
    }
    registrar->getFinalIdles();
    cashier->getFinalIdles();
    finAid->getFinalIdles();

}

// Send students in queue to their mecessary destinations
void ServiceCenter::assignStudentsWaiting(){
    while(!studentsWaiting->isEmpty()){
        if(studentsWaiting->peek()->getRemainingDest() == 0){
            cout << "Student " << studentsWaiting->peek()->studentCount << " has left" << endl;
        } else { 
            switch(studentsWaiting->peek()->getNextDest()) {
                case 'R':
                    registrar->enqueue(studentsWaiting->peek());
                    break;
                case 'C':
                    cashier->enqueue(studentsWaiting->peek());
                    break;
                case 'F':
                    finAid->enqueue(studentsWaiting->peek());
                    break;
            }
        }
        studentsWaiting->remove();
    }
}

// Check if theres no more students to queue, and all queues in offices are empty
bool ServiceCenter::checkFinished(){
    if(registrar->isQueueEmpty() && registrar->isDoneEmpty() && registrar->allWindowsIdle && cashier->isQueueEmpty() && cashier->isDoneEmpty() && cashier->allWindowsIdle &&  finAid->isQueueEmpty() && finAid->isDoneEmpty() && finAid->allWindowsIdle && !moreStudents){
        return true;
    }
    else   
        return false;
    
}

// Print necessary statistics
void ServiceCenter::getStats(){
    calcStats();

    cout << "Registrar's office:" << endl;
    registrar->getStats();
    cout << "Cashier's office:" << endl;
    cashier->getStats();
    cout << "Financial Aid office:" << endl;
    finAid->getStats();
    cout << "Totals:" << endl;
    cout << "Total idles greater than five minutes: " << totalFiveMinIdles << endl;
    cout << "Total waits greater than ten minutes: " << totalTenMinuteWaits << endl;

}

// Calculate stats that need math prior to printing
void ServiceCenter::calcStats(){
    totalFiveMinIdles += registrar->getFiveMinIdleCount();
    totalFiveMinIdles += cashier->getFiveMinIdleCount();
    totalFiveMinIdles += finAid->getFiveMinIdleCount();

    totalTenMinuteWaits += registrar->getTenMinWaitCount();
    totalTenMinuteWaits += cashier->getTenMinWaitCount();
    totalTenMinuteWaits += finAid->getTenMinWaitCount();
}
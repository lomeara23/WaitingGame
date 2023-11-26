#include "Customer.h"

// Default constructor
Customer::Customer(){
    destinations = new ListQueue<char>();
    times = new ListQueue<int>();

    // Goes to the offices in default order
    destinations->insert('R');
    destinations->insert('C');
    destinations->insert('F');

    // Stays at each office for 1 tick
    times->insert(1);
    times->insert(1);
    times->insert(1);

}

Customer::Customer(string input){
    destinations = new ListQueue<char>();
    times = new ListQueue<int>();

    // Break down the string, taking each time and adding it to time queue
    for(int i = 0 ; i < 3 ; i++){
        int time = std::stoi(input.substr(0,input.find(" ")));
        input = input.substr(input.find(" ")+1);
        times->insert(time);
    }

    // Break down second half of string, taking each char and using it to identify where to go
    for(int i = 0 ; i < 3 ; i++){
        char dest = input.substr(0,input.find(" "))[0];
        input = input.substr(input.find(" ")+1);
        destinations->insert(dest);
    }
    
}
            
Customer::~Customer(){
    delete destinations;
    delete times;
}

// Returns char correlating with next destination
char Customer::getNextDest(){
    return destinations->remove();
}

// Returns time to spend at next destination
int Customer::getNextTime(){
    return times->remove();
}

// Returns time to spend at next destination without removing from queue
int Customer::peekNextTime(){
    return times->peek();
}

// Set whether or not you are in a queue
void Customer::setQueue(bool queueStatus){
    inQueue = queueStatus;
}

// Increment amount of time in queue by 1
void Customer::incrementTimeWaiting(){
    timeWaiting++;
}

// Return time waiting in queue
int Customer::getTimeWaiting(){
    return timeWaiting;
}

// Reset time in queue to 0(for after leaving queue)
void Customer::resetTimeWaiting(){
    timeWaiting = 0;
}

// Print the customer(Debugging)
void Customer::printCustomer(){
    cout << "Destinations: " << endl;
    destinations->printList();
    cout << endl;
    cout << "Wait times: " << endl;
    times->printList();
}

// Return how many destinations remaining
int Customer::getRemainingDest(){
    return destinations->size();
}
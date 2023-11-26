#ifndef LISTQUEUE_H
#define LISTQUEUE_H

#include <iostream>
#include <typeinfo>

#include "DblList.h"

using namespace std;

// Generic queue implemented with doubly-linked list
template<class T>
class ListQueue{
    protected:
        DoubleList<T> *myQueue;
        
    public:
        ListQueue(); //Default constructor
        ~ListQueue(); //Destructor

        //Core functions
        void insert(T data);
        T remove();

        //Auxiliary functions
        T peek();
        bool isEmpty();
        unsigned int size();
        void printList();
};

template<class T>
ListQueue<T>::ListQueue(){
    myQueue = new DoubleList<T>();
}

template<class T>
ListQueue<T>::~ListQueue(){
    delete myQueue;
}

template<class T>
void ListQueue<T>::insert(T data){
    myQueue->insertBack(data);
}

template<class T>
T ListQueue<T>::remove(){
    return myQueue->removeFront();
}

template<class T>
T ListQueue<T>::peek(){
    return myQueue->get(0)->data;
}

template<class T>
bool ListQueue<T>::isEmpty(){
    return myQueue->isEmpty();
}

template<class T>
unsigned int ListQueue<T>::size(){
    return myQueue->getSize();
}

template<class T>
void ListQueue<T>::printList(){
    ListNode<T> *node = myQueue->get(0);
    int i = 0;
    while(node != NULL){
        cout << "index: " << i << endl;
        cout << myQueue->get(i)->data << endl;
        node = node->next;
        i++;
    }
}
#endif
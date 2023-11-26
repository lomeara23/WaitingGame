#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>

#include <typeinfo>

using namespace std;


// Generic Double List
template<class T>
class ListNode{
    public:
        ListNode();
        ListNode(T d);
        ~ListNode();
        ListNode *next;
        ListNode *prev;
        T data;
};

template<class T>
ListNode<T>::ListNode(){
}

template<class T>
ListNode<T>::ListNode(T d){
    data = d;
    next = NULL;
    prev = NULL;
}

template<class T>
ListNode<T>::~ListNode(){}

template<class T>
class DoubleList{
    private:
        ListNode<T> *back;
        unsigned int size;
    public:
        ListNode<T> *front;
        DoubleList(); //Default constructor
        ~DoubleList(); //Destructor

        void insertFront(T d);
        void insertBack(T d);
        T removeFront();
        T removeBack();
        T removeNode(T *val);
        int find(T *val);
        bool isEmpty();
        unsigned int getSize();
        ListNode<T>* get(int index);
};

template<class T>
DoubleList<T>::DoubleList(){
    front = NULL;
    back = NULL;
    size = 0;
}

template<class T>
DoubleList<T>::~DoubleList(){
    while(!isEmpty()){
        removeFront();
    }
}

template<class T>
void DoubleList<T>::insertFront(T d){
    ListNode<T> *node = new ListNode<T>(d);
    if(isEmpty()){
        back = node;
    }
    else{
        node->next = front;
        front->prev = node;
    }
    front = node;
    size++;
}

template<class T>
void DoubleList<T>::insertBack(T d){
    ListNode<T> *node = new ListNode<T>(d);
     if(isEmpty()){
        front = node;
    }
    else{
        node->prev = back;
        back->next = node;
    }
    back = node;
    size++;
}

template<class T>
T DoubleList<T>::removeFront(){
    ListNode<T> *temp = front;

    if(front->next == NULL){
        back = NULL;
    }
    else{
        front->next->prev = NULL;
    }
    front = front->next;
    temp->next = NULL;
    T data = temp->data;
    size--;
    delete temp;

    return data;
}

template<class T>
T DoubleList<T>::removeBack(){
    ListNode<T> *temp = back;

    if(back->prev == NULL){
        front = NULL;
    }
    else{
        back->prev->next = NULL;
    }
    back = back->prev;
    temp->prev = NULL;
    T data = temp->data;
    size--;
    delete temp;

    return data;
}

template<class T>
T DoubleList<T>::removeNode(T *value){
    if(isEmpty()){
        throw runtime_error("List is empty");
    }

    ListNode<T> *curr = front;
    while(curr->data != value){
        curr = curr->next;
        if(curr == NULL){
            return -1;
        }
    }

    if(curr != front){
        curr->prev->next = curr->next;
        curr->prev = NULL;
    }
    else{
        curr->next = front;
    }
    if(curr != back){
        curr->next->prev = curr->prev;
        curr->next = NULL;
    }
    else {
        curr->prev = back;
    }
    int data = curr->data;
    --size;
    delete curr;

    return data;
}

template<class T>
int DoubleList<T>::find(T *value){
    int pos = -1;
    ListNode<T> *curr = front;
    while(curr->data != NULL){
        pos++;
        if(curr->data == value){
            break;
        }
        curr = curr->next;
    }

    if(curr == NULL){
        pos = -1;
    }
    return pos;
}

template<class T>
bool DoubleList<T>::isEmpty(){
    return (front == NULL && back == NULL);
}

template<class T>
unsigned int DoubleList<T>::getSize(){
    return size;
}

template<class T>
ListNode<T>* DoubleList<T>::get(int index){
    ListNode<T> *node = front;
    for(int i = 0 ; i < index ; i++){
        node = node->next;
    }
    return node;
}

#endif
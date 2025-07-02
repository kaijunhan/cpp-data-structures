// Lock-Free Implementation: using atomic::compare and exchange
#pragma once 

#include <atomic>
#include <thread>
using namespace std;

template <typename T> class Stack{
private:
    struct Node{
        T data; // use data 
        Node* next = nullptr;  
    };

    atomic<Node*> head;

public:
    Stack() {
        head.store(nullptr);
    }

    ~Stack() {
        // Clean up remaining nodes
        while (pop()) {}
    }

    bool push(T arg){
        Node* new_head = new Node; // create a new node
        new_head->data = arg;  
        new_head->next = head.load();
        while (!head.compare_exchange_weak(new_head->next, new_head)){
        } 
        // CAS (Compare and swap) - compare_exchange_weak(expected, desired) checks the value of head and if it is not equal to new_head->next then it will store the value of head that it found into new_head->next instead
        // but if it is true then it will store the
        return true;
    }

    T top(){
        return head->next->data;
    }

    bool pop() {
        Node* curr_head = head.load();
        do{
            if(curr_head == nullptr) return false;
        }
        while(!head.compare_exchange_weak(curr_head, curr_head->next));
        delete curr_head;
        return true; 
    }

    bool empty() const {
        return head.load() == nullptr;
    }
};

#include "lock_free_stack.h"
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

Stack<int>* stack;

void push_function()
{
    for(int i = 0; i < 100000; i++)
    {
        stack->push(i);
        // Comment out in production - printing slows down the test significantly
        // cout << "push " << i << endl;
    }
}

void pop_function()
{
    for(int i = 0; i < 100000;)
    {
        bool result = stack->pop();
        if(!result) {
            // Stack is empty
            // cout << "the stack is empty" << endl;
            // Add a small delay to avoid busy waiting
            // this_thread::sleep_for(chrono::microseconds(1));
        }
        else {
            i++;
            // cout << "popped successfully" << endl;
        }
    }
}

int main()
{
    // Initialize the lock-free stack
    stack = new Stack<int>();

    vector<thread> threads;
    threads.reserve(200);
    
    // Create 100 push threads
    for(int i = 0; i < 100; i++) {
        threads.emplace_back(push_function);
    }
    
    // Create 100 pop threads
    for(int i = 0; i < 100; i++) {
        threads.emplace_back(pop_function);
    }
    
    // Wait for all threads to complete
    for(auto& t : threads) {
        t.join();
    }
    
    // Check if stack is empty
    cout << "Test completed. Stack is " << (stack->empty() ? "empty" : "not empty") << endl;
    
    // Clean up
    delete stack;
    
    return 0;
}
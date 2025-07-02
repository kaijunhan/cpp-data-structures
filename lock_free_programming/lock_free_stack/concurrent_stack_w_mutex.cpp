// Implementation 1: using mutexes
#include <iostream>
#include <thread>
#include <mutex>
#include <vector> 
#include <optional>

using namespace std;

template <typename T> class Stack {
private:
    vector<T> stack;
    std::mutex mutex; 
public:
    Stack(){
        stack.reserve(128); 
    }

    void push(T arg){
        mutex.lock();
        stack.push_back(arg);
        mutex.unlock();
    }

    std::optional <T> top(){
        std::optional<T> elt = nullopt;
        mutex.lock();
        if(!stack.empty()){
            elt = stack.back();
        }
        mutex.unlock();
        return elt; // what if there is nothing? return nullopt
    }

    void pop(){
        mutex.lock();
        if(!stack.empty()){
            stack.pop_back();
        }
        mutex.unlock();
    }
};

template <typename T>
void worker_func(T a, Stack<T>& stack){
    for (int i = 0; i < 100; i++){
        stack.push(a++);
    }
}

template <typename T>
void worker_func_pop(Stack<T>& stack){
    for(int i = 0; i < 100; i++){
        stack.pop();
    }
}


int main(){
    Stack<int> mystack;
    
    std::thread t1(worker_func<int>, 0, std::ref(mystack));
    std::thread t2(worker_func_pop<int>, ref(mystack));
    t1.join();
    t2.join();
    return 0;    
}

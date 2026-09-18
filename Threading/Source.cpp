#include <iostream>
#include <thread>
#include <mutex>


int counter = 0;
std::mutex m;
std::mutex m1;
std::mutex m2;
void worker()
{
    
    for (int i = 0; i < 100'000; ++i) {
        std::lock_guard lock{ m };
        // garantiert, dass nur ein Thread gleichzeitig 
        // counter verändern daf
        ++counter; // mit mutex Data Race
    }
}

void worker1() {
    std::lock_guard lock1{ m1 };
    std::lock_guard lock2{ m2 };
}

void worker2() {
    std::lock_guard lock2{ m2 };
    std::lock_guard lock1{ m1 };
}

int main()
{

    std::thread t1{ worker1 };
    std::thread t2{ worker2 };

    t1.join();
    t2.join();

    std::cout << counter << '\n';

    // unter der Haube passiert ungefähr das: 
    int temp = counter;
    temp = temp + 1;
    counter = temp;
}
#include <generator>
#include <iostream>


std::generator<int> fibonacci()                  // unendliche Folge — lazy kein Problem
{
    int a = 0, b = 1;
    while (true) {
        co_yield a;
        int next = a + b;
        a = b;
        b = next;
    }
}

int main() {
    int taken = 0;
    for (int x : fibonacci()) {                  
        std::cout << ' ' << x;
        if (++taken == 10) break;
    }
}
/**
g++ -Wall -std=c++11 main.cpp 
*/

#include "mytimer.h"

#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[])
{
    std::cout << "adsfsdfasdf" << std::endl;
    
    CTimer t;
    
    sleep(1);
    t.reset();
    std::cout << "time is:" << t.times() << std::endl;
    std::cout << "time is:" << t.elapsed_nano() << std::endl;
    std::cout << "time is:" << t.elapsed_micro() << std::endl;
    
    return 0;
}

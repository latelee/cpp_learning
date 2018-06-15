/**
耗时统计类

g++ -Wall -std=c++11 main.cpp 

命名空间太长了。。。
*/

#include <iostream>
#include <unistd.h>
#include "mytimer.h"

int main(int argc, char* argv[])
{
    std::cout << "adsfsdfasdf" << std::endl;
    
    CTimer t;
    
    sleep(1);
    
    std::cout << "time is:" << t.times() << std::endl;
    return 0;
}
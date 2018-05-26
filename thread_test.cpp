/**
多线程、延时测试
g++ -std=c++11 thread_test.cpp -lpthread
*/
#include <thread>
#include <chrono>
#include <iostream>

#include <ctime>
#include <ratio>
#include <chrono>

int system_clock_test(void)
{
  using std::chrono::system_clock; // 命名空间太长了，减少一些

  // duration类，第一个参数为类型，第二个为时长，分子分母形式，
  // ratio类，第二个是分母，默认为1，可不写
  // 这个是定义一天有多少秒
  std::chrono::duration<int,std::ratio<60*60*24> > one_day (1);

  system_clock::time_point today = system_clock::now();
  system_clock::time_point tomorrow = today + one_day; // 加上一天
  
  std::time_t tt;

  tt = system_clock::to_time_t(today);
  std::cout << "today is: " << ctime(&tt);

  tt = system_clock::to_time_t ( tomorrow );
  std::cout << "tomorrow will be: " << ctime(&tt);

  return 0;
}

void click()
{

}

void click_new()
{

}


int main(int argc, char* argv[])
{
    system_clock_test();
    return 0;
    
    std::thread task01(click_new);  
    std::thread task02(click_new);  
    task01.join();  
    task02.join(); 
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 延时1秒
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 延时1秒
    
    return 0;
}
/**
多线程、互斥测试

clock()函数在ctime头文件定义
返回值除以CLOCKS_PER_SEC，得到秒数，
但没有权威资料说clock返回值为毫秒。对于严格的计时函数来说，不建议使用，
但对比不同函数执行的相对时长，则可以使用
g++ -std=c++11 atomic_test.cpp -lpthread
*/
#include <thread>
#include <chrono>
#include <atomic>
#include <iostream>
#include <mutex>
#include <ctime> // clock

using namespace std;
// 全局的结果数据 
long total = 0; 
mutex mt;

// 类似还有atomic_bool，atomic_int
atomic_long atotal(0);

// 点击函数
void add1()
{
    for(int i=0; i<1000000;++i)
    {
        // 加锁，否则total结果是不可预知的
        // 但加锁后，时间是不加锁的10倍
        mt.lock();
        total += 1;
        mt.unlock();
    }
}

// 使用mutex多线程耗时统计
// 不加锁：duration:25139ms
// 加锁：duration:345849ms
void test1()
{
    // 计时开始
    clock_t start = clock();
    
    thread task01(add1);  
    thread task02(add1);  
    task01.join();  
    task02.join(); 
    
    // 计时结束
    clock_t finish = clock();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    // 输出结果
    cout<<"test1\n";
    cout<<"result:"<<total<<endl;
    cout<<"duration:"<<finish -start<<"ms"<<endl;
}

void add2()
{
    for(int i=0; i<1000000;++i)
    {
        atotal += 1;
    }
}

// 原子类型在多程耗时统计
// duration:65393ms
void test2()
{
    // 计时开始
    clock_t start = clock();
    
    thread task01(add2);  
    thread task02(add2);  
    task01.join();  
    task02.join(); 
    
    // 计时结束
    clock_t finish = clock();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    // 输出结果
    cout<<"test2\n";
    cout<<"result:"<<total<<endl;
    cout<<"duration:"<<finish -start<<"ms"<<endl;
}

typedef struct foo_tt
{
    int foo;
    int bar;
}foo_t;

std::atomic<foo_t> foo;

// 使用结构体方式，还不知道如何测试
#if 0
void add3()
{
    for(int i=0; i<1000000;++i)
    {
        foo.foo++;
        foo.bar++;
    }
}

void test3()
{
    // 计时开始
    clock_t start = clock();
    
    thread task01(add3);  
    thread task02(add3);  
    task01.join();  
    task02.join(); 
    
    // 计时结束
    clock_t finish = clock();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    // 输出结果
    cout<<"test3\n";
    cout<<"result:"<<foo.foo<<" " << foo.bar << endl;
    cout<<"duration:"<<finish -start<<"ms"<<endl;
}
#endif

int main(int argc, char* argv[])
{
    test1();
    test2();
    test3();
    
    return 0;
}
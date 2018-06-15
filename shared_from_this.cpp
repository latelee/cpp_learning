/**
shared_ptr和enable_shared_from_this的使用
g++ -Wall -std=c++11 shared_from_this.cpp

结论：
不要在构造函数中使用 shared_from_this，可以写一个init手动初始化
不要一些地方使用 shared_ptr，另一些地方没使用，一定要统一使用
使用std::dynamic_pointer_cast<T>()需要基类中存在虚函数
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>


class CTest1: public std::enable_shared_from_this<CTest1>
{
public:
    CTest1()
    {
        printf("CTest1::CTest1()\n");
        // 此时使用shared_from_this(), 但CTest1的实例本身尚未构造成功 出错
        //std::shared_ptr<CTest1> p= shared_from_this();
    }

    void foo()
    {
        printf("CTest1::foo()\n");
        std::shared_ptr<CTest1> p= shared_from_this();
    }
    virtual ~CTest1() // 注：CTest2继承于CTest1，且用到shared_ptr，则父类必须一个虚函数。
    {
        printf("~CTest1...\n");
    }
};

// 前置声明
class CTest2;
// 外部函数使用了该类
void hello(std::shared_ptr<CTest2> ptr)
{
    printf("here in hello...\n");
}

// 继承测试
class CTest2: public CTest1
{
public:
    CTest2() { /* ... */ }
    virtual ~CTest2() { }
    
    void method(std::shared_ptr<CTest2> p)
    {
        printf("here in CTest2...\n");

        // shared_from_this()的返回值类型为std::shared_ptr<CTest1>，
        // 使用std::dynamic_pointer_cast<CTest2>函数将其转为std::shared_ptr<CTest2>类型
        std::shared_ptr<CTest2> ptr = std::dynamic_pointer_cast<CTest2>(shared_from_this());
        hello(ptr);
    }
};


int main()
{
    /**
    出错：
    CTest1::CTest1()
    terminate called after throwing an instance of 'std::bad_weak_ptr'
      what():  bad_weak_ptr
    Aborted (core dumped)

    */
    //std::shared_ptr<CTest1> a(new CTest1);
    
    /**
    出错
    terminate called after throwing an instance of 'std::bad_weak_ptr'
    what():  bad_weak_ptr
    因为用CTest1 test声明，是栈上分配的空间，但foo却使用了shared_ptr。
    */
    //CTest1 test;
    //test.foo();
    
    // 正确方式 
    std::shared_ptr<CTest1> p(new CTest1); // 使用shared_ptr创建类实例
    p->foo();
    
    std::shared_ptr<CTest1> p1 = std::make_shared<CTest1>(); // 使用make_shared也可以
    p1->foo();
    
    std::shared_ptr<CTest2> p2 = std::make_shared<CTest2>();
    
    p2->method(p2);
    return 0;
}
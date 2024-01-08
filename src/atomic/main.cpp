/* 测试在不同线程中原子数据发生变化的情况 */
#include <atomic>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono;
using std::cout;
using std::endl;

std::atomic<int> tem;
int indata ;

void Thread1();
// void Thread2();

int main()
{
    std::thread thread1(Thread1);
    thread1.detach();

    // std::thread thread2(Thread2);
    // thread2.detach();

    // std::cin >> indata;
    int i=0;
    while(true)
    {
        tem.store(i++); 
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    
}

void Thread1()
{
    while(true)
    {
        cout << "thread1---tem=" << tem.load() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// void Thread2()
// {
//     while(true)
//     {
//         cout << "thread2---tem=" << tem.load() << endl;
//         std::this_thread::sleep_for(std::chrono::seconds(1));
//     }
// }
#include <iostream>

#include <azh/timer_thread.hpp>

int i=0;

void print()
{
    std::cout<<"i="<<i<<"\n";
}

int main()
{
    azh::timer_thread t;
    t.start(print,2);

    for(int ii=0;ii<10;ii++)
    {
        i+=1;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    return 0;
}
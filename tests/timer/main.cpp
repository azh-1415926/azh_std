#include <iostream>

#include <azh/timer.hpp>

int main()
{
    // start timer
    azh::timer timer1;

    for(int i=0;i<10000;i++)
    {
        std::cout<<"";
    }

    // get interval between 'start timer' and now
    std::cout<<timer1.end()<<"ms\n";

    azh::timer timer2=timer1;

    for(int i=0;i<10000;i++)
    {
        std::cout<<"";
    }

    double t1=timer1.end(),t2=timer2.end();

    std::cout<<"timer1:"<<t1<<"ms\n";
    std::cout<<"timer2:"<<t2<<"ms\n";
    std::cout<<"timer2-timer1:"<<timer2-timer1<<"ms\n";

    azh::timer timer3;

    for(int i=0;i<100000000;i++)
    {
        std::cout<<"";
    }

    azh::timer timer4;
    double t3=timer3.end();

    std::cout<<"timer3:"<<t3<<"ms\n";
    std::cout<<"timer4-timer3:"<<timer4-timer3<<"ms\n";

    return 0;
}
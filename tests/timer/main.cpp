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
    std::cout<<timer1.end()<<"s\n";

    azh::timer timer2=timer1;

    for(int i=0;i<10000;i++)
    {
        std::cout<<"";
    }

    double t1=timer1.end(),t2=timer2.end();

    std::cout<<"timer1:"<<t1<<"s\n";
    std::cout<<"timer2:"<<t2<<"s\n";
    std::cout<<"timer2-timer1:"<<timer2-timer1<<"s\n";

    azh::timer timer3;

    for(int i=0;i<10000;i++)
    {
        std::cout<<"";
    }

    azh::timer timer4;
    double t3=timer3.end();

    std::cout<<"timer3:"<<t3<<"s\n";
    std::cout<<"timer4-timer3:"<<timer4-timer3<<"s\n";

    return 0;
}
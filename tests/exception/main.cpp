#include <iostream>

#include <azh/exception.hpp>
#include <azh/timer_thread.hpp>

int* i=nullptr;

void print()
{
    std::cout<<"i="<<*i<<"\n";
}

int main()
{
    azh::timer_thread t;
    std::function<void(void)> func;

    try
    {
        t.start(print,0.5);
    

        for(int ii=0;ii<10;ii++)
        {
            
            std::this_thread::sleep_for(std::chrono::seconds(1));

            if(ii==0)
            {
                i=new int;
                *i=1;
            }
            *i+=1;
        }

    }
    catch(const azh::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
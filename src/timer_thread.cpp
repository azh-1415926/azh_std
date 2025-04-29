#include "azh/timer_thread.hpp"

#include <iostream>

#if _WIN32
    #include <windows.h>
    #define SLEEP(s) Sleep(s*1000)
#else
    #include <unistd.h>
    #define SLEEP(s) sleep(s)
#endif

namespace azh
{
    timer_thread::timer_thread()
    {
        m_Thread=nullptr;
    }

    timer_thread::~timer_thread()
    {
        if(m_Thread!=nullptr)
            delete m_Thread;
    }

    void timer_thread::start(const std::function<void(void)> &func, double s)
    {
        std::function<void(void)> call_back=[s,&func]()
        {
            while(1)
            {
                SLEEP(s);
                if(func)
                {
                    func();
                }
            }
        };

        m_Thread=new std::thread(call_back);
        m_Thread->detach();
    }
}
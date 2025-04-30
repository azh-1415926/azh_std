#include "azh/timer_thread.hpp"

#include <iostream>

#if _WIN32
    #include <windows.h>
    #define SLEEP(s) Sleep(s*1000)
#else
    #include <unistd.h>
    #define SLEEP(s) sleep(s)
#endif

#include "azh/exception.hpp"

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
        if(!func)
        {
            throw azh::exception(azh::ERROR_TYPE::INVALID_ARGUMENT,ERROR_LINE);
        }

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

        try
        {
            m_Thread=new std::thread(call_back);
            m_Thread->detach();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}
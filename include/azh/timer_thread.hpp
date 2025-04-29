#ifndef TIMER_THREAD_H
#define TIMER_THREAD_H

#include <thread>
#include <functional>

namespace azh
{
    
    class timer_thread
    {
        private:
            std::thread* m_Thread;

        public:
            timer_thread();
            ~timer_thread();

            void start(const std::function<void(void)>& func,double s);

        private:
            ;
    };
}

#endif
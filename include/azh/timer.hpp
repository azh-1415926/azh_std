#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace azh
{
    class timer
    {
        private:
            using milliseconds_ratio = std::ratio<1, 1000>;
            using duration_millis = std::chrono::duration<double, milliseconds_ratio>;

            std::chrono::system_clock::time_point m_Start;
            // std::chrono::_V2::system_clock::time_point m_Start;

        public:
            timer()
            {
                m_Start = std::chrono::system_clock::now();
            }

            void start()
            {
                m_Start = std::chrono::system_clock::now();
            }

            double end()
            {
                duration_millis duration=std::chrono::system_clock::now()-m_Start;
                return duration.count();
            }

            double endAndRestart()
            {
                duration_millis duration=std::chrono::system_clock::now()-m_Start;
                m_Start = std::chrono::system_clock::now();
                return duration.count();
            }

            timer(const timer& t): m_Start(t.m_Start) {  }
            timer operator=(const timer& t) { timer timer; timer.m_Start=t.m_Start; return timer; }
            double operator-(const timer& t) { duration_millis duration=m_Start-t.m_Start; return duration.count(); }
    };
}

#endif
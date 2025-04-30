#pragma once

#include <iostream>
#include <ctime>
#include <mutex>

#ifndef LOGGER_STREAM

#define LOGGER_STREAM std::cout

#endif

#define LOGGER_WARNNING 0
#define LOGGER_INFO 1
#define LOGGER_ERROR 2
#define LOGGER_FATAL 3

namespace azh
{
    enum class LOGGER_LEVEL
    {
        WARNNIING=LOGGER_WARNNING,INFO=LOGGER_INFO,
        ERROR=LOGGER_ERROR,FATAL=LOGGER_FATAL
    };

    class GlobalLoggerLevel
    {
        public:
            static GlobalLoggerLevel& getInstance()
            {
                static GlobalLoggerLevel instance;
                return instance;
            }
            LOGGER_LEVEL get() {  return m_Instance; }
            void set(const LOGGER_LEVEL& data) { m_Instance=data; }
        private:
            explicit GlobalLoggerLevel() { }
            LOGGER_LEVEL m_Instance;
    };

    std::mutex Logger_Mutex;

    class logger
    {
        private:
            bool shouldLogging;
            std::ostream& out;

        public:
            logger(int level=LOGGER_INFO,std::ostream& o=LOGGER_STREAM): out(o)
            {
                if((LOGGER_LEVEL)level<GlobalLoggerLevel::getInstance().get())
                {
                    shouldLogging=false;
                    return;
                }

                Logger_Mutex.lock();
                shouldLogging=true;

                printCurrentTime();
                printLoggerHeader(level);
                
                out<<" ";
            }

            ~logger()
            {
                if(!shouldLogging)
                {
                    return;
                }

                out<<"\n";

                Logger_Mutex.unlock();
            }

            logger(const logger& l)=delete;
            logger operator=(const logger& l)=delete;
            
            void* operator new(size_t size)=delete;
            void* operator new[](size_t size)=delete;
            void operator delete(void* ptr)=delete;
            void operator delete[](void* ptr)=delete;

            static void setGlobalLevel(const LOGGER_LEVEL& level) { GlobalLoggerLevel::getInstance().set(level); }
            static void setGlobalLevel(int level) { GlobalLoggerLevel::getInstance().set((LOGGER_LEVEL)level); }

            template<class T>
            logger& operator<<(const T& type)
            {
                if(!shouldLogging)
                {
                    return *this;
                }

                out<<type;

                return *this;
            }

        private:
            void printLoggerHeader(const LOGGER_LEVEL& level) { printLoggerHeader(((int)level)); }
            void printLoggerHeader(int level)
            {
                out<<"[";

                switch (level)
                {
                case LOGGER_WARNNING:
                    out<<"WARNNING";
                    break;
                
                case LOGGER_INFO:
                    out<<"  INFO  ";
                    break;

                case LOGGER_ERROR:
                    out<<"  ERROR ";
                    break;

                case LOGGER_FATAL:
                    out<<"  FATAL ";
                    break;

                default:
                    break;
                }
                out<<"]";
            }

            void printCurrentTime()
            {
                time_t now;
                time(&now);
                tm p=*localtime(&now);

                out<<"["<<
                    p.tm_year + 1900                        <<"-"<<
                    (p.tm_mon + 1)/10<<(p.tm_mon + 1)%10    <<"-"<<
                    p.tm_mday/10<<p.tm_mday%10              <<" "<<
                    p.tm_hour/10<<p.tm_hour%10              <<":"<<
                    p.tm_min/10<<p.tm_min%10                <<":"<<
                    p.tm_sec/10<<p.tm_sec%10                <<"]";
            }
    };
}
#include <iostream>
#include <thread>
#include <fstream>

std::ofstream stream("test.log");

#define LOGGER_STREAM stream
#include <azh/logger.hpp>

void thread01()
{
    azh::logger::setGlobalLevel(LOGGER_INFO);
    azh::logger(LOGGER_WARNNING)<<"This is a warnning!";
    azh::logger(LOGGER_INFO)<<"This is a info!";
    azh::logger(LOGGER_ERROR)<<"This is a error!";
    azh::logger(LOGGER_FATAL)<<"This is a fatal!";
}

int main()
{
    azh::logger(LOGGER_FATAL)<<"Main Thread Start!";
    // logger level default : warnning
    azh::logger()<<"Hello "<<"World!";
    azh::logger(LOGGER_WARNNING)<<"This is a warnning!";
    azh::logger(LOGGER_INFO)<<"This is a info!";
    azh::logger(LOGGER_ERROR)<<"This is a error!";
    azh::logger(LOGGER_FATAL)<<"This is a fatal!";

    // set level to error, only show error、fatal
    azh::logger::setGlobalLevel(LOGGER_ERROR);
    azh::logger(LOGGER_WARNNING)<<"This is a warnning!";
    azh::logger(LOGGER_INFO)<<"This is a info!";
    azh::logger(LOGGER_ERROR)<<"This is a error!";
    azh::logger(LOGGER_FATAL)<<"This is a fatal!";

    int n=10;
    std::thread* childThreads[n];
    
    for(int i=0;i<n;i++)
    {
        childThreads[i]=new std::thread(thread01);
    }

    for(int i=0;i<n;i++)
    {
        childThreads[i]->join();
        delete childThreads[i];
    }

    azh::logger(LOGGER_FATAL)<<"Main Thread End!";

    return 0;
}
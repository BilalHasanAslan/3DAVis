#ifndef LOG_KEEPER_H_
#define LOG_KEEPER_H_

#include <string>
#include <chrono>

namespace NDAVis
{

    class LogKeeper
    {
    public:

        LogKeeper(std::string msg, bool showTime);

        std::string msg;
        bool showTime;
        std::chrono::high_resolution_clock::time_point t_start;
        std::chrono::high_resolution_clock::time_point t_end;
        double elapsed_time_ms;

        void UpdateLog(std::string msg, bool showTime);
        void endLog(bool Error);
        void writeToLogFile();
    };
}

#endif //LOG_KEEPER_H_
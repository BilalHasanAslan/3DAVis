#include <string>
#include "LogKeeper.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <ctime>

namespace NDAVis
{
    std::chrono::high_resolution_clock::time_point t_end, t_start;
    std::string msg;
    double elapsed_time_ms;
    bool Error;
    //Start a logkeeper
    LogKeeper::LogKeeper(std::string msg, bool showTime)
    {

        this->msg = msg;
        this->showTime = showTime;
        t_start = std::chrono::high_resolution_clock::now();
    }
    //Update a logkeeper
    void LogKeeper::UpdateLog(std::string msg, bool showTime)
    {

        this->msg = msg;
        this->showTime = showTime;
        t_start = std::chrono::high_resolution_clock::now();
    }
     //End a single log
    void LogKeeper::endLog(bool Error)
    {

        if (Error)
        {
            std::cout << "Error Occured for " + msg << std::endl;
        }
        else
        {

            t_end = std::chrono::high_resolution_clock::now();

            if (showTime)
            {
                elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
                std::cout << "Time Taken To " + msg + " : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s" << std::endl;
            }
            else
            {
                std::cout << msg + " is Finished" << std::endl;
            }
        }
        writeToLogFile();
    }
     //Writes single log to log file
    void LogKeeper::writeToLogFile()
    {
        std::ofstream outfile;
        outfile.open("log.txt", std::ios::app);
        if (Error)
        {
            outfile << "------------------------------------------------------------------\n";
            outfile << "Error Occured for " + msg;
            outfile << "------------------------------------------------------------------\n";
        }
        else
        {
            std::time_t end_time = std::chrono::system_clock::to_time_t(t_end);
            outfile << "------------------------------------------------------------------\n";
            outfile << std::ctime(&end_time);
            outfile << "Finished " + msg;
            outfile << "\nTime Taken : " + std::to_string(elapsed_time_ms) + " ms" + " & " + std::to_string(elapsed_time_ms / 1000) + " s\n";
            outfile << "------------------------------------------------------------------\n";
            outfile.close();
        }
    }
}
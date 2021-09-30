#include <string>
#include "LogKeeper.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <ctime>

namespace NDAVis
{


    /*
    The constructor of the LogKeeper class takes two parameters: a string and a boolean.
    The string is the message that will be printed to the console.
    The boolean is a flag that indicates whether or not the time should be printed.
    
    Args:
      msg: The message to be displayed.
      showTime: If true, the time will be shown in the log.
    Returns:
      Nothing
    */
    LogKeeper::LogKeeper(std::string msg, bool showTime)
    {

        this->msg = msg;
        this->showTime = showTime;
        t_start = std::chrono::high_resolution_clock::now();
    }

    /*
    Updates the log msg
    
    Args:
      msg: The message to be logged.
      showTime: If true, the time will be shown in the log.
    Returns:
      Nothing
    */
    void LogKeeper::UpdateLog(std::string msg, bool showTime)
    {

        this->msg = msg;
        this->showTime = showTime;
        t_start = std::chrono::high_resolution_clock::now();
    }

    /*
    End the log writes the log to console and to file
    
    Args:
      None
    Returns:
      Nothing
    */
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

    /*
    Writes Log to file
    
    Args:
      None
    Returns:
      Nothing
    */
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
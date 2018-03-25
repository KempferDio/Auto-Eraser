#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <chrono>
#define LOG_FILE_NAME "log.txt"
#define MS_IN_SEC 1000
#define DEFAULT_COLOR "\033[0m"
#define BLUE_COLOR "\033[0;34m"
#define CYAN_COLOR "\033[0;96m"
#define YELLOW_COLOR "\033[0;33m"
#define RED_COLOR "\033[0;31m"

namespace Core {
    class Log {
    public:
        static bool isLogFileWasCreated;
        static std::chrono::milliseconds startTime;


        template<typename T, typename... Args>
        static void LogInfo(T first, Args... args) {
            std::ostringstream stm;
            if(callCounter == 0) {
                stm << GetCurrentTimeFromStart() << " [" <<  BLUE_COLOR << " INFO" << DEFAULT_COLOR << " ] ";
            }
            stm << first << " :: ";
            std::cout << stm.str();
            RecordIntoLogFile(stm.str());
            callCounter++;
            LogInfo(args ...);
        }

        template<typename T, typename... Args>
        static void LogDebug(T first, Args... args) {
            std::ostringstream stm;
            if(callCounter == 0) {
                stm << GetCurrentTimeFromStart() << " [" << CYAN_COLOR << " DEBUG" << DEFAULT_COLOR << " ] ";
            }
            stm << first << " :: ";
            std::cout << stm.str();
            RecordIntoLogFile(stm.str());
            callCounter++;
            LogDebug(args ...);
        }

        template<typename T, typename... Args>
        static void LogWarning(T first, Args... args) {
            std::ostringstream stm;
            if(callCounter == 0) {
                stm << GetCurrentTimeFromStart() << " [" << YELLOW_COLOR << " WARNING" << DEFAULT_COLOR << " ] ";
            }
            stm << first << " :: ";
            std::cout << stm.str();
            RecordIntoLogFile(stm.str());
            callCounter++;
            LogWarning(args ...);
        }

        template<typename T, typename... Args>
        static void LogError(T first, Args... args) {
            std::ostringstream stm;
            if(callCounter == 0) {
                stm << GetCurrentTimeFromStart() << " [" << RED_COLOR << " ERROR" << DEFAULT_COLOR << " ] ";
            }
            stm << first << " :: ";
            std::cout << stm.str();
            RecordIntoLogFile(stm.str());
            callCounter++;
            LogError(args ...);
        }

        static void LogInfo() {
            breakRecoursion();
        }

        static void LogWarning() {
            breakRecoursion();
        }

        static void LogDebug() {
            breakRecoursion();
        }

        static void LogError() {
            breakRecoursion();
        }
        
    private:
        static void RecordIntoLogFile(std::string fullMsg);
        static float GetCurrentTimeFromStart();
        static int callCounter;

        static void breakRecoursion() {
            callCounter = 0;
            std::cout << "\n";
            RecordIntoLogFile("\n");
        }
    };
}



#endif
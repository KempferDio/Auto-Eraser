#ifndef AUTO_ERASER_H
#define AUTO_ERASER_H
#include <iostream>
#include <time.h>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class AutoEraser {
    public:
        AutoEraser() {}
        AutoEraser(std::string path, std::string ext);
        ~AutoEraser() {}

        void checkFiles();
        void setDeadlineDate(int days, int hours, int mins);
        std::string GetFileExt(fs::directory_entry p);

        time_t GetFileCreationTime();
        int DeleteFile();

        time_t deadlineDate;
        std::string trackingExt;
        std::string trackingPath;
        int strideDay;
        int strideHours;
        int strideMins;
    private:
        time_t getCurrentTime();
};

#endif
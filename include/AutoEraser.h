#ifndef AUTO_ERASER_H
#define AUTO_ERASER_H

#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <experimental/filesystem>
#include <algorithm>

namespace fs = std::experimental::filesystem;

class AutoEraser {

    public:
        AutoEraser() {}
        AutoEraser(std::string path, std::string ext);
        ~AutoEraser() {}

        time_t GetFileCreationTime(fs::directory_entry p);

        void CheckFiles();
        void SetDeadlineDate(int days, int hours, int mins);
        std::string GetFileExt(fs::directory_entry p);

        int DeleteFile();

        time_t deadlineDate;
        std::string trackingExt;
        std::string trackingPath;
        int strideDay;
        int strideHours;
        int strideMins;
    private:
        time_t GetCurrentTime();
        std::string GetStringNameOfFile(fs::directory_entry p);
        
};

#endif
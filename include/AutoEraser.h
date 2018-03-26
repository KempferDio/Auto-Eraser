#ifndef AUTO_ERASER_H
#define AUTO_ERASER_H

#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <experimental/filesystem>
#include <algorithm>
#include <vector>
#include <Log.h>

namespace fs = std::experimental::filesystem;

class AutoEraser {

    public:
        AutoEraser();
        ~AutoEraser() {}

        void CheckFiles();
        void SetDeadlineDate(int days, int hours, int mins);
        void AddTrackingPath(std::string path);
        void AddTrackingExt(std::string ext);
        void PrintDeadlineDate();

        std::string trackingExt;
        std::string trackingPath;

        std::vector<std::string> trackingPaths;
        std::vector<std::string> trackingExts;
        
        time_t deadlineDate;
        int strideDay;
        int strideHours;
        int strideMins;
    private:
        bool CheckFileExt(fs::directory_entry p);
        time_t GetFileCreationTime(fs::directory_entry p);
        std::string GetFileExt(fs::directory_entry p);
        time_t GetCurrentTime();
        std::string GetStringNameOfFile(fs::directory_entry p);
        int DeleteFile(std::string filePath);
        
};

#endif
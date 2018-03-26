#include <AutoEraser.h>

namespace fs = std::experimental::filesystem;
using namespace std;

AutoEraser::AutoEraser() {
    SetDeadlineDate(1, 0, 0);
}

void AutoEraser::CheckFiles() {
    for(vector<string>::iterator pathItem = trackingPaths.begin(); pathItem != trackingPaths.end(); pathItem++) {
        for(auto p : fs::recursive_directory_iterator(*pathItem)) {
#ifdef DEBUG
            Log::LogDebug(p);
#endif
            if(!CheckFileExt(p)) {
                continue;
            }

            Log::LogWarning(GetFileExt(p), "was founded!");

            if(GetFileCreationTime(p) < deadlineDate) {
                string filePath = GetStringNameOfFile(p);
                filePath.erase(remove(filePath.begin(), filePath.end(), '"'), filePath.end());

                DeleteFile(filePath);
            }
        }
    }
}

void AutoEraser::SetDeadlineDate(int days, int hours, int mins) {
    deadlineDate = GetCurrentTime();

    struct tm timeInfo = *localtime(&deadlineDate);
    timeInfo.tm_mday -= days;
    timeInfo.tm_hour -= hours;
    timeInfo.tm_min -= mins;

    deadlineDate = mktime(&timeInfo);
}

void AutoEraser::AddTrackingPath(string path) {
    trackingPaths.push_back(path);
}

void AutoEraser::AddTrackingExt(string ext) {
    trackingExts.push_back(ext);
}

void AutoEraser::PrintDeadlineDate() {
    time_t ct = deadlineDate;
    Log::LogInfo("Deadline: ", std::asctime(std::localtime(&ct)));
}

/* Private methods */

bool AutoEraser::CheckFileExt(fs::directory_entry p) {
    for(vector<string>::iterator extItem = trackingExts.begin(); extItem != trackingExts.end(); extItem++) {
        if(GetFileExt(p) == *extItem) {
            return true;
        }
    }

    return false;
}

time_t AutoEraser::GetFileCreationTime(fs::directory_entry p) {
    auto creationTime =  fs::last_write_time(p);
    time_t sysCreationTime = decltype(creationTime)::clock::to_time_t(creationTime);

    return sysCreationTime;
}

string AutoEraser::GetFileExt(fs::directory_entry p) {
    string fileExt = GetStringNameOfFile(p);


    int stride = fileExt.find_last_of(".");
    if(stride == -1) {
        return "FOLDER";
    }

    fileExt.erase(fileExt.end() - 1);

    return fileExt.substr(stride + 1);
}

time_t AutoEraser::GetCurrentTime() {
    time_t timeValue = time(NULL);

    return timeValue;
}

string AutoEraser::GetStringNameOfFile(fs::directory_entry p) {
    ostringstream oss;
    oss << p;
    return oss.str();
}

int AutoEraser::DeleteFile(string filePath) {
    if(remove(filePath.c_str()) != 0) {
        Log::LogError("ERROR::FILE::", filePath, " WAS NOT REMOVED");
        return 1;
    }
    else {
        Log::LogInfo("File ", filePath, " was removed");
    }
    return 0;
}
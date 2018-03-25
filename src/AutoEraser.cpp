#include <AutoEraser.h>

namespace fs = std::experimental::filesystem;

AutoEraser::AutoEraser(std::string path, std::string ext) {
    trackingPath = path;
    trackingExt = ext;
}


std::string AutoEraser::GetFileExt(fs::directory_entry p) {
    std::string fileExt = GetStringNameOfFile(p);


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

void AutoEraser::SetDeadlineDate(int days, int hours, int mins) {
    deadlineDate = GetCurrentTime();

    struct tm timeInfo = *localtime(&deadlineDate);
    timeInfo.tm_mday -= days;
    timeInfo.tm_hour -= hours;
    timeInfo.tm_min -= mins;

    deadlineDate = mktime(&timeInfo);
}

void AutoEraser::CheckFiles() {
    for(auto p : fs::directory_iterator(trackingPath)) {
        if(GetFileExt(p) != trackingExt) {
            
            continue;
        }

        if(GetFileCreationTime(p) < deadlineDate) {
            std::string filePath = GetStringNameOfFile(p);
            filePath.erase(std::remove(filePath.begin(), filePath.end(), '"'), filePath.end());

            if(remove(filePath.c_str()) != 0) {
                std::cout << "ERROR::FILE::" << filePath << "WASN'T REMOVED" << std::endl;
            } else {
                std::cout << "File " << filePath << " was removed" << std::endl;
            }
            
            
        }

    }
}

time_t AutoEraser::GetFileCreationTime(fs::directory_entry p) {
    auto creationTime =  fs::last_write_time(p);
    time_t sysCreationTime = decltype(creationTime)::clock::to_time_t(creationTime);

    return sysCreationTime;
}

std::string AutoEraser::GetStringNameOfFile(fs::directory_entry p) {
    std::ostringstream oss;
    oss << p;
    return oss.str();
}
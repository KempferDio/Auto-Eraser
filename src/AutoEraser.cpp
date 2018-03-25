#include <AutoEraser.h>

AutoEraser::AutoEraser(std::string path, std::string ext) {
    trackingPath = path;
    trackingExt = ext;
}


std::string AutoEraser::GetFileExt(fs::directory_entry p) {
    std::ostringstream oss;
    oss << p;
    std::string fileExt = oss.str();

    int stride = fileExt.find_last_of(".");
    if(stride == -1) {
        return "FOLDER";
    }

    return fileExt.substr(stride + 1);
}

time_t AutoEraser::getCurrentTime() {
    time_t timeValue = time(NULL);

    return timeValue;
}

void AutoEraser::setDeadlineDate(int days, int hours, int mins) {
    deadlineDate = getCurrentTime();

    struct tm timeInfo = *localtime(&deadlineDate);
    timeInfo.tm_mday -= days;
    timeInfo.tm_hour -= hours;
    timeInfo.tm_min -= mins;

    deadlineDate = mktime(&timeInfo);
}

void AutoEraser::checkFiles() {

}
#include <iostream>
#include <AutoEraser.h>
#include <experimental/filesystem>
#include <time.h>

namespace fs = std::experimental::filesystem;

int main() {    

    AutoEraser *autoEraser = new AutoEraser("/home/kempfer/Desktop/winternacht", "txt");
    // Day - hour - min
    autoEraser->SetDeadlineDate(0, 0, 1);

    time_t ct = autoEraser->deadlineDate;
      std::cout << "Deadline: " << std::asctime(std::localtime(&ct)) << std::endl;

    autoEraser->CheckFiles();

    //Get extensions of file
    delete autoEraser;
    
    return 0;
}
#include <iostream>
#include <AutoEraser.h>
#include <experimental/filesystem>
#include <time.h>

namespace fs = std::experimental::filesystem;

int main() {    

    AutoEraser *autoEraser = new AutoEraser();
    // Day - hour - min
    autoEraser->SetDeadlineDate(0, 0, 1);
    autoEraser->SetDeadlineDate(1, 0, 1);
    
    autoEraser->AddTrackingPath("/home/kempfer/Desktop/winternacht/include");
    
    autoEraser->AddTrackingPath("/home/kempfer/Desktop/winternacht/src");

    autoEraser->AddTrackingExt("txt");

    autoEraser->RemoveTrackingPath("/home/kempfer/Desktop/winternacht/src");

    autoEraser->PrintDeadlineDate();

    autoEraser->CheckFiles();

    //Get extensions of file
    delete autoEraser;
    
    return 0;
}
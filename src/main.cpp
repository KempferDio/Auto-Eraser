#include <iostream>
#include <AutoEraser.h>
#include <experimental/filesystem>
#include <time.h>

namespace fs = std::experimental::filesystem;
std::string AutoEraser::deleteExt = "pdf";

int main() {    

    AutoEraser autoEraser("/home/kempfer/Desktop/winternacht", "pdf");

    //Get files in dir
    std::string path = "/home/kempfer/Desktop/winternacht";
    for(auto p : fs::directory_iterator(path)) {
      

    }


    //Get extensions of file

        
    return 0;
}
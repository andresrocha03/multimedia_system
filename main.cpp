#include "Media.h"
#include "Photo.h"
#include "Video.h"
#include <iostream>
#include <sstream>
#include <fstream>

int main(int argc, const char* argv[])
{
    std::cout << "Hello brave new world" << std::endl;
    
    // get a real path to a media file
    std::string path_photo = "/home/andre/Documentos/utensiles.jpeg";

    Photo * p = new Photo("My Title", path_photo, 48.8566, 2.3522);
    Video * v = new Video("My Video", "/path/to/video", 120.0);

    // test play function 
    p->play(p->getFilepath());
    // v->play(v->getFilepath());
    
    return 0;
}



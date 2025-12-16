#include "Media.h"
#include "Photo.h"
#include "Video.h"
#include <iostream>
#include <sstream>
#include <fstream>


int main(int argc, const char* argv[])
{
    std::cout << "Hello brave new world" << std::endl;

    // create an array of Media pointers
    int count = 0;
    Media** media_collection = new Media*[5];

    //the objects can be photos or videos
    std::string path_photo = "/home/andre/Documentos/utensiles.jpeg";
    Photo * p = new Photo("My Photo", path_photo, 48.8566, 2.3522);
    Video * v = new Video("My Video", "undefined", 120.0);

    //insert elements
    media_collection[0] = p;
    count++;
    media_collection[1] = v;
    count++;

    //loop that shows or plays atributs aof all elements of vector
    for (int i = 0; i < count; i++) {
        if (media_collection[i]->getFilepath() != "undefined") {
            media_collection[i]->show(std::cout);
            media_collection[i]->play(media_collection[i]->getFilepath());
        }
        else {
            media_collection[i]->show(std::cout);
        }
    }

        
    return 0;
}



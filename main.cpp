#include "Media.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include <iostream>
#include <sstream>
#include <fstream>


int main(int argc, const char* argv[])
{
    std::cout << "Hello brave new world" << std::endl;

    // create an array of Media pointers
    int count = 0;
    Media** media_collection = new Media*[5];

    //the objects can be photos, videos, films
    std::string path_photo = "/home/andre/Documentos/utensiles.jpeg";
    std::string path_video = "/home/andre/Documentos/myvideo.mp4";
    Photo * p = new Photo("My Photo", path_photo, 48.8566, 2.3522);
    Video * v = new Video("My Video", path_video, 120.0);
    Film * f = new Film("My Film", path_video, 3, new int[3]{30, 40, 50});

    //insert elements
    media_collection[0] = p;
    count++;
    media_collection[1] = v;
    count++;
    media_collection[2] = f;
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


    //modifyng attributes of Film
    f->setChaptersDuration(new int[2]{25, 35}, 2);
    f->show(std::cout);

    //test empty chapters
    f->setChaptersDuration(nullptr, 0);
    f->show(std::cout);
        
    return 0;
}



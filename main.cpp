#include "Media.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Group.h"
#include <iostream>
#include <sstream>
#include <fstream>


int main(int argc, const char* argv[])
{
    std::cout << "Hello brave new world" << std::endl;

    // create a group
    Group * g1 = new Group("g1");
    Group * g2 = new Group("g2");

    //the objects can be photos, videos, films
    std::string path_photo = "/home/andre/Documentos/utensiles.jpeg";
    std::string path_video = "/home/andre/Documentos/myvideo.mp4";
    Photo * p = new Photo("My Photo", path_photo, 48.8566, 2.3522);
    Photo * p2 = new Photo("My Photo 2", path_photo, 34.0522, -118.2437);
    Video * v = new Video("My Video", path_video, 120.0);
    Film * f = new Film("My Film", path_video, 3.0, 2, new int[3]{30, 40, 50});

    //insert elements
    g1->push_back(p);
    g1->push_back(v);
    g1->push_back(f);
    g2->push_back(p);
    g2->push_back(p2);

    //show all media in the group
    g1->showAllMedia(std::cout);
    g2->showAllMedia(std::cout);

    //modifyng attributes of photo
    p->setTitle("Updated Photo Name");

    //destroy g1
    delete g1;

    //show updated group
    g2->showAllMedia(std::cout);

    //destroy g2
    delete g2;

}



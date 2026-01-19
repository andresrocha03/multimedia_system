#include "Media.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Group.h"
#include <iostream>
#include <sstream>
#include <fstream>


typedef std::shared_ptr<Media> MediaPtr;
typedef std::shared_ptr<Group> GroupPtr;

int main(int argc, const char* argv[])
{
    std::cout << "Hello brave new world" << std::endl;

    // create a group
    GroupPtr g1 = std::make_shared<Group>("g1");
    GroupPtr g2 = std::make_shared<Group>("g2");

    // Group * g3 = new Group("g3");

    //the objects can be photos, videos, films
    std::string path_photo = "/home/andre/Documentos/utensiles.jpeg";
    std::string path_video = "/home/andre/Documentos/myvideo.mp4";
    MediaPtr p = std::make_shared<Photo>("My Photo", path_photo, 48.8566, 2.3522);
    MediaPtr p2 = std::make_shared<Photo>("My Photo 2", path_photo, 34.0522, -118.2437);
    MediaPtr v = std::make_shared<Video>("My Video", path_video, 120.0);
    MediaPtr f = std::make_shared<Film>("My Film", path_video, 3.0, 2, new int[3]{30, 40, 50});

    //insert elements in g1
    g1->push_back(p);
    g1->push_back(v);
    g1->push_back(f);

    //insert elements in g2
    g2->push_back(p);
    g2->push_back(p2);

    //show all media in the group
    g2->showAllMedia(std::cout);

    //modifyng attributes of photo
    p->setTitle("photo p");

    //remove p from both groups to check if media destructor is called on p
    g1->remove(p);
    g2->remove(p);
    std::cout << "After removing p from both groups" << std::endl;

    //reset shared pointer to trigger destructor
    p.reset();    
    std::cout << "After reseting p" << std::endl;
    // at this point, p should be destroyed and indeed it was in my tests

    //show updated group
    g2->showAllMedia(std::cout);
}



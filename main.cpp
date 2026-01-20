#include "Media.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Group.h"
#include "Creator.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <memory>

typedef std::shared_ptr<Media> MediaPtr;
typedef std::shared_ptr<Group> GroupPtr;

int main(int argc, const char* argv[])
{
    std::cout << "Hello brave new world" << std::endl;

    // trying to create a group -> should not work as Group's constructor is private to Creator
    GroupPtr g1 = std::make_shared<Group>("g1");
    GroupPtr g2 = std::make_shared<Group>("g2");

    //new creator
    Creator creator1 = Creator();
    
    //testing creator
    std::string path_photo = "/home/andre/Documentos/utensiles.jpeg";
    std::string path_video = "/home/andre/Documentos/myvideo.mp4";
    
    creator1.createPhoto("P1", path_photo, 48.8566, 2.3522);
    creator1.createPhoto("P2", path_photo, 34.0522, -118.2437);
    creator1.createVideo("V1", path_video, 150.0);
    creator1.createFilm("F1", path_video, 300.0, 3, new int[3]{60, 90, 150});

    //create groups
    std::list<MediaPtr> group1Media = {creator1.getPhoto("P1"), creator1.getPhoto("P2")};
    creator1.createGroup("Group1", group1Media);
    
    std::list<MediaPtr> group2Media = {creator1.getVideo("V1"), creator1.getFilm("F1")};
    creator1.createGroup("Group2", group2Media);

    //show all media in the group
    creator1.showGroup("Group1");

    //show updated group
    creator1.showGroup("Group2");
}



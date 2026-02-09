#include "Creator.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Group.h"

void Creator::createPhoto(const std::string& title, const std::string& filepath, double latitude, double longitude) {
    //create photo with new and wrap in smart pointer
    MediaPtr photo(new Photo(title, filepath, latitude, longitude));
    mediaMap[title] = photo;
}

void Creator::createVideo(const std::string& title, const std::string& filepath, double duration) {
    MediaPtr video(new Video(title, filepath, duration));
    mediaMap[title] = video;
}

void Creator::createFilm(const std::string& title, const std::string& filepath, double duration, int chaptersCount, const int* chaptersDurations) {
    MediaPtr film(new Film(title, filepath, duration, chaptersCount, chaptersDurations));
    mediaMap[title] = film;
}

void Creator::createGroup(const std::string& groupName, const std::list<MediaPtr>& mediaList) {
    GroupPtr group(new Group(groupName, mediaList));
    groupMap[groupName] = group;
}

bool Creator::showMedia(const std::string& title, std::ostream& out) const {
    auto it = mediaMap.find(title);
    if (it != mediaMap.end()){
        it->second->show(out);
        return true;
    }
    std::cout << "Media with title '" << title << "' not found." << std::endl;
    return false;
    
}

bool Creator::showGroup(const std::string& groupName, std::ostream& out) const {    
    auto groupIt = groupMap.find(groupName);
    if (groupIt != groupMap.end()) {
        groupIt->second->showAllMedia(out);
        return true;
    } 
    std::cout << "Group with name '" << groupName << "' not found." << std::endl;
    return false;
    
}



bool Creator::playMedia(const std::string& title) const {
    auto it = mediaMap.find(title);
    if (it != mediaMap.end()){
        it->second->play(it->second->getFilepath());
        return true;
    } 
    
    std::cout << "Media with title '" << title << "' not found." << std::endl;
    return false;

}

void Creator::addMediaToGroup(const std::string& title, const std::string& groupName) {
    auto groupIt = groupMap.find(groupName);
    if (groupIt != groupMap.end()) {
        auto mediaIt = mediaMap.find(title);
        if (mediaIt != mediaMap.end()) {
            groupIt->second->push_back(mediaIt->second);
        } else {
            std::cout << "Media with title '" << title << "' not found." << std::endl;
        }
    } else {
        std::cout << "Group with name '" << groupName << "' not found." << std::endl;
    }
}

MediaPtr Creator::getPhoto(const std::string& title) const {
    auto it = mediaMap.find(title);
    if (it != mediaMap.end()){
        return it->second;
    } else {
        return nullptr;
    }
}

MediaPtr Creator::getVideo(const std::string& title) const {
    auto it = mediaMap.find(title);
    if (it != mediaMap.end()){
        return it->second;
    } else {
        return nullptr;
    }
}

MediaPtr Creator::getFilm(const std::string& title) const {
    auto it = mediaMap.find(title);
    if (it != mediaMap.end()){
        return it->second;
    } else {
        return nullptr;
    }
}

GroupPtr Creator::getGroup(const std::string& groupName) const {
    auto it = groupMap.find(groupName);
    if (it != groupMap.end()){
        return it->second;
    } else {
        return nullptr;
    }
}


void Creator::save(std::ostream& out, std::string& title, std::string& type) const {
    MediaPtr media = nullptr;
    GroupPtr group = nullptr;

    if (type == "Photo") media = getPhoto(title);
    else if (type == "Video") media = getVideo(title);
    else if (type == "Film") media = getFilm(title);
    else if (type == "Group") group = getGroup(title);

    if (media) {
        media->saveToFile(out);
    } else if (group) {
        group->saveToFile(out);
    } else {
        std::cout << "No media or group found with title '" << title << "' and type '" << type << "'." << std::endl;
    }
}

void Creator::load(std::istream& in, std::string& type) {
    
    // Assuming each file has only one media or group, we can determine the type by reading the first line of the file
    std::string title;
    std::getline(in, title);


    if (type == "Photo") {
        MediaPtr media(new Photo());
        media->loadFromFile(in);
        mediaMap[title] = media;
    } else if (type == "Video") {
        MediaPtr media(new Video());
        media->loadFromFile(in);
        mediaMap[title] = media;
    } else if (type == "Film") {
        MediaPtr media(new Film());
        media->loadFromFile(in);
        mediaMap[title] = media;
    } else if (type == "Group") {
        GroupPtr group(new Group());
        group->loadFromFile(in);
        groupMap[title] = group;
    } else {
        std::cout << "Unknown type '" << type << "'. Cannot load." << std::endl;
    }

}
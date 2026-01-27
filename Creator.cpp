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

void save(const std::string& filename) const {
    for (const auto& pair: mediaMap) {
        // Serialize each media object
    }
}

void load(const std::string& filename) {

}
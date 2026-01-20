#include "Creator.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"


void Creator::createPhoto(const std::string& title, const std::string& filepath, double latitude, double longitude) {
    MediaPtr photo = std::make_shared<Photo>(title, filepath, latitude, longitude);
    mediaMap[title] = photo;
}

void Creator::createVideo(const std::string& title, const std::string& filepath, double duration) {
    MediaPtr video =  std::make_shared<Video>(title, filepath, duration);
    mediaMap[title] = video;
}

void Creator::createFilm(const std::string& title, const std::string& filepath, double duration, int chaptersCount, const int* chaptersDurations) {
    MediaPtr film = std::make_shared<Film>(title, filepath, duration, chaptersCount, chaptersDurations);
    mediaMap[title] = film;
}

void Creator::createGroup(const std::string& groupName) {
    GroupPtr group = std::make_shared<Group>(groupName);
    groupMap[groupName] = group;
}

void Creator::showMedia(const std::string& title) const {
    auto it = mediaMap.find(title);
    if (it != mediaMap.end()){
        it->second->show(std::cout);
    } else {
        std::cout << "Media with title '" << title << "' not found." << std::endl;
    }
}

void Creator::showGroup(const std::string& groupName) const {
    auto it = groupMap.find(groupName);
    if (it != groupMap.end()){
        it->second->showAllMedia(std::cout);
    } else {
        std::cout << "Group with name '" << groupName << "' not found." << std::endl;
    }
}

void Creator::playMedia(const std::string& title) const {
    auto it = mediaMap.find(title);
    if (it != mediaMap.end()){
        it->second->play(it->second->getFilepath());
    } else {
        std::cout << "Media with title '" << title << "' not found." << std::endl;
    }
}


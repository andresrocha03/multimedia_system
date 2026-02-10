#include "Group.h"
#include "Media.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"



Group::Group(const std::string& name) : name(name) {};

Group::Group(const std::string& name, const std::list<std::shared_ptr<Media>>& mediaList)
            : std::list<std::shared_ptr<Media>>(mediaList), name(name) {};

std::string Group::getName() const {
    return this->name;
}

std::string Group::getClassName() const {
    return "Group";
}

void Group::showAllMedia(std::ostream& s) const {

    s << "Group: " << this->name << std::endl;
    for (const auto& media : *this) {
        media->show(s);
        s << " ------------------------ " << std::endl;
    }

}

void Group::saveToFile(std::ostream& s) const
{
    s << this->getClassName() << std::endl;
    s << this->name << std::endl;
    s << this->size() << std::endl;
    for (const auto& media : *this) {
        media->saveToFile(s);
    }
}

MediaPtr Group::loadOneMedia(std::istream& s) {
    std::string className;
    std::getline(s, className);

    MediaPtr media = nullptr;

    if (className == "Photo") {
        Photo* p = new Photo();
        p->loadFromFile(s);
        media = MediaPtr(p);
    } else if (className == "Video") {
        Video* v = new Video();
        v->loadFromFile(s);
        media = MediaPtr(v);
    } else if (className == "Film") {
        Film* f = new Film();
        f->loadFromFile(s);
        media = MediaPtr(f);
    }

   return media;
}

void Group::loadFromFile(std::istream& s)
{
    //erase all current media in the group
    this->clear();

    std::getline(s, this->name);
    std::string mediaCountStr;
    std::getline(s, mediaCountStr);
    size_t mediaCount = std::stoul(mediaCountStr);

    
    for (size_t i = 0; i < mediaCount; ++i) {       
        MediaPtr media = loadOneMedia(s);
        if (media) {
            this->push_back(media);
        }
    }
}
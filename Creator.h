#ifndef CREATOR_H
#define CREATOR_H

#include <map>
#include <string>
#include <memory>
#include "Media.h"
#include "Group.h"

typedef std::shared_ptr<Media> MediaPtr;
typedef std::shared_ptr<Group> GroupPtr;

class Creator  {
    private:
        std::map<std::string, MediaPtr> mediaMap;
        std::map<std::string, GroupPtr> groupMap;
    public:
        Creator() = default;
        
        ~Creator() = default;

        void createPhoto(const std::string& title, const std::string& filepath, double latitude, double longitude);

        void createVideo(const std::string& title, const std::string& filepath, double duration);

        void createFilm(const std::string& title, const std::string& filepath, double duration, int chaptersCount, const int* chaptersDurations);

        void createGroup(const std::string& groupName);

        void showMedia(const std::string& title) const;

        void showGroup(const std::string& groupName) const;

        void playMedia(const std::string& title) const;
};




#endif // CREATOR_H
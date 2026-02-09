#ifndef CREATOR_H
#define CREATOR_H

#include <map>
#include <list>
#include <string>
#include <memory>

class Media;
class Group;

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

        void createGroup(const std::string& groupName, const std::list<MediaPtr>& mediaList);

        MediaPtr getPhoto(const std::string& title) const;
        
        MediaPtr getVideo(const std::string& title) const;
        
        MediaPtr getFilm(const std::string& title) const;

        GroupPtr getGroup(const std::string& groupName) const;
    
        bool showMedia(const std::string& title, std::ostream& out) const;

        bool showGroup(const std::string& groupName, std::ostream& out) const;

        bool playMedia(const std::string& title) const;

        void addMediaToGroup(const std::string& title, const std::string& groupName);

        void save(std::ostream& out, std::string& title, std::string& type) const;

        void load(std::istream& in, std::string& type);


};




#endif // CREATOR_H
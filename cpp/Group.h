#ifndef GROUP_H
#define GROUP_H

#include <memory>
#include <list>
#include <string>
#include <iostream>

class Media;
class Photo;
class Video;
class Film;

typedef std::shared_ptr<Media> MediaPtr;

class Group : public std::list<MediaPtr> {
    private:
        std::string name {};

    public:
        Group() = default;

        Group(const std::string& name);

        Group(const std::string& name, const std::list<MediaPtr>& mediaList);

        ~Group() = default;

        std::string getName() const;

        std::string getClassName() const;

        void showAllMedia(std::ostream& s) const;

        void saveToFile(std::ostream& s) const;

        void loadFromFile(std::istream& s);

        static MediaPtr loadOneMedia(std::istream& s);
    };

#endif // GROUP_H
#ifndef GROUP_H
#define GROUP_H

#include <memory>
#include <list>
#include <string>

class Media;

class Group : public std::list<std::shared_ptr<Media>> {
    private:
        std::string name {};

    public:
        Group(const std::string& name);

        Group(const std::string& name, const std::list<std::shared_ptr<Media>>& mediaList);
                
        ~Group() = default;

        std::string getName() const;

        void showAllMedia(std::ostream& s) const;
    };

#endif // GROUP_H
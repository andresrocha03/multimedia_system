#ifndef GROUP_H
#define GROUP_H

#include <list>
#include <string>

class Media;

class Group : public std::list<Media*> {
    private:
        std::string name;
    public:
        Group(const std::string& name);
        
        ~Group() = default;

        std::string getName() const;

        void showAllMedia(std::ostream& s) const;
    };

#endif // GROUP_H
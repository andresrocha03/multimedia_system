#include "Group.h"
#include "Media.h"



Group::Group(const std::string& name) : name(name) {};

std::string Group::getName() const {
    return this->name;
}

void Group::showAllMedia(std::ostream& s) const {
    s << "Group: " << this->name << std::endl;
    for (const auto& media : *this) {
        media->show(s);
        s << "------------------------" << std::endl;
    }
}


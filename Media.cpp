#include <iostream>
#include "Media.h"

Media::Media (std:: string title, std::string filepath) {
    this->title = title;
    this->filepath = filepath;
}

Media::Media() {
    this->title = "untitled";
    this->filepath = "./untitled";
}

Media::~Media() {
    std::cerr << "Media destructor called for " << this->title << std::endl;
}
std::string Media::getTitle() const {
    return this->title;
}

std::string Media::getFilepath() const {
    return this->filepath;
}

void Media::setTitle(std::string newTitle) {
    this->title = newTitle;
}

void Media::setFilepath(std::string newFilepath) {
    this->filepath = newFilepath;
}

void Media::show(std::ostream & s) const {
    s << "Title: " << this->title << std::endl;
    s << "Filepath: " << this->filepath << std::endl;
}


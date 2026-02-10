#include "Video.h"

Video::Video(const std::string& title, const std::string& filepath, 
             const double duration)
    : Media(title, filepath), duration(duration) {
}

Video::Video() : Media() {
    this->duration = 0.0;
}

Video::~Video() = default;

double Video::getDuration() const {
    return this->duration;
}

std::string Video::getClassName() const {
    return  "Video";
}

void Video::setDuration(double duration) {
    this->duration = duration;
}

void Video::show(std::ostream & s) const {
    Media::show(s);
    s << "Duration: " << this->duration << " seconds" << std::endl;
}

void Video::play(std::string path) const {
    if (path.empty()) {
        std::cerr << "Error: Filepath is empty. Cannot play video." << std::endl;
        return;
    }
    
    std::string cmd = "mpv " + path + " &";
    system(cmd.c_str());
}

void Video::saveToFile(std::ostream& s) const
{
    Media::saveToFile(s);
    s << this->duration << std::endl;
}

void Video::loadFromFile(std::istream& s)
{
    Media::loadFromFile(s);
    std::string durationStr;
    std::getline(s, durationStr);
    this->duration = std::stod(durationStr);
}
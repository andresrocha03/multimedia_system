#include "Photo.h"

Photo::Photo( const std::string& title, const std::string& filepath,
              const double lat, const double longi)
    : Media(title, filepath)
{
    this->lat = lat;
    this->longi = longi;
}

Photo::Photo() : Media()
{
    this->lat = 0.0;
    this->longi = 0.0;
}

Photo::~Photo() = default;

double Photo::getLat() const
{
    return this->lat;
}

double Photo::getLong() const
{
    return this->longi;
}

void Photo::setLat(double lat)
{
    this->lat = lat;
}

void Photo::setLong(double longi)
{
    this->longi = longi;
}

void Photo::show(std::ostream &s) const
{
    Media::show(s);
    s << "Latitude: " << this->lat << std::endl;
    s << "Longitude: " << this->longi << std::endl;
}

void Photo::play(std::string path) const 
{  
    std::string cmd = "imagej " + path + " &";
    system(cmd.c_str());
}
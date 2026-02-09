#ifndef PHOTO_H
#define PHOTO_H

#include "Media.h"
#include <string>
#include <iostream>

class Photo : public Media {
    friend class Creator;
    friend class Group;

    private:
        double lat {};
        double longi {};

    protected:
        Photo( const std::string& title, const std::string& filepath, 
                const double lat, const double longi);
        
        Photo();
    
    public:
    
        ~Photo() override;

        double getLat() const;

        double getLong() const;

        std::string getClassName() const override;

        void setLat(double lat);

        void setLong(double longi);

        void show(std::ostream & s) const override;
        
        void play(std::string path) const override;

        void saveToFile(std::ostream& s) const override;

        void loadFromFile(std::istream& s) override;
    };

#endif // PHOTO_H
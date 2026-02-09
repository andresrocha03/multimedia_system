#ifndef VIDEO_H
#define VIDEO_H

#include "Media.h"
#include <string>
#include <iostream>

class Video : public Media {
    friend class Creator;
    friend class Group;


    private:
        double duration {};

    protected:
        Video( const std::string& title, const std::string& filepath, 
               const double duration);
        
        Video();

    public:
        virtual ~Video() override;

        double getDuration() const;

        std::string getClassName() const override;

        void setDuration(double duration);

        virtual void show(std::ostream & s) const override;

        virtual void play(std::string path) const override;

        virtual void saveToFile(std::ostream& s) const override;

        virtual void loadFromFile(std::istream& s) override;
    };

#endif // VIDEO_H
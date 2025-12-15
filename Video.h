#ifndef VIDEO_H
#define VIDEO_H

#include "Media.h"
#include <string>
#include <iostream>

class Video : public Media {
    private:
        double duration {};

    public:
        Video(const std::string& title, const std::string& filepath, 
              const double duration);

        Video();

        ~Video() override;

        double getDuration() const;

        void setDuration(double duration);

        void show(std::ostream & s) const override;

        void play(std::string path) const override;
    };

#endif // VIDEO_H
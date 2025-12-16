#ifndef FILM_H
#define FILM_H

#include "Video.h"
#include <string>

class Film : public Video {
    private:
        int chapters_count {};
        int* chapters_durations {};

    public:
        Film(const std::string title, const std::string filepath, const int chapters_count, const int* chapters_durations);

        Film();

        ~Film() override;

        void show(std::ostream & s) const override;

        void play(std::string path) const override;
};

#endif // FILM_H
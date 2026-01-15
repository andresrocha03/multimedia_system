#ifndef FILM_H
#define FILM_H

#include "Video.h"
#include <string>

class Film : public Video {
    private:
        int chapters_count {};
        int* chapters_durations {};

        void clearChapters();
        void copyChapters(const int* chapters_durations, int count);

    public:
        Film(); 
    
        Film(const std::string& title, const std::string& filepath, const double duration, const int chapters_count, const int* chapters_durations);

        ~Film() override;

        void show(std::ostream & s) const override;
        
        int getChaptersCount() const;

        const int* getChaptersDurations() const;

        int getChapterDuration(int chapter_index) const;

        void setChaptersDuration(const int * chapters_durations, int count);

};

#endif // FILM_H
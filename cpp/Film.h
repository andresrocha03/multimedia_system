#ifndef FILM_H
#define FILM_H

#include "Video.h"
#include <string>

class Film : public Video {
    friend class Creator;
    friend class Group;

    private:
        int chapters_count {};
        int* chapters_durations {};

        void clearChapters();
        void copyChapters(const int* chapters_durations, int count);

    protected:
        Film( const std::string& title, const std::string& filepath, const double duration, const int chapters_count, const int* chapters_durations);

        Film();
    
        Film(const Film& other);

        Film& operator=(const Film& other);

    public:
        ~Film() override;


        void show(std::ostream & s) const override;
        
        int getChaptersCount() const;

        const int* getChaptersDurations() const;

        int getChapterDuration(int chapter_index) const;

        std::string getClassName() const override;

        void setChaptersDuration(const int * chapters_durations, int count);

        void saveToFile(std::ostream& s) const override;

        void loadFromFile(std::istream& s) override;

};

#endif // FILM_H
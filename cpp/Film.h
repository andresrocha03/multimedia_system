#ifndef FILM_H
#define FILM_H

#include "Video.h"
#include <string>

/**
 * @class Film
 * @brief Represents a film composed of multiple chapters.
 *
 * This class extends Video by adding chapter management.
 * Each chapter has a duration and the chapter list is stored as a dynamic array.
 */
class Film : public Video {
    friend class Creator;
    friend class Group;

    private:
        /// Number of chapters.
        int chapters_count {};

        /// Dynamic array holding durations for each chapter.
        int* chapters_durations {};

        /**
         * @brief Clears the chapter array and resets internal state.
         */
        void clearChapters();

        /**
         * @brief Copies chapter durations into internal storage.
         *
         * @param chapters_durations Source array.
         * @param count Number of elements.
         */
        void copyChapters(const int* chapters_durations, int count);

    protected:
        /**
         * @brief Protected constructor used by Creator.
         *
         * @param title Film title.
         * @param filepath Film file path.
         * @param duration Total duration.
         * @param chapters_count Number of chapters.
         * @param chapters_durations Array of chapter durations.
         */
        Film(const std::string& title, const std::string& filepath, const double duration,
             const int chapters_count, const int* chapters_durations);

        /**
         * @brief Default protected constructor.
         */
        Film();

        /**
         * @brief Copy constructor.
         *
         * @param other Source film.
         */
        Film(const Film& other);

        /**
         * @brief Copy assignment operator.
         *
         * @param other Source film.
         * @return Reference to current object.
         */
        Film& operator=(const Film& other);

    public:
        /**
         * @brief Destructor.
         *
         * Responsible for releasing dynamic chapter storage.
         */
        ~Film() override;

        /**
         * @brief Displays information about the film.
         *
         * @param s Output stream.
         */
        void show(std::ostream & s) const override;

        /**
         * @brief Returns the number of chapters.
         *
         * @return Chapter count.
         */
        int getChaptersCount() const;

        /**
         * @brief Returns a pointer to the chapter durations array.
         *
         * @return Pointer to chapter durations (internal storage).
         */
        const int* getChaptersDurations() const;

        /**
         * @brief Returns the duration of a specific chapter.
         *
         * @param chapter_index Index of the chapter.
         * @return Chapter duration.
         */
        int getChapterDuration(int chapter_index) const;

        /**
         * @brief Returns the class name.
         *
         * @return Class name string.
         */
        std::string getClassName() const override;

        /**
         * @brief Sets the chapter durations array.
         *
         * @param chapters_durations Array of chapter durations.
         * @param count Number of chapters.
         */
        void setChaptersDuration(const int * chapters_durations, int count);

        /**
         * @brief Saves film data to a stream.
         *
         * @param s Output stream.
         */
        void saveToFile(std::ostream& s) const override;

        /**
         * @brief Loads film data from a stream.
         *
         * @param s Input stream.
         */
        void loadFromFile(std::istream& s) override;
};

#endif // FILM_H

#include "Film.h"

Film::Film(const std::string title, const std::string filepath, const int chapters_count, const int* chapters_durations)
    : Video(title, filepath, 0.0), chapters_count(chapters_count){
    this->chapters_durations = new int[chapters_count];
    copyChapters(chapters_durations, chapters_count);
}

Film::Film() : Video(), chapters_count(0) {
    this->chapters_durations = nullptr;
}

Film::~Film() {
    clearChapters();
}

void Film::copyChapters(const int * chapters_durations, int count) {
    this->chapters_count = count;
    for (int i=0; i<count; i++){
        this->chapters_durations[i] = chapters_durations[i];
    }
}

void Film::clearChapters() {
    if (this->chapters_durations != nullptr) {
        delete[] this->chapters_durations;
        this->chapters_durations = nullptr;
    }
    this->chapters_count = 0;
}

void Film::show() {
    Video::show();
    std::cout << "Chapters count: " << this->chapters_count << std::endl;
    std::cout << "Chapters durations: ";
    for (int i = 0; i < this->chapters_count; i++) {
        std::cout << this->chapters_durations[i] << " ";
    }
    std::cout << std::endl;
}

int Film::getChaptersCount() const {
    return this->chapters_count;
}

const int* Film::getChaptersDurations() const {
    return this->chapters_durations;
}

int Film::getChapterDuration(int chapter_index) const {
    if (chapter_index < 0 || chapter_index >= this->chapters_count) {
        throw std::out_of_range("Chapter index out of range");
    }
    return this->chapters_durations[chapter_index];
}

void Film::setChaptersDuration(const int * chapters_durations, int count) {
    clearChapters();
    this->chapters_durations = new int[count];
    copyChapters(chapters_durations, count);
}


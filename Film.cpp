#include "Film.h"

Film::Film(const std::string& title, const std::string& filepath, const double duration, const int chapters_count, const int* chapters_durations)
    : Video(title, filepath, duration), chapters_count(chapters_count)

{
    copyChapters(chapters_durations, chapters_count);
}

Film::Film() : Video(), chapters_count(0) {
    this->chapters_durations = nullptr;
}

Film::~Film() {
    clearChapters();
}

Film::Film(const Film& other)
  : Video(other), chapters_count(0), chapters_durations(nullptr)
{
  copyChapters(other.chapters_durations, other.chapters_count);
}

void Film::copyChapters(const int * chapters_durations, int count) {
    this->chapters_durations = new int[count];
    this->chapters_count = count;
    for (int i=0; i<count; i++){
        this->chapters_durations[i] = chapters_durations[i];
    }
}

Film& Film::operator=(const Film& other) {
  if (this == &other) return *this;

  Video::operator=(other);      // important: copy base class too

  clearChapters();
  copyChapters(other.chapters_durations, other.chapters_count);

  return *this;
}

void Film::clearChapters() {
    if (this->chapters_durations != nullptr) {
        delete[] this->chapters_durations;
        this->chapters_durations = nullptr;
    }
    this->chapters_count = 0;
}

void Film::show(std::ostream & s) const {
    Video::show(s);
    s << "Chapters Count: " << this->chapters_count << std::endl; 
    s << "Chapters Durations: ";
    for (int i = 0; i < this->chapters_count; i++) {
        s << this->chapters_durations[i];
        if (i < this->chapters_count - 1) {
            s << ", ";
        }
    }
    s << std::endl;
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
    //first, clear existing chapters
    clearChapters();

    // in case the input is null or count is non-positive
    if (chapters_durations == nullptr || count <= 0) {
        this->chapters_durations = nullptr;
        this->chapters_count = 0;
        return;
    }

    copyChapters(chapters_durations, count);
}


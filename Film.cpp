#include "Film.h"

Film::Film(const std::string title, const std::string filepath, const int chapters_count, const int* chapters_durations)
    : Video(title, filepath, 0.0), chapters_count(chapters_count)
{
    this->chapters_durations = new int[chapters_count];
    for (int i = 0; i < chapters_count; i++) {
        this->chapters_durations[i] = chapters_durations[i];
        // Update total duration in Video
        setDuration(getDuration() + chapters_durations[i]);
    }
}
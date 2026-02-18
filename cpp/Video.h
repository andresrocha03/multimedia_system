#ifndef VIDEO_H
#define VIDEO_H

#include "Media.h"
#include <string>
#include <iostream>

/**
 * @class Video
 * @brief Represents a video media with a duration.
 *
 * This class derives from Media and adds a duration attribute.
 * It provides implementations for showing, playing and serialization.
 */
class Video : public Media {
    friend class Creator;
    friend class Group;

    private:
        /// Duration of the video.
        double duration {};

    protected:
        /**
         * @brief Protected constructor used by Creator.
         *
         * @param title Video title.
         * @param filepath Video file path.
         * @param duration Video duration.
         */
        Video( const std::string& title, const std::string& filepath,
               const double duration);

        /**
         * @brief Default protected constructor.
         */
        Video();

    public:
        /**
         * @brief Virtual destructor.
         */
        virtual ~Video() override;

        /**
         * @brief Returns the duration.
         *
         * @return Duration value.
         */
        double getDuration() const;

        /**
         * @brief Returns the class name.
         *
         * @return Class name string.
         */
        std::string getClassName() const override;

        /**
         * @brief Sets the duration.
         *
         * @param duration New duration value.
         */
        void setDuration(double duration);

        /**
         * @brief Displays information about the video.
         *
         * @param s Output stream.
         */
        virtual void show(std::ostream & s) const override;

        /**
         * @brief Plays the video using the provided path.
         *
         * @param path File path to play.
         * @return true if playback succeeds, false otherwise.
         */
        virtual bool play(std::string path) const override;

        /**
         * @brief Saves video data to a stream.
         *
         * @param s Output stream.
         */
        virtual void saveToFile(std::ostream& s) const override;

        /**
         * @brief Loads video data from a stream.
         *
         * @param s Input stream.
         */
        virtual void loadFromFile(std::istream& s) override;
};

#endif // VIDEO_H

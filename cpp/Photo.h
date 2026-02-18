#ifndef PHOTO_H
#define PHOTO_H

#include "Media.h"
#include <string>
#include <iostream>

/**
 * @class Photo
 * @brief Represents a photo media with GPS coordinates.
 *
 * This class derives from Media and adds latitude and longitude attributes.
 * It provides implementations for displaying, playing and serialization.
 */
class Photo : public Media {
    friend class Creator;
    friend class Group;

    private:
        /// Latitude coordinate.
        double lat {};

        /// Longitude coordinate.
        double longi {};

    protected:
        /**
         * @brief Protected constructor used by Creator.
         *
         * @param title Photo title.
         * @param filepath Photo file path.
         * @param lat Latitude coordinate.
         * @param longi Longitude coordinate.
         */
        Photo(const std::string& title, const std::string& filepath,
              const double lat, const double longi);

        /**
         * @brief Default protected constructor.
         */
        Photo();

    public:
        /**
         * @brief Destructor.
         */
        ~Photo() override;

        /**
         * @brief Returns the latitude.
         *
         * @return Latitude value.
         */
        double getLat() const;

        /**
         * @brief Returns the longitude.
         *
         * @return Longitude value.
         */
        double getLong() const;

        /**
         * @brief Returns the class name.
         *
         * @return Class name string.
         */
        std::string getClassName() const override;

        /**
         * @brief Sets the latitude.
         *
         * @param lat New latitude value.
         */
        void setLat(double lat);

        /**
         * @brief Sets the longitude.
         *
         * @param longi New longitude value.
         */
        void setLong(double longi);

        /**
         * @brief Displays information about the photo.
         *
         * @param s Output stream.
         */
        void show(std::ostream & s) const override;

        /**
         * @brief Plays the photo (typically by opening it).
         *
         * @param path File path to open.
         * @return true if opening succeeds, false otherwise.
         */
        bool play(std::string path) const override;

        /**
         * @brief Saves photo data to a stream.
         *
         * @param s Output stream.
         */
        void saveToFile(std::ostream& s) const override;

        /**
         * @brief Loads photo data from a stream.
         *
         * @param s Input stream.
         */
        void loadFromFile(std::istream& s) override;
};

#endif // PHOTO_H

#ifndef MEDIA_H
#define MEDIA_H

#include <iostream>

/**
 * @class Media
 * @brief Abstract base class representing a generic multimedia object.
 *
 * This class defines the common interface shared by all media types
 * (Photo, Video, Film). It stores a title and a file path and provides
 * virtual methods for displaying, playing, saving and loading media.
 */
class Media {
    private:
        /// Title of the media object
        std::string title {};
        
        /// File path of the media object
        std::string filepath {};

    public:

        /**
         * @brief Constructs a Media object with a title and file path.
         * 
         * @param title Title of the media.
         * @param filepath Path to the media file.
         */
        Media(const std::string title, const std::string filepath);

        /**
         * @brief Default constructor.
         */
        Media();

        /**
         * @brief Virtual destructor.
         */
        virtual ~Media();

        /**
         * @brief Returns the title of the media.
         * 
         * @return Title string.
         */
        virtual std::string getTitle() const;
         
        /**
         * @brief Returns the file path of the media.
         * 
         * @return File path string.
         */
        virtual std::string getFilepath() const;

        /**
         * @brief Returns the class name of the media type.
         * 
         * Pure virtual function implemented by derived classes.
         * 
         * @return Class name as string.
         */
        virtual std::string getClassName() const = 0;

        /**
         * @brief Sets a new title for the media.
         * 
         * @param newTitle New title value.
         */
        virtual void setTitle(std::string newTitle);

        /**
         * @brief Sets a new file path for the media.
         * 
         * @param newFilepath New file path value.
         */
        virtual void setFilepath(std::string newFilepath);

        /**
         * @brief Displays media information to the output stream.
         * 
         * @param s Output stream.
         */
        virtual void show(std::ostream & s) const;

        /**
         * @brief Plays the media.
         * 
         * Pure virtual function implemented by derived classes.
         * 
         * @param path Path of the media file.
         * @return true if playback succeeds, false otherwise.
         */
        virtual bool play(std::string path) const = 0;

        /**
         * @brief Saves the media data to an output stream.
         * 
         * @param s Output stream.
         */
        virtual void saveToFile(std::ostream& s) const;

        /**
         * @brief Loads the media data from an input stream.
         * 
         * @param s Input stream.
         */
        virtual void loadFromFile(std::istream& s);
};

#endif // MEDIA_H

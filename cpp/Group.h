#ifndef GROUP_H
#define GROUP_H

#include <memory>
#include <list>
#include <string>
#include <iostream>

/**
 * @class Media
 * @brief Forward declaration of the Media base class.
 */
class Media;
class Photo;
class Video;
class Film;

/**
 * @typedef MediaPtr
 * @brief Shared pointer type for Media objects.
 */
typedef std::shared_ptr<Media> MediaPtr;

/**
 * @class Group
 * @brief Represents a named group of Media objects.
 *
 * This class inherits from std::list<MediaPtr> and adds a name field.
 * It provides helper methods for displaying and serializing group contents.
 */
class Group : public std::list<MediaPtr> {
    private:
        /// Name of the group.
        std::string name {};

    public:
        /**
         * @brief Default constructor.
         */
        Group() = default;

        /**
         * @brief Constructs a group with a name.
         *
         * @param name Group name.
         */
        Group(const std::string& name);

        /**
         * @brief Constructs a group with a name and initial media list.
         *
         * @param name Group name.
         * @param mediaList Initial list of media elements.
         */
        Group(const std::string& name, const std::list<MediaPtr>& mediaList);

        /**
         * @brief Default destructor.
         */
        ~Group() = default;

        /**
         * @brief Returns the group name.
         *
         * @return Group name.
         */
        std::string getName() const;

        /**
         * @brief Returns the class name for identification purposes.
         *
         * @return Class name string.
         */
        std::string getClassName() const;

        /**
         * @brief Displays all media contained in the group.
         *
         * @param s Output stream.
         */
        void showAllMedia(std::ostream& s) const;

        /**
         * @brief Saves the group content to a stream.
         *
         * @param s Output stream.
         */
        void saveToFile(std::ostream& s) const;

        /**
         * @brief Loads the group content from a stream.
         *
         * @param s Input stream.
         */
        void loadFromFile(std::istream& s);

        /**
         * @brief Loads a single Media object from a stream.
         *
         * This method is responsible for instantiating the correct derived
         * type based on data read from the stream.
         *
         * @param s Input stream.
         * @return Shared pointer to the loaded media object.
         */
        static MediaPtr loadOneMedia(std::istream& s);
};

#endif // GROUP_H

#ifndef CREATOR_H
#define CREATOR_H

#include <map>
#include <list>
#include <string>
#include <memory>

/**
 * @class Media
 * @brief Forward declaration of the Media base class.
 */
class Media;

/**
 * @class Group
 * @brief Forward declaration of the Group class.
 */
class Group;

/**
 * @typedef MediaPtr
 * @brief Shared pointer type for Media objects.
 */
typedef std::shared_ptr<Media> MediaPtr;

/**
 * @typedef GroupPtr
 * @brief Shared pointer type for Group objects.
 */
typedef std::shared_ptr<Group> GroupPtr;

/**
 * @class Creator
 * @brief Factory and manager for multimedia objects and groups.
 *
 * This class centralizes the creation of Photo, Video and Film objects and
 * stores them in associative containers for fast retrieval by name/title.
 * It also manages groups that contain lists of Media objects.
 */
class Creator  {
    private:
        /// Map storing media objects indexed by title.
        std::map<std::string, MediaPtr> mediaMap;

        /// Map storing groups indexed by group name.
        std::map<std::string, GroupPtr> groupMap;

    public:
        /**
         * @brief Default constructor.
         */
        Creator() = default;

        /**
         * @brief Default destructor.
         */
        ~Creator() = default;

        /**
         * @brief Creates and stores a Photo object.
         *
         * @param title Title used as key in the media map.
         * @param filepath File path of the photo.
         * @param latitude Latitude coordinate.
         * @param longitude Longitude coordinate.
         */
        void createPhoto(const std::string& title, const std::string& filepath, double latitude, double longitude);

        /**
         * @brief Creates and stores a Video object.
         *
         * @param title Title used as key in the media map.
         * @param filepath File path of the video.
         * @param duration Duration in seconds (or chosen time unit).
         */
        void createVideo(const std::string& title, const std::string& filepath, double duration);

        /**
         * @brief Creates and stores a Film object.
         *
         * A film is a video composed of chapters with individual durations.
         *
         * @param title Title used as key in the media map.
         * @param filepath File path of the film.
         * @param duration Total duration.
         * @param chaptersCount Number of chapters.
         * @param chaptersDurations Pointer to an array containing chapter durations.
         */
        void createFilm(const std::string& title, const std::string& filepath, double duration, int chaptersCount, const int* chaptersDurations);

        /**
         * @brief Creates and stores a Group object.
         *
         * @param groupName Group name used as key in the group map.
         * @param mediaList List of media objects included in the group.
         */
        void createGroup(const std::string& groupName, const std::list<MediaPtr>& mediaList);

        /**
         * @brief Retrieves a Photo by title.
         *
         * @param title Photo title.
         * @return Shared pointer to the media object (may be null if not found).
         */
        MediaPtr getPhoto(const std::string& title) const;

        /**
         * @brief Retrieves a Video by title.
         *
         * @param title Video title.
         * @return Shared pointer to the media object (may be null if not found).
         */
        MediaPtr getVideo(const std::string& title) const;

        /**
         * @brief Retrieves a Film by title.
         *
         * @param title Film title.
         * @return Shared pointer to the media object (may be null if not found).
         */
        MediaPtr getFilm(const std::string& title) const;

        /**
         * @brief Retrieves a Group by name.
         *
         * @param groupName Group name.
         * @return Shared pointer to the group (may be null if not found).
         */
        GroupPtr getGroup(const std::string& groupName) const;

        /**
         * @brief Displays a media object by title.
         *
         * @param title Media title.
         * @param out Output stream used to print information.
         * @return true if found, false otherwise.
         */
        bool showMedia(const std::string& title, std::ostream& out) const;

        /**
         * @brief Displays a group by name.
         *
         * @param groupName Group name.
         * @param out Output stream used to print information.
         * @return true if found, false otherwise.
         */
        bool showGroup(const std::string& groupName, std::ostream& out) const;

        /**
         * @brief Displays the list of all groups stored in the group map.
         *
         * @param out Output stream used to print information.
         * @return true if at least one group exists, false otherwise.
         */
        bool showGroupMap(std::ostream& out) const;

        /**
         * @brief Displays the list of all media stored in the media map.
         *
         * @param out Output stream used to print information.
         * @return true if at least one media exists, false otherwise.
         */
        bool showMediaMap(std::ostream& out) const;

        /**
         * @brief Plays a media object by title.
         *
         * @param title Media title.
         * @return true if found and played, false otherwise.
         */
        bool playMedia(const std::string& title) const;

        /**
         * @brief Adds a media object to a group.
         *
         * @param title Media title.
         * @param groupName Group name.
         */
        void addMediaToGroup(const std::string& title, const std::string& groupName);

        /**
         * @brief Saves an object (media or group) to an output stream.
         *
         * The behavior depends on the provided type value.
         *
         * @param out Output stream.
         * @param title Object identifier.
         * @param type Object type (e.g. "Photo", "Video", "Film", "Group").
         */
        void save(std::ostream& out, std::string& title, std::string& type) const;

        /**
         * @brief Loads objects from an input stream.
         *
         * @param in Input stream.
         */
        void load(std::istream& in);
};

#endif // CREATOR_H

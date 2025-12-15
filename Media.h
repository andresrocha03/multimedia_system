#ifndef MEDIA_H
#define MEDIA_H

#include <string>
#include <iostream>

class Media {
    private:
        std::string title {};
        std::string filepath {};

    public:
        Media(const std::string title, const std::string filepath);

        Media();

        virtual ~Media();

        virtual std::string getTitle() const;
         
        virtual std::string getFilepath() const;

        virtual void setTitle(std::string newTitle);

        virtual void setFilepath(std::string newFilepath);

        virtual void show(std::ostream & s) const;

        virtual void play(std::string path) const = 0;
    };

#endif // MEDIA_H
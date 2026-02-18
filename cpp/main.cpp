#include "Media.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Group.h"
#include "Creator.h"
#include "tcpserver.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <memory>


const int PORT = 3331;

typedef std::shared_ptr<Media> MediaPtr;
typedef std::shared_ptr<Group> GroupPtr;

static std::string oneLine(std::string s) {
    for (char& c : s) if (c == '\n' || c == '\r') c = ' ';
    return s;
}

int main(int argc, const char* argv[])
{    
    // // New creator
    Creator creator = Creator();
    
    // // Testing creator
    std::string path = "path/to/media.jpg";
    
    creator.createPhoto("Photo1", path, 48.8566, 2.3522);
    creator.createPhoto("Photo2", path, 34.0522, -118.2437);
    creator.createVideo("Video1", path, 150.0);
    int* chapters = new int[3]{60, 90, 150};
    creator.createFilm("Film1", path, 300.0, 3, chapters);
    delete[] chapters;
    
    // Create groups
    std::list<MediaPtr> group1Media = {creator.getPhoto("Photo1"), creator.getPhoto("Photo2")};
    creator.createGroup("Group1", group1Media);
    
    std::list<MediaPtr> group2Media = {creator.getVideo("Video1"), creator.getFilm("Film1")};
    creator.createGroup("Group2", group2Media);
    
    
    // Create the TCPServer
    auto* server = new TCPServer([&](std::string const& request, std::string& response) {
        std::cout << "request: " << request << std::endl;

        std::stringstream ss(request);
        std::string cmd;
        ss >> cmd;

        if (cmd == "SHOW") {
            std::string what;
            ss >> what; 
            if (what == "GROUP") {
                std::stringstream out;
                creator.showGroupMap(out);
                response = oneLine(out.str());
                return true;
            }

            if (what == "MEDIA") {
                std::stringstream out;
                creator.showMediaMap(out);
                response = oneLine(out.str());
                return true;
            }
        }
        if (cmd == "SEARCH") {
            std::string name;
            ss >> name;
            if (name.empty()) {
                response = "ERROR missing name";
                return true;
            }

            std::stringstream out;
            bool ok = creator.showGroup(name, out);
            bool okMedia = creator.showMedia(name, out);
            ok = ok || okMedia;  
            response = ok ? oneLine(out.str()) : "NOT_FOUND " + name;
            return true;
        }

        if (cmd == "PLAY") {
            std::string name;
            ss >> name;
            if (name.empty()) {
                response = "ERROR missing name";
                return true;
            }

            bool ok = creator.playMedia(name);
            response = ok ? ("OK PLAY " + name) : ("NOT_FOUND " + name);
            return true;
        }

        if (cmd == "SAVE") {
            std::string name;
            std::string type;
            
            ss >> name >> type;
            if (name.empty() || type.empty()) {
                response = "ERROR missing name or type";
                return true;
            }

            std::ofstream outFile(type + "_" + name + ".txt");
            creator.save(outFile, name, type);
            response = "OK SAVED " + name + " of type " + type;
            return true;
        }

         if (cmd == "LOAD") {
            std::string path;

            ss >> path;
            if (path.empty()) {
                response = "ERROR missing path";
                return true;
            }

            std::ifstream inFile(path);
            creator.load(inFile);
            response = "OK LOADED ";
            return true;
        }

        if (cmd == "HELP") {
            response = "Commands:   SEARCH <title> | PLAY <title> | SAVE <title> <type> | LOAD <path> | SHOW GROUP MAP | SHOW MEDIA MAP | EXIT";
            return true;
        }

        
        if (cmd == "EXIT") {
            response = "OK BYE";
            return false; // signal to close connection
        }



        response = "ERROR unknown command";
        return true;
    });

    // Run server loop
    std::cout << "Starting Server on port " << PORT << std::endl;
    int status = server->run(PORT);
    
    // Clean up
    delete server; 

    if (status < 0) {
        std::cerr << "Could not start Server on port " << PORT << std::endl;
        return 1;
    }
    return 0;
    
}



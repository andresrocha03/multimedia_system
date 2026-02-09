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
    // New creator
    Creator creator1 = Creator();
    
    // Testing creator
    std::string path_photo = "/home/andre/Documentos/utensiles.jpeg";
    std::string path_video = "/home/andre/Documentos/myvideo.mp4";
    
    creator1.createPhoto("P1", path_photo, 48.8566, 2.3522);
    creator1.createPhoto("P2", path_photo, 34.0522, -118.2437);
    creator1.createVideo("V1", path_video, 150.0);
    creator1.createFilm("F1", path_video, 300.0, 3, new int[3]{60, 90, 150});
    
    // Create groups
    std::list<MediaPtr> group1Media = {creator1.getPhoto("P1"), creator1.getPhoto("P2")};
    creator1.createGroup("Group1", group1Media);
    
    std::list<MediaPtr> group2Media = {creator1.getVideo("V1"), creator1.getFilm("F1")};
    creator1.createGroup("Group2", group2Media);
    
    
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
                creator1.showGroupMap(out);
                response = oneLine(out.str());
                return true;
            }

            if (what == "MEDIA") {
                std::stringstream out;
                creator1.showMediaMap(out);
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
            bool ok = creator1.showGroup(name, out);
            bool okMedia = creator1.showMedia(name, out);
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

            bool ok = creator1.playMedia(name);
            response = ok ? ("OK PLAY " + name) : ("NOT_FOUND " + name);
            return true;
        }

        if (cmd == "SAVE") {
            std::string name;
            std::string type;
            
            ss >> type >> name;
            if (name.empty() || type.empty()) {
                response = "ERROR missing name or type";
                return true;
            }

            // std::ofstream outFile(type + "_" + name + ".txt");
            std::stringstream outFile;
            creator1.save(outFile, name, type);
            std::cout << outFile.str() << std::endl; // For debugging, print the saved content
            response = "OK SAVED " + name + " of type " + type;
            return true;
        }

         if (cmd == "LOAD") {
            std::string type;
            std::string path;

            ss >> type  >> path;
            if (type.empty() || path.empty()) {
                response = "ERROR missing type or path";
                return true;
            }

            std::ifstream inFile(path);
            creator1.load(inFile, type);
            return true;
        }

        if (cmd == "HELP") {
            response = "Commands:   SEARCH <name> | PLAY <name> | SAVE <name> <type> | LOAD <type> | SHOW GROUP MAP | SHOW MEDIA MAP | EXIT";
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
    if (status < 0) {
        std::cerr << "Could not start Server on port " << PORT << std::endl;
        return 1;
    }
    return 0;
    
}



#include "App.h"
#include "FileManager.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace NDAVis;
int numfile;

int main() {
    NDAVis::FileManager fm;
    numfile = fm.getNumberOfFiles();
    //Name Of the Files that are preprocessed
    std::vector<std::string> fileNames;
    fm.getFileNames(&fileNames);
    
    /* ws->getUserData returns one of these */
    struct PerSocketData {
        /* Fill with user data */
    };

    uWS::App().ws<PerSocketData>("/*", {
        /* Settings */
        .compression = uWS::DEDICATED_COMPRESSOR_256KB,
        .maxPayloadLength = 256 * 1024 * 1024,
        .open = [](auto * ws) {
            std::cout << "Dummy Client Connected" << std::endl;
            std::cout << ws->getRemoteAddressAsText() << std::endl;
           
            //std::cout << numberOfFiles << std::endl;
            /* Open event here, you may access ws->getUserData() which points to a PerSocketData struct */
        },
        .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
            std::cout << message << std::endl;
            ws->send(message, opCode, true);
            std::string s = std::to_string(numfile);
            ws->send(s, opCode, true);
        },
        .drain = [](auto */*ws*/) {
            /* Check ws->getBufferedAmount() here */
        },
        .ping = [](auto */*ws*/, std::string_view) {
            /* Not implemented yet */
        },
        .pong = [](auto */*ws*/, std::string_view) {
            /* Not implemented yet */
        },
        .close = [](auto */*ws*/, int /*code*/, std::string_view /*message*/) {
            /* You may access ws->getUserData() here */
        }
    }).listen("0.0.0.0", 9000, [](auto *listen_socket) {
        if (listen_socket) {
            std::cout << "Listening on port " << 9000 << std::endl;
        }
    }).run();
    
}
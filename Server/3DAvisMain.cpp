#include "VtkVisul.h"
#include "vtkAutoInit.h"
#include "FileManager.h"
#include "Server.h"
#include "Compression.h"
#include <string>
#include <vector>
#include <iostream>
#include <charconv>
#include <nlohmann/json.hpp>
#include <typeinfo>
#include <cmath>
#include <algorithm>
#include <vtkRayCastImageDisplayHelper.h>



using json = nlohmann::json;
using namespace NDAVis;

FileManager fileManager;
Compression compression;
const std::string WHITESPACE = " \n\r\t\f\v";

std::string trim (const std::string &s) {
    size_t pos = s.find_last_not_of(WHITESPACE);
    return (pos == std::string::npos) ? "" : s.substr(0, pos+1);
}

void onConnect (uWS::WebSocket<false, true, NDAVis::Server::PerSocketData>* ws) {
    std::cout << "Client Connected" << std::endl;
    std::cout << ws->getRemoteAddressAsText() << std::endl;
    auto socketData = ws->getUserData();
    if (!socketData) {std::cout << "Does not exist" <<std::endl; }

    std::vector<std::string> fileNames;
    fileManager.getFileNames(&fileNames);

    json j;
    j["numberOfFiles"] = fileManager.getNumberOfFiles();
    j["files"] = {};
    for (auto it = fileNames.begin(); it != fileNames.end(); it++) {
        j["files"].push_back((*it));
    }
    ws->send(j.dump(), uWS::OpCode::TEXT, true);    
}

void onMessage(uWS::WebSocket<false, true, NDAVis::Server::PerSocketData>* ws, std::string_view message, uWS::OpCode opCode) {
    json j = json::parse(message);
    std::cout << message << std::endl;
    std::string jType = j["type"].dump();
    jType =jType.substr(1, (jType.length()-2));
    if (jType == "file") {
        /* code after client selects file */
    }
    else if (jType == "volume") {
        /* code for cubes needed for interaction process */
    }
    else if (jType == "image") {
        /* code for image needed at camera position same way as client */
    }
    else {
        std::cout << "JSON message received of invalid format" << std::endl;
    }
     
}

/* VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingOpenGL2);  */
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
int main()
{
    uWS::App().ws<NDAVis::Server::PerSocketData>("/*", (uWS::App::WebSocketBehavior<NDAVis::Server::PerSocketData>){
            /* Settings */
            .compression = uWS::DEDICATED_COMPRESSOR_256KB,
            .maxPayloadLength = 256 * 1024 * 1024,
            .open = onConnect,
            .message = onMessage,
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
    

    return 0;


}
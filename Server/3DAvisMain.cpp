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
        j["files"].push_back(trim(*it));
    }
    ws->send(j.dump(), uWS::OpCode::TEXT, true);    
}

void onMessage(uWS::WebSocket<false, true, NDAVis::Server::PerSocketData>* ws, std::string_view message, uWS::OpCode opCode) {
    std::string msg {message};
    msg.erase(std::remove(msg.begin(), msg.end(), '\\'), msg.end());
    msg = msg.substr(1, (msg.length()-2));
    json j = json::parse(msg);

    switch (j["type"])
    {
    case "file":
        /* code */
        break;
    case "volume":
        /* code */
        break;
    case "image":
        /* code */
        break;
    default:
        std::cout << "JSON message received of invalid format" << std::endl;
        break;
    }
}

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
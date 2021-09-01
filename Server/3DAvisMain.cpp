#include "LogKeeper.h"
#include "FileManager.h"
#include "Server.h"
#include <string>
#include <vector>
#include <iostream>
#include <charconv>
#include <nlohmann/json.hpp>
#include <typeinfo>

using json = nlohmann::json;
using namespace NDAVis;

FileManager fileManager;

void onConnect (uWS::WebSocket<false, true, NDAVis::Server::PerSocketData>* ws) {
    std::cout << "Client Connected" << std::endl;
    std::cout << ws->getRemoteAddressAsText() << std::endl;

    auto socketData = ws->getUserData();
    if (!socketData) {std::cout << "Does not exist" <<std::endl; }

    int numberOfFiles = fileManager.getNumberOfFiles();
    std::string numFiles = "Number of Files: " + std::to_string(numberOfFiles) + "\n";
    std::vector<std::string> fileNames;
    fileManager.getFileNames(&fileNames);
    int index = 0;
    for (auto it = fileNames.begin(); it != fileNames.end(); it++)
    {
        numFiles += "(" + std::to_string(index +1) + ") " + *it + "\n";
        index++;
    }

    /*json j =
    {
        {"pi", 3.141},
        {"happy", true},
        {"name", "Niels"},
        {"nothing", nullptr},
        {
            "answer", {
                {"everything", 42}
            }
        },
        {"list", {1, 0, 2}},
        {
            "object", {
                {"currency", "USD"},
                {"value", 42.99}
            }
        }
    };

    std::cout << j["list"][1] << std::endl;*/


    ws->send(numFiles, uWS::OpCode::TEXT, true);
}

void onMessage(uWS::WebSocket<false, true, NDAVis::Server::PerSocketData>* ws, std::string_view message, uWS::OpCode opCode) {
    /*int fileChoice;
    auto res = std::from_chars(message.data(), message.data() + message.size(), fileChoice);
    if (fileChoice <= fileManager.getNumberOfFiles()) {
        //choose from file
        std::cout << "File selected for Rendering: "<< fileChoice <<std::endl;
    }*/
    //auto res = std::from_chars(message.data(), message.data() + message.size(), fileChoice);

    /*std::string msg {message};
    msg.erase(std::remove(msg.begin(), msg.end(), '\\'), msg.end());
    msg = msg.substr(1, (msg.length()-2));
    std::cout << msg << std::endl;
    json v = json::parse(msg);
    std::cout << v["age"] <<std::endl;*/

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
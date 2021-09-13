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

    int numberOfFiles = fileManager.getNumberOfFiles();
    std::vector<std::string> fileNames;
    fileManager.getFileNames(&fileNames);

    json j;
    j["numberOfFiles"] = numberOfFiles;
    j["files"] = {};
    for (auto it = fileNames.begin(); it != fileNames.end(); it++) {
        j["files"].push_back(trim(*it));
    }
    ws->send(j.dump(), uWS::OpCode::TEXT, true);
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


    
}

void onMessage(uWS::WebSocket<false, true, NDAVis::Server::PerSocketData>* ws, std::string_view message, uWS::OpCode opCode) {
    /*int fileChoice;
    auto res = std::from_chars(message.data(), message.data() + message.size(), fileChoice);
    if (fileChoice <= fileManager.getNumberOfFiles()) {
        //choose from file
        std::cout << "File selected for Rendering: "<< fileChoice <<std::endl;
    }*/
    //auto res = std::from_chars(message.data(), message.data() + message.size(), fileChoice);

    std::string msg {message};
    msg.erase(std::remove(msg.begin(), msg.end(), '\\'), msg.end());
    msg = msg.substr(1, (msg.length()-2));
    json j = json::parse(msg);
    //std::cout << msg << std::endl;
    //std::cout << v["camera_pos"][0] <<std::endl;

}

int main()
{
    
    float* arr = new float[64*64*64];
    float* ptr = arr;
    for (int i = 0; i < 262144; i++)
    {
        *ptr = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        ptr++;
    }

    std::vector<char> compressed_data;
    size_t compressed_size = 0;

    auto status = compression.compress(arr, compressed_data, compressed_size, 64, 64, 64, 12);
    compressed_data.resize(compressed_size);
    std::string s = compression.to_base64(reinterpret_cast<char*>(compressed_data.data()), compressed_size);
    //std::cout << s;

    //int status = compression.compress(arr,64,64,64,12);
    //std::cout << status;
    /*for (int i=0;i<10;i++) {
        std::cout << arr[i] <<std::endl;
    }*/
    

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
#include "LogKeeper.h"
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
    //float arr [] = {0.00117518, 0.00728933, 0.00530866, 0.00625596, 0.00565312, 0.0040169, 0.00436136, 0.00487814, 0.00565312, 0.0145229, 0.0177091, 
    //	            0.00548098, 0.00487814, 0.000658589, 0.0049642, 0.0226177, 0.0794531, 0.0689472, 0.00444761, 0.00677274, 0.00453368, 0.0111644, 
    //                0.0983982, 0.0971927, 0.00668649, 0.00703094, 0.00384477, 0.0629191, 0.0606803, 0.0101311, 0.00479207, 0.00367245, 0.00505027, 0.00306978, 
    //                .001, 0.2}
    
    float* arr = new float[4*4*4];
    float* ptr = arr;
    for (int i = 0; i < 64; i++)
    {
        *ptr = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        ptr++;
    }

    std::vector<char> compressed_data;
    size_t compressed_size = 0;

    for (int i=0;i<10;i++) {
        std::cout << arr[i] <<std::endl;
    }

    auto status = compression.compress(arr, compressed_data, compressed_size, 4, 4, 4, 12);
    compressed_data.resize(compressed_size);
    std::string s = compression.to_base64(reinterpret_cast<char*>(compressed_data.data()), compressed_size);
    std::cout << s;

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
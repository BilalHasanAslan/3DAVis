#include "VtkVisul.h"
#include "vtkAutoInit.h"
#include "FileManager.h"
#include "Server.h"
#include "Compression.h"
#include "Controller.h"
#include <string>
#include <vector>
#include <iostream>
#include <charconv>
#include <nlohmann/json.hpp>
#include <typeinfo>
#include <cmath>
#include <algorithm>
#include <vtkRayCastImageDisplayHelper.h>
#include <vtkUnsignedCharArray.h>

using json = nlohmann::json;
using namespace NDAVis;

FileManager fileManager;
Compression compression;
NDAVis::Controller controller = Controller();
const std::string WHITESPACE = " \n\r\t\f\v";

std::string trim(const std::string &s)
{
    size_t pos = s.find_last_not_of(WHITESPACE);
    return (pos == std::string::npos) ? "" : s.substr(0, pos + 1);
}

void onConnect(uWS::WebSocket<false, true, NDAVis::Server::PerSocketData> *ws)
{
    std::cout << "Client Connected" << std::endl;
    std::cout << ws->getRemoteAddressAsText() << std::endl;
    auto socketData = ws->getUserData();
    if (!socketData)
    {
        std::cout << "Does not exist" << std::endl;
    }

    std::vector<std::string> fileNames;
    fileManager.getFileNames(&fileNames);

    json j;
    j["numberOfFiles"] = fileManager.getNumberOfFiles();
    j["type"] = "file";
    j["files"] = {};
    for (auto it = fileNames.begin(); it != fileNames.end(); it++)
    {
        j["files"].push_back((*it));
    }
    ws->send(j.dump(), uWS::OpCode::TEXT, true);
}

void onMessage(uWS::WebSocket<false, true, NDAVis::Server::PerSocketData> *ws, std::string_view message, uWS::OpCode opCode)
{
    json j = json::parse(message);
    std::cout << message << std::endl;
    std::string jType = j["type"].dump();
    jType = jType.substr(1, (jType.length() - 2));
    if (jType == "file")
    {
        /* code after client selects file */
        float colour[] = {1, 2, 3, 4}; //Test Mode
        float opacity[] = {1, 2};      //Test Mode
        std::string fileName = j["file"].dump();
        fileName = fileName.substr(1, (fileName.length() - 2));

        controller.setFile(fileName);
        controller.startServerRender(0, 0, 0, 0, 0, 0, colour, 4, opacity, 2);

        // send Big File Dimension to client after file selection
        json BigFileD;
        BigFileD["type"] = "BigD";
        BigFileD["dimensions"] = {controller.bigNX, controller.bigNY, controller.bigNZ};
        BigFileD["smallXYFile"] = controller.smallXYFile;
        BigFileD["smallZFile"] = controller.smallZFile;
        ws->send(BigFileD.dump(), uWS::OpCode::TEXT, true);

        // Send tiles to client
        for (auto &tile : controller.clientTiles.allTiles)
        {
            std::vector<char> compressed_data;
            size_t compressed_size = 0;
            auto status = compression.compress(tile.cubeArr, compressed_data, compressed_size, tile.NX, tile.NY, tile.NZ, 12);
            compressed_data.resize(compressed_size);
            std::string base64String = compression.to_base64(reinterpret_cast<char *>(compressed_data.data()), compressed_size);

            json vol;
            vol["floatArr"] = {};
            for (int i = 0; i < (tile.NX*tile.NY*tile.NZ); i++) {
                vol["floatArr"].push_back(tile.cubeArr[i]);
            }

            vol["type"] = "volume";
            vol["id"] = tile.ID;
            vol["dimensions"] = {tile.NX, tile.NY, tile.NZ};
            vol["chunk_dimension"] = {controller.clientTiles.xChunksDim,controller.clientTiles.yChunksDim,controller.clientTiles.zChunksDim};
            vol["render_data"] = base64String;
            ws->send(vol.dump(), uWS::OpCode::TEXT, false);
        }
    }

    else if (jType == "volume")
    {
        /* code for cubes needed for interaction process */
        //int* tiles = j["tiles"];
        json t = j["tiles"];
        int* tiles = new int[t.size()];
        for (int i = 0; i < t.size(); i++)
        {
            tiles[i] = t[i];
        }

        controller.setNewCordinates(j["cropPoints"][0], j["cropPoints"][1], j["cropPoints"][2], j["cropPoints"][3], j["cropPoints"][4], j["cropPoints"][5], j["cropPoints"][6], j["cropPoints"][7]);
        controller.clientRequestCube(tiles, t.size(), j["XY"], j["Z"]);

        for (auto &tile : controller.clientTiles.allTiles)
        {
            for (int i = 0; i < j["tiles"].size(); i++)
            {
                if (tile.ID == j["tiles"][i])
                {
                    std::vector<char> compressed_data;
                    size_t compressed_size = 0;
                    auto status = compression.compress(tile.cubeArr, compressed_data, compressed_size, tile.NX, tile.NY, tile.NZ, 12);
                    compressed_data.resize(compressed_size);
                    std::string base64String = compression.to_base64(reinterpret_cast<char *>(compressed_data.data()), compressed_size);

                    json vol;

                    vol["floatArr"] = {};
                    for (int i = 0; i < (tile.NX*tile.NY*tile.NZ); i++) {
                        vol["floatArr"].push_back(tile.cubeArr[i]);
                    }

                    vol["type"] = "volume";
                    vol["id"] = tile.ID;
                    vol["dimensions"] = {tile.NX, tile.NY, tile.NZ};
                    vol["render_data"] = base64String;
                    ws->send(vol.dump(), uWS::OpCode::TEXT, false);
                }
            }
        }
    }

    else if (jType == "image")
    {
        /* code for image needed at camera position same way as client */
        //getcamera
        //getcolor
        json colourMap = j["colourMap"];
        float* colour = new float[colourMap.size()];
        for (int i = 0; i < colourMap.size(); i++)
        {
            colour[i] = colourMap[i];
        }

        json opacityMap = j["nodes"];
        float* opacity = new float[opacityMap.size()];
        for (int i = 0; i < opacityMap.size(); i++)
        {
            opacity[i] = opacityMap[i];
        }

        controller.setColor(colour, colourMap.size(), opacity, opacityMap.size());
        controller.setCameraView(j["camera_view_up"][0], j["camera_view_up"][1], j["camera_view_up"][2], j["camera_pos"][0], j["camera_pos"][1], j["camera_pos"][2]);  

        //to get image
        controller.getImage();
        json im;
        im["type"] = "image";

        vtkUnsignedCharArray* vtkWriterArrayTemp = controller.visul.vtkWriterArray;
        int imageArrSize = vtkWriterArrayTemp->GetNumberOfTuples();
        im["image_data"] = {};
        for (int i = 0; i < imageArrSize; i++)
        {
            im["ïmage_data"][i] = vtkWriterArrayTemp->GetValue(i);
        }
        ws->send(im.dump(), uWS::OpCode::TEXT, true);
        //controller.visul.imageArr this is int array contains jpeg
        //controller.visul.imageArrSize size of array if needed
    }

    else
    {
        std::cout << "JSON message received of invalid format" << std::endl;
    }
}


VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
int main()
{
    uWS::App().ws<NDAVis::Server::PerSocketData>("/*", (uWS::App::WebSocketBehavior<NDAVis::Server::PerSocketData>){/* Settings */
        .compression = uWS::DEDICATED_COMPRESSOR_256KB,
        .maxPayloadLength = 256 * 1024 * 1024,
        .open = onConnect,
        .message = onMessage,
        .drain = [](auto * /*ws*/)
        {
        /* Check ws->getBufferedAmount() here */ },
        .ping = [](auto * /*ws*/, std::string_view)
        {
        /* Not implemented yet */ },
        .pong = [](auto * /*ws*/, std::string_view)
        {
        /* Not implemented yet */ },
        .close = [](auto * /*ws*/, int /*code*/, std::string_view /*message*/)
        {
        /* You may access ws->getUserData() here */ }})
        .listen("0.0.0.0", 9000, [](auto *listen_socket)
                {
                    if (listen_socket)
                    {
                        std::cout << "Listening on port " << 9000 << std::endl;
                    }
                })
        .run();

    return 0;
}
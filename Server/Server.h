#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#include <vector>
#include "App.h"

namespace NDAVis
{
    class Server
    {
    public:
        /* ws->getUserData returns one of these */
        struct PerSocketData {
            /* Fill with user data */
        };
        void runServer();
        void onOpen(uWS::WebSocket<false, true, PerSocketData>* ws);
    };
}

#endif //SERVER_H_
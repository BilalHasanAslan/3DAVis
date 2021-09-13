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
    };
}

#endif //SERVER_H_
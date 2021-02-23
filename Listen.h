//
// Created by apurwa on 2/22/21.
//

#ifndef UNTITLED_LISTEN_H
#define UNTITLED_LISTEN_H

#include <thread>
#include <iostream>
#include <Poco/Net/ServerSocket.h>
#include "node.h"

typedef Poco::Net::ServerSocket serverSocket;

class Listen {

    Node* node;
    serverSocket server;
    bool alive;

public:
    Listen(Node* n);
    bool join();

};

#endif //UNTITLED_LISTEN_H
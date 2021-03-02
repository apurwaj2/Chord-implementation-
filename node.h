//
// Created by apurwa on 2/21/21.
//

#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H

#include <iostream>
#include <functional>
#include "pocoHeader.h"
#include "Finger.h"

using namespace std;

class Node {

    size_t nodeId;
    SocketAddress socket_address;
    int port;
    SocketAddress predecessor;
    SocketAddress successor;
    bool alive;

public:

    Finger* fingerTable;

    TCPServer* listenServer;
    Thread stabilizer;

    //constructor
    Node(SocketAddress, int);

    //get data
    size_t getNodeId();
    SocketAddress getAddress();
    SocketAddress getPredecessor();
    SocketAddress getSuccessor();
    int getPort();
    bool getStatus();
    void createRing();
    bool join(SocketAddress);
    string notifySuccessor(SocketAddress);
    void handleNotification(SocketAddress);
    SocketAddress findSuccessor(size_t);
    SocketAddress findPredecessor(size_t);
    void setPredecessor(SocketAddress);
    void setSuccessor(SocketAddress);
    void getKey(int);
    SocketAddress closest_preceding_finger(size_t, size_t);
    void stopThreads();
};

#endif //UNTITLED_NODE_H
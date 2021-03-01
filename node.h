//
// Created by apurwa on 2/21/21.
//

#include <iostream>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/TCPServer.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/TCPServerConnection.h>
#include <functional>
#include <unordered_map>

typedef Poco::Net::SocketAddress SocketAddress;
typedef Poco::Net::StreamSocket StreamSocket;
typedef Poco::Net::TCPServer TCPServer;

using namespace std;

class Node {

    size_t nodeId;
    SocketAddress socket_address;
    int port;
    SocketAddress predecessor;
    SocketAddress successor;
    unordered_map<int, SocketAddress> fingerTable;

    //Node* node;

public:

    //constructor
    Node(SocketAddress, int);

    //get data
    size_t getNodeId();
    SocketAddress getAddress();
    SocketAddress getPredecessor();
    SocketAddress getSuccessor();
    int getPort();

    void createRing();
    bool join(SocketAddress);
    string notifySuccessor(SocketAddress);
    void handleNotification(SocketAddress);
    void startListner();
    SocketAddress findSuccessor(size_t);
    SocketAddress findPredecessor(size_t);
    SocketAddress getFingerEntry(int);
    void updateFingerEntry(int, SocketAddress);
    void deleteFingerEntryForNode(SocketAddress);
    void deleteSuccessor();
    void setPredecessor(SocketAddress);
    void setSuccessor(SocketAddress);
    int fixFinger(int, int);
    SocketAddress closest_preceding_finger(size_t, size_t);

};

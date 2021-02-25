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

using namespace  std;

typedef Poco::Net::SocketAddress SocketAddress;
typedef Poco::Net::StreamSocket StreamSocket;
typedef Poco::Net::TCPServer TCPServer;

class Node {

    size_t nodeId;
    SocketAddress socket_address;
    int port;
    SocketAddress predecessor;
    SocketAddress successor;
    std::unordered_map<int, SocketAddress> fingerTable;
    Node* node;

public:

//    TCPServer listenServer(Poco::Net::TCPServerConnectionFactoryImpl<Listen>());

    //constructor
    Node(SocketAddress, int);

    //get data
    long getId();
    SocketAddress getAddress();
    SocketAddress getPredecessor();
    SocketAddress getSuccessor();
    int getPort();

    void createRing(Node*);
    void join(SocketAddress);
    void notifySuccessor(SocketAddress);
    void handleNotification(SocketAddress);
    SocketAddress findSuccessor(long);
    SocketAddress findPredecessor(long);
    SocketAddress closestPredecessor(long);
    void updateFingerTable(int, SocketAddress);
    void updateFingerEntry(int, SocketAddress);
    void deleteFingerEntryForNode(SocketAddress);
    void deleteSuccessor();
    void updateSuccessor();
    void setPredecessor(SocketAddress);


};
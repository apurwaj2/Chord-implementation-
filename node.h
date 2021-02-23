//
// Created by apurwa on 2/21/21.
//

#include <iostream>
#include <Poco/Net/SocketAddress.h>
#include <functional>
#include <unordered_map>

using namespace  std;

typedef Poco::Net::SocketAddress socketAddress;

class Node {

    size_t nodeId;
    socketAddress socket_address;
    int port;
    socketAddress predecessor;
    socketAddress successor;
    std::unordered_map<int, socketAddress> fingerTable;

public:

    //constructor
    Node(socketAddress, int);

    //get data
    long getId();
    socketAddress getAddress();
    socketAddress getPredecessor();
    socketAddress getSuccessor();
    int getPort();

    void createRing(Node*);
    bool join(socketAddress);
    void notifySuccessor(socketAddress);
    void handleNotification(socketAddress);
    socketAddress findSuccessor(long);
    socketAddress findPredecessor(long);
    socketAddress closestPredecessor(long);
    void updateFingerTable(int, socketAddress);
    void updateFingerEntry(int, socketAddress);
    void deleteFingerEntryForNode(socketAddress);
    void deleteSuccessor();
    void updateSuccessor();
    void setPredecessor(socketAddress);


};
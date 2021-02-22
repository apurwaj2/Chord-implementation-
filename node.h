//
// Created by apurwa on 2/21/21.
//

#include <iostream>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <functional>
#include <unordered_map>

using namespace  std;

typedef Poco::Net::SocketAddress socketAddress;

class Node {

    size_t nodeId;
    socketAddress socket_address;
    socketAddress predecessor;
    unordered_map<int, socketAddress> fingerTable;

public:

    //constructor
    Node(socketAddress);

    //get data
    long getId();
    socketAddress getAddress();
    socketAddress getPredecessor();
    socketAddress getSuccessor();


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
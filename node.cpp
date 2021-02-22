//
// Created by apurwa on 2/21/21.
//

#include "node.h"

Node::Node(socketAddress add) {

    socket_address = add;
    nodeId = hash<string>{}(add.toString());

    for (int i = 1; i <= 32; i++) {
        updateFingerEntry(i, Poco::Net::SocketAddress());
    }

    cout<<"Done"<<endl;
}

void Node::updateFingerEntry(int i, socketAddress address) {
    fingerTable[i] = address;
    cout<<i<<" ";
}
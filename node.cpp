//
// Created by apurwa on 2/21/21.
//

#include "node.h"

Node::Node(socketAddress add, int portnum) {

    socket_address = add;
    port = portnum;
    nodeId = hash<string>{}(add.toString());

    //FingerTable updated with null entries
    for (int i = 1; i <= 32; i++) {
        updateFingerEntry(i, Poco::Net::SocketAddress());
    }
    cout<<"Node created!"<<endl;
}

void Node::createRing(Node* node) {

    //For ring creation node predecessor is itself
    node->predecessor = node->socket_address;

}

void Node::updateFingerEntry(int i, socketAddress address) {
    fingerTable[i] = address;
    cout<<i<<" ";
}

bool Node::join(socketAddress address) {

}

int Node::getPort() {
    return port;
}

socketAddress Node::getAddress() {
    return socket_address;
}
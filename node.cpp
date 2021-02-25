//
// Created by apurwa on 2/21/21.
//

#include "node.h"
#include "Listen.cpp"

Node::Node(SocketAddress add, int portnum) {

    socket_address = add;
    port = portnum;
    nodeId = hash<string>{}(add.toString());

    //FingerTable updated with null entries
    for (int i = 1; i <= 32; i++) {
        updateFingerEntry(i, Poco::Net::SocketAddress());
    }
    cout << "Node created successfully!" << endl;
}

void Node::setPredecessor(SocketAddress address) {
    predecessor = address;
}

SocketAddress Node::getPredecessor() {
    return predecessor;
}

void Node::setSuccessor(SocketAddress address) {
    successor = address;
}

SocketAddress Node::getSuccessor() {
    return successor;
}

int Node::getPort() {
    return port;
}

SocketAddress Node::getAddress() {
    return socket_address;
}

size_t Node::getNodeId() {
    return nodeId;
}

void Node::printKeysInNode() {

    cout << "Following key entries are present in this node" << endl;

    for(auto it = keyTable.begin(); it != keyTable.end(); it++) {
        cout << it->first << " : " << it->second << endl;
    }

}

void Node::insertKeyInTable(size_t id, string value) {
    keyTable[id] = value;
}

void Node::createRing() {

    //For ring creation node predecessor is itself & successor is itself
    setPredecessor(socket_address);
    setSuccessor(socket_address);
    //start listener
    startListner();
}

void Node::updateFingerEntry(int i, SocketAddress address) {
    fingerTable[i] = address;

}

bool Node::join(SocketAddress address) {
    if (address != getAddress()) {
        // Trying to join an existing ring

    }
}

//int Node::query(int key) {
//    //lookupKey = stub(key)
//    //s = Access fingerTable[lookupKey] and get socketAddress
//    //
//}

void Node::startListner() {
    Poco::Net::ServerSocket serverSocket(getPort());
    //Configure some server params
    Poco::Net::TCPServerParams* pParams = new Poco::Net::TCPServerParams();
    pParams->setMaxThreads(4);
    pParams->setMaxQueued(4);
    pParams->setThreadIdleTime(100);
    TCPServer listenServer(new Poco::Net::TCPServerConnectionFactoryImpl<Listen>(), serverSocket, pParams);
    listenServer.start();

    //Client side code
//    char buffer[1024];
//    SocketAddress sa("localhost", getPort());
//    StreamSocket ss(sa);
//    string data("hello, world");
//    ss.sendBytes(data.data(), (int) data.size());
//    ss.receiveBytes(buffer, sizeof (buffer));
//    string reply(buffer);
//    cout << "Received: " << reply << endl;
//    listenServer.stop();
}


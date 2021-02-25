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
    cout<<"Node created!"<<endl;
}

void Node::createRing(Node* node) {

    //For ring creation node predecessor is itself
    node->predecessor = node->socket_address;

}

void Node::updateFingerEntry(int i, SocketAddress address) {
    fingerTable[i] = address;
    //cout<<i<<" ";
}

void Node::join(SocketAddress address) {
    cout<<"Port "<<port<< endl;
    Poco::Net::ServerSocket serverSocket(8010);
    //Configure some server params
    Poco::Net::TCPServerParams* pParams = new Poco::Net::TCPServerParams();
    pParams->setMaxThreads(4);
    pParams->setMaxQueued(4);
    pParams->setThreadIdleTime(100);
    TCPServer listenServer(new Poco::Net::TCPServerConnectionFactoryImpl<Listen>(), serverSocket, pParams);
    listenServer.start();

    //Client side code
    SocketAddress sa("localhost", 8010);
    StreamSocket ss(sa);
    std::string data("hello, world");
    ss.sendBytes(data.data(), (int) data.size());
    listenServer.stop();
}

//int Node::query(int key) {
//    //lookupKey = stub(key)
//    //s = Access fingerTable[lookupKey] and get socketAddress
//    //
//}

int Node::getPort() {
    return port;
}

SocketAddress Node::getAddress() {
    return socket_address;
}
//
// Created by apurwa on 2/21/21.
//

#include "node.h"
#include "Listen.cpp"
#include "auxiliary.cpp"

Node::Node(SocketAddress add, int portnum) {

    socket_address = add;
    port = portnum;
    nodeId = hashAddress(add);

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
    return 1;
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

//    listenServer.stop();
}

SocketAddress Node::findSuccessor(size_t keyId) {

    SocketAddress successor;

    //find the predecessor of the keyId
    SocketAddress predecessor = findPredecessor(keyId);
    return successor;
}

SocketAddress Node::findPredecessor(size_t keyId) {

    SocketAddress n = getAddress();
    SocketAddress nSuccessor = getSuccessor();
    size_t relative_successor_id = getRelativeId(hashAddress(getSuccessor()), nodeId);
    size_t relative_key_id = getRelativeId(keyId, nodeId);
    SocketAddress most_recently_alive = n;

    while(!(relative_key_id > 0 && relative_key_id <= relative_successor_id)) {

        SocketAddress current = n;

        if(n == getAddress()) {
            n = closest_preceding_finger(keyId, getNodeId());
        } else {

			string key = to_string(keyId);
            SocketAddress result = requestAddress(n, strcat((char *)"CLOSEST_", key.c_str()));

            // if fail to get response, set n to most recently
            if (result == Poco::Net::SocketAddress()) {
                n = most_recently_alive;
                nSuccessor = requestAddress(n, (char *)"YOURSUCC");
                //if nSuccessor is null
                if (nSuccessor == Poco::Net::SocketAddress()) {
                    return getAddress();
                }
                continue;
            }

            // if n's closest is itself, return n
            else if (result == n)
                return result;

            // else n's closest is other node "result"
            else {
                most_recently_alive = n;
                nSuccessor = requestAddress(result, (char *)"YOURSUCC");;
                // if we can get its response, then "result" must be our next n
                if (nSuccessor != Poco::Net::SocketAddress()) {
                    n = result;
                } else {
                    nSuccessor = requestAddress(n, (char *)"YOURSUCC");
                }
            }

            // compute relative ids for while loop judgement
            relative_successor_id = getRelativeId(hashAddress(nSuccessor), hashAddress(n));
            relative_key_id = getRelativeId(keyId, hashAddress(n));

        }

        if(current == n)
            break;

    }

    return n;
}

void Node::deleteFingerEntryForNode(SocketAddress address) {
    for (int i = 32; i > 0; i--) {
        SocketAddress fingerAddress = fingerTable[i];
        if(fingerAddress == address)
            fingerTable[i] = Poco::Net::SocketAddress();
    }
}

SocketAddress Node::closest_preceding_finger(size_t keyId, size_t nodeId) {

    size_t relative_keyId = getRelativeId(keyId, nodeId);

    for(int i = 32; i > 0; i--) {
        SocketAddress fingerAddress = fingerTable[i];
        if(fingerAddress == Poco::Net::SocketAddress()) continue;

        size_t fingerId = hashAddress(fingerAddress);
        size_t relativeFingerId = getRelativeId(fingerId, nodeId);

        if (relativeFingerId > 0 && relativeFingerId < relativeFingerId)  {
            string response  = sendRequest(fingerAddress, "KEEP");
            if (response != "" &&  (strcmp(response.c_str(), "ALIVE") == 0)) {
                return fingerAddress;
            }

            // remove it from finger table
            else {
                deleteFingerEntryForNode(fingerAddress);
            }
        }

    }
    return getAddress();
}

int Node::fixFinger(int i, int m) {
    size_t next = getFingerId(nodeId, i, m);
	return 1;
}


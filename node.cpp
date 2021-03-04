//
// Created by apurwa on 2/21/21.
//
#include "node.h"
#include "Listen.cpp"
#include "Stabilize.cpp"
#include "checkPredecessor.cpp"
#include "fixFingers.cpp"

Node::Node(SocketAddress add, int portnum) {

    socket_address = add;
    port = portnum;
    nodeId = hashAddress(add);
    fingerTable = new Finger();

    //FingerTable updated with null entries
    for (int i = 1; i <= 32; i++) {
        fingerTable->updateFingerEntry(i, Poco::Net::SocketAddress());
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
    setPredecessor(Poco::Net::SocketAddress());
    setSuccessor(socket_address);
    alive= true;
    //start listener
    Listen listen(this);
    listner.start(listen);
    StableRun stable(this);
    stabilizer.start(stable);
    Checker checker(this);
    checkPred.start(checker);
    fixFinger fixer(this);
    finger.start(fixer);
}

bool Node::join(SocketAddress address) {
    if (address != getAddress()) {
        // Trying to join an existing ring
        string id = to_string(nodeId);
        string request = "FINDSUCC_" + id;
        SocketAddress successor = requestAddress(address, request);
        if(successor == Poco::Net::SocketAddress()) {
            cout << "Cannot find the node to join the ring" << endl;
            return false;
        }
        fingerTable->updateFingerEntry(1, successor);
    }

    alive = true;
    //start listener
    Listen listen(this);
    listner.start(listen);
    StableRun stable(this);
    stabilizer.start(stable);
    Checker checker(this);
    checkPred.start(checker);
    fixFinger fixer(this);
    finger.start(fixer);

    return true;
}

string Node::notifySuccessor(SocketAddress successor) {
    if (successor != getAddress()) {
        string port = to_string(getPort());
        string address = "localhost" + port;
        string request = "IAMPRE_" + address;
        return sendRequest(successor, request);
    } else {
        return "";
    }
}


void Node::handleNotification (SocketAddress predecessor) {
    if (getPredecessor() == Poco::Net::SocketAddress()) {
        setPredecessor(predecessor);
    }
    else {
        size_t oldPredecessor = hashAddress(getPredecessor());
        size_t oldPredecessorRelativeId = getRelativeId(nodeId, oldPredecessor);
        size_t newPredecessorRelativeId = getRelativeId(hashAddress(predecessor), oldPredecessor);
        if (newPredecessorRelativeId > 0 && newPredecessorRelativeId < oldPredecessorRelativeId)
            setPredecessor(predecessor);
    }
}

SocketAddress Node::findSuccessor(size_t keyId) {

    cout << "Entered findSuccessor " << endl;

    SocketAddress successor = getSuccessor();

    cout << "Got successor " << endl;

    //find the predecessor of the keyId
    SocketAddress predecessor = findPredecessor(keyId);
    if(predecessor != getAddress()) {
        successor = requestAddress(predecessor, (char *)"YOURSUCC");
    }
    // no other node is present
    if(successor == Poco::Net::SocketAddress()) {
        successor = getAddress();
    }

    return successor;
}

SocketAddress Node::findPredecessor(size_t keyId) {

    cout << "Entered find predecessor" << endl;

    SocketAddress n = getAddress();
    SocketAddress nSuccessor = getSuccessor();
    size_t relative_successor_id = getRelativeId(hashAddress(getSuccessor()), nodeId);
    size_t relative_key_id = getRelativeId(keyId, nodeId);
    SocketAddress most_recently_alive = n;

    cout << "relative_key_id "<< relative_key_id << endl;
    cout << "relative_successor_id " << relative_successor_id << endl;

    while(!(relative_key_id > 0 && relative_key_id <= relative_successor_id)) {

        SocketAddress current = n;

        if(n == getAddress()) {
            n = closest_preceding_finger(keyId, getNodeId());
        } else {
			string key = to_string(keyId);
			string request = "CLOSEST_" + key;
            SocketAddress result = requestAddress(n, request);

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

    cout << "Reached the end" <<endl;
    return n;
}

SocketAddress Node::closest_preceding_finger(size_t keyId, size_t nodeId) {

    size_t relative_keyId = getRelativeId(keyId, nodeId);

    for(int i = 32; i > 0; i--) {
        SocketAddress fingerAddress = fingerTable->getFingerEntry(i);
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
                fingerTable->deleteFingerEntryForNode(fingerAddress);
            }
        }

    }
    return getAddress();
}

void Node::getKey(int key) {
    Query(key, this);
}

void Node::stopThreads() {

    //listener, stabilizer, fixFingers & checkPredecessor should stop after setting alive to false
    alive = false;
    sleep(120);

}

bool Node::getStatus() {
    cout<<"Status of alive: " << alive << endl;
    return alive;
}

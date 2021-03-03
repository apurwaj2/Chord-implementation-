//
// Created by apurwa on 2/25/21.
//

#include "auxiliary.h"

using namespace std;

size_t getFingerId(size_t nodeID, int i, int m) {
    size_t a = size_t(pow(2.0, double (i-1)));
    size_t b = pow(2.0, double(m));

    size_t value = (nodeID + a) % b;

    return value;
}

size_t hashAddress(SocketAddress add) {
    return hash<string>{}(add.toString());
}

size_t hashKey(int key) {
    return hash<string>{}(to_string(key));
}

/*
 * Sending request to another node server
 */
string sendRequest(SocketAddress server, string request) {
    // try to send request to server
    SocketAddress sa("localhost", server.port());
    StreamSocket ss(sa);
    try {
        string data(request);
        ss.sendBytes(data.data(), (int) data.size());
    } catch (exception e) {
        cout << "Cannot send request to " << server.port() << endl;
        return NULL;
    }

    // get response in buffer
    char buffer[1024];
    try {
        ss.receiveBytes(buffer, sizeof (buffer));
    } catch (exception e) {
        cout << "Cannot get response " << server.port() << endl;
    }
    string response(buffer);
    cout << "This is the response " << response << endl;
    ss.close();

    return response;
}

SocketAddress requestAddress (SocketAddress server, string request) {

    string response = sendRequest(server, request);
    if (response == "") {
        return Poco::Net::SocketAddress();
    } else if (response.find("NOTHING") != std::string::npos) {
        return server;
    } else {
        SocketAddress ret = SocketAddress("localhost", stoi(response));
        return ret;
    }
}

void fillSuccessor(Node* node) {
    SocketAddress successor = node->getSuccessor();
    if (successor == Poco::Net::SocketAddress() || successor == node->getAddress()) {
        for (int i = 2; i <= 32; i++) {
            SocketAddress fingerId = node->fingerTable->getFingerEntry(i);
            if (fingerId != Poco::Net::SocketAddress() && fingerId != node->getAddress()) {
                for (int j = i-1; j >=1; j--) {
                    node->fingerTable->updateFingerEntry(j, fingerId);
                }
                break;
            }
        }
    }
    successor = node->getSuccessor();
    SocketAddress predecessor = node->getPredecessor();
    if ((successor == Poco::Net::SocketAddress() || successor == node->getAddress()) &&
        predecessor != Poco::Net::SocketAddress() && predecessor != node->getAddress()) {
        node->fingerTable->updateFingerEntry(1, node->getPredecessor());
    }
}

void deleteSuccessor(Node* node) {

    SocketAddress successor = node->getSuccessor();
    if (successor == Poco::Net::SocketAddress())
        return;

    // get last entry of successor
    int i = 32;
    for (i = 32; i > 0; i--) {
        SocketAddress fingerId = node->fingerTable->getFingerEntry(i);
        if (fingerId != Poco::Net::SocketAddress() && fingerId == successor)
            break;
    }

    // delete it
    for (int j = i; j >= 1 ; j--) {
        node->fingerTable->updateFingerEntry(j, Poco::Net::SocketAddress());
    }

    // if predecessor is successor, delete it
    SocketAddress predecessor = node->getPredecessor();
    if (predecessor!= Poco::Net::SocketAddress() && predecessor == successor)
        node->setPredecessor(Poco::Net::SocketAddress());

    // try to fill successor
    fillSuccessor(node);

    // if successor is still null or local node,
    // and the predecessor is another node, keep asking
    // it's predecessor until find local node's new successor
    if ((successor == Poco::Net::SocketAddress() || successor == node->getSuccessor()) &&
        predecessor != Poco::Net::SocketAddress() && predecessor != node->getAddress()) {

        SocketAddress p = predecessor;
        SocketAddress p_pre = Poco::Net::SocketAddress();
        while (true) {
            p_pre = requestAddress(p, "YOURPRE");
            if (p_pre == Poco::Net::SocketAddress())
                break;

            // if p's predecessor is node is just deleted,
            // or itself (nothing found in p), or local address,
            // p is current node's new successor, break
            if (p_pre == p || p_pre == node->getAddress() || p_pre == successor) {
                break;
            }

                // else, keep asking
            else {
                p = p_pre;
            }
        }

        // update successor
        node->fingerTable->updateFingerEntry(1, p);
    }
}

size_t getRelativeId(size_t a, size_t b) {
    size_t c = a-b;
    if(c < 0) {
        c += (size_t) pow(2.0, double (32));
    }
    return c;
}

void Query(int key, Node* node) {

    size_t keyId = hashKey(key);
    cout << "Hash value is " << keyId << endl;
    string keyHash = to_string(keyId);
    SocketAddress result = requestAddress(node->getAddress(), strcat((char *)"FINDSUCC_", keyHash.c_str()));

    // if fail to send request, local node is disconnected, exit
    if (result == Poco::Net::SocketAddress()) {
        cout << "Unable to contact node!" << endl;
        return;
    }
    // print out response
    cout << "Response from node " << node->getPort() << endl;
    cout << "Key is present at node " << result.port() << endl;

}
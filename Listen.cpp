#include <iostream>
#include <sstream>
#include "pocoHeader.h"
#include "node.h"

#define BUFFER_SIZE 2048

using namespace std;

class Listen: public Poco::Runnable {

    Node* node;

    size_t getSplitString(string input) {
        string token = input.substr(input.find("_") + 1);
        stringstream ss(token);
        size_t result;
        ss >> result;
        return result;
    }

    string processRequest(string request)
    {

        cout<< "Processing the request : " << request << endl;

        SocketAddress result = SocketAddress();
        string ret = "";
        if (request  == "") {
            return "";
        }
        if (request.find("CLOSEST") != string::npos) {
            int id = getSplitString(request);
            SocketAddress address("localhost", id);
            result = node->closest_preceding_finger(id, node->getNodeId());
            string ip = "localhost";
            int port = result.port();
            ret = to_string(port);
        }
        else if (request.find("YOURSUCC") != string::npos) {
            result = node->getSuccessor();
            if (result != Poco::Net::SocketAddress()) {
                string ip = "localhost";
                int port = result.port();
                ret = to_string(port);
            }
            else {
                ret = "NOTHING";
            }
        }
        else if (request.find("YOURPRE") != string::npos) {
            result = node->getPredecessor();
            if (result != Poco::Net::SocketAddress()) {
                string ip = "localhost";
                int port = result.port();
                ret = to_string(port);
            }
            else {
                ret = "NOTHING";
            }
        } else if (request.find("FINDSUCC") != string::npos) {
            size_t id = getSplitString(request);
            result = node->findSuccessor(id);
            string ip = "localhost";
            int port = result.port();
            ret = to_string(port);

        } else if (request.find("IAMPRE") != string::npos) {
            int id = getSplitString(request);
            SocketAddress new_pre = SocketAddress("localhost", to_string(id));
            node->notifySuccessor(new_pre);
            ret = "NOTIFIED";
        } else if (request.find("KEEP") != string::npos) {
            ret = "ALIVE";
        }
        return ret;
    }

public:
    Listen(Node* n)
    {
        node = n;
    }

    void run() {

        char buffer[BUFFER_SIZE];
        const void *reply;
        int port = node->getPort();
        ServerSocket serverSocket(SocketAddress("localhost", port));

        cout<< "Started listening on port " << port << endl;

        while(1) {
            StreamSocket ss = serverSocket.acceptConnection();
            ss.receiveBytes(buffer, sizeof(buffer));
            std::cout<< "Received request : " << string(buffer) << std::endl;
            string reply = processRequest(string(buffer));
            ss.sendBytes(reply.data(), (int) reply.size());

        }
    }

};
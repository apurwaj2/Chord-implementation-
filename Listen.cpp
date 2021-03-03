#include <iostream>
#include <sstream>
#include "pocoHeader.h"
#include "node.h"

#define BUFFER_SIZE 2048

using namespace std;

class Listen: public Poco::Runnable {

    Node* node;

    int getSplitString(string input) {
        stringstream ss(input);
        string token;

        getline(ss, token, '_');

        return stoi(token);
    }

    string processRequest(string request)
    {

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
            ret = "MYCLOSEST_" + ip + ":" + to_string(port);
        }
        else if (request.find("YOURSUCC") != string::npos) {
            result = node->getSuccessor();
            if (result != Poco::Net::SocketAddress()) {
                string ip = "localhost";
                int port = result.port();
                ret = "MYSUCC_" + ip + ":" + to_string(port);
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
                ret = "MYPRE_" + ip + ":" + to_string(port);
            }
            else {
                ret = "NOTHING";
            }
        } else if (request.find("FINDSUCC") != string::npos) {

            int id = getSplitString(request);
            result = node->findSuccessor(id);
            string ip = "localhost";
            int port = result.port();
            ret = "FOUNDSUCC_" + ip + ":" + to_string(port);

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
        ServerSocket serverSocket(SocketAddress("localhost", 8001));
        //sleep(1);

        while(node->getStatus()) {
            StreamSocket ss = serverSocket.acceptConnection();
            ss.receiveBytes(buffer, sizeof(buffer));
            std::cout<< "Received request : " << string(buffer) << std::endl;
            string reply = processRequest(string(buffer));
            const void* response = reply.c_str();
            ss.sendBytes(response, sizeof(response));
        }
        try {
            sleep(5);
        } catch (exception e) {
            cout << "Exception: " << e.what() << endl;
        }
    }

};
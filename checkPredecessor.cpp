//
// Created by apurwa on 3/1/21.
//

#include <string>
#include "auxiliary.h"
#include <Poco/Runnable.h>

using namespace std;

class Checker: public Poco::Runnable {
    Node* node;

public:
    Checker(Node* n) {
        node = n;
    }

    void run() {
        while (node->getStatus() == true) {
            SocketAddress predecessor = node->getPredecessor();
            if (predecessor != Poco::Net::SocketAddress()) {
                string response  = sendRequest(predecessor, "KEEP");
                if (response == "" || strcmp(response.c_str(), (char *)"ALIVE") != 0) {
                    node->setPredecessor(Poco::Net::SocketAddress());
                }

            }
            try {
                sleep(60);
            } catch (exception e) {
                cout << "Exception: " << e.what() << endl;
            }
        }
    }
};

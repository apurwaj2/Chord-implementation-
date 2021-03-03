//
// Created by apurwa on 3/1/21.
//

#include <string>
#include "auxiliary.h"
#include <Poco/Runnable.h>

using namespace std;

class fixFinger: public Poco::Runnable {
    Node* node;
    int random;

public:
    fixFinger(Node* n) {
        node = n;
    }

    void run() {
        while (node->getStatus() == true) {
            random = rand() % 32;
            SocketAddress fingerId = node->findSuccessor(getFingerId(node->getNodeId(),random,32));
            node->fingerTable->updateFingerEntry(random, fingerId);
            try {
                sleep(60);
            } catch (exception e) {
                cout << "Exception: " << e.what() << endl;
            }
        }
    }
};

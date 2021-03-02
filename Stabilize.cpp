//
// Created by apurwa on 3/1/21.
//

#include <string>
#include "auxiliary.h"
#include <Poco/Runnable.h>

using namespace std;

class StableRun : public Poco::Runnable {
    Node* node;

public:
    StableRun(Node* n) {
        node = n;
    }

    void run() {
        while (node->getStatus() == true) {
            SocketAddress successor = node->getSuccessor();
            if (successor == Poco::Net::SocketAddress() ||
                successor == node->getAddress()) {
                fillSuccessor(node);
            }
            successor = node->getSuccessor();
            if (successor != Poco::Net::SocketAddress() &&
                successor != node->getAddress()) {

                // get predecessor
                SocketAddress x = requestAddress(successor, "YOURPRE");
                if (x == Poco::Net::SocketAddress()) {
                    deleteSuccessor(node);
                }

                // else if successor's predecessor is not itself
                else if (x != successor) {
                    size_t successorRelativeId = getRelativeId(hashAddress(successor), node->getNodeId());
                    size_t xRelativeId = getRelativeId(hashAddress(x), node->getNodeId());
                    if (xRelativeId > 0 && xRelativeId < successorRelativeId) {
                        node->fingerTable->updateFingerEntry(1, x);
                    }
                }

                // successor's predecessor is successor itself, then notify successor
                else {
                    node->notifySuccessor(successor);
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

//
// Created by apurwa on 2/22/21.
//

#include "Listen.h"

Listen::Listen(Node* n) {

    node = n;
    alive = true;
    server = serverSocket(n->getAddress());

}

bool Listen::join() {



}

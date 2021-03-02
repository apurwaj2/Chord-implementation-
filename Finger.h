//
// Created by apurwa on 3/1/21.
//

#ifndef UNTITLED_FINGER_H
#define UNTITLED_FINGER_H

#include <unordered_map>
#include "pocoHeader.h"

using namespace std;

class Finger {

    unordered_map<int, SocketAddress> fingerTable;

public:

    SocketAddress getFingerEntry(int);
    void updateFingerEntry(int, SocketAddress);
    void deleteFingerEntryForNode(SocketAddress);

};


#endif //UNTITLED_FINGER_H

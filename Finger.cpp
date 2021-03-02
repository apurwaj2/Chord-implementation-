//
// Created by apurwa on 3/1/21.
//

#include "Finger.h"
#include "auxiliary.cpp"

SocketAddress Finger::getFingerEntry(int i) {
    return fingerTable[i];
}

int Finger::fixFinger(int i, int m, size_t nodeId) {
    size_t next = getFingerId(nodeId, i, m);
    return 1;
}

void Finger::deleteFingerEntryForNode(SocketAddress address) {
    for (int i = 32; i > 0; i--) {
        SocketAddress fingerAddress = fingerTable[i];
        if(fingerAddress == address)
            fingerTable[i] = Poco::Net::SocketAddress();
    }
}

void Finger::updateFingerEntry(int i, SocketAddress address) {
    fingerTable[i] = address;
}
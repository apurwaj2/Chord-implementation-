//
// Created by apurwa on 3/1/21.
//

#ifndef UNTITLED_AUXILIARY_H
#define UNTITLED_AUXILIARY_H

#include <iostream>
#include "pocoHeader.h"
#include "node.h"
#include <string>
#include <math.h>

using namespace std;

size_t getFingerId(size_t, int, int);
size_t hashAddress(SocketAddress);
size_t hashKey(int);
string sendRequest(SocketAddress, string);
SocketAddress requestAddress (SocketAddress, string);
void fillSuccessor(Node*);
void deleteSuccessor(Node*);
void deleteSuccessor(Node*);
size_t getRelativeId(size_t, size_t);
void Query(int, Node*);


#endif //UNTITLED_AUXILIARY_H

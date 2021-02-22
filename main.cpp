#include <iostream>
#include "node.h"

using namespace  std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    socketAddress address("www.abc.com", 80);
    Node* node = new Node(address);
    return 0;
}

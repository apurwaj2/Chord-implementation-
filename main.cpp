#include <iostream>
#include "node.h"

using namespace  std;

int main(int argc, char* argv[]) {

    //Using the same local machine so using localhost
    string node_ipAdd = "localhost";
    if (strcmp(argv[1], "create") == 0) {

        //First create the chord ring
        cout << "Create" <<endl;

        //Get the port number
        char* port = argv[2];
        int portNum = stoi(port);

        //create socket
        SocketAddress address(node_ipAdd, portNum);
        Node *node = new Node(address, portNum);

        //Creates ring
        node->createRing();

    } else if (strcmp(argv[1], "join") == 0) {
        cout << "Join" <<endl;
        char* port1 = argv[2];
        int newPort = stoi(port1);
        char* port2 = argv[3];
        int portNum = stoi(port2);

        SocketAddress address(node_ipAdd, portNum);
        Node *node = new Node(address, newPort);
        bool resp = node->join(address);

        if(resp) {
            cout << "Node successfully joined the chord ring." << endl;
        } else {
            cout << "Could not join the new node to the chord ring." << endl;
        }

    } else if (strcmp(argv[1], "delete") == 0) {
        cout << "Delete" << endl;
    } else if (strcmp(argv[1], "getKey") == 0) {
        cout << "getKey" << endl;
    } else if (strcmp(argv[1], "insertKey") == 0) {
        cout << "insertKey" << endl;
    } else {
        cout << argv[1] << " is an invalid option. Enter a valid option." << endl;
    }

    return 0;
}

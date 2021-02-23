#include <iostream>
#include "node.h"

using namespace  std;

int main(int argc, char* argv[]) {


    //Using the same local machine so using localhost
    string node_ipAdd = "localhost";
    if (strcmp(argv[1], "create") == 0) {

        cout << "Create" <<endl;
        //First create the chord ring

        //Get the port number
        int portNum = (int) *argv[2];
        //create socket
        socketAddress address(node_ipAdd, portNum);
        Node *node = new Node(address, portNum);

        //Creates ring
        node->createRing(node);

    } else if (strcmp(argv[1], "join") == 0) {
        cout << "Join" <<endl;
        int newPort = (int) *argv[2];
        int portNum = (int) *argv[3];

        socketAddress address(node_ipAdd, portNum);



    } else if (strcmp(argv[1], "delete") == 0) {
        cout << "Delete" <<endl;
    } else if (strcmp(argv[1], "query") == 0) {
        cout << "Query" <<endl;
    } else {
        cout << argv[1] << " is an invalid option. Enter a valid option." << endl;
    }


    return 0;
}

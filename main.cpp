#include <iostream>
#include <string>
#include "node.h"

using namespace  std;

int main() {

    string option, port, portNew;

    while(1) {
        //Using the same local machine so using localhost
        string node_ipAdd = "localhost";

        cout<<"Enter anyone of the following options:"<<endl;
        cout<<"create, join, delete, getkey, quit"<<endl;

        cin >> option;

        if (strcmp(option.c_str(), "create") == 0) {

            //First create the chord ring
            cout << "For create enter the port number for main node" << endl;
            cin >> port;

            //Get the port number
            int portNum = stoi(port);

            //create socket
            SocketAddress address(node_ipAdd, portNum);
            Node *node = new Node(address, portNum);

            //Creates ring
           // node->createRing();

        } else if (strcmp(option.c_str(), "join") == 0) {
            cout << "Enter port number of main node for Join" << endl;
            cin >> port;
            cout << "Enter port number for the node you want to join" << endl;
            cin >> portNew;

            int newPort = stoi(port);
            int portNum = stoi(portNew);

            SocketAddress address(node_ipAdd, portNum);
            Node *node = new Node(address, newPort);
         /*   bool resp = node->join(address);

            if (resp) {
                cout << "Node successfully joined the chord ring." << endl;
            } else {
                cout << "Could not join the new node to the chord ring." << endl;
            }*/

        } else if (strcmp(option.c_str(), "delete") == 0) {
            cout << "Enter port number of main node for Delete" << endl;
            cin >> port;
            cout << "Enter port number for the node you want to delete" << endl;
            cin >> portNew;

        } else if (strcmp(option.c_str(), "getKey") == 0) {
            cout << "Enter key for getKey" << endl;
            cin >> portNew;
            cout << "Enter port number of main node" << endl;
            cin >> port;

            int newKey = stoi(portNew);
            int portNum = stoi(port);

            SocketAddress address(node_ipAdd, portNum);
            Node *node = new Node(address, portNum);

          //  node->getKey(newKey);

        } else if (strcmp(option.c_str(), "quit") == 0) {
            break;
        }
        else {
            cout << option << " is an invalid option. Enter a valid option." << endl;
        }

    }


    return 0;
}

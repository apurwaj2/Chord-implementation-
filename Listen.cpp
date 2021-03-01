//
// Created by apurwa on 2/22/21.
//

#include <iostream>
#include <Poco/Net/TCPServer.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/TCPServerConnection.h>

#define BUFFER_SIZE 2048

typedef Poco::Net::StreamSocket StreamSocket;
typedef Poco::Net::TCPServerConnection TCPServerConnection;

using namespace std;

class Listen: public TCPServerConnection {
public:
    Listen(const StreamSocket& s): TCPServerConnection(s) { }

    void run() {
        StreamSocket& ss = socket();
        try {
            char buffer[BUFFER_SIZE];
            int n = ss.receiveBytes(buffer, sizeof(buffer));
            string request(buffer);
            cout << "Received : " << request << endl;
            string data = "I received your message";
            ss.sendBytes(data.c_str(), data.length());

        }
        catch (Poco::Exception& exc)
        {
            cerr << "Listen: " << exc.displayText() << endl;
        }
    }

};




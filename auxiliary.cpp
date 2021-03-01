//
// Created by apurwa on 2/25/21.
//

#include <iostream>
#include <string>
#include <math.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>

using namespace std;

size_t getFingerId(size_t nodeID, int i, int m) {
    size_t a = size_t(pow(2.0, double (i-1)));
    size_t b = pow(2.0, double(m));

    size_t value = (nodeID + a) % b;

    return value;
}

size_t hashAddress(Poco::Net::SocketAddress add) {
    return hash<string>{}(add.toString());
}

size_t getRelativeId(size_t a, size_t b) {
    size_t c = a-b;
    if(c < 0) {
        c += (size_t) pow(2.0, double (32));
    }
    return c;
}

/*
 * Sending request to another node server
 */
string sendRequest(Poco::Net::SocketAddress server, string request) {
    //Client side code
//    listenServer.stop();
//
    // try to send request to server
    Poco::Net::SocketAddress sa("localhost", server.port());
    Poco::Net::StreamSocket ss(sa);
    try {
        string data(request);
        ss.sendBytes(data.data(), (int) data.size());
    } catch (exception e) {
        cout << "Cannot send request to " << server.port() << endl;
        return NULL;
    }

    // sleep for a short time, waiting for response
    sleep(20);

    // get response in buffer
    char buffer[1024];
    try {
        ss.receiveBytes(buffer, sizeof (buffer));
    } catch (exception e) {
        cout << "Cannot get response " << server.port() << endl;
    }
    string response(buffer);
    ss.close();

    return response;
}

Poco::Net::SocketAddress requestAddress (Poco::Net::SocketAddress server, string request) {

    string response = sendRequest(server, request);
    if (response == "") {
        return Poco::Net::SocketAddress();
    } else if (response.find("NOTHING") != std::string::npos) {
        return server;
    } else {
        Poco::Net::SocketAddress ret = Poco::Net::SocketAddress("localhost", stoi(response));
        return ret;
    }
}

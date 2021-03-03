//
// Created by apurwa on 3/1/21.
//

#ifndef UNTITLED_POCOHEADER_H
#define UNTITLED_POCOHEADER_H

#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/TCPServer.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/TCPServerConnection.h>
#include <Poco/Thread.h>

typedef Poco::Net::SocketAddress SocketAddress;
typedef Poco::Net::StreamSocket StreamSocket;
typedef Poco::Net::ServerSocket ServerSocket;
typedef Poco::Thread Thread;

#endif //UNTITLED_POCOHEADER_H

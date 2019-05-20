#include "Socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sstream>
#include <stdexcept>

#define BUF_SIZE 500
#define DEBUG false

void TcpSocket::debug(const char message[], std::string output)
{
    if (DEBUG)
    {
        fprintf(stderr, "TcpSocket-Debug");
        (isServer) ? fprintf(stderr, "Server: ") : fprintf(stderr, "Client: ");
        fprintf(stderr, "%s\n", message);
        if (!output.empty())
            fprintf(stderr, "%s\n", output.c_str());
    }
}

TcpSocket::TcpSocket()
{
    this->isServer = false;
    this->_isConnected = false;
}

TcpSocket::TcpSocket(char port[])
{
    isServer = true;
    _isConnected = false;

    debug("Creating server");

    struct addrinfo hints;
    struct addrinfo *result, *rp;
    struct sockaddr_storage _peer_addr;
    this->peer_addr = &_peer_addr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 6;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int s = getaddrinfo(NULL, port, &hints, &result);
    if (s != 0)
    {
        exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        socketFD = socket(rp->ai_family, rp->ai_socktype,
                          rp->ai_protocol);

        if (socketFD == -1)
            continue;

        if (bind(socketFD, rp->ai_addr, rp->ai_addrlen) == 0)
        {
            debug("Bind success");
            break;
        }

        ::close(socketFD);
    }

    if (rp == NULL)
    {
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);

    if (listen(socketFD, 5) == -1)
    {

        fprintf(stderr, "Could not listen\n");
        exit(EXIT_FAILURE);
    }
    debug("Listening");

    peer_addr_len = sizeof(struct sockaddr_storage);
}

void TcpSocket::client(char port[], char host[])
{
    isServer = false;
    _isConnected = false;

    debug("Creating client");

    struct addrinfo hints;
    struct addrinfo *result, *rp;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 6;

    int s = getaddrinfo(host, port, &hints, &result);
    if (s != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        socketFD = socket(rp->ai_family, rp->ai_socktype,
                          rp->ai_protocol);

        if (socketFD == -1)
            continue;

        if (connect(socketFD, rp->ai_addr, rp->ai_addrlen) != -1)
        {
            debug("Connected");
            break;
        }

        ::close(socketFD);
    }

    if (rp == NULL)
    {
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }

    _isConnected = true;

    connectionFD = socketFD;

    freeaddrinfo(result);
}

TcpSocket::TcpSocket(char port[], char host[])
{
    client(port, host);
}

TcpSocket::TcpSocket(std::string port, std::string server)
{
    int portSize = port.size();
    char charPort[portSize + 1];
    int i = 0;
    while (i <= portSize)
    {
        charPort[i] = port[i];
        i++;
    }
    charPort[i] = '\0';

    int serverSize = server.size();
    char charServer[serverSize + 1];
    i = 0;
    while (i <= serverSize)
    {
        charServer[i] = server[i];
        i++;
    }
    charServer[i] = '\0';

    if (DEBUG)
    {
        std::stringstream connection;
        connection << charServer << ":" << charPort;

        debug("Connecting to: ", connection.str());
    }

    client(charPort, charServer);
}

bool TcpSocket::accept()
{
    do
    {
        connectionFD =
            ::accept(
                socketFD,
                (struct sockaddr *)&peer_addr,
                &peer_addr_len);
    } while (connectionFD == -1);

    debug("Connection accepted");

    _isConnected = true;

    return true;
}

bool TcpSocket::read(std::string &recepticle, std::string endTag)
{
    debug("Reading from socket");

    char
        buffer[BUF_SIZE + 1];

    int
        length = 1,
        total = 0,
        noRead = 0,
        endTagLength = 0;

    std::stringstream
        ss;

    while (true)
    {
        bzero(buffer, BUF_SIZE + 1);
        length = ::recv(connectionFD, buffer, BUF_SIZE, 0);

        noRead++;

        debug("Recieved");

        if (length < 0)
        {
            fprintf(stderr, "Error reading from socket\n");
            return false;
        }
        total += length;

        buffer[length] = '\0';
        ss << buffer;

        if (endTag.empty() || (noRead == 1 && length < BUF_SIZE))
        {
            recepticle.assign(ss.str());
            break;
        }

        if (endTagLength == 0)
            endTagLength = endTag.size();
        int i = 0;
        while (endTagLength > 0 && length > 0)
        {
            if (buffer[--length] != endTag[--endTagLength])
                continue;
            i++;
        }

        recepticle.assign(ss.str());

        if (endTagLength > 0)
        {
            i = recepticle.size() - i;
            while (endTagLength > 0 && i > 0)
            {
                if (recepticle[--i] != endTag[--endTagLength])
                    continue;
            }
        }

        break;
    }

    debug("Read done, reciever:", recepticle);
    return (total != 0);
}

bool TcpSocket::write(std::string &message)
{
    debug("Writing to socket:", message);
    int
        pos = 0,
        cut,
        length = message.size(),
        writeLen;

    char
        buffer[BUF_SIZE];

    while (pos < length)
    {
        bzero(buffer, BUF_SIZE);
        cut = ((pos + BUF_SIZE) < length) ? BUF_SIZE : length - pos;

        for (int i = 0; i < cut; i++)
            buffer[i] = message[pos + i];

        writeLen = ::send(connectionFD, buffer, cut, 0);

        pos = cut;

        if (writeLen < 0)
        {
            fprintf(stderr, "Error writing to buffer\n");
            exit(1);
        }

        if (writeLen != cut)
        {
            fprintf(stderr,
                    "Could only write %i chars, %i tried\n",
                    writeLen, cut);
            exit(1);
        }
    }

    debug("Write done");

    return true;
}

bool TcpSocket::isConnected()
{
    return this->_isConnected;
}

bool TcpSocket::close()
{
    debug("Closing socket(s)");
    if (isServer && _isConnected)
        ::close(connectionFD);
    if (_isConnected && ::close(socketFD))
        return true;
    return false;
}

TcpSocket::~TcpSocket()
{
    debug("Destructing");
    this->close();
}

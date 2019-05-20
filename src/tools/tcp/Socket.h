#ifndef TCPSOCKET
#define TCPSOCKET

#include <sys/socket.h>
#include <string>

class TcpSocket
{
public:
    TcpSocket();
    TcpSocket(char port[]);
    TcpSocket(char port[], char host[]);
    TcpSocket(std::string port, std::string host);
    ~TcpSocket();
    bool accept();
    bool read(std::string &recepticle, std::string endTag = "");
    bool write(std::string &message);
    bool close();

    bool isConnected();

private:
    bool
        isServer,
        _isConnected;

    int
        socketFD,
        connectionFD;

    void
        *peer_addr;

    char
        host[],
        port[];

    socklen_t peer_addr_len;
    void client(char port[], char host[]);
    void debug(const char message[], std::string output = "");
};

#endif

#ifndef TCP_UTILS_H
#define TCP_UTILS_H

#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Common constants
constexpr int kPort = 8080;
constexpr int kBufferSize = 1024;

/**
 * Creates a TCP socket for IPv4 communication
 * @return Socket file descriptor, or throws on error
 */
inline int create_socket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        throw std::runtime_error("Socket creation error");
    return sock;
}

#endif // TCP_UTILS_H

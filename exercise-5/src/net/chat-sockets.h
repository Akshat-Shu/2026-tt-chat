#ifndef CHAT_SOCKETS_H
#define CHAT_SOCKETS_H

#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../utils.h"

namespace tt::chat::net {

class Address {
    sockaddr_in address;

public:
    Address(int port);
    sockaddr_in &get_sockaddr() { return address; }
    void set_ip_address(const std::string &ip_address);
    void set_any_address() { set_s_addr(INADDR_ANY); }
    void set_s_addr(in_addr_t s_addr) { address.sin_addr.s_addr = s_addr; }
    socklen_t get_size() const { return sizeof(address); }
};

class Socket {
    int sock;

    Socket(int sock_fd): sock(sock_fd) {}

public:
    Socket();
    ~Socket();
    void set_options(const int level, int const optname, int opt) const;
    void bind_to_address(Address &address) const;
    void connect_to_address(Address &address) const;
    int listen(const int n) const;
    Socket accept(Address &address) const;
    ssize_t read(const size_t buffer_size, char *buffer) const;
    ssize_t send(const size_t buffer_size, const char *buffer, int flags = 0) const;

};


} // namespace tt::chat::net

#endif // CHAT_SOCKETS_H

#include "chat-sockets.h"
#include <sys/socket.h>
#include <string>

tt::chat::net::Socket::Socket() {
  sock = socket(AF_INET, SOCK_STREAM, 0);
  tt::chat::check_error(sock < 0, "Socket creation error\n");
}

// RAII
tt::chat::net::Socket::~Socket() {
  close(sock);
}

void tt::chat::net::Socket::set_options(const int level, const int optname, int opt) const {
  auto err_code = setsockopt(sock, level, optname, &opt, sizeof(opt));
  tt::chat::check_error(err_code < 0, "setsockopt() error\n");
}

void tt::chat::net::Socket::bind_to_address(Address &address) const {
  sockaddr_in &sock_address = address.get_sockaddr();
  auto err_code = bind(sock, (sockaddr *)&sock_address, sizeof(sock_address));
  tt::chat::check_error(err_code < 0, "bind failed\n");
}

void tt::chat::net::Socket::connect_to_address(Address &address) const {
  sockaddr_in &sock_address = address.get_sockaddr();
  auto err_code = connect(sock, (sockaddr *)&sock_address, sizeof(sock_address));
  tt::chat::check_error(err_code < 0, "Connection Failed.\n");
}

int tt::chat::net::Socket::listen(const int n) const {
  int err_code = ::listen(sock, n);
  tt::chat::check_error(err_code < 0, "listen failed\n");
  return err_code;
}

ssize_t tt::chat::net::Socket::read(const size_t buffer_size, char *buffer) const {
  ssize_t read_size = ::read(sock, buffer, buffer_size);
  tt::chat::check_error(read_size < 0, "Read error on socket\n");
  return read_size;
}

ssize_t tt::chat::net::Socket::send(const size_t buffer_size, const char *buffer, int flags) const {
  ssize_t sent_size = ::send(sock, buffer, buffer_size, flags);
  tt::chat::check_error(sent_size < 0, "Send error on socket\n");
  return sent_size;
}

tt::chat::net::Socket tt::chat::net::Socket::accept(Address &address) const {
  sockaddr_in &sock_address = address.get_sockaddr();
  socklen_t address_size = address.get_size();

  int accepted_sock = ::accept(sock, (sockaddr *)&sock_address, &address_size);
  tt::chat::check_error(accepted_sock < 0, "Accept error\n");
  return Socket(accepted_sock);
}

tt::chat::net::Address::Address(int port) {
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
}

void tt::chat::net::Address::set_ip_address(const std::string &ip_address) {
  auto err_code = inet_pton(AF_INET, ip_address.c_str(), &address.sin_addr);
  tt::chat::check_error(err_code <= 0, "Invalid address/ Address not supported\n");
}
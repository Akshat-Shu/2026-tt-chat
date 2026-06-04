#include "tcp_echo_utils.h"
#include <cstdlib>

template <typename T, typename S> void check_error(T test, S error_message) {
  if (test) {
    std::cerr << error_message << "\n";
    exit(EXIT_FAILURE);
  }
}

template void check_error<bool, const char *>(bool, const char *);
template void check_error<bool, std::string>(bool, std::string);

int create_socket() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  check_error(sock < 0, "Socket creation error\n");
  return sock;
}
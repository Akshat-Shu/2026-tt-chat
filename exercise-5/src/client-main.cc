#include <iostream>
#include <string>

#include "net/chat-sockets.h"

namespace tt::chat::client {

const int kBufferSize = 1024;

class Client {
  net::Socket socket;
  net::Address address;
  char buffer[kBufferSize] = {0};

  void connect_to_server(const std::string &server_ip) {
    address.set_ip_address(server_ip);
    socket.connect_to_address(address);
  }

public:
  Client(const std::string &server_ip, int port) : address(port) {
    connect_to_server(server_ip);
  }

  void send_and_receive_message(const std::string &message) {
    socket.send(message.size(), message.c_str());
    std::cout << "Sent: " << message << "\n";

    ssize_t read_size = socket.read(kBufferSize, buffer);
    if (read_size > 0) {
      std::cout << "Received: " << buffer << "\n";
    } else if (read_size == 0) {
      std::cout << "Server closed connection.\n";
    }
  }
};

} // namespace tt::chat::client

std::string read_args(int argc, char *argv[]) {
  std::string message = "Hello from client";
  if (argc == 1) {
    std::cout << "Usage: " << argv[0] << " <message>\n";
    exit(EXIT_FAILURE);
  }
  if (argc > 1) {
    message = argv[1];
  }
  return message;
}

int main(int argc, char *argv[]) {
  const int kPort = 8080;
  const std::string kServerAddress = "127.0.0.1";

  std::string message = read_args(argc, argv);

  tt::chat::client::Client client(kServerAddress, kPort);
  client.send_and_receive_message(message);

  return 0;
}

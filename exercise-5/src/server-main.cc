#include <iostream>
#include "net/chat-sockets.h"

namespace tt::chat::server {

const int kBufferSize = 1024;
class Server {
  tt::chat::net::Socket socket;
  tt::chat::net::Address address;
  char buffer[kBufferSize] = {0};

  void handle_accept(const tt::chat::net::Socket& sock) {
    ssize_t read_size = sock.read(kBufferSize, buffer);

    if (read_size > 0) {
      std::cout << "Received:" << buffer << "\n";
      sock.send(read_size, buffer);
      std::cout << "Echo message sent\n";
    } else if (read_size == 0) {
      std::cout << "Client disconnected.\n";
    } else {
      std::cerr << "Read error on client socket \n";
    }
  }


public:
  Server(int port): address(port) {
    socket.set_options(SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 1);
    address.set_any_address();
    socket.bind_to_address(address);
    socket.listen(3);
  }

  void run_server() {
    while(true) {
      tt::chat::net::Socket accepted_socket = socket.accept(address);
      handle_accept(accepted_socket);
      // accepted socket will be closed when it goes out of scope
    }
  }
};

} // namespace tt::chat::server

int main() {
  const int kPort = 8080;

  tt::chat::server::Server server(kPort);
  std::cout << "Server listening on port " << kPort << "\n";
  server.run_server();

  return 0;
}

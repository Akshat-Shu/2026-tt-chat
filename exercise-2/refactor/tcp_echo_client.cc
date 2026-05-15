#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Constants
constexpr int kPort = 8080;
constexpr int kBufferSize = 1024;
constexpr const char *kServerAddress = "127.0.0.1";

/**
 * Creates a TCP socket for IPv4 communication
 * @return Socket file descriptor, or -1 on error
 */
int create_socket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        std::cerr << "Socket creation error\n";
        return -1;
    }
    return sock;
}

/**
 * Creates a sockaddr_in structure for server connection
 * @param server_address IP address as string
 * @param port Port number in host byte order
 * @return Configured sockaddr_in structure
 */
sockaddr_in create_address(const char *server_address, int port)
{
    sockaddr_in address = {};
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (inet_pton(AF_INET, server_address, &address.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported\n";
    }
    return address;
}

/**
 * Connects socket to remote server
 * @param sock Socket file descriptor
 * @param address Server address structure
 * @return 0 on success, -1 on failure
 */
int connect_to_server(int sock, const sockaddr_in &address)
{
    if (connect(sock, (sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cerr << "Connection Failed\n";
        return -1;
    }
    return 0;
}

/**
 * Sends a message to server and receives the echo response
 * @param sock Connected socket file descriptor
 * @param message Message to send
 */
void send_and_receive_message(int sock, const std::string &message)
{
    send(sock, message.c_str(), message.size(), 0);
    std::cout << "Sent: " << message << "\n";

    char buffer[kBufferSize] = {0};
    ssize_t read_size = read(sock, buffer, kBufferSize);
    std::cout << "Received: " << buffer << "\n";
}

int main(int argc, char *argv[])
{
    std::string message = "Hello from client";
    if (argc > 1)
        message = argv[1];

    int my_sock = create_socket();
    if (my_sock < 0)
        return -1;

    sockaddr_in address = create_address(kServerAddress, kPort);

    if (connect_to_server(my_sock, address) < 0)
        return -1;

    send_and_receive_message(my_sock, message);

    close(my_sock);
    return 0;
}

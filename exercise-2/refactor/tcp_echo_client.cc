#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Constants
constexpr int kPort = 8080;
constexpr int kBufferSize = 1024;
constexpr const char *kServerAddress = "127.0.0.1";
constexpr const char *kDefaultMessage = "Hello from client";

/**
 * Validates and returns the message from command line arguments
 * @param argc Argument count
 * @param argv Argument vector
 * @return Validated message string
 */
std::string get_message(int argc, char *argv[])
{
    if (argv == nullptr)
        throw std::runtime_error("argv is null");

    if (argc > 1)
    {
        if (argv[1] == nullptr || std::string(argv[1]).empty())
            throw std::runtime_error("message argument cannot be empty");
        return argv[1];
    }

    return kDefaultMessage;
}

/**
 * Creates a TCP socket for IPv4 communication
 * @return Socket file descriptor, or -1 on error
 */
int create_socket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        throw std::runtime_error("Socket creation error");
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
        throw std::runtime_error("Invalid address/ Address not supported");
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
        throw std::runtime_error("Connection Failed");
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
    ssize_t read_size = read(sock, buffer, kBufferSize - 1);
    if (read_size > 0)
        buffer[read_size] = '\0';
    std::cout << "Received: " << buffer << "\n";
}

int main(int argc, char *argv[])
{
    try
    {
        std::string message = get_message(argc, argv);

        int my_sock = create_socket();

        sockaddr_in address = create_address(kServerAddress, kPort);

        connect_to_server(my_sock, address);

        send_and_receive_message(my_sock, message);

        close(my_sock);
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return -1;
    }
}

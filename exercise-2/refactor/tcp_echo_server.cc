#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Constants
constexpr int kPort = 8080;
constexpr int kBufferSize = 1024;
constexpr int kListenBacklog = 3;
constexpr int kSocketOptionValue = 1;

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
 * Configures socket options to allow immediate reuse of the port
 * Useful when restarting the server without waiting for TIME_WAIT
 * @param sock Socket file descriptor
 * @return 0 on success, -1 on failure
 */
int set_socket_options(int sock)
{
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &kSocketOptionValue, sizeof(kSocketOptionValue)))
        throw std::runtime_error("setsockopt error");
    return 0;
}

/**
 * Creates a sockaddr_in structure for server binding
 * @param port Port number in host byte order
 * @return sockaddr_in structure configured for INADDR_ANY
 */
sockaddr_in create_address(int port)
{
    sockaddr_in address = {};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    return address;
}

/**
 * Binds a socket to a local address and port
 * @param sock Socket file descriptor
 * @param address Address structure to bind to
 * @return 0 on success, -1 on failure
 */
int bind_address_to_socket(int sock, const sockaddr_in &address)
{
    if (bind(sock, (sockaddr *)&address, sizeof(address)) < 0)
        throw std::runtime_error("bind failed");
    return 0;
}

/**
 * Configures socket to listen for incoming connections
 * @param sock Socket file descriptor
 * @param backlog Maximum number of pending connections
 * @return 0 on success, -1 on failure
 */
int setup_listen(int sock, int backlog)
{
    if (listen(sock, backlog) < 0)
        throw std::runtime_error("listen failed");
    return 0;
}

/**
 * Handles a single client connection
 * Reads a message from the client and echoes it back
 * @param client_socket Socket file descriptor for the client connection
 */
void handle_client(int client_socket)
{
    char buffer[kBufferSize] = {0};
    ssize_t read_size = read(client_socket, buffer, kBufferSize - 1);
    if (read_size > 0)
        buffer[read_size] = '\0';
    std::cout << "Received: " << buffer << "\n";
    send(client_socket, buffer, read_size, 0);
    std::cout << "Echo message sent\n";
    close(client_socket);
}

/**
 * Main server loop: Accepts incoming connections and handles them
 * @param server_socket Listening socket file descriptor
 * @param address Address structure for accepting connections
 */
void accept_connections(int server_socket, sockaddr_in &address)
{
    socklen_t addrlen = sizeof(address);
    std::cout << "Server listening on port " << kPort << "\n";

    while (true)
    {
        int new_sock = accept(server_socket, (struct sockaddr *)&address, &addrlen);
        if (new_sock < 0)
        {
            std::cerr << "accept error\n";
            continue;
        }
        handle_client(new_sock);
    }
}

int main()
{
    try
    {
        int my_sock = create_socket();

        set_socket_options(my_sock);

        sockaddr_in address = create_address(kPort);

        bind_address_to_socket(my_sock, address);

        setup_listen(my_sock, kListenBacklog);

        accept_connections(my_sock, address);

        close(my_sock);
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return -1;
    }
}

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

int main(int argc, char *argv[])
{
    std::string message = "Hello from client";
    if (argc > 1)
        message = argv[1];

    sockaddr_in address;

    char buffer[kBufferSize] = {0};
    int my_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (my_sock < 0)
    {
        std::cerr << "Socket creation error\n";
        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(kPort);
    if (inet_pton(AF_INET, kServerAddress, &address.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported\n";
        return -1;
    }
    if (connect(my_sock, (sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cerr << "Connection Failed\n";
        return -1;
    }
    send(my_sock, message.c_str(), message.size(), 0);
    std::cout << "Sent: " << message << "\n";
    ssize_t read_size = read(my_sock, buffer, kBufferSize);
    std::cout << "Received: " << buffer << "\n";
    close(my_sock);
    return 0;
}

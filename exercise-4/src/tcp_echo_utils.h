#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>

template <typename T, typename S> void check_error(T test, S error_message);

int create_socket();
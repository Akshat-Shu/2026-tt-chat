#ifndef UTILS_H
#define UTILS_H

#include <iostream>

namespace tt::chat {

template <typename T, typename S> void check_error(T test, S error_message) {
  if (test) {
    std::cerr << error_message << "\n";
    throw std::runtime_error(error_message);
  }
}

} // namespace tt::chat

#endif // UTILS_H

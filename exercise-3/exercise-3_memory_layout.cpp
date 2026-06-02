#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>

struct MyStruct {
  int a;
  char c;
  std::vector<int> vec;
  double b;
  char x;
  std::string s;
};

int main() {
    MyStruct s{
        .a = 42, 
        .c = 'A', 
        .vec = {1, 2, 3}, 
        .b = 3.14, 
        .x = 'B', 
        .s = "Hello"};
    auto v1 = s.a;
    auto v2 = s.c;
    auto v3 = s.vec;
    auto v4 = s.b;
    auto v5 = s.x;
    auto v6 = s.s;

    char* ptr = (char*)(&s);
    std::cout << sizeof(MyStruct) << " bytes " << alignof(MyStruct) << " byte alignment\n";
    for (size_t i = 0; i <= sizeof(MyStruct); ++i) {
        printf("%02x ", static_cast<unsigned char>(ptr[i]));
    }


    int x, y, z; 
    std::vector<std::reference_wrapper<int>> v{x, y, z};
}
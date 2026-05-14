#include <iostream>
#include <string>

struct Point
{
    int x, y;
    std::string label;
};

int main()
{
    const std::string message = "Hello, World!";
    std::cout << message << std::endl;

    std::string point_label = "My Point";
    Point point{10, 20, point_label};
    return 0;
}
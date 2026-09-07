
#include <iostream>
#include <string>

int main()
{
    std::string token;
    while(1)
    {
        std::cout << "==>";
        std::getline(std::cin, token);
        std::cout << token << '\n';
    }

    return 0;
}
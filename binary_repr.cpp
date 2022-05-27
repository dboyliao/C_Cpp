#include <iostream>
#include <bitset>

int main(int argc, char const *argv[])
{
    std::cout << std::bitset<sizeof(size_t) * 8>((size_t)7) << std::endl;
    return 0;
}

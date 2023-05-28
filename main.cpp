#include <iostream>

#include "System.h"

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    System system(nullptr);
    system.build();
    return system.run();
}

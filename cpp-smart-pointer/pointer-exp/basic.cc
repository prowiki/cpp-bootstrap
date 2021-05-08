#include <iostream>
#include <memory>

int main()
{
    int x = 10;

    auto shared = std::make_shared<int>(x);

    std::weak_ptr<int> weak;

    shared = nullptr;

    weak = shared;

    std::cout << *weak.lock() << std::endl;

}
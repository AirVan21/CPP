#include <iostream>
#include <map>
#include <vector>
#include <memory>

size_t calculate_fibon(size_t number)
{
    size_t previous = 0;
    size_t current = 1;
    for (size_t i = 1; i < number; ++i)
    {
        size_t save = current;
        current += previous;
        previous = save;
    }
    return current;
}

std::shared_ptr<size_t> get_fibon(size_t number)
{
    static std::map<size_t, std::weak_ptr<size_t>> cache;
    auto& fibon_cache = cache[number];
    if (fibon_cache.expired())
    {
        auto fibon_value = std::make_shared<size_t>(calculate_fibon(number));
        // Moving to cache
        fibon_cache = std::weak_ptr<size_t>(fibon_value);
        std::cout << "Created new fibon!" << std::endl;
        return fibon_value;
    }
    else
    {
        std::cout << "Used cache!" << std::endl;
        return fibon_cache.lock();
    }
}

int main(int argc, char const *argv[])
{
    size_t input = 0;
    std::cout << "Input a positive number = ";
    std::cin >> input;
    // Creating new value in cache
    auto fibon = get_fibon(input);
    std::cout << "Fibon number = " << *fibon << std::endl << std::endl;
    // Reusing cached value
    auto fibon_two = get_fibon(input);
    std::cout << "Fibon number = " << *fibon_two << std::endl << std::endl;
    // Pointer counter should be zero here (weak_ptr is expired)
    fibon.reset();
    fibon_two.reset();
    auto fibon_three = get_fibon(input);
    std::cout << "Fibon number = " << *fibon_three << std::endl;

    return 0;
}
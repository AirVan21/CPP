#include <iostream>
#include <vector>
#include <list>
#include <cassert>

#include "stl_practice.h"

typedef bool (*bool_function)(int);

int main(int argc, char const *argv[])
{
    using std::vector;
    using std::endl;
    using std::cout;
    using namespace std;


    // #1 
    std::vector<int> vec = {1, -3, 5, -7, 11, 11};
    containers::print(vec.begin(), vec.end());

    // #2
    containers::tree_sort(vec.begin(), vec.end());
    containers::print(vec.begin(), vec.end());

    // #3
    std::list<int> lst(vec.begin(), vec.end());
    containers::remove_duplicates(lst);
    containers::print(lst.begin(), lst.end());

    // #4
    assert(!containers::is_palindrom(vec.cbegin(), vec.cend()));

    std::string palindrom = "abbcbba";
    assert(containers::is_palindrom(palindrom.cbegin(), palindrom.cend()));

    // #4 alternative
    assert(!containers::is_palindrom_iterator(vec.cbegin(), vec.cend()));
    palindrom = "abba";
    assert(containers::is_palindrom(palindrom.cbegin(), palindrom.cend()));
    palindrom = "abbcbba";
    assert(containers::is_palindrom(palindrom.cbegin(), palindrom.cend()));

    bool_function even = [](int x) { return x % 2 == 0; };

     cout << palindrom << endl;
     
    return 0;
}
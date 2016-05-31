#include <iostream>

#include "linked_list.h"

using namespace utils;

int main(int argc, char const *argv[])
{
    using namespace std;
    linked_list<int> lst;
    lst.add_sorted(5);
    lst.add_sorted(2);
    lst.add_sorted(1);
    lst.add_sorted(3);

    lst.show();

    return 0;
}

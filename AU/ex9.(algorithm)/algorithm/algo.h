#ifndef ALGO_H
#define ALGO_H

#include <algorithm>

template<class iterator>
using ivt = typename std::iterator_traits<iterator>::value_type;

template<class T, class comparator = std::less<ivt<T>>>
int elem_num_in_sorted(T begin, T end, ivt<T> target, comparator test = comparator())
{
    auto low = std::lower_bound(begin, end, target, test);
    auto up  = std::upper_bound(begin, end, target, test);

    return up - low;
}

template<class Container, class Pred>
void erase_if(Container& container, Pred pred)
{
    container.erase(std::remove_if(container.begin(), container.end(), pred), container.end());
}

template<class Iterator>
void print(Iterator begin, Iterator end)
{
    while(begin != end) 
    {
        std::cout << *begin << " ";
        begin++;
    }

    std::cout << std::endl;
}

template<class Iterator, class Comparator>
void merge_sort(Iterator begin, Iterator end)
{
    printf("%d\n", std::distance(begin, end));
}

#endif // ALGO_H

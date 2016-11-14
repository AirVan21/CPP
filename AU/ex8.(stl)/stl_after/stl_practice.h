#ifndef stl_practice
#define stl_practice

#include <set>
#include <unordered_set>
#include <list>
#include <stack>

namespace containers
{


template<class container>
using container_type = typename std::iterator_traits<container>::value_type;

template<class fwd_it>
void print(fwd_it begin, fwd_it end)
{
    using std::cout;
    using std::endl;

    for (auto it = begin; it != end; it++)  
    {
        cout << *it << " ";
    }
    cout << endl;
}

template<class fwd_it, class comparator = std::less<typename fwd_it::value_type>>
void tree_sort(fwd_it begin, fwd_it end)
{
    typedef typename fwd_it::value_type type;
    std::multiset<type, comparator> mset;

    for (fwd_it it = begin; it != end; it++)
    {
        mset.insert(*it);
    }

    for (auto it = begin, mset_it = mset.cbegin(); it != end; it++, mset_it++)
    {
        *it = *mset_it;
    }
}

template<class T, class pred = std::equal_to<T>>
void remove_duplicates(std::list<T>& lst)
{
    std::unordered_set<T, std::hash<T>, pred> unord_set;

    for (auto it = lst.begin(); it != lst.end();)
    {
        auto result = unord_set.insert(*it);
        if (!result.second)
        {
            lst.erase(it++);
        } 
        else
        {
            it++;
        }
    }
}

template<class cbd_it>
bool is_palindrom(cbd_it begin, cbd_it end)
{
    typedef typename std::iterator_traits<cbd_it>::value_type T;
    std::stack<T> stack;
    for (auto it = begin; it != end; it++)
    {
        stack.push(*it);
    }

    cbd_it it = begin;
    while (!stack.empty())
    {
        if (stack.top() != *it)
            return false;
        stack.pop();
        ++it;
    }

    return true;
}

template<class cbd_it, class pred = std::equal_to<typename std::iterator_traits<cbd_it>::value_type>>
bool is_palindrom_iterator(cbd_it begin, cbd_it end)
{
    std::reverse_iterator<cbd_it> rev_it(end);
    pred eq;

    for (auto it = begin; it != end; it++, rev_it++)
    {
        if (!eq(*rev_it, *it))
        {
            return false;
        }
    }
    return true;
}

}

#endif // stl_practice
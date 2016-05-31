#include <iostream>

namespace utils
{

template<class T>
class linked_list
{

public:
    linked_list()
    : head_(nullptr)
    , tail_(nullptr)
    {}

    void add(T element)
    {
        list_node* to_add = new list_node(element);
        to_add->next_ = head_;
        head_ = to_add;
    }

    void add_sorted(T element)
    {
      list_node* to_add = new list_node(element);

      if (head_ == nullptr || head_->value_ > element)
      {
        to_add->next_ = head_;
        head_ = to_add;
        return;
      }

      list_node* current = head_;
      while (current->next_ != nullptr && current->next_->value_ < element) {
        current = current->next_;
      }

      to_add->next_ = current->next_;
      current->next_ = to_add;

    }

    void show() const noexcept
    {
        list_node* current = head_;
        while (current != nullptr) {
            std::cout << current->value_ << " ";
            current = current->next_;
        }

        std::cout << std::endl;
    }

    void show_reversed() const
    {

    }

private:
    struct list_node
    {
        list_node(const T& value, list_node* next)
        : value_(value)
        , next_(next)
        {}

        list_node(T value)
        : value_(value)
        , next_(nullptr)
        {}

        T value_;
        list_node* next_;
    };

private:
    list_node* head_;
    list_node* tail_;
};

}

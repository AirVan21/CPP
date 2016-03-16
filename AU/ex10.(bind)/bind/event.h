#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <map>

namespace utils
{

template <class>
class event;

template<class R, class ARG1, class ARG2>
class event<R(ARG1, ARG2)>
{
public:

    typedef std::function<R(ARG1, ARG2)> handler_t;
    typedef std::function<void()> deleter_t;

    event()
        : id_(0)
    {}

    event(event&& other) = default;
    event(const event& other) = delete;

    event& operator=(event&& other) = default;
    event& operator=(const event& other) = delete;
    event& operator=(event other) = delete;

    deleter_t add(handler_t&& callback)
    {
        id_++;

        storage_.insert(make_pair(id_, std::move(callback)));
        return [this]() { this->storage_.erase(this->storage_.find(this->id_)); };
    }

    void fire(ARG1 fst, ARG2 snd)
    {
        for (auto& entity: storage_)
        {
            entity.second(fst, snd);
        }
    }

private:
    size_t id_;
    std::map<size_t, handler_t> storage_;
};

}
#endif // EVENT_H


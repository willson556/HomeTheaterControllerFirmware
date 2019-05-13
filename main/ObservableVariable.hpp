#pragma once

#include <functional>
#include <vector>

template <typename T>
class ObservableVariable
{
public:
    using Callback = std::function<void(T)>;

    ObservableVariable(T value)
        : value{value}
    {
    }

    T get() { return value; }

    void set(T new_value)
    {
        value = new_value;

        for (auto &callback : callbacks)
        {
            if (callback) callback(new_value);
        }
    }

    void add_observer(std::function<void(T)> o)
    {
        callbacks.push_back(o);
    }

private:
    T value;
    std::vector<std::function<void(T)>> callbacks {};
};
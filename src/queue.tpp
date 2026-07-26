#include "queue.h"
#include <stdexcept>

template <typename T>
void queue<T>::push(const T& obj)
{
    q.insertBack(obj);
}

template <typename T>
T queue<T>::pop()
{   
    if(this->empty())
    {
        throw std::runtime_error("queue is empty");
    }
    T front = q.getFront();
    q.deleteFront();
    return front;
}

template <typename T>
int queue<T>::size() const
{
    return q.size();
}

template <typename T>
bool queue<T>::empty() const
{
    return q.size() == 0;
}
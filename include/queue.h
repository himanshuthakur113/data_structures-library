#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"

template <typename T>
class queue
{
    private:
        LinkedList<T> q;
    
    public:
        void push(const T &obj);
        T pop();
        int size() const;
        bool empty() const;
};

#include "queue.tpp"
#endif
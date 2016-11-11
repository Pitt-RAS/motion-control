#ifndef MOTION_CONTROL_INSTANCE_LIST_NODE_H
#define MOTION_CONTROL_INSTANCE_LIST_NODE_H

#include <cstddef>

namespace MotionControl
{

template <class T> class InstanceLinkedList;

template <class T>
class InstanceListNode
{
public:
    InstanceListNode(T element);
    ~InstanceListNode();

    InstanceListNode<T>* get_next();
    InstanceListNode<T>* get_prev();
    bool in_list();

    T get();
private:
    friend class InstanceLinkedList<T>;
    InstanceLinkedList<T>* list;
    InstanceListNode<T>* prev;
    InstanceListNode<T>* next;
    T element;
};

template <class T> InstanceListNode<T>::InstanceListNode(T element)
{
    list = nullptr;
    prev = nullptr;
    next = nullptr;
    this->element = element;
}

template <class T> InstanceListNode<T>::~InstanceListNode()
{
    if ( list != nullptr )
        list->remove(this);
}

template <class T> bool InstanceListNode<T>::in_list()
{
    return list != nullptr;
}

template <class T> InstanceListNode<T>* InstanceListNode<T>::get_next()
{
    return next;
}

template <class T> InstanceListNode<T>* InstanceListNode<T>::get_prev()
{
    return prev;
}

template <class T> T InstanceListNode<T>::get()
{
    return element;
}

}

#endif

#ifndef MOTION_CONTROL_INSTANCE_LINKED_LIST_H
#define MOTION_CONTROL_INSTANCE_LINKED_LIST_H

#include <motion_control/instance_list_node.h>

#include <cstddef>

namespace MotionControl
{
template <class T>
class InstanceLinkedList
{
public:
    InstanceLinkedList();
    ~InstanceLinkedList();
    void add(InstanceListNode<T>* n);
    void remove(InstanceListNode<T>* n);
    InstanceListNode<T>* get_root();
private:
    InstanceListNode<T>* root;
    InstanceListNode<T>* end;
};

template <class T>
InstanceLinkedList<T>::InstanceLinkedList()
{
    root = nullptr;
    end = nullptr;
}

template <class T>
InstanceLinkedList<T>::~InstanceLinkedList()
{
    while ( root != nullptr )
        remove(root);
}

template <class T>
void InstanceLinkedList<T>::add(InstanceListNode<T>* n)
{
    if ( end == nullptr )
    {
        root = n;
        end = n;
        n->next = nullptr;
        n->prev = nullptr;
    }
    else
    {
        end->next = n;
        n->prev = end;
        n->next = nullptr;
        end = n;
    }

    n->list = this;
}

template <class T>
void InstanceLinkedList<T>::remove(InstanceListNode<T>* n)
{
    if ( n->list != this )
        return;

    if ( n->next != nullptr )
        n->next->prev = n->prev;
    else
        end = n->prev;

    if ( n->prev != nullptr )
        n->prev->next = n->next;
    else
        root = n->next;

    n->list = nullptr;
}

template<class T>
InstanceListNode<T>* InstanceLinkedList<T>::get_root()
{
    return root;
}


};

#endif

#ifndef MOTION_CONTROL_INSTANCE_LINKED_LIST_H
#define MOTION_CONTROL_INSTANCE_LINKED_LIST_H

#include <motion_control/instance_list_node.h>

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
    root = 0;
    end = 0;
}

template <class T>
InstanceLinkedList<T>::~InstanceLinkedList()
{
    while ( root != 0 )
        remove(root);
}

template <class T>
void InstanceLinkedList<T>::add(InstanceListNode<T>* n)
{
    if ( end == 0 )
    {
        root = n;
        end = n;
        n->next = 0;
        n->prev = 0;
    }
    else
    {
        end->next = n;
        n->prev = end;
        n->next = 0;
        end = n;
    }

    n->list = this;
}

template <class T>
void InstanceLinkedList<T>::remove(InstanceListNode<T>* n)
{
    if ( n->list != this )
        return;

    if ( n->next != 0 )
        n->next->prev = n->prev;
    else
        end = n->prev;

    if ( n->prev != 0 )
        n->prev->next = n->next;
    else
        root = n->next;

    n->list = 0;
}

template<class T>
InstanceListNode<T>* InstanceLinkedList<T>::get_root()
{
    return root;
}


};

#endif

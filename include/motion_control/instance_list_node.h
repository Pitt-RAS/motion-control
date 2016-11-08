#ifndef MOTION_CONTROL_INSTANCE_LIST_NODE_H
#define MOTION_CONTROL_INSTANCE_LIST_NODE_H

namespace MotionControl
{

template <class T> class InstanceLinkedList;

template <class T>
class InstanceListNode
{
public:
    InstanceLinkedList<T>* list;
    InstanceListNode<T>* prev;
    InstanceListNode<T>* next;

    InstanceListNode(T element);
    ~InstanceListNode();

    T get();
private:
    T element;
};

template <class T> InstanceListNode<T>::InstanceListNode(T element)
{
    list = 0;
    prev = 0;
    next = 0;
    this->element = element;
}

template <class T> InstanceListNode<T>::~InstanceListNode()
{
    if ( list != 0 )
        list->remove(this);
}

template <class T> T InstanceListNode<T>::get()
{
    return element;
}

};

#endif

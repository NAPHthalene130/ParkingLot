#ifndef NODE_H
#define NODE_H

template<typename T>
class Node
{
public:
    T value;
    Node<T> *preNode;
    Node<T> *nextNode;
    Node() {}
};

#endif // NODE_H

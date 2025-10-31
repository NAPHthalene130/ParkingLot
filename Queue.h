#include "Node.h"
#include <stdexcept>
#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
template<typename T>
class Queue
{
private:
    Node<T> *frontNode;
    Node<T> *railNode;
    Node<T> *beginNode;
    int queueSize = 0;

public:
    Queue()
    {
        beginNode = new Node<T>();
        beginNode->nextNode = nullptr;
        frontNode = beginNode;
        railNode = beginNode;
        queueSize = 0;
    }
    ~Queue()
    {
        Node<T> *nowNode = beginNode;
        while (nowNode != nullptr) {
            Node<T> *nextNode = nowNode->nextNode;
            delete nowNode;
            nowNode = nextNode;
        }
    }
    void push(T value)
    {
        Node<T> *newNode = new Node<T>;
        if (queueSize == 0) {
            frontNode = newNode;
            beginNode->nextNode = frontNode;
            newNode->nextNode = nullptr;
            newNode->value = value;
            railNode = newNode;
            queueSize++;
        } else {
            newNode->nextNode = nullptr;
            newNode->value = value;
            railNode->nextNode = newNode;
            railNode = newNode;
            queueSize++;
        }
    }
    T pop()
    {
        if (queueSize == 0) {
            throw std::runtime_error("ERROR: Queue is empty");
        } else {
            if (queueSize == 1) {
                T value = frontNode->value;
                delete frontNode;
                frontNode = beginNode;
                railNode = beginNode;
                beginNode->nextNode = nullptr;;
                queueSize--;
                return value;
            } else {
                T value = frontNode->value;
                Node<T> *nextNode = frontNode->nextNode;
                delete frontNode;
                frontNode = nextNode;
                beginNode->nextNode = nextNode;
                queueSize--;
                return value;
            }
        }
    }
    int size() {
        return queueSize;
    }
    void clear() {
        using std::cout;
        using std::endl;
        while (queueSize > 0) {
            cout << "TEST1" << endl;
            pop();
        }
    }
};
#endif // QUEUE_H

#include "Node.h"
#include <stdexcept>
#ifndef QUEUE_H
#define QUEUE_H
template <typename T>
class Queue
{
private:
    Node<T>* frontNode;
    Node<T>* railNode;
    Node<T>* beginNode;
    int queueSize = 0;
public:
    Queue() {
        beginNode = new Node<T>();
        beginNode->nextNode = nullptr;
        frontNode = beginNode;
        railNode = beginNode;
        int size = 0;
    }
    ~Queue() {
        Node<T>* nowNode = beginNode;
        while (nowNode != nullptr) {
            Node<T>* nextNode = nowNode->nextNode;
            delete nowNode;
            nowNode = nextNode;
        }
    }
    void push(T value) {
        Node<T>* newNode = new Node<T>;
        newNode->nextNode = nullptr;
        newNode->value = value;
        railNode->nextNode = newNode;
        queueSize++;
    }
    T pop() {
        if (queueSize == 0) {
            throw std::runtime_error("ERROR: Queue is empty");
        } else {
            T value = frontNode->value;
            Node<T>* nextNode = frontNode->nextNode;
            delete frontNode;
            frontNode = nextNode;
            beginNode->nextNode = nextNode;
            queueSize--;
            return value;
        }
    }
};
#endif // QUEUE_H

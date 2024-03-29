#include<iostream>
#include<stdexcept>

class BadInput : public std::exception {
public:
    const char* what() const noexcept override {
        return "Bad Input Exception";
    }
};
class OutOfBounds : public std::runtime_error {
public:
    OutOfBounds() : std::runtime_error("Index out of bounds") {}
};



template<class T>
class Node {
public:
    T data;
    Node<T>* next;
};

template<class T>
class LinkedQueue {
    // FIFO objects
public:
    LinkedQueue() { front = rear = 0; }
    ~LinkedQueue();
    bool IsEmpty() const
    {
        return ((front) ? false : true);
    }
    T First() const; // return first element
    T Last() const; // return last element
    int Size() const {
        int count = 0;
        Node<T>* current = front;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }
    LinkedQueue<T>& Add(const T& x);
    LinkedQueue<T>& Delete(T& x) { //删除第一个元素，并将其放入x
        if (IsEmpty()) throw OutOfBounds();
        x = front->data;
        Node<T>* p = front;
        front = front->next;
        delete p;
        return *this;
    }
    LinkedQueue<T>& Delete(){ //弹出第一个元素
        if (IsEmpty()) throw OutOfBounds();
        Node<T>* p = front;
        front = front->next;
        delete p;
        return *this;
    }
private:
    Node<T>* front;  // pointer to first node
    Node<T>* rear;   // pointer to last node
};

template<class T>
LinkedQueue<T>::~LinkedQueue()
{ // Queue destructor.  Delete all nodes.
    Node<T>* next;
    while (front) {
        next = front->next; delete front;  front = next;
    }
}

template<class T>
T LinkedQueue<T>::First() const
{ //返回队列的第一个元素
    if (IsEmpty()) throw OutOfBounds();
    return front->data;
} //Program 6-5

template<class T>
T LinkedQueue<T>::Last() const
{ //返回队列的最后一个元素
    if (IsEmpty()) throw OutOfBounds();
    return rear->data;
} //Program 6-5

template<class T>
LinkedQueue<T>& LinkedQueue<T>::Add(const T& x)
{
    Node<T>* p = new Node<T>;
    p->data = x;
    p->next = 0;
    if (front)  rear->next = p; // queue not empty
    else front = p; 		// queue empty
    rear = p;
    return *this;
}


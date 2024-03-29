#include <exception>
#include <iostream>
#include <string>
using namespace std;

class  OutOfBounds1 : public std::exception {
public:
     const char* what()  noexcept {
        return "Empty!";
    }
};

class  OutOfBounds0 : public std::exception {
public:
    const char* what()  noexcept {
        return "0<k<=N!";
    }
};

class  NoMem : public std::exception {
public:
    const char* what()  noexcept {
        return "there is no more room.";
    }
};

template<class T>
class Stack {
public:
    Stack(int MaxStackSize = 100);
    ~Stack() { delete[] stack; }
    bool IsEmpty()  { return top == -1; }
    bool IsFull()  { return top == MaxTop; }
    T Top() ;
    void get_max() ;
    Stack<T>& Add(T& x);

    Stack<T>& Delete(T& x);
    Stack<T>& Delete();
    void show() ;
    T* getstack() {
        return stack;
    }
    int gettop() {
        return top;
    }
private:
    int top;      // current top of stack
    int MaxTop; // max value for top
    T* stack;    // element array
};

template<class T>
Stack<T>::Stack(int MaxStackSize)
{// Stack constructor.
    MaxTop = MaxStackSize - 1;
    stack = new T[MaxStackSize];
    top = -1;
}
template<class T>
T Stack<T>::Top() 
{// Return top element.
    if (IsEmpty()) throw OutOfBounds1(); // Top fails
    return stack[top];
}

template<class T>
Stack<T>& Stack<T>::Add(T& x)
{// Add x to stack.
    if (IsFull()) throw NoMem(); // add fails
    stack[++top] = x;
    return *this;
}

template<class T>
Stack<T>& Stack<T>::Delete(T& x)
{// Delete top element and put in x.
    if (IsEmpty()) throw OutOfBounds1(); //delete fails
    x = stack[top--];
    return *this;
}

template<class T>
Stack<T>& Stack<T>::Delete()
{
    if (IsEmpty()) throw OutOfBounds1(); //delete fails
    top--;
    return *this;
}

template<class T>
void Stack<T>::show() {
    for (int i = 0; i <= top; i++)
        std::cout << stack[i] << " ";
    std::cout << std::endl;
}
template<class T>
void Stack<T>::get_max() 
{
    T max = 0;
    for (int i = 0; i <= top; i++)
        if (stack[i] > max)
            max = stack[i];
    std::cout << max << std::endl;
}
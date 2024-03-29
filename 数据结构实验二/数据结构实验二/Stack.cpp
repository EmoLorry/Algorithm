#include <exception>
#include <iostream>

class  OutOfBounds : public std::exception {
public:
    const char* what() const noexcept {
        return "the value is out of bounds.";
    }
};

class  NoMem : public std::exception {
public:
    const char* what() const noexcept {
        return "there is no more room.";
    }
};

template<class T>
class Stack {
public:
    Stack(int MaxStackSize = 100);
    ~Stack() { delete[] stack; }
    bool IsEmpty() const { return top == -1; }
    bool IsFull() const { return top == MaxTop; }
    T Top() const;
    void get_max() const;
    Stack<T>& Add(const T& x);
    
    Stack<T>& Delete(T& x);
    Stack<T>& Delete();
    
    Stack<T>& DeleteTheSame();
    void show() const;
    void friend infixStackToPostfixStack(char stack[], Stack<char>&,int len);
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
T Stack<T>::Top() const
{// Return top element.
    if (IsEmpty()) throw OutOfBounds(); // Top fails
    return stack[top];
}

template<class T>
Stack<T>& Stack<T>::Add(const T& x)
{// Add x to stack.
    if (IsFull()) throw NoMem(); // add fails
    stack[++top] = x;
    return *this;
}

template<class T>
Stack<T>& Stack<T>::Delete(T& x)
{// Delete top element and put in x.
    if (IsEmpty()) throw OutOfBounds(); //delete fails
    x = stack[top--];
    return *this;
}

template<class T>
Stack<T>& Stack<T>::Delete()
{   if (IsEmpty()) throw OutOfBounds(); //delete fails
    top--;
    return *this;
}
#include<iostream>
using namespace std;

void OutOfBounds() {cout << "Index is out of bounds";}
void NoMem() {cout << "This is no room for the add of 'x'";}

template<class T>
class Stack { 
public:
    Stack(int MaxStackSize = 10);
    ~Stack() { delete[] stack; }
    bool IsEmpty() const { return top == -1; }
    bool IsFull() const { return top == MaxTop; }
    T Top() const;
    Stack<T>& Add(const T& x);
    Stack<T>& Delete(T& x);
private:
    int top;    
    int MaxTop; 
    T* stack;    
};

template<class T>
Stack<T>::Stack(int MaxStackSize)
{
    MaxTop = MaxStackSize - 1;
    stack = new T[MaxStackSize];
    top = -1;
}

template<class T>
T Stack<T>::Top() const
{
    if (IsEmpty()) throw OutOfBounds(); 
    return stack[top];
}

template<class T>
Stack<T>& Stack<T>::Add(const T& x)
{
    if (IsFull()) throw NoMem(); 
    stack[++top] = x;
    return *this;
}

template<class T>
Stack<T>& Stack<T>::Delete(T& x)
{
    if (IsEmpty()) throw OutOfBounds(); 
    x = stack[top--];
    return *this;
} 

int main() {
    const int n = 10;
    Stack<int> MyStack(n);
    cout << "��������1������ջ����������2���г�ջ����������3��ȡջ��Ԫ�أ�";
    cout << "��������4�ж��Ƿ�Ϊ��ջ������5��������ϲ����������������ջ������0��ȡ���ֵ��";
    cout << "��������6";




    return 0;
}
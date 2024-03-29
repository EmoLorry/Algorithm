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
    cout << "输入数字1进行入栈；输入数字2进行出栈；输入数字3获取栈顶元素；";
    cout << "输入数字4判断是否为空栈；输入5进行两项合并消除操作并输出新栈；输入0获取最大值；";
    cout << "输入数字6";




    return 0;
}
#include"Stack.cpp"
#include <exception>
#include <iostream>
#include <string>
using namespace std;

template<class T>
class QueueUsingStacks {
public:
    QueueUsingStacks(int MaxStackSize = 100)
        : inputStack(MaxStackSize), outputStack(MaxStackSize) {
    }

    bool IsEmpty()  {
        return inputStack.IsEmpty() && outputStack.IsEmpty();
    }


    bool IsFull()  {
        return inputStack.IsFull() || outputStack.IsFull();
    }

    int count() {
        return (inputStack.gettop() + outputStack.gettop() + 2);
    }

    void Enqueue(T& x) {
        if (IsFull()) throw NoMem(); 
        inputStack.Add(x);
    }

    void Dequeue_back() {
        if (IsEmpty()) throw OutOfBounds();
        if (inputStack.IsEmpty()) {

            while (!outputStack.IsEmpty()) {
                T temp;
                outputStack.Delete(temp);
                inputStack.Add(temp);
            }
        }
        inputStack.Delete();
    }

    void Dequeue_front() {
        if (IsEmpty()) throw OutOfBounds();
        if (outputStack.IsEmpty()) {
            while (!inputStack.IsEmpty()) {
                T temp;
                inputStack.Delete(temp);
                outputStack.Add(temp);
            }
        }
        outputStack.Delete();
    }


    T peek_front() {
        if (IsEmpty()) throw OutOfBounds(); 
        if (outputStack.IsEmpty()) {
      
            while (!inputStack.IsEmpty()) {
                T temp;
                inputStack.Delete(temp);
                outputStack.Add(temp);
            }
        }
        return outputStack.Top(); 
    }

    T peek_back() {
        if (IsEmpty()) throw OutOfBounds(); 
        if (inputStack.IsEmpty()) {
            
            while (!outputStack.IsEmpty()) {
                T temp;
                outputStack.Delete(temp);
                inputStack.Add(temp);
            }
        }
        return inputStack.Top();
    }

private:
    Stack<T> inputStack; 
    Stack<T> outputStack; 
};

int main() {
    QueueUsingStacks<int> queue;
    std::cout << "输入任意非数字字符表示结束" << std::endl;
    int t;

    try{
    while (std::cin >> t) {
        queue.Enqueue(t);
    }
   
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Front of the queue: " << queue.peek_front() << endl; 
    cout << "Back of the queue: " << queue.peek_back() << endl;
    
    cout << "input '0' to delete the front of the queue,and '1' to push new element to the back,and '2' to delete the back of the queue,and inintergers to stop the program";
    cout << endl;
    int is = 0;
    while (cin >> is)
    {
        if (is==1) {
            int temp = 0;
            cin >> temp;
            queue.Enqueue(temp);
        }
        else if (is == 0) {
            queue.Dequeue_front();
        }
        else if(is==2)
        {
            queue.Dequeue_back();
        }
        else
            break;
        cout << "Front of the queue: " << queue.peek_front() << endl;
        cout << "Back of the queue: " << queue.peek_back() << endl;
    }
    }catch(OutOfBounds&e){
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }catch(NoMem&e){ std::cerr << "Exception caught: " << e.what() << std::endl; 
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Input N to set the length of the nums" << endl;
    int N = 0; cin >> N;
    int nums[100];
    int d = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> d;
        *(nums + i) = d;
    }

   try{
    cout << "set the k" << endl;
    int k; cin >> k;
    if (k <= 0 || k > N) throw OutOfBounds0();

    for (int i = 0; i < N-k+1; i++) {
        QueueUsingStacks<int> PromoteQueue;
        QueueUsingStacks<int> TempQueue;
        for (int j = i; j < i + k ; j++)
        {
         
            if (PromoteQueue.IsEmpty() || nums[j] >= PromoteQueue.peek_back())
                PromoteQueue.Enqueue(nums[j]);
            else 
            {
                if (PromoteQueue.count() == 1)
                {
                    int temp = PromoteQueue.peek_front();
                    PromoteQueue.Dequeue_front();
                    TempQueue.Enqueue(nums[j]);
                    TempQueue.Enqueue(temp);
                    while (!TempQueue.IsEmpty())
                    {
                        int temp = TempQueue.peek_front();
                        TempQueue.Dequeue_front();
                        PromoteQueue.Enqueue(temp);
                    }

                }
                else
                {
                    if (nums[j] < PromoteQueue.peek_front())
                    {
                        TempQueue.Enqueue(nums[j]);
                        while (!PromoteQueue.IsEmpty())
                        {
                            int temp = PromoteQueue.peek_front();
                            PromoteQueue.Dequeue_front();
                            TempQueue.Enqueue(temp);
                        }
                        while (!TempQueue.IsEmpty())
                        {
                            int temp = TempQueue.peek_front();
                            TempQueue.Dequeue_front();
                            PromoteQueue.Enqueue(temp);
                        }
                    }
                    else
                    {
                    while(!(PromoteQueue.peek_front()>nums[j]&&TempQueue.peek_back()<=nums[j]))
                    {
                        int temp = PromoteQueue.peek_front();
                        PromoteQueue.Dequeue_front();
                        TempQueue.Enqueue(temp);
                    }
                    TempQueue.Enqueue(nums[j]);
                    while (!PromoteQueue.IsEmpty())
                    {
                        int temp = PromoteQueue.peek_front();
                        PromoteQueue.Dequeue_front();
                        TempQueue.Enqueue(temp);
                    }
                    while (!TempQueue.IsEmpty())
                    {
                        int temp = TempQueue.peek_front();
                        TempQueue.Dequeue_front();
                        PromoteQueue.Enqueue(temp);
                    }
                    }
                }

            }
        }
        cout << PromoteQueue.peek_front() << " ";



    }
   }
   catch (OutOfBounds0& e) { std::cerr << "Exception caught: " << e.what() << std::endl; }




    return 0;
}

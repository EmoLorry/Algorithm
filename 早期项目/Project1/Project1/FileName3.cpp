#include<iostream>
#include<stdexcept>
using namespace std;


class Chain;

class ChainNode {
public:
	ChainNode(int item) : data(item), next(nullptr) {}
	friend Chain;

	int data=0;
	ChainNode* next = nullptr;//初始化指向空
};


class Chain {
public:
	Chain() { first = nullptr; }
	~Chain() {
		ChainNode* current = first;
		while (current != nullptr) {
			ChainNode* temp = current;
			current = current->next;
			delete temp;
		}
		first = nullptr;
	};

	void Insert(int x);
	//f presients modes(0 ->the positive order and 1-> the reserve order)

	

	//打印链表
	void Display() {
		ChainNode* current = first;
		while (current != nullptr) {
			if (current->next != nullptr)
				cout << current->data << "->";
			else
				cout << current->data;
			current = current->next;
		}
		cout << endl;
	};



	ChainNode* first;
};




void Chain::Insert(int x)
{
	ChainNode* p = first;  //使用p指向原Chain中首元素
	ChainNode* temp = new ChainNode(x);// 建立并初始化待插入新节点

	if (first == nullptr) {
		//链表头指针为空，即链表未建立
		first = temp;
	}
	else
		while (p->next != nullptr)
			p->next == temp;
	
	 p->next = temp;
		
		
	return;//返回
}



int main() {
	cout << "输入链表A，输入字符任意非数字符号表示结束" << endl;
	int t = 0;
	Chain A;
	while (cin >> t)
	{
		A.Insert(t);
	}
	cout << "链表A如下：";
	A.Display();

	// 重置 cin 的状态和清除输入缓冲区
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "输入链表B，输入字符任意非数字符号表示结束" << endl;
	Chain B;
	while (cin >> t)
	{
		B.Insert(t);
	}
	cout << "链表B如下：";
	B.Display();

	
	return 0;
}
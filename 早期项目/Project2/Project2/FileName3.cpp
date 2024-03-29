#include<iostream>
#include<stdexcept>
using namespace std;


class Chain;

class ChainNode {
public:
	ChainNode(int item) : data(item), next(nullptr) {}
	friend Chain;

	int data = 0;
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

	void Add(int x);

	//倒置链表
	void Reverse(){
		ChainNode* prev = nullptr;
		ChainNode* current = first;
		ChainNode* next = nullptr;

		while (current != nullptr) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}

		first = prev;
	}

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





	void Chain::Add(int x)
	{
		ChainNode* temp = new ChainNode(x);  // 创建一个新节点

		// 将新节点的next指向当前的第一个节点
		temp->next = first;

		// 更新链表的第一个节点为新节点
		first = temp;
	}

	Chain AddTwoChains(Chain& A, Chain& B) {
		Chain result; // 用于存储结果的链表
		int carry = 0; // 进位初始化为0

		ChainNode* nodeA = A.first;
		ChainNode* nodeB = B.first;

		while (nodeA != nullptr || nodeB != nullptr || carry != 0) {
			int sum = carry;
			if (nodeA != nullptr) {
				sum += nodeA->data;
				nodeA = nodeA->next;
			}
			if (nodeB != nullptr) {
				sum += nodeB->data;
				nodeB = nodeB->next;
			}

			carry = sum / 10; // 计算进位
			sum %= 10; // 计算当前位的值

			result.Add(sum); // 将当前位的值添加到结果链表
			

		}
		result.Reverse();
		return result;
	}


int main() {
	cout << "输入链表D，输入字符任意非数字符号表示结束" << endl;
	int t = 0;
	Chain D;
	while (cin>>t)
	{
		D.Add(t);
	}
	cout << "链表D如下：";
	D.Display();

	// 重置 cin 的状态和清除输入缓冲区
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "输入链表E，输入字符任意非数字符号表示结束" << endl;
	Chain E;
	while (cin>>t)
	{
		E.Add(t);
	}
	cout << "链表E如下：";
	E.Display();

	cout << "链表F如下：";
	Chain F = AddTwoChains(D, E);
	F.Display();

	return 0;
}
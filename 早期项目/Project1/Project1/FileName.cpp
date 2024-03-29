#include<iostream>
#include<stdexcept>
using namespace std;

template<class T>
class Chain;

template<class T>
class ChainNode {
public:
	ChainNode(const T& item) : data(item), next(nullptr) {}
	friend Chain<T>;
	
	T data;
	ChainNode<T>* next=nullptr;//初始化指向空
};

template<class T>
class Chain {
public:
	Chain() { first = nullptr; }
	~Chain() {
		ChainNode<T>* current = first;
		while (current != nullptr) {
			ChainNode<T>* temp = current;
			current = current->next;
			delete temp;
		}
		first = nullptr;
	};
	
	//新元素加在链表头部的初始化方式
	void Add(int x)
	{
		ChainNode<T>* temp = new ChainNode<T>(x);  // 创建一个新节点

		// 将新节点的next指向当前的第一个节点
		temp->next = first;

		// 更新链表的第一个节点为新节点0
		first = temp;
	}
	
	//f presients modes(0 ->the positive order and 1-> the reserve order)
	void Insert(int f, const T& x);
    
	
	//去重
	void RemoveDuplicates();
	
	//合并链表
	friend void CombineToC(Chain<T>& C, Chain<T>& A, Chain<T>& B);
	
	//第二问
	void RemoveKthFromEnd(int);
	
	//打印链表
	void Display() {
		ChainNode<T>* current = first;
		while (current != nullptr) {
			if (current->next != nullptr)
				cout << current->data << "->";
			else
				cout << current->data;
			current = current->next;
		}
		cout << endl;
	}
	//倒置链表
	void Reverse() {
		ChainNode<T>* prev = nullptr;
		ChainNode<T>* current = first;
		ChainNode<T>* next = nullptr;

		while (current != nullptr) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}

		first = prev;
	}
    
	

	ChainNode<T>* first;
};

template<class T>
Chain<T> AddTwoChains(Chain<T>& A, Chain<T>& B) {
	Chain<T> result; // 用于存储结果的链表
	int carry = 0; // 进位初始化为0

	ChainNode<T>* nodeA = A.first;
	ChainNode<T>* nodeB = B.first;

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




template<class T>
void CombineToC(Chain<T>& C, Chain<T>& A, Chain<T>& B){
	ChainNode<T>* curA = A.first;
	ChainNode<T>* curB = B.first;

	while (curA != nullptr) {
		C.Insert(0, curA->data);
		curA = curA->next;
	}

	while (curB != nullptr) {
		C.Insert(0, curB->data);
		curB = curB->next;
	}
	
}


template<class T>
void Chain<T>::Insert(int f, const T& x)
{
	if (!(f == 0 || f == 1)) throw invalid_argument("Invalid insert mode.");

	ChainNode<T>* p = first;  //使用p指向原Chain中首元素
	ChainNode<T>* temp = new ChainNode<T>(x);// 建立并初始化待插入新节点

	if (first == nullptr) {
		//链表头指针为空，即链表未建立
		first = temp;
	}
	else
		if (!f)//the positive order
		{
			if (x < p ->data )//当前数据小于链表头结点保存的数据
			{  
				temp->next = first;
				first = temp;
				return;
			}
			ChainNode<T>* curr = first;
			while (curr ->next!= nullptr)//寻找合适的插入位置
			{
				if ((curr->data <= x) && (curr->next->data > x))
				{
					temp->next = curr->next;
					curr->next = temp;
					return ;
				}
				curr = curr->next;
			}//end while
			curr->next = temp;
		}
		else //the reserve order
		{
			if (x > p->data)//当前数据大于链表头结点保存的数据
			{
				temp->next = first;
				first = temp;
				return ;
			}
			ChainNode<T>* curr = first;
			while (curr->next != nullptr)//寻找合适的插入位置
			{
				if ((curr->data >= x) && (curr->next->data < x))
				{
					temp->next = curr->next;
					curr->next = temp;
					return ;
				}
				curr = curr->next;
			}//end while
			curr->next = temp;


		}
    return ;//返回
}

template<class T>
void Chain<T>::RemoveDuplicates() {
	if (first == nullptr || first->next == nullptr) {
		// 如果链表为空或只有一个节点，无需去重
		return;
	}

	ChainNode<T>* current = first;

	while (current != nullptr && current->next != nullptr) {
		if (current->data == current->next->data) {
			// 如果当前节点与下一个节点的数据相同，说明有重复元素
			// 删除下一个节点，保留当前节点
			ChainNode<T>* duplicate = current->next;
			current->next = duplicate->next;
			delete duplicate;
		}
		else {
			// 如果当前节点与下一个节点的数据不同，继续遍历
			current = current->next;
		}
	}
}

template<class T>
void Chain<T>::RemoveKthFromEnd(int k) {
	if (k <= 0 || first == nullptr) {
		// 无效的k值或链表为空,直接返回
		return;
	}

	ChainNode<T>* fast = first;
	ChainNode<T>* slow = first;
	ChainNode<T>* prev = nullptr;

	// 将快指针移动k个节点
	for (int i = 0; i < k; i++) {
		if (fast == nullptr) {
			// 如果k大于链表长度，无法删除
			return;
		}
		fast = fast->next;
	}

	// 同时移动快慢指针，直到快指针到达链表末尾
	while (fast != nullptr) {
		prev = slow;
		slow = slow->next;
		fast = fast->next;
	}

	if (prev == nullptr) {
		// 边界情况，如果prev为空，说明要删除的是第一个节点
		ChainNode<T>* temp = first;
		first = first->next;
		cout << temp->data << endl;
		delete temp;
	}
	else {
		// 否则，删除slow指向的节点
		prev->next = slow->next;
		cout << slow->data << endl;
		delete slow;
	}
}








int main() {
	cout << "输入链表A，输入字符任意非数字符号表示结束"<<endl;
	int t = 0;
	Chain<int> A;
	while (cin >> t)
	{
		A.Insert(0, t);
	}
	cout << "链表A如下：";
	A.Display();

	// 重置 cin 的状态和清除输入缓冲区
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	cout << "输入链表B，输入字符任意非数字符号表示结束"<<endl;
	Chain<int> B;
	while (cin >> t)
	{
		B.Insert(1, t);
	}
	cout << "链表B如下：";
	B.Display();
	
	Chain<int> C;
	CombineToC<int>(C,A,B);
	cout << "合并成的链表C如下：";
	C.Display();
	C.RemoveDuplicates();
	cout << "链表C去重后如下：";
	C.Display();

	int k = 0;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	cin >> k;
	C.RemoveKthFromEnd(k);
	cout << "删除倒数第"<<k<<"个节点后的链表C如下：";
	C.Display();
	
	Chain<int> D;
	while (cin >> t)
	{
		D.Add(t);
	}
	cout << "链表D如下：";
	D.Display();

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	Chain<int> E;
	while (cin >> t)
	{
		E.Add(t);
	}
	cout << "链表E如下：";
	E.Display();

	cout << "按照十进位制进位相加，生成新链表F，并输出F"<<endl;
	Chain<int> F = AddTwoChains<int>(D, E);
	F.Display();






	return 0;



}


#include<iostream>
#include<stdexcept>
using namespace std;


class Chain;

class ChainNode {
public:
	ChainNode(int item) : data(item), next(nullptr) {}
	friend Chain;

	int data=0;
	ChainNode* next = nullptr;//��ʼ��ָ���
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

	

	//��ӡ����
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
	ChainNode* p = first;  //ʹ��pָ��ԭChain����Ԫ��
	ChainNode* temp = new ChainNode(x);// ��������ʼ���������½ڵ�

	if (first == nullptr) {
		//����ͷָ��Ϊ�գ�������δ����
		first = temp;
	}
	else
		while (p->next != nullptr)
			p->next == temp;
	
	 p->next = temp;
		
		
	return;//����
}



int main() {
	cout << "��������A�������ַ���������ַ��ű�ʾ����" << endl;
	int t = 0;
	Chain A;
	while (cin >> t)
	{
		A.Insert(t);
	}
	cout << "����A���£�";
	A.Display();

	// ���� cin ��״̬��������뻺����
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "��������B�������ַ���������ַ��ű�ʾ����" << endl;
	Chain B;
	while (cin >> t)
	{
		B.Insert(t);
	}
	cout << "����B���£�";
	B.Display();

	
	return 0;
}
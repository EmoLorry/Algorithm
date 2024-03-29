#include<iostream>
#include<stdexcept>
using namespace std;


class Chain;

class ChainNode {
public:
	ChainNode(int item) : data(item), next(nullptr) {}
	friend Chain;

	int data = 0;
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

	void Add(int x);

	//��������
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





	void Chain::Add(int x)
	{
		ChainNode* temp = new ChainNode(x);  // ����һ���½ڵ�

		// ���½ڵ��nextָ��ǰ�ĵ�һ���ڵ�
		temp->next = first;

		// ��������ĵ�һ���ڵ�Ϊ�½ڵ�
		first = temp;
	}

	Chain AddTwoChains(Chain& A, Chain& B) {
		Chain result; // ���ڴ洢���������
		int carry = 0; // ��λ��ʼ��Ϊ0

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

			carry = sum / 10; // �����λ
			sum %= 10; // ���㵱ǰλ��ֵ

			result.Add(sum); // ����ǰλ��ֵ��ӵ��������
			

		}
		result.Reverse();
		return result;
	}


int main() {
	cout << "��������D�������ַ���������ַ��ű�ʾ����" << endl;
	int t = 0;
	Chain D;
	while (cin>>t)
	{
		D.Add(t);
	}
	cout << "����D���£�";
	D.Display();

	// ���� cin ��״̬��������뻺����
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "��������E�������ַ���������ַ��ű�ʾ����" << endl;
	Chain E;
	while (cin>>t)
	{
		E.Add(t);
	}
	cout << "����E���£�";
	E.Display();

	cout << "����F���£�";
	Chain F = AddTwoChains(D, E);
	F.Display();

	return 0;
}
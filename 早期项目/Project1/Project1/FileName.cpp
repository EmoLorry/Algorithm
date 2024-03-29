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
	ChainNode<T>* next=nullptr;//��ʼ��ָ���
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
	
	//��Ԫ�ؼ�������ͷ���ĳ�ʼ����ʽ
	void Add(int x)
	{
		ChainNode<T>* temp = new ChainNode<T>(x);  // ����һ���½ڵ�

		// ���½ڵ��nextָ��ǰ�ĵ�һ���ڵ�
		temp->next = first;

		// ��������ĵ�һ���ڵ�Ϊ�½ڵ�0
		first = temp;
	}
	
	//f presients modes(0 ->the positive order and 1-> the reserve order)
	void Insert(int f, const T& x);
    
	
	//ȥ��
	void RemoveDuplicates();
	
	//�ϲ�����
	friend void CombineToC(Chain<T>& C, Chain<T>& A, Chain<T>& B);
	
	//�ڶ���
	void RemoveKthFromEnd(int);
	
	//��ӡ����
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
	//��������
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
	Chain<T> result; // ���ڴ洢���������
	int carry = 0; // ��λ��ʼ��Ϊ0

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

		carry = sum / 10; // �����λ
		sum %= 10; // ���㵱ǰλ��ֵ

		result.Add(sum); // ����ǰλ��ֵ��ӵ��������


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

	ChainNode<T>* p = first;  //ʹ��pָ��ԭChain����Ԫ��
	ChainNode<T>* temp = new ChainNode<T>(x);// ��������ʼ���������½ڵ�

	if (first == nullptr) {
		//����ͷָ��Ϊ�գ�������δ����
		first = temp;
	}
	else
		if (!f)//the positive order
		{
			if (x < p ->data )//��ǰ����С������ͷ��㱣�������
			{  
				temp->next = first;
				first = temp;
				return;
			}
			ChainNode<T>* curr = first;
			while (curr ->next!= nullptr)//Ѱ�Һ��ʵĲ���λ��
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
			if (x > p->data)//��ǰ���ݴ�������ͷ��㱣�������
			{
				temp->next = first;
				first = temp;
				return ;
			}
			ChainNode<T>* curr = first;
			while (curr->next != nullptr)//Ѱ�Һ��ʵĲ���λ��
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
    return ;//����
}

template<class T>
void Chain<T>::RemoveDuplicates() {
	if (first == nullptr || first->next == nullptr) {
		// �������Ϊ�ջ�ֻ��һ���ڵ㣬����ȥ��
		return;
	}

	ChainNode<T>* current = first;

	while (current != nullptr && current->next != nullptr) {
		if (current->data == current->next->data) {
			// �����ǰ�ڵ�����һ���ڵ��������ͬ��˵�����ظ�Ԫ��
			// ɾ����һ���ڵ㣬������ǰ�ڵ�
			ChainNode<T>* duplicate = current->next;
			current->next = duplicate->next;
			delete duplicate;
		}
		else {
			// �����ǰ�ڵ�����һ���ڵ�����ݲ�ͬ����������
			current = current->next;
		}
	}
}

template<class T>
void Chain<T>::RemoveKthFromEnd(int k) {
	if (k <= 0 || first == nullptr) {
		// ��Ч��kֵ������Ϊ��,ֱ�ӷ���
		return;
	}

	ChainNode<T>* fast = first;
	ChainNode<T>* slow = first;
	ChainNode<T>* prev = nullptr;

	// ����ָ���ƶ�k���ڵ�
	for (int i = 0; i < k; i++) {
		if (fast == nullptr) {
			// ���k���������ȣ��޷�ɾ��
			return;
		}
		fast = fast->next;
	}

	// ͬʱ�ƶ�����ָ�룬ֱ����ָ�뵽������ĩβ
	while (fast != nullptr) {
		prev = slow;
		slow = slow->next;
		fast = fast->next;
	}

	if (prev == nullptr) {
		// �߽���������prevΪ�գ�˵��Ҫɾ�����ǵ�һ���ڵ�
		ChainNode<T>* temp = first;
		first = first->next;
		cout << temp->data << endl;
		delete temp;
	}
	else {
		// ����ɾ��slowָ��Ľڵ�
		prev->next = slow->next;
		cout << slow->data << endl;
		delete slow;
	}
}








int main() {
	cout << "��������A�������ַ���������ַ��ű�ʾ����"<<endl;
	int t = 0;
	Chain<int> A;
	while (cin >> t)
	{
		A.Insert(0, t);
	}
	cout << "����A���£�";
	A.Display();

	// ���� cin ��״̬��������뻺����
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	cout << "��������B�������ַ���������ַ��ű�ʾ����"<<endl;
	Chain<int> B;
	while (cin >> t)
	{
		B.Insert(1, t);
	}
	cout << "����B���£�";
	B.Display();
	
	Chain<int> C;
	CombineToC<int>(C,A,B);
	cout << "�ϲ��ɵ�����C���£�";
	C.Display();
	C.RemoveDuplicates();
	cout << "����Cȥ�غ����£�";
	C.Display();

	int k = 0;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	cin >> k;
	C.RemoveKthFromEnd(k);
	cout << "ɾ��������"<<k<<"���ڵ�������C���£�";
	C.Display();
	
	Chain<int> D;
	while (cin >> t)
	{
		D.Add(t);
	}
	cout << "����D���£�";
	D.Display();

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	Chain<int> E;
	while (cin >> t)
	{
		E.Add(t);
	}
	cout << "����E���£�";
	E.Display();

	cout << "����ʮ��λ�ƽ�λ��ӣ�����������F�������F"<<endl;
	Chain<int> F = AddTwoChains<int>(D, E);
	F.Display();






	return 0;



}


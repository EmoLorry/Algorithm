#include <iostream>
#include <string.h>
#include <stdio.h>
#include "stack.cpp"

const int MaxLength = 100; // �����ʽ����

void PrintMatchedPairs(char* expr);



int main() {
    char expr[MaxLength];
    std::cout << "�����볤�����Ϊ " << MaxLength << " �ı��ʽ��" << std::endl;
    std::cin.getline(expr, MaxLength);
    std::cout << "ƥ������Ŷԣ�" << std::endl;
    std::puts(expr);
    std::cout << "Ϊ��" << std::endl;
    PrintMatchedPairs(expr);
    return 0;
}

void PrintMatchedPairs(char* expr) {
    Stack<int> s(MaxLength);
    int j, length = strlen(expr);
    for (int i = 1; i <= length; i++) {
        if (expr[i - 1] == '(') {
            s.Add(i);
        }
        else if (expr[i - 1] == ')') {
            try {
                s.Delete(j); // ��ջƥ���������
                std::cout << j << ' ' << i << std::endl;
            }
            catch (const OutOfBounds& ex) {
                std::cout << "��������ƥ����" << " λ�ã�" << i << std::endl;
            }
        }
    }
    while (!s.IsEmpty()) {
        s.Delete(j);
        std::cout << "��������ƥ���� λ�ã�" << j << std::endl;
    }
}

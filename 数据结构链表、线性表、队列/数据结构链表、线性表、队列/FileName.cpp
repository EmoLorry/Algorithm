#include <iostream>
#include <string.h>
#include <stdio.h>
#include "stack.cpp"

const int MaxLength = 100; // 最大表达式长度

void PrintMatchedPairs(char* expr);



int main() {
    char expr[MaxLength];
    std::cout << "请输入长度最多为 " << MaxLength << " 的表达式：" << std::endl;
    std::cin.getline(expr, MaxLength);
    std::cout << "匹配的括号对：" << std::endl;
    std::puts(expr);
    std::cout << "为：" << std::endl;
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
                s.Delete(j); // 出栈匹配的左括号
                std::cout << j << ' ' << i << std::endl;
            }
            catch (const OutOfBounds& ex) {
                std::cout << "右括号无匹配项" << " 位置：" << i << std::endl;
            }
        }
    }
    while (!s.IsEmpty()) {
        s.Delete(j);
        std::cout << "左括号无匹配项 位置：" << j << std::endl;
    }
}

#include <iostream>
#include <exception>
#include <string>
#include "Stack.cpp"
using namespace std;

template<class T>
void Stack<T>:: show() const {
	for (int i = 0; i <= top; i++)
		std::cout << stack[i] << " ";
	std::cout << std::endl;
}
template<class T>
void Stack<T>::get_max() const
{
	T max = 0;
	for (int i = 0; i <= top; i++)
		if (stack[i] > max)
			max = stack[i];
	std::cout << max<<std::endl;
}

template<class T>
Stack<T>& Stack<T>::DeleteTheSame() {
	T* stack0;
	stack0 = new T[99];
	int top0 = -1;
	for (int i = 0; i <= top; i++)
	{
		T swap = stack[i];
		top0++;
		if (top0 == 0)
		{
			stack0[top0] = swap;
		}
		else
			if (swap != stack0[top0 - 1])
			{
				stack0[top0] = swap;
			}
			else
			{
				top0 -= 2;
			}
	}
	
	top = top0;
	stack = stack0;
	return *this;
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

//带符号字符串转数字的函数
double stringToDoubleWithSign(const std::string& str) {
    size_t startIndex = 0;
    bool isNegative = false;

    if (!str.empty() && str[0] == '-') {
        isNegative = true;
        startIndex = 1;
    }

    double result = std::stod(str.substr(startIndex));

    if (isNegative)
        result = -result;

    return result;
}

//中缀表达式栈转化为后缀表达式栈函数
void infixStackToPostfixStack(string stack[],Stack<string>& Calculator1,int top) {
    
    Stack<string> operatorStack;
    
    int i = 0;

    while (i<=top) {
        string c = stack[i];
        if ((c[0] != '+'&&c[0] != '-'&&c[0] != '*' &&c[0] != '/'&& c[0] != '('&& c[0] != ')') || c[0] == '-' && c.length() > 1) {
            Calculator1.Add(c);
        }
        else if (c[0] == '+' || c[0] == '-' || c[0] == '*' || c[0] == '/') {
            while (!operatorStack.IsEmpty() &&
                precedence(c[0]) <= precedence(operatorStack.Top()[0])) {
                Calculator1.Add(operatorStack.Top());
                operatorStack.Delete();
            }
            operatorStack.Add(c);
        }
        else if (c[0] == '(') {
            operatorStack.Add(c);
        }
        else if (c[0] == ')') {
            while (!operatorStack.IsEmpty() && operatorStack.Top()[0] != '(') {
                Calculator1.Add(operatorStack.Top());
                operatorStack.Delete();
            }
            if (!operatorStack.IsEmpty() && operatorStack.Top()[0] == '(') {
                operatorStack.Delete();
            }
        }
     
        i++;
    }

    while (!operatorStack.IsEmpty()) {
        Calculator1.Add(operatorStack.Top());
        operatorStack.Delete();
    }
}

//计算后缀表达式栈的运算结果的函数
double evaluatePostfix(const string postfix[], int length) {
    Stack<double> operandStack;

    for (int i = 0; i <= length; i++) {
        string token = postfix[i];
        if (('0' <= token[0]&& token[0] <='9')||token[0]=='-'&&token.length()>1) {
            operandStack.Add(stringToDoubleWithSign(token));
        }
        else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/') {
            if ((operandStack.gettop()+1) < 2) {
                cerr << "Invalid postfix expression." << endl;
                return 0;
            }
            double operand2 = operandStack.Top();
            operandStack.Delete();
            double operand1 = operandStack.Top();
            operandStack.Delete();
            double result = 0;
            switch (token[0]) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                if (operand2 == 0) {
                    cerr << "Division by zero." << endl;
                    return 0;
                }
                result = operand1 / operand2;
                break;
            }
            operandStack.Add(result);
        }
    }
    return (operandStack.Top());
}


//打散字符串，识别出小数、非个位数的函数，并将其放入字符串数组
void transfor(char str[],string x[], int& lenx) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == ')') {
            lenx++;
            x[lenx - 1] = str[i];
        }
        else {
            if (i == 0) {
                lenx++;
                x[lenx - 1] = str[i];
            }
            else if ((i==1&&str[i-1]=='-')||(str[i-1]=='-'&&(str[i-2]>'9'||str[i-2]<'0')))
            {
                x[lenx - 1] += str[i];
            }
            else {
                if ((str[i - 1] >= '0' && str[i - 1] <= '9')||str[i-1]=='.') {
                    x[lenx - 1] += str[i];
                }
                else if(str[i]=='.')
                    x[lenx - 1] += str[i];
                else {
                    lenx++;
                    x[lenx - 1] = str[i];
                }
            }
        }
        i++;
    }

}



int main() {
    std::cout << "输入任意非数字字符表示结束" << std::endl;
    Stack<int> myStack;
    int t;
    while (std::cin >> t) {
        myStack.Add(t);
    }
    myStack.get_max();
    myStack.DeleteTheSame();
    myStack.show();

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    

    //Calculator0是存放原始表达式字符串的栈
    
    Stack<string> Calculator0;
    char str[100]; // 指定字符数组的大小
    cin >> str;
    string x[100];//辨别出多位数字字符
    int lenx = 0;
    transfor(str, x, lenx);

//例子
//str 1.3+22/3
//string x[100] "1.3"  "+"  "22"  "/"  "3"
//Calculator0<string> -> stack[]  1.3  +  22  /  3
//Calculator1<string> -> stack[]  1.3  22  3  /  +   
   
    for (int i = 0; i < lenx; i++)
       Calculator0.Add(x[i]);

    Calculator0.show();
    
    //Calculator1是转化为后缀表达式的栈
    Stack<string> Calculator1;
    infixStackToPostfixStack(Calculator0.getstack(), Calculator1,Calculator0.gettop());
   
    Calculator1.show();

    cout << evaluatePostfix(Calculator1.getstack(), Calculator1.gettop());
    


	return 0;
}

#include <stack>
#include <string>
#include <iostream>
#include <cstring>
#include <exception>

using namespace std;
#define MAX_STRING 100

int main(int argc, char const *argv[])
{
    char input_str[MAX_STRING], *symbols;
    stack<double> rpn_stack;
    cout << "Enter RPN string: ";
    cin.getline(input_str, MAX_STRING);
    symbols = strtok(input_str, " ");
    double a, b;
    while (symbols)
    {
        if (symbols[0] == '+' || symbols[0] == '-' || symbols[0] == '*' || symbols[0] == '/')
        {
            a = rpn_stack.top();
            rpn_stack.pop();
            b = rpn_stack.top();
            rpn_stack.pop();
            switch (symbols[0])
            {
            case '+':
                rpn_stack.push(a + b);
                break;
            case '-':
                rpn_stack.push(a - b);
                break;
            case '*':
                rpn_stack.push(a * b);
                break;
            case '/':
                rpn_stack.push(a / b);
                break;
            default:
                throw runtime_error("unknown op");
                break;
            }
        }
        else if (symbols[0] == '#' || symbols[0] == '^')
        {
            a = rpn_stack.top();
            rpn_stack.pop();
            switch (symbols[0])
            {
            case '^':
                rpn_stack.push(-a);
                break;
            case '#':
                rpn_stack.push(1.0 / a);
                break;
            default:
                break;
            }
        }
        else
        {
            rpn_stack.push(atof(symbols));
        }
        symbols = strtok(nullptr, " ");
    }
    if (rpn_stack.size() > 1)
    {
        throw runtime_error("invalid rpn string");
    }
    cout << "The answer is: " << rpn_stack.top() << endl;
    return 0;
}

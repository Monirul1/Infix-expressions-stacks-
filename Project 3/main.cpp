#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
using namespace std;

using ValueType = int;

/**
 * @class IllegalExprException
 * Exception class thrown by illegal infix expression
 */
class IllegalExprException : public runtime_error
{
    
};

ValueType processExpression(const string& expr) throw (IllegalExprException);
bool isValidResponse(char response);
bool isYesResponse(char response);
int precedence(char op);
void provideHelpIfNecessary(void);
void execute(stack<ValueType>& valstack, stack<char>& opStack)
throw (IllegalExprException);
ValueType doOperation(ValueType operandL, char operation, ValueType operandR)
throw (IllegalExprException);

/**
 * The usual main function
 */
int main()
{
    provideHelpIfNecessary();
    
    while (true) {
        cout << "Expression? " ;
        string expr;
        getline(cin, expr);
        if (expr.length() == 0)
            break;
        try {
            ValueType result = processExpression(expr);
            cout << result << endl;
        } catch (exception& ex){
            cerr << ex.what() << endl;
        }
    }
    cout << endl;
}

void provideHelpIfNecessary(void)
{
    static bool isFirstRun = true;
    if (isFirstRun)
    {
        isFirstRun = false;
        char answer;
        do
        {
            cout <<"Do you need help (Y/N)? :";
            cin >> answer;
            cin.ignore();
            if (!isValidResponse(answer)) {
                cout << "Invalid response! Try again.\n" << endl;
            }
        } while (!isValidResponse(answer));
        
        if (isYesResponse(answer))
            cout << "Enter an infix expression at the prompt.\n"
            << "The program will tell you its value.\n"
            << "To stop the program, just hit 'return' at the prompt.\n";
    }
}// end provideHelpIfNecessary

ValueType processExpression(const string& expr) throw (IllegalExprException)
{
    stack<ValueType> ValStack;
    stack<char> OpStack;
    for (int i = 0; i < expr.length(); i++)
    {
        if (isdigit(expr[i]))
        {
            ValueType num = expr[i] - '0';
            ValStack.push(num);
        }
        
        if (expr[i] == '(') OpStack.push(expr[i]);
            
            if (expr[i] == '*'|| expr[i] == '+'||
                expr[i] == '-'|| expr[i] == '/') {
                
                if(OpStack.empty()) OpStack.push(expr[i]);
                    
                    else if (precedence(expr[i]) > precedence(OpStack.top()))
                        OpStack.push(expr[i]);
                        
                        else
                        {
                            while (!OpStack.empty() && precedence(expr[i]) <= precedence(OpStack.top())) execute(ValStack,OpStack);
                                OpStack.push(expr[i]);
                                }
            }
        if (expr[i] == ')') {
            while (OpStack.top() != '(') execute(ValStack,OpStack);
                OpStack.pop();
                }
    }
    
    while (!OpStack.empty()) execute(ValStack,OpStack);
        ValueType result = ValStack.top();
        return result;
}

bool isValidResponse(char response)
{
    {
        if (response == 'Y'|| response == 'y'|| response == 'T'|| response == 't'||
            response == '1'|| response == 'N'|| response == 'n'|| response == 'F'||
            response == 'f'|| response == '0') return true;
        else return false;
    }
}

bool isYesResponse(char response)
{
    if ( response == 'Y'|| response == 'y'|| response == 'T'||
        response == 't'|| response == '1') return true;
    else return false;
}

int precedence(char op)
{
    if (op == '*' || op == '/') op = 3;
    else if    (op == '+' || op == '-') op = 2;
    else if (op == '(') op = 0;
    else op = -1;
    return op;
}

void execute(stack<ValueType>& valStack, stack<char>& opStack)
throw (IllegalExprException)
{
    ValueType result;
    ValueType operand1 = valStack.top();
    valStack.pop();
    ValueType operand2 = valStack.top();
    valStack.pop();
    char op = opStack.top();
    opStack.pop();
    result = doOperation(operand2,op,operand1);
    valStack.push(result);
    
}

ValueType doOperation(ValueType operandL, char operation, ValueType operandR)
throw (IllegalExprException)                    
{
    ValueType ans = 0;
    if (operation == '*') ans = operandL * operandR;
        if (operation == '/') ans = operandL / operandR;
            if (operation == '+') ans = operandL + operandR;
                if (operation == '-') ans = operandL - operandR;
                    return ans;
}

/* ----SAMPLE RUN----
 
 Do you need help (Y/N)? :y
 Enter an infix expression at the prompt.
 The program will tell you its value.
 To stop the program, just hit 'return' at the prompt.
 Expression? 6 *  5 * (5 +1)
 180
 Expression?
 Program ended with exit code: 0

 */







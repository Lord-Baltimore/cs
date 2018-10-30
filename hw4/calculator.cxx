#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <stdlib.h>
#include <cmath>

#include "charlist.h"
#include "charstack.h"
#include "doublelist.h"
#include "doublestack.h"

using namespace std;

string InfixToPostfix (string infix);
double EvaluatePostfix(string postfix);

void TestList();
void TestStack();
void TestInfixToPostfix (string infix, string expected_postfix);
void TestEvaluatePostfix(string postfix, double expected_value);

int main()
{
    try
    {
        TestList();
    }
    catch (const char* message)
    {
        cout << "Exception in TestTList(): " << message << endl;
        return -1;
    }

    try
    {
        TestStack();
    }
    catch (const char* message)
    {
        cout << "Exception in TestTStack(): " << message << endl;
        return -1;
    }

    cout << endl << "Test Rpn() and Eval()" << endl;

    cout << "  test Rpn   1:"; try { TestInfixToPostfix ("1+2;", "12+"   ); } catch (const char* message) { cout << "Exception: " << message << endl; return -1; } cout << " success" << endl;
    cout << "  test Eval  1:"; try { TestEvaluatePostfix(        "12+", 3); } catch (const char* message) { cout << "Exception: " << message << endl; return -1; } cout << " success" << endl;

    cout << "  test Rpn   2:"; try { TestInfixToPostfix ("1*2*3;", "12*3*"   ); } catch (const char* message) { cout << "Exception: " << message << endl; return -1; } cout << " success" << endl;
    cout << "  test Eval  2:"; try { TestEvaluatePostfix(          "12*3*", 6); } catch (const char* message) { cout << "Exception: " << message << endl; return -1; } cout << " success" << endl;

    cout << "  test Rpn   3:"; try { TestInfixToPostfix ("1+2*3;", "123*+"   ); } catch (const char* message) { cout << "Exception: " << message << endl; return -1; } cout << " success" << endl;
    cout << "  test Eval  3:"; try { TestEvaluatePostfix(          "123*+", 7); } catch (const char* message) { cout << "Exception: " << message << endl; return -1; } cout << " success" << endl;

    cout << "  test Rpn   4:"; try { TestInfixToPostfix ("(1+2)*3;", "12+3*"   ); } catch (const char* message) { cout << "Exception: " << message << endl; return -1; } cout << " success" << endl;
    cout << "  test Eval  4:"; try { TestEvaluatePostfix(            "12+3*", 9); } catch (const char* message) { cout << "Exception: " << message << endl; return -1; } cout << " success" << endl;

    cout << "  test Rpn   5:"; try { TestInfixToPostfix ("1+2+3*(4+5+6*7);", "12+345+67*+*+"     ); } catch (const char* message) { cout << "Exception: " << message << endl; return -1; } cout << " success" << endl;
    cout << "  test Eval  5:"; try { TestEvaluatePostfix(                    "12+345+67*+*+", 156); } catch (const char* message) { cout << "Exception: " << message << endl; return -1; } cout << " success" << endl;

    cout << "  test Rpn   6:"; try { TestInfixToPostfix ("1/(2+3)+4*(5-6/7)*8/9-0;", "123+/4567/-*8*9/+0-"                    ); } catch (const char* message) { cout << "Exception: " << message << endl; return -1; } cout << " success" << endl;
    cout << "  test Eval  6:"; try { TestEvaluatePostfix(                            "123+/4567/-*8*9/+0-", 14.930158730158730); } catch (const char* message) { cout << "Exception: " << message << endl; return -1; } cout << " success" << endl;

    cout << endl << "Congratulation!" << endl;
    cout << "You successfully passed all tests!" << endl;
}

void TestInfixToPostfix(string infix, string expected_postfix)
{
    string postfix = InfixToPostfix(infix);
    cout << endl << postfix << endl << expected_postfix << endl << infix << endl;

    if (postfix != expected_postfix)
    {
        ostringstream os;
        os << "Rpn(" << infix << ") = " << postfix << " is not same to its solution " << expected_postfix;
        throw os.str().c_str();
    }
}

void TestEvaluatePostfix(string postfix, double expected_value)
{
    double val = EvaluatePostfix(postfix);
    double err = abs(val - expected_value);
    double tolerance = 0.00001;


    if (err > tolerance)
    {
        ostringstream msg;
        msg << "Eval(" << postfix << ") = " << val << " is not same to its solution " << expected_value;
        throw msg.str().c_str();
    }
}

void TestList()
{
    cout << endl << "Test CharList class" << endl;

    CharList list;
    string     str;
    string     lstr;

    cout << "  test List  1:"; list.AddToHead('e'); lstr = (string)list; str = "(e)"        ;   if(str != lstr) throw "elements after calling list.AddToHead('e') != (\"e\")        "; cout << " success" << endl;
    cout << "  test List  2:"; list.AddToHead('d'); lstr = (string)list; str = "(d,e)"      ;   if(str != lstr) throw "elements after calling list.AddToHead('d') != (\"d,e\")      "; cout << " success" << endl;
    cout << "  test List  3:"; list.AddToTail('f'); lstr = (string)list; str = "(d,e,f)"    ;   if(str != lstr) throw "elements after calling list.AddToTail('f') != (\"d,e,f\")    "; cout << " success" << endl;
    cout << "  test List  4:"; list.AddToTail('g'); lstr = (string)list; str = "(d,e,f,g)"  ;   if(str != lstr) throw "elements after calling list.AddToTail('g') != (\"d,e,f,g\")  "; cout << " success" << endl;
    cout << "  test List  5:"; list.AddToHead('b'); lstr = (string)list; str = "(b,d,e,f,g)";   if(str != lstr) throw "elements after calling list.AddToHead('b') != (\"b,d,e,f,g\")"; cout << " success" << endl;
    cout << "  test List  6:"; list.RemoveHead()  ; lstr = (string)list; str = "(d,e,f,g)"  ;   if(str != lstr) throw "elements after calling list.RemoveHead()   != (\"d,e,f,g\")  "; cout << " success" << endl;
    cout << "  test List  7:"; list.RemoveTail()  ; lstr = (string)list; str = "(d,e,f)"    ;   if(str != lstr) throw "elements after calling list.RemoveTail()   != (\"d,e,f\")    "; cout << " success" << endl;
    cout << "  test List  8:"; list.RemoveHead()  ; lstr = (string)list; str = "(e,f)"      ;   if(str != lstr) throw "elements after calling list.RemoveHead()   != (\"e,f\")      "; cout << " success" << endl;
    cout << "  test List  9:"; list.RemoveTail()  ; lstr = (string)list; str = "(e)"        ;   if(str != lstr) throw "elements after calling list.RemoveTail()   != (\"e\")        "; cout << " success" << endl;
    cout << "  test List 10:"; list.RemoveHead()  ; lstr = (string)list; str = "()"         ;   if(str != lstr) throw "elements after calling list.RemoveHead()   != (\"\")         "; cout << " success" << endl;
}

void TestStack()
{
    cout << endl << "Test DoubleStack class" << endl;

    DoubleStack stack;
    string     str;
    string     lstr;
    int        poped;

    cout << "  test List  1:";                        lstr = (string)stack; str = "()"     ;    if(str != lstr) throw "not an empty stack"                                     ; cout << " success" << endl;
    cout << "  test List  2:";         stack.Push(1); lstr = (string)stack; str = "(1)"    ;    if(str != lstr) throw "elements after calling tstack.AddToHead('5') != (1)    "; cout << " success" << endl;
    cout << "  test List  3:";         stack.Push(2); lstr = (string)stack; str = "(1,2)"  ;    if(str != lstr) throw "elements after calling tstack.AddToHead('3') != (1,2)  "; cout << " success" << endl;
    cout << "  test List  4:";         stack.Push(3); lstr = (string)stack; str = "(1,2,3)";    if(str != lstr) throw "elements after calling tstack.AddToTail('7') != (1,2,3)"; cout << " success" << endl;
    cout << "  test List  5:"; poped = stack.Pop();   lstr = (string)stack; str = "(1,2)"  ;    if(str != lstr) throw "elements after calling tstack.RemoveHead()   != (1,2)  "; cout << " success" << endl;
    cout << "  test List  6:";                                                                  if(poped != 3 ) throw "returned element of    tstack.RemoveHead()   != 3      "; cout << " success" << endl;
    cout << "  test List  7:"; poped = stack.Pop();   lstr = (string)stack; str = "(1)"    ;    if(str != lstr) throw "elements after calling tstack.RemoveTail()   != (1)    "; cout << " success" << endl;
    cout << "  test List  8:";                                                                  if(poped != 2 ) throw "returned element of    tstack.RemoveHead()   != 2      "; cout << " success" << endl;
    cout << "  test List  9:"; poped = stack.Pop();   lstr = (string)stack; str = "()"     ;    if(str != lstr) throw "elements after calling tstack.RemoveHead()   != ()     "; cout << " success" << endl;
    cout << "  test List 10:";                                                                  if(poped != 1 ) throw "returned element of    tstack.RemoveHead()   != 1      "; cout << " success" << endl;
}

int Precedence(char ch)
{
    switch (ch)
    {
    case '(': return 0;
    case ')': return 0;
    case '+': return 1;
    case '-': return 1;
    case '*': return 2;
    case '/': return 2;
    }
    throw "incorrect parameter in Precedence()";
}

bool IsOper(char ch)
{
    switch (ch)
    {
    case ';': return true;
    case '(': return true;
    case ')': return true;
    case '+': return true;
    case '-': return true;
    case '*': return true;
    case '/': return true;
    }
    return false;
}

string InfixToPostfix(string infix)
{
    CharStack operators;

    string postfix = "";

    for (unsigned int i = 0; i < infix.length()-1; i++){
        cout << postfix << endl;
        char c = infix[i];

        if (c == '(') {
            operators.Push(c);
        } else if (c == ')') {
            while (!operators.IsEmpty() && (operators.Top() != '(')){
                postfix += operators.Pop();
            }
            //Pop opening parentesis 
            operators.Pop();
        } else if (IsOper(c)){
            while (!operators.IsEmpty() && (operators.Top() != '(') && (Precedence(operators.Top()) >= Precedence(c))){
                postfix += operators.Pop();
            } 
            
            operators.Push(c);
            
        } else {
            postfix += c;
        }
    }

    while (!operators.IsEmpty()){
        postfix += operators.Pop();
    }

    return postfix;
}

double CharToDouble(char ch)
{
    assert(('0' <= ch) && (ch <= '9'));
    return (ch - '0');
}

double EvaluatePostfix(string postfix)
{
    DoubleStack operands;
    double rhs;
    double lhs;

    for (unsigned int i = 0; i < postfix.length(); i++){
        char c = postfix[i];

        if (IsOper(c)){
            rhs = operands.Pop();
            lhs = operands.Pop();

            switch (c){
                case '+': operands.Push(lhs + rhs); break;
                case '-': operands.Push(lhs - rhs); break;
                case '*': operands.Push(lhs * rhs); break;
                case '/': operands.Push(lhs / rhs); break;
            }

        } else {
            operands.Push(CharToDouble(c));
        }
    }

    return operands.Top();
}

double Evaluate(char c, double lhs, double rhs){
    switch (c){
        case '+': return lhs + rhs;
        case '-': return lhs - rhs;
        case '*': return lhs * rhs;
        case '/': return lhs / rhs;
    }
    throw "incorrect parameter in Evaluate()";
}

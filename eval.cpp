//
//  eval.cpp
//  Homework 2
//
//  Created by Timothy Liu on 5/1/23.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <stack>
#include <cassert>

using namespace std;

int precedence( char ch );

int precedence( char ch ){
    switch (ch)
    {
        case '!':
            return 3;
        case '&':
            return 2;
        case '^':
            return 1;
        default:
            cerr << "error" << endl;
            exit(1);
    }
}

int evaluate(string infix, string& postfix, bool& result)
{
  //  If infix is not a syntactically valid expression, return 1; in
  //   that case, postfix may or may not be changed, but result must
  //   be unchanged.
    
    postfix = "";
    stack<char> operatorStack;
    
    if (infix.size() > 0) // Check for invalid starting and end symbols
    {
        if ( infix.at(0) == '&' || infix.at(0) == '^' || infix.at(0) == ')' ) // Invalid start symbols
            return 1;
        if ( infix.at( (infix.size()-1) ) == '&' || infix.at( (infix.size()-1) ) == '!' || infix.at( (infix.size()-1) ) == '^' || infix.at( (infix.size()-1) ) == '(' ) // Invalid end symbols
            return 1;
    }
    
    
    // Convert infix to postfix
    for ( int i = 0; i < infix.size(); i++ )
    {
        char ch = infix.at(i);
        switch( ch )
        {
            case 'T':
            case 'F':
                if ( i+1 < infix.size() ) // Check for what's after a T or F
                {
                    if ( infix.at(i+1) == 'T' || infix.at(i+1) == 'F' || infix.at(i+1) == '(' || infix.at(i+1) == '!')
                        return 1;
                }
                postfix += ch;
                break;
            case '!':
            case '(':
                if ( i+1 < infix.size() ) // Check for what's after
                {
                    if ( infix.at(i+1) == ')' || infix.at(i+1) == '&' || infix.at(i+1) == '^')
                        return 1;
                }
                operatorStack.push( ch );
                break;
            case ')':
                if ( i+1 < infix.size() ) // Check for what's after
                {
                    if ( infix.at(i+1) == '(' || infix.at(i+1) == 'T' || infix.at(i+1) == 'F')
                        return 1;
                }
                
                while ( !operatorStack.empty() && operatorStack.top() != '(')
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                if ( operatorStack.empty() ) // Unmatched parantheses
                    return 1;
                operatorStack.pop();
                break;
            case '&':
            case '^':
                if( i+1 < infix.size() ) // Check for what's after
                {
                    if ( infix.at(i+1) == ')' || infix.at(i+1) == '&' || infix.at(i+1) == '^')
                        return 1;
                }
                
                while( !operatorStack.empty() && operatorStack.top() != '(' && precedence(ch) <= precedence(operatorStack.top() ) )
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push( ch );
                break;
            case ' ': // Skip white space
                break;
            default: // Invalid character in infix
                return 1;
        }
    }
    // Check for leftover operators in stack
    while ( !operatorStack.empty() )
    {
        if (operatorStack.top() == '(')
        {
            return 1; // Unmatched open parantheses
        }
        postfix += operatorStack.top(); // Add all the operators
        operatorStack.pop();
    }
    cerr << postfix << endl; // REMOVE LATER
    
    
    // Postfix evaluation
    stack<bool> operandStack;
    
    for (int i = 0; i < postfix.size(); i++)
    {
        char ch = postfix.at(i);
        if (ch == 'T' || ch == 'F' ) // If operand, push to stack
            operandStack.push(ch == 'T');
        
        else                        // If operator, do operation to operands
        {
            
            bool operand2 = operandStack.top();
            if (ch != '!')
            {
                operandStack.pop();
            }
            
            if ( operandStack.empty() ) // Not enough operands for operator
                return 1;
            
            bool operand1 = operandStack.top();
            operandStack.pop();
            switch (ch) {
                case '!':
                    operandStack.push(!operand1);
                    break;
                case '&':
                    operandStack.push(operand1 & operand2);
                    break;
                case '^':
                    operandStack.push(operand1 ^ operand2);
                    break;
                default:
                    return 1; // Not valid operator
                    break;
            }
        }
    }
    
    
if ( operandStack.size() != 1 ) // Postfix is wrong
{
    return 1;
}
    
result = operandStack.top();
return 0;
}

int main(){
    cout.setf(ios::boolalpha);
    cout.setf(ios::showpoint);

    string pf;
    bool answer;
    evaluate("T^ F", pf, answer);
    assert( pf == "TF^");
    evaluate("F  ^  !F & (T&F) ", pf, answer);
    assert( pf == "FF!TF&&^");
    evaluate(" F  ", pf, answer);
    assert(pf == "F");
    evaluate("((T))", pf, answer);
    assert(pf == "T");
    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("FF", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F^F)", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 &&  pf == "FF!TF&&^"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer);
    assert( answer == true);
    evaluate("!T&F  ", pf, answer);
    assert( answer == false);
    evaluate("T^F&F", pf, answer);
    assert( answer == true);
    evaluate("!(T&F)", pf, answer);
    assert( answer == true);
    assert(evaluate("T()()", pf, answer) == 1);
    assert(evaluate("T(()", pf, answer) == 1);
    assert(evaluate("T())", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("T&&T", pf, answer) == 1);
    assert(evaluate("T^^T", pf, answer) == 1);
    assert(evaluate("T&!!T", pf, answer) == 0);
    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("!T&!(T^F)", pf, answer) == 0 && !answer && pf == "T!TF^!&");
    assert(evaluate("((T))", pf, answer) == 0 && answer && pf == "T");
    assert(evaluate("((F))", pf, answer) == 0 && !answer && pf == "F");
    assert(evaluate("(!)", pf, answer) == 1);
    assert(evaluate("(^)", pf, answer) == 1);
    assert(evaluate("(&)", pf, answer) == 1);
    assert(evaluate("(T^)", pf, answer) == 1);
    assert(evaluate("(T&)", pf, answer) == 1);
    assert(evaluate("(T!)", pf, answer) == 1);
    assert(evaluate("(^T)", pf, answer) == 1);
    assert(evaluate("(&T)", pf, answer) == 1);
    assert(evaluate("((T)", pf, answer) == 1);
    assert(evaluate("(T))", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("  ", pf, answer) == 1);
    assert(evaluate("!", pf, answer) == 1);
    assert(evaluate("^", pf, answer) == 1);
    assert(evaluate("&", pf, answer) == 1);
    assert(evaluate("T   F", pf, answer) == 1);
    assert(evaluate("F  T", pf, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 &&  pf == "FF!TF&&^"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("(sdf)", pf, answer) == 1);
    assert(evaluate("()sdf", pf, answer) == 1);
    assert(evaluate("!", pf, answer) == 1);
    assert(evaluate("(", pf, answer) == 1);
    assert(evaluate("!!!", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("T(F", pf, answer) == 1);
    assert(evaluate("T(F)", pf, answer) == 1);
    assert(evaluate("( )( )", pf, answer) == 1);
    assert(evaluate("&!", pf, answer) == 1);
    assert(evaluate("!^", pf, answer) == 1);
    assert(evaluate("(&)", pf, answer) == 1);
    assert(evaluate("!()", pf, answer) == 1);
    assert(evaluate("F && F", pf, answer) == 1);
    assert(evaluate("!!T", pf, answer) == 0);
    assert(evaluate("T", pf, answer) == 0);
    assert(evaluate("!T", pf, answer) == 0);
    assert(evaluate("!!!T", pf, answer) == 0 && pf == "T!!!" && !answer);
    cerr << "All tests passed"<< endl;
    return 1;
}

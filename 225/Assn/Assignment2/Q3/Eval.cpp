/* 
 * Eval.cpp
 *
 * Description: Evaluation of infix expressions using two Stacks.
 *
 * Author: Randy Panopio
 * Date: June 2024
 */

#include <iostream>
#include "Scanner.h"
#include "Stack.h"  // TEMPLATE STACK

using std::cout;
using std::endl;
using std::cin;

// helper function to calculate infix expression, returning an integer Token
Token calculateToken (Token leftInput, Token operand, Token rightInput) {
  Token result;
  result.tt = integer;
  result.val = 0; // panic set zero
  if (operand.tt == pltok) {
    result.val = leftInput.val + rightInput.val;
  } else if (operand.tt == mitok) {
    result.val = leftInput.val - rightInput.val;
  } else if (operand.tt == asttok) {
    result.val = leftInput.val * rightInput.val;
  } else if (operand.tt == slashtok) {
    result.val = leftInput.val / rightInput.val;
  }  
  return result;
}

int main () {
  Scanner S(cin);
  Token t;

  Stack<Token> numstack, opstack;  // 2x Stacks of type Token
  t = S.getnext();
  
  // while T is not EOF or the operator stack is non empty
  // cout << "tokens:" << endl;
  while (t.tt != eof || !opstack.isEmpty()) { 
    // cout << "["<< t << "], ";
    // if T is a number
    if (t.tt == integer) {
      // push T to the number stack; get the next token
      numstack.push(t);
      t = S.getnext();
    } 
    // else if T is a left parenthesis:
    else if (t.tt == lptok) {
      //push T to the operator stack; get the next token
      opstack.push(t);
      t = S.getnext();
    }
    // else if T is a right parenthesis:
    else if (t.tt == rptok) {
      // if the top of the operator stack is a left parenthesis:
      if (!opstack.isEmpty() && opstack.peek().tt == lptok) {
        // pop it from the operator stack; get the next token:
        opstack.pop();
        t = S.getnext();
      } 
      // else
      else {
        // pop the top two numbers and the top operator
        Token rightNum = numstack.pop();
        Token leftNum = numstack.pop(); // first number that got pushed is deeper in the stack, so this is our "left" number
        Token op = opstack.pop();
        // perform the operation
        Token resultToken = calculateToken(leftNum, op, rightNum);
        // push the result to the number stack
        numstack.push(resultToken);
      }
    }
    // else if T is +, - or EOF:
    else if (t.tt == pltok || t.tt == mitok || t.tt == eof) {
      // if the operator stack is nonempty and the top is one of +, -, *, /:
      if (!opstack.isEmpty() && (opstack.peek().tt == pltok || opstack.peek().tt == mitok || opstack.peek().tt == asttok || opstack.peek().tt == slashtok)) {
        // pop the top two numbers and the top operator
        Token rightNum = numstack.pop();
        Token leftNum = numstack.pop();
        Token op = opstack.pop();
        // perform the operation
        Token resultToken = calculateToken(leftNum, op, rightNum);
        // push the result to the number stack
        numstack.push(resultToken);
      }          
      // else:
      else {
        // push T to the operator stack; get the next token
        opstack.push(t);
        t = S.getnext();
      }
    }
    // else if T is * or /:
    else if (t.tt == asttok || t.tt == slashtok) {
      // if the operator stack is nonempty and the top is one of *, /:
      if (!opstack.isEmpty() && (opstack.peek().tt == asttok || opstack.peek().tt == slashtok)) {
        // pop the top two numbers and the top operator
        Token rightNum = numstack.pop();
        Token leftNum = numstack.pop();
        Token op = opstack.pop();
        // perform the operation
        Token resultToken = calculateToken(leftNum, op, rightNum);
        // push the result to the number stack
        numstack.push(resultToken);
      }
      // else:
      else {
        // push T to the operator stack; get the next token
        opstack.push(t);
        t = S.getnext();
      }
    } else {
      // t = S.getnext(); // Get the next token for unknown or handled cases

    }
  }
  cout << endl;
  // Print the final result
  if (!numstack.isEmpty()) {
    Token result = numstack.pop();
    cout << "Result: " << result.val << endl;
  } else {
    cout << "No result to display." << endl;
  }
  return 0;
}


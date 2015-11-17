#include "ExpressionTree.h" 
#include <sstream>
#include <iostream>
#include <stdlib.h>

using namespace std;


bool ExpressionTree::isBinaryOperator(TreeNode<Token> *p) const{
  if (p->getInfo().type == Token::VARIABLE){
    cout << "test" << endl;
    return true;
  }
  return false;
}


void ExpressionTree::parse(string s){
  istringstream ss(s);
  Token a;
  while (ss >> s){
    a = translate(s);
    insert(a);
  } 
}

Token ExpressionTree::translate(string s){
  Token a;
  switch (atoi(s.c_str())) {
   //case (s.front() >= '0' && s.front() <= '9'):
     //return Token a {Token::NUMBER, atof(s.c_str())};
   case atoi("pi".c_str()):
     a {Token::NUMBER, 3.14};
 
   case atoi("+".c_str()):
     return Token a {Token::PLUS, '+'};

   case atoi("-".c_str()):
     return Token a {Token::MINUS, '-'};

   case atoi("*".c_str()):
     return Token a {Token::MULTIPLY, '*'};

   case atoi("/".c_str()):
     return Token a {Token::DIVIDE, '/'};

   case atoi("^".c_str()):
     return Token a {Token::POWER, '^'};
   
   case atoi("cos".c_str()):
     return Token a {Token::COS, 'c'};
   
   case atoi("sin".c_str()):
     return Token a {Token::SIN, 's'};

   //case (s.front() >= 'a' && s.front <= 'z')
     //return Token a {Token::VARIABLE, s.front()};

   default:
     return Token a {Token::ERROR, '!'};
  
  }


}








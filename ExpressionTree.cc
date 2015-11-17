#include "ExpressionTree.h" 
#include <sstream>
#include <iostream>
#include <cstdlib>

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
  switch (atoi(s)) {
   //case (s.front() >= '0' && s.front() <= '9'):
     //return Token a {Token::NUMBER, atof(s.c_str())};
   case atoi("pi"):
     return Token a {Token::NUMBER, 3.14};
 
   case atoi("+"):
     return Token a {Token::PLUS, s.front()};

   case atoi("-"):
     return Token a {Token::MINUS, s.front()};

   case atoi("*"):
     return Token a {Token::MULTIPLY, s.front()};

   case atoi("/"):
     return Token a {Token::DIVIDE, s.front()};

   case atoi("^"):
     return Token a {Token::POWER, s.front()};
   
   case atoi("cos"):
     return Token a {Token::COS, 'c'};
   
   case atoi("sin"):
     return Token a {Token::SIN, 's'};

   //case (s.front() >= 'a' && s.front <= 'z')
     //return Token a {Token::VARIABLE, s.front()};

   default:
     return Token a {Token::ERROR, '!'};
  
  }


}








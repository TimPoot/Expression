#include "ExpressionTree.h" 
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;





void ExpressionTree::parse(string s){
  istringstream ss(s);
  Token a;
  while (ss >> s){
    cout << s << endl;
    a = translate(s);
    insert(a);
  } 
}


//??
Token ExpressionTree::translate(string s){
  Token a {Token::ERROR, '!'};
  
  if(s == "+"){
  	 a.type = Token::PLUS;
    a.variable = '+';
    return a;
  }else if(s == "-"){
    a.type = Token::MINUS;
    a.variable = '-';
    return a;
  }else if(s == "*"){
    a.type = Token::MULTIPLY;
    a.variable = '*';
    return a;
  }else if(s == "/"){
    a.type = Token::DIVIDE;
    a.variable = '/';
    return a;
  }else if(s == "^"){
    a.type = Token::POWER;
    a.variable = '^';
    return a;
  }else if(s == "cos"){
    a.type = Token::COS;
    a.variable = 'c';
    return a;
  }else if(s == "sin"){
    a.type = Token::SIN;
    a.variable = 's';
    return a;
  }else if(s.at(0) >= 'a' && s.at(0) <= 'z'){
    a.type = Token::VARIABLE;
    a.variable = s.at(0);
    return a;
  }else if(s.at(0) >= '0' && s.at(0) <= '9'){
    a.type = Token::NUMBER;
    a.number = atof(s.c_str());
    return a;
  }else if(s.at(0) == '-'){
    a.type = Token::NUMBER;
    a.number = atof(s.c_str());
  }

  return a;
}

//might still need to be done via pointers
bool ExpressionTree::isBinaryOperator(Token a) const{
  if (a.type == Token::PLUS
      || a.type == Token::MINUS
      || a.type == Token::MULTIPLY
      || a.type == Token::DIVIDE
      || a.type == Token::POWER  
  ){
    return true;
  }else
  return false;
}


void ExpressionTree::insert(Token a){
  if (isBinaryOperator(a)){
    
  }



}


//void ExpressionTree::biInsert(){}

//void ExpressionTree::MonoInsert(){}
























void ExpressionTree::showPreOrder(){
  if (this->entrance != NULL){
    showPreOrder(this->entrance);
    cout << endl;
    }
}

void ExpressionTree::showPreOrder(TreeNode<Token> *p){
  if(p == NULL){
    return;
  }else{
    printToken(p);
    cout << " ";
    showPreOrder(p->getLeft());
    showPreOrder(p->getRight());
  }
}

void ExpressionTree::showInOrder(){
  if (this->entrance != NULL){
    showInOrder(this->entrance);
    cout << endl;
  }
}

void ExpressionTree::showInOrder(TreeNode<Token> *p){
  if(p == NULL){
    return;
  }else{
    showInOrder(p->getLeft());
    printToken(p);
    cout << " ";
    showInOrder(p->getRight());
  }
}

void ExpressionTree::printToken(TreeNode<Token> *p){
  if(p->getInfo().type == Token::COS){
    cout << "cos"; 
  }else if(p->getInfo().type == Token::SIN){
    cout << "sin";
  }else if(p->getInfo().type == Token::NUMBER){
    cout << p->getInfo().number;
  }else{
    cout << p->getInfo().variable;
  }
}










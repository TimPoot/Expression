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


bool ExpressionTree::isBinaryOperator(TreeNode<Token> *p) const{
  if (p->getInfo().type == Token::PLUS
      || p->getInfo().type == Token::MINUS
      || p->getInfo().type == Token::MULTIPLY
      || p->getInfo().type == Token::DIVIDE
      || p->getInfo().type == Token::POWER  
  ){
    return true;
  }else
    return false;
}

bool ExpressionTree::isUnaryOperator(TreeNode<Token> *p) const{
  if(p->getInfo().type == Token::COS
     || p->getInfo().type == Token::SIN
  ){
    return true;
  }else{
    return false;
  }
}

bool ExpressionTree::isTerminal(TreeNode<Token> *p) const{
  if(p->getInfo().type == Token::VARIABLE
     || p->getInfo().type == Token::NUMBER
  ){
    return true;   
  }else
    return false;
}

void ExpressionTree::insert(Token a){
  bool found = false;
  if (this->entrance == NULL){
    this->entrance = new TreeNode<Token>(a, counter);
  }else{
    insert(a, this->entrance, found);
  }
  counter++;
}


void ExpressionTree::insert(Token a, TreeNode<Token> *p, bool &found){
  if(isBinaryOperator(p)){
    if(p->getLeft() == NULL){
      if (!found){
        p->setLeft(new TreeNode<Token>(a, counter));
      }
      found = true;
      return;
    }else{
      insert(a, p->getLeft(), found);
    }
    if(p->getRight() == NULL){
      if(!found){
        p->setRight(new TreeNode<Token>(a, counter));
      }
      found = true;
      return;
    }else{
      insert(a, p->getRight(), found);
    }
  }
  
  if(isUnaryOperator(p)){
     if(p->getLeft() == NULL){
      if(!found){
        p->setLeft(new TreeNode<Token>(a, counter));
      }
      found = true;
      return;
    }else{
      insert(a, p->getLeft(), found);
    }   
  }
  
  if(isTerminal(p)){
    return;
  }
}

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










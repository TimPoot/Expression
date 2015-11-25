#include "ExpressionTree.h" 
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>

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

void ExpressionTree::simplify(){
  if (this->entrance != NULL){
    simplify(this->entrance);
  }else
  cout << "Tree is empty!" << endl;
}

void ExpressionTree::simplify(TreeNode<Token> *p){
  if(isUnaryOperator(p)){
    if(p->getLeft() != NULL){
      simplify(p->getLeft());
    }
    unarySimplify(p);
  }
  if(isBinaryOperator(p)){
    if (p->getLeft() != NULL){
      simplify(p->getLeft());
    }
    if (p->getRight() != NULL){
      simplify(p->getRight());
    }
    binarySimplify(p);
  }
}

void ExpressionTree::unarySimplify(TreeNode<Token> *p){
  Token a = {Token::ERROR, '!'};
  if (p->getLeft()->getInfo().type == Token::NUMBER){
    if (p->getInfo().type == Token::SIN){
      a.type = Token::NUMBER;
      a.number = sin(p->getLeft()->getInfo().number);
      p->setInfo(a);
      delete p->getLeft();
    }
    if (p->getInfo().type == Token::COS){
      a.type = Token::NUMBER;
      a.number = cos(p->getLeft()->getInfo().number);
      p->setInfo(a);
      delete p->getLeft();
    }
  }    
}

void ExpressionTree::binarySimplify(TreeNode<Token> *p){
  Token a = {Token::ERROR, '!'};
  //num . num
  if (p->getLeft()->getInfo().type == Token::NUMBER
   && p->getRight()->getInfo().type == Token::NUMBER
  ){
    if (p->getInfo().type == Token::PLUS){
      a.type = Token::NUMBER;
      a.number = p->getLeft()->getInfo().number + p->getRight()->getInfo().number;
      p->setinfo(a);
      delete p->getLeft();
      delete p->getRight();
    }
    if (p->getInfo().type == Token::MINUS){
      a.type = Token::NUMBER;
      a.number = p->getLeft()->getInfo().number - p->getRight()->getInfo().number;
      p->setinfo(a);
      delete p->getLeft();
      delete p->getRight();
    }
    if (p->getInfo().type == Token::MULTIPLY){
      a.type = Token::NUMBER;
      a.number = p->getLeft()->getInfo().number * p->getRight()->getInfo().number;
      p->setinfo(a);
      delete p->getLeft();
      delete p->getRight();
    }
    if (p->getInfo().type == Token::DIVIDE){
      a.type = Token::NUMBER;
      a.number = p->getLeft()->getInfo().number / p->getRight()->getInfo().number;
      p->setinfo(a);
      delete p->getLeft();
      delete p->getRight();
    }
    if (p->getInfo().type == Token::POWER){
      a.type = Token::NUMBER;
      a.number = pow(p->getLeft()->getInfo().number, p->getRight()->getInfo().number);
      p->setinfo(a);
      delete p->getLeft();
      delete p->getRight();
    }
    
  }
  //var1 . var2 (var1 = var2)
  if (p->getLeft()->getInfo().type == Token::VARIABLE
   && p->getRight()->getInfo().type == Token::VARIABLE
   && p->getLeft()->getInfo().variable == p->getRight()->getInfo().variable
  ){
    if (p->getInfo().type == Token::MINUS){
      a.type = Token::NUMBER;
      a.number = 0;
      p->setinfo(a);
      delete p->getLeft();
      delete p->getRight();
    }
    if (p->getInfo().type == Token::DIVIDE)
      a.type = Token::NUMBER;
      a.number = 1;
      p->setinfo(a);
      delete p->getLeft();
      delete p->getRight();
  }
  //var . num
  if (p->getLeft()->getInfo().type == Token::VARIABLE
   && p->getRight()->getInfo().type == Token::NUMBER
  ){
    if (p->getRight()->getInfo().number == 0) {//what about divide?
      if (p->getInfo().type == Token::MULTIPLY){
        a.type = Token::NUMBER;
        a.number = 0;
        p->setInfo(a);
        delete p->getLeft();
        delete p->getRight();
      }
      if (p->getInfo().type == Token::POWER){
        a.type = Token::NUMBER;
        a.number = 1;
        p->setInfo(a);
        delete p->getLeft();
        delete p->getRight();
      }
    }
    if (p->getRight()->getInfo().number == 1){
      if(p->getInfo().type == Token::MULTIPLY){
        a.type = Token::VARIABLE;
        a.variable = p->getLeft()->getInfo().variable;
        p->setInfo(a);
        delete p->getLeft();
        delete p->getRight();
      }
      if(p->getInfo().type == Token::DIVIDE){
        a.type = Token::VARIABLE;
        a.variable = p->getLeft()->getInfo().variable;
        p->setInfo(a);
        delete p->getLeft();
        delete p->getRight();
      }
      if(p->getInfo().type == Token::POWER){
        a.type = Token::VARIABLE;
        a.variable = p->getLeft()->getInfo().variable;
        p->setInfo(a);
        delete p->getLeft();
        delete p->getRight();
      }
    }
  }
  //num . var
  if(p->getLeft()->getInfo().type == Token::NUMBER
     && p->getRight()->getInfo().type == Token::VARIABLE){
    if (p->getLeft()->getInfo().number == 0) {
      if (p->getInfo().type == Token::PLUS){
        a.type = Token::VARIABLE;
        a.variable = p->getRight()->getInfo().variable;
        p->setInfo(a);
        delete p->getLeft();
        delete p->getRight();
      }
      if (p->getInfo().type == Token::MINUS){
        a.type = Token::VARIABLE;
        a.variable = p->getRight()->getInfo().variable;
        p->setInfo(a);
        delete p->getLeft();
        delete p->getRight();
      }
      if (p->getInfo().type == Token::MULTIPLY){
        a.type = Token::NUMBER;
        a.number = 0;
        p->setInfo(a);
        delete p->getLeft();
        delete p->getRight();
      }
      if (p->getInfo().type == Token::DIVIDE){
        a.type = Token::NUMBER;
        a.number = 0;
        p->setInfo(a);
        delete p->getLeft();
        delete p->getRight();
      }
    }
    if (p->getRight()->getInfo().number == 1){
      if(p->getInfo().type == Token::MULTIPLY){
        a.type = Token::VARIABLE;
        a.variable = p->getRight()->getInfo().variable;
        p->setInfo(a);
        delete p->getLeft();
        delete p->getRight();
      }
      if(p->getInfo().type == Token::DIVIDE){
        a.type = Token::VARIABLE;
        a.variable = p->getRight()->getInfo().variable;
        p->setInfo(a);
        delete p->getLeft();
        delete p->getRight();
      }
    }
  }
}







/*
void ExpressionTree::switchInfo(TreeNode<Token> *p, Token.type t, double d){
  Token a = {Token::ERROR, '!'};
  a.type = t;
  a.number = d;
  p->setInfo(a);
  if(p->getLeft() != NULL){
    delete p->getLeft();  
  }
  if(p->getRight() != NULL){
    delete p->getRight();  
  }
}
*/

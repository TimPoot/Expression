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
    this->entrance = new TreeNode<Token>(a);
  }else{
    insert(a, this->entrance, found);
  }
}


void ExpressionTree::insert(Token a, TreeNode<Token> *p, bool &found){
  if(isBinaryOperator(p)){
    if(p->getLeft() == NULL){
      if (!found){
        p->setLeft(new TreeNode<Token>(a));
      }
      found = true;
      return;
    }else{
      insert(a, p->getLeft(), found);
    }
    if(p->getRight() == NULL){
      if(!found){
        p->setRight(new TreeNode<Token>(a));
      }
      found = true;
      return;
    }else{
      insert(a, p->getRight(), found);
    }
  }
  
  if(isUnaryOperator(p)){
     if(p->getRight() == NULL){
      if(!found){
        p->setRight(new TreeNode<Token>(a));
      }
      found = true;
      return;
    }else{
      insert(a, p->getRight(), found);
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
    if(p->getRight() != NULL){
      simplify(p->getRight());
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
  if (p->getRight()->getInfo().type == Token::NUMBER){
    if (p->getInfo().type == Token::SIN){
      a.type = Token::NUMBER;
      a.number = sin(p->getRight()->getInfo().number);
      p->setInfo(a);
      delete p->getRight();
      p->setRight(NULL);
      return;
    }
    if (p->getInfo().type == Token::COS){
      a.type = Token::NUMBER;
      a.number = cos(p->getRight()->getInfo().number);
      p->setInfo(a);
      delete p->getRight();
      p->setRight(NULL);
      return;
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
      p->setInfo(a);
      delete p->getLeft();
      p->setLeft(NULL);
      delete p->getRight();
      p->setRight(NULL);
      return;
    }
    if (p->getInfo().type == Token::MINUS){
      a.type = Token::NUMBER;
      a.number = p->getLeft()->getInfo().number - p->getRight()->getInfo().number;
      p->setInfo(a);
      delete p->getLeft();
      p->setLeft(NULL);
      delete p->getRight();
      p->setRight(NULL);
      return;
    }
    if (p->getInfo().type == Token::MULTIPLY){
      a.type = Token::NUMBER;
      a.number = p->getLeft()->getInfo().number * p->getRight()->getInfo().number;
      p->setInfo(a);
      delete p->getLeft();
      p->setLeft(NULL);
      delete p->getRight();
      p->setRight(NULL);
      return;
    }
    if (p->getInfo().type == Token::DIVIDE){
      a.type = Token::NUMBER;
      a.number = p->getLeft()->getInfo().number / p->getRight()->getInfo().number;
      p->setInfo(a);
      delete p->getLeft();
      p->setLeft(NULL);
      delete p->getRight();
      p->setRight(NULL);
      return;
    }
    if (p->getInfo().type == Token::POWER){
      a.type = Token::NUMBER;
      a.number = pow(p->getLeft()->getInfo().number, p->getRight()->getInfo().number);
      p->setInfo(a);
      delete p->getLeft();
      p->setLeft(NULL);
      delete p->getRight();
      p->setRight(NULL);
      return;
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
      p->setInfo(a);
      delete p->getLeft();
      p->setLeft(NULL);
      delete p->getRight();
      p->setRight(NULL);
      return;
    }
    if (p->getInfo().type == Token::DIVIDE) {
      a.type = Token::NUMBER;
      a.number = 1;
      p->setInfo(a);
      delete p->getLeft();
      p->setLeft(NULL);
      delete p->getRight();
      p->setRight(NULL);
      return;
    }
  }
  if (p->getLeft()->getInfo().type == Token::NUMBER){
    if (p->getLeft()->getInfo().number == 0){
      if (p->getInfo().type == Token::PLUS) {
        a.type = Token::VARIABLE;
        a.variable = p->getRight()->getInfo().variable;
        p->setInfo(a);
		if (p->getRight()->getLeft() != NULL){
          p->getLeft()->setInfo(p->getRight()->getLeft()->getInfo());
        }else{
		  deleteSubTree(p->getLeft());
		  p->setLeft(NULL);
		}
		if (p->getRight()->getRight() != NULL){
          p->getRight()->setInfo(p->getRight()->getRight()->getInfo());
        }else{
		  deleteSubTree(p->getRight());
		  p->setRight(NULL);
		}
		return;
      }
      if (p->getInfo().type == Token::MULTIPLY) {
        a.type = Token::NUMBER;
        a.number = 0;
        p->setInfo(a);
        delete p->getLeft();
        p->setLeft(NULL);
        delete p->getRight();
        p->setRight(NULL);
        return;
      }
      if (p->getInfo().type == Token::POWER) {
        a.type = Token::NUMBER;
        a.number = 0;
        p->setInfo(a);
        delete p->getLeft();
        p->setLeft(NULL);
        delete p->getRight();
        p->setRight(NULL);
        return;
      }
    }
    if (p->getLeft()->getInfo().number == 1){
      if (p->getInfo().type == Token::MULTIPLY) {
        a.type = Token::VARIABLE;
        a.variable = p->getRight()->getInfo().variable;
        p->setInfo(a);
		if (p->getRight()->getLeft() != NULL){
          p->getLeft()->setInfo(p->getRight()->getLeft()->getInfo());
        }else{
		  deleteSubTree(p->getLeft());
		  p->setLeft(NULL);
		}
		if (p->getRight()->getRight() != NULL){
          p->getRight()->setInfo(p->getRight()->getRight()->getInfo());
        }else{
		  deleteSubTree(p->getRight());
		  p->setRight(NULL);
		}
        return;
      }
      if (p->getInfo().type == Token::POWER) {
        a.type = Token::NUMBER;
        a.number = 1;
        p->setInfo(a);
        delete p->getLeft();
        p->setLeft(NULL);
        delete p->getRight();
        p->setRight(NULL);
        return;
      }
    }
  }
  if (p->getRight()->getInfo().type == Token::NUMBER){
    if (p->getRight()->getInfo().number == 0){
      if (p->getInfo().type == Token::PLUS) {
        a.type = p->getLeft()->getInfo().type;
        a.variable = p->getLeft()->getInfo().variable;
        p->setInfo(a);
        if (p->getLeft()->getRight() != NULL){
          p->getRight()->setInfo(p->getLeft()->getRight()->getInfo());
        }else{
		  deleteSubTree(p->getLeft()->getRight());
		  p->getLeft()->setRight(NULL);
		}
		if (p->getLeft()->getLeft() != NULL){
          p->getLeft()->setInfo(p->getLeft()->getLeft()->getInfo());
        }else{
		  deleteSubTree(p->getLeft());
		  p->setLeft(NULL);
		}
        return;
      }
      if (p->getInfo().type == Token::MINUS) {
        a.type = p->getLeft()->getInfo().type;
        a.variable = p->getLeft()->getInfo().variable;
        p->setInfo(a);
        if (p->getLeft()->getRight() != NULL){
          p->getRight()->setInfo(p->getLeft()->getRight()->getInfo());
        }else{
		  deleteSubTree(p->getRight());
		  p->setRight(NULL);
		}
		if (p->getLeft()->getLeft() != NULL){
          p->getLeft()->setInfo(p->getLeft()->getLeft()->getInfo());
        }else{
		  deleteSubTree(p->getLeft());
		  p->setLeft(NULL);
		}
        return;
      }
      if (p->getInfo().type == Token::MULTIPLY) {
        a.type = Token::NUMBER;
        a.number = 0;
        p->setInfo(a);
        delete p->getLeft();
        p->setLeft(NULL);
        delete p->getRight();
        p->setRight(NULL);
        return;
      }
      if (p->getInfo().type == Token::POWER) {
        a.type = Token::NUMBER;
        a.number = 1;
        p->setInfo(a);
        delete p->getLeft();
        p->setLeft(NULL);
        delete p->getRight();
        p->setRight(NULL);
        return;
      }
    }
    if (p->getRight()->getInfo().number == 1){
      if (p->getInfo().type == Token::MULTIPLY) {
        a.type = p->getLeft()->getInfo().type;
        a.variable = p->getLeft()->getInfo().variable;
        p->setInfo(a);
        if (p->getLeft()->getRight() != NULL){
          p->getRight()->setInfo(p->getLeft()->getRight()->getInfo());
        }else{
		  deleteSubTree(p->getRight());
		  p->setRight(NULL);
		}
		if (p->getLeft()->getLeft() != NULL){
          p->getLeft()->setInfo(p->getLeft()->getLeft()->getInfo());
        }else{
		  deleteSubTree(p->getLeft());
		  p->setLeft(NULL);
		}return;
      }
      if (p->getInfo().type == Token::POWER) {
        a.type = p->getLeft()->getInfo().type;
        a.variable = p->getLeft()->getInfo().variable;
        p->setInfo(a);
        if (p->getLeft()->getRight() != NULL){
          p->getRight()->setInfo(p->getLeft()->getRight()->getInfo());
        }else{
		  deleteSubTree(p->getRight());
		  p->setRight(NULL);
		}
		if (p->getLeft()->getLeft() != NULL){
          p->getLeft()->setInfo(p->getLeft()->getLeft()->getInfo());
        }else{
		  deleteSubTree(p->getLeft());
		  p->setLeft(NULL);
		}return;
      }
    }
  }
}


//takes the root of the tree and deletes tree and children
void ExpressionTree::deleteSubTree(TreeNode<Token> *p){
  if (p != NULL){
    if (p->getLeft() != NULL){
      deleteSubTree(p->getLeft());
    }
    if (p->getRight() != NULL){
      deleteSubTree(p->getRight());
    }
    delete p;
    p = NULL;
  }
}

//returns the root of the copy
TreeNode<Token>* ExpressionTree::copySubTree(TreeNode<Token> *p){
  Token a;
  TreeNode<Token> *n;
  if (p != NULL){
    a = p->getInfo();
    n = new TreeNode<Token>(a);
    n->setLeft(copySubTree(p->getLeft()));
    n->setRight(copySubTree(p->getRight()));
  }else{ 
    return NULL;
  }
  return n;
}

void ExpressionTree::evaluate(char var, double value){
  Token a;
  Token b;
  a.type = Token::VARIABLE;
  a.variable = var;
  b.type = Token::NUMBER;
  b.number = value;
  if (this->entrance != NULL){
    evaluate(this->entrance, a, b);
  }
}

void ExpressionTree::evaluate(TreeNode<Token> *p, Token a, Token b){
  if (p->getInfo().type == a.type){
    if (p->getInfo().variable == a.variable){
      p->setInfo(b);
    }
  }
  if (p->getLeft() != NULL){
    evaluate(p->getLeft(), a, b);
  }
  if (p->getRight() != NULL){
    evaluate(p->getRight(), a, b);
  }
}

void ExpressionTree::differentiate(){
  if(entrance != NULL){
    differentiate(this->entrance);
  }
}

void ExpressionTree::differentiate(TreeNode<Token> *p){
  Token a = {Token::ERROR, '!'};
  TreeNode<Token> *copy;

  if(p->getInfo().type == Token::NUMBER){ //d(C)
    a.type = Token::NUMBER;
    a.number = 0;
    p->setInfo(a);
  }else if(p->getInfo().type == Token::VARIABLE && p->getInfo().variable == 'x'){ // d(x)
    a.type = Token::NUMBER;
    a.number = 1;
    p->setInfo(a);
  }else if(p->getInfo().type == Token::VARIABLE && p->getInfo().variable != 'x'){ // d(y)
    a.type = Token::NUMBER;
    a.number = 0;
    p->setInfo(a);
  }else if(p->getInfo().type == Token::POWER){ //d(x^y)
    if(p->getLeft()->getInfo().type == Token::NUMBER) { // x = C
      a.type = Token::NUMBER;
      a.number = p->getLeft()->getInfo().number * p->getRight()->getInfo().number;
      p->getLeft()->setInfo(a);
      a.number = p->getRight()->getInfo().number - 1;
      p->getRight()->setInfo(a);
    }else if(p->getLeft()->getInfo().type == Token::VARIABLE){ // x = var
      a.type = Token::NUMBER;
      a.number = p->getRight()->getInfo().number;
      p->getLeft()->setLeft(new TreeNode<Token>(a));
      a.type = Token::VARIABLE;
      a.variable = p->getLeft()->getInfo().variable;
      p->getLeft()->setRight(new TreeNode<Token>(a));
      a.type = Token::MULTIPLY;
      a.variable = '*';
      p->getLeft()->setInfo(a);
      a.type = Token::NUMBER;
      a.number = p->getRight()->getInfo().number - 1;
      p->getRight()->setInfo(a);
    }else{ // x = expression
      copy = copySubTree(p->getLeft());
      int y = p->getRight()->getInfo().number;
      deleteSubTree(p->getLeft());
      p->setRight(copy);
      copy = copySubTree(p->getRight());
      a.type = Token::MULTIPLY;
      a.variable = '*';
      p->setInfo(a);
      a.type = Token::POWER;
      a.variable = '^';
      p->setLeft(new TreeNode<Token>(a));
      a.type = Token::MULTIPLY;
      a.variable = '*';
      p->getLeft()->setLeft(new TreeNode<Token>(a));
      a.type = Token::NUMBER;
      a.number = y - 1;
      p->getLeft()->setRight(new TreeNode<Token>(a));
      a.number = y;
      p->getLeft()->getLeft()->setLeft(new TreeNode<Token>(a));
      p->getLeft()->getLeft()->setRight(copy);
      differentiate(p->getRight());
    }
  }else if(p->getInfo().type == Token::COS){ //we don't treat - like we should, huge fucking problem
    /*if(p->getRight()->getInfo().type == Token::NUMBER || p->getRight()->getInfo().type == Token::VARIABLE){
      a.type =  p->getRight()->getInfo().type;
      if(p->getRight()->getInfo().type == Token::NUMBER){
        a.number = p->getRight()->getInfo().number;
      }else{
        a.variable = p->getRight()->getInfo().variable;
      }
      p->getRight()->setRight(new TreeNode<Token>(a));
      a.type = Token::SIN;
      a.variable = 's';
      p->getRight()->setInfo(a);
      a.type =
      p->setInfo(a);
    }*/
  }else if(p->getInfo().type == Token::SIN){ // d(sin(x))
    if(p->getRight()->getInfo().type == Token::NUMBER || p->getRight()->getInfo().type == Token::VARIABLE) {
      a.type = Token::COS;
      a.variable = 'c';
      p->setInfo(a);
    }else{
      copy = copySubTree(p->getRight());
      a.type = Token::COS;
      a.variable = 'c';
      p->setLeft(new TreeNode<Token>(a));
      p->getLeft()->setRight(copy);
      a.type = Token::MULTIPLY;
      a.variable = '*';
      p->setInfo(a);
      differentiate(p->getRight());
    }
  }else if(p->getInfo().type == Token::PLUS){ // d(f+g)
    differentiate(p->getLeft());
    differentiate(p->getRight());
  }else if(p->getInfo().type == Token::MULTIPLY){ // d(f*g)
    copy = copySubTree(p->getLeft());
    deleteSubTree(p->getLeft());
    a.type = Token::MULTIPLY;
    a.variable = '*';
    p->setLeft(new TreeNode<Token>(a));
    p->getLeft()->setLeft(copy);
    p->getLeft()->setRight(copySubTree(p->getRight()));
    deleteSubTree(p->getRight());
    p->setRight(copySubTree(p->getLeft()));
    a.type = Token::PLUS;
    a.variable = '+';
    p->setInfo(a);
    differentiate(p->getLeft()->getLeft());
    differentiate(p->getRight()->getRight());
  }else if(p->getInfo().type == Token::DIVIDE){
    copy = copySubTree(p->getLeft());
    deleteSubTree(p->getLeft());
    a.type = Token::MINUS;
    a.variable = '-';
    p->setLeft(new TreeNode<Token>(a));
    a.type = Token::MULTIPLY;
    a.variable = '*';
    p->getLeft()->setLeft(new TreeNode<Token>(a));
    p->getLeft()->getLeft()->setLeft(copy);
    p->getLeft()->getLeft()->setRight(copySubTree(p->getRight()));
    p->getLeft()->setRight(copySubTree(p->getLeft()->getLeft()));
    copy = copySubTree(p->getRight());
    deleteSubTree(p->getRight());
    a.type = Token::POWER;
    a.variable = '^';
    p->setRight(new TreeNode<Token>(a));
    p->getRight()->setLeft(copy);
    a.type = Token::NUMBER;
    a.number = 2;
    p->getRight()->setRight(new TreeNode<Token>(a));
    differentiate(p->getLeft()->getLeft()->getLeft());
    differentiate(p->getLeft()->getRight()->getRight());
  }
}


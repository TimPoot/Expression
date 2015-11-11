#include <iostream>
#include "ExpressionTree.h"

using namespace std;

int main(){
  ExpressionTree myTree;
  Token a {Token::VARIABLE, 'x'};
  myTree.parse("+ 1 2");


  

  return 0;
}


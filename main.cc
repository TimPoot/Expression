#include <iostream>
#include "ExpressionTree.h"
#include <cstdlib>

using namespace std;

int main(){
  ExpressionTree myTree;
  myTree.parse("+ - 1 2 - 3 4");
  myTree.showPreOrder();
  myTree.showInOrder();

  return 0;
}


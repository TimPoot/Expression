#include <iostream>
#include "ExpressionTree.h"
#include <cstdlib>

using namespace std;

int main(){
  ExpressionTree myTree;
  myTree.parse("+ 1 2 cos sin -15 ^ * / : + - c");
  myTree.showPreOrder();
  myTree.showInOrder();

  return 0;
}


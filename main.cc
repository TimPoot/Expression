#include <iostream>
#include "ExpressionTree.h"
#include <cstdlib>
#include <cmath>

using namespace std;

int main(){
  ExpressionTree myTree;
  //myTree.parse("+ - 1 2 - 3 4");
  myTree.parse("+ * 2 x - 1 1");
  //myTree.parse("^ - + cos 20 1 0 1");
  //myTree.parse("+ x - x x");
  cout << "---------------------" << endl;
  myTree.showPreOrder();
  myTree.showInOrder();
  //myTree.evaluate('x', 10);
  myTree.simplify();
  cout << "---------------------" << endl;
  myTree.showPreOrder();
  myTree.showInOrder();
  myTree.evaluate('x', 10);
  //myTree.simplify();
  cout << "---------------------" << endl;
  myTree.showPreOrder();
  myTree.showInOrder();
  return 0;
}


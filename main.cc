#include <iostream>
#include "ExpressionTree.h"
#include <cstdlib>
#include <cmath>

using namespace std;

int main(){
  ExpressionTree myTree;
  myTree.parse("+ - 1 2 - 3 4");
  //myTree.parse("+ cos x - 1 2");
  //myTree.parse("cos 20");
  cout << "---------------------" << endl;
  myTree.showPreOrder();
  myTree.showInOrder();
  myTree.simplify();
  cout << "---------------------" << endl;
  myTree.showPreOrder();
  myTree.showInOrder();

  cout << "---------------------" << endl;
  double var = 20;
  cout << cos(var) << endl;
  return 0;
}


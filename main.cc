#include <iostream>
#include "ExpressionTree.h"
#include <cstdlib>
#include <cmath>

using namespace std;

int main(){
  ExpressionTree myTree;
  myTree.parse("+ / * ^ x 3 - y sin + * 2 x 6 + -3.7 * 15 x 5");
  cout << "---------------------" << endl;
  myTree.showPreOrder();
  myTree.showInOrder();
  myTree.differentiate();
  cout << "---------ddd----------" << endl;
  myTree.showPreOrder();
  myTree.showInOrder();
  return 0;
}


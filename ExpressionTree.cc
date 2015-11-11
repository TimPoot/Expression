#include "ExpressionTree.h" 

bool ExpressionTree::isBinaryOperator(TreeNode<Token> *p) const{
  if (p->getInfo().type == Token::VARIABLE){
    cout << "test" << endl;
    return true;
  }
  return false;
}

void ExpressionTree::parse(string s){
  stringstream stream;
  string ins;
  s >> ins;
  
  
  
  cout << ins << endl;
}










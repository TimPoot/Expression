#ifndef _ExpressionTree_H_
#define _ExpressionTree_H_
#include "tree.h" 

struct Token {
  enum {
    PLUS, MINUS, NUMBER, VARIABLE, COS, SIN, DIVIDE, MULTIPLY, POWER
  } type;
  union {
    char variable;
    double number;
  };
};


class ExpressionTree : public Tree<Token>{
  public:
    void parse (string s);
  private:
    bool isBinaryOperator(TreeNode<Token> *p) const; 


};





#endif

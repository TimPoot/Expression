#ifndef _ExpressionTree_H_
#define _ExpressionTree_H_

#include "tree.h" 

struct Token {
  enum {
    PLUS, MINUS, NUMBER, VARIABLE, COS, SIN, DIVIDE, MULTIPLY, POWER, ERROR
  } type;
  union {
    char variable;
    double number;
  };
};


class ExpressionTree : public Tree<Token>{
  public:
    void parse (string s);
    void showPreOrder();
    void showInOrder();
  private:
    void printToken(TreeNode<Token> *p);
    void showPreOrder(TreeNode<Token> *p);
    void showInOrder(TreeNode<Token> *p);
    bool isBinaryOperator(TreeNode<Token> *p) const;
    bool isTerminal(TreeNode<Token> *p) const;
    void insert(Token &a);
    void insert(Token &a, TreeNode<Token> *p);
    Token translate (string s); 
};





#endif

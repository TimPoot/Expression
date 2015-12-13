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
    void saveAsDot(string fileName, string graphName);
    void parse (string s);
    void showPreOrder();
    void showInOrder();
    void simplify();
    void differentiate();
    void evaluate(char var, double value);
  private:
    void saveAsDot(ofstream &output, TreeNode<Token> *p, int label);
    void differentiate(TreeNode<Token> *p);
    void switchInfo(TreeNode<Token> *p, double d);
    void printToken(TreeNode<Token> *p);
    void showPreOrder(TreeNode<Token> *p);
    void showInOrder(TreeNode<Token> *p);
    bool isBinaryOperator(TreeNode<Token> *p) const;
    bool isUnaryOperator(TreeNode<Token> *p) const;
    bool isTerminal(TreeNode<Token> *p) const;
    void insert(Token a);
    void insert(Token a, TreeNode<Token> *p, bool &found);
    Token translate (string s); 
    void simplify(TreeNode<Token> *p);
    void unarySimplify(TreeNode<Token> *p);
    void binarySimplify(TreeNode<Token> *p);
    void evaluate(TreeNode<Token> *p, Token a, Token b);
    void deleteSubTree(TreeNode<Token> *p);
    TreeNode<Token>* copySubTree(TreeNode<Token> *p);
};

#endif

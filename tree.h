#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <fstream>
#include "TreeNode.h"

using namespace std;

template <class T>
class Tree{
  public:
    Tree(){
      entrance = NULL;
      current = entrance;
      counter = 0;
    }
    ~Tree(){}
    bool contains(T info);
    void insert(T& info);
    void showPreOrder();
    void showInOrder();
    void showPostOrder();
    void saveAsDot(string filename, string graphName);
  protected:
    int counter;
    TreeNode<T> *entrance;
    TreeNode<T> *current;
    bool contains(T info, TreeNode<T> *p);
    void saveAsDot(ofstream &output, TreeNode<T> *p);
    void showPreOrder(TreeNode<T> *p);
    void showInOrder(TreeNode<T> *p);
    void showPostOrder(TreeNode<T> *p);
};

template <class T>
void Tree<T>::insert(T& info){
  if(entrance == NULL){
    current = new TreeNode<T>(info, counter);
    entrance = current;
  }else{
    current->setLeft(new TreeNode<T>(info, counter));
    current = current->getLeft();    
  }
  counter++;
}

template <class T>
bool Tree<T>::contains(T request){
  TreeNode<T> *p = entrance;
  return contains(request, p);
}

template <class T>
bool Tree<T>::contains(T request, TreeNode<T> *p){
  
  if(p == NULL)
    return false;
  else{
    if (p->getInfo() == request)
      return true;
    else
      return (contains(request, p->getLeft()) || contains(request, p->getRight()));
  }
  
}

template <class T>
void Tree<T>::showPreOrder(){
  showPreOrder(entrance);
  cout << endl;
}


//avlnode * x = static_cast<TreeNode<T>*>(p->getleft())

template <class T>
void Tree<T>::showPreOrder(TreeNode<T> *p){
  if(static_cast<TreeNode<T>*>(p) == NULL){
    return;
  }else{
    cout << static_cast<TreeNode<T>*>(p)->getInfo() << "-";
    showPreOrder(static_cast<TreeNode<T>*>(p->getLeft()));
    showPreOrder(static_cast<TreeNode<T>*>(p->getRight()));
  }
}

template <class T>
void Tree<T>::showInOrder(){
  showInOrder(entrance);
  cout << endl;
}

template <class T>
void Tree<T>::showInOrder(TreeNode<T> *p){
  if(static_cast<TreeNode<T>*>(p) != NULL){
    showInOrder(static_cast<TreeNode<T>*>(p->getLeft()));
    cout << static_cast<TreeNode<T>*>(p)->getInfo() << "-";
    showInOrder(static_cast<TreeNode<T>*>(p->getRight()));
  }
}

template <class T>
void Tree<T>::showPostOrder(){
  showPostOrder(entrance);
  cout << endl;
}

template <class T>
void Tree<T>::showPostOrder(TreeNode<T> *p){
  if(static_cast<TreeNode<T>*>(p) != NULL){
    showInOrder(static_cast<TreeNode<T>*>(p->getLeft()));
    showInOrder(static_cast<TreeNode<T>*>(p->getRight()));
    cout << p->getInfo() << "-";
  }
}

template <class T>
void Tree<T>::saveAsDot(string fileName, string graphName){
  ofstream output; 
  
  output.open(fileName.c_str(), fstream::out);
  output << "digraph " << graphName << "{" << endl;
  saveAsDot(output, entrance);
  output << "}" << endl;
  output.close();
}

template <class T>
void Tree<T>::saveAsDot(ofstream &output, TreeNode<T> *p){
  if(p != NULL){
    output << "  " << p->getLabel() << " [label ='" << p->getInfo() << "']" << endl;
    if(p->getLeft() != NULL)
      output << "  " << p->getLabel() << " -> " << p->getLeft()->getLabel() << endl;
    if(p->getRight() != NULL)
      output << "  " << p->getLabel() << " -> " << p->getRight()->getLabel() << endl;
    
    saveAsDot(output, p->getLeft());
    saveAsDot(output, p->getRight());
  }
}

#endif

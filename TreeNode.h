#ifndef _TreeNode_H_
#define _TreeNode_H_


using namespace std;

template <class T>
class TreeNode {
  public:
    TreeNode(T& newInfo, int counter){
      setInfo(newInfo);
      setLabel(counter);
      setLeft(NULL);
      setRight(NULL);   
    } 
    void setInfo(T newInfo);
    T getInfo();
    void setLabel(int newLabel);
    int getLabel();
    void setLeft(TreeNode *newLeft);
    TreeNode<T>* getLeft();
    void setRight(TreeNode *newRight);
    TreeNode<T>* getRight();
  protected:
    T info;
    int label;
    TreeNode *left;
    TreeNode *right;
  private:
};

template <class T>
void TreeNode<T>::setInfo(T newInfo){
  info = newInfo;
}

template <class T>
T TreeNode<T>::getInfo(){
  return info;
}

template <class T>
void TreeNode<T>::setLabel(int newLabel){
  label = newLabel;
}

template <class T>
int TreeNode<T>::getLabel(){
  return label;
}

template <class T>
void TreeNode<T>::setLeft(TreeNode *newLeft){
  left = newLeft;
}

template <class T>
TreeNode<T>* TreeNode<T>::getLeft(){
   return left;
}

template <class T>
void TreeNode<T>::setRight(TreeNode *newRight){
  right = newRight;
}

template <class T>
TreeNode<T>* TreeNode<T>::getRight(){
   return right;
}
#endif

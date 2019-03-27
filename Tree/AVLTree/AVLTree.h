//******************************
//**
//* AVLTree.h
//* YS [2018.5.20]
//* generic AVL binary search tree
//**
//******************************
#ifndef AVLTree_H
#define AVLTree_H
#include <iostream>

#include <queue>
#include <stack>


const char EHigher= 0;   //标志该节点左子树与右子树高度相等
const char LHigher= 1;   //标志左子树高于右子树
const char RHigher= -1;
//*****************************
//class: AVLTNode
template <typename T>
class AVLTNode
{

public:
 
  AVLTNode()
  {
    pLeft_ = NULL;
    pRight_=NULL;
    bf_ = EHigher;    //标志左右子树的高度差
    value_=0;
  }

  AVLTNode(const T& value, AVLTNode* pLeft=NULL, AVLTNode* pRight=NULL )
  {
   value_  =value;
   pLeft_  =pLeft;
   pRight_ =pRight;
   bf_ =EHigher;
  }
  T  value_;
  AVLTNode* pLeft_;
  AVLTNode* pRight_;
  char bf_;
};



//***************************
//class: AVLT
template <class T>
class AVLT
{

public:
  AVLT() {}

 ~AVLT()
  {
   //clear();
  }



  void deleteNodeByMerging(const T& value)
  {
   AVLTNode<T>** node =findNode(const_cast<T&>(value));
   deleteByMerging(node);
  }

  void deleteNodeByCopying(const T& value)
  {
   AVLTNode<T>** node =findNode(const_cast<T&>(value));
   deleteByCopying(node);
  } 
 
  void insert(const T& value);
 
  T* search(const T& value) 
  {
   AVLTNode<T>** pNode=NULL;
   pNode=findNode(const_cast<T&>(value));
   if(pNode)
     {
      std::cout<<"search():"
               <<value<<" is in the tree"<<std::endl;
      return &(*pNode)->value_;
     }
   else
      {
       std::cout<<"search():"
                <<value<<" is not in the tree"<<std::endl;
       return NULL;
     }
 
   }

  void inOrder()
  { 
   std::cout<<"the inOrder of the AVLTree is:"<<std::endl;
   inOrder(pRoot_);
  }

  void preOrder()
  {
   std::cout<<"the preOrder of the AVLTree is:"<<std::endl;
   preOrder(pRoot_);
  }  

static int nodeNum;
  void clear()
  {
    erase(pRoot_);
    std::cout<<"clear():clear over..."
             <<"\nthe num of node have be deleted is:"
             <<nodeNum<<std::endl;
  }


public:
  AVLTNode<T>* pRoot_ =NULL;

protected:
  void erase(AVLTNode<T>* pRoot);  
  void destory(AVLTNode<T>* pNode);
  void inOrder(AVLTNode<T>* pRoot);
  void preOrder(AVLTNode<T>* pRoot);
  void visit(T& value);
  AVLTNode<T>** findNode(T& value);
  void deleteByMerging(AVLTNode<T>** node);
  void deleteByCopying(AVLTNode<T>** node);
  void leftBalance(AVLTNode<T>** pRoot);   //维持左树平衡
  void rightBalance(AVLTNode<T>** pRoot);  
  void rRotate(AVLTNode<T>** pRoot);       //实现右旋转
  void lRotate(AVLTNode<T>** pRoot);

};
#include "AVLTree.cpp"
#endif

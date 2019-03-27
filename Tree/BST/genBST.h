//******************************
//**
//* genBST.h
//* YS [2018.5.9]
//* generic binary search tree
//**
//******************************
#ifndef GEN_BST_H
#define GEN_BST_H
#include <iostream>

#include <queue>


//*****************************
//class: BSTNode
template <typename T>
class BSTNode
{

public:
 
  BSTNode()
  {
    pLeft_ = NULL;
    pRight_=NULL;
  }

  BSTNode(const T& value, BSTNode* pLeft=NULL, BSTNode* pRight=NULL )
  {
   value_  =value;
   pLeft_  =pLeft;
   pRight_ =pRight;
  }
  T  value_;
  BSTNode* pLeft_;
  BSTNode* pRight_;
};



//***************************
//class: BST
template <class T>
class BST
{

public:
  BST()
  {
    pRoot_=0;
  }

 ~BST()
  {
   clear();
  }



  void deleteNodeByMerging(const T& value)
  {
   BSTNode<T>** node =findNode(const_cast<T&>(value));
   deleteByMerging(node);
  }

  void deleteNodeByCopying(const T& value)
  {
   BSTNode<T>** node =findNode(const_cast<T&>(value));
   deleteByCopying(node);
  } 
 
  void insert(const T& value);
 
  T* search(const T& value) 
  {
   BSTNode<T>** pNode=NULL;
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
   std::cout<<"the inOrder of the BST is:"<<std::endl;
   inOrder(pRoot_);
  }

  
  void clear()
  {
    clear(pRoot_);
  }


public:
  BSTNode<T>* pRoot_;

protected:
  void clear(BSTNode<T>*){};  //imcomplete  
  void inOrder(BSTNode<T>* pRoot);
  void visit(T& value);
  BSTNode<T>** findNode(T& value);
  void deleteByMerging(BSTNode<T>** node);
  void deleteByCopying(BSTNode<T>** node);
};




//*********************************************

template<class T> 
void BST<T>::insert(const T& value)
{
 BSTNode<T>* node=pRoot_ , *pPrev=0;
 while(node)
   {
     pPrev=node;
     if(value < node->value_ )
        node=node->pLeft_;
     else if(value > node->value_)
        node=node->pRight_;
     else
        {
          std::cout<<"the value is already in the tree..."<<std::endl;
          return;
        }
    }

    if(node==pRoot_)
       pRoot_ = new BSTNode<T>(value); 
    else if(value < pPrev->value_)
       pPrev->pLeft_ =new BSTNode<T>(value);
    else
       pPrev->pRight_=new BSTNode<T>(value);
}


template<class T>
BSTNode<T>** BST<T>::findNode( T& value)
{
 if(pRoot_==NULL)
  {
    std::cout<<"the tree is empty..."<<std::endl;
    return NULL;
  }
 BSTNode<T>* node=pRoot_ , *pPrevious=0;
 while(node)
  {
   if(node->value_ == value)
     {
       if(node==pRoot_) 
          return &pRoot_;
       else if(node == pPrevious->pLeft_) 
           return &(pPrevious->pLeft_);
       else 
          return &(pPrevious->pRight_);  
      }
    else if(value < node->value_)
        {
         pPrevious=node; 
         node=node->pLeft_;
        
        }
   else 
        {
         pPrevious=node;
         node=node->pRight_;
         
        }
  }
   
  return NULL;
}


template <class T>
void BST<T>::deleteByMerging(BSTNode<T>** pNode)
{
 
 if(pNode==NULL)
    std::cout<<"the value which to delete is not in the tree..."<<std::endl;
 else
{
  BSTNode<T>* tmp =(*pNode);
  if((*pNode)->pLeft_ == NULL)
     (*pNode) = (*pNode)->pRight_;
  else if((*pNode)->pRight_ == NULL)
     (*pNode) = (*pNode)->pLeft_;
  else 
    { 
      tmp=(*pNode)->pLeft_;
      while(tmp->pRight_)
            tmp=tmp->pRight_;
     	
      tmp->pRight_ =(*pNode)->pRight_;
      tmp=(*pNode);
      (*pNode)=(*pNode)->pLeft_;
    }
   std::cout<<tmp->value_<<"is delete from the tree..."<<std::endl;
   delete tmp;
   
 }
}

template<class T>
void BST<T>::deleteByCopying(BSTNode<T>** pPNode)
{
 if(pPNode==NULL)
    std::cout<<"the value which to delete is not in the tree..."<<std::endl;
 else
   {
     BSTNode<T>* tmp= (*pPNode) , *pPrev=NULL;
     
     if((*pPNode)->pLeft_ ==NULL)
        (*pPNode)=(*pPNode)->pRight_;
     else if((*pPNode)->pRight_==NULL)
        (*pPNode)=(*pPNode)->pLeft_;
     else
        {
         tmp=(*pPNode)->pLeft_;
         while(tmp->pRight_)
          {
            std::cout<<"right..."<<std::endl;
            pPrev=tmp;
            tmp=tmp->pRight_;
          }
           (*pPNode)->value_ = tmp->value_;
           if(pPrev)
              pPrev->pRight_=NULL;
         } 
       delete tmp;    
   } 
}

template<class T>
void BST<T>::visit(T& value)
{
 std::cout<<value<<std::endl;
}

template <class T>
void BST<T>::inOrder(BSTNode<T>* pRoot)
{
  if(pRoot !=NULL)
   {
     inOrder(pRoot->pLeft_);
     visit(pRoot->value_);
     inOrder(pRoot->pRight_);
   }
}

#endif

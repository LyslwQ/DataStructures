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




//*********************************************
template<class T>
int AVLT<T>::nodeNum=0;

//方案一：相比方案二，可以减小函数栈的大小
template<class T>
void AVLT<T>::erase(AVLTNode<T>* pRoot)
{
 AVLTNode<T>* pNode=pRoot;
 for(;pNode !=NULL; pRoot=pNode)
    {
      erase(pRoot->pRight_);
      pNode=pRoot->pLeft_;
      destory(pRoot);
    }
}//*/

/*方案二：
template<class T>
void AVLT<T>::erase(AVLTNode<T>* pRoot)
{
 if(pRoot==NULL)
   return;

 erase(pRoot->pLeft_);
 erase(pRoot->pRight_); 
 destory(pRoot);
     
}//*/



template<class T>
void AVLT<T>::destory(AVLTNode<T>* pNode)
{
  nodeNum++;
  delete pNode;
}

template<class T> 
void AVLT<T>::insert(const T& value)
{
 AVLTNode<T>** pnode=&pRoot_ , *pPrev=0;
 std::stack<AVLTNode<T>**> nodeStack;    //用于存储插入节点时经过的路径的节点
 while((*pnode))                         //插入节点后沿原路径更新节点的fd_
   {
     pPrev=(*pnode);
     nodeStack.push(pnode);
     if(value < pPrev->value_ )
        pnode= &(*pnode)->pLeft_;
     else if(value > pPrev->value_)
             pnode= &(*pnode)->pRight_;
     else
        {
          std::cout<<"the value is already in the tree..."<<std::endl;
          return;
        }
    }
    
    (*pnode)=new AVLTNode<T>(value);   //找到空子节点后将节点插入
    if((*pnode)==pRoot_)
       pRoot_ = (*pnode); 
    else if(value < pPrev->value_)
       pPrev->pLeft_ =(*pnode);
    else
       pPrev->pRight_=(*pnode);
    while(!nodeStack.empty())         //节点插入后上溯，更新fd_,
     {                                //必要时进行平衡处理
      AVLTNode<T>** pPrev =NULL;      
      pPrev=nodeStack.top();
      nodeStack.pop();
      if(*pnode==(*pPrev)->pLeft_) 
         {
          if((*pPrev)->bf_ == EHigher)  //更新节点的fd_标志
             (*pPrev)->bf_ =LHigher;
          else if((*pPrev)->bf_ == RHigher)
             (*pPrev)->bf_ =EHigher;
          else 
             {
              leftBalance(pPrev);      //在左子树插入节点后，若树本来是偏左的，
              break;                   //进行左平衡处理
             }  
         } 
      else
         {
           if((*pPrev)->bf_ == EHigher)
              (*pPrev)->bf_ = RHigher;
           else if((*pPrev)->bf_ == LHigher)
              (*pPrev)->bf_ = EHigher;
           else
              {
               rightBalance(pPrev);
               break;
              }
         } 
    }
}

template<class T>
void AVLT<T>::rightBalance(AVLTNode<T>** pRoot)
{
 if((*pRoot)->pRight_->bf_ == LHigher)  //左旋时，若子树偏左，则
   {                                    //先将左子树右旋，再沿父节点左旋
    if( (*pRoot)->pRight_->pLeft_->bf_ ==EHigher )
      {
       (*pRoot)->pRight_->bf_=EHigher;
       (*pRoot)->bf_ = EHigher;
      }
    else if( (*pRoot)->pRight_->pLeft_->bf_=LHigher)
      {
       (*pRoot)->pRight_->bf_ =RHigher;
       (*pRoot)->bf_ =EHigher;
      }
    else 
     { 
       (*pRoot)->bf_ =LHigher;
       (*pRoot)->pRight_->bf_=EHigher;
     }
    
    if(pRoot_ ==(*pRoot))
       {
        rRotate(& (pRoot_->pRight_));
        lRotate(&pRoot_);
       }
    else
       {
        rRotate(& (pRoot_->pRight_));
        lRotate(&pRoot_);
       }
      
   }
 else
   {
     (*pRoot)->bf_ =EHigher;
     (*pRoot)->pRight_->bf_=EHigher;
    if(pRoot_==(*pRoot))
     lRotate(&pRoot_);
    else
     lRotate(pRoot);
   } 
}


template<class T>
void AVLT<T>::leftBalance(AVLTNode<T>** pRoot)
{

 std::cout<<"leftBalance..."<<std::endl;
 if((*pRoot)->pLeft_->bf_==RHigher)  //若左子树是偏右的（跟根节点偏向相反）     
  {                                  //先对左子树进行左旋处理

     AVLTNode<T>* leftRight =  (*pRoot)->pLeft_->pRight_;
    if( leftRight->bf_ ==LHigher )
     {
      (*pRoot)->bf_ = RHigher;
      (*pRoot)->pLeft_->bf_ =EHigher; 
     }
   else if(leftRight->bf_ ==RHigher )
     {
      (*pRoot)->bf_ =LHigher;
      (*pRoot)->pLeft_->bf_ =LHigher;
     }
   else 
     {
      (*pRoot)->bf_ =EHigher;
      (*pRoot)->pLeft_->bf_ =EHigher;
     }
   
     (*pRoot)->pLeft_->pRight_->bf_ =EHigher;  
     if((*pRoot) == pRoot_)
       {
         lRotate(&((*pRoot)->pLeft_));
         rRotate(&pRoot_);
       }
      else
       {
        lRotate(&((*pRoot)->pLeft_));
        rRotate(pRoot);
        }

   }
  else
  {
   (*pRoot)->bf_ =EHigher;
   (*pRoot)->pLeft_->bf_ =EHigher;
   if( (*pRoot)==pRoot_)
   rRotate(&pRoot_);
   else
   rRotate(pRoot);
  }
}

template<class T>
void AVLT<T>::rRotate(AVLTNode<T>** pRoot)
{
 AVLTNode<T>* leftNode = (*pRoot)->pLeft_;
 (*pRoot)->pLeft_ = leftNode->pRight_;
 leftNode->pRight_  = (*pRoot);
 (*pRoot) =leftNode;
}

template<class T>
void AVLT<T>::lRotate(AVLTNode<T>** pRoot)
{
 AVLTNode<T>* rightNode =(*pRoot)->pRight_;
 (*pRoot)->pRight_ =rightNode->pLeft_;
  rightNode->pLeft_ =(*pRoot);
 (*pRoot) =rightNode;
}

template<class T>
AVLTNode<T>** AVLT<T>::findNode( T& value)
{
 if(pRoot_==NULL)
  {
    std::cout<<"the tree is empty..."<<std::endl;
    return NULL;
  }
 AVLTNode<T>* node=pRoot_ , *pPrevious=0;
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
void AVLT<T>::deleteByMerging(AVLTNode<T>** pNode)
{
 
 if(pNode==NULL)
    std::cout<<"the value which to delete is not in the tree..."<<std::endl;
 else
{
  AVLTNode<T>* tmp =(*pNode);
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
void AVLT<T>::deleteByCopying(AVLTNode<T>** pPNode)
{
 if(pPNode==NULL)
    std::cout<<"the value which to delete is not in the tree..."<<std::endl;
 else
   {
     AVLTNode<T>* tmp= (*pPNode) , *pPrev=NULL;
     
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
void AVLT<T>::visit(T& value)
{
 std::cout<<value<<std::endl;
}

template <class T>
void AVLT<T>::inOrder(AVLTNode<T>* pRoot)
{
  if(pRoot !=NULL)
   {
     inOrder(pRoot->pLeft_);
     visit(pRoot->value_);
     inOrder(pRoot->pRight_);
   }
}

template<class T>
void AVLT<T>::preOrder(AVLTNode<T>* pRoot)
{
 if(pRoot !=NULL)
   {
     visit(pRoot->value_);
     preOrder(pRoot->pLeft_);
     preOrder(pRoot->pRight_);
   }

}
#endif

//****************************
//**
//* main.cpp
//* YS [5 9 2018]
//**
//****************************

#include <iostream>
#include <stdio.h>
#include "AVLTree.h"

int main()
{
 AVLT<int> myAVLT;
 for(int i=0;i<50000;i++) 
 myAVLT.insert(i);
 myAVLT.preOrder();
 std::cout<<"input a character to start clear..."<<std::endl;
 getchar();
 myAVLT.clear();
// myBST.deleteNodeByCopying(7);
// myBST.deleteNodeByCopying(5);
//myBST.deleteNodeByMerging(4);
// myBST.search(5);
 //myAVLT.inOrder();
 
 return 0;
}

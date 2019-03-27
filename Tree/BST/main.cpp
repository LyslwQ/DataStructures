//****************************
//**
//* main.cpp
//* YS [5 9 2018]
//**
//****************************

#include <iostream>

#include "genBST.h"

int main()
{
 BST<int> myBST; 
 for(int i=0;i<50000;i++)
 myBST.insert(i);
 myBST.inOrder();
// myBST.deleteNodeByCopying(5);

 //myBST.search(5);
 
 return 0;
}

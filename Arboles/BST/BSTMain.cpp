#include <iostream>
#include "Modulos/BSTImplementation.h"

int main(){
    BST::BinarySearchTree<int> arbol;

    arbol.append(5);
    arbol.append(3);
    arbol.append(10);
    arbol.append(7);
    arbol.append(12);
    arbol.append(6);
    arbol.append(8);

    arbol.doubleRotationToLeft(arbol.search(5));

    return 0;
}
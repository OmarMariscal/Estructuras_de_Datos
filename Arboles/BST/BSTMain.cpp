#include <iostream>
#include "Modulos/BSTImplementation.h"

int main(){
    BST::BinarySearchTree<int> arbol;

    arbol.append(32);
    arbol.append(40);
    arbol.append(50);
    arbol.append(39);

    arbol.remove(32);

    arbol.printTreeInOrder();

    return 0;
}
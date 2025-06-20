#include <iostream>
#include "Modulos/BSTImplementation.h"

int main(){
    BST::BinarySearchTree<int> arbol;

    arbol.append(4);
    arbol.append(5);
    arbol.append(2);
    arbol.append(6);
    arbol.append(7);
    arbol.append(1);

    arbol.cleanTree();

    try{
        arbol.printTreeInOrder();
        std::cout<<"fds";
    }
    catch(const BSTExcept::NoItems &mensaje){
        std::cout<<"No hay Items Registrados";
    }

    return 0;
}
#include <iostream>
#include "Modulos/BSTImplementation.h"

int main(){
    BST::SubBinarySearchTree<int> arbol(new int(3));

    arbol.insert(new int(5));
    arbol.insert(new int(4));

    arbol.remove(3);

    if(arbol.search(3))
        std::cout<<"No Eliminado";
    else
        std::cout<<"Sin Eliminar";

    return 0;
}
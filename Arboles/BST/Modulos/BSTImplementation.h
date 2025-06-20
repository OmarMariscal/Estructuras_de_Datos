#ifndef BSTImplementation_H
#define BSTImplementation_H

#include <iostream>
#include "BSTExceptions.h"

namespace BST_Nodes{
    template<typename T>
    class BST_Node{
        public: 
            T* value;
            BST_Node *leftTree;
            BST_Node *rightTree;
        

            BST_Node(T*);
    };

    template<typename T>
    BST_Node<T>::BST_Node(T* value){
        this->value = value;
        leftTree = nullptr;
        rightTree = nullptr;
    }
}

namespace BST{
    template<typename T>
    class SubBinarySearchTree{
        public:
            T* value;
            SubBinarySearchTree* leftTree;
            SubBinarySearchTree* rightTree;
            SubBinarySearchTree* father;
        
            SubBinarySearchTree(T*);
            void insert(T*);
            SubBinarySearchTree<T>* search(T);
            void remove(T);
            void removeSheet(SubBinarySearchTree<T>*);
            void remove1Son(SubBinarySearchTree<T>*);
    };
    
    template<typename T>
    SubBinarySearchTree<T>::SubBinarySearchTree(T* value){
        this->value = value;
        leftTree = nullptr;
        rightTree = nullptr;
        father = nullptr;
    }

    template<typename T>
    void SubBinarySearchTree<T>::insert(T* elemento){
        if((*elemento > *value) && (rightTree == nullptr)){
            SubBinarySearchTree<T>* newTree = new SubBinarySearchTree(elemento);
            newTree->father = this;
            rightTree = newTree;
        }

        if((*elemento < *value) && (leftTree == nullptr)){
            SubBinarySearchTree<T>* newTree = new SubBinarySearchTree(elemento);
            newTree ->father = this;
            leftTree = newTree;            
        }


        if((*elemento >  *value) && (rightTree != nullptr))
            rightTree->insert(elemento);

        if((*elemento < *value) && (leftTree != nullptr))
            leftTree->insert(elemento);
    }

    template<typename T>
    SubBinarySearchTree<T>* SubBinarySearchTree<T>::search(T elemento){
        if(*value == elemento)
            return this;
        if((elemento > *value) && (rightTree != nullptr))
            return rightTree->search(elemento);

        if((elemento < *value) && (leftTree != nullptr))
            return leftTree->search(elemento);
        
        return nullptr;
    }

    template<typename T>
    void SubBinarySearchTree<T>::removeSheet(SubBinarySearchTree<T>* nodo){
        //Si es la hoja izquierda
        if(nodo->father->leftTree == nodo){
            nodo->father->leftTree = nullptr;
            delete nodo;
        }
        //Si la Hoja es la Derecha
        else{
            nodo->father->rightTree = nullptr;
            delete nodo;
        }
    }

    template<typename T>
    void SubBinarySearchTree<T>::remove1Son(SubBinarySearchTree<T>* nodo){
        //Si el hijo restante es el izquierdo
        if(nodo->leftTree != nullptr)
            if(nodo->father->leftTree == nodo)
                nodo->father->leftTree = nodo->leftTree;
            else
                nodo->father->rightTree = nodo->leftTree;
        
        else
            if(nodo->father->leftTree == nodo)
                nodo->father->leftTree = nodo->rightTree;
            else
                nodo->father->rightTree = nodo->rightTree;

        delete nodo;
    }

    template<typename T>
    void SubBinarySearchTree<T>::remove(T elemento){
        SubBinarySearchTree<T>* nodo = search(elemento);

        if(!nodo)
            throw EXC_BTS::ItemNotFoud();

        if(nodo->leftTree == nullptr){
            if(nodo->rightTree == nullptr){
                removeSheet(nodo); //Nodo Hoja
            }
            else
                remove1Son(nodo); //Nodo con 1 hijo
        }

        else if(nodo->rightTree == nullptr){
            if(nodo->leftTree == nullptr)
                removeSheet(nodo);
            else
                remove1Son(nodo);
        }
        
    }

}

#endif
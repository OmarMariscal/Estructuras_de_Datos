#ifndef BSTImplementation_H
#define BSTImplementation_H

#include <iostream>
#include "BSTExceptions.h"

namespace BST_Nodes{
    template<typename T>
    class BST_Node{
        public:
            T* value;
            BST_Node<T>* leftNode;
            BST_Node<T>* rightNode;
            BST_Node<T>* father;

            BST_Node(T*);
            BST_Node(T);

    };

    template<typename T>
    BST_Node<T>::BST_Node(T* value){
        this->value = value;
        leftNode = nullptr;
        rightNode = nullptr;
        father = nullptr;
    }

    template<typename T>
    BST_Node<T>::BST_Node(T data){
        value = new T(data);
        leftNode = nullptr;
        rightNode = nullptr;
        father = nullptr;
    }
}

namespace BST{
    using BST_Nodes::BST_Node;

    template<typename T>
    class BinarySearchTree{
        private:
            int size;
            BST_Node<T> *root;

            void append(BST_Node<T>*, const T&);

            BST_Node<T>* search(BST_Node<T>*, const T&);
            
            void printTreeInOrder(BST_Node<T>*);
        public:
            /// @brief Construir el BST por defecto
            BinarySearchTree();

            /// @brief Agregar un elemento al BST
            /// @param  Value Elemento que se va a agregar al BST
            void append(const T&);

            /// @brief Buscar un elemento en el BST
            /// @param  Value Valor que se buscará en el BST
            /// @return Apuntador al Nodo encontrado
            BST_Node<T>* search(const T&);

            /// @brief Imprimir el BST completo en orden
            void printTreeInOrder();
            
    };

    template<typename T>
    BinarySearchTree<T>::BinarySearchTree(){
        size = 0;
        root = nullptr;
    }

    template<typename T>
    void BinarySearchTree<T>::append(const T& element){
        //Si no hay Elementos en el Árbol
        if(!root){
            root = new BST_Node<T>(element);
            size++;
        }
        else //Si hay al menos 1 elemento
            append(root, element);
    }
    
    template<typename T>
    void BinarySearchTree<T>::append(BST_Node<T>* nodo, const T& element){
        //Agregar el elemento en la derecha
        if((element > *nodo->value) && (nodo->rightNode == nullptr)){
            nodo->rightNode = new BST_Node(element);
            nodo->rightNode->father = nodo;
            size++;
        }
        
        if((element < *nodo->value) && (nodo->leftNode == nullptr)){
            nodo->leftNode = new BST_Node(element);
            nodo->leftNode->father = nodo;
            size++;
        }

        //Si los nodos ya están ocupados
        if((element > *nodo->value) && (nodo->rightNode != nullptr))
            append(nodo->rightNode, element);
        if((element < *nodo->value) && (nodo->leftNode != nullptr))
            append(nodo->leftNode,element);

    }

    template<typename T>
    BST_Node<T>* BinarySearchTree<T>::search(const T &element){
        return search(root, element);
    }

    template<typename T>
    BST_Node<T>* BinarySearchTree<T>::search(BST_Node<T>* nodo, const T &element){
        if(*nodo->value == element)
            return nodo;
        if((element > *nodo->value) && (nodo->rightNode != nullptr))
            return search(nodo->rightNode,element);
        else if((element < *nodo->value) && (nodo->leftNode != nullptr))
            return search(nodo->leftNode,element);
        throw BSTExcept::ItemNotFound();   
    }
    
    template<typename T>
    void BinarySearchTree<T>::printTreeInOrder(){
        if(size == 0)
            throw BSTExcept::NoItems();
        printTreeInOrder(root);
    }

    template<typename T>
    void BinarySearchTree<T>::printTreeInOrder(BST_Node<T>* node){
        if(node->leftNode != nullptr)
            printTreeInOrder(node->leftNode);
        std::cout<<*node->value<<std::endl;
        if(node->rightNode != nullptr)
            printTreeInOrder(node->rightNode);
    }

    
}

#endif
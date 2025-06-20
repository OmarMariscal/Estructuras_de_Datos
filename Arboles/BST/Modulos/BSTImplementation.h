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
            ~BST_Node();

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

    template<typename T>
    BST_Node<T>::~BST_Node(){
        delete value;
        leftNode = nullptr;
        rightNode = nullptr;
        father= nullptr;
    }
}

namespace BST{
    using BST_Nodes::BST_Node;

    template<typename T>
    class BinarySearchTree{
        private:
            int amount;
            BST_Node<T> *root;

            void append(BST_Node<T>*, const T&);

            BST_Node<T>* search(BST_Node<T>*, const T&);
            
            void printTreeInOrder(BST_Node<T>*);
            
            void cleanTree(BST_Node<T>*);
            
            void remove(BST_Node<T>*, const T&);
        public:
            /// @brief Construir el BST por defecto
            BinarySearchTree();

            ~BinarySearchTree();

            /// @brief Agregar un elemento al BST
            /// @param  Value Elemento que se va a agregar al BST
            void append(const T&);

            /// @brief Buscar un elemento en el BST
            /// @param  Value Valor que se buscará en el BST
            /// @return Apuntador al Nodo encontrado
            BST_Node<T>* search(const T&);

            /// @brief Imprimir el BST completo en orden
            void printTreeInOrder();

            /// @brief Elimina todos los nodos y reestablece el BST
            void cleanTree();

            /// @brief Cantidad de nodos en el BST
            /// @return Numero de elementos del BST
            int size();
            
            void remove(const T&);
    };

    template<typename T>
    BinarySearchTree<T>::BinarySearchTree(){
        amount = 0;
        root = nullptr;
    }

    template<typename T>
    BinarySearchTree<T>::~BinarySearchTree(){
        cleanTree();    
    }

    template<typename T>
    void BinarySearchTree<T>::append(const T& element){
        //Si no hay Elementos en el Árbol
        if(!root){
            root = new BST_Node<T>(element);
            amount++;
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
            amount++;
        }
        
        if((element < *nodo->value) && (nodo->leftNode == nullptr)){
            nodo->leftNode = new BST_Node(element);
            nodo->leftNode->father = nodo;
            amount++;
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
        if(amount == 0)
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

    template<typename T>
    void BinarySearchTree<T>::cleanTree(){
        if(amount == 0)
            return;
        cleanTree(root);
        root = nullptr;
        amount = 0;
    }

    template<typename T>
    void BinarySearchTree<T>::cleanTree(BST_Node<T>* node){
        if(node->leftNode != nullptr)
            cleanTree(node->leftNode);
        if(node->rightNode != nullptr)
            cleanTree(node->rightNode);
        delete node;
    }

    template<typename T>
    int BinarySearchTree<T>::size(){
        return amount;
    }
}

#endif
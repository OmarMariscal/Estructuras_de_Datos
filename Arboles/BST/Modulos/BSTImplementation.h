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

            void balanceTree(BST_Node<T>*);
            void balanceSubTree(BST_Node<T>*, int);

            //Auxiliares para eliminar nodos
            void removeSheet(BST_Node<T>*);
            void remove1Son(BST_Node<T>*);
            void remove2Sons(BST_Node<T>*);
            BST_Node<T>* findMenorNode(BST_Node<T>*);
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
            
            /// @brief Eliminar un elemento del BST
            /// @param  Elemento a eliminar del BST
            void remove(T);

            int calculateHeight(BST_Node<T>*);
            int calculateFE(BST_Node<T>*);

            void simpleRotationToRight(BST_Node<T>*);
            void simpleRotationToLeft(BST_Node<T>*);
            void doubleRotationToRight(BST_Node<T>*);
            void doubleRotationToLeft(BST_Node<T>*);
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

        //Balancear el Árbol
        balanceTree(root);
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

    template<typename T>
    void BinarySearchTree<T>::remove(T element){
        if(amount == 0)
            throw BSTExcept::NoItems();
        
        BST_Node<T>* node = search(element);
        //SI es un nodo hoja
        if((node->leftNode == nullptr) && (node->rightNode == nullptr))
            removeSheet(node);

        //Si solo tiene un Hijo
        else if(((node->leftNode != nullptr) && (node->rightNode == nullptr)) || ((node->leftNode == nullptr) && (node->rightNode != nullptr)))
            remove1Son(node);   

        else
            remove2Sons(node);

        amount--;
    }

    template<typename T>
    void BinarySearchTree<T>::removeSheet(BST_Node<T>* node){
        if(node == root)
            root = nullptr;

        else if(node->father->leftNode == node)
                node->father->leftNode = nullptr;
            else
                node->father->rightNode = nullptr;

        delete node;
    }

    template<typename T>
    void BinarySearchTree<T>::remove1Son(BST_Node<T>* node){
        if(node == root)
            if(node->leftNode != nullptr)
                root = node->leftNode;
            else
                root = node->rightNode;

        else if(node->father->leftNode == node){
            if(node->leftNode != nullptr)
                node->father->leftNode = node->leftNode;
            else
                node->father->leftNode = node->rightNode;
        }

        else if(node->father->rightNode == node){
            if(node->leftNode != nullptr)
                node->father->rightNode = node->leftNode;
            else
                node->father->rightNode = node->rightNode;
        }
        delete node;
    }

    template<typename T>
    BST_Node<T>* BinarySearchTree<T>::findMenorNode(BST_Node<T>* node){
        if(node->leftNode != nullptr)
            return findMenorNode(node->leftNode);
        else
            return node;
    }

    template<typename T>
    void BinarySearchTree<T>::remove2Sons(BST_Node<T>* node){
        BST_Node<T>* succesor = findMenorNode(node->rightNode);
        //Si no es la raíz
        if(node != root){
            //Encontrar lado en el que el nodo esta respecto al padre:
            if(node->father->leftNode == node)
                node->father->leftNode = succesor;    

            else
                node->father->rightNode = succesor;
            
            node->leftNode->father = succesor;

            if(node->rightNode != succesor)
                node->rightNode->father = succesor;
            
            succesor->leftNode = node->leftNode;
            if(node->rightNode != succesor)
                succesor->rightNode = node->rightNode;
            succesor->father = node->father;
        }
        //Si es la raíz
        else{
            if(succesor->rightNode != nullptr)
                succesor->father->leftNode = succesor->rightNode;
            else
                succesor->father->leftNode = nullptr;
            succesor->father = nullptr;
            succesor->leftNode = root->leftNode;
            succesor->rightNode = root->rightNode;
            root = succesor;
        }
        delete node;
    }

    template <typename T>
    int BinarySearchTree<T>::calculateHeight(BST_Node<T>* node){
        if(node == nullptr)
            return 0;
        else{
            int altura_izquierda = calculateHeight(node->leftNode);
            int altura_derecha = calculateHeight(node->rightNode);

            if(altura_izquierda>= altura_derecha)
                return 1 + altura_izquierda;
            return 1 + altura_derecha;
        }
        
    }

    template<typename T>
    int BinarySearchTree<T>::calculateFE(BST_Node<T>* node){
        return calculateHeight(node->rightNode) - calculateHeight(node->leftNode);
    }

    template<typename T>
    void BinarySearchTree<T>::simpleRotationToRight(BST_Node<T>* node){
        BST_Node<T>* qNode = node->leftNode;

        node->leftNode = qNode->rightNode;
        if(qNode->rightNode != nullptr)
            qNode->rightNode->father = node;
        qNode->rightNode = node;

        if(node->father != nullptr)
            node->father->rightNode = qNode;
        if(qNode->rightNode != nullptr)
            qNode->rightNode->father = node;
        
        //Reasignación de padres
        qNode->father = node->father;
        node->father = qNode;

        if(root == node){
            root = qNode;
            root->father = nullptr;
        }
    }

    template<typename T>
    void BinarySearchTree<T>::simpleRotationToLeft(BST_Node<T>* node){
        BST_Node<T>* qNode = node->rightNode;

        node->rightNode = qNode->leftNode;

        if(qNode->leftNode != nullptr)
            qNode->leftNode->father = node;

        qNode->leftNode = node;

        if(node->father != nullptr)
            node->father->leftNode = qNode;
        
        if(qNode->leftNode != nullptr)
            qNode->leftNode->father = node;

        //Reasignación de Padres
        qNode->father = node->father;
        node->father = qNode;

        if(root == node){
            root = qNode;    
            root->father = nullptr;        
        }

    }

    template<typename T>
    void BinarySearchTree<T>::doubleRotationToRight(BST_Node<T>* node){
        simpleRotationToLeft(node->leftNode);
        simpleRotationToRight(node);
    }

    template<typename T>
    void BinarySearchTree<T>::doubleRotationToLeft(BST_Node<T>* node){
        simpleRotationToRight(node->rightNode);
        simpleRotationToLeft(node);
    }

    template <typename T>
    void BinarySearchTree<T>::balanceTree(BST_Node<T>* node){
        if(node->leftNode != nullptr)
            balanceTree(node->leftNode);
        if(node->rightNode != nullptr)
            balanceTree(node->rightNode);
        int FE = calculateFE(node);
        if(FE == 2 || FE == -2)
            balanceSubTree(node,FE);
    }

    template <typename T>
    void BinarySearchTree<T>::balanceSubTree(BST_Node<T>* node, int FE){
        if(FE  == -2){
            if(calculateFE(node->leftNode) == -1)
                simpleRotationToRight(node);
            if(calculateFE(node->leftNode) == 1)
                doubleRotationToRight(node);
        }

        if(FE == 2){
            if(calculateFE(node->rightNode) == 1)
                simpleRotationToLeft(node);
            if(calculateFE(node->rightNode) == -1)
                doubleRotationToLeft(node);
        }
    }
}

#endif
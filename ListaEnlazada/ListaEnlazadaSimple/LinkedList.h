#ifndef LinkedList_H
#define LinkedList_H

#include <iostream>
#include "LinkedListExceptions.h"


namespace Nodos{
    template<typename T>
    class NodoListaSimple{
        public:
            T *data;
            NodoListaSimple<T> *next;
            
            NodoListaSimple(T*);
            ~NodoListaSimple();
    };

    template<typename T>
    NodoListaSimple<T>::NodoListaSimple(T* data){
        this->data = data;
        next = nullptr;
    }

    template<typename T>
    NodoListaSimple<T>::~NodoListaSimple(){
        delete data;
    }
}

namespace LinkedList{
    using Nodos::NodoListaSimple;
    
    template<typename T>
    class LinkedList{
        public:
            int numeroElementos;
            NodoListaSimple<T> *head;
            NodoListaSimple<T> *tail;
        public:
            /// @brief Constructor por defecto de la Lista Enlazada
            LinkedList();

            /// @brief Destructor que libera la memoria de los elementos de la Lista Enlazada.
            ~LinkedList();

            /// @brief Agregar un elemento al final de la lista
            /// @param  Elmento Data que se agregará
            void append(const T&);

            /// @brief Agregar un elemento al principio de la lista
            /// @param  Elemento Data que se agregará
            void prepend(const T&);

            /// @brief Eliminar un elemento por el índice
            /// @param  Index Numero de la posición del elemento que se eliminará
            void removeAt(const int&);

            /// @brief Insertar un elemento en un determinado Índice
            /// @param  Data Contenido que se va a inserta en la Lista Enlazada
            /// @param  Index Índice dónde se insertará el contenido.
            void insertAt(const T&, const int&);

            /// @brief Buscar la primera conincidencia con el valor introducido
            /// @param  Elemento Valor que se buscará
            /// @return Apuntador al elemento que se encontró. nullptr en caso de no encontrarse
            T *searchByValue(const T&);

            /// @brief Buscar el índice introducido
            /// @param  Index Índice de la lista enlazada
            /// @return Apuntador al elemento enontrado, nullptr en caso de no encontrarse
            T *searchByIndex(const int&);

            /// @brief Imprimir todo el contenido de la Lista Enlazada
            void printList() const;

            /// @brief Número de elementos registrados
            /// @return Cantidad de elementos
            int size() const;
    };

    template<typename T>
    LinkedList<T>::LinkedList(){
        numeroElementos = 0;
        head = nullptr;
        tail = nullptr;
    }

    template<typename T>
    LinkedList<T>::~LinkedList(){
        //Si hay elementos registrados.
        NodoListaSimple<T> *actual = head;
        NodoListaSimple<T> *siguiente = head;

        while(actual){
            siguiente = siguiente->next;
            delete actual;
            actual = siguiente;
        }
    }
    template <typename T>
    void LinkedList<T>::append(const T& newItem){
        T* data = new T(newItem);
        NodoListaSimple<T> *newNodo = new NodoListaSimple<T>(data);
        //Si es el primer elemento
        if(!head)
            head = newNodo;
        else //Si no lo es
            tail->next = newNodo;
        
        tail = newNodo;
        numeroElementos+=1;
    }

    template<typename T>
    void LinkedList<T>::prepend(const T& newItem){
        //Prepara el Nuevo Ítem como un apuntador
        T* data = new T(newItem);
        //Crear un Nodo Simple
        NodoListaSimple<T> *newNodo = new NodoListaSimple<T>(data);

        //Si es el primer elemento
        if(numeroElementos == 0)
            head = tail = newNodo;
        else{ //Si no lo es
            newNodo->next = head;
            head = newNodo;            
        }
        numeroElementos++;
    }

    template <typename T>
    void LinkedList<T>::removeAt(const int &index){
        if(numeroElementos == 0)
            throw EXC::NoItems();
        if((index > numeroElementos-1) || (index < 0))
            throw EXC::IndexOutOf();
        //Obtener el nodo que se quiere eliminar y el nodo anterior
        NodoListaSimple<T> *actual = head;
        NodoListaSimple<T> *anterior = nullptr;
        for(int i = 0; i < index; i++){
            anterior = actual;
            actual = actual->next;
        }

        //Si se elimina la cabeza
        if(actual == head)
            head = head->next;
        else
            anterior->next = actual->next;
        
        delete actual;
        numeroElementos--;

        //Si era el único elemento de la lista
        if(numeroElementos == 0)
            head = tail = nullptr;
        else if(numeroElementos == 1) //Si queda 1 elemento
            tail = head;
    }

    template <typename T>
    void LinkedList<T>::insertAt(const T &newItem, const int &index){
        if((index > numeroElementos) || (index < 0))
            throw EXC::IndexOutOf();
        
            //Si es el primer elemento
        if(index == 0){
            prepend(newItem);
            return;
        }
        //Si es el último elemento        
        if(index == numeroElementos){
            append(newItem);
            return;
        }

        //Crear el tipo de dato T
        T* data = new T(newItem);
        NodoListaSimple<T> *newNodo = new NodoListaSimple(data);

        //Encontrar la posición donde se quiere insertar el Elemento:
        NodoListaSimple<T> *anterior = head;

        for(int i = 0; i < index - 1 ; i++)
            anterior = anterior->next;

        newNodo->next = anterior->next;
        anterior->next = newNodo;
        numeroElementos++;
    }

    template <typename T>
    void LinkedList<T>::printList() const{
        if(!head){
            std::cout<<"''"<<std::endl;
            return;
        }
        NodoListaSimple<T> *actual = head;
        int count = 0;
        while(actual){
            count++;
            std::cout<<count<<"- "<<*actual->data<<std::endl;
            actual = actual->next;
        }
    }

    template<typename T>
    T*LinkedList<T>::searchByIndex(const int &index){
        if(numeroElementos == 0)
            throw EXC::NoItems();
        if((index > numeroElementos-1) || (index < 0))
            throw EXC::IndexOutOf();
        NodoListaSimple<T> *search = head;
        for(int i = 0; i < index; i++)
            search = search->next;
        return search->data;
    }

    template<typename T>
    T*LinkedList<T>::searchByValue(const T&search){
        if(numeroElementos == 0)
            throw EXC::NoItems();
        NodoListaSimple<T> *actual = head;
        while(actual){
            if(*actual->data == search)
                return actual->data;     
            actual = actual->next;       
        }

        throw EXC::ItemNotFound();
    }
}

#endif
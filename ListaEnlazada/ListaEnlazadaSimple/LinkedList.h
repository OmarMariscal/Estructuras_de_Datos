#ifndef LinkedList_H
#define LinkedList_H

#include <iostream>
#include <stdexcept>

namespace EXC{
    class NoItems : public std::runtime_error{
        public:
            NoItems(const std::string &mensaje = "No hay Items Registrados") : runtime_error(mensaje){}
    };

    class IndexOutOf : public std::runtime_error{
        public:
            IndexOutOf(const std::string &mensaje = "El indice esta fuera del Rango de la Lista") : runtime_error(mensaje){}
    };
}


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
        private:
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
            void removeAt(const int);

            /// @brief Insertar un elemento en un determinado Índice
            /// @param  Data Contenido que se va a inserta en la Lista Enlazada
            /// @param  Index Índice dónde se insertará el contenido.
            void insertAt(const T&, const int);

            /// @brief Buscar la primera conincidencia con el valor introducido
            /// @param  Elemento Valor que se buscará
            /// @return Apuntador al elemento que se encontró. nullptr en caso de no encontrarse
            NodoListaSimple<T> *searchByValue(const T) const;

            /// @brief Buscar el índice introducido
            /// @param  Index Índice de la lista enlazada
            /// @return Apuntador al elemento enontrado, nullptr en caso de no encontrarse
            NodoListaSimple<T> *searchByIndex(const int&) const;

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

}


#endif
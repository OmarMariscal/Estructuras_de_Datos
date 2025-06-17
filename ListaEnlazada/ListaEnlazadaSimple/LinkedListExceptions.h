#ifndef LinkedListExceptions_H
#define LinkedListExceptions_H

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

    class InvalidIndex : public  std::runtime_error{
        public:
            InvalidIndex (const std::string &mensaje = "Indice no es valido") : runtime_error(mensaje){}
    };

    class ItemNotFound : public std::runtime_error{
        public:
            ItemNotFound (const std::string &mensaje = "El elemento buscado no se encontro") : runtime_error(mensaje){} 
    };
}

#endif
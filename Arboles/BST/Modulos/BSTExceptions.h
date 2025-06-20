#ifndef BSTExceptions_H
#define BSTExceptions_H

#include <iostream>
#include <stdexcept>

namespace BSTExcept{
    class NoItems : public std::runtime_error{
        public:
            explicit NoItems(const std::string &mensaje = "No hay Elementos Registrados en el Arbol.") : runtime_error(mensaje){}
    };

    class ItemNotFound : public std::runtime_error{
        public:
            explicit ItemNotFound(const std::string &mensaje = "El elemento registrado no fue entontrado.") : runtime_error(mensaje){}
    };
}

#endif
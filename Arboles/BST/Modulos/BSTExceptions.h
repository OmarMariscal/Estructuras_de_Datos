#ifndef BTSExceptions_H
#define BTSExceptions_H

#include <iostream>
#include <stdexcept>

namespace EXC_BTS{
    class NoItems : public std::runtime_error{
        public:
            explicit NoItems(const std::string &mensaje = "No hay items registrados.") : runtime_error(mensaje){};
    };

    class ItemNotFoud : public std::runtime_error{
        public:
            explicit ItemNotFoud(const std::string &mensaje = "El item buscado no se encontro.") : runtime_error(mensaje){};
    };
}

#endif
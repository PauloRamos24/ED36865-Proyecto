#ifndef LISTADOBLE_H
#define LISTADOBLE_H
#include "Nodo.h"
#include <string>

// Lista doblemente enlazada de docentes. Es la duena de los docentes que guarda.
// Sus 4 operaciones: insertar, mostrar, eliminar y buscar.
class ListaDoble {
private:
    Nodo* cabeza;
    Nodo* cola;

    ListaDoble(const ListaDoble&);               // no se permite copiar
    ListaDoble& operator=(const ListaDoble&);
public:
    ListaDoble();
    ~ListaDoble();

    void insertar(Docente* docente);                   // al final; la lista pasa a ser su duena
    void mostrar();                                    // de la cabeza a la cola
    bool eliminar(const std::string& cedula);          // false si no existe
    Docente* buscar(const std::string& cedula);        // nullptr si no existe
};
#endif

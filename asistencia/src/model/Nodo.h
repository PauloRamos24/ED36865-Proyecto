#ifndef NODO_H
#define NODO_H
#include "Docente.h"

// Nodo de la lista de docentes. Es el dueno del Docente: lo borra al destruirse.
class Nodo {
private:
    Docente* docente;
    Nodo* siguiente;
    Nodo* anterior;
public:
    Nodo(Docente* docente);
    ~Nodo();

    Docente* getDocente() const;
    Nodo* getSiguiente() const;
    Nodo* getAnterior() const;
    void setSiguiente(Nodo* nodo);
    void setAnterior(Nodo* nodo);
};
#endif

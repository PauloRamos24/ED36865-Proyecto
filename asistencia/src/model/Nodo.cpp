#include "Nodo.h"

Nodo::Nodo(Docente* d) : docente(d), siguiente(nullptr), anterior(nullptr) {}
Nodo::~Nodo() { delete docente; }

Docente* Nodo::getDocente() const { return docente; }
Nodo* Nodo::getSiguiente() const { return siguiente; }
Nodo* Nodo::getAnterior() const { return anterior; }
void Nodo::setSiguiente(Nodo* nodo) { siguiente = nodo; }
void Nodo::setAnterior(Nodo* nodo) { anterior = nodo; }

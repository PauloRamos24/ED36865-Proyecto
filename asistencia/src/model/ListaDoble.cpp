#include "ListaDoble.h"
#include <iostream>

ListaDoble::ListaDoble() : cabeza(nullptr), cola(nullptr) {}

ListaDoble::~ListaDoble() {
    while (cabeza != nullptr) {
        Nodo* siguiente = cabeza->getSiguiente();
        delete cabeza;
        cabeza = siguiente;
    }
}

void ListaDoble::insertar(Docente* docente) {
    Nodo* nuevo = new Nodo(docente);
    nuevo->setAnterior(cola);
    if (cola != nullptr) cola->setSiguiente(nuevo);
    else cabeza = nuevo;
    cola = nuevo;
}

void ListaDoble::mostrar() {
    if (cabeza == nullptr) { std::cout << "No hay docentes registrados.\n"; return; }
    for (Nodo* n = cabeza; n != nullptr; n = n->getSiguiente()) {
        n->getDocente()->mostrar();
        std::cout << "-----\n";
    }
}

bool ListaDoble::eliminar(const std::string& cedula) {
    Nodo* nodo = cabeza;
    while (nodo != nullptr && nodo->getDocente()->getCedula() != cedula)
        nodo = nodo->getSiguiente();
    if (nodo == nullptr) return false;

    if (nodo->getAnterior() != nullptr) nodo->getAnterior()->setSiguiente(nodo->getSiguiente());
    else cabeza = nodo->getSiguiente();

    if (nodo->getSiguiente() != nullptr) nodo->getSiguiente()->setAnterior(nodo->getAnterior());
    else cola = nodo->getAnterior();

    delete nodo;
    return true;
}

Docente* ListaDoble::buscar(const std::string& cedula) {
    for (Nodo* n = cabeza; n != nullptr; n = n->getSiguiente())
        if (n->getDocente()->getCedula() == cedula) return n->getDocente();
    return nullptr;
}

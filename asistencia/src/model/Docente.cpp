#include "Docente.h"
#include <iostream>

Docente::Docente(const std::string& cedula, const std::string& nombre, const std::string& apellido,
                 const std::string& pass)
    : Persona(cedula, nombre, apellido), contrasenia(pass),
      primera(nullptr), ultima(nullptr), cantidad(0) {}

Docente::~Docente() {
    while (primera != nullptr) {
        Asignatura* siguiente = primera->getSiguiente();
        delete primera;
        primera = siguiente;
    }
}

std::string Docente::getContrasenia() const { return contrasenia; }
void Docente::setContrasenia(const std::string& c) { contrasenia = c; }

bool Docente::verificarContrasenia(const std::string& intento) {
    return intento == contrasenia;
}

Asignatura* Docente::getPrimeraAsignatura() const { return primera; }
int Docente::getCantidadAsignaturas() const { return cantidad; }

Asignatura* Docente::obtenerAsignatura(int posicion) {
    Asignatura* a = primera;
    for (int i = 0; i < posicion && a != nullptr; ++i) a = a->getSiguiente();
    return a;
}

bool Docente::puedeAgregarAsignatura() { return cantidad < MAX_ASIGNATURAS; }

bool Docente::tieneNrc(const std::string& nrc) {
    for (Asignatura* a = primera; a != nullptr; a = a->getSiguiente())
        if (a->getNrc() == nrc) return true;
    return false;
}

bool Docente::franjaLibre(const FranjaHoraria& franja) {
    for (Asignatura* a = primera; a != nullptr; a = a->getSiguiente())
        if (a->getFranja().seSolapaCon(franja)) return false;
    return true;
}

bool Docente::agregarAsignatura(const std::string& nrc, const std::string& nombre,
                                const FranjaHoraria& franja) {
    if (!puedeAgregarAsignatura()) return false;
    if (tieneNrc(nrc)) return false;
    if (!franjaLibre(franja)) return false;

    Asignatura* nueva = new Asignatura(nrc, nombre, franja);
    nueva->setAnterior(ultima);
    if (ultima != nullptr) ultima->setSiguiente(nueva);
    else primera = nueva;
    ultima = nueva;
    ++cantidad;
    return true;
}

void Docente::mostrarAsignaturas() {
    int numero = 1;
    for (Asignatura* a = primera; a != nullptr; a = a->getSiguiente()) {
        std::cout << "   " << numero << ". [" << a->getNrc() << "] " << a->getNombre()
                  << "  |  " << a->getFranja().aTexto() << "\n";
        ++numero;
    }
}

void Docente::mostrar() {
    std::cout << "Cedula:  " << getCedula() << "\n"
              << "Nombre:  " << nombreCompleto() << "\n"
              << "Asignaturas (" << cantidad << "/" << MAX_ASIGNATURAS << "):\n";
    mostrarAsignaturas();
}

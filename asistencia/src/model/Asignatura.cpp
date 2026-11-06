#include "Asignatura.h"

Asignatura::Asignatura(const std::string& n, const std::string& nom, const FranjaHoraria& f)
    : nrc(n), nombre(nom), franja(f), siguiente(nullptr), anterior(nullptr) {}

std::string Asignatura::getNrc() const { return nrc; }
std::string Asignatura::getNombre() const { return nombre; }
FranjaHoraria Asignatura::getFranja() const { return franja; }
Asignatura* Asignatura::getSiguiente() const { return siguiente; }
Asignatura* Asignatura::getAnterior() const { return anterior; }
void Asignatura::setNrc(const std::string& n) { nrc = n; }
void Asignatura::setNombre(const std::string& n) { nombre = n; }
void Asignatura::setFranja(const FranjaHoraria& f) { franja = f; }
void Asignatura::setSiguiente(Asignatura* a) { siguiente = a; }
void Asignatura::setAnterior(Asignatura* a) { anterior = a; }

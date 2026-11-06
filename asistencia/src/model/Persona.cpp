#include "Persona.h"

Persona::Persona(const std::string& c, const std::string& n, const std::string& a)
    : cedula(c), nombre(n), apellido(a) {}

std::string Persona::getCedula() const { return cedula; }
std::string Persona::getNombre() const { return nombre; }
std::string Persona::getApellido() const { return apellido; }
void Persona::setCedula(const std::string& c) { cedula = c; }
void Persona::setNombre(const std::string& n) { nombre = n; }
void Persona::setApellido(const std::string& a) { apellido = a; }

std::string Persona::nombreCompleto() { return nombre + " " + apellido; }

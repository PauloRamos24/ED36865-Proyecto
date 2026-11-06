#include "Fecha.h"
#include "../util/Validador.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Fecha::Fecha(int d, int m, int a) : dia(d), mes(m), ano(a) {}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAno() const { return ano; }
void Fecha::setDia(int d) { dia = d; }
void Fecha::setMes(int m) { mes = m; }
void Fecha::setAno(int a) { ano = a; }

std::string Fecha::aTexto() const {
    std::ostringstream os;
    os << std::setfill('0') << std::setw(2) << dia << '/' << std::setw(2) << mes << '/'
       << std::setw(4) << ano;
    return os.str();
}

// Algoritmo de Sakamoto
int Fecha::diaSemana() const {
    int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int y = ano;
    if (mes < 3) y -= 1;
    return (y + y / 4 - y / 100 + y / 400 + t[mes - 1] + dia) % 7;
}

// El formato se valida con regex (Validador::esFecha); aqui solo se separan los numeros.
bool Fecha::desdeTexto(const std::string& texto, Fecha& resultado) {
    if (!Validador::esFecha(texto)) return false;
    resultado = Fecha(std::stoi(texto.substr(0, 2)), std::stoi(texto.substr(3, 2)),
                      std::stoi(texto.substr(6, 4)));
    return true;
}

Fecha Fecha::hoy() {
    std::time_t t = std::time(nullptr);
    std::tm* lt = std::localtime(&t);
    return Fecha(lt->tm_mday, lt->tm_mon + 1, lt->tm_year + 1900);
}

std::string Fecha::nombreDia(int d) {
    std::string nombres[] = {"domingo", "lunes", "martes", "miercoles", "jueves", "viernes", "sabado"};
    return nombres[d % 7];
}

#include "Hora.h"
#include "../util/Validador.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Hora::Hora(int h, int m, int s) : hora(h), minuto(m), segundo(s) {}

int Hora::getHora() const { return hora; }
int Hora::getMinuto() const { return minuto; }
int Hora::getSegundo() const { return segundo; }
void Hora::setHora(int h) { hora = h; }
void Hora::setMinuto(int m) { minuto = m; }
void Hora::setSegundo(int s) { segundo = s; }

int Hora::totalSegundos() const { return hora * 3600 + minuto * 60 + segundo; }

Hora Hora::sumarSegundos(int segundos) {
    int total = totalSegundos() + segundos;
    return Hora(total / 3600, (total % 3600) / 60, total % 60);
}

std::string Hora::aTexto() const {
    std::ostringstream os;
    os << std::setfill('0') << std::setw(2) << hora << ':'
       << std::setw(2) << minuto << ':' << std::setw(2) << segundo;
    return os.str();
}

std::string Hora::aTextoCorto() const { return aTexto().substr(0, 5); }

// El formato se valida con regex (Validador::esHora); aqui solo se separan los numeros.
bool Hora::desdeTexto(const std::string& texto, Hora& resultado) {
    if (!Validador::esHora(texto)) return false;
    int s = (texto.size() == 8) ? std::stoi(texto.substr(6, 2)) : 0;
    resultado = Hora(std::stoi(texto.substr(0, 2)), std::stoi(texto.substr(3, 2)), s);
    return true;
}

Hora Hora::ahora() {
    std::time_t t = std::time(nullptr);
    std::tm* lt = std::localtime(&t);
    return Hora(lt->tm_hour, lt->tm_min, lt->tm_sec);
}

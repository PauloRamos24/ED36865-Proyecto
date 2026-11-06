#include "Validador.h"
#include <regex>

// Letra: A-Z, a-z, vocales con tilde, u con dieresis y enie (escritas en UTF-8).
#define LETRA   "(?:[A-Za-z]|\xC3[\xA1\xA9\xAD\xB3\xBA\xBC\xB1\x81\x89\x8D\x93\x9A\x9C\x91])"
// Letra o digito
#define ALFANUM "(?:[A-Za-z0-9]|\xC3[\xA1\xA9\xAD\xB3\xBA\xBC\xB1\x81\x89\x8D\x93\x9A\x9C\x91])"

namespace {

// Pieza comun de todas las reglas: el texto completo cumple el patron y no es demasiado largo.
// (el limite evita recorrer con el regex textos enormes)
bool cumple(const std::string& s, const std::regex& patron, std::size_t largoMaximo) {
    return s.size() <= largoMaximo && std::regex_match(s, patron);
}

// Un nombre o un apellido: 1 o 2 palabras separadas por UN espacio
bool esTextoDePalabras(const std::string& s) {
    static const std::regex patron("^" LETRA "{2,20}(?: " LETRA "{2,20})?$");
    return cumple(s, patron, 60);
}

bool provinciaValida(const std::string& cedula) {
    int provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');
    return (provincia >= 1 && provincia <= 24) || provincia == 30;
}

bool digitoVerificadorCorrecto(const std::string& cedula) {
    int suma = 0;
    for (int i = 0; i < 9; ++i) {
        int d = cedula[i] - '0';
        if (i % 2 == 0) { d *= 2; if (d > 9) d -= 9; }
        suma += d;
    }
    return (10 - suma % 10) % 10 == cedula[9] - '0';
}

int diasDelMes(int mes, int ano) {
    static const int dias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool bisiesto = (ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0;
    return (mes == 2 && bisiesto) ? 29 : dias[mes - 1];
}

}  // namespace

bool Validador::esEnteroEnRango(const std::string& s, int minimo, int maximo) {
    static const std::regex patron("^[0-9]{1,9}$");
    if (!cumple(s, patron, 9)) return false;
    int valor = std::stoi(s);
    return valor >= minimo && valor <= maximo;
}

bool Validador::esSiNo(const std::string& s) {
    static const std::regex patron("^[sSnN]$");
    return cumple(s, patron, 1);
}

bool Validador::esCedula(const std::string& s) {
    static const std::regex patron("^[0-9]{10}$");
    if (!cumple(s, patron, 10)) return false;
    return provinciaValida(s) && s[2] - '0' < 6 && digitoVerificadorCorrecto(s);
}

bool Validador::esNombre(const std::string& s) { return esTextoDePalabras(s); }

bool Validador::esApellido(const std::string& s) { return esTextoDePalabras(s); }

bool Validador::esNrc(const std::string& s) {
    static const std::regex patron("^[0-9]{4,6}$");
    return cumple(s, patron, 6);
}

bool Validador::esNombreAsignatura(const std::string& s) {
    static const std::regex patron("^" ALFANUM "+(?: " ALFANUM "+)*$");
    static const std::regex tieneLetra("[A-Za-z]|\xC3");
    return cumple(s, patron, 50) && std::regex_search(s, tieneLetra);
}

bool Validador::esContrasenia(const std::string& s) {
    // caracteres ASCII visibles, sin espacio y sin '|'
    static const std::regex patron("^[\\x21-\\x7B\\x7D-\\x7E]{6,20}$");
    return cumple(s, patron, 20);
}

bool Validador::esHora(const std::string& s) {
    static const std::regex patron("^([01][0-9]|2[0-3]):[0-5][0-9](:[0-5][0-9])?$");
    return cumple(s, patron, 8);
}

bool Validador::esFecha(const std::string& s) {
    static const std::regex patron("^[0-9]{2}/[0-9]{2}/[0-9]{4}$");
    if (!cumple(s, patron, 10)) return false;
    int dia = std::stoi(s.substr(0, 2));
    int mes = std::stoi(s.substr(3, 2));
    int ano = std::stoi(s.substr(6, 4));
    if (ano < 1900 || ano > 2100 || mes < 1 || mes > 12) return false;
    return dia >= 1 && dia <= diasDelMes(mes, ano);
}

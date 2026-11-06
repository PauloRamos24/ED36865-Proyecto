#ifndef TEXTO_H
#define TEXTO_H
#include <string>

// Funciones para trabajar con campos separados por un caracter.
// Ejemplo: en "a|b|c" hay 3 campos y el campo 1 es "b".

inline std::string recortar(const std::string& s) {
    std::size_t inicio = s.find_first_not_of(" \t\r\n");
    if (inicio == std::string::npos) return "";
    std::size_t fin = s.find_last_not_of(" \t\r\n");
    return s.substr(inicio, fin - inicio + 1);
}

inline int contarCampos(const std::string& s, char sep = '|') {
    int n = 1;
    for (std::size_t i = 0; i < s.size(); ++i)
        if (s[i] == sep) ++n;
    return n;
}

inline std::string campo(const std::string& s, int indice, char sep = '|') {
    int actual = 0;
    std::string resultado;
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (s[i] == sep) {
            if (actual == indice) return resultado;
            ++actual;
            resultado = "";
        } else {
            resultado += s[i];
        }
    }
    if (actual == indice) return resultado;
    return "";
}

// Devuelve la cadena con el campo "indice" cambiado por "nuevo".
inline std::string reemplazarCampo(const std::string& s, int indice,
                                   const std::string& nuevo, char sep = '|') {
    std::string salida;
    int total = contarCampos(s, sep);
    for (int i = 0; i < total; ++i) {
        if (i > 0) salida += sep;
        if (i == indice) salida += nuevo;
        else salida += campo(s, i, sep);
    }
    return salida;
}
#endif

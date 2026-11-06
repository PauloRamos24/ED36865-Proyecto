#ifndef VALIDADOR_H
#define VALIDADOR_H
#include <string>

// Todas las validaciones de entrada usan expresiones regulares (regex_match: el texto
// completo debe cumplir el patron). No se recorta nada: un espacio al inicio, al final
// o doble hace que el dato sea invalido, y un texto vacio nunca es valido.
class Validador {
public:
    static bool esEnteroEnRango(const std::string& s, int minimo, int maximo);
    static bool esSiNo(const std::string& s);                // s, S, n, N
    static bool esCedula(const std::string& s);              // 10 digitos + digito verificador
    static bool esNombre(const std::string& s);              // 1 o 2 palabras, solo letras (2 a 20 c/u)
    static bool esApellido(const std::string& s);            // igual que el nombre
    static bool esNrc(const std::string& s);                 // 4 a 6 digitos
    static bool esNombreAsignatura(const std::string& s);    // palabras separadas por UN espacio
    static bool esContrasenia(const std::string& s);         // 6 a 20 caracteres, sin espacios ni '|'
    static bool esHora(const std::string& s);                // HH:MM o HH:MM:SS (24 horas)
    static bool esFecha(const std::string& s);               // DD/MM/AAAA (fecha real, ano 1900-2100)
};
#endif

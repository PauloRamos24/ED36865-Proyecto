#ifndef CONSOLA_H
#define CONSOLA_H
#include <string>

// Teclas de control de la consola (no son validaciones de datos).
class Consola {
public:
    // Ctrl+C: se llama una vez en main; ya no cierra el programa y muestra un aviso.
    static void bloquearCtrlC();
    static bool huboCtrlC();                         // true si hubo Ctrl+C (y limpia la marca)
    // Ctrl+Z: escrito dentro de la linea llega como el caracter 0x1A.
    static bool contieneCtrlZ(const std::string& s);
};
#endif

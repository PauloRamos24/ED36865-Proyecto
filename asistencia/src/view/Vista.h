#ifndef VISTA_H
#define VISTA_H
#include <string>

// La Vista solo muestra informacion y lee del teclado. No tiene reglas de negocio.
class Vista {
public:
    typedef bool (*Validacion)(const std::string&);

    void mostrarMenu();
    void titulo(const std::string& texto);
    void mensaje(const std::string& texto);
    void exito(const std::string& texto);
    void error(const std::string& texto);

    // Lee una linea TAL CUAL se escribio: no se recortan espacios, para que
    // la validacion (regex) detecte los espacios de sobra.
    std::string pedirLibre(const std::string& mensaje);
    // Repite la pregunta hasta que la validacion (regex) devuelva true
    std::string pedir(const std::string& mensaje, Validacion valida, const std::string& mensajeError);
    int pedirEntero(const std::string& mensaje, int minimo, int maximo);
    bool confirmar(const std::string& mensaje);

    void mostrarDias();
    void mostrarFranjas();
};
#endif

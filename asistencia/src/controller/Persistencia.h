#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H
#include "../model/ListaDoble.h"
#include "../model/RegistroAsistencia.h"
#include <string>

// Todo se guarda en archivos de texto: una linea por registro, campos separados por '|'.
//
// docentes.txt : cedula|nombre|apellido|contrasenia|nrc|asignatura|grupo|franja|nrc|...
//                (de 1 a 3 grupos "nrc|asignatura|grupo de dias|numero de franja")
// registros.txt: cedula|nombre|nrc|asignatura|fecha|franja|entrada|salida|estado
class Persistencia {
private:
    std::string archivoDocentes;
    std::string archivoRegistros;
public:
    Persistencia();

    void cargarDocentes(ListaDoble& lista);
    bool agregarDocente(Docente& d);                     // agrega su linea al final del archivo
    bool eliminarDocente(const std::string& cedula);     // reescribe el archivo sin esa linea

    bool agregarRegistro(RegistroAsistencia& r);
    // Busca el registro de ese docente, asignatura y fecha; devuelve su linea completa
    bool buscarRegistro(const std::string& cedula, const std::string& nrc,
                        const std::string& fecha, std::string& linea);
    // Escribe la salida y pasa el estado a "Completo". false si no hay registro pendiente.
    bool registrarSalida(const std::string& cedula, const std::string& nrc,
                         const std::string& fecha, const std::string& hora);
};
#endif

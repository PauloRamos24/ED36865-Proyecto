#ifndef DOCENTE_H
#define DOCENTE_H
#include "Persona.h"
#include "Asignatura.h"
#include "FranjaHoraria.h"
#include <string>

// Un docente tiene de 1 a 3 asignaturas, cada una con su franja de 2 horas.
// Las asignaturas forman una lista doblemente enlazada que maneja el propio Docente
// (cada Asignatura tiene siguiente / anterior).
// Un Docente no se copia: se crea con "new" y se usa por puntero.
class Docente : public Persona {
public:
    static const int MAX_ASIGNATURAS = 3;
private:
    std::string contrasenia;
    Asignatura* primera;
    Asignatura* ultima;
    int cantidad;

    Docente(const Docente&);                 // no se permite copiar
    Docente& operator=(const Docente&);
public:
    Docente(const std::string& cedula, const std::string& nombre, const std::string& apellido,
            const std::string& contrasenia);
    ~Docente();

    std::string getContrasenia() const;
    void setContrasenia(const std::string& contrasenia);
    bool verificarContrasenia(const std::string& intento);

    Asignatura* getPrimeraAsignatura() const;
    int getCantidadAsignaturas() const;
    Asignatura* obtenerAsignatura(int posicion);           // posicion desde 0
    bool puedeAgregarAsignatura();                         // menos de 3
    bool tieneNrc(const std::string& nrc);
    bool franjaLibre(const FranjaHoraria& franja);         // no se cruza con ninguna
    // false si ya tiene 3, si el NRC esta repetido o si la franja se cruza con otra
    bool agregarAsignatura(const std::string& nrc, const std::string& nombre,
                           const FranjaHoraria& franja);

    void mostrar();                                        // cedula, nombre y asignaturas
    void mostrarAsignaturas();                             // lista numerada desde 1
};
#endif

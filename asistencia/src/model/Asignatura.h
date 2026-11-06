#ifndef ASIGNATURA_H
#define ASIGNATURA_H
#include "FranjaHoraria.h"
#include <string>

// Una asignatura con su franja de 2 horas. Tambien guarda los enlaces
// (siguiente / anterior) para formar la lista doble de asignaturas de un docente.
class Asignatura {
private:
    std::string nrc;
    std::string nombre;
    FranjaHoraria franja;
    Asignatura* siguiente;
    Asignatura* anterior;
public:
    Asignatura(const std::string& nrc, const std::string& nombre, const FranjaHoraria& franja);

    std::string getNrc() const;
    std::string getNombre() const;
    FranjaHoraria getFranja() const;
    Asignatura* getSiguiente() const;
    Asignatura* getAnterior() const;
    void setNrc(const std::string& nrc);
    void setNombre(const std::string& nombre);
    void setFranja(const FranjaHoraria& franja);
    void setSiguiente(Asignatura* a);
    void setAnterior(Asignatura* a);
};
#endif

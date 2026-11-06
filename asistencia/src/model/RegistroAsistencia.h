#ifndef REGISTROASISTENCIA_H
#define REGISTROASISTENCIA_H
#include "Docente.h"
#include "Asignatura.h"
#include "FranjaHoraria.h"
#include "Fecha.h"
#include "Hora.h"
#include <string>

// Registro de asistencia de un docente en una asignatura (fecha y hora del sistema).
// estado: "En curso" (solo tiene entrada) o "Completo" (ya tiene salida).
class RegistroAsistencia {
public:
    static const char* const EN_CURSO;
    static const char* const COMPLETO;
private:
    Docente* docente;
    Asignatura* asignatura;
    FranjaHoraria franja;
    Fecha fecha;
    Hora horaEntrada;
    Hora horaSalida;
    std::string estado;
public:
    RegistroAsistencia(Docente* docente, Asignatura* asignatura, const Fecha& fecha,
                       const Hora& entrada);

    Docente* getDocente() const;
    Asignatura* getAsignatura() const;
    FranjaHoraria getFranja() const;
    Fecha getFecha() const;
    Hora getHoraEntrada() const;
    Hora getHoraSalida() const;
    std::string getEstado() const;
    void setFecha(const Fecha& fecha);
    void setHoraEntrada(const Hora& hora);
    void setHoraSalida(const Hora& hora);          // tambien pasa el estado a "Completo"
    void setEstado(const std::string& estado);

    // cedula|nombre|nrc|asignatura|fecha|franja|entrada|salida(-)|estado
    std::string aLinea();
};
#endif

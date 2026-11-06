#include "RegistroAsistencia.h"

const char* const RegistroAsistencia::EN_CURSO = "En curso";
const char* const RegistroAsistencia::COMPLETO = "Completo";

RegistroAsistencia::RegistroAsistencia(Docente* d, Asignatura* a, const Fecha& fe,
                                       const Hora& entrada)
    : docente(d), asignatura(a), franja(a->getFranja()), fecha(fe), horaEntrada(entrada),
      horaSalida(0, 0, 0), estado(EN_CURSO) {}

Docente* RegistroAsistencia::getDocente() const { return docente; }
Asignatura* RegistroAsistencia::getAsignatura() const { return asignatura; }
FranjaHoraria RegistroAsistencia::getFranja() const { return franja; }
Fecha RegistroAsistencia::getFecha() const { return fecha; }
Hora RegistroAsistencia::getHoraEntrada() const { return horaEntrada; }
Hora RegistroAsistencia::getHoraSalida() const { return horaSalida; }
std::string RegistroAsistencia::getEstado() const { return estado; }
void RegistroAsistencia::setFecha(const Fecha& f) { fecha = f; }
void RegistroAsistencia::setHoraEntrada(const Hora& h) { horaEntrada = h; }
void RegistroAsistencia::setEstado(const std::string& e) { estado = e; }

void RegistroAsistencia::setHoraSalida(const Hora& h) {
    horaSalida = h;
    estado = COMPLETO;
}

std::string RegistroAsistencia::aLinea() {
    std::string salida = (estado == COMPLETO) ? horaSalida.aTexto() : "-";
    return docente->getCedula() + "|" + docente->nombreCompleto() + "|" + asignatura->getNrc() + "|" +
           asignatura->getNombre() + "|" + fecha.aTexto() + "|" + franja.aTexto() + "|" +
           horaEntrada.aTexto() + "|" + salida + "|" + estado;
}

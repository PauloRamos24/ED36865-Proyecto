#include "FranjaHoraria.h"

FranjaHoraria::FranjaHoraria(int g, const Hora& inicio, const Hora& fin)
    : grupoDias(g), horaInicio(inicio), horaFin(fin) {}

int FranjaHoraria::getGrupoDias() const { return grupoDias; }
Hora FranjaHoraria::getHoraInicio() const { return horaInicio; }
Hora FranjaHoraria::getHoraFin() const { return horaFin; }
void FranjaHoraria::setGrupoDias(int g) { grupoDias = g; }
void FranjaHoraria::setHoraInicio(const Hora& h) { horaInicio = h; }
void FranjaHoraria::setHoraFin(const Hora& h) { horaFin = h; }

int FranjaHoraria::numero() const {
    return (horaInicio.getHora() - HORA_INICIAL) / DURACION_HORAS + 1;
}

std::string FranjaHoraria::nombreDias() const { return nombreGrupo(grupoDias); }
std::string FranjaHoraria::rango() const {
    return horaInicio.aTextoCorto() + " - " + horaFin.aTextoCorto();
}
std::string FranjaHoraria::aTexto() const { return nombreDias() + " " + rango(); }

bool FranjaHoraria::incluyeDia(int diaSemana) {
    if (grupoDias == 1) return diaSemana == 1 || diaSemana == 3 || diaSemana == 5;
    return diaSemana == 2 || diaSemana == 4;
}

// Chocan solo si comparten grupo de dias y sus horas se traslapan.
bool FranjaHoraria::seSolapaCon(const FranjaHoraria& otra) {
    return grupoDias == otra.grupoDias &&
           horaInicio.totalSegundos() < otra.horaFin.totalSegundos() &&
           otra.horaInicio.totalSegundos() < horaFin.totalSegundos();
}

// Se compara por minutos: de 07:00 hasta 07:10 inclusive (07:10:59 todavia vale).
bool FranjaHoraria::entradaPermitida(const Hora& hora) {
    int minuto = hora.totalSegundos() / 60;
    int inicio = horaInicio.totalSegundos() / 60;
    return minuto >= inicio && minuto <= inicio + TOLERANCIA_MINUTOS;
}

// Hasta el ultimo minuto de la franja (08:59:59 todavia vale; 09:00 ya no).
bool FranjaHoraria::salidaPermitida(const Hora& hora) {
    int t = hora.totalSegundos();
    return t >= horaInicio.totalSegundos() && t < horaFin.totalSegundos();
}

FranjaHoraria FranjaHoraria::predefinida(int grupo, int numero) {
    int inicio = HORA_INICIAL + (numero - 1) * DURACION_HORAS;
    return FranjaHoraria(grupo, Hora(inicio, 0, 0), Hora(inicio + DURACION_HORAS, 0, 0));
}

std::string FranjaHoraria::nombreGrupo(int grupo) {
    if (grupo == 1) return "Lunes-Miercoles-Viernes";
    return "Martes-Jueves";
}

std::string FranjaHoraria::rangoDeFranja(int numero) {
    return predefinida(1, numero).rango();
}

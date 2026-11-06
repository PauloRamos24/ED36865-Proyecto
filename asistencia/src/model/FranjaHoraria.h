#ifndef FRANJAHORARIA_H
#define FRANJAHORARIA_H
#include "Hora.h"
#include <string>

// Las franjas ya estan definidas (datos fijos): de 07:00 a 19:00, de 2 horas cada una.
//   1: 07-09   2: 09-11   3: 11-13   4: 13-15   5: 15-17   6: 17-19
// y se dictan en uno de dos grupos de dias:
//   1 = Lunes-Miercoles-Viernes     2 = Martes-Jueves
// No se escriben a mano: se obtienen con FranjaHoraria::predefinida(grupo, numero).
class FranjaHoraria {
private:
    int grupoDias;
    Hora horaInicio;
    Hora horaFin;
public:
    static const int HORA_INICIAL = 7;           // 07:00
    static const int DURACION_HORAS = 2;
    static const int CANTIDAD = 6;               // hasta las 19:00
    static const int CANTIDAD_GRUPOS = 2;
    static const int TOLERANCIA_MINUTOS = 10;

    FranjaHoraria(int grupoDias = 1, const Hora& inicio = Hora(7, 0, 0),
                  const Hora& fin = Hora(9, 0, 0));

    int getGrupoDias() const;
    Hora getHoraInicio() const;
    Hora getHoraFin() const;
    void setGrupoDias(int grupo);
    void setHoraInicio(const Hora& hora);
    void setHoraFin(const Hora& hora);

    int numero() const;                              // 1 a 6, segun la hora de inicio
    std::string nombreDias() const;                  // "Lunes-Miercoles-Viernes"
    std::string rango() const;                       // "07:00 - 09:00"
    std::string aTexto() const;                      // "Lunes-Miercoles-Viernes 07:00 - 09:00"
    bool incluyeDia(int diaSemana);                  // 0 = domingo ... 6 = sabado
    bool seSolapaCon(const FranjaHoraria& otra);

    // La entrada se registra desde el inicio hasta 10 minutos despues (ej. 07:00 a 07:10).
    bool entradaPermitida(const Hora& hora);
    // La salida se registra hasta el ultimo minuto de la franja (ej. hasta 08:59).
    bool salidaPermitida(const Hora& hora);

    static FranjaHoraria predefinida(int grupo, int numero);
    static std::string nombreGrupo(int grupo);
    static std::string rangoDeFranja(int numero);
};
#endif

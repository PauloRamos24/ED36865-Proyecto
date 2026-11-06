#ifndef HORA_H
#define HORA_H
#include <string>

class Hora {
private:
    int hora;
    int minuto;
    int segundo;
public:
    Hora(int hora = 0, int minuto = 0, int segundo = 0);

    int getHora() const;
    int getMinuto() const;
    int getSegundo() const;
    void setHora(int hora);
    void setMinuto(int minuto);
    void setSegundo(int segundo);

    int totalSegundos() const;                       // segundos desde las 00:00:00
    Hora sumarSegundos(int segundos);                // admite negativos
    std::string aTexto() const;                      // "HH:MM:SS"
    std::string aTextoCorto() const;                 // "HH:MM"

    static bool desdeTexto(const std::string& texto, Hora& resultado);  // "HH:MM" o "HH:MM:SS"
    static Hora ahora();                                                // hora del sistema
};
#endif

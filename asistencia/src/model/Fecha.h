#ifndef FECHA_H
#define FECHA_H
#include <string>

class Fecha {
private:
    int dia;
    int mes;
    int ano;
public:
    Fecha(int dia = 1, int mes = 1, int ano = 2000);

    int getDia() const;
    int getMes() const;
    int getAno() const;
    void setDia(int dia);
    void setMes(int mes);
    void setAno(int ano);

    std::string aTexto() const;                            // "DD/MM/AAAA"
    int diaSemana() const;                                 // 0 = domingo ... 6 = sabado

    static bool desdeTexto(const std::string& texto, Fecha& resultado);  // "DD/MM/AAAA"
    static Fecha hoy();                                    // fecha del sistema
    static std::string nombreDia(int diaSemana);
};
#endif

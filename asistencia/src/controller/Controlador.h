#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include "../model/ListaDoble.h"
#include "../view/Vista.h"
#include "Persistencia.h"
#include <string>

class Controlador {
private:
    ListaDoble docentes;
    Persistencia persistencia;
    Vista vista;

    std::string pedirCedula();
    FranjaHoraria pedirFranja(Docente* d);
    void pedirAsignatura(Docente* d);
    Docente* autenticar();
    Asignatura* elegirAsignatura(Docente* d);
    void pedirFechaHora(Fecha& fecha, Hora& hora);

    void registrarDocente();
    void listarDocentes();
    void buscarDocente();
    void eliminarDocente();
    void registrarEntrada();
    void registrarSalida();
    void registrarAsistencia();          // pregunta si es entrada o salida

public:
    Controlador();
    void ejecutar();
};
#endif

#include "Persistencia.h"
#include "../util/Texto.h"
#include "../util/Validador.h"
#include <cstdio>
#include <fstream>

// Campos fijos de un docente: cedula, nombre, apellido, contrasenia
static const int CAMPOS_DOCENTE = 4;
// Campos de cada asignatura: nrc, nombre, grupo de dias, numero de franja
static const int CAMPOS_ASIGNATURA = 4;

// Posiciones de los campos en la linea de un registro
static const int REG_CEDULA = 0, REG_NRC = 2, REG_FECHA = 4, REG_SALIDA = 7, REG_ESTADO = 8;

Persistencia::Persistencia() : archivoDocentes("docentes.txt"), archivoRegistros("registros.txt") {}

// ------------------------------ docentes ------------------------------

void Persistencia::cargarDocentes(ListaDoble& lista) {
    std::ifstream in(archivoDocentes.c_str());
    if (!in) return;                         // primera ejecucion: el archivo aun no existe

    std::string linea;
    while (std::getline(in, linea)) {
        linea = recortar(linea);
        if (linea.empty()) continue;

        int total = contarCampos(linea);
        int extras = total - CAMPOS_DOCENTE;
        if (extras < CAMPOS_ASIGNATURA || extras % CAMPOS_ASIGNATURA != 0) continue;
        if (extras / CAMPOS_ASIGNATURA > Docente::MAX_ASIGNATURAS) continue;

        // Los datos guardados tambien se verifican con las mismas reglas de entrada
        std::string cedula = campo(linea, 0), nombre = campo(linea, 1), apellido = campo(linea, 2);
        std::string pass = campo(linea, 3);
        if (!Validador::esCedula(cedula) || !Validador::esNombre(nombre) ||
            !Validador::esApellido(apellido) || !Validador::esContrasenia(pass))
            continue;
        if (lista.buscar(cedula) != nullptr) continue;     // cedula repetida

        Docente* d = new Docente(cedula, nombre, apellido, pass);
        bool correcto = true;
        for (int i = CAMPOS_DOCENTE; i < total && correcto; i += CAMPOS_ASIGNATURA) {
            std::string nrc = campo(linea, i), nom = campo(linea, i + 1);
            std::string grupo = campo(linea, i + 2), franja = campo(linea, i + 3);
            if (!Validador::esNrc(nrc) || !Validador::esNombreAsignatura(nom) ||
                !Validador::esEnteroEnRango(grupo, 1, FranjaHoraria::CANTIDAD_GRUPOS) ||
                !Validador::esEnteroEnRango(franja, 1, FranjaHoraria::CANTIDAD))
                correcto = false;
            else
                correcto = d->agregarAsignatura(
                    nrc, nom, FranjaHoraria::predefinida(std::stoi(grupo), std::stoi(franja)));
        }
        if (correcto) lista.insertar(d);
        else delete d;                       // linea corrupta: se ignora
    }
}

bool Persistencia::agregarDocente(Docente& d) {
    std::ofstream out(archivoDocentes.c_str(), std::ios::app);
    if (!out) return false;
    out << d.getCedula() << '|' << d.getNombre() << '|' << d.getApellido() << '|'
        << d.getContrasenia();
    for (Asignatura* a = d.getPrimeraAsignatura(); a != nullptr; a = a->getSiguiente())
        out << '|' << a->getNrc() << '|' << a->getNombre() << '|'
            << a->getFranja().getGrupoDias() << '|' << a->getFranja().numero();
    out << '\n';
    return static_cast<bool>(out);
}

bool Persistencia::eliminarDocente(const std::string& cedula) {
    std::ifstream in(archivoDocentes.c_str());
    if (!in) return false;
    std::string temporal = archivoDocentes + ".tmp";
    std::ofstream out(temporal.c_str());
    if (!out) return false;

    std::string linea;
    while (std::getline(in, linea)) {
        linea = recortar(linea);
        if (linea.empty() || campo(linea, 0) == cedula) continue;
        out << linea << '\n';
    }
    in.close();
    out.close();

    std::remove(archivoDocentes.c_str());
    return std::rename(temporal.c_str(), archivoDocentes.c_str()) == 0;
}

// ------------------------------ registros ------------------------------

bool Persistencia::agregarRegistro(RegistroAsistencia& r) {
    std::ofstream out(archivoRegistros.c_str(), std::ios::app);
    if (!out) return false;
    out << r.aLinea() << '\n';
    return static_cast<bool>(out);
}

static bool coincide(const std::string& linea, const std::string& cedula,
                     const std::string& nrc, const std::string& fecha) {
    return campo(linea, REG_CEDULA) == cedula && campo(linea, REG_NRC) == nrc &&
           campo(linea, REG_FECHA) == fecha;
}

bool Persistencia::buscarRegistro(const std::string& cedula, const std::string& nrc,
                                  const std::string& fecha, std::string& linea) {
    std::ifstream in(archivoRegistros.c_str());
    std::string actual;
    while (std::getline(in, actual)) {
        actual = recortar(actual);
        if (coincide(actual, cedula, nrc, fecha)) { linea = actual; return true; }
    }
    return false;
}

bool Persistencia::registrarSalida(const std::string& cedula, const std::string& nrc,
                                   const std::string& fecha, const std::string& hora) {
    std::ifstream in(archivoRegistros.c_str());
    if (!in) return false;
    std::string temporal = archivoRegistros + ".tmp";
    std::ofstream out(temporal.c_str());
    if (!out) return false;

    bool encontrado = false;
    std::string linea;
    while (std::getline(in, linea)) {
        linea = recortar(linea);
        if (linea.empty()) continue;
        if (!encontrado && coincide(linea, cedula, nrc, fecha) && campo(linea, REG_SALIDA) == "-") {
            linea = reemplazarCampo(linea, REG_SALIDA, hora);
            linea = reemplazarCampo(linea, REG_ESTADO, RegistroAsistencia::COMPLETO);
            encontrado = true;
        }
        out << linea << '\n';
    }
    in.close();
    out.close();

    if (encontrado) {
        std::remove(archivoRegistros.c_str());
        std::rename(temporal.c_str(), archivoRegistros.c_str());
    } else {
        std::remove(temporal.c_str());
    }
    return encontrado;
}

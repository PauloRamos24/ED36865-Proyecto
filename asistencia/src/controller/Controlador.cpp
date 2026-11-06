#include "Controlador.h"
#include "../util/Texto.h"
#include "../util/Validador.h"

Controlador::Controlador() { persistencia.cargarDocentes(docentes); }

// Para poder hacer pruebas, la fecha y la hora se escriben por teclado (no se usa el reloj).
void Controlador::pedirFechaHora(Fecha& fecha, Hora& hora) {
    std::string f = vista.pedir("Fecha (DD/MM/AAAA): ", Validador::esFecha,
                                "Fecha invalida. Use DD/MM/AAAA con una fecha real, ej. 05/11/2026.");
    std::string h = vista.pedir("Hora (HH:MM o HH:MM:SS, 24 horas): ", Validador::esHora,
                                "Hora invalida. Use HH:MM o HH:MM:SS, ej. 07:05 o 07:05:30.");
    Fecha::desdeTexto(f, fecha);
    Hora::desdeTexto(h, hora);
}

std::string Controlador::pedirCedula() {
    return vista.pedir("Cedula (10 digitos): ", Validador::esCedula,
                       "Cedula invalida: solo 10 digitos, sin espacios, y debe ser una cedula valida.");
}

// Las franjas ya estan definidas (07:00 a 19:00, de 2 horas): solo se elige el grupo
// de dias y una de las 6 franjas.
FranjaHoraria Controlador::pedirFranja(Docente* d) {
    while (true) {
        vista.mostrarDias();
        int grupo = vista.pedirEntero("Elija los dias: ", 1, FranjaHoraria::CANTIDAD_GRUPOS);
        vista.mostrarFranjas();
        int numero = vista.pedirEntero("Elija la franja: ", 1, FranjaHoraria::CANTIDAD);

        FranjaHoraria franja = FranjaHoraria::predefinida(grupo, numero);
        if (d->franjaLibre(franja)) {
            vista.mensaje("Franja: " + franja.aTexto());
            return franja;
        }
        vista.error("Esa franja se cruza con otra ya registrada de este docente.");
    }
}

// Pide NRC, nombre y franja de una asignatura y la agrega al docente.
void Controlador::pedirAsignatura(Docente* d) {
    const std::string msgNrc = "NRC invalido: solo numeros, entre 4 y 6 digitos, sin espacios.";
    std::string nrc = vista.pedir("NRC (4 a 6 digitos): ", Validador::esNrc, msgNrc);
    while (d->tieneNrc(nrc)) {
        vista.error("Ese NRC ya esta asignado a este docente.");
        nrc = vista.pedir("NRC (4 a 6 digitos): ", Validador::esNrc, msgNrc);
    }
    std::string nombre = vista.pedir("Nombre de la asignatura: ", Validador::esNombreAsignatura,
        "Nombre invalido: letras y numeros separados por un solo espacio (maximo 50), "
        "sin espacios al inicio ni al final.");
    FranjaHoraria franja = pedirFranja(d);
    d->agregarAsignatura(nrc, nombre, franja);
}

Docente* Controlador::autenticar() {
    std::string cedula = pedirCedula();
    std::string pass = vista.pedirLibre("Contrasenia: ");
    Docente* d = docentes.buscar(cedula);
    if (d == nullptr || !d->verificarContrasenia(pass)) {
        vista.error("Cedula o contrasenia incorrectas.");
        return nullptr;
    }
    return d;
}

Asignatura* Controlador::elegirAsignatura(Docente* d) {
    vista.mensaje("Sus asignaturas:");
    d->mostrarAsignaturas();
    int numero = vista.pedirEntero("Elija la asignatura: ", 1, d->getCantidadAsignaturas());
    return d->obtenerAsignatura(numero - 1);
}

// ------------------------------ opciones del menu ------------------------------

void Controlador::registrarDocente() {
    vista.titulo("REGISTRAR DOCENTE");
    std::string cedula = pedirCedula();
    if (docentes.buscar(cedula) != nullptr) {
        vista.error("Ya existe un docente con esa cedula.");
        return;
    }
    std::string nombre = vista.pedir("Nombre (1 o 2 nombres, ej. Juan Carlos): ", Validador::esNombre,
        "Nombre invalido: 1 o 2 palabras con solo letras (2 a 20 cada una), separadas por un "
        "solo espacio y sin espacios al inicio ni al final.");
    std::string apellido = vista.pedir("Apellido (1 o 2 apellidos, ej. Perez Delgado): ",
        Validador::esApellido,
        "Apellido invalido: 1 o 2 palabras con solo letras (2 a 20 cada una), separadas por un "
        "solo espacio y sin espacios al inicio ni al final.");
    std::string pass = vista.pedir("Contrasenia (6 a 20 caracteres, sin espacios): ",
                                   Validador::esContrasenia,
                                   "Contrasenia invalida: 6 a 20 caracteres visibles, sin espacios ni '|'.");

    Docente* d = new Docente(cedula, nombre, apellido, pass);
    vista.mensaje("Registre su primera asignatura (maximo 3, cada una con su franja de 2 horas):");
    pedirAsignatura(d);
    while (d->puedeAgregarAsignatura() && vista.confirmar("Agregar otra asignatura?"))
        pedirAsignatura(d);
    if (!d->puedeAgregarAsignatura()) vista.mensaje("Se alcanzo el maximo de 3 franjas horarias.");

    docentes.insertar(d);
    if (!persistencia.agregarDocente(*d)) vista.error("No se pudo guardar el docente en disco.");
    else vista.exito("Docente registrado.");
}

void Controlador::listarDocentes() {
    vista.titulo("DOCENTES");
    docentes.mostrar();
}

void Controlador::buscarDocente() {
    vista.titulo("BUSCAR DOCENTE");
    Docente* d = docentes.buscar(pedirCedula());
    if (d == nullptr) { vista.error("No se encontro un docente con esa cedula."); return; }
    d->mostrar();
}

void Controlador::eliminarDocente() {
    vista.titulo("ELIMINAR DOCENTE");
    std::string cedula = pedirCedula();
    Docente* d = docentes.buscar(cedula);
    if (d == nullptr) { vista.error("No se encontro un docente con esa cedula."); return; }
    d->mostrar();
    if (!vista.confirmar("Eliminar este docente? (sus registros de asistencia se conservan)")) {
        vista.mensaje("Operacion cancelada.");
        return;
    }
    docentes.eliminar(cedula);
    if (!persistencia.eliminarDocente(cedula)) vista.error("No se pudo actualizar el archivo de docentes.");
    else vista.exito("Docente eliminado.");
}

// La fecha y la hora se ingresan por teclado. La entrada solo se acepta desde el inicio de la
// franja hasta 10 minutos despues (ej. franja 07:00: de 07:00 a 07:10).
void Controlador::registrarEntrada() {
    vista.titulo("REGISTRAR ENTRADA");
    Docente* d = autenticar();
    if (d == nullptr) return;
    Asignatura* asignatura = elegirAsignatura(d);
    FranjaHoraria franja = asignatura->getFranja();

    Fecha fecha;
    Hora hora;
    pedirFechaHora(fecha, hora);

    if (!franja.incluyeDia(fecha.diaSemana())) {
        vista.error("Esta asignatura se dicta " + franja.nombreDias() + ", y la fecha ingresada es " +
                    Fecha::nombreDia(fecha.diaSemana()) + ".");
        return;
    }
    if (!franja.entradaPermitida(hora)) {
        Hora limite = franja.getHoraInicio();
        limite = limite.sumarSegundos(FranjaHoraria::TOLERANCIA_MINUTOS * 60);
        vista.error("La entrada solo se puede registrar entre " + franja.getHoraInicio().aTextoCorto() +
                    " y " + limite.aTextoCorto() + ". Hora ingresada: " + hora.aTexto() + ".");
        return;
    }
    std::string existente;
    if (persistencia.buscarRegistro(d->getCedula(), asignatura->getNrc(), fecha.aTexto(), existente)) {
        vista.error("Ya registro la entrada de esta asignatura en esa fecha.");
        return;
    }
    RegistroAsistencia registro(d, asignatura, fecha, hora);
    if (!persistencia.agregarRegistro(registro)) {
        vista.error("No se pudo guardar el registro.");
        return;
    }
    vista.exito("Entrada registrada el " + fecha.aTexto() + " a las " + hora.aTexto() + ".");
}

// La salida se acepta hasta el ultimo minuto de la franja (ej. franja 07:00-09:00: hasta 08:59).
void Controlador::registrarSalida() {
    vista.titulo("REGISTRAR SALIDA");
    Docente* d = autenticar();
    if (d == nullptr) return;
    Asignatura* asignatura = elegirAsignatura(d);
    FranjaHoraria franja = asignatura->getFranja();

    Fecha fecha;
    Hora hora;
    pedirFechaHora(fecha, hora);
    std::string cedula = d->getCedula();
    std::string nrc = asignatura->getNrc();

    std::string linea;
    if (!persistencia.buscarRegistro(cedula, nrc, fecha.aTexto(), linea)) {
        vista.error("Primero debe registrar la entrada de esta asignatura en esa fecha.");
        return;
    }
    if (campo(linea, 7) != "-") {
        vista.error("La salida de esta asignatura ya fue registrada en esa fecha.");
        return;
    }
    Hora entrada;
    Hora::desdeTexto(campo(linea, 6), entrada);
    if (hora.totalSegundos() < entrada.totalSegundos()) {
        vista.error("La salida no puede ser antes de la entrada (" + entrada.aTexto() + ").");
        return;
    }
    if (!franja.salidaPermitida(hora)) {
        Hora limite = franja.getHoraFin();
        limite = limite.sumarSegundos(-60);
        vista.error("La salida solo se puede registrar hasta las " + limite.aTextoCorto() +
                    ". Hora ingresada: " + hora.aTexto() + ".");
        return;
    }
    if (!persistencia.registrarSalida(cedula, nrc, fecha.aTexto(), hora.aTexto())) {
        vista.error("No se pudo guardar la salida.");
        return;
    }
    vista.exito("Salida registrada el " + fecha.aTexto() + " a las " + hora.aTexto() + ".");
}

void Controlador::registrarAsistencia() {
    vista.mensaje("1. Registrar ENTRADA\n2. Registrar SALIDA");
    int opcion = vista.pedirEntero("Opcion: ", 1, 2);
    if (opcion == 1) registrarEntrada();
    else registrarSalida();
}

void Controlador::ejecutar() {
    int opcion = 0;
    do {
        vista.mostrarMenu();
        opcion = vista.pedirEntero("Opcion: ", 1, 6);
        switch (opcion) {
            case 1: registrarDocente(); break;
            case 2: listarDocentes(); break;
            case 3: buscarDocente(); break;
            case 4: eliminarDocente(); break;
            case 5: registrarAsistencia(); break;
            default: break;
        }
    } while (opcion != 6);
    vista.mensaje("Hasta luego.");
}

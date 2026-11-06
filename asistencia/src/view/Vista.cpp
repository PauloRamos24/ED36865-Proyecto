#include "Vista.h"
#include "../model/FranjaHoraria.h"
#include "../util/Consola.h"
#include "../util/Validador.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

void Vista::mostrarMenu() {
    std::cout << "\n=========== REGISTRO DE ASISTENCIA ===========\n"
              << " 1. Registrar docente\n"
              << " 2. Listar docentes\n"
              << " 3. Buscar docente por cedula\n"
              << " 4. Eliminar docente\n"
              << " 5. Registrar entrada y salida\n"
              << " 6. Salir\n"
              << "==============================================\n";
}

void Vista::titulo(const std::string& texto) { std::cout << "\n--- " << texto << " ---\n"; }
void Vista::mensaje(const std::string& texto) { std::cout << texto << "\n"; }
void Vista::exito(const std::string& texto) { std::cout << "[OK] " << texto << "\n"; }
void Vista::error(const std::string& texto) { std::cout << "[ERROR] " << texto << "\n"; }

std::string Vista::pedirLibre(const std::string& mensaje) {
    int fallos = 0;
    while (true) {
        std::cout << mensaje << std::flush;
        std::string linea;
        if (std::getline(std::cin, linea)) {
            Consola::huboCtrlC();                              // limpia la marca de Ctrl+C
            if (!linea.empty() && linea[linea.size() - 1] == '\r') linea.erase(linea.size() - 1);
            if (Consola::contieneCtrlZ(linea)) {               // Ctrl+Z escrito dentro de la linea
                std::cout << "[AVISO] Ctrl+Z esta deshabilitado. Use la opcion 6 del menu para salir.\n";
                continue;
            }
            return linea;
        }

        // getline fallo: Ctrl+Z + Enter (fin de entrada) o Ctrl+C. Se limpia el error y se pregunta de nuevo.
        std::cin.clear();
        std::clearerr(stdin);
        if (Consola::huboCtrlC()) continue;                    // el manejador ya mostro el aviso

        // Si la entrada se acabo de verdad (archivo), se sale para no repetir para siempre.
        if (++fallos >= 3) {
            std::cout << "\nEntrada finalizada.\n";
            std::exit(0);
        }
        std::cout << "\n[AVISO] Ctrl+Z esta deshabilitado. Use la opcion 6 del menu para salir.\n";
    }
}

std::string Vista::pedir(const std::string& mensaje, Validacion valida,
                         const std::string& mensajeError) {
    while (true) {
        std::string texto = pedirLibre(mensaje);
        if (valida(texto)) return texto;
        error(mensajeError);
    }
}

int Vista::pedirEntero(const std::string& mensaje, int minimo, int maximo) {
    while (true) {
        std::string texto = pedirLibre(mensaje);
        if (Validador::esEnteroEnRango(texto, minimo, maximo)) return std::stoi(texto);
        error("Ingrese un numero entre " + std::to_string(minimo) + " y " +
              std::to_string(maximo) + " (sin espacios ni otros caracteres).");
    }
}

bool Vista::confirmar(const std::string& mensaje) {
    std::string r = pedir(mensaje + " (s/n): ", Validador::esSiNo, "Responda con s o n.");
    return r == "s" || r == "S";
}

void Vista::mostrarDias() {
    std::cout << "Dias de clase:\n";
    for (int g = 1; g <= FranjaHoraria::CANTIDAD_GRUPOS; ++g)
        std::cout << "   " << g << ". " << FranjaHoraria::nombreGrupo(g) << "\n";
}

void Vista::mostrarFranjas() {
    std::cout << "Franjas horarias (2 horas):\n";
    for (int n = 1; n <= FranjaHoraria::CANTIDAD; ++n)
        std::cout << "   " << n << ". " << FranjaHoraria::rangoDeFranja(n) << "\n";
}

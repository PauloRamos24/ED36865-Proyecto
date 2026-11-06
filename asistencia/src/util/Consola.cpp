#include "Consola.h"
#include <iostream>

static bool ctrlCPresionado = false;

#ifdef _WIN32
#include <windows.h>

// Windows llama a esta funcion cuando se presiona Ctrl+C.
// Devolver TRUE significa "ya lo manejo yo": el programa NO se cierra.
static BOOL WINAPI manejarCtrl(DWORD evento) {
    if (evento == CTRL_C_EVENT || evento == CTRL_BREAK_EVENT) {
        ctrlCPresionado = true;
        std::cout << "\n[AVISO] Ctrl+C esta deshabilitado. Use la opcion 6 del menu para salir.\n"
                  << std::flush;
        return TRUE;
    }
    return FALSE;
}

void Consola::bloquearCtrlC() { SetConsoleCtrlHandler(manejarCtrl, TRUE); }
#else
void Consola::bloquearCtrlC() {}                     // solo se bloquea en Windows
#endif

bool Consola::huboCtrlC() {
    bool hubo = ctrlCPresionado;
    ctrlCPresionado = false;
    return hubo;
}

bool Consola::contieneCtrlZ(const std::string& s) { return s.find('\x1a') != std::string::npos; }

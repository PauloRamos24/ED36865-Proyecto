#include "controller/Controlador.h"
#include "util/Consola.h"

int main() {
    Consola::bloquearCtrlC();   // Ctrl+C ya no cierra el programa
    Controlador app;
    app.ejecutar();
    return 0;
}

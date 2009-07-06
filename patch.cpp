#include <iostream>
#include "Diferencial.h"
#include "Archivo.h"

using namespace std;

int main(int argc, char *argv[])
{

    string uso =  "uso: " + string(argv[0]) + " [OPCIÓN] <archivo a patchear> <archivo diff>\n"
                  + "opciones: \n " +
                    "\t-R \taplica el diff de objetivo a origen (inversa)\n";
    bool inversa = false;
    char * nombre_diff, * nombre_orig;
    if (argc < 3 || argc > 4) {
        cout << uso;
        return 0;
    }
    if (argc == 4) {
        if (string(argv[1]) != "-R") {
            cout << "opción inválida " << argv[1] << endl;
            return 1;
        } else
            inversa = true;
    }
    nombre_orig = (argc == 3) ? argv[1] : argv[2];
    nombre_diff = (argc == 3) ? argv[2] : argv[3];

    Archivo origen(nombre_orig);
    if (!origen.isOpen()) {
        cout << "Error al intentar abrir: " << nombre_orig << endl;
        return 1;
    }
    Archivo diff(nombre_diff);
    if (!diff.isOpen()) {
        cout << "Error al intentar abrir: " << nombre_diff << endl;
        return 1;
    }
    Diferencial diferencial(diff, inversa);
    int n = diferencial.calcularLineasObjetivo(origen);
    Archivo objetivo(n);
    diferencial.aplicarCambios(origen, objetivo);
    objetivo.imprimir();
    return 0;
}

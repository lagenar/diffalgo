#include <iostream>
#include "Diferencial.h"
#include "Archivo.h"

using namespace std;

void uso()
{
    cout << "uso: ./patch [-o] <archivo a patchear> <archivo diff>" << endl;
    cout << "opciones: " << endl;
    cout << "          -o --> aplica el diff de objetivo a origen" << endl;
}

int main(int argc, char *argv[])
{
    bool reversa = false;
    char * nombrediff, * nombreobj;
    if (argc < 3 || argc > 4) {
        uso();
        return 0;
    }
    if (argc == 4) {
        if (string(argv[1]) != "-o") {
            cout << "opción inválida " << argv[1] << endl;
            return 1;
        } else
            reversa = true;
    }
    nombreobj = (argc == 3) ? argv[1] : argv[2];
    nombrediff = (argc == 3) ? argv[2] : argv[3];

    Archivo obj(nombreobj);
    if (!obj.isOpen()) {
        cout << "Error al intentar abrir: " << nombreobj << endl;
        return 1;
    }
    Archivo diff(nombrediff);
    if (!diff.isOpen()) {
        cout << "Error al intentar abrir: " << nombrediff << endl;
        return 1;
    }
    Diferencial diferencial(diff, obj, reversa);
    diferencial.aplicarPatch();
    return 0;
}

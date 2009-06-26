#include <iostream>
#include "Archivo.h"
#include "Diferencial.h"

using namespace std;

int main(int argc, char *argv[])
{
    Archivo orig(argv[1]);
    Archivo diff(argv[2]);
    Diferencial diferencial(diff, orig, false);
    diferencial.aplicarPatch();
    return 0;
    if (argc < 3) {
        cout << "uso: diff <archivo origen> <archivo objetivo>" << endl;
        return 0;
    }
    Archivo origen(argv[1]);
    if (!origen.isOpen()) {
        cout << "Error al intentar abrir " << argv[1] << endl;
        return 1;
    }
    Archivo objetivo(argv[2]);
    if (!objetivo.isOpen()) {
        cout << "Error al intentar abrir " << argv[2] << endl;
        return 1;
    }

//    Subsecuencia subsec;
//    calcularSubsecuencia(origen, objetivo, subsec);
//    Diferencial diff(origen, objetivo, subsec);
//    diff.imprimirDiff();
//    return 0;
}

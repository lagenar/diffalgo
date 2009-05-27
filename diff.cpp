#include <iostream>
#include <fstream>
#include "Archivo.h"
#include "Diferencial.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3) {
        cout << "uso: diff <archivo origen> <archivo objetivo>" << endl;
        return 0;
    }
    ifstream arch_orig(argv[1]);
    if (!arch_orig.is_open()) {
        cout << "Error al intentar abrir " << argv[1] << endl;
        return 1;
    }
    ifstream arch_obj(argv[2]);
    if (!arch_obj.is_open()) {
        cout << "Error al intentar abrir " << argv[2] << endl;
        return 1;
    }
    Archivo origen(arch_orig);
    Archivo objetivo(arch_obj);
    arch_orig.close();
    arch_obj.close();

    Diferencial diff(origen, objetivo);
    diff.imprimirDiff();
    return 0;
}

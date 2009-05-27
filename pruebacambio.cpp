#include "Cambio.h"
#include <fstream>
#include <iostream>

using namespace std;
int main (int argc, char * argv[])
{
    ifstream arch(argv[1]);
    Archivo a(arch);
    CambioEliminar celim(1,3,5);
    cout << celim.getDiff(a);
}

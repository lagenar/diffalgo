#include "Archivo.h"
#include <iostream>
int main(int argc, char * argv[])
{
	ifstream arch(argv[1]);
	if (!arch.is_open()) {
		cout << "El archivo no se encuentra, revise bien." << endl;
		return 1;
	}
	Archivo a(arch);
	/*for (int i=0;i<a.getCantLineas();i++){
		cout << a.getLinea(i) << endl;
	}*/
	a.imprimirArchivo();
	arch.close();
	return 0;
}

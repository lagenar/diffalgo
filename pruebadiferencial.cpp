#include <iostream>
#include <fstream>
#include "Diferencial.h"
#include "Archivo.h"

using namespace std;

int main(int argc, char * argv[])
{
	ifstream orig(argv[1]), dest(argv[2]);
	Archivo archorig(orig), archdest(dest);
	Diferencial diff(&archorig, &archdest);
	diff.imprimirDiff();
}

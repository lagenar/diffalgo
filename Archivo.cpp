#include "Archivo.h"
#include <iostream>

Archivo::Archivo(ifstream & arch)
{
    string temp;
    cantLineas = nroLineas(arch);
    lineas = new string[cantLineas];
    int n(0); // n es el contador que sirve para determinar las posiciones en el arreglo de strings.
    while (getline(arch, temp)) {
        lineas[n++]=temp;
    }
}

Archivo::~Archivo()
{
    delete [] lineas;
}

string Archivo::getLinea(int n) const
{
    return lineas[n-1];
}

void Archivo::setLinea(int n, string linea)
{
    lineas[n]=linea;
}

int Archivo::nroLineas(ifstream & arch)
{
    string linea;
    int n(0); // n es la cantidad de líneas.
    while (getline(arch, linea))
        n++;
    arch.clear();
    arch.seekg(0, ios::beg);
    return n;
}

int Archivo::getCantLineas()
{
    return cantLineas;
}

void Archivo::guardarArchivo(ostream & arch)
{
    for (int i = 0; i < cantLineas; i++)
        arch << lineas[i] << endl;
}


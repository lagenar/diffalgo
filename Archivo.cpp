#include "Archivo.h"
#include <iostream>

Archivo::Archivo(ifstream & arch)
{
    cantLineas = nroLineas(arch);
    lineas = new string[cantLineas];
    int n = 0;
    string temp;
    while (getline(arch, temp)) {
        lineas[n++] = temp;
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

void Archivo::setLinea(int n, const string & linea)
{
    lineas[n-1] = linea;
}

int Archivo::nroLineas(ifstream & arch)
{
    string linea;
    int n = 0;
    while (getline(arch, linea))
        n++;
    arch.clear();
    arch.seekg(0, ios::beg); // se deja el puntero de lectura en el principio
    return n;
}

int Archivo::getCantLineas() const
{
    return cantLineas;
}

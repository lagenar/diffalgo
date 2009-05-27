#include "Archivo.h"
#include <iostream>

Archivo::Archivo(const char nombre[])
{
    errorAbrir = false;
    ifstream arch(nombre);
    if (!arch.is_open()) { //si el archivo no se puede abrir, se retorna inmediatamente
                           //quien use esta clase debe llamar al método isOpen para verificar
        errorAbrir = true;
        return;
    }
    cantLineas = nroLineas(arch);
    lineas = new string[cantLineas];
    int n = 0;
    string temp;
    while (getline(arch, temp)) {
        lineas[n++] = temp;
    }
    arch.close();
}

bool Archivo::isOpen() const
{
    return !errorAbrir;
}

Archivo::~Archivo()
{
    if (!errorAbrir) // solo se hace el delete si se han alocado lineas
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

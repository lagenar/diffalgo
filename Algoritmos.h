#ifndef ALGORITMOS_H
#define ALGORITMOS_H
#include "Archivo.h"
#include "Lista.h"

class parInt {
    public:
        int Primero() { return primero; }
        int Segundo() { return segundo; }
        parInt(int p, int s) : primero(p), segundo(s) { }
    private:
        int primero, segundo;
};

typedef Lista<parInt> Subsecuencia;

void calcularSubsecuencia(const Archivo &, const Archivo &, Subsecuencia &);

#endif

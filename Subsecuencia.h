#ifndef SUBSECUENCIA_H
#define SUBSECUENCIA_H
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


#endif // SUBSECUENCIA_H

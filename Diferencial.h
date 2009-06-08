#ifndef DIFERENCIAL_H
#define DIFERENCIAL_H
#include "Lista.h"
#include "Cambio.h"
#include "Archivo.h"

class parInt {
    public:
        int Primero() { return primero; }
        int Segundo() { return segundo; }
        parInt(int p, int s) : primero(p), segundo(s) { }
    private:
        int primero, segundo;
};

typedef Lista<parInt> Subsecuencia;

class Diferencial : public Lista<Cambio*>
{
    public:
        Diferencial(Archivo &, Archivo &);
        ~Diferencial() { }
        void imprimirDiff();
    private:
        Archivo *archorig, *archobj;
};

void calcularSubsecuencia(const Archivo &, const Archivo &, Subsecuencia &);
void calcularCambios(const Archivo &, const Archivo &, Subsecuencia &, Diferencial &);

#endif // DIFERENCIAL_H

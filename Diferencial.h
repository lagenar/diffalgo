#ifndef DIFERENCIAL_H
#define DIFERENCIAL_H
#include "Lista.h"
#include "Cambio.h"
#include "Archivo.h"

class parInt {
    public:
        int primero;
        int segundo;
        parInt(int p, int s) : primero(p), segundo(s) { }
};

class Diferencial
{
    public:
        Diferencial(Archivo &, Archivo &);
        ~Diferencial() { }
        void imprimirDiff();
    private:
        Archivo *archorig, *archobj;

        void calcularSubsecuencia(Lista<parInt> &);
        void calcularCambios(Lista<Cambio*> &, Lista<parInt> &);
};

#endif // DIFERENCIAL_H

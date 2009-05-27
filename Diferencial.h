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
        Lista<parInt> subsecuencia;
        Lista<Cambio*> Cambios;

        void calcularCambios();
        void calcularSubsecuencia();
};

#endif // DIFERENCIAL_H

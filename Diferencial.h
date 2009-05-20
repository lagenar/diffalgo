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
        Diferencial(Archivo *, Archivo *);
        virtual ~Diferencial();
        void imprimirDiff();
    protected:
    private:
        Lista<parInt> subsecuencia;
        typedef IteradorLista<parInt> iterSubsecuencia;
        Lista<Cambio*> Cambios;
        Archivo *archorig, *archdest;

        void calcularSubsecuencia();
        void crearCambios();
};

#endif // DIFERENCIAL_H

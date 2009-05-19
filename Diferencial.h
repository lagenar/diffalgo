#ifndef DIFERENCIAL_H
#define DIFERENCIAL_H
#include "Lista.h"
#include "Cambio.h"
#include "Archivo.h"

struct parInt{
                int primero;
                int segundo;
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

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
        Diferencial(Archivo &, Archivo &, const Subsecuencia &);
        Diferencial(Archivo &, bool);
        ~Diferencial() { }
        void imprimirDiff();
    private:
        void calcularCambiosDiff(Archivo &, bool);
        void crearCambiosSubsecuencia(const Subsecuencia &);
        Archivo *archorig, *archobj;
};

void calcularSubsecuencia(const Archivo &, const Archivo &, Subsecuencia &);
void revertirDiff(Archivo &);
#endif // DIFERENCIAL_H

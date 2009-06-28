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
        //constructor para crear cambios a partir de dos archivos y su subsecuencia (diff)
        Diferencial(Archivo &, Archivo &, const Subsecuencia &);
        //constructor para crear cambios a partir dos archivos (origen y diff) y un flag
        //para la opción de aplicación inversa (patch)
        Diferencial(Archivo &, Archivo &, bool);
        ~Diferencial() { }
        void imprimirDiff();
        void aplicarPatch();
    private:
        //calcula la cantidad de lineas del archivo resultante en la aplicación del patch.
        int calcularLineasObjetivo();
        void calcularCambiosDiff(Archivo &, bool);
        void crearCambiosSubsecuencia(const Subsecuencia &);
        Archivo *archorig, *archobj;
};

void calcularSubsecuencia(const Archivo &, const Archivo &, Subsecuencia &);
#endif // DIFERENCIAL_H

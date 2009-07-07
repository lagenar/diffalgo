#ifndef DIFERENCIAL_H
#define DIFERENCIAL_H
#include "Lista.h"
#include "Cambio.h"
#include "Archivo.h"
#include "Subsecuencia.h"

class Diferencial : public Lista<Cambio*>
{
    public:
        //constructor para crear cambios a partir de dos archivos y su subsecuencia (diff)
        Diferencial(const Archivo &, const Archivo &, const Subsecuencia &);
        //constructor para crear cambios a partir dos archivos (origen y diff) y un flag
        //para la opción de aplicación inversa (patch)
        Diferencial(Archivo &, bool);
        ~Diferencial() { }
        void imprimirDiff();
        void aplicarCambios(const Archivo &, Archivo &);
        //calcula la cantidad de lineas del archivo resultante en la aplicación del patch.
        int calcularLineasObjetivo(const Archivo &);
    private:
        void crearCambiosDiff(Archivo &, bool);
        void crearCambiosSubsecuencia(const Archivo &, const Archivo &, const Subsecuencia &);
};

#endif // DIFERENCIAL_H

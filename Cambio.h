#ifndef CAMBIO_H
#define CAMBIO_H
#include "Archivo.h"
#include "Lista.h"
#include <string>
#include <sstream>

using namespace std;

class Cambio
{
    public:
        virtual string getDiff() = 0;
        virtual void aplicarPatch() = 0;
};

class CambioAgregar: public Cambio
{
    public:
        CambioAgregar(const Archivo &, int, int, int);
        string getDiff();
        void aplicarPatch() {  }
    private:
        int lineaOrigen;
        int lineaDestinoComienzo;
        int lineaDestinoFinal;
        Lista<string> lineas;
};

class CambioEliminar: public Cambio
{
    public:
        CambioEliminar(const Archivo &, int, int, int);
        string getDiff();
        void aplicarPatch() {  }
    private:
        int lineaDestino;
        int lineaOrigenComienzo;
        int lineaOrigenFinal;
        Lista<string> lineas;
};
#endif // CAMBIO_H

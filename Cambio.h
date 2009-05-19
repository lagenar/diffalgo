#ifndef CAMBIO_H
#define CAMBIO_H
#include "Archivo.h"
#include <string>
#include <sstream>

using namespace std;

class Cambio
{
    public:
        virtual string getDiff(const Archivo &) =0;
        virtual void aplicarPatch()=0;
};

class CambioAgregar: public Cambio
{
    public:
        CambioAgregar(int,int,int);
        ~CambioAgregar() {  }
        string getDiff(const Archivo &);
        void aplicarPatch() {  }
    private:
        int lineaOrigen;
        int lineaDestinoComienzo;
        int lineaDestinoFinal;
};

class CambioEliminar: public Cambio
{
    public:
        CambioEliminar(int, int, int);
        ~CambioEliminar() {  }
        string getDiff(const Archivo &);
        void aplicarPatch() {  }
    private:
        int lineaDestino;
        int lineaOrigenComienzo;
        int lineaOrigenFinal;
};
#endif // CAMBIO_H

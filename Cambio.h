#ifndef CAMBIO_H
#define CAMBIO_H
#include "Archivo.h"
#include "Lista.h"
#include <string>
#include <sstream>

using namespace std;

enum TipoCambio {AGREGAR, ELIMINAR};

class Cambio
{
    public:
        virtual ~Cambio() { }
        virtual string getDiff() = 0;
        virtual void aplicarPatch(Archivo&, int &, int &) = 0;
        virtual TipoCambio tipoCambio() = 0;
        virtual int getCantLineas() = 0;
        virtual int getIndiceInversa() = 0;
        virtual bool editaAPartirDe(int) = 0;
};

class CambioAgregar: public Cambio
{
    public:
        CambioAgregar(const Archivo &, int);
        CambioAgregar(const Archivo &, int, int, int);
        ~CambioAgregar() { }
        string getDiff();
        TipoCambio tipoCambio() { return AGREGAR;}
        int getCantLineas() { return lineaDestinoFinal - lineaDestinoComienzo +1; }
        void aplicarPatch(Archivo &, int &, int &);
        int getIndiceInversa() { return lineaOrigen; }
        bool editaAPartirDe(int);
    private:
        int lineaOrigen;
        int lineaDestinoComienzo;
        int lineaDestinoFinal;
        Lista<string> lineas;
};

class CambioEliminar: public Cambio
{
    public:
        CambioEliminar(const Archivo &, int);
        CambioEliminar(const Archivo &, int, int, int);
        ~CambioEliminar() { }
        string getDiff();
        TipoCambio tipoCambio() { return ELIMINAR;}
        int getCantLineas() { return lineaOrigenFinal - lineaOrigenComienzo + 1; }
        void aplicarPatch(Archivo &, int &, int &);
        int getIndiceInversa() { return lineaOrigenComienzo; }
        bool editaAPartirDe(int);
    private:
        int lineaDestino;
        int lineaOrigenComienzo;
        int lineaOrigenFinal;
        Lista<string> lineas;
};
#endif // CAMBIO_H

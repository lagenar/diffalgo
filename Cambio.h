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
        virtual void aplicarCambio(Archivo&, int) = 0;
        //Utilizado para reflexión de tipos de cambio
        virtual TipoCambio tipoCambio() = 0;
        //retorna la cantidad de líneas que edita
        virtual int getCantLineas() = 0;
        virtual int getIndiceOrigen() = 0;
        virtual bool editaAPartirDe(int) = 0;
    protected:
        Lista<string> lineas;
};

class CambioAgregar: public Cambio
{
    public:
        CambioAgregar(const Archivo &, int);
        CambioAgregar(const Archivo &, int, int, int);
        ~CambioAgregar() { }
        string getDiff();
        TipoCambio tipoCambio() { return AGREGAR; }
        int getCantLineas() { return lineaDestinoFinal - lineaDestinoComienzo + 1; }
        void aplicarCambio(Archivo &, int);
        int getIndiceOrigen() { return lineaOrigen; }
        bool editaAPartirDe(int);
    private:
        int lineaOrigen;
        int lineaDestinoComienzo;
        int lineaDestinoFinal;
};

class CambioEliminar: public Cambio
{
    public:
        CambioEliminar(const Archivo &, int);
        CambioEliminar(const Archivo &, int, int, int);
        ~CambioEliminar() { }
        string getDiff();
        TipoCambio tipoCambio() { return ELIMINAR; }
        int getCantLineas() { return lineaOrigenFinal - lineaOrigenComienzo + 1; }
        void aplicarCambio(Archivo &, int);
        int getIndiceOrigen() { return lineaOrigenComienzo; }
        bool editaAPartirDe(int);
    private:
        int lineaDestino;
        int lineaOrigenComienzo;
        int lineaOrigenFinal;
};
#endif // CAMBIO_H

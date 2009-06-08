#include "Cambio.h"

CambioAgregar::CambioAgregar(const Archivo & objetivo, int lineaOrigen, int lineaDestinoComienzo, int lineaDestinoFinal)
{
    this->lineaOrigen = lineaOrigen;
    this->lineaDestinoComienzo = lineaDestinoComienzo;
    this->lineaDestinoFinal = lineaDestinoFinal;
    for (int k = lineaDestinoComienzo; k <= lineaDestinoFinal; k++)
        lineas.insertarFinal(objetivo.getLinea(k));
}

string CambioAgregar::getDiff()
{
    stringstream resultado; // Se usa para la conversión de int a string.
    resultado << lineaOrigen << "a" << lineaDestinoComienzo << "," << lineaDestinoFinal << endl;
    IteradorLista<string> it(&lineas);
    while (!it.terminado()) {
        resultado << "> " << it.elemActual() << endl;
        it.sucesor();
    }
    return resultado.str();
}

CambioEliminar::CambioEliminar(const Archivo & origen, int lineaDestino, int lineaOrigenComienzo, int lineaOrigenFinal)
{
    this->lineaDestino = lineaDestino;
    this->lineaOrigenComienzo = lineaOrigenComienzo;
    this->lineaOrigenFinal = lineaOrigenFinal;
    for (int k = lineaOrigenComienzo; k <= lineaOrigenFinal; k++)
        lineas.insertarFinal(origen.getLinea(k));
}

string CambioEliminar::getDiff()
{
    stringstream resultado;
    resultado << lineaOrigenComienzo << "," << lineaOrigenFinal << "d" << lineaDestino << endl;
    IteradorLista<string> it(&lineas);
    while (!it.terminado()) {
        resultado << "< " << it.elemActual() << endl;
        it.sucesor();
    }
    return resultado.str();
}

#include "Cambio.h"

CambioAgregar::CambioAgregar(int lineaOrigen, int lineaDestinoComienzo, int lineaDestinoFinal)
{
    this->lineaOrigen = lineaOrigen;
    this->lineaDestinoComienzo = lineaDestinoComienzo;
    this->lineaDestinoFinal = lineaDestinoFinal;
}

string CambioAgregar::getDiff(const Archivo & archorig, const Archivo & archdest)
{
    stringstream resultado; // Se usa para la conversión de int a string.
    resultado << lineaOrigen << "a" << lineaDestinoComienzo << "," << lineaDestinoFinal << endl;
    for (int i = lineaDestinoComienzo; i <= lineaDestinoFinal; i++)
        resultado << "> " << archdest.getLinea(i) << endl;
    return resultado.str();
}

CambioEliminar::CambioEliminar(int lineaDestino, int lineaOrigenComienzo, int lineaOrigenFinal)
{
    this->lineaDestino = lineaDestino;
    this->lineaOrigenComienzo = lineaOrigenComienzo;
    this->lineaOrigenFinal = lineaOrigenFinal;
}

string CambioEliminar::getDiff(const Archivo & archorig, const Archivo & archdest)
{
    stringstream resultado;
    resultado << lineaOrigenComienzo << "," << lineaOrigenFinal << "d" << lineaDestino << endl;
    for (int i = lineaOrigenComienzo; i <= lineaOrigenFinal; i++)
        resultado << "< " << archorig.getLinea(i) << endl;
    return resultado.str();
}

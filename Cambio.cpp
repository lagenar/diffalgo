#include "Cambio.h"
#include <cstdlib>

CambioAgregar::CambioAgregar(const Archivo & Diff, int comienzo)
{
    string cabecera = Diff.getLinea(comienzo);
    int pos_a = cabecera.find('a');
    int pos_coma = cabecera.find(',');
    lineaOrigen = atoi(cabecera.substr(0, pos_a).c_str());
    lineaDestinoComienzo = atoi(cabecera.substr(pos_a + 1, pos_coma).c_str());
    lineaDestinoFinal = atoi(cabecera.substr(pos_coma + 1, cabecera.size()).c_str());
    int k = comienzo + 1;
    while (++k <= comienzo + lineaDestinoFinal - lineaDestinoComienzo + 1)
    {
        string linea = Diff.getLinea(k);
        lineas.insertarFinal(linea.substr(2, linea.size()));
    }
}

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

CambioEliminar::CambioEliminar(const Archivo & Diff, int comienzo)
{
    string cabecera = Diff.getLinea(comienzo);
    int pos_d = cabecera.find('d');
    int pos_coma = cabecera.find(',');
    lineaDestino = atoi(cabecera.substr(pos_d + 1, cabecera.size()).c_str());
    lineaOrigenComienzo = atoi(cabecera.substr(0, pos_coma).c_str());
    lineaOrigenFinal = atoi(cabecera.substr(pos_coma + 1, pos_d).c_str());
    int k = comienzo + 1;
    while (++k <= comienzo + lineaOrigenFinal - lineaOrigenComienzo + 1)
    {
        string linea = Diff.getLinea(k);
        lineas.insertarFinal(linea.substr(2, linea.size()));
    }
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

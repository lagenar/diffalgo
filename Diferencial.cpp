#include "Diferencial.h"
#include <iostream>

using namespace std;

Diferencial::Diferencial(Archivo & archorig, Archivo & archobj)
{
    this->archorig = &archorig;
    this->archobj = &archobj;
}

void Diferencial::calcularSubsecuencia(Lista<parInt> & subsecuencia)
{
    int k = 1;
    int j = 1;
    for (int i = 1; i <= archorig->getCantLineas(); i++) {
        j = k;
        while(j <= archobj->getCantLineas() && archorig->getLinea(i) != archobj->getLinea(j))
            j++;
        if (j <= archobj->getCantLineas()) {
            subsecuencia.insertarFinal(parInt(i, j));
            k = j + 1;
        }
    }
}

void Diferencial::calcularCambios(Lista<Cambio*> & Cambios, Lista<parInt> & subsecuencia)
{
    int i = 1;
    int k = 1;
    IteradorLista<parInt> it(&subsecuencia);
    if (!it.terminado()) {
        if (it.elemActual().primero > 1) { /* se eliminan las lineas anteriores a la primera linea
                                              del archivo origen que esta en la subsec*/
            Cambios.insertarFinal(new CambioEliminar(0, 1, it.elemActual().primero - 1));
            i = it.elemActual().primero;
        }
        if (it.elemActual().segundo > 1) { /* se agregan las lineas anteriores a la primera linea
                                              del archivo objetivo que esta en la subsec*/
            Cambios.insertarFinal(new CambioAgregar(0, 1, it.elemActual().segundo - 1));
            k = it.elemActual().segundo;
        }
        it.sucesor();
    } else
        k = i = 0; /*subsecuencia vacia: los indices se ponen en 0 para que se agregen todas
                     las lineas del archivo destino y se eliminen todas las del origen*/
    while (!it.terminado()) {
        if (it.elemActual().primero > i + 1)
            Cambios.insertarFinal(new CambioEliminar(k , i + 1, it.elemActual().primero - 1));
        if (it.elemActual().segundo > k + 1)
            Cambios.insertarFinal(new CambioAgregar(i, k + 1, it.elemActual().segundo - 1));
        i = it.elemActual().primero;
        k = it.elemActual().segundo;
        it.sucesor();
    }
    if (archorig->getCantLineas() > i) /* se crea el cambio que elimina las lineas
                                          que estan despues de la ultima linea de la subsec
                                          perteneciente al archivo origen
                                        */
        Cambios.insertarFinal(new CambioEliminar(k, i + 1, archorig->getCantLineas()));
    if (archobj->getCantLineas() > k) /* se crea el cambio que agrega las lineas
                                          que estan despues de la ultima linea de la subsec
                                          perteneciente al archivo objetivo
                                        */
        Cambios.insertarFinal(new CambioAgregar(i, k + 1, archobj->getCantLineas()));
}

void Diferencial::imprimirDiff()
{
    Lista<parInt> subsecuencia;
    Lista<Cambio*> Cambios;
    calcularSubsecuencia(subsecuencia);
    calcularCambios(Cambios, subsecuencia);
    IteradorLista<Cambio*> it(&Cambios);
    while (!it.terminado()) {
        cout << it.elemActual()->getDiff(*archorig, *archobj);
        it.sucesor();
    }
}

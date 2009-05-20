#include "Diferencial.h"
#include <iostream>

using namespace std;

Diferencial::Diferencial(Archivo * archorig, Archivo * archdest)
{
    this->archorig=archorig;
    this->archdest=archdest;
}

Diferencial::~Diferencial()
{

}

void Diferencial::calcularSubsecuencia()
{
    int k(1), j(1);
    for (int i=1; i<=archorig->getCantLineas(); i++) {
        j=k;
        while(j<=archdest->getCantLineas() && archorig->getLinea(i)!=archdest->getLinea(j))
            j++;
        if (j<=archdest->getCantLineas()) {
            subsecuencia.insertarFinal(parInt(i, j));
            k=j+1;
        }
    }
}

void Diferencial::crearCambios()
{
    int i(1), j(1);
    IteradorLista<parInt> it(&subsecuencia);
    if(!it.terminado()){ //Si la subsecuencia no es vacía.

        if (i < it.elemActual().primero) {
            Cambios.insertarFinal(new CambioEliminar(0,1,it.elemActual().primero-1));
            i=it.elemActual().primero;
        }
        if (j < it.elemActual().segundo) {
            Cambios.insertarFinal(new CambioAgregar(0,1,it.elemActual().segundo-1));
            j=it.elemActual().segundo;
        }
        it.sucesor();
        while (!it.terminado()) {
            if (i+1 < it.elemActual().primero) {
                Cambios.insertarFinal(new CambioEliminar(j,i+1,it.elemActual().primero-1));
            }
            if (j+1 <it.elemActual().segundo) {
                Cambios.insertarFinal(new CambioAgregar(i,j+1,it.elemActual().segundo-1));
            }
            i=it.elemActual().primero;
            j=it.elemActual().segundo;
            it.sucesor();
        }
        if (it.elemUltimo().primero<archorig->getCantLineas())
            Cambios.insertarFinal(new CambioEliminar(archdest->getCantLineas(),it.elemUltimo().primero+1,archorig->getCantLineas()));
        if (it.elemUltimo().segundo<archdest->getCantLineas())
            Cambios.insertarFinal(new CambioAgregar(archorig->getCantLineas(),it.elemUltimo().segundo+1,archdest->getCantLineas()));
    }
    else // Si la subsecuencia es vacía.
    {
        Cambios.insertarFinal(new CambioEliminar(archdest->getCantLineas(),1,archorig->getCantLineas()));
        Cambios.insertarFinal(new CambioAgregar(1,1,archdest->getCantLineas()));
    }
}

void Diferencial::imprimirDiff()
{
    this->calcularSubsecuencia();
    this->crearCambios();
    IteradorLista<Cambio*> it(&Cambios);
    while (!it.terminado()) {
        cout << it.elemActual()->getDiff(*archorig,*archdest);
        it.sucesor();
    }
}

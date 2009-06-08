#include "Diferencial.h"
#include <iostream>

using namespace std;

void calcularSubsecuencia(const Archivo & archorig, const Archivo & archobj, Subsecuencia & subsecuencia)
{
    int k = 1;
    int j = 1;
    for (int i = 1; i <= archorig.getCantLineas() && k <= archobj.getCantLineas(); i++) {
        j = k;
        while(j <= archobj.getCantLineas() && archorig.getLinea(i) != archobj.getLinea(j))
            j++;
        if (j <= archobj.getCantLineas()) {
            subsecuencia.insertarFinal(parInt(i, j));
            k = j + 1;
        }
    }
}

void calcularCambios(const Archivo & archorig, const Archivo & archobj, Subsecuencia & subsec, Diferencial & diff)
{
    int i = 1;
    int k = 1;
    IteradorLista<parInt> it(&subsec);
    if (!it.terminado()) {
        if (it.elemActual().Primero() > 1) { /* se eliminan las lineas anteriores a la primera linea
                                              del archivo origen que esta en la subsec*/
            diff.insertarFinal(new CambioEliminar(0, 1, it.elemActual().Primero() - 1));
            i = it.elemActual().Primero();
        }
        if (it.elemActual().Segundo() > 1) { /* se agregan las lineas anteriores a la primera linea
                                              del archivo objetivo que esta en la subsec*/
            diff.insertarFinal(new CambioAgregar(0, 1, it.elemActual().Segundo() - 1));
            k = it.elemActual().Segundo();
        }
        it.sucesor();
    } else
        k = i = 0; /*subsecuencia vacia: los indices se ponen en 0 para que se agregen todas
                     las lineas del archivo objetivo y se eliminen todas las del origen*/
    while (!it.terminado()) {
        if (it.elemActual().Primero() > i + 1)
            diff.insertarFinal(new CambioEliminar(k , i + 1, it.elemActual().Primero() - 1));
        if (it.elemActual().Segundo() > k + 1)
            diff.insertarFinal(new CambioAgregar(i, k + 1, it.elemActual().Segundo() - 1));
        i = it.elemActual().Primero();
        k = it.elemActual().Segundo();
        it.sucesor();
    }
    if (archorig.getCantLineas() > i) /* se crea el cambio que elimina las lineas
                                          que estan despues de la ultima linea de la subsec
                                          perteneciente al archivo origen
                                        */
        diff.insertarFinal(new CambioEliminar(k, i + 1, archorig.getCantLineas()));
    if (archobj.getCantLineas() > k) /* se crea el cambio que agrega las lineas
                                          que estan despues de la ultima linea de la subsec
                                          perteneciente al archivo objetivo
                                        */
        diff.insertarFinal(new CambioAgregar(i, k + 1, archobj.getCantLineas()));
}

Diferencial::Diferencial(Archivo & archorig, Archivo & archobj)
{
    this->archorig = &archorig;
    this->archobj = &archobj;
}

void Diferencial::imprimirDiff()
{
    IteradorLista<Cambio*> it(this);
    while (!it.terminado()) {
        cout << it.elemActual()->getDiff(*archorig, *archobj);
        it.sucesor();
    }
}

#include "Diferencial.h"
#include <iostream>

using namespace std;

Diferencial::Diferencial(Archivo & archorig, Archivo & archobj)
{
    this->archorig = &archorig;
    this->archobj = &archobj;
    calcularSubsecuencia();
    calcularCambios();
}

void Diferencial::calcularSubsecuencia()
{
    int m = archorig->getCantLineas() + 1;
    int n = archobj->getCantLineas() + 1;
    int MatLCS[m][n];
    for (int i = 1; i < m; i++)
        MatLCS[i][0] = 0;
    for (int i = 0; i < n; i++)
        MatLCS[0][i] = 0;
    for (int i = 1; i < m; i++)
        for (int k = 1; k < n; k++) {
            if (archorig->getLinea(i) == archobj->getLinea(k))
                MatLCS[i][k] = MatLCS[i - 1][k - 1] + 1;
            else if (MatLCS[i - 1][k] >= MatLCS[i][k - 1])
                MatLCS[i][k] = MatLCS[i - 1][k];
            else
                MatLCS[i][k] = MatLCS[i][k - 1];
        }
   m--;
   n--;
   while (m > 0 && n > 0) {
       if (archorig->getLinea(m) == archobj->getLinea(n)) {
           subsecuencia.insertarPrincipio(parInt(m, n));
           m--;
           n--;
       }
       else if (MatLCS[m - 1][n] >= MatLCS[m][n - 1]) {
           m--;
       }
       else {
           n--;
       }
   }
}

void Diferencial::calcularCambios()
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
                     las lineas del archivo objetivo y se eliminen todas las del origen*/
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
    IteradorLista<Cambio*> it(&Cambios);
    while (!it.terminado()) {
        cout << it.elemActual()->getDiff(*archorig, *archobj);
        it.sucesor();
    }
}

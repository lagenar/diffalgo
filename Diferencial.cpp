#include "Diferencial.h"
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

void calcularSubsecuencia(const Archivo & archorig, const Archivo & archobj, Subsecuencia & subsecuencia)
{
    int k = 1;
    int j = 1;
    int i = 1;
    while (i <= archorig.getCantLineas() && k <= archobj.getCantLineas()) {
        j = k;
        while(j <= archobj.getCantLineas() && archorig.getLinea(i) != archobj.getLinea(j))
            j++;
        if (j <= archobj.getCantLineas()) {
            subsecuencia.insertarFinal(parInt(i, j));
            k = j + 1;
        }
        i++;
    }
}

void Diferencial::crearCambiosSubsecuencia(const Subsecuencia & subsec)
{
    int i = 1;
    int k = 1;
    IteradorLista<parInt> it(&subsec);
    if (!it.terminado()) {
        if (it.elemActual().Segundo() > 1) { /* se agregan las lineas anteriores a la primera linea
                                              del archivo objetivo que esta en la subsec*/
            insertarFinal(new CambioAgregar(*archobj, 0, 1, it.elemActual().Segundo() - 1));
            k = it.elemActual().Segundo();
        }
        if (it.elemActual().Primero() > 1) { /* se eliminan las lineas anteriores a la primera linea
                                              del archivo origen que esta en la subsec*/
            insertarFinal(new CambioEliminar(*archorig, 0, 1, it.elemActual().Primero() - 1));
            i = it.elemActual().Primero();
        }
        it.sucesor();
    } else
        k = i = 0; /*subsecuencia vacia: los indices se ponen en 0 para que se agregen todas
                     las lineas del archivo objetivo y se eliminen todas las del origen*/
    while (!it.terminado()) {
        if (it.elemActual().Segundo() > k + 1)
            insertarFinal(new CambioAgregar(*archobj, i, k + 1, it.elemActual().Segundo() - 1));
        if (it.elemActual().Primero() > i + 1)
            insertarFinal(new CambioEliminar(*archorig, k , i + 1, it.elemActual().Primero() - 1));
        i = it.elemActual().Primero();
        k = it.elemActual().Segundo();
        it.sucesor();
    }
    if (archobj->getCantLineas() > k) /* se crea el cambio que agrega las lineas
                                          que estan despues de la ultima linea de la subsec
                                          perteneciente al archivo objetivo
                                        */
        insertarFinal(new CambioAgregar(*archobj, i, k + 1, archobj->getCantLineas()));
    if (archorig->getCantLineas() > i) /* se crea el cambio que elimina las lineas
                                          que estan despues de la ultima linea de la subsec
                                          perteneciente al archivo origen
                                        */
        insertarFinal(new CambioEliminar(*archorig, k, i + 1, archorig->getCantLineas()));
}

Diferencial::Diferencial(Archivo & archorig, Archivo & archobj, const Subsecuencia & subsec)
{
    this->archorig = &archorig;
    this->archobj = &archobj;
    crearCambiosSubsecuencia(subsec);
}

void Diferencial::imprimirDiff()
{
    IteradorLista<Cambio*> it(this);
    while (!it.terminado()) {
        cout << it.elemActual()->getDiff();
        it.sucesor();
    }
}

void revertirDiff(Archivo & Diff)
{
    int i = 1;
    while (i <= Diff.getCantLineas()) {
        string linea = Diff.getLinea(i);
        int pos_a = linea.find('a');
        if (pos_a != -1) {
            int pos_coma = linea.find(',');
            int lineaOrig = atoi(linea.substr(0, pos_a).c_str());
            int lineaDestCom = atoi(linea.substr(pos_a + 1, pos_coma).c_str());
            int lineaDestFin = atoi(linea.substr(pos_coma + 1, linea.size()).c_str());
            stringstream res;
            res << lineaDestCom << "," << lineaDestFin << "d" << lineaOrig;
            Diff.setLinea(i, res.str());
            int k = i;
            while (++k <= i + lineaDestFin - lineaDestCom +1) {
                string temp = Diff.getLinea(k);
                temp[0] = '<';
                Diff.setLinea(k, temp);
            }
            i = k;
        } else {
            int pos_d = linea.find('d');
            int pos_coma = linea.find(',');
            int lineaOrigCom = atoi(linea.substr(0, pos_coma).c_str());
            int lineaOrigFin = atoi(linea.substr(pos_coma + 1, pos_d).c_str());
            int lineaDest = atoi(linea.substr(pos_d +1, linea.size()).c_str());
            stringstream res;
            res << lineaDest << "a" << lineaOrigCom << "," << lineaOrigFin;
            Diff.setLinea(i, res.str());
            int k = i;
            while (++k <= i + lineaOrigFin - lineaOrigCom + 1) {
                string temp = Diff.getLinea(k);
                temp[0] = '>';
                Diff.setLinea(k, temp);
            }
            i = k;
        }
    }
}


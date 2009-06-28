#include "Diferencial.h"
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

/*compilación condicional para la subsecuencia más larga,
comentar la siguiente línea si se quiere usar el algoritmo básico*/
#define LCS
#ifndef LCS
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
#else
void calcularSubsecuencia(const Archivo & archorig, const Archivo & archobj, Subsecuencia & subsecuencia)
{
    int m = archorig.getCantLineas() + 1;
    int n = archobj.getCantLineas() + 1;
    int MatLCS[m][n];
    for (int i = 1; i < m; i++)
        MatLCS[i][0] = 0;
    for (int i = 0; i < n; i++)
        MatLCS[0][i] = 0;
    for (int i = 1; i < m; i++)
        for (int k = 1; k < n; k++) {
            if (archorig.getLinea(i) == archobj.getLinea(k))
                MatLCS[i][k] = MatLCS[i - 1][k - 1] + 1;
            else if (MatLCS[i - 1][k] >= MatLCS[i][k - 1])
                MatLCS[i][k] = MatLCS[i - 1][k];
            else
                MatLCS[i][k] = MatLCS[i][k - 1];
        }
   m--;
   n--;
   while (m > 0 && n > 0) {
       if (archorig.getLinea(m) == archobj.getLinea(n)) {
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
#endif

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

Diferencial::Diferencial(Archivo & Diff, Archivo & origen, bool inversa) {
    archorig = &origen;
    archobj = NULL;
    calcularCambiosDiff(Diff, inversa);
}

void Diferencial::imprimirDiff()
{
    IteradorLista<Cambio*> it(this);
    while (!it.terminado()) {
        cout << it.elemActual()->getDiff();
        it.sucesor();
    }
}

void invertirDiff(Archivo & Diff)
{
    int i = 1;
    while (i <= Diff.getCantLineas()) {
        string linea = Diff.getLinea(i);
        size_t pos_a = linea.find('a');
        if (pos_a != string::npos) {
            size_t pos_coma = linea.find(',');
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
            size_t pos_d = linea.find('d');
            size_t pos_coma = linea.find(',');
            int lineaOrigCom = atoi(linea.substr(0, pos_coma).c_str());
            int lineaOrigFin = atoi(linea.substr(pos_coma + 1, pos_d).c_str());
            int lineaDest = atoi(linea.substr(pos_d + 1, linea.size()).c_str());
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

Cambio * getCambioDiff(Archivo & Diff, int i)
{
    if (Diff.getLinea(i).find('a') != string::npos)
        return new CambioAgregar(Diff, i);
    return new CambioEliminar(Diff, i);
}

void Diferencial::calcularCambiosDiff(Archivo & Diff, bool inversa)
{
    if(inversa)
        invertirDiff(Diff);
    int i = 1;
    Cambio * anterior = NULL;
    while (i <= Diff.getCantLineas()) {
        Cambio * actual = getCambioDiff(Diff, i);
        i += actual->getCantLineas() + 1;
        if (anterior != NULL && actual->getIndiceOrigen() < anterior->getIndiceOrigen()) {
            insertarFinal(actual);
            insertarFinal(anterior);
            anterior = NULL;
        }
        else {
            if (anterior != NULL) {
                insertarFinal(anterior);
            }
            anterior = actual;
        }
    }
    if (anterior != NULL)
        insertarFinal(anterior);
}

int Diferencial::calcularLineasObjetivo()
{
    IteradorLista<Cambio*> it(this);
    int lineas_eliminadas = 0;
    int lineas_agregadas = 0;
    while(!it.terminado()) {
        Cambio * cambio = it.elemActual();
        if(cambio->tipoCambio() == AGREGAR)
            lineas_agregadas += cambio->getCantLineas();
        else
            lineas_eliminadas += cambio->getCantLineas();
        it.sucesor();
    }
    return archorig->getCantLineas() + lineas_agregadas - lineas_eliminadas;
}

void Diferencial::aplicarPatch()
{
    int n = calcularLineasObjetivo();
    Archivo resultado(n);
    IteradorLista<Cambio*> it(this);
    int ind_orig = 1;
    int ind_obj = 1;
    while(!it.terminado()) {
        Cambio * cambio = it.elemActual();
        while (!cambio->editaAPartirDe(ind_orig)) {
            resultado.setLinea(ind_obj, archorig->getLinea(ind_orig));
            ind_orig++;
            ind_obj++;
        }
        cambio->aplicarPatch(resultado, ind_orig, ind_obj);
        it.sucesor();
    }
    while (ind_orig <= archorig->getCantLineas()) {
        resultado.setLinea(ind_obj, archorig->getLinea(ind_orig));
        ind_orig++;
        ind_obj++;
    }
    resultado.imprimir();
}

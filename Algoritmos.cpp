#include "Algoritmos.h"

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
    enum flecha {diagonal, arriba, izquierda, nada};
    struct elem_mat {
        flecha fl;
        int lcs;
    };
    int m = archorig.getCantLineas() + 1;
    int n = archobj.getCantLineas() + 1;
    elem_mat MatLCS[m][n];
    for (int i = 1; i < m; i++) {
        MatLCS[i][0].fl = nada;
        MatLCS[i][0].lcs = 0;
    }
    for (int i = 0; i < n; i++) {
        MatLCS[0][i].fl = nada;
        MatLCS[0][i].lcs = 0;
    }
    for (int i = 1; i < m; i++)
        for (int k = 1; k < n; k++) {
            if (archorig.getLinea(i) == archobj.getLinea(k)) {
                MatLCS[i][k].fl = diagonal;
                MatLCS[i][k].lcs = MatLCS[i - 1][k - 1].lcs + 1;
            }
            else if (MatLCS[i - 1][k].lcs >= MatLCS[i][k - 1].lcs) {
                MatLCS[i][k].fl = arriba;
                MatLCS[i][k].lcs = MatLCS[i - 1][k].lcs;
            }
            else {
                MatLCS[i][k].fl = izquierda;
                MatLCS[i][k].lcs = MatLCS[i][k - 1].lcs;
            }
        }
   m--;
   n--;
   while (m > 0 && n > 0) {
       if (MatLCS[m][n].fl == diagonal) {
           subsecuencia.insertarPrincipio(parInt(m, n));
           m--;
           n--;
       }
       else if (MatLCS[m][n].fl == arriba) {
           m--;
       }
       else {
           n--;
       }
   }
}
#endif

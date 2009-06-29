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

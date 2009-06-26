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


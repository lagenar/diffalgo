//prueba del algoritmo dinamico para calcular la subsecuencia mas larga(LCS).
//el algoritmo se encuentra en Introduction to algorithms (Mit-press, Thomas Cormen) pag 350

#include <iostream>
#include <string>

using namespace std;

//para que el algoritmo se entienda mejor se usan strings
void LCS(string origen, string objetivo)
{
  int m = origen.length() + 1;
  int n = objetivo.length() + 1;
  int MatLCS[m][n];
  for (int i = 1; i < m; i++)
    MatLCS[i][0] = 0;
  for (int i = 0; i < n; i++)
    MatLCS[0][i] = 0;
  for (int i = 1; i < m; i++)
    for (int k = 1; k < n; k++) {
      if (origen[i-1] == objetivo[k-1])
	MatLCS[i][k] = MatLCS[i - 1][k - 1] + 1;
      else if (MatLCS[i - 1][k] >= MatLCS[i][k - 1])
	MatLCS[i][k] = MatLCS[i - 1][k];
      else
	MatLCS[i][k] = MatLCS[i][k - 1];
    }
  cout << "Matriz de LCS" << endl;
  for (int i = 0; i < m; i++) {
    for (int k = 0; k < n; k++)
      cout << MatLCS[i][k] << " ";
    cout << endl;
  }
  string resultado = "";
  string temp = " ";
  m--;
  n--;
  while(m > 0 && n > 0) {
    if(origen[m-1] == objetivo[n-1]) {
      temp[0] = origen[m-1];
      resultado = temp + resultado;
      m--;
      n--;
    }
    else if (MatLCS[m-1][n] >= MatLCS[m][n-1]) 
      m--;
    else
      n--;
  }
  cout << endl << "La subsecuencia más larga es: " << resultado << endl;
			 
}

int main()
{
  LCS("ABCBDAB","BDCABA");
  return 0;
}

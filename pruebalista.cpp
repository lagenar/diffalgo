#include "lista.h"
#include <iostream>

using namespace std;

int main()
{
  Lista<int> l;
  l.insertarFinal(1);
  l.insertarFinal(2);
  IteradorLista<int> it(&l);
  while (!it.terminado()) {
    cout << it.elemActual() << endl;
    it.sucesor();
  }
  return 0;
}

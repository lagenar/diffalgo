#ifndef LISTA_H
#define LISTA_H

template <class T>
class Lista {
  struct nodo_lista{
    T elem;
    struct nodo_lista* sig;
  } *cabeza, *final;

  void _eliminarLista();
  
 public:
  Lista();
  ~Lista();
  void insertarFinal(T elem);
};

template <class T>
Lista<T>::Lista()
{
  cabeza = 0;
  final = 0;
}

template <class T>
void Lista<T>::insertarFinal(T elem)
{
  nodo_lista* nuevo = new nodo_lista;
  nuevo->elem = elem;
  nuevo->sig = 0;
  if (cabeza == 0) 
    cabeza = final =  nuevo;
  else {
    final->sig = nuevo;
    final = nuevo;
  }
}

template <class T>
void Lista<T>::_eliminarLista()
{
  nodo_lista* cursor;
  while (cabeza != 0) {
    cursor = cabeza;
    cabeza = cabeza->sig;
    delete cursor;
  }
}

template <class T>
Lista<T>::~Lista()
{
  _eliminarLista();
}

#endif

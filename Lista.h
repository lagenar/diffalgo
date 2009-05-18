#ifndef LISTA_H
#define LISTA_H

template <class T>
struct nodo_lista {
  T elem;
  struct nodo_lista* sig;
};

template <class T> class IteradorLista;

template <class T>
class Lista {
  struct nodo_lista<T> *cabeza, *cola;
  void _eliminarLista();
  
 public:
  Lista();
  ~Lista();
  void insertarFinal(T elem);
  friend class IteradorLista<T>;
};

template <class T>
Lista<T>::Lista()
{
  cabeza = 0;
  cola = 0;
}

template <class T>
void Lista<T>::insertarFinal(T elem)
{
  nodo_lista<T>* nuevo = new nodo_lista<T>;
  nuevo->elem = elem;
  nuevo->sig = 0;
  if (cabeza == 0) 
    cabeza = cola =  nuevo;
  else {
    cola->sig = nuevo;
    cola = nuevo;
  }
}

template <class T>
void Lista<T>::_eliminarLista()
{
  nodo_lista<T>* cursor;
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

template <class T>
class IteradorLista {
  struct nodo_lista<T> *cursor;
  const Lista<T>* lista;
 public:
  IteradorLista(const Lista<T> *);
  ~IteradorLista() { };
  void rewind();
  void sucesor();
  bool terminado();
  T elemActual();
};

template <class T>
IteradorLista<T>::IteradorLista(const Lista<T> * L)
{
  cursor = L->cabeza;
  lista = L;
}

template <class T>
void IteradorLista<T>::rewind()
{
  cursor = lista->cabeza;
}

template <class T>
void IteradorLista<T>::sucesor()
{
  cursor = cursor->sig;
}

template <class T>
bool IteradorLista<T>::terminado()
{
  return (cursor == 0);
}

template <class T>
T IteradorLista<T>::elemActual()
{
  return (cursor->elem);
}

#endif

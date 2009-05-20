#ifndef LISTA_H
#define LISTA_H

template <class T> class Lista;
template <class T> class IteradorLista;

template <class T>
class Nodo {
    T elem;
    Nodo<T> * sig;
    public:
        Nodo(const T & e, Nodo * s) : elem(e), sig(s) { };
        friend class Lista<T>;
        friend class IteradorLista<T>;
};

template <class T>
class Lista {
  struct Nodo<T> *cabeza, *cola;
  void _eliminarLista();

 public:
  Lista();
  ~Lista();
  void insertarFinal(const T & elem);
  friend class IteradorLista<T>;
};

template <class T>
Lista<T>::Lista()
{
  cabeza = 0;
  cola = 0;
}

template <class T>
void Lista<T>::insertarFinal(const T & elem)
{
  Nodo<T>* nuevo = new Nodo<T>(elem, 0);
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
  Nodo<T>* cursor;
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
  struct Nodo<T> *cursor;
  const Lista<T>* lista;
 public:
  IteradorLista(const Lista<T> *);
  ~IteradorLista() { };
  void rewind();
  void sucesor();
  bool terminado();
  T elemActual();
  T elemUltimo();
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

template <class T>
T IteradorLista<T>::elemUltimo()
{
    return (lista->cola->elem);
}

#endif

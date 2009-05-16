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

#endif

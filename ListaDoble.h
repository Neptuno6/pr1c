#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include <iostream>
#include <string>
//Haremos la clase lista doble para representar a las listas dobles
template <typename T>
struct NodoDoble{
    T dato;
    NodoDoble<T>* siguiente;
    NodoDoble<T>* anterior;

    // Inicializa el dato y ambos enlaces del nodo doble.
    NodoDoble<T>(const T& d): dato(d), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>

class ListaDoble{
protected:
    NodoDoble<T>* primero;
    NodoDoble<T>* ultimo;

    // Agrega un nodo al final y actualiza los enlaces anterior y siguiente.
    void insertarAlFinal(const T& elemento){
        NodoDoble<T>* nuevo = new NodoDoble<T>(elemento);
        if(primero == nullptr){
            primero = nuevo;
            ultimo = nuevo;
            return;
        }

        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
        }


public:
    // Crea una lista doble sin nodos.
    ListaDoble(): primero(nullptr), ultimo(nullptr) {}

    // Permite recorrer la lista desde los modulos de consultas sin exponer sus enlaces internos.
    // Devuelve el primer nodo para permitir recorridos externos.
    NodoDoble<T>* inicio() const {
        return primero;
    }

    // Libera todos los nodos y restablece el extremo final.
    virtual ~ListaDoble() {
        while (primero != nullptr) {
            NodoDoble<T>* siguiente = primero->siguiente;
            delete primero;
            primero = siguiente;
        }
        ultimo = nullptr;
    }

    // puede ser NodoInvestigador, NodoProyecto, NodoRevista, etc.
    // Inserta un elemento utilizando la operación genérica al final.
    virtual void insertar(const T& elemento) {
        insertarAlFinal(elemento);
    }

    virtual void imprimir() const = 0;
};

#endif



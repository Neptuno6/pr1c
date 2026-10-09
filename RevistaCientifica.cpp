#include <iostream>
#include "RevistasCientificas.h"
#include <string> //El uso de string facilita el ordenar la inserción por nombre, ya que permite comparar cadenas de texto directamente.
//Con sobrecarga cambiamos la insercención a una por nombre ordenado
//Esto se ve como más código que el de Investigador, pero es porque la inserción por defecto de listaSimple.h, ya es una inserción al final
//Y en este caso, queremos que la inserción sea ordenada por nombre, lo que requiere más código para recorrer la lista y encontrar la posición correcta para insertar el nuevo nodo.
// Recorre hasta el último nodo de la lista circular.
// Rompe su enlace con primero para que el destructor de la lista base pueda liberar memoria.
RevistaCientifica::~RevistaCientifica() {
    if (primero == nullptr) {
        return;
    }
    NodoSimple<NodoRevista>* actual = primero;
    while (actual->siguiente != primero) {
        actual = actual->siguiente;
    }
    actual->siguiente = nullptr;
}

// Comprueba que la ID no exista antes de reservar el nuevo nodo.
// Después recorre por nombre y ajusta los enlaces para conservar el orden circular.
void RevistaCientifica::insertar(const NodoRevista& revista) {
    if (buscarPorId(revista.idRevista) != nullptr) {
        std::cout << "Error: el ID de la revista ya esta registrado.\n";
        return;
    }
    NodoSimple<NodoRevista>* nuevo = new NodoSimple<NodoRevista>(revista);

    if (primero == nullptr || revista.nombre < primero->dato.nombre) { 
        //La condición para ordenar por nombre inicia pimero en que no puede estar vacía la lista
        //Si la lista está vacía o el nombre de la revista es menor que el nombre del primer nodo, se inserta al inicio de la lista.
        if (primero == nullptr) {
            nuevo->siguiente = nuevo;
        } else {
            NodoSimple<NodoRevista>* ultimo = primero;
            while (ultimo->siguiente != primero) {
                ultimo = ultimo->siguiente;
            }
            nuevo->siguiente = primero;
            ultimo->siguiente = nuevo;
        }
        primero = nuevo;
        return;
    }

    NodoSimple<NodoRevista>* actual = primero;
    while (actual->siguiente != primero &&
           actual->siguiente->dato.nombre < revista.nombre) { //Mientras el siguiente nodo no sea nulo 
      //y el nombre del siguiente nodo sea menor que el nombre de la revista, se avanza al siguiente nodo.
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente; //Nuevo nodo ahora apunta al siguiente nodo del actual, insertando el nuevo nodo en la posición correcta.
    actual->siguiente = nuevo; //El nodo actual ahora apunta al nuevo nodo, completando la inserción en la lista ordenada.
}

// Empaqueta los datos recibidos en un NodoRevista.
// La inserción principal se encarga del orden alfabético y de los duplicados.
void RevistaCientifica::insertar(
    int id, const std::string& nombre, const std::string& editorial,
    const std::string& pais, int FactorImpacto, const std::string& Cuartil) {
    NodoRevista revista(id, nombre, editorial, pais, FactorImpacto, Cuartil);
    insertar(revista);
}

// Recorre la lista circular comparando la ID de cada revista.
// Se detiene al encontrarla o cuando vuelve al primer nodo.
NodoRevista* RevistaCientifica::buscarPorId(int idRevista) {
    NodoSimple<NodoRevista>* actual = primero;
    if (actual == nullptr) {
        return nullptr;
    }
    do {
        if (actual->dato.idRevista == idRevista) {
            return &actual->dato;
        }
        actual = actual->siguiente;
    } while (actual != primero);
    return nullptr;
}

// Usa buscarPorId para localizar la revista solicitada.
// Si existe, reemplaza la editorial y confirma la operación con true.
bool RevistaCientifica::modificarEditorial(int idRevista, const std::string& editorial) {
    NodoRevista* revista = buscarPorId(idRevista);
    if (revista == nullptr) {
        return false;
    }
    revista->editorial = editorial;
    return true;
}

// Busca la revista y distingue si es el único nodo, el primero o uno intermedio.
// Repara los enlaces circulares, libera el nodo y devuelve si la eliminación fue posible.
bool RevistaCientifica::eliminar(int idRevista) {
    if (primero == nullptr) {
        return false;
    }
    NodoSimple<NodoRevista>* anterior = primero;
    while (anterior->siguiente != primero &&
           anterior->siguiente->dato.idRevista != idRevista) {
        anterior = anterior->siguiente;
    }
    NodoSimple<NodoRevista>* objetivo = nullptr;
    if (primero->dato.idRevista == idRevista) {
        objetivo = primero;
        if (primero->siguiente == primero) {
            primero = nullptr;
        } else {
            NodoSimple<NodoRevista>* ultimo = primero;
            while (ultimo->siguiente != primero) {
                ultimo = ultimo->siguiente;
            }
            primero = primero->siguiente;
            ultimo->siguiente = primero;
        }
    } else if (anterior->siguiente != primero &&
               anterior->siguiente->dato.idRevista == idRevista) {
        objetivo = anterior->siguiente;
        anterior->siguiente = objetivo->siguiente;
    }
    if (objetivo == nullptr) {
        return false;
    }
    delete objetivo;
    return true;
}

// Recorre la lista desde primero y muestra todos sus campos.
// La condición de regreso al inicio evita que una lista circular se vuelva infinita.
void RevistaCientifica::imprimir() const {
    NodoSimple<NodoRevista>* actual = primero;

    if (actual == nullptr) {
        return;
    }
    do {
        std::cout << actual->dato.idRevista << " - "
                  << actual->dato.nombre << " - "
                  << actual->dato.editorial << " - "
                  << actual->dato.pais << " - "
                  << actual->dato.FactorImpacto << " - "
                  << actual->dato.Cuartil << '\n';
        actual = actual->siguiente;
    } while (actual != primero);
}

#include "Universidad.h"
#include <iostream>
#include <string>

// No necesita liberar nodos manualmente.
// El destructor heredado recorre la lista doble y libera primero, siguiente y ultimo.
Universidad::~Universidad() = default;

// Comprueba que la ID de universidad no esté registrada.
// Si es válida, usa insertarAlFinal para actualizar primero, ultimo y anterior.
void Universidad::insertar(const NodoUniversidad& universidad) {
    if (buscarPorId(universidad.idUniversidad) != nullptr) {
        std::cout << "Error: el IDU ya esta registrado.\n";
        return;
    }
    insertarAlFinal(universidad);
}
// Construye una universidad con su ID, nombre, país y ranking.
// Delega la inserción para aplicar la misma validación de duplicados.
void Universidad::insertar(const std::string& idUniversidad, const std::string& nombre, const std::string& pais, const int& ranking) {
    NodoUniversidad universidad(idUniversidad, nombre, pais, ranking);
    insertar(universidad);
}

// Recorre los nodos desde primero y compara sus IDs.
// Devuelve el dato encontrado o nullptr cuando no existe coincidencia.
NodoUniversidad* Universidad::buscarPorId(const std::string& idUniversidad) {
    NodoDoble<NodoUniversidad>* actual = primero;
    while (actual != nullptr) {
        if (actual->dato.idUniversidad == idUniversidad) {
            return &actual->dato;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Avanza por la lista doble mediante siguiente.
// Imprime cada universidad en el orden en que quedó enlazada.
void Universidad::imprimir() const{
    NodoDoble<NodoUniversidad>* actual = primero;
    while(actual != nullptr){
        std::cout << actual->dato.idUniversidad << " - "
                  << actual->dato.nombre << " - "
                  << actual->dato.pais << " - "
                  << actual->dato.ranking << '\n';
        actual = actual->siguiente;
    }
}
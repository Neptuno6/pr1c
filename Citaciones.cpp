#include "Citaciones.h"
#include <iostream>
#include <string>

// Recorre la lista original desde primero hasta nullptr.
// Crea cada citación en la nueva lista usando la validación de IDs.
Citaciones::Citaciones(const Citaciones& otra)
    : ListaDoble<NodoCitacion>() {
    NodoDoble<NodoCitacion>* actual = otra.primero;
    while (actual != nullptr) {
        insertar(actual->dato);
        actual = actual->siguiente;
    }
}

// Evita autoasignación y elimina todos los nodos actuales.
// Luego recorre otra lista y reconstruye cada citación en esta instancia.
Citaciones& Citaciones::operator=(const Citaciones& otra) {
    if (this == &otra) {
        return *this;
    }

    while (primero != nullptr) {
        NodoDoble<NodoCitacion>* siguiente = primero->siguiente;
        delete primero;
        primero = siguiente;
    }
    ultimo = nullptr;

    NodoDoble<NodoCitacion>* actual = otra.primero;
    while (actual != nullptr) {
        insertar(actual->dato);
        actual = actual->siguiente;
    }

    return *this;
}

// No realiza un recorrido propio porque la clase base posee los enlaces.
// El destructor heredado libera los nodos de la lista doble.
Citaciones::~Citaciones() = default;

// Busca la ID dentro de la lista antes de crear un nuevo enlace.
// Si no existe, agrega la citación al final y evita duplicados.
void Citaciones::insertar(const NodoCitacion& citacion) {
    // Las citaciones comparten un espacio de IDs y no pueden repetirse.
    if (buscarPorId(citacion.idCita) != nullptr) {
        std::cout << "Error: el IDC ya esta registrado.\n";
        return;
    }
    insertarAlFinal(citacion);
}

// Empaqueta los datos recibidos en un NodoCitacion.
// Delega la inserción para aplicar la misma validación que las demás rutas.
void Citaciones::insertar(const std::string& idCita, const int& annio, const std::string& enlacePublicacionEntrante, const std::string& enlaceAutorEntrante) {
    NodoCitacion citacion(idCita, annio, enlacePublicacionEntrante, enlaceAutorEntrante);
    insertar(citacion);
}

// Avanza desde primero comparando idCita en cada nodo.
// Devuelve un puntero al dato encontrado o nullptr si termina la lista.
NodoCitacion* Citaciones::buscarPorId(const std::string& idCita) {
    NodoDoble<NodoCitacion>* actual = primero;
    while (actual != nullptr) {
        if (actual->dato.idCita == idCita) return &actual->dato;
        actual = actual->siguiente;
    }
    return nullptr;
}

// Realiza la misma búsqueda en contexto constante.
// Se usa para validar IDs sin modificar la lista de citaciones.
NodoCitacion* Citaciones::buscarPorId(const std::string& idCita) const {
    NodoDoble<NodoCitacion>* actual = primero;
    while (actual != nullptr) {
        if (actual->dato.idCita == idCita) return &actual->dato;
        actual = actual->siguiente;
    }
    return nullptr;
}

// Recorre los nodos en orden y muestra año y referencias externas.
// El recorrido termina cuando el enlace siguiente llega a nullptr.
void Citaciones::imprimir() const {
    NodoDoble<NodoCitacion>* actual = primero;
    while (actual != nullptr) {
        std::cout << actual->dato.idCita << " - "
                  << actual->dato.annio << " - "
                  << actual->dato.enlacePublicacionEntrante << " - "
                  << actual->dato.enlaceAutorEntrante << '\n';
        actual = actual->siguiente;
    }
};
#include <iostream>
#include <string>

#include "AreaInvestigacion.h"

// Asigna la ID y los textos recibidos al nuevo nodo.
// El puntero siguiente comienza en nullptr porque todavía no pertenece a la lista.
NodoAreaInvestigacion::NodoAreaInvestigacion(int idA,const std::string& n, const std::string& d):
        idArea(idA), nombre(n),descripcion(d), siguiente(nullptr){}

// Busca primero una ID igual para evitar registros duplicados.
// Si la ID es válida, enlaza el nuevo nodo antes del actual primero.
void AreaInvestigacion::insertar(const NodoAreaInvestigacion& area) {
    if (buscarPorId(area.idArea) != nullptr) {
        std::cout << "Error: el ID del area ya esta registrado.\n";
        return;
    }
    NodoSimple<NodoAreaInvestigacion>* nuevo =
        new NodoSimple<NodoAreaInvestigacion>(area);
    nuevo->siguiente = primero;
    primero = nuevo;
}

// Construye un nodo temporal con los datos recibidos.
// Luego delega la inserción para reutilizar la validación de IDs.
void AreaInvestigacion::insertar(int idArea, const std::string& nombre, const std::string& descripcion) {
        NodoAreaInvestigacion area(idArea, nombre, descripcion);
        insertar(area);
    }

//Este metodo busca un área de investigación por su ID en la lista y devuelve un puntero al nodo correspondiente si se encuentra, o nullptr si no se encuentra.
// Avanza por la lista simple comparando la ID de cada nodo.
// Devuelve la dirección del área encontrada o nullptr cuando llega al final.
NodoAreaInvestigacion* AreaInvestigacion::buscarPorId(int idArea) {
    NodoSimple<NodoAreaInvestigacion>* actual = primero;
    while (actual != nullptr) {
        if (actual->dato.idArea == idArea) {
            return &actual->dato; //usamos & para devolver la dirección de memoria del nodo encontrado, ya que el método devuelve un puntero a NodoAreaInvestigacion.
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Busca el área mediante su ID antes de modificarla.
// Devuelve true si actualiza la descripción y false si no encuentra el nodo.
bool AreaInvestigacion::modificarDescripcion(int idArea, const std::string& descripcion) {
    NodoAreaInvestigacion* area = buscarPorId(idArea);
    if (area == nullptr) {
        return false;
    }
    area->descripcion = descripcion;
    return true;
}

// Recorre la lista hasta localizar el área que se desea eliminar.
// Ajusta primero o el enlace anterior y libera el nodo encontrado.
bool AreaInvestigacion::eliminar(int idArea) {
    NodoSimple<NodoAreaInvestigacion>* anterior = nullptr;
    NodoSimple<NodoAreaInvestigacion>* actual = primero;
    while (actual != nullptr && actual->dato.idArea != idArea) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == nullptr) {
        return false;
    }
    if (anterior == nullptr) {
        primero = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    delete actual;
    return true;
}

// Recorre desde el primer nodo siguiendo los enlaces siguiente.
// Imprime ID, nombre y descripción hasta llegar a nullptr.
void AreaInvestigacion::imprimir() const {
    NodoSimple<NodoAreaInvestigacion>* actual = primero;

    while (actual != nullptr) {
        std::cout << actual->dato.idArea << " - "
                  << actual->dato.nombre << " - "
                  << actual->dato.descripcion << '\n';
        actual = actual->siguiente;
    }
}

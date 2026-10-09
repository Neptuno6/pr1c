#include <iostream>
#include <string>   
#include "ProyectoInvestigacion.h"
#include "../ListasSimples/Investigador.h"

// Busca primero una IDPRO repetida antes de reservar memoria.
// Luego recorre por año de inicio y ajusta anterior y siguiente para insertarlo.
void ProyectoInvestigacion::insertar(const NodoProyecto& proyecto) {
    if (buscarPorId(proyecto.idProyecto) != nullptr) {
        std::cout << "Error: el IDPRO ya esta registrado.\n";
        return;
    }
    NodoDoble<NodoProyecto>* nuevo = new NodoDoble<NodoProyecto>(proyecto);

    if (primero == nullptr) {
        primero = nuevo;
        ultimo = nuevo;
        return;
    }

    NodoDoble<NodoProyecto>* actual = primero;
    while (actual != nullptr && actual->dato.AnnioInicio <= proyecto.AnnioInicio) {
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
        return;
    }

    nuevo->siguiente = actual;
    nuevo->anterior = actual->anterior;

    if (actual->anterior != nullptr) {
        actual->anterior->siguiente = nuevo;
    } else {
        primero = nuevo;
    }

    actual->anterior = nuevo;
}

// Construye un NodoProyecto con su posible responsable.
// La función principal decide la posición ordenada y actualiza los enlaces.
void ProyectoInvestigacion::insertar(
    const std::string& idProyecto, const std::string& nombre,
    const std::string& financimiento, const std::string& AnnioInicio,
    const std::string& AnnioFin, NodoInvestigador* responsable) {
    insertar(NodoProyecto(idProyecto, nombre, financimiento, AnnioInicio,
                          AnnioFin, responsable));
}

// Recorre desde primero comparando idProyecto en cada nodo.
// Devuelve el proyecto encontrado o nullptr cuando no existe.
NodoProyecto* ProyectoInvestigacion::buscarPorId(const std::string& idProyecto) {
    NodoDoble<NodoProyecto>* actual = primero;
    while (actual != nullptr) {
        if (actual->dato.idProyecto == idProyecto) {
            return &actual->dato;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Recorre proyectos y revisa el puntero del investigador responsable.
// Devuelve el primer proyecto relacionado con la ID recibida.
NodoProyecto* ProyectoInvestigacion::buscarPorInvestigadorResponsable(int idInvestigador) {
    NodoDoble<NodoProyecto>* actual = primero;
    while (actual != nullptr) {
        if (actual->dato.enlaceInvestigadorResponsable != nullptr &&
            actual->dato.enlaceInvestigadorResponsable->id == idInvestigador) {
            return &actual->dato;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Avanza por la lista y filtra usando el enlace del responsable.
// Imprime cada proyecto que coincide con el investigador indicado.
void ProyectoInvestigacion::imprimirPorInvestigadorResponsable(int idInvestigador) const {
    NodoDoble<NodoProyecto>* actual = primero;
    while (actual != nullptr) {
        if (actual->dato.enlaceInvestigadorResponsable != nullptr &&
            actual->dato.enlaceInvestigadorResponsable->id == idInvestigador) {
            std::cout << actual->dato.idProyecto << " - "
                      << actual->dato.nombre << " - Responsable: "
                      << actual->dato.enlaceInvestigadorResponsable->nombre << '\n';
        }
        actual = actual->siguiente;
    }
}

// Recorre todos los proyectos en su orden actual.
// Muestra los datos y reemplaza un responsable nulo por "Sin responsable".
void ProyectoInvestigacion::imprimir() const {
    NodoDoble<NodoProyecto>* actual = primero;
    while (actual != nullptr) {
        std::cout << actual->dato.idProyecto << " - "
                  << actual->dato.nombre << " - "
                  << actual->dato.financimiento << " - "
                  << actual->dato.AnnioInicio << " - "
                  << actual->dato.AnnioFin << " - Responsable: "
                  << (actual->dato.enlaceInvestigadorResponsable != nullptr
                      ? actual->dato.enlaceInvestigadorResponsable->nombre
                      : "Sin responsable")
                  << '\n';
        actual = actual->siguiente;
    }
}
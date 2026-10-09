#include "Investigador.h"
#include <iostream>

// Inicializa un investigador asignando sus datos y punteros de enlace.
// La lista de coautores comienza vacía para llenarse después.
NodoInvestigador::NodoInvestigador(
    int id, const std::string& n, NodoUniversidad* u, const std::string& p, NodoAreaInvestigacion* a,
    const std::string& c, int h)
    : id(id), nombre(n), universidad(u), pais(p), area(a), correo(c), indiceH(h), coautores() {}

// Inserta al final después de recorrer la lista y verificar que la ID no exista.
// Si encuentra un duplicado, muestra el error y conserva la lista intacta.
void Investigador::insertar(const NodoInvestigador& investigador) {
    // La lista rechaza IDs repetidas aunque la insercion venga de otro modulo.
    if (buscarPorId(investigador.id) != nullptr) {
        std::cout << "Error: el IDI ya esta registrado.\n";
        return;
    }
    insertarAlFinal(investigador);
}

// Crea el nodo con sus enlaces opcionales y lo pasa a la inserción validada.
// La función centraliza la comprobación de IDs antes de enlazarlo.
void Investigador::insertar(
    int id, const std::string& nombre,NodoUniversidad* universidad, const std::string& pais, NodoAreaInvestigacion* area,
    const std::string& correo, int indiceH) {
    NodoInvestigador investigador(id, nombre, universidad, pais, area, correo, indiceH);
    insertar(investigador);
}

// Crea el nodo dejando universidad y área en nullptr antes de insertarlo.
// Es la variante usada cuando esos vínculos se asignan posteriormente.
void Investigador::insertar(
    int id, const std::string& nombre, const std::string& pais,
    const std::string& correo, int indiceH) {
    insertar(id, nombre, nullptr, pais, nullptr, correo, indiceH);
}

// Recorre nodo por nodo y devuelve la dirección del investigador coincidente.
// Si llega al final sin coincidencia, devuelve nullptr.
NodoInvestigador* Investigador::buscarPorId(int id) {
    NodoSimple<NodoInvestigador>* actual = primero;
    while (actual != nullptr) {
        if (actual->dato.id == id) {
            return &actual->dato;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Busca el nodo por ID y modifica su campo país cuando lo encuentra.
// Devuelve true si actualizó el dato y false si no encontró la ID.
bool Investigador::modificarPais(int id, const std::string& pais) {
    NodoInvestigador* investigador = buscarPorId(id);
    if (investigador == nullptr) return false;
    investigador->pais = pais;
    return true;
}

// Recorre la lista, desconecta el nodo coincidente y lo libera con delete.
// También actualiza primero cuando se elimina el primer elemento.
bool Investigador::eliminar(int id) {
    NodoSimple<NodoInvestigador>* anterior = nullptr;
    NodoSimple<NodoInvestigador>* actual = primero;
    while (actual != nullptr && actual->dato.id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == nullptr) return false;
    if (anterior == nullptr) primero = actual->siguiente;
    else anterior->siguiente = actual->siguiente;
    delete actual;
    return true;
}

bool Investigador::existeCoautor(const std::string& idCoautor) const {
    // Recorre investigadores y sus sublistas para comparar todas las IDs de coautor.
    // Devuelve true en la primera coincidencia y false si termina todos los recorridos.
    NodoSimple<NodoInvestigador>* investigador = primero;
    while (investigador != nullptr) {
        NodoDoble<NodoCoautor>* coautor = investigador->dato.coautores.inicio();
        while (coautor != nullptr) {
            if (coautor->dato.idCoautor == idCoautor) return true;
            coautor = coautor->siguiente;
        }
        investigador = investigador->siguiente;
    }
    return false;
}

// Recorre investigadores, encuentra al responsable y delega el alta del coautor.
// El coautor recibe además el puntero de la universidad seleccionada.
void Investigador::agregarCoautor(
    int idInvestigador,
    const std::string& idCoautor,
    const std::string& nombre,
    int publicacionesConjuntas,
    NodoUniversidad* universidad) {
    NodoSimple<NodoInvestigador>* actual = primero;

    while (actual != nullptr) {
        if (actual->dato.id == idInvestigador) {
            actual->dato.coautores.insertar(
                idCoautor, nombre, universidad, publicacionesConjuntas);
            return;
        }
        actual = actual->siguiente;
    }
}

// Recorre investigadores, imprime sus datos y luego recorre sus coautores.
// Los enlaces nulos se representan con un texto descriptivo.
void Investigador::imprimir() const {
    NodoSimple<NodoInvestigador>* actual = primero;

    while (actual != nullptr) {
        std::cout << actual->dato.id << " - "
                  << actual->dato.nombre << " - "
                  << (actual->dato.universidad != nullptr ? actual->dato.universidad->nombre : "Sin universidad") << " - "
                  << actual->dato.pais << " - "
                  << (actual->dato.area != nullptr ? actual->dato.area->nombre : "Sin area") << " - "
                  << actual->dato.correo << " - h: "
                  << actual->dato.indiceH << '\n';
        actual->dato.coautores.imprimir();
        actual = actual->siguiente;
    }
}
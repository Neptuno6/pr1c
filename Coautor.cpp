#include "Coautor.h"
#include <iostream>
#include <string>

// Recorre la lista original desde primero hasta nullptr.
// Inserta copias de cada nodo para que ambas listas tengan memoria independiente.
Coautor::Coautor(const Coautor& otra)
    : ListaDoble<NodoCoautor>() {
    NodoDoble<NodoCoautor>* actual = otra.primero;
    while (actual != nullptr) {
        insertar(actual->dato);
        actual = actual->siguiente;
    }
}

// Evita autoasignarse y libera todos los nodos actuales.
// Después recorre la lista recibida y reconstruye sus coautores mediante inserciones.
Coautor& Coautor::operator=(const Coautor& otra) {
    if (this == &otra) {
        return *this;
    }

    while (primero != nullptr) {
        NodoDoble<NodoCoautor>* siguiente = primero->siguiente;
        delete primero;
        primero = siguiente;
    }
    ultimo = nullptr;

    NodoDoble<NodoCoautor>* actual = otra.primero;
    while (actual != nullptr) {
        insertar(actual->dato);
        actual = actual->siguiente;
    }

    return *this;
}

// Avanza con el enlace siguiente y libera cada nodo de la lista.
// Finalmente restablece primero y ultimo para evitar referencias pendientes.
Coautor::~Coautor() {
    while (primero != nullptr) {
        NodoDoble<NodoCoautor>* siguiente = primero->siguiente;
        delete primero;
        primero = siguiente;
    }
    ultimo = nullptr;
}

// Comprueba que la IDCO no exista antes de crear el nodo.
// Guarda directamente el puntero de la universidad seleccionada y lo enlaza al final.
void Coautor::insertar(
    const std::string& idCoautor,
    const std::string& nombre,
    NodoUniversidad* universidad,
    const int& publicacionesConjuntas) {
    if (buscarPorId(idCoautor) != nullptr) {
        std::cout << "Error: el IDCO ya esta registrado.\n";
        return;
    }
    NodoCoautor coautor(idCoautor, nombre, universidad, publicacionesConjuntas);
    insertarAlFinal(coautor);
}

// Permite crear un coautor sin universidad asignada.
// Reutiliza la función completa y envía nullptr como enlace opcional.
void Coautor::insertar(
    const std::string& idCoautor,
    const std::string& nombre,
    const int& publicacionesConjuntas) {
    insertar(idCoautor, nombre, nullptr, publicacionesConjuntas);
}

// Recibe un nodo ya construido y verifica nuevamente su ID.
// Si es única, lo agrega al final mediante los enlaces de la lista doble.
void Coautor::insertar(const NodoCoautor& coautor) {
    if (buscarPorId(coautor.idCoautor) != nullptr) {
        std::cout << "Error: el IDCO ya esta registrado.\n";
        return;
    }
    insertarAlFinal(coautor);
}

// Recorre los nodos y compara idCoautor con la búsqueda solicitada.
// Devuelve el dato encontrado para que otros módulos puedan usarlo o modificarlo.
NodoCoautor* Coautor::buscarPorId(const std::string& idCoautor) {
    NodoDoble<NodoCoautor>* actual = primero;
    while (actual != nullptr) {
        if (actual->dato.idCoautor == idCoautor) {
            return &actual->dato;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Avanza por toda la lista e imprime cada coautor y sus publicaciones conjuntas.
// Si el puntero de universidad es nulo, muestra "Sin universidad".
void Coautor::imprimir() const{
    NodoDoble<NodoCoautor>* actual = primero;
    while(actual != nullptr){
        std::cout << actual->dato.idCoautor << " - "
                  << actual->dato.nombre << " - "
                  << (actual->dato.universidad != nullptr
                          ? actual->dato.universidad->nombre
                          : "Sin universidad") << " - "
                  << actual->dato.publicacionesConjuntas << '\n';
        actual = actual->siguiente;
    }
}
#include "ListaCircular.h"

#include <algorithm>
#include <iostream>
#include <vector>

// Libera cada nodo avanzando por la lista circular hasta regresar al primero.
// Luego elimina el nodo inicial y deja la lista en estado vacío.
ListaCircular::~ListaCircular() {
    if (primero == nullptr) {
        return;
    }

    NodoCircular* actual = primero->siguiente;
    while (actual != primero) {
        NodoCircular* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }

    delete primero;
    primero = nullptr;
}

// Compara el año para ubicar la publicación y busca antes una ID repetida.
// Ajusta los enlaces siguiente para conservar el orden circular.
void ListaCircular::insertar(const NodoCircular& publicacion) {
    if (buscarPorId(publicacion.idPublicacion) != nullptr) {
        std::cout << "Error: el IDPUB ya esta registrado.\n";
        return;
    }
    NodoCircular* nuevo = new NodoCircular(publicacion);

    if (primero == nullptr) {
        primero = nuevo;
        nuevo->siguiente = nuevo;
        return;
    }

    if (publicacion.annio < primero->annio) {
        NodoCircular* ultimo = primero;
        while (ultimo->siguiente != primero) {
            ultimo = ultimo->siguiente;
        }

        nuevo->siguiente = primero;
        ultimo->siguiente = nuevo;
        primero = nuevo;
        return;
    }

    NodoCircular* actual = primero;
    while (actual->siguiente != primero &&
           actual->siguiente->annio <= publicacion.annio) {
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}

// Construye el nodo y delega su validación y ordenamiento a la otra inserción.
// Así se mantiene una sola ruta para controlar duplicados y enlaces.
void ListaCircular::insertar(
    const std::string& idPublicacion, const std::string& titulo, int annio,
    const std::string& tipo, int cantidadCitas, const std::string& doi,
    NodoInvestigador* enlaceInvestigador, NodoRevista* enlaceRevista,
    NodoProyecto* enlaceProyecto, const Citaciones& citaciones, int cantidadAutores) {
    insertar(NodoCircular(idPublicacion, titulo, annio, tipo, cantidadCitas, doi,
                          enlaceInvestigador, enlaceRevista, enlaceProyecto, citaciones,
                          cantidadAutores));
}

// Compara la ID mientras avanza nodo por nodo hasta completar el ciclo.
// Devuelve el puntero encontrado o nullptr cuando no existe.
NodoCircular* ListaCircular::buscarPorId(const std::string& idPublicacion) {
    if (primero == nullptr) {
        return nullptr;
    }

    NodoCircular* actual = primero;
    do {
        if (actual->idPublicacion == idPublicacion) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != primero);

    return nullptr;
}

// Recorre el ciclo y devuelve el primer nodo cuyo puntero de investigador coincide.
// La comparación se hace sobre la ID del investigador enlazado.
NodoCircular* ListaCircular::buscarPorInvestigador(int idInvestigador) {
    if (primero == nullptr) {
        return nullptr;
    }

    NodoCircular* actual = primero;
    do {
        if (actual->enlaceInvestigador != nullptr &&
            actual->enlaceInvestigador->id == idInvestigador) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != primero);

    return nullptr;
}

// Ordena las citas del investigador y calcula el mayor índice H válido.
int ListaCircular::calcularIndiceH(int idInvestigador) const {
    // Reúne las citas, las ordena de mayor a menor y compara cada posición con h.
    // El último valor válido representa el índice H calculado.
    std::vector<int> citas;

    if (primero == nullptr) {
        return 0;
    }

    const NodoCircular* actual = primero;
    do {
        if (actual->enlaceInvestigador != nullptr &&
            actual->enlaceInvestigador->id == idInvestigador) {
            citas.push_back(actual->cantidadCitas);
        }

        actual = actual->siguiente;
    } while (actual != primero);

    std::sort(citas.begin(), citas.end(), std::greater<int>());

    int indiceH = 0;
    for (std::size_t i = 0; i < citas.size(); ++i) {
        if (citas[i] >= static_cast<int>(i + 1)) {
            indiceH = static_cast<int>(i + 1);
        } else {
            break;
        }
    }

    return indiceH;
}

// Recorre el ciclo y muestra solo los nodos cuyo enlace coincide con la ID.
// El recorrido termina al regresar al primer nodo para evitar repeticiones.
void ListaCircular::imprimirPorInvestigador(int idInvestigador) const {
    if (primero == nullptr) {
        return;
    }

    const NodoCircular* actual = primero;
    do {
        if (actual->enlaceInvestigador != nullptr &&
            actual->enlaceInvestigador->id == idInvestigador) {
            std::cout << "ID publicacion: " << actual->idPublicacion << " - "
                      << actual->titulo << " - "
                      << actual->annio << " - "
                      << actual->tipo << " - citas: "
                      << actual->cantidadCitas << '\n';
        }
        actual = actual->siguiente;
    } while (actual != primero);
}

// Recorre enlaces de investigador y área hasta encontrar una coincidencia.
// Devuelve la primera publicación vinculada con el área solicitada.
NodoCircular* ListaCircular::buscarPorArea(int idArea) {
    if (primero == nullptr) {
        return nullptr;
    }

    NodoCircular* actual = primero;
    do {
        if (actual->enlaceInvestigador != nullptr &&
            actual->enlaceInvestigador->area != nullptr &&
            actual->enlaceInvestigador->area->idArea == idArea) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != primero);

    return nullptr;
}

// Compara el enlace de revista de cada nodo hasta encontrar la ID solicitada.
// Si no hay coincidencia, completa el ciclo y devuelve nullptr.
NodoCircular* ListaCircular::buscarPorRevista(int idRevista) {
    if (primero == nullptr) {
        return nullptr;
    }

    NodoCircular* actual = primero;
    do {
        if (actual->enlaceRevista != nullptr &&
            actual->enlaceRevista->idRevista == idRevista) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != primero);

    return nullptr;
}

// Recorre la lista circular y muestra los nodos enlazados a la revista.
// Cada publicación se imprime solo una vez.
void ListaCircular::imprimirPorRevista(int idRevista) const {
    if (primero == nullptr) {
        return;
    }

    const NodoCircular* actual = primero;
    do {
        if (actual->enlaceRevista != nullptr &&
            actual->enlaceRevista->idRevista == idRevista) {
            std::cout << "ID publicacion: " << actual->idPublicacion << " - "
                      << actual->titulo << '\n';
        }
        actual = actual->siguiente;
    } while (actual != primero);
}

// Avanza por el ciclo comparando el proyecto enlazado en cada publicación.
// Devuelve la primera publicación asociada con ese proyecto.
NodoCircular* ListaCircular::buscarPorProyecto(const std::string& idProyecto) {
    if (primero == nullptr) {
        return nullptr;
    }

    NodoCircular* actual = primero;
    do {
        if (actual->enlaceProyecto != nullptr &&
            actual->enlaceProyecto->idProyecto == idProyecto) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != primero);

    return nullptr;
}

// Busca la publicación, valida la ID global y luego inserta e incrementa el contador.
// Si falla alguna validación, conserva la cantidad de citas sin cambios.
bool ListaCircular::agregarCitacion(
    const std::string& idPublicacion, const NodoCitacion& citacion) {
    NodoCircular* publicacion = buscarPorId(idPublicacion);
    if (publicacion == nullptr || existeCitacion(citacion.idCita)) {
        return false;
    }

    publicacion->citaciones.insertar(citacion);
    ++publicacion->cantidadCitas;
    return true;
}

// Recorre publicaciones y sus sublistas de citaciones comparando cada ID.
// Esto evita que una misma citación se registre en dos publicaciones.
bool ListaCircular::existeCitacion(const std::string& idCita) const {
    if (primero == nullptr) return false;
    const NodoCircular* publicacion = primero;
    do {
        if (publicacion->citaciones.buscarPorId(idCita) != nullptr) return true;
        publicacion = publicacion->siguiente;
    } while (publicacion != primero);
    return false;
}

// Avanza desde el primer nodo y se detiene al regresar a él para no repetir datos.
// Cada línea muestra los datos básicos almacenados en la publicación.
void ListaCircular::imprimir() const {
    if (primero == nullptr) {
        return;
    }

    const NodoCircular* actual = primero;
    do {
        std::cout << "ID publicacion: " << actual->idPublicacion << " - "
                  << actual->titulo << " - "
                  << actual->annio << " - "
                  << actual->tipo << " - citas: "
                  << actual->cantidadCitas << '\n';
        actual = actual->siguiente;
    } while (actual != primero);
}
#include "Reportes.h"

#include "Entrada.h"
#include <iostream>

namespace {

// Recorre investigadores y delega en la lista circular el filtro por investigador.
// Cada bloque de salida reúne las publicaciones del investigador actual.
void reporteInvestigadoresPublicaciones(const Investigador& investigadores, const ListaCircular& publicaciones) {
    NodoSimple<NodoInvestigador>* investigador = investigadores.inicio();
    while (investigador != nullptr) {
        std::cout << "\nID investigador: " << investigador->dato.id
                  << " - " << investigador->dato.nombre << ":\n";
        publicaciones.imprimirPorInvestigador(investigador->dato.id);
        investigador = investigador->siguiente;
    }
}

// Copia punteros a un arreglo, los ordena por citas y luego imprime el arreglo.
// Los nodos originales no se mueven; solo se ordenan sus direcciones.
void reportePublicacionesPorCitas(const ListaCircular& publicaciones) {
    NodoCircular* primero = publicaciones.inicio();
    if (primero == nullptr) { std::cout << "No hay publicaciones.\n"; return; }
    int cantidad = 0; NodoCircular* actual = primero;
    do { ++cantidad; actual = actual->siguiente; } while (actual != primero);
    // Se ordenan punteros en un arreglo dinamico para respetar la restriccion sin STL.
    NodoCircular** ordenadas = new NodoCircular*[cantidad];
    actual = primero;
    for (int i = 0; i < cantidad; ++i) { ordenadas[i] = actual; actual = actual->siguiente; }
    for (int i = 0; i < cantidad - 1; ++i) {
        int mayor = i;
        for (int j = i + 1; j < cantidad; ++j) {
            if (ordenadas[j]->cantidadCitas > ordenadas[mayor]->cantidadCitas) mayor = j;
        }
        NodoCircular* temporal = ordenadas[i]; ordenadas[i] = ordenadas[mayor]; ordenadas[mayor] = temporal;
    }
    for (int i = 0; i < cantidad; ++i) {
        std::cout << "ID publicacion: " << ordenadas[i]->idPublicacion
                  << " - " << ordenadas[i]->titulo << " - "
                  << ordenadas[i]->cantidadCitas << " citas\n";
    }
    delete[] ordenadas;
}

// Llama al método de la lista, que controla internamente el ciclo circular.
void reporteRevistas(const RevistaCientifica& revistas) {
    revistas.imprimir();
}

// Recorre investigadores hasta la ID solicitada y delega la impresión de coautores.
void reporteRedCoautores(const Investigador& investigadores) {
    int id = leerEntero("ID del investigador: ");
    NodoSimple<NodoInvestigador>* actual = investigadores.inicio();
    while (actual != nullptr && actual->dato.id != id) actual = actual->siguiente;
    if (actual == nullptr) { std::cout << "Investigador no encontrado.\n"; return; }
    actual->dato.coautores.imprimir();
}

// Recorre la lista circular y muestra nodos cuyo enlace de revista coincide.
void reportePublicacionesRevista(const ListaCircular& publicaciones, int idRevista) {
    NodoCircular* primero = publicaciones.inicio();
    if (primero == nullptr) return;
    NodoCircular* actual = primero;
    do {
        if (actual->enlaceRevista != nullptr && actual->enlaceRevista->idRevista == idRevista) {
            std::cout << actual->titulo << " - " << actual->annio << "\n";
        }
        actual = actual->siguiente;
    } while (actual != primero);
}

// Recorre enlaces de investigador y área y muestra las coincidencias.
void reportePublicacionesArea(const ListaCircular& publicaciones, int idArea) {
    NodoCircular* primero = publicaciones.inicio();
    if (primero == nullptr) return;
    NodoCircular* actual = primero;
    do {
        if (actual->enlaceInvestigador != nullptr && actual->enlaceInvestigador->area != nullptr &&
            actual->enlaceInvestigador->area->idArea == idArea) {
            std::cout << actual->titulo << " - " << actual->annio << "\n";
        }
        actual = actual->siguiente;
    } while (actual != primero);
}

// Recorre universidades y, para cada una, filtra investigadores por su puntero.
void reportePorUniversidad(const Investigador& investigadores, const Universidad& universidades) {
    NodoDoble<NodoUniversidad>* universidad = universidades.inicio();
    while (universidad != nullptr) {
        std::cout << "\n" << universidad->dato.nombre << ":\n";
        NodoSimple<NodoInvestigador>* investigador = investigadores.inicio();
        while (investigador != nullptr) {
            if (investigador->dato.universidad != nullptr &&
                investigador->dato.universidad->idUniversidad == universidad->dato.idUniversidad) {
                std::cout << "- " << investigador->dato.nombre << "\n";
            }
            investigador = investigador->siguiente;
        }
        universidad = universidad->siguiente;
    }
}

// Ordena punteros comparando el índice H calculado para cada investigador.
// El cálculo se hace en el momento usando las citas de sus publicaciones.
void reporteInvestigadoresPorH(const Investigador& investigadores, const ListaCircular& publicaciones) {
    int cantidad = 0; NodoSimple<NodoInvestigador>* actual = investigadores.inicio();
    while (actual != nullptr) { ++cantidad; actual = actual->siguiente; }
    if (cantidad == 0) { std::cout << "No hay investigadores.\n"; return; }
    NodoInvestigador** ordenados = new NodoInvestigador*[cantidad];
    actual = investigadores.inicio();
    for (int i = 0; i < cantidad; ++i) { ordenados[i] = &actual->dato; actual = actual->siguiente; }
    for (int i = 0; i < cantidad - 1; ++i) {
        int mayor = i;
        for (int j = i + 1; j < cantidad; ++j) {
            if (publicaciones.calcularIndiceH(ordenados[j]->id) >
                publicaciones.calcularIndiceH(ordenados[mayor]->id)) mayor = j;
        }
        NodoInvestigador* temporal = ordenados[i]; ordenados[i] = ordenados[mayor]; ordenados[mayor] = temporal;
    }
    for (int i = 0; i < cantidad; ++i) {
        std::cout << ordenados[i]->nombre << " - h="
                  << publicaciones.calcularIndiceH(ordenados[i]->id) << "\n";
    }
    delete[] ordenados;
}

} // namespace

// Muestra opciones, ejecuta el reporte elegido y repite hasta seleccionar volver.
// Después de cada reporte pausa la terminal para que el resultado sea legible.
void menuReportes(Investigador& investigadores, RevistaCientifica& revistas,
                  AreaInvestigacion&, Universidad& universidades,
                  ListaCircular& publicaciones) {
    char opcion;
    do {
        std::cout << "\n=== Reportes del sistema ===\n"
                  << "1. Investigadores con sus publicaciones\n2. Publicaciones por año ascendente\n"
                  << "3. Publicaciones por citas descendente\n4. Revistas y factores de impacto\n"
                  << "5. Red de coautores\n6. Publicaciones de una revista\n"
                  << "7. Publicaciones de un area\n8. Investigadores por universidad\n"
                  << "9. Investigadores por indice H\n0. Volver\n";
        opcion = leerOpcion("Opcion: ");
        switch (opcion) {
        case '1': reporteInvestigadoresPublicaciones(investigadores, publicaciones); break;
        case '2': publicaciones.imprimir(); break;
        case '3': reportePublicacionesPorCitas(publicaciones); break;
        case '4': reporteRevistas(revistas); break;
        case '5': reporteRedCoautores(investigadores); break;
        case '6': reportePublicacionesRevista(publicaciones, leerEntero("ID revista: ")); break;
        case '7': reportePublicacionesArea(publicaciones, leerEntero("ID area: ")); break;
        case '8': reportePorUniversidad(investigadores, universidades); break;
        case '9': reporteInvestigadoresPorH(investigadores, publicaciones); break;
        case '0': break;
        default: std::cout << "Opcion no valida.\n";
        }
        if (opcion != '0') pausarPantalla();
    } while (opcion != '0');
}

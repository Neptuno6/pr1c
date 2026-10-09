#include "Consultas.h"

#include "Entrada.h"
#include <cctype>
#include <iostream>
#include <stdexcept>

namespace {

// Las consultas recorren las listas propias y muestran todos los empates.
// Recorre publicaciones y suma cantidadCitas cuando coincide el investigador.
// Devuelve cero si la lista está vacía o no encuentra publicaciones enlazadas.
int citasDeInvestigador(const ListaCircular& publicaciones, int id) {
    int total = 0;
    NodoCircular* primero = publicaciones.inicio();
    if (primero == nullptr) return 0;
    NodoCircular* actual = primero;
    do {
        if (actual->enlaceInvestigador != nullptr && actual->enlaceInvestigador->id == id) {
            total += actual->cantidadCitas;
        }
        actual = actual->siguiente;
    } while (actual != primero);
    return total;
}

// Recorre enlaces de investigador y área y aumenta el contador por coincidencia.
// Así calcula cuántas publicaciones pertenecen al área indicada.
int publicacionesDeArea(const ListaCircular& publicaciones, int idArea) {
    int total = 0;
    NodoCircular* primero = publicaciones.inicio();
    if (primero == nullptr) return 0;
    NodoCircular* actual = primero;
    do {
        if (actual->enlaceInvestigador != nullptr && actual->enlaceInvestigador->area != nullptr &&
            actual->enlaceInvestigador->area->idArea == idArea) ++total;
        actual = actual->siguiente;
    } while (actual != primero);
    return total;
}

// Recorre la lista circular y cuenta los nodos con el año recibido.
// Se detiene al volver al primer nodo para no contar elementos dos veces.
int publicacionesDeAño(const ListaCircular& publicaciones, int año) {
    int total = 0;
    NodoCircular* primero = publicaciones.inicio();
    if (primero == nullptr) return 0;
    NodoCircular* actual = primero;
    do {
        if (actual->annio == año) ++total;
        actual = actual->siguiente;
    } while (actual != primero);
    return total;
}

// Recorre desde el inicio hasta el nodo actual para detectar un año previo.
bool añoYaRecorrido(const NodoCircular* primero, const NodoCircular* actual) {
    const NodoCircular* recorrido = primero;
    while (recorrido != actual) {
        if (recorrido->annio == actual->annio) return true;
        recorrido = recorrido->siguiente;
    }
    return false;
}

// Busca al investigador y recorre su sublista para contar los coautores.
int coautoresDeInvestigador(const Investigador& investigadores, int id) {
    NodoSimple<NodoInvestigador>* actual = investigadores.inicio();
    while (actual != nullptr) {
        if (actual->dato.id == id) {
            int total = 0;
            NodoDoble<NodoCoautor>* coautor = actual->dato.coautores.inicio();
            while (coautor != nullptr) {
                ++total;
                coautor = coautor->siguiente;
            }
            return total;
        }
        actual = actual->siguiente;
    }
    return 0;
}

// Recorre investigadores y compara la ID de su universidad enlazada.
int investigadoresDeUniversidad(const Investigador& investigadores, const std::string& id) {
    int total = 0;
    NodoSimple<NodoInvestigador>* actual = investigadores.inicio();
    while (actual != nullptr) {
        if (actual->dato.universidad != nullptr && actual->dato.universidad->idUniversidad == id) ++total;
        actual = actual->siguiente;
    }
    return total;
}

// Recorre publicaciones y suma las que coinciden con investigador y cuartil Q1.
int publicacionesQ1DeInvestigador(const ListaCircular& publicaciones, int id) {
    int total = 0;
    NodoCircular* primero = publicaciones.inicio();
    if (primero == nullptr) return 0;
    NodoCircular* actual = primero;
    do {
        if (actual->enlaceInvestigador != nullptr && actual->enlaceInvestigador->id == id &&
            actual->enlaceRevista != nullptr && actual->enlaceRevista->Cuartil == "Q1") ++total;
        actual = actual->siguiente;
    } while (actual != primero);
    return total;
}

// Calcula H para cada investigador, conserva el máximo y vuelve a recorrer para empates.
// El valor proviene de las citas reales de sus publicaciones.
void consultaMayorIndiceH(const Investigador& investigadores, const ListaCircular& publicaciones) {
    int maximo = -1;
    NodoSimple<NodoInvestigador>* actual = investigadores.inicio();
    while (actual != nullptr) { int indiceH = publicaciones.calcularIndiceH(actual->dato.id); if (indiceH > maximo) maximo = indiceH; actual = actual->siguiente; }
    if (maximo < 0) { std::cout << "No hay investigadores.\n"; return; }
    actual = investigadores.inicio();
    while (actual != nullptr) { if (publicaciones.calcularIndiceH(actual->dato.id) == maximo) std::cout << actual->dato.nombre << " (h=" << maximo << ")\n"; actual = actual->siguiente; }
}

// Calcula citas por investigador, conserva el máximo y muestra los empates.
void consultaMasCitas(const Investigador& investigadores, const ListaCircular& publicaciones) {
    int maximo = -1; NodoSimple<NodoInvestigador>* actual = investigadores.inicio();
    while (actual != nullptr) { int total = citasDeInvestigador(publicaciones, actual->dato.id); if (total > maximo) maximo = total; actual = actual->siguiente; }
    if (maximo < 0) { std::cout << "No hay investigadores.\n"; return; }
    actual = investigadores.inicio();
    while (actual != nullptr) { if (citasDeInvestigador(publicaciones, actual->dato.id) == maximo) std::cout << actual->dato.nombre << " (" << maximo << " citas)\n"; actual = actual->siguiente; }
}

// Recorre para hallar el máximo y vuelve a recorrer para mostrar coincidencias.
void consultaPublicacionMasCitas(const ListaCircular& publicaciones) {
    NodoCircular* primero = publicaciones.inicio();
    if (primero == nullptr) { std::cout << "No hay publicaciones.\n"; return; }
    int maximo = primero->cantidadCitas; NodoCircular* actual = primero;
    do { if (actual->cantidadCitas > maximo) maximo = actual->cantidadCitas; actual = actual->siguiente; } while (actual != primero);
    actual = primero; do { if (actual->cantidadCitas == maximo) std::cout << actual->titulo << " (" << maximo << " citas)\n"; actual = actual->siguiente; } while (actual != primero);
}

// Recorre la lista circular para hallar el máximo y mostrar sus coincidencias.
void consultaRevistaMayorImpacto(const RevistaCientifica& revistas) {
    NodoSimple<NodoRevista>* primero = revistas.inicio();
    if (primero == nullptr) { std::cout << "No hay revistas.\n"; return; }
    int maximo = primero->dato.FactorImpacto;
    NodoSimple<NodoRevista>* actual = primero->siguiente;
    while (actual != primero) {
        if (actual->dato.FactorImpacto > maximo) maximo = actual->dato.FactorImpacto;
        actual = actual->siguiente;
    }
    actual = primero;
    do {
        if (actual->dato.FactorImpacto == maximo) std::cout << actual->dato.nombre << " (" << maximo << ")\n";
        actual = actual->siguiente;
    } while (actual != primero);
}

// Cuenta coautores por investigador, conserva el máximo y muestra los empates.
void consultaMasCoautores(const Investigador& investigadores) {
    NodoSimple<NodoInvestigador>* actual = investigadores.inicio();
    if (actual == nullptr) { std::cout << "No hay investigadores.\n"; return; }
    int maximo = coautoresDeInvestigador(investigadores, actual->dato.id);
    while (actual != nullptr) { int total = coautoresDeInvestigador(investigadores, actual->dato.id); if (total > maximo) maximo = total; actual = actual->siguiente; }
    actual = investigadores.inicio(); while (actual != nullptr) { if (coautoresDeInvestigador(investigadores, actual->dato.id) == maximo) std::cout << actual->dato.nombre << " (" << maximo << ")\n"; actual = actual->siguiente; }
}

// Cuenta enlaces por universidad, conserva el máximo y muestra las coincidencias.
void consultaUniversidadMasInvestigadores(const Investigador& investigadores, const Universidad& universidades) {
    NodoDoble<NodoUniversidad>* actual = universidades.inicio();
    if (actual == nullptr) { std::cout << "No hay universidades.\n"; return; }
    int maximo = investigadoresDeUniversidad(investigadores, actual->dato.idUniversidad);
    while (actual != nullptr) { int total = investigadoresDeUniversidad(investigadores, actual->dato.idUniversidad); if (total > maximo) maximo = total; actual = actual->siguiente; }
    actual = universidades.inicio(); while (actual != nullptr) { if (investigadoresDeUniversidad(investigadores, actual->dato.idUniversidad) == maximo) std::cout << actual->dato.nombre << " (" << maximo << ")\n"; actual = actual->siguiente; }
}

// Cuenta publicaciones por área, conserva el máximo y muestra las coincidencias.
void consultaAreaMasPublicaciones(const AreaInvestigacion& areas, const ListaCircular& publicaciones) {
    NodoSimple<NodoAreaInvestigacion>* actual = areas.inicio();
    if (actual == nullptr) { std::cout << "No hay areas.\n"; return; }
    int maximo = publicacionesDeArea(publicaciones, actual->dato.idArea);
    while (actual != nullptr) { int total = publicacionesDeArea(publicaciones, actual->dato.idArea); if (total > maximo) maximo = total; actual = actual->siguiente; }
    actual = areas.inicio(); while (actual != nullptr) { if (publicacionesDeArea(publicaciones, actual->dato.idArea) == maximo) std::cout << actual->dato.nombre << " (" << maximo << ")\n"; actual = actual->siguiente; }
}

// Cuenta publicaciones por año y evita repetir años al imprimir el máximo.
void consultaAñoMasProduccion(const ListaCircular& publicaciones) {
    NodoCircular* primero = publicaciones.inicio();
    if (primero == nullptr) { std::cout << "No hay publicaciones.\n"; return; }
    int maximo = 0; NodoCircular* actual = primero;
    do { int total = publicacionesDeAño(publicaciones, actual->annio); if (total > maximo) maximo = total; actual = actual->siguiente; } while (actual != primero);
    actual = primero;
    do {
        if (!añoYaRecorrido(primero, actual) &&
            publicacionesDeAño(publicaciones, actual->annio) == maximo) {
            std::cout << actual->annio << " (" << maximo << ")\n";
        }
        actual = actual->siguiente;
    } while (actual != primero);
}

// Recorre para hallar la cantidad máxima y luego muestra sus publicaciones.
void consultaPublicacionMasAutores(const ListaCircular& publicaciones) {
    NodoCircular* primero = publicaciones.inicio();
    if (primero == nullptr) { std::cout << "No hay publicaciones.\n"; return; }
    int maximo = primero->cantidadAutores; NodoCircular* actual = primero;
    do { if (actual->cantidadAutores > maximo) maximo = actual->cantidadAutores; actual = actual->siguiente; } while (actual != primero);
    actual = primero; do { if (actual->cantidadAutores == maximo) std::cout << actual->titulo << " (" << maximo << " autores)\n"; actual = actual->siguiente; } while (actual != primero);
}

// Cuenta Q1 por investigador, conserva el máximo y muestra los empates.
void consultaMasQ1(const Investigador& investigadores, const ListaCircular& publicaciones) {
    NodoSimple<NodoInvestigador>* actual = investigadores.inicio();
    if (actual == nullptr) { std::cout << "No hay investigadores.\n"; return; }
    int maximo = publicacionesQ1DeInvestigador(publicaciones, actual->dato.id);
    while (actual != nullptr) { int total = publicacionesQ1DeInvestigador(publicaciones, actual->dato.id); if (total > maximo) maximo = total; actual = actual->siguiente; }
    actual = investigadores.inicio(); while (actual != nullptr) { if (publicacionesQ1DeInvestigador(publicaciones, actual->dato.id) == maximo) std::cout << actual->dato.nombre << " (" << maximo << ")\n"; actual = actual->siguiente; }
}

// Recorre los caracteres y los convierte a mayúsculas antes de comparar.
// Esto permite aceptar entradas como idi6 o IDI6.
std::string aMayusculas(std::string texto) {
    // Permite buscar IDs sin importar si el usuario escribe prefijos en minuscula.
    for (char& caracter : texto) {
        caracter = static_cast<char>(std::toupper(static_cast<unsigned char>(caracter)));
    }
    return texto;
}

// Comprueba el prefijo, convierte el sufijo a entero y rechaza formatos inválidos.
// Usa la posición convertida para asegurar que no sobren caracteres.
bool obtenerNumeroId(const std::string& idCompleta, const std::string& prefijo, int& numero) {
    // Comprueba el prefijo y extrae el numero para consultar la lista correspondiente.
    if (idCompleta.rfind(prefijo, 0) != 0 || idCompleta.size() == prefijo.size()) return false;
    try {
        std::size_t posicion = 0;
        numero = std::stoi(idCompleta.substr(prefijo.size()), &posicion);
        return posicion == idCompleta.size() - prefijo.size() && numero > 0;
    } catch (const std::exception&) {
        return false;
    }
}

// Busca una ID en entidades principales y también en coautores o citaciones.
// Primero identifica el prefijo y luego recorre la lista o sublista adecuada.
void buscarIdUniversal(const Investigador& investigadores,
                       const RevistaCientifica& revistas,
                       const AreaInvestigacion& areas,
                       const Universidad& universidades,
                       const ProyectoInvestigacion& proyectos,
                       const ListaCircular& publicaciones) {
    // Separa prefijo y número, selecciona la lista correspondiente y recorre sublistas.
    std::string id = aMayusculas(leerTexto("ID (ejemplo IDI6): "));
    int numero = 0;

    // Un prefijo sin número selecciona la lista y recorre todos sus elementos.
    if (id == "IDI") investigadores.imprimir();
    else if (id == "IDA") areas.imprimir();
    else if (id == "IDR") revistas.imprimir();
    else if (id == "IDU") universidades.imprimir();
    else if (id == "IDPRO") proyectos.imprimir();
    else if (id == "IDPUB") publicaciones.imprimir();
    else if (id == "IDCO") {
        // Los coautores están anidados dentro de cada investigador.
        NodoSimple<NodoInvestigador>* investigador = investigadores.inicio();
        while (investigador != nullptr) {
            investigador->dato.coautores.imprimir();
            investigador = investigador->siguiente;
        }
    } else if (id == "IDC") {
        // Las citaciones están anidadas dentro de cada publicación circular.
        NodoCircular* primero = publicaciones.inicio();
        if (primero != nullptr) {
            NodoCircular* publicacion = primero;
            do {
                publicacion->citaciones.imprimir();
                publicacion = publicacion->siguiente;
            } while (publicacion != primero);
        }
    }
    if (id == "IDI" || id == "IDA" || id == "IDR" || id == "IDU" ||
        id == "IDPRO" || id == "IDPUB" || id == "IDCO" || id == "IDC") {
        return;
    }

    if (obtenerNumeroId(id, "IDI", numero)) {
        NodoSimple<NodoInvestigador>* investigador = investigadores.inicio();
        while (investigador != nullptr && investigador->dato.id != numero) investigador = investigador->siguiente;
        if (investigador != nullptr) {
            std::cout << "Encontrado: " << id << " - Investigador: " << investigador->dato.nombre << '\n';
            return;
        }
    } else if (obtenerNumeroId(id, "IDA", numero)) {
        NodoSimple<NodoAreaInvestigacion>* area = areas.inicio();
        while (area != nullptr && area->dato.idArea != numero) area = area->siguiente;
        if (area != nullptr) {
            std::cout << "Encontrado: " << id << " - Area: " << area->dato.nombre << '\n';
            return;
        }
    } else if (obtenerNumeroId(id, "IDR", numero)) {
        NodoSimple<NodoRevista>* revista = revistas.inicio();
        while (revista != nullptr && revista->dato.idRevista != numero) revista = revista->siguiente;
        if (revista != nullptr) {
            std::cout << "Encontrado: " << id << " - Revista: " << revista->dato.nombre << '\n';
            return;
        }
    } else if (obtenerNumeroId(id, "IDU", numero)) {
        NodoDoble<NodoUniversidad>* universidad = universidades.inicio();
        std::string idUniversidad = "U" + std::to_string(numero);
        while (universidad != nullptr && universidad->dato.idUniversidad != idUniversidad) universidad = universidad->siguiente;
        if (universidad != nullptr) {
            std::cout << "Encontrado: " << id << " - Universidad: " << universidad->dato.nombre << '\n';
            return;
        }
    } else if (obtenerNumeroId(id, "IDPRO", numero)) {
        NodoDoble<NodoProyecto>* proyecto = proyectos.inicio();
        std::string idProyecto = "P" + std::to_string(numero);
        while (proyecto != nullptr && proyecto->dato.idProyecto != idProyecto) proyecto = proyecto->siguiente;
        if (proyecto != nullptr) {
            std::cout << "Encontrado: " << id << " - Proyecto: " << proyecto->dato.nombre << '\n';
            return;
        }
    } else if (obtenerNumeroId(id, "IDPUB", numero)) {
        std::string idPublicacion = "PUB" + std::to_string(numero);
        NodoCircular* primero = publicaciones.inicio();
        if (primero != nullptr) {
            NodoCircular* publicacion = primero;
            do {
                if (publicacion->idPublicacion == idPublicacion) {
                    std::cout << "Encontrado: " << id << " - Publicacion: " << publicacion->titulo << '\n';
                    return;
                }
                publicacion = publicacion->siguiente;
            } while (publicacion != primero);
        }
    } else if (obtenerNumeroId(id, "IDCO", numero)) {
        std::string idCoautor = "CA" + std::to_string(numero);
        NodoSimple<NodoInvestigador>* investigador = investigadores.inicio();
        while (investigador != nullptr) {
            NodoDoble<NodoCoautor>* coautor = investigador->dato.coautores.inicio();
            while (coautor != nullptr) {
                if (coautor->dato.idCoautor == idCoautor) {
                    std::cout << "Encontrado: " << id << " - Coautor: " << coautor->dato.nombre
                              << " - Investigador: " << investigador->dato.nombre << '\n';
                    return;
                }
                coautor = coautor->siguiente;
            }
            investigador = investigador->siguiente;
        }
    } else if (obtenerNumeroId(id, "IDC", numero)) {
        std::string idCitacion = "C" + std::to_string(numero);
        NodoCircular* primero = publicaciones.inicio();
        if (primero != nullptr) {
            NodoCircular* publicacion = primero;
            do {
                if (publicacion->citaciones.buscarPorId(idCitacion) != nullptr) {
                    std::cout << "Encontrado: " << id << " - Citacion en: " << publicacion->idPublicacion << '\n';
                    return;
                }
                publicacion = publicacion->siguiente;
            } while (publicacion != primero);
        }
    }

    std::cout << "No se encontro la ID o el formato no es valido.\n";
}

}

void buscadorUniversal(Investigador& investigadores,
                       RevistaCientifica& revistas,
                       AreaInvestigacion& areas,
                       Universidad& universidades,
                       ProyectoInvestigacion& proyectos,
                       ListaCircular& publicaciones) {
    // Llama al buscador interno y pausa la pantalla para conservar el resultado visible.
    buscarIdUniversal(investigadores, revistas, areas, universidades, proyectos, publicaciones);
    pausarPantalla();
}

// Muestra opciones, ejecuta la función seleccionada y repite hasta elegir volver.
// La pausa posterior mantiene visible cada resultado antes de redibujar el menú.
void menuConsultas(Investigador& investigadores, RevistaCientifica& revistas,
                   AreaInvestigacion& areas, Universidad& universidades,
                   ProyectoInvestigacion& proyectos,
                   ListaCircular& publicaciones) {
    int opcion;
    do {
        std::cout << "\n=== Consultas ===\n"
                  << "1. Mayor indice H\n2. Mas citas acumuladas\n3. Publicacion con mas citas\n"
                  << "4. Revista con mayor factor de impacto\n5. Investigador con mas coautores\n"
                  << "6. Universidad con mas investigadores\n7. Area con mas publicaciones\n"
                  << "8. Año con mayor produccion\n9. Publicacion con mas autores\n"
                  << "10. Investigador con mas articulos Q1\n11. Buscador universal\n12. Volver\n";
        opcion = leerEntero("Opcion: ");
        switch (opcion) {
        case 1: consultaMayorIndiceH(investigadores, publicaciones); break;
        case 2: consultaMasCitas(investigadores, publicaciones); break;
        case 3: consultaPublicacionMasCitas(publicaciones); break;
        case 4: consultaRevistaMayorImpacto(revistas); break;
        case 5: consultaMasCoautores(investigadores); break;
        case 6: consultaUniversidadMasInvestigadores(investigadores, universidades); break;
        case 7: consultaAreaMasPublicaciones(areas, publicaciones); break;
        case 8: consultaAñoMasProduccion(publicaciones); break;
        case 9: consultaPublicacionMasAutores(publicaciones); break;
        case 10: consultaMasQ1(investigadores, publicaciones); break;
        case 11: buscarIdUniversal(investigadores, revistas, areas, universidades, proyectos, publicaciones); break;
        case 12: break;
        default: std::cout << "Opcion no valida.\n";
        }
        if (opcion != 12) pausarPantalla();
    } while (opcion != 12);
}

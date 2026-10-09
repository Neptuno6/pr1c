#include "Principal.h"

#include "Consultas.h"
#include "DatosIniciales.h"
#include "Entrada.h"
#include "Gestion.h"
#include "Reportes.h"
#include "../ListasDobles/ProyectoInvestigacion.h"

#include <iostream>

namespace {

// Envía secuencias ANSI para limpiar la terminal antes de cada vista.
// Esto evita mezclar los resultados de una pantalla con la siguiente.
void limpiarPantalla() {
    std::cout << "\x1b[2J\x1b[H";
}

// Dibuja el encabezado académico con color y separadores visuales.
// Usa códigos ANSI para mantener una presentación uniforme en la terminal.
void mostrarCabecera() {
    std::cout << "\x1b[36m"
              << "============================================================\n"
              << "              ACADEMIC SCHOLAR TERMINAL\n"
              << "          Research and Knowledge Navigator\n"
              << "============================================================\x1b[0m\n\n";
}

}

// Crea las listas, carga datos iniciales y repite el menú hasta elegir salir.
// Cada opción dirige al buscador, Gestión, Consultas o Reportes correspondiente.
int menuPrincipal() {
    // Estas listas viven durante toda la ejecucion para conservar sus enlaces.
    Investigador investigadores;
    RevistaCientifica revistas;
    AreaInvestigacion areas;
    Universidad universidades;
    ProyectoInvestigacion proyectos;
    ListaCircular publicaciones;
    cargarDatosIniciales(investigadores, revistas, areas, universidades,
                         proyectos, publicaciones);

    int opcion;
    do {
        limpiarPantalla();
        mostrarCabecera();
        std::cout << "  [1] Buscar en el catalogo universal\n"
                  << "  [2] Gestionar datos\n"
                  << "  [3] Consultas academicas\n"
                  << "  [4] Ver reportes\n"
                  << "  [0] Salir\n\n";
        opcion = leerEntero("Opcion: ");
        switch (opcion) {
        case 1:
            limpiarPantalla();
            mostrarCabecera();
            buscadorUniversal(investigadores, revistas, areas, universidades, proyectos, publicaciones);
            break;
        case 2:
            limpiarPantalla();
            menuGestion(investigadores, revistas, areas, universidades, proyectos, publicaciones);
            break;
        case 3:
            limpiarPantalla();
            menuConsultas(investigadores, revistas, areas, universidades, proyectos, publicaciones);
            break;
        case 4:
            limpiarPantalla();
            menuReportes(investigadores, revistas, areas, universidades, publicaciones);
            break;
        case 0:
            std::cout << "\nSesion finalizada.\n";
            break;
        default:
            std::cout << "\nOpcion no valida.\n";
            pausarPantalla();
        }
    } while (opcion != 0);
    return 0;
}

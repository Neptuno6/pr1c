#include "Gestion.h"

#include "Entrada.h"
#include <iostream>

namespace {

// Muestra opciones y delega altas, cambios o bajas en la lista de investigadores.
// Antes de insertar valida la ID; para modificar o eliminar busca el nodo y devuelve el resultado.
void menuInvestigadores(Investigador& lista) {
    char opcion;
    do {
        std::cout << "\n--- Gestion de Investigadores ---\n"
                  << "a. Insertar\nb. Modificar pais\nc. Eliminar\n"
                  << "d. Volver\n";
        opcion = leerOpcion("Opcion: ");
        switch (opcion) {
        case 'a': {
            // Se repite la captura hasta obtener una IDI que no exista.
            int id;
            do {
                id = leerEntero("IDI (solo numero): ");
                if (lista.buscarPorId(id) != nullptr) std::cout << "Ese IDI ya existe.\n";
            } while (lista.buscarPorId(id) != nullptr);
            lista.insertar(id, leerTexto("Nombre: "),
                           leerTexto("Pais: "), leerTexto("Correo: "),
                           leerEntero("Indice H: "));
            break;
        }
        case 'b':
            if (lista.modificarPais(leerEntero("IDI: "), leerTexto("Nuevo pais: "))) {
                std::cout << "Pais actualizado.\n";
            } else {
                std::cout << "Investigador no encontrado.\n";
            }
            break;
        case 'c':
            if (lista.eliminar(leerEntero("IDI: "))) {
                std::cout << "Investigador eliminado.\n";
            } else {
                std::cout << "Investigador no encontrado.\n";
            }
            break;
        case 'd':
            break;
        default:
            std::cout << "Opcion no valida.\n";
        }
    } while (opcion != 'd');
}

// Muestra opciones y llama a la lista para validar y modificar revistas.
// La lista circular ordena por nombre, conserva enlaces y rechaza IDs repetidas.
void menuRevistas(RevistaCientifica& lista) {
    char opcion;
    do {
        std::cout << "\n--- Gestion de Revistas ---\n"
                  << "a. Insertar\nb. Modificar editorial\nc. Eliminar\n"
                  << "d. Volver\n";
        opcion = leerOpcion("Opcion: ");
        switch (opcion) {
        case 'a': {
            // La validacion evita duplicar IDs antes de capturar los demas datos.
            int id;
            do {
                id = leerEntero("IDR (solo numero): ");
                if (lista.buscarPorId(id) != nullptr) std::cout << "Ese IDR ya existe.\n";
            } while (lista.buscarPorId(id) != nullptr);
            lista.insertar(id, leerTexto("Nombre: "),
                           leerTexto("Editorial: "), leerTexto("Pais: "),
                           leerEntero("Factor de impacto: "), leerTexto("Cuartil: "));
            break;
        }
        case 'b':
            if (lista.modificarEditorial(leerEntero("IDR: "), leerTexto("Nueva editorial: "))) {
                std::cout << "Editorial actualizada.\n";
            } else {
                std::cout << "Revista no encontrada.\n";
            }
            break;
        case 'c':
            if (lista.eliminar(leerEntero("IDR: "))) {
                std::cout << "Revista eliminada.\n";
            } else {
                std::cout << "Revista no encontrada.\n";
            }
            break;
        case 'd':
            break;
        default:
            std::cout << "Opcion no valida.\n";
        }
    } while (opcion != 'd');
}

// Lee la opción y delega cada operación de áreas en sus métodos de lista.
// Esos métodos recorren nodos, actualizan la descripción o desconectan el nodo solicitado.
void menuAreas(AreaInvestigacion& lista) {
    char opcion;
    do {
        std::cout << "\n--- Gestion de Areas ---\n"
                  << "a. Insertar\nb. Modificar descripcion\nc. Eliminar\n"
                  << "d. Volver\n";
        opcion = leerOpcion("Opcion: ");
        switch (opcion) {
        case 'a': {
            // Las areas tambien usan numero interno, mostrado con el prefijo IDA.
            int id;
            do {
                id = leerEntero("IDA (solo numero): ");
                if (lista.buscarPorId(id) != nullptr) std::cout << "Ese IDA ya existe.\n";
            } while (lista.buscarPorId(id) != nullptr);
            lista.insertar(id, leerTexto("Nombre: "),
                           leerTexto("Descripcion: "));
            break;
        }
        case 'b':
            if (lista.modificarDescripcion(leerEntero("IDA: "), leerTexto("Nueva descripcion: "))) {
                std::cout << "Descripcion actualizada.\n";
            } else {
                std::cout << "Area no encontrada.\n";
            }
            break;
        case 'c':
            if (lista.eliminar(leerEntero("IDA: "))) {
                std::cout << "Area eliminada.\n";
            } else {
                std::cout << "Area no encontrada.\n";
            }
            break;
        case 'd':
            break;
        default:
            std::cout << "Opcion no valida.\n";
        }
    } while (opcion != 'd');
}

// Lee opciones y usa los métodos de inserción e impresión de universidades.
// El número ingresado se convierte en IDU y la lista doble valida el duplicado.
void menuUniversidades(Universidad& lista) {
    char opcion;
    do {
        std::cout << "\n--- Gestion de Universidades ---\n"
                  << "a. Insertar\nb. Mostrar\nc. Volver\n";
        opcion = leerOpcion("Opcion: ");
        switch (opcion) {
        case 'a': {
            // Las IDs de texto se construyen automaticamente como U + numero.
            std::string id;
            do {
                id = leerIdConPrefijo("IDU (solo numero): ", "U");
                if (lista.buscarPorId(id) != nullptr) std::cout << "Ese IDU ya existe.\n";
            } while (lista.buscarPorId(id) != nullptr);
            lista.insertar(id, leerTexto("Nombre: "),
                           leerTexto("Pais: "), leerEntero("Ranking: "));
            break;
        }
        case 'b':
            lista.imprimir();
            break;
        case 'c':
            break;
        default:
            std::cout << "Opcion no valida.\n";
        }
    } while (opcion != 'c');
}

// Captura datos, busca al responsable y delega la inserción ordenada del proyecto.
// La IDPRO se forma automáticamente y el proyecto guarda el puntero del responsable.
void menuProyectos(ProyectoInvestigacion& lista, Investigador& investigadores) {
    char opcion;
    do {
        std::cout << "\n--- Gestion de Proyectos ---\n"
                  << "a. Insertar\nb. Mostrar\nc. Volver\n";
        opcion = leerOpcion("Opcion: ");
        switch (opcion) {
        case 'a': {
            int idInvestigador = leerEntero("IDI responsable (0 si no aplica): ");
            NodoInvestigador* responsable = idInvestigador == 0
                ? nullptr : investigadores.buscarPorId(idInvestigador);
            std::string idProyecto;
            do {
                idProyecto = leerIdConPrefijo("IDPRO (solo numero): ", "P");
                if (lista.buscarPorId(idProyecto) != nullptr) std::cout << "Ese IDPRO ya existe.\n";
            } while (lista.buscarPorId(idProyecto) != nullptr);
            lista.insertar(idProyecto, leerTexto("Nombre: "),
                           leerTexto("Financiamiento: "), leerTexto("Año inicio: "),
                           leerTexto("Año fin: "), responsable);
            break;
        }
        case 'b':
            lista.imprimir();
            break;
        case 'c':
            break;
        default:
            std::cout << "Opcion no valida.\n";
        }
    } while (opcion != 'c');
}

// Captura IDs, resuelve enlaces y delega publicaciones o citaciones en sus listas.
// Convierte los números a prefijos, valida duplicados y conserva enlaces entre entidades.
void menuPublicaciones(ListaCircular& publicaciones, Investigador& investigadores,
                       RevistaCientifica& revistas, ProyectoInvestigacion& proyectos) {
    char opcion;
    do {
        std::cout << "\n--- Gestion de Publicaciones ---\n"
                  << "a. Insertar\nb. Agregar citacion\nc. Mostrar\nd. Volver\n";
        opcion = leerOpcion("Opcion: ");
        switch (opcion) {
        case 'a': {
            NodoInvestigador* investigador = investigadores.buscarPorId(leerEntero("IDI investigador: "));
            NodoRevista* revista = revistas.buscarPorId(leerEntero("IDR revista (0 si no aplica): "));
            NodoProyecto* proyecto = proyectos.buscarPorId(leerIdConPrefijo("IDPRO proyecto (0 si no aplica): ", "P"));
            std::string idPublicacion;
            do {
                idPublicacion = leerIdConPrefijo("IDPUB (solo numero): ", "PUB");
                if (publicaciones.buscarPorId(idPublicacion) != nullptr) std::cout << "Ese IDPUB ya existe.\n";
            } while (publicaciones.buscarPorId(idPublicacion) != nullptr);
            publicaciones.insertar(idPublicacion, leerTexto("Titulo: "),
                                   leerEntero("Año: "), leerTexto("Tipo: "),
                                   leerEntero("Cantidad de citas: "), leerTexto("DOI: "),
                                   investigador, revista, proyecto, Citaciones(),
                                   leerEntero("Cantidad de autores: "));
            break;
        }
        case 'b': {
            std::string id = leerIdConPrefijo("IDPUB publicacion: ", "PUB");
            NodoCitacion citacion(leerIdConPrefijo("IDC (solo numero): ", "C"), leerEntero("Año: "),
                                  leerTexto("Publicacion entrante: "), leerTexto("Autor entrante: "));
            if (publicaciones.agregarCitacion(id, citacion)) {
                std::cout << "Citacion agregada.\n";
            } else {
                std::cout << "Publicacion no encontrada.\n";
            }
            break;
        }
        case 'c':
            publicaciones.imprimir();
            break;
        case 'd':
            break;
        default:
            std::cout << "Opcion no valida.\n";
        }
    } while (opcion != 'd');
}

// Busca nodos relacionados y guarda sus punteros dentro del investigador.
// Así universidad, área y coautor comparten objetos existentes sin crear copias.
void menuVinculos(Investigador& investigadores, Universidad& universidades,
                  AreaInvestigacion& areas) {
    // Los enlaces guardan punteros a nodos existentes; no se crean copias de las entidades.
    char opcion;
    do {
        std::cout << "\n--- Vinculos de investigadores ---\n"
                  << "a. Asignar universidad\nb. Asignar area\nc. Agregar coautor\nd. Volver\n";
        opcion = leerOpcion("Opcion: ");
        switch (opcion) {
        case 'a': {
            NodoInvestigador* investigador = investigadores.buscarPorId(leerEntero("ID investigador: "));
            NodoUniversidad* universidad = universidades.buscarPorId(leerIdConPrefijo("IDU universidad: ", "U"));
            if (investigador != nullptr && universidad != nullptr) {
                investigador->universidad = universidad;
                std::cout << "Universidad asignada.\n";
            } else {
                std::cout << "Investigador o universidad no encontrada.\n";
            }
            break;
        }
        case 'b': {
            NodoInvestigador* investigador = investigadores.buscarPorId(leerEntero("IDI investigador: "));
            NodoAreaInvestigacion* area = areas.buscarPorId(leerEntero("IDA area: "));
            if (investigador != nullptr && area != nullptr) {
                investigador->area = area;
                std::cout << "Area asignada.\n";
            } else {
                std::cout << "Investigador o area no encontrada.\n";
            }
            break;
        }
        case 'c':
            {
                std::string idCoautor;
                do {
                    idCoautor = leerIdConPrefijo("IDCO (solo numero): ", "CA");
                    if (investigadores.existeCoautor(idCoautor)) std::cout << "Ese IDCO ya existe.\n";
                } while (investigadores.existeCoautor(idCoautor));
                int idInvestigador = leerEntero("IDI investigador: ");
                NodoUniversidad* universidad = nullptr;
                // El coautor conserva un puntero a la universidad seleccionada.
                do {
                    universidad = universidades.buscarPorId(
                        leerIdConPrefijo("IDU universidad (solo numero): ", "U"));
                    if (universidad == nullptr) std::cout << "Universidad no encontrada.\n";
                } while (universidad == nullptr);
                investigadores.agregarCoautor(idInvestigador, idCoautor,
                                              leerTexto("Nombre: "),
                                              leerEntero("Publicaciones conjuntas: "),
                                              universidad);
                std::cout << "Coautor agregado si el investigador existe.\n";
            }
            break;
        case 'd':
            break;
        default:
            std::cout << "Opcion no valida.\n";
        }
    } while (opcion != 'd');
}

} // namespace

// Muestra el menú general y dirige cada opción al submenú correspondiente.
// El ciclo conserva las listas activas hasta que el usuario selecciona volver.
void menuGestion(Investigador& investigadores, RevistaCientifica& revistas,
                 AreaInvestigacion& areas, Universidad& universidades,
                 ProyectoInvestigacion& proyectos, ListaCircular& publicaciones) {
    char opcion;
    do {
        std::cout << "\n=== Gestion de datos ===\n"
                  << "1. Investigadores\n2. Revistas\n3. Areas\n"
                  << "4. Universidades\n5. Proyectos\n6. Publicaciones\n"
                  << "7. Vinculos\n8. Volver\n";
        opcion = leerOpcion("Opcion: ");
        switch (opcion) {
        case '1': menuInvestigadores(investigadores); break;
        case '2': menuRevistas(revistas); break;
        case '3': menuAreas(areas); break;
        case '4': menuUniversidades(universidades); break;
        case '5': menuProyectos(proyectos, investigadores); break;
        case '6': menuPublicaciones(publicaciones, investigadores, revistas, proyectos); break;
        case '7': menuVinculos(investigadores, universidades, areas); break;
        case '8': break;
        default: std::cout << "Opcion no valida.\n";
        }
    } while (opcion != '8');
}

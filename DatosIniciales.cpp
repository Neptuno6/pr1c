#include "DatosIniciales.h"

// Inserta datos base y después busca sus nodos para conectar las relaciones.
// Los punteros se asignan después de crear las entidades referenciadas.
void cargarDatosIniciales(Investigador& investigadores,
                          RevistaCientifica& revistas,
                          AreaInvestigacion& areas,
                          Universidad& universidades,
                          ProyectoInvestigacion& proyectos,
                          ListaCircular& publicaciones) {
    // Las entidades referenciadas se crean antes de asignar sus punteros.
    universidades.insertar("U1", "Universidad Nacional", "Colombia", 1);
    universidades.insertar("U2", "Universidad Central", "Colombia", 2);
    universidades.insertar("U3", "Universidad del Norte", "Colombia", 3);
    universidades.insertar("U4", "Universidad de Antioquia", "Colombia", 4);
    universidades.insertar("U5", "Universidad del Valle", "Colombia", 5);

    areas.insertar(1, "Inteligencia Artificial", "Sistemas inteligentes y aprendizaje automatico");
    areas.insertar(2, "Biotecnologia", "Aplicaciones tecnologicas de sistemas biologicos");
    areas.insertar(3, "Energia", "Fuentes y sistemas de energia sostenible");
    areas.insertar(4, "Salud Digital", "Tecnologias aplicadas a la salud");
    areas.insertar(5, "Ciencias Sociales", "Analisis de fenomenos sociales");

    investigadores.insertar(1, "Ana Perez", "Colombia", "ana@correo.com", 5);
    investigadores.insertar(2, "Bruno Gomez", "Colombia", "bruno@correo.com", 4);
    investigadores.insertar(3, "Carla Ruiz", "Colombia", "carla@correo.com", 3);
    investigadores.insertar(4, "Diego Torres", "Colombia", "diego@correo.com", 2);
    investigadores.insertar(5, "Elena Castro", "Colombia", "elena@correo.com", 1);

    const char* idsUniversidad[] = {"U1", "U2", "U3", "U4", "U5"};
    int idsArea[] = {1, 2, 3, 4, 5};
    for (int indice = 0; indice < 5; ++indice) {
        NodoInvestigador* investigador = investigadores.buscarPorId(indice + 1);
        investigador->universidad = universidades.buscarPorId(idsUniversidad[indice]);
        investigador->area = areas.buscarPorId(idsArea[indice]);
    }

    revistas.insertar(1, "Revista de Tecnologia", "Editorial Alfa", "Colombia", 95, "Q1");
    revistas.insertar(2, "Revista de Salud", "Editorial Beta", "Colombia", 82, "Q1");
    revistas.insertar(3, "Revista de Energia", "Editorial Gamma", "Colombia", 74, "Q2");
    revistas.insertar(4, "Revista Social", "Editorial Delta", "Colombia", 61, "Q2");
    revistas.insertar(5, "Revista Biologica", "Editorial Epsilon", "Colombia", 53, "Q3");

    proyectos.insertar("P1", "Proyecto IA", "100000", "2021", "2024", investigadores.buscarPorId(1));
    proyectos.insertar("P2", "Proyecto Salud", "90000", "2020", "2023", investigadores.buscarPorId(2));
    proyectos.insertar("P3", "Proyecto Energia", "80000", "2022", "2025", investigadores.buscarPorId(3));
    proyectos.insertar("P4", "Proyecto Sociedad", "70000", "2019", "2022", investigadores.buscarPorId(4));
    proyectos.insertar("P5", "Proyecto Biologia", "60000", "2023", "2026", investigadores.buscarPorId(5));

    publicaciones.insertar("PUB1", "Aprendizaje automatico aplicado", 2021, "Articulo", 5,
                           "10.1000/pub1", investigadores.buscarPorId(1), revistas.buscarPorId(1),
                           proyectos.buscarPorId("P1"), Citaciones(), 3);
    publicaciones.insertar("PUB2", "Tecnologia para la salud", 2022, "Articulo", 4,
                           "10.1000/pub2", investigadores.buscarPorId(2), revistas.buscarPorId(2),
                           proyectos.buscarPorId("P2"), Citaciones(), 2);
    publicaciones.insertar("PUB3", "Energia sostenible", 2020, "Articulo", 3,
                           "10.1000/pub3", investigadores.buscarPorId(3), revistas.buscarPorId(3),
                           proyectos.buscarPorId("P3"), Citaciones(), 4);
    publicaciones.insertar("PUB4", "Analisis de comunidades", 2019, "Articulo", 2,
                           "10.1000/pub4", investigadores.buscarPorId(4), revistas.buscarPorId(4),
                           proyectos.buscarPorId("P4"), Citaciones(), 2);
    publicaciones.insertar("PUB5", "Sistemas biologicos", 2023, "Articulo", 1,
                           "10.1000/pub5", investigadores.buscarPorId(5), revistas.buscarPorId(5),
                           proyectos.buscarPorId("P5"), Citaciones(), 5);

    // Las listas de coautores y citaciones son internas a investigadores y publicaciones.
    investigadores.agregarCoautor(1, "CA1", "Coautor Uno", 2);
    investigadores.agregarCoautor(2, "CA2", "Coautor Dos", 3);
    investigadores.agregarCoautor(3, "CA3", "Coautor Tres", 1);
    investigadores.agregarCoautor(4, "CA4", "Coautor Cuatro", 4);
    investigadores.agregarCoautor(5, "CA5", "Coautor Cinco", 2);

    publicaciones.agregarCitacion("PUB1", NodoCitacion("C1", 2022, "PUB1", "Autor externo 1"));
    publicaciones.agregarCitacion("PUB2", NodoCitacion("C2", 2022, "PUB2", "Autor externo 2"));
    publicaciones.agregarCitacion("PUB3", NodoCitacion("C3", 2021, "PUB3", "Autor externo 3"));
    publicaciones.agregarCitacion("PUB4", NodoCitacion("C4", 2020, "PUB4", "Autor externo 4"));
    publicaciones.agregarCitacion("PUB5", NodoCitacion("C5", 2024, "PUB5", "Autor externo 5"));
}

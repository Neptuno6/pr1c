#pragma once
#include <string>
#include "ListasDobles/Citaciones.h"
#include "ListasDobles/ProyectoInvestigacion.h"
#include "ListasSimples/Investigador.h"
#include "ListasSimples/RevistasCientificas.h"

struct NodoCircular {
    std::string idPublicacion;
    std::string titulo; 
    int annio;
    std::string tipo; // Artículo, Libro, Conferencia
    int cantidadCitas;
    // Se captura para responder el reporte de publicaciones con mas autores.
    int cantidadAutores;
    std::string doi;
    NodoInvestigador* enlaceInvestigador;
    NodoRevista* enlaceRevista;
    NodoProyecto* enlaceProyecto;
    Citaciones citaciones;
    NodoCircular* siguiente;

    // Inicializa una publicación con sus enlaces y datos bibliográficos.
    NodoCircular(const std::string& idP, const std::string& t, int a, const std::string& ty,
                 int cC, const std::string& d, NodoInvestigador* eI,
                                 NodoRevista* eR, NodoProyecto* eP, const Citaciones& cit,
                                 int autores = 1)
        : idPublicacion(idP), titulo(t), annio(a), tipo(ty), cantidadCitas(cC),
                    cantidadAutores(autores), doi(d), enlaceInvestigador(eI), enlaceRevista(eR), enlaceProyecto(eP),
          citaciones(cit), siguiente(nullptr) {}
};

class ListaCircular {
private:
    NodoCircular* primero;

public:
    // Crea una lista circular sin publicaciones.
    ListaCircular() : primero(nullptr) {}
    ~ListaCircular();

    // Las consultas recorren la lista circular respetando su punto de inicio.
    // Devuelve el primer nodo como punto de control del recorrido circular.
    NodoCircular* inicio() const {
        return primero;
    }

    void insertar(const NodoCircular& publicacion);
    void insertar(const std::string& idPublicacion, const std::string& titulo, int annio,
                  const std::string& tipo, int cantidadCitas, const std::string& doi,
                  NodoInvestigador* enlaceInvestigador, NodoRevista* enlaceRevista,
                  NodoProyecto* enlaceProyecto, const Citaciones& citaciones = Citaciones(),
                  int cantidadAutores = 1);

    NodoCircular* buscarPorId(const std::string& idPublicacion);
    NodoCircular* buscarPorInvestigador(int idInvestigador);
    int calcularIndiceH(int idInvestigador) const;
    void imprimirPorInvestigador(int idInvestigador) const;
    NodoCircular* buscarPorArea(int idArea);
    NodoCircular* buscarPorRevista(int idRevista);
    void imprimirPorRevista(int idRevista) const;
    NodoCircular* buscarPorProyecto(const std::string& idProyecto);
    bool existeCitacion(const std::string& idCita) const;
    bool agregarCitacion(const std::string& idPublicacion, const NodoCitacion& citacion);

    void imprimir() const;
};
   

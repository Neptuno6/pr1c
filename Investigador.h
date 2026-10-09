#pragma once

#include "../listaSimple.h"
#include <string>
#include "AreaInvestigacion.h"
#include "../ListasDobles/Universidad.h"
#include "../ListasDobles/Coautor.h"

struct NodoInvestigador {
    int id;
    std::string nombre;
    NodoUniversidad* universidad; //Un investigador pertenece a una universidad, por lo que se utiliza un puntero a NodoUniversidad para establecer la relación.
    std::string pais;
    NodoAreaInvestigacion* area; //Un investigador pertenece a un área de investigación, por lo que se utiliza un puntero a NodoAreaInvestigacion para establecer la relación.
    std::string correo;
    int indiceH;
    Coautor coautores;

    NodoInvestigador(int id, const std::string& n, NodoUniversidad* u, const std::string& p,
                     NodoAreaInvestigacion* a,
                     const std::string& c, int h);
};

class Investigador : public ListaSimple<NodoInvestigador> {
public:
    // Este metodo sobrescribe el metodo generico de ListaSimple<T>.
    void insertar(const NodoInvestigador& investigador) override;

    void insertar(int id, const std::string& nombre, NodoUniversidad* universidad, const std::string& pais,
                  NodoAreaInvestigacion* area, const std::string& correo, int indiceH);
    void insertar(int id, const std::string& nombre, const std::string& pais,
                  const std::string& correo, int indiceH);
    NodoInvestigador* buscarPorId(int id);
    bool modificarPais(int id, const std::string& pais);
    bool eliminar(int id);
    bool existeCoautor(const std::string& idCoautor) const;

    void agregarCoautor(int idInvestigador,
                        const std::string& idCoautor,
                        const std::string& nombre,
                        int publicacionesConjuntas,
                        NodoUniversidad* universidad = nullptr);

    void imprimir() const override;
};
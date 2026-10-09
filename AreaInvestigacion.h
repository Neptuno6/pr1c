#pragma once

#include "../listaSimple.h"
#include <string>

struct NodoAreaInvestigacion {//Atributos
    int idArea;
    std::string nombre;
    std::string descripcion;
    NodoAreaInvestigacion*siguiente;
    //Constructor
    NodoAreaInvestigacion(int idA, const std::string& n,const std::string& d);
};


class AreaInvestigacion : public ListaSimple<NodoAreaInvestigacion> {
    public:
    void insertar(const NodoAreaInvestigacion& area) override;
    // Esta sobrecarga permite llamar insertar con los cinco datos del investigador.
    void insertar(int idArea, const std::string& nombre, const std::string& descripcion);
    // Este metodo busca un área de investigación por su ID en la lista y devuelve un puntero al nodo correspondiente si se encuentra, o nullptr si no se encuentra.
    NodoAreaInvestigacion* buscarPorId(int idArea);
    bool modificarDescripcion(int idArea, const std::string& descripcion);
    bool eliminar(int idArea);
    void imprimir() const override;
};


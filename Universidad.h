#pragma once
#include "../ListaDoble.h"
#include <iostream>
#include <string>

struct NodoUniversidad{
    std::string idUniversidad;
    std::string nombre;
    std::string pais;   
    int ranking; 
    NodoUniversidad*siguiente;
    NodoUniversidad*anterior;
    //Constructor de NodoUniversidad
    // Inicializa una universidad con sus datos y ranking.
    NodoUniversidad(const std::string& idU, const std::string& n, const std::string& p, const int& r)
    : idUniversidad(idU), nombre(n), pais(p), ranking(r), siguiente(nullptr), anterior(nullptr){}
};

class Universidad: public ListaDoble<NodoUniversidad> {
public:
    Universidad& operator=(const Universidad& otra);
    ~Universidad();

    void insertar(const NodoUniversidad& universidad) override;
    // Esta sobrecarga permite llamar insertar con los cuatro datos de la universidad.
    void insertar(const std::string& idUniversidad, const std::string& nombre, const std::string& pais, const int& ranking);
    NodoUniversidad* buscarPorId(const std::string& idUniversidad);
    void imprimir() const override;
};

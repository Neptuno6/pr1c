#pragma once
#include "../listaSimple.h"
#include <iostream>
#include <string>
 
struct NodoRevista{ //Nodo y atributos
    int idRevista;
    std::string nombre;
    std::string editorial;
    std::string pais;
    int FactorImpacto;
    std::string Cuartil; // Q1, Q2, Q3, Q4 Debo ver como definirlo mejor
    NodoRevista* siguiente; //puntero al siguiente nodo

    // Inicializa los datos bibliográficos y deja libre el enlace siguiente.
    NodoRevista(int id, const std::string& n, const std::string& e,
                const std::string& p, int fi, const std::string& c)
        : idRevista(id), nombre(n), editorial(e), pais(p), FactorImpacto(fi), Cuartil(c), siguiente(nullptr) {}
};

//Definicion de la clase Revista que hereda de ListaSimple<NodoRevista<T>>
class RevistaCientifica : public ListaSimple<NodoRevista>{
public:
    ~RevistaCientifica() override;
    // Este metodo sobrescribe el metodo generico de ListaSimple<T>.
    void insertar(const NodoRevista& revista) override;

    // Esta sobrecarga permite llamar insertar con los cinco datos del investigador.
    void insertar(int id, const std::string& nombre, 
        const std::string& editorial, const std::string& pais, 
        int FactorImpacto, const std::string& Cuartil);     

    NodoRevista* buscarPorId(int idRevista);
    bool modificarEditorial(int idRevista, const std::string& editorial);
    bool eliminar(int idRevista);

    void imprimir() const override;
};

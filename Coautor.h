#pragma once
#include "../ListaDoble.h"
#include <iostream>
#include <string>
#include "Universidad.h" // Asegúrate de incluir la definición de NodoUniversidad
struct NodoCoautor{
    std::string idCoautor;
    std::string nombre;
    NodoUniversidad* universidad; //atributo tipo lista Universidad(todavía no hay clase Universidad)
    int publicacionesConjuntas;
    NodoCoautor*siguiente;
    NodoCoautor*anterior;
    //Constructor de NodoCoautor
    // Inicializa el coautor y conserva el puntero a su universidad.
    NodoCoautor(const std::string& idC, const std::string& n,NodoUniversidad* u, const int& pub)
    : idCoautor(idC), nombre(n), universidad(u), publicacionesConjuntas(pub), siguiente(nullptr), anterior(nullptr){}
};

class Coautor : public ListaDoble<NodoCoautor> {
public:
    // Crea una lista de coautores vacía.
    Coautor() = default;
    Coautor(const Coautor& otra);
    Coautor& operator=(const Coautor& otra);
    ~Coautor();

    void insertar(const NodoCoautor& coautor) override;
    // Esta sobrecarga permite asociar el coautor con una universidad.
    void insertar(const std::string& idCoautor, const std::string& nombre, NodoUniversidad* universidad, const int& publicacionesConjuntas);
    void insertar(const std::string& idCoautor, const std::string& nombre, const int& publicacionesConjuntas);
    NodoCoautor* buscarPorId(const std::string& idCoautor);
    void imprimir() const override;
};
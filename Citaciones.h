#pragma once
#include "../ListaDoble.h"
#include <string>
#include <ctime>
struct NodoCitacion {
    std::string idCita;
    int annio;
    std::string enlacePublicacionEntrante;
    std::string enlaceAutorEntrante;
    
    // Inicializa la citación y sus referencias externas.
    NodoCitacion(const std::string& idC, const int& a, const std::string& enlacePub, const std::string& enlaceAutor)
        : idCita(idC), annio(a), enlacePublicacionEntrante(enlacePub), enlaceAutorEntrante(enlaceAutor) {}
};

class Citaciones : public ListaDoble<NodoCitacion> {
public:
    // Crea una lista de citaciones vacía.
    Citaciones() = default;
    Citaciones(const Citaciones& otra);
    Citaciones& operator=(const Citaciones& otra);
    ~Citaciones();

    void insertar(const NodoCitacion& citacion) override;
    // Esta sobrecarga permite llamar insertar con los tres datos de la citación.
    void insertar(const std::string& idCita, const int& annio, const std::string& enlacePublicacionEntrante, const std::string& enlaceAutorEntrante);
    NodoCitacion* buscarPorId(const std::string& idCita);
    NodoCitacion* buscarPorId(const std::string& idCita) const;
    void imprimir() const override;
};
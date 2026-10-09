#pragma once
#include "../ListaDoble.h"
#include <iostream>
#include <string>

struct NodoInvestigador;

struct NodoProyecto {
    std::string idProyecto;
    std::string nombre;
    std::string financimiento;
    std::string AnnioInicio;
    std::string AnnioFin;
        NodoInvestigador* enlaceInvestigadorResponsable;
    NodoProyecto* siguiente;
    NodoProyecto* anterior;

    // Inicializa el proyecto y su posible investigador responsable.
    NodoProyecto(const std::string& idP, const std::string& n, const std::string& f,
                                    const std::string& fI, const std::string& fF,
                                    NodoInvestigador* responsable = nullptr)
        : idProyecto(idP), nombre(n), financimiento(f), AnnioInicio(fI), AnnioFin(fF),
                    enlaceInvestigadorResponsable(responsable),
                    siguiente(nullptr), anterior(nullptr) {}
};

class ProyectoInvestigacion : public ListaDoble<NodoProyecto> {
    public:
    void insertar(const NodoProyecto& proyecto) override;
    // Esta sobrecarga permite llamar insertar con los cinco datos del proyecto.
    void insertar(const std::string& idProyecto, const std::string& nombre, 
        const std::string& financimiento, const std::string& AnnioInicio, 
        const std::string& AnnioFin,
        NodoInvestigador* responsable = nullptr);
    NodoProyecto* buscarPorId(const std::string& idProyecto);
    NodoProyecto* buscarPorInvestigadorResponsable(int idInvestigador);
    void imprimirPorInvestigadorResponsable(int idInvestigador) const;
    void imprimir() const override;
};
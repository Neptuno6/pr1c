#pragma once

#include "../ListaCircular.h"
#include "../ListasDobles/ProyectoInvestigacion.h"
#include "../ListasDobles/Universidad.h"
#include "../ListasSimples/AreaInvestigacion.h"
#include "../ListasSimples/Investigador.h"
#include "../ListasSimples/RevistasCientificas.h"

void cargarDatosIniciales(Investigador& investigadores,
                          RevistaCientifica& revistas,
                          AreaInvestigacion& areas,
                          Universidad& universidades,
                          ProyectoInvestigacion& proyectos,
                          ListaCircular& publicaciones);

#pragma once

#include "../ListaCircular.h"
#include "../ListasDobles/Universidad.h"
#include "../ListasSimples/AreaInvestigacion.h"
#include "../ListasSimples/Investigador.h"
#include "../ListasSimples/RevistasCientificas.h"

void menuReportes(Investigador& investigadores,
                  RevistaCientifica& revistas,
                  AreaInvestigacion& areas,
                  Universidad& universidades,
                  ListaCircular& publicaciones);

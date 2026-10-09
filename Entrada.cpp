#include "Entrada.h"

#include <iostream>
#include <limits>

int leerEntero(const std::string& mensaje) {
    int valor;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> valor) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
        std::cout << "Error: ingrese un numero valido.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string leerTexto(const std::string& mensaje) {
    std::string valor;
    std::cout << mensaje;
    std::getline(std::cin, valor);
    return valor;
}

std::string leerIdConPrefijo(const std::string& mensaje, const std::string& prefijo) {
    // Lee el número y concatena el prefijo fijo antes de devolver la ID completa.
    return prefijo + std::to_string(leerEntero(mensaje));
}

char leerOpcion(const std::string& mensaje) {
    char opcion;
    std::cout << mensaje;
    std::cin >> opcion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return opcion;
}

// Detiene la pantalla hasta que el usuario presiona Enter.
// Así conserva visible el resultado antes de dibujar nuevamente el menú.
void pausarPantalla() {
    std::cout << "\nPresione Enter para volver al menu...";
    std::cin.get();
}

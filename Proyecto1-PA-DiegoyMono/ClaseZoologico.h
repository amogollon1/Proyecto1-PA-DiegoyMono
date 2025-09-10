#pragma once
#include <iostream>
#include <vector>
#include "EstructuraHabitat.h"

using namespace std;

/*class Zoologico {
    vector<Habitat> habitats;
    double ingresosTotales = 0;
    double gastosTotales = 0;

public:
    void configurarHabitats(int num);
    void asignarAnimal(Animal* animal, int habitatID);
    void alimentarAnimales();
    void aplicarTratamiento(int idAnimal, int opcion);
    void avanzarDia();
    void mostrarReporteAnimales() const;
};*/

class Zoologico {
    vector<Habitat> habitats;
    double ingresosTotales = 0;
    double gastosTotales = 0;
    static int siguienteID;  // Variable para asegurar IDs únicos a nivel global

public:
    void configurarHabitats(int num);
    void asignarAnimal(Animal* animal, int habitatID);
    void alimentarAnimales();
    void aplicarTratamiento(int idAnimal, int opcion);
    void avanzarDia();
    void mostrarReporteAnimales() const;
    void mostrarReporteFinal() const; // NUEVO DEEPSEEK
    string getTipoHabitat(int habitatID) const;
//Deepseek NUEVO
    static int generarIDUnico() { return siguienteID++; } // Método nuevo
    static void reiniciarContadorID() { siguienteID = 1; } // Para reiniciar si es necesario
private:
    void procesarReproduccion();
};



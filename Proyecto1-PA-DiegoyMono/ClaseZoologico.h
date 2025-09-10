#pragma once
#include <iostream>
#include <vector>
#include "EstructuraHabitat.h"

using namespace std;

class Zoologico { // variables con las que cuenta la clase
    vector<Habitat> habitats;
    double ingresosTotales = 0;
    double gastosTotales = 0;
    static int siguienteID;

public: // metodos publicos de la clase 
    void configurarHabitats(int num);
    void asignarAnimal(Animal* animal, int habitatID);
    void alimentarAnimales();
    void aplicarTratamiento(int idAnimal, int opcion);
    void avanzarDia();
    void mostrarReporteAnimales() const;
    void mostrarReporteFinal() const;
    string getTipoHabitat(int habitatID) const;
    static int generarIDUnico() { return siguienteID++; }
    static void reiniciarContadorID() { siguienteID = 1; }
private: // metodos privados de la clase
    void procesarReproduccion();
};
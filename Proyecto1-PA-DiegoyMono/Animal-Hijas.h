#pragma once
#include "ClaseAnimal.h"

class Ave : public Animal {
public:
    Ave(int id, double precio) : Animal(id, "Ave", 1, 5, 4, precio) {} //Constructor de Ave con sus respectivos parametros y añade parametros de todos los animales
    string MostrarDescripcion() const override { //Usamos const porque así los elementos en el metodo no cambiaran
        return "Un tipo de animal vertebrado que se caracteriza por tener plumas, alas y poner huevos.";
    }
};

class Mamifero : public Animal {
public:
    Mamifero(int id, double precio) : Animal(id, "Mamifero", 5, 3, 2, precio) {} //Constructor de Mamifero con sus respectivos parametros y añade parametros de todos los animales
    string MostrarDescripcion() const override {
        return "Animal vertebrado de sangre caliente, con pelo y glandulas mamarias.";
    }
};

class Reptil : public Animal {
public:
    Reptil(int id, double precio) : Animal(id, "Reptil", 3, 4, 3, precio) {} //Constructor de Reptil con sus respectivos parametros y añade parametros de todos los animales
    string MostrarDescripcion() const override {
        return "Vertebrado de sangre fria, piel escamosa, generalmente pone huevos.";
    }
};

class Pez : public Animal {
public:
    Pez(int id, double precio) : Animal(id, "Pez", 1, 5, 5, precio) {} //Constructor de Pez con sus respectivos parametros y añade parametros de todos los animales
    string MostrarDescripcion() const override {
        return "Animal acuatico, generalmente con aletas y branquias.";
    }
};

class Anfibio : public Animal {
public:
    Anfibio(int id, double precio) : Animal(id, "Anfibio", 2, 2, 4, precio) {} //Constructor de Anfibio con sus respectivos parametros y añade parametros de todos los animales
    string MostrarDescripcion() const override {
        return "Animal vertebrado que vive parte de su vida en agua y parte en tierra.";
    }
};


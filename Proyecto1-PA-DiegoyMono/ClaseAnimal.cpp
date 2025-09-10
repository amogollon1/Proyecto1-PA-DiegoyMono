#include "ClaseAnimal.h"
#include "Animal-Hijas.h"
#include <iostream>
#include <cstdlib> //para la generacion de numeros aleatorios

using namespace std;

Animal::Animal(int id, string tipo, int comida, double probNac, double probEnf, double precio) {
    //Asignacion de cada elemento local a su respectivo elemento en el contructor
    IDAnimal = id;
    tipoAnimal = tipo;
    unidades_comida = comida;
    probabilidad_nacimiento = probNac;
    probabilidad_enfermedad = probEnf;
    precioAnimal = precio;
    estadoNutricion = EstadoNutricion::Nutrido; //Instancia del enum, nutrido por default
    estadoSalud = EstadoSalud::Saludable; //Saludable por default
}

void Animal::Alimentar(int comida) {
    if (!estaVivo()) { //estaVivo es vivo por defualt por lo que su negacion es que esta muerto
        cout << "No se puede alimentar un animal muerto (ID: " << IDAnimal << ")." << endl;
        return;
    }

    cout << "Alimentando animal ID: " << IDAnimal << " con " << comida
        << " unidades (requiere: " << unidades_comida << ")" << endl;

    if (comida < unidades_comida) { //Si la comida administrada es menor a sus unidades de comida requeridas
        if (estadoNutricion == EstadoNutricion::Desnutrido) { // si el estado de nutricion es desnutrido y no recibe la comida necesaria fallece
            estadoSalud = EstadoSalud::Fallecido;
            cout << "El animal con el ID " << IDAnimal << " murio por desnutricion." << endl;
        }
        else { // si el estado de nutricion es nutrido y no recibe la comida necesaria pasa a estar desutrido
            estadoNutricion = EstadoNutricion::Desnutrido;
            cout << "El animal con el ID " << IDAnimal << " esta desnutrido." << endl;
        }
    }
    else {
        estadoNutricion = EstadoNutricion::Nutrido;
        cout << "El animal con el ID " << IDAnimal << " fue alimentado correctamente." << endl;
    }
}

void Animal::Enfermar() { 
    if (!estaVivo()) return; // si el animal no esta vivo no puede enfermarse

    int prob = rand() % 20 + 1; // se genera aleatoreamente la probabilidad que se comparara
    if (prob <= probabilidad_enfermedad) { // dependiendo de la probabilidad de cada animal se valida si se enferma o no
        estadoSalud = (rand() % 2 == 0) ? EstadoSalud::EnfermoLeve : EstadoSalud::EnfermoGrave; // en caso de enfermarse, aleatoriamente se decide si es leve o grave
        // Configurar resistencia según gravedad
        if (estadoSalud == EstadoSalud::EnfermoLeve) { // si es leve reciste 3 dias enfermo
            maxDiasResistencia = 3;
        }
        else {
            maxDiasResistencia = 1; // si es grave resiste solo un dia enfermo
        }

        diasEnfermo = 0;
        cout << "El animal con el ID " << IDAnimal << " se enfermo ("
            << (estadoSalud == EstadoSalud::EnfermoLeve ? "leve" : "grave") << ")." << endl;
    }
}
void Animal::avanzarDia() { 
    if (!estaVivo()) return;

    if (estadoSalud == EstadoSalud::EnfermoLeve || estadoSalud == EstadoSalud::EnfermoGrave) { 
        diasEnfermo++;
        if (diasEnfermo > maxDiasResistencia) { // si el animal esta enfermo se conparan los dias que lleva en ese estado con la cantidad de dias que puede resistir
            estadoSalud = EstadoSalud::Fallecido; // en caso de superar el limite el animal fallece
            cout << "El animal con ID " << IDAnimal << " murio por enfermedad." << endl;
        }
    }
} 
bool Animal::puedeReproducirse() const { // se valida que se cumplan todas las condiciones para que el animal pueda reproducirse
    return estaVivo() && estadoNutricion == EstadoNutricion::Nutrido &&
        estadoSalud == EstadoSalud::Saludable;
}
Animal* Animal::reproducir(int nuevoID) {
    if (!puedeReproducirse()) return nullptr;

    int prob = rand() % 50 + 1; // se obtine un valor aleatorio que se comparara con la posibilidad de nacimiento de cada animal
    if (prob <= probabilidad_nacimiento) {
        double precioCria = 50 + rand() % 451; // Precio entre 50-500 para crías

        if (tipoAnimal == "Ave") return new Ave(nuevoID, precioCria);
        if (tipoAnimal == "Mamifero") return new Mamifero(nuevoID, precioCria);
        if (tipoAnimal == "Reptil") return new Reptil(nuevoID, precioCria);
        if (tipoAnimal == "Pez") return new Pez(nuevoID, precioCria);
        if (tipoAnimal == "Anfibio") return new Anfibio(nuevoID, precioCria);
    }
    return nullptr; // en caso de no poder reproducirse se devuelve un valor nulo de memoria
}

void Animal::TratarSuero() {
    if (estadoNutricion == EstadoNutricion::Desnutrido) {
        estadoNutricion = EstadoNutricion::Nutrido; //lo nutre si se trata con suero
        cout << "Tratamiento con suero aplicado al animal con ID " << IDAnimal << "." << endl;
    }
}

void Animal::TratarMedicina() {
    if (estadoSalud == EstadoSalud::EnfermoLeve || estadoSalud == EstadoSalud::EnfermoGrave) {
        estadoSalud = EstadoSalud::Saludable; //lo cura si se trata con medicina y esta enfermo
        cout << "El animal con el ID " << IDAnimal << " fue curado con medicina." << endl;
    }
}

void Animal::Vacunar() {
    if (probabilidad_enfermedad > 1) probabilidad_enfermedad--; // la vacuna disminuye la probabilidad de enfermarse
    cout << "El animal con el ID " << IDAnimal << " fue vacunado. Ahora tiene menor probabilidad de enfermar." << endl;
}

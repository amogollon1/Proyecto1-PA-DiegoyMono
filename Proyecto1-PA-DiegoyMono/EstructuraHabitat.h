#pragma once
#include <string>
#include <vector>
#include "ClaseAnimal.h"
using namespace std;

struct Habitat { //Esta es la estructura donde se guardarán todos los animales por habitat
	int IDHabitat = 0;
	string tipoHabitat = "";
	vector<Animal*> animalesAsignados;
};

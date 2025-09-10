#pragma once
#include <string>
#include <vector>
#include "ClaseAnimal.h"
using namespace std;

struct Habitat {
	int IDHabitat = 0;
	string tipoHabitat = "";
	vector<Animal*> animalesAsignados;
};

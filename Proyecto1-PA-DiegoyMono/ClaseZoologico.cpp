#include "ClaseZoologico.h"
#include "ClaseAnimal.h"
#include "Animal-Hijas.h"
#include <iostream>
using namespace std;

int Zoologico::siguienteID = 1; //Inicializar ID s

void Zoologico::configurarHabitats(int num) {
    string tipos[] = { "Aviario", "Acuario", "Laguna", "Bosque" }; //Arreglo con los 4 habitats posibles
    for (int i = 0; i < num; i++) {
        Habitat h; //Instancia de habitat temporal
        h.IDHabitat = i + 1; //Asigna cada habitat a un id unico i+1 para empezar desde 1
        h.tipoHabitat = tipos[rand() % 4]; //Se asigna de manera aleatoria segun el random de 4 posibilidades
        habitats.push_back(h); //Pushea el habitat al vector de habitats
    }
}

void Zoologico::asignarAnimal(Animal* animal, int habitatID) {
    for (auto& h : habitats) { //foreach habitat en el vector habitats se usa auto& para hacer los cambios por referencia
        if (h.IDHabitat == habitatID) { 
            bool asignado = false;

            // Verificación de compatibilidad (valida que el habitat solo reciba ciertos animales en específico)
            if (h.tipoHabitat == "Aviario" && animal->getTipo() == "Ave") {
                h.animalesAsignados.push_back(animal);
                asignado = true;
            }
            else if (h.tipoHabitat == "Acuario" && animal->getTipo() == "Pez") {
                h.animalesAsignados.push_back(animal);
                asignado = true;
            }
            else if (h.tipoHabitat == "Laguna" &&
                (animal->getTipo() == "Anfibio" ||
                    animal->getTipo() == "Reptil" ||
                    animal->getTipo() == "Pez")) {
                h.animalesAsignados.push_back(animal);
                asignado = true;
            }
            else if (h.tipoHabitat == "Bosque" &&
                (animal->getTipo() == "Mamifero" ||
                    animal->getTipo() == "Reptil")) {
                h.animalesAsignados.push_back(animal);
                asignado = true;
            }

            // Si el animal NO era válido, genera uno nuevo adecuado para este habitat
            if (!asignado) {
                delete animal; // liberamos memoria del animal invalido
                Animal* nuevo = nullptr;
                double precio = 100 + rand() % 901; // se genera un nuevo precio aleatorio entre 100–1000
                int nuevoID = generarIDUnico(); // se genera un nuevo id
                if (h.tipoHabitat == "Aviario") {
                    nuevo = new Ave(nuevoID++, precio);
                }
                else if (h.tipoHabitat == "Acuario") {
                    nuevo = new Pez(nuevoID++, precio);
                }
                else if (h.tipoHabitat == "Laguna") {
                    int tipo = rand() % 3; // si el habitat recibe mas de un tipo de animal, este se elige aleatoriamente
                    if (tipo == 0) nuevo = new Anfibio(nuevoID++, precio);
                    else if (tipo == 1) nuevo = new Reptil(nuevoID++, precio);
                    else nuevo = new Pez(nuevoID++, precio);
                }
                else if (h.tipoHabitat == "Bosque") {
                    if (rand() % 2 == 0) nuevo = new Mamifero(nuevoID++, precio); // si el habitat recibe mas de un tipo de animal, este se elige aleatoriamente
                    else nuevo = new Reptil(nuevoID++, precio);
                }

                cout << "Se genero un nuevo animal válido para el habitat: " << h.tipoHabitat << endl;
                h.animalesAsignados.push_back(nuevo);
            }
            return;
        }
    }
}

void Zoologico::alimentarAnimales() { 
    int opcion;
    double gastoDia = 0;
    int animalesAlimentados = 0;
    int animalesDesnutridos = 0;

    cout << "\n=== SISTEMA DE ALIMENTACION ===" << endl;
    cout << "1. Alimentacion completa (costoso)" << endl;
    cout << "2. Alimentacion minima (economico)" << endl;
    cout << "3. No alimentar (riesgoso)" << endl;
    cout << "Seleccione opcion: ";
    
    cin >> opcion;

    for (auto& h : habitats) {
        for (auto a : h.animalesAsignados) { //foreach habitat en el vector habitats
            if (a->estaVivo()) { //si el animal esta vivo se le da por default 0 de comida para que esté hambriento
                int comidaADar = 0;

                switch (opcion) {
                case 1: // en este caso se le da de comer todas las unidades de comida que necesita cada animal
                    comidaADar = a->getUnidadesComida();
                    break;
                case 2: // en este caso se le da de comer la mitad de las unidades que necesita cada animal
                    comidaADar = a->getUnidadesComida() / 2;
                    break;
                case 3: // se da la opcion de no alimentar los animales con el riesgo de que mueran
                    comidaADar = 0;
                    break;
                }
                a->Alimentar(comidaADar); // se alimeta segun la opcion seleccionada
                gastoDia += 50 * comidaADar; // cada unidad de comida se multiplica por 50 (el costo de cada unidad)
                animalesAlimentados++;

                if (comidaADar < a->getUnidadesComida()) { // si la cantidad de comida dada al animal es menor a la que necesita este entra en estado de desnutricion
                    animalesDesnutridos++;
                }
            }
        }
    }

    gastosTotales += gastoDia;
    cout << "\n--- RESULTADO ALIMENTACION ---" << endl;
    cout << "Animales alimentados: " << animalesAlimentados << endl;
    cout << "Animales con comida insuficiente: " << animalesDesnutridos << endl;
    cout << "Gasto del dia: " << gastoDia << endl;
}


void Zoologico::aplicarTratamiento(int idAnimal, int opcion) {
    for (auto& h : habitats) { //foreach habitat en el vector habitats se usa auto& para hacer los cambios por referencia
        for (auto a : h.animalesAsignados) { //foreach habitat en el vector habitats
            if (a->getID() == idAnimal) { //Valida la existencia de ese id del animal
                switch (opcion) {
                case 1: a->TratarSuero(); gastosTotales += 100; break;
                case 2: a->TratarMedicina(); gastosTotales += 250; break;
                case 3: a->Vacunar(); gastosTotales += 500; break;
                }
                return;
            }
        }
    }
}

void Zoologico::avanzarDia() { 
    double ingresoDia = 0;
    int animalesMuertosHoy = 0;
    int animalesDesnutridosHoy = 0;

    cout << "\n=== AVANZANDO DIA ===" << endl;

    for (auto& h : habitats) { //foreach habitat en el vector habitats se usa auto& para hacer los cambios por referencia
        for (auto a : h.animalesAsignados) {
            if (a->estaVivo()) {
                // Simular que NO fueron alimentados hoy esto causa la desnutrición
                a->Alimentar(0);

                // Contar estados
                if (!a->estaNutrido()) {
                    animalesDesnutridosHoy++;
                }
                if (!a->estaVivo()) {
                    animalesMuertosHoy++;
                }
            }
        }
    }

    procesarReproduccion();

    for (auto& h : habitats) { //foreach habitat en el vector habitats se usa auto& para hacer los cambios por referencia
        for (auto a : h.animalesAsignados) {
            if (a->estaVivo()) { // se valida que el animal este con vida
                a->Enfermar();
                a->avanzarDia();
                ingresoDia += 0.5 * a->getPrecio(); // el ingreso diario se obtiene sumando el 50% del precio de cada animal

                if (!a->estaVivo()) { // Verificar si murió después de avanzar el día
                    animalesMuertosHoy++;
                }
            }
        }
    }

    ingresosTotales += ingresoDia; // se acumulan los ingresos del dia en los totales

    cout << "\n--- RESUMEN DEL DIA ---" << endl;
    cout << "Animales desnutridos: " << animalesDesnutridosHoy << endl;
    cout << "Animales muertos hoy: " << animalesMuertosHoy << endl;
    cout << "Ingreso del dia: " << ingresoDia << endl;
}
void Zoologico::procesarReproduccion() { 
    vector<Animal*> nuevasCrias;

    for (auto& h : habitats) { //foreach habitat en el vector habitats se usa auto& para hacer los cambios por referencia
        for (auto a : h.animalesAsignados) {
            if (a->puedeReproducirse()) { // se llama al metodo que valida si el animal puede reproducirse o no
                Animal* cria = a->reproducir(generarIDUnico()); // en caso de hacerlo se crea una instancia nueva de Animal, en conjunto con un su ID
                if (cria != nullptr) { // si el espacio de memoria de la cria no esta vacia significa que nacio una nueva y se pushea al vector nuevasCrias
                    nuevasCrias.push_back(cria);
                    cout << "Nueva cria de " << a->getTipo() << " nacida en habitat " << h.IDHabitat << " con ID " << cria->getID() << endl;
                }
            }
        }
    }

    for (auto cria : nuevasCrias) { // Asignar crias a habitats aleatorios
        int habitatID = 1 + rand() % habitats.size(); // se elige aleatoriamente a que habitat se ingresara la cria
        asignarAnimal(cria, habitatID); // se valida que la cria sea del tipo que acepta el habitat
    }
}
void Zoologico::mostrarReporteFinal() const { // este metodo recoge varios datos totales para presentarlo al final de la simulacion
    double totalVivos = 0;
    double totalFallecidos = 0;
    int countVivos = 0;
    int countFallecidos = 0;

    cout << "\n===== REPORTE FINAL =====" << endl;

    for (auto& h : habitats) { //foreach habitat en el vector habitats se usa auto& para hacer los cambios por referencia
        cout << "\nHabitat " << h.IDHabitat << " (" << h.tipoHabitat << "):" << endl;

        for (auto a : h.animalesAsignados) { 
            string estado = a->estaVivo() ? "Vivo" : "Muerto";
            if (a->estaVivo()) { // si el animal esta vivo se incrementa la cantidad de animales vivos
                totalVivos += a->getPrecio();
                countVivos++;
            }
            else {
                totalFallecidos += a->getPrecio(); // caso contrario se incrementan los fallecidos
                countFallecidos++;
            }

            cout << " - ID: " << a->getID() << " Tipo: " << a->getTipo() << " Precio: " << a->getPrecio() << " Estado: " << estado << endl;
        }
    }

    cout << "\n----- RESUMEN FINAL -----" << endl;
    cout << "Animales vivos: " << countVivos << " - Valor total: " << totalVivos << endl;
    cout << "Animales fallecidos: " << countFallecidos << " - Valor perdido: " << totalFallecidos << endl;
    cout << "Total invertido en comida: " << gastosTotales << endl;
    cout << "Total de ingresos generados: " << ingresosTotales << endl;
    cout << "Balance neto: " << (ingresosTotales - gastosTotales) << endl;
}
string Zoologico::getTipoHabitat(int habitatID) const { // devuelve el tipo de habitat, basado en el ID que tiene asignado
    for (const auto& h : habitats) { 
        if (h.IDHabitat == habitatID) {
            return h.tipoHabitat;
        }
    }
    return ""; // Retorna string vacio si no encuentra el habitat
}


void Zoologico::mostrarReporteAnimales() const { // se muestra la informacion individual de cada animal
    for (auto& h : habitats) {  // se muestra para cada habitat su informacion
        cout << "\nHabitat " << h.IDHabitat << " (" << h.tipoHabitat << "):" << endl; 
        for (auto a : h.animalesAsignados) {  // se muestra para cada animal su informacion
            string estadoSalud;
            switch (a->getSalud()) { // como el estado de salud esta guardado en un enum, primero se obtiene el valor y se almacena en un string para poder imprimirlo
            case EstadoSalud::Saludable: estadoSalud = "Saludable"; break;
            case EstadoSalud::EnfermoLeve: estadoSalud = "Enfermo Leve"; break;
            case EstadoSalud::EnfermoGrave: estadoSalud = "Enfermo Grave"; break;
            case EstadoSalud::Fallecido: estadoSalud = "Fallecido"; break;
            default: estadoSalud = "Desconocido"; break;
            }

            cout << " - ID: " << a->getID()
                << " Tipo: " << a->getTipo()
                << " Precio: " << a->getPrecio()
                << " Estado: " << (a->estaVivo() ? "Vivo" : "Muerto")
                << " / Nutricion: " << (a->estaNutrido() ? "Nutrido" : "Desnutrido")
                << " / Salud: " << estadoSalud
                << endl;
        }
    }
    cout << "\nIngresos totales: " << ingresosTotales << endl; 
    cout << "Gastos totales: " << gastosTotales << endl;
}
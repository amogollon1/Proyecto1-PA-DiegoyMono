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
    for (auto& h : habitats) {
        if (h.IDHabitat == habitatID) {
            bool asignado = false;

            // Verificación de compatibilidad
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

            // Si el animal NO era válido, generar uno nuevo adecuado para este hábitat
            if (!asignado) {
                delete animal; // liberamos memoria del animal inválido
                Animal* nuevo = nullptr;
                double precio = 100 + rand() % 901; // precio aleatorio entre 100–1000
                int nuevoID = generarIDUnico();
                if (h.tipoHabitat == "Aviario") {
                    nuevo = new Ave(nuevoID++, precio);
                }
                else if (h.tipoHabitat == "Acuario") {
                    nuevo = new Pez(nuevoID++, precio);  // Usamos siguienteID global
                }
                else if (h.tipoHabitat == "Laguna") {
                    int tipo = rand() % 3; // aleatorio entre 0 y 2
                    if (tipo == 0) nuevo = new Anfibio(nuevoID++, precio);
                    else if (tipo == 1) nuevo = new Reptil(nuevoID++, precio);
                    else nuevo = new Pez(nuevoID++, precio);
                }
                else if (h.tipoHabitat == "Bosque") {
                    if (rand() % 2 == 0) nuevo = new Mamifero(nuevoID++, precio);
                    else nuevo = new Reptil(nuevoID++, precio);
                }

                cout << "Se genero un nuevo animal válido para el habitat: "
                    << h.tipoHabitat << endl;

                h.animalesAsignados.push_back(nuevo);
            }

            return;
        }
    }
}
//void Zoologico::alimentarAnimales() {
//    int opcionAlimentacion;
//    cout << "\nOpciones de alimentacion:" << endl;
//    cout << "1. Alimentar todos completamente" << endl;
//    cout << "2. Alimentar con cantidad minima" << endl;
//    cout << "3. No alimentar" << endl;
//    cout << "Seleccione opcion: ";
//    cin >> opcionAlimentacion;
//
//    double gastoDia = 0;
//
//    for (auto& h : habitats) {
//        for (auto a : h.animalesAsignados) {
//            if (a->estaVivo()) {
//                int comidaADar = 0;
//
//                switch (opcionAlimentacion) {
//                case 1: // Alimentar completamente
//                    comidaADar = a->getUnidadesComida();
//                    break;
//                case 2: // Alimentar con cantidad minima (50%)
//                    comidaADar = a->getUnidadesComida() / 2;
//                    break;
//                case 3: // No alimentar
//                    comidaADar = 0;
//                    break;
//                default:
//                    comidaADar = a->getUnidadesComida();
//                }
//
//                a->Alimentar(comidaADar);
//                gastoDia += 50 * comidaADar;
//            }
//        }
//    }
//
//    gastosTotales += gastoDia;
//    cout << "Gasto en comida este dia: " << gastoDia << endl;
//}
void Zoologico::alimentarAnimales() {
    cout << "\n=== SISTEMA DE ALIMENTACION ===" << endl;
    cout << "1. Alimentacion completa (costoso)" << endl;
    cout << "2. Alimentacion minima (economico)" << endl;
    cout << "3. No alimentar (riesgoso)" << endl;
    cout << "Seleccione opcion: ";

    int opcion;
    cin >> opcion;

    double gastoDia = 0;
    int animalesAlimentados = 0;
    int animalesDesnutridos = 0;

    for (auto& h : habitats) {
        for (auto a : h.animalesAsignados) {
            if (a->estaVivo()) {
                int comidaADar = 0;

                switch (opcion) {
                case 1: // Completa
                    comidaADar = a->getUnidadesComida();
                    break;
                case 2: // Minima (50%)
                    comidaADar = a->getUnidadesComida() / 2;
                    break;
                case 3: // No alimentar
                    comidaADar = 0;
                    break;
                }
                a->Alimentar(comidaADar);
                gastoDia += 50 * comidaADar;
                animalesAlimentados++;

                if (comidaADar < a->getUnidadesComida()) {
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


//void Zoologico::alimentarAnimales() {
//    for (auto& h : habitats) {
//        for (auto a : h.animalesAsignados) { //Dentro de cada habitat recorre cada animal a
//            a->Alimentar(a->getUnidadesComida()); //LLama al metodo alimentar a-> porque son punteros 
//            gastosTotales += 50 * a->getUnidadesComida(); // cada unidad cuesta 50
//        }
//    }
//}

void Zoologico::aplicarTratamiento(int idAnimal, int opcion) {
    for (auto& h : habitats) {
        for (auto a : h.animalesAsignados) {
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

//void Zoologico::avanzarDia() {
//    double ingresoDia = 0;
//    for (auto& h : habitats) {
//        for (auto a : h.animalesAsignados) {
//            if (a->estaVivo()) {
//                a->Enfermar(); //enfermar segun las probabilidades
//                ingresoDia += 0.5 * a->getPrecio(); //al finalizar el dia, en este caso el bloque de codigo, le suma la mitad del precio original del animal como ganancia
//            }
//        }
//    }
//    ingresosTotales += ingresoDia; //a ingresos totales se le añadira el ingreso del dia constantemente
//    cout << "Ingreso del dia: " << ingresoDia << endl;
//}
void Zoologico::avanzarDia() {
    double ingresoDia = 0;
    int animalesMuertosHoy = 0;
    int animalesDesnutridosHoy = 0;

    cout << "\n=== AVANZANDO DIA ===" << endl;

    // 1. Primero procesar la falta de alimentación
    for (auto& h : habitats) {
        for (auto a : h.animalesAsignados) {
            if (a->estaVivo()) {
                // Simular que NO fueron alimentados hoy (esto causa desnutrición)
                // Pasamos 0 unidades de comida para forzar la desnutrición
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

    // 2. Luego procesar reproducción y enfermedad
    procesarReproduccion();

    for (auto& h : habitats) {
        for (auto a : h.animalesAsignados) {
            if (a->estaVivo()) {
                a->Enfermar();
                a->avanzarDia();
                ingresoDia += 0.5 * a->getPrecio();

                // Verificar si murió después de avanzar el día
                if (!a->estaVivo()) {
                    animalesMuertosHoy++;
                }
            }
        }
    }

    ingresosTotales += ingresoDia;

    cout << "\n--- RESUMEN DEL DIA ---" << endl;
    cout << "Animales desnutridos: " << animalesDesnutridosHoy << endl;
    cout << "Animales muertos hoy: " << animalesMuertosHoy << endl;
    cout << "Ingreso del dia: " << ingresoDia << endl;
}
void Zoologico::procesarReproduccion() { //NUEVO DEEPSEEK
    vector<Animal*> nuevasCrias;

    for (auto& h : habitats) {
        for (auto a : h.animalesAsignados) {
            if (a->puedeReproducirse()) {
                Animal* cria = a->reproducir(generarIDUnico());
                if (cria != nullptr) {
                    nuevasCrias.push_back(cria);
                    cout << "Nueva cría de " << a->getTipo() << " nacida en hábitat "
                        << h.IDHabitat << " con ID " << cria->getID() << endl;
                }
            }
        }
    }

    // Asignar crías a habitats aleatorios
    for (auto cria : nuevasCrias) {
        int habitatID = 1 + rand() % habitats.size();
        asignarAnimal(cria, habitatID);
    }
}
void Zoologico::mostrarReporteFinal() const { //NUEVO DEEPSEEK
    double totalVivos = 0;
    double totalFallecidos = 0;
    int countVivos = 0;
    int countFallecidos = 0;

    cout << "\n===== REPORTE FINAL =====" << endl;

    for (auto& h : habitats) {
        cout << "\nHabitat " << h.IDHabitat << " (" << h.tipoHabitat << "):" << endl;

        for (auto a : h.animalesAsignados) {
            string estado = a->estaVivo() ? "Vivo" : "Muerto";
            if (a->estaVivo()) {
                totalVivos += a->getPrecio();
                countVivos++;
            }
            else {
                totalFallecidos += a->getPrecio();
                countFallecidos++;
            }

            cout << " - ID: " << a->getID()
                << " Tipo: " << a->getTipo()
                << " Precio: " << a->getPrecio()
                << " Estado: " << estado
                << endl;
        }
    }

    cout << "\n----- RESUMEN FINAL -----" << endl;
    cout << "Animales vivos: " << countVivos << " - Valor total: " << totalVivos << endl;
    cout << "Animales fallecidos: " << countFallecidos << " - Valor perdido: " << totalFallecidos << endl;
    cout << "Total invertido en comida: " << gastosTotales << endl;
    cout << "Total de ingresos generados: " << ingresosTotales << endl;
    cout << "Balance neto: " << (ingresosTotales - gastosTotales) << endl;
}
string Zoologico::getTipoHabitat(int habitatID) const {
    for (const auto& h : habitats) {
        if (h.IDHabitat == habitatID) {
            return h.tipoHabitat;
        }
    }
    return ""; // Retorna string vacío si no encuentra el hábitat
}


void Zoologico::mostrarReporteAnimales() const {
    for (auto& h : habitats) {
        //Para cada habitat su informacion
        cout << "\nHabitat " << h.IDHabitat << " (" << h.tipoHabitat << "):" << endl;
        //para cada animal su informacion
        for (auto a : h.animalesAsignados) {
            string estadoSalud;
            switch (a->getSalud()) {
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


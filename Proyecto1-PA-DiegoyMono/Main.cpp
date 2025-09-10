#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ClaseAnimal.h"
#include "Animal-Hijas.h"
#include "ClaseZoologico.h"
#include "EstructuraHabitat.h"
#include "pch.h"


using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));
    // inicializar aleatoriedad con una semilla distinta cada vez que se ejecute el programa, static cast unsigned int es una manera de convertir el formato horario a un entero unsigned (sin negativos) ya que no siempre sería el caso tratando con la hora
   // ¿Que pasa si no está esta linea? -> el programa utilizaria la semilla default de srand que es 1, por lo que se incializaria cada vez con los mismos valores
    Zoologico zoo;

    int numHabitats, numAnimales, numDias;

    cout << "---------CONFIGURACION INICIAL---------" << endl;
    
    cout << "Ingrese la cantidad de habitats: ";
    cin >> numHabitats;
    zoo.configurarHabitats(numHabitats);

    cout << "Ingrese la cantidad de animales: ";
    cin >> numAnimales;

    //// Crear animales y asignar a habitats
    //for (int i = 0; i < numAnimales; i++) {
    //    int tipo = rand() % 5; // Aleatorio entre 0 y 4
    //    double precio = 100 + rand() % 901; // 100–1000
    //    Animal* nuevoAnimal = nullptr;

    //    switch (tipo) {
    //    case 0: nuevoAnimal = new Ave(i + 1, precio); cout << "\nAve: " << nuevoAnimal->MostrarDescripcion() << endl; break; //asigna los ids por i + 1 para empezar en 1
    //    case 1: nuevoAnimal = new Mamifero(i + 1, precio);   cout << "\nMamifero: " << nuevoAnimal->MostrarDescripcion() << endl; break;
    //    case 2: nuevoAnimal = new Reptil(i + 1, precio);  cout << "\nReptil: " << nuevoAnimal->MostrarDescripcion() << endl; break;
    //    case 3: nuevoAnimal = new Pez(i + 1, precio);  cout << "\nPez: " << nuevoAnimal->MostrarDescripcion() << endl;break;
    //    case 4: nuevoAnimal = new Anfibio(i + 1, precio);  cout << "\nAnfibio: " << nuevoAnimal->MostrarDescripcion() << endl;break;
    //    }

    //    int habitatAsignado = 1 + rand() % numHabitats; //hace un rango de numero aleatorios de numHabitats, por ejemplo numHabitats = 4, rango de numeros aleatorios = 0,1,2,3
    //    //+1 porque no tratamos con 0 habitats asignados
    //    zoo.asignarAnimal(nuevoAnimal, habitatAsignado);
    //}

    // Primero: asignar al menos un animal compatible a cada hábitat
    for (int i = 0; i < numHabitats; i++) {
        Animal* nuevoAnimal = nullptr;
        double precio = 100 + rand() % 901;

        string tipoHabitat = zoo.getTipoHabitat(i + 1);
        int nuevoID = Zoologico::generarIDUnico(); // Usar ID único

        if (tipoHabitat == "Aviario") {
            nuevoAnimal = new Ave(nuevoID, precio);
        }
        else if (tipoHabitat == "Acuario") {
            nuevoAnimal = new Pez(nuevoID, precio);
        }
        else if (tipoHabitat == "Laguna") {
            int tipo = rand() % 3;
            if (tipo == 0) nuevoAnimal = new Anfibio(nuevoID, precio);
            else if (tipo == 1) nuevoAnimal = new Reptil(nuevoID, precio);
            else nuevoAnimal = new Pez(nuevoID, precio);
        }
        else if (tipoHabitat == "Bosque") {
            int tipo = rand() % 2;
            if (tipo == 0) nuevoAnimal = new Mamifero(nuevoID, precio);
            else nuevoAnimal = new Reptil(nuevoID, precio);
        }

        zoo.asignarAnimal(nuevoAnimal, i + 1);
        cout << "\n" << nuevoAnimal->getTipo() << " (ID: " << nuevoID << "): "
            << nuevoAnimal->MostrarDescripcion() << endl;
    }

    // Segundo: asignar los animales restantes aleatoriamente
    for (int i = numHabitats; i < numAnimales; i++) {
        int tipo = rand() % 5;
        double precio = 100 + rand() % 901;
        Animal* nuevoAnimal = nullptr;
        int nuevoID = Zoologico::generarIDUnico(); // Usar ID único

        switch (tipo) {
        case 0: nuevoAnimal = new Ave(nuevoID, precio); break;
        case 1: nuevoAnimal = new Mamifero(nuevoID, precio); break;
        case 2: nuevoAnimal = new Reptil(nuevoID, precio); break;
        case 3: nuevoAnimal = new Pez(nuevoID, precio); break;
        case 4: nuevoAnimal = new Anfibio(nuevoID, precio); break;
        }

        int habitatAsignado = 1 + rand() % numHabitats;
        zoo.asignarAnimal(nuevoAnimal, habitatAsignado);
        cout << "\n" << nuevoAnimal->getTipo() << " (ID: " << nuevoID << "): "
            << nuevoAnimal->MostrarDescripcion() << endl;
    }



    cout << "Ingrese la cantidad de dias a simular: ";
    cin >> numDias;

    // Bucle de simulación
    for (int dia = 1; dia <= numDias; dia++) {
        cout << "\n------ DIA " << dia << " -----" << endl;

        int opcion;
        do {
            cout << "\nMenu de opciones:" << endl;
            cout << "1. Ver reporte de animales" << endl;
            cout << "2. Alimentar animales" << endl;
            cout << "3. Tratamiento medico" << endl;
            cout << "4. Avanzar de dia" << endl;
            cout << "0. Salir de la simulacion" << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                zoo.mostrarReporteAnimales();
                
                break;
            case 2:
                zoo.alimentarAnimales();
                break;
            case 3: {
                int id, tipoTrat;
                cout << "Ingrese ID del animal: ";
                cin >> id;
                cout << "Tratamiento: 1=Suero (100), 2=Medicina (250), 3=Vacuna (500): ";
                cin >> tipoTrat;
                zoo.aplicarTratamiento(id, tipoTrat);
                break;
            }
            case 4:
                zoo.avanzarDia();
                break;
            case 0:
                cout << "Saliendo de la simulacion..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
            }
        } while (opcion != 4 && opcion != 0); // avanzar o salir

        if (opcion == 0) break; // usuario decidió salir
    }

    cout << "\n===== SIMULACION FINALIZADA =====" << endl; //NUEVO DEEPSEEK
    zoo.mostrarReporteFinal(); // Cambiar por el nuevo método

    return 0;
}


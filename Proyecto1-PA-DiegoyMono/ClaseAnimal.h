#pragma once
#include <iostream>
#include <string>
using namespace std;

// Enumeraciones para mejor control de estados, son como arreglos definidos que permiten un mejor manejo de cierto estado a comparacion de un bool, nos permite acceder directamente al tipo de estado sin tener que hacer logica de arreglos compleja, funcionan como clases: https://www.geeksforgeeks.org/cpp/enum-classes-in-c-and-their-advantage-over-enum-datatype
enum class EstadoNutricion { Nutrido, Desnutrido };
enum class EstadoSalud { Saludable, EnfermoLeve, EnfermoGrave, Fallecido };

class Animal {
protected:
    int IDAnimal;
    string tipoAnimal;
    int unidades_comida;
    double probabilidad_nacimiento;
    double probabilidad_enfermedad;
    double precioAnimal;
    EstadoNutricion estadoNutricion;
    EstadoSalud estadoSalud;

public:
    Animal(int id, string tipo, int comida, double probNac, double probEnf, double precio);

    virtual ~Animal() {}

    // Método virtual
    virtual string MostrarDescripcion() const = 0;

    // Métodos comunes que se repiten para los animales
    void Alimentar(int comida);
    void Enfermar();
    void TratarSuero();
    void TratarMedicina();
    void Vacunar();

    // Metodos de obtencion de datos
    int getID() const { return IDAnimal; }
    string getTipo() const { return tipoAnimal; }
    double getPrecio() const { return precioAnimal; }
    EstadoNutricion getNutricion() const { return estadoNutricion; } //Declaracion de los enum como clases, con su metodo para obtener el estado
    EstadoSalud getSalud() const { return estadoSalud; }
    bool estaVivo() const { return estadoSalud != EstadoSalud::Fallecido; } //Metodo especial ya que contiene algo de logica dentro de si, llama una instancia del enum y devolvera el contrario, en este caso por default un animal esta vivo
    bool estaNutrido() const { return estadoNutricion != EstadoNutricion::Desnutrido; }
    void avanzarDia(); // Nuevo método //DeepSeek NUEVO
    void setMaxDiasResistencia(int dias) { maxDiasResistencia = dias; } //DeepSeek NUEVO
    int getDiasEnfermo() const { return diasEnfermo; } //DeepSeek NUEVO
    int getUnidadesComida() const { return unidades_comida; }

    bool puedeReproducirse() const; //DeepSeek NUEVO
    Animal* reproducir(int nuevoID); //DeepSeek NUEVO
    double getProbabilidadNacimiento() const { return probabilidad_nacimiento; } //DeepSeek NUEVO

private: //DeepSeek NUEVO
    int diasEnfermo = 0; // Añadir este atributo
    int maxDiasResistencia = 0; // Añadir este atributo
};


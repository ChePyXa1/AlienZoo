#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <utility>
#include <random>
#include <iostream>

enum class Gender { MALE, FEMALE };
enum class AnimalType { CARNIVORE, HERBIVORE, AQUATIC };

// Структура для хранения информации о родителях
struct ParentInfo {
    std::string name;
    std::string species;
    Gender gender;

    ParentInfo(const std::string& name = "", const std::string& species = "", Gender gender = Gender::MALE)
        : name(name), species(species), gender(gender) {}
};

class Animal {
private:
    std::string name;
    std::string species; // Вид животного
    int ageInDays;       // Возраст в днях
    double weight;       // Вес животного
    std::string preferredClimate;
    double price;        // Цена животного
    AnimalType type;     // Тип животного (хищник, травоядное и т.д.)
    Gender gender;       // Пол животного
    std::pair<ParentInfo, ParentInfo> parents; // Информация о родителях
    bool isBornInZoo;    // Указывает, родилось ли животное в зоопарке

    // Методы для генерации случайных чисел
    int generateRandomInt(int min, int max) const;
    double generateRandomDouble(double min, double max) const;

public:
    // Конструктор
    Animal(const std::string& name, const std::string& species, Gender gender,
        int ageInDays = 0, double weight = -1, const std::string& preferredClimate = "",
        double price = 0.0, AnimalType type = AnimalType::CARNIVORE, bool isBornInZoo = false,
        const std::string& parent1Name = "", const std::string& parent2Name = "");


    // Деструктор
    ~Animal();

    // Геттеры
    std::string getName() const;
    std::string getSpecies() const;
    int getAgeInDays() const;
    double getWeight() const;
    std::string getPreferredClimate() const;
    double getPrice() const;
    AnimalType getType() const;
    Gender getGender() const;
    std::pair<ParentInfo, ParentInfo> getParents() const;
    bool wasBornInZoo() const;

    // Сеттеры
    void setName(const std::string& newName);
    void increaseAgeInDays();
    bool checkDeathAfterTenDays() const;

    // Перегрузка оператора для размножения
    Animal* operator+(Animal& partner);
};

#endif

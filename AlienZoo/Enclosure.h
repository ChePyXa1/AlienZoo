#ifndef ENCLOSURE_H
#define ENCLOSURE_H

#include <string>
#include "Animal.h"

class Enclosure {
private:
    int capacity; // Вместимость вольера
    AnimalType allowedType; // Тип разрешённых животных
    double dailyExpense; // Ежедневные расходы
    int currentCount; // Текущее количество животных
    std::string climate; // Климат вольера

public:
    Enclosure(int capacity, AnimalType allowedType, double dailyExpense, const std::string& climate);

    // Методы доступа
    int getCapacity() const;
    AnimalType getAllowedType() const;
    double getDailyExpense() const;
    int getCurrentCount() const;
    std::string getClimate() const;

    // Управление животными
    void addAnimal();
    void removeAnimal();
    bool hasFreeSlot() const; // Новый метод для проверки слота
};

#endif

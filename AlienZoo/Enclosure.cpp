#include "Enclosure.h"

// Конструктор
Enclosure::Enclosure(int capacity, AnimalType allowedType, double dailyExpense, const std::string& climate)
    : capacity(capacity), allowedType(allowedType), dailyExpense(dailyExpense), currentCount(0), climate(climate) {}

int Enclosure::getCapacity() const { return capacity; }
AnimalType Enclosure::getAllowedType() const { return allowedType; }
double Enclosure::getDailyExpense() const { return dailyExpense; }
int Enclosure::getCurrentCount() const { return currentCount; }
std::string Enclosure::getClimate() const { return climate; }

void Enclosure::addAnimal() {
    if (currentCount < capacity) currentCount++;
}

void Enclosure::removeAnimal() {
    if (currentCount > 0) currentCount--;
}

bool Enclosure::hasFreeSlot() const {
    return currentCount < capacity;
}

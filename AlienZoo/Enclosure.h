#ifndef ENCLOSURE_H
#define ENCLOSURE_H

#include <string>
#include "Animal.h"

class Enclosure {
private:
    int capacity; // ����������� �������
    AnimalType allowedType; // ��� ����������� ��������
    double dailyExpense; // ���������� �������
    int currentCount; // ������� ���������� ��������
    std::string climate; // ������ �������

public:
    Enclosure(int capacity, AnimalType allowedType, double dailyExpense, const std::string& climate);

    // ������ �������
    int getCapacity() const;
    AnimalType getAllowedType() const;
    double getDailyExpense() const;
    int getCurrentCount() const;
    std::string getClimate() const;

    // ���������� ���������
    void addAnimal();
    void removeAnimal();
    bool hasFreeSlot() const; // ����� ����� ��� �������� �����
};

#endif

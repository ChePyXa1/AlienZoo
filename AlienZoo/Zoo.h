#ifndef ZOO_H
#define ZOO_H

#include <string>
#include <vector>
#include "Employee.h"
#include "Animal.h"
#include "Enclosure.h"

// ��������� ��� �������� ���������� � ��������
struct AnimalInfo {
    std::string name;       // ��� ���������
    std::string species;    // ��� ���������
    double price;           // ����
    AnimalType type;        // ��� (������, ����������, �������������)
    std::string climate;    // ������
};

// ��������� ������� ��������
struct SickAnimal {
    Animal* animal;
    int daysSick;  // ���������� ���� �������
};

class Zoo {
private:
    std::string name;              // ��� ��������
    int food;                      // ���������� ���
    double money;                  // ������ ��������
    int popularity;                // ������������ ��������
    int currentDay;                // ������� ����
    int availableFeeders = 0;

    std::vector<SickAnimal> sickAnimals; // ������� ��������
    std::vector<Employee> employees;     // ������ �����������
    std::vector<Animal*> animals;        // ������ ��������
    std::vector<Enclosure> enclosures;   // ������ ��������

    static const std::vector<AnimalInfo> animalOptions; // ������ ��������� ��������

    // ��������������� ������
    void processVeterinarianShortage(int shortage);  // ��������� �������� �����������
    void processCleanerShortage(int shortage);       // ��������� �������� ���������
    void processFeederShortage(int shortage);        // ��������� �������� ������������
    int dailyAnimalPurchases; // ����� ������� �������� � ����
    std::vector<Animal*> purchasePool; // ��� �������� ��� �������

public:
    // ����������� � ����������
    Zoo(const std::string& name);
    ~Zoo(); // ������� ����������� ��������� ��������
    void refreshPurchasePool(); // ���������� ���� ��������
    void updatePurchasePool();  // ���������� ���� �������� �� ������

    // ����� ���������� � ��������� ��������
    void displayStatus() const;    // ����� �������� ��������� ��������
    void displayMenu() const;      // ����� ����
    void processChoice();          // ��������� ������ ������������
    void listAnimals() const;      // ����� ������ ��������

    // ���� ����������
    void manageAnimals();          // ���������� ��������
    void manageProcurements();     // ���������� �������
    void manageBuildings();        // ���������� ��������
    void displayEnclosureInfo() const; // ���������� � ��������

    // �������� ���������
    void breedAnimals();           // ����������� ��������
    void renameAnimal();
    void buyAnimal();              // ������� ��������
    void sellAnimal();             // ������� ��������
    void buyFood();                // ������� ���
    void advertise();              // ������� ��������
    void buyEnclosure();           // ������� ��������
    void addAnimalToEnclosure(Animal* child, AnimalType type); // ���������� ��������� � ������
    void healAnimal();             // ������� ������� ��������

    // ������� � ���������� ���: ���������� �����������
    void nextDay();                // ������� � ���������� ���

    // �������
    int totalAnimalCount() const;  // ������� ���� ��������
    bool isGameOver() const;       // �������� ���������� ����
    int getCurrentDay() const { return currentDay; } // ��������� �������� ���

    // ���������� �����������
    void manageEmployees();        // ���� ���������� ������������
    void hireEmployee();           // ������ ���������
    void fireEmployee();           // ������� ���������
    void listEmployees() const;    // ����������� ������ ����������
};

#endif

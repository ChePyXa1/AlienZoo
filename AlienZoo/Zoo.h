#ifndef ZOO_H
#define ZOO_H

#include <string>
#include <vector>
#include "Employee.h"
#include "Animal.h"
#include "Enclosure.h"

// Структура для хранения информации о животных
struct AnimalInfo {
    std::string name;       // Имя животного
    std::string species;    // Вид животного
    double price;           // Цена
    AnimalType type;        // Тип (хищник, травоядное, водоплавающее)
    std::string climate;    // Климат
};

// Структура больных животных
struct SickAnimal {
    Animal* animal;
    int daysSick;  // Количество дней болезни
};

class Zoo {
private:
    std::string name;              // Имя зоопарка
    int food;                      // Количество еды
    double money;                  // Деньги зоопарка
    int popularity;                // Популярность зоопарка
    int currentDay;                // Текущий день
    int availableFeeders = 0;

    std::vector<SickAnimal> sickAnimals; // Больные животные
    std::vector<Employee> employees;     // Список сотрудников
    std::vector<Animal*> animals;        // Список животных
    std::vector<Enclosure> enclosures;   // Список вольеров

    static const std::vector<AnimalInfo> animalOptions; // Список доступных животных

    // Вспомогательные методы
    void processVeterinarianShortage(int shortage);  // Обработка нехватки ветеринаров
    void processCleanerShortage(int shortage);       // Обработка нехватки уборщиков
    void processFeederShortage(int shortage);        // Обработка нехватки кормильщиков
    int dailyAnimalPurchases; // Лимит покупок животных в день
    std::vector<Animal*> purchasePool; // Пул животных для покупки

public:
    // Конструктор и деструктор
    Zoo(const std::string& name);
    ~Zoo(); // Удаляет динамически созданных животных
    void refreshPurchasePool(); // Обновление пула животных
    void updatePurchasePool();  // Обновление пула животных за деньги

    // Вывод информации о состоянии зоопарка
    void displayStatus() const;    // Вывод текущего состояния зоопарка
    void displayMenu() const;      // Вывод меню
    void processChoice();          // Обработка выбора пользователя
    void listAnimals() const;      // Вывод списка животных

    // Меню управления
    void manageAnimals();          // Менеджмент животных
    void manageProcurements();     // Менеджмент закупок
    void manageBuildings();        // Менеджмент построек
    void displayEnclosureInfo() const; // Информация о вольерах

    // Действия подсистем
    void breedAnimals();           // Размножение животных
    void renameAnimal();
    void buyAnimal();              // Покупка животных
    void sellAnimal();             // Продажа животных
    void buyFood();                // Покупка еды
    void advertise();              // Реклама зоопарка
    void buyEnclosure();           // Покупка вольеров
    void addAnimalToEnclosure(Animal* child, AnimalType type); // Добавление животного в вольер
    void healAnimal();             // Лечение больных животных

    // Переход к следующему дню: перерасчёт показателей
    void nextDay();                // Переход к следующему дню

    // Утилиты
    int totalAnimalCount() const;  // Подсчёт всех животных
    bool isGameOver() const;       // Проверка завершения игры
    int getCurrentDay() const { return currentDay; } // Получение текущего дня

    // Менеджмент сотрудников
    void manageEmployees();        // Меню управления сотрудниками
    void hireEmployee();           // Нанять работника
    void fireEmployee();           // Уволить работника
    void listEmployees() const;    // Просмотреть список работников
};

#endif

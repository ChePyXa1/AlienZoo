#include "Zoo.h"
#include "Enclosure.h"
#include "Employee.h"
#include "Animal.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// ����������� ��������
Zoo::Zoo(const std::string& zooName)
    : name(zooName), food(100), money(100000), popularity(10), currentDay(1), dailyAnimalPurchases(0) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<Employee> employees;
    refreshPurchasePool();
    std::cout << "������� \"" << name << "\" ������!\n";
}

// ���������� ��������
Zoo::~Zoo() {
    // ������� ����������� ��������� ��������
    for (auto animal : animals) {
        delete animal;
    }
}

// ����������� ��������� ��������
void Zoo::displayStatus() const {
    std::cout << "\n=== ���� " << currentDay << " ===\n";
    std::cout << "�������: " << name << "\n";
    std::cout << "���: " << food << "\n";
    std::cout << "������: " << money << "\n";

    if (currentDay == 1) {
        // ������������ � ���������� ����� ���� �� ������ ����
        std::cout << "������������: 0\n";
        std::cout << "����������: 0\n\n";
        std::cout << "������ ���� - ��� ���� �� �������� ��������\n������������� � �������� ��������:\n������ ��������\n������� ������ �����������\n����������� �������\n";
    }
    else {
        std::cout << "������������: " << popularity << "\n";
        std::cout << "���������� ��������: " << totalAnimalCount() << "\n";

        int visitors = 2 * popularity;

        // ��������� ������� ������������� �������� (��������)
        int aquaticCount = 0;
        for (auto animal : animals) {
            if (animal->getType() == AnimalType::AQUATIC) {
                aquaticCount++;
            }
        }
        if (aquaticCount > 0) {
            visitors *= (1 << aquaticCount); // �������� �� ������� �������
        }
        if (totalAnimalCount() == 0) {
            visitors = 0;
            std::cout << "����������: " << visitors << "\n";
        }
        else {
            std::cout << "����������: " << visitors << "\n";
        }
    }
}

// ����������� �������� ����
void Zoo::displayMenu() const {
    std::cout << "\n�������� ��������:\n";
    std::cout << "1. ���������� ��������\n";
    std::cout << "2. ���������� ������� (���, �������)\n";
    std::cout << "3. ���������� �������� (�������)\n";
    std::cout << "4. ������� � ���������� ���\n";
    std::cout << "5. ���������� ����������\n";
}

// ��������� ������ ������������
void Zoo::processChoice() {
    int choice;

    while (true) {
        std::cout << "������� ��� ����� (1�5): ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������ �����. ����������, ������� ����� ����� �� 1 �� 5.\n";
            continue;
        }

        if (choice < 1 || choice > 5) {
            std::cout << "�������� ����. ������� ����� �� 1 �� 5.\n";
            continue;
        }

        break;
    }

    switch (choice) {
    case 1:
        manageAnimals();
        break;
    case 2:
        manageProcurements();
        break;
    case 3:
        manageBuildings();
        break;
    case 4:
        nextDay();
        break;
    case 5:
        manageEmployees();
        break;
    default:
        std::cout << "�������� �����. ������� ����� �� 1 �� 5.\n";
        break;
    }
}

void Zoo::manageAnimals() {
    std::cout << "\n���������� ��������:\n";
    std::cout << "1. ������ ��������\n";
    std::cout << "2. ������� ��������\n";
    std::cout << "3. ����������� ���� ��������\n";
    std::cout << "4. �������� ��� ��������\n";
    std::cout << "5. ������������� ��������\n";
    std::cout << "6. ����������� ��������\n";
    std::cout << "7. ������� ������� ��������\n";

    std::cout << "��� �����: ";
    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        buyAnimal();
        break;
    case 2:
        sellAnimal();
        break;
    case 3:
        listAnimals();
        break;
    case 4:
        refreshPurchasePool();
        break;
    case 5:
        renameAnimal();
        break;
    case 6:
        breedAnimals();
        break;
    case 7:
        healAnimal();
        break;
    default:
        std::cout << "�������� �����.\n";
        break;
    }
}

const std::vector<AnimalInfo> Zoo::animalOptions = {
    {"���", "���", 150, AnimalType::CARNIVORE, "�������"},
    {"����", "����", 180, AnimalType::CARNIVORE, "�������"},
    {"�������", "�������", 200, AnimalType::CARNIVORE, "���"},
    {"����", "����", 200, AnimalType::HERBIVORE, "�������"},
    {"�����", "�����", 170, AnimalType::HERBIVORE, "�������"},
    {"�����", "�����", 160, AnimalType::HERBIVORE, "�������"},
    {"�������", "�������", 300, AnimalType::AQUATIC, "�����"},
    {"��������", "��������", 250, AnimalType::AQUATIC, "������� ����"},
    {"���", "���", 400, AnimalType::AQUATIC, "�����"}
};

// ���������� �������
void Zoo::manageProcurements() {
    std::cout << "\n���������� �������:\n";
    std::cout << "1. ������ ���\n";
    std::cout << "2. ������� (���������� ������������)\n";
    std::cout << "��� �����: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1)
        buyFood();
    else if (choice == 2)
        advertise();
    else
        std::cout << "�������� �����.\n";
}

// ���������� ��������
void Zoo::manageBuildings() {
    std::cout << "\n���������� ��������:\n";
    std::cout << "1. ������ ������\n";
    std::cout << "2. ����������� ���������� � ��������\n";
    std::cout << "��� �����: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1) {
        buyEnclosure();
    }
    else if (choice == 2) {
        displayEnclosureInfo();
    }
    else {
        std::cout << "�������� �����. ���������� ��� ���.\n";
    }
}

void Zoo::listAnimals() const {
    if (animals.empty()) {
        std::cout << "� �������� ��� ��������.\n";
        return;
    }

    std::cout << "\n--- ������ �������� ---\n";
    for (size_t i = 0; i < animals.size(); ++i) {
        const Animal* animal = animals[i];

        // ���������, ������� �� ��������
        bool isSick = false;
        int daysSick = 0;
        for (const auto& sickAnimal : sickAnimals) {
            if (sickAnimal.animal == animal) {
                isSick = true;
                daysSick = sickAnimal.daysSick;
                break;
            }
        }

        std::cout << i + 1 << ". ���: " << animal->getName()
            << " (���: " << animal->getSpecies()
            << ", ���: " << (animal->getGender() == Gender::MALE ? "�������" : "�������")
            << ", �������: " << animal->getAgeInDays() << " ����)\n"
            << "   ���: " << (animal->getType() == AnimalType::CARNIVORE ? "������" :
                animal->getType() == AnimalType::HERBIVORE ? "����������" : "�������������") << "\n"
            << "   ���: " << animal->getWeight() << " ��\n"
            << "   ������: " << animal->getPreferredClimate() << "\n";

        // ����������� ��������� ������ ���� �������� �������� � ��������
        if (animal->wasBornInZoo()) {
            const auto& parents = animal->getParents();
            std::cout << "   ��������: "
                << parents.first.name << " (" << parents.first.species << ", ���: " << (parents.first.gender == Gender::MALE ? "�������" : "�������") << ") � "
                << parents.second.name << " (" << parents.second.species << ", ���: " << (parents.second.gender == Gender::MALE ? "�������" : "�������") << ")\n";
        }

        // ����� �������, ���� �������� �������
        if (isSick) {
            std::cout << "������!(������ ��� " << daysSick << " ����) ������ ��������� �������!\n";
        }
    }
}


void Zoo::buyAnimal() {
    while (true) { // ����, ����� ����� ���������� ����� ���������� ���
        if (currentDay > 10 && dailyAnimalPurchases >= 1) {
            std::cout << "����� 10-�� ��� ����� �������� ������ ���� �������� � ����.\n";
            return;
        }

        if (purchasePool.empty()) {
            std::cout << "��� ��������� �������� ��� �������. �������� ���.\n";
            return;
        }

        std::cout << "\n��������� �������� ��� �������:\n";
        for (size_t i = 0; i < purchasePool.size(); ++i) {
            Animal* animal = purchasePool[i];
            std::cout << i + 1 << ". " << animal->getName()
                << " (���: " << (animal->getGender() == Gender::MALE ? "�������" : "�������")
                << ", ����: " << animal->getPrice()
                << ", ���: " << (animal->getType() == AnimalType::CARNIVORE ? "������" :
                    animal->getType() == AnimalType::HERBIVORE ? "����������" : "�������������")
                << ", ������: " << animal->getPreferredClimate() << ")\n";
        }

        std::cout << "0. �������� ��� �������� (���������: 100 �����)\n";

        int choice;
        std::cin >> choice;

        if (choice == 0) { // ���������� ����
            if (money < 100) {
                std::cout << "������������ ����� ��� ���������� ���� ��������.\n";
                return;
            }
            money -= 100;
            refreshPurchasePool();
            continue;
        }

        if (choice < 1 || choice > purchasePool.size()) {
            std::cout << "�������� �����. ���������� �����.\n";
            continue;
        }

        Animal* selectedAnimal = purchasePool[choice - 1];
        if (money < selectedAnimal->getPrice()) {
            std::cout << "������������ �����.\n";
            return;
        }

        bool enclosureAvailable = false;
        for (auto& enc : enclosures) {
            if (enc.getAllowedType() == selectedAnimal->getType() &&
                enc.hasFreeSlot() &&
                enc.getClimate() == selectedAnimal->getPreferredClimate()) {
                enclosureAvailable = true;
                enc.addAnimal();
                break;
            }
        }

        if (!enclosureAvailable) {
            std::cout << "��� ����������� ������� ��� ����� ���������.\n";
            return;
        }

        money -= selectedAnimal->getPrice();
        animals.push_back(selectedAnimal);
        purchasePool.erase(purchasePool.begin() + choice - 1); // ������� �� ����
        dailyAnimalPurchases++;
        std::cout << "�� ������ " << selectedAnimal->getName() << " (" << (selectedAnimal->getGender() == Gender::MALE ? "�������" : "�������") << ").\n";
        return;
    }
}

// ������� ���������
void Zoo::sellAnimal() {
    if (animals.empty()) {
        std::cout << "\n� �������� ��� �������� ��� �������.\n";
        return;
    }

    std::cout << "\n--- ������� ��������� ---\n";
    for (size_t i = 0; i < animals.size(); ++i) {
        std::cout << i + 1 << ". " << animals[i]->getName()
            << " (����: " << animals[i]->getPrice() << ")\n";
    }

    int index;
    std::cin >> index;
    std::cin.ignore();

    if (index < 1 || index > animals.size()) {
        std::cout << "�������� �����.\n";
        return;
    }

    money += animals[index - 1]->getPrice();
    AnimalType type = animals[index - 1]->getType();
    for (auto& enc : enclosures) {
        if (enc.getAllowedType() == type && enc.getCurrentCount() > 0) {
            enc.removeAnimal();
            break;
        }
    }
    delete animals[index - 1];
    animals.erase(animals.begin() + index - 1);
    std::cout << "�������� �������.\n";
}

void Zoo::buyFood() {
    std::cout << "\n--- ������� ��� ---\n";
    std::cout << "������� ���������� ������ ��� (1 ��. = 1 �������� �������): ";
    int amount;
    std::cin >> amount;
    std::cin.ignore();

    if (money < amount) {
        std::cout << "������������ ����� ��� ������� ���.\n";
        return;
    }

    money -= amount;
    food += amount;
    std::cout << "������� " << amount << " ������ ���.\n";
}

void Zoo::advertise() {
    std::cout << "\n--- ������� ---\n";
    std::cout << "������� �����, ������� ������ ��������� �� �������: ";
    double cost;
    std::cin >> cost;
    std::cin.ignore();

    if (money < cost) {
        std::cout << "������������ ����� ��� �������.\n";
        return;
    }

    money -= cost;
    int increase = static_cast<int>(cost / 10); // ������ 10 ����� ����������� ������������
    popularity += increase;

    std::cout << "������������ ����� ��������� �� " << increase << " ������� �� ��������� ����.\n";
}

void Zoo::buyEnclosure() {
    struct EnclosureInfo {
        int capacity;
        double price;
    };

    std::vector<EnclosureInfo> options = {
        {2, 25}, {4, 50}, {6, 75}, {8, 100}
    };

    std::cout << "\n�������� ��� �������:\n";
    std::cout << "1. ��� ��������\n";
    std::cout << "2. ��� ����������\n";
    std::cout << "3. ��� �������������\n";
    int typeChoice;
    std::cin >> typeChoice;
    std::cin.ignore();

    if (typeChoice < 1 || typeChoice > 3) {
        std::cout << "�������� �����.\n";
        return;
    }

    AnimalType type = (typeChoice == 1 ? AnimalType::CARNIVORE :
        (typeChoice == 2 ? AnimalType::HERBIVORE : AnimalType::AQUATIC));

    // ������ ��������� ������� �� ������ ���� �������
    std::vector<std::string> climates;
    if (type == AnimalType::CARNIVORE || type == AnimalType::HERBIVORE) {
        climates = { "�������", "�������", "���" }; // ������ ��� �������� ��������
    }
    else if (type == AnimalType::AQUATIC) {
        climates = { "�����", "������� ����" }; // ������ ��� �������������
    }

    std::cout << "\n�������� ������ ��� �������:\n";
    for (size_t i = 0; i < climates.size(); ++i) {
        std::cout << i + 1 << ". " << climates[i] << "\n";
    }

    int climateChoice;
    std::cin >> climateChoice;
    std::cin.ignore();

    if (climateChoice < 1 || climateChoice > climates.size()) {
        std::cout << "�������� ����� �������.\n";
        return;
    }

    std::string climate = climates[climateChoice - 1];

    std::cout << "\n�������� ����������� �������:\n";
    for (size_t i = 0; i < options.size(); ++i) {
        double adjustedPrice = options[i].price;
        if (type == AnimalType::AQUATIC) {
            adjustedPrice *= 2.0; // ���������� ��������� ��� �������������
        }

        std::cout << i + 1 << ". " << options[i].capacity
            << " �������� �� " << adjustedPrice << " �����.\n";
    }

    int optionChoice;
    std::cin >> optionChoice;
    std::cin.ignore();

    if (optionChoice < 1 || optionChoice > options.size()) {
        std::cout << "�������� �����.\n";
        return;
    }

    const EnclosureInfo& selectedEnclosure = options[optionChoice - 1];
    double finalPrice = selectedEnclosure.price;

    if (type == AnimalType::AQUATIC) {
        finalPrice *= 2.0;
    }

    if (money < finalPrice) {
        std::cout << "������������ ����� ��� ������� �������.\n";
        return;
    }

    money -= finalPrice;
    enclosures.push_back(Enclosure(selectedEnclosure.capacity, type, finalPrice, climate));
    std::cout << "������ ������.\n";
}


void Zoo::nextDay() {
    int totalPopularityChange = 0;
    std::cout << "\n--- ������� � ���������� ��� ---\n";

    // ������ ����: ���������� �������
    if (currentDay == 1) {
        std::cout << "������ ����: ������� �� ������������.\n";
        currentDay++;
        return;
    }

    // 1. ����������� ���: ������� ��������� ����� 1 ������� ���
    int animalCount = totalAnimalCount();
    if (food >= animalCount) {
        food -= animalCount;
        std::cout << "��� �������� ����������.\n";
    }
    else {
        int unfed = animalCount - food;
        food = 0;
        std::cout << unfed << " �������� �� �������� ���.\n";

        // �������� ������� �������� �� ������
        int deaths = 0;
        for (auto it = animals.begin(); it != animals.end();) {
            if (std::rand() % 100 < 50) { // 50% ���� ������ �� ������
                AnimalType type = (*it)->getType();
                // �������������� �������� � ��������
                for (auto& enc : enclosures) {
                    if (enc.getAllowedType() == type && enc.getCurrentCount() > 0) {
                        enc.removeAnimal(); // ��������� ��������� �������
                        break;
                    }
                }
                delete* it; // ������� ������ ��������� �� ������
                it = animals.erase(it); // ������� �� ������
                deaths++;
            }
            else {
                ++it; // ��������� � ���������� ���������
            }
        }
        std::cout << deaths << " �������� ������ �� ������.\n";
    }

    // 2. ������� ������� �����������
    double totalSalaries = 0.0;
    for (const auto& emp : employees) {
        totalSalaries += emp.getSalary();
    }

    if (money >= totalSalaries) {
        money -= totalSalaries;
        std::cout << "��������� �������: " << totalSalaries << "\n";
    }
    else {
        std::cout << "������������ ����� ��� ������ �������! ������ ������.\n";
        money = 0;
    }

    // 3. ���������� ������� �� �������
    double totalMaintenance = 0.0;
    for (const auto& enc : enclosures) {
        totalMaintenance += enc.getDailyExpense();
    }

    if (money >= totalMaintenance) {
        money -= totalMaintenance;
        std::cout << "�������� ������� �� �������: " << totalMaintenance << "\n";
    }
    else {
        std::cout << "������������ ����� ��� ������ �������� �� �������! ������ ������.\n";
        money = 0;
    }

    // 4. �������� �� ������� ����������
    int availableVeterinarians = 0;
    int availableCleaners = 0;
    int availableFeeders = 0;

    for (const auto& emp : employees) {
        switch (emp.getRole()) {
        case EmployeeRole::VETERINARIAN:
            availableVeterinarians += 10; // ������ ��������� ����������� �� 10 ��������
            break;
        case EmployeeRole::CLEANER:
            availableCleaners += 1; // ������ ������� ����������� 1 ������
            break;
        case EmployeeRole::FEEDER:
            availableFeeders += 2; // ������ ���������� ����������� 2 �������
            break;
        }
    }

    // 5. ������ �� �������� ����������
    // ��������� �������� ���������
    int uncleanedEnclosures = enclosures.size() - availableCleaners;
    if (uncleanedEnclosures > 0) {
        std::cout << uncleanedEnclosures << "�������� �������� ��������!\n";
        std::cout <<"�������� ������������ ��:\n" << uncleanedEnclosures;
        totalPopularityChange -= uncleanedEnclosures; // �������� ������������
    }

    // ��������� �������� ������������
    int animalsWithoutFoodCare = animalCount - (availableFeeders * 2);
    if (animalsWithoutFoodCare > 0) {
        std::cout << animalsWithoutFoodCare << " �������� �������� ���������!\n";
        std::cout << " �������� ������������ ��:\n" << animalsWithoutFoodCare;
        totalPopularityChange -= animalsWithoutFoodCare; // �������� ������������

        int deaths = 0;
        for (int i = 0; i < animalsWithoutFoodCare; ++i) {
            if (std::rand() % 100 < 15) { // 15% ���� ������
                for (auto it = animals.begin(); it != animals.end();) {
                    AnimalType type = (*it)->getType();

                    // ������� �������� �� ���������������� �������
                    for (auto& enc : enclosures) {
                        if (enc.getAllowedType() == type && enc.getCurrentCount() > 0) {
                            enc.removeAnimal(); // ��������� ���������� �������� � �������
                            break;
                        }
                    }

                    delete* it; // ������������ ������ ���������
                    it = animals.erase(it); // �������� �� ������
                    deaths++;
                    break;
                }
            }
        }
        std::cout << deaths << " �������� ������.\n";
    }

    // 6. ����� �� �����������
    int finalVisitors = 0; // ���� �������� ���, ����������� ���� �� �����
    double income = 0;     // ���� ��� �����������, ����� ����� 0

    if (animalCount > 0) {
        int baseVisitors = 2 * popularity;
        int aquaticCount = 0;

        for (const auto& animal : animals) {
            if (animal->getType() == AnimalType::AQUATIC) {
                aquaticCount++;
            }
        }

        // �������� ��������� �� ������� �������
        finalVisitors = baseVisitors * (1 << aquaticCount);
        finalVisitors = std::max(finalVisitors, 1); // ������� 1 ���������� ��� ������� ��������
        income = finalVisitors * std::max(animalCount, 1); // ����� ������� �� ����������� � ��������
    }
    else {
        std::cout << "� ����� �������� ��� ��������! ���������� �� ��������.\n";
        finalVisitors = 0; // ���������� �����������
        income = 0;        // ����� �����������
    }

    money += income;
    std::cout << "���������� �����������: " << finalVisitors << "\n";
    std::cout << "����� �� �����������: " << income << " �����\n";

    // 7. ��������� ���������� ������ ������������ �� �����������
    int popularityBonus = 0;
    int photographers = 0, celebrities = 0, animalFans = 0;
    int maxBonusEvents = 4; // ����������� �� ���������� ������� �� ����

    // ���������, ����� �� ������ �������� ������� � ���� ���� (50% ����)
    if (std::rand() % 100 < 50) {
        for (int i = 0; i < finalVisitors && (photographers + celebrities + animalFans) < maxBonusEvents; ++i) {
            int visitorType = std::rand() % 100;
            if (visitorType < 0.5) {
                popularityBonus += 5; // ������������
                celebrities++;
            }
            else if (visitorType < 2) {
                popularityBonus += 3;  // ��������
                photographers++;
            }
            else if (visitorType < 5) {
                popularityBonus += 1;  // ������� ���������� (������ �����)
                animalFans++;
            }
        }
    }

    // ����� ������� ������ (������ ���� ���� �������)
    if (photographers > 0) std::cout << "������� ��� ������� �������� " << photographers << " ���������(��), �������� ������������ �� +" << photographers * 3 << "!\n";
    if (celebrities > 0) std::cout << "������� ��� ������� ������� " << celebrities << " ������������(��)! +5 � ������������ �� �������!\n";
    if (animalFans > 0) std::cout << animalFans << " ���������� ��������� �������� ��������, ������� +" << animalFans << " � ������������!\n";

    std::cout << "����� ����� ������������ �� ������ ����������� �� ����: " << popularityBonus << "\n";





    // 8. ���������� ���� �������� ��� �������
    if (currentDay % 1 == 0) { // ��������� ��� ���������
        refreshPurchasePool();
    }

    // 9. ���������� �������� ���� ��������
    int deathsByAge = 0;
    for (auto it = animals.begin(); it != animals.end();) {
        (*it)->increaseAgeInDays(); // ����������� ������� ��������� � ����

        // ��������� ������ ��������� ����� 10 ����
        if ((*it)->checkDeathAfterTenDays()) {
            std::cout << (*it)->getName() << " ���� �� ��������.\n";

            // ������� �������� �� ���������������� �������
            AnimalType type = (*it)->getType();
            for (auto& enc : enclosures) {
                if (enc.getAllowedType() == type && enc.getCurrentCount() > 0) {
                    enc.removeAnimal();
                    break;
                }
            }

            delete* it; // ����������� ������
            it = animals.erase(it); // ������� �� ������
            deathsByAge++;
        }
        else {
            ++it; // ��������� � ���������� ���������
        }
    }
    std::cout << deathsByAge << " �������� ������ �� ��������.\n";

    dailyAnimalPurchases = 0;
    currentDay++;

    // 10. ��������� ��������� (10% ���� ��������� ���������� ���������)
    if (std::rand() % 100 < 10) {
        std::vector<Animal*> healthyAnimals;

        for (auto& animal : animals) {
            bool alreadySick = std::any_of(sickAnimals.begin(), sickAnimals.end(),
                [&](const SickAnimal& sick) { return sick.animal == animal; });

            if (!alreadySick) {
                healthyAnimals.push_back(animal);
            }
        }

        if (!healthyAnimals.empty()) {
            Animal* randomAnimal = healthyAnimals[std::rand() % healthyAnimals.size()];
            auto exists = std::find_if(sickAnimals.begin(), sickAnimals.end(),
                [&](const SickAnimal& sick) { return sick.animal == randomAnimal; });

            if (exists == sickAnimals.end()) {
                sickAnimals.push_back({ randomAnimal, 0 });
                std::cout << randomAnimal->getName() << " ��������� ������������!\n";
            }
        }
    }



    // ��������� ������� �����������
    bool hasVeterinarian = false;
    for (const auto& employee : employees) {
        if (employee.getRole() == EmployeeRole::VETERINARIAN) {
            hasVeterinarian = true;
            break;
        }
    }

    // 11. ��������������� ����������� (������ ���� �������� ������ ����� 1 ���)
    int newInfections = 0;
    std::vector<Animal*> newlyInfected;
    std::vector<Enclosure*> infectedEnclosures;

    for (auto& sickAnimal : sickAnimals) {
        sickAnimal.daysSick++; // ����������� ���������� ���� �������

        if (sickAnimal.daysSick >= 1) { //���������� �������� �������� �������� ������ ����� 1 ��� �������
            for (auto& enclosure : enclosures) {
                if (enclosure.getAllowedType() != sickAnimal.animal->getType()) continue;

                std::vector<Animal*> healthyAnimals;

                // �������� �������� �������� � ��� �� �������
                for (auto& animal : animals) {
                    bool alreadySick = std::any_of(sickAnimals.begin(), sickAnimals.end(),
                        [&](const SickAnimal& sick) { return sick.animal == animal; });

                    if (!alreadySick && animal->getType() == sickAnimal.animal->getType()) {
                        healthyAnimals.push_back(animal);
                    }
                }

                // ���������� ������� ����� �������� ���������
                if (!healthyAnimals.empty()) {
                    int infectionRate = hasVeterinarian ? 2 : 3; // ��� ���������� ���������� 3
                    int toInfect = std::min(infectionRate, (int)healthyAnimals.size());

                    for (int i = 0; i < toInfect; ++i) {
                        newlyInfected.push_back(healthyAnimals[i]);
                    }
                }
            }
        }
    }

    // ��������� ����� ��������� � ������ (�� ��������� ����)
    for (auto& animal : newlyInfected) {
        auto exists = std::find_if(sickAnimals.begin(), sickAnimals.end(),
            [&](const SickAnimal& sick) { return sick.animal == animal; });

        if (exists == sickAnimals.end()) {
            sickAnimals.push_back({ animal, 0 });
            std::cout << animal->getName() << " ��������� ������������!\n";
        }
    }

    // ��������� ����������� ������� ��������� � ��������
    for (auto& enclosure : infectedEnclosures) {
        std::vector<Animal*> infectedAnimals;
        for (auto& animal : animals) {
            bool isSick = std::any_of(sickAnimals.begin(), sickAnimals.end(),
                [&](const SickAnimal& sick) { return sick.animal == animal; });

            if (isSick && animal->getType() == enclosure->getAllowedType()) {
                infectedAnimals.push_back(animal);
            }
        }

        if (infectedAnimals.size() > enclosure->getCurrentCount() / 2) {
            std::cout << "��������! � ������� " << enclosure->getClimate() << " ������� �������� �� �����������!\n";

            for (int i = 0; i < std::min((int)infectedAnimals.size(), 2); ++i) {
                Animal* dyingAnimal = infectedAnimals.back();
                infectedAnimals.pop_back(); // ������� �� ������ ��������� ����� ��������� �������

                sickAnimals.erase(std::remove_if(sickAnimals.begin(), sickAnimals.end(),
                    [&](const SickAnimal& s) { return s.animal == dyingAnimal; }),
                    sickAnimals.end());

                delete dyingAnimal;
                animals.erase(std::remove(animals.begin(), animals.end(), dyingAnimal), animals.end());
            }
        }
    }

    // ������������ ��������� �� ������ ������� ��������
    totalPopularityChange -= sickAnimals.size();

    // 12. ��������� ������������ (���� �������, �������� � ��������� ���������)

    // ���������� ������������ �� ������� ��������
    int illnessPenalty = sickAnimals.size();
    totalPopularityChange -= illnessPenalty;

    // ���������� ������ �� �����������
    totalPopularityChange += popularityBonus;

    popularity += totalPopularityChange;
    if (popularity < 0) {
        popularity = std::max(1, popularity + totalPopularityChange);
    }

    if (animalCount <= 0) {
        popularity = 1;
        std::cout << "������������ ������� ����������� ��-�� ��������� ��������\n";
        totalPopularityChange = 0;
    }

    std::cout << "�������� ��������� ������������ �� ����: " << totalPopularityChange
        << ", ������ ��� ���������� " << popularity << ".\n";
}

void Zoo::manageEmployees() {
    std::cout << "\n���������� ����������:\n";
    std::cout << "1. ������ ���������\n";
    std::cout << "2. ������� ���������\n";
    std::cout << "3. ����������� ������ ����������\n";
    std::cout << "��� �����: ";
    int choice;
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "������ �����. ���������� �����.\n";
        return;
    }

    switch (choice) {
        case 1:
            hireEmployee();
            break;
        case 2:
            fireEmployee();
            break;
        case 3:
            listEmployees();
            return;
        default:
            std::cout << "�������� �����.\n";
            break;
    }
}

void Zoo::hireEmployee() {
    std::string name;
    int typeChoice;

    std::cout << "������� ��� ������ ���������: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "�������� ��� ���������:\n"
        << "1. ��������� (����������� �� 20 ��������, �������� 20)\n"
        << "2. ������� (����������� 1 ������, �������� 12)\n"
        << "3. ���������� (����������� 2 �������, �������� 15)\n";
    std::cin >> typeChoice;

    if (std::cin.fail() || typeChoice < 1 || typeChoice > 3) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "������ �����. �������� �� �������.\n";
        return;
    }

    EmployeeRole role;
    double salary;
    switch (typeChoice) {
    case 1:
        role = EmployeeRole::VETERINARIAN;
        salary = 20.0;
        break;
    case 2:
        role = EmployeeRole::CLEANER;
        salary = 12.0;
        break;
    case 3:
        role = EmployeeRole::FEEDER;
        salary = 15.0;
        break;
    }

    employees.emplace_back(name, role, salary);
    std::cout << "�������� " << name << " ����� ��� " << employees.back().getRoleString() << ".\n";
}

void Zoo::fireEmployee() {
    if (employees.empty()) {
        std::cout << "\n� �������� ��� ���������� ��� ����������.\n";
        return;
    }

    std::cout << "\n--- ���������� ��������� ---\n";
    std::cout << "������ ����������:\n";
    for (size_t i = 0; i < employees.size(); ++i) {
        std::cout << i + 1 << ". " << employees[i].getName()
            << " (���������: " << (employees[i].getRole() == EmployeeRole::CLEANER ? "�������" :
                employees[i].getRole() == EmployeeRole::FEEDER ? "����������" : "�����������")
            << ")\n";
    }

    std::cout << "������� ����� ��������� ��� ����������: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice < 1 || choice > employees.size()) {
        std::cout << "�������� �����.\n";
        return;
    }

    std::cout << "�������� " << employees[choice - 1].getName() << " ������.\n";
    employees.erase(employees.begin() + choice - 1);
}

void Zoo::listEmployees() const {
    if (employees.empty()) {
        std::cout << "� �������� ���� ��� ����������.\n";
        return;
    }

    std::cout << "\n--- ������ ���������� ---\n";
    for (const auto& employee : employees) {
        std::cout << "���: " << employee.getName()
            << ", ���: ";
        switch (employee.getRole()) {
        case EmployeeRole::VETERINARIAN:
            std::cout << "���������";
            break;
        case EmployeeRole::CLEANER:
            std::cout << "�������";
            break;
        case EmployeeRole::FEEDER:
            std::cout << "����������";
            break;
        }
        std::cout << ", ��������: " << employee.getSalary() << "\n";
    }
}

void Zoo::displayEnclosureInfo() const {
    if (enclosures.empty()) {
        std::cout << "\n� �������� ��� ��������.\n";
        return;
    }

    std::cout << "\n--- ���������� � �������� ---\n";
    for (size_t i = 0; i < enclosures.size(); ++i) {
        const Enclosure& enc = enclosures[i];
        std::string typeName;
        if (enc.getAllowedType() == AnimalType::CARNIVORE) {
            typeName = "�������";
        }
        else if (enc.getAllowedType() == AnimalType::HERBIVORE) {
            typeName = "����������";
        }
        else if (enc.getAllowedType() == AnimalType::AQUATIC) {
            typeName = "�������������";
        }
        if (enc.getCurrentCount() == 0) {
            std::cout << "  ���� ������ ����.\n";
        }

        std::cout << "������ " << i + 1 << ":\n";
        std::cout << "  ��� ��������: " << typeName << "\n";
        std::cout << "  ������: " << enc.getClimate() << "\n";
        std::cout << "  �����������: " << enc.getCapacity() << "\n";
        std::cout << "  ������� ���������� ��������: " << enc.getCurrentCount() << "\n";
        std::cout << "  ���������� �������: " << enc.getDailyExpense() << " �����\n";
    }
}

int Zoo::totalAnimalCount() const {
    return animals.size(); // ���������� ����� ���������� �������� � ��������
}

bool Zoo::isGameOver() const {
    return money < 0; // ���� �������������, ���� ��� �����
}

void Zoo::refreshPurchasePool() {
    purchasePool.clear();
    for (int i = 0; i < 10; ++i) {
        const AnimalInfo& info = animalOptions[std::rand() % animalOptions.size()];
        Gender randomGender = (std::rand() % 2 == 0) ? Gender::MALE : Gender::FEMALE;
        purchasePool.push_back(new Animal(info.name, info.species, randomGender, 0, -1, info.climate, info.price, info.type));
    }
    std::cout << "��� �������� �������.\n";
}

void Zoo::updatePurchasePool() {
    const int updateCost = 100; // ��������� ����������

    if (money < updateCost) {
        std::cout << "������������ ����� ��� ���������� ���� ��������! ����� " << updateCost << " �����.\n";
        return;
    }

    money -= updateCost; // ��������� ������
    refreshPurchasePool(); // ��������� ��� ��������
    std::cout << "��� �������� ������� �� " << updateCost << " �����.\n";
}

void Zoo::renameAnimal() {
    if (animals.empty()) {
        std::cout << "� �������� ��� �������� ��� ��������������.\n";
        return;
    }

    // ����� ������ ��������
    std::cout << "\n--- ������ �������� ---\n";
    for (size_t i = 0; i < animals.size(); ++i) {
        std::cout << i + 1 << ". ���: " << animals[i]->getName() << " (���: " << animals[i]->getSpecies() << ")\n";
    }

    // ����� ��������� ��� ��������������
    std::cout << "������� ����� ���������, ������� ������ �������������: ";
    size_t choice;
    std::cin >> choice;

    if (choice < 1 || choice > animals.size()) {
        std::cout << "�������� �����. �������������� ��������.\n";
        return;
    }

    // ���� ������ �����
    std::cout << "������� ����� ��� ��� ���������: ";
    std::string newName;
    std::cin.ignore();
    std::getline(std::cin, newName);

    // ��������� �����
    animals[choice - 1]->setName(newName);
}

void Zoo::breedAnimals() {
    if (animals.size() < 2) {
        std::cout << "� �������� ������������ �������� ��� �����������.\n";
        return;
    }

    std::cout << "\n--- ������ �������� ---\n";
    for (size_t i = 0; i < animals.size(); ++i) {
        const Animal* animal = animals[i];
        std::cout << i + 1 << ". ���: " << animal->getName()
            << " (���: " << animal->getSpecies()
            << ", ���: " << (animal->getGender() == Gender::MALE ? "�������" : "�������")
            << ", �������: " << animal->getAgeInDays() << " ����)\n";
    }

    std::cout << "������� ����� ������� ���������: ";
    size_t parent1Index, parent2Index;
    std::cin >> parent1Index;

    std::cout << "������� ����� ������� ���������: ";
    std::cin >> parent2Index;

    if (parent1Index < 1 || parent1Index > animals.size() ||
        parent2Index < 1 || parent2Index > animals.size()) {
        std::cout << "�������� �����. ����������� ��������.\n";
        return;
    }

    Animal* parent1 = animals[parent1Index - 1];
    Animal* parent2 = animals[parent2Index - 1];

    if (parent1->getGender() == parent2->getGender()) {
        std::cout << "������: ��� ��������� ������ ����. ����������� ����������.\n";
        return;
    }

    if (parent1->getSpecies() == parent2->getSpecies()) {
        if (parent1->getAgeInDays() < 5 && parent2->getAgeInDays() < 5) {
            std::cout << "������: ���� �� ���� �������� ������ ���� ������ 5 ����!\n";
            return;
        }

        Animal* child = *parent1 + *parent2;
        if (child) {
            addAnimalToEnclosure(child, parent1->getType());
            std::cout << "�����������! � " << parent1->getSpecies() << " ������� �����: " << child->getName() << "!\n";
        }
        else {
            std::cout << "����������� �� �������.\n";
        }
    }
    else {
        if (parent1->getAgeInDays() < 5 || parent2->getAgeInDays() < 5) {
            std::cout << "������: ��� �������� ������ ���� ������ 5 ����!\n";
            return;
        }

        std::string hybridSpecies = parent1->getSpecies().substr(0, parent1->getSpecies().size() / 2) +
            parent2->getSpecies().substr(parent2->getSpecies().size() / 2);

        std::string hybridName = parent1->getName().substr(0, parent1->getName().size() / 2) +
            parent2->getName().substr(parent2->getName().size() / 2);

        Gender hybridGender = (std::rand() % 2 == 0) ? Gender::MALE : Gender::FEMALE;
        double hybridWeight = (parent1->getWeight() + parent2->getWeight()) / 2;
        double hybridPrice = (parent1->getPrice() + parent2->getPrice()) / 2;
        AnimalType hybridType = parent1->getType();
        std::string hybridClimate = parent1->getPreferredClimate();

        Animal* hybrid = new Animal(hybridName, hybridSpecies, hybridGender, 0, hybridWeight,
            hybridClimate, hybridPrice, hybridType, true,
            parent1->getSpecies(), parent2->getSpecies());

        addAnimalToEnclosure(hybrid, hybridType);
        std::cout << "�����������! ������� ����� ������: " << hybridName << " (���: " << hybridSpecies << ")\n";
    }
}


void Zoo::addAnimalToEnclosure(Animal* child, AnimalType type) {
    for (auto& enclosure : enclosures) {
        if (enclosure.getAllowedType() == type && enclosure.hasFreeSlot()) {
            enclosure.addAnimal(); // ��������� � ������
            animals.push_back(child); // ��������� ������� � ������ ��������
            std::cout << "����� �������� ��������� � ������!\n";
            return;
        }
    }

    std::cerr << "������: ��� ���������� ����� � �������� ��� �������!\n";
    delete child; // ������� �������, ���� �������� �� �������
}

void Zoo::healAnimal() {
    // ��������� ������� ����������
    bool hasVeterinarian = std::any_of(employees.begin(), employees.end(),
        [](const Employee& emp) { return emp.getRole() == EmployeeRole::VETERINARIAN; });

    if (!hasVeterinarian) {
        std::cout << "� �������� ��� ����������! ������� ����������.\n";
        return;
    }

    if (sickAnimals.empty()) {
        std::cout << "��� ������� �������� ��� �������.\n";
        return;
    }

    sickAnimals.erase(std::remove_if(sickAnimals.begin(), sickAnimals.end(),
        [&](const SickAnimal& sick) { return std::find(animals.begin(), animals.end(), sick.animal) == animals.end(); }),
        sickAnimals.end());

    std::cout << "�������� �������� ��� �������:\n";
    for (size_t i = 0; i < sickAnimals.size(); ++i) {
        std::cout << i + 1 << ". " << sickAnimals[i].animal->getName()
            << " (������ " << sickAnimals[i].daysSick << " ����)\n";
    }

    int choice;
    std::cin >> choice;

    if (std::cin.fail() || choice < 1 || choice > static_cast<int>(sickAnimals.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "������ �����. ����������, ������� ���������� ����� ���������.\n";
        return;
    }

    Animal* healedAnimal = sickAnimals[choice - 1].animal;
    std::cout << "�������� " << healedAnimal->getName() << " ��������� �����������!\n";

    sickAnimals.erase(std::remove_if(sickAnimals.begin(), sickAnimals.end(),
        [&](const SickAnimal& sick) { return sick.animal == healedAnimal; }),
        sickAnimals.end());
}


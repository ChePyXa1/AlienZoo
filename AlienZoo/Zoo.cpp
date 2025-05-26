#include "Zoo.h"
#include "Enclosure.h"
#include "Employee.h"
#include "Animal.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Конструктор зоопарка
Zoo::Zoo(const std::string& zooName)
    : name(zooName), food(100), money(100000), popularity(10), currentDay(1), dailyAnimalPurchases(0) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<Employee> employees;
    refreshPurchasePool();
    std::cout << "Зоопарк \"" << name << "\" открыт!\n";
}

// Деструктор зоопарка
Zoo::~Zoo() {
    // Удаляем динамически созданных животных
    for (auto animal : animals) {
        delete animal;
    }
}

// Отображение состояния зоопарка
void Zoo::displayStatus() const {
    std::cout << "\n=== День " << currentDay << " ===\n";
    std::cout << "Зоопарк: " << name << "\n";
    std::cout << "Еда: " << food << "\n";
    std::cout << "Деньги: " << money << "\n";

    if (currentDay == 1) {
        // Популярность и посетители равны нулю на первый день
        std::cout << "Популярность: 0\n";
        std::cout << "Посетители: 0\n\n";
        std::cout << "Первый день - это день до открытия зоопарка\nПодготовьтесь к открытию зоопарка:\nКупите животных\nНаймите больше сотрудников\nПриобретите рекламу\n";
    }
    else {
        std::cout << "Популярность: " << popularity << "\n";
        std::cout << "Количество животных: " << totalAnimalCount() << "\n";

        int visitors = 2 * popularity;

        // Учитываем наличие водоплавающих животных (аквоидов)
        int aquaticCount = 0;
        for (auto animal : animals) {
            if (animal->getType() == AnimalType::AQUATIC) {
                aquaticCount++;
            }
        }
        if (aquaticCount > 0) {
            visitors *= (1 << aquaticCount); // Удвоение за каждого аквоида
        }
        if (totalAnimalCount() == 0) {
            visitors = 0;
            std::cout << "Посетители: " << visitors << "\n";
        }
        else {
            std::cout << "Посетители: " << visitors << "\n";
        }
    }
}

// Отображение главного меню
void Zoo::displayMenu() const {
    std::cout << "\nВыберите действие:\n";
    std::cout << "1. Менеджмент животных\n";
    std::cout << "2. Менеджмент закупок (еда, реклама)\n";
    std::cout << "3. Менеджмент построек (вольеры)\n";
    std::cout << "4. Переход к следующему дню\n";
    std::cout << "5. Менеджмент работников\n";
}

// Обработка выбора пользователя
void Zoo::processChoice() {
    int choice;

    while (true) {
        std::cout << "Введите ваш выбор (1–5): ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Пожалуйста, введите целое число от 1 до 5.\n";
            continue;
        }

        if (choice < 1 || choice > 5) {
            std::cout << "Неверный ввод. Введите число от 1 до 5.\n";
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
        std::cout << "Неверный выбор. Введите число от 1 до 5.\n";
        break;
    }
}

void Zoo::manageAnimals() {
    std::cout << "\nМенеджмент животных:\n";
    std::cout << "1. Купить животное\n";
    std::cout << "2. Продать животное\n";
    std::cout << "3. Просмотреть всех животных\n";
    std::cout << "4. Обновить пул животных\n";
    std::cout << "5. Переименовать животное\n";
    std::cout << "6. Размножение животных\n";
    std::cout << "7. Лечение больных животных\n";

    std::cout << "Ваш выбор: ";
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
        std::cout << "Неверный выбор.\n";
        break;
    }
}

const std::vector<AnimalInfo> Zoo::animalOptions = {
    {"Лев", "Лев", 150, AnimalType::CARNIVORE, "Саванна"},
    {"Тигр", "Тигр", 180, AnimalType::CARNIVORE, "Тропики"},
    {"Медведь", "Медведь", 200, AnimalType::CARNIVORE, "Лес"},
    {"Слон", "Слон", 200, AnimalType::HERBIVORE, "Тропики"},
    {"Жираф", "Жираф", 170, AnimalType::HERBIVORE, "Саванна"},
    {"Зебра", "Зебра", 160, AnimalType::HERBIVORE, "Саванна"},
    {"Дельфин", "Дельфин", 300, AnimalType::AQUATIC, "Океан"},
    {"Аквариус", "Аквариус", 250, AnimalType::AQUATIC, "Пресная вода"},
    {"Кит", "Кит", 400, AnimalType::AQUATIC, "Океан"}
};

// Менеджмент закупок
void Zoo::manageProcurements() {
    std::cout << "\nМенеджмент закупок:\n";
    std::cout << "1. Купить еду\n";
    std::cout << "2. Реклама (увеличение популярности)\n";
    std::cout << "Ваш выбор: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1)
        buyFood();
    else if (choice == 2)
        advertise();
    else
        std::cout << "Неверный выбор.\n";
}

// Менеджмент построек
void Zoo::manageBuildings() {
    std::cout << "\nМенеджмент построек:\n";
    std::cout << "1. Купить вольер\n";
    std::cout << "2. Просмотреть информацию о вольерах\n";
    std::cout << "Ваш выбор: ";
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
        std::cout << "Неверный выбор. Попробуйте ещё раз.\n";
    }
}

void Zoo::listAnimals() const {
    if (animals.empty()) {
        std::cout << "В зоопарке нет животных.\n";
        return;
    }

    std::cout << "\n--- Список животных ---\n";
    for (size_t i = 0; i < animals.size(); ++i) {
        const Animal* animal = animals[i];

        // Проверяем, больное ли животное
        bool isSick = false;
        int daysSick = 0;
        for (const auto& sickAnimal : sickAnimals) {
            if (sickAnimal.animal == animal) {
                isSick = true;
                daysSick = sickAnimal.daysSick;
                break;
            }
        }

        std::cout << i + 1 << ". Имя: " << animal->getName()
            << " (Вид: " << animal->getSpecies()
            << ", Пол: " << (animal->getGender() == Gender::MALE ? "Мужской" : "Женский")
            << ", Возраст: " << animal->getAgeInDays() << " дней)\n"
            << "   Тип: " << (animal->getType() == AnimalType::CARNIVORE ? "Хищник" :
                animal->getType() == AnimalType::HERBIVORE ? "Травоядное" : "Водоплавающее") << "\n"
            << "   Вес: " << animal->getWeight() << " кг\n"
            << "   Климат: " << animal->getPreferredClimate() << "\n";

        // Отображение родителей только если животное родилось в зоопарке
        if (animal->wasBornInZoo()) {
            const auto& parents = animal->getParents();
            std::cout << "   Родители: "
                << parents.first.name << " (" << parents.first.species << ", Пол: " << (parents.first.gender == Gender::MALE ? "Мужской" : "Женский") << ") и "
                << parents.second.name << " (" << parents.second.species << ", Пол: " << (parents.second.gender == Gender::MALE ? "Мужской" : "Женский") << ")\n";
        }

        // Вывод отметки, если животное больное
        if (isSick) {
            std::cout << "БОЛЬНО!(Болеет уже " << daysSick << " дней) Срочно требуется лечение!\n";
        }
    }
}


void Zoo::buyAnimal() {
    while (true) { // Цикл, чтобы после обновления снова показывать пул
        if (currentDay > 10 && dailyAnimalPurchases >= 1) {
            std::cout << "После 10-го дня можно покупать только одно животное в день.\n";
            return;
        }

        if (purchasePool.empty()) {
            std::cout << "Нет доступных животных для покупки. Обновите пул.\n";
            return;
        }

        std::cout << "\nДоступные животные для покупки:\n";
        for (size_t i = 0; i < purchasePool.size(); ++i) {
            Animal* animal = purchasePool[i];
            std::cout << i + 1 << ". " << animal->getName()
                << " (Пол: " << (animal->getGender() == Gender::MALE ? "Мужской" : "Женский")
                << ", Цена: " << animal->getPrice()
                << ", Тип: " << (animal->getType() == AnimalType::CARNIVORE ? "Хищник" :
                    animal->getType() == AnimalType::HERBIVORE ? "Травоядное" : "Водоплавающее")
                << ", Климат: " << animal->getPreferredClimate() << ")\n";
        }

        std::cout << "0. Обновить пул животных (стоимость: 100 монет)\n";

        int choice;
        std::cin >> choice;

        if (choice == 0) { // Обновление пула
            if (money < 100) {
                std::cout << "Недостаточно денег для обновления пула животных.\n";
                return;
            }
            money -= 100;
            refreshPurchasePool();
            continue;
        }

        if (choice < 1 || choice > purchasePool.size()) {
            std::cout << "Неверный выбор. Попробуйте снова.\n";
            continue;
        }

        Animal* selectedAnimal = purchasePool[choice - 1];
        if (money < selectedAnimal->getPrice()) {
            std::cout << "Недостаточно денег.\n";
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
            std::cout << "Нет подходящего вольера для этого животного.\n";
            return;
        }

        money -= selectedAnimal->getPrice();
        animals.push_back(selectedAnimal);
        purchasePool.erase(purchasePool.begin() + choice - 1); // Убираем из пула
        dailyAnimalPurchases++;
        std::cout << "Вы купили " << selectedAnimal->getName() << " (" << (selectedAnimal->getGender() == Gender::MALE ? "Мужской" : "Женский") << ").\n";
        return;
    }
}

// Продажа животного
void Zoo::sellAnimal() {
    if (animals.empty()) {
        std::cout << "\nВ зоопарке нет животных для продажи.\n";
        return;
    }

    std::cout << "\n--- Продажа животного ---\n";
    for (size_t i = 0; i < animals.size(); ++i) {
        std::cout << i + 1 << ". " << animals[i]->getName()
            << " (Цена: " << animals[i]->getPrice() << ")\n";
    }

    int index;
    std::cin >> index;
    std::cin.ignore();

    if (index < 1 || index > animals.size()) {
        std::cout << "Неверный выбор.\n";
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
    std::cout << "Животное продано.\n";
}

void Zoo::buyFood() {
    std::cout << "\n--- Покупка еды ---\n";
    std::cout << "Введите количество единиц еды (1 ед. = 1 денежная единица): ";
    int amount;
    std::cin >> amount;
    std::cin.ignore();

    if (money < amount) {
        std::cout << "Недостаточно денег для покупки еды.\n";
        return;
    }

    money -= amount;
    food += amount;
    std::cout << "Куплено " << amount << " единиц еды.\n";
}

void Zoo::advertise() {
    std::cout << "\n--- Реклама ---\n";
    std::cout << "Введите сумму, которую хотите потратить на рекламу: ";
    double cost;
    std::cin >> cost;
    std::cin.ignore();

    if (money < cost) {
        std::cout << "Недостаточно денег для рекламы.\n";
        return;
    }

    money -= cost;
    int increase = static_cast<int>(cost / 10); // Каждые 10 монет увеличивают популярность
    popularity += increase;

    std::cout << "Популярность будет увеличена на " << increase << " пунктов на следующий день.\n";
}

void Zoo::buyEnclosure() {
    struct EnclosureInfo {
        int capacity;
        double price;
    };

    std::vector<EnclosureInfo> options = {
        {2, 25}, {4, 50}, {6, 75}, {8, 100}
    };

    std::cout << "\nВыберите тип вольера:\n";
    std::cout << "1. Для хищников\n";
    std::cout << "2. Для травоядных\n";
    std::cout << "3. Для водоплавающих\n";
    int typeChoice;
    std::cin >> typeChoice;
    std::cin.ignore();

    if (typeChoice < 1 || typeChoice > 3) {
        std::cout << "Неверный выбор.\n";
        return;
    }

    AnimalType type = (typeChoice == 1 ? AnimalType::CARNIVORE :
        (typeChoice == 2 ? AnimalType::HERBIVORE : AnimalType::AQUATIC));

    // Создаём доступные климаты на основе типа вольера
    std::vector<std::string> climates;
    if (type == AnimalType::CARNIVORE || type == AnimalType::HERBIVORE) {
        climates = { "Саванна", "Тропики", "Лес" }; // Климат для наземных животных
    }
    else if (type == AnimalType::AQUATIC) {
        climates = { "Океан", "Пресная вода" }; // Климат для водоплавающих
    }

    std::cout << "\nВыберите климат для вольера:\n";
    for (size_t i = 0; i < climates.size(); ++i) {
        std::cout << i + 1 << ". " << climates[i] << "\n";
    }

    int climateChoice;
    std::cin >> climateChoice;
    std::cin.ignore();

    if (climateChoice < 1 || climateChoice > climates.size()) {
        std::cout << "Неверный выбор климата.\n";
        return;
    }

    std::string climate = climates[climateChoice - 1];

    std::cout << "\nВыберите вместимость вольера:\n";
    for (size_t i = 0; i < options.size(); ++i) {
        double adjustedPrice = options[i].price;
        if (type == AnimalType::AQUATIC) {
            adjustedPrice *= 2.0; // Увеличение стоимости для водоплавающих
        }

        std::cout << i + 1 << ". " << options[i].capacity
            << " животных за " << adjustedPrice << " монет.\n";
    }

    int optionChoice;
    std::cin >> optionChoice;
    std::cin.ignore();

    if (optionChoice < 1 || optionChoice > options.size()) {
        std::cout << "Неверный выбор.\n";
        return;
    }

    const EnclosureInfo& selectedEnclosure = options[optionChoice - 1];
    double finalPrice = selectedEnclosure.price;

    if (type == AnimalType::AQUATIC) {
        finalPrice *= 2.0;
    }

    if (money < finalPrice) {
        std::cout << "Недостаточно денег для покупки вольера.\n";
        return;
    }

    money -= finalPrice;
    enclosures.push_back(Enclosure(selectedEnclosure.capacity, type, finalPrice, climate));
    std::cout << "Вольер куплен.\n";
}


void Zoo::nextDay() {
    int totalPopularityChange = 0;
    std::cout << "\n--- Переход к следующему дню ---\n";

    // Первый день: пропускаем расчёты
    if (currentDay == 1) {
        std::cout << "Первый день: расчёты не производятся.\n";
        currentDay++;
        return;
    }

    // 1. Потребление еды: каждому животному нужна 1 единица еды
    int animalCount = totalAnimalCount();
    if (food >= animalCount) {
        food -= animalCount;
        std::cout << "Все животные накормлены.\n";
    }
    else {
        int unfed = animalCount - food;
        food = 0;
        std::cout << unfed << " животных не получили еду.\n";

        // Удаление умерших животных от голода
        int deaths = 0;
        for (auto it = animals.begin(); it != animals.end();) {
            if (std::rand() % 100 < 50) { // 50% шанс смерти от голода
                AnimalType type = (*it)->getType();
                // Синхронизируем удаление с вольером
                for (auto& enc : enclosures) {
                    if (enc.getAllowedType() == type && enc.getCurrentCount() > 0) {
                        enc.removeAnimal(); // Обновляем состояние вольера
                        break;
                    }
                }
                delete* it; // Удаляем объект животного из памяти
                it = animals.erase(it); // Удаляем из списка
                deaths++;
            }
            else {
                ++it; // Переходим к следующему животному
            }
        }
        std::cout << deaths << " животных умерли от голода.\n";
    }

    // 2. Выплата зарплат сотрудникам
    double totalSalaries = 0.0;
    for (const auto& emp : employees) {
        totalSalaries += emp.getSalary();
    }

    if (money >= totalSalaries) {
        money -= totalSalaries;
        std::cout << "Выплачено зарплат: " << totalSalaries << "\n";
    }
    else {
        std::cout << "Недостаточно денег для оплаты зарплат! Баланс обнулён.\n";
        money = 0;
    }

    // 3. Ежедневные расходы на вольеры
    double totalMaintenance = 0.0;
    for (const auto& enc : enclosures) {
        totalMaintenance += enc.getDailyExpense();
    }

    if (money >= totalMaintenance) {
        money -= totalMaintenance;
        std::cout << "Оплачены расходы за вольеры: " << totalMaintenance << "\n";
    }
    else {
        std::cout << "Недостаточно денег для оплаты расходов за вольеры! Баланс обнулён.\n";
        money = 0;
    }

    // 4. Проверка на наличие работников
    int availableVeterinarians = 0;
    int availableCleaners = 0;
    int availableFeeders = 0;

    for (const auto& emp : employees) {
        switch (emp.getRole()) {
        case EmployeeRole::VETERINARIAN:
            availableVeterinarians += 10; // Каждый ветеринар обслуживает до 10 животных
            break;
        case EmployeeRole::CLEANER:
            availableCleaners += 1; // Каждый уборщик обслуживает 1 вольер
            break;
        case EmployeeRole::FEEDER:
            availableFeeders += 2; // Каждый кормильщик обслуживает 2 вольера
            break;
        }
    }

    // 5. Штрафы за нехватку работников
    // Обработка нехватки уборщиков
    int uncleanedEnclosures = enclosures.size() - availableCleaners;
    if (uncleanedEnclosures > 0) {
        std::cout << uncleanedEnclosures << "Вольеров остались грязными!\n";
        std::cout <<"Снижение популярности на:\n" << uncleanedEnclosures;
        totalPopularityChange -= uncleanedEnclosures; // Снижение популярности
    }

    // Обработка нехватки кормильщиков
    int animalsWithoutFoodCare = animalCount - (availableFeeders * 2);
    if (animalsWithoutFoodCare > 0) {
        std::cout << animalsWithoutFoodCare << " животных остались голодными!\n";
        std::cout << " Снижение популярности на:\n" << animalsWithoutFoodCare;
        totalPopularityChange -= animalsWithoutFoodCare; // Снижение популярности

        int deaths = 0;
        for (int i = 0; i < animalsWithoutFoodCare; ++i) {
            if (std::rand() % 100 < 15) { // 15% шанс смерти
                for (auto it = animals.begin(); it != animals.end();) {
                    AnimalType type = (*it)->getType();

                    // Удаляем животное из соответствующего вольера
                    for (auto& enc : enclosures) {
                        if (enc.getAllowedType() == type && enc.getCurrentCount() > 0) {
                            enc.removeAnimal(); // Уменьшаем количество животных в вольере
                            break;
                        }
                    }

                    delete* it; // Освобождение памяти животного
                    it = animals.erase(it); // Удаление из списка
                    deaths++;
                    break;
                }
            }
        }
        std::cout << deaths << " животных умерло.\n";
    }

    // 6. Доход от посетителей
    int finalVisitors = 0; // Если животных нет, посетителей быть не может
    double income = 0;     // Если нет посетителей, доход равен 0

    if (animalCount > 0) {
        int baseVisitors = 2 * popularity;
        int aquaticCount = 0;

        for (const auto& animal : animals) {
            if (animal->getType() == AnimalType::AQUATIC) {
                aquaticCount++;
            }
        }

        // Удвоение множителя за каждого аквоида
        finalVisitors = baseVisitors * (1 << aquaticCount);
        finalVisitors = std::max(finalVisitors, 1); // Минимум 1 посетитель при наличии животных
        income = finalVisitors * std::max(animalCount, 1); // Доход зависит от посетителей и животных
    }
    else {
        std::cout << "В вашем зоопарке нет животных! Посетители не приходят.\n";
        finalVisitors = 0; // Посетители отсутствуют
        income = 0;        // Доход отсутствует
    }

    money += income;
    std::cout << "Количество посетителей: " << finalVisitors << "\n";
    std::cout << "Доход от посетителей: " << income << " монет\n";

    // 7. Генерация случайного бонуса популярности от посетителей
    int popularityBonus = 0;
    int photographers = 0, celebrities = 0, animalFans = 0;
    int maxBonusEvents = 4; // Ограничение на количество бонусов за день

    // Проверяем, будет ли вообще бонусное событие в этот день (50% шанс)
    if (std::rand() % 100 < 50) {
        for (int i = 0; i < finalVisitors && (photographers + celebrities + animalFans) < maxBonusEvents; ++i) {
            int visitorType = std::rand() % 100;
            if (visitorType < 0.5) {
                popularityBonus += 5; // Знаменитость
                celebrities++;
            }
            else if (visitorType < 2) {
                popularityBonus += 3;  // Фотограф
                photographers++;
            }
            else if (visitorType < 5) {
                popularityBonus += 1;  // Обычный посетитель (редкий бонус)
                animalFans++;
            }
        }
    }

    // Вывод краткой сводки (только если были события)
    if (photographers > 0) std::cout << "Сегодня ваш зоопарк посетили " << photographers << " фотографа(ов), увеличив популярность на +" << photographers * 3 << "!\n";
    if (celebrities > 0) std::cout << "Сегодня ваш зоопарк посетил " << celebrities << " знаменитость(ей)! +5 к популярности за каждого!\n";
    if (animalFans > 0) std::cout << animalFans << " посетителя оказались фанатами животных, добавив +" << animalFans << " к популярности!\n";

    std::cout << "Общий бонус популярности от особых посетителей за день: " << popularityBonus << "\n";





    // 8. Обновление пула животных для покупки
    if (currentDay % 1 == 0) { // Обновляем пул ежедневно
        refreshPurchasePool();
    }

    // 9. Обновление возраста всех животных
    int deathsByAge = 0;
    for (auto it = animals.begin(); it != animals.end();) {
        (*it)->increaseAgeInDays(); // Увеличиваем возраст животного в днях

        // Проверяем смерть животного после 10 дней
        if ((*it)->checkDeathAfterTenDays()) {
            std::cout << (*it)->getName() << " умер от старости.\n";

            // Удаляем животное из соответствующего вольера
            AnimalType type = (*it)->getType();
            for (auto& enc : enclosures) {
                if (enc.getAllowedType() == type && enc.getCurrentCount() > 0) {
                    enc.removeAnimal();
                    break;
                }
            }

            delete* it; // Освобождаем память
            it = animals.erase(it); // Удаляем из списка
            deathsByAge++;
        }
        else {
            ++it; // Переходим к следующему животному
        }
    }
    std::cout << deathsByAge << " животных умерли от старости.\n";

    dailyAnimalPurchases = 0;
    currentDay++;

    // 10. Первичное заражение (10% шанс заражения случайного животного)
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
                std::cout << randomAnimal->getName() << " заразился тиаравирусом!\n";
            }
        }
    }



    // Проверяем наличие ветеринаров
    bool hasVeterinarian = false;
    for (const auto& employee : employees) {
        if (employee.getRole() == EmployeeRole::VETERINARIAN) {
            hasVeterinarian = true;
            break;
        }
    }

    // 11. Распространение тиаравируса (только если животное болеет более 1 дня)
    int newInfections = 0;
    std::vector<Animal*> newlyInfected;
    std::vector<Enclosure*> infectedEnclosures;

    for (auto& sickAnimal : sickAnimals) {
        sickAnimal.daysSick++; // Увеличиваем количество дней болезни

        if (sickAnimal.daysSick >= 1) { //Заболевшее животное начинает заражать только после 1 дня болезни
            for (auto& enclosure : enclosures) {
                if (enclosure.getAllowedType() != sickAnimal.animal->getType()) continue;

                std::vector<Animal*> healthyAnimals;

                // Собираем здоровых животных в том же вольере
                for (auto& animal : animals) {
                    bool alreadySick = std::any_of(sickAnimals.begin(), sickAnimals.end(),
                        [&](const SickAnimal& sick) { return sick.animal == animal; });

                    if (!alreadySick && animal->getType() == sickAnimal.animal->getType()) {
                        healthyAnimals.push_back(animal);
                    }
                }

                // Определяем сколько новых животных заразятся
                if (!healthyAnimals.empty()) {
                    int infectionRate = hasVeterinarian ? 2 : 3; // Без ветеринара заражаются 3
                    int toInfect = std::min(infectionRate, (int)healthyAnimals.size());

                    for (int i = 0; i < toInfect; ++i) {
                        newlyInfected.push_back(healthyAnimals[i]);
                    }
                }
            }
        }
    }

    // Добавляем новых заражённых в список (на следующий день)
    for (auto& animal : newlyInfected) {
        auto exists = std::find_if(sickAnimals.begin(), sickAnimals.end(),
            [&](const SickAnimal& sick) { return sick.animal == animal; });

        if (exists == sickAnimals.end()) {
            sickAnimals.push_back({ animal, 0 });
            std::cout << animal->getName() << " заразился тиаравирусом!\n";
        }
    }

    // Проверяем критический уровень заражения в вольерах
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
            std::cout << "Внимание! В вольере " << enclosure->getClimate() << " погибли животные от тиаравируса!\n";

            for (int i = 0; i < std::min((int)infectedAnimals.size(), 2); ++i) {
                Animal* dyingAnimal = infectedAnimals.back();
                infectedAnimals.pop_back(); // Удаляем из списка заражённых перед удалением объекта

                sickAnimals.erase(std::remove_if(sickAnimals.begin(), sickAnimals.end(),
                    [&](const SickAnimal& s) { return s.animal == dyingAnimal; }),
                    sickAnimals.end());

                delete dyingAnimal;
                animals.erase(std::remove(animals.begin(), animals.end(), dyingAnimal), animals.end());
            }
        }
    }

    // Популярность снижается за каждое больное животное
    totalPopularityChange -= sickAnimals.size();

    // 12. Изменение популярности (учёт бонусов, болезней и случайных изменений)

    // Уменьшение популярности за больных животных
    int illnessPenalty = sickAnimals.size();
    totalPopularityChange -= illnessPenalty;

    // Добавление бонуса от посетителей
    totalPopularityChange += popularityBonus;

    popularity += totalPopularityChange;
    if (popularity < 0) {
        popularity = std::max(1, popularity + totalPopularityChange);
    }

    if (animalCount <= 0) {
        popularity = 1;
        std::cout << "Популярность остаётся минимальной из-за отсутсвия животных\n";
        totalPopularityChange = 0;
    }

    std::cout << "Итоговое изменение популярности за день: " << totalPopularityChange
        << ", теперь она составляет " << popularity << ".\n";
}

void Zoo::manageEmployees() {
    std::cout << "\nМенеджмент работников:\n";
    std::cout << "1. Нанять работника\n";
    std::cout << "2. Уволить работника\n";
    std::cout << "3. Просмотреть список работников\n";
    std::cout << "Ваш выбор: ";
    int choice;
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка ввода. Попробуйте снова.\n";
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
            std::cout << "Неверный выбор.\n";
            break;
    }
}

void Zoo::hireEmployee() {
    std::string name;
    int typeChoice;

    std::cout << "Введите имя нового работника: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Выберите тип работника:\n"
        << "1. Ветеринар (обслуживает до 20 животных, зарплата 20)\n"
        << "2. Уборщик (обслуживает 1 вольер, зарплата 12)\n"
        << "3. Кормильщик (обслуживает 2 вольера, зарплата 15)\n";
    std::cin >> typeChoice;

    if (std::cin.fail() || typeChoice < 1 || typeChoice > 3) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка ввода. Нанимать не удалось.\n";
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
    std::cout << "Работник " << name << " нанят как " << employees.back().getRoleString() << ".\n";
}

void Zoo::fireEmployee() {
    if (employees.empty()) {
        std::cout << "\nВ зоопарке нет работников для увольнения.\n";
        return;
    }

    std::cout << "\n--- Увольнение работника ---\n";
    std::cout << "Список работников:\n";
    for (size_t i = 0; i < employees.size(); ++i) {
        std::cout << i + 1 << ". " << employees[i].getName()
            << " (Должность: " << (employees[i].getRole() == EmployeeRole::CLEANER ? "Уборщик" :
                employees[i].getRole() == EmployeeRole::FEEDER ? "Кормильщик" : "Экскурсовод")
            << ")\n";
    }

    std::cout << "Введите номер работника для увольнения: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice < 1 || choice > employees.size()) {
        std::cout << "Неверный выбор.\n";
        return;
    }

    std::cout << "Работник " << employees[choice - 1].getName() << " уволен.\n";
    employees.erase(employees.begin() + choice - 1);
}

void Zoo::listEmployees() const {
    if (employees.empty()) {
        std::cout << "В зоопарке пока нет работников.\n";
        return;
    }

    std::cout << "\n--- Список работников ---\n";
    for (const auto& employee : employees) {
        std::cout << "Имя: " << employee.getName()
            << ", Тип: ";
        switch (employee.getRole()) {
        case EmployeeRole::VETERINARIAN:
            std::cout << "Ветеринар";
            break;
        case EmployeeRole::CLEANER:
            std::cout << "Уборщик";
            break;
        case EmployeeRole::FEEDER:
            std::cout << "Кормильщик";
            break;
        }
        std::cout << ", Зарплата: " << employee.getSalary() << "\n";
    }
}

void Zoo::displayEnclosureInfo() const {
    if (enclosures.empty()) {
        std::cout << "\nВ зоопарке нет вольеров.\n";
        return;
    }

    std::cout << "\n--- Информация о вольерах ---\n";
    for (size_t i = 0; i < enclosures.size(); ++i) {
        const Enclosure& enc = enclosures[i];
        std::string typeName;
        if (enc.getAllowedType() == AnimalType::CARNIVORE) {
            typeName = "Хищники";
        }
        else if (enc.getAllowedType() == AnimalType::HERBIVORE) {
            typeName = "Травоядные";
        }
        else if (enc.getAllowedType() == AnimalType::AQUATIC) {
            typeName = "Водоплавающие";
        }
        if (enc.getCurrentCount() == 0) {
            std::cout << "  Этот вольер пуст.\n";
        }

        std::cout << "Вольер " << i + 1 << ":\n";
        std::cout << "  Тип животных: " << typeName << "\n";
        std::cout << "  Климат: " << enc.getClimate() << "\n";
        std::cout << "  Вместимость: " << enc.getCapacity() << "\n";
        std::cout << "  Текущее количество животных: " << enc.getCurrentCount() << "\n";
        std::cout << "  Ежедневные расходы: " << enc.getDailyExpense() << " монет\n";
    }
}

int Zoo::totalAnimalCount() const {
    return animals.size(); // Возвращает общее количество животных в зоопарке
}

bool Zoo::isGameOver() const {
    return money < 0; // Игра заканчивается, если нет денег
}

void Zoo::refreshPurchasePool() {
    purchasePool.clear();
    for (int i = 0; i < 10; ++i) {
        const AnimalInfo& info = animalOptions[std::rand() % animalOptions.size()];
        Gender randomGender = (std::rand() % 2 == 0) ? Gender::MALE : Gender::FEMALE;
        purchasePool.push_back(new Animal(info.name, info.species, randomGender, 0, -1, info.climate, info.price, info.type));
    }
    std::cout << "Пул животных обновлён.\n";
}

void Zoo::updatePurchasePool() {
    const int updateCost = 100; // Стоимость обновления

    if (money < updateCost) {
        std::cout << "Недостаточно денег для обновления пула животных! Нужно " << updateCost << " монет.\n";
        return;
    }

    money -= updateCost; // Списываем деньги
    refreshPurchasePool(); // Обновляем пул животных
    std::cout << "Пул животных обновлён за " << updateCost << " монет.\n";
}

void Zoo::renameAnimal() {
    if (animals.empty()) {
        std::cout << "В зоопарке нет животных для переименования.\n";
        return;
    }

    // Вывод списка животных
    std::cout << "\n--- Список животных ---\n";
    for (size_t i = 0; i < animals.size(); ++i) {
        std::cout << i + 1 << ". Имя: " << animals[i]->getName() << " (Вид: " << animals[i]->getSpecies() << ")\n";
    }

    // Выбор животного для переименования
    std::cout << "Введите номер животного, которое хотите переименовать: ";
    size_t choice;
    std::cin >> choice;

    if (choice < 1 || choice > animals.size()) {
        std::cout << "Неверный выбор. Переименование отменено.\n";
        return;
    }

    // Ввод нового имени
    std::cout << "Введите новое имя для животного: ";
    std::string newName;
    std::cin.ignore();
    std::getline(std::cin, newName);

    // Изменение имени
    animals[choice - 1]->setName(newName);
}

void Zoo::breedAnimals() {
    if (animals.size() < 2) {
        std::cout << "В зоопарке недостаточно животных для размножения.\n";
        return;
    }

    std::cout << "\n--- Список животных ---\n";
    for (size_t i = 0; i < animals.size(); ++i) {
        const Animal* animal = animals[i];
        std::cout << i + 1 << ". Имя: " << animal->getName()
            << " (Вид: " << animal->getSpecies()
            << ", Пол: " << (animal->getGender() == Gender::MALE ? "Мужской" : "Женский")
            << ", Возраст: " << animal->getAgeInDays() << " дней)\n";
    }

    std::cout << "Введите номер первого животного: ";
    size_t parent1Index, parent2Index;
    std::cin >> parent1Index;

    std::cout << "Введите номер второго животного: ";
    std::cin >> parent2Index;

    if (parent1Index < 1 || parent1Index > animals.size() ||
        parent2Index < 1 || parent2Index > animals.size()) {
        std::cout << "Неверный выбор. Размножение отменено.\n";
        return;
    }

    Animal* parent1 = animals[parent1Index - 1];
    Animal* parent2 = animals[parent2Index - 1];

    if (parent1->getGender() == parent2->getGender()) {
        std::cout << "Ошибка: Оба животного одного пола. Размножение невозможно.\n";
        return;
    }

    if (parent1->getSpecies() == parent2->getSpecies()) {
        if (parent1->getAgeInDays() < 5 && parent2->getAgeInDays() < 5) {
            std::cout << "Ошибка: хотя бы один родитель должен быть старше 5 дней!\n";
            return;
        }

        Animal* child = *parent1 + *parent2;
        if (child) {
            addAnimalToEnclosure(child, parent1->getType());
            std::cout << "Поздравляем! У " << parent1->getSpecies() << " родился малыш: " << child->getName() << "!\n";
        }
        else {
            std::cout << "Размножение не удалось.\n";
        }
    }
    else {
        if (parent1->getAgeInDays() < 5 || parent2->getAgeInDays() < 5) {
            std::cout << "Ошибка: оба родителя должны быть старше 5 дней!\n";
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
        std::cout << "Поздравляем! Родился новый гибрид: " << hybridName << " (Вид: " << hybridSpecies << ")\n";
    }
}


void Zoo::addAnimalToEnclosure(Animal* child, AnimalType type) {
    for (auto& enclosure : enclosures) {
        if (enclosure.getAllowedType() == type && enclosure.hasFreeSlot()) {
            enclosure.addAnimal(); // Добавляем в вольер
            animals.push_back(child); // Добавляем потомка в список животных
            std::cout << "Новое животное добавлено в вольер!\n";
            return;
        }
    }

    std::cerr << "Ошибка: Нет свободного места в вольерах для потомка!\n";
    delete child; // Удаляем потомка, если добавить не удалось
}

void Zoo::healAnimal() {
    // Проверяем наличие ветеринара
    bool hasVeterinarian = std::any_of(employees.begin(), employees.end(),
        [](const Employee& emp) { return emp.getRole() == EmployeeRole::VETERINARIAN; });

    if (!hasVeterinarian) {
        std::cout << "В зоопарке нет ветеринара! Лечение невозможно.\n";
        return;
    }

    if (sickAnimals.empty()) {
        std::cout << "Нет больных животных для лечения.\n";
        return;
    }

    sickAnimals.erase(std::remove_if(sickAnimals.begin(), sickAnimals.end(),
        [&](const SickAnimal& sick) { return std::find(animals.begin(), animals.end(), sick.animal) == animals.end(); }),
        sickAnimals.end());

    std::cout << "Выберите животное для лечения:\n";
    for (size_t i = 0; i < sickAnimals.size(); ++i) {
        std::cout << i + 1 << ". " << sickAnimals[i].animal->getName()
            << " (Болеет " << sickAnimals[i].daysSick << " дней)\n";
    }

    int choice;
    std::cin >> choice;

    if (std::cin.fail() || choice < 1 || choice > static_cast<int>(sickAnimals.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка ввода. Пожалуйста, введите корректный номер животного.\n";
        return;
    }

    Animal* healedAnimal = sickAnimals[choice - 1].animal;
    std::cout << "Животное " << healedAnimal->getName() << " полностью выздоровело!\n";

    sickAnimals.erase(std::remove_if(sickAnimals.begin(), sickAnimals.end(),
        [&](const SickAnimal& sick) { return sick.animal == healedAnimal; }),
        sickAnimals.end());
}


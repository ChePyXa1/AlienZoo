#include "Animal.h"
#include <cstdlib>
#include <ctime>

// Конструктор класса Animal
Animal::Animal(const std::string& name, const std::string& species, Gender gender,
    int ageInDays, double weight, const std::string& preferredClimate,
    double price, AnimalType type, bool isBornInZoo,
    const std::string& parent1Name, const std::string& parent2Name)
    : name(name), species(species), gender(gender), ageInDays(ageInDays),
    preferredClimate(preferredClimate), price(price), type(type),
    isBornInZoo(isBornInZoo),
    parents(ParentInfo(parent1Name, species, Gender::MALE), ParentInfo(parent2Name, species, Gender::FEMALE))
{
    if (weight == -1) {
        this->weight = generateRandomDouble(50.0, 500.0);
    }
    else {
        this->weight = weight;
    }
}




// Деструктор класса Animal
Animal::~Animal() {}

// Возвращает имя животного
std::string Animal::getName() const {
    return name;
}

// Возвращает вид животного
std::string Animal::getSpecies() const {
    return species;
}

// Возвращает возраст в днях
int Animal::getAgeInDays() const {
    return ageInDays;
}

// Возвращает вес животного
double Animal::getWeight() const {
    return weight;
}

// Возвращает предпочтительный климат животного
std::string Animal::getPreferredClimate() const {
    return preferredClimate;
}

// Возвращает цену животного
double Animal::getPrice() const {
    return price;
}

// Возвращает тип животного
AnimalType Animal::getType() const {
    return type;
}

// Возвращает пол животного
Gender Animal::getGender() const {
    return gender;
}

// Возвращает информацию о родителях
std::pair<ParentInfo, ParentInfo> Animal::getParents() const {
    return parents;
}

// Проверяет, родилось ли животное в зоопарке
bool Animal::wasBornInZoo() const {
    return isBornInZoo;
}

// Увеличивает возраст животного в днях
void Animal::increaseAgeInDays() {
    ageInDays++;
}

// Проверяет смерть животного после 10 дней
bool Animal::checkDeathAfterTenDays() const {
    if (ageInDays > 10) {
        return (std::rand() % 100) < 20; // 20% шанс смерти
    }
    return false;
}

// Перегрузка оператора + для размножения животных
Animal* Animal::operator+(Animal& partner) {
    // Проверка: животные должны быть одного вида
    if (species != partner.getSpecies()) {
        std::cerr << "Ошибка: Разные виды животных не могут размножаться!\n";
        return nullptr;
    }

    // Проверка: животные должны быть разнополыми
    if (gender == partner.getGender()) {
        std::cerr << "Ошибка: Однополое размножение невозможно!\n";
        return nullptr;
    }

    // Проверка: животные должны быть старше 5 дней
    if (ageInDays < 5 || partner.getAgeInDays() < 5) {
        std::cerr << "Ошибка: Животные должны быть старше 5 дней для размножения!\n";
        return nullptr;
    }

    // Генерация пола потомка
    Gender childGender = (std::rand() % 2 == 0) ? Gender::MALE : Gender::FEMALE;

    // Создание нового животного
    Animal* child = new Animal("Безымянный", species, childGender, 0, -1, preferredClimate, price, type, true);
    child->parents = { ParentInfo(name, species, gender), ParentInfo(partner.getName(), partner.getSpecies(), partner.getGender()) }; // Сохраняем данные родителей

    std::cout << "Новое животное родилось! Вид: " << species << "\n";

    return child;
}

// Генерация случайного числа с плавающей точкой (Необходимо для случайной генерации веса животного)
double Animal::generateRandomDouble(double min, double max) const {
    double f = (double)std::rand() / RAND_MAX;
    return min + f * (max - min);
}

// Изменение имени животного
void Animal::setName(const std::string& newName) {
    name = newName;
    std::cout << "Имя животного успешно изменено на: " << name << "\n";
}

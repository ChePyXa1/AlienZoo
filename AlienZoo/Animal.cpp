#include "Animal.h"
#include <cstdlib>
#include <ctime>

// ����������� ������ Animal
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




// ���������� ������ Animal
Animal::~Animal() {}

// ���������� ��� ���������
std::string Animal::getName() const {
    return name;
}

// ���������� ��� ���������
std::string Animal::getSpecies() const {
    return species;
}

// ���������� ������� � ����
int Animal::getAgeInDays() const {
    return ageInDays;
}

// ���������� ��� ���������
double Animal::getWeight() const {
    return weight;
}

// ���������� ���������������� ������ ���������
std::string Animal::getPreferredClimate() const {
    return preferredClimate;
}

// ���������� ���� ���������
double Animal::getPrice() const {
    return price;
}

// ���������� ��� ���������
AnimalType Animal::getType() const {
    return type;
}

// ���������� ��� ���������
Gender Animal::getGender() const {
    return gender;
}

// ���������� ���������� � ���������
std::pair<ParentInfo, ParentInfo> Animal::getParents() const {
    return parents;
}

// ���������, �������� �� �������� � ��������
bool Animal::wasBornInZoo() const {
    return isBornInZoo;
}

// ����������� ������� ��������� � ����
void Animal::increaseAgeInDays() {
    ageInDays++;
}

// ��������� ������ ��������� ����� 10 ����
bool Animal::checkDeathAfterTenDays() const {
    if (ageInDays > 10) {
        return (std::rand() % 100) < 20; // 20% ���� ������
    }
    return false;
}

// ���������� ��������� + ��� ����������� ��������
Animal* Animal::operator+(Animal& partner) {
    // ��������: �������� ������ ���� ������ ����
    if (species != partner.getSpecies()) {
        std::cerr << "������: ������ ���� �������� �� ����� ������������!\n";
        return nullptr;
    }

    // ��������: �������� ������ ���� �����������
    if (gender == partner.getGender()) {
        std::cerr << "������: ��������� ����������� ����������!\n";
        return nullptr;
    }

    // ��������: �������� ������ ���� ������ 5 ����
    if (ageInDays < 5 || partner.getAgeInDays() < 5) {
        std::cerr << "������: �������� ������ ���� ������ 5 ���� ��� �����������!\n";
        return nullptr;
    }

    // ��������� ���� �������
    Gender childGender = (std::rand() % 2 == 0) ? Gender::MALE : Gender::FEMALE;

    // �������� ������ ���������
    Animal* child = new Animal("����������", species, childGender, 0, -1, preferredClimate, price, type, true);
    child->parents = { ParentInfo(name, species, gender), ParentInfo(partner.getName(), partner.getSpecies(), partner.getGender()) }; // ��������� ������ ���������

    std::cout << "����� �������� ��������! ���: " << species << "\n";

    return child;
}

// ��������� ���������� ����� � ��������� ������ (���������� ��� ��������� ��������� ���� ���������)
double Animal::generateRandomDouble(double min, double max) const {
    double f = (double)std::rand() / RAND_MAX;
    return min + f * (max - min);
}

// ��������� ����� ���������
void Animal::setName(const std::string& newName) {
    name = newName;
    std::cout << "��� ��������� ������� �������� ��: " << name << "\n";
}

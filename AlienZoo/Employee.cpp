#include "Employee.h"

Employee::Employee(const std::string& name, EmployeeRole role, double salary)
    : name(name), role(role), salary(salary) {}

std::string Employee::getName() const {
    return name;
}

EmployeeRole Employee::getRole() const {
    return role;
}

double Employee::getSalary() const {
    return salary;
}

std::string Employee::getRoleString() const {
    switch (role) {
    case EmployeeRole::CLEANER:
        return "Уборщик";
    case EmployeeRole::FEEDER:
        return "Кормильщик";
    case EmployeeRole::VETERINARIAN:
        return "Ветеринар";
    default:
        return "Неизвестная роль";
    }
}

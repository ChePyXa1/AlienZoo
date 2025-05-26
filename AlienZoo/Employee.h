#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

// Перечисление типов сотрудников
enum class EmployeeRole {
    CLEANER,      // Уборщик
    FEEDER,       // Кормильщик
    VETERINARIAN  // Ветеринар
};

class Employee {
private:
    std::string name;       // Имя сотрудника
    EmployeeRole role;      // Роль сотрудника
    double salary;          // Зарплата сотрудника

public:
    // Конструктор
    Employee(const std::string& name, EmployeeRole role, double salary);

    // Геттеры
    std::string getName() const;
    EmployeeRole getRole() const;
    double getSalary() const;

    // Строковое представление роли
    std::string getRoleString() const;
};

#endif

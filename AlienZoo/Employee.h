#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

// ������������ ����� �����������
enum class EmployeeRole {
    CLEANER,      // �������
    FEEDER,       // ����������
    VETERINARIAN  // ���������
};

class Employee {
private:
    std::string name;       // ��� ����������
    EmployeeRole role;      // ���� ����������
    double salary;          // �������� ����������

public:
    // �����������
    Employee(const std::string& name, EmployeeRole role, double salary);

    // �������
    std::string getName() const;
    EmployeeRole getRole() const;
    double getSalary() const;

    // ��������� ������������� ����
    std::string getRoleString() const;
};

#endif

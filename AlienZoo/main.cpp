#include "Zoo.h"
#include <iostream>
#include <windows.h>
#include <limits>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string zooName;
    std::cout << "������� �������� ������ ������������� ��������: ";
    std::getline(std::cin, zooName);

    Zoo zoo(zooName);
    const int simulationDaysGoal = 30;

    while (true) {
        if (zoo.isGameOver()) {
            std::cout << "\n� ��� ��������� ������. �� ���������.\n";
            break;
        }
        if (zoo.getCurrentDay() > simulationDaysGoal) {
            std::cout << "\n�����������! �� ������������ " << simulationDaysGoal
                << " ����. �� ��������!\n";
            break;
        }

        zoo.displayStatus();
        zoo.displayMenu();
        zoo.processChoice();
    }

    return 0;
}

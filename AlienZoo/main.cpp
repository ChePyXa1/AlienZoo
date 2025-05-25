#include "Zoo.h"
#include <iostream>
#include <windows.h>
#include <limits>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string zooName;
    std::cout << "Введите название вашего инопланетного зоопарка: ";
    std::getline(std::cin, zooName);

    Zoo zoo(zooName);
    const int simulationDaysGoal = 30;

    while (true) {
        if (zoo.isGameOver()) {
            std::cout << "\nУ вас кончились деньги. Вы проиграли.\n";
            break;
        }
        if (zoo.getCurrentDay() > simulationDaysGoal) {
            std::cout << "\nПоздравляем! Вы продержались " << simulationDaysGoal
                << " дней. Вы выиграли!\n";
            break;
        }

        zoo.displayStatus();
        zoo.displayMenu();
        zoo.processChoice();
    }

    return 0;
}

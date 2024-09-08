#include <iostream>
#include <limits> // для numeric_limits

// Функция для проверки, является ли число числом, цифры которого идут по возрастанию
bool isAscending(int num) {
    if (num / 10 < 1) {
        return false;
    }
    else {
        int lastDigit = 10; // Начинаем с невозможной цифры
        while (num > 0) {
            int digit = num % 10;
            if (digit >= lastDigit) {
                return false;
            }
            lastDigit = digit;
            num /= 10;
        }
        return true;
    }
}

// Функция для переворачивания числа
int reverseNumber(int num) {
    int reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return reversed;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    int num;

    // Считываем количество чисел
    std::cin >> n;
    if (std::cin.fail() || n <= 0) {
        std::cout << "Ошибка: введено некорректное значение." << std::endl;
        return 1;
    }

    // Считываем и обрабатываем числа по одному
    for (int i = 0; i < n; ++i) {
        std::cin >> num;
        if (std::cin.fail()) {
            std::cout << "Ошибка: введено некорректное значение." << std::endl;
            return 1;
        }

        // Если число состоит из цифр, идущих по возрастанию, переворачиваем его
        if (isAscending(num)) {
            std::cout << reverseNumber(num) << " ";
        }
    }

    // Завершаем программу после вывода обратных чисел
    return 0;
}

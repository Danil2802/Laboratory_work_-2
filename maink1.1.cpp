#include <iostream>
#include <string>
#include <cctype> // Для функции isalpha
#include <sstream> // Для работы с потоками строк

// Функция для получения следующей буквы алфавита
char nextChar(char c) {
    if (c == 'z') return 'a'; // Если это 'z', то следующая буква будет 'a'
    if (c == 'Z') return 'A'; // То же самое для заглавной 'Z'
    return c + 1; // Для всех остальных букв просто увеличиваем код символа на 1
}

// Функция для добавления символов в строку, чтобы избежать трех одинаковых символов подряд
std::string makeValidString(std::string str) {
    std::string result;
    int count = 1;

    for (int i = 0; i < str.length(); i++) {
        result += str[i];
        if (i < str.length() - 1 && str[i] == str[i + 1]) {
            count++;
            if (count == 3) {
                result += nextChar(str[i]); // Добавляем следующую букву алфавита
                count = 1; // Сбрасываем счетчик
            }
        }
        else {
            count = 1; // Сбрасываем счетчик, если текущий и следующий символы различны
        }
    }
    return result;
}

// Функция для подсчета минимального количества добавлений
int minAdditions(std::string str) {
    int additions = 0;
    int count = 1;

    for (int i = 1; i < str.length(); i++) {
        if (str[i] == str[i - 1]) {
            count++;
            if (count == 3) {
                additions++;
                count = 1;
            }
        }
        else {
            count = 1;
        }
    }
    return additions;
}

// Функция для проверки, есть ли пробелы 
bool isSingleWord(const std::string& str) {
    std::stringstream ss(str);
    std::string word;
    int wordCount = 0;

    while (ss >> word) {
        wordCount++;
        if (wordCount > 1) {
            return false; // Если строчек больше одной, возвращаем false
        }
    }
    return wordCount == 1; // Возвращаем true, если строчка одна
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string inputStr;

    while (true) {
        std::cout << "Введите строчку: ";
        std::getline(std::cin, inputStr);

        if (!isSingleWord(inputStr)) {
            std::cout << "Пожалуйста, введите строку без пробелов." << std::endl;
            continue;
        }

        bool isValid = true;
        for (int i = 0; i < inputStr.length(); i++) {
            if (!isalpha(inputStr[i])) {
                isValid = false;
                break;
            }
        }

        if (isValid) {
            break;
        }
        else {
            std::cout << "Недопустимые символы. Пожалуйста, введите строчку заново." << std::endl;
        }
    }

    int additions = minAdditions(inputStr);
    std::string validStr = makeValidString(inputStr);

    std::cout << "Минимальное количество добавлений: " << additions << std::endl;
    std::cout << "Измененная строка: " << validStr << std::endl;

    return 0;
}

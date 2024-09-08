# Лабораторная работа №2
## «Классификация языков программирования»
## по дисциплине: «Программирование»
### Цели и задачи работы: изучение функций ввода-вывода данных, программирования вычисления значения выражения. 
### Задание к работе: 
### 1. Реализовать линейный вычислительный процесс. Самостоятельно решить задачу в соответствии с индивидуальным вариантом. Реализовать представленные задачи на языках программирования JavaScript, Go (Golang), Swift, С#, Haskell, Ruby, Rust, C++, Python, Java, Kotlin. 
### 2. Реализовать линейный вычислительный процесс любого задания на языке программирования Assembler. 
### 3. Представленные задачи можно реализовать на каждом языке в одной программе с последовательным выполнением.
### Методика выполнения работы: 
### 1. Определить типы используемых в программе данных. 
### 2. Описать переменные. 
### 3. Написать функции ввода-вывода. 
### 4. Разработать алгоритм решения задачи по индивидуальному заданию. 
### 5. Написать и отладить программу с вводом-выводом информации 
### 6. Протестировать работу программы на различных исходных данных. 
### 7. Изменить формат вывода, проверить работу программы при другом формате вывода.

### Индивидуальные задания:
### Задание 1:
### Вам задана строка. Для того, чтобы она стала действительной, необходимо ее изменить в соответствии со следующими правилами: 
### - Строка не должна содержать трех одинаковых символов подряд. 
### - Можно добавлять любое количество символов в любом месте строки. 
### Найдите минимальное количество символов, которое необходимо добавить в строку, чтобы сделать ее действительной. 
### Пример: str=’nnnsstuu’ 
### Результат: 1 = nnsnsstuu 
### Пример: str=’aaaaaa’ 
### Результат: 2 = aabaabaa
### Решение задачи на языке С++ в maink1.1.cpp
```C++
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
```
### Решение 1 задачи на других языках смотрите в файлах: maink1.2.txt - maink1.12.txt

### Задание 2: 
### Дан массив строк, где каждое слово может быть записано как с позиций азбуки Морзе. Определить количество уникальных слов на азбуке Морзе при условии, что буквы можно переставлять. Принять длину слова в строке не более 11 символов. Количество слов не ограничено. 
### Пример 1: 
### Input: ign igg ezn smg 
### Output: 2 
### Примечание: Строка содержит только 2 вида кодов: "--...-." "--...--.". 
### Пример 2: 
### Input: b 
### Output: 1 
### Ограничения: 
### • 1 <= words.length <= 100 
### • 1 <= words[i].length < 12 
### • words[i]состоит из строчных английских букв.
### Решение задачи на языке С++ в mainkp2.1.cpp
```C++
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

// Функция для преобразования символа в азбуку Морзе
std::string charToMorse(char c) {
    std::unordered_map<char, std::string> morseMap = {
        {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
        {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
        {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
        {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
        {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
        {'Z', "--.."}
    };

    c = toupper(c); // Переводим символ в верхний регистр
    if (morseMap.find(c) != morseMap.end()) {
        return morseMap[c];
    }
    else {
        return ""; // Возвращаем пустую строку для неизвестных символов
    }
}

// Функция для преобразования перестановки в азбуку Морзе
std::string permToMorse(const std::string& perm) {
    std::string morsePerm;
    for (char c : perm) {
        morsePerm += charToMorse(c);
    }
    return morsePerm;
}

// Функция для получения всех перестановок символов в строке
std::vector<std::string> getPermutations(const std::string& str) {
    std::vector<std::string> permutations;
    std::string sortedStr = str;
    std::sort(sortedStr.begin(), sortedStr.end());

    do {
        permutations.push_back(sortedStr);
    } while (std::next_permutation(sortedStr.begin(), sortedStr.end()));

    return permutations;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string input;
    std::cout << "Введите строку: ";
    std::getline(std::cin, input); // Ввод строки

    for (char c : input) {
        if (!isalpha(c) && !isspace(c)) {
            std::cout << "Не балуетесь" << std::endl;
            return 0;
        }
    }

    std::istringstream iss(input);
    std::string word;
    std::vector<std::string> words;
    int wordCount = 0;
    std::vector<std::vector<std::string>> allPermutations;

    // Разделение строки на слова и получение перестановок для каждого слова
    while (iss >> word) {
        if (word.length() > 11) {
            std::cout << "Слишком длинное слово: " << word << std::endl;
            return 0; // Завершаем работу кода при обнаружении слишком длинного слова
        }
        words.push_back(word);
        wordCount++;

        if (wordCount > 100) {
            std::cout << "Слишком много слов" << std::endl;
            return 0;
        }

        allPermutations.push_back(getPermutations(word));
    }

    // Отслеживание слов с уникальными перестановками в азбуке Морзе
    std::unordered_set<std::string> uniqueMorsePerms;
    std::vector<std::string> wordsWithUniquePerms;

    for (size_t i = 0; i < words.size(); ++i) {
        bool hasUniquePerm = true;
        for (const auto& perm : allPermutations[i]) {
            std::string morse = permToMorse(perm);
            if (uniqueMorsePerms.find(morse) != uniqueMorsePerms.end()) {
                hasUniquePerm = false;
                break;
            }
        }
        if (hasUniquePerm) {
            wordsWithUniquePerms.push_back(words[i]);
            for (const auto& perm : allPermutations[i]) {
                uniqueMorsePerms.insert(permToMorse(perm));
            }
        }
    }

    // Вывод количества слов с уникальными перестановками и одного из таких слов
    std::cout << "Количество слов с уникальными перестановками в азбуке Морзе: " << wordsWithUniquePerms.size() << std::endl;
    return 0;
}
```
### Решение 2 задачи на других языках смотрите в файлах: mainkp2.2.txt - mainkp2.10.txt

### Задание 3: 
### С клавиатуры вводится число n, после чего вводятся n чисел. Все числа из последовательности, которые составлены из цифр, идущих по возрастанию необходимо перевернуть и вывести на экран. 
### Пример. 
### Вход: 4 87 129 33 45 
### Выход: 921 54.
### Решение задачи на языке С++ в mainl3.1.cpp
```C++
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
```
### Решение 3 задачи на других языках смотрите в файлах: mainl3.2.txt - mainl3.10.txt



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

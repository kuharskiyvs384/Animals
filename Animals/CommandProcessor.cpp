#include "AnimalContainer.h"
#include "AnimalFactory.h"
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>
#include <windows.h>

class CommandProcessor {
    AnimalContainer container;

    // Парсит "key=value" токены в map
    static std::map<std::string, std::string> parseKV(std::istringstream& iss) {
        std::map<std::string, std::string> kv;
        std::string token;
        while (iss >> token) {
            auto pos = token.find('=');
            if (pos != std::string::npos) {
                kv[token.substr(0, pos)] = token.substr(pos + 1);
            }
        }
        return kv;
    }

    // Извлекает тип и параметры из потока, делегирует создание объекта фабрике.
    static std::unique_ptr<IAnimal> parseAdd(std::istringstream& iss) {
        std::string type;
        iss >> type;
        auto kv = parseKV(iss);
        return AnimalFactory::create(type, kv);
    }

public:
    void processFile(const std::string& filename) {
        std::ifstream fin(filename);
        if (!fin) {
            std::cerr << "Не удалось открыть файл: " << filename << "\n";
            return;
        }
        std::string line;
        int lineNum = 0;
        while (std::getline(fin, line)) {
            ++lineNum;
            if (line.empty() || line[0] == '#') continue;
            std::istringstream iss(line);
            std::string cmd;
            iss >> cmd;
            try {
                if (cmd == "ADD") {
                    container.add(parseAdd(iss));
                    std::cout << "ADD ok (строка " << lineNum << ")\n";
                } else if (cmd == "REM") {
                    std::string field, op, value;
                    iss >> field >> op >> value;
                    container.remove(field, op, value);
                } else if (cmd == "PRINT") {
                    container.print();
                } else {
                    std::cerr << "Неизвестная команда: " << cmd << "\n";
                }
            } catch (const std::exception& e) {
                std::cerr << "Ошибка в строке " << lineNum
                          << ": " << e.what() << "\n";
            }
        }
    }
};

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);   // вывод в UTF-8
    SetConsoleCP(CP_UTF8);         // ввод в UTF-8
    std::string file = (argc > 1) ? argv[1] : "commands.txt";
    CommandProcessor cp;
    cp.processFile(file);
    return 0;
}
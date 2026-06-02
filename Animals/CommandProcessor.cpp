#include "AnimalContainer.h"
#include "AnimalFactory.h"
#include "CommandParser.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <windows.h>

class CommandProcessor {
    AnimalContainer container;

    // Маршрутизация команды ADD: первый токен — тип, остальные — параметры key=value
    void handleAdd(const std::vector<std::string>& tokens) {
        if (tokens.empty()) {
            throw std::invalid_argument("ADD: missing animal type");
        }
        const std::string& type = tokens[0];
        std::vector<std::string> params(tokens.begin() + 1, tokens.end());
        auto kv = CommandParser::parseKV(params);
        container.add(AnimalFactory::create(type, kv));
    }

    // Маршрутизация команды REM: ожидается ровно три токена — field, op, value
    void handleRem(const std::vector<std::string>& tokens) {
        if (tokens.size() < 3) {
            throw std::invalid_argument("REM: expected <field> <op> <value>");
        }
        container.remove(tokens[0], tokens[1], tokens[2]);
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
            ParsedCommand pc = CommandParser::parse(line);

            // Пустые строки и комментарии пропускаем
            if (pc.command.empty()) continue;

            try {
                if (pc.command == "ADD") {
                    handleAdd(pc.tokens);
                    std::cout << "ADD ok (строка " << lineNum << ")\n";
                } else if (pc.command == "REM") {
                    handleRem(pc.tokens);
                } else if (pc.command == "PRINT") {
                    container.print();
                } else {
                    std::cerr << "Неизвестная команда: " << pc.command << "\n";
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
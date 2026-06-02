#include "FileProcessor.h"
#include "CommandParser.h"
#include <fstream>
#include <iostream>

void FileProcessor::processFile(const std::string& filename) {
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
            manager.execute(pc);
            if (pc.command == "ADD") {
                std::cout << "ADD ok (строка " << lineNum << ")\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка в строке " << lineNum
                      << ": " << e.what() << "\n";
        }
    }
}
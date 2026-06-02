#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include <vector>
#include <map>

// Результат разбора одной строки команды.
struct ParsedCommand {
    std::string command;              // ADD / REM / PRINT / пустая строка для комментариев
    std::vector<std::string> tokens;  // остальные токены строки (без имени команды)
};

// Класс, отвечающий за лексический разбор команд.
// Не зависит от доменной модели — работает только со строками.
class CommandParser {
public:
    // Разбирает строку файла на команду и токены.
    // Пустые строки и строки-комментарии (начинаются с '#') возвращаются
    // с пустым полем command.
    [[nodiscard]] static ParsedCommand parse(const std::string& line);

    // Объединяет токены вида key=value в map.
    // Токены без знака '=' игнорируются.
    [[nodiscard]] static std::map<std::string, std::string> parseKV(
        const std::vector<std::string>& tokens);
};

#endif
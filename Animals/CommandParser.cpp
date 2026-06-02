#include "CommandParser.h"
#include <sstream>

ParsedCommand CommandParser::parse(const std::string& line) {
    ParsedCommand result;

    // Пропускаем пустые строки и комментарии
    if (line.empty() || line[0] == '#') {
        return result;
    }

    std::istringstream iss(line);
    iss >> result.command;

    std::string token;
    while (iss >> token) {
        result.tokens.push_back(token);
    }
    return result;
}

std::map<std::string, std::string> CommandParser::parseKV(
    const std::vector<std::string>& tokens) {
    std::map<std::string, std::string> kv;
    for (const auto& token : tokens) {
        auto pos = token.find('=');
        if (pos != std::string::npos) {
            kv[token.substr(0, pos)] = token.substr(pos + 1);
        }
    }
    return kv;
}
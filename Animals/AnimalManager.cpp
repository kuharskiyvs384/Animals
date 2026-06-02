#include "AnimalManager.h"
#include "AnimalFactory.h"
#include <iostream>
#include <stdexcept>

void AnimalManager::execute(const ParsedCommand& pc) {
    if (pc.command == "ADD") {
        handleAdd(pc.tokens);
    } else if (pc.command == "REM") {
        handleRem(pc.tokens);
    } else if (pc.command == "PRINT") {
        handlePrint();
    } else {
        throw std::invalid_argument("Неизвестная команда: " + pc.command);
    }
}

void AnimalManager::handleAdd(const std::vector<std::string>& tokens) {
    if (tokens.empty()) {
        throw std::invalid_argument("ADD: missing animal type");
    }
    const std::string& type = tokens[0];
    std::vector<std::string> params(tokens.begin() + 1, tokens.end());
    auto kv = CommandParser::parseKV(params);
    container.add(AnimalFactory::create(type, kv));
}

void AnimalManager::handleRem(const std::vector<std::string>& tokens) {
    if (tokens.size() < 3) {
        throw std::invalid_argument("REM: expected <field> <op> <value>");
    }
    container.remove(tokens[0], tokens[1], tokens[2]);
}

void AnimalManager::handlePrint() {
    container.print();
}
#ifndef ANIMAL_MANAGER_H
#define ANIMAL_MANAGER_H

#include "AnimalContainer.h"
#include "CommandParser.h"
#include <string>
#include <vector>

// Менеджер коллекции животных.
// Принимает уже разобранные команды (ParsedCommand) и выполняет их.
// Не знает ни о файлах, ни о текстовых строках.
class AnimalManager {
    AnimalContainer container;

public:
    // Выполнить разобранную команду.
    // Бросает std::exception при ошибках выполнения.
    void execute(const ParsedCommand& pc);

private:
    void handleAdd(const std::vector<std::string>& tokens);
    void handleRem(const std::vector<std::string>& tokens);
    void handlePrint();
};

#endif
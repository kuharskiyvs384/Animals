#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include "AnimalManager.h"
#include <string>

// Класс отвечает исключительно за чтение файла построчно
// и передачу строк парсеру + менеджеру.
// Не знает о доменной модели и о конкретных командах.
class FileProcessor {
    AnimalManager& manager;

public:
    explicit FileProcessor(AnimalManager& m) : manager(m) {}

    // Открывает файл и обрабатывает его построчно.
    // Ошибки выполнения отдельных команд логируются, но не прерывают обработку.
    void processFile(const std::string& filename);
};

#endif
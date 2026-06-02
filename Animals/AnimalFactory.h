#ifndef ANIMAL_FACTORY_H
#define ANIMAL_FACTORY_H

#include "IAnimal.h"
#include <memory>
#include <string>
#include <map>

// Фабрика создания объектов-животных по типу и параметрам.
// Инкапсулирует знание о соответствии "тип -> класс -> набор параметров".
// Является единой точкой расширения при добавлении нового вида животного.
class AnimalFactory {
public:
    // Создаёт объект IAnimal по строковому типу и набору параметров key=value.
    // Бросает std::runtime_error / std::invalid_argument при ошибках.
    static std::unique_ptr<IAnimal> create(
        const std::string& type,
        const std::map<std::string, std::string>& kv);

private:
    // Вспомогательная функция: возвращает значение по ключу или бросает исключение.
    static const std::string& requireField(
        const std::map<std::string, std::string>& kv,
        const std::string& key);
};

#endif
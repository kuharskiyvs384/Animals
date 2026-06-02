#ifndef ANIMAL_TYPES_H
#define ANIMAL_TYPES_H

// Константы-идентификаторы типов животных.
// Используются как:
//  - возвращаемые значения IAnimal::getType()
//  - ключи в AnimalFactory::create()
// Единый источник истины — изменение строки в одном месте.
namespace AnimalTypes {
    constexpr const char* FISH   = "FISH";
    constexpr const char* BIRD   = "BIRD";
    constexpr const char* INSECT = "INSECT";
}

#endif
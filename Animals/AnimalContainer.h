#ifndef ANIMAL_CONTAINER_H
#define ANIMAL_CONTAINER_H

#include "IAnimal.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

class AnimalContainer {
    std::vector<std::unique_ptr<IAnimal>> items;
public:
    void add(std::unique_ptr<IAnimal> a) {
        items.push_back(std::move(a));
    }

    void remove(const std::string& field,
                const std::string& op,
                const std::string& value) {
        auto it = std::remove_if(items.begin(), items.end(),
            [&](const std::unique_ptr<IAnimal>& a) {
                return a->matchField(field, op, value);
            });
        size_t removed = std::distance(it, items.end());
        items.erase(it, items.end());
        std::cout << "REM: удалено объектов = " << removed << "\n";
    }

    void print() const {
        std::cout << "----- Содержимое контейнера ("
                  << items.size() << " шт.) -----\n";
        for (const auto& a : items) a->print(std::cout);
        std::cout << "-------------------------------------\n";
    }
};

#endif
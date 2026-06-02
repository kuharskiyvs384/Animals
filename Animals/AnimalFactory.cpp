#include "AnimalFactory.h"
#include "Animal.h"
#include <stdexcept>

const std::string& AnimalFactory::requireField(
    const std::map<std::string, std::string>& kv,
    const std::string& key) {
    auto it = kv.find(key);
    if (it == kv.end()) {
        throw std::invalid_argument("Обязательное поле не указано: " + key);
    }
    return it->second;
}

std::unique_ptr<IAnimal> AnimalFactory::create(
    const std::string& type,
    const std::map<std::string, std::string>& kv) {

    // Общий для всех типов параметр — name
    const std::string& name = requireField(kv, "name");

    if (type == "FISH") {
        const std::string& habitatStr = requireField(kv, "habitat");
        Habitat h = stringToHabitat(habitatStr);
        return std::make_unique<Fish>(name, h);
    }

    if (type == "BIRD") {
        const std::string& speedStr = requireField(kv, "maxspeed");
        double s = std::stod(speedStr);
        return std::make_unique<Bird>(name, s);
    }

    if (type == "INSECT") {
        const std::string& sizeStr = requireField(kv, "size");
        const std::string& dateStr = requireField(kv, "date");
        double sz = std::stod(sizeStr);
        return std::make_unique<Insect>(name, sz, dateStr);
    }

    throw std::runtime_error("Не известный тип животного: " + type);
}
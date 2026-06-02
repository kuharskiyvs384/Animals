#include "AnimalFactory.h"
#include "Animal.h"
#include "AnimalTypes.h"
#include "Utils.h"
#include <stdexcept>

const std::string& AnimalFactory::requireField(
    const std::map<std::string, std::string>& kv,
    const std::string& key) {
    auto it = kv.find(key);
    if (it == kv.end()) {
        throw std::invalid_argument("Missing required field: " + key);
    }
    return it->second;
}

std::unique_ptr<IAnimal> AnimalFactory::create(
    const std::string& type,
    const std::map<std::string, std::string>& kv) {

    const std::string& name = requireField(kv, "name");

    if (type == AnimalTypes::FISH) {
        const std::string& habitatStr = requireField(kv, "habitat");
        Habitat h = stringToHabitat(habitatStr);
        return std::make_unique<Fish>(name, h);
    }

    if (type == AnimalTypes::BIRD) {
        const std::string& speedStr = requireField(kv, "maxspeed");
        auto s = tryParseDouble(speedStr);
        if (!s.has_value()) {
            throw std::invalid_argument("Невозможно распарсить число: " + speedStr);
        }
        return std::make_unique<Bird>(name, s.value());
    }

    if (type == AnimalTypes::INSECT) {
        const std::string& sizeStr = requireField(kv, "size");
        const std::string& dateStr = requireField(kv, "date");
        auto sz = tryParseDouble(sizeStr);
        if (!sz.has_value()) {
            throw std::invalid_argument("Невозможно распарсить число: " + sizeStr);
        }
        return std::make_unique<Insect>(name, sz.value(), dateStr);
    }

    throw std::runtime_error("Unknown animal type: " + type);
}
#include "Animal.h"
#include "Utils.h"
#include <stdexcept>

// Универсальный шаблон сравнения
template <typename T>
static bool compare(const T& a, const std::string& op, const T& b) {
    if (op == "==") return a == b;
    if (op == "!=") return a != b;
    if (op == "<")  return a <  b;
    if (op == ">")  return a >  b;
    if (op == "<=") return a <= b;
    if (op == ">=") return a >= b;
    throw std::runtime_error("Unknown operator: " + op);
}

bool Animal::matchField(const std::string& field,
                        const std::string& op,
                        const std::string& value) const {
    if (field == "name") return compare<std::string>(name, op, value);
    if (field == "type") return compare<std::string>(getType(), op, value);
    return false;
}

bool Fish::matchField(const std::string& field,
                      const std::string& op,
                      const std::string& value) const {
    if (field == "habitat") {
        return compare<std::string>(habitatToString(habitat), op,
                                    habitatToString(stringToHabitat(value)));
    }
    return Animal::matchField(field, op, value);
}

bool Bird::matchField(const std::string& field,
                      const std::string& op,
                      const std::string& value) const {
    if (field == "maxspeed") {
        auto v = tryParseDouble(value);
        if (!v.has_value()) {
            throw std::invalid_argument(
                "Невозможно распарсить число: " + value);
        }
        return compare<double>(maxSpeed, op, v.value());
    }
    return Animal::matchField(field, op, value);
}

bool Insect::matchField(const std::string& field,
                        const std::string& op,
                        const std::string& value) const {
    if (field == "size") {
        auto v = tryParseDouble(value);
        if (!v.has_value()) {
            throw std::invalid_argument(
                "Невозможно распарсить число: " + value);
        }
        return compare<double>(size, op, v.value());
    }
    if (field == "date") return compare<std::string>(date, op, value);
    return Animal::matchField(field, op, value);
}
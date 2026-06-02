#include "Animal.h"
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
        return compare<double>(maxSpeed, op, std::stod(value));
    }
    return Animal::matchField(field, op, value);
}

bool Insect::matchField(const std::string& field,
                        const std::string& op,
                        const std::string& value) const {
    if (field == "size") return compare<double>(size, op, std::stod(value));
    if (field == "date") return compare<std::string>(date, op, value);
    return Animal::matchField(field, op, value);
}
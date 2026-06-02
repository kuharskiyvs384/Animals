#ifndef ANIMAL_H
#define ANIMAL_H

#include "IAnimal.h"
#include <string>
#include <iostream>
#include <stdexcept>

// Перечислимый тип для места обитания рыб
enum class Habitat { RIVER, SEA, LAKE, OCEAN, POND, UNKNOWN };

inline std::string habitatToString(Habitat h) {
    switch (h) {
        case Habitat::RIVER: return "РЕКА";
        case Habitat::SEA:   return "МОРЕ";
        case Habitat::LAKE:  return "ОЗЕРО";
        case Habitat::OCEAN: return "ОКЕАН";
        case Habitat::POND:  return "ПРУД";
        default:             return "НЕИЗВЕСТНО";
    }
}

inline Habitat stringToHabitat(const std::string& s) {
    if (s == "RIVER" || s == "РЕКА")  return Habitat::RIVER;
    if (s == "SEA"   || s == "МОРЕ")  return Habitat::SEA;
    if (s == "LAKE"  || s == "ОЗЕРО") return Habitat::LAKE;
    if (s == "OCEAN" || s == "ОКЕАН") return Habitat::OCEAN;
    if (s == "POND"  || s == "ПРУД")  return Habitat::POND;
    return Habitat::UNKNOWN;
}

// Абстрактный базовый класс — реализует общую часть интерфейса IAnimal.
// Поле name иммутабельно после конструирования.
class Animal : public IAnimal {
protected:
    const std::string name;

public:
    explicit Animal(const std::string& n) : name(n) {
        if (n.empty()) {
            throw std::invalid_argument("имя не указано");
        }
    }

    [[nodiscard]] const std::string& getName() const override { return name; }

    // Базовая реализация matchField (общие поля: name, type).
    // Наследники могут расширять эту логику.
    [[nodiscard]] bool matchField(const std::string& field,
                                  const std::string& op,
                                  const std::string& value) const override;
};

// ===== Рыбы =====
class Fish : public Animal {
    const Habitat habitat;
public:
    Fish(const std::string& n, Habitat h)
        : Animal(n), habitat(h) {
        if (h == Habitat::UNKNOWN) {
            throw std::invalid_argument("место обитания не известно");
        }
    }

    [[nodiscard]] std::string getType() const override { return "FISH"; }
    [[nodiscard]] Habitat getHabitat() const { return habitat; }

    void print(std::ostream& os) const override {
        os << "[Рыба]  Название: " << name
           << "   Место обитания: " << habitatToString(habitat) << "\n";
    }

    [[nodiscard]] bool matchField(const std::string& field,
                                  const std::string& op,
                                  const std::string& value) const override;
};

// ===== Птицы =====
class Bird : public Animal {
    const double maxSpeed;
public:
    Bird(const std::string& n, double s)
        : Animal(n), maxSpeed(s) {
        if (s < 0) {
            throw std::invalid_argument("максимальная скорость должна быть >= 0");
        }
    }

    [[nodiscard]] std::string getType() const override { return "BIRD"; }
    [[nodiscard]] double getMaxSpeed() const { return maxSpeed; }

    void print(std::ostream& os) const override {
        os << "[Птица]  Название: " << name
           << "   Максимальтная скорость: " << maxSpeed << "\n";
    }

    [[nodiscard]] bool matchField(const std::string& field,
                                  const std::string& op,
                                  const std::string& value) const override;
};

// ===== Насекомые =====
class Insect : public Animal {
    const double size;
    const std::string date; // дата в формате YYYY-MM-DD
public:
    Insect(const std::string& n, double sz, const std::string& d)
        : Animal(n), size(sz), date(d) {
        if (sz < 0) {
            throw std::invalid_argument("размер должен быть >= 0");
        }
        if (d.empty()) {
            throw std::invalid_argument("дата не указана");
        }
    }

    [[nodiscard]] std::string getType() const override { return "INSECT"; }
    [[nodiscard]] double getSize() const { return size; }
    [[nodiscard]] const std::string& getDate() const { return date; }

    void print(std::ostream& os) const override {
        os << "[Насекомое]  Название: " << name
           << "   Размер: " << size
           << "   Дата обнаружения: " << date << "\n";
    }

    [[nodiscard]] bool matchField(const std::string& field,
                                  const std::string& op,
                                  const std::string& value) const override;
};

#endif
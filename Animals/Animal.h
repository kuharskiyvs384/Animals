#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>

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

// Абстрактный базовый класс
class Animal {
protected:
    std::string name;
public:
    explicit Animal(const std::string& n) : name(n) {}
    virtual ~Animal() = default;

    // [Cppcheck fix] возврат по const-ссылке вместо копии
    [[nodiscard]] const std::string& getName() const { return name; }

    [[nodiscard]] virtual std::string getType() const = 0;
    virtual void print(std::ostream& os) const = 0;

    // Проверка соответствия условию для команды REM
    // field — имя поля, op — оператор, value — значение
    [[nodiscard]] virtual bool matchField(const std::string& field,
                                          const std::string& op,
                                          const std::string& value) const;
};

// ===== Рыбы =====
class Fish : public Animal {
    Habitat habitat;
public:
    Fish(const std::string& n, Habitat h) : Animal(n), habitat(h) {}

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
    double maxSpeed;
public:
    Bird(const std::string& n, double s) : Animal(n), maxSpeed(s) {}

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
    double size;
    std::string date; // дата в формате YYYY-MM-DD
public:
    Insect(const std::string& n, double sz, const std::string& d)
        : Animal(n), size(sz), date(d) {}

    [[nodiscard]] std::string getType() const override { return "INSECT"; }
    [[nodiscard]] double getSize() const { return size; }

    // [Cppcheck fix] возврат по const-ссылке вместо копии
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
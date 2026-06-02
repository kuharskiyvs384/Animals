#ifndef IANIMAL_H
#define IANIMAL_H

#include <string>
#include <iostream>

// Чисто абстрактный интерфейс для всех животных.
// Описывает контракт, не содержит данных.
class IAnimal {
public:
    virtual ~IAnimal() = default;

    [[nodiscard]] virtual const std::string& getName() const = 0;
    [[nodiscard]] virtual std::string getType() const = 0;

    virtual void print(std::ostream& os) const = 0;

    // Проверка соответствия условию для команды REM:
    // field — имя поля, op — оператор сравнения, value — значение
    [[nodiscard]] virtual bool matchField(const std::string& field,
                                          const std::string& op,
                                          const std::string& value) const = 0;
};

#endif
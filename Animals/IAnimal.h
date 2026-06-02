#ifndef IANIMAL_H
#define IANIMAL_H

#include <string>
#include <iosfwd>

// Чисто абстрактный интерфейс для всех животных.
class IAnimal {
public:
    virtual ~IAnimal() = default;

    [[nodiscard]] virtual const std::string& getName() const = 0;
    [[nodiscard]] virtual std::string getType() const = 0;

    virtual void print(std::ostream& os) const = 0;

    [[nodiscard]] virtual bool matchField(const std::string& field,
                                          const std::string& op,
                                          const std::string& value) const = 0;
};

#endif
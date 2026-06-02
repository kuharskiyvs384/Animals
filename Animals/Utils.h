#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <optional>
#include <cstddef>

// Безопасный парсинг строки в double.
// Возвращает std::nullopt, если:
//  - строка содержит нечисловые символы;
//  - значение выходит за пределы диапазона double;
//  - строка пустая или содержит лишний "хвост" (например, "12.3abc").
inline std::optional<double> tryParseDouble(const std::string& s) {
    if (s.empty()) return std::nullopt;
    try {
        std::size_t pos = 0;
        double v = std::stod(s, &pos);
        if (pos != s.size()) return std::nullopt;  // лишние символы после числа
        return v;
    } catch (...) {
        return std::nullopt;
    }
}

#endif
#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AnimalsTests {

    TEST_CLASS(UtilsTests) {
    public:
        TEST_METHOD(TryParseDouble_ValidNumber_ReturnsValue) {
            auto v = tryParseDouble("3.14");
            Assert::IsTrue(v.has_value());
            Assert::AreEqual(3.14, v.value(), 1e-9);
        }

        TEST_METHOD(TryParseDouble_Integer_ReturnsValue) {
            auto v = tryParseDouble("42");
            Assert::IsTrue(v.has_value());
            Assert::AreEqual(42.0, v.value(), 1e-9);
        }

        TEST_METHOD(TryParseDouble_NegativeNumber_ReturnsValue) {
            auto v = tryParseDouble("-7.5");
            Assert::IsTrue(v.has_value());
            Assert::AreEqual(-7.5, v.value(), 1e-9);
        }

        TEST_METHOD(TryParseDouble_Empty_ReturnsNullopt) {
            auto v = tryParseDouble("");
            Assert::IsFalse(v.has_value());
        }

        TEST_METHOD(TryParseDouble_NotANumber_ReturnsNullopt) {
            auto v = tryParseDouble("abc");
            Assert::IsFalse(v.has_value());
        }

        TEST_METHOD(TryParseDouble_TrailingGarbage_ReturnsNullopt) {
            auto v = tryParseDouble("12.3abc");
            Assert::IsFalse(v.has_value());
        }
    };
}
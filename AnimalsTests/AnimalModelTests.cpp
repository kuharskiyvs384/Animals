#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AnimalsTests {

    TEST_CLASS(AnimalModelTests) {
    public:
        // ===== Fish =====
        TEST_METHOD(CreateValidFish_InitializesCorrectly) {
            Fish f("Карп", Habitat::RIVER);
            Assert::AreEqual(std::string("Карп"), f.getName());
            Assert::AreEqual(std::string(AnimalTypes::FISH), f.getType());
            Assert::IsTrue(f.getHabitat() == Habitat::RIVER);
        }

        TEST_METHOD(Fish_UnknownHabitat_ThrowsInvalidArgument) {
            Assert::ExpectException<std::invalid_argument>([] {
                Fish f("Карп", Habitat::UNKNOWN);
            });
        }

        // ===== Bird =====
        TEST_METHOD(CreateValidBird_InitializesCorrectly) {
            Bird b("Сокол", 320.5);
            Assert::AreEqual(std::string("Сокол"), b.getName());
            Assert::AreEqual(std::string(AnimalTypes::BIRD), b.getType());
            Assert::AreEqual(320.5, b.getMaxSpeed(), 1e-9);
        }

        TEST_METHOD(Bird_NegativeSpeed_ThrowsInvalidArgument) {
            Assert::ExpectException<std::invalid_argument>([] {
                Bird b("Сокол", -10.0);
            });
        }

        // ===== Insect =====
        TEST_METHOD(CreateValidInsect_InitializesCorrectly) {
            Insect i("Жук", 2.5, "2024-05-12");
            Assert::AreEqual(std::string("Жук"), i.getName());
            Assert::AreEqual(std::string(AnimalTypes::INSECT), i.getType());
            Assert::AreEqual(2.5, i.getSize(), 1e-9);
            Assert::AreEqual(std::string("2024-05-12"), i.getDate());
        }

        TEST_METHOD(Insect_NegativeSize_ThrowsInvalidArgument) {
            Assert::ExpectException<std::invalid_argument>([] {
                Insect i("Жук", -1.0, "2024-01-01");
            });
        }

        TEST_METHOD(Insect_EmptyDate_ThrowsInvalidArgument) {
            Assert::ExpectException<std::invalid_argument>([] {
                Insect i("Жук", 2.5, "");
            });
        }

        // ===== Общий случай: пустое имя =====
        TEST_METHOD(EmptyName_Fish_ThrowsInvalidArgument) {
            Assert::ExpectException<std::invalid_argument>([] {
                Fish f("", Habitat::SEA);
            });
        }

        TEST_METHOD(EmptyName_Bird_ThrowsInvalidArgument) {
            Assert::ExpectException<std::invalid_argument>([] {
                Bird b("", 100.0);
            });
        }

        TEST_METHOD(EmptyName_Insect_ThrowsInvalidArgument) {
            Assert::ExpectException<std::invalid_argument>([] {
                Insect i("", 1.0, "2024-01-01");
            });
        }

        // ===== Конвертация Habitat <-> string =====
        TEST_METHOD(StringToHabitat_KnownStrings) {
            Assert::IsTrue(Habitat::RIVER == stringToHabitat("РЕКА"));
            Assert::IsTrue(Habitat::SEA   == stringToHabitat("SEA"));
            Assert::IsTrue(Habitat::LAKE  == stringToHabitat("ОЗЕРО"));
            Assert::IsTrue(Habitat::OCEAN == stringToHabitat("OCEAN"));
            Assert::IsTrue(Habitat::POND  == stringToHabitat("ПРУД"));
        }

        TEST_METHOD(StringToHabitat_Unknown_ReturnsUnknown) {
            Assert::IsTrue(Habitat::UNKNOWN == stringToHabitat("ABRACADABRA"));
        }

        TEST_METHOD(HabitatToString_ReturnsExpected) {
            Assert::AreEqual(std::string("РЕКА"),   habitatToString(Habitat::RIVER));
            Assert::AreEqual(std::string("МОРЕ"),   habitatToString(Habitat::SEA));
            Assert::AreEqual(std::string("ОЗЕРО"),  habitatToString(Habitat::LAKE));
        }

        // ===== Полиморфный print =====
        TEST_METHOD(Print_Fish_OutputsExpected) {
            Fish f("Карп", Habitat::RIVER);
            std::ostringstream os;
            f.print(os);
            std::string s = os.str();
            Assert::IsTrue(s.find("[Рыба]")    != std::string::npos);
            Assert::IsTrue(s.find("Карп")      != std::string::npos);
            Assert::IsTrue(s.find("РЕКА")      != std::string::npos);
        }
    };
}
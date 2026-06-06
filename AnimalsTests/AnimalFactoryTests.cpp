#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AnimalsTests {

    TEST_CLASS(AnimalFactoryTests) {
    public:
        TEST_METHOD(CreateFish_ValidParams_ReturnsFishInstance) {
            std::map<std::string, std::string> kv{
                {"name", "Тунец"}, {"habitat", "МОРЕ"}
            };
            auto a = AnimalFactory::create(AnimalTypes::FISH, kv);
            Assert::IsNotNull(a.get());
            Assert::AreEqual(std::string(AnimalTypes::FISH), a->getType());
            Assert::AreEqual(std::string("Тунец"), a->getName());
        }

        TEST_METHOD(CreateBird_ValidParams_ReturnsBirdInstance) {
            std::map<std::string, std::string> kv{
                {"name", "Орёл"}, {"maxspeed", "150.5"}
            };
            auto a = AnimalFactory::create(AnimalTypes::BIRD, kv);
            Assert::AreEqual(std::string(AnimalTypes::BIRD), a->getType());
            Bird* b = dynamic_cast<Bird*>(a.get());
            Assert::IsNotNull(b);
            Assert::AreEqual(150.5, b->getMaxSpeed(), 1e-9);
        }

        TEST_METHOD(CreateInsect_ValidParams_ReturnsInsectInstance) {
            std::map<std::string, std::string> kv{
                {"name", "Жук"}, {"size", "3.14"}, {"date", "2024-05-01"}
            };
            auto a = AnimalFactory::create(AnimalTypes::INSECT, kv);
            Assert::AreEqual(std::string(AnimalTypes::INSECT), a->getType());
        }

        TEST_METHOD(MissingNameField_ThrowsInvalidArgument) {
            std::map<std::string, std::string> kv{{"habitat", "МОРЕ"}};
            Assert::ExpectException<std::invalid_argument>([&] {
                AnimalFactory::create(AnimalTypes::FISH, kv);
            });
        }

        TEST_METHOD(MissingHabitatField_ThrowsInvalidArgument) {
            std::map<std::string, std::string> kv{{"name", "Карп"}};
            Assert::ExpectException<std::invalid_argument>([&] {
                AnimalFactory::create(AnimalTypes::FISH, kv);
            });
        }

        TEST_METHOD(InvalidSpeedFormat_ThrowsInvalidArgument) {
            std::map<std::string, std::string> kv{
                {"name", "Орёл"}, {"maxspeed", "abc"}
            };
            Assert::ExpectException<std::invalid_argument>([&] {
                AnimalFactory::create(AnimalTypes::BIRD, kv);
            });
        }

        TEST_METHOD(InvalidSizeFormat_ThrowsInvalidArgument) {
            std::map<std::string, std::string> kv{
                {"name", "Жук"}, {"size", "xyz"}, {"date", "2024-01-01"}
            };
            Assert::ExpectException<std::invalid_argument>([&] {
                AnimalFactory::create(AnimalTypes::INSECT, kv);
            });
        }

        TEST_METHOD(UnknownType_ThrowsRuntimeError) {
            std::map<std::string, std::string> kv{{"name", "X"}};
            Assert::ExpectException<std::runtime_error>([&] {
                AnimalFactory::create("DRAGON", kv);
            });
        }

        TEST_METHOD(UnknownHabitatValue_ThrowsInvalidArgument) {
            std::map<std::string, std::string> kv{
                {"name", "Карп"}, {"habitat", "КОСМОС"}
            };
            Assert::ExpectException<std::invalid_argument>([&] {
                AnimalFactory::create(AnimalTypes::FISH, kv);
            });
        }
    };
}
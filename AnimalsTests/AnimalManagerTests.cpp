#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AnimalsTests {

    TEST_CLASS(AnimalManagerTests) {
    public:
        // Хелпер — создать корректную команду ADD
        static ParsedCommand makeAdd(const std::vector<std::string>& tokens) {
            ParsedCommand pc;
            pc.command = "ADD";
            pc.tokens = tokens;
            return pc;
        }

        TEST_METHOD(Execute_AddValidFish_DoesNotThrow) {
            AnimalManager m;
            auto pc = makeAdd({"FISH", "name=Карп", "habitat=РЕКА"});
            m.execute(pc);  // не должно бросить исключений
        }

        TEST_METHOD(Execute_AddSeveralAnimals_DoesNotThrow) {
            AnimalManager m;
            m.execute(makeAdd({"FISH",   "name=Карп",  "habitat=РЕКА"}));
            m.execute(makeAdd({"BIRD",   "name=Сокол", "maxspeed=320"}));
            m.execute(makeAdd({"INSECT", "name=Жук",   "size=2.5", "date=2024-05-12"}));
        }

        TEST_METHOD(Execute_RemByCondition_RemovesMatching) {
            AnimalManager m;
            m.execute(makeAdd({"BIRD", "name=Воробей", "maxspeed=45"}));
            m.execute(makeAdd({"BIRD", "name=Сокол",   "maxspeed=320"}));

            ParsedCommand rem;
            rem.command = "REM";
            rem.tokens = {"maxspeed", ">", "100"};
            m.execute(rem);  // должно удалить Сокола, не бросать исключения
        }

        TEST_METHOD(Execute_PrintEmptyContainer_DoesNotThrow) {
            AnimalManager m;
            ParsedCommand pc;
            pc.command = "PRINT";
            m.execute(pc);
        }

        TEST_METHOD(Execute_UnknownCommand_ThrowsInvalidArgument) {
            AnimalManager m;
            ParsedCommand pc;
            pc.command = "FOO";
            Assert::ExpectException<std::invalid_argument>([&] {
                m.execute(pc);
            });
        }

        TEST_METHOD(Execute_AddWithoutType_ThrowsInvalidArgument) {
            AnimalManager m;
            ParsedCommand pc;
            pc.command = "ADD";
            Assert::ExpectException<std::invalid_argument>([&] {
                m.execute(pc);
            });
        }

        TEST_METHOD(Execute_RemWithTooFewArgs_ThrowsInvalidArgument) {
            AnimalManager m;
            ParsedCommand pc;
            pc.command = "REM";
            pc.tokens = {"name"};  // недостаточно
            Assert::ExpectException<std::invalid_argument>([&] {
                m.execute(pc);
            });
        }

        TEST_METHOD(Execute_RemByUnknownField_DoesNotRemove) {
            AnimalManager m;
            m.execute(makeAdd({"FISH", "name=Карп", "habitat=РЕКА"}));
            ParsedCommand rem;
            rem.command = "REM";
            rem.tokens = {"color", "==", "red"};
            m.execute(rem);  // должно безопасно выполниться (никого не удалить)
        }
    };
}
#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AnimalsTests {

    TEST_CLASS(CommandParserTests) {
    public:
        TEST_METHOD(Parse_AddCommand_SplitsCorrectly) {
            auto pc = CommandParser::parse("ADD FISH name=Карп habitat=РЕКА");
            Assert::AreEqual(std::string("ADD"), pc.command);
            Assert::AreEqual(size_t(3), pc.tokens.size());
            Assert::AreEqual(std::string("FISH"), pc.tokens[0]);
            Assert::AreEqual(std::string("name=Карп"), pc.tokens[1]);
            Assert::AreEqual(std::string("habitat=РЕКА"), pc.tokens[2]);
        }

        TEST_METHOD(Parse_RemCommand_SplitsCorrectly) {
            auto pc = CommandParser::parse("REM maxspeed > 100");
            Assert::AreEqual(std::string("REM"), pc.command);
            Assert::AreEqual(size_t(3), pc.tokens.size());
            Assert::AreEqual(std::string("maxspeed"), pc.tokens[0]);
            Assert::AreEqual(std::string(">"),        pc.tokens[1]);
            Assert::AreEqual(std::string("100"),      pc.tokens[2]);
        }

        TEST_METHOD(Parse_PrintCommand_NoTokens) {
            auto pc = CommandParser::parse("PRINT");
            Assert::AreEqual(std::string("PRINT"), pc.command);
            Assert::AreEqual(size_t(0), pc.tokens.size());
        }

        TEST_METHOD(Parse_EmptyLine_ReturnsEmptyCommand) {
            auto pc = CommandParser::parse("");
            Assert::IsTrue(pc.command.empty());
            Assert::AreEqual(size_t(0), pc.tokens.size());
        }

        TEST_METHOD(Parse_CommentLine_ReturnsEmptyCommand) {
            auto pc = CommandParser::parse("# это комментарий ADD FISH");
            Assert::IsTrue(pc.command.empty());
        }

        TEST_METHOD(ParseKV_NormalTokens_ReturnsMap) {
            std::vector<std::string> tokens{"name=Карп", "habitat=РЕКА", "size=2.5"};
            auto kv = CommandParser::parseKV(tokens);
            Assert::AreEqual(size_t(3), kv.size());
            Assert::AreEqual(std::string("Карп"), kv["name"]);
            Assert::AreEqual(std::string("РЕКА"), kv["habitat"]);
            Assert::AreEqual(std::string("2.5"),  kv["size"]);
        }

        TEST_METHOD(ParseKV_TokensWithoutEquals_AreIgnored) {
            std::vector<std::string> tokens{"name=Карп", "FISH", "habitat=РЕКА"};
            auto kv = CommandParser::parseKV(tokens);
            Assert::AreEqual(size_t(2), kv.size());
            Assert::IsTrue(kv.find("FISH") == kv.end());
        }

        TEST_METHOD(ParseKV_EmptyVector_ReturnsEmptyMap) {
            auto kv = CommandParser::parseKV({});
            Assert::AreEqual(size_t(0), kv.size());
        }
    };
}
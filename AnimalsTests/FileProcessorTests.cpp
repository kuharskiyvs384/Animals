#include "pch.h"
#include <cstdio>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AnimalsTests {

    TEST_CLASS(FileProcessorTests) {
    private:
        // Хелпер: создать временный файл с заданным содержимым
        static std::string createTempFile(const std::string& content) {
            std::string path = std::tmpnam(nullptr);
            std::ofstream out(path);
            out << content;
            out.close();
            return path;
        }

    public:
        TEST_METHOD(ProcessFile_ValidCommands_NoExceptions) {
            std::string content =
                "ADD FISH name=Карп habitat=РЕКА\n"
                "ADD BIRD name=Сокол maxspeed=320\n"
                "PRINT\n"
                "REM maxspeed > 100\n"
                "PRINT\n";
            auto path = createTempFile(content);

            AnimalManager m;
            FileProcessor fp(m);
            fp.processFile(path);  // не должно падать

            std::remove(path.c_str());
        }

        TEST_METHOD(ProcessFile_InvalidLine_ContinuesProcessing) {
            // Программа должна сообщить об ошибке, но продолжить со следующей строкой
            std::string content =
                "ADD BIRD name=Орёл maxspeed=abc\n"      // ошибка
                "ADD FISH name=Карп habitat=РЕКА\n";     // валидная
            auto path = createTempFile(content);

            AnimalManager m;
            FileProcessor fp(m);
            fp.processFile(path);  // не должно бросать исключения наружу

            std::remove(path.c_str());
        }

        TEST_METHOD(ProcessFile_NonExistentFile_DoesNotThrow) {
            AnimalManager m;
            FileProcessor fp(m);
            fp.processFile("nonexistent_file_xyz_12345.txt");  // вывод в stderr, но не падает
        }

        TEST_METHOD(ProcessFile_OnlyCommentsAndEmpty_NoExceptions) {
            std::string content =
                "# комментарий\n"
                "\n"
                "# ещё один\n";
            auto path = createTempFile(content);

            AnimalManager m;
            FileProcessor fp(m);
            fp.processFile(path);

            std::remove(path.c_str());
        }
    };
}
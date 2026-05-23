#include "../include/create.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <print>
#include <string>
#include <vector>

static void clearScreen() {
#ifdef _WIN32
    system("cls");
#elif defined(__linux__) || defined(__unix__)
    system("clear");
#endif
}

auto main() -> int {
    try {
        std::string fileName;
        std::print("Enter file name (without extension): ");
        std::getline(std::cin, fileName);
        clearScreen();

        ClassGenerator gen(fileName);

        std::string className;
        std::print("Class name: ");
        std::getline(std::cin, className);
        gen.setClassName(className);

        std::string baseClass;
        std::print("Base class (public inheritance, leave empty if none): ");
        std::getline(std::cin, baseClass);
        if (!baseClass.empty()) { gen.setBaseClass(baseClass); }

        // Ввод полей
        std::println("\n--- Define fields ---");
        std::println("For each field enter: type name [static] [mutable] [no_getter] [no_setter] [no_nodiscard]");
        std::println("Empty line finishes fields.");
        while (true) {
            std::string line;
            std::print("> ");
            std::getline(std::cin, line);
            if (line.empty()) { break; }

            Field f;
            std::vector<std::string> tokens;
            size_t pos = 0;
            while (pos < line.size()) {
                size_t const sp = line.find(' ', pos);
                if (sp == std::string::npos) {
                    tokens.push_back(line.substr(pos));
                    break;
                }
                tokens.push_back(line.substr(pos, sp - pos));
                pos = sp + 1;
            }

            if (tokens.size() < 2) {
                std::cerr << "  Error: need at least type and name\n";
                continue;
            }
            f.type = tokens[0];
            f.name = tokens[1];

            for (size_t i = 2; i < tokens.size(); ++i) {
                if (tokens[i] == "static") f.isStatic = true;
                else if (tokens[i] == "mutable") f.isMutable = true;
                else if (tokens[i] == "no_getter") f.generateGetter = false;
                else if (tokens[i] == "no_setter") f.generateSetter = false;
                else if (tokens[i] == "no_nodiscard") f.nodiscard = false;
                else std::cerr << "  Unknown flag: " << tokens[i] << "\n";
            }
            gen.addField(f);
            std::println("  Added field: {} {}", f.type, f.name);
        }

        // Ввод дополнительных методов
        std::println("\n--- Additional methods (enter signature, e.g. \"void foo() const override\") ---");
        std::println("Prefix with 'static ' if needed. Empty line to stop.");
        while (true) {
            std::print("> ");
            std::string sig;
            std::getline(std::cin, sig);
            if (sig.empty()) break;
            CustomMethod m;
            if (sig.rfind("static ", 0) == 0) {
                m.isStatic = true;
                sig = sig.substr(7); // remove "static "
            }
            m.signature = sig;
            gen.addCustomMethod(m);
        }

        // Настройки конструкторов
        std::string choice;
        std::print("\nGenerate default constructor? (y/n) [y]: ");
        std::getline(std::cin, choice);
        gen.setGenerateDefaultCtor(choice != "n");
        std::print("Generate parameterized constructor (all fields)? (y/n) [y]: ");
        std::getline(std::cin, choice);
        gen.setGenerateParamCtor(choice != "n");

        gen.generate();
        std::println("\nFiles {}.hpp and {}.cpp generated successfully.", fileName, fileName);
        std::println("You can now edit them to add more complex logic.");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#pragma once

#include <string>
#include <vector>
#include <unordered_set>

// Структуры для описания полей и методов
struct Field {
    std::string type;
    std::string name;
    bool isStatic = false;
    bool isMutable = false;
    bool generateGetter = true;
    bool generateSetter = true;
    bool nodiscard = true;
};

struct CustomMethod {
    std::string signature;   // полная сигнатура, например "void foo() const override"
    bool isStatic = false;
};

// Класс-генератор файлов .hpp и .cpp
class ClassGenerator {
public:
    explicit ClassGenerator(const std::string& fileName);

    void setClassName(const std::string& name);
    void setBaseClass(const std::string& base);
    void addField(const Field& f);
    void addCustomMethod(const CustomMethod& m);
    void setGenerateDefaultCtor(bool val);
    void setGenerateParamCtor(bool val);

    void generate();  // создаёт .hpp и .cpp

private:
    std::string fileName_;
    std::string className_;
    std::string baseClass_;
    std::vector<Field> fields_;
    std::vector<CustomMethod> customMethods_;
    bool genDefaultCtor_ = true;
    bool genParamCtor_ = true;

    static auto capitalize(const std::string& s) -> std::string;
    static auto neededHeader(const std::string& type) -> std::string;
    void collectHeaders(std::unordered_set<std::string>& headers) const;
};

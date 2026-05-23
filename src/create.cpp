#include "../include/create.hpp"
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_set>

// Вспомогательная функция: необходимые заголовки
auto ClassGenerator::neededHeader(const std::string& type) -> std::string {
    if (type.find("std::string") != std::string::npos) { return "#include <string>\n"; }
    if (type.find("std::vector") != std::string::npos) { return "#include <vector>\n"; }
    if (type.find("std::unique_ptr") != std::string::npos ||
        type.find("std::shared_ptr") != std::string::npos) { return "#include <memory>\n"; }
    if (type.find("uint") != std::string::npos ||
        type.find("int8_t") != std::string::npos ||
        type.find("int16_t") != std::string::npos ||
        type.find("int32_t") != std::string::npos ||
        type.find("int64_t") != std::string::npos ||
        type.find("uint8_t") != std::string::npos ||
        type.find("uint16_t") != std::string::npos ||
        type.find("uint32_t") != std::string::npos ||
        type.find("uint64_t") != std::string::npos){ return "#include <cstdint>\n"; }
    return "";
}

auto ClassGenerator::capitalize(const std::string& s) -> std::string {
    if (s.empty()) return s;
    std::string res = s;
    res[0] = std::toupper(res[0]);
    return res;
}

ClassGenerator::ClassGenerator(const std::string& fileName) : fileName_(fileName) {}

void ClassGenerator::setClassName(const std::string& name) { className_ = name; }
void ClassGenerator::setBaseClass(const std::string& base) { baseClass_ = base; }
void ClassGenerator::addField(const Field& f) { fields_.push_back(f); }
void ClassGenerator::addCustomMethod(const CustomMethod& m) { customMethods_.push_back(m); }
void ClassGenerator::setGenerateDefaultCtor(bool val) { genDefaultCtor_ = val; }
void ClassGenerator::setGenerateParamCtor(bool val) { genParamCtor_ = val; }

void ClassGenerator::collectHeaders(std::unordered_set<std::string>& headers) const {
    for (const auto& f : fields_) {
        std::string h = neededHeader(f.type);
        if (!h.empty()) headers.insert(h);
    }
    for (const auto& m : customMethods_) {
        if (m.signature.find("std::string") != std::string::npos) {
            headers.insert("#include <string>\n"); }
        if (m.signature.find("std::vector") != std::string::npos) {
            headers.insert("#include <vector>\n"); }
        if (m.signature.find("unique_ptr") != std::string::npos ||
            m.signature.find("shared_ptr") != std::string::npos) {
            headers.insert("#include <memory>\n"); }
    }
}

auto ClassGenerator::generate() -> void{
    std::unordered_set<std::string> headers;
    collectHeaders(headers);

    // --- Запись .hpp ---
    std::ofstream hpp(fileName_ + ".hpp");
    if (!hpp) { throw std::runtime_error("Cannot create .hpp"); }
    hpp << "#pragma once\n";
    for (const auto& h : headers) { hpp << h; }
    hpp << "\n";

    hpp << "class " << className_;
    if (!baseClass_.empty()){ hpp << " : public " << baseClass_; }
    hpp << " {\npublic:\n";

    // Конструкторы
    if (genDefaultCtor_) { hpp << "    " << className_ << "() = default;\n"; }
    if (genParamCtor_ && !fields_.empty()) {
        hpp << "    explicit " << className_ << "(";
        bool first = true;
        for (const auto& f : fields_) {
            if (f.isStatic) { continue; }
            if (!first) { hpp << ", "; }
            hpp << f.type << " " << f.name;
            first = false;
        }
        hpp << ")\n        : ";
        first = true;
        for (const auto& f : fields_) {
            if (f.isStatic) { continue; }
            if (!first) { hpp << ", "; }
            hpp << f.name << "_(" << f.name << ")";
            first = false;
        }
        hpp << " {}\n";
    }
    hpp << "\n";

    // Геттеры/сеттеры
    for (const auto& f : fields_) {
        if (f.isStatic) { continue; }
        if (f.generateGetter) {
            if (f.nodiscard) { hpp << "    [[nodiscard]] "; }
            hpp << "const " << f.type << "& get" << capitalize(f.name) << "() const { return " << f.name << "_; }\n";
        }
        if (f.generateSetter) {
            hpp << "    void set" << capitalize(f.name) << "(const " << f.type << "& value) { " << f.name << "_ = value; }\n";
        }
    }
    hpp << "\n";

    // Пользовательские методы
    for (const auto& m : customMethods_) {
        if (m.isStatic) { hpp << "    static "; }
        hpp << "    " << m.signature << ";\n";
    }
    hpp << "\n";

    // Статические поля (объявления)
    for (const auto& f : fields_) {
        if (f.isStatic) {
            hpp << "    static " << f.type << " " << f.name << "_;\n";
        }
    }
    hpp << "\nprivate:\n";
    for (const auto& f : fields_) {
        if (!f.isStatic) {
            if (f.isMutable) { hpp << "    mutable "; }
            hpp << f.type << " " << f.name << "_;\n";
        }
    }
    hpp << "};\n";
    hpp.close();

    // --- .cpp файл ---
    std::ofstream cpp(fileName_ + ".cpp");
    if (!cpp) { throw std::runtime_error("Cannot create .cpp"); }
    cpp << "#include \"" << fileName_ << ".hpp\"\n\n";
    for (const auto& f : fields_) {
        if (f.isStatic) {
            cpp << f.type << " " << className_ << "::" << f.name << "_ = {};\n";
        }
    }
    cpp.close();
}

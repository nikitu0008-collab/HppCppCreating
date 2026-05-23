# 🚀 C++ Class Generator — Automated Modern C++ Code Creator

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](http://makeapullrequest.com)

> **Stop writing boilerplate. Start creating.**  
> Generate complete, production‑ready C++ classes with getters, setters, `[[nodiscard]]`, `static` members, inheritance, and smart pointers — all in seconds.

## ✨ Features

- ✅ **Automatic getter/setter generation** with `[[nodiscard]]` support
- ✅ **Modern C++ awareness** – detects `std::string`, `std::vector`, `<cstdint>`, `<memory>` and adds required `#include`s
- ✅ **Constructor generation** – default and parameterized (all fields)
- ✅ **Static fields & methods** – define once, use everywhere
- ✅ **Inheritance** – single public base class
- ✅ **`const` / `constexpr` / `override` / `virtual`** – you provide the signature, we generate the stub
- ✅ **Smart pointers ready** – `std::unique_ptr`, `std::shared_ptr`
- ✅ **Zero external dependencies** – just a C++23 compiler
- ✅ **Cross‑platform** – Windows (cl.exe, MinGW) and Linux/macOS

## 🎯 What You Get

**Input** (interactive session):

Class name: Player
Base class: Entity
Fields:

    std::string name mutable
    int health no_setter
    static uint64_t totalPlayers static

Methods:

    virtual void attack(int damage) = 0
    static void printCount()


**Output** (`Player.hpp` + `Player.cpp`):

```cpp
#pragma once
#include <string>
#include <cstdint>

class Player : public Entity {
public:
    Player() = default;
    explicit Player(std::string name, int health)
        : name_(name), health_(health) {}

    [[nodiscard]] const std::string& getName() const { return name_; }
    void setName(const std::string& value) { name_ = value; }
    [[nodiscard]] const int& getHealth() const { return health_; }

    virtual void attack(int damage) = 0;
    static void printCount();

    static uint64_t totalPlayers_;

private:
    mutable std::string name_;
    int health_;
};

cpp

#include "Player.hpp"

uint64_t Player::totalPlayers_ = {};

📦 Installation
Clone and compile

git clone https://github.com/yourusername/cpp-class-generator.git
cd cpp-class-generator
mkdir build && cd build
cmake ..
make

Or simply compile manually (no CMake required)

g++ -std=c++23 -Iinclude -o cpp_class_gen main.cpp src/class_generator.cpp

Run

./cpp_class_gen

🖥️ Usage Example

Enter file name (without extension): MyAwesomeClass
Class name: MyAwesomeClass
Base class (public inheritance, leave empty if none): 

--- Define fields ---
For each field enter: type name [static] [mutable] [no_getter] [no_setter] [no_nodiscard]
Empty line finishes fields.
> std::string title
  Added field: std::string title
> double score mutable no_setter
  Added field: double score
> static int instanceCount static
  Added field: static int instanceCount

--- Additional methods (enter signature, e.g. "void foo() const override") ---
Prefix with 'static ' if needed. Empty line to stop.
> constexpr int magic() const noexcept
> static void showStats()

Generate default constructor? (y/n) [y]: 
Generate parameterized constructor (all fields)? (y/n) [y]: y

Files MyAwesomeClass.hpp and MyAwesomeClass.cpp generated successfully.

🛠️ Advanced Capabilities
Feature	How to use
Virtual method	virtual void update(float dt) = 0
Constexpr method	constexpr int getValue() const
Override	void draw() const override
No getter for a field	append no_getter
No setter	append no_setter
Disable [[nodiscard]] on getter	append no_nodiscard
Mutable field	append mutable
Static field / method	append static or prefix method with static
📁 Project Structure

cpp-class-generator/
├── include/
│   └── class_generator.hpp    # Public API
├── src/
│   └── class_generator.cpp    # Implementation
├── main.cpp                   # Interactive CLI
├── CMakeLists.txt
└── README.md

🤝 Contributing

PRs are welcome! Please open an issue first to discuss what you'd like to change.

Areas to extend:

    Multiple inheritance

    Move constructor / assignment generation

    Custom constructor signatures (not just all fields)

    Template class support

    noexcept specification inference

📄 License

MIT © 2025 Your Name
⭐ Star History

If this tool saves you time, give it a star on GitHub! ⭐

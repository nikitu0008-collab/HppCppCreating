cmake_minimum_required(VERSION 3.20)  # Минимальная версия для C++26 (реально 3.30+ лучше, но 3.20 достаточно для установки стандарта)
project(FileCreator LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    main.cpp
    src/create.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

# Устанавливаем стандарт C++26 (поддерживается в CMake 3.30+ для явного 26, но для более старых версий можно использовать "c++26")
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 26
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

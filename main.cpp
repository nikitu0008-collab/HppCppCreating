#include <stdexcept>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <print>
#include <fstream>
#include <vector>

//#include "include/create.hpp"

//TODO сначало ВСЮ реализацию сделаю здесь потом перенесу под hpp и классы и тд

static auto funcClear()->void{
    #ifdef _WIN32
        system("cls");
    #elif defined(__linux__)
        system("clear");
    #endif
}
//TODO записи можно делать сразу после ответа пользователя веть тут нет меню
auto main() -> int {
    uint16_t col_class, col_method, type_method;
    std::string name_file, name;

    std::vector<std::string> name_class;

    std::print("Enter name file: ");
    std::getline(std::cin, name_file);
   
    funcClear();

    std::fstream hpp(name_file + ".hpp");
    std::fstream cpp(name_file + ".cpp");
    if(!hpp.is_open()){
        throw std::runtime_error("file not creating or opening");
    } else if(!cpp.is_open()){
        throw std::runtime_error("file not creating or opening");
    }

    std::print("enter quantity class: ");
    std::cin >> col_class;

    for(size_t i = 0; i < col_class ; i++){
        std::print("class {}\n\tname: ",i + 1);
        std::cin >> name;
        hpp << "class " << name << "{" 
        cpp << "class " << name_file << "::" << 
        name_class.emplace_back(name);
        
        std::print("Enter quantity private variables\n>_:");
        std::cin >> quantity_private;

        for(size_t i = 0 ; i < quantity_private ; i++){

            std::println("enter private type variables"
                    "(1.std::string 2.double 3.int 4.bool 5.char 6.float)"
                    ": ");
            std::cin >> type_variables;
            switch(type_variables){
                case 1: 
                    variables.emplace_back("std::string");
                    std::print("Enter name: ");
                    std::getline(std::cin, name);
                    break; 
                case 2: variables.emplace_back("double");
                    break;
                case 3: variables.emplace_back("int");
                    break;
                case 4: variables.emplace_back("bool");
                    break;
                case 5: variables.emplace_back("char");
                    break;
                case 6: variables.emplace_back("float");
                    break;
                default:
                    std::cerr << "Error choice" << std::endl;
                    break;
            }
        }
        std::print("Enter col method: ");
        std::cin >> col_method;
        for(size_t i = 0 ; i < col_method ; i++){
            std::print("[1.void][2.float][3.int][4.double][5.std::string]"
                    ":_>"
                    );
            std::cin >> type_method;
            switch(type_method){
                case 1: method.emplace_back("void");
                break;
                case 2: method.emplace_back("float");
                break;
                case 3: method.emplace_back("int");
                break;
                case 4: method.emplace_back("double");
                break;
                case 5: method.emplace_back("std::string");
                break;
                default:
                std::cerr << "Error type method" << std::endl;
                break;
            }
        }
        //hpp
        hpp << "#pragma once" << std::endl;
        if(type_method == "std::string" or type_variables == "std::string"){
            hpp << "#include <string>" << std::endl;
        } else if(type_variables == "uint16_t"){ //другие тоже доделать
            hpp << "#include <cstdint>" << std::endl;    
        }
        hpp << "class " << name_class << "{"
            << "    public:"
            << "        " << name_class << "(){}"
            << "        ~" << name_class << "(){}"
            <<""
            <<"         " << type_method << " " << name_method << "(){}" 
            <<"     private:"
            <<"     " << type_variables[i] << " " << name_variables[i];
        hpp.close();
        //cpp
        cpp << "#include \"" << name_file<< ".hpp \"" << std::endl;
        if(type_method == "std::string" or type_variables == "std::string"){
            cpp << "#include <string>" << std::endl;
        }

        cpp.close();
    }
    
    return EXIT_SUCCESS;
};
//TODO сначало разобраться с реализацией в hpp потом только в cpp
//Так-как в cpp легче будет делать дальнейшие действия

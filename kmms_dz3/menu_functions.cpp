#include "menu_functions.hpp"
#include "menu_parts.hpp"

namespace yenni {
    const MenuPart *exit(const MenuPart *current) {
        std::exit(0);
    }
    const MenuPart *show_menu(const MenuPart *current) {
        std::cout << "Супер крутое меню!1!1!!!1 " << std::endl;
        for(int i = 1; i < current->children_count; i++) {
            std::cout << current->children[i]->title << std::endl;
        }
        std::cout << current->children[0]->title << std::endl;

        int input;
        std::cin >> input;
        std::cout << std::endl;

        return current->children[input];
    }
    const MenuPart *plus(const MenuPart *current) {
        int num1, num2;
        std::cout << "Введите инт1 и инт2 " << std::endl;
        std::cin >> num1 >> num2;
        std::cout << num1 + num2 << std::endl;
        return current->parent;
    }
    const MenuPart *minus(const MenuPart *current) {
        int num1, num2;
        std::cout << "Введите инт1 и инт2 " << std::endl;
        std::cin >> num1 >> num2;
        std::cout << num1 - num2 << std::endl;
        return current->parent;
    }
    const MenuPart *go_main(const MenuPart *current) {
        return current->parent;
    }
}
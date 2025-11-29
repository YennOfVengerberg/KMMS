#include "menu_functions.hpp"

namespace yenni {
    const MenuPart *exit(const MenuPart *current) {
        std::cout << "Еду домой... " << std::endl;
        std::exit(0);
    }
    const MenuPart *show_menu(const MenuPart *current) {
        std::cout << "Карта России " << std::endl;
        for(int i = 1; i < current->children_count; i++) {
            std::cout << current->children[i]->title << std::endl;
        }
        std::cout << current->children[0]->title << std::endl;

        int input;
        std::cin >> input;
        std::cout << std::endl;

        return current->children[input];
    }
    const MenuPart *go_parent(const MenuPart *current) {
        return current->parent;
    }
    const MenuPart *vlad_info(const MenuPart *current) {
        std::cout << "Тут что-то про Владивосток " << std::endl;
        return current->parent;
    }
    const MenuPart *sakh_info(const MenuPart *current) {
        std::cout << "Сахалин где-то там " << std::endl;
        return current->parent;
    }
    const MenuPart *khab_info(const MenuPart *current) {
        std::cout << "Хабаровск " << std::endl;
        return current->parent;
    }
}
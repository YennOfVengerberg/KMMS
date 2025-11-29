#ifndef MENU_FUNCTIONS_HPP
#define MENU_FUNCTIONS_HPP

#include <iostream>

#include "menu_struct.hpp"

namespace yenni {
    const MenuPart *exit(const MenuPart *current);
    const MenuPart *show_menu(const MenuPart *current);
    const MenuPart *go_parent(const MenuPart *current);
    const MenuPart *vlad_info(const MenuPart *current);
    const MenuPart *sakh_info(const MenuPart *current);
    const MenuPart *khab_info(const MenuPart *current);
}

#endif
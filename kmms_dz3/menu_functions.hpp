#ifndef MENU_FUNCTIONS_HPP
#define MENU_FUNCTIONS_HPP

#include <iostream>

#include "menu_struct.hpp"

namespace yenni {
    const MenuPart *exit(const MenuPart *current);
    const MenuPart *show_menu(const MenuPart *current);
    const MenuPart *plus(const MenuPart *current);
    const MenuPart *minus(const MenuPart *current);
    const MenuPart *go_main(const MenuPart *current);
}

#endif
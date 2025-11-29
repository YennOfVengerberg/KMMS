#ifndef MENU_STRUCT_HPP
#define MENU_STRUCT_HPP

namespace yenni {
    struct MenuPart {
        const char *const title;
        const MenuPart *(*function)(const MenuPart *current);

        const MenuPart *parent;

        const MenuPart *const *children;
        const int children_count;        
    };
}

#endif
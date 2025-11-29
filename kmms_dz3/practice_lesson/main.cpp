#include "menu_functions.hpp"
#include "menu_parts.hpp"
#include "menu_struct.hpp"
//задача 4
int main() {
    const yenni::MenuPart *current = &yenni::MAIN_MENU;
    do {
        current = current->function(current);
    } while(true);
}
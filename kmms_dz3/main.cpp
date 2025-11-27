#include <iostream>

struct MenuPart {
    const char *const title;
    const MenuPart* (*function)(const MenuPart *current);

    const MenuPart *const *children;
    const int children_count;

    const MenuPart *parent;
};

namespace yenni {
    const MenuPart *exit(const MenuPart *current) {
        std::exit(0);
    }
    const MenuPart *show_menu(const MenuPart *current) {
        std::cout << "Супер крутое меню!3131 " << std::endl;
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
        std::cout << current->title << std::endl;
        return current->parent;
    }
    const MenuPart *minus(const MenuPart *current) {
        std::cout << current->title << std::endl;
        return current->parent;
    }
    const MenuPart *go_main(const MenuPart *current) {
        return current->parent->parent;
    }
}

int main() {
    int input;

    MenuPart study_p = {"2 + ", yenni::plus};
    MenuPart study_m = {"1 - ", yenni::minus};
    MenuPart go_main = {"0 go main", yenni::go_main};

    MenuPart *study_children[] = {
        &go_main,
        &study_p,
        &study_m
        
        
    };
    const int study_size = sizeof(study_children)/sizeof(study_children[0]);

    
    MenuPart study = {"1 - study ", yenni::show_menu, study_children, study_size};
    MenuPart exit = {"0 exit ", yenni::exit};
    MenuPart *main_children[] = {&exit, &study};
    const int main_size = sizeof(main_children)/sizeof(main_children[0]);

    MenuPart main = {nullptr, yenni::show_menu, main_children, main_size};

    study_p.parent = &study;
    study_m.parent = &study;
    go_main.parent = &study;

    study.parent = &main;
    exit.parent = &main;
    const MenuPart *current = &main;
    do {
        current = current->function(current);
    } while(true);

}
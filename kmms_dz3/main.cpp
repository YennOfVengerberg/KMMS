#include <iostream>

struct MenuPart {
    const char *const title;
    void (*function)();
};

namespace yenni {
    void exit() {
        std::exit(0);
    }
    void study() {

    }
}

int main() {
    int input;

    MenuPart study = {"1 - study ", yenni::study};
    MenuPart exit = {"0 exit ", yenni::exit};

    MenuPart *main_children[] = {&exit, &study};
    const int main_size = sizeof(main_children)/sizeof(main_children[0]);
    do {
        std::cout << "Супер крутое меню!3131 " << std::endl;
        for(int i = 1; i < main_size; i++) {
            std::cout << main_children[i]->title << std::endl;
        }
        std::cout << main_children[0]->title << std::endl;
        std::cin >> input;
        main_children[input]->function();
        std::cout << std::endl;
    } while(true);

}
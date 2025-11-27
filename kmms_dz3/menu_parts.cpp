#include "menu_struct.hpp"
#include "menu_parts.hpp"
#include "menu_functions.hpp"

const yenni::MenuPart yenni::STUDY_PLUS = {"2 Поиграть с плюсиком", yenni::plus, &yenni::STUDY};
const yenni::MenuPart yenni::STUDY_MINUS = {"1 Сделать вычет", yenni::minus, &yenni::STUDY};
const yenni::MenuPart yenni::GO_MM = {"0 Рекурсия в начало ", yenni::go_main, &yenni::MAIN_MENU};

namespace {
    const yenni::MenuPart *const study_children[] = {
        &yenni::GO_MM,
        &yenni::STUDY_MINUS,
        &yenni::STUDY_PLUS
        
    };
    const int study_size = sizeof(study_children)/sizeof(study_children[0]);
}

const yenni::MenuPart yenni::STUDY = { "1 Попытаться не уснуть ", yenni::show_menu, &yenni::MAIN_MENU, study_children, study_size };
const yenni::MenuPart yenni::EXIT = { "0 Выключить компьютер ", yenni::exit };

namespace {
    const yenni::MenuPart *const main_children[] = {
        &yenni::EXIT,
        &yenni::STUDY
    };
    const int main_size = sizeof(main_children)/sizeof(main_children[0]);
}

const yenni::MenuPart yenni::MAIN_MENU = {nullptr, yenni::show_menu, nullptr, main_children, main_size};


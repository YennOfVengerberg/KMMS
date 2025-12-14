#include "menu_parts.hpp"
#include "menu_functions.hpp"

namespace yenni {

    const MenuPart VLAD = {"1 - Владивосток ", vlad_info, &FE};
    const MenuPart SAKH = {"2 - Сахалин ", sakh_info, &FE};
    const MenuPart KHAB = {"3 - Хабаровск ", khab_info, &FE};
    const MenuPart GO_BACK = {"0 - Выйти в предыдущее меню ", go_parent, &TRAVEL};

    namespace {
        const MenuPart *fe_children[] = {&GO_BACK, &VLAD, &SAKH, &KHAB};
        const int fe_size = sizeof(fe_children)/sizeof(fe_children[0]);
    }

    const MenuPart FE = {"1 - Дальний Восток ", show_fe_m, &TRAVEL, fe_children, fe_size};
    const MenuPart AL = {"2 - Алтай ", nullptr, &TRAVEL};
    const MenuPart RGR = {"3 - Золотое Кольцо России ", nullptr, &TRAVEL};
    const MenuPart GO_MM = {"0 - Выйти в главное меню ", go_parent, &MAIN_MENU};

    namespace {
        const MenuPart *travel_children[] = {&GO_MM, &FE, &AL, &RGR };
        const int travel_size = sizeof(travel_children)/sizeof(travel_children[0]);
    }

    const MenuPart EXIT = {"0 - Закончить путешествие ", exit};
    const MenuPart TRAVEL = {"1 - Путешествовать по России ", show_travel_m, nullptr, travel_children, travel_size};

    namespace {
        const MenuPart *mm_children[] = {&EXIT, &TRAVEL};
        const int mm_size = sizeof(mm_children)/sizeof(mm_children[0]);
    }
    const MenuPart MAIN_MENU = {nullptr, show_mm, nullptr, mm_children, mm_size};
}
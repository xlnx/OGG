#ifndef OGG_GRAPHIC_COMPONENT__BUTTON__HEADER_FILE____
#define OGG_GRAPHIC_COMPONENT__BUTTON__HEADER_FILE____
#include "graphic_components.h"
#include "graphic_component_shape.h"

    typedef void(*button_callback)(void);

    def_startup(
        button_callback callback;
    ) ogg_button_info;

    def_component_inh(ogg_rect,
        button_callback callback;
    ) ogg_button;

    ogg_button* create_button(const ogg_button_info* st);

#endif //OGG_GRAPHIC_COMPONENT__BUTTON__HEADER_FILE____
#ifndef OGG_GRAPHIC_COMPONENT__BUTTON__HEADER_FILE____
#define OGG_GRAPHIC_COMPONENT__BUTTON__HEADER_FILE____
#include "ogg_shape.h"

    typedef void(*button_callback)(void* self);

    def_startup_inh(ogg_button, ogg_rect) (
        ogg_color focused_color;
        button_callback callback;
    );

    def_component_inh(ogg_button, ogg_rect)(
        ogg_color default_color;
        ogg_color focused_color;
        button_callback callback;
    );

#endif //OGG_GRAPHIC_COMPONENT__BUTTON__HEADER_FILE____
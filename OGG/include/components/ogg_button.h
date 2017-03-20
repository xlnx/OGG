#ifndef OGG_GRAPHIC_COMPONENT__BUTTON__HEADER_FILE____
#define OGG_GRAPHIC_COMPONENT__BUTTON__HEADER_FILE____
#include "ogg_shape.h"

    typedef void(*button_callback)(void* self);

    def_startup(ogg_button) (
        button_callback callback;
    );

    def_component_inh(ogg_button, ogg_rect)(
        button_callback callback;
    );

    constructor(ogg_button);

#endif //OGG_GRAPHIC_COMPONENT__BUTTON__HEADER_FILE____
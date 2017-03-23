#ifndef OGG_GRAPHIC_COMPONENT__BUTTON__HEADER_FILE____
#define OGG_GRAPHIC_COMPONENT__BUTTON__HEADER_FILE____
#include "ogg_shape.h"

    typedef void(*button_callback)(void* self);

    typedef struct {
        const char* content;
        ogg_color color;
    } ogg_text;

    def_startup_inh(ogg_button, ogg_rect) (
        ogg_color focused_color;
        ogg_color down_color;
        ogg_text text;
        button_callback callback;
    );

    def_component_inh(ogg_button, ogg_rect)(
        ogg_color default_color;
        ogg_color focused_color;
        ogg_color down_color;
        ogg_text text;
        button_callback callback;
    );

    void ogg_paint_text(ogg_text* text, coordf pix);

    ogg_color ogg_make_color(int R, int G, int B);

#endif //OGG_GRAPHIC_COMPONENT__BUTTON__HEADER_FILE____
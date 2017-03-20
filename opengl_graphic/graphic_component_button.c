#include "graphic_component_button.h"

extern void destroy_shape(ogg_shape* shape);

extern void paint_shape(ogg_shape* shape);

static void button_click(ogg_button* button, va_list args, ogg_handle_flag *handled);

def_vtable(ogg_button) (
    destroy_shape,  // OGG_DESTROY_EVENT
    paint_shape,    // OGG_PAINT_EVENT
    0,              // OGG_KEYBOARD_EVENT
    0,              // OGG_SPECIAL_KEY_EVENT
    button_click,   // OGG_MOUSE_EVENT
    0,              // OGG_MOUSE_DRAG_EVENT
    0,              // OGG_MOUSE_MOVE_EVENT
    0,              // OGG_MOUSE_ENTRY_EVENT
);

def_constructor(ogg_button, args)
{
    this->callback = args->callback;
}

static void button_click(ogg_button* button, va_list args, ogg_handle_flag *handled)
{
    ogg_coord coord; coord.x = va_arg(args, int); coord.y = va_arg(args, int);
    if (1) {
        button->callback(button);
        *handled = ogg_true;
    }
}

#include "graphic_component_button.h"

extern void destroy_shape(ogg_shape* shape);

extern void paint_shape(ogg_shape* shape);

extern void create_rect_dest(ogg_rect* rect, const ogg_rect_info* st);

static void button_click(ogg_button* button, va_list args, ogg_handle_flag *handled);

static ogg_event_handler ogg_button_vtable[OGG_EVENT_COUNT] = {
    destroy_shape,  // OGG_DESTROY_EVENT
    paint_shape,    // OGG_PAINT_EVENT
    0,              // OGG_KEYBOARD_EVENT
    0,              // OGG_SPECIAL_KEY_EVENT
    button_click,   // OGG_MOUSE_EVENT
    0,              // OGG_MOUSE_DRAG_EVENT
    0,              // OGG_MOUSE_MOVE_EVENT
    0,              // OGG_MOUSE_ENTRY_EVENT
};

void create_button_dest(ogg_button* button, const ogg_button_info* st)
{
    create_rect_dest((ogg_rect*)button, (ogg_rect_info*)st);
    ((ogg_component*)button)->vptr = ogg_button_vtable;
    button->callback = st->callback;
}

ogg_button* create_button(const ogg_button_info* st)
{
    ogg_button *button = (ogg_button*)malloc(sizeof(ogg_button));
# ifdef DEBUG
    alloc_memory++;
# endif
    create_button_dest(button, st);
    return button;
}

static void button_click(ogg_button* button, va_list args, ogg_handle_flag *handled)
{
    ogg_coord coord; coord.x = va_arg(args, int); coord.y = va_arg(args, int);
    if (1) {
        button->callback();
        *handled = ogg_true;
    }
}